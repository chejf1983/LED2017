# Microsoft Developer Studio Project File - Name="HighPowerInterface" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=HighPowerInterface - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "HighPowerInterface.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "HighPowerInterface.mak" CFG="HighPowerInterface - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "HighPowerInterface - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "HighPowerInterface - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "HighPowerInterface - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "C:\Program Files\Ocean Optics\OmniDriverSPAM\include" /I "C:\JDK\include" /I "C:\JDK\include\win32" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 SpectraArsenalEmission.lib msimg32.lib common32.lib SPAM32.lib highpower.lib HolyChipOptics.lib /nologo /subsystem:windows /machine:I386 /out:"APP/HighPowerInterface.exe" /libpath:"C:\System\OOI_HOME"

!ELSEIF  "$(CFG)" == "HighPowerInterface - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /GX /I "C:\Program Files\Ocean Optics\OmniDriverSPAM\include" /I "C:\JDK\include" /I "C:\JDK\include\win32" /D "C:\Program Files\Ocean Optics\OmniDriverSPAM\include" /D "C:\JDK\include" /D "C:\JDK\include\win32" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 SpectraArsenalEmission.lib msimg32.lib common32.lib SPAM32.lib highpower.lib HolyChipOptics.lib /nologo /subsystem:windows /debug /machine:I386 /out:"APP/HighPowerInterface_d.exe" /pdbtype:sept /libpath:"System\OOI_HOME"

!ENDIF 

# Begin Target

# Name "HighPowerInterface - Win32 Release"
# Name "HighPowerInterface - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AccumulateLevel.cpp
# End Source File
# Begin Source File

SOURCE=.\AddUsersDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AuthorityView.cpp
# End Source File
# Begin Source File

SOURCE=.\BinDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\resFile\BitButtonNL\BitButtonNL.cpp
# End Source File
# Begin Source File

SOURCE=.\ChangePassword.cpp
# End Source File
# Begin Source File

SOURCE=.\Chip1Dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Chip2Dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Chip3Dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ChipsHandle.cpp
# End Source File
# Begin Source File

SOURCE=.\ChipType.cpp
# End Source File
# Begin Source File

SOURCE=.\CIEDiagram.cpp
# End Source File
# Begin Source File

SOURCE=.\resFile\ReDrawListCtrl\ComboListCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\ControlsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\resFile\coolmenu\CoolMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\CSpecGCS.cpp
# End Source File
# Begin Source File

SOURCE=.\DeleteUsersDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\EngineerLogin.cpp
# End Source File
# Begin Source File

SOURCE=.\FileHandle.cpp
# End Source File
# Begin Source File

SOURCE=.\Functions.cpp
# End Source File
# Begin Source File

SOURCE=.\HandleLevel.cpp
# End Source File
# Begin Source File

SOURCE=.\HardDisk.cpp
# End Source File
# Begin Source File

SOURCE=.\HighPowerInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\HighPowerInterface.rc
# End Source File
# Begin Source File

SOURCE=.\HighPowerInterfaceDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\INITIALDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\resFile\ReDrawListCtrl\InPlaceCombo.cpp
# End Source File
# Begin Source File

SOURCE=.\resFile\ReDrawListCtrl\InPlaceEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\LevelDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Light.cpp
# End Source File
# Begin Source File

SOURCE=.\Login.cpp
# End Source File
# Begin Source File

SOURCE=.\resFile\Progress\MacProgressCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\MD5Checksum.cpp
# End Source File
# Begin Source File

SOURCE=.\mscomm.cpp
# End Source File
# Begin Source File

SOURCE=.\resFile\PopMenu\PopupMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\ReDrawEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\RedrawTabCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\RedrawTabCtrl2.cpp
# End Source File
# Begin Source File

SOURCE=.\RegisterDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RegistHandle.cpp
# End Source File
# Begin Source File

SOURCE=.\resFile\ResizingDialog\ResizingDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\SetChipFeet.cpp
# End Source File
# Begin Source File

SOURCE=.\SetParameter.cpp
# End Source File
# Begin Source File

SOURCE=.\SetPrint.cpp
# End Source File
# Begin Source File

SOURCE=.\SetPrintForm.cpp
# End Source File
# Begin Source File

SOURCE=.\SetSpmCompen.cpp
# End Source File
# Begin Source File

SOURCE=.\SetSpmReadLmp.cpp
# End Source File
# Begin Source File

