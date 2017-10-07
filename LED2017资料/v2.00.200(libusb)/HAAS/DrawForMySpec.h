#if !defined(AFX_DRAWFORMYSPEC_H__E51CB5E1_93FB_11DB_949D_00055D02EEF1__INCLUDED_)
#define AFX_DRAWFORMYSPEC_H__E51CB5E1_93FB_11DB_949D_00055D02EEF1__INCLUDED_

#include "SpectData.h"
#include "WhiteZone.h"


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DrawForMySpec.h : header file
//

#define   CO_BK  RGB(0,128,255)

/////////////////////////////////////////////////////////////////////////////
// CDrawForMySpec window
typedef struct tag_debug_draw
{
	int  iCurSele;
	float fCurSele;
	BOOL bMouse;
	CPoint pt;

	BOOL bSetZ;
	int  X1;
	int  X2;
} DEBUG_DRAW;

class CDrawForMySpec : public CStatic
{
// Construction
public:
	CDrawForMySpec();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawForMySpec)
	//}}AFX_VIRTUAL

// Implementation
public:
	void GetRGB(float fSpect, int &R, int &G, int &B);
	float m_fWL[501];
	float m_fPL[100][501];
	void DrawMyDebug_2();
	void DrawBk(COLORREF RgbColor);

	void DrawC(COLORREF RgbColor);
	void DrawZONE(CWhiteZone &xyZone, int iSele);

	void DrawSpect(CSpectData &spData, DATA_DRAW &drawData, CString strNote,BOOL bShow=FALSE);
	void DrawSpectBW(CSpectData &spData, DATA_DRAW &drawData, CString strNote,BOOL bShow=FALSE);
	void DrawSDCM(CSpectData &spData, int iSeleK, int iSDCM1, int iSDCM2);
	void DrawData(CSpectData &spData);

	void DrawMyDebug(float fAD[], int iN,BOOL bLine,DEBUG_DRAW &draw,float fHalf=0);

	virtual ~CDrawForMySpec();

	// Generated message map functions
protected:
	int m_nClientWidth;
	int m_nClientHeight;
	
	CRect m_rectPlot;
	CDC m_dcPlot;

	CBitmap *m_pbitmapOldPlot;
	CBitmap m_bitmapPlot;
	//{{AFX_MSG(CDrawForMySpec)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAWFORMYSPEC_H__E51CB5E1_93FB_11DB_949D_00055D02EEF1__INCLUDED_)
