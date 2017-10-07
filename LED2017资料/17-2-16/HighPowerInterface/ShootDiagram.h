#if !defined(AFX_SHOOTDIAGRAM_H__8F64ABDF_713E_4917_AA77_8B6A256311C4__INCLUDED_)
#define AFX_SHOOTDIAGRAM_H__8F64ABDF_713E_4917_AA77_8B6A256311C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ShootDiagram.h : header file
//
#include <Afxtempl.h>
#include "Math.h"
#include "resFile\ResizingDialog\ResizingDialog.h"
#include "resFile\BitButtonNL\BitButtonNL.h"
#include "resFile\ReDrawListCtrl\ComboListCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CShootDiagram dialog
UINT shoot(LPVOID lpParam);
void AddTail(double x, double y);

typedef struct
{
	double x[2];
	double y[2];
	double k;
	double b;
}LineParam;

class CShootDiagram : public CResizingDialog
{
// Construction
public:
	CMenu m_menu;
	CPoint m_vInputPoint[4];  //存放用户输入的点
	CShootDiagram(CWnd* pParent = NULL);   // standard constructor
	CPoint m_cMovePoint; 
	CRect rectdraw;
	int pointnum[3];
	int rectpointnum[3];
	int parallelnum[3];

	CWnd *pWnd_picture; 
	CDC *pDC_picture;
	COLORREF m_color;   //画笔颜色
	RECT rect; 	
	bool drag;
	bool dragRect;
	CPoint downPoint;
	int dragPointNum;

	CPoint ResizeStaPoint;

	bool showCIELine;
	bool newCIERect;

	int CIERectNum;

// Dialog Data
	//{{AFX_DATA(CShootDiagram)
	enum { IDD = IDD_ShootDiagram };
	CButton	m_figureRange;
	CButton	m_showScale;
	CButton	m_ShowCIEPicture;
	CButton	m_parallelDrag;
	CBitButtonNL	m_file;
	CBitButtonNL	m_setColor;
	CBitButtonNL	m_showLevel;
	CBitButtonNL	m_clearPicture;
	CBitButtonNL	m_clearDot;
	CBitButtonNL	m_binNum;
	CBitButtonNL	m_addlevelbutton;
	CBitButtonNL	m_deletebutton;
	CBitButtonNL	m_applybutton;
	CBitButtonNL	m_shootpoint;
	CBitButtonNL	m_exit;
	CBitButtonNL	m_inputpoint;
	CButton	m_accu;
	CEdit	m_ystart;
	CEdit	m_yend;
	CEdit	m_xstart;
	CEdit	m_xend;
	CButton	m_resize;
	CButton	m_adjust;
	CButton	m_levelstyle;
	CComboListCtrl	m_showpointlist;
	CButton	m_sure;
	CStatic	m_shootpicture;
	int		m_shootchip;
	int		m_inputset;
	BOOL	m_CIEPicture;
	BOOL	m_showscale;
	int		m_HandleRange;
	int		m_AddLevelStyle;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShootDiagram)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CShootDiagram)
	virtual BOOL OnInitDialog();
	afx_msg void OnExit();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnDrawPoint();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg bool Oninputpoint();
	afx_msg void OnClearPicture();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSetColor();
	afx_msg void OnSure();
	afx_msg void Oninputset();
	afx_msg void Onlineset();
	afx_msg void Onrectset();
	afx_msg bool OnSave();
	afx_msg bool OnApply();
	afx_msg void OnSelectCIEPicture();
	afx_msg void OnShowScale();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnAddLevel();
	afx_msg void OnSetRange();
	afx_msg void OnSetLevel();
	afx_msg void OnInsertLevel();
	afx_msg void OnCoverLevel();
	afx_msg void OnDeleteLevel();
	afx_msg void OnSelectLevel();
	afx_msg void Onparallelrectset();
	afx_msg void OnCheckBinNum();
	afx_msg void OnShowLevelPicture();
	afx_msg void OnLevelAdjust();
	afx_msg void OnEnlarge();
	afx_msg void OnSmaller();
	afx_msg void OnEnableResize();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnClickShowPointList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnXYlevelFile();
	afx_msg void OnExportXYLevel();
	afx_msg void OnImportXYLevel();
	afx_msg void OnSaveXYLevel();
	afx_msg void OnClearDot();
	afx_msg void OnUpdateShowCIELine(CCmdUI* pCmdUI);
	afx_msg void OnShowCIELine();
	afx_msg void OnSaveShootDot();
	afx_msg void OnLoadShootDot();
	afx_msg void OnNewCIERect();
	afx_msg void OnUpdateNewCIERect(CCmdUI* pCmdUI);
	afx_msg void OnFigureRange();
	afx_msg void OnImportXYLevel2();
	afx_msg void OnExportXYLevel2();
	afx_msg void OnSaveXYLevel2();
	//}}AFX_MSG
	void InitPictureParam(); 
	bool setDlgText();
	void Onshootchip1();
	void Onshootchip2();
	void Onshootchip3();
	bool FindSelectedRect(double x, double y);
	bool FindSelectedRect2(double x, double y);
	bool IfLinesCross(LineParam *line, bool vertical);
	bool IfCrossLineExist(int pointnum);
	bool IfRectIntersectionExist();
	bool IfConvexQuadrangle(double *x, double *y); 
	bool SetPointInOrder(int way);
	void XYLevelSave();
	void enlarge(double staPointX, double staPointY);
	void smaller(double staPointX, double staPointY); 
	bool RefreshBigRect();
	void SetDialogFace();
	void FreezeWindow();
	void ReleaseWindow();

	bool FindNewCIERect(double x, double y);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOOTDIAGRAM_H__8F64ABDF_713E_4917_AA77_8B6A256311C4__INCLUDED_)
