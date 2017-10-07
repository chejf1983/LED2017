#pragma once


// CAlarmRingEditDlg �Ի���

class CAlarmRingEditDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAlarmRingEditDlg)

public:
	CAlarmRingEditDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAlarmRingEditDlg();

	void RelistRing();

// �Ի�������
	enum { IDD = IDD_RING_EDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_iOFFTimems;
	int m_iRingONTimems;
	int m_iRingNumber;
	CListBox m_cRingListBox;
	afx_msg void OnBnClickedButtonAdd();
	CString m_strName;
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnBnClickedButtonModify();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnLbnSelchangeListRing();
};
