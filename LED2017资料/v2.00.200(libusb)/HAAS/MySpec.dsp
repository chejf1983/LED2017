# Microsoft Developer Studio Project File - Name="MySpec" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=MySpec - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MySpec.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MySpec.mak" CFG="MySpec - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MySpec - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "MySpec - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MySpec - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 imageobject.lib imageload.lib SpectraArsenal.lib NH_GetColorParaDLL.lib /nologo /subsystem:windows /machine:I386 /out:"APP/SpectraNexus.exe"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "MySpec - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 imageobject.lib imageload.lib SpectraArsenal.lib NH_GetColorParaDLL.lib /nologo /subsystem:windows /debug /machine:I386 /out:"APP/SpectraNexus_D.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "MySpec - Win32 Release"
# Name "MySpec - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\_recordset.cpp
# End Source File
# Begin Source File

SOURCE=.\AccreditData.cpp
# End Source File
# Begin Source File

SOURCE=.\adodc.cpp
# End Source File
# Begin Source File

SOURCE=.\BCMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\BWSerial.cpp
# End Source File
# Begin Source File

SOURCE=.\BWTEK_RS.cpp
# End Source File
# Begin Source File

SOURCE=.\CalFluxData.cpp
# End Source File
# Begin Source File

SOURCE=.\CalFluxList.cpp
# End Source File
# Begin Source File

SOURCE=.\CalFluxPLData.cpp
# End Source File
# Begin Source File

SOURCE=.\CalFluxPLList.cpp
# End Source File
# Begin Source File

SOURCE=.\CoolTabCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\DataPage1.cpp
# End Source File
# Begin Source File

SOURCE=.\DataPage2.cpp
# End Source File
# Begin Source File

SOURCE=.\DataPage3.cpp
# End Source File
# Begin Source File

SOURCE=.\DataPage4.cpp
# End Source File
# Begin Source File

SOURCE=.\DataSheet.cpp
# End Source File
# Begin Source File

SOURCE=.\DataSheetT.cpp
# End Source File
# Begin Source File

SOURCE=.\DaXinPowerComm.cpp
# End Source File
# Begin Source File

SOURCE=.\Debug1.cpp
# End Source File
# Begin Source File

SOURCE=.\Debug2.cpp
# End Source File
# Begin Source File

SOURCE=.\Debug3.cpp
# End Source File
# Begin Source File

SOURCE=.\Debug4.cpp
# End Source File
# Begin Source File

SOURCE=.\Debug5.cpp
# End Source File
# Begin Source File

SOURCE=.\Debug6.cpp
# End Source File
# Begin Source File

SOURCE=.\DebugLine.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCalAtt.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCalFlux.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCalPLFlux.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCheckBW.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgControlKEY.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgExportLamp.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgFastLevel.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgFluxCal.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgInputPower.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLEDClassDataEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLEDClassEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLEDClassSetPara.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLevel.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgName.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgNewFluxCal.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgParaSele.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgReGe.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSeleCT.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSelePara.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSelfKEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSelfPhK.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSetPower.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSpectrumCal.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSpectrumCalU.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgWhite.cpp
# End Source File
# Begin Source File

SOURCE=.\DrawForMySpec.cpp
# End Source File
# Begin Source File

SOURCE=.\FailFlagData.cpp
# End Source File
# Begin Source File

SOURCE=.\field.cpp
# End Source File
# Begin Source File

SOURCE=.\fields.cpp
# End Source File
# Begin Source File

SOURCE=.\FluxLampSelfCalData.cpp
# End Source File
# Begin Source File

SOURCE=.\font1.cpp
# End Source File
# Begin Source File

SOURCE=.\Fulllist.cpp
# End Source File
# Begin Source File

SOURCE=.\Global_U.cpp
# End Source File
# Begin Source File

SOURCE=.\Label.cpp
# End Source File
# Begin Source File

SOURCE=.\LED300Data.cpp
# End Source File
# Begin Source File

SOURCE=.\LED300ListData.cpp
# End Source File
# Begin Source File

