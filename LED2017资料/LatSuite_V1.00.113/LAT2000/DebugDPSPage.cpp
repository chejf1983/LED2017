// DebugDPSPage.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "DebugDPSPage.h"
#include "afxdialogex.h"
#include "LAT2000Doc.h"

// CDebugDPSPage 对话框

IMPLEMENT_DYNAMIC(CDebugDPSPage, CPropertyPage)

CDebugDPSPage::CDebugDPSPage()
	: CPropertyPage(CDebugDPSPage::IDD)
{
	m_fCurrentRead = 0.0f;
	m_fVoltageRead = 0.0f;
	m_fVoltageSet = 220.0f;
	m_fFrequencySet = 50.0f;
	m_fFrequencyRead = 0.0f;

	CString strSection = "Debug_DPS";
	m_strCOM = AfxGetApp()->GetProfileStringA(strSection, "m_strCOM", "COM1");
	m_iRangeU = AfxGetApp()->GetProfileIntA(strSection, "m_iRangeU", 0);
}

CDebugDPSPage::~CDebugDPSPage()
{
	CString strSection = "Debug_DPS";
	AfxGetApp()->WriteProfileString(strSection, "m_strCOM", m_strCOM);
	AfxGetApp()->WriteProfileInt(strSection, "m_iRangeU", m_iRangeU);
}

void CDebugDPSPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO_COM, m_strCOM);
	DDX_CBIndex(pDX, IDC_COMBO_RANGE, m_iRangeU);
	DDX_Text(pDX, IDC_EDIT_CURRENT, m_fCurrentRead);
	DDX_Text(pDX, IDC_EDIT_VOLTAGE_READ, m_fVoltageRead);
	DDX_Text(pDX, IDC_EDIT_VOLTAGE_SET, m_fVoltageSet);
	DDX_Text(pDX, IDC_EDIT_FREQUENCY_SET, m_fFrequencySet);
	DDX_Text(pDX, IDC_EDIT_FREQUENCY_READ, m_fFrequencyRead);
}


BEGIN_MESSAGE_MAP(CDebugDPSPage, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_READ, &CDebugDPSPage::OnBnClickedButtonRead)
	ON_BN_CLICKED(IDC_BUTTON_OUTPUT, &CDebugDPSPage::OnBnClickedButtonOutput)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CDebugDPSPage::OnBnClickedButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_SET, &CDebugDPSPage::OnBnClickedButtonSet)
	ON_BN_CLICKED(IDC_BUTTON_SET2, &CDebugDPSPage::OnBnClickedButtonSet2)
END_MESSAGE_MAP()


// CDebugDPSPage 消息处理程序


void CDebugDPSPage::OnBnClickedButtonRead()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	BeginWaitCursor();
	int iCOM = 1;
	sscanf_s(m_strCOM.GetBuffer(), "COM%d", &iCOM);
	g_DPSComm.InitializeComm(iCOM);

	RealTimeData data;
	BOOL bR = g_DPSComm.GetRealTimeData(data);
	EndWaitCursor();
	if (bR)
	{
		m_fCurrentRead = data.fCurrentValue;
		m_fVoltageRead = data.fVoltageValue;
		m_fFrequencyRead = data.fFrequence;

		UpdateData(FALSE);
	}
	else
	{
		AfxMessageBox("读取失败！");
	}
}


void CDebugDPSPage::OnBnClickedButtonOutput()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	BeginWaitCursor();
	int iCOM = 1;
	sscanf_s(m_strCOM.GetBuffer(), "COM%d", &iCOM);
	g_DPSComm.InitializeComm(iCOM);
	BOOL bR = g_DPSComm.FastRun(m_fVoltageSet, m_fFrequencySet);
	EndWaitCursor();
	if (!bR)
	{
		AfxMessageBox("输出失败！");
	}
}


void CDebugDPSPage::OnBnClickedButtonReset()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	BeginWaitCursor();
	int iCOM = 1;
	sscanf_s(m_strCOM.GetBuffer(), "COM%d", &iCOM);
	g_DPSComm.InitializeComm(iCOM);
	BOOL bR = g_DPSComm.StopOutput();
	if (bR)
	{
		AfxMessageBox("复位成功！");
	}
	else
	{
		AfxMessageBox("复位失败！");
	}
	EndWaitCursor();
}


void CDebugDPSPage::OnBnClickedButtonSet()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	int iCOM = 1;
	sscanf_s(m_strCOM.GetBuffer(), "COM%d", &iCOM);
	g_DPSComm.InitializeComm(iCOM);
	
	BOOL bR = FALSE;
	Parameter data;
	data.fVoltage = m_fVoltageSet;
	data.fFrequence = m_fFrequencySet;
	data.fAlarmCurrent = g_DPSComm.GetLimitData().LimitCurrentRange2.fUpper;
	data.fAlarmPower = g_DPSComm.GetLimitData().LimitPower.fUpper;
	data.iRangeU = m_iRangeU;
	bR = g_DPSComm.SetParameter(data);
	if (bR)
	{
		AfxMessageBox("设置参数成功！");
	}
	else
	{
		AfxMessageBox("设置参数失败！");
	}
}


void CDebugDPSPage::OnBnClickedButtonSet2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	int iCOM = 1;
	sscanf_s(m_strCOM.GetBuffer(), "COM%d", &iCOM);
	g_DPSComm.InitializeComm(iCOM);
	BOOL bR = FALSE;
	bR = g_DPSComm.SetParameterRunning(m_fVoltageSet, m_fFrequencySet, 
			g_DPSComm.GetLimitData().LimitCurrentRange2.fUpper, g_DPSComm.GetLimitData().LimitPower.fUpper);
	if (bR)
	{
		AfxMessageBox("输出状态设置参数成功！");
	}
	else
	{
		AfxMessageBox("输出状态设置参数失败！");
	}
}


BOOL CDebugDPSPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_strCOM = g_pDoc->m_CommSettingsData.m_strCOMDPS;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
