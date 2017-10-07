// RectificationTestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "RectificationTestDlg.h"
#include "afxdialogex.h"
#include <math.h>
#include "LedData.h"
#include "LAT2000Doc.h"
#include "WarningYesNODlg.h"

// CRectificationTestDlg 对话框

IMPLEMENT_DYNAMIC(CRectificationTestDlg, CDialogEx)

CRectificationTestDlg::CRectificationTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRectificationTestDlg::IDD, pParent)
{
	m_strFlux1 = _T("");
	m_strFlux10 = _T("");
	m_strFlux2 = _T("");
	m_strFlux3 = _T("");
	m_strFlux4 = _T("");
	m_strFlux5 = _T("");
	m_strFlux6 = _T("");
	m_strFlux7 = _T("");
	m_strFlux8 = _T("");
	m_strFlux9 = _T("");
	m_fFrequency = 0.0f;
	m_fVoltage = 0.0f;
	m_fIntegralTimems = 0.0f;
	m_bIsElectricalRunning = FALSE;
	m_bIsSpectrumRunning = FALSE;

	CString strSection = "RectificationTestDlg";
	m_iWarmUpTimeMinute = AfxGetApp()->GetProfileInt(strSection, "m_iWarmUpTimeMinute", 5);
	m_strStdFlux1 = _T("");
	m_strStdFlux2 = _T("");
	m_strStdFlux3 = _T("");
	m_strStdFlux4 = _T("");
	m_strStdFlux5 = _T("");
	m_strStdFlux6 = _T("");
	m_strStdFlux7 = _T("");
	m_strStdFlux8 = _T("");
	m_strStdFlux9 = _T("");
	m_strStdFlux10 = _T("");
	m_iRangeU = 0;
	m_iRangeI = 0;
	m_iRangeCF = 0;
}

CRectificationTestDlg::~CRectificationTestDlg()
{
	CString strSection = "RectificationTestDlg";
	AfxGetApp()->WriteProfileInt(strSection, "m_iWarmUpTimeMinute", m_iWarmUpTimeMinute);
}

void CRectificationTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TEST_FLUX1, m_strFlux1);
	DDX_Text(pDX, IDC_EDIT_TEST_FLUX10, m_strFlux10);
	DDX_Text(pDX, IDC_EDIT_TEST_FLUX2, m_strFlux2);
	DDX_Text(pDX, IDC_EDIT_TEST_FLUX3, m_strFlux3);
	DDX_Text(pDX, IDC_EDIT_TEST_FLUX4, m_strFlux4);
	DDX_Text(pDX, IDC_EDIT_TEST_FLUX5, m_strFlux5);
	DDX_Text(pDX, IDC_EDIT_TEST_FLUX6, m_strFlux6);
	DDX_Text(pDX, IDC_EDIT_TEST_FLUX7, m_strFlux7);
	DDX_Text(pDX, IDC_EDIT_TEST_FLUX8, m_strFlux8);
	DDX_Text(pDX, IDC_EDIT_TEST_FLUX9, m_strFlux9);
    DDX_Text(pDX, IDC_EDIT_LED_WARMUP_SINGLETIME, m_iElectricalHeatingmsec);
	DDX_Text(pDX, IDC_EDIT_LED_WARMUP_TIME, m_iWarmUpTimeMinute);
	DDX_Text(pDX, IDC_EDIT_TEST_FREQUENCY, m_fFrequency);
	DDX_Text(pDX, IDC_EDIT_TEST_VOLTAGE, m_fVoltage);
	DDX_Text(pDX, IDC_EDIT_INTEGRAL_TIME, m_fIntegralTimems);
	DDX_Text(pDX, IDC_EDIT_TEST_FLUX11, m_strStdFlux1);
	DDX_Text(pDX, IDC_EDIT_TEST_FLUX12, m_strStdFlux2);
	DDX_Text(pDX, IDC_EDIT_TEST_FLUX13, m_strStdFlux3);
	DDX_Text(pDX, IDC_EDIT_TEST_FLUX14, m_strStdFlux4);
	DDX_Text(pDX, IDC_EDIT_TEST_FLUX15, m_strStdFlux5);
	DDX_Text(pDX, IDC_EDIT_TEST_FLUX16, m_strStdFlux6);
	DDX_Text(pDX, IDC_EDIT_TEST_FLUX17, m_strStdFlux7);
	DDX_Text(pDX, IDC_EDIT_TEST_FLUX18, m_strStdFlux8);
	DDX_Text(pDX, IDC_EDIT_TEST_FLUX19, m_strStdFlux9);
	DDX_Text(pDX, IDC_EDIT_TEST_FLUX20, m_strStdFlux10);
	DDX_Control(pDX, IDC_COMBO_RANGE_U, m_cRangeV);
	DDX_Control(pDX, IDC_COMBO_RANGE_I, m_cRangeI);

	DDX_CBIndex(pDX, IDC_COMBO_CF2, m_iRangeCF);
	DDX_CBIndex(pDX, IDC_COMBO_RANGE_I, m_iRangeI);
	DDX_CBIndex(pDX, IDC_COMBO_RANGE_U, m_iRangeU);
}