SOURCE=.\LEDTypeCal.cpp
# End Source File
# Begin Source File

SOURCE=.\LevelLimit.cpp
# End Source File
# Begin Source File

SOURCE=.\LimitData.cpp
# End Source File
# Begin Source File

SOURCE=.\LogFile.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MatrixStatic.cpp
# End Source File
# Begin Source File

SOURCE=.\MPCLogoPane.cpp
# End Source File
# Begin Source File

SOURCE=.\MPCStatusBar.cpp
# End Source File
# Begin Source File

SOURCE=.\msflexgrid.cpp
# End Source File
# Begin Source File

SOURCE=.\msflexgrid1.cpp
# End Source File
# Begin Source File

SOURCE=.\MusterData.cpp
# End Source File
# Begin Source File

SOURCE=.\MusterType.cpp
# End Source File
# Begin Source File

SOURCE=.\My_iniFile.cpp
# End Source File
# Begin Source File

SOURCE=.\MySheet.cpp
# End Source File
# Begin Source File

SOURCE=.\MySpec.cpp
# End Source File
# Begin Source File

SOURCE=.\MySpec.rc
# End Source File
# Begin Source File

SOURCE=.\MySpecDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\MySpecView.cpp
# End Source File
# Begin Source File

SOURCE=.\NewLEDClass.cpp
# End Source File
# Begin Source File

SOURCE=.\NewLEDClassData.cpp
# End Source File
# Begin Source File

SOURCE=.\Note.cpp
# End Source File
# Begin Source File

SOURCE=.\NPPowerMeterComm.cpp
# End Source File
# Begin Source File

SOURCE=.\ntgraph.cpp
# End Source File
# Begin Source File

SOURCE=.\OPSetupData.cpp
# End Source File
# Begin Source File

SOURCE=.\Option1.cpp
# End Source File
# Begin Source File

SOURCE=.\Option2.cpp
# End Source File
# Begin Source File

SOURCE=.\Option3.cpp
# End Source File
# Begin Source File

SOURCE=.\Page1.cpp
# End Source File
# Begin Source File

SOURCE=.\Page2.cpp
# End Source File
# Begin Source File

SOURCE=.\Page3.cpp
# End Source File
# Begin Source File

SOURCE=.\Page4.cpp
# End Source File
# Begin Source File

SOURCE=.\Page5.cpp
# End Source File
# Begin Source File

SOURCE=.\PageCurrVsL1.cpp
# End Source File
# Begin Source File

SOURCE=.\PageCurrVsL2.cpp
# End Source File
# Begin Source File

SOURCE=.\PageCurrVsT1.cpp
# End Source File
# Begin Source File

SOURCE=.\PageCurrVsT2.cpp
# End Source File
# Begin Source File

SOURCE=.\picture1.cpp
# End Source File
# Begin Source File

SOURCE=.\PowerComm.cpp
# End Source File
# Begin Source File

SOURCE=.\ProcessData.cpp
# End Source File
# Begin Source File

SOURCE=.\properties.cpp
# End Source File
# Begin Source File

SOURCE=.\property.cpp
# End Source File
# Begin Source File

SOURCE=.\rowcursor.cpp
# End Source File
# Begin Source File

SOURCE=.\rowcursor1.cpp
# End Source File
# Begin Source File

SOURCE=.\Rowview.cpp
# End Source File
# Begin Source File

SOURCE=.\scbarg.cpp
# End Source File
# Begin Source File

SOURCE=.\SDCM.cpp
# End Source File
# Begin Source File

SOURCE=.\SelfCorrectData.cpp
# End Source File
# Begin Source File

SOURCE=.\Serial.cpp
# End Source File
# Begin Source File

SOURCE=.\Setup1.cpp
# End Source File
# Begin Source File

SOURCE=.\Setup2.cpp
# End Source File
# Begin Source File

SOURCE=.\Setup3.cpp
# End Source File
# Begin Source File

SOURCE=.\Setup4.cpp
# End Source File
# Begin Source File

