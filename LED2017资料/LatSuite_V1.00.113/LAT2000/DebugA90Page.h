#pragma once
#include "afxwin.h"


// CDebugA90Page 对话框

class CDebugA90Page : public CPropertyPage
{
	DECLARE_DYNAMIC(CDebugA90Page)

public:
	CDebugA90Page();
	virtual ~CDebugA90Page();

// 对话框数据
	enum { IDD = IDD_DEBUG_PAGE_A90 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedButtonSample();
	int m_iIntegralTimems;
	CStatic m_cSDCM;
	virtual BOOL OnInitDialog();
};
