#pragma once


// CTestInfoPage_TestConditionPage 对话框

class CTestInfoPage_TestConditionPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CTestInfoPage_TestConditionPage)

public:
	CTestInfoPage_TestConditionPage();
	virtual ~CTestInfoPage_TestConditionPage();

// 对话框数据
	enum { IDD = IDD_TESTINFO_PAGE_TEST_CONDITION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    CString m_strTMP;
    CString m_strWet;
    float m_fTestRate;
    CString m_strRemark;
    CString m_strTestMachine;
    CString m_strTester;
    CString m_strTestDate;
    BOOL m_bCustomVol_Aging;
    BOOL m_bEMC_Test;
    BOOL m_bHighLowVol_Aging;
    BOOL m_bHighTMP_Aging;
    BOOL m_bNormalTMP_Aging;
    BOOL m_bStaVol_Aging;
    BOOL m_bSwitch_Aging;
};
