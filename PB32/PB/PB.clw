; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPropOptionsDirectories
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "pb.h"
LastPage=0

ClassCount=14
Class1=CdlgEditLevel
Class2=CDlgSecLevels
Class3=CListBoxSecLev
Class4=CPBApp
Class5=CPropSheetOptions
Class6=CPropOptionsDirectories
Class7=CPropOptionsNewUsers
Class8=CPropOptionsSecurity
Class9=CAboutDlg
Class10=CPBStatusDlg

ResourceCount=24
Resource1=IDD_ABOUTBOX
Resource2=IDD_PROP_USERED_GENERAL
Resource3=IDD_MSGAREA
Resource4=IDD_PBWIN_DIALOG
Resource5=IDD_SECLEVELS
Resource6=IDD_PROP_OPT_SITEINFO
Resource7=IDD_PROP_OPT_DIRECTORIES
Resource8=IDD_PROP_OPT_SECURITY
Resource9=IDD_EDIT_SECLEVEL
Class11=CPropSiteInfo
Class12=CPropUserSecurity
Resource10=IDD_PROP_USERED_SECURITY
Resource11=IDD_AREAS
Class13=CDlgMsgAreas
Class14=CDlgEditMsgArea
Resource12=IDD_PROP_OPT_NEWUSERS
Resource13=IDD_PBWIN_DIALOG (English (U.S.))
Resource14=IDD_ABOUTBOX (English (U.S.))
Resource15=IDD_PROP_USERED_GENERAL (English (U.S.))
Resource16=IDD_PROP_USERED_SECURITY (English (U.S.))
Resource17=IDD_SECLEVELS (English (U.S.))
Resource18=IDD_EDIT_SECLEVEL (English (U.S.))
Resource19=IDD_PROP_OPT_DIRECTORIES (English (U.S.))
Resource20=IDD_PROP_OPT_NEWUSERS (English (U.S.))
Resource21=IDD_PROP_OPT_SECURITY (English (U.S.))
Resource22=IDD_PROP_OPT_SITEINFO (English (U.S.))
Resource23=IDD_MSGAREA (English (U.S.))
Resource24=IDD_AREAS (English (U.S.))

[CLS:CdlgEditLevel]
Type=0
BaseClass=CDialog
HeaderFile=dlgEditLevel.h
ImplementationFile=dlgEditLevel.cpp
Filter=D
VirtualFilter=dWC
LastObject=CdlgEditLevel

[CLS:CDlgSecLevels]
Type=0
BaseClass=CDialog
HeaderFile=DlgSecLevels.h
ImplementationFile=DlgSecLevels.cpp

[CLS:CListBoxSecLev]
Type=0
BaseClass=CListBox
HeaderFile=ListBoxSecLev.h
ImplementationFile=ListBoxSecLev.cpp

[CLS:CPBApp]
Type=0
BaseClass=CWinApp
HeaderFile=PB.h
ImplementationFile=PB.CPP

[CLS:CPropSheetOptions]
Type=0
BaseClass=CPropertySheet
HeaderFile=PropOptions.h
ImplementationFile=PropOptions.CPP

[CLS:CPropOptionsDirectories]
Type=0
BaseClass=CPropertyPage
HeaderFile=PropOptions.h
ImplementationFile=PropOptions.CPP
Filter=D
VirtualFilter=idWC
LastObject=IDC_ED_TXTFILES

[CLS:CPropOptionsNewUsers]
Type=0
BaseClass=CPropertyPage
HeaderFile=PropOptions.h
ImplementationFile=PropOptions.CPP
Filter=D
VirtualFilter=idWC
LastObject=CPropOptionsNewUsers

[CLS:CPropOptionsSecurity]
Type=0
BaseClass=CPropertyPage
HeaderFile=PropOptions.h
ImplementationFile=PropOptions.CPP
LastObject=CPropOptionsSecurity

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=StatDlg.cpp
ImplementationFile=StatDlg.cpp
LastObject=CAboutDlg

[CLS:CPBStatusDlg]
Type=0
BaseClass=CDialog
HeaderFile=StatDlg.h
ImplementationFile=StatDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_LB_SESSIONS

[DLG:IDD_EDIT_SECLEVEL]
Type=1
Class=CdlgEditLevel
ControlCount=7
Control1=IDC_LEVEL,edit,1350631552
Control2=IDC_DESCRIPTION,edit,1350631552
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352

[DLG:IDD_SECLEVELS]
Type=1
Class=CDlgSecLevels
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LEVELS,listbox,1352728787
Control4=IDC_EDIT,button,1342242816
Control5=IDC_NEW,button,1342242816
Control6=IDC_DELETE,button,1342242816

