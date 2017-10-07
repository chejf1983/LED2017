// DebugSC1600Page.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "DebugSC1600Page.h"
#include "afxdialogex.h"
#include "LAT2000Doc.h"

// CDebugSC1600Page 对话框

IMPLEMENT_DYNAMIC(CDebugSC1600Page, CPropertyPage)

CDebugSC1600Page::CDebugSC1600Page()
	: CPropertyPage(CDebugSC1600Page::IDD)
{

	m_strBaudrate = _T("9600");

	CString strSection = "Debug_SC1600";
	m_strCOM = AfxGetApp()->GetProfileString(strSection, "m_strCOM", "COM1");
	m_ucAddress = (BYTE)AfxGetApp()->GetProfileIntA(strSection, "m_ucAddress", 1);
}

CDebugSC1600Page::~CDebugSC1600Page()
{
	CString strSection = "Debug_SC1600";
	AfxGetApp()->WriteProfileString(strSection, "m_strCOM", m_strCOM);
	AfxGetApp()->WriteProfileInt(strSection, "m_ucAddress", 1);
}

void CDebugSC1600Page::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_C1, m_bC1);
	DDX_Check(pDX, IDC_CHECK_C10, m_bC10);
	DDX_Check(pDX, IDC_CHECK_C11, m_bC11);
	DDX_Check(pDX, IDC_CHECK_C12, m_bC12);
	DDX_Check(pDX, IDC_CHECK_C13, m_bC13);
	DDX_Check(pDX, IDC_CHECK_C14, m_bC14);
	DDX_Check(pDX, IDC_CHECK_C15, m_bC15);
	DDX_Check(pDX, IDC_CHECK_C16, m_bC16);
	DDX_Check(pDX, IDC_CHECK_C2, m_bC2);
	DDX_Check(pDX, IDC_CHECK_C3, m_bC3);
	DDX_Check(pDX, IDC_CHECK_C4, m_bC4);
	DDX_Check(pDX, IDC_CHECK_C5, m_bC5);
	DDX_Check(pDX, IDC_CHECK_C6, m_bC6);
	DDX_Check(pDX, IDC_CHECK_C7, m_bC7);
	DDX_Check(pDX, IDC_CHECK_C8, m_bC8);
	DDX_Check(pDX, IDC_CHECK_C9, m_bC9);
	DDX_CBString(pDX, IDC_COMBO_BAUDRATE, m_strBaudrate);
	DDX_CBString(pDX, IDC_COMBO_COM, m_strCOM);
	DDX_Text(pDX, IDC_EDIT_ADDRESS, m_ucAddress);
}


BEGIN_MESSAGE_MAP(CDebugSC1600Page, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_SET, &CDebugSC1600Page::OnBnClickedButtonSet)
	ON_BN_CLICKED(IDC_BUTTON_QUIT_REMOTE, &CDebugSC1600Page::OnBnClickedButtonQuitRemote)
	ON_BN_CLICKED(IDC_BUTTON_READ, &CDebugSC1600Page::OnBnClickedButtonRead)
	ON_BN_CLICKED(IDC_BUTTON_BUZZER_ON, &CDebugSC1600Page::OnBnClickedButtonBuzzerOn)
	ON_BN_CLICKED(IDC_BUTTON_BUZZER_OFF, &CDebugSC1600Page::OnBnClickedButtonBuzzerOff)
	ON_BN_CLICKED(IDC_BUTTON_START, &CDebugSC1600Page::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_ALL, &CDebugSC1600Page::OnBnClickedButtonCloseAll)
END_MESSAGE_MAP()


// CDebugSC1600Page 消息处理程序


void CDebugSC1600Page::OnBnClickedButtonSet()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!UpdateData(TRUE))
	{
		return;
	}

	BeginWaitCursor();
	g_SC1000Comm.Initialize(m_strCOM, m_ucAddress, FALSE);

	BOOL bOn[16];
	bOn[0] = m_bC1;
	bOn[1] = m_bC2;
	bOn[2] = m_bC3;
	bOn[3] = m_bC4;
	bOn[4] = m_bC5;

	bOn[5] = m_bC6;
	bOn[6] = m_bC7;
	bOn[7] = m_bC8;
	bOn[8] = m_bC9;
	bOn[9] = m_bC10;

	bOn[10] = m_bC11;
	bOn[11] = m_bC12;
	bOn[12] = m_bC13;
	bOn[13] = m_bC14;
	bOn[14] = m_bC15;

	bOn[15] = m_bC16;

	if (g_SC1000Comm.SetOnOff(bOn))
	{
		AfxMessageBox("设置成功！");
	}
	else
	{
		AfxMessageBox("设置失败！");
	}

	EndWaitCursor();
}


