// Configure_TestControlPage.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "Configure_TestControlPage.h"
#include "afxdialogex.h"
#include "LAT2000Doc.h"
#include "DlgSaftSetup.h"
// CConfigure_TestControlPage 对话框

IMPLEMENT_DYNAMIC(CConfigure_TestControlPage, CPropertyPage)

extern CSafetyTest_CSComm2676 g_SafetyTest_CS2676Comm;
extern CSafetyTest_TongHui_TH2683AComm g_SafetyTest_TongHui_TH2683AComm;
extern CSafetyTest_TongHui_TH9310_20Comm g_SafetyTest_TongHui_TH9310_20Comm;

CConfigure_TestControlPage::CConfigure_TestControlPage()
	: CPropertyPage(CConfigure_TestControlPage::IDD)
	, m_iMyLastPowerType(0)
	, m_bHaveMyLast(FALSE)
	, m_bHaveSaft_NYY(FALSE)
	, m_bHaveSaft_JYDZ(FALSE)
	, m_bHaveSaft_XLDL(FALSE)
	, m_iTypeSaftNyy(0)
	, m_iTypeSaftJydz(0)
	, m_iTypeSaftXLDL(0)
	, m_strSaftNyyCOM(_T(""))
	, m_strSaftJydzCOM(_T(""))
	, m_strSaftXLDLCOM(_T(""))
	, m_strComNyy2(_T(""))
	, m_strComJydz2(_T(""))
	, m_strComXldl2(_T(""))
{

	m_iStandardSupplyType = 0;
	m_iTestChannelControlerType = 0;
}

CConfigure_TestControlPage::~CConfigure_TestControlPage()
{
}

void CConfigure_TestControlPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_DYNAMOMETER, m_bDynamometer);
	DDX_Check(pDX, IDC_CHECK_TESTCHANNEL_CONTROLLER, m_bTestChannelController);
	DDX_Check(pDX, IDC_CHECK_SPECTROMETER, m_bSpectrometer);
	DDX_Check(pDX, IDC_CHECK_STANDARD_POWER, m_bStandardSupply);
	DDX_Check(pDX, IDC_CHECK_TEST_POWER, m_bTestSupply);
	DDX_Check(pDX, IDC_CHECK_LINE_CONTROL, m_bLineController);
	DDX_Check(pDX, IDC_CHECK_THUNDER_RELAY, m_bThunderRelay);

	DDX_CBString(pDX, IDC_COMBO_DYNAMOMETER_COM, m_strDynamometerCOM);
	DDX_CBString(pDX, IDC_COMBO_TESTCHANNEL_CONTROLLER_COM, m_strTestChannelControllerCOM);
	DDX_CBString(pDX, IDC_COMBO_STANDARD_POWER_COM, m_strStandardSupplyCOM);
	DDX_CBString(pDX, IDC_COMBO_TEST_POWER_COM, m_strTestSupplyCOM);
	DDX_CBString(pDX, IDC_COMBO_MY_POWER_COM, m_strMyLastCOM);
	DDX_CBString(pDX, IDC_COMBO_LINE_CONTROL_COM, m_strLineControllerCOM);
	DDX_CBString(pDX, IDC_COMBO_THUNDER_RELAY_COM, m_strThunderRelayCOM);
	DDX_CBString(pDX, IDC_COMBO_AGEPOWER_COM1, m_strAgePowerCOM[0]);
	DDX_CBString(pDX, IDC_COMBO_AGEPOWER_COM2, m_strAgePowerCOM[1]);


	DDX_CBIndex(pDX, IDC_COMBO_TEST_POWER_TYPE, m_iDPSTypeIndex);
	DDX_CBIndex(pDX, IDC_COMBO_MY_POWER_TYPE, m_iMyLastPowerType);

	DDX_CBIndex(pDX, IDC_COMBO_TEST_PF_TYPE, m_iPFType);

	DDX_CBIndex(pDX, IDC_COMBO_STALAMP_POWER_TYPE, m_iStandardSupplyType);
	DDX_Check(pDX, IDC_CHECK_FOR_4A, m_bfor4A);
	DDX_CBIndex(pDX, IDC_COMBO_TESTCHANNEL_CONTROLLER_TYPE, m_iTestChannelControlerType);
	DDX_Check(pDX, IDC_CHECK_TEST_POWER2, m_bHaveMyLast);
	DDX_Check(pDX, IDC_CHECK_SAFT_NYY, m_bHaveSaft_NYY);
	DDX_Check(pDX, IDC_CHECK_SAFT_JYDZ, m_bHaveSaft_JYDZ);
	DDX_Check(pDX, IDC_CHECK_SAFT_XLDL, m_bHaveSaft_XLDL);
	DDX_CBIndex(pDX, IDC_COMBO_SAFT_NYY, m_iTypeSaftNyy);
	DDX_CBIndex(pDX, IDC_COMBO_SAFT_JYDZ, m_iTypeSaftJydz);
	DDX_CBIndex(pDX, IDC_COMBO_SAFT_XLDL, m_iTypeSaftXLDL);
	DDX_CBString(pDX, IDC_COMBO_SAFT_NYY_COM, m_strSaftNyyCOM);
	DDX_CBString(pDX, IDC_COMBO_SAFT_JYDZ_COM, m_strSaftJydzCOM);
	DDX_CBString(pDX, IDC_COMBO_SAFT_XLDL_COM, m_strSaftXLDLCOM);
	DDX_CBString(pDX, IDC_COMBO_SAFT_NYY_COM2, m_strComNyy2);
	DDX_CBString(pDX, IDC_COMBO_SAFT_JYDZ_COM2, m_strComJydz2);
	DDX_CBString(pDX, IDC_COMBO_SAFT_XLDL_COM2, m_strComXldl2);
}


