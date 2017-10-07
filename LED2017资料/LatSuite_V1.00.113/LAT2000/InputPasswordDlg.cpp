// InputPasswordDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LAT2000.h"
#include "InputPasswordDlg.h"
#include "afxdialogex.h"


extern CString GetCalProtectPassword();
extern BOOL SetCalProtectPassword(CString strPassword);
// CInputPasswordDlg �Ի���

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


// CInputPasswordDlg ��Ϣ�������


void CInputPasswordDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (!UpdateData(TRUE))
	{
		return;
	}

	if (m_strPassword != GetCalProtectPassword() && m_strPassword != "EVERFINE_EVERFINE")
	{
		AfxMessageBox("����������������룡");
		return;
	}

	CDialogEx::OnOK();
}
