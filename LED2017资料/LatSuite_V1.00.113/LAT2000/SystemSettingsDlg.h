#pragma once
#include "_grid.h"


// CSystemSettingsDlg 对话框

class CSystemSettingsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSystemSettingsDlg)

public:
	CSystemSettingsDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSystemSettingsDlg();

public:

// 对话框数据
	enum { IDD = IDD_SYSTEM_SETTINGS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();

	virtual BOOL OnInitDialog();
	CString m_strFileDataNum;
	CString m_strFileName;
	BOOL m_bAutoSave;
	afx_msg void OnBnClickedRadioAutoSave1();
	afx_msg void OnBnClickedRadioAutoSave2();
	BOOL m_bLineNotMove;
	afx_msg void OnBnClickedButtonScan();
	CString m_strFilePath;
    int m_iSaveType;
    int m_iPrefixInputMode;
    afx_msg void OnBnClickedRadioNum();
    afx_msg void OnBnClickedRadioDay();
    afx_msg void OnBnClickedRadioManuInput();
    afx_msg void OnBnClickedRadioManuInput2();
    BOOL m_bDemo;
	BOOL m_bInputPower;
};
