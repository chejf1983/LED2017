// DebugDJ4000Page.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "DebugDJ4000Page.h"
#include "afxdialogex.h"
#include "DJ4000Comm.h"

// CDebugDJ4000Page 对话框

IMPLEMENT_DYNAMIC(CDebugDJ4000Page, CPropertyPage)

CDebugDJ4000Page::CDebugDJ4000Page()
	: CPropertyPage(CDebugDJ4000Page::IDD)
{
	m_strBaudrate = _T("2400");
	
	m_iOFFSeconds = 5;
	m_iONSeconds = 5;
	m_iTimes = 99;

	CString strSection = "Debug_DJ4000";
	m_strCOM = AfxGetApp()->GetProfileStringA(strSection, "m_strCOM", "COM1");
	m_iOFFSeconds = AfxGetApp()->GetProfileIntA(strSection, "m_iOFFSeconds", 5);
	m_iONSeconds = AfxGetApp()->GetProfileIntA(strSection, "m_iONSeconds", 5);
	m_iTimes = AfxGetApp()->GetProfileIntA(strSection, "m_iTimes", 99);
}

CDebugDJ4000Page::~CDebugDJ4000Page()
{
	CString strSection = "Debug_DJ4000";
	AfxGetApp()->WriteProfileString(strSection, "m_strCOM", m_strCOM);
	AfxGetApp()->WriteProfileInt(strSection, "m_iOFFSeconds", m_iOFFSeconds);
	AfxGetApp()->WriteProfileInt(strSection, "m_iONSeconds", m_iONSeconds);
	AfxGetApp()->WriteProfileInt(strSection, "m_iTimes", m_iTimes);
}

void CDebugDJ4000Page::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO_BAUDRATE, m_strBaudrate);
	DDX_CBString(pDX, IDC_COMBO_COM, m_strCOM);
	DDX_Text(pDX, IDC_EDIT_OFF_SECONDS, m_iOFFSeconds);
	DDX_Text(pDX, IDC_EDIT_ON_SECONDS, m_iONSeconds);
	DDX_Text(pDX, IDC_EDIT_TIMES, m_iTimes);
	DDV_MinMaxInt(pDX, m_iTimes, 0, 999999);
}


BEGIN_MESSAGE_MAP(CDebugDJ4000Page, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_SET, &CDebugDJ4000Page::OnBnClickedButtonSet)
	ON_BN_CLICKED(IDC_BUTTON_RUN, &CDebugDJ4000Page::OnBnClickedButtonRun)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CDebugDJ4000Page::OnBnClickedButtonStop)
END_MESSAGE_MAP()


// CDebugDJ4000Page 消息处理程序


void CDebugDJ4000Page::OnBnClickedButtonSet()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!UpdateData(TRUE))
	{
		return;
	}

	BeginWaitCursor();
	g_DJ4000Comm.Initialize(m_strCOM, atoi(m_strBaudrate));

	BOOL bR1 = g_DJ4000Comm.SetParameter(m_iONSeconds, m_iOFFSeconds);
	BOOL bR2 = g_DJ4000Comm.SetRunTimes(0);
	EndWaitCursor();

	if (bR1 && bR2)
	{
		AfxMessageBox("设置成功！");
	}
	else
	{
		AfxMessageBox("设置失败！");
	}
}


void CDebugDJ4000Page::OnBnClickedButtonRun()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	BeginWaitCursor();
	g_DJ4000Comm.Initialize(m_strCOM, atoi(m_strBaudrate));
	BOOL bR = g_DJ4000Comm.Start();
	EndWaitCursor();
	if (bR)
	{
		AfxMessageBox("启动成功！");
	}
	else
	{
		AfxMessageBox("启动成功！");
	}
}


void CDebugDJ4000Page::OnBnClickedButtonStop()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	BeginWaitCursor();
	g_DJ4000Comm.Initialize(m_strCOM, atoi(m_strBaudrate));
	BOOL bR = g_DJ4000Comm.Stop();
	EndWaitCursor();
	if (bR)
	{
		AfxMessageBox("停止成功！");
	}
	else
	{
		AfxMessageBox("停止成功！");
	}
}
