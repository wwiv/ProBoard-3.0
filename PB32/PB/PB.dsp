# Microsoft Developer Studio Project File - Name="PB" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=PB - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "PB.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "PB.mak" CFG="PB - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PB - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "PB - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "PB - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "D:\PB32"
# PROP Intermediate_Dir ".\Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /GB /Zp1 /MT /W3 /Gi /GX /O2 /Ob2 /I "\Dev\PBLib" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 \Dev\PBLib\Release\PBLIB.LIB /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "PB - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "D:\Dev\PB32\PBNode\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /GB /Zp1 /MTd /W3 /Gm /Gi /GX /ZI /Od /I "\Dev\PBLib" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 \Dev\PBLib\Debug\PBLIB.LIB /nologo /subsystem:windows /debug /machine:I386 /out:"\Dev\PB32\PBNode\Debug/PB.exe"

!ENDIF 

# Begin Target

# Name "PB - Win32 Release"
# Name "PB - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\dlgEditLevel.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMsgAreas.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSecLevels.cpp
# End Source File
# Begin Source File

SOURCE=.\editmsgarea.cpp
# End Source File
# Begin Source File

SOURCE=.\ListBoxSecLev.cpp
# End Source File
# Begin Source File

SOURCE=.\PB.cpp
# End Source File
# Begin Source File

SOURCE=.\PB.rc
# End Source File
# Begin Source File

SOURCE=.\PropOptions.CPP
# End Source File
# Begin Source File

SOURCE=.\PropUserEd.cpp
# End Source File
# Begin Source File

SOURCE=.\ServerSock.cpp
# End Source File
# Begin Source File

SOURCE=.\StatDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\dlgEditLevel.h
# End Source File
# Begin Source File

SOURCE=.\DlgMsgAreas.h
# End Source File
# Begin Source File

SOURCE=.\DlgSecLevels.h
# End Source File
# Begin Source File

SOURCE=.\editmsgarea.h
# End Source File
# Begin Source File

SOURCE=.\ListBoxSecLev.h
# End Source File
# Begin Source File

SOURCE=.\PB.h
# End Source File
# Begin Source File

SOURCE=.\PropOptions.h
# End Source File
# Begin Source File

SOURCE=.\PropUserEd.h
# End Source File
# Begin Source File

SOURCE=.\ServerSock.h
# End Source File
# Begin Source File

SOURCE=.\StatDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\PB.rc2
# End Source File
# End Group
# End Target
# End Project
# Section PB : {94525901-6183-11D0-9E20-00A024D40EEA}
# 	2:23:OLE Control Containment:1
# End Section
