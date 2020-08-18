# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=FlagEdit - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to FlagEdit - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "FlagEdit - Win32 Release" && "$(CFG)" !=\
 "FlagEdit - Win32 Debug" && "$(CFG)" != "FlagEdit - Win32 Unicode Debug" &&\
 "$(CFG)" != "FlagEdit - Win32 Unicode Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "FlagEdit.mak" CFG="FlagEdit - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "FlagEdit - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "FlagEdit - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "FlagEdit - Win32 Unicode Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "FlagEdit - Win32 Unicode Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "FlagEdit - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "FlagEdit - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP BASE Target_Ext "ocx"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "D:\PB32"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# PROP Target_Ext "ocx"
OUTDIR=D:\PB32
INTDIR=.\Release
# Begin Custom Macros
OutDir=D:\PB32
# End Custom Macros

ALL : "$(OUTDIR)\FlagEdit.ocx" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase "..\..\..\PB32\FlagEdit.lib"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\FlagEdit.obj"
	-@erase ".\Release\FlagEdit.pch"
	-@erase ".\Release\FlagEditPpg.obj"
	-@erase ".\Release\FlagEditCtl.obj"
	-@erase ".\Release\FlagEdit.res"
	-@erase "\PB32\FlagEdit.tlb"
	-@erase "..\..\..\PB32\FlagEdit.exp"
	-@erase "..\..\..\PB32\regsvr32.trg"
	-@erase "..\..\..\PB32\FlagEdit.ocx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)/FlagEdit.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/FlagEdit.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/FlagEdit.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/FlagEdit.pdb" /machine:I386 /def:".\FlagEdit.def"\
 /out:"$(OUTDIR)/FlagEdit.ocx" /implib:"$(OUTDIR)/FlagEdit.lib" 
DEF_FILE= \
	".\FlagEdit.def"
LINK32_OBJS= \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/FlagEdit.obj" \
	"$(INTDIR)/FlagEditPpg.obj" \
	"$(INTDIR)/FlagEditCtl.obj" \
	"$(INTDIR)/FlagEdit.res"

"$(OUTDIR)\FlagEdit.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=D:\PB32
TargetPath=\PB32\FlagEdit.ocx
InputPath=\PB32\FlagEdit.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "FlagEdit - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP BASE Target_Ext "ocx"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "D:\PB3DEBUG"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# PROP Target_Ext "ocx"
OUTDIR=D:\PB3DEBUG
INTDIR=.\Debug
# Begin Custom Macros
OutDir=D:\PB3DEBUG
# End Custom Macros

ALL : "$(OUTDIR)\FlagEdit.ocx" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\FlagEdit.pch"
	-@erase ".\Debug\vc40.idb"
	-@erase "..\..\..\PB3DEBUG\FlagEdit.ilk"
	-@erase ".\Debug\FlagEditPpg.obj"
	-@erase ".\Debug\FlagEdit.obj"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\FlagEditCtl.obj"
	-@erase ".\Debug\FlagEdit.res"
	-@erase "\PB3DEBUG\FlagEdit.tlb"
	-@erase "..\..\..\PB3DEBUG\FlagEdit.lib"
	-@erase "..\..\..\PB3DEBUG\FlagEdit.exp"
	-@erase "..\..\..\PB3DEBUG\FlagEdit.pdb"
	-@erase "..\..\..\PB3DEBUG\regsvr32.trg"
	-@erase "..\..\..\PB3DEBUG\FlagEdit.ocx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)/FlagEdit.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/FlagEdit.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/FlagEdit.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/FlagEdit.pdb" /debug /machine:I386 /def:".\FlagEdit.def"\
 /out:"$(OUTDIR)/FlagEdit.ocx" /implib:"$(OUTDIR)/FlagEdit.lib" 
DEF_FILE= \
	".\FlagEdit.def"
LINK32_OBJS= \
	"$(INTDIR)/FlagEditPpg.obj" \
	"$(INTDIR)/FlagEdit.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/FlagEditCtl.obj" \
	"$(INTDIR)/FlagEdit.res"