BEGIN_MESSAGE_MAP(CRectificationTestDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_TEST, &CRectificationTestDlg::OnBnClickedButtonTest)
	ON_BN_CLICKED(IDOK, &CRectificationTestDlg::OnBnClickedOk)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_ONE_STEP, &CRectificationTestDlg::OnBnClickedButtonOneStep)
	ON_BN_CLICKED(IDC_BUTTON_IN_POSITION, &CRectificationTestDlg::OnBnClickedButtonInPosition)
	ON_CBN_SELCHANGE(IDC_COMBO_CF2, &CRectificationTestDlg::OnCbnSelchangeComboCf2)
	ON_BN_CLICKED(IDC_BUTTON_TEST_STOP, &CRectificationTestDlg::OnBnClickedButtonTestStop)
END_MESSAGE_MAP()


// CRectificationTestDlg 消息处理程序


void CRectificationTestDlg::OnBnClickedButtonTest()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strTemp;
	strTemp.Format("当前测试电源输出电压为%gV，频率为%gHz, 是否控制电源输出?", 
		m_fSetVoltage, 
		m_fSetFrequency);
	CWarningYesNODlg WarningYesNODlg;
	WarningYesNODlg.m_strInfo = strTemp;
	if (IDCANCEL == WarningYesNODlg.DoModal())
	{
		return;
	}
    BOOL bR;
    if (g_DPSComm.IsRunning())
    {
        RealTimeData data;
        bR = g_DPSComm.GetRealTimeData(data);
        float fVoltage = m_fSetVoltage, 
            fFrequency = m_fSetFrequency;
        if (fabs(data.fVoltageValue - fVoltage) > fVoltage / 100 || fabs(data.fFrequence - fFrequency) > fFrequency / 100)
        {
            bR = g_DPSComm.SetParameterRunning(m_fSetVoltage, m_fSetFrequency,
                g_DPSComm.GetLimitData().LimitCurrentRange2.fUpper, g_DPSComm.GetLimitData().LimitPower.fUpper);
        }
    }
    else
    {
        bR = g_DPSComm.StopOutput();
        bR = g_DPSComm.FastRun(m_fSetVoltage, m_fSetFrequency);
    }
    if (!bR)
    {
        AfxMessageBox("输出电源控制失败!");
        return;
    }

	if (!UpdateData(TRUE))
	{
		return;
	}

   
	m_fStdValue[0] = (float)atof(m_strStdFlux1);
	m_fStdValue[1] = (float)atof(m_strStdFlux2);
	m_fStdValue[2] = (float)atof(m_strStdFlux3);
	m_fStdValue[3] = (float)atof(m_strStdFlux4);
	m_fStdValue[4] = (float)atof(m_strStdFlux5);
	
	m_fStdValue[5] = (float)atof(m_strStdFlux6);
	m_fStdValue[6] = (float)atof(m_strStdFlux7);
	m_fStdValue[7] = (float)atof(m_strStdFlux8);
	m_fStdValue[8] = (float)atof(m_strStdFlux9);
	m_fStdValue[9] = (float)atof(m_strStdFlux10);

	GetDlgItem(IDC_BUTTON_TEST)->GetWindowTextA(strTemp);
	if (1)//"重测" == strTemp)
	{
		BeginWaitCursor();
		if (g_pDoc->m_CommSettingsData.m_iTestChannelControlerType == 1)
		{
			if (!g_SC1000Comm.SwitchAllLamp(TRUE))
			{
				AfxMessageBox("开灯失败！");
				return;
			}
		}
		else
		{
			if (!g_TestChannelControlComm.SwitchAllChannel(TRUE))
			{
				AfxMessageBox("开灯失败！");
				return;
			}
		}
		EndWaitCursor();
	
		m_bIsElectricalRunning = FALSE;
		m_bIsSpectrumRunning = FALSE;

		m_strFlux1 = _T("");
		m_strFlux10 = _T("");
		m_strFlux2 = _T("");
		m_strFlux3 = _T("");
		m_strFlux4 = _T("");
		m_strFlux5 = _T("");
		m_strFlux6 = _T("");
		m_strFlux7 = _T("");
		m_strFlux8 = _T("");
		m_strFlux9 = _T("");

	//	GetDlgItem(IDC_BUTTON_TEST)->SetWindowText("取消测试");
	//	GetDlgItem(IDOK)->EnableWindow(FALSE);
	
		m_timeStart = CTime::GetCurrentTime();

		//SetTimer(1, 1000, NULL);
		m_bCancel = FALSE;
		AfxBeginThread(ThreadSpectrumCorr, this);
	}
/*	else
	{
		m_bCancel = TRUE;
		KillTimer(1);
		GetDlgItem(IDC_BUTTON_TEST)->SetWindowText("重测");
		GetDlgItem(IDC_STATIC_REMAIN_TIME)->SetWindowTextA("");
	}*/
}


BOOL CRectificationTestDlg::IsTesting()
{
	return m_bIsSpectrumRunning || m_bIsElectricalRunning;
}


