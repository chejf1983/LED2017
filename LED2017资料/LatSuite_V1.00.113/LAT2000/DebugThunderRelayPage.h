#pragma once
#include "LAT2000.h"


// CDebugThunderRelayPage 对话框

class CDebugThunderRelayPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CDebugThunderRelayPage)

public:
	CDebugThunderRelayPage();
	virtual ~CDebugThunderRelayPage();

// 对话框数据
	enum { IDD = IDD_DEBUG_PAGE_THUNDER_RELAY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_bChannel1;
	BOOL m_bChannel2;
	BOOL m_bChannel10;
	BOOL m_bChannel3;
	BOOL m_bChannel4;
	BOOL m_bChannel5;
	BOOL m_bChannel6;
	BOOL m_bChannel7;
	BOOL m_bChannel8;
	BOOL m_bChannel9;
	CString m_strBaudRage;
	CString m_strCOM;
	CString m_strAddress;
	afx_msg void OnBnClickedButtonSet();
	virtual BOOL OnInitDialog();
};
