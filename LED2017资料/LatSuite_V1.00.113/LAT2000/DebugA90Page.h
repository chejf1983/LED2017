#pragma once
#include "afxwin.h"


// CDebugA90Page �Ի���

class CDebugA90Page : public CPropertyPage
{
	DECLARE_DYNAMIC(CDebugA90Page)

public:
	CDebugA90Page();
	virtual ~CDebugA90Page();

// �Ի�������
	enum { IDD = IDD_DEBUG_PAGE_A90 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedButtonSample();
	int m_iIntegralTimems;
	CStatic m_cSDCM;
	virtual BOOL OnInitDialog();
};
