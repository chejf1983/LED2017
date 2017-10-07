#pragma once


// CDlgShowOldingTime 对话框

class CDlgShowOldingTime : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgShowOldingTime)

public:
	CDlgShowOldingTime(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgShowOldingTime();

// 对话框数据
	enum { IDD = IDD_DIALOG_SHOW_OLDING_STATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    CString m_strDot;
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    float m_fOldTimes;
    int m_iStartTimes;
    CFont m_font;
    void Init(float fOldTimes);
};
