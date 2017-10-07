#pragma once


// CDebugGaugePage 对话框

class CDebugGaugePage : public CPropertyPage
{
	DECLARE_DYNAMIC(CDebugGaugePage)

public:
	CDebugGaugePage();
	virtual ~CDebugGaugePage();

// 对话框数据
	enum { IDD = IDD_DEBUG_PAGE_GAUGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_strBaudrate;
	CString m_strCOM;
	BYTE m_ucAddress;
	float m_fCurrentA;
	float m_fPowerW;
	float m_fVoltageV;
	afx_msg void OnBnClickedButtonRead();
	virtual BOOL OnInitDialog();
};