SOURCE=.\SheetOthers.cpp
# End Source File
# Begin Source File

SOURCE=.\sizecbar.cpp
# End Source File
# Begin Source File

SOURCE=.\SortHeaderCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\SortListCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\SPEC_HAAS.cpp
# End Source File
# Begin Source File

SOURCE=.\SPEC_PRO.cpp
# End Source File
# Begin Source File

SOURCE=.\SpectData.cpp
# End Source File
# Begin Source File

SOURCE=.\SpectrumView.cpp
# End Source File
# Begin Source File

SOURCE=.\Splash.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TenView.cpp
# End Source File
# Begin Source File

SOURCE=.\TestInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\WhiteZone.cpp
# End Source File
# Begin Source File

SOURCE=.\WLCheck.cpp
# End Source File
# Begin Source File

SOURCE=.\WLCorData.cpp
# End Source File
# Begin Source File

SOURCE=.\WYDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ZOoneXY.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\_recordset.h
# End Source File
# Begin Source File

SOURCE=.\About_def.h
# End Source File
# Begin Source File

SOURCE=.\AccreditData.h
# End Source File
# Begin Source File

SOURCE=.\adodc.h
# End Source File
# Begin Source File

SOURCE=.\as161.h
# End Source File
# Begin Source File

SOURCE=.\BCMenu.h
# End Source File
# Begin Source File

SOURCE=.\BW.h
# End Source File
# Begin Source File

SOURCE=.\BWSerial.h
# End Source File
# Begin Source File

SOURCE=.\BWTEK_RS.h
# End Source File
# Begin Source File

SOURCE=.\CalFluxData.h
# End Source File
# Begin Source File

SOURCE=.\CalFluxList.h
# End Source File
# Begin Source File

SOURCE=.\CalFluxPLData.h
# End Source File
# Begin Source File

SOURCE=.\CalFluxPLList.h
# End Source File
# Begin Source File

SOURCE=.\CoolTabCtrl.h
# End Source File
# Begin Source File

SOURCE=.\CurrVsLData.h
# End Source File
# Begin Source File

SOURCE=.\CurrVsTData.h
# End Source File
# Begin Source File

SOURCE=.\DataPage1.h
# End Source File
# Begin Source File

SOURCE=.\DataPage2.h
# End Source File
# Begin Source File

SOURCE=.\DataPage3.h
# End Source File
# Begin Source File

SOURCE=.\DataPage4.h
# End Source File
# Begin Source File

SOURCE=.\DataSheet.h
# End Source File
# Begin Source File

SOURCE=.\DataSheetT.h
# End Source File
# Begin Source File

SOURCE=.\DaXinPowerComm.h
# End Source File
# Begin Source File

SOURCE=.\Debug1.h
# End Source File
# Begin Source File

SOURCE=.\Debug2.h
# End Source File
# Begin Source File

SOURCE=.\Debug3.h
# End Source File
# Begin Source File

SOURCE=.\Debug4.h
# End Source File
# Begin Source File

SOURCE=.\Debug5.h
# End Source File
# Begin Source File

SOURCE=.\Debug6.h
# End Source File
# Begin Source File

SOURCE=.\DebugLine.h
# End Source File
# Begin Source File

SOURCE=.\DlgCalAtt.h
# End Source File
# Begin Source File

SOURCE=.\DlgCalFlux.h
# End Source File
# Begin Source File

SOURCE=.\DlgCalPLFlux.h
# End Source File
# Begin Source File

SOURCE=.\DlgCheckBW.h
# End Source File
# Begin Source File

SOURCE=.\DlgControlKEY.h
# End Source File
# Begin Source File

SOURCE=.\DlgFastLevel.h
# End Source File
# Begin Source File

SOURCE=.\DlgFluxCal.h
# End Source File
# Begin Source File

SOURCE=.\DlgInputPower.h
# End Source File
# Begin Source File

SOURCE=.\DlgLEDClassDataEdit.h
# End Source File
# Begin Source File

