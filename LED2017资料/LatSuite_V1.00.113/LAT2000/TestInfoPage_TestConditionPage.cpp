// TestInfoPage_TestConditionPage.cpp : 实现文件
//

#include "stdafx.h"
#include "LAT2000.h"
#include "TestInfoPage_TestConditionPage.h"
#include "afxdialogex.h"


// CTestInfoPage_TestConditionPage 对话框

IMPLEMENT_DYNAMIC(CTestInfoPage_TestConditionPage, CPropertyPage)

CTestInfoPage_TestConditionPage::CTestInfoPage_TestConditionPage()
	: CPropertyPage(CTestInfoPage_TestConditionPage::IDD)
{

    m_strTMP = _T("");
    m_strWet = _T("");
    m_fTestRate = 0.0f;
    m_strRemark = _T("");
    m_strTestMachine = _T("");
    m_strTester = _T("");
    m_strTestDate = _T("");
}

CTestInfoPage_TestConditionPage::~CTestInfoPage_TestConditionPage()
{
}

void CTestInfoPage_TestConditionPage::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_T, m_strTMP);
    DDX_Text(pDX, IDC_EDIT_H, m_strWet);
    DDX_Text(pDX, IDC_EDIT_RATE, m_fTestRate);
    DDX_Text(pDX, IDC_EDIT_REMARK, m_strRemark);
    DDX_Text(pDX, IDC_EDIT_TEST_MACHINE, m_strTestMachine);
    DDX_Text(pDX, IDC_EDIT_TESTER, m_strTester);
    DDX_Text(pDX, IDC_EDIT_DATE, m_strTestDate);
    DDX_Check(pDX, IDC_CHECK_CUSTOM_VOL_AGING, m_bCustomVol_Aging);
    DDX_Check(pDX, IDC_CHECK_EMC_TEST, m_bEMC_Test);
    DDX_Check(pDX, IDC_CHECK_HIGH_LOW_VOL_AGING, m_bHighLowVol_Aging);
    DDX_Check(pDX, IDC_CHECK_HIGH_TEMP_AGING, m_bHighTMP_Aging);
    DDX_Check(pDX, IDC_CHECK_NOMAL_TEMP_AGING, m_bNormalTMP_Aging);
    DDX_Check(pDX, IDC_CHECK_STA_VOL_AGING, m_bStaVol_Aging);
    DDX_Check(pDX, IDC_CHECK_SWITCH_AGING, m_bSwitch_Aging);
}


BEGIN_MESSAGE_MAP(CTestInfoPage_TestConditionPage, CPropertyPage)
END_MESSAGE_MAP()


// CTestInfoPage_TestConditionPage 消息处理程序
