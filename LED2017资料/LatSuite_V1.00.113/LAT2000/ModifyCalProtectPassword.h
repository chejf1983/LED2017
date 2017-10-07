#pragma once


// CModifyCalProtectPassword 对话框

class CModifyCalProtectPassword : public CDialogEx
{
	DECLARE_DYNAMIC(CModifyCalProtectPassword)

public:
	CModifyCalProtectPassword(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CModifyCalProtectPassword();

// 对话框数据
	enum { IDD = IDD_MODIFY_PROTECT_PASSWORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_strNewPassword1;
	CString m_strNewPassword2;
	CString m_strOldPassword;
	afx_msg void OnBnClickedOk();
};