BEGIN_MESSAGE_MAP(CConfigure_TestControlPage, CPropertyPage)
    ON_BN_CLICKED(IDC_BUTTON_STANDARD, &CConfigure_TestControlPage::OnBnClickedButtonStandard)
    ON_BN_CLICKED(IDC_BUTTON_TEST_POWER, &CConfigure_TestControlPage::OnBnClickedButtonTestPower)
    ON_BN_CLICKED(IDC_BUTTON_INTELLECT_CONTROLLER, &CConfigure_TestControlPage::OnBnClickedButtonIntellectController)
    ON_BN_CLICKED(IDC_BUTTON_SPECTROMETER, &CConfigure_TestControlPage::OnBnClickedButtonSpectrometer)
    ON_BN_CLICKED(IDC_BUTTON_DYNAMOMETER, &CConfigure_TestControlPage::OnBnClickedButtonDynamometer)
    ON_BN_CLICKED(IDC_BUTTON_THUNDER_RELAY, &CConfigure_TestControlPage::OnBnClickedButtonThunderRelay)
    ON_BN_CLICKED(IDC_BUTTON_LINE_CONTROL, &CConfigure_TestControlPage::OnBnClickedButtonLineControl)
    ON_CBN_SELCHANGE(IDC_COMBO_TEST_PF_TYPE, &CConfigure_TestControlPage::OnCbnSelchangeComboTestPfType)
    ON_BN_CLICKED(IDC_BUTTON_AGEPOWER1, &CConfigure_TestControlPage::OnBnClickedButtonAgepower1)
    ON_BN_CLICKED(IDC_BUTTON_AGEPOWER2, &CConfigure_TestControlPage::OnBnClickedButtonAgepower2)
	ON_BN_CLICKED(IDC_BUTTON_TEST_POWER2, &CConfigure_TestControlPage::OnBnClickedButtonTestPower2)
	ON_BN_CLICKED(IDC_BUTTON_SAFT_NYY, &CConfigure_TestControlPage::OnBnClickedButtonSaftNyy)
	ON_BN_CLICKED(IDC_BUTTON_SAFT_JYDZ, &CConfigure_TestControlPage::OnBnClickedButtonSaftJydz)
	ON_BN_CLICKED(IDC_BUTTON_SAFT_XLDL, &CConfigure_TestControlPage::OnBnClickedButtonSaftXldl)
	ON_BN_CLICKED(IDC_BUTTON_SAFT_NYY2, &CConfigure_TestControlPage::OnBnClickedButtonSaftNyy2)
	ON_BN_CLICKED(IDC_BUTTON_SAFT_NYY3, &CConfigure_TestControlPage::OnBnClickedButtonSaftNyy3)
	ON_BN_CLICKED(IDC_BUTTON_SAFT_NYY4, &CConfigure_TestControlPage::OnBnClickedButtonSaftNyy4)
