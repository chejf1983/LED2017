// DebugEMS61000_5APage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LAT2000.h"
#include "DebugEMS61000_5APage.h"
#include "afxdialogex.h"
#include "LAT2000Doc.h"

extern CString g_strCurrentPath;
// CDebugEMS61000_5APage �Ի���

IMPLEMENT_DYNAMIC(CDebugEMS61000_5APage, CPropertyPage)

CDebugEMS61000_5APage::CDebugEMS61000_5APage()
	: CPropertyPage(CDebugEMS61000_5APage::IDD)
{
	m_iCurSele = 0;
	m_strRe = _T("");
	m_iResult = 0;
	m_fTime = 0.0f;
	m_strCOM = _T("");

	CString strSection = "CDebugEMS61000_5APage";
	m_strCOM = AfxGetApp()->GetProfileString(strSection, "m_strCOM", "COM1");
}

CDebugEMS61000_5APage::~CDebugEMS61000_5APage()
{
	CString strSection = "CDebugEMS61000_5APage";
	AfxGetApp()->WriteProfileStringA(strSection, "m_strCOM", m_strCOM);
}

void CDebugEMS61000_5APage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_RE, m_strRe);
	DDX_Text(pDX, IDC_EDIT_RESULT, m_iResult);
	DDX_Text(pDX, IDC_EDIT_TIME, m_fTime);
	DDX_Control(pDX, IDC_EDIT_RE1, m_cRe1);
	DDX_CBString(pDX, IDC_COMBO_COM, m_strCOM);
}


BEGIN_MESSAGE_MAP(CDebugEMS61000_5APage, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_SET, &CDebugEMS61000_5APage::OnBnClickedButtonSet)
	ON_BN_CLICKED(IDC_BUTTON_START, &CDebugEMS61000_5APage::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CDebugEMS61000_5APage::OnBnClickedButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_READ, &CDebugEMS61000_5APage::OnBnClickedButtonRead)
END_MESSAGE_MAP()


// CDebugEMS61000_5APage ��Ϣ�������


void CDebugEMS61000_5APage::OnBnClickedButtonSet()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	BeginWaitCursor();
	g_EMS61000_5AComm.Initialize(g_strCurrentPath + "Communication Settings\\", m_strCOM);

	EMC5ASetData data;
	g_EMS61000_5AComm.ShowSettingsDialog(data, m_iCurSele,FALSE);
	EndWaitCursor();
}


void CDebugEMS61000_5APage::OnBnClickedButtonStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	EMC5ASetData data;
	BeginWaitCursor();
	BOOL bR = g_EMS61000_5AComm.Start(data, m_iCurSele);
	EndWaitCursor();
	if (bR)
	{
		AfxMessageBox("�����ɹ���");
	}
	else
	{
		AfxMessageBox("����ʧ�ܣ�");
	}
}


void CDebugEMS61000_5APage::OnBnClickedButtonReset()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	//BeginWaitCursor();
	//BOOL bR = g_EMS61000_5AComm.Reset();
	//EndWaitCursor();
	//if (bR)
	//{
	//	AfxMessageBox("��λ�ɹ���");
	//}
	//else
	//{
	//	AfxMessageBox("��λʧ�ܣ�");
	//}
}


void CDebugEMS61000_5APage::OnBnClickedButtonRead()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	EMC5AREData data;
	BeginWaitCursor();
	BOOL bR = g_EMS61000_5AComm.Read(data);
	EndWaitCursor();
	if (1 != bR)
	{
		m_strRe = data.strRe;
		m_iResult = data.m_iResult;
		m_fTime = data.m_fTime;
		m_cRe1.SetWindowTextA(m_strRe);
		UpdateData(FALSE);

		AfxMessageBox("��ȡ�ɹ���");
	}
	else
	{
		AfxMessageBox("��ȡʧ�ܣ�");
	}
}


BOOL CDebugEMS61000_5APage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_strCOM = g_pDoc->m_CommSettingsData.m_strCOMEMS61000_5A;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
