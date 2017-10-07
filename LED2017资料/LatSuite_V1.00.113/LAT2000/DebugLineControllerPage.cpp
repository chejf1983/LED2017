// DebugLineControllerPage.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "DebugLineControllerPage.h"
#include "afxdialogex.h"
#include "LAT2000Doc.h"

// CDebugLineControllerPage 对话框

IMPLEMENT_DYNAMIC(CDebugLineControllerPage, CPropertyPage)

CDebugLineControllerPage::CDebugLineControllerPage()
	: CPropertyPage(CDebugLineControllerPage::IDD)
{
	m_strAddress = _T("");
	m_strBaudrate = _T("2400");
	m_fOffTimeSec = 1.0f;
	m_fOnTimeSec = 2.0f;
	
	CString strSection = "CDebugLineControllerPage";
	m_strCOM = AfxGetApp()->GetProfileStringA(strSection, "m_strCOM", "COM1");
}

CDebugLineControllerPage::~CDebugLineControllerPage()
{
	CString strSection = "CDebugLineControllerPage";
	AfxGetApp()->WriteProfileStringA(strSection, "m_strCOM", m_strCOM);
}

void CDebugLineControllerPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO_COM, m_strCOM);
	DDX_Text(pDX, IDC_EDIT_ADDRESS, m_strAddress);
	DDX_CBString(pDX, IDC_COMBO_BAUDRATE, m_strBaudrate);
	DDX_Text(pDX, IDC_EDIT_OLD_OFF_TIME, m_fOffTimeSec);
	DDX_Text(pDX, IDC_EDIT_OLD_ON_TIME, m_fOnTimeSec);
}


BEGIN_MESSAGE_MAP(CDebugLineControllerPage, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_MOVE, &CDebugLineControllerPage::OnBnClickedButtonMove)
	ON_BN_CLICKED(IDC_BUTTON_CONTINUE, &CDebugLineControllerPage::OnBnClickedButtonContinue)
	ON_BN_CLICKED(IDC_BUTTON_LINESTOP, &CDebugLineControllerPage::OnBnClickedButtonLinestop)
	ON_BN_CLICKED(IDC_BUTTON_GET_LINE_STATE, &CDebugLineControllerPage::OnBnClickedButtonGetLineState)
	ON_BN_CLICKED(IDC_BUTTON_OLD_TIME, &CDebugLineControllerPage::OnBnClickedButtonOldTime)
	ON_BN_CLICKED(IDC_BUTTON_BUZZER_ON, &CDebugLineControllerPage::OnBnClickedButtonBuzzerOn)
	ON_BN_CLICKED(IDC_BUTTON_BUZZER_OFF, &CDebugLineControllerPage::OnBnClickedButtonBuzzerOff)
END_MESSAGE_MAP()


// CDebugLineControllerPage 消息处理程序


void CDebugLineControllerPage::OnBnClickedButtonMove()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!UpdateData(TRUE))
	{
		return;
	}

	BeginWaitCursor();
	g_LineControllerComm.Initialize(m_strCOM);
	BOOL bR = g_LineControllerComm.MoveLineOneStep();
	EndWaitCursor();
	if (!bR)
	{
		AfxMessageBox("控制失败！");
	}
}


void CDebugLineControllerPage::OnBnClickedButtonContinue()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!UpdateData(TRUE))
	{
		return;
	}

	BeginWaitCursor();
	g_LineControllerComm.Initialize(m_strCOM);
	BOOL bR = g_LineControllerComm.MoveLineContinuous();
	EndWaitCursor();
	if (!bR)
	{
		AfxMessageBox("控制失败！");
	}
}


void CDebugLineControllerPage::OnBnClickedButtonLinestop()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!UpdateData(TRUE))
	{
		return;
	}

	BeginWaitCursor();
	g_LineControllerComm.Initialize(m_strCOM);
	BOOL bR = g_LineControllerComm.SetLinePause();
	EndWaitCursor();
	if (!bR)
	{
		AfxMessageBox("控制失败！");
	}
}


void CDebugLineControllerPage::OnBnClickedButtonGetLineState()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!UpdateData(TRUE))
	{
		return;
	}
	BOOL bInposition, bManualStopped, bLampTooHigh;
	BeginWaitCursor();
	g_LineControllerComm.Initialize(m_strCOM);
	BOOL bR = g_LineControllerComm.ReadLineState(bInposition,  bManualStopped,  bLampTooHigh);
	EndWaitCursor();
	CString strTemp;
	if (!bR)
	{
		strTemp = "Error!";
		AfxMessageBox("控制失败！");
	}
	else
	{
		strTemp.Format("Inposition:%d, ManualStopped:%d, LampTooHigh:%d",
			bInposition, bManualStopped, bLampTooHigh);
	}
	GetDlgItem(IDC_EDIT_LINESTATE)->SetWindowText(strTemp);
}


void CDebugLineControllerPage::OnBnClickedButtonOldTime()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!UpdateData(TRUE))
	{
		return;
	}

	BeginWaitCursor();
	g_LineControllerComm.Initialize(m_strCOM);
	BOOL bR = g_LineControllerComm.SetOldTime(m_fOnTimeSec, m_fOffTimeSec);
	EndWaitCursor();
	if (!bR)
	{
		AfxMessageBox("控制失败！");
	}
}


BOOL CDebugLineControllerPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_strCOM = g_pDoc->m_CommSettingsData.m_strLineControllerCOM;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDebugLineControllerPage::OnBnClickedButtonBuzzerOn()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!UpdateData(TRUE))
	{
		return;
	}

	BeginWaitCursor();
	g_LineControllerComm.Initialize(m_strCOM);
	BOOL bR = g_LineControllerComm.SetBuzzer(TRUE);
	EndWaitCursor();
	if (!bR)
	{
		AfxMessageBox("控制失败！");
	}
}


void CDebugLineControllerPage::OnBnClickedButtonBuzzerOff()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!UpdateData(TRUE))
	{
		return;
	}

	BeginWaitCursor();
	g_LineControllerComm.Initialize(m_strCOM);
	BOOL bR = g_LineControllerComm.SetBuzzer(FALSE);
	EndWaitCursor();
	if (!bR)
	{
		AfxMessageBox("控制失败！");
	}
}
