# Microsoft Developer Studio Project File - Name="MultiLan" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=MultiLan - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MultiLan.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MultiLan.mak" CFG="MultiLan - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MultiLan - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MultiLan - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MultiLan - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "MULTILAN_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "MULTILAN_EXPORTS" /D "_WINDLL" /D "_AFXDLL" /FR /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG" /d "AFX_TARG_ENU" /d "AFX_RESOURCE_DLL" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 /nologo /dll /machine:I386 /out:"HAAS/APP/SpectraNexus_En.dll" /NOENTRY
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "MultiLan - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "MULTILAN_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "MULTILAN_EXPORTS" /D "_WINDLL" /D "_AFXDLL" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /dll /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "MultiLan - Win32 Release"
# Name "MultiLan - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\MultiLang.rc
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\2.ico
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap_d.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap_o.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap_s.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cie.ico
# End Source File
# Begin Source File

SOURCE=.\res\cie1931.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cie1976.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cie_uv1.ico
# End Source File
# Begin Source File

SOURCE=.\res\curr_vs_.ico
# End Source File
# Begin Source File

SOURCE=.\res\data.ico
# End Source File
# Begin Source File

SOURCE=.\res\demo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\edit.ico
# End Source File
# Begin Source File

SOURCE=.\res\EMC.ico
# End Source File
# Begin Source File

SOURCE=.\res\EMCDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\everfine.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Flgusa02.ico
# End Source File
# Begin Source File

SOURCE=.\res\flux_cal.ico
# End Source File
# Begin Source File

SOURCE=.\res\GO1000.ico
# End Source File
# Begin Source File

SOURCE=.\res\GO1000Doc.ico
# End Source File
# Begin Source File

SOURCE=.\res\hand.cur
# End Source File
# Begin Source File

SOURCE=.\res\HbMfc.ico
# End Source File
# Begin Source File

SOURCE=.\res\HbMfcDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00002.ico
# End Source File
# Begin Source File

SOURCE=.\res\icoEMC.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_main.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_mult.ico
# End Source File
# Begin Source File

SOURCE=.\res\label.bmp
# End Source File
# Begin Source File

SOURCE=.\res\mainfram.bmp
# End Source File
# Begin Source File

SOURCE=.\res\man.ico
# End Source File
# Begin Source File

SOURCE=.\res\matrixsetblue.bmp
# End Source File
# Begin Source File

SOURCE=.\res\matrixsetsmallblue.bmp
# End Source File
# Begin Source File

SOURCE=.\res\matrixsettinyblue.bmp
# End Source File
# Begin Source File

SOURCE=.\res\MultiLang.ico
# End Source File
# Begin Source File

SOURCE=.\res\MultiLangDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\MySpec.ico
# End Source File
# Begin Source File

SOURCE=.\res\MySpecDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\p.bmp
# End Source File
# Begin Source File

SOURCE=.\res\para.ico
# End Source File
# Begin Source File

SOURCE=.\res\sdcm.ico
# End Source File
# Begin Source File

SOURCE=.\res\Secur02a.ico
# End Source File
# Begin Source File

SOURCE=.\res\sele.ico
# End Source File
# Begin Source File

SOURCE=.\res\show.bmp
# End Source File
# Begin Source File

SOURCE=.\res\smallico.bmp
# End Source File
# Begin Source File

SOURCE=.\res\spec.ico
# End Source File
# Begin Source File

SOURCE=.\res\spect.ico
# End Source File
# Begin Source File

SOURCE=.\res\spect_ca.ico
# End Source File
# Begin Source File

SOURCE=.\res\splash.bmp
# End Source File
# Begin Source File

SOURCE=.\Splsh16.bmp
# End Source File
# Begin Source File

SOURCE=.\res\test.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# End Target
# End Project
