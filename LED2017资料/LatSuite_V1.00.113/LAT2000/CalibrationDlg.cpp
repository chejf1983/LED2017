// CalibrationDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "CalibrationDlg.h"
#include "afxdialogex.h"
#include "MyMFC_Lib.h"


extern CString			g_strCurrentPath;
// CCalibrationDlg 对话框

IMPLEMENT_DYNAMIC(CCalibrationDlg, CDialogEx)

CCalibrationDlg::CCalibrationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCalibrationDlg::IDD, pParent), m_pDoc(NULL)
{
	m_strCalPath = g_strCurrentPath + "Cal\\";
	CreateDirectory(m_strCalPath, NULL);

	m_iRangeI = 0;
	m_iRangeU = 0;
	
	CString strSection = "Calibration";
	m_fbI = (float)atof(AfxGetApp()->GetProfileString(strSection, "m_fbI", "0"));
	m_fbU = (float)atof(AfxGetApp()->GetProfileString(strSection, "m_fbU", "0"));
	m_fDAI1 = (float)atof(AfxGetApp()->GetProfileString(strSection, "m_fDAI1", "0"));
	m_fDAI2 = (float)atof(AfxGetApp()->GetProfileString(strSection, "m_fDAI2", "0"));
	m_fDAU1 = (float)atof(AfxGetApp()->GetProfileString(strSection, "m_fDAU1", "0"));

	m_fDAU2 = (float)atof(AfxGetApp()->GetProfileString(strSection, "m_fDAU2", "0"));
	m_fI1 = (float)atof(AfxGetApp()->GetProfileString(strSection, "m_fI1", "0"));
	m_fI2 = (float)atof(AfxGetApp()->GetProfileString(strSection, "m_fI2", "0"));
	m_fkI = (float)atof(AfxGetApp()->GetProfileString(strSection, "m_fkI", "0"));
	m_fkU = (float)atof(AfxGetApp()->GetProfileString(strSection, "m_fkU", "0"));

	m_fStdI1 = (float)atof(AfxGetApp()->GetProfileString(strSection, "m_fStdI1", "0"));
	m_fStdI2 = (float)atof(AfxGetApp()->GetProfileString(strSection, "m_fStdI2", "0"));
	m_fStdU1 = (float)atof(AfxGetApp()->GetProfileString(strSection, "m_fStdU1", "0"));
	m_fStdU2 = (float)atof(AfxGetApp()->GetProfileString(strSection, "m_fStdU2", "0"));
	m_fU1 = (float)atof(AfxGetApp()->GetProfileString(strSection, "m_fU1", "0"));

	m_fU2 = (float)atof(AfxGetApp()->GetProfileString(strSection, "m_fU2", "0"));
}

CCalibrationDlg::~CCalibrationDlg()
{
	CString strSection = "Calibration";
	CString strTemp;
	
	strTemp.Format("%f", m_fbI);
	AfxGetApp()->WriteProfileString(strSection, "m_fbI", strTemp);
	strTemp.Format("%f", m_fbU);
	AfxGetApp()->WriteProfileString(strSection, "m_fbU", strTemp);
	strTemp.Format("%f", m_fDAI1);
	AfxGetApp()->WriteProfileString(strSection, "m_fDAI1", strTemp);
	strTemp.Format("%f", m_fDAI2);
	AfxGetApp()->WriteProfileString(strSection, "m_fDAI2", strTemp);
	strTemp.Format("%f", m_fDAU1);
	AfxGetApp()->WriteProfileString(strSection, "m_fDAU1", strTemp);
	strTemp.Format("%f", m_fDAU2);

	AfxGetApp()->WriteProfileString(strSection, "m_fDAU2", strTemp);
	strTemp.Format("%f", m_fI1);
	AfxGetApp()->WriteProfileString(strSection, "m_fI1", strTemp);
	strTemp.Format("%f", m_fI2);
	AfxGetApp()->WriteProfileString(strSection, "m_fI2", strTemp);
	strTemp.Format("%f", m_fI2);
	AfxGetApp()->WriteProfileString(strSection, "m_fI2", strTemp);
	strTemp.Format("%f", m_fkI);
	AfxGetApp()->WriteProfileString(strSection, "m_fkI", strTemp);
	strTemp.Format("%f", m_fkU);
	AfxGetApp()->WriteProfileString(strSection, "m_fkU", strTemp);

	strTemp.Format("%f", m_fStdI1);
	AfxGetApp()->WriteProfileString(strSection, "m_fStdI1", strTemp);
	strTemp.Format("%f", m_fStdI2);
	AfxGetApp()->WriteProfileString(strSection, "m_fStdI2", strTemp);
	strTemp.Format("%f", m_fStdU1);
	AfxGetApp()->WriteProfileString(strSection, "m_fStdU1", strTemp);
	strTemp.Format("%f", m_fStdU2);
	AfxGetApp()->WriteProfileString(strSection, "m_fStdU2", strTemp);
	strTemp.Format("%f", m_fU1);
	AfxGetApp()->WriteProfileString(strSection, "m_fU1", strTemp);

	strTemp.Format("%f", m_fU2);
	AfxGetApp()->WriteProfileString(strSection, "m_fU2", strTemp);
}

void CCalibrationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_COMBO_RANGE_CURRENT, m_iRangeI);
	DDX_CBIndex(pDX, IDC_COMBO_RANGE_VOLTAGE, m_iRangeU);
	DDX_Text(pDX, IDC_EDIT_B_CURRENT, m_fbI);
	DDX_Text(pDX, IDC_EDIT_B_VOLTAGE, m_fbU);
	DDX_Text(pDX, IDC_EDIT_DA_I1, m_fDAI1);
	DDX_Text(pDX, IDC_EDIT_DA_I2, m_fDAI2);
	DDX_Text(pDX, IDC_EDIT_DA_U1, m_fDAU1);
	DDX_Text(pDX, IDC_EDIT_DA_U2, m_fDAU2);
	DDX_Text(pDX, IDC_EDIT_I1, m_fI1);
	DDX_Text(pDX, IDC_EDIT_I2, m_fI2);
	DDX_Text(pDX, IDC_EDIT_K_CURRENT, m_fkI);
	DDX_Text(pDX, IDC_EDIT_K_VOLTAGE, m_fkU);
	DDX_Text(pDX, IDC_EDIT_STD_I1, m_fStdI1);
	DDX_Text(pDX, IDC_EDIT_STD_I2, m_fStdI2);
	DDX_Text(pDX, IDC_EDIT_STD_U1, m_fStdU1);
	DDX_Text(pDX, IDC_EDIT_STD_U2, m_fStdU2);
	DDX_Text(pDX, IDC_EDIT_VOLTAGE1, m_fU1);
	DDX_Text(pDX, IDC_EDIT_VOLTAGE2, m_fU2);
}


BEGIN_MESSAGE_MAP(CCalibrationDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CAL_VOLTAGE, &CCalibrationDlg::OnBnClickedButtonCalVoltage)
	ON_BN_CLICKED(IDC_BUTTON_OUTPUT_U1, &CCalibrationDlg::OnBnClickedButtonOutputU1)
	ON_BN_CLICKED(IDC_BUTTON_OUTPUT_U2, &CCalibrationDlg::OnBnClickedButtonOutputU2)
	ON_BN_CLICKED(IDC_BUTTON_OUTPUT_I1, &CCalibrationDlg::OnBnClickedButtonOutputI1)
	ON_BN_CLICKED(IDC_BUTTON_OUTPUT_I2, &CCalibrationDlg::OnBnClickedButtonOutputI2)
	ON_BN_CLICKED(IDC_BUTTON_CAL_CURRENT, &CCalibrationDlg::OnBnClickedButtonCalCurrent)
	ON_CBN_SELCHANGE(IDC_COMBO_RANGE_VOLTAGE, &CCalibrationDlg::OnCbnSelchangeComboRangeVoltage)
	ON_CBN_SELCHANGE(IDC_COMBO_RANGE_CURRENT, &CCalibrationDlg::OnCbnSelchangeComboRangeCurrent)
	ON_BN_CLICKED(IDC_BUTTON_UPLOAD, &CCalibrationDlg::OnBnClickedButtonUpload)
	ON_BN_CLICKED(IDOK, &CCalibrationDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CCalibrationDlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDCANCEL, &CCalibrationDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_DOWNLOAD, &CCalibrationDlg::OnBnClickedButtonDownload)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CCalibrationDlg::OnBnClickedButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_WY_RESET1, &CCalibrationDlg::OnBnClickedButtonWyReset1)
	ON_BN_CLICKED(IDC_BUTTON_WY_RESET2, &CCalibrationDlg::OnBnClickedButtonWyReset2)
END_MESSAGE_MAP()