SOURCE=.\DlgLEDClassEdit.h
# End Source File
# Begin Source File

SOURCE=.\DlgLEDClassSetPara.h
# End Source File
# Begin Source File

SOURCE=.\DlgLevel.h
# End Source File
# Begin Source File

SOURCE=.\DlgName.h
# End Source File
# Begin Source File

SOURCE=.\DlgNewFluxCal.h
# End Source File
# Begin Source File

SOURCE=.\DlgParaSele.h
# End Source File
# Begin Source File

SOURCE=.\DlgPhBress.h
# End Source File
# Begin Source File

SOURCE=.\DlgPhoEff.h
# End Source File
# Begin Source File

SOURCE=.\DlgReGe.h
# End Source File
# Begin Source File

SOURCE=.\DlgSeleCT.h
# End Source File
# Begin Source File

SOURCE=.\DlgSelePara.h
# End Source File
# Begin Source File

SOURCE=.\DlgSelfKEdit.h
# End Source File
# Begin Source File

SOURCE=.\DlgSelfPhK.h
# End Source File
# Begin Source File

SOURCE=.\DlgSetHaas.h
# End Source File
# Begin Source File

SOURCE=.\DlgSetPower.h
# End Source File
# Begin Source File

SOURCE=.\DlgSpectrumCal.h
# End Source File
# Begin Source File

SOURCE=.\DlgSpectrumCalU.h
# End Source File
# Begin Source File

SOURCE=.\DlgWhite.h
# End Source File
# Begin Source File

SOURCE=.\DrawForMySpec.h
# End Source File
# Begin Source File

SOURCE=.\ExGetColorParaDLL.h
# End Source File
# Begin Source File

SOURCE=.\FailFlagData.h
# End Source File
# Begin Source File

SOURCE=.\field.h
# End Source File
# Begin Source File

SOURCE=.\fields.h
# End Source File
# Begin Source File

SOURCE=.\FluxLampSelfCalData.h
# End Source File
# Begin Source File

SOURCE=.\font1.h
# End Source File
# Begin Source File

SOURCE=.\FULLLIST.H
# End Source File
# Begin Source File

SOURCE=.\Global_MySpec.h
# End Source File
# Begin Source File

SOURCE=.\Global_U.h
# End Source File
# Begin Source File

SOURCE=.\HAAS_Pipe_Def.h
# End Source File
# Begin Source File

SOURCE=.\imageload.h
# End Source File
# Begin Source File

SOURCE=.\ImageObject.h
# End Source File
# Begin Source File

SOURCE=.\Label.h
# End Source File
# Begin Source File

SOURCE=.\LED300Data.h
# End Source File
# Begin Source File

SOURCE=.\LED300ListData.h
# End Source File
# Begin Source File

SOURCE=.\LEDTypeCal.h
# End Source File
# Begin Source File

SOURCE=.\LevelLimit.h
# End Source File
# Begin Source File

SOURCE=.\LimitData.h
# End Source File
# Begin Source File

SOURCE=.\Listvwex.h
# End Source File
# Begin Source File

SOURCE=.\LogFile.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MatrixStatic.h
# End Source File
# Begin Source File

SOURCE=.\MemDC.h
# End Source File
# Begin Source File

SOURCE=.\MPCLogoPane.h
# End Source File
# Begin Source File

SOURCE=.\MPCStatusBar.h
# End Source File
# Begin Source File

SOURCE=.\msflexgrid.h
# End Source File
# Begin Source File

SOURCE=.\msflexgrid1.h
# End Source File
# Begin Source File

SOURCE=.\MusterData.h
# End Source File
# Begin Source File

SOURCE=.\MusterType.h
# End Source File
# Begin Source File

SOURCE=.\My_iniFile.h
# End Source File
# Begin Source File

SOURCE=.\MySheet.h
# End Source File
# Begin Source File

SOURCE=.\MySpec.h
# End Source File
# Begin Source File

SOURCE=.\MySpecDoc.h
# End Source File
# Begin Source File

