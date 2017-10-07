#pragma once


// CDlgInputPower 对话框

class CDlgInputPower : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgInputPower)

public:
	CDlgInputPower(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgInputPower();

// 对话框数据
	enum { IDD = IDD_DIALOG_INPUT_POWER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
//	float m_fInputVol;
	float m_fInputCurr;
	float m_fInputPF;
	float m_fInputPower;
	float m_fInputVol;
	afx_msg void OnBnClickedOk();
};
