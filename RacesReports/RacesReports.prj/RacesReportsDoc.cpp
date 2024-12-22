// RacesReportsDOC.cpp : implementation of the RacesReportsDOC class
//

#include "pch.h"
#include "RacesReportsDOC.h"
#include "CntResponders.h"
#include "Copyfile.h"
#include "Database.h"
#include "DeadRcds.h"
#include "Everbridge.h"
#include "FileName.h"
#include "FCClist.h"
#include "GetPathDlg.h"
#include "GoogleRpt.h"
#include "MbrInfo.h"
#include "MbrSortList.h"
#include "MemberRpts.h"
#include "Resource.h"
#include "ResourceData.h"
#include "RacesReports.h"
#include "RacesReportsView.h"
#include "StatusUpdate.h"


enum {col2 = 10, col3 = 35, col4 = 58, col5 = 81};
enum ShowFeeType {NilShowFee, StableStable, StableTack, StableBedding, StableOther, OtherFees};

static TCchar* FileSection = _T("FileSection");
static TCchar* DBFileKey   = _T("DBfile");


IMPLEMENT_DYNCREATE(RacesReportsDOC, CDocument)

BEGIN_MESSAGE_MAP(RacesReportsDOC, CDocument)

  ON_COMMAND(ID_OpenDatabase,   &openDatabase)

  ON_COMMAND(ID_Status,         &OnLoadCSVfile)
  ON_COMMAND(ID_LoadCSVfile,    &OnLoadCSVfile)
  ON_COMMAND(ID_UploadToDB,     &OnUploadToDB)

  ON_COMMAND(ID_ExcelReport,    &OnExcelReport)
  ON_COMMAND(ID_GoogleEarth,    &OnGoogleEarth)
  ON_COMMAND(ID_Everbridge,     &OnEverbridge)
  ON_COMMAND(ID_CntResponders,  &OnCountResponders)
  ON_COMMAND(ID_FCC,            &OnFCCcallSigns)
  ON_COMMAND(ID_MemberIDs,      &OnMemberInfo)

  ON_COMMAND(ID_Badges,         &OnBadgesCS)
  ON_COMMAND(ID_BadgesCS,       &OnBadgesCS)
  ON_COMMAND(ID_BadgesDate,     &OnBadgesDT)

  ON_COMMAND(ID_FormerNm,       &OnFormerNm)
  ON_COMMAND(ID_Former,         &OnFormerNm)
  ON_COMMAND(ID_FormerCS,       &OnFormerCS)

  ON_COMMAND(ID_CovidList,      &OnCovidList)

  ON_COMMAND(ID_FILE_SAVE,      &onFileSave)

  ON_COMMAND(ID_MakeFileCopy,   &OnMakeFileCopy)
  ON_COMMAND(ID_Backup,         &OnBackup)
  ON_COMMAND(ID_Restore,        &OnRestoreNew)
  ON_COMMAND(ID_Comparison,     &OnComparison)

  ON_COMMAND(ID_FixDeadRcds,    &OnFixDeadRcds)
END_MESSAGE_MAP()


RacesReportsDOC::RacesReportsDOC() : dataSource(NotePadSrc), dbLoaded(false) {getTitle();}


void RacesReportsDOC::getTitle() {CString  ttl;   ttl.LoadString(AFX_IDS_APP_TITLE); title = ttl;}


void RacesReportsDOC::initDatabase() {

  if (!iniFile.readString(FileSection, DBFileKey, path)) return;

  loadDatabase();
  }


void RacesReportsDOC::openDatabase() {
PathDlgDsc dsc(_T("Database"), 0, _T("accdb"), _T("*.accdb"));

  notePad.clear();

  if (!setOpenPath(dsc)) return;

  iniFile.writeString(FileSection, DBFileKey, path);   loadDatabase();
  }


void RacesReportsDOC::loadDatabase() {

  dbLoaded = database.load(path);

  notePad << _T("Database at ") << path << (dbLoaded ? _T(" Loaded") : _T(" Not Loaded"));
  notePad << nCrlf;

  if (dbLoaded) {dbPath = path; mbrSortList.create();}

  display(NotePadSrc);
  }


void RacesReportsDOC::OnExcelReport() {
MemberRpts memberRpts(ExcelDspType);

  view()->setFont(_T("Arial"), 12.0);

  setFileSaveAttr(_T("Excel"), _T("csv"));   memberRpts.excel();      display(NotePadSrc);
  }


void RacesReportsDOC::OnCovidList() {
MemberRpts memberRpts(ExcelDspType);

  view()->setFont(_T("Arial"), 12.0);

  setFileSaveAttr(_T("CovidList"), _T("csv"));   memberRpts.covidList();      display(NotePadSrc);
  }


void RacesReportsDOC::OnComparison() {
MemberRpts memberRpts(CmpDspType);

  view()->setFont(_T("Arial"), 12.0);

  setFileSaveAttr(_T("Comparison"), _T("csv"));   memberRpts.comparison();     display(NotePadSrc);
  }


