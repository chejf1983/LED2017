#pragma once


// CBurnInSettingsDlg �Ի���

class CBurnInSettingsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBurnInSettingsDlg)

public:
	CBurnInSettingsDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBurnInSettingsDlg();

// �Ի�������
	enum { IDD = IDD_BURN_IN_SETTINGS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_iOFFSeconds;
	int m_iONSeconds;
//	int m_iRunTimes;
	void EnaleControls_bDisor_LowExecu();
	virtual BOOL OnInitDialog();
};
