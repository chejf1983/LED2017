#pragma once


// CDebugPF2010APage 对话框

class CDebugPF2010APage : public CPropertyPage
{
	DECLARE_DYNAMIC(CDebugPF2010APage)

public:
	CDebugPF2010APage();
	virtual ~CDebugPF2010APage();

// 对话框数据
	enum { IDD = IDD_DEBUG_PAGE_PF2010A };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_strCOM;
	CString m_strTypeName;
	CComboBox m_cTypeList;
	float m_fPower;
	float m_fCurrent;
	float m_fPowerFactor;
	float m_fVoltage;
	afx_msg void OnBnClickedButtonRead();
	virtual BOOL OnInitDialog();
	int m_iRangeCF;
	int m_iRangeI;
	int m_iRangeU;
	afx_msg void OnBnClickedButtonSet();
    afx_msg void OnCbnSelchangeComboCf();
    CComboBox m_cRangeI;
    CComboBox m_cRangeV;
};
