// DebugLRAPage.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "DebugLRAPage.h"
#include "afxdialogex.h"
#include "LAT2000Doc.h"

// CDebugLRAPage 对话框

IMPLEMENT_DYNAMIC(CDebugLRAPage, CPropertyPage)

CDebugLRAPage::CDebugLRAPage()
	: CPropertyPage(CDebugLRAPage::IDD)
{

	m_strCOM = _T("COM1");
	m_strAddress = _T("AF");
	m_iBaudRate = 0;
}

CDebugLRAPage::~CDebugLRAPage()
{
}

void CDebugLRAPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO_COM, m_strCOM);
	DDX_Text(pDX, IDC_EDIT_ADDRESS, m_strAddress);
	DDX_Check(pDX, IDC_CHECK1, m_bChannel1);
	DDX_Check(pDX, IDC_CHECK10, m_bChannel10);
	DDX_Check(pDX, IDC_CHECK2, m_bChannel2);
	DDX_Check(pDX, IDC_CHECK3, m_bChannel3);
	DDX_Check(pDX, IDC_CHECK4, m_bChannel4);
	DDX_Check(pDX, IDC_CHECK5, m_bChannel5);
	DDX_Check(pDX, IDC_CHECK6, m_bChannel6);
	DDX_Check(pDX, IDC_CHECK7, m_bChannel7);
	DDX_Check(pDX, IDC_CHECK8, m_bChannel8);
	DDX_Check(pDX, IDC_CHECK9, m_bChannel9);
	DDX_CBIndex(pDX, IDC_COMBO_BAUDRATE, m_iBaudRate);
}


BEGIN_MESSAGE_MAP(CDebugLRAPage, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_SET, &CDebugLRAPage::OnBnClickedButtonSet)
END_MESSAGE_MAP()


// CDebugLRAPage 消息处理程序


void CDebugLRAPage::OnBnClickedButtonSet()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!UpdateData(TRUE))
	{
		return;
	}

	BOOL bChannel[LRA_CHANNEL_NUM];
	int i = 0;
	bChannel[i++] = m_bChannel1;
	bChannel[i++] = m_bChannel2;
	bChannel[i++] = m_bChannel3;
	bChannel[i++] = m_bChannel4;
	bChannel[i++] = m_bChannel5;

	bChannel[i++] = m_bChannel6;
	bChannel[i++] = m_bChannel7;
	bChannel[i++] = m_bChannel8;
	bChannel[i++] = m_bChannel9;
	bChannel[i++] = m_bChannel10;

	BeginWaitCursor();
	g_LRAComm.Initialize(m_strCOM);
	if (g_LRAComm.SetChannel(bChannel))
	{
		AfxMessageBox("设置成功！");
	}
	else
	{
		AfxMessageBox("设置失败！");
	}
	EndWaitCursor();
}


BOOL CDebugLRAPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_strCOM = g_pDoc->m_CommSettingsData.m_strLRACOM;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
