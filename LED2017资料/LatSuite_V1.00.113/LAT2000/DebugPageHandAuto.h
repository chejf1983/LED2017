#pragma once


// CDebugPageHandAuto 对话框

class CDebugPageHandAuto : public CPropertyPage
{
	DECLARE_DYNAMIC(CDebugPageHandAuto)

public:
	CDebugPageHandAuto();
	virtual ~CDebugPageHandAuto();

// 对话框数据
	enum { IDD = IDD_DEBUG_PAGE_LINE_HAND_AUTO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString m_strCOM;
	afx_msg void OnBnClickedButtonBuzzerOff();
	afx_msg void OnBnClickedButtonMove();
	afx_msg void OnBnClickedButtonGetLineState();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButtonLinestop();
	afx_msg void OnBnClickedButtonSet();

	int m_iChannel1;
	int m_iChannel10;
	int m_iChannel9;
	int m_iChannel8;
	int m_iChannel7;
	int m_iChannel6;
	int m_iChannel5;
	int m_iChannel4;
	int m_iChannel3;
	int m_iChannel2;
};
