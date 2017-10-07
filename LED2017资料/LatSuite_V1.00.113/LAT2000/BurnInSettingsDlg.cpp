// BurnInSettingsDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "BurnInSettingsDlg.h"
#include "afxdialogex.h"


// CBurnInSettingsDlg 对话框

IMPLEMENT_DYNAMIC(CBurnInSettingsDlg, CDialogEx)

CBurnInSettingsDlg::CBurnInSettingsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBurnInSettingsDlg::IDD, pParent)
{

	m_iOFFSeconds = 0;
	m_iONSeconds = 0;
	//  m_iRunTimes = 0;
}

CBurnInSettingsDlg::~CBurnInSettingsDlg()
{
}

void CBurnInSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_OFF_SECONDS, m_iOFFSeconds);
	DDX_Text(pDX, IDC_EDIT_ON_SECONDS, m_iONSeconds);
	//  DDX_Text(pDX, IDC_EDIT_TIMES, m_iRunTimes);
}


BEGIN_MESSAGE_MAP(CBurnInSettingsDlg, CDialogEx)
END_MESSAGE_MAP()


// CBurnInSettingsDlg 消息处理程序
void CBurnInSettingsDlg::EnaleControls_bDisor_LowExecu()
{
	if (LOW_EXECUTION_LEVEL ==  g_iExecutionLevel || TRUE == g_bDisplayLimitOnly)
	{
		CEdit *pEdit = (CEdit*)GetDlgItem(IDC_EDIT_ON_SECONDS);
		pEdit->SetReadOnly(TRUE);
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT_OFF_SECONDS);
		pEdit->SetReadOnly(TRUE);
	}

}


BOOL CBurnInSettingsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	EnaleControls_bDisor_LowExecu();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
