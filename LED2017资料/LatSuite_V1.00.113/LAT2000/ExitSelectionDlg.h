#pragma once


// CExitSelectionDlg �Ի���

class CExitSelectionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CExitSelectionDlg)

public:
	CExitSelectionDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CExitSelectionDlg();

// �Ի�������
	enum { IDD = IDD_EXIT_SELECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