END_MESSAGE_MAP()


// CConfigure_TestControlPage 消息处理程序


BOOL CConfigure_TestControlPage::OnInitDialog()
{
    CPropertyPage::OnInitDialog();

    // TODO:  在此添加额外的初始化
    CString strTemp;
    strTemp.Format("Baudate:%d, Address:0X%x", 2400, 0x64);  
    GetDlgItem(IDC_EDIT_STANDARD_POWER)->SetWindowTextA(strTemp);
    strTemp.Format("Baudate:%d, Address:0X%x", 9600, 0x61);  
    GetDlgItem(IDC_EDIT_INTELLECT_CONTROLLER)->SetWindowTextA(strTemp);
    if (m_iPFType == 0)
    {
        strTemp.Format("Baudate:%d", 2400);  
    }
    else
    {
        strTemp.Format("Baudate:%d", 9600);  
    }
    GetDlgItem(IDC_EDIT_DYNAMOMETER)->SetWindowTextA(strTemp); 
    strTemp.Format("Baudate:%d, Address:0X%x", 9600, 0xBF);  
    GetDlgItem(IDC_EDIT_THUNDER_RELAY)->SetWindowTextA(strTemp);
    strTemp.Format("Baudate:%d", 9600);  
    GetDlgItem(IDC_EDIT_LINE_CONTROL)->SetWindowTextA(strTemp);

    GetDlgItem(IDC_COMBO_TEST_PF_TYPE)->EnableWindow(m_bDynamometer);
    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}


void CConfigure_TestControlPage::OnBnClickedButtonStandard()
{
    // TODO: 在此添加控件通知处理程序代码
    UpdateData(TRUE);

    int iCOM = 1;
    sscanf_s(m_strStandardSupplyCOM, "COM%d", &iCOM);

    g_WYComm.Initialize(iCOM, 1);
    g_HLS_200.SetCom(iCOM);
    float f1, f2;
    if (m_iStandardSupplyType == 0)
    {
        if (g_WYComm.GetPower(f1, f2, FALSE))
        {
            AfxMessageBox("试通成功！");
        }
        else
        {
            AfxMessageBox("试通失败！");
        }
    }
    else
    {
        BOOL Output,Load,Warning;
        if (g_HLS_200.GetState(Output,Load,Warning))
        {
            AfxMessageBox("试通成功！");
        }
        else
        {
            AfxMessageBox("试通失败！");
        }
    }
    
}


void CConfigure_TestControlPage::OnBnClickedButtonTestPower()
{
    // TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	DeviceType Temp;
	switch (m_iDPSTypeIndex)
	{
	case 0:
		Temp = DPS_1005;
		break;
	case 1:
		Temp = DPS_1005_V100;
		break;
	case 2:
		Temp = DPS_1010;
		break;
	case 3:
		Temp = DPS_1010_V100;
		break;
	case 4:        
		Temp = DPS_1020;
		break;
	case 5:
		Temp = DPS_1020_V100;
		break;
	case 6:
		Temp = DPS_1030V200_65;
		break;
	case 7:
		Temp = DPS_1030V200_450;
		break;
	case 8:
		Temp = DPS_1060V200_65;
		break;
	case 9:
		Temp = DPS_1060V200_450;
		break;
	default:
		Temp  = DPS_1010;
		break;
	}
	g_DPSComm.SetDeviceType(Temp);

	int iCOM = -1;
	m_strTestSupplyCOM.Trim();
	m_strTestSupplyCOM.MakeUpper();
	sscanf_s(m_strTestSupplyCOM.GetBuffer(), "COM%d", &iCOM);
	g_DPSComm.InitializeComm(iCOM);
	if (g_DPSComm.InRemote())
	{
		AfxMessageBox("试通成功！");
	}
	else
	{
		AfxMessageBox("试通失败！");
	}
}