SOURCE=.\SetSpmReadParam.cpp
# End Source File
# Begin Source File

SOURCE=.\SetSpmSaveDark.cpp
# End Source File
# Begin Source File

SOURCE=.\SetSpmSaveRefer.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ShootDiagram.cpp
# End Source File
# Begin Source File

SOURCE=.\ShowLevel.cpp
# End Source File
# Begin Source File

SOURCE=.\ShowTestDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ShowTestPopup.cpp
# End Source File
# Begin Source File

SOURCE=.\resFile\ReDrawListCtrl\SkinHeaderCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\resFile\ReDrawListCtrl\SkinHorizontalScrollbar.cpp
# End Source File
# Begin Source File

SOURCE=.\resFile\ReDrawListCtrl\SkinVerticleScrollbar.cpp
# End Source File
# Begin Source File

SOURCE=.\Spectrum.cpp
# End Source File
# Begin Source File

SOURCE=.\SpectrumSetting.cpp
# End Source File
# Begin Source File

SOURCE=.\StatisticDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Status.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\resFile\autocomplete\Subclass.cpp
# End Source File
# Begin Source File

SOURCE=.\SystemSetting.cpp
# End Source File
# Begin Source File

SOURCE=.\resFile\Tools\Tools.cpp
# End Source File
# Begin Source File

SOURCE=.\Wizard.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AccumulateLevel.h
# End Source File
# Begin Source File

SOURCE=.\AddUsersDlg.h
# End Source File
# Begin Source File

SOURCE=.\AuthorityView.h
# End Source File
# Begin Source File

SOURCE=.\resFile\Barcode\Barcode.h
# End Source File
# Begin Source File

SOURCE=.\BinDlg.h
# End Source File
# Begin Source File

SOURCE=.\resFile\BitButtonNL\BitButtonNL.h
# End Source File
# Begin Source File

SOURCE=.\ChangePassword.h
# End Source File
# Begin Source File

SOURCE=.\Chip1Dlg.h
# End Source File
# Begin Source File

SOURCE=.\Chip2Dlg.h
# End Source File
# Begin Source File

SOURCE=.\Chip3Dlg.h
# End Source File
# Begin Source File

SOURCE=.\ChipsHandle.h
# End Source File
# Begin Source File

SOURCE=.\ChipType.h
# End Source File
# Begin Source File

SOURCE=.\CIEDiagram.h
# End Source File
# Begin Source File

SOURCE=.\resFile\ReDrawListCtrl\ComboListCtrl.h
# End Source File
# Begin Source File

SOURCE=.\ControlsDlg.h
# End Source File
# Begin Source File

SOURCE=.\resFile\coolmenu\CoolMenu.h
# End Source File
# Begin Source File

SOURCE=.\CSpecGCS.h
# End Source File
# Begin Source File

SOURCE=.\DeleteUsersDlg.h
# End Source File
# Begin Source File

SOURCE=.\EngineerLogin.h
# End Source File
# Begin Source File

SOURCE=.\FileHandle.h
# End Source File
# Begin Source File

SOURCE=.\Functions.h
# End Source File
# Begin Source File

SOURCE=.\Global_MySpecGCS.h
# End Source File
# Begin Source File

SOURCE=.\HandleLevel.h
# End Source File
# Begin Source File

SOURCE=.\HardDisk.h
# End Source File
# Begin Source File

SOURCE=.\highpower.h
# End Source File
# Begin Source File

SOURCE=.\HighPowerInterface.h
# End Source File
# Begin Source File

SOURCE=.\HighPowerInterfaceDlg.h
# End Source File
# Begin Source File

SOURCE=.\HolyChipOptics.h
# End Source File
# Begin Source File

SOURCE=.\INITIALDlg.h
# End Source File
# Begin Source File

SOURCE=.\resFile\ReDrawListCtrl\InPlaceCombo.h
# End Source File
# Begin Source File

SOURCE=.\resFile\ReDrawListCtrl\InPlaceEdit.h
# End Source File
# Begin Source File

SOURCE=.\LevelDlg.h
# End Source File
# Begin Source File

SOURCE=.\Light.h
# End Source File
# Begin Source File

SOURCE=.\Login.h
# End Source File
# Begin Source File

SOURCE=.\MD5Checksum.h
# End Source File
# Begin Source File

SOURCE=.\resFile\ProgressCtrlX\MemDC.h
# End Source File
# Begin Source File