void CRectificationTestDlg::SetResult(int iIndex, float fFlux)
{
	switch(iIndex)
	{
	case 0:
		m_strFlux1.Format("%.2f", fFlux);
		GetDlgItem(IDC_EDIT_TEST_FLUX1)->SetWindowTextA(m_strFlux1);
		break;

	case 1:
		m_strFlux2.Format("%.2f", fFlux);
		GetDlgItem(IDC_EDIT_TEST_FLUX2)->SetWindowTextA(m_strFlux2);
		break;

	case 2:
		m_strFlux3.Format("%.2f", fFlux);
		GetDlgItem(IDC_EDIT_TEST_FLUX3)->SetWindowTextA(m_strFlux3);
		break;

	case 3:
		m_strFlux4.Format("%.2f", fFlux);
		GetDlgItem(IDC_EDIT_TEST_FLUX4)->SetWindowTextA(m_strFlux4);
		break;

	case 4:
		m_strFlux5.Format("%.2f", fFlux);
		GetDlgItem(IDC_EDIT_TEST_FLUX5)->SetWindowTextA(m_strFlux5);
		break;

	case 5:
		m_strFlux6.Format("%.2f", fFlux);
		GetDlgItem(IDC_EDIT_TEST_FLUX6)->SetWindowTextA(m_strFlux6);
		break;

	case 6:
		m_strFlux7.Format("%.2f", fFlux);
		GetDlgItem(IDC_EDIT_TEST_FLUX7)->SetWindowTextA(m_strFlux7);
		break;

	case 7:
		m_strFlux8.Format("%.2f", fFlux);
		GetDlgItem(IDC_EDIT_TEST_FLUX8)->SetWindowTextA(m_strFlux8);
		break;

	case 8:
		m_strFlux9.Format("%.2f", fFlux);
		GetDlgItem(IDC_EDIT_TEST_FLUX9)->SetWindowTextA(m_strFlux9);
		break;

	case 9:
		m_strFlux10.Format("%.2f", fFlux);
		GetDlgItem(IDC_EDIT_TEST_FLUX10)->SetWindowTextA(m_strFlux10);
		break;

	default:
		break;
	}

	//UpdateData(FALSE);
}

