// StandardLampSettingsDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LAT2000.h"
#include "StandardLampSettingsDlg.h"
#include "afxdialogex.h"


// CStandardLampSettingsDlg �Ի���

IMPLEMENT_DYNAMIC(CStandardLampSettingsDlg, CDialogEx)

CStandardLampSettingsDlg::CStandardLampSettingsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CStandardLampSettingsDlg::IDD, pParent)
{
	m_fCurrent = 0.0f;
	m_fProtectVoltage = 0.0f;

	CString strSection = "StandardLampSettingsDlg";
	m_fCurrent = (float)( atof(AfxGetApp()->GetProfileString(strSection, "m_fCurrent", "0.0")) );
	m_fProtectVoltage = (float)( atof(AfxGetApp()->GetProfileString(strSection, "m_fProtectVoltage", "0.0")) );
}

CStandardLampSettingsDlg::~CStandardLampSettingsDlg()
{
	CString strTemp, strSection = "StandardLampSettingsDlg";
	
	strTemp.Format("%f", m_fCurrent);
	AfxGetApp()->WriteProfileString(strSection, "m_fCurrent", strTemp);
	
	strTemp.Format("%f", m_fProtectVoltage);
	AfxGetApp()->WriteProfileString(strSection, "m_fProtectVoltage", strTemp);
}

void CStandardLampSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CURRENT, m_fCurrent);
	DDX_Text(pDX, IDC_EDIT_PROTECT_VOLTAGE, m_fProtectVoltage);
}


BEGIN_MESSAGE_MAP(CStandardLampSettingsDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CStandardLampSettingsDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CStandardLampSettingsDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_OFF, &CStandardLampSettingsDlg::OnBnClickedButtonOff)
END_MESSAGE_MAP()


// CStandardLampSettingsDlg ��Ϣ�������


void CStandardLampSettingsDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CDialogEx::OnOK();
}


void CStandardLampSettingsDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void CStandardLampSettingsDlg::OnBnClickedButtonOff()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	BeginWaitCursor();
	g_WYComm.Reset(TRUE);
	EndWaitCursor();
}
