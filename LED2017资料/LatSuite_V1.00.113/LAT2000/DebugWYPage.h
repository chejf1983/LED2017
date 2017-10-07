#pragma once


// CDebugWYPage 对话框

class CDebugWYPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CDebugWYPage)

public:
	CDebugWYPage();
	virtual ~CDebugWYPage();

// 对话框数据
	enum { IDD = IDD_DEBUG_PAGE_WY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonRead();
	CString m_strCOM;
	float m_fVoltage;
	float m_fCurrent;
	float m_fProtectCurrent;
	float m_fVoltageSet;
	afx_msg void OnBnClickedButtonOutput();
	virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedOutputHls200();
    afx_msg void OnBnClickedResetHls200();
    afx_msg void OnBnClickedButtonReadState();
	afx_msg void OnBnClickedButtonSet();
	float m_fCurr;
};
