#pragma once


// CExitSelectionDlg 对话框

class CExitSelectionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CExitSelectionDlg)

public:
	CExitSelectionDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CExitSelectionDlg();

// 对话框数据
	enum { IDD = IDD_EXIT_SELECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_bResetDPS;
	BOOL m_bDPSEnable;
	BOOL m_bResetTMPController;
	BOOL m_bTMPControllerEnable;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedSaveFile();
	afx_msg void OnBnClickedOk();
};