void CConfigure_TestControlPage::OnBnClickedButtonIntellectController()
{
    // TODO: 在此添加控件通知处理程序代码
    UpdateData(TRUE);
	if (m_iTestChannelControlerType == 1)
	{
		g_SC1000Comm.Initialize(m_strTestChannelControllerCOM);
		if (g_SC1000Comm.SwitchAllLamp(FALSE))
		{
			AfxMessageBox("试通成功！");
		}
		else
		{
			AfxMessageBox("试通失败！");
		}
	}
	else
	{
		g_TestChannelControlComm.Initialize(m_strTestChannelControllerCOM);
		if (g_TestChannelControlComm.SwitchAllChannel(FALSE))
		{
			AfxMessageBox("试通成功！");
		}
		else
		{
			AfxMessageBox("试通失败！");
		}
	}
   
}


void CConfigure_TestControlPage::OnBnClickedButtonSpectrometer()
{
    // TODO: 在此添加控件通知处理程序代码
    UpdateData(TRUE);

    if (g_Hass1200Meter.SetShutterOn())
    {
        AfxMessageBox("试通成功！");
    }
    else
    {
        AfxMessageBox("试通失败！");
    }
}


void CConfigure_TestControlPage::OnBnClickedButtonDynamometer()
{
    // TODO: 在此添加控件通知处理程序代码
    UpdateData(TRUE);

    g_PowerMeterComm.Initialize(m_strDynamometerCOM,g_pDoc->m_CommSettingsData.m_iPFType, 
        g_pDoc->m_dataContainer.GetTestSettingData().m_iRangeCF);
    float f1, f2, f3, f4;
    if (g_PowerMeterComm.Read(f1, f2, f3, f4))
    {
        AfxMessageBox("试通成功！");
    }
    else
    {
        AfxMessageBox("试通失败！");
    }
}


void CConfigure_TestControlPage::OnBnClickedButtonThunderRelay()
{
    // TODO: 在此添加控件通知处理程序代码
    UpdateData(TRUE);

    BeginWaitCursor();
    g_ThunderRelayComm.Initialize(m_strThunderRelayCOM);
    BOOL bR = g_ThunderRelayComm.SwitchAllChannel(FALSE);
    EndWaitCursor();
    if (bR)
    {
        AfxMessageBox("试通成功！");
    }
    else
    {
        AfxMessageBox("试通失败！");
    }
}


void CConfigure_TestControlPage::OnBnClickedButtonLineControl()
{
    // TODO: 在此添加控件通知处理程序代码
    UpdateData(TRUE);

    BeginWaitCursor();
    g_LineControllerComm.Initialize(m_strLineControllerCOM);
    BOOL b1, b2, b3 ;
    BOOL bR = g_LineControllerComm.ReadLineState(b1, b2, b3);
    EndWaitCursor();
    if (bR)
    {
        AfxMessageBox("试通成功！");
    }
    else
    {
        AfxMessageBox("试通失败！");
    }
}

void CConfigure_TestControlPage::OnCbnSelchangeComboTestPfType()
{
    // TODO: 在此添加控件通知处理程序代码
    UpdateData(TRUE);
    CString strTemp;
    if (m_iPFType == 0)
    {
        strTemp.Format("Baudate:%d", 2400);  
    }
    else
    {
        strTemp.Format("Baudate:%d", 9600);  
    }
    GetDlgItem(IDC_COMBO_DYNAMOMETER_COM)->SetWindowTextA(strTemp);
}


void CConfigure_TestControlPage::OnBnClickedButtonAgepower1()
{
    // TODO: 在此添加控件通知处理程序代码
    UpdateData(TRUE);
    int iCOM = -1;
    m_strAgePowerCOM[0].Trim();
    m_strAgePowerCOM[0].MakeUpper();
    sscanf_s(m_strAgePowerCOM[0].GetBuffer(), "COM%d", &iCOM);
    g_DPSAgeComm[0].InitializeComm(iCOM);
    if (g_DPSAgeComm[0].InRemote())
    {
        AfxMessageBox("试通成功！");
    }
    else
    {
        AfxMessageBox("试通失败！");
    }
}


