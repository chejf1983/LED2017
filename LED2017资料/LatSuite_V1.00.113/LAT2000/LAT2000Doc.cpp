
// CLAT2000Doc.cpp : CLAT2000Doc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "LAT2000.h"
#endif

#include "LAT2000Doc.h"
#include "MainFrm.h"
#include <propkey.h>
#include <math.h>

#include "StandardLampSettingsDlg.h"
#include "InputPasswordDlg.h"
#include "ModifyCalProtectPassword.h"
#include "CalibrationDlg.h"
#include "ExNewCorrectColorParaDLL.h"
#include "MyDockablePaneData.h"
#include "SystemSettingsDlg.h"
#include "AlarmSettingsDlg.h"
#include "AlarmRingEditDlg.h"

#include "SheetDebug.h"
#include "DebugGaugePage.h"
#include "DebugDPSPage.h"
#include "DebugSC1600Page.h"
#include "DebugPF2010APage.h"
#include "DebugIndicatorPage.h"
#include "DebugA90Page.h"
#include "DebugWYPage.h"
#include "DebugEMS61000_5APage.h"
#include "DebugEMS61000_11KPage.h"
#include "DebugTemperaturePage.h"
#include "DebugLRAPage.h"
#include "DebugThunderRelayPage.h"
#include "DebugLineControllerPage.h"
#include "DebugBribePage.h"
#include "DebugPageHandAuto.h"

#include "MySheet.h"
#include "TestInfoPage_LampInfoPage.h"
#include "TestInfoPage_TestConditionPage.h"   
#include "StatisticParaChooseDlg.h"
#include "TestInfoPage_PrintOpinionPage.h"
#include "CurrentLEDID_Dlg.h"
#include "LineControlerDlg.h"
#include "MainTabWnd.h"
#include "DlgBeforeChangeLamp.h"
#include "DlgSetOldLineTime.h"
#include "AccountDlg.h"
#include "MainTestFormView.h"
#include "DlgShowOldingTime.h"
#include "DlgStatisticFileChoose.h"
#include "DlgListParaChoose.h"
#include "LEDDataStatView.h"
#include "DebugScanerPage.h"
#include "CurrentBoardID_Dlg.h"
#include "WarningYesNODlg.h" 
#include "Configure_AssistantPage.h"
#include "Configure_ExaminationPage.h"
#include "Configure_IndicatorPage.h"
#include "Configure_OthersPage.h"
#include "Configure_TestControlPage.h"
#include "Configure_WatchPage.h"
#include "DebugTestChannelControler.h"
#include "DlgShowOtherNote.h"

#include "DlgDebugSaft.h"
#include "DlgControlShow.h"
#include "DlgInputPower.h"

#include "DlgCurrentBroad.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CBrush g_brBackBlack;
CBrush g_brBackBlue;
CBrush g_brBackGreen;
CBrush g_brSilver;

CSpectrumCommDemo	g_SpectrumDemoComm;		// Only for demo

CLAT2000Doc *g_pDoc = NULL;
CString g_strPathNameAuto;

CMyDockablePaneData g_myDockablePaneData;


int		g_iGaugeNum			= 6;
int		g_iTMPControlNum	= 2;
BOOL	g_bColorCorrection	= FALSE;

extern BOOL Haas1200CorrectColor(CNewTestColorData &data);
extern CMainTestFormView *g_pMainTestFormView;

CString g_strHaveSaveFileName;
CString g_strHaveSaveCsvName;
// CLAT2000Doc

extern BOOL g_bUseArea2;
extern BOOL g_bHaveArea2;
extern int	g_iHaveBribe;
extern int	g_iSeleTestLamp;

BOOL	g_bInputPower;
float	g_fInputVol;
float	g_fInputCurr;
float	g_fInputPower;
float	g_fInputPF;

//CArray <CString, CString> g_strGaugeData[16];

IMPLEMENT_DYNCREATE(CLAT2000Doc, CDocument)

	BEGIN_MESSAGE_MAP(CLAT2000Doc, CDocument)
		ON_COMMAND(ID_SYSTEM_SETTINGS, OnMenuSystemSettings)
		ON_COMMAND(ID_BUTTON_TEST, OnMenuTest)
		ON_UPDATE_COMMAND_UI(ID_BUTTON_TEST, &CLAT2000Doc::OnUpdateButtonTest)
		ON_COMMAND(ID_BUTTON_EDIT_LIMIT, &CLAT2000Doc::OnButtonEditLimit)
		ON_COMMAND(ID_BUTTON_SPECTRUM_CAL, &CLAT2000Doc::OnButtonSpectrumCal)
		ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, &CLAT2000Doc::OnUpdateFileSaveAs)
		ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, &CLAT2000Doc::OnUpdateFileOpen)
		ON_COMMAND(ID_BUTTON_STOP, &CLAT2000Doc::OnMenuStop)
		ON_UPDATE_COMMAND_UI(ID_BUTTON_STOP, &CLAT2000Doc::OnUpdateButtonPause)
		ON_UPDATE_COMMAND_UI(ID_INDICATOR_TEST_INFO, &CLAT2000Doc::OnUpdateIndicatorTestInfo)
		ON_UPDATE_COMMAND_UI(ID_INDICATOR_STATISTICINFO, &CLAT2000Doc::OnUpdateIndicatorStatisticInfo)
		ON_COMMAND(ID_DEBUG, &CLAT2000Doc::OnDebug)
		ON_UPDATE_COMMAND_UI(ID_DEBUG, &CLAT2000Doc::OnUpdateDebug)
		ON_UPDATE_COMMAND_UI(ID_BUTTON_SPECTRUM_CAL, &CLAT2000Doc::OnUpdateButtonSpectrumCal)
		ON_UPDATE_COMMAND_UI(ID_MODIFY_PROTECT_PASSWORD, &CLAT2000Doc::OnUpdateModifyProtectPassword)
		ON_COMMAND(ID_MODIFY_PROTECT_PASSWORD, &CLAT2000Doc::OnModifyProtectPassword)
		ON_COMMAND(ID_MAKE_REGION, &CLAT2000Doc::OnMakeRegion)
		ON_UPDATE_COMMAND_UI(ID_MAKE_REGION, &CLAT2000Doc::OnUpdateMakeRegion)
		ON_COMMAND(ID_COLOR_OFFSET_EDIT, &CLAT2000Doc::OnColorOffsetEdit)
		ON_UPDATE_COMMAND_UI(ID_COLOR_OFFSET_EDIT, &CLAT2000Doc::OnUpdateColorOffsetEdit)
		ON_COMMAND(ID_COLOR_OFFSET_SELECT, &CLAT2000Doc::OnColorOffsetSelect)
		ON_UPDATE_COMMAND_UI(ID_COLOR_OFFSET_SELECT, &CLAT2000Doc::OnUpdateColorOffsetSelect)
		ON_UPDATE_COMMAND_UI(ID_COMM_SETTINGS, &CLAT2000Doc::OnUpdateCommSettings)
		ON_COMMAND(ID_COMM_SETTINGS, &CLAT2000Doc::OnCommSettings)
		ON_UPDATE_COMMAND_UI(ID_BUTTON_EDIT_LIMIT, &CLAT2000Doc::OnUpdateButtonEditLimit)
		ON_UPDATE_COMMAND_UI(ID_SPECTRUM_TEST, &CLAT2000Doc::OnUpdateSpectrumTest)
		ON_COMMAND(ID_SPECTRUM_TEST, &CLAT2000Doc::OnSpectrumTest)
		ON_COMMAND(ID_ALARM_RING_EDIT, &CLAT2000Doc::OnAlarmRingEdit)
		ON_COMMAND(ID_IMPORT_LAST_DATA, &CLAT2000Doc::OnImportLastData)
		ON_COMMAND(ID_CLEAR_ALL_DATA, &CLAT2000Doc::OnClearAllData)
		ON_UPDATE_COMMAND_UI(ID_IMPORT_LAST_DATA, &CLAT2000Doc::OnUpdateImportLastData)
		ON_UPDATE_COMMAND_UI(ID_CLEAR_ALL_DATA, &CLAT2000Doc::OnUpdateClearAllData)
		ON_COMMAND(ID_STD_LAMP_IN_POSITION, &CLAT2000Doc::OnStdLampInPosition)
        ON_COMMAND(ID_STATISTIC, &CLAT2000Doc::OnStatistic)
        ON_UPDATE_COMMAND_UI(ID_STATISTIC, &CLAT2000Doc::OnUpdateStatistic)
        ON_COMMAND(ID_TESTINFO, &CLAT2000Doc::OnTestinfo)
        ON_UPDATE_COMMAND_UI(ID_TESTINFO, &CLAT2000Doc::OnUpdateTestinfo)
        ON_COMMAND(ID_STATISTIC_PARA_CHOOSE, &CLAT2000Doc::OnStatisticParaChoose)
        ON_UPDATE_COMMAND_UI(ID_STATISTIC_PARA_CHOOSE, &CLAT2000Doc::OnUpdateStatisticParaChoose)
        ON_COMMAND(ID_LINE_CONTROL, &CLAT2000Doc::OnLineControl)
        ON_UPDATE_COMMAND_UI(ID_LINE_CONTROL, &CLAT2000Doc::OnUpdateLineControl)
		ON_COMMAND(ID_VIEW_CUR_SET_PARA, &CLAT2000Doc::OnViewCurSetPara)
		ON_COMMAND(ID_BEFORE_CHANGE_LAMP, &CLAT2000Doc::OnBeforeChangeLamp)
		ON_UPDATE_COMMAND_UI(ID_BEFORE_CHANGE_LAMP, &CLAT2000Doc::OnUpdateBeforeChangeLamp)
		ON_UPDATE_COMMAND_UI(ID_STD_LAMP_IN_POSITION, &CLAT2000Doc::OnUpdateStdLampInPosition)
		ON_UPDATE_COMMAND_UI(ID_ALARM_RING_EDIT, &CLAT2000Doc::OnUpdateAlarmRingEdit)
		ON_COMMAND(ID_CHANGE_ACCOUNT, &CLAT2000Doc::OnChangeAccount)
		ON_UPDATE_COMMAND_UI(ID_CHANGE_ACCOUNT, &CLAT2000Doc::OnUpdateChangeAccount)
        ON_COMMAND(ID_LISTPARA_CHOOSE, &CLAT2000Doc::OnListparaChoose)
		ON_UPDATE_COMMAND_UI(ID_EXPORT_STATISTIC_DATA, &CLAT2000Doc::OnUpdateExportStatisticData)
		ON_COMMAND(ID_SELE_SDCM_STD, &CLAT2000Doc::OnSeleSdcmStd)
		ON_UPDATE_COMMAND_UI(ID_SELE_SDCM_STD, &CLAT2000Doc::OnUpdateSeleSdcmStd)
	END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL CLAT2000Doc::ReadFlagFile(CString strPathName)
{
    int DisPlayFlag, StatisticFlag;
    CFile file;
    if (!file.Open(strPathName, CFile::modeRead))
    {
        return FALSE;
    }

    int iLength = (int)file.GetLength();
    CString strTemp, strTemp2;

    strTemp.GetBufferSetLength(iLength + 1);
    file.Read(strTemp.GetBuffer(), iLength);

    int iIndex = 0;
    iIndex = strTemp.Find("DisplayFlag:", iIndex);
    if (-1 != iIndex)
    {
        strTemp2 = strTemp.Mid(iIndex, 32);
        sscanf_s(strTemp2, "DisplayFlag:%d", &DisPlayFlag);
    }

    iIndex = iIndex > 0? iIndex + 1 : 0;
    iIndex = strTemp.Find("StatisticFlag:", iIndex);
    if (-1 != iIndex)
    {
        strTemp2 = strTemp.Mid(iIndex, 32);
        sscanf_s(strTemp2, "StatisticFlag:%d", &StatisticFlag);
    }
    BOOL bStatistic[PARA_NUM];
    for (int i = 0; i < PARA_NUM; i++)
    {
        g_bListPara[i]	= (DisPlayFlag & (0x01 << i)) / (0x01 << i);
        bStatistic[i]	= (StatisticFlag & (0x01 << i))  / (0x01 << i);          
    }
    m_StatisticLedDataContainer.SetbStatisticPara(bStatistic);
    return TRUE;
}

BOOL CLAT2000Doc::WriteFlagFile(CString strPathName)
{
    FILE *fp;
    if (fopen_s(&fp , strPathName, "wt"))
    {
        return FALSE;
    }
    else
    {
        UINT32 u32flag = 0;
        for (int i = 0; i < PARA_NUM; i++)
        {
            u32flag |= (g_bListPara[i] << i);
        }
        fprintf_s(fp,"DisplayFlag:%d\n", u32flag);
        u32flag = 0;
        for (int i = 0; i < PARA_NUM; i++)
        {
            u32flag |= (m_StatisticLedDataContainer.IsSelectedToStatistic(i) << i);
        }
        fprintf_s(fp,"StatisticFlag:%d\n", u32flag);
        fclose(fp);
        return TRUE;
    }
}

//读取光谱校正数据
BOOL ReadCorrectSpectrumFile(CString strPathName);

BOOL CLAT2000Doc::ReadWatchPaneFile(CString strPathName)
{
    CFile file;
    if (!file.Open(strPathName, CFile::modeRead))
    {
        return FALSE;
    }
    int iLength = (int)file.GetLength();
    CString strTemp, strTemp2;
    char szTemp[256];

    strTemp.GetBufferSetLength(iLength + 1);
    file.Read(strTemp.GetBuffer(), iLength);

    int iTMPControlNum	= 0;
    int iRegionNum		= 0;
    int iIndex			= 0;
    iIndex = strTemp.Find("TemperatureControl Numer:", iIndex);
    if (-1 != iIndex)
    {
        strTemp2 = strTemp.Mid(iIndex, 32);
        sscanf_s(strTemp2, "TemperatureControl Numer:%d", &iTMPControlNum);
    }
		
	BOOL bUseArea2 = 0;
	iIndex = strTemp.Find("USE Area2:", iIndex);
	if (-1 != iIndex)
	{
		strTemp2 = strTemp.Mid(iIndex, 16);
		sscanf_s(strTemp2, "USE Area2:%d", &bUseArea2);
	}
	if (g_bUseArea2)
	{
		//
		iIndex = 0;
		iIndex = iIndex > 0? iIndex + 1 : 0;
		iIndex = strTemp.Find("Area2 Number:", iIndex);
		if (-1 != iIndex)
		{
			strTemp2 = strTemp.Mid(iIndex, 32);
			sscanf_s(strTemp2, "Area2 Number:%d", &iRegionNum);
		}

		g_iGaugeNum = iRegionNum;
		g_iTMPControlNum = iTMPControlNum;

		g_myDockablePaneData.m_strSetTMP.SetSize(iTMPControlNum);
		g_myDockablePaneData.m_strTemperatureControllerText.SetSize(iTMPControlNum);
		g_myDockablePaneData.m_TemperatureController.SetSize(iTMPControlNum);
		g_myDockablePaneData.m_strRegionText.SetSize(iRegionNum);
		g_myDockablePaneData.m_dataRegion.SetSize(iRegionNum);
		g_myDockablePaneData.m_strOutPutVoltage.SetSize(iRegionNum);
		g_myDockablePaneData.m_strOutPutFrequezy.SetSize(iRegionNum);
		iIndex = 0;
		for (int i = 0; i < iTMPControlNum; i ++)
		{
			iIndex = iIndex > 0? iIndex + 1 : 0;
			iIndex = strTemp.Find("TemperatureControlName:", iIndex);
			if (-1 != iIndex)
			{
				strTemp2 = strTemp.Mid(iIndex, 40);
				sscanf_s(strTemp2, "TemperatureControlName:%s", &szTemp, 256);
				g_myDockablePaneData.m_strTemperatureControllerText[i] = szTemp;
			}
		}

		for (int i = 0; i < iRegionNum; i ++)
		{
			iIndex = iIndex > 0? iIndex + 1 : 0;
			iIndex = strTemp.Find("AreaName2:", iIndex);
			if (-1 != iIndex)
			{
				strTemp2 = strTemp.Mid(iIndex, 32);
				sscanf_s(strTemp2, "AreaName2:%s", &szTemp, 256);
				g_myDockablePaneData.m_strRegionText[i] = szTemp;
			}
		}
	}
	else
	{
		iIndex = 0;
		iIndex = iIndex > 0? iIndex + 1 : 0;
		iIndex = strTemp.Find("Area Number:", iIndex);
		if (-1 != iIndex)
		{
			strTemp2 = strTemp.Mid(iIndex, 32);
			sscanf_s(strTemp2, "Area Number:%d", &iRegionNum);
		}

		g_iGaugeNum = iRegionNum;
		g_iTMPControlNum = iTMPControlNum;

		g_myDockablePaneData.m_strSetTMP.SetSize(iTMPControlNum);
		g_myDockablePaneData.m_strTemperatureControllerText.SetSize(iTMPControlNum);
		g_myDockablePaneData.m_TemperatureController.SetSize(iTMPControlNum);
		g_myDockablePaneData.m_strRegionText.SetSize(iRegionNum);
		g_myDockablePaneData.m_dataRegion.SetSize(iRegionNum);
		g_myDockablePaneData.m_strOutPutVoltage.SetSize(iRegionNum);
		g_myDockablePaneData.m_strOutPutFrequezy.SetSize(iRegionNum);
		for (int i = 0; i < iTMPControlNum; i ++)
		{
			iIndex = iIndex > 0? iIndex + 1 : 0;
			iIndex = strTemp.Find("TemperatureControlName:", iIndex);
			if (-1 != iIndex)
			{
				strTemp2 = strTemp.Mid(iIndex, 64);
				sscanf_s(strTemp2, "TemperatureControlName:%s", &szTemp, 256);
				g_myDockablePaneData.m_strTemperatureControllerText[i] = szTemp;
			}
		}

		for (int i = 0; i < iRegionNum; i ++)
		{
			iIndex = iIndex > 0? iIndex + 1 : 0;
			iIndex = strTemp.Find("AreaName:", iIndex);
			if (-1 != iIndex)
			{
				strTemp2 = strTemp.Mid(iIndex, 32);
				sscanf_s(strTemp2, "AreaName:%s", &szTemp, 256);
				g_myDockablePaneData.m_strRegionText[i] = szTemp;
			}
		}
	}

    strTemp.ReleaseBuffer();
    file.Close();
    return TRUE;
}

BOOL g_bDemo;

// CLAT2000Doc 构造/析构
CEvent g_EventOlding(FALSE, TRUE);
CLAT2000Doc::CLAT2000Doc() : m_eventTest(FALSE, TRUE),
	m_eventStartOne(FALSE, TRUE),
	m_eventElectricalEnd(FALSE, FALSE),
	m_eventLightningSurgeEnd(FALSE, FALSE),
	m_eventSpectrumEnd(FALSE, FALSE),
	m_eventVoltageDipsAndUPEnd(FALSE, FALSE),
    m_eventScanerEnd(FALSE, FALSE),
	m_eventSaftJYDZEnd(FALSE, FALSE),
	m_eventSaftNYYEnd(FALSE, FALSE),
	m_eventSaftXLDLEnd(FALSE, FALSE),
	m_eventHandAutoEnd(FALSE,FALSE)
{
	// TODO: 在此添加一次性构造代码
	g_brBackBlack.CreateSolidBrush(RGB(83, 83, 83));
	g_brBackBlue.CreateSolidBrush(RGB(191, 219, 255));
	g_brBackGreen.CreateSolidBrush(RGB(196, 202, 217));
	g_brSilver.CreateSolidBrush(RGB(208, 212, 221));

	m_TestContainer.SetLEDMatrix(g_iRowNum, g_iColomnNum);

	m_bIsElectricalRunning		= FALSE;
	m_bIsLightningSurgeRunning	= FALSE;
	m_bIsSpectrumRunning		= FALSE;
	m_bIsVoltageDipsAndUPRunning= FALSE;
	m_bIsLineControlRunning		= FALSE;
	m_bComtinueMoveRunning		= FALSE;
    m_bIsScanerRunning			= FALSE;
	m_bIsMyLastRunning			= FALSE;
	m_bIsSaftJYDZRunning		= FALSE;
	m_bIsSaftNYYRunning			= FALSE;
	m_bIsSaftXLDLRunning		= FALSE;
	m_bIsHandAutoRunning		= FALSE;
	
	m_bNeedSetTMP			= TRUE;
	m_bSetStop				= TRUE;
	m_iGridCurrentItem		= -1;
	m_iWaitRemainSeconds	= -1;
	m_bCloseDocument		= FALSE;
	m_pThreadGauge			= NULL;

	//////////////////////////////////////////////////////////////////////////////////////////////
	g_pDoc		= this;
	
	m_iNumSaftR = 0;
	m_iNumSaftV = 0;
	m_iNumSaftC = 0;
	m_iHaveBoradSaftR = 0;
	m_iHaveBoradSaftV = 0;
	m_iHaveBoradSaftC = 0;
	// Dockable pane data

	m_systemSettingsData.ReadRegistry();

	CString strSection = "LAT2000Doc_113";

	g_strTestSettingFileName = AfxGetApp()->GetProfileStringA(strSection, "m_strLimitDataFilePathName", g_strLimitDataPath + "LastLimit.dat");
	m_iHaveInLampBroadNum = AfxGetApp()->GetProfileInt(strSection, "m_iHaveInLampBroadNum", 0);
	m_iStartInLampBroad = AfxGetApp()->GetProfileInt(strSection, "m_iStartInLampBroad", 1);
	CString strTemp;
	g_bInputPower	= AfxGetApp()->GetProfileInt(strSection, "g_bInputPower", FALSE);
	strTemp			= AfxGetApp()->GetProfileStringA(strSection, "g_fInputVol", "220");
	g_fInputVol		= (float)atof(strTemp);
	strTemp			= AfxGetApp()->GetProfileStringA(strSection, "g_fInputCurr", "0.1");
	g_fInputCurr	= (float)atof(strTemp);
	strTemp			= AfxGetApp()->GetProfileStringA(strSection, "g_fInputPower", "17.6");
	g_fInputPower	= (float)atof(strTemp);
	strTemp			= AfxGetApp()->GetProfileStringA(strSection, "g_fInputPF", "0.8");
	g_fInputPF		= (float)atof(strTemp);
	
	m_dataContainer.GetTestSettingData().m_AlarmSettingsData.InitAlarmSettings();
    m_CommSettingsData.InitWatchPaneSetting();

	int iN = m_strListCtrlFile.GetSize();
	// Read File///////////////////////////////////////////
	try
	{
		ReadWatchPaneFile(g_strCurrentPath + "WatchPane.def");
		m_AlarmRingData.LoadFile(g_strCurrentPath + "Alarm\\RingData.dat");
        m_dataContainer.GetTestSettingData().Load(g_strTestSettingFileName);
        m_StatisticLedDataContainer.GetTestSettingData() = m_dataContainer.GetTestSettingData();
		if(g_bUseArea2)
			m_CommSettingsData.ReadFromFile(g_strCurrentPath + "Communication Settings\\CommSettings2.dat");
		else
			m_CommSettingsData.ReadFromFile(g_strCurrentPath + "Communication Settings\\CommSettings.dat");
		InitializeComm();

		// Load region data
		CString strPahtName = g_strCurrentPath + "Region.rgn";
		Region_LoadFile(strPahtName.GetBuffer());

		// Color correction
		NewCorrectColorParaDLL_Init((g_strRectificationPath + "ColorCorrect.dat").GetBuffer(), FALSE);
        ReadFlagFile(g_strCurrentPath + "Flag\\DisplayAndStatistic.flg");
        m_dataContainer.GetDisplayParaNum();
	}
	catch (CException* e)
	{
		e;
		AfxMessageBox("Initialize error!");
	}
	//新增
	char strPath[256];
	int iLen = g_strCurrentPath.GetLength();

	for (int i = 0; i < iLen; i++)
	{
		strPath[i] = g_strCurrentPath.GetAt(i);
	}
	strPath[iLen] = '\0';
	BOOL bEn = FALSE;
	SDCM_DLL_Judge_Init(0.4f,0.4f,bEn);
	SDCM_DLL_Judge_Init_Path(strPath,0.4f,0.4f,FALSE);

	if(!g_bDebug)
	{
		m_bDemo = FALSE;
	}

	//打点仪器地址码设置
	if (m_CommSettingsData.m_bBribe)
	{
		if (g_iHaveBribe == 0)
		{
			g_BribeComm.SetAddress(0xEE, 0xCF);
		}
		else if (g_iHaveBribe == 1)
		{
			g_BribeComm.SetAddress(0xEE,m_CommSettingsData.m_iBribeAddr);
		}
		else
		{
			if (g_iSeleTestLamp == 0)
			{
				g_BribeComm.SetAddress(0xEE,m_CommSettingsData.m_iBribeAddr);
			}
			else
			{
				g_BribeComm.SetAddress(0xEE,m_CommSettingsData.m_iBribeAddr2);
			}
		}
	}
	
    m_StatisticLedDataContainer.toStatisticPara();
    ::PostMessage(m_hWndStatisticGridView, MSG_STATISTIC_GRID_RELIST_DATA, 0, 0);
    ::PostMessage(m_hWndStatisticDisbuteGridView, MSG_STATISTIC_DIS_GRID_RELIST_DATA, 0, 0); 
	/// Begin all test thread
	m_bFirstTime		= TRUE;
	m_bLineHaveMoved	= FALSE;
    g_fUnOnPowLimit		= m_dataContainer.GetTestSettingData().m_fLEDUnOnPow;
    AfxBeginThread(ThreadTest, this);
	m_pThreadGauge		= AfxBeginThread(_ThreadGauge, this);
	AfxBeginThread(_ThreadGaugeTMP, this);
    AfxBeginThread(_ThreadScaner, this);
}