[DLG:IDD_PROP_OPT_DIRECTORIES]
Type=1
Class=CPropOptionsDirectories
ControlCount=10
Control1=IDC_ED_MSGBASE,edit,1350631552
Control2=IDC_STATIC,static,1342308352
Control3=IDC_ED_PEX,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_ED_MENUS,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_ED_TXTFILES,edit,1350631552
Control8=IDC_STATIC,static,1342308352
Control9=IDC_ED_BROW_MSGBASE,button,1342242816
Control10=IDC_ED_BROW_MSGBASE2,button,1342242816

[DLG:IDD_PROP_OPT_NEWUSERS]
Type=1
Class=CPropOptionsNewUsers
ControlCount=23
Control1=IDC_AVATAR,button,1342242819
Control2=IDC_ANSI,button,1342242819
Control3=IDC_ASKVOICE,button,1342242819
Control4=IDC_ASKDATAPHONE,button,1342242819
Control5=IDC_ASKFAXPHONE,button,1342242819
Control6=IDC_ASKBIRTHDATE,button,1342242819
Control7=IDC_ASKSTATE,button,1342242819
Control8=IDC_ASKCOUNTRY,button,1342242819
Control9=IDC_ASKADDRESS,button,1342242819
Control10=IDC_ASKSEX,button,1342242819
Control11=IDC_ASKDATEFMT,button,1342242819
Control12=IDC_LOGLEVEL,combobox,1344339971
Control13=IDC_STATIC,static,1342308352
Control14=IDC_LEVEL,edit,1350631552
Control15=IDC_STATIC,static,1342308352
Control16=IDC_EXPDATE_DAY,edit,1350631552
Control17=IDC_SPIN1,msctls_updown32,1342177334
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,button,1342177287
Control21=IDC_EXPDATE_MONTH,combobox,1344340995
Control22=IDC_EXPDATE_YEAR,combobox,1344340226
Control23=IDC_EXPLEVEL,combobox,1344339971

[DLG:IDD_PROP_OPT_SECURITY]
Type=1
Class=CPropOptionsSecurity
ControlCount=6
Control1=IDC_AVATAR,button,1342242819
Control2=IDC_ANSI,button,1342242819
Control3=IDC_ASKVOICE,button,1342242819
Control4=IDC_ASKDATAPHONE,button,1342242819
Control5=IDC_ASKFAXPHONE,button,1342242819
Control6=IDC_USESYSTEMPWD,button,1342242819

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_PBWIN_DIALOG]
Type=1
Class=CPBStatusDlg
ControlCount=9
Control1=65535,button,1342177287
Control2=IDC_LB_SESSIONS,listbox,1352728705
Control3=IDC_LOCAL,button,1342243584
Control4=CM_REFRESH,button,1342243584
Control5=IDC_TB_REFRESH,msctls_trackbar32,1342177280
Control6=65535,button,1342177287
Control7=IDC_LB_MODEMS,listbox,1352728705
Control8=IDC_DISABLE,button,1342243584
Control9=IDC_HANGUP,button,1342243584

[DLG:IDD_PROP_USERED_GENERAL]
Type=1
Class=?
ControlCount=28
Control1=IDC_NAME,edit,1350631552
Control2=IDC_STATIC,static,1342308352
Control3=IDC_ALIAS,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_NAME2,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_ALIAS2,edit,1350631552
Control8=IDC_STATIC,static,1342308352
Control9=IDC_NAME3,edit,1350631552
Control10=IDC_STATIC,static,1342308352
Control11=IDC_ALIAS3,edit,1350631552
Control12=IDC_STATIC,static,1342308352
Control13=IDC_NAME4,edit,1350635524
Control14=IDC_STATIC,static,1342308352
Control15=IDC_NAME5,edit,1350631552
Control16=IDC_STATIC,static,1342308352
Control17=IDC_ALIAS4,edit,1350631552
Control18=IDC_STATIC,static,1342308352
Control19=IDC_NAME6,edit,1350631552
Control20=IDC_STATIC,static,1342308352
Control21=IDC_ALIAS5,edit,1350631552
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_COMBO1,combobox,1344340226
Control25=IDC_LISTUSERS,button,1342242816
Control26=IDC_DATEFMT,combobox,1344340226
Control27=IDC_STATIC,static,1342308352
Control28=IDC_EDIT1,edit,1350631552

[DLG:IDD_PROP_USERED_SECURITY]
Type=1
Class=CPropUserSecurity
ControlCount=10
Control1=IDC_LEVEL,combobox,1344339971
Control2=IDC_EXPDATE_DAY,edit,1350631552
Control3=IDC_SPIN1,msctls_updown32,1342177334
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,button,1342177287
Control8=IDC_EXPDATE_MONTH,combobox,1344340995
Control9=IDC_EXPDATE_YEAR,combobox,1344340226
Control10=IDC_EXPLEVEL,combobox,1344339971

