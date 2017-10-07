#pragma once


// CBurnInSettingsDlg 对话框

class CBurnInSettingsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBurnInSettingsDlg)

public:
	CBurnInSettingsDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBurnInSettingsDlg();

// 对话框数据
	enum { IDD = IDD_BURN_IN_SETTINGS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_iOFFSeconds;
	int m_iONSeconds;
//	int m_iRunTimes;
	void EnaleControls_bDisor_LowExecu();
	virtual BOOL OnInitDialog();
};