CLAT2000Doc::~CLAT2000Doc()
{
	m_systemSettingsData.WriteRegistry();

	CString strSection = "LAT2000Doc_113";
	AfxGetApp()->WriteProfileString(strSection, "m_strLimitDataFilePathName", g_strTestSettingFileName);
	AfxGetApp()->WriteProfileInt(strSection, "m_iHaveInLampBroadNum", m_iHaveInLampBroadNum);
	AfxGetApp()->WriteProfileInt(strSection, "m_iStartInLampBroad", m_iStartInLampBroad);

	AfxGetApp()->WriteProfileInt(strSection, "g_bInputPower", g_bInputPower);
	CString strTemp;
	strTemp.Format("%.2f",g_fInputVol);
	AfxGetApp()->WriteProfileString(strSection, "g_fInputVol",	strTemp);
	strTemp.Format("%.3f",g_fInputCurr);
	AfxGetApp()->WriteProfileString(strSection, "g_fInputCurr", strTemp);
	strTemp.Format("%.2f",g_fInputPower);
	AfxGetApp()->WriteProfileString(strSection, "g_fInputPower",strTemp);
	strTemp.Format("%.4f",g_fInputPF);
	AfxGetApp()->WriteProfileString(strSection, "g_fInputPF",	strTemp);

	m_dataContainer.GetTestSettingData().Store(g_strLimitDataPath + "LastLimit.dat");
	WriteFlagFile(g_strCurrentPath + "Flag\\DisplayAndStatistic.flg");
}


BOOL CLAT2000Doc::InitializeComm()
{
	// 1.Initialize Hass1200
	CString strSpectrumCalPath = g_strCurrentPath + "Cal\\";
	g_Hass1200Meter.InitMeter(strSpectrumCalPath.GetBuffer(),m_systemSettingsData.m_bDemo);
	g_bDemo = m_systemSettingsData.m_bDemo;

	g_Hass1200Meter.SetBinRange(TEST_BIN_RANGE_1);
	g_Hass1200Meter.SetCommType(COMM_TYPE_USB);
	g_Hass1200Meter.SetCom("COM1");
    ReadCorrectSpectrumFile(g_strCurrentPath + "Cal\\Phcorrect.cor");

	// 2.Test supply
	g_DPSComm.SetDeviceType((DeviceType)m_CommSettingsData.m_iDPSType);
	g_DPSComm.InitializeComm(GetCOM(m_CommSettingsData.m_strCOMDPS));
	// 12.Line Controller
	g_LineControllerComm.Initialize(m_CommSettingsData.m_strLineControllerCOM);
	// 7.Standard supply
	g_WYComm.Initialize(GetCOM(m_CommSettingsData.m_strStandardSupplyCOM), 1);
	g_HLS_200.SetCom(GetCOM(m_CommSettingsData.m_strStandardSupplyCOM));

	// 3.Dynamo meter
	if (!g_PowerMeterComm.Initialize(m_CommSettingsData.m_strCOMPF2010A, g_pDoc->m_CommSettingsData.m_iPFType))
	{
        ShowMessageDialog("功率计初始化失败！");
	}

	// 4.Gauge
	if (m_CommSettingsData.m_bHaveGauge)
	{
		g_GaugeComm.Initialize(m_CommSettingsData.m_strCOMGauge);
	}

	// 5.Intellect controller
	if (m_CommSettingsData.m_bHaveTestChannelController)
	{
		if (m_CommSettingsData.m_iTestChannelControlerType == 1)
		{
			g_SC1000Comm.Initialize(m_CommSettingsData.m_strCOMTestChannelController, 1, FALSE);
		}
		else
		{
			g_TestChannelControlComm.Initialize(m_CommSettingsData.m_strCOMTestChannelController);
		}
	}
	
	if (m_CommSettingsData.m_bHaveHandAuto)
	{
		g_HandAutoComm.Initialize(m_CommSettingsData.m_strHandAutoCOM);
	}

	// 8.Temperature controller
	if (m_CommSettingsData.m_bHaveTemperatureContrller)
	{
		g_FujiTMPComm.InitAddress(m_CommSettingsData.m_ucTemperatureAddress);
		g_FujiTMPComm.Initialize(m_CommSettingsData.m_strCOMTemperature);
	}

	// 9.LED indicator
	if (m_CommSettingsData.m_bHaveLEDIndicator)
	{
		g_IndicatorComm.Initialize(m_CommSettingsData.m_strCOMLEDIndicator);
	}

	// 10.EMS61000-11K
	if (m_CommSettingsData.m_bHaveEMS61000_11K)
	{
		g_EMS61000_11KComm.Initialize(g_strCurrentPath + "Communication Settings\\", m_CommSettingsData.m_strCOMEMS61000_11K);
	}

	// 11.EMS61000-5A
	if (m_CommSettingsData.m_bHaveEMS61000_5A)
	{
		g_EMS61000_5AComm.Initialize(g_strCurrentPath + "Communication Settings\\", m_CommSettingsData.m_strCOMEMS61000_5A);
	}


	// 13.LRA
	if (m_CommSettingsData.m_bHaveLRA)
	{
		g_LRAComm.Initialize(m_CommSettingsData.m_strLRACOM);
	}

	// 14.Thunder relay
	if (m_CommSettingsData.m_bHaveThunderRelay)
	{
		g_ThunderRelayComm.Initialize(m_CommSettingsData.m_strThunderRelayCOM);
	}

    // 15.Bribe
	if (m_CommSettingsData.m_bBribe)
	    g_BribeComm.Initialize(m_CommSettingsData.m_strBribeCOM);

    // 16.Age Power
	if (m_CommSettingsData.m_bfor4A)
	{
		g_DPSAgeComm[0].SetDeviceType(DPS_1005);
		g_DPSAgeComm[0].InitializeComm(GetCOM(m_CommSettingsData.m_strAgePowerCOM[0]));
		g_DPSAgeComm[1].SetDeviceType(DPS_1005);
		g_DPSAgeComm[1].InitializeComm(GetCOM(m_CommSettingsData.m_strAgePowerCOM[1]));
	}

    // 17 Scaner
	if (m_CommSettingsData.m_bHaveScaner)
	{
		g_ScanerComm.Initialize(m_CommSettingsData.m_strScanerCOM);
		g_TSrceenComm.Initialize(1,9600);
		g_ScanerComm.SetDemo(m_systemSettingsData.m_bDemo);
	}


	g_DPSComm.SetDemo(m_systemSettingsData.m_bDemo);
    g_PowerMeterComm.SetDemo(m_systemSettingsData.m_bDemo);
    g_LineControllerComm.SetDemo(m_systemSettingsData.m_bDemo);

	int bChannel[10];
	for(int i = 0; i < 10; i++)
	{
		bChannel[i] = 4;
	}
	g_HandAutoComm.WriteToHandLamp(bChannel);


	return TRUE;
}


void CLAT2000Doc::GetCurrentData()
{
    int iIndex = 0;
    for (int i = 0; i < m_TestContainer.GetLEDCount(); i++)
    {
        iIndex = m_dataContainer.GetSize() - g_iColomnNum * (i / g_iColomnNum + 1) + i % g_iColomnNum;
        if (iIndex >= 0 && iIndex < m_dataContainer.GetSize())
        {
            CLedData & data = m_dataContainer.GetAt(iIndex);
            if (1)
            {
                m_TestContainer.GetLEDData(i) = data;
                LEDState state;
                state.ElectricalTestState = Successful;
                state.SpectrumTestState = Successful;
                m_TestContainer.SetLEDState(i, state);
            }
        }
    }
}

void CLAT2000Doc::ShowMessageDialog(CString strInfo, AlarmType eType)
{
	m_strNoneBorderMsg = strInfo;
	g_LineControllerComm.SetShowLED(2);
	::PostMessageA(m_hWndTestFormView, MSG_SHOW_NONE_BRODER_MESSAGE, eType, 0);
}


BOOL CLAT2000Doc::IsAllDeviceConnected()
{
	// 1.Hass1200
	if (!g_Hass1200Meter.SetShutterOn())
	{
		ShowMessageDialog("A90未连接！");
		return FALSE;
	}

	// 2.Test supply
	RealTimeData data;
	if (!g_DPSComm.GetRealTimeData(data))
	{
		ShowMessageDialog("测试电源未连接！");
		return FALSE;
	}

	// 3.Dynamo meter
	float f1, f2, f3, f4;
	int nAlm = 0;
	if (!g_PowerMeterComm.Read(f1, f2, f3, f4))
	{
		ShowMessageDialog("功率计未连接！");
		return FALSE;
	}

	// 4.Gauge
	if (!g_GaugeComm.Read3(0, f1, f2, f3))
	{
		ShowMessageDialog("表头未连接！");
		return FALSE;
	}

	// 5.Intellect controller
	BOOL b1, b2, b3;
	if (!g_LineControllerComm.ReadLineState(b1, b2, b3))
	{
		ShowMessageDialog("智能控制器未连接！");
		return FALSE;
	}

	// 7.Standard supply
	if (!g_WYComm.GetPower(f1, f2, FALSE) && m_CommSettingsData.m_iStandardSupplyType == 0)
	{
		ShowMessageDialog("标准灯电源未连接！");
		return FALSE;
	}
       
    BOOL Output,Load,Warning;
    if (!g_HLS_200.GetState(Output,Load,Warning) && m_CommSettingsData.m_iStandardSupplyType == 1)
    {
        ShowMessageDialog("标准灯电源未连接！");
        return FALSE;
    }

	// 8.Temperature controller
	if (m_CommSettingsData.m_bHaveTemperatureContrller && !g_FujiTMPComm.ReadTemperature(0, f1, nAlm))
	{
		ShowMessageDialog("温控未连接！");
		return FALSE;
	}

	// 9.LED indicator
	if (!g_IndicatorComm.IsConnected())
	{
		ShowMessageDialog("指示灯未连接！");
		return FALSE;
	}

	// 10.EMS61000-11K
	EMC11KREData data11k;
	if (!g_EMS61000_11KComm.Read(data11k))
	{
		ShowMessageDialog("周波跌落仪器未连接！");
		return FALSE;
	}

	// 11.EMS61000-5A
	EMC5AREData data5A;
	if (!g_EMS61000_5AComm.Read(data5A))
	{
		ShowMessageDialog("雷击仪器未连接！");
		return FALSE;
	}

	return TRUE;
}


BOOL CLAT2000Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)
	g_bhaveSaveFile = TRUE;


	return TRUE;
}



// CLAT2000Doc 序列化

