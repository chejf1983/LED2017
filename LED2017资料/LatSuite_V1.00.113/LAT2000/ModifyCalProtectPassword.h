#pragma once


// CModifyCalProtectPassword �Ի���

class CModifyCalProtectPassword : public CDialogEx
{
	DECLARE_DYNAMIC(CModifyCalProtectPassword)

public:
	CModifyCalProtectPassword(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CModifyCalProtectPassword();

// �Ի�������
	enum { IDD = IDD_MODIFY_PROTECT_PASSWORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_strNewPassword1;
	CString m_strNewPassword2;
	CString m_strOldPassword;
	afx_msg void OnBnClickedOk();
};
