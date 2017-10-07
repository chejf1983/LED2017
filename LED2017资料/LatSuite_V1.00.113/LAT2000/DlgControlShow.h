#pragma once


// CDlgControlShow 对话框

class CDlgControlShow : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgControlShow)

public:
	CDlgControlShow(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgControlShow();

// 对话框数据
	enum { IDD = IDD_DIALOG_SELE_CONTROL_SHOW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	
	DECLARE_MESSAGE_MAP()
public:
	int m_iSeleControl;
};