UINT CRectificationTestDlg::ThreadSpectrumCorr(LPVOID pPar)
{
	CRectificationTestDlg * pDlg = (CRectificationTestDlg *)pPar;
	pDlg->EnableAllData(TRUE);
	//预热
	while (1)
	{
		if(pDlg->m_bCancel)
		{
			pDlg->EnableAllData(FALSE);
			return 0;
		}

		CTime time2 = CTime::GetCurrentTime();
		if ( (time2 - pDlg->m_timeStart).GetTotalSeconds() >= pDlg->m_iWarmUpTimeMinute * 60)
		{
			
		}

		CString strTemp;
		if (pDlg->m_iWarmUpTimeMinute * 60 - (time2 - pDlg->m_timeStart).GetTotalSeconds() < 0)
		{
			strTemp.Format("预热完成！");
			pDlg->GetDlgItem(IDC_STATIC_REMAIN_TIME)->SetWindowTextA(strTemp);
			break;
		}
		else
		{
			strTemp.Format("预热剩余时间：%d 秒",
				pDlg->m_iWarmUpTimeMinute * 60 - (time2 - pDlg->m_timeStart).GetTotalSeconds());
			pDlg->GetDlgItem(IDC_STATIC_REMAIN_TIME)->SetWindowTextA(strTemp);
			Sleep(200);
		}		
	}

	//1. Check DPS
	BOOL bR = FALSE;
	if (g_DPSComm.IsRunning())
	{
		RealTimeData data;
		bR = g_DPSComm.GetRealTimeData(data);
		float fVoltage = pDlg->m_fSetVoltage, 
			fFrequency = pDlg->m_fSetFrequency;
		if (fabs(data.fVoltageValue - fVoltage) > fVoltage / 100 || fabs(data.fFrequence - fFrequency) > fFrequency / 100)
		{
			bR = g_DPSComm.SetParameterRunning(pDlg->m_fSetVoltage, pDlg->m_fSetFrequency,
				g_DPSComm.GetLimitData().LimitCurrentRange2.fUpper, g_DPSComm.GetLimitData().LimitPower.fUpper);
		}
	}
	else
	{
		g_DPSComm.StopOutput();
		bR = g_DPSComm.FastRun(pDlg->m_fSetVoltage, pDlg->m_fSetFrequency);
	}

	// Wait spectrum get dark AD OK
	// 2.Sample dark AD
	if(g_pDoc->m_CommSettingsData.m_iTestChannelControlerType == 1)
	{
		bR = g_SC1000Comm.SwitchAllLamp(FALSE);	// Turn off all lamp		
	}
	else
	{
		bR = g_TestChannelControlComm.SwitchAllChannel(FALSE);	// Turn off all lamp				
	}
	if (!bR)
	{
		AfxMessageBox("切换测试通道失败！");
	}

	float * pAD = new float[g_Hass1200Meter.GetCCDPixNum()];
	float * pDarkAD = new float[g_Hass1200Meter.GetCCDPixNum()];
	float * pDarkAD_ShutterOff = new float[g_Hass1200Meter.GetCCDPixNum()];

	ASSERT(NULL != pAD && NULL != pDarkAD);
	g_Hass1200Meter.SetIntTime(pDlg->m_fIntegralTimems);
	g_Hass1200Meter.SetShutterOff();
	Sleep(100);
	g_Hass1200Meter.SampleAD(pDarkAD_ShutterOff, FALSE);

	g_Hass1200Meter.SetShutterOn();
	Sleep(100);
	g_Hass1200Meter.SampleAD(pDarkAD, FALSE);

	float fIp;
	for (int i = 0; i < g_Hass1200Meter.GetCCDPixNum(); i++)
	{
		if (i == 0)
		{
			fIp = pDarkAD[i] - pDarkAD_ShutterOff[i];
		}
		else
		{
			if (fIp < pDarkAD[i] - pDarkAD_ShutterOff[i])
			{
				fIp = pDarkAD[i] - pDarkAD_ShutterOff[i];
			}
		}
	}
	delete[]pDarkAD_ShutterOff;
	if (fIp > g_iDarkAD)
	{
		CString strTemp;
		strTemp.Format("Dark AD > %d，请调整测试装置到合适的位置再测试！", g_iDarkAD);
		AfxMessageBox(strTemp);
	}

	BOOL bADTooSmall = FALSE, bADOverFlow = FALSE;

	//开始校正
	for (int i = 0; i < g_iColomnNum; i++)
	{
		if (pDlg->m_bCancel)
		{
			pDlg->EnableAllData(FALSE);
			return 0;
		}

		// a.Switch to current channel
		if (g_pDoc->m_CommSettingsData.m_iTestChannelControlerType == 1)
		{
			g_SC1000Comm.SwitchChannel(i);
		}
		else
		{
			g_TestChannelControlComm.SwitchOneChannel(i, TRUE);
		}

		// Warm up time
		Sleep(pDlg->m_iElectricalHeatingmsec);

		// Let spectrum begin test this LED
		// b.Get LED spectrum data
		if (1)
		{
			bR = g_Hass1200Meter.SampleAD(pAD);
			if (i == 0)
			{
				CLedData data;
				if (!g_pDoc->m_CommSettingsData.m_iPFType)
				{
					for (int j = g_PowerMeterComm.GetCurRangeNum() - 1; j >= 0; j --)
					{
						// Set power meter range
						bR = g_PowerMeterComm.SetRange(pDlg->m_iRangeU,
							j,	pDlg->m_iRangeCF);
						Sleep(100);
						bR = g_PowerMeterComm.Read(data.m_fVoltageV, data.m_fCurrentA, data.m_fPowerW, data.m_fPowerFactor);
						if (data.m_fCurrentA > g_PowerMeterComm.GetCurRange(j) * 0.05f && data.m_fCurrentA < g_PowerMeterComm.GetCurRange(j) * 0.90f)
						{
							pDlg->m_fCurrentA[i] = data.m_fCurrentA;
							pDlg->m_iRangeI = j;
							pDlg->m_cRangeI.SetCurSel(pDlg->m_iRangeI);
							break;
						}
					}
				}
				else
				{
					bR = g_PowerMeterComm.SetCurrentAutoRange(TRUE);
					int iCurSel = 0;
					Sleep(1000);
readI:
					bR = g_PowerMeterComm.Read(data.m_fVoltageV, data.m_fCurrentA, data.m_fPowerW, data.m_fPowerFactor);
					bR = g_PowerMeterComm.GetCurrentAutoRange(iCurSel);
					Sleep(1000);
					bR = g_PowerMeterComm.Read(data.m_fVoltageV, data.m_fCurrentA, data.m_fPowerW, data.m_fPowerFactor);
					bR = g_PowerMeterComm.GetCurrentAutoRange(pDlg->m_iRangeI);	
					if (iCurSel != pDlg->m_iRangeI)
					{
						iCurSel = pDlg->m_iRangeI;
						goto readI;
					}
					pDlg->m_cRangeI.SetCurSel(pDlg->m_iRangeI);
					Sleep(100);
					bR = g_PowerMeterComm.SetCurrentAutoRange(FALSE);

					bR = g_PowerMeterComm.Read(data.m_fVoltageV, data.m_fCurrentA, data.m_fPowerW, data.m_fPowerFactor);
					pDlg->m_fCurrentA[i] = data.m_fCurrentA;

				}
			}
			Sleep(1000);
			if (bR)// && pDlg->m_fCurrentA[i] > 0.001)
			{
				CNewTestColorData data;
				g_Hass1200Meter.CalcColor(0.2f, pDlg->m_fIntegralTimems,
					pDlg->m_fIntegralTimems, pDarkAD, pAD, data);
				pDlg->m_fTestValue1[i] = data.m_fPh;

				Sleep(100);
				bR = g_Hass1200Meter.SampleAD(pAD);
				g_Hass1200Meter.CalcColor(0.2f, pDlg->m_fIntegralTimems,
					pDlg->m_fIntegralTimems, pDarkAD, pAD, data);
				pDlg->m_fTestValue2[i] = data.m_fPh;

				// Show test value
				pDlg->SetResult(i, pDlg->m_fTestValue2[i] * pDlg->m_fStdValue[i] / (pDlg->m_fTestValue1[i] > 1 ? pDlg->m_fTestValue1[i] : 1));

				CString strTemp;
				strTemp.Format("Ip:%.0f", data.m_fIp);
				pDlg->GetDlgItem(IDC_STATIC_REMAIN_TIME)->SetWindowTextA(strTemp);

				if (data.m_fIp < 10000)
				{
					bADTooSmall = TRUE;
				}
				if (data.m_fIp > 65000)
				{
					bADOverFlow = TRUE;
				}
			}
			else
			{
				pDlg->m_fTestValue2[i] = 0;
				pDlg->SetResult(i, 0);
			}
		}
	}

	delete [] pAD;
	delete [] pDarkAD;

	// 5.Show info
	if (bADOverFlow)
	{
		AfxMessageBox("AD溢出，请适当减小积分时间！");
	}
	if (bADTooSmall)
	{
		AfxMessageBox("AD过小，请适当增大积分时间！");
	}
    int iUnOnLEDNum = 0;
    for (int i = 0; i < g_iColomnNum; i++)
    {
        if (pDlg->m_fTestValue2[i] == 0)
        {
            iUnOnLEDNum ++;
        }
    }
    if (iUnOnLEDNum > 0)
    {
        CString strTemp;
        strTemp.Format("光度校正过程中有%d通道灯未亮!", iUnOnLEDNum);
        AfxMessageBox(strTemp);
    }

	pDlg->EnableAllData(FALSE);
	return 0;
}

