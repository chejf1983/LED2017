#pragma once


// CStandardLampSettingsDlg 对话框

class CStandardLampSettingsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CStandardLampSettingsDlg)

public:
	CStandardLampSettingsDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CStandardLampSettingsDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_STANDARD_LAMP_SETTINGS};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	float m_fCurrent;
	float m_fProtectVoltage;
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonOff();
};