void CLAT2000Doc::Serialize(CArchive& ar)
{
	CString strDev;
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
		m_dataContainer.Serialize(ar);	
		g_bhaveSaveFile = TRUE;
	}
	else
	{
		// TODO: 在此添加加载代码
		m_dataContainer.Serialize(ar);
		::PostMessageA(m_hWndDataContainerGridView, MSG_GRID_RELIST_DATA, 0, 0);
		g_bhaveSaveFile = TRUE;	
        g_strTestSettingFileName = g_strLimitDataPath + "LastLimit.dat";
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CLAT2000Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CLAT2000Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:  strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CLAT2000Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

	// CLAT2000Doc 诊断

#ifdef _DEBUG
	void CLAT2000Doc::AssertValid() const
	{
		CDocument::AssertValid();
	}

	void CLAT2000Doc::Dump(CDumpContext& dc) const
	{
		CDocument::Dump(dc);
	}
#endif //_DEBUG


	// CLAT2000Doc 命令



void CLAT2000Doc::OnMenuSystemSettings()
{
	CSystemSettingsDlg dlg;
	dlg.m_bInputPower		= g_bInputPower;
	dlg.m_strFileName		= m_systemSettingsData.m_strFileName;
	dlg.m_strFileDataNum.Format("%d", m_systemSettingsData.m_iSaveFileDataNum);
	dlg.m_strFilePath		= m_systemSettingsData.m_strFilePath;
	dlg.m_bAutoSave			= m_systemSettingsData.m_bAutoSave;

	dlg.m_bLineNotMove		= m_systemSettingsData.m_bLineNotMove;

    dlg.m_iPrefixInputMode	= m_systemSettingsData.m_iPrefixInputMode;
    dlg.m_iSaveType			= m_systemSettingsData.m_iSaveType;
    dlg.m_bDemo				= m_systemSettingsData.m_bDemo;
	if (IDOK == dlg.DoModal())
	{
		g_bInputPower							= dlg.m_bInputPower;
		if (g_bInputPower)
		{
			g_PowerMeterComm.SetDemo(TRUE);
		}
		else
		{
			g_PowerMeterComm.SetDemo(FALSE);
		}
		m_systemSettingsData.m_bLineNotMove		= dlg.m_bLineNotMove;

		m_systemSettingsData.m_strFileName		= dlg.m_strFileName;
		m_systemSettingsData.m_iSaveFileDataNum = atoi(dlg.m_strFileDataNum);
		m_systemSettingsData.m_strFilePath		= dlg.m_strFilePath;
		m_systemSettingsData.m_bAutoSave		= dlg.m_bAutoSave;

        m_systemSettingsData.m_iPrefixInputMode = dlg.m_iPrefixInputMode;
        m_systemSettingsData.m_iSaveType		= dlg.m_iSaveType;
        m_systemSettingsData.m_bDemo			= dlg.m_bDemo;
		g_bDemo = dlg.m_bDemo;
		m_systemSettingsData.WriteRegistry();
	}
		

	g_EMS61000_11KComm.Initialize(g_strCurrentPath + "Communication Settings\\", m_CommSettingsData.m_strCOMEMS61000_11K);
	g_EMS61000_5AComm.Initialize(g_strCurrentPath + "Communication Settings\\", m_CommSettingsData.m_strCOMEMS61000_5A);
    CString strSpectrumCalPath = g_strCurrentPath + "Cal\\";
	g_Hass1200Meter.InitMeter(strSpectrumCalPath.GetBuffer(),m_systemSettingsData.m_bDemo);
	//   g_Hass1200Meter.InitMeter(m_systemSettingsData.m_bDemo,FALSE);
//	g_Hass1200Meter.SetCalPath(strSpectrumCalPath.GetBuffer());
    g_DPSComm.SetDemo(m_systemSettingsData.m_bDemo);
    g_PowerMeterComm.SetDemo(m_systemSettingsData.m_bDemo);
    g_LineControllerComm.SetDemo(m_systemSettingsData.m_bDemo);
    g_ScanerComm.SetDemo(FALSE);
    ::PostMessageA(m_hWndDataContainerGridView, MSG_GRID_RELIST_DATA, 0, 0);    
	::PostMessage(m_hWndStatisticGridView, MSG_STATISTIC_GRID_RELIST_DATA, 0, 0);
	::PostMessage(m_hWndStatisticDisbuteGridView, MSG_STATISTIC_DIS_GRID_RELIST_DATA, 0, 0);
	return;
}

int g_iT1,g_iT2;
ChannelState *g_channelState;

//合格状态
int g_iChannelOK[10];
CString g_strShowNote1 = "";
CString g_strShowNote2 = "";
CString g_strShowNote3 = "";
CString g_strShowNote4 = "";
CString g_strShowNote5 = "";
CString g_strShowNote6 = "";

BOOL SaveTempData(CString strPathName)
{

    FILE *fp;
    if (fopen_s(&fp , strPathName, "wt"))
    {
        return FALSE;
    }
    else
    {
        fprintf_s(fp,"%s\n", g_strShowNote1);
        fprintf_s(fp,"%s\n", g_strShowNote2);
        fprintf_s(fp,"%s\n", g_strShowNote3);
        fprintf_s(fp,"%s\n", g_strShowNote4);
        fprintf_s(fp,"%s\n", g_strShowNote5);
        fprintf_s(fp,"%s\n", g_strShowNote6);

        fclose(fp);
        return TRUE;
    }

	return TRUE;
}

UINT CLAT2000Doc::ThreadTest(LPVOID pPar)
{
	//测试控制线程
	CLAT2000Doc * pDoc = (CLAT2000Doc *)pPar;
	pDoc->m_TestContainer.ResetLEDState();
	for (int i = 0; i < 10; i++)
	{
		g_iChannelOK[i] = 0;
	}

	AfxBeginThread(_ThreadLightningSurge,	pPar);	//雷击
	AfxBeginThread(_ThreadVoltageDipsAndUP, pPar);	//周波跌落
	AfxBeginThread(_ThreadElectrical,		pPar);	//电参数
	AfxBeginThread(_ThreadSpectrum,			pPar);	//光谱仪采样
	AfxBeginThread(_ThreadSaftJYDZTest,		pPar);
	AfxBeginThread(_ThreadSaftNYYTest,		pPar);
	AfxBeginThread(_ThreadSaftXLDLTest,		pPar);
	AfxBeginThread(_ThreadHandAutoLamp,		pPar);
	
	//事件控制
	CSyncObject * allEvents[9] = {	&pDoc->m_eventElectricalEnd, 
									&pDoc->m_eventLightningSurgeEnd,
									&pDoc->m_eventSpectrumEnd, 
									&pDoc->m_eventVoltageDipsAndUPEnd, 
									&pDoc->m_eventScanerEnd,
									&pDoc->m_eventSaftJYDZEnd,
									&pDoc->m_eventSaftNYYEnd,
									&pDoc->m_eventSaftXLDLEnd,
									&pDoc->m_eventHandAutoEnd};

	CMultiLock multiLock(allEvents, 9);
	CTime timeBegin, timeEnd;
	g_channelState = new ChannelState [10 * 3];
	BOOL bLineNotMove = FALSE; //产线移动标志
	BOOL bR;

	while(1)
	{
		if (pDoc->m_bCloseDocument)
		{
			return 0;
		}
		CString strTemp;

Stop:
		if(pDoc->m_bSetStop)
		{
			pDoc->m_bIsLineControlRunning	= FALSE;//
			continue;
		}
		int iT1 = GetCurrentTime();
		// 1. Prepare to start test
		pDoc->m_iWaitRemainSeconds		= -1;   //
		pDoc->m_bIsLineControlRunning	= FALSE;//
		pDoc->m_lineState				= Free;
		
		pDoc->m_eventTest.Lock();
		pDoc->m_eventOneLEDON.ResetEvent();   
		pDoc->m_eventOneLEDSpectrumOK.ResetEvent();
		pDoc->m_bIsLineControlRunning = TRUE;
		
		timeBegin = CTime::GetCurrentTime();

		if (pDoc->m_systemSettingsData.m_iTestHaveScanedMode && pDoc->m_CommSettingsData.m_bHaveScaner)
		{
			if (pDoc->m_TestContainer.GetRowLEDSNCount() == 0)
			{
				AfxMessageBox("未扫码,请扫码后再测试!");
				pDoc->OnMenuStop();
				continue;
			}
		}
		strTemp.Format("Read1:%d",GetCurrentTime() - iT1);
		g_strShowNote1 = g_strShowNote1 + strTemp;
		iT1 = GetCurrentTime();

		// 2. Check before test
		BOOL bInPosition;	 //产线到位标志
		BOOL bManualStopped; //紧急停止标志
		BOOL bLampTooHigh;   //产线过高标志
		if(g_LineControllerComm.ReadLineState(bInPosition, bManualStopped, bLampTooHigh))
		{
			if (bManualStopped && !pDoc->m_systemSettingsData.m_bLineNotMove)
			{
				g_LineControllerComm.SetLinePause();
				pDoc->ShowMessageDialog("产线紧急停止，请取消紧急停止后再测试!",AT_MANUAL_STOP);
				pDoc->OnMenuStop();
				goto Stop;
			}

			if(bLampTooHigh)
			{
				// 2.1 Clear LineControl State
				g_LineControllerComm.ClearAllState();
				g_LineControllerComm.ReadLineState(bInPosition, bManualStopped, bLampTooHigh);
				if(bLampTooHigh)
				{
					g_LineControllerComm.ClearAllState();
					g_LineControllerComm.ReadLineState(bInPosition, bManualStopped, bLampTooHigh);
					if (bLampTooHigh)
					{
						g_LineControllerComm.ClearAllState();
					}						
				}
			}
		}
		else
		{
			pDoc->ShowMessageDialog("读取产线状态失败，请检验产线是否正常运行!");
			pDoc->OnMenuStop();
			goto Stop;
		}
		g_LineControllerComm.SetShowLED(1);
	

		// 3. Set parameter for some device
		// 3.1 Burn in
		// 3.2 Power meter range
		iT1 = GetCurrentTime();
		bR = g_PowerMeterComm.SetRange(PM_URange_600V, PM_IRange_20A, pDoc->m_dataContainer.GetTestSettingData().m_iRangeCF);
		// 5. Prepare container and move production line
		pDoc->m_TestContainer.SetTestChannel(pDoc->m_dataContainer.GetTestSettingData().m_pbTestChannel);

		strTemp.Format("SetRange:%d",GetCurrentTime() - iT1);
		g_strShowNote1 = g_strShowNote1 + strTemp;
		iT1 = GetCurrentTime();

		if((pDoc->m_TestContainer.IsAllLEDTest() && pDoc->m_TestContainer.HaveLastRowLEDScaned()) 
			|| (!pDoc->m_TestContainer.IsLastRowNeedTest() && pDoc->m_TestContainer.HaveLastRowLEDScaned()) 
			|| !bInPosition
			|| (pDoc->m_systemSettingsData.m_iTestHaveScanedMode
				&& (!pDoc->m_TestContainer.IsLastRowNeedTest() || (pDoc->m_TestContainer.IsLastRowNeedTest()
				&& pDoc->m_TestContainer.IsAllLEDTest())))
			|| (pDoc->m_dataContainer.GetTestSettingData().m_bTestAutoHand && !pDoc->m_bFirstTime)
			)
		{
			bLineNotMove = TRUE;
			if (!pDoc->m_systemSettingsData.m_bLineNotMove)
			{
				if (!pDoc->m_bLineHaveMoved)
				{
					if (pDoc->m_dataContainer.GetTestSettingData().m_bTestAutoHand)
					{
						//读取到机械手允许运行信号后开始将产线移动一步
						BOOL bAllow = FALSE;
						while(1)
						{
							bR = g_HandAutoComm.ReadHandState(bAllow);
							if (bAllow)
							{
								break;
							}
							Sleep(100);
							if (pDoc->m_bSetStop)
							{
								pDoc->OnMenuStop();
								goto Stop;
							}
						}

						//产线移动 清到位标志 保证机械手不移动
						bR = g_HandAutoComm.WriteToHandInpos(FALSE);
					}
					

					pDoc->m_lineState = Stepping;
					bInPosition = bManualStopped = bLampTooHigh = FALSE;
					//将老化线移动一步
					bR = g_LineControllerComm.MoveLineOneStep();
					if (g_LineControllerComm.ReadLineState(bInPosition, bManualStopped, bLampTooHigh))
					{
						if (bLampTooHigh) 
						{
							bR = g_LineControllerComm.SetLinePause();
							pDoc->ShowMessageDialog("灯过高，请调整检测装置高度后再测试!", 
								AT_LAMP_TOO_HIGH);
							pDoc->OnMenuStop();
							goto Stop;
						}

						if (bManualStopped)
						{
							bR = g_LineControllerComm.SetLinePause();
							pDoc->ShowMessageDialog("产线紧急停止，请取消紧急停止后再测试!", 
								AT_MANUAL_STOP);
							pDoc->OnMenuStop();
							//if bInPosition == 0, Linecontrol haveMove One Step
							if (0 == bInPosition)
							{
								pDoc->m_bLineHaveMoved = TRUE;
							}
							goto Stop;
						}
					}
					pDoc->m_bLineHaveMoved = TRUE;
				}			
			}
		}
		else  
		{
			pDoc->m_TestContainer.ResetCurrentRow();				
		}
		
		strTemp.Format("Move:%d",GetCurrentTime() - iT1);
		g_strShowNote1 = g_strShowNote1 + strTemp;
		iT1 = GetCurrentTime();

        //移动前将所有通道关闭 AllChannelOff
		if (pDoc->m_CommSettingsData.m_bHaveLRA)
		{
			bR = g_LRAComm.SwitchAllChannel(FALSE);
		}
		if (pDoc->m_CommSettingsData.m_bBribe)
		{
			bR = g_BribeComm.SwitchAllChannel(FALSE);
		}
        // 6. Wait production line in position
        int iWaitms = 0;
        bInPosition = bManualStopped = bLampTooHigh = FALSE;
        while (!bInPosition)
        {
			if (pDoc->m_bSetStop)
			{
				// User stop test
				pDoc->OnMenuStop();
				goto Stop;
			}
            g_LineControllerComm.ReadLineState(bInPosition, bManualStopped, bLampTooHigh);
            if (bLampTooHigh)
            {
				bR = g_LineControllerComm.SetLinePause();
				pDoc->ShowMessageDialog("灯过高，请调整检测装置高度后再测试!",AT_LAMP_TOO_HIGH);
                pDoc->OnMenuStop();
                bInPosition = FALSE;
				pDoc->m_bLineHaveMoved = FALSE;
                break;
            }
            Sleep(100);
            iWaitms += 100;
            if (iWaitms > 10000)
            {
                pDoc->ShowMessageDialog("等待产线到位超时，请检查产线是否有故障!");
                pDoc->OnMenuStop();
				pDoc->m_bLineHaveMoved = FALSE;
                break;
            }
        }
        if (!bInPosition)
        {
			pDoc->m_bInposition = FALSE;
            Sleep(1000);
            goto Stop;
        }
		if(bInPosition)
		{
			pDoc->m_bInposition = TRUE;
		}
		g_iT1 = GetCurrentTime();
		strTemp.Format("Wait:%d",GetCurrentTime() - iT1);
		g_strShowNote1 = g_strShowNote1 + strTemp;
		iT1 = GetCurrentTime();

		// be in position 到位了 且已扫码或者是直接测试 或者机械手上灯到位了
		if (pDoc->m_TestContainer.IsAllLEDTest()
			&& ((pDoc->m_TestContainer.HaveLastRowLEDScaned() && !pDoc->m_systemSettingsData.m_iTestHaveScanedMode) || pDoc->m_systemSettingsData.m_iTestHaveScanedMode) 
			|| pDoc->m_iHaveInLampBroadNum >= (atoi(g_pDoc->m_CommSettingsData.m_strHandAutoRange1))
			|| !pDoc->m_dataContainer.GetTestSettingData().m_bTestAutoHand )
		{
			pDoc->m_TestContainer.StartNewRow();
		}
		else
		{
			//  Production line is set in position by the last test 
			// or the test is started by the first time and no led is tested
		}
		// Have moved  in position Add SN,Update Indicator
		if ((!pDoc->m_bFirstTime) && pDoc->m_bLineHaveMoved)
		{
			if(pDoc->m_dataContainer.GetTestSettingData().m_bTestAutoHand)
			{
				if (g_pDoc->m_iHaveInLampBroadNum > (atoi(g_pDoc->m_CommSettingsData.m_strHandAutoRange1)))
				{
					pDoc->m_systemSettingsData.m_iCurrentLEDID += pDoc->m_TestContainer.GetLEDColumnSize();
				}
			}
			else
			{
				pDoc->m_systemSettingsData.m_iCurrentLEDID += pDoc->m_TestContainer.GetLEDColumnSize();
			}
			
			pDoc->m_bLineHaveMoved = FALSE;
			bLineNotMove = FALSE;
			pDoc->m_TestContainer.RemoveLEDDownRow();
            pDoc->AddBoardID();
		}
		
		pDoc->m_bFirstTime = FALSE;

		//指示灯控制
		// 7. Production line is moved, update indicator color data
		CArray<int, int>m_IndicorPos;
		m_IndicorPos.RemoveAll();
		BOOL bMoveLineHaveAdd = FALSE;

		for (int i = 0 ; i < pDoc->m_bNotMoveLine.GetSize(); i += g_iColomnNum)
		{
			if (bMoveLineHaveAdd)
			{
				if (pDoc->m_bNotMoveLine.GetAt(i) == FALSE)
				{
					bMoveLineHaveAdd = FALSE;
				}
				continue;
			}
			if (bMoveLineHaveAdd == FALSE)
			{
				if (pDoc->m_bNotMoveLine.GetAt(i) == TRUE)
				{
					bMoveLineHaveAdd = TRUE;
				}
			}
			m_IndicorPos.Add(i);
			if (m_IndicorPos.GetSize() >= atoi(pDoc->m_CommSettingsData.m_strIndicatorRange) + g_iRowNum + bLineNotMove)
			{
				break;
			}
		}
		if (bLineNotMove)
		{
			if (m_IndicorPos.GetSize())
			{
				m_IndicorPos.RemoveAt(0);
			}
		}
		int iHaveTestRow; //已测量的行数
		iHaveTestRow = pDoc->m_dataContainer.GetSize() / pDoc->m_TestContainer.GetLEDColumnSize();
	//	CString strTemp;
	//	strTemp.Format("%d %d %d",iHaveTestRow, pDoc->m_TestContainer.GetLEDCount(),pDoc->m_TestContainer.GetLEDColumnSize());
	//	AfxMessageBox(strTemp);
		if (iHaveTestRow > atoi(pDoc->m_CommSettingsData.m_strHandAutoRange2))
		{
			for (int j = 0; j < 10; j ++)
			{
				int iIndex = (pDoc->m_dataContainer.GetSize() - atoi(pDoc->m_CommSettingsData.m_strHandAutoRange2) * pDoc->m_TestContainer.GetLEDColumnSize())  + j;
				CLedData & data = pDoc->m_dataContainer.GetAt(iIndex);
				int iTypeFail = 0;
				pDoc->m_dataContainer.GetTestSettingData().IsQulified(data,iTypeFail);
				g_iChannelOK[j] = iTypeFail;
			}
		}

		int iColorDataIndex;
		int iTempIndex = 0;
		for (int i = 0; i <  g_iRowNum; i++)
		{
			if (m_IndicorPos.GetSize() - 1 < atoi(pDoc->m_CommSettingsData.m_strCOMLEDIndicator) + i)
			{
				for (int j = 0; j < 10; j ++)
				{
					g_channelState[i * 10 + j] = CHANNEL_OFF; 
				}
			}
			else
			{
				iColorDataIndex =  m_IndicorPos.GetAt(atoi(pDoc->m_CommSettingsData.m_strCOMLEDIndicator) + i);
				for (int j = 0; j < 10; j ++)
				{
					iTempIndex = iColorDataIndex + j;
					if (iTempIndex >= 0 && iTempIndex < pDoc->m_IndicatorColorData.GetCount() && j < g_iColomnNum)
					{
						g_channelState[i * 10 + j] = pDoc->m_IndicatorColorData[iTempIndex];
					}
					else
					{
						g_channelState[i * 10 + j] = CHANNEL_OFF;
					}
				}  
			}
		}
		if (pDoc->m_CommSettingsData.m_bHaveLEDIndicator)
		{
			bR = g_IndicatorComm.SetAllChannelState(g_channelState);
		}
				
		// 8.1 Set LRA channels 
		BOOL bLRAChannel[LRA_CHANNEL_NUM];
		if (pDoc->m_CommSettingsData.m_bHaveLRA)
		{
			for (int i = 0; i < LRA_CHANNEL_NUM; i++)
			{
				// g_iColomnNum must be equal to LRA_CHANNEL_NUM
				bLRAChannel[i] = CHANNEL_RED == g_channelState[20 + i] ? TRUE : FALSE;
			}
			bR = g_LRAComm.SetChannel(bLRAChannel);
		}
		
		//在此增加控制机械手各夹具合格不合格标志
		//bR = g_HandAutoComm.SetChannel(bLRAChannel);

		// 8.2 Set Reiveter channels   Reivetercomm similar to LRAcomm
		if (m_IndicorPos.GetSize() - 1 < atoi(pDoc->m_CommSettingsData.m_strBribeRange))
		{
			for (int j = 0; j < LRA_CHANNEL_NUM; j ++)
			{
				bLRAChannel[j] = FALSE; 
			}
		}
		else
		{
			iColorDataIndex =  m_IndicorPos.GetAt(atoi(pDoc->m_CommSettingsData.m_strBribeRange));
			for (int j = 0; j < LRA_CHANNEL_NUM; j ++)
			{
				iTempIndex = iColorDataIndex + j;
				if (iTempIndex >= 0 && iTempIndex < pDoc->m_IndicatorColorData.GetCount() && j < g_iColomnNum)
				{
					bLRAChannel[j] = CHANNEL_RED == pDoc->m_IndicatorColorData[iTempIndex] ? TRUE : FALSE;
				}
				else
				{
					bLRAChannel[j] = FALSE;
				}
			}

			if(pDoc->m_CommSettingsData.m_bBribe)
			{
				//打点机选择
				BOOL bBribeChannel[LRA_CHANNEL_NUM];
				for (int i = 0; i < LRA_CHANNEL_NUM; i ++)
				{
					if (i % 2 == 0)
					{
						bBribeChannel[i] = bLRAChannel[i];
					}
					else
					{
						bBribeChannel[i] = FALSE;
					}
				}
				bR = g_BribeComm.SetChannel(bBribeChannel);  
				Sleep(100);
				for (int i = 0; i < LRA_CHANNEL_NUM; i ++)
				{
					if (i % 2 == 1)
					{
						bBribeChannel[i] = bLRAChannel[i];
					}
					else
					{
						bBribeChannel[i] = FALSE;
					}
				}
				bR = g_BribeComm.SetChannel(bBribeChannel);
			}
		}

		// 9. Start all child thread, this event will manual reset by every child thread
		pDoc->m_lineState = Testing;
		bR = pDoc->m_eventStartOne.SetEvent();

		// 10. Wait all child one circle test end
		int iLock = multiLock.Lock();

  		strTemp.Format("Test:%d",GetCurrentTime() - iT1);
		g_strShowNote2 = g_strShowNote2 + strTemp;
		iT1 = GetCurrentTime();
	      //  Auto save data(Save By Day)
        if (pDoc->m_systemSettingsData.m_bAutoSave)
        {
            if (!pDoc->m_systemSettingsData.m_iSaveType)
            {
            }
            else
            {
                CString strPathName;   
                CTime tNow = CTime::GetCurrentTime();
                if (tNow.GetDay() != pDoc->m_LastTime.GetDay() &&  pDoc->m_dataContainer.GetSize() >= 1)
                {
                    if (!pDoc->m_systemSettingsData.m_iPrefixInputMode)
                    {
                        strPathName = pDoc->m_systemSettingsData.m_strFilePath + "\\" + 
                            pDoc->m_systemSettingsData.m_strFileName + pDoc->m_LastTime.Format("%Y-%m-%d %H-%M-%S.lat2000-everfine");// %H-%M-%S
                    }
                    else
                    {
                        strPathName = pDoc->m_systemSettingsData.m_strFilePath + "\\" + 
                            pDoc->m_dataContainer.GetTestSettingData().m_strLedModel + pDoc->m_LastTime.Format("%Y-%m-%d %H-%M-%S.lat2000-everfine");// %H-%M-%S
                    }
                    pDoc->m_dataContainer.SaveFile(strPathName);
					strPathName.Replace(".lat2000-everfine","");
					g_strPathNameAuto = strPathName+".csv";
					::PostMessageA(pDoc->m_hWndDataContainerGridView, MSG_SAVE_CSV_DATA, 0, 0);
					pDoc->m_dataContainer.RemoveAllData();
                }
                pDoc->m_LastTime =  CTime::GetCurrentTime();
            }
        }

		// 11. One circle test end, add test data and indicator color data to data container 
		if ((pDoc->m_TestContainer.IsAllLEDTest() && 
			((pDoc->m_TestContainer.HaveLastRowLEDScaned() && !pDoc->m_systemSettingsData.m_iTestHaveScanedMode)
			|| pDoc->m_systemSettingsData.m_iTestHaveScanedMode)))
		{
			//11.2 Add data to test container
			pDoc->m_dataContainer.SetTestTime(CTime::GetCurrentTime());
			int iHaveTestNum;//已经测量的列数
			if(pDoc->m_CommSettingsData.m_bHaveScaner)
			{
				iHaveTestNum = pDoc->m_TestContainer.GetRowLEDSN(pDoc->m_TestContainer.GetCurrentTestRow()).GetSNNum();
			}
			else
			{
				iHaveTestNum = pDoc->m_TestContainer.GetLEDColumnSize();
			}
			for (int i = 0; i < pDoc->m_TestContainer.GetLEDColumnSize(); i++)
			{
				if(i >= iHaveTestNum)
				{
					pDoc->m_bNotMoveLine.InsertAt(i,bLineNotMove); 
					pDoc->m_IndicatorColorData.InsertAt(i, CHANNEL_OFF);
				}
				else
				{
					if (pDoc->m_TestContainer.GetLEDState(0, i).IsTested())
					{
						CLedData & data = pDoc->m_TestContainer.GetLEDData(0, i);
						data.m_ulID = (ULONG)pDoc->m_systemSettingsData.m_iCurrentLEDID + i;
						data.m_strLedModel = pDoc->m_dataContainer.GetTestSettingData().m_strLedModel;
						data.m_bNotMoveLine = bLineNotMove;
						if (pDoc->m_CommSettingsData.m_bHaveScaner)
						{
							RowLEDSN rowLEDSN;
							rowLEDSN = pDoc->m_TestContainer.GetRowLEDSN(pDoc->m_TestContainer.GetCurrentTestRow());
							data.m_strSN = rowLEDSN.GetLEDSN(i);
						}

						pDoc->m_dataContainer.InsertData(0, i, data);
						pDoc->m_bNotMoveLine.InsertAt(i,data.m_bNotMoveLine); 
						if (!pDoc->m_TestContainer.GetLEDState(0, i).IsSuccessful())
						{
							pDoc->m_IndicatorColorData.InsertAt(i, CHANNEL_OFF);
							pDoc->m_testStatisticsData.StatisticsData(pDoc->m_dataContainer, i, DT_TESTFAIL);
							continue;
						}

						if (data.IsLEDON())
						{
							int iTypeFail = 0;
							if (pDoc->m_dataContainer.GetTestSettingData().IsQulified(data,iTypeFail))
							{
								pDoc->m_IndicatorColorData.InsertAt(i, CHANNEL_GREEN);
								pDoc->m_testStatisticsData.StatisticsData(pDoc->m_dataContainer, i, DT_LEDQ);
							}
							else
							{
								pDoc->m_IndicatorColorData.InsertAt(i, CHANNEL_RED);
								pDoc->m_testStatisticsData.StatisticsData(pDoc->m_dataContainer, i, DT_LEDUNQ);                                
							}
						}
						else
						{
							pDoc->m_IndicatorColorData.InsertAt(i, CHANNEL_RED);
							pDoc->m_testStatisticsData.StatisticsData(pDoc->m_dataContainer, i, DT_LEDUNON); 
						}
					}
					else
					{
						pDoc->m_IndicatorColorData.InsertAt(i, CHANNEL_OFF);
					}
				}
			} 
			if (pDoc->m_IndicatorColorData.GetCount() > 2000)
			{
				pDoc->m_IndicatorColorData.SetSize(2000);
                pDoc->m_bNotMoveLine.SetSize(2000);
			}
		}
		else
		{
			// 11.1 Production line is not all tested 
			// or the test is started by the first time and no led is tested
		}

		// 12. Auto save data(Save By Num)
		g_bhaveSaveFile = FALSE;
        if (pDoc->m_systemSettingsData.m_bAutoSave)
        {
            if (!pDoc->m_systemSettingsData.m_iSaveType)
            {
                if (pDoc->m_dataContainer.GetSize() >= pDoc->m_systemSettingsData.m_iSaveFileDataNum)
                {
                    CString strPathName;
                    CTime tNow = CTime::GetCurrentTime();
                    if (!pDoc->m_systemSettingsData.m_iPrefixInputMode)
                    {
                        strPathName = pDoc->m_systemSettingsData.m_strFilePath + "\\" + 
                            pDoc->m_systemSettingsData.m_strFileName + tNow.Format("%Y-%m-%d %H-%M-%S.lat2000-everfine");// %H-%M-%S
                    }
                    else
                    {
                        strPathName = pDoc->m_systemSettingsData.m_strFilePath + "\\" + 
                            pDoc->m_dataContainer.GetTestSettingData().m_strLedModel + tNow.Format("%Y-%m-%d %H-%M-%S.lat2000-everfine"); // %H-%M-%S
                    }
                    pDoc->m_dataContainer.SaveFile(strPathName);
					strPathName.Replace(".lat2000-everfine","");
					g_strPathNameAuto = strPathName+".csv";
					::PostMessageA(pDoc->m_hWndDataContainerGridView, MSG_SAVE_CSV_DATA, 0, 0);

                    pDoc->m_dataContainer.RemoveAllData();
                }
            }
        }

		::PostMessageA(pDoc->m_hWndDataContainerGridView, MSG_GRID_RELIST_DATA, 0, 0);

		// 13. Auto backup data
		pDoc->m_dataContainer.SaveFile(g_strHistoryDataPath + "AutoManage.dat");
		// 13. Check if test time is too short
		if (g_pDoc->m_iHaveInLampBroadNum >= (atoi(g_pDoc->m_CommSettingsData.m_strHandAutoRange1)))
			pDoc->m_lineState = WaitTime;
		timeEnd = CTime::GetCurrentTime();
		CTimeSpan span = timeEnd - timeBegin;
		while (span.GetTotalSeconds() < pDoc->m_dataContainer.GetTestSettingData().m_iTestMinSeconds)
		{
			timeEnd = CTime::GetCurrentTime();
			span = timeEnd - timeBegin;
			pDoc->m_iWaitRemainSeconds = pDoc->m_dataContainer.GetTestSettingData().m_iTestMinSeconds - (int)span.GetTotalSeconds();
			if (pDoc->m_bSetStop)
			{
				g_LineControllerComm.SetLinePause();
				pDoc->OnMenuStop();
				break;
			}
		}
  		strTemp.Format("Save:%d",GetCurrentTime() - iT1);
		g_strShowNote3 = g_strShowNote3 + strTemp;
		iT1 = GetCurrentTime();

		SaveTempData(g_strCurrentPath + "History Data\\Time.dat");
	}

	::PostMessageA(pDoc->m_hWndTestFormView, MSG_TEST_ENDED, 0, 0);

	return 0;
}

UINT CLAT2000Doc::_ThreadSpectrum(LPVOID pPar)
{
	//光谱仪测试
	CLAT2000Doc * pDoc = (CLAT2000Doc *)pPar;

	while(1)
	{
		int iNeedB = pDoc->m_CommSettingsData.m_iJydzLedTestRange;
		if (pDoc->m_eventStartOne.Lock())
		{
			if((!pDoc->m_dataContainer.GetTestSettingData().m_bTestSaft || pDoc->m_iHaveBoradSaftR >= iNeedB)
				|| pDoc->m_iHaveInLampBroadNum >= (atoi(pDoc->m_CommSettingsData.m_strHandAutoRange1))
				|| !pDoc->m_dataContainer.GetTestSettingData().m_bTestAutoHand)
			{
				if (!pDoc->m_TestContainer.CurrentTestRowIsScaned() && pDoc->m_CommSettingsData.m_bHaveScaner)
				{
					pDoc->m_TestContainer.SetCurrentRowNeedTest(FALSE); 
					goto SpeEnd;
				}
				else
				{
					pDoc->m_TestContainer.SetCurrentRowNeedTest(TRUE);
				}
				// 1.Start test
				pDoc->m_bIsSpectrumRunning = TRUE;

				// 2.Sample dark AD
				if (pDoc->m_CommSettingsData.m_iTestChannelControlerType == 1)
				{
					g_SC1000Comm.SwitchAllLamp(FALSE);	// Turn off all lamp
				}
				else
				{
					g_TestChannelControlComm.SwitchAllChannel(FALSE);					
				}
				Sleep((DWORD)pDoc->m_dataContainer.GetTestSettingData().m_fWarmUpTimems);
				float * pAD = new float[g_Hass1200Meter.GetCCDPixNum()];
				float * pDarkAD = new float[g_Hass1200Meter.GetCCDPixNum()];
				ASSERT(NULL != pAD && NULL != pDarkAD);
				g_Hass1200Meter.SetShutterOn();
				g_Hass1200Meter.SetIntTime(g_pDoc->m_dataContainer.GetTestSettingData().m_fIntegralTimems);
				Sleep(100);		// Wait 
				g_Hass1200Meter.SampleAD(pDarkAD);
				BOOL bR;
				if (pDoc->m_TestContainer.GetCurrentLEDIndex() == -1)
				{
				}
				else
				{
					// Get dark AD OK
					pDoc->m_eventOneLEDSpectrumOK.SetEvent();
				
					while(1)
					{
						if (pDoc->m_bSetStop)
						{
							break;
						}

						// a.Wait LED ON
						bR = pDoc->m_eventOneLEDON.Lock();

						// b.Get LED spectrum data
						BOOL bGetDark = FALSE;
						if (!g_bDemo)
						{
	sample:					bR = g_Hass1200Meter.SampleAD(pAD);
							if (bR)
							{
								// auto integ
								float fIp;
								for (int m = 0; m < g_Hass1200Meter.GetCCDPixNum(); m++)
								{
									if (m == 0)
									{
										fIp = pAD[m];
									}
									else
									{
										if (fIp < pAD[m])
										{
											fIp = pAD[m];
										}
									}
								}
								if (g_pDoc->m_dataContainer.GetTestSettingData().m_fIntegralTimems > 0.1f
									&& fIp > 65535 * 0.92f)
								{
									g_pDoc->m_dataContainer.GetTestSettingData().m_fIntegralTimems *=
										40000 / fIp;
									if (g_pDoc->m_dataContainer.GetTestSettingData().m_fIntegralTimems < 0.1f)
									{
										g_pDoc->m_dataContainer.GetTestSettingData().m_fIntegralTimems = 0.1f;
									}
									else
									{
										if (g_pDoc->m_dataContainer.GetTestSettingData().m_fIntegralTimems > 10.0f)
										{
											g_pDoc->m_dataContainer.GetTestSettingData().m_fIntegralTimems = (float)(int)(g_pDoc->m_dataContainer.GetTestSettingData().m_fIntegralTimems + 0.5f);
										}
									}
									g_Hass1200Meter.SetIntTime(g_pDoc->m_dataContainer.GetTestSettingData().m_fIntegralTimems);
									bGetDark = TRUE;
									goto sample;
								}
								if (bGetDark == TRUE)
								{
									if (pDoc->m_CommSettingsData.m_iTestChannelControlerType == 1)
									{
										g_SC1000Comm.SwitchAllLamp(FALSE);	// Turn off all lamp
									}
									else
									{
										g_TestChannelControlComm.SwitchAllChannel(FALSE);					
									}
									Sleep(100);		// Wait 
									g_Hass1200Meter.SampleAD(pDarkAD);
									if (pDoc->m_CommSettingsData.m_iTestChannelControlerType == 1)
									{
										g_SC1000Comm.SwitchChannel(g_pDoc->m_TestContainer.GetCurrentLEDIndex());
									}
									else
									{
										g_TestChannelControlComm.SwitchOneChannel(g_pDoc->m_TestContainer.GetCurrentLEDIndex(), TRUE);
									}
									Sleep(100);
									CLedData &data = pDoc->m_TestContainer.GetCurrentLEDData();
									data.m_fFrequencyHz = g_pDoc->m_dataContainer.GetTestSettingData().m_fTestFrquencyHz;
									if(g_bInputPower)
									{
										bR = TRUE;
										data.m_fVoltageV = g_fInputVol;
										data.m_fCurrentA = g_fInputCurr;
										data.m_fPowerW   = g_fInputPower;
										data.m_fPowerFactor = g_fInputPF;
									}
									else
									{
										bR = g_PowerMeterComm.Read(data.m_fVoltageV, data.m_fCurrentA, data.m_fPowerW, data.m_fPowerFactor);
										if (!bR)
										{
											Sleep(200);
											bR = g_PowerMeterComm.Read(data.m_fVoltageV, data.m_fCurrentA, data.m_fPowerW, data.m_fPowerFactor);
										}
									}
									pDoc->m_TestContainer.GetCurrentLEDState().ElectricalTestState = (bR ? Successful : Failed);
									pDoc->m_TestContainer.SetCurrentLEDUpdated(FALSE);
									g_pDoc->m_dataContainer.GetTestSettingData().Store(g_strTestSettingFileName);
								}
								// calc color
								if (g_bCorrectPh)
								{
									g_Hass1200Meter.CalcColor(0.2f, g_pDoc->m_dataContainer.GetTestSettingData().m_fIntegralTimems,
										g_pDoc->m_dataContainer.GetTestSettingData().m_fIntegralTimems, pDarkAD, pAD,
										g_pDoc->m_TestContainer.GetCurrentLEDData().m_ColorData);
									float fWL[4096], fPL[4096];
									int iNum = int((g_Hass1200Meter.GetWL_Range2() - g_Hass1200Meter.GetWL_Range1()) / 0.2f + 1 + 0.5f);
									float fMaxPh;
									for (int i = 0; i < iNum; i ++)
									{
										g_pDoc->m_TestContainer.GetCurrentLEDData().m_ColorData.m_fPL[i] *=  g_fCorrectPhK0dot2nm[i];
                                        
										if (i == 0)
										{
											fMaxPh = g_pDoc->m_TestContainer.GetCurrentLEDData().m_ColorData.m_fPL[i];
										}
										else
										{
											if (fMaxPh < g_pDoc->m_TestContainer.GetCurrentLEDData().m_ColorData.m_fPL[i])
											{
												fMaxPh = g_pDoc->m_TestContainer.GetCurrentLEDData().m_ColorData.m_fPL[i];
											}
										}
									}

									for (int i = 0; i < iNum; i ++)
									{
										g_pDoc->m_TestContainer.GetCurrentLEDData().m_ColorData.m_fPL[i] /=  (fMaxPh > 0 ? fMaxPh : 1);

										if (i % 5 == 0)
										{
											fWL[i / 5]  = g_Hass1200Meter.GetWL_Range1() + i / 5;
											fPL[i / 5] = g_pDoc->m_TestContainer.GetCurrentLEDData().m_ColorData.m_fPL[i];
										}
									}

									iNum = int((g_Hass1200Meter.GetWL_Range2() - g_Hass1200Meter.GetWL_Range1()) / 1.0f + 1 + 0.5f);
									COLOR_PARA para;
									CC_CalcColor(fWL, fPL, iNum, para, FALSE, 0.4f, 0.4f);
									
									pDoc->m_TestContainer.GetCurrentLEDData().m_ColorData.m_fCIEx = para.fx;
									pDoc->m_TestContainer.GetCurrentLEDData().m_ColorData.m_fCIEy = para.fy;
									pDoc->m_TestContainer.GetCurrentLEDData().m_ColorData.m_fCIEu_ = para.fu;
									pDoc->m_TestContainer.GetCurrentLEDData().m_ColorData.m_fTc = para.fCCT;
									pDoc->m_TestContainer.GetCurrentLEDData().m_ColorData.m_fduv = para.dC;
									pDoc->m_TestContainer.GetCurrentLEDData().m_ColorData.m_fLp = para.fLp;
									pDoc->m_TestContainer.GetCurrentLEDData().m_ColorData.m_fHW = para.fHW;
									pDoc->m_TestContainer.GetCurrentLEDData().m_ColorData.m_fLd = para.fLd;
									pDoc->m_TestContainer.GetCurrentLEDData().m_ColorData.m_fLav = para.fLav;
									pDoc->m_TestContainer.GetCurrentLEDData().m_ColorData.m_fPur = para.fPur;
									pDoc->m_TestContainer.GetCurrentLEDData().m_ColorData.m_fRR = para.fRR;
									pDoc->m_TestContainer.GetCurrentLEDData().m_ColorData.m_fGR = para.fGR;
									pDoc->m_TestContainer.GetCurrentLEDData().m_ColorData.m_fBR = para.fBR;
									pDoc->m_TestContainer.GetCurrentLEDData().m_ColorData.m_fRa = para.fRa;
									for (int i = 0; i < 15; i ++)
									{
										pDoc->m_TestContainer.GetCurrentLEDData().m_ColorData.m_fRi[i] = para.fRi[i];
									}
								}
								else
								{
									g_Hass1200Meter.CalcColor(0.2f, g_pDoc->m_dataContainer.GetTestSettingData().m_fIntegralTimems,
										g_pDoc->m_dataContainer.GetTestSettingData().m_fIntegralTimems, pDarkAD, pAD,
										g_pDoc->m_TestContainer.GetCurrentLEDData().m_ColorData);
								}
								// Luminosity correction								
								Haas1200CorrectColor(g_pDoc->m_TestContainer.GetCurrentLEDData().m_ColorData);
								int iCurrentIndex = g_pDoc->m_TestContainer.GetCurrentLEDIndex();
								float fK = g_pDoc->m_dataContainer.GetTestSettingData().m_pfLuminosityK[iCurrentIndex];
								g_pDoc->m_TestContainer.GetCurrentLEDData().m_ColorData.m_fPh *= fK;

								g_pDoc->m_TestContainer.GetCurrentLEDState().SpectrumTestState = Successful;
							}
							else
							{
								g_pDoc->m_TestContainer.GetCurrentLEDState().SpectrumTestState = Failed;
							}
						
							g_pDoc->m_TestContainer.SetCurrentLEDUpdated(FALSE);
						}
						else
						{
							bR = g_SpectrumDemoComm.Sample(pDoc->m_TestContainer.GetCurrentLEDData());

							pDoc->m_TestContainer.GetCurrentLEDState().SpectrumTestState = Successful;
							g_pDoc->m_TestContainer.SetCurrentLEDUpdated(FALSE);
						}
						///////////////////////////////////////////////////////////////////////////////////////////////////////////////
						//2014.5.5 增加SDCM start
						SDCM_DLL_Calc(pDoc->m_TestContainer.GetCurrentLEDData().m_ColorData.m_fCIEx, 
							pDoc->m_TestContainer.GetCurrentLEDData().m_ColorData.m_fCIEy);
						int iType;
						char strName[256];
						SDCM_DLL_GetSelSDCM_OneGraType(iType,strName);
						pDoc->m_TestContainer.GetCurrentLEDData().m_iSDCMType = iType;
						pDoc->m_TestContainer.GetCurrentLEDData().m_strSDCMSta  = strName;
						if (iType == CLedData::SDCMType_ELLI)
						{
							pDoc->m_TestContainer.GetCurrentLEDData().m_fSDCM = SDCM_DLL_GetSelSDCM_Ellipse_SDCMValue();
						}
						if (iType == CLedData::SDCMType_PLOY)
						{
							pDoc->m_TestContainer.GetCurrentLEDData().m_bInPoly = SDCM_DLL_GetSelSDCM_Polygon_WhetherIn();
						}
						////end
						///////////////////////////////////////////////////////////////////////////////////////////////////////////////
						if(pDoc->m_dataContainer.GetTestSettingData().m_bTestSaft)
						{
							pDoc->m_TestContainer.GetCurrentLEDData().m_bHaveTestSaft = TRUE;
							//JYDZ
							int iBR = pDoc->m_iNumSaftR - g_iColomnNum * pDoc->m_CommSettingsData.m_iJydzLedTestRange;
							if(iBR < 0)
							{
								if(pDoc->m_iHaveBoradSaftR > pDoc->m_CommSettingsData.m_iJydzLedTestRange)
									iBR = 2000 + pDoc->m_iNumSaftR - g_iColomnNum * pDoc->m_CommSettingsData.m_iJydzLedTestRange;
								else
									iBR = 0;
							}
						
							pDoc->m_TestContainer.GetCurrentLEDData().m_fSaft_R = pDoc->m_fSaft_R[iBR];
							pDoc->m_TestContainer.GetCurrentLEDData().m_fSaftLimit_R = pDoc->m_fSaftLimit_R[iBR];
							//NYY
							int iBV = pDoc->m_iNumSaftV - g_iColomnNum * pDoc->m_CommSettingsData.m_iNyyLedTestRange;
							if(iBV < 0)
							{
								if(pDoc->m_iHaveBoradSaftV > pDoc->m_CommSettingsData.m_iNyyLedTestRange)
									iBV = 2000 + pDoc->m_iNumSaftV - g_iColomnNum * pDoc->m_CommSettingsData.m_iNyyLedTestRange;
								else
									iBV = 0;
							}
							pDoc->m_TestContainer.GetCurrentLEDData().m_fSaft_V = pDoc->m_fSaft_V[iBV];
							pDoc->m_TestContainer.GetCurrentLEDData().m_fSaftLimit_V = pDoc->m_fSaftLimit_V[iBV];
							//XLDL
							int iBC = pDoc->m_iNumSaftC - g_iColomnNum * pDoc->m_CommSettingsData.m_iXldlLedTestRange;
							if(iBC < 0)
							{
								if(pDoc->m_iHaveBoradSaftC > pDoc->m_CommSettingsData.m_iXldlLedTestRange)
									iBV = 2000 + pDoc->m_iNumSaftC - g_iColomnNum * pDoc->m_CommSettingsData.m_iXldlLedTestRange;
								else
									iBV = 0;
							}
							pDoc->m_TestContainer.GetCurrentLEDData().m_fSaft_C = pDoc->m_fSaft_C[iBC];
							pDoc->m_TestContainer.GetCurrentLEDData().m_fSaftLimit_C = pDoc->m_fSaftLimit_C[iBC];

						}
						else
						{
							pDoc->m_TestContainer.GetCurrentLEDData().m_bHaveTestSaft = FALSE;

						}
						// d.Check if there is any LED remain to be test
						pDoc->m_eventOneLEDSpectrumOK.SetEvent();
						if (!pDoc->m_TestContainer.HaveSpectrumUntestedLED())
						{
							break;
						}
					}
				}
				delete [] pAD;
				delete [] pDarkAD;

				// 4.Test end, reset event
	SpeEnd:
				g_Hass1200Meter.SetShutterOff();
				pDoc->m_bIsSpectrumRunning = FALSE;
				pDoc->m_eventStartOne.ResetEvent();
				pDoc->m_eventSpectrumEnd.SetEvent();
			}
			else
			{
				pDoc->m_bIsSpectrumRunning = FALSE;
				pDoc->m_eventStartOne.ResetEvent();
				pDoc->m_eventSpectrumEnd.SetEvent();
			}
		}
	}
	return 0;
}


UINT CLAT2000Doc::_ThreadElectrical(LPVOID pPar)
{
	//测试工位供电控制
	CLAT2000Doc * pDoc = (CLAT2000Doc *)pPar;

	while(1)
	{
		int iNeedB = pDoc->m_CommSettingsData.m_iJydzLedTestRange;
		if (pDoc->m_eventStartOne.Lock())
		{
			if((!pDoc->m_dataContainer.GetTestSettingData().m_bTestSaft || pDoc->m_iHaveBoradSaftR >= iNeedB)
				|| pDoc->m_iHaveInLampBroadNum >= (atoi(pDoc->m_CommSettingsData.m_strHandAutoRange1))
				|| !pDoc->m_dataContainer.GetTestSettingData().m_bTestAutoHand)
			{
	           if(!pDoc->m_TestContainer.CurrentTestRowIsScaned() && pDoc->m_CommSettingsData.m_bHaveScaner)
				{
					pDoc->m_TestContainer.SetCurrentRowNeedTest(FALSE);
					goto eleEnd;
				}
				else
				{
					pDoc->m_TestContainer.SetCurrentRowNeedTest(TRUE);
				}
				// 1.Start test
				pDoc->m_bIsElectricalRunning = TRUE;
				pDoc->m_TestContainer.MoveToFirst();
				if (pDoc->m_TestContainer.GetCurrentLEDIndex() == -1)
				{	
				}
				else
				{
					// 2.Check DPS
					BOOL bR = FALSE;
					if (g_DPSComm.IsRunning())
					{
						RealTimeData data;
						bR = g_DPSComm.GetRealTimeData(data);
						float fVoltage = g_pDoc->m_dataContainer.GetTestSettingData().m_fTestVoltageV, 
							fFrequency = g_pDoc->m_dataContainer.GetTestSettingData().m_fTestFrquencyHz;
						if (fabs(data.fVoltageValue - fVoltage) > fVoltage / 100 || fabs(data.fFrequence - fFrequency) > fFrequency / 100)
						{
							bR = g_DPSComm.SetParameterRunning(g_pDoc->m_dataContainer.GetTestSettingData().m_fTestVoltageV, g_pDoc->m_dataContainer.GetTestSettingData().m_fTestFrquencyHz,
								g_DPSComm.GetLimitData().LimitCurrentRange2.fUpper, g_DPSComm.GetLimitData().LimitPower.fUpper);
						}
					}
					else
					{
						g_DPSComm.StopOutput();
						bR = g_DPSComm.FastRun(g_pDoc->m_dataContainer.GetTestSettingData().m_fTestVoltageV, g_pDoc->m_dataContainer.GetTestSettingData().m_fTestFrquencyHz);
					}

					// Wait spectrum get dark AD OK
					bR = pDoc->m_eventOneLEDSpectrumOK.Lock();
					// Set power meter range
					bR = g_PowerMeterComm.SetCurrentAutoRange(FALSE);
					bR = g_PowerMeterComm.SetRange(pDoc->m_dataContainer.GetTestSettingData().m_iRangeU,
						pDoc->m_dataContainer.GetTestSettingData().m_iRangeI,
						pDoc->m_dataContainer.GetTestSettingData().m_iRangeCF);
					Sleep(500);
					while(1)
					{
						if (pDoc->m_bSetStop)
						{
							pDoc->m_eventOneLEDON.SetEvent();
							g_LineControllerComm.SetLinePause();
							break;
						}
						// a.Switch to current channel
						if (pDoc->m_CommSettingsData.m_iTestChannelControlerType == 1)
						{
							g_SC1000Comm.SwitchChannel(g_pDoc->m_TestContainer.GetCurrentLEDIndex());
						}
						else
						{
							g_TestChannelControlComm.SwitchOneChannel(g_pDoc->m_TestContainer.GetCurrentLEDIndex(), TRUE);
						}
						// Warm up time
						Sleep((int)g_pDoc->m_dataContainer.GetTestSettingData().m_fWarmUpTimems);
						// Let spectrum begin test this LED
						BOOL bR = pDoc->m_eventOneLEDON.SetEvent();
						// b.Test electrical data of this LED
						CLedData &data = pDoc->m_TestContainer.GetCurrentLEDData();
						data.m_fFrequencyHz = g_pDoc->m_dataContainer.GetTestSettingData().m_fTestFrquencyHz;
						if(g_bInputPower)
						{
							bR = TRUE;
							data.m_fVoltageV = g_fInputVol;
							data.m_fCurrentA = g_fInputCurr;
							data.m_fPowerW   = g_fInputPower;
							data.m_fPowerFactor = g_fInputPF;
						}
						else
						{
							bR = g_PowerMeterComm.Read(data.m_fVoltageV, data.m_fCurrentA, data.m_fPowerW, data.m_fPowerFactor);
							if (!bR)
							{
								Sleep(200);
								bR = g_PowerMeterComm.Read(data.m_fVoltageV, data.m_fCurrentA, data.m_fPowerW, data.m_fPowerFactor);
							}
						}
						
						pDoc->m_TestContainer.GetCurrentLEDState().ElectricalTestState = (bR ? Successful : Failed);
						pDoc->m_TestContainer.GetCurrentLEDData().m_strLedModel = pDoc->m_dataContainer.GetTestSettingData().m_strLedModel;
						pDoc->m_TestContainer.SetCurrentLEDUpdated(FALSE);

						//pDoc->m_TestContainer.GetCurrentLEDData().m_fPositiveCurrent = rand() % 5 / 100.0f + 0.2f;
						//pDoc->m_TestContainer.GetCurrentLEDData().m_fPositiveVoltage = rand() % 5 + 218.0f;
						//Sleep(rand() % 500);

						// c.Wait spectrum be OK
						bR = pDoc->m_eventOneLEDSpectrumOK.Lock();

						// d.Check if there is any LED remain to be test
						if (!pDoc->m_TestContainer.HaveElectricalUntestedLED())
						{
							break;
						}
						pDoc->m_TestContainer.MoveToNext();
					}
				}
				// 2.Reset event
				//g_DPSComm.StopOutput();
				if (pDoc->m_CommSettingsData.m_iTestChannelControlerType == 1)
				{
					g_SC1000Comm.SwitchAllLamp(TRUE);
				}
				else
				{
					g_TestChannelControlComm.SwitchAllChannel(TRUE);
				}
eleEnd:
				pDoc->m_bIsElectricalRunning = FALSE;
				pDoc->m_eventStartOne.ResetEvent();
				pDoc->m_eventElectricalEnd.SetEvent();
			}
			else
			{
				pDoc->m_bIsElectricalRunning = FALSE;
				pDoc->m_eventStartOne.ResetEvent();
				pDoc->m_eventElectricalEnd.SetEvent();
			}
		}
	}

	return 0;
}


UINT CLAT2000Doc::_ThreadLightningSurge(LPVOID pPar)
{
	//雷击
	CLAT2000Doc * pDoc = (CLAT2000Doc *)pPar;

	//g_EMS61000_5AComm.Reset();
	BOOL bR = FALSE;
	while(1)
	{
		if (pDoc->m_eventStartOne.Lock())
		{
			// Start test
			pDoc->m_bIsLightningSurgeRunning = TRUE;
	
			// 3.3 EMS61000-5A
			// Test
			if (pDoc->m_dataContainer.GetTestSettingData().m_bTestLightning)
			{
				EMC5ASetData data;
				for (int i = 0; i < g_iColomnNum; i++)
				{
					if (pDoc->m_CommSettingsData.m_bHaveThunderRelay)
					{
						bR = g_ThunderRelayComm.SwitchOneChannel(i, TRUE);
						if (!bR)
						{
							Sleep(200);
							bR = g_ThunderRelayComm.SwitchOneChannel(i, TRUE);
							if (!bR)
							{
								pDoc->ShowMessageDialog("雷击测试切换通道失败，请检查仪器是否正确连接！");
								pDoc->OnMenuStop();

								goto exit;
							}
						}
					}
 					
					bR = g_EMS61000_5AComm.Start(data, pDoc->m_dataContainer.GetTestSettingData().m_iEMC5ASelectIndex);
					Sleep(100);
					pDoc->m_TestContainer.m_iCurrentThunderChannel = i;						
					if (!bR)
					{
						pDoc->ShowMessageDialog("雷击测试启动失败，请检查仪器是否正确连接！");
						pDoc->OnMenuStop();

						goto exit;
					}
					else
					{
						EMC5AREData data;
						int iReadFaileTimes = 0;
						while(1)
						{
							// Wait test end
							
							int iResult = g_EMS61000_5AComm.Read(data);
							if(data.m_fTime == 0)
								iResult = 0;
							if (1 == iResult)
							{
								iReadFaileTimes++;
							}
							else if (-1 == iResult)
							{
								// Running
							}
							else
							{
								// Over
								break;
							}
							Sleep(200);
							if (iReadFaileTimes > 10)
							{
								pDoc->ShowMessageDialog("雷击测试读取状态失败，请检查仪器是否正确连接！");
								pDoc->OnMenuStop();
								goto exit;
							}
							if (pDoc->m_bSetStop)
							{
								// User stop test
								goto exit;
							}
						} // while
				
						if (pDoc->m_bSetStop)
						{
							// User stop test
							goto exit;
						}
					} // else
				}// for
			}// if
exit:
			// Test end, reset event
			//g_EMS61000_5AComm.Reset();
			pDoc->m_bIsLightningSurgeRunning = FALSE;
			pDoc->m_TestContainer.m_iCurrentThunderChannel = -1;
			pDoc->m_eventStartOne.ResetEvent();
			pDoc->m_eventLightningSurgeEnd.SetEvent();
		}
	}// while

	return 0;
}

UINT CLAT2000Doc::_ThreadMyLastTest(LPVOID pPar)
{
	//漫游
	BOOL bR;
	CLAT2000Doc * pDoc = (CLAT2000Doc *)pPar;
	int i;
	int iCOM;
	//if (pDoc->m_eventStartOne.Lock() && 
	if(pDoc->m_dataContainer.GetTestSettingData().m_bTestMyLast)
	{
		sscanf_s(pDoc->m_CommSettingsData.m_strMyLastCOM.GetBuffer(), "COM%d", &iCOM);
		g_DPSComm_MyLast.SetDeviceType((DeviceType)pDoc->m_CommSettingsData.m_iMyLastPowerType);
		g_DPSComm_MyLast.InitializeComm(iCOM);
		g_DPSComm_MyLast.InRemote();
		g_DPSComm_MyLast.StopOutput();
		Sleep(100);

		if(pDoc->m_dataContainer.GetTestSettingData().m_fVolMyLast.GetSize() > 0)
		{
			Parameter data;
			data.fFrequenceLow				= 45;
			data.fFrequenceUpper			= 60;
			data.fExternalCurrentFactor		= 0;
			data.fVoltageLow				= 10;
			data.fVoltageUpper				= 300;
			data.bOvercurrentFoldBackEnable = FALSE;
			data.bHarmonicEnable			= FALSE;
			data.bExternalVoltageSamplingEnable = FALSE;
			data.bExternalCurrentSamplingEnable = FALSE;
			data.bVoltageAutoAdjustEnable	= TRUE;
			data.iMemory		= 0;
			data.fVoltage		= pDoc->m_dataContainer.GetTestSettingData().m_fVolMyLast[0];
			data.fFrequence		= pDoc->m_dataContainer.GetTestSettingData().m_fFreqMyLast[0];
			data.fAlarmCurrent	= g_DPSComm_MyLast.GetLimitData().LimitCurrentRange2.fUpper;
			data.fAlarmPower	= g_DPSComm_MyLast.GetLimitData().LimitPower.fUpper;
			data.iRangeU		= 1;
			g_DPSComm_MyLast.SetParameter(data);
			Sleep(100);
		}

		if (!g_DPSComm_MyLast.IsRunning())
		{
			bR = g_DPSComm_MyLast.StartOutput();
			Sleep(100);
		}
	}

	while(1)
	{
		if (1)//pDoc->m_eventStartOne.Lock())
		{
			// Start test
			if (pDoc->m_dataContainer.GetTestSettingData().m_bTestMyLast)
			{
				pDoc->m_bIsMyLastRunning = TRUE;
				for (i = 0; i < pDoc->m_dataContainer.GetTestSettingData().m_fVolMyLast.GetSize(); i++)
				{
					int iT1 = GetCurrentTime();
					int iT2 = GetCurrentTime();
					bR = g_DPSComm_MyLast.SetParameterRunning(pDoc->m_dataContainer.GetTestSettingData().m_fVolMyLast[i], 
						pDoc->m_dataContainer.GetTestSettingData().m_fFreqMyLast[i],
						g_DPSComm_MyLast.GetLimitData().LimitCurrentRange2.fUpper, 
						g_DPSComm_MyLast.GetLimitData().LimitPower.fUpper);
					if (!bR)
					{
						bR = g_DPSComm_MyLast.SetParameterRunning(pDoc->m_dataContainer.GetTestSettingData().m_fVolMyLast[i], 
																		pDoc->m_dataContainer.GetTestSettingData().m_fFreqMyLast[i],
																		g_DPSComm_MyLast.GetLimitData().LimitCurrentRange2.fUpper, 
																		g_DPSComm_MyLast.GetLimitData().LimitPower.fUpper);
						
						if(!bR)
						{
							bR = g_DPSComm_MyLast.SetParameterRunning(pDoc->m_dataContainer.GetTestSettingData().m_fVolMyLast[i], 
																		pDoc->m_dataContainer.GetTestSettingData().m_fFreqMyLast[i],
																		g_DPSComm_MyLast.GetLimitData().LimitCurrentRange2.fUpper, 
																		g_DPSComm_MyLast.GetLimitData().LimitPower.fUpper);
						}
						
						if(!bR)
						{
							pDoc->ShowMessageDialog("漫游测试启动失败，请检查仪器是否正确连接！");
							pDoc->OnMenuStop();
							return 0;
						}
					}

					while(1)
					{
						Sleep(10);
						if (pDoc->m_bSetStop)
						{
							// User stop test
							break;
						}
						iT2 = GetCurrentTime();
						if(iT2 - iT1 > pDoc->m_dataContainer.GetTestSettingData().m_iTimeMyLast[i] * 1000)
						{
							break;
						}
					} // while, end wait
				}
			} // if

			if (pDoc->m_bSetStop)
			{
				// User stop test
				break;
			}
	
			// Test end, reset event
			pDoc->m_bIsMyLastRunning = FALSE;
		}// while
	}
	if(pDoc->m_dataContainer.GetTestSettingData().m_bTestMyLast)
		g_DPSComm_MyLast.StopOutput();
	pDoc->m_bIsMyLastRunning = FALSE;

	return 0;
}

UINT CLAT2000Doc::_ThreadHandAutoLamp(LPVOID pPar)
{
	CLAT2000Doc * pDoc = (CLAT2000Doc *)pPar;
	BOOL bR;
	//初始化机械手仪器配置
	while(1)
	{
		if (pDoc->m_eventStartOne.Lock())
		{
			pDoc->m_bIsHandAutoRunning = TRUE;
			CString strTemp;
			int iT1 = GetCurrentTime();
  
			if (!pDoc->m_dataContainer.GetTestSettingData().m_bTestAutoHand)
			{
				//没有选机械手上灯
				goto endHndAuto;
			}
			BOOL bHaveMove = FALSE;
			//先发送测试OK信号到机械手
			bR = g_HandAutoComm.WriteToHandLamp(g_iChannelOK);

			//发到位信号 允许上灯 同时在进行下灯动作
			bR = g_HandAutoComm.WriteToHandInpos(TRUE);
			if (!bR)
			{
				pDoc->ShowMessageDialog("机械手控制失败，请检查仪器是否正确连接！");
				pDoc->OnMenuStop();
				goto endHndAuto;
			}
			//读取到允许运行说明上灯结束了
			BOOL bAllow = FALSE;
			while(1)
			{
				bR = g_HandAutoComm.ReadHandState(bAllow);
				if (bAllow)
				{
					break;
				}
				if (pDoc->m_bSetStop)
				{
					pDoc->OnMenuStop();
					goto endHndAuto;
				}
			}
			strTemp.Format("ReadHand:%d",GetCurrentTime() - iT1);
			g_strShowNote4 = g_strShowNote4 + strTemp;
			iT1 = GetCurrentTime();
			//已经插灯的板数++
			pDoc->m_iHaveInLampBroadNum++;
			pDoc->m_iCurrentInLampBroad++;
			int iTolBroad = pDoc->m_CommSettingsData.m_iTotalBoard;
			if (pDoc->m_iCurrentInLampBroad > iTolBroad)
			{
				pDoc->m_iCurrentInLampBroad = 1;
			}
				
				goto endHndAuto;
//			} // if
endHndAuto:		
			// Test end, reset event
			pDoc->m_bIsHandAutoRunning = FALSE;
			pDoc->m_eventStartOne.ResetEvent();
			pDoc->m_eventHandAutoEnd.SetEvent();
		}// while
	}

	return 0;
}

UINT CLAT2000Doc::_ThreadSaftXLDLTest(LPVOID pPar)
{
	//泄露电流工位测试 注意:如果有泄露电流工位 则要隔N个之后才能开始电参数 才能添加到数据列表中去
	CLAT2000Doc * pDoc = (CLAT2000Doc *)pPar;
	int i;
	BOOL bR;
	//初始化泄露电流仪器配置
	BOOL bHaveTestXLDL = FALSE;
	while(1)
	{
		if (pDoc->m_eventStartOne.Lock())
		{
			pDoc->m_bIsSaftXLDLRunning = TRUE;
			if(pDoc->m_CommSettingsData.m_bHaveSaft_XLDL && pDoc->m_dataContainer.GetTestSettingData().m_bTestSaft)
			{
				bR = g_SafetyTest_CS5505Comm.CS_Init_XL(pDoc->m_CommSettingsData.m_strSaftXLDLCOM);
				if(!bR)
				{
					//	AfxMessageBox("通讯失败!");
					goto endXLDL;
				}

				bR = g_SafetyTest_CS5505Comm.CS_Setup_XL(pDoc->m_dataContainer.GetTestSettingData().m_fSetVolXLDL ,pDoc->m_dataContainer.GetTestSettingData().m_fSetTimeXLDL);
				if(!bR)
				{
					//AfxMessageBox("通讯失败!");
					goto endXLDL;
				}

				g_ContXldlComm.Initialize(pDoc->m_CommSettingsData.m_strComXldl2);


				if (pDoc->m_bSetStop)
				{
					// User stop test
					break;
				}
				if (pDoc->m_lineState != Testing)
				{
					bHaveTestXLDL = FALSE;
				}

				int iNeedB = pDoc->m_CommSettingsData.m_iJydzLedTestRange - pDoc->m_CommSettingsData.m_iXldlLedTestRange;
			//	if (1)//pDoc->m_lineState == Testing && !bHaveTestJydz) //移动到位 允许测试当前
				if(pDoc->m_iHaveBoradSaftR >= iNeedB)
				{
					// Start test
					g_ContXldlComm.SwitchAllChannel(FALSE);
					if (pDoc->m_dataContainer.GetTestSettingData().m_bTestSaft && pDoc->m_CommSettingsData.m_bHaveSaft_XLDL)
					{
						for (i = 0; i < g_iColomnNum; i++)
						{
							if (pDoc->m_bSetStop)
							{
								// User stop test
								break;
							}
							//切换通道
							g_ContXldlComm.SwitchOneChannel(i,TRUE);

							bR = g_SafetyTest_CS5505Comm.CS_Test_XL(TRUE);					
							if(!bR)
							{
								pDoc->ShowMessageDialog("泄露电流测试失败，请检查仪器是否正确连接！");
								pDoc->OnMenuStop();
								goto endXLDL;
							}
							Sleep(100);
							float fLC;
							BOOL bOK = FALSE;
							
							int iErr = 0;
							while(1)
							{
								Sleep(10);
								bR = g_SafetyTest_CS5505Comm.CS_GetData_XL(fLC,bOK);
								if(bOK || iErr > 10)
									break;
								else
									iErr++;
							}
						
							if(!bR && iErr > 10)
							{
								pDoc->ShowMessageDialog("绝缘电阻测试失败，请检查仪器是否正确连接！");
								pDoc->OnMenuStop();
								goto endXLDL;
							}
							g_SafetyTest_CS5505Comm.CS_Test_XL(FALSE); //必须停止才能再次测试
							//添加数据
							pDoc->m_fSaft_C[pDoc->m_iNumSaftC]		= fLC;
							pDoc->m_fSaftLimit_C[pDoc->m_iNumSaftC]	= pDoc->m_dataContainer.GetTestSettingData().m_fXLDLLimit;
							pDoc->m_iNumSaftC++;
							if(pDoc->m_iNumSaftC > 2000)
								pDoc->m_iNumSaftC = 0;
						}
						bHaveTestXLDL = TRUE;
						pDoc->m_iHaveBoradSaftC++;
						goto endXLDL;
					} // if
endXLDL:			// Test end, reset event
					pDoc->m_bIsSaftXLDLRunning = FALSE;
					pDoc->m_eventStartOne.ResetEvent();
					pDoc->m_eventSaftXLDLEnd.SetEvent();
				}// while
				else
				{
					pDoc->m_bIsSaftXLDLRunning = FALSE;
					pDoc->m_eventStartOne.ResetEvent();
					pDoc->m_eventSaftXLDLEnd.SetEvent();
				}
			}
			else
			{
				pDoc->m_bIsSaftXLDLRunning = FALSE;
				pDoc->m_eventStartOne.ResetEvent();
				pDoc->m_eventSaftXLDLEnd.SetEvent();
			}
		}
	}

	return 0;
}

UINT CLAT2000Doc::_ThreadSaftNYYTest(LPVOID pPar)
{
	//耐压仪测试工位测试 注意:如果有耐压仪工位 则要隔N个之后才能开始电参数 才能添加到数据列表中去
	CLAT2000Doc * pDoc = (CLAT2000Doc *)pPar;
	int i;
	BOOL bR;
	//初始化耐压仪仪器配置
	
	if(pDoc->m_CommSettingsData.m_bHaveSaft_NYY && pDoc->m_dataContainer.GetTestSettingData().m_bTestSaft)
	{
		if(pDoc->m_CommSettingsData.m_iTypeSaftNyy == 0)
		{
			g_SafetyTest_TongHui_TH9310_20Comm.Initialize(pDoc->m_CommSettingsData.m_strSaftNyyCOM);
			bR = TRUE;
		}
		else
		{
			bR = g_SafetyTest_CS9912Comm.CS_Init_NYY(pDoc->m_CommSettingsData.m_strSaftNyyCOM);
		}

		if (g_pDoc->m_CommSettingsData.m_iTypeSaftJydz == 0)
			bR = g_SafetyTest_TongHui_TH9310_20Comm.TH_Setup_NYY(pDoc->m_dataContainer.GetTestSettingData().m_iTypeNYY,
			pDoc->m_dataContainer.GetTestSettingData().m_fSetVolNYY, 
			pDoc->m_dataContainer.GetTestSettingData().m_fSetTimeNYY);
		else
			bR = g_SafetyTest_CS9912Comm.CS_Setup_NYY(pDoc->m_dataContainer.GetTestSettingData().m_iTypeNYY,
			pDoc->m_dataContainer.GetTestSettingData().m_fSetVolNYY ,
			pDoc->m_dataContainer.GetTestSettingData().m_fSetTimeNYY,
			pDoc->m_dataContainer.GetTestSettingData().m_fNYYLimit);

		g_ContNyyComm.Initialize(pDoc->m_CommSettingsData.m_strComNyy2);
		Sleep(100);
	}

	while(1)
	{
		if (pDoc->m_eventStartOne.Lock())
		{
			pDoc->m_bIsSaftNYYRunning = TRUE;
			if(pDoc->m_CommSettingsData.m_bHaveSaft_NYY && pDoc->m_dataContainer.GetTestSettingData().m_bTestSaft)
			{
				BOOL bHaveTestNyy = FALSE;
				int iNeedB = pDoc->m_CommSettingsData.m_iJydzLedTestRange - pDoc->m_CommSettingsData.m_iNyyLedTestRange;

				if (pDoc->m_bSetStop)
				{
					// User stop test
					goto EndNyy;
				}

				if(pDoc->m_iHaveBoradSaftR >= iNeedB)
				{
					// Start test
					g_ContNyyComm.SwitchAllChannel(FALSE);
					if (pDoc->m_dataContainer.GetTestSettingData().m_bTestSaft && pDoc->m_CommSettingsData.m_bHaveSaft_NYY)
					{
						for (i = 0; i < g_iColomnNum; i++)
						{
							if (pDoc->m_bSetStop)
							{
								// User stop test
								goto EndNyy;
							}
							//切换通道
							g_ContNyyComm.SwitchOneChannel(i,TRUE);

							if (pDoc->m_CommSettingsData.m_iTypeSaftNyy == 0)
							{
								//TH2683A
								bR = g_SafetyTest_TongHui_TH9310_20Comm.TH_SetTestStart_NYY(TRUE);
							}
							else
							{
								//CS2676
								bR = g_SafetyTest_CS9912Comm.CS_Test_NYY(TRUE);
							}

							if(!bR)
							{
								pDoc->ShowMessageDialog("耐压测试失败1，请检查仪器是否正确连接！");
								pDoc->OnMenuStop();
								goto EndNyy;
							}

							float fLC;
							if (g_pDoc->m_CommSettingsData.m_iTypeSaftJydz == 0)
							{
								Sleep(500);
								bR = g_SafetyTest_TongHui_TH9310_20Comm.TH_GetTestResult_NYY(fLC);
								if(!bR)
								{
									pDoc->ShowMessageDialog("耐压测试失败2，请检查仪器是否正确连接！");
									pDoc->OnMenuStop();
									goto EndNyy;
								}
								bR = g_SafetyTest_TongHui_TH9310_20Comm.TH_SetTestStart_NYY(FALSE);
							}
							else
							{
								BOOL bOK;
								bR = g_SafetyTest_CS9912Comm.CS_GetData_NYY(pDoc->m_dataContainer.GetTestSettingData().m_iTypeNYY,bOK,fLC);
								if(!bR)
								{
									pDoc->ShowMessageDialog("耐压测试失败，请检查仪器是否正确连接！");
									pDoc->OnMenuStop();
									goto EndNyy;
								}
								bR = g_SafetyTest_CS9912Comm.CS_Test_NYY(FALSE);
							}
							//添加数据
							pDoc->m_bHaveTestSaft[pDoc->m_iNumSaftV]= TRUE;
							pDoc->m_bSaftOK[pDoc->m_iNumSaftV]		= TRUE;
							pDoc->m_fSaft_V[pDoc->m_iNumSaftV]		= fLC;
							pDoc->m_fSaftLimit_V[pDoc->m_iNumSaftV]	= pDoc->m_dataContainer.GetTestSettingData().m_fNYYLimit;					
							pDoc->m_iNumSaftV++;
							if(pDoc->m_iNumSaftV >= 2000)
							{
								pDoc->m_iNumSaftV = 0;
							}
							Sleep(1000);
						}
						pDoc->m_iHaveBoradSaftV++;
						bHaveTestNyy = TRUE;
						goto EndNyy;
					} // if
				// Test end, reset event
EndNyy:
					pDoc->m_bIsSaftNYYRunning = FALSE;
					pDoc->m_eventStartOne.ResetEvent();
					pDoc->m_eventSaftNYYEnd.SetEvent();
				}
				else
				{
					pDoc->m_bIsSaftNYYRunning = FALSE;
					pDoc->m_eventStartOne.ResetEvent();
					pDoc->m_eventSaftNYYEnd.SetEvent();
				}
			}
			else
			{
				pDoc->m_bIsSaftNYYRunning = FALSE;
				pDoc->m_eventStartOne.ResetEvent();
				pDoc->m_eventSaftNYYEnd.SetEvent();
			}
		}
	}
	return 0;
}

UINT CLAT2000Doc::_ThreadSaftJYDZTest(LPVOID pPar)
{
	//绝缘电阻工位测试 注意:如果有绝缘电阻工位 则要隔N个之后才能开始电参数 才能添加到数据列表中去
	CLAT2000Doc * pDoc = (CLAT2000Doc *)pPar;
	int i;
	BOOL bR;
	//初始化绝缘电阻仪器配置
	BOOL bHaveTestJydz = FALSE;
	while(1)
	{
		if (pDoc->m_eventStartOne.Lock())
		{
			pDoc->m_bIsSaftJYDZRunning = TRUE;
			if(pDoc->m_CommSettingsData.m_bHaveSaft_JYDZ && pDoc->m_dataContainer.GetTestSettingData().m_bTestSaft)
			{

				if(pDoc->m_CommSettingsData.m_iTypeSaftJydz == 0)
				{
					g_SafetyTest_TongHui_TH2683AComm.Initialize(pDoc->m_CommSettingsData.m_strSaftJydzCOM);
					bR = TRUE;
				}
				else
					bR = g_SafetyTest_CS2676Comm.CS_Init_IR(pDoc->m_CommSettingsData.m_strSaftJydzCOM);
				if(!bR)
				{
					//	AfxMessageBox("通讯失败!");
					goto endJYDZ;
				}

				if (g_pDoc->m_CommSettingsData.m_iTypeSaftJydz == 0)
					bR = g_SafetyTest_TongHui_TH2683AComm.TH_Setup_IR(pDoc->m_dataContainer.GetTestSettingData().m_fSetVolJYDZ, pDoc->m_dataContainer.GetTestSettingData().m_fSetTimeJYDZ);
				else
					bR = g_SafetyTest_CS2676Comm.CS_Setup_IR(pDoc->m_dataContainer.GetTestSettingData().m_fSetVolJYDZ ,pDoc->m_dataContainer.GetTestSettingData().m_fSetTimeJYDZ);
				if(!bR)
				{
					//AfxMessageBox("通讯失败!");
					goto endJYDZ;
				}

				g_ContJydzComm.Initialize(pDoc->m_CommSettingsData.m_strComJydz2);


				if (pDoc->m_bSetStop)
				{
					// User stop test
					break;
				}
				if (pDoc->m_lineState != Testing)
				{
					bHaveTestJydz = FALSE;
				}

				if (1)//pDoc->m_lineState == Testing && !bHaveTestJydz) //移动到位 允许测试当前
				{
					// Start test

					g_ContJydzComm.SwitchAllChannel(FALSE);
					if (pDoc->m_dataContainer.GetTestSettingData().m_bTestSaft && pDoc->m_CommSettingsData.m_bHaveSaft_JYDZ)
					{
						for (i = 0; i < g_iColomnNum; i++)
						{
							if (pDoc->m_bSetStop)
							{
								// User stop test
								break;
							}
							//切换通道
							g_ContJydzComm.SwitchOneChannel(i,TRUE);

							if (pDoc->m_CommSettingsData.m_iTypeSaftJydz == 0)
							{
								//TH2683A
								bR = g_SafetyTest_TongHui_TH2683AComm.TH_SetTestStart_IR(TRUE);
							}
							else
							{
								//CS2676
								bR = g_SafetyTest_CS2676Comm.CS_Test_IR(TRUE);
							}
					
						/*	if(!bR)
							{
								pDoc->ShowMessageDialog("绝缘电阻测试失败，请检查仪器是否正确连接！");
								pDoc->OnMenuStop();
								goto endJYDZ;
							}*/

							float fIR,fLC,fTime;
							if (g_pDoc->m_CommSettingsData.m_iTypeSaftJydz == 0)
							{
								int iT1,iT2;
								iT1 = GetCurrentTime();
								int iErr = 0;
								while(1)
								{
									Sleep(10);
									iT2 = GetCurrentTime() - iT1;
									if(iT2 > pDoc->m_dataContainer.GetTestSettingData().m_fSetTimeJYDZ * 1000)
									{
										bR = g_SafetyTest_TongHui_TH2683AComm.TH_GetTestResult_IR(fIR,fLC,fTime);
										if((bR && fIR > 10) || iErr > 10)
										{
											break;
										}
										else
										{
											Sleep(100);
											iErr++;
										}
									}
								}
						
								if(!bR)
								{
									pDoc->ShowMessageDialog("绝缘电阻测试失败，请检查仪器是否正确连接！");
									pDoc->OnMenuStop();
									goto endJYDZ;
								}
								fIR = fIR / 1000 / 1000; //转化为M
							}
							else
							{
								bR = g_SafetyTest_CS2676Comm.CS_GetData_IR(fIR);
								if(!bR)
								{
									pDoc->ShowMessageDialog("绝缘电阻测试失败，请检查仪器是否正确连接！");
									pDoc->OnMenuStop();
									goto endJYDZ;
								}
							}
							//添加数据
							pDoc->m_bHaveTestSaft[pDoc->m_iNumSaftR]= TRUE;
							pDoc->m_bSaftOK[pDoc->m_iNumSaftR]		= TRUE;
							pDoc->m_fSaft_R[pDoc->m_iNumSaftR]		= fIR;
							pDoc->m_fSaftLimit_R[pDoc->m_iNumSaftR]	= pDoc->m_dataContainer.GetTestSettingData().m_fJYDZLimit;
							pDoc->m_iNumSaftR++;
							if(pDoc->m_iNumSaftR > 2000)
								pDoc->m_iNumSaftR = 0;
						}
						bHaveTestJydz = TRUE;
						pDoc->m_iHaveBoradSaftR++;
						goto endJYDZ;
					} // if
		endJYDZ:			// Test end, reset event
					pDoc->m_bIsSaftJYDZRunning = FALSE;
					pDoc->m_eventStartOne.ResetEvent();
					pDoc->m_eventSaftJYDZEnd.SetEvent();
				}// while
			}
			else
			{
				pDoc->m_bIsSaftJYDZRunning = FALSE;
				pDoc->m_eventStartOne.ResetEvent();
				pDoc->m_eventSaftJYDZEnd.SetEvent();
			}
		}
	}

	return 0;
}

UINT CLAT2000Doc::_ThreadVoltageDipsAndUP(LPVOID pPar)
{
	//跌落试验
	CLAT2000Doc * pDoc = (CLAT2000Doc *)pPar;

	g_EMS61000_11KComm.Reset();
	g_EMS61000_11KComm.SetEUT(FALSE);

		
	while(1)
	{
		if (pDoc->m_eventStartOne.Lock())
		{
			// Start test
			pDoc->m_bIsVoltageDipsAndUPRunning = TRUE;

			if (pDoc->m_dataContainer.GetTestSettingData().m_bTestVoltageUpAndDips)
			{
				g_EMS61000_11KComm.SetEUT(TRUE);
				BOOL bR = g_EMS61000_11KComm.Start(pDoc->m_dataContainer.GetTestSettingData().m_iEMC11KSelectIndex);
				if (!bR)
				{
					pDoc->ShowMessageDialog("周波跌落测试启动失败，请检查仪器是否正确连接！");
					pDoc->OnMenuStop();
				}
				else
				{
					EMC11KREData data;
					int iReadFaileTimes = 0;
					while(1)
					{
						// Wait test end
						int iResult = g_EMS61000_11KComm.Read(data);
						if (1 == iResult)
						{
							iReadFaileTimes++;
						}
						else if (-1 == iResult)
						{
							// Running
							;
						}
						else
						{
							break;
						}

						if (iReadFaileTimes > 10)
						{
							pDoc->ShowMessageDialog("周波跌落测试读取状态失败，请检查仪器是否正确连接！");
							pDoc->OnMenuStop();
							break;
						}

						Sleep(500);
						if (pDoc->m_bSetStop)
						{
							// User stop test
							break;
						}
					} // while, end wait
				} // else
				g_EMS61000_11KComm.SetEUT(FALSE);
			} // if

			// Test end, reset event
			g_EMS61000_11KComm.Reset();
			pDoc->m_bIsVoltageDipsAndUPRunning = FALSE;
			pDoc->m_eventStartOne.ResetEvent();
			pDoc->m_eventVoltageDipsAndUPEnd.SetEvent();
		}// while
	}
	return 0;
}

UINT CLAT2000Doc::_ThreadGauge(LPVOID pPar)
{
	//表头显示
	CLAT2000Doc * pDoc = (CLAT2000Doc *)pPar;
	CAlarmSettingsData & data = pDoc->m_dataContainer.GetTestSettingData().m_AlarmSettingsData;
	CString strTempInfo;
	int iTMP1AlarmTimes[20];
	for (int i = 0; i < 20; i++)
	{
		iTMP1AlarmTimes[i] = 0;
	}
	while(1)
	{
		if (pDoc->m_bCloseDocument)
		{
			return 0;
		}
        int i = 0;
        BOOL bR = FALSE;

        // TMP
        /*for (i = 0; i < g_myDockablePaneData.m_TemperatureController.GetSize(); i ++)
        {
			if (pDoc->m_bCloseDocument)
			{
				return 0;
			}
            bR = FALSE;
            bR = g_FujiTMPComm.ReadTemperature(pDoc->m_CommSettingsData.m_ucTemperatureAddress[i],
				g_myDockablePaneData.m_TemperatureController[i].m_fTMP, g_myDockablePaneData.m_TemperatureController[i].m_nAlarm);
            if (!bR)
            { 
                Sleep(200);
                bR = g_FujiTMPComm.ReadTemperature(pDoc->m_CommSettingsData.m_ucTemperatureAddress[i],
					g_myDockablePaneData.m_TemperatureController[i].m_fTMP, g_myDockablePaneData.m_TemperatureController[i].m_nAlarm);
            }
            if (bR)
            {
				CString strTemp;
				strTemp.Format("%d %.1f",i+1,g_myDockablePaneData.m_TemperatureController[i].m_fTMP);
				g_strGaugeData[i].Add(strTemp);
                g_myDockablePaneData.m_TemperatureController[i].m_bTMPReadSuccessful = TRUE;
                if (data.m_bTMPAlarm[i] && (g_myDockablePaneData.m_TemperatureController[i].m_fTMP < data.m_fTMPL[i] || g_myDockablePaneData.m_TemperatureController[i].m_fTMP > data.m_fTMPH[i]))
                {
                    g_myDockablePaneData.m_TemperatureController[i].m_bTMPAlarm = TRUE;
                    iTMP1AlarmTimes[i]++;

                    if (iTMP1AlarmTimes[i] >= 3)
                    {
                        if (data.m_bTMPAlarm[i] && data.m_bStopTest && pDoc->IsRunning())
                        {
                            pDoc->OnMenuStop();
                        }

                        strTempInfo.Format("%s 温度报警！合理温度范围(%.1f℃-->%.1f℃)", 
                            g_myDockablePaneData.m_strTemperatureControllerText[i],
                            data.m_fTMPL[i], data.m_fTMPH[i]);
                        pDoc->ShowMessageDialog(strTempInfo, (AlarmType)(AT_TMP1 + i));
                    }
                }
                else
                {
                    iTMP1AlarmTimes[i] = 0;
                    g_myDockablePaneData.m_TemperatureController[i].m_bTMPAlarm = FALSE;
                } 
            }
            else
            {
                g_myDockablePaneData.m_TemperatureController[i].m_bTMPAlarm = FALSE;
                g_myDockablePaneData.m_TemperatureController[i].m_bTMPReadSuccessful = FALSE;
            }
        }
				
		Sleep(500);*/
		// Region
		if (pDoc->m_bCloseDocument)
		{
			return 0;
		}
        for (i = 0; i < g_myDockablePaneData.m_dataRegion.GetSize(); i ++)
        {
			if (pDoc->m_bCloseDocument)
			{
				return 0;
			}
            bR = FALSE;
            if (pDoc->m_CommSettingsData.m_bfor4A) //4m线特殊使用DPS代替表头
            {
                if (g_DPSAgeComm[i].IsRunning())
                {
                    RealTimeData data;
                    bR = g_DPSAgeComm[i].GetRealTimeData(data);
                    g_myDockablePaneData.m_dataRegion[i].fVoltageV = data.fVoltageValue;
                    g_myDockablePaneData.m_dataRegion[i].fCurrentA = data.fCurrentValue;
                    g_myDockablePaneData.m_dataRegion[i].fPowerW = data.fPower;
                }
            }
            else
            {
                bR = g_GaugeComm.Read3(pDoc->m_CommSettingsData.m_ucGaugeAddress[i], 
                    g_myDockablePaneData.m_dataRegion[i].fVoltageV, 
                    g_myDockablePaneData.m_dataRegion[i].fCurrentA, 
                    g_myDockablePaneData.m_dataRegion[i].fPowerW);
            }
			if (bR)
			{
// 				CString strTemp;
// 				strTemp.Format("%d %.2f %.3f %.3f",i,g_myDockablePaneData.m_dataRegion[i].fVoltageV, 
// 													g_myDockablePaneData.m_dataRegion[i].fCurrentA, 
// 													g_myDockablePaneData.m_dataRegion[i].fPowerW);
// 				g_strGaugeData[i + g_myDockablePaneData.m_TemperatureController.GetSize()].Add(strTemp);
	
				g_myDockablePaneData.m_dataRegion[i].bReadSuccessful = TRUE;
				if (data.m_bRegionAlarm[i] && (g_myDockablePaneData.m_dataRegion[i].fVoltageV < data.m_fVoltageL[i] || 
					g_myDockablePaneData.m_dataRegion[i].fVoltageV > data.m_fVoltageH[i]))
				{
					// Voltage alarm
					g_myDockablePaneData.m_dataRegion[i].bAlarmVoltage = TRUE;
					if (data.m_bRegionAlarm[i] && data.m_bStopTest && pDoc->IsRunning())
					{
						pDoc->OnMenuStop();
					}

					strTempInfo.Format("%s 电压报警！合理电压范围(%.1fV-->%.1fV)", 
						g_myDockablePaneData.m_strRegionText[i],
						data.m_fVoltageL[i], data.m_fVoltageH[i]);
					pDoc->ShowMessageDialog(strTempInfo, (AlarmType)(AT_REGION1 + i));
				}
				else
				{
					g_myDockablePaneData.m_dataRegion[i].bAlarmVoltage = FALSE;
				}
				if (data.m_bRegionAlarm[i] && (g_myDockablePaneData.m_dataRegion[i].fCurrentA < data.m_fCurrentL[i] ||
					g_myDockablePaneData.m_dataRegion[i].fCurrentA > data.m_fCurrentH[i]))
				{
					// Current alarm
					g_myDockablePaneData.m_dataRegion[i].bAlarmCurrent = TRUE;
					if (data.m_bRegionAlarm[i] && data.m_bStopTest && pDoc->IsRunning())
					{
						pDoc->OnMenuStop();
					}

					strTempInfo.Format("%s 电流报警！合理电流范围(%.1fA-->%.1fA)", 
						g_myDockablePaneData.m_strRegionText[i],
						data.m_fCurrentL[i], data.m_fCurrentH[i]);
					pDoc->ShowMessageDialog(strTempInfo, (AlarmType)(AT_REGION1 + i));
				}
				else
				{
					g_myDockablePaneData.m_dataRegion[i].bAlarmCurrent = FALSE;
				}
				if (data.m_bRegionAlarm[i] && (g_myDockablePaneData.m_dataRegion[i].fPowerW < data.m_fPowerL[i] ||
					g_myDockablePaneData.m_dataRegion[i].fPowerW > data.m_fPowerH[i]))
				{
					// Power alarm
					g_myDockablePaneData.m_dataRegion[i].bAlarmPower = TRUE;
					if (data.m_bRegionAlarm[i] && data.m_bStopTest && pDoc->IsRunning())
					{
						pDoc->OnMenuStop();
					}

					strTempInfo.Format("%s 功率报警！合理功率范围(%.1fW-->%.1fW)", 
						g_myDockablePaneData.m_strRegionText[i], data.m_fPowerL[i], data.m_fPowerH[i]);
					pDoc->ShowMessageDialog(strTempInfo, (AlarmType)(AT_REGION1 + i));
				}
				else
				{
					g_myDockablePaneData.m_dataRegion[i].bAlarmPower	= FALSE;
				}
			}
			else
			{
				g_myDockablePaneData.m_dataRegion[i].bReadSuccessful	= FALSE;
				g_myDockablePaneData.m_dataRegion[i].bAlarmCurrent		= FALSE;
				g_myDockablePaneData.m_dataRegion[i].bAlarmVoltage		= FALSE;
				g_myDockablePaneData.m_dataRegion[i].bAlarmPower		= FALSE;
			}
        }
		//保存监视数据信息
		if (1)
		{
			//
		}
		//发显示数据消息
		::PostMessageA(g_hDockablePaneDialog, MSG_DOCKABLE_PANE_UPDATE_INFO, 0, 0);
		Sleep(500);
		if (pDoc->m_bCloseDocument)
		{
			return 0;
		}
	}

	return 0;
}

UINT CLAT2000Doc::_ThreadGaugeTMP(LPVOID pPar)
{
	//温控
	CLAT2000Doc * pDoc = (CLAT2000Doc *)pPar;
	CAlarmSettingsData & data = pDoc->m_dataContainer.GetTestSettingData().m_AlarmSettingsData;
	CString strTempInfo;
	int iTMP1AlarmTimes[20];
	
	for (int i = 0; i < 20; i++)
	{
		iTMP1AlarmTimes[i] = 0;
	}
	while(1)
	{
		if(pDoc->m_bNeedSetTMP)
		{
			float fSetTMPDown;
			float fSetOpen;

			for (int i = 0; i < g_myDockablePaneData.m_strSetTMP.GetSize(); i++)
			{
		
				if(1)//i % 4 == 0)
				{
					fSetTMPDown = pDoc->m_dataContainer.GetTestSettingData().m_AlarmSettingsData.m_fTMPL[i];
					fSetOpen = pDoc->m_dataContainer.GetTestSettingData().m_AlarmSettingsData.m_fTMPOPEN[i];
				}
				if (!g_FujiTMPComm.SetTemperature(g_FujiTMPComm.m_ucAddress[i], 0.0, fSetTMPDown, fSetOpen) )
				{
					Sleep(100);
					if (!g_FujiTMPComm.SetTemperature(g_FujiTMPComm.m_ucAddress[i], 0.0, fSetTMPDown, fSetOpen) )
					{
						Sleep(100);
						if (!g_FujiTMPComm.SetTemperature(g_FujiTMPComm.m_ucAddress[i], 0.0, fSetTMPDown, fSetOpen) )
						{
							break;
						}
						else
						{
							pDoc->m_bNeedSetTMP = FALSE;
						}
					}
				}
			}

		}
		if (pDoc->m_bCloseDocument)
		{
			return 0;
		}
        int i = 0;
        BOOL bR = FALSE;

        // TMP
        for (i = 0; i < g_myDockablePaneData.m_TemperatureController.GetSize(); i ++)
        {
			if (pDoc->m_bCloseDocument)
			{
				return 0;
			}
            bR = FALSE;
            bR = g_FujiTMPComm.ReadTemperature(pDoc->m_CommSettingsData.m_ucTemperatureAddress[i],
				g_myDockablePaneData.m_TemperatureController[i].m_fTMP, g_myDockablePaneData.m_TemperatureController[i].m_nAlarm);
            if (!bR)
            { 
                Sleep(200);
                bR = g_FujiTMPComm.ReadTemperature(pDoc->m_CommSettingsData.m_ucTemperatureAddress[i],
					g_myDockablePaneData.m_TemperatureController[i].m_fTMP, g_myDockablePaneData.m_TemperatureController[i].m_nAlarm);
            }
            if (bR)
            {
				//CString strTemp;
				//strTemp.Format("%d %.1f",i+1,g_myDockablePaneData.m_TemperatureController[i].m_fTMP);
				//g_strGaugeData[i].Add(strTemp);
                g_myDockablePaneData.m_TemperatureController[i].m_bTMPReadSuccessful = TRUE;
                if (data.m_bTMPAlarm[i] && (g_myDockablePaneData.m_TemperatureController[i].m_fTMP < data.m_fTMPL[i] || g_myDockablePaneData.m_TemperatureController[i].m_fTMP > data.m_fTMPH[i]))
                {
                    g_myDockablePaneData.m_TemperatureController[i].m_bTMPAlarm = TRUE;
                    iTMP1AlarmTimes[i]++;

                    if (iTMP1AlarmTimes[i] >= 3)
                    {
                        if (data.m_bTMPAlarm[i] && data.m_bStopTest && pDoc->IsRunning())
                        {
                            pDoc->OnMenuStop();
                        }

                        strTempInfo.Format("%s 温度报警！合理温度范围(%.1f℃-->%.1f℃)", 
                            g_myDockablePaneData.m_strTemperatureControllerText[i],
                            data.m_fTMPL[i], data.m_fTMPH[i]);
                        pDoc->ShowMessageDialog(strTempInfo, (AlarmType)(AT_TMP1 + i));
                    }
                }
                else
                {
                    iTMP1AlarmTimes[i] = 0;
                    g_myDockablePaneData.m_TemperatureController[i].m_bTMPAlarm = FALSE;
                } 
            }
            else
            {
                g_myDockablePaneData.m_TemperatureController[i].m_bTMPAlarm = FALSE;
                g_myDockablePaneData.m_TemperatureController[i].m_bTMPReadSuccessful = FALSE;
            }
        }
								
		//发显示数据消息
		::PostMessageA(g_hDockablePaneDialog, MSG_DOCKABLE_PANE_UPDATE_TMP, 0, 0);
		Sleep(500);
		if (pDoc->m_bCloseDocument)
		{
			return 0;
		}
	}

	return 0;
}

void CLAT2000Doc::OnButtonEditLimit()
{
	// TODO: 在此添加命令处理程序代码
	CEditLimitDlg dlg;
	g_bDisplayLimitOnly = FALSE;
	dlg.m_LimitData = m_dataContainer.GetTestSettingData();

	dlg.m_bHaveVoltageUpAndDips = m_CommSettingsData.m_bHaveEMS61000_11K;
	dlg.m_bHaveBurnIn = TRUE;
	dlg.m_bHaveLightning = m_CommSettingsData.m_bHaveEMS61000_5A;


	dlg.DoModal();

	m_dataContainer.GetTestSettingData() = dlg.m_LimitData;
	CString strSection = "LAT2000Doc";
	g_Hass1200Meter.SetIntTime(m_dataContainer.GetTestSettingData().m_fIntegralTimems);
    m_TestContainer.SetDirectionOpposite(m_dataContainer.GetTestSettingData().m_bTestDirectionOpposite);
	::PostMessage(m_hWndTestFormView, MSG_LIMIT_FILE_RELIST, 0, 0);
	::PostMessage(m_hWndStatisticGridView, MSG_STATISTIC_GRID_RELIST_DATA, 0, 0);
	::PostMessage(m_hWndStatisticDisbuteGridView, MSG_STATISTIC_DIS_GRID_RELIST_DATA, 0, 0);
	m_dataContainer.GetTestSettingData().Store(g_strTestSettingFileName);
	m_bNeedSetTMP = TRUE;
}


void CLAT2000Doc::OnButtonSpectrumCal()
{
	// TODO: 在此添加命令处理程序代码
	if (m_CommSettingsData.m_iTestChannelControlerType == 1)
	{
		if (!g_SC1000Comm.SwitchAllLamp(FALSE))
		{
			AfxMessageBox("关闭LED灯失败！");
		}
	}
	else
	{
		if (!g_TestChannelControlComm.SwitchAllChannel(FALSE))
		{
			AfxMessageBox("关闭LED灯失败！");
		}
	}
 		
    BOOL bR;
    if (m_CommSettingsData.m_iStandardSupplyType == 0)
    {
        CStandardLampSettingsDlg dlg;
        if (IDCANCEL == dlg.DoModal())
        {
            return;
        }

        CString strTemp;
        strTemp.Format("确定以 %.1f mA(保护电压：%.1fV) 电流打开标准灯？\n如果标准灯已经打开，请选择 否(N) 直接开始定标。", 
            dlg.m_fCurrent, dlg.m_fProtectVoltage);
        int iReturn = AfxMessageBox(strTemp, MB_YESNOCANCEL | MB_ICONQUESTION);

        if ( IDYES ==  iReturn)
        {
            BeginWaitCursor();
            float f1, f2;
            if (re_ok != g_WYComm.SetPower(sele_i, dlg.m_fProtectVoltage, dlg.m_fCurrent / 1000, f1, f2, TRUE))
            {
                return;
            }
        }
    }
 	else
    {
		CStandardLampSettingsDlg dlg;
		if (IDCANCEL == dlg.DoModal())
		{
			return;
		}

		CString strTemp;
		strTemp.Format("确定以 %.1f mA(保护电压：%.1fV) 电流打开标准灯？\n如果标准灯已经打开，请选择 否(N) 直接开始定标。", 
			dlg.m_fCurrent, dlg.m_fProtectVoltage);
		int iReturn = AfxMessageBox(strTemp, MB_YESNOCANCEL | MB_ICONQUESTION);

		if ( IDYES ==  iReturn)
		{
			BeginWaitCursor();
			bR = g_HLS_200.SetCurr( dlg.m_fCurrent * 10);
			if (!bR)
			{
				return;
			}

			BOOL Output, Load, Warning;
			BOOL bR = g_HLS_200.GetState(Output,Load,Warning);
			if (!bR)
			{
				ShowMessageDialog("标准灯电源未连接！");
				return;
			}

			bR = g_HLS_200.OpenOutput();

			if (!bR)
			{
				ShowMessageDialog("开标准灯失败！");
				return;
			}
			CDlgShowOtherNote dlg;
			dlg.SetNote("标准灯电流调整中，请等待", 6);
			dlg.DoModal();
			bR = g_HLS_200.GetState(Output,Load,Warning);
			if (!Load)
			{
				ShowMessageDialog("负载未连接！");
				return;
			}
			if (Warning)
			{
				ShowMessageDialog("电路短路！");
				return;
			}
		}
    }

	g_Hass1200Meter.ShowSpectrumCalDlg();

	if (IDYES == AfxMessageBox("是否关闭标准灯？", MB_YESNO))
	{
		BeginWaitCursor();
        if (m_CommSettingsData.m_iStandardSupplyType == 0)
        {
            bR = g_WYComm.Reset(FALSE);
        }
        else
        {
            bR = g_HLS_200.CloseOutput();
        }
		EndWaitCursor();

		if (!bR)
		{
			AfxMessageBox("关闭标准灯失败！");
		}
	}
}


BOOL CLAT2000Doc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (IsRunning())
	{
		AfxMessageBox("测试正在进行，请等待测试结束后再保存。");
		return FALSE;
	}

	return CDocument::OnSaveDocument(lpszPathName);
}


