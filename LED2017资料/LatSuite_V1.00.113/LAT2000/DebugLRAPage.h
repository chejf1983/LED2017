#pragma once


// CDebugLRAPage 对话框

class CDebugLRAPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CDebugLRAPage)

public:
	CDebugLRAPage();
	virtual ~CDebugLRAPage();

// 对话框数据
	enum { IDD = IDD_DEBUG_PAGE_LRA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_strCOM;
	CString m_strAddress;
	int	 m_iBaudRate;
	BOOL m_bChannel1;
	BOOL m_bChannel10;
	BOOL m_bChannel2;
	BOOL m_bChannel3;
	BOOL m_bChannel4;
	BOOL m_bChannel5;
	BOOL m_bChannel6;
	BOOL m_bChannel7;
	BOOL m_bChannel8;
	BOOL m_bChannel9;
	afx_msg void OnBnClickedButtonSet();
	virtual BOOL OnInitDialog();
};
