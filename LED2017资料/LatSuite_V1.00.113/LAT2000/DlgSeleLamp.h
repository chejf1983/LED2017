#pragma once


// CDlgSeleLamp 对话框

class CDlgSeleLamp : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSeleLamp)

public:
	CDlgSeleLamp(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSeleLamp();

// 对话框数据
	enum { IDD = IDD_DIALOG_SELE_LAMP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	int m_iSeleTestLamp;
};
