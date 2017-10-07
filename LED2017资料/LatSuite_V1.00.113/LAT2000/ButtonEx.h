#if !defined(AFX_BUTTONEX_H__C30DE880_9E5D_49A5_8E53_A856FAF148BE__INCLUDED_) 
#define AFX_BUTTONEX_H__C30DE880_9E5D_49A5_8E53_A856FAF148BE__INCLUDED_ 
#include "afxtempl.h" 
 
#if _MSC_VER > 1000 
#pragma once 
#endif // _MSC_VER > 1000 
// ButtonEx.h : header file 
// 
 
 
#define INVAILD_GROUP_ID	-1 
#define INVAILD_POS_ID		-1 
#define INVAILD_TRANSPARENT_KEY_COLOR -1 
 
///////////////////////////////// 
//确定指定状态画的句柄类型 
enum 
{ 
	DRAW_TYPE_UNKNOW, 
	DRAW_TYPE_BITMAP, 
	DRAW_TYPE_ICON 
} ; 
 
///////////////////////////////// 
//控件类型 
enum 
{ 
	CTL_TYPE_UNKNOW,	//未知控件 
	CTL_TYPE_BUTTON,	//按钮控件 
	CTL_TYPE_CHECK,		//复选框控件 
	CTL_TYPE_RADIO		//单选框控件 
} ; 
 
///////////////////////////////// 
//控件状态 
enum 
{ 
	NORMAL, 
	ENTER, 
	FOCUS, 
	PRESS, 
	DISABLED, 
	DEFAULT 
} ; 
 
 
///////////////////////////////////// 
//按钮信息结构 
class CButtonInfoStruct  
{ 
public: 
	BOOL bDrawFrameForFocusState ;//当控件有焦点时是否显示边框 
	BOOL bDrawText ;//是否画文字 
	BOOL bDrawFrame ;//是否画边框 
	////////////////////////// 
	//位图句柄 
	HBITMAP hBitmapOfNormal ; 
	HBITMAP hBitmapOfFocus ; 
	HBITMAP hBitmapOfPress ; 
	HBITMAP hBitmapOfDisable ; 
	HBITMAP hBitmapOfEnter ; 
	HBITMAP hBitmapOfDefault ; 
	////////////////////////// 
	//图标句柄 
	HICON hIconOfNormal ; 
	HICON hIconOfFocus ; 
	HICON hIconOfPress ; 
	HICON hIconOfDisable ; 
	HICON hIconOfEnter ; 
	HICON hIconOfDefault ; 
	////////////////////////// 
	//进入时光标句柄 
	HCURSOR hCursor ; 
 
	////////////////////////// 
	//按钮其它设置信息 
	CString strFontName ; 
	int nFontSize ; 
	COLORREF clrTextColor ; 
	COLORREF clrBkColor ; 
	int nLineWidth ; 
 
	COLORREF clrTransparentKeyColor ;//透明色，如果有位图显示时 
 
	CRgn rgnCtl ;//按钮有效区域 
 
	////////////////////////// 
	//构造函数初始化各变量值 
	CButtonInfoStruct () 
	{ 
		bDrawFrameForFocusState = FALSE ; 
		strFontName = _T("宋体") ; 
		nFontSize = 90 ; 
		bDrawText = TRUE ; 
		bDrawFrame = TRUE ; 
 
		hBitmapOfNormal = NULL ; 
		hBitmapOfFocus = NULL ; 
		hBitmapOfPress = NULL ; 
		hBitmapOfDisable = NULL ; 
		hBitmapOfEnter = NULL ; 
		hBitmapOfDefault = NULL ; 
 
		hIconOfNormal = NULL ; 
		hIconOfFocus = NULL ; 
		hIconOfPress = NULL ; 
		hIconOfDisable = NULL ; 
		hIconOfEnter = NULL ; 
		hIconOfDefault = NULL ; 
 
		hCursor = NULL ; 
 
		clrTransparentKeyColor = INVAILD_TRANSPARENT_KEY_COLOR ;//默认关键色无效 
 
		clrTextColor = RGB(0,0,0) ;//默认文字显示黑色 
		clrBkColor = (COLORREF)::GetSysColor(COLOR_3DFACE) ; 
		nLineWidth = 1 ; //边框宽度 ; 
	} 
} ; 
 
///////////////////////////////////// 
//子类化控件后保存相应的信息结构 
class CButtonSubclassStruct 
{ 
public: 
	CButtonSubclassStruct() 
	{ 
		nButtonType = CTL_TYPE_UNKNOW ; 
		nGroup = INVAILD_GROUP_ID ; 
		nPos = INVAILD_POS_ID ; 
		hCtlWnd = NULL ; 
		dwContext = NULL ; 
	} 
 
	CButtonSubclassStruct& operator = (CButtonSubclassStruct subclassInfo) 
	{ 
		nButtonType = subclassInfo.nButtonType ; 
		nGroup = subclassInfo.nGroup ; 
		nPos = subclassInfo.nPos ; 
		hCtlWnd = subclassInfo.hCtlWnd ; 
		dwContext = subclassInfo.dwContext ; 
		return *this ; 
	} 
 
