// BurnInSettingsDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LAT2000.h"
#include "BurnInSettingsDlg.h"
#include "afxdialogex.h"


// CBurnInSettingsDlg �Ի���

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


// CBurnInSettingsDlg ��Ϣ�������
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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	EnaleControls_bDisor_LowExecu();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
