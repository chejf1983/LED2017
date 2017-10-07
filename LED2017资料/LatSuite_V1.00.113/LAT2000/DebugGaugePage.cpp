// DebugGaugePage.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "DebugGaugePage.h"
#include "afxdialogex.h"
#include "LAT2000Doc.h"

// CDebugGaugePage 对话框

IMPLEMENT_DYNAMIC(CDebugGaugePage, CPropertyPage)

CDebugGaugePage::CDebugGaugePage()
	: CPropertyPage(CDebugGaugePage::IDD)
{

	m_strBaudrate = _T("9600");
	m_strCOM = _T("COM1");
	m_ucAddress = 1;
	m_fCurrentA = 0.0f;
	m_fPowerW = 0.0f;
	m_fVoltageV = 0.0f;
}

CDebugGaugePage::~CDebugGaugePage()
{
}

void CDebugGaugePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO_BAUDRATE, m_strBaudrate);
	DDX_CBString(pDX, IDC_COMBO_COM, m_strCOM);
	DDX_Text(pDX, IDC_EDIT_ADDRESS, m_ucAddress);
	DDX_Text(pDX, IDC_EDIT_CURRENT, m_fCurrentA);
	DDX_Text(pDX, IDC_EDIT_POWER, m_fPowerW);
	DDX_Text(pDX, IDC_EDIT_VOLTAGE, m_fVoltageV);
}


BEGIN_MESSAGE_MAP(CDebugGaugePage, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_READ, &CDebugGaugePage::OnBnClickedButtonRead)
END_MESSAGE_MAP()


// CDebugGaugePage 消息处理程序


void CDebugGaugePage::OnBnClickedButtonRead()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!UpdateData(TRUE))
	{
		return;
	}

	BeginWaitCursor();
	g_GaugeComm.Initialize(m_strCOM, atoi(m_strBaudrate));
	BOOL bR = g_GaugeComm.Read(m_ucAddress, m_fVoltageV, m_fCurrentA, m_fPowerW);
	EndWaitCursor();
	if (bR)
	{
		AfxMessageBox("读取成功！");
	}
	else
	{
		AfxMessageBox("读取失败！");
	}
	
	UpdateData(FALSE);
}


BOOL CDebugGaugePage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_strCOM = g_pDoc->m_CommSettingsData.m_strCOMGauge;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