SOURCE=.\resFile\ReDrawListCtrl\MEMDC.H
# End Source File
# Begin Source File

SOURCE=.\mscomm.h
# End Source File
# Begin Source File

SOURCE=.\resFile\PopMenu\PopupMenu.h
# End Source File
# Begin Source File

SOURCE=.\ReDrawEdit.h
# End Source File
# Begin Source File

SOURCE=.\RedrawTabCtrl.h
# End Source File
# Begin Source File

SOURCE=.\RedrawTabCtrl2.h
# End Source File
# Begin Source File

SOURCE=.\RegisterDlg.h
# End Source File
# Begin Source File

SOURCE=.\RegistHandle.h
# End Source File
# Begin Source File

SOURCE=.\resFile\ResizingDialog\ResizingDialog.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SetChipFeet.h
# End Source File
# Begin Source File

SOURCE=.\SetParameter.h
# End Source File
# Begin Source File

SOURCE=.\SetPrint.h
# End Source File
# Begin Source File

SOURCE=.\SetPrintForm.h
# End Source File
# Begin Source File

SOURCE=.\SetSpmCompen.h
# End Source File
# Begin Source File

SOURCE=.\SetSpmReadLmp.h
# End Source File
# Begin Source File

SOURCE=.\SetSpmReadParam.h
# End Source File
# Begin Source File

SOURCE=.\SetSpmSaveDark.h
# End Source File
# Begin Source File

SOURCE=.\SetSpmSaveRefer.h
# End Source File
# Begin Source File

SOURCE=.\SettingDlg.h
# End Source File
# Begin Source File

SOURCE=.\ShootDiagram.h
# End Source File
# Begin Source File

SOURCE=.\ShowLevel.h
# End Source File
# Begin Source File

SOURCE=.\ShowTestDlg.h
# End Source File
# Begin Source File

SOURCE=.\ShowTestPopup.h
# End Source File
# Begin Source File

SOURCE=.\resFile\ReDrawListCtrl\SkinHeaderCtrl.h
# End Source File
# Begin Source File

SOURCE=.\resFile\ReDrawListCtrl\SkinHorizontalScrollbar.h
# End Source File
# Begin Source File

SOURCE=.\resFile\ReDrawListCtrl\SkinVerticleScrollbar.h
# End Source File
# Begin Source File

SOURCE=.\SpectraArsenalEmissionAPI.h
# End Source File
# Begin Source File

SOURCE=.\Spectrum.h
# End Source File
# Begin Source File

SOURCE=.\SpectrumSetting.h
# End Source File
# Begin Source File

SOURCE=.\StatisticDlg.h
# End Source File
# Begin Source File

SOURCE=.\Status.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SystemSetting.h
# End Source File
# Begin Source File

SOURCE=.\Tools.h
# End Source File
# Begin Source File

SOURCE=.\Wizard.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Accumulate.bmp
# End Source File
# Begin Source File

SOURCE=.\res\AccumulateBK.bmp
# End Source File
# Begin Source File

SOURCE=.\res\AccumulateLevel.bmp
# End Source File
# Begin Source File

SOURCE=.\res\add1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\add2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\add3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\add4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\AddDarkDisable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\AddDarkDown.bmp
# End Source File
# Begin Source File

SOURCE=.\res\AddDarkHigh.bmp
# End Source File
# Begin Source File

SOURCE=.\res\AddDarkNormal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\AddDisable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\AddDown.bmp
# End Source File
# Begin Source File

SOURCE=.\res\AddHigh.bmp
# End Source File
# Begin Source File

SOURCE=.\res\AddItemDisable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\AddItemDown.bmp
# End Source File
# Begin Source File

SOURCE=.\res\AddItemHigh.bmp
# End Source File
# Begin Source File

SOURCE=.\res\AddItemNormal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\AddLevelDisable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\AddLevelDown.bmp
# End Source File
# Begin Source File

SOURCE=.\res\AddLevelHigh.bmp
# End Source File
# Begin Source File

SOURCE=.\res\AddLevelNormal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\AddNormal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\AddUserBK.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ApplyLevelDisable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ApplyLevelDisable2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ApplyLevelDown.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ApplyLevelDown2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ApplyLevelHigh.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ApplyLevelHigh2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ApplyLevelNormal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ApplyLevelNormal2.bmp
# End Source File
# Begin Source File