"$(OUTDIR)\FlagEdit.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=D:\PB3DEBUG
TargetPath=\PB3DEBUG\FlagEdit.ocx
InputPath=\PB3DEBUG\FlagEdit.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "FlagEdit - Win32 Unicode Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugU"
# PROP BASE Intermediate_Dir "DebugU"
# PROP BASE Target_Dir ""
# PROP BASE Target_Ext "ocx"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugU"
# PROP Intermediate_Dir "DebugU"
# PROP Target_Dir ""
# PROP Target_Ext "ocx"
OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

ALL : "$(OUTDIR)\FlagEdit.ocx" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase ".\DebugU\vc40.pdb"
	-@erase ".\DebugU\FlagEdit.pch"
	-@erase ".\DebugU\vc40.idb"
	-@erase ".\DebugU\FlagEdit.ilk"
	-@erase ".\DebugU\FlagEdit.obj"
	-@erase ".\DebugU\StdAfx.obj"
	-@erase ".\DebugU\FlagEditPpg.obj"
	-@erase ".\DebugU\FlagEditCtl.obj"
	-@erase ".\DebugU\FlagEdit.res"
	-@erase ".\DebugU\FlagEdit.tlb"
	-@erase ".\DebugU\FlagEdit.lib"
	-@erase ".\DebugU\FlagEdit.exp"
	-@erase ".\DebugU\FlagEdit.pdb"
	-@erase ".\DebugU\regsvr32.trg"
	-@erase ".\DebugU\FlagEdit.ocx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE"\
 /Fp"$(INTDIR)/FlagEdit.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\DebugU/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/FlagEdit.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/FlagEdit.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/FlagEdit.pdb" /debug /machine:I386 /def:".\FlagEdit.def"\
 /out:"$(OUTDIR)/FlagEdit.ocx" /implib:"$(OUTDIR)/FlagEdit.lib" 
DEF_FILE= \
	".\FlagEdit.def"
LINK32_OBJS= \
	"$(INTDIR)/FlagEdit.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/FlagEditPpg.obj" \
	"$(INTDIR)/FlagEditCtl.obj" \
	"$(INTDIR)/FlagEdit.res"

"$(OUTDIR)\FlagEdit.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\DebugU
TargetPath=.\DebugU\FlagEdit.ocx
InputPath=.\DebugU\FlagEdit.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "FlagEdit - Win32 Unicode Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseU"
# PROP BASE Intermediate_Dir "ReleaseU"
# PROP BASE Target_Dir ""
# PROP BASE Target_Ext "ocx"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseU"
# PROP Intermediate_Dir "ReleaseU"
# PROP Target_Dir ""
# PROP Target_Ext "ocx"
OUTDIR=.\ReleaseU
INTDIR=.\ReleaseU
# Begin Custom Macros
OutDir=.\ReleaseU
# End Custom Macros

ALL : "$(OUTDIR)\FlagEdit.ocx" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase ".\ReleaseU\FlagEdit.lib"
	-@erase ".\ReleaseU\FlagEditPpg.obj"
	-@erase ".\ReleaseU\FlagEdit.pch"
	-@erase ".\ReleaseU\FlagEditCtl.obj"
	-@erase ".\ReleaseU\StdAfx.obj"
	-@erase ".\ReleaseU\FlagEdit.obj"
	-@erase ".\ReleaseU\FlagEdit.res"
	-@erase ".\ReleaseU\FlagEdit.tlb"
	-@erase ".\ReleaseU\FlagEdit.exp"
	-@erase ".\ReleaseU\regsvr32.trg"
	-@erase ".\ReleaseU\FlagEdit.ocx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)/FlagEdit.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\ReleaseU/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/FlagEdit.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/FlagEdit.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/FlagEdit.pdb" /machine:I386 /def:".\FlagEdit.def"\
 /out:"$(OUTDIR)/FlagEdit.ocx" /implib:"$(OUTDIR)/FlagEdit.lib" 
DEF_FILE= \
	".\FlagEdit.def"
LINK32_OBJS= \
	"$(INTDIR)/FlagEditPpg.obj" \
	"$(INTDIR)/FlagEditCtl.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/FlagEdit.obj" \
	"$(INTDIR)/FlagEdit.res"

"$(OUTDIR)\FlagEdit.ocx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Registering OLE control...
OutDir=.\ReleaseU
TargetPath=.\ReleaseU\FlagEdit.ocx
InputPath=.\ReleaseU\FlagEdit.ocx
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

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

