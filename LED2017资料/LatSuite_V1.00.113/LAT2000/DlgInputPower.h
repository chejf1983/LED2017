#pragma once


// CDlgInputPower �Ի���

class CDlgInputPower : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgInputPower)

public:
	CDlgInputPower(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgInputPower();

// �Ի�������
	enum { IDD = IDD_DIALOG_INPUT_POWER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
//	float m_fInputVol;
	float m_fInputCurr;
	float m_fInputPF;
	float m_fInputPower;
	float m_fInputVol;
	afx_msg void OnBnClickedOk();
};
