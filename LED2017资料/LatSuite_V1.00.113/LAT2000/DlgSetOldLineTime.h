#pragma once


// CDlgSetOldLineTime 对话框

class CDlgSetOldLineTime : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSetOldLineTime)

public:
	CDlgSetOldLineTime(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSetOldLineTime();

// 对话框数据
	enum { IDD = IDD_DIALOG_PRATIME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	float m_fOldLineT_Times;
};