# Name "FlagEdit - Win32 Release"
# Name "FlagEdit - Win32 Debug"
# Name "FlagEdit - Win32 Unicode Debug"
# Name "FlagEdit - Win32 Unicode Release"

!IF  "$(CFG)" == "FlagEdit - Win32 Release"

!ELSEIF  "$(CFG)" == "FlagEdit - Win32 Debug"

!ELSEIF  "$(CFG)" == "FlagEdit - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "FlagEdit - Win32 Unicode Release"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "FlagEdit - Win32 Release"

!ELSEIF  "$(CFG)" == "FlagEdit - Win32 Debug"

!ELSEIF  "$(CFG)" == "FlagEdit - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "FlagEdit - Win32 Unicode Release"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "FlagEdit - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)/FlagEdit.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\FlagEdit.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "FlagEdit - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)/FlagEdit.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\FlagEdit.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "FlagEdit - Win32 Unicode Debug"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE"\
 /Fp"$(INTDIR)/FlagEdit.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\FlagEdit.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "FlagEdit - Win32 Unicode Release"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)/FlagEdit.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\FlagEdit.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FlagEdit.cpp
DEP_CPP_FLAGE=\
	".\StdAfx.h"\
	".\FlagEdit.h"\
	

!IF  "$(CFG)" == "FlagEdit - Win32 Release"


"$(INTDIR)\FlagEdit.obj" : $(SOURCE) $(DEP_CPP_FLAGE) "$(INTDIR)"\
 "$(INTDIR)\FlagEdit.pch"


!ELSEIF  "$(CFG)" == "FlagEdit - Win32 Debug"


"$(INTDIR)\FlagEdit.obj" : $(SOURCE) $(DEP_CPP_FLAGE) "$(INTDIR)"\
 "$(INTDIR)\FlagEdit.pch"


!ELSEIF  "$(CFG)" == "FlagEdit - Win32 Unicode Debug"


"$(INTDIR)\FlagEdit.obj" : $(SOURCE) $(DEP_CPP_FLAGE) "$(INTDIR)"\
 "$(INTDIR)\FlagEdit.pch"


!ELSEIF  "$(CFG)" == "FlagEdit - Win32 Unicode Release"


"$(INTDIR)\FlagEdit.obj" : $(SOURCE) $(DEP_CPP_FLAGE) "$(INTDIR)"\
 "$(INTDIR)\FlagEdit.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FlagEdit.def

!IF  "$(CFG)" == "FlagEdit - Win32 Release"

!ELSEIF  "$(CFG)" == "FlagEdit - Win32 Debug"

!ELSEIF  "$(CFG)" == "FlagEdit - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "FlagEdit - Win32 Unicode Release"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FlagEdit.rc

!IF  "$(CFG)" == "FlagEdit - Win32 Release"

DEP_RSC_FLAGED=\
	".\FlagEdit.ico"\
	".\FlagEditCtl.bmp"\
	"\PB32\FlagEdit.tlb"\
	

"$(INTDIR)\FlagEdit.res" : $(SOURCE) $(DEP_RSC_FLAGED) "$(INTDIR)"\
 "\PB32\FlagEdit.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/FlagEdit.res" /i "D:\PB32" /d "NDEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "FlagEdit - Win32 Debug"

DEP_RSC_FLAGED=\
	".\FlagEdit.ico"\
	".\FlagEditCtl.bmp"\
	
NODEP_RSC_FLAGED=\
	"\PB3DEBUG\FlagEdit.tlb"\
	

"$(INTDIR)\FlagEdit.res" : $(SOURCE) $(DEP_RSC_FLAGED) "$(INTDIR)"\
 "\PB3DEBUG\FlagEdit.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/FlagEdit.res" /i "D:\PB3DEBUG" /d "_DEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "FlagEdit - Win32 Unicode Debug"

DEP_RSC_FLAGED=\
	".\FlagEdit.ico"\
	".\FlagEditCtl.bmp"\
	
NODEP_RSC_FLAGED=\
	".\DebugU\FlagEdit.tlb"\
	

"$(INTDIR)\FlagEdit.res" : $(SOURCE) $(DEP_RSC_FLAGED) "$(INTDIR)"\
 "$(INTDIR)\FlagEdit.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/FlagEdit.res" /i "DebugU" /d "_DEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "FlagEdit - Win32 Unicode Release"

DEP_RSC_FLAGED=\
	".\FlagEdit.ico"\
	".\FlagEditCtl.bmp"\
	
