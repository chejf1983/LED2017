#pragma once


// CInputPasswordDlg �Ի���

class CInputPasswordDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInputPasswordDlg)

public:
	CInputPasswordDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInputPasswordDlg();

// �Ի�������
	enum { IDD = IDD_INPUT_PASSWORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString m_strPassword;
};