[MNU:IDD_PBWIN_DIALOG]
Type=1
Class=CPBStatusDlg
Command1=IDC_SHUTDOWN
Command2=IDM_OPT_DIRS
Command3=IDM_OPT_NEWUSERS
Command4=IDM_OPT_SECURITY
Command5=IDM_SITEINFO
Command6=IDM_PAGING
Command7=IDM_FILEAREAS
Command8=IDM_MSGAREAS
Command9=IDM_USERS
Command10=IDM_LEVELS
Command11=IDM_PROTOCOLS
Command12=IDM_MENUS
Command13=IDM_MACROS
Command14=IDM_EVENTS
Command15=IDM_LANGUAGES
Command16=IDM_MODEMS
Command17=IDM_TCPIP
Command18=IDC_ABOUT
CommandCount=18

[DLG:IDD_PROP_OPT_SITEINFO]
Type=1
Class=CPropSiteInfo
ControlCount=8
Control1=IDC_EDIT_BBSNAME,edit,1350631552
Control2=IDC_STATIC,static,1342308352
Control3=IDC_EDIT_SYSOPNAME,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT_LOCATION,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_EDIT_ORIGINLINE,edit,1350631552
Control8=IDC_STATIC,static,1342308352

[CLS:CPropSiteInfo]
Type=0
HeaderFile=propoptions.h
ImplementationFile=propoptions.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=IDC_EDIT_LOCATION
VirtualFilter=idWC

[CLS:CPropUserSecurity]
Type=0
HeaderFile=PropUserEd.h
ImplementationFile=PropUserEd.cpp
BaseClass=CPropertyPage
Filter=D
VirtualFilter=idWC
LastObject=CPropUserSecurity

[DLG:IDD_MSGAREA]
Type=1
Class=CDlgEditMsgArea
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_ED_AREANAME,edit,1350631552
Control7=IDC_ED_FILELOCATION,edit,1350631552
Control8=IDC_ED_CATALOGFILE,edit,1350631552

[CLS:CDlgMsgAreas]
Type=0
HeaderFile=DlgMsgAreas.h
ImplementationFile=DlgMsgAreas.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDlgMsgAreas

[DLG:IDD_AREAS]
Type=1
Class=CDlgMsgAreas
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LISTBOX,listbox,1352729985
Control4=IDC_EDIT,button,1342242816
Control5=IDC_NEW,button,1342242816

[CLS:CDlgEditMsgArea]
Type=0
HeaderFile=editmsgarea.h
ImplementationFile=editmsgarea.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDlgEditMsgArea

[MNU:IDD_PBWIN_DIALOG (English (U.S.))]
Type=1
Command1=IDC_SHUTDOWN
Command2=IDM_OPT_DIRS
Command3=IDM_OPT_NEWUSERS
Command4=IDM_OPT_SECURITY
Command5=IDM_SITEINFO
Command6=IDM_PAGING
Command7=IDM_FILEAREAS
Command8=IDM_MSGAREAS
Command9=IDM_USERS
Command10=IDM_LEVELS
Command11=IDM_PROTOCOLS
Command12=IDM_MENUS
Command13=IDM_MACROS
Command14=IDM_EVENTS
Command15=IDM_LANGUAGES
Command16=IDM_MODEMS
Command17=IDM_TCPIP
Command18=IDC_ABOUT
CommandCount=18

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_PBWIN_DIALOG (English (U.S.))]
Type=1
ControlCount=9
Control1=65535,button,1342177287
Control2=IDC_LB_SESSIONS,listbox,1352728705
Control3=IDC_LOCAL,button,1342243584
Control4=CM_REFRESH,button,1342243584
Control5=IDC_TB_REFRESH,msctls_trackbar32,1342177280
Control6=65535,button,1342177287
Control7=IDC_LB_MODEMS,listbox,1352728705
Control8=IDC_DISABLE,button,1342243584
Control9=IDC_HANGUP,button,1342243584

[DLG:IDD_PROP_USERED_GENERAL (English (U.S.))]
Type=1
ControlCount=28
Control1=IDC_NAME,edit,1350631552
Control2=IDC_STATIC,static,1342308352
Control3=IDC_ALIAS,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_NAME2,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_ALIAS2,edit,1350631552
Control8=IDC_STATIC,static,1342308352
Control9=IDC_NAME3,edit,1350631552
Control10=IDC_STATIC,static,1342308352
Control11=IDC_ALIAS3,edit,1350631552
Control12=IDC_STATIC,static,1342308352
Control13=IDC_NAME4,edit,1350635524
Control14=IDC_STATIC,static,1342308352
Control15=IDC_NAME5,edit,1350631552
Control16=IDC_STATIC,static,1342308352
Control17=IDC_ALIAS4,edit,1350631552
Control18=IDC_STATIC,static,1342308352
Control19=IDC_NAME6,edit,1350631552
Control20=IDC_STATIC,static,1342308352
Control21=IDC_ALIAS5,edit,1350631552
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_COMBO1,combobox,1344340226
Control25=IDC_LISTUSERS,button,1342242816
Control26=IDC_DATEFMT,combobox,1344340226
Control27=IDC_STATIC,static,1342308352
Control28=IDC_EDIT1,edit,1350631552