void CDebugSC1600Page::OnBnClickedButtonQuitRemote()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!UpdateData(TRUE))
	{
		return;
	}

	BeginWaitCursor();
	g_SC1000Comm.Initialize(m_strCOM, m_ucAddress, FALSE);
	if (g_SC1000Comm.ExitRemoteMode())
	{
		AfxMessageBox("已退出远程！");
	}
	EndWaitCursor();
}


void CDebugSC1600Page::OnBnClickedButtonRead()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!UpdateData(TRUE))
	{
		return;
	}

	BeginWaitCursor();
	g_SC1000Comm.Initialize(m_strCOM, m_ucAddress, FALSE);
	BOOL bLampTooHigh = FALSE;
	BOOL bR = g_SC1000Comm.SwitchAllLamp(FALSE);
	//BOOL bFlag[16];
	//bR = g_SC1000Comm.GetLineState(bFlag);
	EndWaitCursor();
	if (!bR)
	{
		AfxMessageBox("读取失败！");
	}
	else
	{
		CString strTemp;
		strTemp.Format("灯过高：%d", 
			bLampTooHigh);
		AfxMessageBox(strTemp);
	}
}


void CDebugSC1600Page::OnBnClickedButtonBuzzerOn()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!UpdateData(TRUE))
	{
		return;
	}

	BeginWaitCursor();
	g_SC1000Comm.Initialize(m_strCOM, m_ucAddress, FALSE);
	BOOL bR = g_SC1000Comm.SetBuzzer(TRUE);
	if (!bR)
	{
		AfxMessageBox("控制失败！");
	}
}


void CDebugSC1600Page::OnBnClickedButtonBuzzerOff()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!UpdateData(TRUE))
	{
		return;
	}

	BeginWaitCursor();
	g_SC1000Comm.Initialize(m_strCOM, m_ucAddress, FALSE);
	BOOL bR = g_SC1000Comm.SetBuzzer(FALSE);
	if (!bR)
	{
		AfxMessageBox("控制失败！");
	}
}


void CDebugSC1600Page::OnBnClickedButtonStart()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!UpdateData(TRUE))
	{
		return;
	}

	BeginWaitCursor();
	g_SC1000Comm.Initialize(m_strCOM, m_ucAddress, FALSE);
	BOOL bLampTooHigh = FALSE;
	BOOL bR = g_SC1000Comm.SwitchAllLamp(FALSE);
	if (!bR)
	{
		AfxMessageBox("控制失败！");
	}
	EndWaitCursor();
}


void CDebugSC1600Page::OnBnClickedButtonTmpStart()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!UpdateData(TRUE))
	{
		return;
	}

	BeginWaitCursor();
	BOOL bR = g_FujiTMPComm.RunTwo();
	if (!bR)
	{
		AfxMessageBox("控制失败！");
	}
	EndWaitCursor();
}


void CDebugSC1600Page::OnBnClickedButtonTmpStop()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!UpdateData(TRUE))
	{
		return;
	}

	BeginWaitCursor();
	BOOL bR1 = g_FujiTMPComm.SetTemperature(g_FujiTMPComm.m_ucAddress[0], 0, 0, 0);
	BOOL bR2 = g_FujiTMPComm.SetTemperature(g_FujiTMPComm.m_ucAddress[0], 0, 0 ,0);
	if (bR1 && bR2)
	{
		AfxMessageBox("控制成功！");
	}
	else
	{
		AfxMessageBox("控制失败！");
	}
	EndWaitCursor();
}


void CDebugSC1600Page::OnBnClickedButtonCloseAll()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!UpdateData(TRUE))
	{
		return;
	}

	BeginWaitCursor();
	g_SC1000Comm.Initialize(m_strCOM, m_ucAddress, FALSE);
	BOOL bR = g_SC1000Comm.SwitchAllLamp(FALSE);
	if (!bR)
	{
		AfxMessageBox("控制失败！");
	}
	EndWaitCursor();
}


BOOL CDebugSC1600Page::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_strCOM = g_pDoc->m_CommSettingsData.m_strCOMTestChannelController;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
