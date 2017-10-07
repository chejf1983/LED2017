// Configure_ExaminationPage.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "Configure_ExaminationPage.h"
#include "afxdialogex.h"


// CConfigure_ExaminationPage 对话框

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


// CConfigure_ExaminationPage 消息处理程序


BOOL CConfigure_ExaminationPage::OnInitDialog()
{
    CPropertyPage::OnInitDialog();

    // TODO:  在此添加额外的初始化

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}

void CConfigure_ExaminationPage::OnBnClickedButtonLightning()
{
    // TODO: 在此添加控件通知处理程序代码
    UpdateData(TRUE);
    g_EMS61000_5AComm.Initialize(g_strCurrentPath + "Communication Settings\\", m_strLightningCOM);
    EMC5AREData data;
    BeginWaitCursor();
    if (1 != g_EMS61000_5AComm.Read(data))
    {
        AfxMessageBox("试通成功！");
    }
    else
    {
        AfxMessageBox("试通失败！");
    }
    EndWaitCursor();
}

void CConfigure_ExaminationPage::OnBnClickedButtonVoltageUpanddips()
{
    // TODO: 在此添加控件通知处理程序代码
    UpdateData(TRUE);
    g_EMS61000_11KComm.Initialize(g_strCurrentPath + "Communication Settings\\", m_strVoltageUpAndDipsCOM);
    EMC11KREData data;
    BeginWaitCursor();
    if (1 != g_EMS61000_11KComm.Read(data))
    {
        AfxMessageBox("试通成功！");
    }
    else
    {
        AfxMessageBox("试通失败！");
    }
    EndWaitCursor();
}




void CConfigure_ExaminationPage::OnBnClickedButtonCustomVolAging()
{
    // TODO: 在此添加控件通知处理程序代码
}

