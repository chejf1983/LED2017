#pragma once


// CDebugEMS61000_5APage 对话框

class CDebugEMS61000_5APage : public CPropertyPage
{
	DECLARE_DYNAMIC(CDebugEMS61000_5APage)

public:
	CDebugEMS61000_5APage();
	virtual ~CDebugEMS61000_5APage();

// 对话框数据
	enum { IDD = IDD_DEBUG_PAGE_EMS61000_5A };

protected:
	int m_iCurSele;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSet();
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonReset();
	afx_msg void OnBnClickedButtonRead();
	CString m_strRe;
	int m_iResult;
	float m_fTime;
	CEdit m_cRe1;
	CString m_strCOM;
	virtual BOOL OnInitDialog();
};
