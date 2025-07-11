# RacesReports
Manipulate SJ RACES Database in a variety of ways:

  - Connect to the RACES database and show the number of records in each table
  - Load an attendance/activity csv file maintained by other members into the App.
  - Upload the information from the attendance/activity csv into the database
  - Produce Monthly update reports based on the database:
    * Excel compatible csv file, one line per member, all database fields
    * Google Earth csv file useful for updating Google Earth Pro with the locations of each
      member
    * Everbridge compatible csv file
    * Counts of members by readiness categories
    * List of FCC call signs
    * Member ID list in CSV format
    * Members Badge Expiration Date Sorted by
      * Call Sign
      * Expiration Date
    * Former Members Sorted by
      * Name
      * Call Sign
  - Save content of the window to a file (all reports are output to the window)
  - Display Options dialog
  - Print anything in the window

## Getting Started

RacesReports is composed of three projects and compiled with Visual Studio 2022.  The three
projects are:
  - RacesReports -- Solution File is in the ...\RacesReports\RacesReports\ folder.  It references the other two
    projects (Library and Installer)
  - Library -- This project produces a static library of which some object files are loaded into
    the executable and the msi (installer file)
  - Installer -- A Wix Toolset Installer.  Currently this file (Product.wxs) contains reference to only
    one file RacesReports.exe (and renames RacesReports on the desktop and elsewhere).  If you wish to change
    the installer then I suggest you look at WixApp.

### Prerequisites

Of course this all depends on having the SJ RACES database, a Visual Studio 2022 +/- and the ability to
debug if things don't go right.  The Extension "Wix Toolset visual Studio 2022 Extension" is also
required.  It can be found in "Tools/Extensions and Updates".

A version of the Data Access Object dynamic library must be on your system.  The library module,
AceDao.h, contains the following lines (which you may have to change):
```
#import <C:\Program Files (x86)\Microsoft Office\root\Office16\ACEDAO.DLL> rename(_T("EOF"), _T("DaoEof"))
using namespace DAO;
```
Here is an explanation of DAO:
```
   https://en.wikipedia.org/wiki/Data_access_object
```

All the code is contained in the two directories.

## Updates

### Update 7/8/25

Update Database objects to suppress memory leak reporting.  Factored IniFile into three classes.

### Update 12/26/24

Split the library into DocLib and Library where DocLib supports the MFC Document/Library App
projects and Library has support classes and supports the Dialog Apps with only one class.

### Update 12/22/24

Change the name from RWracesDB to RACESreports to better reflect that nature of the program.
Extensive rewrite of the display and print library.

### Fix Default Path Bug in Product.wxs.

### Update 10/30/24

Rename, fix NotePad archive.

### Update 8/7/24

Library update.

### Update 6/29/24

Add MIT License to installation.

### Update 6/14/24

Fix WinPos.

### Update 4/15/24

Add MyToolBar class to deal with the differences between Doc/View and Dialog Box Toolbars.

### Update 2/18/24

Reorganized the Library so that it compiles once into Debug and Release directories under the Library
directory.

### Update 1/8/24

Library and other changes.

### Update 12/25/23

Modify ExpandableP and subsequent ripple...

### Update 7/7/23

Library Update

### Update 3/30/23

Significant changes to the library and update the application to accomodate them.

### Update 11/10/22

Update help file icons.  Update Open/Save file function calls.  Replace stdafx.h with pch.h/framework.h.

### Update 10/24/22

Update toolbar background.  Adjust code that records position and size of window to fit the new library
module.

### Update 8/4/22

Minor Library Updates.

### Update 4/15/22

Big adventure in February when I started moving to a new Win11 and Visual Studio 2022.  I now
feel that this version is working in the new environment.  There were several changes made to the app
in order to compile properly on VS22.

### Update 01/31/22

Updates to the library, mostly about the toolbar, but also NewAllocator, and a minor addition to
Expandable.

Also scrubbed the project files to remove all references to precompiled header files which I turned off
in VS17.  Unfortnately VS does not remove all references and pch files kept cropping up.  Not only does
that slow down the compiler but the files are large...

### Update 12/22/21

