#pragma once


// CDlgControlShow �Ի���

class CDlgControlShow : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgControlShow)

public:
	CDlgControlShow(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgControlShow();

// �Ի�������
	enum { IDD = IDD_DIALOG_SELE_CONTROL_SHOW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	
	DECLARE_MESSAGE_MAP()
public:
	int m_iSeleControl;
};