	int nButtonType ;	//按钮类型 
	int nGroup ;		//所在组号 
	int nPos ;			//所在组中的位置 
	HWND hCtlWnd ;		//控件自身句柄 
	DWORD dwContext ;	//保存与控件相联系的值 
} ; 
 
 
class CButtonEx : public CButton 
{ 
// Construction 
public: 
	CButtonEx(); 
// Attributes 
public: 
 
// Operations 
public: 
 
// Overrides 
	// ClassWizard generated virtual function overrides 
	//{{AFX_VIRTUAL(CButtonEx) 
	public: 
	virtual BOOL PreTranslateMessage(MSG* pMsg); 
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct); 
	protected: 
	virtual void PreSubclassWindow(); 
	//}}AFX_VIRTUAL 
 
// Implementation 
public: 
	BOOL IsDrawFrameForState(int nState); 
	CString SetFontInfo(CString strFontName,int nSize,int* pPreSize); 
	void SetTransparent(BOOL bTransparent);
	COLORREF SetTextColor(COLORREF clrTextColor);
	COLORREF SetButtonBkColor(COLORREF clrBkColor);
	int GetCtlType(); 
	int GetCheck(); 
	void SetCheck(int nCheck); 
	BOOL SetCursorFromID(UINT nID); 
	BOOL SetCursorFromFile(CString strFileName); 
	HCURSOR GetHcursor(); 
	HCURSOR SetCursorFromHcursor(HCURSOR hCursor); 
	void ShowFrame(BOOL bShowFrame); 
	void ShowText(BOOL bShowText); 
	HICON GetHiconOf(int nState); 
	BOOL SetIconFromHicon(HICON hIcon,int nState); 
	BOOL SetBitmapFromHbitmap(HBITMAP hBitmap,int nState); 
	BOOL SetIconFromFile(CString strFileName,int nState); 
	BOOL SetIconFromID(UINT nID,int nState); 
	BOOL SetBitmapFromFile(CString strFileName,int nState); 
	BOOL SetBitmapFromID(UINT nID,int nState); 
	COLORREF SetTransparentKeyColor(COLORREF clrKeyColor); 
	CString GetTooltip(); 
	BOOL SetTooltip(CString strTooltipText); 
	virtual ~CButtonEx(); 
	HBITMAP GetHbitmapOf(int nState); 
 
	// Generated message map functions 
protected: 
	void SetOwnerDraw(); 
	int GetPreCtlType(); 
	BOOL IsOwnerDraw(); 
	void SetCheckValue(int nCheck); 
	static BOOL GetSubclassInfo(HWND hWnd,CButtonSubclassStruct* pSubclassInfo); 
	void RefreshShell(HDC hdc,BOOL bPress=FALSE); 
	static void AdjustRadioValue(HWND hRadioCtl); 
	int m_nCheck; 
	static int RemoveSubclassInfo(HWND hWnd); 
	BOOL m_bFirstMouseEnter; 
	LRESULT OnMouseLeave(WPARAM wParam,LPARAM lParam); 
	void SetBIcon(HICON hIcon,int nState); 
	void SetBBitmap(HBITMAP hBitmap,int nState); 
	COLORREF GetTransparentKeyColor(); 
	void SetBRgn(CRgn* pRgn); 
	void SetClipRgn(HDC hdc); 
	void DrawBFrame(HDC hdc,int nState); 
	BOOL IsDrawFrame(); 
	void DrawBText(HDC hdc,int nState); 
	BOOL IsDrawText(); 
	void DrawBNormal(HDC hdc); 
	void DrawBIcon(HDC hdc,HICON hIcon); 
	void DrawBBitmap(HDC hdc,HBITMAP hBitmap); 
	int GetDrawType(int nState,DWORD* pdwHandle); 
	void DrawBState(HDC hdc,int nState); 
	static POSITION FindSubclassInfoPos(HWND hWnd); 
	static int AddSubclassInfo(CButtonSubclassStruct* pSubclassInfo); 
	CButtonInfoStruct m_buttonCtlInfo ;//保存本控件设置信息结构 
	static CList<CButtonSubclassStruct,CButtonSubclassStruct&> m_listSubclassInfo ;//子类化信息结构链表 
	int m_nCtlType;//控件类型 
	static CToolTipCtrl m_tooltipCtl;//信息提示控件变量 
	BOOL m_bTransparent;
	//{{AFX_MSG(CButtonEx) 
	afx_msg void OnMouseMove(UINT nFlags, CPoint point); 
	afx_msg void OnDestroy(); 
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message); 
	afx_msg void OnClicked(); 
	//}}AFX_MSG 
 
	DECLARE_MESSAGE_MAP() 
}; 
 
///////////////////////////////////////////////////////////////////////////// 
 
//{{AFX_INSERT_LOCATION}} 
// Microsoft Visual C++ will insert additional declarations immediately before the previous line. 
 
#endif // !defined(AFX_BUTTONEX_H__C30DE880_9E5D_49A5_8E53_A856FAF148BE__INCLUDED_) 