void RacesReportsDOC::OnMakeFileCopy() {
PathDlgDsc dsc(_T("Copy Database"), path, _T("accdb"), _T("*.accdb"));
String newPath;
String destinationFile;
String ext;
int    pos;

  if (!getOpenDlg(dsc, newPath)) return;

  pos = newPath.find_last_of(_T('.'));   if (pos < 0) pos = newPath.size();
  ext = newPath.substr(pos);
  destinationFile = newPath.substr(0, pos);   destinationFile += _T(" - Copy");   destinationFile += ext;

  if (!copyFile(newPath, destinationFile)) return;

  if (ext == ".accdb") {
    iniFile.writeString(FileSection, DBFileKey, destinationFile);
    }
  }


void RacesReportsDOC::OnBackup() {
MemberRpts dspMbrRcd(BkupDspType);

  view()->setFont(_T("Arial"), 12.0);

  setFileSaveAttr(_T("Backup"), _T("csv"));   dspMbrRcd.backup();      display(NotePadSrc);
  }


void RacesReportsDOC::OnRestoreNew() {display(NotePadSrc);}


void RacesReportsDOC::OnGoogleEarth() {
GoogleRpt rpt(ExcelDspType);

  view()->setFont(_T("Arial"), 12.0);

  setFileSaveAttr(_T("Google Report"), _T("csv"));   rpt();      display(NotePadSrc);
  }


void RacesReportsDOC::OnEverbridge() {
Everbridge rpt(ExcelDspType);

  view()->setFont(_T("Arial"), 12.0);

  setFileSaveAttr(_T("Everbridge"), _T("csv"));   rpt();      display(NotePadSrc);
  }


void RacesReportsDOC::OnCountResponders() {
CntResponders rpt;

  view()->setFont(_T("Arial"), 12.0);

  setFileSaveAttr(_T("ResponderCounts"), _T("txt"));   rpt();    display(NotePadSrc);
  }


void RacesReportsDOC::OnFCCcallSigns() {
FCClist fccList;

  view()->setFont(_T("Arial"), 12.0);

  setFileSaveAttr(_T("CallSigns"), _T("txt"));    fccList();      display(NotePadSrc);
  }



void RacesReportsDOC::OnMemberInfo() {
InfoRpts rpt;

  view()->setFont(_T("Arial"), 12.0);

  setFileSaveAttr(_T("MemberInfo"), _T("txt"));   rpt.info();  display(NotePadSrc);
  }


void RacesReportsDOC::OnBadgesCS() {
InfoRpts rpt;

  view()->setFont(_T("Courier New"), 12.0);

  setFileSaveAttr(_T("BadgesByCallSign"), _T("txt"));   rpt.dspBadges(BdgFCCSort);;

  display(NotePadSrc);
  }


void RacesReportsDOC::OnBadgesDT() {
InfoRpts rpt;

  view()->setFont(_T("Courier New"), 12.0);

  setFileSaveAttr(_T("BadgesByDate"), _T("txt"));   rpt.dspBadges(BdgDateSort);

  display(NotePadSrc);
  }


void RacesReportsDOC::OnFormerNm() {
InfoRpts rpt;

  view()->setFont(_T("Courier New"), 12.0);

  setFileSaveAttr(_T("FormerByName"), _T("txt"));   rpt.former(FmrNameSort);  display(NotePadSrc);
  }


void RacesReportsDOC::OnFormerCS() {
InfoRpts rpt;

  view()->setFont(_T("Courier New"), 12.0);

  setFileSaveAttr(_T("FormerByCallSign"), _T("txt"));   rpt.former(FmrFCCSort);

  display(NotePadSrc);
  }



void RacesReportsDOC::OnLoadCSVfile() {
PathDlgDsc   dsc(_T("Status Update csv File"), 0, _T("csv"), _T("*.csv"));
String       path;
StatusUpdate stsUpdt;

  dataSource = StsUpdtSrc;

  if (!setOpenPath(dsc)) return;

  OnOpenDocument(path);

  stsUpdt.isLoaded();   display(NotePadSrc);
  }


void RacesReportsDOC::OnUploadToDB() {
StatusUpdate stsUpdt;

  dataSource = StsUpdtSrc;   stsUpdt.store(path);   theApp.announceFinish();

  setFileSaveAttr(_T("StatusUpdate"), _T("txt"));   display(NotePadSrc);
  }


void RacesReportsDOC::OnFixDeadRcds() {
DeadRcds deadRcds;

  view()->setFont(_T("Arial"), 12.0);

  setFileSaveAttr(_T("DeadFields"), _T("txt"));     deadRcds.fix(path); invalidate();
  }


void RacesReportsDOC::display(DataSource ds) {dataSource = ds; invalidate();}


void RacesReportsDOC::onFileSave() {
String     name    = getMainName(dbPath) + sffx;
String     pattern = _T("*.") + fileType;
PathDlgDsc dsc(_T("Output File"), name, fileType, pattern);

  if (setSaveAsPath(dsc)) OnSaveDocument(path);
  }


// RacesReportsDOC serialization

void RacesReportsDOC::serialize(Archive& ar) {

  if (ar.isStoring()) notePad.archive(ar);

  else
    switch(dataSource) {
      case StsUpdtSrc : {StatusUpdate stsUpdt; stsUpdt.load(ar);  return;}
      }
  }




// RacesReportsDOC diagnostics

#ifdef _DEBUG
void RacesReportsDOC::AssertValid() const          {CDocument::AssertValid();}
void RacesReportsDOC::Dump(CDumpContext& dc) const {CDocument::Dump(dc);}
#endif //_DEBUG



