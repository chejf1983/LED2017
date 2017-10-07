#pragma once


// CDebugDPSPage 对话框

class CDebugDPSPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CDebugDPSPage)

public:
	CDebugDPSPage();
	virtual ~CDebugDPSPage();

// 对话框数据
	enum { IDD = IDD_DEBUG_PAGE_DPS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_strCOM;
	int m_iRangeU;
	float m_fCurrentRead;
	float m_fVoltageRead;
	float m_fVoltageSet;
	afx_msg void OnBnClickedButtonRead();
	float m_fFrequencySet;
	float m_fFrequencyRead;
	afx_msg void OnBnClickedButtonOutput();
	afx_msg void OnBnClickedButtonReset();
	afx_msg void OnBnClickedButtonSet();
	afx_msg void OnBnClickedButtonSet2();
	virtual BOOL OnInitDialog();
};
