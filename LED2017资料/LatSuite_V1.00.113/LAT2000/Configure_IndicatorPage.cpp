// Configure_IndicatorPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LAT2000.h"
#include "Configure_IndicatorPage.h"
#include "afxdialogex.h"


// CConfigure_IndicatorPage �Ի���

IMPLEMENT_DYNAMIC(CConfigure_IndicatorPage, CPropertyPage)

CConfigure_IndicatorPage::CConfigure_IndicatorPage()
	: CPropertyPage(CConfigure_IndicatorPage::IDD)
	, m_iBribeAddr(0)
	, m_iBribeAddr2(0)
{

}

CConfigure_IndicatorPage::~CConfigure_IndicatorPage()
{
}

void CConfigure_IndicatorPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_LED_INDICATOR, m_bLEDIndicator);
	DDX_Check(pDX, IDC_CHECK_RIVETER, m_bBribe);
	DDX_Check(pDX, IDC_CHECK_LRA, m_bLRA);
	DDX_CBString(pDX, IDC_COMBO_LED_INDICATOR_COM, m_strLEDIndicatorCOM);
	DDX_CBString(pDX, IDC_COMBO_LRA_COM, m_strLRACOM);
	DDX_CBString(pDX, IDC_COMBO_RIVETER_COM, m_strBribeCOM);
	DDX_CBString(pDX, IDC_COMBO_LED_INDICATOR_RANGE, m_strIndicatorRange);
	DDX_CBString(pDX, IDC_COMBO_RIVETER_RANGE, m_strBribeRange);
	DDX_CBIndex(pDX, IDC_COMBO_BRIBE_ADDR, m_iBribeAddr);
	DDX_CBIndex(pDX, IDC_COMBO_BRIBE_ADDR2, m_iBribeAddr2);
}


BEGIN_MESSAGE_MAP(CConfigure_IndicatorPage, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_LED_INDICATOR, &CConfigure_IndicatorPage::OnBnClickedButtonLedIndicator)
	ON_BN_CLICKED(IDC_BUTTON_LRA, &CConfigure_IndicatorPage::OnBnClickedButtonLra)
    ON_BN_CLICKED(IDC_BUTTON_RIVETER, &CConfigure_IndicatorPage::OnBnClickedButtonBribe)
    ON_BN_CLICKED(IDC_CHECK_LED_INDICATOR, &CConfigure_IndicatorPage::OnBnClickedCheckLedIndicator)
    ON_BN_CLICKED(IDC_CHECK_RIVETER, &CConfigure_IndicatorPage::OnBnClickedCheckBribe)
	ON_BN_CLICKED(IDC_BUTTON_RIVETER2, &CConfigure_IndicatorPage::OnBnClickedButtonRiveter2)
END_MESSAGE_MAP()


// CConfigure_IndicatorPage ��Ϣ�������


BOOL CConfigure_IndicatorPage::OnInitDialog()
{
    CPropertyPage::OnInitDialog();

    // TODO:  �ڴ���Ӷ���ĳ�ʼ��
    CString strTemp;
    strTemp.Format("Baudate:%d, Address:0X%x", 9600, 0x9F);  
    GetDlgItem(IDC_EDIT_LED_INDICATOR)->SetWindowTextA(strTemp);
    strTemp.Format("Baudate:%d, Address:0X%x", 9600, 0xAF);  
    GetDlgItem(IDC_EDIT_LRA)->SetWindowTextA(strTemp);
    strTemp.Format("Baudate:%d, Address:0X%x", 9600, 0xCF);  
    GetDlgItem(IDC_EDIT_RIVETER)->SetWindowTextA(strTemp);  
    GetDlgItem(IDC_COMBO_RIVETER_RANGE)->EnableWindow(m_bBribe);
    GetDlgItem(IDC_COMBO_LED_INDICATOR_RANGE)->EnableWindow(m_bLEDIndicator);
    return TRUE;  // return TRUE unless you set the focus to a control
    // �쳣: OCX ����ҳӦ���� FALSE
}

void CConfigure_IndicatorPage::OnBnClickedButtonLedIndicator()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    UpdateData(TRUE);

    g_IndicatorComm.Initialize(m_strLEDIndicatorCOM);
    ChannelState *iState;
    iState = new ChannelState [g_iColomnNum * g_iRowNum];
    for (int i = 0; i < g_iColomnNum * g_iRowNum; i++)
    {
        iState[i] = CHANNEL_OFF;
    }
    if (g_IndicatorComm.SetAllChannelState(iState))
    {
        AfxMessageBox("��ͨ�ɹ���");
    }
    else
    {
        AfxMessageBox("��ͨʧ�ܣ�");
    }
}

void CConfigure_IndicatorPage::OnBnClickedButtonLra()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    UpdateData(TRUE);

    BeginWaitCursor();
    g_LRAComm.Initialize(m_strLRACOM);
    BOOL bR = g_LRAComm.SwitchAllChannel(FALSE);
    EndWaitCursor();
    if (bR)
    {
        AfxMessageBox("��ͨ�ɹ���");
    }
    else
    {
        AfxMessageBox("��ͨʧ�ܣ�");
    }
}

void CConfigure_IndicatorPage::OnBnClickedButtonBribe()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    UpdateData(TRUE);

    BeginWaitCursor();
    g_BribeComm.Initialize(m_strBribeCOM);
	g_BribeComm.SetAddress(0xEE, m_iBribeAddr);
    BOOL bR = g_BribeComm.SwitchAllChannel(FALSE);
    EndWaitCursor();
    if (bR)
    {
        AfxMessageBox("��ͨ�ɹ���");
    }
    else
    {
        AfxMessageBox("��ͨʧ�ܣ�");
    }
}

void CConfigure_IndicatorPage::OnBnClickedButtonRiveter2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	BeginWaitCursor();
	g_BribeComm.Initialize(m_strBribeCOM);
	g_BribeComm.SetAddress(0xEE, m_iBribeAddr2);
	BOOL bR = g_BribeComm.SwitchAllChannel(FALSE);
	EndWaitCursor();
	if (bR)
	{
		AfxMessageBox("��ͨ�ɹ���");
	}
	else
	{
		AfxMessageBox("��ͨʧ�ܣ�");
	}
}

void CConfigure_IndicatorPage::OnBnClickedCheckLedIndicator()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    UpdateData(TRUE);
    GetDlgItem(IDC_COMBO_LED_INDICATOR_RANGE)->EnableWindow(m_bLEDIndicator);
}

void CConfigure_IndicatorPage::OnBnClickedCheckBribe()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    UpdateData(TRUE);
    GetDlgItem(IDC_COMBO_RIVETER_RANGE)->EnableWindow(m_bBribe);
}