While creating a template for a dialog box only application with a toolbar the Library was added to and
changed to hopefully simplify toolbar creation.  This version of the toolbar includes buttons, edit boxes,
combo boxes and drop down menus as well as the traditional 16x15 icons.

There are two drop down menus on the toolbar.

### Update 11/13/21

But the major changes are in the library:

  - Expandable and ExpandableP -- moved the functions out of the class to make the compilation smaller,
also fixed one bug (or feature) in the ExpandableP insert sorted function that would throw out entries
that were already in in the array.
  - FileIO -- Changed the type of path from "String&" to "TCchar*".  It turns out that automatic
conversion from String to TCchar* is easy, but the reverse is is not easy.  Also added a function to
get the length of a file given a path.
  - FineName -- Added a function to get the directory name of from a path
  - NewAllocator -- Corrected the debug dependency from if to ifdef
  - ToolBar -- Added data for drop down menus

### Update 10/31/21

Changed Resources (i.e. xxx.rc data) access so that it will work with a dll.  Changed the logic in the
About Box code.  Some other library changes.  Some corresponding changes in the application.

The member status is being kept in a different way now and changes were made to upload the new version.

Due to the Covid-19 rules at the San Jose EOC a list of qualified people needed to be generated to supply
people to the EOC during an emergency.  This list was sent to the city so that they could verify the
vaccination status of those individuals.  For the forseeable future no one will be allowed on city
property without being fully vaccinated.

### Update 5/20/21

Fixed a bug in delete dead records.  Also clear the internal database before loading a new one.  Ugh!

Also modified CodeGen to provide a clear function in the table modules.

### Update 4/20/21

CodeGen changed the names in fields to non-capitalized names and this caused changes in the application.
Also changed the handling of printer orientation in Printer Setup and the Options dialog.

### Update 2/10/21

Updated the icons on the toolbar.

### Update 2/3/21

While working on CodeGen to create a help file many changes in the database interface files
were made to simplify the interface to the c++ application and to make the inner workings more
secure (by hiding things from the c++ application).  The effect of trying to explain things
one notices things which it the light of day could be improved.  Just the name of things were
changed to reflect their real function in an application, moving things to put them in better
places as well as programming changes to improve the interfaces.

I also removed several out of date functions.  Having said that, they may come back sometime
in the future as the needs of the application/membership change.

### Update 1/22/21

Cleaned up the toolbar removing obsolete commands and adding icons for some of the CSV file
reports.  Added a help file.

### Update 11/25/20

Library improvement project integrated into this application.  Then I noticed that the Doc module had
too many unrelated functions.  This led to refactoring the program into many classes which are called
for the Doc module as a consequence of the user selecting a command.

### Update 9/27/20
Added a feature to display and save the non-former members for which badges may be created.  The list
may be sorted by expiration date of the badge or by the member's call sign.

### Update 9/10/20
Library improvement project.  Changed the Expandable Array classes, added templates for a pointer only
class in the ExpandableP class definition.  It turned out I was defining this RcdPtr class many times
worrying about exactly how it should be defined.  So I turned it into a template, which of course then
I needed to go back and add it to all the programs.  Severl iterations later I added some documentation
and I am uploading the programs today.

### August 16, 2020

Internal changes only.  Functionality is the same.

### July 20, 2020

The initial try at the Everbridge csv file had a couple of flaws.  Apparently there is some time when
the Access database shows a blank but RacesReports gets a zero.  Test for that and eliminate it from the
Everbridge output.  Also moved the END on the records to the same column as the END in the header.
Changed one of the header names too.


### July 16, 2020

The Chief Radio Officer (CRO) has the use of Everbridge, a management application used by Emergency Service
Agencies.  He needs the data from the SJ RACES database in a particular format to upload into Everbridge.
Recently he has discovered that the original csv file produced by RacesReports was not adequate for this
purpose.  The CRO did find a sample format for the file and RacesReports has been changed to provide the
correct input to Everbridge.  The CRO needs to test this version of the csv so while I am saving the
current version it remains to be seen if it is correct.

## Authors

Robert R. Van Tuyl, K6RWY, romeo romeo victor tango alpha tango sam whisky delta echo dot charlie oscar mike

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

