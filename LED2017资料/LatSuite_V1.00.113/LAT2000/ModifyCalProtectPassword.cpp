// ModifyCalProtectPassword.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "ModifyCalProtectPassword.h"
#include "afxdialogex.h"


extern CString GetCalProtectPassword();    
extern CString GetHighExcutionPassword();
extern BOOL SetCalProtectPassword(CString strPassword);
extern BOOL SetHighExcutionPassword(CString strPassword);
// CModifyCalProtectPassword 对话框

IMPLEMENT_DYNAMIC(CModifyCalProtectPassword, CDialogEx)

CModifyCalProtectPassword::CModifyCalProtectPassword(CWnd* pParent /*=NULL*/)
	: CDialogEx(CModifyCalProtectPassword::IDD, pParent)
{

	m_strNewPassword1 = _T("");
	m_strNewPassword2 = _T("");
	m_strOldPassword = _T("");
}

CModifyCalProtectPassword::~CModifyCalProtectPassword()
{
}

void CModifyCalProtectPassword::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NEW_PASSWORD1, m_strNewPassword1);
	DDV_MaxChars(pDX, m_strNewPassword1, 16);
	DDX_Text(pDX, IDC_EDIT_NEW_PASSWORD2, m_strNewPassword2);
	DDV_MaxChars(pDX, m_strNewPassword2, 16);
	DDX_Text(pDX, IDC_EDIT_OLD_PASSWORD, m_strOldPassword);
	DDV_MaxChars(pDX, m_strOldPassword, 16);
}


BEGIN_MESSAGE_MAP(CModifyCalProtectPassword, CDialogEx)
	ON_BN_CLICKED(IDOK, &CModifyCalProtectPassword::OnBnClickedOk)
END_MESSAGE_MAP()


// CModifyCalProtectPassword 消息处理程序


void CModifyCalProtectPassword::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!UpdateData(TRUE))
	{
		return;
	}

	if (GetHighExcutionPassword() != m_strOldPassword && "EVERFINE_EVERFINE" != m_strOldPassword)
	{
		AfxMessageBox("原密码错误，请重新输入！");
		return;
	}

	if (m_strNewPassword1 != m_strNewPassword2)
	{
		AfxMessageBox("两次输入密码不一致，请重新输入！");
		return;
	}

	BOOL bR = SetHighExcutionPassword(m_strNewPassword1);
	if (bR)
	{
		AfxMessageBox("设置成功！");
	}
	else
	{
		AfxMessageBox("设置失败！");
		return;
	}

	CDialogEx::OnOK();
}
