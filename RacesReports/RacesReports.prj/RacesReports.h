// RacesReports.h : main header file for the RacesReports application


#pragma once
#include "CApp.h"
#include "IniFile.h"


extern TCchar* GenFilePathKey;

class RacesReportsDOC;
class RacesReportsView;



class RacesReports : public CApp {

String programName;

public:

//String databasePath;

  RacesReports() : CApp(this) { }

  virtual BOOL InitInstance();

  void announceFinish();

  RacesReportsDOC*  doc()  {return (RacesReportsDOC*)  CApp::getDoc();}
  RacesReportsView* view() {return (RacesReportsView*) CApp::getView();}

  DECLARE_MESSAGE_MAP()

  afx_msg void refresh();
  afx_msg void OnAppAbout();

  afx_msg void OnHelp();

  friend  RacesReportsDOC* doc();
  };


extern RacesReports theApp;

inline void           invalidate() {theApp.invalidate();}
inline RacesReportsDOC*  doc()        {return theApp.doc();}
inline RacesReportsView* view()       {return theApp.view();}

