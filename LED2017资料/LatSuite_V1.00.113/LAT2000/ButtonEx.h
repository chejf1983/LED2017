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
//ȷ��ָ��״̬���ľ������ 
enum 
{ 
	DRAW_TYPE_UNKNOW, 
	DRAW_TYPE_BITMAP, 
	DRAW_TYPE_ICON 
} ; 
 
///////////////////////////////// 
//�ؼ����� 
enum 
{ 
	CTL_TYPE_UNKNOW,	//δ֪�ؼ� 
	CTL_TYPE_BUTTON,	//��ť�ؼ� 
	CTL_TYPE_CHECK,		//��ѡ��ؼ� 
	CTL_TYPE_RADIO		//��ѡ��ؼ� 
} ; 
 
///////////////////////////////// 
//�ؼ�״̬ 
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
//��ť��Ϣ�ṹ 
class CButtonInfoStruct  
{ 
public: 
	BOOL bDrawFrameForFocusState ;//���ؼ��н���ʱ�Ƿ���ʾ�߿� 
	BOOL bDrawText ;//�Ƿ����� 
	BOOL bDrawFrame ;//�Ƿ񻭱߿� 
	////////////////////////// 
	//λͼ��� 
	HBITMAP hBitmapOfNormal ; 
	HBITMAP hBitmapOfFocus ; 
	HBITMAP hBitmapOfPress ; 
	HBITMAP hBitmapOfDisable ; 
	HBITMAP hBitmapOfEnter ; 
	HBITMAP hBitmapOfDefault ; 
	////////////////////////// 
	//ͼ���� 
	HICON hIconOfNormal ; 
	HICON hIconOfFocus ; 
	HICON hIconOfPress ; 
	HICON hIconOfDisable ; 
	HICON hIconOfEnter ; 
	HICON hIconOfDefault ; 
	////////////////////////// 
	//����ʱ����� 
	HCURSOR hCursor ; 
 
	////////////////////////// 
	//��ť����������Ϣ 
	CString strFontName ; 
	int nFontSize ; 
	COLORREF clrTextColor ; 
	COLORREF clrBkColor ; 
	int nLineWidth ; 
 
	COLORREF clrTransparentKeyColor ;//͸��ɫ�������λͼ��ʾʱ 
 
	CRgn rgnCtl ;//��ť��Ч���� 
 
	////////////////////////// 
	//���캯����ʼ��������ֵ 
	CButtonInfoStruct () 
	{ 
		bDrawFrameForFocusState = FALSE ; 
		strFontName = _T("����") ; 
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
 
		clrTransparentKeyColor = INVAILD_TRANSPARENT_KEY_COLOR ;//Ĭ�Ϲؼ�ɫ��Ч 
 
		clrTextColor = RGB(0,0,0) ;//Ĭ��������ʾ��ɫ 
		clrBkColor = (COLORREF)::GetSysColor(COLOR_3DFACE) ; 
		nLineWidth = 1 ; //�߿��� ; 
	} 
} ; 
 
///////////////////////////////////// 
//���໯�ؼ��󱣴���Ӧ����Ϣ�ṹ 
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
 
	int nButtonType ;	//��ť���� 
	int nGroup ;		//������� 
	int nPos ;			//�������е�λ�� 
	HWND hCtlWnd ;		//�ؼ������� 
	DWORD dwContext ;	//������ؼ�����ϵ��ֵ 
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
	CButtonInfoStruct m_buttonCtlInfo ;//���汾�ؼ�������Ϣ�ṹ 
	static CList<CButtonSubclassStruct,CButtonSubclassStruct&> m_listSubclassInfo ;//���໯��Ϣ�ṹ���� 
	int m_nCtlType;//�ؼ����� 
	static CToolTipCtrl m_tooltipCtl;//��Ϣ��ʾ�ؼ����� 
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