NODEP_RSC_FLAGED=\
	".\ReleaseU\FlagEdit.tlb"\
	

"$(INTDIR)\FlagEdit.res" : $(SOURCE) $(DEP_RSC_FLAGED) "$(INTDIR)"\
 "$(INTDIR)\FlagEdit.tlb"
   $(RSC) /l 0x409 /fo"$(INTDIR)/FlagEdit.res" /i "ReleaseU" /d "NDEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FlagEdit.odl

!IF  "$(CFG)" == "FlagEdit - Win32 Release"


"$(OUTDIR)\FlagEdit.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "NDEBUG" /tlb "$(OUTDIR)/FlagEdit.tlb" /win32 $(SOURCE)


!ELSEIF  "$(CFG)" == "FlagEdit - Win32 Debug"


"$(OUTDIR)\FlagEdit.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "_DEBUG" /tlb "$(OUTDIR)/FlagEdit.tlb" /win32 $(SOURCE)


!ELSEIF  "$(CFG)" == "FlagEdit - Win32 Unicode Debug"


"$(OUTDIR)\FlagEdit.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "_DEBUG" /tlb "$(OUTDIR)/FlagEdit.tlb" /win32 $(SOURCE)


!ELSEIF  "$(CFG)" == "FlagEdit - Win32 Unicode Release"


"$(OUTDIR)\FlagEdit.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "NDEBUG" /tlb "$(OUTDIR)/FlagEdit.tlb" /win32 $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FlagEditCtl.cpp
DEP_CPP_FLAGEDI=\
	".\StdAfx.h"\
	".\FlagEdit.h"\
	".\FlagEditCtl.h"\
	".\FlagEditPpg.h"\
	

!IF  "$(CFG)" == "FlagEdit - Win32 Release"


"$(INTDIR)\FlagEditCtl.obj" : $(SOURCE) $(DEP_CPP_FLAGEDI) "$(INTDIR)"\
 "$(INTDIR)\FlagEdit.pch"


!ELSEIF  "$(CFG)" == "FlagEdit - Win32 Debug"


"$(INTDIR)\FlagEditCtl.obj" : $(SOURCE) $(DEP_CPP_FLAGEDI) "$(INTDIR)"\
 "$(INTDIR)\FlagEdit.pch"


!ELSEIF  "$(CFG)" == "FlagEdit - Win32 Unicode Debug"


"$(INTDIR)\FlagEditCtl.obj" : $(SOURCE) $(DEP_CPP_FLAGEDI) "$(INTDIR)"\
 "$(INTDIR)\FlagEdit.pch"


!ELSEIF  "$(CFG)" == "FlagEdit - Win32 Unicode Release"


"$(INTDIR)\FlagEditCtl.obj" : $(SOURCE) $(DEP_CPP_FLAGEDI) "$(INTDIR)"\
 "$(INTDIR)\FlagEdit.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FlagEditPpg.cpp
DEP_CPP_FLAGEDIT=\
	".\StdAfx.h"\
	".\FlagEdit.h"\
	".\FlagEditPpg.h"\
	

!IF  "$(CFG)" == "FlagEdit - Win32 Release"


"$(INTDIR)\FlagEditPpg.obj" : $(SOURCE) $(DEP_CPP_FLAGEDIT) "$(INTDIR)"\
 "$(INTDIR)\FlagEdit.pch"


!ELSEIF  "$(CFG)" == "FlagEdit - Win32 Debug"


"$(INTDIR)\FlagEditPpg.obj" : $(SOURCE) $(DEP_CPP_FLAGEDIT) "$(INTDIR)"\
 "$(INTDIR)\FlagEdit.pch"


!ELSEIF  "$(CFG)" == "FlagEdit - Win32 Unicode Debug"


"$(INTDIR)\FlagEditPpg.obj" : $(SOURCE) $(DEP_CPP_FLAGEDIT) "$(INTDIR)"\
 "$(INTDIR)\FlagEdit.pch"


!ELSEIF  "$(CFG)" == "FlagEdit - Win32 Unicode Release"


"$(INTDIR)\FlagEditPpg.obj" : $(SOURCE) $(DEP_CPP_FLAGEDIT) "$(INTDIR)"\
 "$(INTDIR)\FlagEdit.pch"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
