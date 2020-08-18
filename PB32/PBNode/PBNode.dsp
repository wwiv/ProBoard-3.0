# Microsoft Developer Studio Project File - Name="PBNode" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=PBNode - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "PBNode.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "PBNode.mak" CFG="PBNode - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PBNode - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "PBNode - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "PBNode - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "D:\PB32"
# PROP Intermediate_Dir ".\Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "\GCPP300\H" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 \GCPP300\MSVC40\CPFWM.LIB \DEV\PB32\PBSESS\RELEASE\PBSESS.LIB /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "PBNode - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MTd /W4 /Gm /GX /ZI /Od /I "\GCPP300\H" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 \GCPP300\MSVC40\CPFWM.LIB \DEV\PB32\PBSESS\DEBUG\PBSESS.LIB /nologo /subsystem:windows /debug /machine:I386

!ENDIF 

# Begin Target

# Name "PBNode - Win32 Release"
# Name "PBNode - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Group "TCP/IP Code"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\bufsock.cpp
# End Source File
# Begin Source File

SOURCE=.\gfcomsock.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\PBFrWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\PBNode.cpp
# End Source File
# Begin Source File

SOURCE=.\PBNode.rc
# End Source File
# Begin Source File

SOURCE=.\pbthread.cpp
# End Source File
# Begin Source File

SOURCE=.\PBWND.CPP
# End Source File
# Begin Source File

SOURCE=.\rcvthread.cpp
# End Source File
# Begin Source File

SOURCE=.\SCRNBUF.CPP
# End Source File
# Begin Source File

SOURCE=.\serial.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\THREAD.CPP
# End Source File
# Begin Source File

SOURCE=.\TTYWND.CPP
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\bufsock.h
# End Source File
# Begin Source File

SOURCE=.\gfcomsock.h
# End Source File
# Begin Source File

SOURCE=.\PBFrWnd.h
# End Source File
# Begin Source File

SOURCE=.\PBNode.h
# End Source File
# Begin Source File

SOURCE=.\pbthread.h
# End Source File
# Begin Source File

SOURCE=.\PBWnd.h
# End Source File
# Begin Source File

SOURCE=.\rcvthread.h
# End Source File
# Begin Source File

SOURCE=.\SCRNBUF.HPP
# End Source File
# Begin Source File

SOURCE=.\serial.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\THREAD.H
# End Source File
# Begin Source File

SOURCE=.\ttywnd.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\PBNode.ico
# End Source File
# Begin Source File

SOURCE=.\res\PBNode.rc2
# End Source File
# End Group
# End Target
# End Project