void CCalibrationDlg::ShowUData(int iRangeU)
{
	//if (iRangeU >= 0 && iRangeU < MAX_RANGE)
	//{
	//	m_fkU = g_LED850Comm.m_calData.m_fkU[iRangeU];
	//	m_fbU = g_LED850Comm.m_calData.m_fbU[iRangeU];
	//	
	//	m_fU1 = g_LED850Comm.m_calData.m_fU[iRangeU][0];
	//	m_fU2 = g_LED850Comm.m_calData.m_fU[iRangeU][1];

	//	m_fDAU1 = g_LED850Comm.m_calData.m_fDAU[iRangeU][0];
	//	m_fDAU2 = g_LED850Comm.m_calData.m_fDAU[iRangeU][1];

	//	m_fStdU1 = g_LED850Comm.m_calData.m_fStdU[iRangeU][0];
	//	m_fStdU2 = g_LED850Comm.m_calData.m_fStdU[iRangeU][1];
	//	
	//	UpdateData(FALSE);
	//}
}
void CCalibrationDlg::ShowIData(int iRangeI)
{
	//if (iRangeI >= 0 && iRangeI < MAX_RANGE)
	//{
	//	m_fkI = g_LED850Comm.m_calData.m_fkI[iRangeI];
	//	m_fbI = g_LED850Comm.m_calData.m_fbI[iRangeI];
	//	
	//	m_fI1 = g_LED850Comm.m_calData.m_fI[iRangeI][0];
	//	m_fI2 = g_LED850Comm.m_calData.m_fI[iRangeI][1];

	//	m_fDAI1 = g_LED850Comm.m_calData.m_fDAI[iRangeI][0];
	//	m_fDAI2 = g_LED850Comm.m_calData.m_fDAI[iRangeI][1];

	//	m_fStdI1 = g_LED850Comm.m_calData.m_fStdI[iRangeI][0];
	//	m_fStdI2 = g_LED850Comm.m_calData.m_fStdI[iRangeI][1];

	//	UpdateData(FALSE);
	//}
}

// CCalibrationDlg 消息处理程序


void CCalibrationDlg::OnBnClickedButtonCalVoltage()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	//float fx[2], fy[2], a[2];
	//fx[0] = m_fDAU1;
	//fx[1] = m_fDAU2;

	//fy[0] = m_fStdU1;
	//fy[1] = m_fStdU2;

	//BOOL bR = MyMFC_Lib::Gauss2XF_Calc(fx, fy, 2, 1, a);
	//if (bR)
	//{
	//	m_fbU = a[0];
	//	m_fkU = a[1];

	//	UpdateData(FALSE);

	//	g_LED850Comm.m_calData.m_fU[m_iRangeU][0] = m_fU1;
	//	g_LED850Comm.m_calData.m_fU[m_iRangeU][1] = m_fU2;

	//	g_LED850Comm.m_calData.m_fDAU[m_iRangeU][0] = m_fDAU1;
	//	g_LED850Comm.m_calData.m_fDAU[m_iRangeU][1] = m_fDAU2;

	//	g_LED850Comm.m_calData.m_fStdU[m_iRangeU][0] = m_fStdU1;
	//	g_LED850Comm.m_calData.m_fStdU[m_iRangeU][1] = m_fStdU2;

	//	g_LED850Comm.m_calData.m_fkU[m_iRangeU] = m_fkU;
	//	g_LED850Comm.m_calData.m_fbU[m_iRangeU] = m_fbU;
	//}
	//else
	//{
	//	AfxMessageBox("计算失败！");
	//}
}


