#pragma once
#include "ilabelx1.h"

// CWarningYesNODlg �Ի���

class CWarningYesNODlg : public CDialogEx
{
	DECLARE_DYNAMIC(CWarningYesNODlg)

public:
	CWarningYesNODlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWarningYesNODlg();

// �Ի�������
	enum { IDD = IDD_WARNING_YESNO };
	CString m_strInfo;
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
private:
	CFont m_font;
};