void CLAT2000Doc::OnUpdateFileSaveAs(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(!IsRunning() && !IsContinueMoveOneStepRunning());
}


void CLAT2000Doc::OnUpdateFileOpen(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(!IsRunning() && !IsContinueMoveOneStepRunning());
}


void CLAT2000Doc::OnMenuTest()
{
	//查找同名文件
	g_bDemo = m_systemSettingsData.m_bDemo;
	m_bSetStop = FALSE;
		
	BeginWaitCursor();
	if (m_dataContainer.GetTestSettingData().m_bTestAutoHand)
	{
		//机械手开始上灯的板号
		CDlgCurrentBroad dlg;
		//起始板号变成了当前板号

		dlg.m_iTolBroadNum		= m_iHaveInLampBroadNum;
		dlg.m_iCurrentBroadID	= m_iStartInLampBroad;
		dlg.m_iTestStartLEDID	= m_systemSettingsData.m_iCurrentLEDID;
		if (IDCANCEL == dlg.DoModal())
		{
			m_bSetStop = TRUE;
			return;
		}
		m_iHaveInLampBroadNum	= dlg.m_iTolBroadNum;
		m_iStartInLampBroad		= dlg.m_iCurrentBroadID;
		m_iCurrentInLampBroad	= m_iStartInLampBroad;
		m_systemSettingsData.m_iCurrentLEDID = dlg.m_iTestStartLEDID;
	}
    else if (!m_CommSettingsData.m_bHaveScaner)
    {
        CCurrentLEDID_Dlg dlg;
        dlg.m_iCurrentLEDID = m_systemSettingsData.m_iCurrentLEDID;
        if (IDCANCEL == dlg.DoModal())
        {
			m_bSetStop = TRUE;
            return;
        }
        m_systemSettingsData.m_iCurrentLEDID = dlg.m_iCurrentLEDID;
    }
    else
    {
        CCurrentBoardID_Dlg dlg;
        dlg.m_iCurrentBoardID		= m_systemSettingsData.m_iCurrentBoardID;
		dlg.m_iLEDOnPos				= m_systemSettingsData.m_iLEDOnPos;
		dlg.m_iTestHaveScanedMode	= m_systemSettingsData.m_iTestHaveScanedMode;
        if (IDCANCEL == dlg.DoModal())
        {
			m_bSetStop = TRUE;
            return;
        }
        m_systemSettingsData.m_iCurrentBoardID		= dlg.m_iCurrentBoardID;
		m_systemSettingsData.m_iLEDOnPos			= dlg.m_iLEDOnPos;
		m_systemSettingsData.m_iTestHaveScanedMode	= dlg.m_iTestHaveScanedMode;
    }
    // Set Burn in Times
    BOOL bR;
    if (m_dataContainer.GetTestSettingData().m_bTestBurnIn)
    {
        bR = g_LineControllerComm.SetOldTime((float)m_dataContainer.GetTestSettingData().m_iBurnInONSeconds, (float)m_dataContainer.GetTestSettingData().m_iBurnInOFFSeconds);
    }
    else
    {
        bR = g_LineControllerComm.SetOldTime(1.0f, 0.0f);	// Always be ON
    }
    if (!bR)
    {
		m_bSetStop = TRUE;
        ShowMessageDialog("开关老炼参数设置失败!");
        return;
    }
	// Set Powmeter auto range

//	g_LineControllerComm.SetShowLED(1);

	CString strTemp;
	strTemp.Format("当前测试电源输出电压为%gV，频率为%gHz, 是否控制电源输出?", 
		m_dataContainer.GetTestSettingData().m_fTestVoltageV, 
		m_dataContainer.GetTestSettingData().m_fTestFrquencyHz);
	CWarningYesNODlg WarningYesNODlg;
	WarningYesNODlg.m_strInfo = strTemp;
	if (IDCANCEL == WarningYesNODlg.DoModal())
	{
		m_bSetStop = TRUE;
		return;
	}
    // Set DPS if SetParaChanged
    if (g_DPSComm.IsRunning())
    {
        RealTimeData data;
        bR = g_DPSComm.GetRealTimeData(data);
        float fVoltage = g_pDoc->m_dataContainer.GetTestSettingData().m_fTestVoltageV, 
            fFrequency = g_pDoc->m_dataContainer.GetTestSettingData().m_fTestFrquencyHz;
        if (fabs(data.fVoltageValue - fVoltage) > fVoltage / 100 || fabs(data.fFrequence - fFrequency) > fFrequency / 100)
        {
            bR = g_DPSComm.SetParameterRunning(g_pDoc->m_dataContainer.GetTestSettingData().m_fTestVoltageV, g_pDoc->m_dataContainer.GetTestSettingData().m_fTestFrquencyHz,
                g_DPSComm.GetLimitData().LimitCurrentRange2.fUpper, g_DPSComm.GetLimitData().LimitPower.fUpper);
        }
    }
    else
    {
        g_DPSComm.StopOutput();
        bR = g_DPSComm.FastRun(g_pDoc->m_dataContainer.GetTestSettingData().m_fTestVoltageV, g_pDoc->m_dataContainer.GetTestSettingData().m_fTestFrquencyHz);
    }
    if (!bR)
    {
		m_bSetStop = TRUE;
        ShowMessageDialog("测试电源控制失败!");
        return;
    }

	if (g_bInputPower)
	{
		CDlgInputPower dlg;
		dlg.m_fInputCurr	= g_fInputCurr;
		dlg.m_fInputVol		= g_fInputVol;
		dlg.m_fInputPower	= g_fInputPower;
		dlg.m_fInputPF		= g_fInputPF;

		if (IDCANCEL == dlg.DoModal())
		{
			m_bSetStop = TRUE;
			return;
		}

		g_fInputCurr	= dlg.m_fInputCurr;
		g_fInputVol		= dlg.m_fInputVol;
		g_fInputPower	= dlg.m_fInputPower;
		g_fInputPF		= dlg.m_fInputPF;
	}


	//
	if(m_dataContainer.GetTestSettingData().m_bTestMyLast)
		AfxBeginThread(_ThreadMyLastTest, this);

	m_eventTest.SetEvent();
	::PostMessageA(m_hWndTestFormView, MSG_TEST_STARTED, 0, 0);
	Sleep(100);
	EndWaitCursor();
}


