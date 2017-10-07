#pragma once


// CDlgSaftSetup 对话框

class CDlgSaftSetup : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSaftSetup)

public:
	CDlgSaftSetup(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSaftSetup();

// 对话框数据
	enum { IDD = IDD_DIALOG_SAFT_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	int m_iDebugType;

	float m_fSetVolNYY;
	float m_fSetTimeNYY;
	float m_fNYYLimit;
	float m_fSetVolJYDZ;
	float m_fSetTimeJYDZ;
	float m_fJYDZLimit;
	float m_fSetVolXLDL;
	float m_fSetTimeXLDL;
	float m_fXLDLLimit;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	int m_iTypeNYY;
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	CString m_strSetVolJYDZ;
	afx_msg void OnBnClickedButton17();
	afx_msg void OnBnClickedButton18();
	afx_msg void OnBnClickedButton19();
};
