#pragma once


// CDlgDebugSaft �Ի���

class CDlgDebugSaft : public CPropertyPage
{
	DECLARE_DYNAMIC(CDlgDebugSaft)

public:
	CDlgDebugSaft();
	virtual ~CDlgDebugSaft();

// �Ի�������
	enum { IDD = IDD_DEBUG_PAGE_SAFT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonSetpara();
	afx_msg void OnBnClickedButtonStart1();
	afx_msg void OnBnClickedButtonReadpara();
	afx_msg void OnBnClickedButtonSetpara2();
	afx_msg void OnBnClickedButtonStart2();
	afx_msg void OnBnClickedButtonDicharge();
	CString m_strCOM;
};
