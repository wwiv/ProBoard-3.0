# Microsoft Developer Studio Project File - Name="PBSess" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=PBSess - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "PBSess.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "PBSess.mak" CFG="PBSess - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PBSess - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "PBSess - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "PBSess - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "D:\PB32"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /Zp1 /MT /W3 /GX /O2 /I "\DEV\PBLIB" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FD /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib \dev\pblib\release\pblib.lib /nologo /subsystem:windows /dll /machine:I386

!ELSEIF  "$(CFG)" == "PBSess - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "D:\PB3DEBUG"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /Zp1 /MTd /W3 /Gm /GX /ZI /Od /I "\DEV\PBLIB" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /FD /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib \dev\pblib\debug\pblib.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:".\Debug\PBSess.dll"

!ENDIF 

# Begin Target

# Name "PBSess - Win32 Release"
# Name "PBSess - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\AKA.CPP
# End Source File
# Begin Source File

SOURCE=.\BULLETIN.CPP
# End Source File
# Begin Source File

SOURCE=.\CDROM.CPP
# End Source File
# Begin Source File

SOURCE=.\COMBINED.CPP
# End Source File
# Begin Source File

SOURCE=.\DATEFMT.CPP
# End Source File
# Begin Source File

SOURCE=.\delay.cpp
# End Source File
# Begin Source File

SOURCE=.\DL.CPP
# End Source File
# Begin Source File

SOURCE=.\FILEAREA.CPP
# End Source File
# Begin Source File

SOURCE=.\GLOBAL.CPP
# End Source File
# Begin Source File

SOURCE=.\HUDSON.CPP
# End Source File
# Begin Source File

SOURCE=.\INPDATE.CPP
# End Source File
# Begin Source File

SOURCE=.\INTRO.CPP
# End Source File
# Begin Source File

SOURCE=.\IO.CPP
# End Source File
# Begin Source File

SOURCE=.\JAM.CPP
# End Source File
# Begin Source File

SOURCE=.\LANGUAGE.CPP
# End Source File
# Begin Source File

SOURCE=.\LIMIT.CPP
# End Source File
# Begin Source File

SOURCE=.\LISTFILE.CPP
# End Source File
# Begin Source File

SOURCE=.\LOGIN.CPP
# End Source File
# Begin Source File

SOURCE=.\MARK.CPP
# End Source File
# Begin Source File

SOURCE=.\MENUPROC.CPP
# End Source File
# Begin Source File

SOURCE=.\MSG.CPP
# End Source File
# Begin Source File

SOURCE=.\MSGAREA.CPP
# End Source File
# Begin Source File

SOURCE=.\MSGBASE.CPP
# End Source File
# Begin Source File

SOURCE=.\MSGDEL.CPP
# End Source File
# Begin Source File

SOURCE=.\MSGED.CPP
# End Source File
# Begin Source File

SOURCE=.\MSGEXPRT.CPP
# End Source File
# Begin Source File

SOURCE=.\MSGFIND.CPP
# End Source File
# Begin Source File

SOURCE=.\MSGFWD.CPP
# End Source File
# Begin Source File

SOURCE=.\MSGMOVE.CPP
# End Source File
# Begin Source File

SOURCE=.\NODELIST.CPP
# End Source File
# Begin Source File

SOURCE=.\POSTMSG.CPP
# End Source File
# Begin Source File

SOURCE=.\PROBOARD.CPP
# End Source File
# Begin Source File

SOURCE=.\PROTOCOL.CPP
# End Source File
# Begin Source File

SOURCE=.\QUESTION.CPP
# End Source File
# Begin Source File

SOURCE=.\RACRC.CPP
# End Source File
# Begin Source File

SOURCE=.\READCFG.CPP
# End Source File
# Begin Source File

SOURCE=.\READMSG.CPP
# End Source File
# Begin Source File

SOURCE=.\REPLYMSG.CPP
# End Source File
# Begin Source File

SOURCE=.\RUNPEX.CPP
# End Source File
# Begin Source File

SOURCE=.\SELLANG.CPP
# End Source File
# Begin Source File

SOURCE=.\SETAREA.CPP
# End Source File
# Begin Source File

SOURCE=.\SHELL.CPP
# End Source File
# Begin Source File

SOURCE=.\SHOWANS.CPP
# End Source File
# Begin Source File

SOURCE=.\SHOWMSG.CPP
# End Source File
# Begin Source File

SOURCE=.\STRVAR.CPP
# End Source File
# Begin Source File

SOURCE=.\TAG.CPP
# End Source File
# Begin Source File

SOURCE=.\TAG_RW.CPP
# End Source File
# Begin Source File

SOURCE=.\TIMER.CPP
# End Source File
# Begin Source File

SOURCE=.\UL.CPP
# End Source File
# Begin Source File

SOURCE=.\USERSET.CPP
# End Source File
# Begin Source File

SOURCE=.\WORDWRAP.CPP
# End Source File
# Begin Source File

SOURCE=.\WRITEMSG.CPP
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\JAM.HPP
# End Source File
# Begin Source File

SOURCE=.\MSGBASE.HPP
# End Source File
# Begin Source File

SOURCE=.\PROBOARD.HPP
# End Source File
# Begin Source File

SOURCE=.\PROMPTS.HPP
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
