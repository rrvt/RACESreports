

RacesReports.chm : *.htm RacesReports.hhp RacesReports.hhc App.css
  -1 "C:\Program Files (x86)\HTML Help Workshop\hhc" RacesReports


Clean.cln    :
  @echo "Cleaning"
  cd $(MAKEDIR)
  if exist RacesReports.chm del /F RacesReports.chm


Release/RacesReports.chm : RacesReports.chm
  copy $(MAKEDIR)\RacesReports.chm  $(MAKEDIR)\..\Release\RacesReports.chm


Release/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\Release
  if exist RacesReports.chm del /F RacesReports.chm
  cd $(MAKEDIR)


Debug/RacesReports.chm : RacesReports.chm
  copy $(MAKEDIR)\RacesReports.chm  $(MAKEDIR)\..\Debug\RacesReports.chm


Debug/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\Debug
  if exist RacesReports.chm del /F RacesReports.chm
  cd $(MAKEDIR)


Release/Rebuild.rbd : Release/Clean.cln Release/RacesReports.chm


Debug/Rebuild.rbd   : Debug/Clean.cln Debug/RacesReports.chm


