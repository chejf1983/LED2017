// DebugEMS61000_11KPage.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "DebugEMS61000_11KPage.h"
#include "afxdialogex.h"
#include "LAT2000Doc.h"


extern CString g_strCurrentPath;
// CDebugEMS61000_11KPage 对话框

IMPLEMENT_DYNAMIC(CDebugEMS61000_11KPage, CPropertyPage)

CDebugEMS61000_11KPage::CDebugEMS61000_11KPage()
	: CPropertyPage(CDebugEMS61000_11KPage::IDD)
{
	m_iCurSele = 0;
	m_strRe = _T("");
	m_iResult = 0;
	m_iTime = 0;
	m_strCOM = _T("");
	
	CString strSection = "CDebugEMS61000_11KPage";
	m_strCOM = AfxGetApp()->GetProfileString(strSection, "m_strCOM", "COM1");
}

CDebugEMS61000_11KPage::~CDebugEMS61000_11KPage()
{
	CString strSection = "CDebugEMS61000_11KPage";
	AfxGetApp()->WriteProfileStringA(strSection, "m_strCOM", m_strCOM);
}

void CDebugEMS61000_11KPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_RE, m_strRe);
	DDX_Text(pDX, IDC_EDIT_RESULT, m_iResult);
	DDX_Text(pDX, IDC_EDIT_TIME, m_iTime);
	DDX_CBString(pDX, IDC_COMBO_COM, m_strCOM);
}


BEGIN_MESSAGE_MAP(CDebugEMS61000_11KPage, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_SET, &CDebugEMS61000_11KPage::OnBnClickedButtonSet)
	ON_BN_CLICKED(IDC_BUTTON_START, &CDebugEMS61000_11KPage::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CDebugEMS61000_11KPage::OnBnClickedButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_READ, &CDebugEMS61000_11KPage::OnBnClickedButtonRead)
	ON_BN_CLICKED(IDC_BUTTON_EUT_ON, &CDebugEMS61000_11KPage::OnBnClickedButtonEutOn)
	ON_BN_CLICKED(IDC_BUTTON_EUT_OFF, &CDebugEMS61000_11KPage::OnBnClickedButtonEutOff)
END_MESSAGE_MAP()


// CDebugEMS61000_11KPage 消息处理程序


void CDebugEMS61000_11KPage::OnBnClickedButtonSet()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	BeginWaitCursor();
	g_EMS61000_11KComm.Initialize(g_strCurrentPath + "Communication Settings\\", m_strCOM);

	g_EMS61000_11KComm.ShowSettingsDialog(m_iCurSele, FALSE);
	EndWaitCursor();
}


void CDebugEMS61000_11KPage::OnBnClickedButtonStart()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	BeginWaitCursor();
	g_EMS61000_11KComm.Initialize(g_strCurrentPath + "Communication Settings\\", m_strCOM);
	BOOL bR = g_EMS61000_11KComm.Start(m_iCurSele);
	EndWaitCursor();
	if (bR)
	{
		AfxMessageBox("启动成功！");
	}
	else
	{
		AfxMessageBox("启动失败！");
	}
}


void CDebugEMS61000_11KPage::OnBnClickedButtonReset()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	BeginWaitCursor();
	g_EMS61000_11KComm.Initialize(g_strCurrentPath + "Communication Settings\\", m_strCOM);
	BOOL bR = g_EMS61000_11KComm.Reset();
	EndWaitCursor();
	if (bR)
	{
		AfxMessageBox("复位成功！");
	}
	else
	{
		AfxMessageBox("复位失败！");
	}
}


void CDebugEMS61000_11KPage::OnBnClickedButtonRead()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	EMC11KREData data;
	BeginWaitCursor();
	g_EMS61000_11KComm.Initialize(g_strCurrentPath + "Communication Settings\\", m_strCOM);
	BOOL bR = g_EMS61000_11KComm.Read(data);
	EndWaitCursor();
	if (1 != bR)
	{
		m_strRe = data.strRe;
		m_iResult = data.m_iResult;
		m_iTime = data.m_iTime;
		UpdateData(FALSE);

		AfxMessageBox("读取成功！");
	}
	else
	{
		AfxMessageBox("读取失败！");
	}
}


void CDebugEMS61000_11KPage::OnBnClickedButtonEutOn()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	BeginWaitCursor();
	g_EMS61000_11KComm.Initialize(g_strCurrentPath + "Communication Settings\\", m_strCOM);
	BOOL bR = g_EMS61000_11KComm.SetEUT(TRUE);
	EndWaitCursor();

	if (bR)
	{
		AfxMessageBox("打开成功！");
	}
	else
	{
		AfxMessageBox("打开失败！");
	}
}


void CDebugEMS61000_11KPage::OnBnClickedButtonEutOff()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	BeginWaitCursor();
	g_EMS61000_11KComm.Initialize(g_strCurrentPath + "Communication Settings\\", m_strCOM);
	BOOL bR = g_EMS61000_11KComm.SetEUT(FALSE);
	EndWaitCursor();

	if (bR)
	{
		AfxMessageBox("关闭成功！");
	}
	else
	{
		AfxMessageBox("关闭失败！");
	}
}


BOOL CDebugEMS61000_11KPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_strCOM = g_pDoc->m_CommSettingsData.m_strCOMEMS61000_11K;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