[DLG:IDD_PROP_USERED_SECURITY (English (U.S.))]
Type=1
ControlCount=10
Control1=IDC_LEVEL,combobox,1344339971
Control2=IDC_EXPDATE_DAY,edit,1350631552
Control3=IDC_SPIN1,msctls_updown32,1342177334
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,button,1342177287
Control8=IDC_EXPDATE_MONTH,combobox,1344340995
Control9=IDC_EXPDATE_YEAR,combobox,1344340226
Control10=IDC_EXPLEVEL,combobox,1344339971

[DLG:IDD_SECLEVELS (English (U.S.))]
Type=1
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LEVELS,listbox,1352728787
Control4=IDC_EDIT,button,1342242816
Control5=IDC_NEW,button,1342242816
Control6=IDC_DELETE,button,1342242816

[DLG:IDD_EDIT_SECLEVEL (English (U.S.))]
Type=1
ControlCount=7
Control1=IDC_LEVEL,edit,1350631552
Control2=IDC_DESCRIPTION,edit,1350631552
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352

[DLG:IDD_PROP_OPT_DIRECTORIES (English (U.S.))]
Type=1
ControlCount=10
Control1=IDC_ED_MSGBASE,edit,1350631552
Control2=IDC_STATIC,static,1342308352
Control3=IDC_ED_PEX,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_ED_MENUS,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_ED_TXTFILES,edit,1350631552
Control8=IDC_STATIC,static,1342308352
Control9=IDC_ED_BROW_MSGBASE,button,1342242816
Control10=IDC_ED_BROW_MSGBASE2,button,1342242816

[DLG:IDD_PROP_OPT_NEWUSERS (English (U.S.))]
Type=1
ControlCount=23
Control1=IDC_AVATAR,button,1342242819
Control2=IDC_ANSI,button,1342242819
Control3=IDC_ASKVOICE,button,1342242819
Control4=IDC_ASKDATAPHONE,button,1342242819
Control5=IDC_ASKFAXPHONE,button,1342242819
Control6=IDC_ASKBIRTHDATE,button,1342242819
Control7=IDC_ASKSTATE,button,1342242819
Control8=IDC_ASKCOUNTRY,button,1342242819
Control9=IDC_ASKADDRESS,button,1342242819
Control10=IDC_ASKSEX,button,1342242819
Control11=IDC_ASKDATEFMT,button,1342242819
Control12=IDC_LOGLEVEL,combobox,1344339971
Control13=IDC_STATIC,static,1342308352
Control14=IDC_LEVEL,edit,1350631552
Control15=IDC_STATIC,static,1342308352
Control16=IDC_EXPDATE_DAY,edit,1350631552
Control17=IDC_SPIN1,msctls_updown32,1342177334
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,button,1342177287
Control21=IDC_EXPDATE_MONTH,combobox,1344340995
Control22=IDC_EXPDATE_YEAR,combobox,1344340226
Control23=IDC_EXPLEVEL,combobox,1344339971

[DLG:IDD_PROP_OPT_SECURITY (English (U.S.))]
Type=1
ControlCount=6
Control1=IDC_AVATAR,button,1342242819
Control2=IDC_ANSI,button,1342242819
Control3=IDC_ASKVOICE,button,1342242819
Control4=IDC_ASKDATAPHONE,button,1342242819
Control5=IDC_ASKFAXPHONE,button,1342242819
Control6=IDC_USESYSTEMPWD,button,1342242819

[DLG:IDD_PROP_OPT_SITEINFO (English (U.S.))]
Type=1
ControlCount=8
Control1=IDC_EDIT_BBSNAME,edit,1350631552
Control2=IDC_STATIC,static,1342308352
Control3=IDC_EDIT_SYSOPNAME,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT_LOCATION,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_EDIT_ORIGINLINE,edit,1350631552
Control8=IDC_STATIC,static,1342308352

[DLG:IDD_MSGAREA (English (U.S.))]
Type=1
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_ED_AREANAME,edit,1350631552
Control7=IDC_ED_FILELOCATION,edit,1350631552
Control8=IDC_ED_CATALOGFILE,edit,1350631552

[DLG:IDD_AREAS (English (U.S.))]
Type=1
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LISTBOX,listbox,1352729985
Control4=IDC_EDIT,button,1342242816
Control5=IDC_NEW,button,1342242816

