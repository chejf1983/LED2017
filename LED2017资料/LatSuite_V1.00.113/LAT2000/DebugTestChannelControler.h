#pragma once


// CDebugTestChannelControler �Ի���

class CDebugTestChannelControler : public CPropertyPage
{
	DECLARE_DYNAMIC(CDebugTestChannelControler)

public:
	CDebugTestChannelControler();
	virtual ~CDebugTestChannelControler();

// �Ի�������
	enum { IDD = IDD_PAGE_TESTCHANNEL_CONTROLLER };

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
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonSet();
};
