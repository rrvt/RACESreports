// RacesReportsView.cpp : implementation of the RacesReportsView class
//

#include "pch.h"
#include "RacesReportsView.h"
#include "OptionsDlg.h"
#include "Resource.h"
#include "RacesReports.h"
#include "RacesReportsDOC.h"
#include "RptOrientDlgTwo.h"


static TCchar* StsOrietnKey = _T("Status");


// RacesReportsView

IMPLEMENT_DYNCREATE(RacesReportsView, CScrView)

BEGIN_MESSAGE_MAP(RacesReportsView, CScrView)
  ON_COMMAND(ID_Options,     &onOptions)
  ON_COMMAND(ID_Orientation, &onRptOrietn)
END_MESSAGE_MAP()


void RacesReportsView::onOptions() {
OptionsDlg dlg;

  if (printer.name.isEmpty()) printer.load(0);

  if (dlg.DoModal() == IDOK) pMgr.setFontScale(printer.scale);
  }


void RacesReportsView::onRptOrietn() {
RptOrietnDlg dlg;

  dlg.lbl01 = _T("Store:");
  dlg.ntpd = printer.toStg(prtNote.prtrOrietn);
  dlg.rpt1 = printer.toStg(prtStatus.prtrOrietn);

  if (dlg.DoModal() == IDOK) {
    prtNote.prtrOrietn  = printer.toOrient(dlg.ntpd);
    prtStatus.prtrOrietn = printer.toOrient(dlg.rpt1);
    saveRptOrietn();
    }
  }


void RacesReportsView::initRptOrietn()
    {prtStatus.prtrOrietn = (PrtrOrient) iniFile.readInt(RptOrietnSect, StsOrietnKey, PortOrient);}


void RacesReportsView::saveRptOrietn()
     {saveNoteOrietn();   iniFile.write(RptOrietnSect, StsOrietnKey,  (int) prtStatus.prtrOrietn);}


void RacesReportsView::onPreparePrinting(CPrintInfo* info) {

  switch(doc()->dataSrc()) {
    case NotePadSrc : prtNote.onPreparePrinting(info);   break;
    case StsUpdtSrc : prtStatus.onPreparePrinting(info); break;
    }
  }


// Perpare output (i.e. report) then start the output with the call to SCrView

void RacesReportsView::onBeginPrinting() {

  switch(doc()->dataSrc()) {
    case NotePadSrc :
    case RestoreSrc : prtNote.onBeginPrinting(*this);   break;
    case StsUpdtSrc : prtStatus.onBeginPrinting(*this); break;
    }
  }


void RacesReportsView::onDisplayOutput() {

  switch(doc()->dataSrc()) {
    case NotePadSrc :
    case RestoreSrc : dspNote.display(*this);   break;
    case StsUpdtSrc : dspStatus.display(*this); break;
    }
  }



// The footer is injected into the printed output, so the output goes directly to the device.
// The output streaming functions are very similar to NotePad's streaming functions so it should
// not be a great hardship to construct a footer.

void RacesReportsView::printFooter(DevStream& dev, int pageNo) {prtNote.prtFooter(dev, pageNo);}



void RacesReportsView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) {

  CScrView::OnEndPrinting(pDC, pInfo);

  switch(doc()->dataSrc()) {
    case NotePadSrc :
    case RestoreSrc :
    case StsUpdtSrc : break;
    }
  }


void RacesReportsView::OnSetFocus(CWnd* pOldWnd) {

  CScrView::OnSetFocus(pOldWnd);

  switch(doc()->dataSrc()) {
    case NotePadSrc :
    case RestoreSrc :
    case StsUpdtSrc : break;
    }
  }


#ifdef _DEBUG
void RacesReportsView::AssertValid() const          {CScrollView::AssertValid();}
void RacesReportsView::Dump(CDumpContext& dc) const {CScrollView::Dump(dc);}

RacesReportsDOC* RacesReportsView::GetDocument() const
  {ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(RacesReportsDOC)));  return (RacesReportsDOC*)m_pDocument;}
#endif //_DEBUG