void CCalibrationDlg::OnBnClickedButtonOutputU1()
{
	// TODO: 在此添加控件通知处理程序代码
	//UpdateData(TRUE);
	//BeginWaitCursor();
	//BOOL bR;
	//if (g_ExPowerSettings.m_bUse)
	//{
	//	if (!g_ExPowerSettings.m_bManualControl)
	//	{
	//		float fVoltageV, fCurrentmA;
	//		bR = WY_SetPowerOVP(sele_u, m_fU1, m_pDoc->m_dataContainer.GetTestSettingData().m_fTestCurrent / 1000, fVoltageV, fCurrentmA, FALSE);
	//		if (bR != re_ok)
	//		{
	//			Sleep(100);
	//			bR = WY_SetPowerOVP(sele_u, m_fU1, m_pDoc->m_dataContainer.GetTestSettingData().m_fTestCurrent / 1000, fVoltageV, fCurrentmA, FALSE);
	//			if (bR != re_ok)
	//			{
	//				AfxMessageBox("输出失败！");
	//				return;
	//			}
	//		}
	//	}

	//	float fSetRange = 0;
	//	switch(m_iRangeU)
	//	{
	//	case 0:
	//		fSetRange = 4.99f;
	//		break;

	//	case 1:
	//		fSetRange = 19.99f;
	//		break;

	//	case 2:
	//		fSetRange = 49.99f;
	//		break;

	//	case 3:
	//		fSetRange = 199.99f;
	//		break;
	//	}
	//	bR = g_LED850Comm.SetTestParameter(0, fSetRange, 30, 100);
	//	if (!bR)
	//	{
	//		AfxMessageBox("设置参数失败！");
	//		return;
	//	}

	//	CLedData data;
	//	bR = g_LED850Comm.LEDTouchOff(FALSE, 0, 0, data);
	//	if (bR)
	//	{
	//		m_fDAU1 = data.m_fPositiveVoltage;
	//		m_fStdU1 = m_fU1;
	//	}
	//	else
	//	{
	//		m_fDAU1 = 0.0f;
	//	}
	//}

	//EndWaitCursor();
	//UpdateData(FALSE);
	//
	//CString strTemp;
	//strTemp.Format("%.6g", m_fDAU1);
	//GetDlgItem(IDC_EDIT_DA_U1)->SetWindowTextA(strTemp);
}


void CCalibrationDlg::OnBnClickedButtonOutputU2()
{
	// TODO: 在此添加控件通知处理程序代码
	//UpdateData(TRUE);
	//BeginWaitCursor();

	//BOOL bR;
	//if (g_ExPowerSettings.m_bUse)
	//{
	//	if (!g_ExPowerSettings.m_bManualControl)
	//	{
	//		float fVoltageV, fCurrentmA;
	//		bR = WY_SetPowerOVP(sele_u, m_fU2, m_pDoc->m_dataContainer.GetTestSettingData().m_fTestCurrent / 1000, fVoltageV, fCurrentmA, FALSE);
	//		if (bR != re_ok)
	//		{
	//			bR = WY_SetPowerOVP(sele_u, m_fU2, m_pDoc->m_dataContainer.GetTestSettingData().m_fTestCurrent / 1000, fVoltageV, fCurrentmA, FALSE);
	//			if (bR != re_ok)
	//			{
	//				AfxMessageBox("输出失败！");
	//				return;
	//			}
	//		}
	//	}

	//	float fSetRange = 0;
	//	switch(m_iRangeU)
	//	{
	//	case 0:
	//		fSetRange = 4.99f;
	//		break;

	//	case 1:
	//		fSetRange = 19.99f;
	//		break;

	//	case 2:
	//		fSetRange = 49.99f;
	//		break;

	//	case 3:
	//		fSetRange = 199.99f;
	//		break;
	//	}
	//	bR = g_LED850Comm.SetTestParameter(0, fSetRange, 30, 100);
	//	if (!bR)
	//	{
	//		AfxMessageBox("设置参数失败！");
	//		return;
	//	}

	//	CLedData data;
	//	bR = g_LED850Comm.LEDTouchOff(FALSE, 0, 0, data);
	//	if (bR)
	//	{
	//		m_fDAU2 = data.m_fPositiveVoltage;
	//		m_fStdU2 = m_fU2;
	//	}
	//	else
	//	{
	//		m_fDAU2 = 0.0f;
	//	}
	//}

	//EndWaitCursor();
	//UpdateData(FALSE);
	//
	//CString strTemp;
	//strTemp.Format("%.6g", m_fDAU2);
	//GetDlgItem(IDC_EDIT_DA_U2)->SetWindowTextA(strTemp);
}