BOOL CLAT2000Doc::IsRunning()
{
	return m_bIsElectricalRunning 
		|| m_bIsLightningSurgeRunning 
		|| m_bIsSpectrumRunning 
		|| m_bIsVoltageDipsAndUPRunning 
		|| m_bIsLineControlRunning 
		|| m_bIsScanerRunning
		|| m_bIsSaftJYDZRunning
		|| m_bIsSaftNYYRunning
		|| m_bIsSaftXLDLRunning
		|| m_bIsHandAutoRunning;
}

BOOL CLAT2000Doc::IsContinueMoveOneStepRunning()
{
	return m_bComtinueMoveRunning;
}


void CLAT2000Doc::OnUpdateButtonTest(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(!IsRunning() && !IsContinueMoveOneStepRunning());
}


void CLAT2000Doc::OnMenuStop()
{
	// TODO: 在此添加命令处理程序代码
	if (g_bhaveSaveFile == FALSE && g_pDoc->m_dataContainer.GetSize())
	{

		if (!g_pDoc->m_systemSettingsData.m_bAutoSave)
		{

		}
		else
		{
			CString strPathName;
			CTime tNow = CTime::GetCurrentTime();
			if (!g_pDoc->m_systemSettingsData.m_iPrefixInputMode)
			{
				strPathName = g_pDoc->m_systemSettingsData.m_strFilePath + "\\" + 
					g_pDoc->m_systemSettingsData.m_strFileName + tNow.Format("%Y-%m-%d %H-%M-%S.lat2000-everfine");
			}
			else
			{
				strPathName = g_pDoc->m_systemSettingsData.m_strFilePath + "\\" + 
					g_pDoc->m_dataContainer.GetTestSettingData().m_strLedModel + tNow.Format("%Y-%m-%d %H-%M-%S.lat2000-everfine");
			}
			g_pDoc->m_dataContainer.SaveFile(strPathName);
			DeleteFileA(g_strHaveSaveFileName);
			g_strHaveSaveFileName = strPathName;

			strPathName.Replace(".lat2000-everfine","");
			g_strPathNameAuto = strPathName+".csv";
			::PostMessageA(g_pDoc->m_hWndDataContainerGridView, MSG_SAVE_CSV_DATA, 0, 0);

		}

		g_bhaveSaveFile = TRUE;
	}

	BeginWaitCursor();
	m_eventStartOne.ResetEvent();
	m_eventTest.ResetEvent();
    g_ScanerComm.SetStop();
	m_bSetStop = TRUE;
	Sleep(200);

	g_LineControllerComm.SetShowLED(0);

	EndWaitCursor();
}


