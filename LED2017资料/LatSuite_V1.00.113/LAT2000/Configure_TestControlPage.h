#pragma once


// CConfigure_TestControlPage 对话框

class CConfigure_TestControlPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CConfigure_TestControlPage)

public:
	CConfigure_TestControlPage();
	virtual ~CConfigure_TestControlPage();

// 对话框数据
	enum { IDD = IDD_CONFIGUE_TESTCONTROL_PAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    BOOL m_bDynamometer;
    BOOL m_bTestChannelController;
    BOOL m_bSpectrometer;
    BOOL m_bStandardSupply;
    BOOL m_bTestSupply;
    BOOL m_bLineController;
    BOOL m_bThunderRelay;   

    CString m_strDynamometerCOM;
    CString m_strTestChannelControllerCOM;
    CString m_strStandardSupplyCOM;
    CString m_strTestSupplyCOM;
    CString m_strLineControllerCOM;
    CString m_strThunderRelayCOM;
    CString m_strAgePowerCOM[2];

    int m_iDPSTypeIndex;
    int m_iPFType;
    afx_msg void OnBnClickedButtonStandard();
    afx_msg void OnBnClickedButtonTestPower();
    afx_msg void OnBnClickedButtonIntellectController();
    afx_msg void OnBnClickedButtonSpectrometer();
    afx_msg void OnBnClickedButtonDynamometer();
    afx_msg void OnBnClickedButtonThunderRelay();
    afx_msg void OnBnClickedButtonLineControl();
    virtual BOOL OnInitDialog();
    afx_msg void OnCbnSelchangeComboTestPfType();
    int m_iStandardSupplyType;
    afx_msg void OnBnClickedButtonAgepower1();
    afx_msg void OnBnClickedButtonAgepower2();
    BOOL m_bfor4A;
	int m_iTestChannelControlerType;
	afx_msg void OnBnClickedButtonTestPower2();
	int m_iMyLastPowerType;
	BOOL m_bHaveMyLast;
	CString m_strMyLastCOM;
	afx_msg void OnBnClickedButtonSaftNyy();
	afx_msg void OnBnClickedButtonSaftJydz();
	afx_msg void OnBnClickedButtonSaftXldl();
	BOOL m_bHaveSaft_NYY;
	BOOL m_bHaveSaft_JYDZ;
	BOOL m_bHaveSaft_XLDL;
	int m_iTypeSaftNyy;
	int m_iTypeSaftJydz;
	int m_iTypeSaftXLDL;
	CString m_strSaftNyyCOM;
	CString m_strSaftJydzCOM;
	CString m_strSaftXLDLCOM;
	afx_msg void OnBnClickedButtonSaftNyy2();
	afx_msg void OnBnClickedButtonSaftNyy3();
	afx_msg void OnBnClickedButtonSaftNyy4();
	CString m_strComNyy2;
	CString m_strComJydz2;
	CString m_strComXldl2;
};
