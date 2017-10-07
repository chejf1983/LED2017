#pragma once


// CDlgCurrentBroad 对话框

class CDlgCurrentBroad : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgCurrentBroad)

public:
	CDlgCurrentBroad(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgCurrentBroad();

// 对话框数据
	enum { IDD = IDD_DIALOG_CURRENT_BOARD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_iTestStartLEDID;
	int m_iCurrentBroadID;
	afx_msg void OnBnClickedOk();
	int m_iTolBroadNum;
};
