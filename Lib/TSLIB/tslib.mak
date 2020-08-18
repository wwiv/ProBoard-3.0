# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

!IF "$(CFG)" == ""
CFG=TSLIB - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to TSLIB - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "TSLIB - Win32 Release" && "$(CFG)" != "TSLIB - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "TSLIB.MAK" CFG="TSLIB - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TSLIB - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "TSLIB - Win32 Debug" (based on "Win32 (x86) Static Library")
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
# PROP Target_Last_Scanned "TSLIB - Win32 Debug"
CPP=cl.exe

!IF  "$(CFG)" == "TSLIB - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\TSLIB.lib"

CLEAN : 
	-@erase ".\Release\TSLIB.lib"
	-@erase ".\Release\DIRFUNC.OBJ"
	-@erase ".\Release\INIVAR.OBJ"
	-@erase ".\Release\MISC.OBJ"
	-@erase ".\Release\COPYFILE.OBJ"
	-@erase ".\Release\FUZZY.OBJ"
	-@erase ".\Release\CRC32.OBJ"
	-@erase ".\Release\DATE.OBJ"
	-@erase ".\Release\DSTRING.OBJ"
	-@erase ".\Release\DIRSCAN.OBJ"
	-@erase ".\Release\DIRPORT.OBJ"
	-@erase ".\Release\FILE.OBJ"
	-@erase ".\Release\FNAME.OBJ"
	-@erase ".\Release\FORM.OBJ"
	-@erase ".\Release\BITARRAY.OBJ"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /Zp1 /MD /W3 /GX /O2 /I "." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /c
# SUBTRACT CPP /YX
CPP_PROJ=/nologo /Zp1 /MD /W3 /GX /O2 /I "." /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/TSLIB.bsc" 
BSC32_SBRS=
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/TSLIB.lib" 
LIB32_OBJS= \
	"$(INTDIR)/DIRFUNC.OBJ" \
	"$(INTDIR)/INIVAR.OBJ" \
	"$(INTDIR)/MISC.OBJ" \
	"$(INTDIR)/COPYFILE.OBJ" \
	"$(INTDIR)/FUZZY.OBJ" \
	"$(INTDIR)/CRC32.OBJ" \
	"$(INTDIR)/DATE.OBJ" \
	"$(INTDIR)/DSTRING.OBJ" \
	"$(INTDIR)/DIRSCAN.OBJ" \
	"$(INTDIR)/DIRPORT.OBJ" \
	"$(INTDIR)/FILE.OBJ" \
	"$(INTDIR)/FNAME.OBJ" \
	"$(INTDIR)/FORM.OBJ" \
	"$(INTDIR)/BITARRAY.OBJ"

"$(OUTDIR)\TSLIB.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "TSLIB - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\TSLIB.lib"

CLEAN : 
	-@erase ".\Debug\TSLIB.lib"
	-@erase ".\Debug\INIVAR.OBJ"
	-@erase ".\Debug\DSTRING.OBJ"
	-@erase ".\Debug\DIRSCAN.OBJ"
	-@erase ".\Debug\DATE.OBJ"
	-@erase ".\Debug\MISC.OBJ"
	-@erase ".\Debug\COPYFILE.OBJ"
	-@erase ".\Debug\DIRPORT.OBJ"
	-@erase ".\Debug\BITARRAY.OBJ"
	-@erase ".\Debug\FILE.OBJ"
	-@erase ".\Debug\FORM.OBJ"
	-@erase ".\Debug\FUZZY.OBJ"
	-@erase ".\Debug\CRC32.OBJ"
	-@erase ".\Debug\FNAME.OBJ"
	-@erase ".\Debug\DIRFUNC.OBJ"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /Zp1 /MDd /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /Zp1 /MDd /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/TSLIB.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/TSLIB.bsc" 
BSC32_SBRS=
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/TSLIB.lib" 
LIB32_OBJS= \
	"$(INTDIR)/INIVAR.OBJ" \
	"$(INTDIR)/DSTRING.OBJ" \
	"$(INTDIR)/DIRSCAN.OBJ" \
	"$(INTDIR)/DATE.OBJ" \
	"$(INTDIR)/MISC.OBJ" \
	"$(INTDIR)/COPYFILE.OBJ" \
	"$(INTDIR)/DIRPORT.OBJ" \
	"$(INTDIR)/BITARRAY.OBJ" \
	"$(INTDIR)/FILE.OBJ" \
	"$(INTDIR)/FORM.OBJ" \
	"$(INTDIR)/FUZZY.OBJ" \
	"$(INTDIR)/CRC32.OBJ" \
	"$(INTDIR)/FNAME.OBJ" \
	"$(INTDIR)/DIRFUNC.OBJ"

"$(OUTDIR)\TSLIB.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
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

# Name "TSLIB - Win32 Release"
# Name "TSLIB - Win32 Debug"

!IF  "$(CFG)" == "TSLIB - Win32 Release"

!ELSEIF  "$(CFG)" == "TSLIB - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\MISC.CPP
DEP_CPP_MISC_=\
	".\tslib.hpp"\
	".\cache.hpp"\
	".\recfile.hpp"\
	".\llist.hpp"\
	

