#pragma once
#include "ilabelx1.h"


// CAccountDlg �Ի���

class CAccountDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAccountDlg)

public:
	CAccountDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAccountDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_ACCOUNT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    int m_iExecutionLevel;
    CString m_strAdminExcutionPassword;
    CString m_strHighExcutionPassword;
    afx_msg void OnBnClickedOk();
    CIlabelx1 m_iLabel;
    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedHighExecutionLevel();
    afx_msg void OnBnClickedAdminExecutionLevel();
    void Enable(void);
};
