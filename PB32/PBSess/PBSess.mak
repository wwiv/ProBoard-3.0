# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=PBSess - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to PBSess - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "PBSess - Win32 Release" && "$(CFG)" != "PBSess - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "PBSess.mak" CFG="PBSess - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PBSess - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "PBSess - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "PBSess - Win32 Debug"
RSC=rc.exe
CPP=cl.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "PBSess - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "D:\PB32"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=D:\PB32
INTDIR=.\Release

ALL : "$(OUTDIR)\PBSess.dll"

CLEAN : 
	-@erase "..\..\..\PB32\PBSess.dll"
	-@erase ".\Release\MSGEXPRT.OBJ"
	-@erase ".\Release\DL.OBJ"
	-@erase ".\Release\READMSG.OBJ"
	-@erase ".\Release\PROBOARD.OBJ"
	-@erase ".\Release\TAG_RW.OBJ"
	-@erase ".\Release\MSGAREA.OBJ"
	-@erase ".\Release\PROTOCOL.OBJ"
	-@erase ".\Release\COMBINED.OBJ"
	-@erase ".\Release\SHOWMSG.OBJ"
	-@erase ".\Release\RUNPEX.OBJ"
	-@erase ".\Release\BULLETIN.OBJ"
	-@erase ".\Release\MSGFWD.OBJ"
	-@erase ".\Release\STRVAR.OBJ"
	-@erase ".\Release\UL.OBJ"
	-@erase ".\Release\SHELL.OBJ"
	-@erase ".\Release\NODELIST.OBJ"
	-@erase ".\Release\LIMIT.OBJ"
	-@erase ".\Release\USERSET.OBJ"
	-@erase ".\Release\MENUPROC.OBJ"
	-@erase ".\Release\POSTMSG.OBJ"
	-@erase ".\Release\JAM.OBJ"
	-@erase ".\Release\LISTFILE.OBJ"
	-@erase ".\Release\MSGDEL.OBJ"
	-@erase ".\Release\MSGFIND.OBJ"
	-@erase ".\Release\SHOWANS.OBJ"
	-@erase ".\Release\INPDATE.OBJ"
	-@erase ".\Release\HUDSON.OBJ"
	-@erase ".\Release\LOGIN.OBJ"
	-@erase ".\Release\WORDWRAP.OBJ"
	-@erase ".\Release\AKA.OBJ"
	-@erase ".\Release\FILEAREA.OBJ"
	-@erase ".\Release\GLOBAL.OBJ"
	-@erase ".\Release\DATEFMT.OBJ"
	-@erase ".\Release\TAG.OBJ"
	-@erase ".\Release\TIMER.OBJ"
	-@erase ".\Release\CDROM.OBJ"
	-@erase ".\Release\INTRO.OBJ"
	-@erase ".\Release\MSGBASE.OBJ"
	-@erase ".\Release\SELLANG.OBJ"
	-@erase ".\Release\delay.obj"
	-@erase ".\Release\MARK.OBJ"
	-@erase ".\Release\MSGED.OBJ"
	-@erase ".\Release\READCFG.OBJ"
	-@erase ".\Release\MSGMOVE.OBJ"
	-@erase ".\Release\WRITEMSG.OBJ"
	-@erase ".\Release\LANGUAGE.OBJ"
	-@erase ".\Release\REPLYMSG.OBJ"
	-@erase ".\Release\QUESTION.OBJ"
	-@erase ".\Release\SETAREA.OBJ"
	-@erase ".\Release\MSG.OBJ"
	-@erase ".\Release\RACRC.OBJ"
	-@erase ".\Release\IO.OBJ"
	-@erase "..\..\..\PB32\PBSess.lib"
	-@erase "..\..\..\PB32\PBSess.exp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /Zp1 /MD /W3 /GX /O2 /I "D:\DEV\PBLIB" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /c
# SUBTRACT CPP /YX
CPP_PROJ=/nologo /Zp1 /MD /W3 /GX /O2 /I "D:\DEV\PBLIB" /D "WIN32" /D "NDEBUG"\
 /D "_WINDOWS" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/PBSess.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib d:\dev\tslib\release\tslib.lib d:\dev\pblib\release\pblib.lib /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib d:\dev\tslib\release\tslib.lib d:\dev\pblib\release\pblib.lib\
 /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)/PBSess.pdb"\
 /machine:I386 /out:"$(OUTDIR)/PBSess.dll" /implib:"$(OUTDIR)/PBSess.lib" 
LINK32_OBJS= \
	"$(INTDIR)/MSGEXPRT.OBJ" \
	"$(INTDIR)/DL.OBJ" \
	"$(INTDIR)/READMSG.OBJ" \
	"$(INTDIR)/PROBOARD.OBJ" \
	"$(INTDIR)/TAG_RW.OBJ" \
	"$(INTDIR)/MSGAREA.OBJ" \
	"$(INTDIR)/PROTOCOL.OBJ" \
	"$(INTDIR)/COMBINED.OBJ" \
	"$(INTDIR)/SHOWMSG.OBJ" \
	"$(INTDIR)/RUNPEX.OBJ" \
	"$(INTDIR)/BULLETIN.OBJ" \
	"$(INTDIR)/MSGFWD.OBJ" \
	"$(INTDIR)/STRVAR.OBJ" \
	"$(INTDIR)/UL.OBJ" \
	"$(INTDIR)/SHELL.OBJ" \
	"$(INTDIR)/NODELIST.OBJ" \
	"$(INTDIR)/LIMIT.OBJ" \
	"$(INTDIR)/USERSET.OBJ" \
	"$(INTDIR)/MENUPROC.OBJ" \
	"$(INTDIR)/POSTMSG.OBJ" \
	"$(INTDIR)/JAM.OBJ" \
	"$(INTDIR)/LISTFILE.OBJ" \
	"$(INTDIR)/MSGDEL.OBJ" \
	"$(INTDIR)/MSGFIND.OBJ" \
	"$(INTDIR)/SHOWANS.OBJ" \
	"$(INTDIR)/INPDATE.OBJ" \
	"$(INTDIR)/HUDSON.OBJ" \
	"$(INTDIR)/LOGIN.OBJ" \
	"$(INTDIR)/WORDWRAP.OBJ" \
	"$(INTDIR)/AKA.OBJ" \
	"$(INTDIR)/FILEAREA.OBJ" \
	"$(INTDIR)/GLOBAL.OBJ" \
	"$(INTDIR)/DATEFMT.OBJ" \
	"$(INTDIR)/TAG.OBJ" \
	"$(INTDIR)/TIMER.OBJ" \
	"$(INTDIR)/CDROM.OBJ" \
	"$(INTDIR)/INTRO.OBJ" \
	"$(INTDIR)/MSGBASE.OBJ" \
	"$(INTDIR)/SELLANG.OBJ" \
	"$(INTDIR)/delay.obj" \
	"$(INTDIR)/MARK.OBJ" \
	"$(INTDIR)/MSGED.OBJ" \
	"$(INTDIR)/READCFG.OBJ" \
	"$(INTDIR)/MSGMOVE.OBJ" \
	"$(INTDIR)/WRITEMSG.OBJ" \
	"$(INTDIR)/LANGUAGE.OBJ" \
	"$(INTDIR)/REPLYMSG.OBJ" \
	"$(INTDIR)/QUESTION.OBJ" \
	"$(INTDIR)/SETAREA.OBJ" \
	"$(INTDIR)/MSG.OBJ" \
	"$(INTDIR)/RACRC.OBJ" \
	"$(INTDIR)/IO.OBJ"

"$(OUTDIR)\PBSess.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "PBSess - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "D:\PB3DEBUG"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=D:\PB3DEBUG
INTDIR=.\Debug

