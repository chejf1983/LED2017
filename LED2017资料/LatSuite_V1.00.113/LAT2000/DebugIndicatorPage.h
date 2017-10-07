#pragma once


// CDebugIndicatorPage �Ի���

class CDebugIndicatorPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CDebugIndicatorPage)

public:
	CDebugIndicatorPage();
	virtual ~CDebugIndicatorPage();

// �Ի�������
	enum { IDD = IDD_DEBUG_PAGE_INDICATOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_strBaudrate;
	CString m_strCOM;
	int m_iState;
	int m_iChannel;
	BYTE m_ucAddress;
	afx_msg void OnBnClickedButtonRed();
	afx_msg void OnBnClickedButtonGreen();
	afx_msg void OnBnClickedButtonOff();
	afx_msg void OnBnClickedButtonSetOne();
	virtual BOOL OnInitDialog();
};
