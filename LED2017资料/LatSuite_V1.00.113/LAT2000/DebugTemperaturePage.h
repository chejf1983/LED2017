#pragma once


// CDebugTemperaturePage 对话框

class CDebugTemperaturePage : public CPropertyPage
{
	DECLARE_DYNAMIC(CDebugTemperaturePage)

public:
	CDebugTemperaturePage();
	virtual ~CDebugTemperaturePage();

// 对话框数据
	enum { IDD = IDD_DEBUG_PAGE_TEMPERATURE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonRead();
	CString m_strBaudrate;
	CString m_strCOM;
	BYTE m_ucAddress;
	float m_fTMPRead;
	float m_fTMPSet;
	float m_fTMPSetH;
	float m_fTMPSetL;
	int m_iAlarm;
	afx_msg void OnBnClickedButtonSet();
	afx_msg void OnBnClickedButtonTmpStop();
    afx_msg void OnBnClickedButtonSelfTurningMode();
    afx_msg void OnBnClickedButtonCalRightPid();
    afx_msg void OnBnClickedButtonReadPidturningMode();
    afx_msg void OnBnClickedButtonReadPid();
    afx_msg void OnBnClickedButtonInit();
	virtual BOOL OnInitDialog();
};
