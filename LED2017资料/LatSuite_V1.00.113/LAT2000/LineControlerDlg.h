#pragma once


// CLineControlerDlg 对话框

class CLineControlerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLineControlerDlg)

public:
	CLineControlerDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLineControlerDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_LINE_CONTROLER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    BOOL m_bStopMoveOneStep;
private:
    static UINT ThreadLineControlerMoveOneStep(LPVOID lPar);
public:
    afx_msg void OnBnClickedButtonContinueMoveOnesetp();
    afx_msg void OnBnClickedCancel();
    afx_msg void OnBnClickedButtonStopMoveOnesetp();
    afx_msg void OnBnClickedButtonContinueMove();
    afx_msg void OnBnClickedButtonSeopMove();
    void EnableButton();
    virtual BOOL OnInitDialog();
	int m_iSleepTimems;
};
