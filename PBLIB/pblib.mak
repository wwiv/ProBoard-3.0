# Microsoft Developer Studio Generated NMAKE File, Format Version 40001
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

!IF "$(CFG)" == ""
CFG=PBWinLib - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to PBWinLib - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "PBWinLib - Win32 Release" && "$(CFG)" !=\
 "PBWinLib - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "pblib.mak" CFG="PBWinLib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PBWinLib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "PBWinLib - Win32 Debug" (based on "Win32 (x86) Static Library")
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
# PROP Target_Last_Scanned "PBWinLib - Win32 Debug"
CPP=cl.exe

!IF  "$(CFG)" == "PBWinLib - Win32 Release"

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

ALL : "$(OUTDIR)\pblib.lib"

CLEAN : 
	-@erase ".\Release\pblib.lib"
	-@erase ".\Release\USER.OBJ"
	-@erase ".\Release\PBLIB.OBJ"
	-@erase ".\Release\LANGUAGE.OBJ"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /Zp1 /MD /W3 /GR /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /c
# SUBTRACT CPP /YX
CPP_PROJ=/nologo /Zp1 /MD /W3 /GR /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/pblib.bsc" 
BSC32_SBRS=
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/pblib.lib" 
LIB32_OBJS= \
	"$(INTDIR)/USER.OBJ" \
	"$(INTDIR)/PBLIB.OBJ" \
	"$(INTDIR)/LANGUAGE.OBJ"

"$(OUTDIR)\pblib.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "PBWinLib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "PBWinLib"
# PROP BASE Intermediate_Dir "PBWinLib"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\pblib.lib"

CLEAN : 
	-@erase ".\Debug\pblib.lib"
	-@erase ".\Debug\USER.OBJ"
	-@erase ".\Debug\PBLIB.OBJ"
	-@erase ".\Debug\LANGUAGE.OBJ"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /Zp1 /MDd /W3 /GR /GX /Z7 /O2 /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /c
# SUBTRACT CPP /YX
CPP_PROJ=/nologo /Zp1 /MDd /W3 /GR /GX /Z7 /O2 /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/pblib.bsc" 
BSC32_SBRS=
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/pblib.lib" 
LIB32_OBJS= \
	"$(INTDIR)/USER.OBJ" \
	"$(INTDIR)/PBLIB.OBJ" \
	"$(INTDIR)/LANGUAGE.OBJ"

"$(OUTDIR)\pblib.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
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

# Name "PBWinLib - Win32 Release"
# Name "PBWinLib - Win32 Debug"

!IF  "$(CFG)" == "PBWinLib - Win32 Release"

!ELSEIF  "$(CFG)" == "PBWinLib - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\USER.CPP
DEP_CPP_USER_=\
	{$(INCLUDE)}"\TSLIB.HPP"\
	".\pblib.hpp"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	

"$(INTDIR)\USER.OBJ" : $(SOURCE) $(DEP_CPP_USER_) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\PBLIB.CPP
DEP_CPP_PBLIB=\
	{$(INCLUDE)}"\TSLIB.HPP"\
	".\pblib.hpp"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	

"$(INTDIR)\PBLIB.OBJ" : $(SOURCE) $(DEP_CPP_PBLIB) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\LANGUAGE.CPP
DEP_CPP_LANGU=\
	{$(INCLUDE)}"\TSLIB.HPP"\
	".\pblib.hpp"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	

"$(INTDIR)\LANGUAGE.OBJ" : $(SOURCE) $(DEP_CPP_LANGU) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################