ALL : "$(OUTDIR)\PBSess.dll" "$(OUTDIR)\PBSess.bsc"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"
	-@erase "..\..\..\PB3DEBUG\PBSess.dll"
	-@erase ".\Debug\LOGIN.OBJ"
	-@erase ".\Debug\MSGBASE.OBJ"
	-@erase ".\Debug\NODELIST.OBJ"
	-@erase ".\Debug\RACRC.OBJ"
	-@erase ".\Debug\SELLANG.OBJ"
	-@erase ".\Debug\MSGDEL.OBJ"
	-@erase ".\Debug\HUDSON.OBJ"
	-@erase ".\Debug\UL.OBJ"
	-@erase ".\Debug\LISTFILE.OBJ"
	-@erase ".\Debug\READCFG.OBJ"
	-@erase ".\Debug\TAG.OBJ"
	-@erase ".\Debug\MSGMOVE.OBJ"
	-@erase ".\Debug\LANGUAGE.OBJ"
	-@erase ".\Debug\TIMER.OBJ"
	-@erase ".\Debug\REPLYMSG.OBJ"
	-@erase ".\Debug\QUESTION.OBJ"
	-@erase ".\Debug\CDROM.OBJ"
	-@erase ".\Debug\GLOBAL.OBJ"
	-@erase ".\Debug\MSGFWD.OBJ"
	-@erase ".\Debug\SETAREA.OBJ"
	-@erase ".\Debug\MSGED.OBJ"
	-@erase ".\Debug\INPDATE.OBJ"
	-@erase ".\Debug\FILEAREA.OBJ"
	-@erase ".\Debug\COMBINED.OBJ"
	-@erase ".\Debug\READMSG.OBJ"
	-@erase ".\Debug\MSGAREA.OBJ"
	-@erase ".\Debug\SHOWMSG.OBJ"
	-@erase ".\Debug\AKA.OBJ"
	-@erase ".\Debug\MARK.OBJ"
	-@erase ".\Debug\WRITEMSG.OBJ"
	-@erase ".\Debug\MENUPROC.OBJ"
	-@erase ".\Debug\TAG_RW.OBJ"
	-@erase ".\Debug\USERSET.OBJ"
	-@erase ".\Debug\POSTMSG.OBJ"
	-@erase ".\Debug\MSGEXPRT.OBJ"
	-@erase ".\Debug\INTRO.OBJ"
	-@erase ".\Debug\RUNPEX.OBJ"
	-@erase ".\Debug\SHELL.OBJ"
	-@erase ".\Debug\PROBOARD.OBJ"
	-@erase ".\Debug\delay.obj"
	-@erase ".\Debug\MSGFIND.OBJ"
	-@erase ".\Debug\PROTOCOL.OBJ"
	-@erase ".\Debug\WORDWRAP.OBJ"
	-@erase ".\Debug\SHOWANS.OBJ"
	-@erase ".\Debug\LIMIT.OBJ"
	-@erase ".\Debug\IO.OBJ"
	-@erase ".\Debug\BULLETIN.OBJ"
	-@erase ".\Debug\STRVAR.OBJ"
	-@erase ".\Debug\JAM.OBJ"
	-@erase ".\Debug\MSG.OBJ"
	-@erase ".\Debug\DL.OBJ"
	-@erase ".\Debug\DATEFMT.OBJ"
	-@erase "..\..\..\PB3DEBUG\PBSess.ilk"
	-@erase "..\..\..\PB3DEBUG\PBSess.lib"
	-@erase "..\..\..\PB3DEBUG\PBSess.exp"
	-@erase "..\..\..\PB3DEBUG\PBSess.pdb"
	-@erase "..\..\..\PB3DEBUG\PBSess.bsc"
	-@erase ".\Debug\WRITEMSG.SBR"
	-@erase ".\Debug\WORDWRAP.SBR"
	-@erase ".\Debug\USERSET.SBR"
	-@erase ".\Debug\TAG_RW.SBR"
	-@erase ".\Debug\STRVAR.SBR"
	-@erase ".\Debug\SHOWMSG.SBR"
	-@erase ".\Debug\SHOWANS.SBR"
	-@erase ".\Debug\SHELL.SBR"
	-@erase ".\Debug\SELLANG.SBR"
	-@erase ".\Debug\RUNPEX.SBR"
	-@erase ".\Debug\REPLYMSG.SBR"
	-@erase ".\Debug\READMSG.SBR"
	-@erase ".\Debug\READCFG.SBR"
	-@erase ".\Debug\RACRC.SBR"
	-@erase ".\Debug\QUESTION.SBR"
	-@erase ".\Debug\POSTMSG.SBR"
	-@erase ".\Debug\NODELIST.SBR"
	-@erase ".\Debug\MSGFIND.SBR"
	-@erase ".\Debug\MSGEXPRT.SBR"
	-@erase ".\Debug\MSGED.SBR"
	-@erase ".\Debug\MSGBASE.SBR"
	-@erase ".\Debug\MSGAREA.SBR"
	-@erase ".\Debug\MSG.SBR"
	-@erase ".\Debug\MENUPROC.SBR"
	-@erase ".\Debug\MARK.SBR"
	-@erase ".\Debug\LOGIN.SBR"
	-@erase ".\Debug\LANGUAGE.SBR"
	-@erase ".\Debug\JAM.SBR"
	-@erase ".\Debug\IO.SBR"
	-@erase ".\Debug\INTRO.SBR"
	-@erase ".\Debug\INPDATE.SBR"
	-@erase ".\Debug\HUDSON.SBR"
	-@erase ".\Debug\DATEFMT.SBR"
	-@erase ".\Debug\delay.sbr"
	-@erase ".\Debug\GLOBAL.SBR"
	-@erase ".\Debug\MSGMOVE.SBR"
	-@erase ".\Debug\MSGDEL.SBR"
	-@erase ".\Debug\MSGFWD.SBR"
	-@erase ".\Debug\AKA.SBR"
	-@erase ".\Debug\SETAREA.SBR"
	-@erase ".\Debug\FILEAREA.SBR"
	-@erase ".\Debug\PROBOARD.SBR"
	-@erase ".\Debug\LISTFILE.SBR"
	-@erase ".\Debug\TAG.SBR"
	-@erase ".\Debug\BULLETIN.SBR"
	-@erase ".\Debug\COMBINED.SBR"
	-@erase ".\Debug\DL.SBR"
	-@erase ".\Debug\TIMER.SBR"
	-@erase ".\Debug\UL.SBR"
	-@erase ".\Debug\PROTOCOL.SBR"
	-@erase ".\Debug\LIMIT.SBR"
	-@erase ".\Debug\CDROM.SBR"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /Zp1 /MDd /W3 /Gm /GX /Zi /Od /I "D:\DEV\PBLIB" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /c
