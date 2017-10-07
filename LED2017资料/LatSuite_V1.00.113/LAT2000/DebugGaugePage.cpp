// DebugGaugePage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LAT2000.h"
#include "DebugGaugePage.h"
#include "afxdialogex.h"
#include "LAT2000Doc.h"

// CDebugGaugePage �Ի���

IMPLEMENT_DYNAMIC(CDebugGaugePage, CPropertyPage)

CDebugGaugePage::CDebugGaugePage()
	: CPropertyPage(CDebugGaugePage::IDD)
{

	m_strBaudrate = _T("9600");
	m_strCOM = _T("COM1");
	m_ucAddress = 1;
	m_fCurrentA = 0.0f;
	m_fPowerW = 0.0f;
	m_fVoltageV = 0.0f;
}

CDebugGaugePage::~CDebugGaugePage()
{
}

void CDebugGaugePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO_BAUDRATE, m_strBaudrate);
	DDX_CBString(pDX, IDC_COMBO_COM, m_strCOM);
	DDX_Text(pDX, IDC_EDIT_ADDRESS, m_ucAddress);
	DDX_Text(pDX, IDC_EDIT_CURRENT, m_fCurrentA);
	DDX_Text(pDX, IDC_EDIT_POWER, m_fPowerW);
	DDX_Text(pDX, IDC_EDIT_VOLTAGE, m_fVoltageV);
}


BEGIN_MESSAGE_MAP(CDebugGaugePage, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_READ, &CDebugGaugePage::OnBnClickedButtonRead)
END_MESSAGE_MAP()


// CDebugGaugePage ��Ϣ�������


void CDebugGaugePage::OnBnClickedButtonRead()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (!UpdateData(TRUE))
	{
		return;
	}

	BeginWaitCursor();
	g_GaugeComm.Initialize(m_strCOM, atoi(m_strBaudrate));
	BOOL bR = g_GaugeComm.Read(m_ucAddress, m_fVoltageV, m_fCurrentA, m_fPowerW);
	EndWaitCursor();
	if (bR)
	{
		AfxMessageBox("��ȡ�ɹ���");
	}
	else
	{
		AfxMessageBox("��ȡʧ�ܣ�");
	}
	
	UpdateData(FALSE);
}


BOOL CDebugGaugePage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_strCOM = g_pDoc->m_CommSettingsData.m_strCOMGauge;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
