#pragma once


// CConfigure_WatchPage 对话框

class CConfigure_WatchPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CConfigure_WatchPage)

public:
	CConfigure_WatchPage();
	virtual ~CConfigure_WatchPage();

// 对话框数据
	enum { IDD = IDD_CONFIGUE_WATCH_PAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    BOOL m_bGauge;
    BOOL m_bTemperatureController;

    CString m_strGaugeCOM;
    CString m_strTemperatureContrllerCOM;

    BYTE m_ucCurSelGaugeAddress;
    BYTE m_ucCurSelTemperatureContrllerAddress;

    CArray<BYTE, BYTE> m_ucGaugeAddress;
    CArray<BYTE, BYTE> m_ucTemperatureAddress;
    afx_msg void OnBnClickedButtonTemperatureController();
    afx_msg void OnBnClickedButtonitGauge();
    afx_msg void OnBnClickedModifyTemperatureControllerAddress();
    afx_msg void OnBnClickedModifyGaugeAddress();
    virtual BOOL OnInitDialog();
    void  ListTMPAdress();
    void  ListGaugeAdress();
    CListCtrl m_cListTMP;
    CListCtrl m_cListGauge;


    CString m_strTMPControlName;
    CString m_strGaugeName;
    int m_iSelTMPControl;
    int m_iSelGauge;
    afx_msg void OnNMClickListTemperatureController(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnNMClickListGauge(NMHDR *pNMHDR, LRESULT *pResult);
};
