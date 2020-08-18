# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=PBNode - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to PBNode - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "PBNode - Win32 Release" && "$(CFG)" != "PBNode - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "PBNode.mak" CFG="PBNode - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PBNode - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "PBNode - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "PBNode - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "PBNode - Win32 Release"

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

ALL : "$(OUTDIR)\PBNode.exe"

CLEAN : 
	-@erase "..\..\..\PB32\PBNode.exe"
	-@erase ".\Release\serial.obj"
	-@erase ".\Release\PBNode.pch"
	-@erase ".\Release\gfcomsock.obj"
	-@erase ".\Release\THREAD.OBJ"
	-@erase ".\Release\PBFrWnd.obj"
	-@erase ".\Release\TTYWND.OBJ"
	-@erase ".\Release\SCRNBUF.OBJ"
	-@erase ".\Release\PBWND.OBJ"
	-@erase ".\Release\pbthread.obj"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\PBNode.obj"
	-@erase ".\Release\rcvthread.obj"
	-@erase ".\Release\bufsock.obj"
	-@erase ".\Release\PBNode.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/PBNode.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c\
 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/PBNode.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/PBNode.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 D:\GCPP300\MSVC40\CPFWM.LIB D:\DEV\PB32\PBSESS\RELEASE\PBSESS.LIB /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=D:\GCPP300\MSVC40\CPFWM.LIB D:\DEV\PB32\PBSESS\RELEASE\PBSESS.LIB\
 /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)/PBNode.pdb"\
 /machine:I386 /out:"$(OUTDIR)/PBNode.exe" 
LINK32_OBJS= \
	"$(INTDIR)/serial.obj" \
	"$(INTDIR)/gfcomsock.obj" \
	"$(INTDIR)/THREAD.OBJ" \
	"$(INTDIR)/PBFrWnd.obj" \
	"$(INTDIR)/TTYWND.OBJ" \
	"$(INTDIR)/SCRNBUF.OBJ" \
	"$(INTDIR)/PBWND.OBJ" \
	"$(INTDIR)/pbthread.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/PBNode.obj" \
	"$(INTDIR)/rcvthread.obj" \
	"$(INTDIR)/bufsock.obj" \
	"$(INTDIR)/PBNode.res"

"$(OUTDIR)\PBNode.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "PBNode - Win32 Debug"

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

ALL : "$(OUTDIR)\PBNode.exe" "$(OUTDIR)\PBNode.bsc"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\PBNode.pch"
	-@erase ".\Debug\vc40.idb"
	-@erase "..\..\..\PB3DEBUG\PBNode.bsc"
	-@erase ".\Debug\StdAfx.sbr"
	-@erase ".\Debug\gfcomsock.sbr"
	-@erase ".\Debug\PBNode.sbr"
	-@erase ".\Debug\TTYWND.SBR"
	-@erase ".\Debug\serial.sbr"
	-@erase ".\Debug\PBFrWnd.sbr"
	-@erase ".\Debug\PBWND.SBR"
	-@erase ".\Debug\bufsock.sbr"
	-@erase ".\Debug\pbthread.sbr"
	-@erase ".\Debug\THREAD.SBR"
	-@erase ".\Debug\SCRNBUF.SBR"
	-@erase ".\Debug\rcvthread.sbr"
	-@erase "..\..\..\PB3DEBUG\PBNode.exe"
	-@erase ".\Debug\bufsock.obj"
	-@erase ".\Debug\pbthread.obj"
	-@erase ".\Debug\THREAD.OBJ"
	-@erase ".\Debug\SCRNBUF.OBJ"
	-@erase ".\Debug\rcvthread.obj"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\gfcomsock.obj"
	-@erase ".\Debug\PBNode.obj"
	-@erase ".\Debug\TTYWND.OBJ"
	-@erase ".\Debug\serial.obj"
	-@erase ".\Debug\PBFrWnd.obj"
	-@erase ".\Debug\PBWND.OBJ"
	-@erase ".\Debug\PBNode.res"
	-@erase "..\..\..\PB3DEBUG\PBNode.ilk"
	-@erase "..\..\..\PB3DEBUG\PBNode.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/PBNode.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/PBNode.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/PBNode.bsc" 