SOURCE=".\res\Aqua Smooth Folder Developer.ico"
# End Source File
# Begin Source File

SOURCE=".\res\Aqua Smooth Folder DropBox.ico"
# End Source File
# Begin Source File

SOURCE=".\res\Aqua Smooth Folder Library.ico"
# End Source File
# Begin Source File

SOURCE=".\res\Aqua Stripped Folder Generic.ico"
# End Source File
# Begin Source File

SOURCE=.\res\ArrowDown.bmp
# End Source File
# Begin Source File

SOURCE=.\res\AuthorityBtDisable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\AuthorityBtDown.bmp
# End Source File
# Begin Source File

SOURCE=.\res\AuthorityBtHigh.bmp
# End Source File
# Begin Source File

SOURCE=.\res\AuthorityBtNormal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\AutoDisable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\AutoDisable2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\AutoDown.bmp
# End Source File
# Begin Source File

SOURCE=.\res\AutoDown2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\AutoHigh.bmp
# End Source File
# Begin Source File

SOURCE=.\res\AutoHigh2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\AutoNormal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\AutoNormal2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\big0.bmp
# End Source File
# Begin Source File

SOURCE=.\res\big1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BigT21.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BigT22.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BigT42.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BigT430A.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BigT430B.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BigT431A.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BigT431B.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BigT63.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BigZ21.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BigZ22.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BigZ3200.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BigZ3201.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BigZ3210.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BigZ3211.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BigZ4300.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BigZ4301.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BigZ4310.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BigZ4311.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BinNum.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BinNum2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap7.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BK.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bk1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bk10.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bk11.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bk12.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bk2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bk3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bk4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bk5.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bk6.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bk7.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bk8.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bk9.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BKtest.bmp
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

SOURCE=.\res\bt1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bt2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bt3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\button_a.bmp
# End Source File
# Begin Source File

SOURCE=.\res\button_m.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CalTestDisable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CalTestDown.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CalTestHigh.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CalTestNormal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cancel1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cancel2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cancel3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cancel4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CancelDisable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CancelDisable0.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CancelDisable2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CancelDisable3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CancelDisable4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CancelDisable5.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CancelDown.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CancelDown0.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CancelDown2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CancelDown3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CancelDown4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CancelDown5.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CancelHigh.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CancelHigh0.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CancelHigh2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CancelHigh3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CancelHigh4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CancelHigh5.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CancelNormal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CancelNormal2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CancelNormal3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CancelNormal4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CancelNormal5.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CancelNromal0.bmp
# End Source File
# Begin Source File

SOURCE=.\res\changepassword.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ChangePsdBK.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CheckLevelDisable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CheckLevelDown.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CheckLevelHigh.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CheckLevelNormal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\chip1.1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\chip1.2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\chip1.3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\chip1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\chip2.1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\chip2.2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\chip2.3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\chip2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\chip3.1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\chip3.2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\chip3.3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\chip3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\chipType.bmp
# End Source File
# Begin Source File

SOURCE=".\res\Chromaticity-diagram.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\CIE.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CIE2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ClearCalDisable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ClearCalDown.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ClearCalHigh.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ClearCalNormal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ClearDarkDisable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ClearDarkDown.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ClearDarkHigh.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ClearDarkNormal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ClearDotDisable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ClearDotDown.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ClearDotHigh.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ClearDotNormal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ClearRectDisable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ClearRectDown.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ClearRectHigh.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ClearRectNormal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CloseLightDisable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CloseLightDown.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CloseLightHigh.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CloseLightNormal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\colHeader.bmp
# End Source File
# Begin Source File

SOURCE=.\res\colHeader2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Color.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ColumnHeaderEnd.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ColumnHeaderSpan.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ColumnHeaderStart.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ContinueDisable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ContinueDisable2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ContinueDown.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ContinueDown2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ContinueHigh.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ContinueHigh2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ContinueNormal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ContinueNormal2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CSVFileDisable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CSVFileDown.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CSVFileHigh.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CSVFileNormal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\dark.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DarkSpec.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DelDisable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DelDown.bmp
# End Source File
# Begin Source File

SOURCE=.\res\delete.bmp
# End Source File
# Begin Source File

SOURCE=.\res\delete2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\delete3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DelHigh.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DelItemDisable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DelItemDown.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DelItemHigh.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DelItemNormal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DelLevelDisable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DelLevelDown.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DellevelHigh.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DelLevelNormal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DelNormal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DelUserBK.bmp
# End Source File
# Begin Source File