# SUBTRACT CPP /YX
CPP_PROJ=/nologo /Zp1 /MDd /W3 /Gm /GX /Zi /Od /I "D:\DEV\PBLIB" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)/" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/PBSess.bsc" 
BSC32_SBRS= \
	"$(INTDIR)/WRITEMSG.SBR" \
	"$(INTDIR)/WORDWRAP.SBR" \
	"$(INTDIR)/USERSET.SBR" \
	"$(INTDIR)/TAG_RW.SBR" \
	"$(INTDIR)/STRVAR.SBR" \
	"$(INTDIR)/SHOWMSG.SBR" \
	"$(INTDIR)/SHOWANS.SBR" \
	"$(INTDIR)/SHELL.SBR" \
	"$(INTDIR)/SELLANG.SBR" \
	"$(INTDIR)/RUNPEX.SBR" \
	"$(INTDIR)/REPLYMSG.SBR" \
	"$(INTDIR)/READMSG.SBR" \
	"$(INTDIR)/READCFG.SBR" \
	"$(INTDIR)/RACRC.SBR" \
	"$(INTDIR)/QUESTION.SBR" \
	"$(INTDIR)/POSTMSG.SBR" \
	"$(INTDIR)/NODELIST.SBR" \
	"$(INTDIR)/MSGFIND.SBR" \
	"$(INTDIR)/MSGEXPRT.SBR" \
	"$(INTDIR)/MSGED.SBR" \
	"$(INTDIR)/MSGBASE.SBR" \
	"$(INTDIR)/MSGAREA.SBR" \
	"$(INTDIR)/MSG.SBR" \
	"$(INTDIR)/MENUPROC.SBR" \
	"$(INTDIR)/MARK.SBR" \
	"$(INTDIR)/LOGIN.SBR" \
	"$(INTDIR)/LANGUAGE.SBR" \
	"$(INTDIR)/JAM.SBR" \
	"$(INTDIR)/IO.SBR" \
	"$(INTDIR)/INTRO.SBR" \
	"$(INTDIR)/INPDATE.SBR" \
	"$(INTDIR)/HUDSON.SBR" \
	"$(INTDIR)/DATEFMT.SBR" \
	"$(INTDIR)/delay.sbr" \
	"$(INTDIR)/GLOBAL.SBR" \
	"$(INTDIR)/MSGMOVE.SBR" \
	"$(INTDIR)/MSGDEL.SBR" \
	"$(INTDIR)/MSGFWD.SBR" \
	"$(INTDIR)/AKA.SBR" \
	"$(INTDIR)/SETAREA.SBR" \
	"$(INTDIR)/FILEAREA.SBR" \
	"$(INTDIR)/PROBOARD.SBR" \
	"$(INTDIR)/LISTFILE.SBR" \
	"$(INTDIR)/TAG.SBR" \
	"$(INTDIR)/BULLETIN.SBR" \
	"$(INTDIR)/COMBINED.SBR" \
	"$(INTDIR)/DL.SBR" \
	"$(INTDIR)/TIMER.SBR" \
	"$(INTDIR)/UL.SBR" \
	"$(INTDIR)/PROTOCOL.SBR" \
	"$(INTDIR)/LIMIT.SBR" \
	"$(INTDIR)/CDROM.SBR"

"$(OUTDIR)\PBSess.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib d:\dev\tslib\debug\tslib.lib d:\dev\pblib\debug\pblib.lib /nologo /subsystem:windows /dll /debug /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib d:\dev\tslib\debug\tslib.lib d:\dev\pblib\debug\pblib.lib /nologo\
 /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)/PBSess.pdb" /debug\
 /machine:I386 /out:"$(OUTDIR)/PBSess.dll" /implib:"$(OUTDIR)/PBSess.lib" 
LINK32_OBJS= \
	"$(INTDIR)/LOGIN.OBJ" \
	"$(INTDIR)/MSGBASE.OBJ" \
	"$(INTDIR)/NODELIST.OBJ" \
	"$(INTDIR)/RACRC.OBJ" \
	"$(INTDIR)/SELLANG.OBJ" \
	"$(INTDIR)/MSGDEL.OBJ" \
	"$(INTDIR)/HUDSON.OBJ" \
	"$(INTDIR)/UL.OBJ" \
	"$(INTDIR)/LISTFILE.OBJ" \
	"$(INTDIR)/READCFG.OBJ" \
	"$(INTDIR)/TAG.OBJ" \
	"$(INTDIR)/MSGMOVE.OBJ" \
	"$(INTDIR)/LANGUAGE.OBJ" \
	"$(INTDIR)/TIMER.OBJ" \
	"$(INTDIR)/REPLYMSG.OBJ" \
	"$(INTDIR)/QUESTION.OBJ" \
	"$(INTDIR)/CDROM.OBJ" \
	"$(INTDIR)/GLOBAL.OBJ" \
	"$(INTDIR)/MSGFWD.OBJ" \
	"$(INTDIR)/SETAREA.OBJ" \
	"$(INTDIR)/MSGED.OBJ" \
	"$(INTDIR)/INPDATE.OBJ" \
	"$(INTDIR)/FILEAREA.OBJ" \
	"$(INTDIR)/COMBINED.OBJ" \
	"$(INTDIR)/READMSG.OBJ" \
	"$(INTDIR)/MSGAREA.OBJ" \
	"$(INTDIR)/SHOWMSG.OBJ" \
	"$(INTDIR)/AKA.OBJ" \
	"$(INTDIR)/MARK.OBJ" \
	"$(INTDIR)/WRITEMSG.OBJ" \
	"$(INTDIR)/MENUPROC.OBJ" \
	"$(INTDIR)/TAG_RW.OBJ" \
	"$(INTDIR)/USERSET.OBJ" \
	"$(INTDIR)/POSTMSG.OBJ" \
	"$(INTDIR)/MSGEXPRT.OBJ" \
	"$(INTDIR)/INTRO.OBJ" \
	"$(INTDIR)/RUNPEX.OBJ" \
	"$(INTDIR)/SHELL.OBJ" \
	"$(INTDIR)/PROBOARD.OBJ" \
	"$(INTDIR)/delay.obj" \
	"$(INTDIR)/MSGFIND.OBJ" \
	"$(INTDIR)/PROTOCOL.OBJ" \
	"$(INTDIR)/WORDWRAP.OBJ" \
	"$(INTDIR)/SHOWANS.OBJ" \
	"$(INTDIR)/LIMIT.OBJ" \
	"$(INTDIR)/IO.OBJ" \
	"$(INTDIR)/BULLETIN.OBJ" \
	"$(INTDIR)/STRVAR.OBJ" \
	"$(INTDIR)/JAM.OBJ" \
	"$(INTDIR)/MSG.OBJ" \
	"$(INTDIR)/DL.OBJ" \
	"$(INTDIR)/DATEFMT.OBJ"

"$(OUTDIR)\PBSess.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "PBSess - Win32 Release"
# Name "PBSess - Win32 Debug"

!IF  "$(CFG)" == "PBSess - Win32 Release"

!ELSEIF  "$(CFG)" == "PBSess - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\WRITEMSG.CPP
DEP_CPP_WRITE=\
	".\PROBOARD.HPP"\
	{$(INCLUDE)}"\TSLIB.HPP"\
	"\DEV\PBLIB\pblib.hpp"\
	".\MSGBASE.HPP"\
	".\PROMPTS.HPP"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	

!IF  "$(CFG)" == "PBSess - Win32 Release"