BSC32_SBRS= \
	"$(INTDIR)/StdAfx.sbr" \
	"$(INTDIR)/gfcomsock.sbr" \
	"$(INTDIR)/PBNode.sbr" \
	"$(INTDIR)/TTYWND.SBR" \
	"$(INTDIR)/serial.sbr" \
	"$(INTDIR)/PBFrWnd.sbr" \
	"$(INTDIR)/PBWND.SBR" \
	"$(INTDIR)/bufsock.sbr" \
	"$(INTDIR)/pbthread.sbr" \
	"$(INTDIR)/THREAD.SBR" \
	"$(INTDIR)/SCRNBUF.SBR" \
	"$(INTDIR)/rcvthread.sbr"

"$(OUTDIR)\PBNode.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 D:\GCPP300\MSVC40\CPFWM.LIB D:\DEV\PB32\PBSESS\DEBUG\PBSESS.LIB /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=D:\GCPP300\MSVC40\CPFWM.LIB D:\DEV\PB32\PBSESS\DEBUG\PBSESS.LIB\
 /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)/PBNode.pdb" /debug\
 /machine:I386 /out:"$(OUTDIR)/PBNode.exe" 
LINK32_OBJS= \
	"$(INTDIR)/bufsock.obj" \
	"$(INTDIR)/pbthread.obj" \
	"$(INTDIR)/THREAD.OBJ" \
	"$(INTDIR)/SCRNBUF.OBJ" \
	"$(INTDIR)/rcvthread.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/gfcomsock.obj" \
	"$(INTDIR)/PBNode.obj" \
	"$(INTDIR)/TTYWND.OBJ" \
	"$(INTDIR)/serial.obj" \
	"$(INTDIR)/PBFrWnd.obj" \
	"$(INTDIR)/PBWND.OBJ" \
	"$(INTDIR)/PBNode.res"

"$(OUTDIR)\PBNode.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "PBNode - Win32 Release"
# Name "PBNode - Win32 Debug"

!IF  "$(CFG)" == "PBNode - Win32 Release"

!ELSEIF  "$(CFG)" == "PBNode - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "PBNode - Win32 Release"

!ELSEIF  "$(CFG)" == "PBNode - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PBNode.cpp
DEP_CPP_PBNOD=\
	".\StdAfx.h"\
	".\PBNode.h"\
	".\PBFrWnd.h"\
	".\PBWnd.h"\
	".\ttywnd.h"\
	".\pbthread.h"\
	".\serial.h"\
	".\SCRNBUF.HPP"\
	{$(INCLUDE)}"\tslib.hpp"\
	".\THREAD.H"\
	{$(INCLUDE)}"\cache.hpp"\
	{$(INCLUDE)}"\recfile.hpp"\
	{$(INCLUDE)}"\llist.hpp"\
	

!IF  "$(CFG)" == "PBNode - Win32 Release"


"$(INTDIR)\PBNode.obj" : $(SOURCE) $(DEP_CPP_PBNOD) "$(INTDIR)"\
 "$(INTDIR)\PBNode.pch"


!ELSEIF  "$(CFG)" == "PBNode - Win32 Debug"


"$(INTDIR)\PBNode.obj" : $(SOURCE) $(DEP_CPP_PBNOD) "$(INTDIR)"\
 "$(INTDIR)\PBNode.pch"

"$(INTDIR)\PBNode.sbr" : $(SOURCE) $(DEP_CPP_PBNOD) "$(INTDIR)"\
 "$(INTDIR)\PBNode.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "PBNode - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/PBNode.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\PBNode.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "PBNode - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/PBNode.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StdAfx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\PBNode.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PBNode.rc
DEP_RSC_PBNODE=\
	".\res\PBNode.ico"\
	".\res\PBNode.rc2"\
	