void CLAT2000Doc::OnUpdateButtonPause(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(IsRunning() || IsContinueMoveOneStepRunning());
}


void CLAT2000Doc::OnUpdateIndicatorTestInfo(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetText(m_strInfo);
}


void CLAT2000Doc::OnUpdateIndicatorStatisticInfo(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
    CView *pView;
    CMainTabWnd *pMainTabWnd;
    POSITION pos = GetFirstViewPosition();  
    CString strTemp;
    while(pos)
    {
        pView = GetNextView(pos);
        if (pView->IsKindOf(RUNTIME_CLASS(CMainTabWnd)))
        {
            pMainTabWnd =  (CMainTabWnd*)pView;
            if (pMainTabWnd->GetActiveView()->IsKindOf(RUNTIME_CLASS(CLEDDataStatView)))
            {    
                strTemp.Format("灯型号%s，标称电压:%gV,标称功率:%gW,标称光通量:%glm,标称色温:%gK",
                    m_StatisticLedDataContainer.GetTestSettingData().m_strLedModel,
                    m_StatisticLedDataContainer.GetTestSettingData().m_fStaVol,
                    m_StatisticLedDataContainer.GetTestSettingData().m_fStaPow,
                    m_StatisticLedDataContainer.GetTestSettingData().m_fStaFlux,
                    m_StatisticLedDataContainer.GetTestSettingData().m_fStaTc);
                pCmdUI->SetText(strTemp);
            }
            else
            {
                pCmdUI->SetText("");
            }
            break;
        }
    }
    pCmdUI->Enable(TRUE);
}


void CLAT2000Doc::OnDebug()
{
	// TODO: 在此添加命令处理程序代码
	CSheetDebug sheet("系统调试");

	CDebugA90Page pageA90;
	sheet.AddPage(&pageA90);

	CDebugDPSPage pageDPS;
	sheet.AddPage(&pageDPS);

	CDebugWYPage pageWY;
	sheet.AddPage(&pageWY);

	CDebugSC1600Page pageSC1600;
	sheet.AddPage(&pageSC1600);

	CDebugPF2010APage pagePF2010A;
	sheet.AddPage(&pagePF2010A);

	CDebugIndicatorPage pageIndicator;
	sheet.AddPage(&pageIndicator);

	CDebugGaugePage pageGauge;
	sheet.AddPage(&pageGauge);

	CDebugTemperaturePage pageTemperature;
	sheet.AddPage(&pageTemperature);

	CDebugEMS61000_11KPage page11K;
	sheet.AddPage(&page11K);

	CDebugEMS61000_5APage page5A;
	sheet.AddPage(&page5A);

	CDebugLRAPage pageLRA;
	sheet.AddPage(&pageLRA);   
       
    CDebugBribePage pageBribe;
    sheet.AddPage(&pageBribe);

	CDebugThunderRelayPage pageThunderRelay;
	sheet.AddPage(&pageThunderRelay);

	CDebugLineControllerPage pageLineController;
	sheet.AddPage(&pageLineController);

	CDebugPageHandAuto pageHandAuto;
	sheet.AddPage(&pageHandAuto);

    CDebugScanerPage pageScaner;
	sheet.AddPage(&pageScaner);

	CDebugTestChannelControler pageTestChannelControler;
    sheet.AddPage(&pageTestChannelControler);

	//CDlgDebugSaft pageSaft;
	//sheet.AddPage(&pageSaft);
	sheet.DoModal();
}


void CLAT2000Doc::OnUpdateDebug(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(g_iExecutionLevel == ADMIN_EXECUTION_LEVEL 
		&& !IsRunning() && !IsContinueMoveOneStepRunning());
	if (ADMIN_EXECUTION_LEVEL != g_iExecutionLevel)
	{
		pCmdUI->SetText("----");
	}
	else
	{
		pCmdUI->SetText("调试");
	}
}


void CLAT2000Doc::OnUpdateButtonSpectrumCal(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(!IsRunning() && LOW_EXECUTION_LEVEL != g_iExecutionLevel
		&& !IsContinueMoveOneStepRunning());
    if (LOW_EXECUTION_LEVEL == g_iExecutionLevel)
    {
        pCmdUI->SetText("光谱定标");
    }
    else
    {
        pCmdUI->SetText("光谱定标");
    }
}


void CLAT2000Doc::OnUpdateModifyProtectPassword(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
    if (HIGH_EXECUTION_LEVEL != g_iExecutionLevel)
    {
        pCmdUI->Enable(FALSE);
        pCmdUI->SetText("----");
    }
    else
    {
        pCmdUI->SetText("修改管理员权限密码");
    }
}


void CLAT2000Doc::OnModifyProtectPassword()
{
	// TODO: 在此添加命令处理程序代码
	CModifyCalProtectPassword dlg;
	dlg.DoModal();
}


void CLAT2000Doc::OnMakeRegion()
{
	// TODO: 在此添加命令处理程序代码
	SDCM_DLL_Dlg_Domodal();
// 	Region_ShowEditRegionDlg();
// 
// 	CString strPahtName = g_strCurrentPath + "Region.rgn";
// 	Region_SaveFile(strPahtName.GetBuffer());
// 
// 	::PostMessage(m_hWndDataListView, MSG_REGION_RELIST, 0, 0);

}


void CLAT2000Doc::OnUpdateMakeRegion(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(g_iExecutionLevel != LOW_EXECUTION_LEVEL);
	if (LOW_EXECUTION_LEVEL == g_iExecutionLevel)
	{
		pCmdUI->SetText("----");
	}
}


void CLAT2000Doc::OnColorOffsetEdit()
{
	// TODO: 在此添加命令处理程序代码
	NewCorrectColorParaDLL_Edit();
}


void CLAT2000Doc::OnUpdateColorOffsetEdit(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (!g_bColorCorrection)
	{
		pCmdUI->Enable(FALSE);
		pCmdUI->SetText("----");
	}
	else
	{
		pCmdUI->Enable(TRUE);
	}
}


void CLAT2000Doc::OnColorOffsetSelect()
{
	// TODO: 在此添加命令处理程序代码
	NewCorrectColorParaDLL_Select();
}


void CLAT2000Doc::OnUpdateColorOffsetSelect(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (!g_bColorCorrection)
	{
		pCmdUI->Enable(FALSE);
		pCmdUI->SetText("----");
	}
	else
	{
		pCmdUI->Enable(TRUE);
	}
}


void CLAT2000Doc::OnUpdateCommSettings(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
    pCmdUI->Enable(g_iExecutionLevel == ADMIN_EXECUTION_LEVEL  && !IsRunning()
		&& !IsContinueMoveOneStepRunning());
    if (ADMIN_EXECUTION_LEVEL != g_iExecutionLevel)
    {
        pCmdUI->SetText("----");
    }
    else
    {
        pCmdUI->SetText("通信设置");
    }
}