UINT CRectificationTestDlg::ThreadElectrical(LPVOID pPar)
{
	CRectificationTestDlg * pDlg = (CRectificationTestDlg *)pPar;

	// 1.Start test
	pDlg->m_bIsElectricalRunning = TRUE;

	// Check DPS
	BOOL bR = FALSE;
	if (g_DPSComm.IsRunning())
	{
        RealTimeData data;
        bR = g_DPSComm.GetRealTimeData(data);
		float fVoltage = pDlg->m_fSetVoltage, 
			fFrequency = pDlg->m_fSetFrequency;
		if (fabs(data.fVoltageValue - fVoltage) > fVoltage / 100 || fabs(data.fFrequence - fFrequency) > fFrequency / 100)
		{
			bR = g_DPSComm.SetParameterRunning(pDlg->m_fSetVoltage, pDlg->m_fSetFrequency,
				g_DPSComm.GetLimitData().LimitCurrentRange2.fUpper, g_DPSComm.GetLimitData().LimitPower.fUpper);
		}
	}
	else
	{
		g_DPSComm.StopOutput();
		bR = g_DPSComm.FastRun(pDlg->m_fSetVoltage, pDlg->m_fSetFrequency);
	}
	
	// Wait spectrum get dark AD OK
	bR = pDlg->m_eventOneLEDSpectrumOK.Lock();

	for (int i = 0; i < g_iColomnNum; i++)
	{
		if (!pDlg->m_pbTestChannel[i])
		{
			continue;
		}

		// a.Switch to current channel
		if (g_pDoc->m_CommSettingsData.m_iTestChannelControlerType == 1)
		{
			g_SC1000Comm.SwitchChannel(i);
		}
		else
		{
			g_TestChannelControlComm.SwitchOneChannel(i, TRUE);
		}

		// Warm up time
		Sleep(pDlg->m_iElectricalHeatingmsec);

		// Let spectrum begin test this LED
		BOOL bR = pDlg->m_eventOneLEDON.SetEvent();

		// b.Test electrical data of this LED
		CLedData data;
		data.m_fFrequencyHz = pDlg->m_fFrequency;

		if (i == 0)
		{
		}
		else
		{
			bR = g_PowerMeterComm.Read(data.m_fVoltageV, data.m_fCurrentA, data.m_fPowerW, data.m_fPowerFactor);
			pDlg->m_fCurrentA[i] = data.m_fCurrentA;			
		}
		// c.Wait spectrum be OK
		bR = pDlg->m_eventOneLEDSpectrumOK.Lock();
	}
			
	// 2.Reset event
	//g_DPSComm.StopOutput();
	if (g_pDoc->m_CommSettingsData.m_iTestChannelControlerType == 1)
	{
		g_SC1000Comm.SwitchAllLamp(TRUE);
	}
	else
	{
		g_TestChannelControlComm.SwitchAllChannel(TRUE);
	}
	pDlg->m_bIsElectricalRunning = FALSE;

	return 0;
}


