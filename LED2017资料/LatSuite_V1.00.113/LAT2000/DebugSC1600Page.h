#pragma once


// CDebugSC1600Page 对话框

class CDebugSC1600Page : public CPropertyPage
{
	DECLARE_DYNAMIC(CDebugSC1600Page)

public:
	CDebugSC1600Page();
	virtual ~CDebugSC1600Page();

// 对话框数据
	enum { IDD = IDD_DEBUG_PAGE_SC1600 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_bC1;
	BOOL m_bC10;
	BOOL m_bC11;
	BOOL m_bC12;
	BOOL m_bC13;
	BOOL m_bC14;
	BOOL m_bC15;
	BOOL m_bC16;
	BOOL m_bC2;
	BOOL m_bC3;
	BOOL m_bC4;
	BOOL m_bC5;
	BOOL m_bC6;
	BOOL m_bC7;
	BOOL m_bC8;
	BOOL m_bC9;
	CString m_strBaudrate;
	CString m_strCOM;
	BYTE m_ucAddress;
	afx_msg void OnBnClickedButtonSet();
	afx_msg void OnBnClickedButtonQuitRemote();
	afx_msg void OnBnClickedButtonRead();
	afx_msg void OnBnClickedButtonBuzzerOn();
	afx_msg void OnBnClickedButtonBuzzerOff();
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonTmpStart();
	afx_msg void OnBnClickedButtonTmpStop();
	afx_msg void OnBnClickedButtonCloseAll();
	virtual BOOL OnInitDialog();
};
