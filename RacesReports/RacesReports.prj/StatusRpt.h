// Status Report


#pragma once
#include "ReportNtPd.h"


class StatusRpt : public ReportNtPd {

public:

  StatusRpt(NotePad& notePad) : ReportNtPd(notePad) { }
 ~StatusRpt() { }

  int  header(NotePad& np, bool printing);

private:

  StatusRpt() : ReportNtPd(*(NotePad*)0) { }
  };

