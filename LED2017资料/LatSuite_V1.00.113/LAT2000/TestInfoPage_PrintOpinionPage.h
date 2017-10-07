#pragma once
#include "Label.h"

// CTestInfoPage_PrintOpinionPage 对话框

class CTestInfoPage_PrintOpinionPage : public CPropertyPage
{
    DECLARE_DYNAMIC(CTestInfoPage_PrintOpinionPage)

public:
    CTestInfoPage_PrintOpinionPage();   // 标准构造函数
    virtual ~CTestInfoPage_PrintOpinionPage();

    // 对话框数据
    enum { IDD = IDD_TESTINFO_PAGE_PRINT_OPINION };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

    DECLARE_MESSAGE_MAP()
public:
    BOOL m_bPrintPageHeadLogo;
    int m_iPageHeadLogoPos;
    CString m_strPrintCap;

    CString m_strPageHeadCap;
    CString m_strPageHeadCapInfo;
    CString m_strPrintSubCap;
    BOOL m_bPrintSubCap;
    CComboBox m_ccomPos;
    CLabel m_cModify_Logo;
    afx_msg void OnStaticLogo();
    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedCheckPrintLogo();
    void MSPAINT(CString strPathName);
    afx_msg void OnBnClickedCheckPrintSubcap();
};
