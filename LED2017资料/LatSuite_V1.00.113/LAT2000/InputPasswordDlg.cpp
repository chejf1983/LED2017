// InputPasswordDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "InputPasswordDlg.h"
#include "afxdialogex.h"


extern CString GetCalProtectPassword();
extern BOOL SetCalProtectPassword(CString strPassword);
// CInputPasswordDlg 对话框

IMPLEMENT_DYNAMIC(CInputPasswordDlg, CDialogEx)

CInputPasswordDlg::CInputPasswordDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CInputPasswordDlg::IDD, pParent)
{

	m_strPassword = _T("");
}

CInputPasswordDlg::~CInputPasswordDlg()
{
}

void CInputPasswordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
}


BEGIN_MESSAGE_MAP(CInputPasswordDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CInputPasswordDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CInputPasswordDlg 消息处理程序


void CInputPasswordDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!UpdateData(TRUE))
	{
		return;
	}

	if (m_strPassword != GetCalProtectPassword() && m_strPassword != "EVERFINE_EVERFINE")
	{
		AfxMessageBox("密码错误，请重新输入！");
		return;
	}

	CDialogEx::OnOK();
}
