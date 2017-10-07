#pragma once
#include "ilabelx1.h"

// CWarningYesNODlg 对话框

class CWarningYesNODlg : public CDialogEx
{
	DECLARE_DYNAMIC(CWarningYesNODlg)

public:
	CWarningYesNODlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CWarningYesNODlg();

// 对话框数据
	enum { IDD = IDD_WARNING_YESNO };
	CString m_strInfo;
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
private:
	CFont m_font;
};
