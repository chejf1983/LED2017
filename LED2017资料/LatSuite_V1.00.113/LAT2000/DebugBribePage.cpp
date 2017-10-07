// DebugBribePage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LAT2000.h"
#include "DebugBribePage.h"
#include "afxdialogex.h"
#include "LAT2000Doc.h"

// CDebugBribePage �Ի���

IMPLEMENT_DYNAMIC(CDebugBribePage, CPropertyPage)

CDebugBribePage::CDebugBribePage()
	: CPropertyPage(CDebugBribePage::IDD)
{
    m_strCOM = _T("COM1");
    m_strAddress = _T("CF");
    m_iBaudRate = 9600;
}

CDebugBribePage::~CDebugBribePage()
{
}

void CDebugBribePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
    DDX_CBString(pDX, IDC_COMBO_COM, m_strCOM);
    DDX_Text(pDX, IDC_EDIT_ADDRESS, m_strAddress);
    DDX_Check(pDX, IDC_CHECK1, m_bChannel1);
    DDX_Check(pDX, IDC_CHECK10, m_bChannel10);
    DDX_Check(pDX, IDC_CHECK2, m_bChannel2);
    DDX_Check(pDX, IDC_CHECK3, m_bChannel3);
    DDX_Check(pDX, IDC_CHECK4, m_bChannel4);
    DDX_Check(pDX, IDC_CHECK5, m_bChannel5);
    DDX_Check(pDX, IDC_CHECK6, m_bChannel6);
    DDX_Check(pDX, IDC_CHECK7, m_bChannel7);
    DDX_Check(pDX, IDC_CHECK8, m_bChannel8);
    DDX_Check(pDX, IDC_CHECK9, m_bChannel9);
    DDX_CBIndex(pDX, IDC_COMBO_BAUDRATE, m_iBaudRate);
}


BEGIN_MESSAGE_MAP(CDebugBribePage, CPropertyPage)
    ON_BN_CLICKED(IDC_BUTTON_SET, &CDebugBribePage::OnBnClickedButtonSet)
END_MESSAGE_MAP()


// CDebugBribePage ��Ϣ�������


void CDebugBribePage::OnBnClickedButtonSet()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    if (!UpdateData(TRUE))
    {
        return;
    }

    BOOL bChannel[LRA_CHANNEL_NUM];
    int i = 0;
    bChannel[i++] = m_bChannel1;
    bChannel[i++] = m_bChannel2;
    bChannel[i++] = m_bChannel3;
    bChannel[i++] = m_bChannel4;
    bChannel[i++] = m_bChannel5;

    bChannel[i++] = m_bChannel6;
    bChannel[i++] = m_bChannel7;
    bChannel[i++] = m_bChannel8;
    bChannel[i++] = m_bChannel9;
    bChannel[i++] = m_bChannel10;

    BeginWaitCursor();
    g_BribeComm.Initialize(m_strCOM);
    if (g_BribeComm.SetChannel(bChannel))
    {
        AfxMessageBox("���óɹ���");
    }
    else
    {
        AfxMessageBox("����ʧ�ܣ�");
    }
    g_BribeComm.SwitchAllChannel(FALSE);
    EndWaitCursor();
}


BOOL CDebugBribePage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_strCOM = g_pDoc->m_CommSettingsData.m_strBribeCOM;
	
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