void CLAT2000Doc::OnCommSettings()
{
	// TODO: 在此添加命令处理程序代码
    CMySheet Configsheet("出厂配置");
    CConfigure_AssistantPage	Configure_AssistantPage;
    CConfigure_ExaminationPage	Configure_ExaminationPage;
    CConfigure_IndicatorPage	Configure_IndicatorPage;
    CConfigure_OthersPage		Configure_OthersPage;
    CConfigure_TestControlPage	Configure_TestControlPage;
    CConfigure_WatchPage		Configure_WatchPage;
    
	Configsheet.AddPage(&Configure_TestControlPage);
    Configsheet.AddPage(&Configure_IndicatorPage);
    Configsheet.AddPage(&Configure_AssistantPage);
    Configsheet.AddPage(&Configure_WatchPage);
    Configsheet.AddPage(&Configure_ExaminationPage);
    Configsheet.AddPage(&Configure_OthersPage);
 
	//CConfigure_TestControlPage
    Configure_TestControlPage.m_bDynamometer			= m_CommSettingsData.m_bHavePF2010A;
    Configure_TestControlPage.m_bTestChannelController	= m_CommSettingsData.m_bHaveTestChannelController;
    Configure_TestControlPage.m_bSpectrometer			= m_CommSettingsData.m_bHaveA90;
    Configure_TestControlPage.m_bStandardSupply			= m_CommSettingsData.m_bStandardSupply;
    Configure_TestControlPage.m_bLineController			= m_CommSettingsData.m_bHaveLineController;
    Configure_TestControlPage.m_bTestSupply				= m_CommSettingsData.m_bHaveDPS;
    Configure_TestControlPage.m_bThunderRelay			= m_CommSettingsData.m_bHaveThunderRelay;

	Configure_TestControlPage.m_bHaveSaft_NYY	= m_CommSettingsData.m_bHaveSaft_NYY;
	Configure_TestControlPage.m_bHaveSaft_JYDZ	= m_CommSettingsData.m_bHaveSaft_JYDZ;
	Configure_TestControlPage.m_bHaveSaft_XLDL	= m_CommSettingsData.m_bHaveSaft_XLDL;
	
	Configure_TestControlPage.m_iTypeSaftNyy	= m_CommSettingsData.m_iTypeSaftNyy;
	Configure_TestControlPage.m_iTypeSaftJydz	= m_CommSettingsData.m_iTypeSaftJydz;
	Configure_TestControlPage.m_iTypeSaftXLDL	= m_CommSettingsData.m_iTypeSaftXLDL;
	
	Configure_TestControlPage.m_strSaftNyyCOM	= m_CommSettingsData.m_strSaftNyyCOM;
	Configure_TestControlPage.m_strSaftXLDLCOM	= m_CommSettingsData.m_strSaftXLDLCOM;
	Configure_TestControlPage.m_strSaftJydzCOM	= m_CommSettingsData.m_strSaftJydzCOM;
	Configure_TestControlPage.m_strComNyy2		= m_CommSettingsData.m_strComNyy2;
	Configure_TestControlPage.m_strComJydz2		= m_CommSettingsData.m_strComJydz2;
	Configure_TestControlPage.m_strComXldl2		= m_CommSettingsData.m_strComXldl2;

	Configure_TestControlPage.m_bHaveMyLast		= m_CommSettingsData.m_bHaveMyLast;
	switch(m_CommSettingsData.m_iMyLastPowerType)
	{
	case DPS_1005:
		Configure_TestControlPage.m_iMyLastPowerType = 0;
		break;
	case DPS_1005_V100:
		Configure_TestControlPage.m_iMyLastPowerType = 1;
		break;
	case DPS_1010:
		Configure_TestControlPage.m_iMyLastPowerType = 2;
		break;
	case DPS_1010_V100:
		Configure_TestControlPage.m_iMyLastPowerType = 3;
		break;
	case DPS_1020:
		Configure_TestControlPage.m_iMyLastPowerType = 4;
		break;
	case DPS_1020_V100:
		Configure_TestControlPage.m_iMyLastPowerType = 5;
		break;
	case DPS_1030V200_65:
		Configure_TestControlPage.m_iMyLastPowerType = 6;
		break;
	case DPS_1030V200_450:    
		Configure_TestControlPage.m_iMyLastPowerType = 7;
		break;
	case DPS_1060V200_65:
		Configure_TestControlPage.m_iMyLastPowerType = 8;
		break;
	case DPS_1060V200_450:
		Configure_TestControlPage.m_iMyLastPowerType = 9;
		break;
	default:
		Configure_TestControlPage.m_iMyLastPowerType = 0;
		break;
	}
	Configure_TestControlPage.m_strMyLastCOM				= m_CommSettingsData.m_strMyLastCOM;
      
    Configure_TestControlPage.m_strDynamometerCOM			= m_CommSettingsData.m_strCOMPF2010A;
    Configure_TestControlPage.m_strTestChannelControllerCOM = m_CommSettingsData.m_strCOMTestChannelController;
    Configure_TestControlPage.m_strStandardSupplyCOM		= m_CommSettingsData.m_strStandardSupplyCOM;
    Configure_TestControlPage.m_strLineControllerCOM		= m_CommSettingsData.m_strLineControllerCOM;       
    Configure_TestControlPage.m_strTestSupplyCOM			= m_CommSettingsData.m_strCOMDPS;
    Configure_TestControlPage.m_strThunderRelayCOM			= m_CommSettingsData.m_strThunderRelayCOM;
    Configure_TestControlPage.m_strAgePowerCOM[0]			= m_CommSettingsData.m_strAgePowerCOM[0];
    Configure_TestControlPage.m_strAgePowerCOM[1]			= m_CommSettingsData.m_strAgePowerCOM[1];
    Configure_TestControlPage.m_bfor4A						= m_CommSettingsData.m_bfor4A;
	Configure_TestControlPage.m_iTestChannelControlerType	= m_CommSettingsData.m_iTestChannelControlerType;
   
	switch(m_CommSettingsData.m_iDPSType)
    {
    case DPS_1005:
        Configure_TestControlPage.m_iDPSTypeIndex = 0;
        break;
    case DPS_1005_V100:
        Configure_TestControlPage.m_iDPSTypeIndex = 1;
        break;
    case DPS_1010:
        Configure_TestControlPage.m_iDPSTypeIndex = 2;
        break;
    case DPS_1010_V100:
        Configure_TestControlPage.m_iDPSTypeIndex = 3;
        break;
    case DPS_1020:
        Configure_TestControlPage.m_iDPSTypeIndex = 4;
        break;
    case DPS_1020_V100:
        Configure_TestControlPage.m_iDPSTypeIndex = 5;
        break;
    case DPS_1030V200_65:
        Configure_TestControlPage.m_iDPSTypeIndex = 6;
        break;
    case DPS_1030V200_450:    
        Configure_TestControlPage.m_iDPSTypeIndex = 7;
        break;
    case DPS_1060V200_65:
        Configure_TestControlPage.m_iDPSTypeIndex = 8;
        break;
    case DPS_1060V200_450:
        Configure_TestControlPage.m_iDPSTypeIndex = 9;
        break;
    default:
        Configure_TestControlPage.m_iDPSTypeIndex = 0;
        break;
    }
        
    Configure_TestControlPage.m_iPFType				= m_CommSettingsData.m_iPFType;
	Configure_TestControlPage.m_iStandardSupplyType = m_CommSettingsData.m_iStandardSupplyType;
    //CConfigure_IndicatorPage
    Configure_IndicatorPage.m_bLEDIndicator			= m_CommSettingsData.m_bHaveLEDIndicator;
    Configure_IndicatorPage.m_bLRA					= m_CommSettingsData.m_bHaveLRA;
    Configure_IndicatorPage.m_bBribe				= m_CommSettingsData.m_bBribe;
       
    Configure_IndicatorPage.m_strLEDIndicatorCOM	= m_CommSettingsData.m_strCOMLEDIndicator;
    Configure_IndicatorPage.m_strLRACOM				= m_CommSettingsData.m_strLRACOM;
    Configure_IndicatorPage.m_strBribeCOM			= m_CommSettingsData.m_strBribeCOM;
	Configure_IndicatorPage.m_iBribeAddr			= m_CommSettingsData.m_iBribeAddr;
	Configure_IndicatorPage.m_iBribeAddr2			= m_CommSettingsData.m_iBribeAddr2;
       
    Configure_IndicatorPage.m_strIndicatorRange		= m_CommSettingsData.m_strIndicatorRange;
    Configure_IndicatorPage.m_strBribeRange			= m_CommSettingsData.m_strBribeRange;

    //CConfigure_AssistantPage
    Configure_AssistantPage.m_bHaveScaner			= m_CommSettingsData.m_bHaveScaner;
	Configure_AssistantPage. m_strScanerCOM			= m_CommSettingsData.m_strScanerCOM;
    
	Configure_AssistantPage.m_bHaveHandAuto			= m_CommSettingsData.m_bHaveHandAuto;
	Configure_AssistantPage.m_strHandAutoCOM		= m_CommSettingsData.m_strHandAutoCOM;
	Configure_AssistantPage.m_strHandAutoRange1		= m_CommSettingsData.m_strHandAutoRange1;
	Configure_AssistantPage.m_strHandAutoRange2		= m_CommSettingsData.m_strHandAutoRange2;

    //CConfigure_WatchPage
    Configure_WatchPage.m_bGauge					= m_CommSettingsData.m_bHaveGauge;
    Configure_WatchPage.m_bTemperatureController	= m_CommSettingsData.m_bHaveTemperatureContrller;
       
    Configure_WatchPage.m_strGaugeCOM				= m_CommSettingsData.m_strCOMGauge;
    Configure_WatchPage.m_strTemperatureContrllerCOM= m_CommSettingsData.m_strCOMTemperature;
       

    for (int i = 0; i < g_iGaugeNum; i ++)
    {
        Configure_WatchPage.m_ucGaugeAddress[i] = m_CommSettingsData.m_ucGaugeAddress[i];
    }
    for (int i = 0; i < g_iTMPControlNum; i ++)
    {
        Configure_WatchPage.m_ucTemperatureAddress[i] = m_CommSettingsData.m_ucTemperatureAddress[i];
    }
    //CConfigure_ExaminationPage
    Configure_ExaminationPage.m_bLightning					= m_CommSettingsData.m_bHaveEMS61000_5A;       
    Configure_ExaminationPage.m_bVoltageUpAndDips			= m_CommSettingsData.m_bHaveEMS61000_11K;
       
    Configure_ExaminationPage.m_strLightningCOM				= m_CommSettingsData.m_strCOMEMS61000_5A;      
    Configure_ExaminationPage.m_strVoltageUpAndDipsCOM		= m_CommSettingsData.m_strCOMEMS61000_11K;

    //CConfigure_OthersPage
    Configure_OthersPage.m_strCalibrationRange				= m_CommSettingsData.m_strCalibrationRange;
    Configure_OthersPage.m_iTotalBoard						= m_CommSettingsData.m_iTotalBoard;
    Configure_OthersPage.m_iLEDTestAndLEDDownRange			= m_CommSettingsData.m_iLEDTestAndLEDDownRange;
    Configure_OthersPage.m_iLEDOnAndLEDTestRange			= m_CommSettingsData.m_iLEDOnAndLEDTestRange;
	Configure_OthersPage.m_iSpectialLEDOnAndLEDTestRange	= m_CommSettingsData.m_iSpectialLEDOnAndLEDTestRange;
	Configure_OthersPage.m_iJydzLedTestRange				= m_CommSettingsData.m_iJydzLedTestRange;	//绝缘电阻工位到测试光色电工位
	Configure_OthersPage.m_iNyyLedTestRange					= m_CommSettingsData.m_iNyyLedTestRange;	//绝缘电阻工位到测试光色电工位
	Configure_OthersPage.m_iXldlLedTestRange				= m_CommSettingsData.m_iXldlLedTestRange;	//绝缘电阻工位到测试光色电工位
	
    if (IDOK == Configsheet.DoModal())
    {
        //CConfigure_TestControlPage
        m_CommSettingsData.m_bHavePF2010A				= Configure_TestControlPage.m_bDynamometer;
        m_CommSettingsData.m_bHaveTestChannelController = Configure_TestControlPage.m_bTestChannelController;
        m_CommSettingsData.m_bHaveA90					= Configure_TestControlPage.m_bSpectrometer;
        m_CommSettingsData.m_bStandardSupply			= Configure_TestControlPage.m_bStandardSupply;
        m_CommSettingsData.m_bHaveLineController		= Configure_TestControlPage.m_bLineController;
        m_CommSettingsData.m_bHaveDPS					= Configure_TestControlPage.m_bTestSupply;
        m_CommSettingsData.m_bHaveThunderRelay			= Configure_TestControlPage.m_bThunderRelay; 

        m_CommSettingsData.m_strCOMPF2010A					= Configure_TestControlPage.m_strDynamometerCOM;
        m_CommSettingsData.m_strCOMTestChannelController	= Configure_TestControlPage.m_strTestChannelControllerCOM; 
        m_CommSettingsData.m_strStandardSupplyCOM			= Configure_TestControlPage.m_strStandardSupplyCOM;  
        m_CommSettingsData.m_strLineControllerCOM			= Configure_TestControlPage.m_strLineControllerCOM;
        m_CommSettingsData.m_strCOMDPS						= Configure_TestControlPage.m_strTestSupplyCOM; 
        m_CommSettingsData.m_strThunderRelayCOM				= Configure_TestControlPage.m_strThunderRelayCOM;
        m_CommSettingsData.m_strAgePowerCOM[0]				= Configure_TestControlPage.m_strAgePowerCOM[0];
        m_CommSettingsData.m_strAgePowerCOM[1]				= Configure_TestControlPage.m_strAgePowerCOM[1];
        m_CommSettingsData.m_bfor4A							= Configure_TestControlPage.m_bfor4A;
	
		m_CommSettingsData.m_bHaveSaft_NYY		= Configure_TestControlPage.m_bHaveSaft_NYY;
		m_CommSettingsData.m_bHaveSaft_JYDZ		= Configure_TestControlPage.m_bHaveSaft_JYDZ;
		m_CommSettingsData.m_bHaveSaft_XLDL		= Configure_TestControlPage.m_bHaveSaft_XLDL;

		m_CommSettingsData.m_iTypeSaftNyy		= Configure_TestControlPage.m_iTypeSaftNyy;
		m_CommSettingsData.m_iTypeSaftJydz		= Configure_TestControlPage.m_iTypeSaftJydz;
		m_CommSettingsData.m_iTypeSaftXLDL		= Configure_TestControlPage.m_iTypeSaftXLDL;

		m_CommSettingsData.m_strSaftNyyCOM		= Configure_TestControlPage.m_strSaftNyyCOM;
		m_CommSettingsData.m_strSaftXLDLCOM		= Configure_TestControlPage.m_strSaftXLDLCOM;
		m_CommSettingsData.m_strSaftJydzCOM		= Configure_TestControlPage.m_strSaftJydzCOM;
		m_CommSettingsData.m_strComNyy2			= Configure_TestControlPage.m_strComNyy2;
		m_CommSettingsData.m_strComJydz2		= Configure_TestControlPage.m_strComJydz2;
		m_CommSettingsData.m_strComXldl2		= Configure_TestControlPage.m_strComXldl2;

		m_CommSettingsData.m_bHaveMyLast		= Configure_TestControlPage.m_bHaveMyLast;
		switch (Configure_TestControlPage.m_iMyLastPowerType)
		{
		case 0:
			m_CommSettingsData.m_iMyLastPowerType = DPS_1005;
			break;
		case 1:
			m_CommSettingsData.m_iMyLastPowerType = DPS_1005_V100;
			break;
		case 2:
			m_CommSettingsData.m_iMyLastPowerType = DPS_1010;
			break;
		case 3:
			m_CommSettingsData.m_iMyLastPowerType = DPS_1010_V100;
			break;
		case 4:        
			m_CommSettingsData.m_iMyLastPowerType = DPS_1020;
			break;
		case 5:
			m_CommSettingsData.m_iMyLastPowerType = DPS_1020_V100;
			break;
		case 6:
			m_CommSettingsData.m_iMyLastPowerType = DPS_1030V200_65;
			break;
		case 7:
			m_CommSettingsData.m_iMyLastPowerType = DPS_1030V200_450;
			break;
		case 8:
			m_CommSettingsData.m_iMyLastPowerType = DPS_1060V200_65;
			break;
		case 9:
			m_CommSettingsData.m_iMyLastPowerType = DPS_1060V200_450;
			break;
		default:
			m_CommSettingsData.m_iMyLastPowerType  = DPS_1010;
			break;
		}
		m_CommSettingsData.m_strMyLastCOM		= Configure_TestControlPage.m_strMyLastCOM;
       
		switch (Configure_TestControlPage.m_iDPSTypeIndex)
		{
		case 0:
			m_CommSettingsData.m_iDPSType = DPS_1005;
			break;
		case 1:
			m_CommSettingsData.m_iDPSType = DPS_1005_V100;
			break;
		case 2:
			m_CommSettingsData.m_iDPSType = DPS_1010;
			break;
		case 3:
			m_CommSettingsData.m_iDPSType = DPS_1010_V100;
			break;
		case 4:        
			m_CommSettingsData.m_iDPSType = DPS_1020;
			break;
		case 5:
			m_CommSettingsData.m_iDPSType = DPS_1020_V100;
			break;
		case 6:
			m_CommSettingsData.m_iDPSType = DPS_1030V200_65;
			break;
		case 7:
			m_CommSettingsData.m_iDPSType = DPS_1030V200_450;
			break;
		case 8:
			m_CommSettingsData.m_iDPSType = DPS_1060V200_65;
			break;
		case 9:
			m_CommSettingsData.m_iDPSType = DPS_1060V200_450;
			break;
		default:
			m_CommSettingsData.m_iDPSType  = DPS_1010;
			break;
		}
            
        m_CommSettingsData.m_iPFType					= Configure_TestControlPage.m_iPFType;
		m_CommSettingsData.m_iStandardSupplyType		= Configure_TestControlPage.m_iStandardSupplyType;
		m_CommSettingsData.m_iTestChannelControlerType	= Configure_TestControlPage.m_iTestChannelControlerType;
  

        //CConfigure_IndicatorPage
        m_CommSettingsData.m_bHaveLEDIndicator	= Configure_IndicatorPage.m_bLEDIndicator; 
        m_CommSettingsData.m_bHaveLRA			= Configure_IndicatorPage.m_bLRA;
        m_CommSettingsData.m_bBribe				= Configure_IndicatorPage.m_bBribe;

        m_CommSettingsData.m_strCOMLEDIndicator = Configure_IndicatorPage.m_strLEDIndicatorCOM;
        m_CommSettingsData.m_strLRACOM			= Configure_IndicatorPage.m_strLRACOM; 
        m_CommSettingsData.m_strBribeCOM		= Configure_IndicatorPage.m_strBribeCOM;
		m_CommSettingsData.m_iBribeAddr			= Configure_IndicatorPage.m_iBribeAddr;
		m_CommSettingsData.m_iBribeAddr2		= Configure_IndicatorPage.m_iBribeAddr2;
		
		//打点仪器地址码设置
		if (m_CommSettingsData.m_bBribe)
		{
			if (g_iHaveBribe == 0)
			{
				g_BribeComm.SetAddress(0xEE,0xCF);
			}
			else if (g_iHaveBribe == 1)
			{
				g_BribeComm.SetAddress(0xEE,m_CommSettingsData.m_iBribeAddr);
			}
			else
			{
				if (g_iSeleTestLamp == 0)
				{
					g_BribeComm.SetAddress(0xEE,m_CommSettingsData.m_iBribeAddr);
				}
				else
				{
					g_BribeComm.SetAddress(0xEE,m_CommSettingsData.m_iBribeAddr2);
				}
			}
		}
		

        m_CommSettingsData.m_strIndicatorRange	= Configure_IndicatorPage.m_strIndicatorRange;
        m_CommSettingsData.m_strBribeRange		= Configure_IndicatorPage.m_strBribeRange;

        //CConfigure_AssistantPage
        m_CommSettingsData.m_bHaveScaner		= Configure_AssistantPage.m_bHaveScaner;
		m_CommSettingsData.m_strScanerCOM		= Configure_AssistantPage. m_strScanerCOM;

		m_CommSettingsData.m_bHaveHandAuto		= Configure_AssistantPage.m_bHaveHandAuto;
        m_CommSettingsData.m_strHandAutoCOM		= Configure_AssistantPage.m_strHandAutoCOM ;
        m_CommSettingsData.m_strHandAutoRange1	= Configure_AssistantPage.m_strHandAutoRange1;
		m_CommSettingsData.m_strHandAutoRange2	= Configure_AssistantPage.m_strHandAutoRange2;

        //CConfigure_WatchPage
        m_CommSettingsData.m_bHaveGauge					= Configure_WatchPage.m_bGauge;
        m_CommSettingsData.m_bHaveTemperatureContrller	= Configure_WatchPage.m_bTemperatureController; 

        m_CommSettingsData.m_strCOMGauge				= Configure_WatchPage.m_strGaugeCOM;
        m_CommSettingsData.m_strCOMTemperature			= Configure_WatchPage.m_strTemperatureContrllerCOM;

        for (int i = 0; i < g_iGaugeNum; i ++)
        {
            m_CommSettingsData.m_ucGaugeAddress[i] = Configure_WatchPage.m_ucGaugeAddress[i];
        }
        for (int i = 0; i < g_iTMPControlNum; i ++)
        {
            m_CommSettingsData.m_ucTemperatureAddress[i] = Configure_WatchPage.m_ucTemperatureAddress[i];
        }
        //CConfigure_ExaminationPage
        m_CommSettingsData.m_bHaveEMS61000_5A	= Configure_ExaminationPage.m_bLightning;
        m_CommSettingsData.m_strCOMEMS61000_5A	= Configure_ExaminationPage.m_strLightningCOM; 
		m_CommSettingsData.m_bHaveEMS61000_11K	= Configure_ExaminationPage.m_bVoltageUpAndDips;
        m_CommSettingsData.m_strCOMEMS61000_11K = Configure_ExaminationPage.m_strVoltageUpAndDipsCOM;

        //CConfigure_OthersPage
        m_CommSettingsData.m_strCalibrationRange			= Configure_OthersPage.m_strCalibrationRange;
        m_CommSettingsData.m_iTotalBoard					= Configure_OthersPage.m_iTotalBoard;
        m_CommSettingsData.m_iLEDTestAndLEDDownRange		= Configure_OthersPage.m_iLEDTestAndLEDDownRange;
        m_CommSettingsData.m_iLEDOnAndLEDTestRange			= Configure_OthersPage.m_iLEDOnAndLEDTestRange;
		m_CommSettingsData.m_iSpectialLEDOnAndLEDTestRange	= Configure_OthersPage.m_iSpectialLEDOnAndLEDTestRange;
		m_CommSettingsData.m_iJydzLedTestRange				= Configure_OthersPage.m_iJydzLedTestRange;	//绝缘电阻工位到测试光色电工位
		m_CommSettingsData.m_iNyyLedTestRange				= Configure_OthersPage.m_iNyyLedTestRange;	//绝缘电阻工位到测试光色电工位
		m_CommSettingsData.m_iXldlLedTestRange				= Configure_OthersPage.m_iXldlLedTestRange;	//绝缘电阻工位到测试光色电工位

        CreateDirectory(g_strCurrentPath + "Communication Settings", NULL);
		if(g_bUseArea2)
			m_CommSettingsData.WriteToFile(g_strCurrentPath + "Communication Settings\\CommSettings2.dat");
		else
			m_CommSettingsData.WriteToFile(g_strCurrentPath + "Communication Settings\\CommSettings.dat");
		InitializeComm();       
	}
}


int CLAT2000Doc::GetCOM(CString strCOM)
{
	strCOM.Trim();
	strCOM.MakeUpper();

	int iCOM = 1;
	sscanf_s(strCOM.GetBuffer(), "COM%d", &iCOM);

	return iCOM;
}


void CLAT2000Doc::OnUpdateButtonEditLimit(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(!IsRunning() && !IsContinueMoveOneStepRunning());
}

void CLAT2000Doc::OnUpdateSpectrumTest(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(g_iExecutionLevel != LOW_EXECUTION_LEVEL && !IsRunning()
		&& !IsContinueMoveOneStepRunning());
	if (LOW_EXECUTION_LEVEL == g_iExecutionLevel)
	{
		pCmdUI->SetText("----");
	}
}

void CLAT2000Doc::OnSpectrumTest()
{
	// TODO: 在此添加命令处理程序代码
	g_Hass1200Meter.ShowTestDialog();
}


void CLAT2000Doc::OnAlarmRingEdit()
{
	// TODO: 在此添加命令处理程序代码
	CAlarmRingEditDlg dlg;
	if (IDOK == dlg.DoModal())
	{
		BOOL bR = m_AlarmRingData.SaveFile(g_strCurrentPath + "Alarm\\RingData.dat");
		if (!bR)
		{
			AfxMessageBox("数据保存失败！");
		}
	}
}




void CLAT2000Doc::OnResetStatistics()
{
	// TODO: 在此添加命令处理程序代码
}


BOOL CLAT2000Doc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  在此添加您专用的创建代码

	return TRUE;
}


void CLAT2000Doc::OnImportLastData()
{
	// TODO: 在此添加命令处理程序代码
	BeginWaitCursor();
	if (m_dataContainer.LoadFile(g_strHistoryDataPath + "AutoManage.dat"))
	{
		GetCurrentData();
		UpdateAllViews(NULL);
	}	
	EndWaitCursor();
    ::PostMessage(m_hWndDataContainerGridView, MSG_GRID_RELIST_DATA, 0, 0);     
    UpdateAllViews(NULL);
}


void CLAT2000Doc::OnClearAllData()
{
	// TODO: 在此添加命令处理程序代码
    if (IDCANCEL == ::MessageBox(g_hMainFrm, "是否清空当前测试数据?", "Warning",
        MB_OKCANCEL))
    {
        return;
    }

	g_strHaveSaveFileName = "";
	g_strHaveSaveCsvName = "";
	m_dataContainer.RemoveAllData();
    m_TestContainer.ResetAllRows();
	UpdateAllViews(NULL);
}


void CLAT2000Doc::OnUpdateImportLastData(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(!IsRunning() && !IsContinueMoveOneStepRunning());
}


void CLAT2000Doc::OnUpdateClearAllData(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(!IsRunning() && !IsContinueMoveOneStepRunning());
}


void CLAT2000Doc::OnCloseDocument()
{
	// TODO: 在此添加专用代码和/或调用基类
	m_bCloseDocument = TRUE;
	WaitForSingleObject(m_pThreadGauge->m_hThread, INFINITE);

	CDocument::OnCloseDocument();
}


void CLAT2000Doc::OnStdLampInPosition()
{
	// TODO: 在此添加命令处理程序代码
	BeginWaitCursor();
	for (int i = 0; i < atoi(m_CommSettingsData.m_strCalibrationRange) + 1; i++)
	{
		if (!g_LineControllerComm.MoveLineOneStep())
		{
			AfxMessageBox("移动产线失败！");
			return;
		}
		Sleep(1000);

		BOOL bR, bInposition = FALSE, bManualStopped = FALSE, bLampTooHigh = FALSE;
		int iReadFailedNum = 0;
		while(!bInposition)
		{
			bR = g_LineControllerComm.ReadLineState(bInposition, bManualStopped, bLampTooHigh);
			if (bR)
			{
				if (bManualStopped)
				{
					AfxMessageBox("产线强制停止！");
					return;
				}

				if (bLampTooHigh)
				{
					AfxMessageBox("产线灯过高！");
					return;
				}
			}
			else
			{
				iReadFailedNum++;
			}
			if (iReadFailedNum > 5)
			{
				AfxMessageBox("读取产线状态失败！");
				return;
			}
			Sleep(500);
		}// End while

		Sleep(1000);		// Make sure the line is stopped
	}// End for
	EndWaitCursor();

	AfxMessageBox("标准灯已经到位！");
}

void CLAT2000Doc::OnUpdateStdLampInPosition(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(g_iExecutionLevel != LOW_EXECUTION_LEVEL && !IsRunning()
		&& !IsContinueMoveOneStepRunning());
	if (LOW_EXECUTION_LEVEL == g_iExecutionLevel)
	{
		pCmdUI->SetText("----");
	}
}

void CLAT2000Doc::OnStatistic()
{
    // TODO: 在此添加命令处理程序代码
	POSITION pos;
	pos = GetFirstViewPosition();
	while(pos)
	{
		CView *pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CMainTabWnd)))
		{
			CMainTabWnd *MainTabWnd = (CMainTabWnd*)pView;
			MainTabWnd->SetActiveView(2);
		}
	}
    m_StatisticLedDataContainer.RemoveAllLedData();
	m_StatisticLedDataContainer.SetStatisticParaMode(StatisticParaMode(m_systemSettingsData.m_iStatisticMode));
     
    CDlgStatisticFileChoose dlg;
    m_systemSettingsData.m_iStatisticMode = dlg.m_iStatisticMode;        
    if (IDCANCEL == dlg.DoModal())
    {
        return;
    }                
    dlg.m_iStatisticMode = m_systemSettingsData.m_iStatisticMode;
  
    m_StatisticLedDataContainer.toStatisticPara();
    ::PostMessage(m_hWndStatisticGridView, MSG_STATISTIC_GRID_RELIST_DATA, 0, 0);
    ::PostMessage(m_hWndStatisticDisbuteGridView, MSG_STATISTIC_DIS_GRID_RELIST_DATA, 0, 0);
    m_StatisticLedDataContainer.IsAllStatisticPara(TRUE);
}


