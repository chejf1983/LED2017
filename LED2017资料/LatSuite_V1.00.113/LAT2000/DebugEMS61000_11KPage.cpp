// DebugEMS61000_11KPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LAT2000.h"
#include "DebugEMS61000_11KPage.h"
#include "afxdialogex.h"
#include "LAT2000Doc.h"


extern CString g_strCurrentPath;
// CDebugEMS61000_11KPage �Ի���

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


// CDebugEMS61000_11KPage ��Ϣ�������


void CDebugEMS61000_11KPage::OnBnClickedButtonSet()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	BeginWaitCursor();
	g_EMS61000_11KComm.Initialize(g_strCurrentPath + "Communication Settings\\", m_strCOM);

	g_EMS61000_11KComm.ShowSettingsDialog(m_iCurSele, FALSE);
	EndWaitCursor();
}


void CDebugEMS61000_11KPage::OnBnClickedButtonStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	BeginWaitCursor();
	g_EMS61000_11KComm.Initialize(g_strCurrentPath + "Communication Settings\\", m_strCOM);
	BOOL bR = g_EMS61000_11KComm.Start(m_iCurSele);
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


void CDebugEMS61000_11KPage::OnBnClickedButtonReset()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	BeginWaitCursor();
	g_EMS61000_11KComm.Initialize(g_strCurrentPath + "Communication Settings\\", m_strCOM);
	BOOL bR = g_EMS61000_11KComm.Reset();
	EndWaitCursor();
	if (bR)
	{
		AfxMessageBox("��λ�ɹ���");
	}
	else
	{
		AfxMessageBox("��λʧ�ܣ�");
	}
}


void CDebugEMS61000_11KPage::OnBnClickedButtonRead()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

		AfxMessageBox("��ȡ�ɹ���");
	}
	else
	{
		AfxMessageBox("��ȡʧ�ܣ�");
	}
}


void CDebugEMS61000_11KPage::OnBnClickedButtonEutOn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	BeginWaitCursor();
	g_EMS61000_11KComm.Initialize(g_strCurrentPath + "Communication Settings\\", m_strCOM);
	BOOL bR = g_EMS61000_11KComm.SetEUT(TRUE);
	EndWaitCursor();

	if (bR)
	{
		AfxMessageBox("�򿪳ɹ���");
	}
	else
	{
		AfxMessageBox("��ʧ�ܣ�");
	}
}


void CDebugEMS61000_11KPage::OnBnClickedButtonEutOff()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	BeginWaitCursor();
	g_EMS61000_11KComm.Initialize(g_strCurrentPath + "Communication Settings\\", m_strCOM);
	BOOL bR = g_EMS61000_11KComm.SetEUT(FALSE);
	EndWaitCursor();

	if (bR)
	{
		AfxMessageBox("�رճɹ���");
	}
	else
	{
		AfxMessageBox("�ر�ʧ�ܣ�");
	}
}


BOOL CDebugEMS61000_11KPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_strCOM = g_pDoc->m_CommSettingsData.m_strCOMEMS61000_11K;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
