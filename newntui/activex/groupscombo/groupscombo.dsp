# Microsoft Developer Studio Project File - Name="GroupsCombo" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=GroupsCombo - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "GroupsCombo.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "GroupsCombo.mak" CFG="GroupsCombo - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "GroupsCombo - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "GroupsCombo - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "GroupsCombo"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "GroupsCombo - Win32 Release"

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
# ADD CPP /nologo /MT /W3 /GX /O2 /I ".\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /FD /c
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
TargetPath=.\Release\GroupsCombo.ocx
InputPath=.\Release\GroupsCombo.ocx
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "GroupsCombo - Win32 Debug"

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
TargetPath=.\Debug\GroupsCombo.ocx
InputPath=.\Debug\GroupsCombo.ocx
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "GroupsCombo - Win32 Release"
# Name "GroupsCombo - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\src\GroupsCombo.cpp
# End Source File
# Begin Source File

SOURCE=.\GroupsCombo.def
# End Source File
# Begin Source File

SOURCE=.\GroupsCombo.odl
# End Source File
# Begin Source File

SOURCE=.\GroupsCombo.rc
# End Source File
# Begin Source File

SOURCE=.\src\GroupsComboCtl.cpp
# End Source File
# Begin Source File

SOURCE=.\src\GroupsComboPpg.cpp
# End Source File
# Begin Source File

SOURCE=.\src\GroupsSearch.cpp
# End Source File
# Begin Source File

SOURCE=.\src\NewGroupDlg.cpp
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

SOURCE=.\include\GroupsCombo.h
# End Source File
# Begin Source File

SOURCE=.\include\GroupsComboCtl.h
# End Source File
# Begin Source File

SOURCE=.\include\GroupsComboPpg.h
# End Source File
# Begin Source File

SOURCE=.\include\GroupsSearch.h
# End Source File
# Begin Source File

SOURCE=.\include\NewGroupDlg.h
# End Source File
# Begin Source File

SOURCE=.\include\NewSelectionList.h
# End Source File
# Begin Source File

SOURCE=.\include\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\addgrup.bmp
# End Source File
# Begin Source File

SOURCE=.\res\all1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\allelem.bmp
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

SOURCE=.\res\bmp00004.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00006.bmp
# End Source File
# Begin Source File

SOURCE=.\res\commel.bmp
# End Source File
# Begin Source File

SOURCE=.\res\concat.bmp
# End Source File
# Begin Source File

SOURCE=.\res\difftel.bmp
# End Source File
# Begin Source File

SOURCE=.\res\findfirs.bmp
# End Source File
# Begin Source File

SOURCE=.\res\findnext.bmp
# End Source File
# Begin Source File

SOURCE=.\res\groups.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GroupsCombo.ico
# End Source File
# Begin Source File

SOURCE=.\res\GroupsComboCtl.bmp
# End Source File
# Begin Source File

SOURCE=.\res\remgrup.bmp
# End Source File
# Begin Source File

SOURCE=.\res\remsel.bmp
# End Source File
# End Group
# End Target
# End Project
# Section GroupsCombo : {1487DD50-1CB6-11D2-AEF0-00A0C9B71DC4}
# 	0:20:NewSelectionList.cpp:C:\NewDiscover\ActiveX\GroupsCombo\NewSelectionList.cpp
# 	0:18:NewSelectionList.h:C:\NewDiscover\ActiveX\GroupsCombo\NewSelectionList.h
# 	2:24:CLASS: CNewSelectionList:CNewSelectionList
# 	2:20:NewSelectionList.cpp:NewSelectionList.cpp
# 	2:18:NewSelectionList.h:NewSelectionList.h
# 	2:19:Application Include:GroupsCombo.h
# End Section