SOURCE=.\res\e3fcfb1a703f01d85ff15d9b98de5287.ico
# End Source File
# Begin Source File

SOURCE=.\res\ElecTestDisable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ElecTestDown.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ElecTestHigh.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ElecTestNormal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\email.ico
# End Source File
# Begin Source File

SOURCE=.\res\EngineerBK.bmp
# End Source File
# Begin Source File

SOURCE=.\res\exit.ico
# End Source File
# Begin Source File

SOURCE=.\res\ExitDisable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ExitDown.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ExitHigh.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ExitNormal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\FinalCal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GetCalDisable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GetcalDown.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GetCalHigh.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GetCalNormal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GetGainDisable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GetGainDown.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GetGainHigh.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GetGainNormal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GetSpecParamDisable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GetSpecParamDown.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GetSpecParamHigh.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GetSpecParamNormal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GetTypeDisable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GetTypeDown.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GetTypeHigh.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GetTypeNomal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GetTypeNormal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GetWL1Disable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GetWL1Down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GetWL1High.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GetWL1Normal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GetWL2Disable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GetWL2Down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GetWL2High.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GetWL2Normal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\HandleLevelDisable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\HandleLevelDown.bmp
# End Source File
# Begin Source File

SOURCE=.\res\HandleLevelHigh.bmp
# End Source File
# Begin Source File

SOURCE=.\res\HandleLevelNormal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\help.ico
# End Source File
# Begin Source File

SOURCE=.\res\HighPowerInterface.ico
# End Source File
# Begin Source File

SOURCE=.\res\HighPowerInterface.rc2
# End Source File
# Begin Source File

SOURCE=.\res\HolyChip.ico
# End Source File
# Begin Source File

SOURCE=.\res\HorizontalScrollBarLeftArrow.bmp
# End Source File
# Begin Source File

SOURCE=.\res\HorizontalScrollBarRightArrow.bmp
# End Source File
# Begin Source File

SOURCE=.\res\HorizontalScrollBarSpan.bmp
# End Source File
# Begin Source File

SOURCE=.\res\HorizontalScrollBarThumb.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon3.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon4.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon5.ico
# End Source File
# Begin Source File

SOURCE=.\res\idjr0405.bmp
# End Source File
# Begin Source File

SOURCE=.\res\idjr0405.jpg
# End Source File
# Begin Source File

SOURCE=.\res\InitCancelDown.bmp
# End Source File
# Begin Source File

SOURCE=.\res\InitCancelHigh.bmp
# End Source File
# Begin Source File

SOURCE=.\res\InitCancelNormal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\InitialBK.bmp
# End Source File
# Begin Source File

SOURCE=.\res\InitialBTDown.bmp
# End Source File
# Begin Source File

SOURCE=.\res\InitialBTHigh.bmp
# End Source File
# Begin Source File

SOURCE=.\res\InitialBTNormal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\InitialDlg.bmp
# End Source File
# Begin Source File

SOURCE=.\res\InitText.bmp
# End Source File
# Begin Source File

SOURCE=.\res\InteTimeDisable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\InteTimeDown.bmp
# End Source File
# Begin Source File

SOURCE=.\res\InteTimeHigh.bmp
# End Source File
# Begin Source File

SOURCE=.\res\InteTimeNormal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\LampFile.bmp
# End Source File
# Begin Source File

SOURCE=.\res\LeftTime.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Light.bmp
# End Source File
# Begin Source File

SOURCE=.\res\LightBK.bmp
# End Source File
# Begin Source File

SOURCE=.\res\LightDisable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\LightDown.bmp
# End Source File
# Begin Source File

SOURCE=.\res\LightHigh.bmp
# End Source File
# Begin Source File

SOURCE=.\res\LightNormal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ListBK.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ListBK2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\login.bmp
# End Source File
# Begin Source File

SOURCE=.\res\login2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\login3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\LoginBK.bmp
# End Source File
# Begin Source File

SOURCE=.\res\MainBK.bmp
# End Source File
# Begin Source File

SOURCE=.\res\MainBK2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\MinusDarkDisable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\MinusDarkDisable2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\MinusDarkDown.bmp
# End Source File
# Begin Source File