void CConfigure_TestControlPage::OnBnClickedButtonAgepower2()
{
    // TODO: 在此添加控件通知处理程序代码
    UpdateData(TRUE);
    int iCOM = -1;
    m_strAgePowerCOM[1].Trim();
    m_strAgePowerCOM[1].MakeUpper();
    sscanf_s(m_strAgePowerCOM[1].GetBuffer(), "COM%d", &iCOM);
    g_DPSAgeComm[1].InitializeComm(iCOM);
    if (g_DPSAgeComm[1].InRemote())
    {
        AfxMessageBox("试通成功！");
    }
    else
    {
        AfxMessageBox("试通失败！");
    }
}


void CConfigure_TestControlPage::OnBnClickedButtonTestPower2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	DeviceType Temp;
	switch (m_iMyLastPowerType)
	{
	case 0:
		Temp = DPS_1005;
		break;
	case 1:
		Temp = DPS_1005_V100;
		break;
	case 2:
		Temp = DPS_1010;
		break;
	case 3:
		Temp = DPS_1010_V100;
		break;
	case 4:        
		Temp = DPS_1020;
		break;
	case 5:
		Temp = DPS_1020_V100;
		break;
	case 6:
		Temp = DPS_1030V200_65;
		break;
	case 7:
		Temp = DPS_1030V200_450;
		break;
	case 8:
		Temp = DPS_1060V200_65;
		break;
	case 9:
		Temp = DPS_1060V200_450;
		break;
	default:
		Temp  = DPS_1010;
		break;
	}
	g_DPSComm_MyLast.SetDeviceType(Temp);

	int iCOM = -1;
	m_strMyLastCOM.Trim();
	m_strMyLastCOM.MakeUpper();
	sscanf_s(m_strMyLastCOM.GetBuffer(), "COM%d", &iCOM);
	g_DPSComm_MyLast.InitializeComm(iCOM);
	if (g_DPSComm_MyLast.InRemote())
	{
		AfxMessageBox("试通成功！");
	}
	else
	{
		AfxMessageBox("试通失败！");
	}
}


void CConfigure_TestControlPage::OnBnClickedButtonSaftNyy()
{
	// TODO: 在此添加控件通知处理程序代码
	BOOL bR;
	bR = UpdateData(TRUE);
	if(!bR)
		return;
	CDlgSaftSetup dlg;

	g_pDoc->m_CommSettingsData.m_iTypeSaftNyy = m_iTypeSaftNyy;
	g_pDoc->m_CommSettingsData.m_strSaftNyyCOM = m_strSaftNyyCOM;
	dlg.m_iDebugType = 1;
	dlg.DoModal();
/*	BOOL bR = UpdateData(TRUE);
	if(!bR)
		return;
	int iCOM = -1;
	m_strSaftNyyCOM.Trim();
	m_strSaftNyyCOM.MakeUpper();
	sscanf_s(m_strSaftNyyCOM.GetBuffer(), "COM%d", &iCOM);
	if(m_iTypeSaftNyy == 0)
	{
		//TH9320
		g_SafetyTest_TongHui_TH2683AComm.Initialize(m_strSaftNyyCOM);
		float fIR, fLC, fTime;
		bR = g_SafetyTest_TongHui_TH2683AComm .GetTestResult(fIR, fLC, fTime);
	}
	if(m_iTypeSaftNyy == 1)
	{
		//CS9912BI
		g_SafetyTest_CS2676Comm .Initialize(m_strSaftNyyCOM);
		bR = g_SafetyTest_CS2676Comm .SetRemote();
	}

	if (bR)
	{
		AfxMessageBox("试通成功！");
	}
	else
	{
		AfxMessageBox("试通失败！");
	}*/
}