SOURCE=.\MySpecView.h
# End Source File
# Begin Source File

SOURCE=.\NewLEDClass.h
# End Source File
# Begin Source File

SOURCE=.\NewLEDClassData.h
# End Source File
# Begin Source File

SOURCE=.\Note.h
# End Source File
# Begin Source File

SOURCE=.\NPPowerMeterComm.h
# End Source File
# Begin Source File

SOURCE=.\ntgraph.h
# End Source File
# Begin Source File

SOURCE=.\OPSetupData.h
# End Source File
# Begin Source File

SOURCE=.\Option1.h
# End Source File
# Begin Source File

SOURCE=.\Option2.h
# End Source File
# Begin Source File

SOURCE=.\Option3.h
# End Source File
# Begin Source File

SOURCE=.\Page1.h
# End Source File
# Begin Source File

SOURCE=.\Page2.h
# End Source File
# Begin Source File

SOURCE=.\Page3.h
# End Source File
# Begin Source File

SOURCE=.\Page4.h
# End Source File
# Begin Source File

SOURCE=.\Page5.h
# End Source File
# Begin Source File

SOURCE=.\PEC2001View.h
# End Source File
# Begin Source File

SOURCE=.\picture1.h
# End Source File
# Begin Source File

SOURCE=.\PowerComm.h
# End Source File
# Begin Source File

SOURCE=.\ProcessData.h
# End Source File
# Begin Source File

SOURCE=.\properties.h
# End Source File
# Begin Source File

SOURCE=.\property.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\rowcursor.h
# End Source File
# Begin Source File

SOURCE=.\rowcursor1.h
# End Source File
# Begin Source File

SOURCE=.\Rowview.h
# End Source File
# Begin Source File

SOURCE=.\scbarg.h
# End Source File
# Begin Source File

SOURCE=.\SDCM.h
# End Source File
# Begin Source File

SOURCE=.\SelfCorrectData.h
# End Source File
# Begin Source File

SOURCE=.\Serial.h
# End Source File
# Begin Source File

SOURCE=.\Setup1.h
# End Source File
# Begin Source File

SOURCE=.\Setup2.h
# End Source File
# Begin Source File

SOURCE=.\Setup3.h
# End Source File
# Begin Source File

SOURCE=.\Setup4.h
# End Source File
# Begin Source File

SOURCE=.\SheetOthers.h
# End Source File
# Begin Source File

SOURCE=.\sizecbar.h
# End Source File
# Begin Source File

SOURCE=.\SortHeaderCtrl.h
# End Source File
# Begin Source File

SOURCE=.\SortListCtrl.h
# End Source File
# Begin Source File

SOURCE=.\SPEC_HAAS.h
# End Source File
# Begin Source File

SOURCE=.\SPEC_PRO.h
# End Source File
# Begin Source File

SOURCE=.\SpectData.h
# End Source File
# Begin Source File

SOURCE=.\SpectraArsenal.h
# End Source File
# Begin Source File

SOURCE=.\SpectrumView.h
# End Source File
# Begin Source File

SOURCE=.\Splash.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TenView.h
# End Source File
# Begin Source File

SOURCE=.\TestInfo.h
# End Source File
# Begin Source File

SOURCE=.\thsFun.h
# End Source File
# Begin Source File

SOURCE=.\WhiteZone.h
# End Source File
# Begin Source File

SOURCE=.\WLCheck.h
# End Source File
# Begin Source File

SOURCE=.\WLCorData.h
# End Source File
# Begin Source File

SOURCE=.\WYDlg.h
# End Source File
# Begin Source File

SOURCE=.\ZOoneXY.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
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

SOURCE=.\res\flux_cal.ico
# End Source File
# Begin Source File

SOURCE=.\res\hand.cur
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00002.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\matrixla.bmp
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

SOURCE=.\res\matrixsm.bmp
# End Source File
# Begin Source File

SOURCE=.\res\matrixti.bmp
# End Source File
# Begin Source File