SOURCE=.\res\MinusDarkDown2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\MinusDarkHigh.bmp
# End Source File
# Begin Source File

SOURCE=.\res\MinusDarkHigh2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\MinusDarkNormal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\MinusDarkNormal2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\newuser10.bmp
# End Source File
# Begin Source File

SOURCE=.\res\newuser2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\newuser3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\newuser4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\newuser5.bmp
# End Source File
# Begin Source File

SOURCE=.\res\newuser6.bmp
# End Source File
# Begin Source File

SOURCE=.\res\newuser7.bmp
# End Source File
# Begin Source File

SOURCE=.\res\newuser8.bmp
# End Source File
# Begin Source File

SOURCE=.\res\newuser9.bmp
# End Source File
# Begin Source File

SOURCE=.\res\open.ico
# End Source File
# Begin Source File

SOURCE=.\res\Picture.ico
# End Source File
# Begin Source File

SOURCE=.\res\picture10.bmp
# End Source File
# Begin Source File

SOURCE=.\res\picture11.bmp
# End Source File
# Begin Source File

SOURCE=.\res\picture12.bmp
# End Source File
# Begin Source File

SOURCE=.\res\picture13.bmp
# End Source File
# Begin Source File

SOURCE=.\res\picture14.bmp
# End Source File
# Begin Source File

SOURCE=.\res\picture15.bmp
# End Source File
# Begin Source File

SOURCE=.\res\picture16.bmp
# End Source File
# Begin Source File

SOURCE=.\res\picture17.bmp
# End Source File
# Begin Source File

SOURCE=.\res\picture18.bmp
# End Source File
# Begin Source File

SOURCE=.\res\picture19.bmp
# End Source File
# Begin Source File

SOURCE=.\res\picture20.bmp
# End Source File
# Begin Source File

SOURCE=.\res\picture21.bmp
# End Source File
# Begin Source File

SOURCE=.\res\picture22.bmp
# End Source File
# Begin Source File

SOURCE=.\res\picture23.bmp
# End Source File
# Begin Source File

SOURCE=.\res\picture24.bmp
# End Source File
# Begin Source File

SOURCE=.\res\picture25.bmp
# End Source File
# Begin Source File

SOURCE=.\res\picture3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\picture4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\picture5.bmp
# End Source File
# Begin Source File

SOURCE=.\res\picture6.bmp
# End Source File
# Begin Source File

SOURCE=.\res\picture7.bmp
# End Source File
# Begin Source File

SOURCE=.\res\picture8.bmp
# End Source File
# Begin Source File

SOURCE=.\res\picture9.bmp
# End Source File
# Begin Source File

SOURCE=.\res\refer.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ReferSpec.bmp
# End Source File
# Begin Source File

SOURCE=.\res\RegistBK.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Register.bmp
# End Source File
# Begin Source File

SOURCE=.\res\RegisterBTDown.bmp
# End Source File
# Begin Source File

SOURCE=.\res\RegisterBTHigh.bmp
# End Source File
# Begin Source File

SOURCE=.\res\RegisterBTNormal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\RegisterCancelDown.bmp
# End Source File
# Begin Source File

SOURCE=.\res\RegisterCancelHigh.bmp
# End Source File
# Begin Source File

SOURCE=.\res\RegisterCancelNormal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\save.ico
# End Source File
# Begin Source File

SOURCE=.\res\SaveDisable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SaveDisable2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SaveDown.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SaveDown2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SaveHigh.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SaveHigh2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SaveNormal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SaveNormal2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SetAuthorityDisable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SetAuthorityDown.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SetAuthorityHigh.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SetAuthorityNormal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SetChipBK.bmp
# End Source File
# Begin Source File

SOURCE=.\res\setlevel.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SetLevelBK.bmp
# End Source File
# Begin Source File

SOURCE=.\res\setok1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\setpara.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SetParamBK.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SetParamBK2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SetParameter.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SetSpectrumBK.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SetSystemBK.bmp
# End Source File
# Begin Source File

SOURCE=.\res\setting.bmp
# End Source File
# Begin Source File

SOURCE=.\res\settingbk.bmp
# End Source File
# Begin Source File

SOURCE=.\res\settingbk2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\shoot.bmp
# End Source File
# Begin Source File

SOURCE=.\res\shootBK.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ShootBTDisable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ShootBTDown.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ShootBTHigh.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ShootBTNormal.bmp
# End Source File
# Begin Source File

