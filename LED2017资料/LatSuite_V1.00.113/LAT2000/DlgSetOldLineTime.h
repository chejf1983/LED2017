#pragma once


// CDlgSetOldLineTime �Ի���

class CDlgSetOldLineTime : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSetOldLineTime)

public:
	CDlgSetOldLineTime(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSetOldLineTime();

// �Ի�������
	enum { IDD = IDD_DIALOG_PRATIME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	float m_fOldLineT_Times;
};