SOURCE=.\res\MySpec.ico
# End Source File
# Begin Source File

SOURCE=.\res\MySpec.rc2
# End Source File
# Begin Source File

SOURCE=.\res\MySpecDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\sdcm.ico
# End Source File
# Begin Source File

SOURCE=.\res\sele.bmp
# End Source File
# Begin Source File

SOURCE=.\res\smallico.bmp
# End Source File
# Begin Source File

SOURCE=.\res\spec.ico
# End Source File
# Begin Source File

SOURCE=.\res\spect_ca.ico
# End Source File
# Begin Source File

SOURCE=.\Splsh16.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\MySpec.reg
# End Source File
# End Target
# End Project
# Section MySpec : {9F6AA700-D188-11CD-AD48-00AA003C9CB6}
# 	2:5:Class:CRowCursor
# 	2:10:HeaderFile:rowcursor1.h
# 	2:8:ImplFile:rowcursor1.cpp
# End Section
# Section MySpec : {72ADFD6C-2C39-11D0-9903-00A0C91BC942}
# 	1:25:CG_IDR_POPUP_MY_SPEC_VIEW:114
# End Section
# Section MySpec : {0000054D-0000-0010-8000-00AA006D2EA4}
# 	2:5:Class:CFields
# 	2:10:HeaderFile:fields.h
# 	2:8:ImplFile:fields.cpp
# End Section
# Section MySpec : {0000054C-0000-0010-8000-00AA006D2EA4}
# 	2:5:Class:CField
# 	2:10:HeaderFile:field.h
# 	2:8:ImplFile:field.cpp
# End Section
# Section MySpec : {6262D3A0-531B-11CF-91F6-C2863C385E30}
# 	2:21:DefaultSinkHeaderFile:msflexgrid1.h
# 	2:16:DefaultSinkClass:CMSFlexGrid1
# End Section
# Section MySpec : {5F4DF280-531B-11CF-91F6-C2863C385E30}
# 	2:5:Class:CMSFlexGrid1
# 	2:10:HeaderFile:msflexgrid1.h
# 	2:8:ImplFile:msflexgrid1.cpp
# End Section
# Section MySpec : {47A738F1-7FAF-11D0-B148-00A0C922E820}
# 	2:5:Class:CAdodc
# 	2:10:HeaderFile:adodc.h
# 	2:8:ImplFile:adodc.cpp
# End Section
# Section MySpec : {00000504-0000-0010-8000-00AA006D2EA4}
# 	2:5:Class:CProperties
# 	2:10:HeaderFile:properties.h
# 	2:8:ImplFile:properties.cpp
# End Section
# Section MySpec : {72ADFD78-2C39-11D0-9903-00A0C91BC942}
# 	1:10:IDB_SPLASH:104
# 	2:21:SplashScreenInsertKey:4.0
# End Section
# Section MySpec : {BEF6E003-A874-101A-8BBA-00AA00300CAB}
# 	2:5:Class:COleFont
# 	2:10:HeaderFile:font1.h
# 	2:8:ImplFile:font1.cpp
# End Section
# Section MySpec : {67397AA3-7FB1-11D0-B148-00A0C922E820}
# 	2:21:DefaultSinkHeaderFile:adodc.h
# 	2:16:DefaultSinkClass:CAdodc
# End Section
# Section MySpec : {7BF80981-BF32-101A-8BBB-00AA00300CAB}
# 	2:5:Class:CPicture
# 	2:10:HeaderFile:picture1.h
# 	2:8:ImplFile:picture1.cpp
# End Section
# Section MySpec : {0000054F-0000-0010-8000-00AA006D2EA4}
# 	2:5:Class:C_Recordset
# 	2:10:HeaderFile:_recordset.h
# 	2:8:ImplFile:_recordset.cpp
# End Section
# Section MySpec : {00000503-0000-0010-8000-00AA006D2EA4}
# 	2:5:Class:CProperty
# 	2:10:HeaderFile:property.h
# 	2:8:ImplFile:property.cpp
# End Section
