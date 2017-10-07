#pragma once


// CConfigure_AssistantPage 对话框

class CConfigure_AssistantPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CConfigure_AssistantPage)

public:
	CConfigure_AssistantPage();
	virtual ~CConfigure_AssistantPage();

// 对话框数据
	enum { IDD = IDD_CONFIGUE_ASSISTANT_PAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_bHaveScaner;
	CString m_strScanerCOM;

	BOOL	m_bHaveHandAuto;
	CString m_strHandAutoCOM;
	CString m_strHandAutoRange1;
	CString m_strHandAutoRange2;

	afx_msg void OnBnClickedButtonScaner();
	afx_msg void OnBnClickedButtonManipulator();

    afx_msg void OnBnClickedCheckScaner();
    afx_msg void OnBnClickedCheckManipulator();
    virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	int m_iDis1;
	int m_iSpeed1;
	int m_iDis2;
	int m_iSpeed2;
	int m_iDis3;
	int m_iSpeed3;
	int m_iDis4;
	int m_iSpeed4;
	int m_iDis5;
	int m_iSpeed5;
	int m_iXMove;
	int m_iZMove;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButtonScaner2();
	CString m_strTouscnComm;

};
