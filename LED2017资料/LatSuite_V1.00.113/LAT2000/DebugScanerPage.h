#pragma once
#include "afxwin.h"


// CDebugScanerPage �Ի���

class CDebugScanerPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CDebugScanerPage)

public:
	CDebugScanerPage();
	virtual ~CDebugScanerPage();

// �Ի�������
	enum { IDD = IDD_DEBUG_PAGE_SCANER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    CString m_strCOM;
    afx_msg void OnCbnSelchangeComboCom();
    afx_msg void OnBnClickedButtonStartScaner();
    afx_msg void OnBnClickedButtonStopScaner();
private:
    static UINT  ThreadScaner(LPVOID par);
    BOOL m_bStopScaner;
public:
    virtual BOOL OnInitDialog();
    CListBox m_cScaner;
    int m_iNum;
	afx_msg void OnBnClickedButton1();
};
