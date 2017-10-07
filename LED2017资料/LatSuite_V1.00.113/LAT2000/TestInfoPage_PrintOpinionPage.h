#pragma once
#include "Label.h"

// CTestInfoPage_PrintOpinionPage �Ի���

class CTestInfoPage_PrintOpinionPage : public CPropertyPage
{
    DECLARE_DYNAMIC(CTestInfoPage_PrintOpinionPage)

public:
    CTestInfoPage_PrintOpinionPage();   // ��׼���캯��
    virtual ~CTestInfoPage_PrintOpinionPage();

    // �Ի�������
    enum { IDD = IDD_TESTINFO_PAGE_PRINT_OPINION };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