SOURCE=".\res\ShootChromaticity-diagram.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\ShootCIE.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ShootCIE3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ShootFileDisable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ShootFileDown.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ShootFileHigh.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ShootFileNormal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ShowAuthority.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ShowLevelDisable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ShowLevelDown.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ShowLevelHigh.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ShowLevelNormal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ShowRectDisable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ShowRectDown.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ShowRectHigh.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ShowRectNormal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SingleDisable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SingleDisable2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SingleDown.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SingleDown2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SingleHigh.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SingleHigh2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SingleNormal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SingleNormal2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SmallT21.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SmallT22.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SmallT42.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SmallT430A.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SmallT430B.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SmallT431A.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SmallT431B.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SmallT63.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SmallZ21.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SmallZ22.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SmallZ3200.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SmallZ3201.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SmallZ3210.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SmallZ3211.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SmallZ4300.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SmallZ4301.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SmallZ4310.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SmallZ4311.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SpectrumConfigDisable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SpectrumConfigDown.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SpectrumConfigHigh.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SpectrumConfigNormal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\spectrumsetting.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SpmReadParam.bmp
# End Source File
# Begin Source File

SOURCE=.\res\StaFilePath.bmp
# End Source File
# Begin Source File

SOURCE=.\res\StopDisable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\StopDisable2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\StopDown.bmp
# End Source File
# Begin Source File

SOURCE=.\res\StopDown2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\StopHigh.bmp
# End Source File
# Begin Source File

SOURCE=.\res\StopHigh2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\StopNormal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\StopNormal2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SureDisable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SureDisable2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SureDisable3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SureDown.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SureDown2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SureDown3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SureHigh.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SureHigh2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SureHigh3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SureNormal.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SureNormal2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SureNormal3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\t0.bmp
# End Source File
# Begin Source File

SOURCE=.\res\TabHeadChip1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\TabHeadChip2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\TabHeadChip3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\TabHeadSetChip.bmp
# End Source File
# Begin Source File

SOURCE=.\res\TabHeadSetLevel.bmp
# End Source File
# Begin Source File

SOURCE=.\res\TabHeadSetParam.bmp
# End Source File
# Begin Source File

SOURCE=.\res\TabHeadSetParameter.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Temperature.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Temperature2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Temperature3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ToolBar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbarbk.bmp
# End Source File
# Begin Source File

SOURCE=.\res\typeBK.bmp
# End Source File
# Begin Source File

SOURCE=.\res\VerticleScrollbarBottom.bmp
# End Source File
# Begin Source File

SOURCE=.\res\VerticleScrollBarDownArrow.bmp
# End Source File
# Begin Source File

SOURCE=.\res\VerticleScrollBarSpan.bmp
# End Source File
# Begin Source File

SOURCE=.\res\VerticleScrollBarThumb.bmp
# End Source File
# Begin Source File

SOURCE=.\res\VerticleScrollbarTop.bmp
# End Source File
# Begin Source File

SOURCE=.\res\VerticleScrollBarUpArrow.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Wizard.bmp
# End Source File
# Begin Source File

SOURCE=.\res\wzd.ico
# End Source File
# Begin Source File

SOURCE=.\res\xpic3171.bmp
# End Source File
# Begin Source File

SOURCE=.\res\xpic3172.bmp
# End Source File
# Begin Source File

SOURCE=".\res\操作员登陆.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\打开.ico"
# End Source File
# Begin Source File

SOURCE=".\res\登陆Disable.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\登陆Down.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\登陆High.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\登陆Normal.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\工程师登陆.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\密码修改.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\确定Disable.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\确定Down.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\确定High.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\确定Normal.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\软件注册.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\色度图.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\色度图2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\修改密码Disable.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\修改密码Down.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\修改密码High.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\修改密码Normal.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\直插 三脚双晶共阳中.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\直插 双脚单晶.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\直插 双脚双晶.bmp"
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section HighPowerInterface : {E6E17E90-DF38-11CF-8E74-00A0C90F26F8}
# 	2:5:Class:CMSComm
# 	2:10:HeaderFile:mscomm.h
# 	2:8:ImplFile:mscomm.cpp
# End Section
# Section HighPowerInterface : {648A5600-2C6E-101B-82B6-000000000014}
# 	2:21:DefaultSinkHeaderFile:mscomm.h
# 	2:16:DefaultSinkClass:CMSComm
# End Section
