#pragma once


// CDlgCurrentBroad �Ի���

class CDlgCurrentBroad : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgCurrentBroad)

public:
	CDlgCurrentBroad(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgCurrentBroad();

// �Ի�������
	enum { IDD = IDD_DIALOG_CURRENT_BOARD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_iTestStartLEDID;
	int m_iCurrentBroadID;
	afx_msg void OnBnClickedOk();
	int m_iTolBroadNum;
};
