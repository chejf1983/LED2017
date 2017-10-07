#pragma once
#include "ilabelx1.h"


// CNoneBorderDlg �Ի���

class CNoneBorderDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CNoneBorderDlg)

public:
	CNoneBorderDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CNoneBorderDlg();


// �Ի�������
	enum { IDD = IDD_NONE_BORDER_MESSAGEBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
