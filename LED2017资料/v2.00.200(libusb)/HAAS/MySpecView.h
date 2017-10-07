// MySpecView.h : interface of the CMySpecView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYSPECVIEW_H__799E038C_8CF0_11DB_949D_00055D02EEF1__INCLUDED_)
#define AFX_MYSPECVIEW_H__799E038C_8CF0_11DB_949D_00055D02EEF1__INCLUDED_

////////////////////////////////////////////////////////////////////////////////
#include "MySpecDoc.h"

#include <AfxMT.h>

#include "HAAS_Pipe_Def.h"
#include "SortListCtrl.h"
////////////////////////////////////////////////////////////////////////////////

#define  WM_PC2_PRO          (WM_USER + 0x401)

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//打印标志
#define     PRINT_TYPE_MAIN       0
#define     PRINT_TYPE_CURVE      1
#define     PRINT_TYPE_SPECT      2
#define     PRINT_TYPE_CURVE_T    3  //时间变化曲线
#define     PRINT_TYPE_TR	      4


class CMySpecView : public CListView
{
protected: // create from serialization only
	CMySpecView();
	DECLARE_DYNCREATE(CMySpecView)

// Attributes
public:
	CMySpecDoc* GetDocument();

// Operations
public:
	CArray<int,int> m_arra_iPrintSele;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMySpecView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:

	BOOL  m_bRemoteAutoIntTime;
	float m_fRemoteIntTime;
	int   m_iRemoteSeleViewAngle;
	int   m_iRemoteGainRange;

	HANDLE m_hEvents;
	BOOL m_bSetStop;
	int m_iCurrRead;

	CEvent m_EventTest;
	static BOOL   m_bPC2Mode;
	int    m_iTestResult;

	static UINT Thread_NamePipe(LPVOID pParam);
	void NamePipe();

	CMySpecDoc *m_pDoc;
	float m_fIf;
	float m_fVf;

	void SHOW_DATA();
	void EnableShow(BOOL bStart);

	CString AddNumber(CString strNumber);
	BOOL Test();

	BOOL m_bAllSele;
	int m_iNumTMP;
	int m_iPerSig;  //前一次的信号选择 DC 50 60
	int m_iPerInt;  //前一次的积分时间
	int m_iPerBin;  //前一次的灵敏度
	int m_iCur;
	int m_iPerCur;  //前一次的序号

	//打印标志
	int m_iPrintType;
	int m_iPrintTableB;
	int m_iPrintLineN;

	virtual ~CMySpecView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	//{{AFX_MSG(CMySpecView)
	afx_msg void OnCustomdrawMyList ( NMHDR* pNMHDR, LRESULT* pResult );
	afx_msg void OnWMTestStart(UINT wParam, LONG lParam);//add
	afx_msg void OnWM_Update(UINT wParam, LONG lParam);//add
	afx_msg void OnWMReHead(UINT wParam, LONG lParam);//add
	afx_msg void OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTestInfo();
	afx_msg void OnUpdateTestInfo(CCmdUI* pCmdUI);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnAllSele();
	afx_msg void OnUpdateAllSele(CCmdUI* pCmdUI);
	afx_msg void OnPower();
	afx_msg void OnUpdatePower(CCmdUI* pCmdUI);
	afx_msg void OnModeInttime();
	afx_msg void OnUpdateModeInttime(CCmdUI* pCmdUI);
	afx_msg void OnWM_PC2_Pro(UINT wParam, LONG lParam);
	afx_msg void OnDelete();
	afx_msg void OnUpdateDelete(CCmdUI* pCmdUI);
	afx_msg void OnEditCopyTxt1();
	afx_msg void OnUpdateEditCopyTxt1(CCmdUI* pCmdUI);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	static BOOL CommPh(void *p, float &fPh);
	BOOL m_bFir;
	CImageList m_SmallImageList;
};

#ifndef _DEBUG  // debug version in MySpecView.cpp
inline CMySpecDoc* CMySpecView::GetDocument()
   { return (CMySpecDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSPECVIEW_H__799E038C_8CF0_11DB_949D_00055D02EEF1__INCLUDED_)
