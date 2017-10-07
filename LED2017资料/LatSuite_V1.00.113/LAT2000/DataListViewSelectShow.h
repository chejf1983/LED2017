#pragma once


// CDataListViewSelectShow 对话框

class CDataListViewSelectShow : public CDialogEx
{
	DECLARE_DYNAMIC(CDataListViewSelectShow)

public:
	CDataListViewSelectShow(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDataListViewSelectShow();

// 对话框数据
	enum { IDD = IDD_DATA_LISTVIEW_SELECT_SHOW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	BOOL m_bFlux;
	BOOL m_bHw;
	BOOL m_bIF;
	BOOL m_bIp;
	BOOL m_bIR;
	BOOL m_bLd;
	BOOL m_bLp;
	BOOL m_bPur;
	BOOL m_bRa;
	BOOL m_bTc;
	BOOL m_bU;
	BOOL m_bV;
	BOOL m_bVF;
	BOOL m_bVR;
	BOOL m_bX;
	BOOL m_bY;
	BOOL m_bEff;
};