"$(INTDIR)\PBNode.res" : $(SOURCE) $(DEP_RSC_PBNODE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\PBWND.CPP
DEP_CPP_PBWND=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\compplib.hpp"\
	".\ttywnd.h"\
	".\pbthread.h"\
	".\PBWnd.h"\
	"..\..\..\GCPP300\H\cppcomp.h"\
	"..\..\..\GCPP300\H\comdef.hpp"\
	"..\..\..\GCPP300\H\compat20.h"\
	"..\..\..\GCPP300\H\_comlink.hpp"\
	"..\..\..\GCPP300\H\_defs386.h"\
	"..\..\..\GCPP300\H\_dosisr.hpp"\
	"..\..\..\GCPP300\H\_star.hpp"\
	"..\..\..\GCPP300\H\nasi.hpp"\
	"..\..\..\GCPP300\H\asciidef.h"\
	"..\..\..\GCPP300\H\_8250.hpp"\
	".\SCRNBUF.HPP"\
	{$(INCLUDE)}"\tslib.hpp"\
	".\THREAD.H"\
	{$(INCLUDE)}"\cache.hpp"\
	{$(INCLUDE)}"\recfile.hpp"\
	{$(INCLUDE)}"\llist.hpp"\
	".\serial.h"\
	

!IF  "$(CFG)" == "PBNode - Win32 Release"


"$(INTDIR)\PBWND.OBJ" : $(SOURCE) $(DEP_CPP_PBWND) "$(INTDIR)"\
 "$(INTDIR)\PBNode.pch"


!ELSEIF  "$(CFG)" == "PBNode - Win32 Debug"


"$(INTDIR)\PBWND.OBJ" : $(SOURCE) $(DEP_CPP_PBWND) "$(INTDIR)"\
 "$(INTDIR)\PBNode.pch"

"$(INTDIR)\PBWND.SBR" : $(SOURCE) $(DEP_CPP_PBWND) "$(INTDIR)"\
 "$(INTDIR)\PBNode.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\pbthread.cpp
DEP_CPP_PBTHR=\
	{$(INCLUDE)}"\tslib.hpp"\
	{$(INCLUDE)}"\compplib.hpp"\
	{$(INCLUDE)}"\filexfer.hpp"\
	".\gfcomsock.h"\
	".\pbthread.h"\
	".\rcvthread.h"\
	".\PBWnd.h"\
	{$(INCLUDE)}"\cache.hpp"\
	{$(INCLUDE)}"\recfile.hpp"\
	{$(INCLUDE)}"\llist.hpp"\
	"..\..\..\GCPP300\H\cppcomp.h"\
	"..\..\..\GCPP300\H\comdef.hpp"\
	"..\..\..\GCPP300\H\compat20.h"\
	"..\..\..\GCPP300\H\_comlink.hpp"\
	"..\..\..\GCPP300\H\_defs386.h"\
	"..\..\..\GCPP300\H\_dosisr.hpp"\
	"..\..\..\GCPP300\H\_star.hpp"\
	"..\..\..\GCPP300\H\nasi.hpp"\
	"..\..\..\GCPP300\H\asciidef.h"\
	"..\..\..\GCPP300\H\_8250.hpp"\
	"..\..\..\GCPP300\H\_engine.hpp"\
	".\bufsock.h"\
	".\THREAD.H"\
	".\serial.h"\
	".\ttywnd.h"\
	".\SCRNBUF.HPP"\
	

!IF  "$(CFG)" == "PBNode - Win32 Release"


"$(INTDIR)\pbthread.obj" : $(SOURCE) $(DEP_CPP_PBTHR) "$(INTDIR)"\
 "$(INTDIR)\PBNode.pch"


!ELSEIF  "$(CFG)" == "PBNode - Win32 Debug"


"$(INTDIR)\pbthread.obj" : $(SOURCE) $(DEP_CPP_PBTHR) "$(INTDIR)"\
 "$(INTDIR)\PBNode.pch"

"$(INTDIR)\pbthread.sbr" : $(SOURCE) $(DEP_CPP_PBTHR) "$(INTDIR)"\
 "$(INTDIR)\PBNode.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PBFrWnd.cpp
DEP_CPP_PBFRW=\
	".\StdAfx.h"\
	".\PBNode.h"\
	".\PBFrWnd.h"\
	".\PBWnd.h"\
	".\ttywnd.h"\
	".\pbthread.h"\
	".\serial.h"\
	".\SCRNBUF.HPP"\
	{$(INCLUDE)}"\tslib.hpp"\
	".\THREAD.H"\
	{$(INCLUDE)}"\cache.hpp"\
	{$(INCLUDE)}"\recfile.hpp"\
	{$(INCLUDE)}"\llist.hpp"\
	

!IF  "$(CFG)" == "PBNode - Win32 Release"


"$(INTDIR)\PBFrWnd.obj" : $(SOURCE) $(DEP_CPP_PBFRW) "$(INTDIR)"\
 "$(INTDIR)\PBNode.pch"


!ELSEIF  "$(CFG)" == "PBNode - Win32 Debug"


"$(INTDIR)\PBFrWnd.obj" : $(SOURCE) $(DEP_CPP_PBFRW) "$(INTDIR)"\
 "$(INTDIR)\PBNode.pch"

"$(INTDIR)\PBFrWnd.sbr" : $(SOURCE) $(DEP_CPP_PBFRW) "$(INTDIR)"\
 "$(INTDIR)\PBNode.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TTYWND.CPP
DEP_CPP_TTYWN=\
	".\StdAfx.h"\
	".\ttywnd.h"\
	".\SCRNBUF.HPP"\
	

!IF  "$(CFG)" == "PBNode - Win32 Release"


"$(INTDIR)\TTYWND.OBJ" : $(SOURCE) $(DEP_CPP_TTYWN) "$(INTDIR)"\
 "$(INTDIR)\PBNode.pch"


!ELSEIF  "$(CFG)" == "PBNode - Win32 Debug"


"$(INTDIR)\TTYWND.OBJ" : $(SOURCE) $(DEP_CPP_TTYWN) "$(INTDIR)"\
 "$(INTDIR)\PBNode.pch"

"$(INTDIR)\TTYWND.SBR" : $(SOURCE) $(DEP_CPP_TTYWN) "$(INTDIR)"\
 "$(INTDIR)\PBNode.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SCRNBUF.CPP
DEP_CPP_SCRNB=\
	".\StdAfx.h"\
	".\SCRNBUF.HPP"\
	

!IF  "$(CFG)" == "PBNode - Win32 Release"


"$(INTDIR)\SCRNBUF.OBJ" : $(SOURCE) $(DEP_CPP_SCRNB) "$(INTDIR)"\
 "$(INTDIR)\PBNode.pch"


!ELSEIF  "$(CFG)" == "PBNode - Win32 Debug"


"$(INTDIR)\SCRNBUF.OBJ" : $(SOURCE) $(DEP_CPP_SCRNB) "$(INTDIR)"\
 "$(INTDIR)\PBNode.pch"

"$(INTDIR)\SCRNBUF.SBR" : $(SOURCE) $(DEP_CPP_SCRNB) "$(INTDIR)"\
 "$(INTDIR)\PBNode.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\serial.cpp
DEP_CPP_SERIA=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\compplib.hpp"\
	".\gfcomsock.h"\
	".\serial.h"\
	"..\..\..\GCPP300\H\cppcomp.h"\
	"..\..\..\GCPP300\H\comdef.hpp"\
	"..\..\..\GCPP300\H\compat20.h"\
	"..\..\..\GCPP300\H\_comlink.hpp"\
	"..\..\..\GCPP300\H\_defs386.h"\
	"..\..\..\GCPP300\H\_dosisr.hpp"\
	"..\..\..\GCPP300\H\_star.hpp"\
	"..\..\..\GCPP300\H\nasi.hpp"\
	"..\..\..\GCPP300\H\asciidef.h"\
	"..\..\..\GCPP300\H\_8250.hpp"\
	".\bufsock.h"\
	

!IF  "$(CFG)" == "PBNode - Win32 Release"


"$(INTDIR)\serial.obj" : $(SOURCE) $(DEP_CPP_SERIA) "$(INTDIR)"\
 "$(INTDIR)\PBNode.pch"


!ELSEIF  "$(CFG)" == "PBNode - Win32 Debug"


"$(INTDIR)\serial.obj" : $(SOURCE) $(DEP_CPP_SERIA) "$(INTDIR)"\
 "$(INTDIR)\PBNode.pch"

"$(INTDIR)\serial.sbr" : $(SOURCE) $(DEP_CPP_SERIA) "$(INTDIR)"\
 "$(INTDIR)\PBNode.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\THREAD.CPP
DEP_CPP_THREA=\
	".\THREAD.H"\
	

!IF  "$(CFG)" == "PBNode - Win32 Release"


"$(INTDIR)\THREAD.OBJ" : $(SOURCE) $(DEP_CPP_THREA) "$(INTDIR)"\
 "$(INTDIR)\PBNode.pch"


!ELSEIF  "$(CFG)" == "PBNode - Win32 Debug"


"$(INTDIR)\THREAD.OBJ" : $(SOURCE) $(DEP_CPP_THREA) "$(INTDIR)"\
 "$(INTDIR)\PBNode.pch"

"$(INTDIR)\THREAD.SBR" : $(SOURCE) $(DEP_CPP_THREA) "$(INTDIR)"\
 "$(INTDIR)\PBNode.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\gfcomsock.cpp
DEP_CPP_GFCOM=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\compplib.hpp"\
	{$(INCLUDE)}"\_cppmem.hpp"\
	".\gfcomsock.h"\
	"..\..\..\GCPP300\H\cppcomp.h"\
	"..\..\..\GCPP300\H\comdef.hpp"\
	"..\..\..\GCPP300\H\compat20.h"\
	"..\..\..\GCPP300\H\_comlink.hpp"\
	"..\..\..\GCPP300\H\_defs386.h"\
	"..\..\..\GCPP300\H\_dosisr.hpp"\
	"..\..\..\GCPP300\H\_star.hpp"\
	"..\..\..\GCPP300\H\nasi.hpp"\
	"..\..\..\GCPP300\H\asciidef.h"\
	"..\..\..\GCPP300\H\_8250.hpp"\
	".\bufsock.h"\
	

!IF  "$(CFG)" == "PBNode - Win32 Release"


"$(INTDIR)\gfcomsock.obj" : $(SOURCE) $(DEP_CPP_GFCOM) "$(INTDIR)"\
 "$(INTDIR)\PBNode.pch"


!ELSEIF  "$(CFG)" == "PBNode - Win32 Debug"


"$(INTDIR)\gfcomsock.obj" : $(SOURCE) $(DEP_CPP_GFCOM) "$(INTDIR)"\
 "$(INTDIR)\PBNode.pch"

"$(INTDIR)\gfcomsock.sbr" : $(SOURCE) $(DEP_CPP_GFCOM) "$(INTDIR)"\
 "$(INTDIR)\PBNode.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\bufsock.cpp
DEP_CPP_BUFSO=\
	".\StdAfx.h"\
	".\bufsock.h"\
	

!IF  "$(CFG)" == "PBNode - Win32 Release"


"$(INTDIR)\bufsock.obj" : $(SOURCE) $(DEP_CPP_BUFSO) "$(INTDIR)"\
 "$(INTDIR)\PBNode.pch"


!ELSEIF  "$(CFG)" == "PBNode - Win32 Debug"


"$(INTDIR)\bufsock.obj" : $(SOURCE) $(DEP_CPP_BUFSO) "$(INTDIR)"\
 "$(INTDIR)\PBNode.pch"

"$(INTDIR)\bufsock.sbr" : $(SOURCE) $(DEP_CPP_BUFSO) "$(INTDIR)"\
 "$(INTDIR)\PBNode.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\rcvthread.cpp
DEP_CPP_RCVTH=\
	{$(INCLUDE)}"\tslib.hpp"\
	{$(INCLUDE)}"\compplib.hpp"\
	".\gfcomsock.h"\
	".\rcvthread.h"\
	{$(INCLUDE)}"\cache.hpp"\
	{$(INCLUDE)}"\recfile.hpp"\
	{$(INCLUDE)}"\llist.hpp"\
	"..\..\..\GCPP300\H\cppcomp.h"\
	"..\..\..\GCPP300\H\comdef.hpp"\
	"..\..\..\GCPP300\H\compat20.h"\
	"..\..\..\GCPP300\H\_comlink.hpp"\
	"..\..\..\GCPP300\H\_defs386.h"\
	"..\..\..\GCPP300\H\_dosisr.hpp"\
	"..\..\..\GCPP300\H\_star.hpp"\
	"..\..\..\GCPP300\H\nasi.hpp"\
	"..\..\..\GCPP300\H\asciidef.h"\
	"..\..\..\GCPP300\H\_8250.hpp"\
	".\bufsock.h"\
	".\THREAD.H"\
	".\serial.h"\
	

!IF  "$(CFG)" == "PBNode - Win32 Release"


"$(INTDIR)\rcvthread.obj" : $(SOURCE) $(DEP_CPP_RCVTH) "$(INTDIR)"\
 "$(INTDIR)\PBNode.pch"


!ELSEIF  "$(CFG)" == "PBNode - Win32 Debug"


"$(INTDIR)\rcvthread.obj" : $(SOURCE) $(DEP_CPP_RCVTH) "$(INTDIR)"\
 "$(INTDIR)\PBNode.pch"

"$(INTDIR)\rcvthread.sbr" : $(SOURCE) $(DEP_CPP_RCVTH) "$(INTDIR)"\
 "$(INTDIR)\PBNode.pch"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
