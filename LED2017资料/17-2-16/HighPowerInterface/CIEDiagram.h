#if !defined(AFX_CIEDIAGRAM_H__E5CE98B4_A01D_4A77_8BDD_E8C4543A9839__INCLUDED_)
#define AFX_CIEDIAGRAM_H__E5CE98B4_A01D_4A77_8BDD_E8C4543A9839__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CIEDiagram.h : header file
//

#include "resFile\ResizingDialog\ResizingDialog.h"
/////////////////////////////////////////////////////////////////////////////
// CCIEDiagram dialog

class CCIEDiagram : public CResizingDialog
{
// Construction
public:
	CCIEDiagram(CWnd* pParent = NULL);   // standard constructor
	BOOL MoveWindowBig();
	BOOL MoveWindowSmall();
	int width;
	int unit;
	CWnd *pWnd_picture; 
	CDC *pDC_picture;
	RECT rect; 
	CPoint standard;
	CPoint getpoint[3];

	void InitPictureParam();
	void enlarge(double staPointX, double staPointY);
	void smaller(double staPointX, double staPointY);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	void DrawPic();
// Dialog Data
	//{{AFX_DATA(CCIEDiagram)
	enum { IDD = IDD_CIEDiagram };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCIEDiagram)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCIEDiagram)
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnCIEPicture();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CIEDIAGRAM_H__E5CE98B4_A01D_4A77_8BDD_E8C4543A9839__INCLUDED_)
