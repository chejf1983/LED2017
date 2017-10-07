// DebugWYPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LAT2000.h"
#include "DebugWYPage.h"
#include "afxdialogex.h"
#include "LAT2000Doc.h"


// CDebugWYPage �Ի���

IMPLEMENT_DYNAMIC(CDebugWYPage, CPropertyPage)

CDebugWYPage::CDebugWYPage()
	: CPropertyPage(CDebugWYPage::IDD)
	, m_fCurr(0)
{

	m_fVoltage = 0.0f;
	m_fCurrent = 0.0f;

	CString strSection = "WYDebugPage";
	m_strCOM = AfxGetApp()->GetProfileStringA(strSection, "m_strCOM", "COM1");
	m_fProtectCurrent = 0.0f;
	m_fVoltageSet = 0.0f;
}

CDebugWYPage::~CDebugWYPage()
{
	CString strSection = "WYDebugPage";
	AfxGetApp()->WriteProfileStringA(strSection, "m_strCOM", m_strCOM);
}

void CDebugWYPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO_COM, m_strCOM);
	DDX_Text(pDX, IDC_EDIT_VOLTAGE_READ, m_fVoltage);
	DDX_Text(pDX, IDC_EDIT_CURRENT_READ, m_fCurrent);
	DDX_Text(pDX, IDC_EDIT_PRPTECT_CURRENT, m_fProtectCurrent);
	DDX_Text(pDX, IDC_EDIT_VOLTAGE_SET, m_fVoltageSet);
	DDX_Text(pDX, IDC_EDIT_CURRENT_SET, m_fCurr);
}


BEGIN_MESSAGE_MAP(CDebugWYPage, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_READ, &CDebugWYPage::OnBnClickedButtonRead)
	ON_BN_CLICKED(IDC_BUTTON_OUTPUT, &CDebugWYPage::OnBnClickedButtonOutput)
    ON_BN_CLICKED(IDC_OUTPUT_HLS_200, &CDebugWYPage::OnBnClickedOutputHls200)
    ON_BN_CLICKED(IDC_RESET_HLS_200, &CDebugWYPage::OnBnClickedResetHls200)
    ON_BN_CLICKED(IDC_BUTTON_READ_STATE, &CDebugWYPage::OnBnClickedButtonReadState)
	ON_BN_CLICKED(IDC_BUTTON_SET, &CDebugWYPage::OnBnClickedButtonSet)
END_MESSAGE_MAP()


// CDebugWYPage ��Ϣ�������


void CDebugWYPage::OnBnClickedButtonRead()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	BeginWaitCursor();
	int iCom = 1;
	sscanf_s(m_strCOM, "COM%d", &iCom);
	g_WYComm.Initialize(iCom, 1);
    
	BOOL bR = g_WYComm.GetPower(m_fVoltage, m_fCurrent, TRUE);
	EndWaitCursor();
}


void CDebugWYPage::OnBnClickedButtonOutput()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	BeginWaitCursor();
	int iCom = 1;
	sscanf_s(m_strCOM, "COM%d", &iCom);
	g_WYComm.Initialize(iCom, 1);
	float f1, f2;
	BOOL bR = g_WYComm.SetPower(sele_u, m_fVoltageSet, m_fProtectCurrent, f1, f2, TRUE);
	EndWaitCursor();
}


BOOL CDebugWYPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_strCOM = g_pDoc->m_CommSettingsData.m_strStandardSupplyCOM;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDebugWYPage::OnBnClickedOutputHls200()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    UpdateData(TRUE);

    BeginWaitCursor();
    int iCom = 1;
    sscanf_s(m_strCOM, "COM%d", &iCom);
    g_HLS_200.SetCom(iCom);

    BOOL bR = g_HLS_200.OpenOutput();
    if (!bR)
    {
        AfxMessageBox("���ʧ��!");
    }
    EndWaitCursor();
}


void CDebugWYPage::OnBnClickedResetHls200()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    BeginWaitCursor();
    int iCom = 1;
    sscanf_s(m_strCOM, "COM%d", &iCom);
    g_HLS_200.SetCom(iCom);

    BOOL bR = g_HLS_200.CloseOutput();
    if (!bR)
    {
        AfxMessageBox("��λʧ��!");
    }
    EndWaitCursor();
}


void CDebugWYPage::OnBnClickedButtonReadState()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    BeginWaitCursor();
    int iCom = 1;
    sscanf_s(m_strCOM, "COM%d", &iCom);
    g_HLS_200.SetCom(iCom);
    BOOL Output,Load,Warning;
    BOOL bR = g_HLS_200.GetState(Output,Load,Warning);
    if (!bR)
    {
        AfxMessageBox("��ȡ״̬ʧ��!");
    }
    else
    {
        CString strTemp;
        strTemp.Format("���״̬:%d, ����״̬: %d, ��·״̬: %d", Output,Load,Warning);
        AfxMessageBox(strTemp);
    }
    EndWaitCursor();
}


void CDebugWYPage::OnBnClickedButtonSet()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	BeginWaitCursor();
	int iCom = 1;
	sscanf_s(m_strCOM, "COM%d", &iCom);
	g_HLS_200.SetCom(iCom);
	BOOL bR = g_HLS_200.SetCurr(m_fCurr*10);
	if (!bR)
	{
		AfxMessageBox("ʧ��!");
	}
	else
	{
		AfxMessageBox("OK!");
	}
	EndWaitCursor();
}