void CLAT2000Doc::OnUpdateStatistic(CCmdUI *pCmdUI)
{
    // TODO: 在此添加命令更新用户界面处理程序代码
    if (!g_bStatistic)
    {
        pCmdUI->SetText("---");
        pCmdUI->Enable(FALSE);
    }
}


void CLAT2000Doc::OnTestinfo()
{
    // TODO: 在此添加命令处理程序代码
    CMySheet sheet("测试信息");
    CTestInfoPage_LampInfoPage page1;
    CTestInfoPage_TestConditionPage page2;
    CTestInfoPage_PrintOpinionPage page3;
    CTestInfoData *TestInfoData = &m_dataContainer.GetTestInfoData();
    page1.m_strLampName = TestInfoData->m_strLampName;
    page1.m_strLampNote = TestInfoData->m_strLampNote;
    page1.m_strLampNum = TestInfoData->m_strLampNum;
    page1.m_strLampRule = TestInfoData->m_strLampRule;
    page1.m_fStaPow = m_dataContainer.GetTestSettingData().m_fStaPow;
    page1.m_fStaFlux = m_dataContainer.GetTestSettingData().m_fStaFlux;
    page1.m_fStaTc = m_dataContainer.GetTestSettingData().m_fStaTc;
    page1.m_fStaVol = m_dataContainer.GetTestSettingData().m_fStaVol;
    page1.m_strComboInerface = TestInfoData->m_strComboInerface;
    page1.m_strFactory = TestInfoData->m_strFactory;
    page1.m_strLampModel = m_dataContainer.GetTestSettingData().m_strLedModel;

    page2.m_strTMP = TestInfoData->m_strTMP;
    page2.m_strWet = TestInfoData->m_strWet;
    page2.m_fTestRate = TestInfoData->m_fTestRate;
    page2.m_strRemark = TestInfoData->m_strRemark;
    page2.m_strTestMachine = TestInfoData->m_strTestMachine;
    page2.m_strTester = TestInfoData->m_strTester;
    page2.m_strTestDate = TestInfoData->m_strTestDate;
    page2.m_bCustomVol_Aging = TestInfoData->m_bCustomVol_Aging;
    page2.m_bEMC_Test = TestInfoData->m_bEMC_Test;
    page2.m_bHighLowVol_Aging = TestInfoData->m_bHighLowVol_Aging;
    page2.m_bHighTMP_Aging = TestInfoData->m_bHighTMP_Aging;
    page2.m_bNormalTMP_Aging = TestInfoData->m_bNormalTMP_Aging;
    page2.m_bStaVol_Aging = TestInfoData->m_bStaVol_Aging;
    page2.m_bSwitch_Aging = TestInfoData->m_bSwitch_Aging;

    page3.m_bPrintPageHeadLogo = TestInfoData->m_bPrintPageHeadLogo;
    page3.m_iPageHeadLogoPos = TestInfoData->m_iPageHeadLogoPos;
    page3.m_bPrintSubCap = TestInfoData->m_bPrintSubCap;
    page3.m_strPageHeadCap = TestInfoData->m_strPageHeadCap;
    page3.m_strPageHeadCapInfo = TestInfoData->m_strPageHeadCapInfo;
    page3.m_strPrintCap = TestInfoData->m_strPrintCap;
    page3.m_strPrintSubCap = TestInfoData->m_strPrintSubCap;

    sheet.AddPage(&page1);
    sheet.AddPage(&page2);
    sheet.AddPage(&page3);
    if (IDCANCEL == sheet.DoModal())
    {
        return;
    }        

    TestInfoData->m_strLampName = page1.m_strLampName;
    TestInfoData->m_strLampNote = page1.m_strLampNote;
    TestInfoData->m_strLampNum = page1.m_strLampNum;
    TestInfoData->m_strLampRule = page1.m_strLampRule;
    TestInfoData->m_fStaPow = page1.m_fStaPow;
    TestInfoData->m_fStaFlux = page1.m_fStaFlux;
    TestInfoData->m_fStaTc = page1.m_fStaTc;
    TestInfoData->m_fStaVol = page1.m_fStaVol;
    TestInfoData->m_strComboInerface = page1.m_strComboInerface;
    TestInfoData->m_strFactory = page1.m_strFactory;
    TestInfoData->m_strLampModel = page1.m_strLampModel;

    TestInfoData->m_strTMP = page2.m_strTMP;
    TestInfoData->m_strWet = page2.m_strWet;
    TestInfoData->m_fTestRate = page2.m_fTestRate;
    TestInfoData->m_strRemark = page2.m_strRemark;
    TestInfoData->m_strTestMachine = page2.m_strTestMachine;
    TestInfoData->m_strTester = page2.m_strTester;
    TestInfoData->m_strTestDate = page2.m_strTestDate;
    TestInfoData->m_bCustomVol_Aging = page2.m_bCustomVol_Aging;
    TestInfoData->m_bEMC_Test = page2.m_bEMC_Test;
    TestInfoData->m_bHighLowVol_Aging = page2.m_bHighLowVol_Aging;
    TestInfoData->m_bHighTMP_Aging = page2.m_bHighTMP_Aging;
    TestInfoData->m_bNormalTMP_Aging = page2.m_bNormalTMP_Aging;
    TestInfoData->m_bStaVol_Aging = page2.m_bStaVol_Aging;
    TestInfoData->m_bSwitch_Aging = page2.m_bSwitch_Aging;

    TestInfoData->m_bPrintPageHeadLogo = page3.m_bPrintPageHeadLogo;
    TestInfoData->m_iPageHeadLogoPos = page3.m_iPageHeadLogoPos;
    TestInfoData->m_bPrintSubCap = page3.m_bPrintSubCap;
    TestInfoData->m_strPageHeadCap = page3.m_strPageHeadCap;
    TestInfoData->m_strPageHeadCapInfo = page3.m_strPageHeadCapInfo;
    TestInfoData->m_strPrintCap = page3.m_strPrintCap;
    TestInfoData->m_strPrintSubCap = page3.m_strPrintSubCap;
    TestInfoData->SaveTestInfoSection();
    m_StatisticLedDataContainer.GetTestInfoData() = m_dataContainer.GetTestInfoData();
}


void CLAT2000Doc::OnUpdateTestinfo(CCmdUI *pCmdUI)
{
    // TODO: 在此添加命令更新用户界面处理程序代码
}


void CLAT2000Doc::OnStatisticParaChoose()
{
    // TODO: 在此添加命令处理程序代码    
    CStatisticParaChooseDlg dlg;
    dlg.DoModal();
	m_StatisticLedDataContainer.SetStatisticParaMode(StatisticParaMode(m_systemSettingsData.m_iStatisticMode));
    m_StatisticLedDataContainer.toStatisticPara();
    ::PostMessage(m_hWndStatisticGridView, MSG_STATISTIC_GRID_RELIST_DATA, 0, 0);
    ::PostMessage(m_hWndStatisticDisbuteGridView, MSG_STATISTIC_DIS_GRID_RELIST_DATA, 0, 0);
}


void CLAT2000Doc::OnUpdateStatisticParaChoose(CCmdUI *pCmdUI)
{
    // TODO: 在此添加命令更新用户界面处理程序代码
    if (!g_bStatistic)
    {
        pCmdUI->SetText("---");
        pCmdUI->Enable(FALSE);
    }
  
}

void CLAT2000Doc::OnLineControl()
{
    // TODO: 在此添加命令处理程序代码 
	//老化按钮
    CDlgSetOldLineTime dlg;
	dlg.m_fOldLineT_Times = m_systemSettingsData.m_fOldLineT_Times;		
    if (IDCANCEL == dlg.DoModal())
    {
		return;
    }
	m_systemSettingsData.m_fOldLineT_Times = dlg.m_fOldLineT_Times;
    // Set Burn in Times

    BOOL bR;
    if (m_dataContainer.GetTestSettingData().m_bTestBurnIn)
    {
        bR = g_LineControllerComm.SetOldTime((float)m_dataContainer.GetTestSettingData().m_iBurnInONSeconds, (float)m_dataContainer.GetTestSettingData().m_iBurnInOFFSeconds);
    }
    else
    {
        bR = g_LineControllerComm.SetOldTime(1.0f, 0.0f);	// Always be ON
    }
    if (!bR)
    {
        ShowMessageDialog("开关老炼参数设置失败!");
        return;
    }
	g_LineControllerComm.SetShowLED(1);

	AfxBeginThread(_ThreadLineControlerMoveOneStep, this);
}

UINT CLAT2000Doc::_ThreadLineControlerMoveOneStep(LPVOID lPar)
{
	//产线控制移动一步
    g_EventOlding.ResetEvent();
	CLAT2000Doc *pDoc = (CLAT2000Doc*)lPar;
	pDoc->m_bComtinueMoveRunning = TRUE;
	pDoc->m_bSetStop = FALSE;

	BOOL bR;
    // StopOutput DPS
    if (g_DPSComm.IsRunning())
    {
        if (!g_DPSComm.StopOutput())
        {
            AfxMessageBox("测试电源停止失败！");
            goto Exit;
        }
    }         
	
    // Show OldingDialog
    pDoc->m_pShowOldTime->Init(pDoc->m_systemSettingsData.m_fOldLineT_Times);
    pDoc->m_pShowOldTime->ShowWindow(SW_SHOW);

	// Clear LineControl State
	g_LineControllerComm.ClearAllState();

	// Switch All Display Off
    ChannelState channelState[30];
    for (int j = 0; j < 30; j ++)
    {
        channelState[j] = CHANNEL_OFF; 
    }
	if (pDoc->m_CommSettingsData.m_bHaveLEDIndicator)
	{
		g_IndicatorComm.SetAllChannelState(channelState);
	}
	if (pDoc->m_CommSettingsData.m_bHaveLRA)
	{
		g_LRAComm.SwitchAllChannel(FALSE);
	}
	if (pDoc->m_CommSettingsData.m_bBribe)
	{
		g_BribeComm.SwitchAllChannel(FALSE);
	}

	//Remove All Indicator State
    pDoc->m_IndicatorColorData.RemoveAll();
    pDoc->m_bNotMoveLine.RemoveAll();
    //Det  bManualStopped Pos
    int bInposition, bManualStopped, bLampTooHigh;
    bManualStopped = bInposition = FALSE;
	if(g_LineControllerComm.ReadLineState(bInposition, bManualStopped, bLampTooHigh))
	{
		if (bManualStopped)
		{
			pDoc->m_bComtinueMoveRunning = FALSE;
			g_LineControllerComm.SetLinePause();
			pDoc->ShowMessageDialog("产线紧急停止，请取消紧急停止后再测试!", 
				AT_MANUAL_STOP);
			goto Exit;
		}
		// Clear LineControl State
		if(bLampTooHigh)
		{
			g_LineControllerComm.ClearAllState();				
		}
	}

	// Set OldTime
	g_pMainTestFormView->m_cOtherInfo.SetOldTimeSeconds(pDoc->m_systemSettingsData.m_fOldLineT_Times);
	g_pMainTestFormView->m_cOtherInfo.SetLineState(Olding);

	int iT1,iT2;
	while(1)
	{
		iT1 = GetCurrentTime();
		if (pDoc->m_dataContainer.GetTestSettingData().m_bTestAutoHand)
		{
			BOOL bHaveMove = FALSE;
			int iChannel[10];
			for (int i = 0 ;i < 10; i++)
			{
				iChannel[i] = 0;
			}
			bR = g_HandAutoComm.WriteToHandLamp(iChannel);
			//发到位信号 允许上灯 同时在进行下灯动作
			bR = g_HandAutoComm.WriteToHandInpos(TRUE);
			if (!bR)
			{
				pDoc->ShowMessageDialog("机械手控制失败，请检查仪器是否正确连接！");
				pDoc->OnMenuStop();
				goto Exit;
			}
			Sleep(100);
			//读取到允许运行说明上灯结束了
			BOOL bAllow = FALSE;
			while(1)
			{
				bR = g_HandAutoComm.ReadHandState(bAllow);
				if (bAllow)
				{
					break;
				}
				if (pDoc->m_bSetStop)
				{
					pDoc->OnMenuStop();
					goto Exit;
				}
			}
		}


		if (!g_LineControllerComm.MoveLineOneStep())
		{
			pDoc->ShowMessageDialog("产线控制失败!");
			break;
		}
		int iWaitms = 0;
		bManualStopped = bInposition = FALSE;
		while(g_LineControllerComm.ReadLineState(bInposition, bManualStopped, bLampTooHigh))
		{
			if (bManualStopped)
			{
				pDoc->m_bComtinueMoveRunning = FALSE;					
				g_LineControllerComm.SetLinePause();
				pDoc->ShowMessageDialog("产线紧急停止，请取消紧急停止后再测试!", 
					AT_MANUAL_STOP);
				goto Exit;
			}

			if (bLampTooHigh)
			{
				pDoc->m_bComtinueMoveRunning = FALSE;					
				g_LineControllerComm.SetLinePause();
				pDoc->ShowMessageDialog("灯过高，请调整检测装置高度后再测试!", 
					AT_LAMP_TOO_HIGH);
				pDoc->OnMenuStop();
				goto Exit;
			}

			if (bInposition == 2)
			{
				pDoc->AddBoardID();
				break;
			}
			else
			{
				Sleep(100);
				iWaitms += 100;
				if (iWaitms > 10000)
				{
					pDoc->ShowMessageDialog("等待产线到位超时，请检查产线是否有故障!");
					goto Exit;
				}
			}
		}

		if (pDoc->m_bSetStop == TRUE)
		{
			goto Exit;
		}

		while(1)
		{
			if (pDoc->m_bSetStop == TRUE)
			{
				goto Exit;
			}
			Sleep(100);
			iT2 = GetCurrentTime();
			if ((iT2 - iT1) >= (int)(pDoc->m_systemSettingsData.m_fOldLineT_Times * 1000))
			{
				break;
			}
		}
	}
Exit:
	pDoc->m_bComtinueMoveRunning = FALSE;
    pDoc->m_pShowOldTime->ShowWindow(SW_HIDE);
    g_EventOlding.SetEvent();
	g_pMainTestFormView->m_cOtherInfo.SetLineState(Free);
	return 0;
}

void CLAT2000Doc::OnUpdateLineControl(CCmdUI *pCmdUI)
{
    // TODO: 在此添加命令更新用户界面处理程序代码
    pCmdUI->Enable(!IsRunning() && !IsContinueMoveOneStepRunning());
}

void CLAT2000Doc::GetCtrlFileList(CString strPathName)
{

	m_strListCtrlFile.RemoveAll();

	CFileFind myFinder;
	CStringList myList;
	CString FileName;
	myList.AddTail(strPathName + "");

	while (!myList.IsEmpty())
	{
		CString strTemp;
		FileName=myList.GetHead()+_T("\\*.*");

		if (myFinder.FindFile(LPCTSTR(FileName)))
		{
			while (myFinder.FindNextFile())
			{
				if (myFinder.IsDots())
					continue;
				strTemp = myFinder.GetFilePath();
				m_strListCtrlFile.Add(strTemp);

				if(myFinder.IsDirectory())
					myList.AddTail(myFinder.GetFilePath());
			}
	
			strTemp = myFinder.GetFilePath();
			m_strListCtrlFile.Add(strTemp);
		}
		myList.RemoveHead();
	}
	return;
}

void CLAT2000Doc::OnViewCurSetPara()
{
	// TODO: 在此添加命令处理程序代码
	CEditLimitDlg dlg;
	g_bDisplayLimitOnly = TRUE;
	dlg.m_LimitData = m_dataContainer.GetTestSettingData();

	dlg.m_bHaveVoltageUpAndDips = m_CommSettingsData.m_bHaveEMS61000_11K;
	dlg.m_bHaveBurnIn = TRUE;
	dlg.m_bHaveLightning = m_CommSettingsData.m_bHaveEMS61000_5A;
	dlg.DoModal();
}

	
void CLAT2000Doc::OnBeforeChangeLamp()
{
	// TODO: 在此添加命令处理程序代码

	if (!m_systemSettingsData.m_bAutoSave)
    {
        if (MessageBox(NULL, "换灯是否保存当前测试文件？","提醒",  MB_YESNO) == IDYES)
        {
            CFileDialog dlg(FALSE, "lat2000-everfine", "LAT-2000", 6UL, "nLAT2000 Files(*.lat2000-everfine)|*.lat2000-everfine|");
            if (IDOK == dlg.DoModal())
            {          
                m_dataContainer.SaveFile(dlg.GetPathName());
            }
        }  	
	}
	else
	{
		if (m_dataContainer.GetSize() > 0)
		{
			CString strPathName;
			CTime tNow = CTime::GetCurrentTime();
			//	strPathName = m_systemSettingsData.m_strFilePath + "\\" + 
			//		m_dataContainer.GetTestSettingData().m_strLedModel + tNow.Format("%Y-%m-%d %H-%M-%S.lat2000-everfine");// %H-%M-%S
			if (!m_systemSettingsData.m_iPrefixInputMode)
			{
				strPathName = m_systemSettingsData.m_strFilePath + "\\" + 
				m_systemSettingsData.m_strFileName + tNow.Format("%Y-%m-%d %H-%M-%S.lat2000-everfine");// %H-%M-%S
			}
			else
			{
				strPathName = m_systemSettingsData.m_strFilePath + "\\" + 
					m_dataContainer.GetTestSettingData().m_strLedModel + tNow.Format("%Y-%m-%d %H-%M-%S.lat2000-everfine"); // %H-%M-%S
			}	
			m_dataContainer.SaveFile(strPathName);
			strPathName.Replace(".lat2000-everfine","");
			g_strPathNameAuto = strPathName+".csv";
			::PostMessageA(m_hWndDataContainerGridView, MSG_SAVE_CSV_DATA, 0, 0);
		} 		
	}
	m_dataContainer.RemoveAllData();
		
	CDlgBeforeChangeLamp dlg;
	dlg.m_strFileName = m_systemSettingsData.m_strFileName;
	dlg.m_strFilePath = m_systemSettingsData.m_strFilePath;
	dlg.m_bAutoSave = m_systemSettingsData.m_bAutoSave;
	dlg.m_TestSettingsData = m_dataContainer.GetTestSettingData();
	dlg.TestInfoData = m_dataContainer.GetTestInfoData();
    dlg.m_iSaveType = m_systemSettingsData.m_iSaveType;
    dlg.m_iPrefixInputMode = m_systemSettingsData.m_iPrefixInputMode;
	dlg.m_strFileDataNum.Format("%d", m_systemSettingsData.m_iSaveFileDataNum);
	if (dlg.DoModal() == IDCANCEL)
	{
		return;
	}
	m_systemSettingsData.m_strFileName = dlg.m_strFileName;
	m_systemSettingsData.m_strFilePath = dlg.m_strFilePath;
	m_systemSettingsData.m_bAutoSave = dlg.m_bAutoSave;
	m_systemSettingsData.m_iSaveFileDataNum = atoi(dlg.m_strFileDataNum);
    m_systemSettingsData.m_iSaveType = dlg.m_iSaveType;
    m_systemSettingsData.m_iPrefixInputMode = dlg.m_iPrefixInputMode;

	m_dataContainer.GetTestSettingData() = dlg.m_TestSettingsData;
	m_dataContainer.GetTestInfoData() = dlg.TestInfoData;
	g_Hass1200Meter.SetIntTime(m_dataContainer.GetTestSettingData().m_fIntegralTimems);
	m_TestContainer.SetDirectionOpposite(m_dataContainer.GetTestSettingData().m_bTestDirectionOpposite);

    m_dataContainer.GetTestSettingData().Store(g_strTestSettingFileName);

	g_EMS61000_11KComm.Initialize(g_strCurrentPath + "Communication Settings\\", m_CommSettingsData.m_strCOMEMS61000_11K);
	g_EMS61000_5AComm.Initialize(g_strCurrentPath + "Communication Settings\\", m_CommSettingsData.m_strCOMEMS61000_5A);
	::PostMessage(m_hWndTestFormView, MSG_LIMIT_FILE_RELIST, 0, 0);
}


void CLAT2000Doc::OnUpdateBeforeChangeLamp(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(!IsRunning() && !IsContinueMoveOneStepRunning());
}


BOOL CLAT2000Doc::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// TODO: 在此添加专用代码和/或调用基类
	
	return CDocument::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CLAT2000Doc::OnUpdateAlarmRingEdit(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(g_iExecutionLevel != LOW_EXECUTION_LEVEL && !IsRunning()
		&& !IsContinueMoveOneStepRunning());
	if (LOW_EXECUTION_LEVEL == g_iExecutionLevel)
	{
		pCmdUI->SetText("----");
	}
}

void CLAT2000Doc::OnChangeAccount()
{
	// TODO: 在此添加命令处理程序代码
	CAccountDlg dlg;
	if(IDCANCEL == dlg.DoModal())
	{
		return ;
	}
	g_iExecutionLevel = dlg.m_iExecutionLevel;
    if (TRUE == g_bDebug)
    {
        g_iExecutionLevel = ADMIN_EXECUTION_LEVEL;
    }
}

void CLAT2000Doc::OnUpdateChangeAccount(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(!IsRunning() && !IsContinueMoveOneStepRunning());
}

void CLAT2000Doc::OnListparaChoose()
{
    // TODO: 在此添加命令处理程序代码
    CDlgListParaChoose dlg;
    dlg.DoModal();
    m_dataContainer.GetDisplayParaNum(); 
    ::PostMessageA(m_hWndDataContainerGridView, MSG_GRID_RELIST_DATA, 0, 0);
}

void CLAT2000Doc::OnUpdateExportStatisticData(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (!g_bStatistic)
	{
		pCmdUI->SetText("---");
		pCmdUI->Enable(FALSE);
	}
}


void CLAT2000Doc::AddBoardID()
{
	//板号+1
    m_systemSettingsData.m_iCurrentBoardID ++;
    if (m_systemSettingsData.m_iCurrentBoardID > (int)m_CommSettingsData.m_iTotalBoard)
    {
        m_systemSettingsData.m_iCurrentBoardID = 1;
    }
}

UINT CLAT2000Doc::_ThreadScaner(LPVOID pPar)
{
	//扫码控制
    CLAT2000Doc *pDoc = (CLAT2000Doc*)pPar;
    while(1)
    {
        if (pDoc->m_eventStartOne.Lock())
        {
			RowLEDSN rowLEDSN;   
			if (pDoc->m_systemSettingsData.m_iTestHaveScanedMode)
			{
				//直接测试已扫码
				goto exit;
			}
            pDoc->m_bIsScanerRunning = TRUE;
            pDoc->m_TestContainer.SetCurrentRowScaned(FALSE);
            if (!pDoc->m_CommSettingsData.m_bHaveScaner || pDoc->m_systemSettingsData.m_bLineNotMove)
            {
                goto exit;
            }
            DWORD dwTime = (DWORD)::GetCurrentTime();
            int iR;
            iR = g_ScanerComm.ScanSN(pDoc->m_dataContainer.GetTestSettingData().GetAllTestChannelNum(),
				pDoc->m_dataContainer.GetTestSettingData().m_iTestMinSeconds * 1000); 
                // Alarm
			if (iR == SCAN_FAIL)
			{
				pDoc->ShowMessageDialog("扫码机扫描超时，请检查仪器是否正确连接！", AT_SCANEROVERTIME);
				pDoc->OnMenuStop();
				goto exit;
			}
			g_TSrceenComm.SendShowData(0,g_ScanerComm.m_strLedSN.GetAt(g_ScanerComm.m_strLedSN.GetSize() - 1));

			rowLEDSN.SetRowSN(pDoc->m_systemSettingsData.m_iCurrentBoardID);
			for (int i = 0; i < g_ScanerComm.m_strLedSN.GetSize(); i++)
			{
				rowLEDSN.AddLEDSN(g_ScanerComm.m_strLedSN.GetAt(i));
			}

			pDoc->m_TestContainer.InsertRowLEDSN(0, rowLEDSN); 
            pDoc->m_TestContainer.SetCurrentRowScaned(TRUE);
            // Scan dimension code over
exit:     
            pDoc->m_bIsScanerRunning = FALSE;
            pDoc->m_eventStartOne.ResetEvent();
            pDoc->m_eventScanerEnd.SetEvent();
        }
    }
    return 0;
}

void CLAT2000Doc::OnSeleSdcmStd()
{
	// TODO: 在此添加命令处理程序代码
	if (!SDCM_DLL_Dlg_Sel_Display_OneGra())
	{
		return;
	}

// 	for (int i = 0; i < m_dataContainer.GetSize(); i ++)
// 	{
// 		SDCM_DLL_Calc(m_dataContainer.GetAt(i).m_ColorData.m_fCIEx, 
// 			m_dataContainer.GetAt(i).m_ColorData.m_fCIEy);
// 		int iType;
// 		char strName[256];
// 		SDCM_DLL_GetSelSDCM_OneGraType(iType,strName);
// 		m_dataContainer.GetAt(i).m_iSDCMType = iType;
// 		m_dataContainer.GetAt(i).m_strSDCMSta  = strName;
// 		if (iType == CLedData::SDCMType_ELLI)
// 		{
// 			m_dataContainer.GetAt(i).m_fSDCM = SDCM_DLL_GetSelSDCM_Ellipse_SDCMValue();
// 		}
// 		if (iType == CLedData::SDCMType_PLOY)
// 		{
// 			m_dataContainer.GetAt(i).m_bInPoly = SDCM_DLL_GetSelSDCM_Polygon_WhetherIn();
// 		}
// 	}
	::PostMessage(m_hWndDataContainerGridView, MSG_GRID_RELIST_DATA, 0, 0);
	::PostMessageA(m_hWndDataContainerDrawView, MSG_DATA_CONTAINER_DRAW, 0,0);

}


void CLAT2000Doc::OnUpdateSeleSdcmStd(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
}
