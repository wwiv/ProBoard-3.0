# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=PB - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to PB - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "PB - Win32 Release" && "$(CFG)" != "PB - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "PB.MAK" CFG="PB - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PB - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "PB - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "PB - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "PB - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "D:\PB32"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=D:\PB32
INTDIR=.\Release

ALL : "$(OUTDIR)\PB.exe"

CLEAN : 
	-@erase "..\..\..\PB32\PB.exe"
	-@erase ".\Release\ServerSock.obj"
	-@erase ".\Release\PB.pch"
	-@erase ".\Release\ListBoxSecLev.obj"
	-@erase ".\Release\DlgMsgAreas.obj"
	-@erase ".\Release\editmsgarea.obj"
	-@erase ".\Release\dlgEditLevel.obj"
	-@erase ".\Release\DlgSecLevels.obj"
	-@erase ".\Release\PropUserEd.obj"
	-@erase ".\Release\PropOptions.obj"
	-@erase ".\Release\StatDlg.obj"
	-@erase ".\Release\PB.obj"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\PB.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /G4 /Zp1 /MD /W3 /Gi /GX /O2 /Ob2 /I "D:\Dev\PBLib" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /G4 /Zp1 /MD /W3 /Gi /GX /O2 /Ob2 /I "D:\Dev\PBLib" /D "WIN32"\
 /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/PB.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/PB.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/PB.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 D:\Dev\TSLIB\Release\TSLIB.LIB D:\Dev\PBLib\Release\PBLIB.LIB /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=D:\Dev\TSLIB\Release\TSLIB.LIB D:\Dev\PBLib\Release\PBLIB.LIB\
 /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)/PB.pdb"\
 /machine:I386 /out:"$(OUTDIR)/PB.exe" 
LINK32_OBJS= \
	"$(INTDIR)/ServerSock.obj" \
	"$(INTDIR)/ListBoxSecLev.obj" \
	"$(INTDIR)/DlgMsgAreas.obj" \
	"$(INTDIR)/editmsgarea.obj" \
	"$(INTDIR)/dlgEditLevel.obj" \
	"$(INTDIR)/DlgSecLevels.obj" \
	"$(INTDIR)/PropUserEd.obj" \
	"$(INTDIR)/PropOptions.obj" \
	"$(INTDIR)/StatDlg.obj" \
	"$(INTDIR)/PB.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/PB.res"

"$(OUTDIR)\PB.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "PB - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "D:\PB3DEBUG"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=D:\PB3DEBUG
INTDIR=.\Debug

ALL : "$(OUTDIR)\PB.exe"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\PB.pch"
	-@erase ".\Debug\vc40.idb"
	-@erase "..\..\..\PB3DEBUG\PB.exe"
	-@erase ".\Debug\StatDlg.obj"
	-@erase ".\Debug\PropUserEd.obj"
	-@erase ".\Debug\dlgEditLevel.obj"
	-@erase ".\Debug\ServerSock.obj"
	-@erase ".\Debug\PB.obj"
	-@erase ".\Debug\ListBoxSecLev.obj"
	-@erase ".\Debug\DlgMsgAreas.obj"
	-@erase ".\Debug\editmsgarea.obj"
	-@erase ".\Debug\DlgSecLevels.obj"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\PropOptions.obj"
	-@erase ".\Debug\PB.res"
	-@erase "..\..\..\PB3DEBUG\PB.ilk"
	-@erase "..\..\..\PB3DEBUG\PB.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /G4 /Zp1 /MDd /W3 /Gm /Gi /GX /Zi /Od /I "D:\Dev\PBLib" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /G4 /Zp1 /MDd /W3 /Gm /Gi /GX /Zi /Od /I "D:\Dev\PBLib" /D\
 "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/PB.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/PB.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/PB.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 D:\Dev\TSLIB\Debug\TSLIB.LIB D:\Dev\PBLib\Debug\PBLIB.LIB /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=D:\Dev\TSLIB\Debug\TSLIB.LIB D:\Dev\PBLib\Debug\PBLIB.LIB /nologo\
 /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)/PB.pdb" /debug\
 /machine:I386 /out:"$(OUTDIR)/PB.exe" 
LINK32_OBJS= \
	"$(INTDIR)/StatDlg.obj" \
	"$(INTDIR)/PropUserEd.obj" \
	"$(INTDIR)/dlgEditLevel.obj" \
	"$(INTDIR)/ServerSock.obj" \
	"$(INTDIR)/PB.obj" \
	"$(INTDIR)/ListBoxSecLev.obj" \
	"$(INTDIR)/DlgMsgAreas.obj" \
	"$(INTDIR)/editmsgarea.obj" \
	"$(INTDIR)/DlgSecLevels.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/PropOptions.obj" \
	"$(INTDIR)/PB.res"

"$(OUTDIR)\PB.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "PB - Win32 Release"
# Name "PB - Win32 Debug"

!IF  "$(CFG)" == "PB - Win32 Release"

!ELSEIF  "$(CFG)" == "PB - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "PB - Win32 Release"

