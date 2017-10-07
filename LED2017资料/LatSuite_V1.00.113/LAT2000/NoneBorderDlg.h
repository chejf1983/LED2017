#pragma once
#include "ilabelx1.h"


// CNoneBorderDlg 对话框

class CNoneBorderDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CNoneBorderDlg)

public:
	CNoneBorderDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CNoneBorderDlg();


// 对话框数据
	enum { IDD = IDD_NONE_BORDER_MESSAGEBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	CFont m_font;
	CIlabelx1 m_cLabelXInfo;

public:
	virtual BOOL OnInitDialog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBnClickedOk();
	CString m_strInfo;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	BOOL m_bIgnoreSame;
};
