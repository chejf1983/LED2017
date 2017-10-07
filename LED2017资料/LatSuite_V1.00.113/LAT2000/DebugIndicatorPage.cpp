// DebugLinePage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LAT2000.h"
#include "DebugIndicatorPage.h"
#include "afxdialogex.h"
#include "LAT2000Doc.h"

// CDebugIndicatorPage �Ի���

IMPLEMENT_DYNAMIC(CDebugIndicatorPage, CPropertyPage)

CDebugIndicatorPage::CDebugIndicatorPage()
	: CPropertyPage(CDebugIndicatorPage::IDD)
{

	m_strBaudrate = _T("9600");
	m_strCOM = _T("COM1");
	m_iState = 0;
	m_iChannel = 0;
	m_ucAddress = 0x9F;

	CString strSection = "Debug_IndicatorPage";
	m_strCOM = AfxGetApp()->GetProfileStringA(strSection, "m_strCOM", "COM1");
}

CDebugIndicatorPage::~CDebugIndicatorPage()
{
	CString strSection = "Debug_IndicatorPage";
	AfxGetApp()->WriteProfileStringA(strSection, "m_strCOM", m_strCOM);
}

void CDebugIndicatorPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO_BAUDRATE, m_strBaudrate);
	DDX_CBString(pDX, IDC_COMBO_COM, m_strCOM);
	DDX_CBIndex(pDX, IDC_COMBO_STATE, m_iState);
	DDX_Text(pDX, IDC_EDIT_CHANNEL, m_iChannel);
	DDX_Text(pDX, IDC_EDIT_ADDRESS, m_ucAddress);
}


BEGIN_MESSAGE_MAP(CDebugIndicatorPage, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_RED, &CDebugIndicatorPage::OnBnClickedButtonRed)
	ON_BN_CLICKED(IDC_BUTTON_GREEN, &CDebugIndicatorPage::OnBnClickedButtonGreen)
	ON_BN_CLICKED(IDC_BUTTON_OFF, &CDebugIndicatorPage::OnBnClickedButtonOff)
	ON_BN_CLICKED(IDC_BUTTON_SET_ONE, &CDebugIndicatorPage::OnBnClickedButtonSetOne)
END_MESSAGE_MAP()


// CDebugIndicatorPage ��Ϣ�������


void CDebugIndicatorPage::OnBnClickedButtonRed()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (!UpdateData(TRUE))
	{
		return;
	}
	
	g_IndicatorComm.Initialize(m_strCOM);

	ChannelState *ucState;
	ucState = new ChannelState [10 * 3];
	for (int i = 0; i < g_iRowNum; i++)
	{
		for(int j = 0; j < 10; j++)
			if (j < g_iColomnNum)
				ucState[i * 10 + j] = CHANNEL_RED;
			else
				ucState[i * 10 + j] = CHANNEL_OFF;
	}

	if (g_IndicatorComm.SetAllChannelState(ucState))
	{
		AfxMessageBox("���óɹ���");
	}
	else
	{
		AfxMessageBox("����ʧ�ܣ�");
	}
}


void CDebugIndicatorPage::OnBnClickedButtonGreen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (!UpdateData(TRUE))
	{
		return;
	}
	
	g_IndicatorComm.Initialize(m_strCOM);

	ChannelState *ucState;
	ucState = new ChannelState [10 * 3];
	for (int i = 0; i < g_iRowNum; i++)
	{
		for(int j = 0; j < 10; j++)
			if (j < g_iColomnNum)
				ucState[i * 10 + j] = CHANNEL_GREEN;
			else
				ucState[i * 10 + j] = CHANNEL_OFF;
	}

	BeginWaitCursor();
	if (g_IndicatorComm.SetAllChannelState(ucState))
	{
		AfxMessageBox("���óɹ���");
	}
	else
	{
		AfxMessageBox("����ʧ�ܣ�");
	}
	EndWaitCursor();
}


void CDebugIndicatorPage::OnBnClickedButtonOff()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (!UpdateData(TRUE))
	{
		return;
	}
	
	g_IndicatorComm.Initialize(m_strCOM);

	ChannelState *ucState;
	ucState = new ChannelState [10 * 3];
	for (int i = 0; i < g_iRowNum; i++)
	{
		for(int j = 0; j < 10; j++)
			if (j < g_iColomnNum)
				ucState[i * 10 + j] = CHANNEL_OFF;
		else
			ucState[i * 10 + j] = CHANNEL_OFF;
	}

	BeginWaitCursor();
	if (g_IndicatorComm.SetAllChannelState(ucState))
	{
		AfxMessageBox("���óɹ���");
	}
	else
	{
		AfxMessageBox("����ʧ�ܣ�");
	}
	EndWaitCursor();
}


void CDebugIndicatorPage::OnBnClickedButtonSetOne()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


BOOL CDebugIndicatorPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_strCOM = g_pDoc->m_CommSettingsData.m_strCOMLEDIndicator;
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
