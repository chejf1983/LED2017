//{{AFX_INCLUDES()
#include "ntgraph.h"
//}}AFX_INCLUDES
#if !defined(AFX_SPECTRUMVIEW_H__E5B2CA50_51A2_44E5_9CCD_8ACCA494ADE6__INCLUDED_)
#define AFX_SPECTRUMVIEW_H__E5B2CA50_51A2_44E5_9CCD_8ACCA494ADE6__INCLUDED_

#include "DrawForMySpec.h"
#include "DataSheet.h"
#include "MySpecDoc.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SpectrumView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSpectrumView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CSpectrumView : public CFormView
{
protected:
	CSpectrumView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CSpectrumView)

// Form Data
public:
	//{{AFX_DATA(CSpectrumView)
	enum { IDD = IDD_SPECTRUM_VIEW };
//	CDrawForPmsLab	m_cSpecDraw;
	CStatic	m_cSheet;
	CNTGraph	m_cNTspec;
	CDrawForMySpec m_cSpecDraw;
	//}}AFX_DATA

// Attributes
public:
	CMySpecDoc* GetDocument();
	DATA_DRAW m_drawData;

// Operations
public:
	int m_iType;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpectrumView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CSpectrumView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CSpectrumView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClickNtgraphctrl();
//	afx_msg void OnSpecBmpCopy();
//	afx_msg void OnUpdateSpecBmpCopy(CCmdUI* pCmdUI);
//	afx_msg void OnShowAd();
//	afx_msg void OnUpdateShowAd(CCmdUI* pCmdUI);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnType1();
//	afx_msg void OnUpdateType1(CCmdUI* pCmdUI);
//	afx_msg void OnType2();
//	afx_msg void OnUpdateType2(CCmdUI* pCmdUI);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bShowAD;
	void ReDraw();
	void SetPos();
	BOOL m_bFir;
	CDataSheet  m_cDataSheet;
};
#ifndef _DEBUG  // debug version in SpectrumView.cpp
inline CMySpecDoc* CSpectrumView::GetDocument()
{ return (CMySpecDoc*)m_pDocument; }
#endif
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPECTRUMVIEW_H__E5B2CA50_51A2_44E5_9CCD_8ACCA494ADE6__INCLUDED_)
