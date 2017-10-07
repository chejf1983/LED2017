#pragma once


// CDebugEMS61000_11KPage 对话框

class CDebugEMS61000_11KPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CDebugEMS61000_11KPage)

public:
	CDebugEMS61000_11KPage();
	virtual ~CDebugEMS61000_11KPage();

// 对话框数据
	enum { IDD = IDD_DEBUG_PAGE_EMS61000_11K };

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
	int m_iTime;
	CString m_strCOM;
	afx_msg void OnBnClickedButtonEutOn();
	afx_msg void OnBnClickedButtonEutOff();
	virtual BOOL OnInitDialog();
};