UINT CRectificationTestDlg::ThreadSpectrum(LPVOID pPar)
{
	CRectificationTestDlg * pDlg = (CRectificationTestDlg *)pPar;

	// 1.Start test
	pDlg->m_bIsSpectrumRunning = TRUE;
	BOOL bADTooSmall = FALSE, bADOverFlow = FALSE;

	// 2.Sample dark AD
	BOOL bR;
	if(g_pDoc->m_CommSettingsData.m_iTestChannelControlerType == 1)
	{
		bR = g_SC1000Comm.SwitchAllLamp(FALSE);	// Turn off all lamp		
	}
	else
	{
		bR = g_TestChannelControlComm.SwitchAllChannel(FALSE);	// Turn off all lamp				
	}
	if (!bR)
	{
		AfxMessageBox("切换测试通道失败！");
	}

	float * pAD = new float[g_Hass1200Meter.GetCCDPixNum()];
	float * pDarkAD = new float[g_Hass1200Meter.GetCCDPixNum()];
	float * pDarkAD_ShutterOff = new float[g_Hass1200Meter.GetCCDPixNum()];

	ASSERT(NULL != pAD && NULL != pDarkAD);
	g_Hass1200Meter.SetIntTime(pDlg->m_fIntegralTimems);
	g_Hass1200Meter.SetShutterOff();
	Sleep(100);
	g_Hass1200Meter.SampleAD(pDarkAD_ShutterOff, FALSE);

	g_Hass1200Meter.SetShutterOn();
	Sleep(100);
	g_Hass1200Meter.SampleAD(pDarkAD, FALSE);

	float fIp;
	for (int i = 0; i < g_Hass1200Meter.GetCCDPixNum(); i++)
	{
		if (i == 0)
		{
			fIp = pDarkAD[i] - pDarkAD_ShutterOff[i];
		}
		else
		{
			if (fIp < pDarkAD[i] - pDarkAD_ShutterOff[i])
			{
				fIp = pDarkAD[i] - pDarkAD_ShutterOff[i];
			}
		}
	}
	delete[]pDarkAD_ShutterOff;
	if (fIp > g_iDarkAD)
	{
		CString strTemp;
		strTemp.Format("Dark AD > %d，请调整测试装置到合适的位置再测试！", g_iDarkAD);
		AfxMessageBox(strTemp);
	}
			
	// Get dark AD OK
	pDlg->m_eventOneLEDSpectrumOK.SetEvent();


	for (int i = 0; i < g_iColomnNum; i++)
	{
		if (!pDlg->m_pbTestChannel[i])
		{
			continue;
		}
/*
		CLedData data;
		data.m_fFrequencyHz = pDlg->m_fFrequency;
		bR = g_PowerMeterComm.Read(data.m_fVoltageV, data.m_fCurrentA, data.m_fPowerW, data.m_fPowerFactor);
		pDlg->m_fCurrentA[i] = data.m_fCurrentA;
		*/
		// a.Wait LED ON
		BOOL bR = pDlg->m_eventOneLEDON.Lock();

		// b.Get LED spectrum data
		if (1)
		{
			bR = g_Hass1200Meter.SampleAD(pAD);
			if (i == 0)
			{
				CLedData data;
				if (!g_pDoc->m_CommSettingsData.m_iPFType)
				{
					for (int j = g_PowerMeterComm.GetCurRangeNum() - 1; j >= 0; j --)
					{
						// Set power meter range
						bR = g_PowerMeterComm.SetRange(pDlg->m_iRangeU,
							j,	pDlg->m_iRangeCF);
						Sleep(100);
						bR = g_PowerMeterComm.Read(data.m_fVoltageV, data.m_fCurrentA, data.m_fPowerW, data.m_fPowerFactor);
						if (data.m_fCurrentA > g_PowerMeterComm.GetCurRange(j) * 0.05f && data.m_fCurrentA < g_PowerMeterComm.GetCurRange(j) * 0.90f)
						{
							pDlg->m_fCurrentA[i] = data.m_fCurrentA;
							pDlg->m_iRangeI = j;
							pDlg->m_cRangeI.SetCurSel(pDlg->m_iRangeI);
							break;
						}
					}
				}
				else
				{
					bR = g_PowerMeterComm.SetCurrentAutoRange(TRUE);
					int iCurSel = 0;
					Sleep(1000);
readI:
					bR = g_PowerMeterComm.Read(data.m_fVoltageV, data.m_fCurrentA, data.m_fPowerW, data.m_fPowerFactor);
					bR = g_PowerMeterComm.GetCurrentAutoRange(iCurSel);
					Sleep(1000);
					bR = g_PowerMeterComm.Read(data.m_fVoltageV, data.m_fCurrentA, data.m_fPowerW, data.m_fPowerFactor);
					bR = g_PowerMeterComm.GetCurrentAutoRange(pDlg->m_iRangeI);	
					if (iCurSel != pDlg->m_iRangeI)
					{
						iCurSel = pDlg->m_iRangeI;
						goto readI;
					}
					pDlg->m_cRangeI.SetCurSel(pDlg->m_iRangeI);
					Sleep(100);
					bR = g_PowerMeterComm.SetCurrentAutoRange(FALSE);

					bR = g_PowerMeterComm.Read(data.m_fVoltageV, data.m_fCurrentA, data.m_fPowerW, data.m_fPowerFactor);
					pDlg->m_fCurrentA[i] = data.m_fCurrentA;

				}
			}
			Sleep(1000);
			if (bR)// && pDlg->m_fCurrentA[i] > 0.001)
			{
				CNewTestColorData data;
				g_Hass1200Meter.CalcColor(0.2f, pDlg->m_fIntegralTimems,
					pDlg->m_fIntegralTimems, pDarkAD, pAD, data);
				pDlg->m_fTestValue1[i] = data.m_fPh;

				Sleep(100);
				bR = g_Hass1200Meter.SampleAD(pAD);
				g_Hass1200Meter.CalcColor(0.2f, pDlg->m_fIntegralTimems,
					pDlg->m_fIntegralTimems, pDarkAD, pAD, data);
				pDlg->m_fTestValue2[i] = data.m_fPh;

				// Show test value
				pDlg->SetResult(i, pDlg->m_fTestValue2[i] * pDlg->m_fStdValue[i] / (pDlg->m_fTestValue1[i] > 1 ? pDlg->m_fTestValue1[i] : 1));
				
				CString strTemp;
				strTemp.Format("Ip:%.0f", data.m_fIp);
				pDlg->GetDlgItem(IDC_STATIC_REMAIN_TIME)->SetWindowTextA(strTemp);
				
				if (data.m_fIp < 10000)
				{
					bADTooSmall = TRUE;
				}
				if (data.m_fIp > 65000)
				{
					bADOverFlow = TRUE;
				}
			}
			else
			{
                pDlg->m_fTestValue2[i] = 0;
				pDlg->SetResult(i, 0);
			}
		}

		// d.Check if there is any LED remain to be test
		pDlg->m_eventOneLEDSpectrumOK.SetEvent();
	}

	delete [] pAD;
	delete [] pDarkAD;
			
	// 4.Test end
	g_Hass1200Meter.SetShutterOff();
	pDlg->m_bIsSpectrumRunning = FALSE;

	pDlg->GetDlgItem(IDC_STATIC_REMAIN_TIME)->SetWindowTextA("");

	// 5.Show info
	if (bADOverFlow)
	{
		AfxMessageBox("AD溢出，请适当减小积分时间！");
	}
	if (bADTooSmall)
	{
		AfxMessageBox("AD过小，请适当增大积分时间！");
	}
    int iUnOnLEDNum = 0;
    for (int i = 0; i < DATA_CAHNNEL_NUM; i++)
    {
        if (!pDlg->m_pbTestChannel[i])
        {
            continue;
        }
        if (pDlg->m_fTestValue2[i] == 0)
        {
            iUnOnLEDNum ++;
        }
    }
    if (iUnOnLEDNum > 0)
    {
        CString strTemp;
        strTemp.Format("光度校正过程中有%d通道灯未亮!", iUnOnLEDNum);
        AfxMessageBox(strTemp);
    }
	return 0;
}


void CRectificationTestDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	if (IsTesting())
	{
		AfxMessageBox("测试正在进行，请等待测试结束后再退出！");
		return;
	}

	CDialogEx::OnCancel();
}


void CRectificationTestDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	if (IsTesting())
	{
		return;
	}

	CDialogEx::OnOK();
}


void CRectificationTestDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (1 == nIDEvent)
	{
		CTime time2 = CTime::GetCurrentTime();
		if ( (time2 - m_timeStart).GetTotalSeconds() >= m_iWarmUpTimeMinute * 60)
		{
			GetDlgItem(IDC_COMBO_RANGE_U)->EnableWindow(FALSE);
			GetDlgItem(IDC_COMBO_RANGE_I)->EnableWindow(FALSE);
			GetDlgItem(IDC_COMBO_CF2)->EnableWindow(FALSE);
	//		AfxBeginThread(ThreadElectrical, this);
	//		AfxBeginThread(ThreadSpectrum, this);
			AfxBeginThread(ThreadSpectrumCorr, this);
			KillTimer(nIDEvent);
			GetDlgItem(IDC_STATIC_REMAIN_TIME)->SetWindowTextA("");
			GetDlgItem(IDC_BUTTON_TEST)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_TEST)->SetWindowText("重测");
		}

        CString strTemp;
        if (m_iWarmUpTimeMinute * 60 - (time2 - m_timeStart).GetTotalSeconds() < 0)
        {
            strTemp.Format("预热完成！");
        }
        else
        {
            strTemp.Format("预热剩余时间：%d 秒",
                m_iWarmUpTimeMinute * 60 - (time2 - m_timeStart).GetTotalSeconds());
        }
        GetDlgItem(IDC_STATIC_REMAIN_TIME)->SetWindowTextA(strTemp);
	}

	CDialogEx::OnTimer(nIDEvent);
}


BOOL CRectificationTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString strTemp;
	m_cRangeI.ResetContent();
	m_cRangeV.ResetContent();
	for (int i = 0; i < g_PowerMeterComm.GetVolRangeNum(); i ++)
	{
		strTemp.Format("%g", g_PowerMeterComm.GetVolRange(i));
		m_cRangeV.AddString(strTemp);
	}

	for (int i = 0; i < g_PowerMeterComm.GetCurRangeNum(); i ++)
	{
		strTemp.Format("%g", g_PowerMeterComm.GetCurRange(i));
		m_cRangeI.AddString(strTemp);
	}

	GetDlgItem(IDC_STATIC_REMAIN_TIME)->SetWindowTextA("");


	m_strFlux1.Format("%.2f", m_fShowValue[0]);
	m_strFlux2.Format("%.2f", m_fShowValue[1]);
	m_strFlux3.Format("%.2f", m_fShowValue[2]);
	m_strFlux4.Format("%.2f", m_fShowValue[3]);
	m_strFlux5.Format("%.2f", m_fShowValue[4]);

	m_strFlux6.Format("%.2f", m_fShowValue[5]);
	m_strFlux7.Format("%.2f", m_fShowValue[6]);
	m_strFlux8.Format("%.2f", m_fShowValue[7]);
	m_strFlux9.Format("%.2f", m_fShowValue[8]);
	m_strFlux10.Format("%.2f", m_fShowValue[8]);
	
	m_strStdFlux1.Format("%.2f", m_fStdValue[0]);
	m_strStdFlux2.Format("%.2f", m_fStdValue[1]);
	m_strStdFlux3.Format("%.2f", m_fStdValue[2]);
	m_strStdFlux4.Format("%.2f", m_fStdValue[3]);
	m_strStdFlux5.Format("%.2f", m_fStdValue[4]);

	m_strStdFlux6.Format("%.2f", m_fStdValue[5]);
	m_strStdFlux7.Format("%.2f", m_fStdValue[6]);
	m_strStdFlux8.Format("%.2f", m_fStdValue[7]);
	m_strStdFlux9.Format("%.2f", m_fStdValue[8]);
	m_strStdFlux10.Format("%.2f", m_fStdValue[9]);
	EnaleControls_bDisor_LowExecu();
	UpdateData(FALSE);
	for (int i = 0; i < DATA_CAHNNEL_NUM; i ++)
	{
		if (i >= g_iColomnNum)
		{
            GetDlgItem(IDC_STATIC_VOLTAGE2 + i)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_TEST_FLUX1 + i)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_EDIT_TEST_FLUX11 + i)->ShowWindow(SW_HIDE);
		}
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CRectificationTestDlg::OnBnClickedButtonOneStep()
{
	// TODO: 在此添加控件通知处理程序代码
	BeginWaitCursor();
    BOOL bR;
    if (g_DPSComm.IsRunning())
    {
        bR = g_DPSComm.StopOutput();
        if (!bR)
        {
            AfxMessageBox("输出电源控制失败!");
            return;
        }
    }
	g_LineControllerComm.MoveLineOneStep();
	EndWaitCursor();
}


