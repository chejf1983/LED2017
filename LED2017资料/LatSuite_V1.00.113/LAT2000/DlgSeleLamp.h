#pragma once


// CDlgSeleLamp �Ի���

class CDlgSeleLamp : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSeleLamp)

public:
	CDlgSeleLamp(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSeleLamp();

// �Ի�������
	enum { IDD = IDD_DIALOG_SELE_LAMP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	int m_iSeleTestLamp;
};