"$(INTDIR)\WRITEMSG.OBJ" : $(SOURCE) $(DEP_CPP_WRITE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PBSess - Win32 Debug"


"$(INTDIR)\WRITEMSG.OBJ" : $(SOURCE) $(DEP_CPP_WRITE) "$(INTDIR)"

"$(INTDIR)\WRITEMSG.SBR" : $(SOURCE) $(DEP_CPP_WRITE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\WORDWRAP.CPP
DEP_CPP_WORDW=\
	".\PROBOARD.HPP"\
	{$(INCLUDE)}"\TSLIB.HPP"\
	"\DEV\PBLIB\pblib.hpp"\
	".\MSGBASE.HPP"\
	".\PROMPTS.HPP"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	

!IF  "$(CFG)" == "PBSess - Win32 Release"


"$(INTDIR)\WORDWRAP.OBJ" : $(SOURCE) $(DEP_CPP_WORDW) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PBSess - Win32 Debug"


"$(INTDIR)\WORDWRAP.OBJ" : $(SOURCE) $(DEP_CPP_WORDW) "$(INTDIR)"

"$(INTDIR)\WORDWRAP.SBR" : $(SOURCE) $(DEP_CPP_WORDW) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\USERSET.CPP
DEP_CPP_USERS=\
	".\PROBOARD.HPP"\
	{$(INCLUDE)}"\TSLIB.HPP"\
	"\DEV\PBLIB\pblib.hpp"\
	".\MSGBASE.HPP"\
	".\PROMPTS.HPP"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	

!IF  "$(CFG)" == "PBSess - Win32 Release"


"$(INTDIR)\USERSET.OBJ" : $(SOURCE) $(DEP_CPP_USERS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PBSess - Win32 Debug"


"$(INTDIR)\USERSET.OBJ" : $(SOURCE) $(DEP_CPP_USERS) "$(INTDIR)"

"$(INTDIR)\USERSET.SBR" : $(SOURCE) $(DEP_CPP_USERS) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TAG_RW.CPP
DEP_CPP_TAG_R=\
	".\PROBOARD.HPP"\
	{$(INCLUDE)}"\TSLIB.HPP"\
	"\DEV\PBLIB\pblib.hpp"\
	".\MSGBASE.HPP"\
	".\PROMPTS.HPP"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	

!IF  "$(CFG)" == "PBSess - Win32 Release"


"$(INTDIR)\TAG_RW.OBJ" : $(SOURCE) $(DEP_CPP_TAG_R) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PBSess - Win32 Debug"


"$(INTDIR)\TAG_RW.OBJ" : $(SOURCE) $(DEP_CPP_TAG_R) "$(INTDIR)"

"$(INTDIR)\TAG_RW.SBR" : $(SOURCE) $(DEP_CPP_TAG_R) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRVAR.CPP
DEP_CPP_STRVA=\
	".\PROBOARD.HPP"\
	{$(INCLUDE)}"\TSLIB.HPP"\
	"\DEV\PBLIB\pblib.hpp"\
	".\MSGBASE.HPP"\
	".\PROMPTS.HPP"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	

!IF  "$(CFG)" == "PBSess - Win32 Release"


"$(INTDIR)\STRVAR.OBJ" : $(SOURCE) $(DEP_CPP_STRVA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PBSess - Win32 Debug"


"$(INTDIR)\STRVAR.OBJ" : $(SOURCE) $(DEP_CPP_STRVA) "$(INTDIR)"

"$(INTDIR)\STRVAR.SBR" : $(SOURCE) $(DEP_CPP_STRVA) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SHOWMSG.CPP
DEP_CPP_SHOWM=\
	".\PROBOARD.HPP"\
	{$(INCLUDE)}"\TSLIB.HPP"\
	"\DEV\PBLIB\pblib.hpp"\
	".\MSGBASE.HPP"\
	".\PROMPTS.HPP"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	

!IF  "$(CFG)" == "PBSess - Win32 Release"


"$(INTDIR)\SHOWMSG.OBJ" : $(SOURCE) $(DEP_CPP_SHOWM) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PBSess - Win32 Debug"


"$(INTDIR)\SHOWMSG.OBJ" : $(SOURCE) $(DEP_CPP_SHOWM) "$(INTDIR)"

"$(INTDIR)\SHOWMSG.SBR" : $(SOURCE) $(DEP_CPP_SHOWM) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SHOWANS.CPP
DEP_CPP_SHOWA=\
	".\PROBOARD.HPP"\
	{$(INCLUDE)}"\TSLIB.HPP"\
	"\DEV\PBLIB\pblib.hpp"\
	".\MSGBASE.HPP"\
	".\PROMPTS.HPP"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	

!IF  "$(CFG)" == "PBSess - Win32 Release"


"$(INTDIR)\SHOWANS.OBJ" : $(SOURCE) $(DEP_CPP_SHOWA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PBSess - Win32 Debug"


"$(INTDIR)\SHOWANS.OBJ" : $(SOURCE) $(DEP_CPP_SHOWA) "$(INTDIR)"

"$(INTDIR)\SHOWANS.SBR" : $(SOURCE) $(DEP_CPP_SHOWA) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SHELL.CPP
DEP_CPP_SHELL=\
	".\PROBOARD.HPP"\
	{$(INCLUDE)}"\TSLIB.HPP"\
	"\DEV\PBLIB\pblib.hpp"\
	".\MSGBASE.HPP"\
	".\PROMPTS.HPP"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	

!IF  "$(CFG)" == "PBSess - Win32 Release"


"$(INTDIR)\SHELL.OBJ" : $(SOURCE) $(DEP_CPP_SHELL) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PBSess - Win32 Debug"


"$(INTDIR)\SHELL.OBJ" : $(SOURCE) $(DEP_CPP_SHELL) "$(INTDIR)"

"$(INTDIR)\SHELL.SBR" : $(SOURCE) $(DEP_CPP_SHELL) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SELLANG.CPP
DEP_CPP_SELLA=\
	".\PROBOARD.HPP"\
	{$(INCLUDE)}"\TSLIB.HPP"\
	"\DEV\PBLIB\pblib.hpp"\
	".\MSGBASE.HPP"\
	".\PROMPTS.HPP"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	

!IF  "$(CFG)" == "PBSess - Win32 Release"


"$(INTDIR)\SELLANG.OBJ" : $(SOURCE) $(DEP_CPP_SELLA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PBSess - Win32 Debug"


"$(INTDIR)\SELLANG.OBJ" : $(SOURCE) $(DEP_CPP_SELLA) "$(INTDIR)"

"$(INTDIR)\SELLANG.SBR" : $(SOURCE) $(DEP_CPP_SELLA) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\RUNPEX.CPP
DEP_CPP_RUNPE=\
	".\PROBOARD.HPP"\
	{$(INCLUDE)}"\TSLIB.HPP"\
	"\DEV\PBLIB\pblib.hpp"\
	".\MSGBASE.HPP"\
	".\PROMPTS.HPP"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	

!IF  "$(CFG)" == "PBSess - Win32 Release"


"$(INTDIR)\RUNPEX.OBJ" : $(SOURCE) $(DEP_CPP_RUNPE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PBSess - Win32 Debug"


"$(INTDIR)\RUNPEX.OBJ" : $(SOURCE) $(DEP_CPP_RUNPE) "$(INTDIR)"

"$(INTDIR)\RUNPEX.SBR" : $(SOURCE) $(DEP_CPP_RUNPE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\REPLYMSG.CPP
DEP_CPP_REPLY=\
	".\PROBOARD.HPP"\
	{$(INCLUDE)}"\TSLIB.HPP"\
	"\DEV\PBLIB\pblib.hpp"\
	".\MSGBASE.HPP"\
	".\PROMPTS.HPP"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	

!IF  "$(CFG)" == "PBSess - Win32 Release"


"$(INTDIR)\REPLYMSG.OBJ" : $(SOURCE) $(DEP_CPP_REPLY) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PBSess - Win32 Debug"


"$(INTDIR)\REPLYMSG.OBJ" : $(SOURCE) $(DEP_CPP_REPLY) "$(INTDIR)"

"$(INTDIR)\REPLYMSG.SBR" : $(SOURCE) $(DEP_CPP_REPLY) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\READMSG.CPP
DEP_CPP_READM=\
	".\PROBOARD.HPP"\
	{$(INCLUDE)}"\TSLIB.HPP"\
	"\DEV\PBLIB\pblib.hpp"\
	".\MSGBASE.HPP"\
	".\PROMPTS.HPP"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	

!IF  "$(CFG)" == "PBSess - Win32 Release"


"$(INTDIR)\READMSG.OBJ" : $(SOURCE) $(DEP_CPP_READM) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PBSess - Win32 Debug"


"$(INTDIR)\READMSG.OBJ" : $(SOURCE) $(DEP_CPP_READM) "$(INTDIR)"

"$(INTDIR)\READMSG.SBR" : $(SOURCE) $(DEP_CPP_READM) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\READCFG.CPP
DEP_CPP_READC=\
	".\PROBOARD.HPP"\
	{$(INCLUDE)}"\TSLIB.HPP"\
	"\DEV\PBLIB\pblib.hpp"\
	".\MSGBASE.HPP"\
	".\PROMPTS.HPP"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	

!IF  "$(CFG)" == "PBSess - Win32 Release"


"$(INTDIR)\READCFG.OBJ" : $(SOURCE) $(DEP_CPP_READC) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PBSess - Win32 Debug"


"$(INTDIR)\READCFG.OBJ" : $(SOURCE) $(DEP_CPP_READC) "$(INTDIR)"

"$(INTDIR)\READCFG.SBR" : $(SOURCE) $(DEP_CPP_READC) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\RACRC.CPP
DEP_CPP_RACRC=\
	".\PROBOARD.HPP"\
	{$(INCLUDE)}"\TSLIB.HPP"\
	"\DEV\PBLIB\pblib.hpp"\
	".\MSGBASE.HPP"\
	".\PROMPTS.HPP"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	

!IF  "$(CFG)" == "PBSess - Win32 Release"


"$(INTDIR)\RACRC.OBJ" : $(SOURCE) $(DEP_CPP_RACRC) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PBSess - Win32 Debug"


"$(INTDIR)\RACRC.OBJ" : $(SOURCE) $(DEP_CPP_RACRC) "$(INTDIR)"

"$(INTDIR)\RACRC.SBR" : $(SOURCE) $(DEP_CPP_RACRC) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\QUESTION.CPP
DEP_CPP_QUEST=\
	".\PROBOARD.HPP"\
	{$(INCLUDE)}"\TSLIB.HPP"\
	"\DEV\PBLIB\pblib.hpp"\
	".\MSGBASE.HPP"\
	".\PROMPTS.HPP"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	

!IF  "$(CFG)" == "PBSess - Win32 Release"


"$(INTDIR)\QUESTION.OBJ" : $(SOURCE) $(DEP_CPP_QUEST) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PBSess - Win32 Debug"


"$(INTDIR)\QUESTION.OBJ" : $(SOURCE) $(DEP_CPP_QUEST) "$(INTDIR)"

"$(INTDIR)\QUESTION.SBR" : $(SOURCE) $(DEP_CPP_QUEST) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\POSTMSG.CPP
DEP_CPP_POSTM=\
	".\PROBOARD.HPP"\
	{$(INCLUDE)}"\TSLIB.HPP"\
	"\DEV\PBLIB\pblib.hpp"\
	".\MSGBASE.HPP"\
	".\PROMPTS.HPP"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	

!IF  "$(CFG)" == "PBSess - Win32 Release"


"$(INTDIR)\POSTMSG.OBJ" : $(SOURCE) $(DEP_CPP_POSTM) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PBSess - Win32 Debug"


"$(INTDIR)\POSTMSG.OBJ" : $(SOURCE) $(DEP_CPP_POSTM) "$(INTDIR)"

"$(INTDIR)\POSTMSG.SBR" : $(SOURCE) $(DEP_CPP_POSTM) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\NODELIST.CPP
DEP_CPP_NODEL=\
	".\PROBOARD.HPP"\
	{$(INCLUDE)}"\TSLIB.HPP"\
	"\DEV\PBLIB\pblib.hpp"\
	".\MSGBASE.HPP"\
	".\PROMPTS.HPP"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	

!IF  "$(CFG)" == "PBSess - Win32 Release"


"$(INTDIR)\NODELIST.OBJ" : $(SOURCE) $(DEP_CPP_NODEL) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PBSess - Win32 Debug"


"$(INTDIR)\NODELIST.OBJ" : $(SOURCE) $(DEP_CPP_NODEL) "$(INTDIR)"

"$(INTDIR)\NODELIST.SBR" : $(SOURCE) $(DEP_CPP_NODEL) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MSGFIND.CPP
DEP_CPP_MSGFI=\
	".\PROBOARD.HPP"\
	{$(INCLUDE)}"\TSLIB.HPP"\
	"\DEV\PBLIB\pblib.hpp"\
	".\MSGBASE.HPP"\
	".\PROMPTS.HPP"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	

!IF  "$(CFG)" == "PBSess - Win32 Release"


"$(INTDIR)\MSGFIND.OBJ" : $(SOURCE) $(DEP_CPP_MSGFI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PBSess - Win32 Debug"


"$(INTDIR)\MSGFIND.OBJ" : $(SOURCE) $(DEP_CPP_MSGFI) "$(INTDIR)"

"$(INTDIR)\MSGFIND.SBR" : $(SOURCE) $(DEP_CPP_MSGFI) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MSGEXPRT.CPP
DEP_CPP_MSGEX=\
	".\PROBOARD.HPP"\
	{$(INCLUDE)}"\TSLIB.HPP"\
	"\DEV\PBLIB\pblib.hpp"\
	".\MSGBASE.HPP"\
	".\PROMPTS.HPP"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	

!IF  "$(CFG)" == "PBSess - Win32 Release"


"$(INTDIR)\MSGEXPRT.OBJ" : $(SOURCE) $(DEP_CPP_MSGEX) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PBSess - Win32 Debug"


"$(INTDIR)\MSGEXPRT.OBJ" : $(SOURCE) $(DEP_CPP_MSGEX) "$(INTDIR)"

"$(INTDIR)\MSGEXPRT.SBR" : $(SOURCE) $(DEP_CPP_MSGEX) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MSGED.CPP
DEP_CPP_MSGED=\
	".\PROBOARD.HPP"\
	{$(INCLUDE)}"\TSLIB.HPP"\
	"\DEV\PBLIB\pblib.hpp"\
	".\MSGBASE.HPP"\
	".\PROMPTS.HPP"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	

!IF  "$(CFG)" == "PBSess - Win32 Release"


"$(INTDIR)\MSGED.OBJ" : $(SOURCE) $(DEP_CPP_MSGED) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PBSess - Win32 Debug"


"$(INTDIR)\MSGED.OBJ" : $(SOURCE) $(DEP_CPP_MSGED) "$(INTDIR)"

"$(INTDIR)\MSGED.SBR" : $(SOURCE) $(DEP_CPP_MSGED) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MSGBASE.CPP
DEP_CPP_MSGBA=\
	".\PROBOARD.HPP"\
	{$(INCLUDE)}"\TSLIB.HPP"\
	"\DEV\PBLIB\pblib.hpp"\
	".\MSGBASE.HPP"\
	".\PROMPTS.HPP"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	

!IF  "$(CFG)" == "PBSess - Win32 Release"


"$(INTDIR)\MSGBASE.OBJ" : $(SOURCE) $(DEP_CPP_MSGBA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PBSess - Win32 Debug"


"$(INTDIR)\MSGBASE.OBJ" : $(SOURCE) $(DEP_CPP_MSGBA) "$(INTDIR)"

"$(INTDIR)\MSGBASE.SBR" : $(SOURCE) $(DEP_CPP_MSGBA) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MSGAREA.CPP
DEP_CPP_MSGAR=\
	".\PROBOARD.HPP"\
	{$(INCLUDE)}"\TSLIB.HPP"\
	"\DEV\PBLIB\pblib.hpp"\
	".\MSGBASE.HPP"\
	".\PROMPTS.HPP"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	

!IF  "$(CFG)" == "PBSess - Win32 Release"


"$(INTDIR)\MSGAREA.OBJ" : $(SOURCE) $(DEP_CPP_MSGAR) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PBSess - Win32 Debug"


"$(INTDIR)\MSGAREA.OBJ" : $(SOURCE) $(DEP_CPP_MSGAR) "$(INTDIR)"

"$(INTDIR)\MSGAREA.SBR" : $(SOURCE) $(DEP_CPP_MSGAR) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MSG.CPP
DEP_CPP_MSG_C=\
	".\PROBOARD.HPP"\
	{$(INCLUDE)}"\TSLIB.HPP"\
	"\DEV\PBLIB\pblib.hpp"\
	".\MSGBASE.HPP"\
	".\PROMPTS.HPP"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	

!IF  "$(CFG)" == "PBSess - Win32 Release"


"$(INTDIR)\MSG.OBJ" : $(SOURCE) $(DEP_CPP_MSG_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PBSess - Win32 Debug"


"$(INTDIR)\MSG.OBJ" : $(SOURCE) $(DEP_CPP_MSG_C) "$(INTDIR)"

"$(INTDIR)\MSG.SBR" : $(SOURCE) $(DEP_CPP_MSG_C) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MENUPROC.CPP
DEP_CPP_MENUP=\
	".\PROBOARD.HPP"\
	{$(INCLUDE)}"\TSLIB.HPP"\
	"\DEV\PBLIB\pblib.hpp"\
	".\MSGBASE.HPP"\
	".\PROMPTS.HPP"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	

!IF  "$(CFG)" == "PBSess - Win32 Release"


"$(INTDIR)\MENUPROC.OBJ" : $(SOURCE) $(DEP_CPP_MENUP) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PBSess - Win32 Debug"


"$(INTDIR)\MENUPROC.OBJ" : $(SOURCE) $(DEP_CPP_MENUP) "$(INTDIR)"

"$(INTDIR)\MENUPROC.SBR" : $(SOURCE) $(DEP_CPP_MENUP) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MARK.CPP
DEP_CPP_MARK_=\
	".\PROBOARD.HPP"\
	{$(INCLUDE)}"\TSLIB.HPP"\
	"\DEV\PBLIB\pblib.hpp"\
	".\MSGBASE.HPP"\
	".\PROMPTS.HPP"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	

!IF  "$(CFG)" == "PBSess - Win32 Release"


"$(INTDIR)\MARK.OBJ" : $(SOURCE) $(DEP_CPP_MARK_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PBSess - Win32 Debug"


"$(INTDIR)\MARK.OBJ" : $(SOURCE) $(DEP_CPP_MARK_) "$(INTDIR)"

"$(INTDIR)\MARK.SBR" : $(SOURCE) $(DEP_CPP_MARK_) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\LOGIN.CPP
DEP_CPP_LOGIN=\
	".\PROBOARD.HPP"\
	{$(INCLUDE)}"\TSLIB.HPP"\
	"\DEV\PBLIB\pblib.hpp"\
	".\MSGBASE.HPP"\
	".\PROMPTS.HPP"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	

!IF  "$(CFG)" == "PBSess - Win32 Release"


"$(INTDIR)\LOGIN.OBJ" : $(SOURCE) $(DEP_CPP_LOGIN) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PBSess - Win32 Debug"


"$(INTDIR)\LOGIN.OBJ" : $(SOURCE) $(DEP_CPP_LOGIN) "$(INTDIR)"

"$(INTDIR)\LOGIN.SBR" : $(SOURCE) $(DEP_CPP_LOGIN) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\LANGUAGE.CPP
DEP_CPP_LANGU=\
	".\PROBOARD.HPP"\
	{$(INCLUDE)}"\TSLIB.HPP"\
	"\DEV\PBLIB\pblib.hpp"\
	".\MSGBASE.HPP"\
	".\PROMPTS.HPP"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	

!IF  "$(CFG)" == "PBSess - Win32 Release"


"$(INTDIR)\LANGUAGE.OBJ" : $(SOURCE) $(DEP_CPP_LANGU) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PBSess - Win32 Debug"


"$(INTDIR)\LANGUAGE.OBJ" : $(SOURCE) $(DEP_CPP_LANGU) "$(INTDIR)"

"$(INTDIR)\LANGUAGE.SBR" : $(SOURCE) $(DEP_CPP_LANGU) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\JAM.CPP
DEP_CPP_JAM_C=\
	".\PROBOARD.HPP"\
	".\JAM.HPP"\
	{$(INCLUDE)}"\TSLIB.HPP"\
	"\DEV\PBLIB\pblib.hpp"\
	".\MSGBASE.HPP"\
	".\PROMPTS.HPP"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	

!IF  "$(CFG)" == "PBSess - Win32 Release"


"$(INTDIR)\JAM.OBJ" : $(SOURCE) $(DEP_CPP_JAM_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PBSess - Win32 Debug"


"$(INTDIR)\JAM.OBJ" : $(SOURCE) $(DEP_CPP_JAM_C) "$(INTDIR)"

"$(INTDIR)\JAM.SBR" : $(SOURCE) $(DEP_CPP_JAM_C) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\IO.CPP
DEP_CPP_IO_CP=\
	".\PROBOARD.HPP"\
	{$(INCLUDE)}"\TSLIB.HPP"\
	"\DEV\PBLIB\pblib.hpp"\
	".\MSGBASE.HPP"\
	".\PROMPTS.HPP"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	

!IF  "$(CFG)" == "PBSess - Win32 Release"


"$(INTDIR)\IO.OBJ" : $(SOURCE) $(DEP_CPP_IO_CP) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PBSess - Win32 Debug"


"$(INTDIR)\IO.OBJ" : $(SOURCE) $(DEP_CPP_IO_CP) "$(INTDIR)"

"$(INTDIR)\IO.SBR" : $(SOURCE) $(DEP_CPP_IO_CP) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\INTRO.CPP
DEP_CPP_INTRO=\
	".\PROBOARD.HPP"\
	{$(INCLUDE)}"\TSLIB.HPP"\
	"\DEV\PBLIB\pblib.hpp"\
	".\MSGBASE.HPP"\
	".\PROMPTS.HPP"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	

!IF  "$(CFG)" == "PBSess - Win32 Release"


"$(INTDIR)\INTRO.OBJ" : $(SOURCE) $(DEP_CPP_INTRO) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PBSess - Win32 Debug"


"$(INTDIR)\INTRO.OBJ" : $(SOURCE) $(DEP_CPP_INTRO) "$(INTDIR)"

"$(INTDIR)\INTRO.SBR" : $(SOURCE) $(DEP_CPP_INTRO) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\INPDATE.CPP
DEP_CPP_INPDA=\
	".\PROBOARD.HPP"\
	{$(INCLUDE)}"\TSLIB.HPP"\
	"\DEV\PBLIB\pblib.hpp"\
	".\MSGBASE.HPP"\
	".\PROMPTS.HPP"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	

!IF  "$(CFG)" == "PBSess - Win32 Release"


"$(INTDIR)\INPDATE.OBJ" : $(SOURCE) $(DEP_CPP_INPDA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PBSess - Win32 Debug"


"$(INTDIR)\INPDATE.OBJ" : $(SOURCE) $(DEP_CPP_INPDA) "$(INTDIR)"

"$(INTDIR)\INPDATE.SBR" : $(SOURCE) $(DEP_CPP_INPDA) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\HUDSON.CPP
DEP_CPP_HUDSO=\
	".\PROBOARD.HPP"\
	{$(INCLUDE)}"\TSLIB.HPP"\
	"\DEV\PBLIB\pblib.hpp"\
	".\MSGBASE.HPP"\
	".\PROMPTS.HPP"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	

!IF  "$(CFG)" == "PBSess - Win32 Release"


"$(INTDIR)\HUDSON.OBJ" : $(SOURCE) $(DEP_CPP_HUDSO) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PBSess - Win32 Debug"


"$(INTDIR)\HUDSON.OBJ" : $(SOURCE) $(DEP_CPP_HUDSO) "$(INTDIR)"

"$(INTDIR)\HUDSON.SBR" : $(SOURCE) $(DEP_CPP_HUDSO) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DATEFMT.CPP
DEP_CPP_DATEF=\
	".\PROBOARD.HPP"\
	{$(INCLUDE)}"\TSLIB.HPP"\
	"\DEV\PBLIB\pblib.hpp"\
	".\MSGBASE.HPP"\
	".\PROMPTS.HPP"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	

!IF  "$(CFG)" == "PBSess - Win32 Release"


"$(INTDIR)\DATEFMT.OBJ" : $(SOURCE) $(DEP_CPP_DATEF) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PBSess - Win32 Debug"


"$(INTDIR)\DATEFMT.OBJ" : $(SOURCE) $(DEP_CPP_DATEF) "$(INTDIR)"

"$(INTDIR)\DATEFMT.SBR" : $(SOURCE) $(DEP_CPP_DATEF) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\delay.cpp

!IF  "$(CFG)" == "PBSess - Win32 Release"


"$(INTDIR)\delay.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PBSess - Win32 Debug"


"$(INTDIR)\delay.obj" : $(SOURCE) "$(INTDIR)"

"$(INTDIR)\delay.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GLOBAL.CPP
DEP_CPP_GLOBA=\
	".\PROBOARD.HPP"\
	{$(INCLUDE)}"\TSLIB.HPP"\
	"\DEV\PBLIB\pblib.hpp"\
	".\MSGBASE.HPP"\
	".\PROMPTS.HPP"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	

!IF  "$(CFG)" == "PBSess - Win32 Release"


"$(INTDIR)\GLOBAL.OBJ" : $(SOURCE) $(DEP_CPP_GLOBA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PBSess - Win32 Debug"


"$(INTDIR)\GLOBAL.OBJ" : $(SOURCE) $(DEP_CPP_GLOBA) "$(INTDIR)"

"$(INTDIR)\GLOBAL.SBR" : $(SOURCE) $(DEP_CPP_GLOBA) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MSGMOVE.CPP
DEP_CPP_MSGMO=\
	".\PROBOARD.HPP"\
	{$(INCLUDE)}"\TSLIB.HPP"\
	"\DEV\PBLIB\pblib.hpp"\
	".\MSGBASE.HPP"\
	".\PROMPTS.HPP"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	

!IF  "$(CFG)" == "PBSess - Win32 Release"


"$(INTDIR)\MSGMOVE.OBJ" : $(SOURCE) $(DEP_CPP_MSGMO) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PBSess - Win32 Debug"


"$(INTDIR)\MSGMOVE.OBJ" : $(SOURCE) $(DEP_CPP_MSGMO) "$(INTDIR)"

"$(INTDIR)\MSGMOVE.SBR" : $(SOURCE) $(DEP_CPP_MSGMO) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MSGDEL.CPP
DEP_CPP_MSGDE=\
	".\PROBOARD.HPP"\
	{$(INCLUDE)}"\TSLIB.HPP"\
	"\DEV\PBLIB\pblib.hpp"\
	".\MSGBASE.HPP"\
	".\PROMPTS.HPP"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	

!IF  "$(CFG)" == "PBSess - Win32 Release"


"$(INTDIR)\MSGDEL.OBJ" : $(SOURCE) $(DEP_CPP_MSGDE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PBSess - Win32 Debug"


"$(INTDIR)\MSGDEL.OBJ" : $(SOURCE) $(DEP_CPP_MSGDE) "$(INTDIR)"

"$(INTDIR)\MSGDEL.SBR" : $(SOURCE) $(DEP_CPP_MSGDE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MSGFWD.CPP
DEP_CPP_MSGFW=\
	".\PROBOARD.HPP"\
	{$(INCLUDE)}"\TSLIB.HPP"\
	"\DEV\PBLIB\pblib.hpp"\
	".\MSGBASE.HPP"\
	".\PROMPTS.HPP"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	

!IF  "$(CFG)" == "PBSess - Win32 Release"


"$(INTDIR)\MSGFWD.OBJ" : $(SOURCE) $(DEP_CPP_MSGFW) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PBSess - Win32 Debug"


"$(INTDIR)\MSGFWD.OBJ" : $(SOURCE) $(DEP_CPP_MSGFW) "$(INTDIR)"

"$(INTDIR)\MSGFWD.SBR" : $(SOURCE) $(DEP_CPP_MSGFW) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\AKA.CPP
DEP_CPP_AKA_C=\
	".\PROBOARD.HPP"\
	{$(INCLUDE)}"\TSLIB.HPP"\
	"\DEV\PBLIB\pblib.hpp"\
	".\MSGBASE.HPP"\
	".\PROMPTS.HPP"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	

!IF  "$(CFG)" == "PBSess - Win32 Release"


"$(INTDIR)\AKA.OBJ" : $(SOURCE) $(DEP_CPP_AKA_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PBSess - Win32 Debug"


"$(INTDIR)\AKA.OBJ" : $(SOURCE) $(DEP_CPP_AKA_C) "$(INTDIR)"

"$(INTDIR)\AKA.SBR" : $(SOURCE) $(DEP_CPP_AKA_C) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SETAREA.CPP
DEP_CPP_SETAR=\
	".\PROBOARD.HPP"\
	{$(INCLUDE)}"\TSLIB.HPP"\
	"\DEV\PBLIB\pblib.hpp"\
	".\MSGBASE.HPP"\
	".\PROMPTS.HPP"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	

!IF  "$(CFG)" == "PBSess - Win32 Release"


"$(INTDIR)\SETAREA.OBJ" : $(SOURCE) $(DEP_CPP_SETAR) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PBSess - Win32 Debug"


"$(INTDIR)\SETAREA.OBJ" : $(SOURCE) $(DEP_CPP_SETAR) "$(INTDIR)"

"$(INTDIR)\SETAREA.SBR" : $(SOURCE) $(DEP_CPP_SETAR) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FILEAREA.CPP
DEP_CPP_FILEA=\
	".\PROBOARD.HPP"\
	{$(INCLUDE)}"\TSLIB.HPP"\
	"\DEV\PBLIB\pblib.hpp"\
	".\MSGBASE.HPP"\
	".\PROMPTS.HPP"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	

!IF  "$(CFG)" == "PBSess - Win32 Release"


"$(INTDIR)\FILEAREA.OBJ" : $(SOURCE) $(DEP_CPP_FILEA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PBSess - Win32 Debug"


"$(INTDIR)\FILEAREA.OBJ" : $(SOURCE) $(DEP_CPP_FILEA) "$(INTDIR)"

"$(INTDIR)\FILEAREA.SBR" : $(SOURCE) $(DEP_CPP_FILEA) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PROBOARD.CPP
DEP_CPP_PROBO=\
	".\PROBOARD.HPP"\
	{$(INCLUDE)}"\TSLIB.HPP"\
	"\DEV\PBLIB\pblib.hpp"\
	".\MSGBASE.HPP"\
	".\PROMPTS.HPP"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	

!IF  "$(CFG)" == "PBSess - Win32 Release"


"$(INTDIR)\PROBOARD.OBJ" : $(SOURCE) $(DEP_CPP_PROBO) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PBSess - Win32 Debug"


"$(INTDIR)\PROBOARD.OBJ" : $(SOURCE) $(DEP_CPP_PROBO) "$(INTDIR)"

"$(INTDIR)\PROBOARD.SBR" : $(SOURCE) $(DEP_CPP_PROBO) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\LISTFILE.CPP
DEP_CPP_LISTF=\
	".\PROBOARD.HPP"\
	{$(INCLUDE)}"\TSLIB.HPP"\
	"\DEV\PBLIB\pblib.hpp"\
	".\MSGBASE.HPP"\
	".\PROMPTS.HPP"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	

!IF  "$(CFG)" == "PBSess - Win32 Release"


"$(INTDIR)\LISTFILE.OBJ" : $(SOURCE) $(DEP_CPP_LISTF) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PBSess - Win32 Debug"


"$(INTDIR)\LISTFILE.OBJ" : $(SOURCE) $(DEP_CPP_LISTF) "$(INTDIR)"

"$(INTDIR)\LISTFILE.SBR" : $(SOURCE) $(DEP_CPP_LISTF) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TAG.CPP
DEP_CPP_TAG_C=\
	".\PROBOARD.HPP"\
	{$(INCLUDE)}"\TSLIB.HPP"\
	"\DEV\PBLIB\pblib.hpp"\
	".\MSGBASE.HPP"\
	".\PROMPTS.HPP"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	

!IF  "$(CFG)" == "PBSess - Win32 Release"


"$(INTDIR)\TAG.OBJ" : $(SOURCE) $(DEP_CPP_TAG_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PBSess - Win32 Debug"


"$(INTDIR)\TAG.OBJ" : $(SOURCE) $(DEP_CPP_TAG_C) "$(INTDIR)"

"$(INTDIR)\TAG.SBR" : $(SOURCE) $(DEP_CPP_TAG_C) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\BULLETIN.CPP
DEP_CPP_BULLE=\
	".\PROBOARD.HPP"\
	{$(INCLUDE)}"\TSLIB.HPP"\
	"\DEV\PBLIB\pblib.hpp"\
	".\MSGBASE.HPP"\
	".\PROMPTS.HPP"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	

!IF  "$(CFG)" == "PBSess - Win32 Release"


"$(INTDIR)\BULLETIN.OBJ" : $(SOURCE) $(DEP_CPP_BULLE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PBSess - Win32 Debug"


"$(INTDIR)\BULLETIN.OBJ" : $(SOURCE) $(DEP_CPP_BULLE) "$(INTDIR)"

"$(INTDIR)\BULLETIN.SBR" : $(SOURCE) $(DEP_CPP_BULLE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\COMBINED.CPP
DEP_CPP_COMBI=\
	".\PROBOARD.HPP"\
	{$(INCLUDE)}"\TSLIB.HPP"\
	"\DEV\PBLIB\pblib.hpp"\
	".\MSGBASE.HPP"\
	".\PROMPTS.HPP"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	

!IF  "$(CFG)" == "PBSess - Win32 Release"


"$(INTDIR)\COMBINED.OBJ" : $(SOURCE) $(DEP_CPP_COMBI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PBSess - Win32 Debug"


"$(INTDIR)\COMBINED.OBJ" : $(SOURCE) $(DEP_CPP_COMBI) "$(INTDIR)"

"$(INTDIR)\COMBINED.SBR" : $(SOURCE) $(DEP_CPP_COMBI) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DL.CPP
DEP_CPP_DL_CP=\
	".\PROBOARD.HPP"\
	{$(INCLUDE)}"\TSLIB.HPP"\
	"\DEV\PBLIB\pblib.hpp"\
	".\MSGBASE.HPP"\
	".\PROMPTS.HPP"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	

!IF  "$(CFG)" == "PBSess - Win32 Release"


"$(INTDIR)\DL.OBJ" : $(SOURCE) $(DEP_CPP_DL_CP) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PBSess - Win32 Debug"


"$(INTDIR)\DL.OBJ" : $(SOURCE) $(DEP_CPP_DL_CP) "$(INTDIR)"

"$(INTDIR)\DL.SBR" : $(SOURCE) $(DEP_CPP_DL_CP) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TIMER.CPP
DEP_CPP_TIMER=\
	".\PROBOARD.HPP"\
	{$(INCLUDE)}"\TSLIB.HPP"\
	"\DEV\PBLIB\pblib.hpp"\
	".\MSGBASE.HPP"\
	".\PROMPTS.HPP"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	

!IF  "$(CFG)" == "PBSess - Win32 Release"


"$(INTDIR)\TIMER.OBJ" : $(SOURCE) $(DEP_CPP_TIMER) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PBSess - Win32 Debug"


"$(INTDIR)\TIMER.OBJ" : $(SOURCE) $(DEP_CPP_TIMER) "$(INTDIR)"

"$(INTDIR)\TIMER.SBR" : $(SOURCE) $(DEP_CPP_TIMER) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\UL.CPP
DEP_CPP_UL_CP=\
	".\PROBOARD.HPP"\
	{$(INCLUDE)}"\TSLIB.HPP"\
	"\DEV\PBLIB\pblib.hpp"\
	".\MSGBASE.HPP"\
	".\PROMPTS.HPP"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	

!IF  "$(CFG)" == "PBSess - Win32 Release"


"$(INTDIR)\UL.OBJ" : $(SOURCE) $(DEP_CPP_UL_CP) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PBSess - Win32 Debug"


"$(INTDIR)\UL.OBJ" : $(SOURCE) $(DEP_CPP_UL_CP) "$(INTDIR)"

"$(INTDIR)\UL.SBR" : $(SOURCE) $(DEP_CPP_UL_CP) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PROTOCOL.CPP
DEP_CPP_PROTO=\
	".\PROBOARD.HPP"\
	{$(INCLUDE)}"\TSLIB.HPP"\
	"\DEV\PBLIB\pblib.hpp"\
	".\MSGBASE.HPP"\
	".\PROMPTS.HPP"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	

!IF  "$(CFG)" == "PBSess - Win32 Release"


"$(INTDIR)\PROTOCOL.OBJ" : $(SOURCE) $(DEP_CPP_PROTO) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PBSess - Win32 Debug"


"$(INTDIR)\PROTOCOL.OBJ" : $(SOURCE) $(DEP_CPP_PROTO) "$(INTDIR)"

"$(INTDIR)\PROTOCOL.SBR" : $(SOURCE) $(DEP_CPP_PROTO) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\LIMIT.CPP
DEP_CPP_LIMIT=\
	".\PROBOARD.HPP"\
	{$(INCLUDE)}"\TSLIB.HPP"\
	"\DEV\PBLIB\pblib.hpp"\
	".\MSGBASE.HPP"\
	".\PROMPTS.HPP"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	

!IF  "$(CFG)" == "PBSess - Win32 Release"


"$(INTDIR)\LIMIT.OBJ" : $(SOURCE) $(DEP_CPP_LIMIT) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PBSess - Win32 Debug"


"$(INTDIR)\LIMIT.OBJ" : $(SOURCE) $(DEP_CPP_LIMIT) "$(INTDIR)"

"$(INTDIR)\LIMIT.SBR" : $(SOURCE) $(DEP_CPP_LIMIT) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CDROM.CPP
DEP_CPP_CDROM=\
	".\PROBOARD.HPP"\
	{$(INCLUDE)}"\TSLIB.HPP"\
	"\DEV\PBLIB\pblib.hpp"\
	".\MSGBASE.HPP"\
	".\PROMPTS.HPP"\
	{$(INCLUDE)}"\CACHE.HPP"\
	{$(INCLUDE)}"\RECFILE.HPP"\
	{$(INCLUDE)}"\LLIST.HPP"\
	

!IF  "$(CFG)" == "PBSess - Win32 Release"


"$(INTDIR)\CDROM.OBJ" : $(SOURCE) $(DEP_CPP_CDROM) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "PBSess - Win32 Debug"


"$(INTDIR)\CDROM.OBJ" : $(SOURCE) $(DEP_CPP_CDROM) "$(INTDIR)"

"$(INTDIR)\CDROM.SBR" : $(SOURCE) $(DEP_CPP_CDROM) "$(INTDIR)"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