"$(INTDIR)\MISC.OBJ" : $(SOURCE) $(DEP_CPP_MISC_) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\INIVAR.CPP
DEP_CPP_INIVA=\
	".\tslib.hpp"\
	".\cache.hpp"\
	".\recfile.hpp"\
	".\llist.hpp"\
	

"$(INTDIR)\INIVAR.OBJ" : $(SOURCE) $(DEP_CPP_INIVA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\FUZZY.CPP
DEP_CPP_FUZZY=\
	".\tslib.hpp"\
	".\cache.hpp"\
	".\recfile.hpp"\
	".\llist.hpp"\
	

"$(INTDIR)\FUZZY.OBJ" : $(SOURCE) $(DEP_CPP_FUZZY) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\FORM.CPP
DEP_CPP_FORM_=\
	".\tslib.hpp"\
	".\cache.hpp"\
	".\recfile.hpp"\
	".\llist.hpp"\
	

"$(INTDIR)\FORM.OBJ" : $(SOURCE) $(DEP_CPP_FORM_) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\FNAME.CPP
DEP_CPP_FNAME=\
	".\tslib.hpp"\
	".\cache.hpp"\
	".\recfile.hpp"\
	".\llist.hpp"\
	

"$(INTDIR)\FNAME.OBJ" : $(SOURCE) $(DEP_CPP_FNAME) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\FILE.CPP
DEP_CPP_FILE_=\
	{$(INCLUDE)}"\sys\STAT.H"\
	{$(INCLUDE)}"\sys\LOCKING.H"\
	".\tslib.hpp"\
	{$(INCLUDE)}"\sys\TYPES.H"\
	".\cache.hpp"\
	".\recfile.hpp"\
	".\llist.hpp"\
	

"$(INTDIR)\FILE.OBJ" : $(SOURCE) $(DEP_CPP_FILE_) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DSTRING.CPP
DEP_CPP_DSTRI=\
	".\tslib.hpp"\
	".\cache.hpp"\
	".\recfile.hpp"\
	".\llist.hpp"\
	

"$(INTDIR)\DSTRING.OBJ" : $(SOURCE) $(DEP_CPP_DSTRI) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DIRSCAN.CPP

!IF  "$(CFG)" == "TSLIB - Win32 Release"

DEP_CPP_DIRSC=\
	".\tslib.hpp"\
	".\dirport.h"\
	".\cache.hpp"\
	".\recfile.hpp"\
	".\llist.hpp"\
	".\extkword.h"\
	
NODEP_CPP_DIRSC=\
	".\os2.h"\
	".\dir.h"\
	

"$(INTDIR)\DIRSCAN.OBJ" : $(SOURCE) $(DEP_CPP_DIRSC) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "TSLIB - Win32 Debug"

DEP_CPP_DIRSC=\
	".\tslib.hpp"\
	".\dirport.h"\
	".\cache.hpp"\
	".\recfile.hpp"\
	".\llist.hpp"\
	

"$(INTDIR)\DIRSCAN.OBJ" : $(SOURCE) $(DEP_CPP_DIRSC) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DIRFUNC.CPP
DEP_CPP_DIRFU=\
	".\tslib.hpp"\
	".\cache.hpp"\
	".\recfile.hpp"\
	".\llist.hpp"\
	

"$(INTDIR)\DIRFUNC.OBJ" : $(SOURCE) $(DEP_CPP_DIRFU) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DATE.CPP
DEP_CPP_DATE_=\
	".\tslib.hpp"\
	".\cache.hpp"\
	".\recfile.hpp"\
	".\llist.hpp"\
	

"$(INTDIR)\DATE.OBJ" : $(SOURCE) $(DEP_CPP_DATE_) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\CRC32.CPP
DEP_CPP_CRC32=\
	".\tslib.hpp"\
	".\cache.hpp"\
	".\recfile.hpp"\
	".\llist.hpp"\
	

"$(INTDIR)\CRC32.OBJ" : $(SOURCE) $(DEP_CPP_CRC32) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\COPYFILE.CPP
DEP_CPP_COPYF=\
	".\tslib.hpp"\
	".\cache.hpp"\
	".\recfile.hpp"\
	".\llist.hpp"\
	

"$(INTDIR)\COPYFILE.OBJ" : $(SOURCE) $(DEP_CPP_COPYF) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\BITARRAY.CPP
DEP_CPP_BITAR=\
	".\tslib.hpp"\
	".\cache.hpp"\
	".\recfile.hpp"\
	".\llist.hpp"\
	

"$(INTDIR)\BITARRAY.OBJ" : $(SOURCE) $(DEP_CPP_BITAR) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DIRPORT.C

!IF  "$(CFG)" == "TSLIB - Win32 Release"

DEP_CPP_DIRPO=\
	".\dirport.h"\
	".\extkword.h"\
	
NODEP_CPP_DIRPO=\
	".\os2.h"\
	".\dir.h"\
	

"$(INTDIR)\DIRPORT.OBJ" : $(SOURCE) $(DEP_CPP_DIRPO) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "TSLIB - Win32 Debug"

DEP_CPP_DIRPO=\
	".\dirport.h"\
	

"$(INTDIR)\DIRPORT.OBJ" : $(SOURCE) $(DEP_CPP_DIRPO) "$(INTDIR)"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
