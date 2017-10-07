#pragma once
#include "afxcmn.h"


// CDlgMyLastSet 对话框

class CDlgMyLastSet : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgMyLastSet)

public:
	CDlgMyLastSet(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgMyLastSet();

// 对话框数据
	enum { IDD = IDD_DIALOG_MY_LAST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonDel();
	afx_msg void OnBnClickedOk();

	
	float m_fCurVolMyLast;
	int m_iCurTimeMyLast;
	int m_iCurSele; //当前选择的

	CArray<float, float> m_fVolMyLastList;
	CArray<float, float> m_fFreqMyLastList;
	CArray<int, int> m_iTimeMyLastList;

	afx_msg void OnItemchangedListLimit(NMHDR *pNMHDR, LRESULT *pResult);
	void ReList();
	CListCtrl m_cList;
	float m_fCurFreqMyLast;
	afx_msg void OnBnClickedButton2();
};