void CConfigure_TestControlPage::OnBnClickedButtonSaftJydz()
{
	// TODO: 在此添加控件通知处理程序代码
	BOOL bR;
	bR = UpdateData(TRUE);
	if(!bR)
		return;
	CDlgSaftSetup dlg;

	g_pDoc->m_CommSettingsData.m_iTypeSaftJydz = m_iTypeSaftJydz;
	g_pDoc->m_CommSettingsData.m_strSaftJydzCOM = m_strSaftJydzCOM;
	dlg.m_iDebugType = 1;
	dlg.DoModal();
/*	BeginWaitCursor();
	BOOL bR = UpdateData(TRUE);
	if(!bR)
		return;
	int iCOM = -1;
	m_strSaftJydzCOM.Trim();
	m_strSaftJydzCOM.MakeUpper();
	sscanf_s(m_strSaftJydzCOM.GetBuffer(), "COM%d", &iCOM);
	if(m_iTypeSaftJydz == 0)
	{
		//CS5505 长盛
		g_SafetyTest_CS2676Comm .Initialize(m_strSaftXLDLCOM);
		bR = g_SafetyTest_CS2676Comm.SetRemote();
	}

	if (bR)
	{
		AfxMessageBox("试通成功！");
	}
	else
	{
		AfxMessageBox("试通失败！");
	}
	EndWaitCursor();*/
}


void CConfigure_TestControlPage::OnBnClickedButtonSaftXldl()
{
	// TODO: 在此添加控件通知处理程序代码
	BOOL bR;
	bR = UpdateData(TRUE);
	if(!bR)
		return;
	CDlgSaftSetup dlg;

	g_pDoc->m_CommSettingsData.m_iTypeSaftXLDL = m_iTypeSaftXLDL;
	g_pDoc->m_CommSettingsData.m_strSaftXLDLCOM = m_strSaftXLDLCOM;
	g_pDoc->m_CommSettingsData.m_bHaveSaft_XLDL = TRUE;

	dlg.m_iDebugType = 1;
	dlg.DoModal();
/*	BeginWaitCursor();
	BOOL bR = UpdateData(TRUE);
	if(!bR)
		return;
	int iCOM = -1;
	m_strSaftXLDLCOM.Trim();
	m_strSaftXLDLCOM.MakeUpper();
	sscanf_s(m_strSaftXLDLCOM.GetBuffer(), "COM%d", &iCOM);
	if(m_iTypeSaftXLDL == 0)
	{
		//CS5505 长盛
		g_SafetyTest_CS2676Comm.Initialize(m_strSaftXLDLCOM);
		bR = g_SafetyTest_CS2676Comm.SetRemote();
	}

	if (bR)
	{
		AfxMessageBox("试通成功！");
	}
	else
	{
		AfxMessageBox("试通失败！");
	}
	EndWaitCursor();*/
}


void CConfigure_TestControlPage::OnBnClickedButtonSaftNyy2()
{
	// TODO: 在此添加控件通知处理程序代码
	BeginWaitCursor();
	BOOL bR = UpdateData(TRUE);
	if(!bR)
		return;
	g_ContNyyComm.Initialize(m_strComNyy2);
	bR = g_ContNyyComm.SwitchAllChannel(FALSE);
	if (bR)
	{
		AfxMessageBox("试通成功！");
	}
	else
	{
		AfxMessageBox("试通失败！" + m_strComNyy2);
	}
	EndWaitCursor();
}


void CConfigure_TestControlPage::OnBnClickedButtonSaftNyy3()
{
	// TODO: 在此添加控件通知处理程序代码
	BeginWaitCursor();
	BOOL bR = UpdateData(TRUE);
	if(!bR)
		return;
	g_ContJydzComm.Initialize(m_strComJydz2);
	bR = g_ContJydzComm.SwitchAllChannel(FALSE);
	if (bR)
	{
		AfxMessageBox("试通成功！");
	}
	else
	{
		AfxMessageBox("试通失败！");
	}
	EndWaitCursor();
}


void CConfigure_TestControlPage::OnBnClickedButtonSaftNyy4()
{
	// TODO: 在此添加控件通知处理程序代码
	BeginWaitCursor();
	BOOL bR = UpdateData(TRUE);
	if(!bR)
		return;
	g_ContXldlComm.Initialize(m_strComXldl2);
	bR = g_ContXldlComm.SwitchAllChannel(FALSE);
	if (bR)
	{
		AfxMessageBox("试通成功！");
	}
	else
	{
		AfxMessageBox("试通失败！");
	}
	EndWaitCursor();
}
