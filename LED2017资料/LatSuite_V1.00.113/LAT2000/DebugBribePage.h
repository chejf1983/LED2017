#pragma once


// CDebugBribePage �Ի���

class CDebugBribePage : public CPropertyPage
{
	DECLARE_DYNAMIC(CDebugBribePage)

public:
	CDebugBribePage();
	virtual ~CDebugBribePage();

// �Ի�������
	enum { IDD = IDD_DEBUG_PAGE_RIVETER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    CString m_strCOM;
    CString m_strAddress;
    int	 m_iBaudRate;
    BOOL m_bChannel1;
    BOOL m_bChannel10;
    BOOL m_bChannel2;
    BOOL m_bChannel3;
    BOOL m_bChannel4;
    BOOL m_bChannel5;
    BOOL m_bChannel6;
    BOOL m_bChannel7;
    BOOL m_bChannel8;
    BOOL m_bChannel9;
    afx_msg void OnBnClickedButtonSet();
	virtual BOOL OnInitDialog();
};