void CCalibrationDlg::OnBnClickedButtonOutputI1()
{
	// TODO: 在此添加控件通知处理程序代码
	//UpdateData(TRUE);
	//BeginWaitCursor();

	//BOOL bR;
	//if (g_ExPowerSettings.m_bUse)
	//{
	//	if (!g_ExPowerSettings.m_bManualControl)
	//	{
	//		float fVoltageV, fCurrentmA;
	//		bR = WY_SetPowerOVP(sele_i, m_pDoc->m_dataContainer.GetTestSettingData().m_fProtectVoltage, m_fI1 / 1000.0f, fVoltageV, fCurrentmA, FALSE);
	//		if (bR != re_ok)
	//		{
	//			bR = WY_SetPowerOVP(sele_i, m_pDoc->m_dataContainer.GetTestSettingData().m_fProtectVoltage, m_fI1 / 1000.0f, fVoltageV, fCurrentmA, FALSE);
	//			if (bR != re_ok)
	//			{
	//				AfxMessageBox("输出失败！");
	//				return;
	//			}
	//		}
	//	}

	//	float fSetRange = 0;
	//	switch(m_iRangeI)
	//	{
	//	case 0:
	//		fSetRange = 49.99f;
	//		break;

	//	case 1:
	//		fSetRange = 199.99f;
	//		break;

	//	case 2:
	//		fSetRange = 999.99f;
	//		break;

	//	case 3:
	//		fSetRange = 3999.99f;
	//		break;
	//	}
	//	bR = g_LED850Comm.SetTestParameter(fSetRange, 0, 30, 100);
	//	if (!bR)
	//	{
	//		AfxMessageBox("设置参数失败！");
	//		return;
	//	}
	//	CLedData data;
	//	bR = g_LED850Comm.LEDTouchOff(FALSE, 0, 0, data);
	//	if (bR)
	//	{
	//		m_fDAI1 = data.m_fPositiveCurrent;
	//		m_fStdI1 = m_fI1;
	//	}
	//	else
	//	{
	//		m_fDAI1 = 0.0f;
	//	}
	//}

	//EndWaitCursor();
	//UpdateData(FALSE);
	//
	//CString strTemp;
	//strTemp.Format("%.6g", m_fDAI1);
	//GetDlgItem(IDC_EDIT_DA_I1)->SetWindowTextA(strTemp);
}


void CCalibrationDlg::OnBnClickedButtonOutputI2()
{
	// TODO: 在此添加控件通知处理程序代码
	//UpdateData(TRUE);
	//BeginWaitCursor();

	//BOOL bR;
	//if (g_ExPowerSettings.m_bUse)
	//{
	//	if (!g_ExPowerSettings.m_bManualControl)
	//	{
	//		float fVoltageV, fCurrentmA;
	//		bR = WY_SetPowerOVP(sele_i, m_pDoc->m_dataContainer.GetTestSettingData().m_fProtectVoltage, m_fI2 / 1000.0f, fVoltageV, fCurrentmA, FALSE);
	//		if (bR != re_ok)
	//		{
	//			bR = WY_SetPowerOVP(sele_i, m_pDoc->m_dataContainer.GetTestSettingData().m_fProtectVoltage, m_fI2 / 1000.0f, fVoltageV, fCurrentmA, FALSE);
	//			if (bR != re_ok)
	//			{
	//				AfxMessageBox("输出失败！");
	//				return;
	//			}
	//		}
	//	}

	//	float fSetRange = 0;
	//	switch(m_iRangeI)
	//	{
	//	case 0:
	//		fSetRange = 49.99f;
	//		break;

	//	case 1:
	//		fSetRange = 199.99f;
	//		break;

	//	case 2:
	//		fSetRange = 999.99f;
	//		break;

	//	case 3:
	//		fSetRange = 3999.99f;
	//		break;
	//	}
	//	bR = g_LED850Comm.SetTestParameter(fSetRange, 0, 30, 100);
	//	if (!bR)
	//	{
	//		AfxMessageBox("设置参数失败！");
	//		return;
	//	}

	//	CLedData data;
	//	bR = g_LED850Comm.LEDTouchOff(FALSE, 0, 0, data);
	//	if (bR)
	//	{
	//		m_fDAI2 = data.m_fPositiveCurrent;
	//		m_fStdI2 = m_fI2;
	//	}
	//	else
	//	{
	//		m_fDAI2 = 0.0f;
	//	}
	//}

	//EndWaitCursor();
	//UpdateData(FALSE);
	//
	//CString strTemp;
	//strTemp.Format("%.6g", m_fDAI2);
	//GetDlgItem(IDC_EDIT_DA_I2)->SetWindowTextA(strTemp);
}


