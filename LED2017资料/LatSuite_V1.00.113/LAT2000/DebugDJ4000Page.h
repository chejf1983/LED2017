#pragma once


// CDebugDJ4000Page �Ի���

class CDebugDJ4000Page : public CPropertyPage
{
	DECLARE_DYNAMIC(CDebugDJ4000Page)

public:
	CDebugDJ4000Page();
	virtual ~CDebugDJ4000Page();

// �Ի�������
	enum { IDD = IDD_DEBUG_PAGE_DJ4000 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_strBaudrate;
	CString m_strCOM;
	int m_iOFFSeconds;
	int m_iONSeconds;
	int m_iTimes;
	afx_msg void OnBnClickedButtonSet();
	afx_msg void OnBnClickedButtonRun();
	afx_msg void OnBnClickedButtonStop();
};
