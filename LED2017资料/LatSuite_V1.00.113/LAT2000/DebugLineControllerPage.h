#pragma once


// CDebugLineControllerPage 对话框

class CDebugLineControllerPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CDebugLineControllerPage)

public:
	CDebugLineControllerPage();
	virtual ~CDebugLineControllerPage();

// 对话框数据
	enum { IDD = IDD_DEBUG_PAGE_LINE_CONTROLLER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_strCOM;
	CString m_strAddress;
	CString m_strBaudrate;
	afx_msg void OnBnClickedButtonMove();
	afx_msg void OnBnClickedButtonContinue();
	afx_msg void OnBnClickedButtonLinestop();
	afx_msg void OnBnClickedButtonGetLineState();
	float m_fOffTimeSec;
	float m_fOnTimeSec;
	afx_msg void OnBnClickedButtonOldTime();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonBuzzerOn();
	afx_msg void OnBnClickedButtonBuzzerOff();
};