void CRectificationTestDlg::OnBnClickedButtonInPosition()
{
	// TODO: 在此添加控件通知处理程序代码
	// Move standard LED to the test row
	if (IDOK != AfxMessageBox("标准灯是否已经正确安装在标准灯上灯区？", MB_OKCANCEL))
	{
		return;
	}
	BeginWaitCursor();
    BOOL bR;
    if (g_DPSComm.IsRunning())
    {
        bR = g_DPSComm.StopOutput();
        if (!bR)
        {
            AfxMessageBox("输出电源控制失败!");
            return;
        }
    }
   	for (int i = 0; i < atoi(g_pDoc->m_CommSettingsData.m_strCalibrationRange)  + 1; i++)
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
			Sleep(100);
		}// while
		
		Sleep(1000);		// Make sure the line is stopped
	}
	EndWaitCursor();

	// Test one time
	OnBnClickedButtonTest();
}


void CRectificationTestDlg::EnaleControls_bDisor_LowExecu()
{
	if (LOW_EXECUTION_LEVEL ==  g_iExecutionLevel || TRUE == g_bDisplayLimitOnly)
	{
		CEdit *pEdit = (CEdit*)GetDlgItem(IDC_EDIT_TEST_FLUX11);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_TEST_FLUX12);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_TEST_FLUX13);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_TEST_FLUX14);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_TEST_FLUX15);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_TEST_FLUX16);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_TEST_FLUX17);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_TEST_FLUX18);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_TEST_FLUX19);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_TEST_FLUX20);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_INTEGRAL_TIME);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_LED_WARMUP_TIME);
		pEdit->SetReadOnly(TRUE);
		GetDlgItem(IDC_BUTTON_ONE_STEP)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_IN_POSITION)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_TEST)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_COMBO_RANGE_U)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_RANGE_I)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_CF2)->EnableWindow(FALSE);
	}
}


void CRectificationTestDlg::OnCbnSelchangeComboCf2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	g_PowerMeterComm.Initialize(g_pDoc->m_CommSettingsData.m_strCOMPF2010A ,g_pDoc->m_CommSettingsData.m_iPFType, 
		m_iRangeCF);
	CString strTemp;
	m_cRangeI.ResetContent();
	m_cRangeV.ResetContent();
	for (int i = 0; i < g_PowerMeterComm.GetVolRangeNum(); i ++)
	{
		strTemp.Format("%g", g_PowerMeterComm.GetVolRange(i));
		m_cRangeV.AddString(strTemp);
	}

	for (int i = 0; i < g_PowerMeterComm.GetCurRangeNum(); i ++)
	{
		strTemp.Format("%g", g_PowerMeterComm.GetCurRange(i));
		m_cRangeI.AddString(strTemp);
	}
	m_cRangeV.SetCurSel(0);
	m_cRangeI.SetCurSel(0);
}

void CRectificationTestDlg::EnableAllData(BOOL bTest)
{
	GetDlgItem(IDC_BUTTON_TEST)->EnableWindow(!bTest);
	GetDlgItem(IDOK)->EnableWindow(!bTest);
	GetDlgItem(IDC_BUTTON_TEST_STOP)->EnableWindow(bTest);
	GetDlgItem(IDC_BUTTON_ONE_STEP)->EnableWindow(!bTest);
	GetDlgItem(IDC_BUTTON_IN_POSITION)->EnableWindow(!bTest);
	GetDlgItem(IDC_COMBO_RANGE_U)->EnableWindow(!bTest);
	GetDlgItem(IDC_COMBO_RANGE_I)->EnableWindow(!bTest);
	GetDlgItem(IDC_COMBO_CF2)->EnableWindow(!bTest);

	GetDlgItem(IDC_STATIC_REMAIN_TIME)->SetWindowTextA("");
}


void CRectificationTestDlg::OnBnClickedButtonTestStop()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bCancel = TRUE;
}
