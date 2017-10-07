// Configure_ExaminationPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LAT2000.h"
#include "Configure_ExaminationPage.h"
#include "afxdialogex.h"


// CConfigure_ExaminationPage �Ի���

IMPLEMENT_DYNAMIC(CConfigure_ExaminationPage, CPropertyPage)

CConfigure_ExaminationPage::CConfigure_ExaminationPage()
	: CPropertyPage(CConfigure_ExaminationPage::IDD)
{

    m_iCustomVolAgingCOM = 0;
}

CConfigure_ExaminationPage::~CConfigure_ExaminationPage()
{
}

void CConfigure_ExaminationPage::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
    DDX_Check(pDX, IDC_CHECK_LIGHTNING, m_bLightning);
    DDX_Check(pDX, IDC_CHECK_VOLTAGE_UPANDDIPS, m_bVoltageUpAndDips);
    DDX_CBString(pDX, IDC_COMBO_LIGHTNING_COM, m_strLightningCOM);
    DDX_CBString(pDX, IDC_COMBO_VOLTAGE_UPANDDIPS_COM, m_strVoltageUpAndDipsCOM);
    DDX_Check(pDX, IDC_CHECK_CUSTOM_VOL_AGING, m_bCustomVolAging);
    DDX_CBIndex(pDX, IDC_COMBO_CUSTOM_VOL_AGING, m_iCustomVolAgingCOM);
}


BEGIN_MESSAGE_MAP(CConfigure_ExaminationPage, CPropertyPage)
    ON_BN_CLICKED(IDC_BUTTON_VOLTAGE_UPANDDIPS, &CConfigure_ExaminationPage::OnBnClickedButtonVoltageUpanddips)
    ON_BN_CLICKED(IDC_BUTTON_LIGHTNING, &CConfigure_ExaminationPage::OnBnClickedButtonLightning)
    ON_BN_CLICKED(IDC_BUTTON_CUSTOM_VOL_AGING, &CConfigure_ExaminationPage::OnBnClickedButtonCustomVolAging)
END_MESSAGE_MAP()


// CConfigure_ExaminationPage ��Ϣ�������


BOOL CConfigure_ExaminationPage::OnInitDialog()
{
    CPropertyPage::OnInitDialog();

    // TODO:  �ڴ���Ӷ���ĳ�ʼ��

    return TRUE;  // return TRUE unless you set the focus to a control
    // �쳣: OCX ����ҳӦ���� FALSE
}

void CConfigure_ExaminationPage::OnBnClickedButtonLightning()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    UpdateData(TRUE);
    g_EMS61000_5AComm.Initialize(g_strCurrentPath + "Communication Settings\\", m_strLightningCOM);
    EMC5AREData data;
    BeginWaitCursor();
    if (1 != g_EMS61000_5AComm.Read(data))
    {
        AfxMessageBox("��ͨ�ɹ���");
    }
    else
    {
        AfxMessageBox("��ͨʧ�ܣ�");
    }
    EndWaitCursor();
}

void CConfigure_ExaminationPage::OnBnClickedButtonVoltageUpanddips()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    UpdateData(TRUE);
    g_EMS61000_11KComm.Initialize(g_strCurrentPath + "Communication Settings\\", m_strVoltageUpAndDipsCOM);
    EMC11KREData data;
    BeginWaitCursor();
    if (1 != g_EMS61000_11KComm.Read(data))
    {
        AfxMessageBox("��ͨ�ɹ���");
    }
    else
    {
        AfxMessageBox("��ͨʧ�ܣ�");
    }
    EndWaitCursor();
}




void CConfigure_ExaminationPage::OnBnClickedButtonCustomVolAging()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
}

