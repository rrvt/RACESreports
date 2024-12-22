// RacesReportsView.h : interface of the RacesReportsView class


#pragma once
#include "CScrView.h"
#include "ReportNtPd.h"
#include "StatusRpt.h"


class RacesReportsDOC;


class RacesReportsView : public CScrView {

StatusRpt  dspStatus;
StatusRpt  prtStatus;

protected: // create from serialization only

  RacesReportsView() : CScrView(), dspStatus(dMgr.getNotePad()), prtStatus(pMgr.getNotePad()) { }

  DECLARE_DYNCREATE(RacesReportsView)

// Attributes

public:

  virtual           ~RacesReportsView() { }

  virtual void       initNoteOrietn() { }
  virtual void       saveNoteOrietn() { }
  virtual void       initRptOrietn();
  virtual void       saveRptOrietn();
  virtual PrtrOrient getOrientation() {return prtNote.prtrOrietn;}

  virtual void       onDisplayOutput();
  virtual void       onPreparePrinting(CPrintInfo* info);
  virtual void       onBeginPrinting();

  virtual void       printFooter(DevStream& dev, int pageNo);
  virtual void       OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

  RacesReportsDOC*        GetDocument() const;


#ifdef _DEBUG

  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;

#endif
protected:

  DECLARE_MESSAGE_MAP()

  afx_msg void onOptions();
  afx_msg void onRptOrietn();
  afx_msg void OnSetFocus(CWnd* pOldWnd);
  };


#ifndef _DEBUG  // debug version in RacesReportsView.cpp
inline RacesReportsDOC* RacesReportsView::GetDocument() const
                                            {return reinterpret_cast<RacesReportsDOC*>(m_pDocument);}
#endif