void CCalibrationDlg::OnBnClickedButtonCalCurrent()
{
	// TODO: 在此添加控件通知处理程序代码
//	UpdateData(TRUE);
//	BeginWaitCursor();
//
//	float fx[2], fy[2], a[2];
//	fx[0] = m_fDAI1;
//	fx[1] = m_fDAI2;
//
//	fy[0] = m_fStdI1;
//	fy[1] = m_fStdI2;
//
//	BOOL bR = MyMFC_Lib::Gauss2XF_Calc(fx, fy, 2, 1, a);
//	if (bR)
//	{
//		m_fbI = a[0];
//		m_fkI = a[1];
//
//		UpdateData(FALSE);
//		
//		g_LED850Comm.m_calData.m_fI[m_iRangeI][0] = m_fI1;
//		g_LED850Comm.m_calData.m_fI[m_iRangeI][1] = m_fI2;
//
//		g_LED850Comm.m_calData.m_fDAI[m_iRangeI][0] = m_fDAI1;
//		g_LED850Comm.m_calData.m_fDAI[m_iRangeI][1] = m_fDAI2;
//
//		g_LED850Comm.m_calData.m_fStdI[m_iRangeI][0] = m_fStdI1;
//		g_LED850Comm.m_calData.m_fStdI[m_iRangeI][1] = m_fStdI2;
//
//		g_LED850Comm.m_calData.m_fkI[m_iRangeI] = m_fkI;
//		g_LED850Comm.m_calData.m_fbI[m_iRangeI] = m_fbI;
//	}
//	else
//	{
//		AfxMessageBox("计算失败！");
//	}
//
//	EndWaitCursor();
}


BOOL CCalibrationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
//	ShowIData(m_iRangeI);
//	ShowUData(m_iRangeU);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CCalibrationDlg::OnCbnSelchangeComboRangeVoltage()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!UpdateData(TRUE))
	{
		return;
	}

	ShowUData(m_iRangeU);
}


void CCalibrationDlg::OnCbnSelchangeComboRangeCurrent()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!UpdateData(TRUE))
	{
		return;
	}

	ShowIData(m_iRangeI);
}


void CCalibrationDlg::OnBnClickedButtonUpload()
{
	// TODO: 在此添加控件通知处理程序代码
	//BOOL bR = g_LED850Comm.UploadCalData(g_LED850Comm.m_calData);
	//if (bR)
	//{
	//	ShowIData(m_iRangeI);
	//	ShowUData(m_iRangeU);
	//	AfxMessageBox("读取成功!");
	//}
	//else
	//{
	//	AfxMessageBox("读取失败！");
	//}
}


void CCalibrationDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//if (!g_LED850Comm.m_calData.SaveFile(m_strCalPath + "cal.dat"))
	//{
	//	AfxMessageBox("保存失败！");
	//	return;
	//}

	CDialogEx::OnOK();
}


void CCalibrationDlg::OnBnClickedButtonOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	//CFileDialog dlg(TRUE, NULL, NULL, 6UL, "Calibration Data(*.dat)|*.dat|");
	//dlg.m_ofn.lpstrInitialDir = m_strCalPath;
	//if (IDOK == dlg.DoModal())
	//{
	//	if (!g_LED850Comm.m_calData.OpenFile(dlg.GetPathName()))
	//	{
	//		AfxMessageBox("打开失败！");
	//	}

	//	ShowIData(m_iRangeI);
	//	ShowUData(m_iRangeU);
	//}
}


void CCalibrationDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CCalibrationDlg::OnBnClickedButtonDownload()
{
	// TODO: 在此添加控件通知处理程序代码
	//BOOL bR = g_LED850Comm.DownloadCalData(g_LED850Comm.m_calData);
	//if (bR)
	//{
	//	AfxMessageBox("下载成功！");
	//}
	//else
	//{
	//	AfxMessageBox("下载失败！");
	//}
}


void CCalibrationDlg::OnBnClickedButtonReset()
{
	// TODO: 在此添加控件通知处理程序代码
	//if (IDCANCEL == AfxMessageBox("确定要复位下位机定标数据？", MB_OKCANCEL))
	//{
	//	return;
	//}

	//CCalibrationData data;
	//if (g_LED850Comm.DownloadCalData(data))
	//{
	//	AfxMessageBox("复位成功！");
	//}
	//else
	//{
	//	AfxMessageBox("复位失败！");
	//}
}


void CCalibrationDlg::OnBnClickedButtonWyReset1()
{
	// TODO: 在此添加控件通知处理程序代码
	BeginWaitCursor();
//	WY_Reset(TRUE);
	EndWaitCursor();
}


void CCalibrationDlg::OnBnClickedButtonWyReset2()
{
	// TODO: 在此添加控件通知处理程序代码
	BeginWaitCursor();
//	WY_Reset(TRUE);
	EndWaitCursor();
}
