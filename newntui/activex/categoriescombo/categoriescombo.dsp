# Microsoft Developer Studio Project File - Name="CategoriesCombo" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=CategoriesCombo - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "CategoriesCombo.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CategoriesCombo.mak" CFG="CategoriesCombo - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CategoriesCombo - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "CategoriesCombo - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "CategoriesCombo"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CategoriesCombo - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Ext "ocx"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Target_Ext "ocx"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\..\CommonResources\Include" /I "..\CBrowserFrame" /I ".\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /FD /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /stack:0x1000000 /subsystem:windows /dll /machine:I386
# Begin Custom Build - Registering OLE control...
OutDir=.\Release
TargetPath=.\Release\CategoriesCombo.ocx
InputPath=.\Release\CategoriesCombo.ocx
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "CategoriesCombo - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Ext "ocx"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Target_Ext "ocx"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I ".\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /FD /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 /nologo /stack:0x1000000 /subsystem:windows /dll /incremental:no /debug /machine:I386
# Begin Custom Build - Registering OLE control...
OutDir=.\Debug
TargetPath=.\Debug\CategoriesCombo.ocx
InputPath=.\Debug\CategoriesCombo.ocx
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "CategoriesCombo - Win32 Release"
# Name "CategoriesCombo - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\src\CategoriesCombo.cpp
# End Source File
# Begin Source File

SOURCE=.\CategoriesCombo.def
# End Source File
# Begin Source File

SOURCE=.\CategoriesCombo.odl
# End Source File
# Begin Source File

SOURCE=.\CategoriesCombo.rc
# End Source File
# Begin Source File

SOURCE=.\src\CategoriesComboCtl.cpp
# End Source File
# Begin Source File

SOURCE=.\src\CategoriesComboPpg.cpp
# End Source File
# Begin Source File

SOURCE=.\src\NewSelectionList.cpp
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\src\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\include\CategoriesCombo.h
# End Source File
# Begin Source File

SOURCE=.\include\CategoriesComboCtl.h
# End Source File
# Begin Source File

SOURCE=.\include\CategoriesComboPpg.h
# End Source File
# Begin Source File

SOURCE=.\include\NewSelectionList.h
# End Source File
# Begin Source File

SOURCE=.\include\resource.h
# End Source File
# Begin Source File

SOURCE=.\include\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\assoc.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CategoriesCombo.ico
# End Source File
# Begin Source File

SOURCE=.\res\CategoriesComboCtl.bmp
# End Source File
# Begin Source File

SOURCE=.\res\classes.bmp
# End Source File
# Begin Source File

SOURCE=.\res\classvar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cursor.bmp
# End Source File
# Begin Source File

SOURCE=.\res\defects.bmp
# End Source File
# Begin Source File

SOURCE=.\res\enum.bmp
# End Source File
# Begin Source File

SOURCE=.\res\error.bmp
# End Source File
# Begin Source File

SOURCE=.\res\files.bmp
# End Source File
# Begin Source File

SOURCE=.\res\function.bmp
# End Source File
# Begin Source File

SOURCE=.\res\groups.bmp
# End Source File
# Begin Source File

SOURCE=.\res\interfac.bmp
# End Source File
# Begin Source File

SOURCE=.\res\linktype.bmp
# End Source File
# Begin Source File

SOURCE=.\res\locvar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\macro.bmp
# End Source File
# Begin Source File

SOURCE=.\res\macros.bmp
# End Source File
# Begin Source File

SOURCE=.\res\methods.bmp
# End Source File
# Begin Source File

SOURCE=.\res\packages.bmp
# End Source File
# Begin Source File

SOURCE=.\res\relations.bmp
# End Source File
# Begin Source File

SOURCE=.\res\strings.bmp
# End Source File
# Begin Source File

SOURCE=.\res\struct.bmp
# End Source File
# Begin Source File

SOURCE=.\res\table.bmp
# End Source File
# Begin Source File

SOURCE=.\res\template.bmp
# End Source File
# Begin Source File

SOURCE=.\res\test.bmp
# End Source File
# Begin Source File

SOURCE=.\res\typedef.bmp
# End Source File
# Begin Source File

SOURCE=.\res\union.bmp
# End Source File
# Begin Source File

SOURCE=.\res\var.bmp
# End Source File
# Begin Source File

SOURCE=.\res\variables.bmp
# End Source File
# Begin Source File

SOURCE=.\res\xref.bmp
# End Source File
# End Group
# End Target
# End Project
# Section CategoriesCombo : {50F35761-169F-11D2-AEED-00A0C9B71DC4}
# 	0:20:NewSelectionList.cpp:C:\NT-Discover\src\ocx\CategoriesCombo\NewSelectionList.cpp
# 	0:18:NewSelectionList.h:C:\NT-Discover\src\ocx\CategoriesCombo\NewSelectionList.h
# 	1:25:IDD_ABOUTBOX_QUERIESCOMBO:102
# 	2:16:Resource Include:resource.h
# 	2:25:IDD_ABOUTBOX_QUERIESCOMBO:IDD_ABOUTBOX_QUERIESCOMBO
# 	2:24:CLASS: CNewSelectionList:CNewSelectionList
# 	2:20:NewSelectionList.cpp:NewSelectionList.cpp
# 	2:18:NewSelectionList.h:NewSelectionList.h
# 	2:19:Application Include:CategoriesCombo.h
# End Section
