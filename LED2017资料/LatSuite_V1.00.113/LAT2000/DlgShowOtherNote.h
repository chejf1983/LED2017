#pragma once


// CDlgShowOtherNote �Ի���

class CDlgShowOtherNote : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgShowOtherNote)

public:
	CDlgShowOtherNote(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgShowOtherNote();

// �Ի�������
	enum { IDD = IDD_DIALOG_SHOW_OTHERNOTE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
