#pragma once


// CConfigure_IndicatorPage 对话框

class CConfigure_IndicatorPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CConfigure_IndicatorPage)

public:
	CConfigure_IndicatorPage();
	virtual ~CConfigure_IndicatorPage();

// 对话框数据
	enum { IDD = IDD_CONFIGUE_INDICATOR_PAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    BOOL m_bLEDIndicator;
    BOOL m_bLRA;
    BOOL m_bBribe;

    CString m_strLEDIndicatorCOM;
    CString m_strLRACOM;
    CString m_strBribeCOM;

    CString m_strIndicatorRange;
    CString m_strBribeRange;

    afx_msg void OnBnClickedButtonLedIndicator();
    afx_msg void OnBnClickedButtonLra();
    afx_msg void OnBnClickedButtonBribe();
    afx_msg void OnBnClickedCheckBribe();
    afx_msg void OnBnClickedCheckLedIndicator();
	afx_msg void OnBnClickedButtonRiveter2();
    virtual BOOL OnInitDialog();
	int		m_iBribeAddr;
	int		m_iBribeAddr2;
};
