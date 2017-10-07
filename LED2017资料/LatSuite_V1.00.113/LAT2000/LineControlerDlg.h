#pragma once


// CLineControlerDlg �Ի���

class CLineControlerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLineControlerDlg)

public:
	CLineControlerDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLineControlerDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_LINE_CONTROLER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