!ELSEIF  "$(CFG)" == "PB - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PB.cpp
DEP_CPP_PB_CP=\
	".\StdAfx.h"\
	"\Dev\PBLib\pblib.hpp"\
	".\PB.h"\
	".\StatDlg.h"\
	{$(INCLUDE)}"\TSLIB.HPP"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	".\ServerSock.h"\
	

"$(INTDIR)\PB.obj" : $(SOURCE) $(DEP_CPP_PB_CP) "$(INTDIR)" "$(INTDIR)\PB.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "PB - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /G4 /Zp1 /MD /W3 /Gi /GX /O2 /Ob2 /I "D:\Dev\PBLib" /D "WIN32"\
 /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/PB.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\PB.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "PB - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /G4 /Zp1 /MDd /W3 /Gm /Gi /GX /Zi /Od /I "D:\Dev\PBLib" /D\
 "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/PB.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\PB.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PB.rc
DEP_RSC_PB_RC=\
	".\res\PB.rc2"\
	

"$(INTDIR)\PB.res" : $(SOURCE) $(DEP_RSC_PB_RC) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StatDlg.cpp
DEP_CPP_STATD=\
	".\StdAfx.h"\
	"\Dev\PBLib\pblib.hpp"\
	".\PB.h"\
	".\StatDlg.h"\
	".\DlgSecLevels.h"\
	".\PropOptions.h"\
	".\PropUserEd.h"\
	".\DlgMsgAreas.h"\
	{$(INCLUDE)}"\TSLIB.HPP"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	".\ServerSock.h"\
	".\ListBoxSecLev.h"\
	

"$(INTDIR)\StatDlg.obj" : $(SOURCE) $(DEP_CPP_STATD) "$(INTDIR)"\
 "$(INTDIR)\PB.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ServerSock.cpp
DEP_CPP_SERVE=\
	".\StdAfx.h"\
	".\PB.h"\
	".\StatDlg.h"\
	".\ServerSock.h"\
	

"$(INTDIR)\ServerSock.obj" : $(SOURCE) $(DEP_CPP_SERVE) "$(INTDIR)"\
 "$(INTDIR)\PB.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ListBoxSecLev.cpp
DEP_CPP_LISTB=\
	".\StdAfx.h"\
	".\PB.h"\
	".\ListBoxSecLev.h"\
	

"$(INTDIR)\ListBoxSecLev.obj" : $(SOURCE) $(DEP_CPP_LISTB) "$(INTDIR)"\
 "$(INTDIR)\PB.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgSecLevels.cpp
DEP_CPP_DLGSE=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\TSLIB.HPP"\
	".\PB.h"\
	".\DlgSecLevels.h"\
	".\dlgEditLevel.h"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	".\ListBoxSecLev.h"\
	

"$(INTDIR)\DlgSecLevels.obj" : $(SOURCE) $(DEP_CPP_DLGSE) "$(INTDIR)"\
 "$(INTDIR)\PB.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\dlgEditLevel.cpp
DEP_CPP_DLGED=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\TSLIB.HPP"\
	".\PB.h"\
	".\dlgEditLevel.h"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	

"$(INTDIR)\dlgEditLevel.obj" : $(SOURCE) $(DEP_CPP_DLGED) "$(INTDIR)"\
 "$(INTDIR)\PB.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\PropOptions.CPP
DEP_CPP_PROPO=\
	".\StdAfx.h"\
	".\PB.h"\
	".\PropOptions.h"\
	

"$(INTDIR)\PropOptions.obj" : $(SOURCE) $(DEP_CPP_PROPO) "$(INTDIR)"\
 "$(INTDIR)\PB.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\PropUserEd.cpp
DEP_CPP_PROPU=\
	".\StdAfx.h"\
	".\PB.h"\
	".\PropUserEd.h"\
	

"$(INTDIR)\PropUserEd.obj" : $(SOURCE) $(DEP_CPP_PROPU) "$(INTDIR)"\
 "$(INTDIR)\PB.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgMsgAreas.cpp
DEP_CPP_DLGMS=\
	".\StdAfx.h"\
	".\PB.h"\
	"\Dev\PBLib\pblib.hpp"\
	".\DlgMsgAreas.h"\
	".\editmsgarea.h"\
	{$(INCLUDE)}"\TSLIB.HPP"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	

"$(INTDIR)\DlgMsgAreas.obj" : $(SOURCE) $(DEP_CPP_DLGMS) "$(INTDIR)"\
 "$(INTDIR)\PB.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\editmsgarea.cpp
DEP_CPP_EDITM=\
	".\StdAfx.h"\
	".\PB.h"\
	".\editmsgarea.h"\
	

"$(INTDIR)\editmsgarea.obj" : $(SOURCE) $(DEP_CPP_EDITM) "$(INTDIR)"\
 "$(INTDIR)\PB.pch"


# End Source File
# End Target
# End Project
################################################################################
################################################################################
# Section PB : {94525901-6183-11D0-9E20-00A024D40EEA}
# 	2:23:OLE Control Containment:1
# End Section
################################################################################
