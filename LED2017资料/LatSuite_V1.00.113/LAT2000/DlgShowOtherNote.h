#pragma once


// CDlgShowOtherNote 对话框

class CDlgShowOtherNote : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgShowOtherNote)

public:
	CDlgShowOtherNote(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgShowOtherNote();

// 对话框数据
	enum { IDD = IDD_DIALOG_SHOW_OTHERNOTE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CString m_strDot;
	void SetNote(CString strNote, int iTimes);
	CString m_strNote;
	CFont m_font;
	int m_iTimems;
	int m_iStartTimes;
	virtual BOOL OnInitDialog();
};
