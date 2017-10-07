//******************************************************************
// BitButtonNL.h : header file
// ���ƣ��Զ�������λͼ��ť 
// ���ܣ�ʵ�������������ʾ3d����
// ˵�����̳���CButton��
//
//									Author	   NingLi
//											2003-12-3
//******************************************************************

#if !defined(AFX_BITBUTTONNL_H__D6CCC57A_D357_41DA_ADC7_551F0726B3E8__INCLUDED_)
#define AFX_BITBUTTONNL_H__D6CCC57A_D357_41DA_ADC7_551F0726B3E8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define	BTNNL_USE_SOUND

#define BTNNL_COLOR_FG_NORMAL	0
#define BTNNL_COLOR_FG_CLICK	1
#define BTNNL_COLOR_FG_HIGH		2

#define NL_ALIGN_LEFT			0
#define NL_ALIGN_RIGHT			1
#define NL_ALIGN_CENTER			2

/////////////////////////////////////////////////////////////////////////////
// CBitButtonNL window

class CBitButtonNL : public CButton
{
// Construction
public:

	CBitButtonNL();

// Attributes
public:
	
public:
//-------------------------------------------------------------------
//  ���������ð�ťλͼ
//	BOOL SetBitmaps(UINT nBitmapNormal,	UINT nBitmapMouseDown = NULL, UINT nBitmapHigh = NULL, UINT nBitmapDisable = NULL);
//  ����:
//	UINT nBitmapNormal		- Ĭ��λͼ
//	UINT nBitmapMouseDown	- ��갴�� λͼ
//	UINT nBitmapHigh		- ����ƶ�������ť�Ϸ� λͼ��
//	UINT nBitmapDisable		- ��ť��Ч λͼ
//-------------------------------------------------------------------
	BOOL SetBitmaps(UINT nBitmapNormal, UINT nBitmapMouseDown = NULL, UINT nBitmapHigh = NULL, UINT nBitmapDisable = NULL);
	BOOL SetBitmaps(HBITMAP hBitmapNormal, HBITMAP hBitmapMouseDown = NULL, HBITMAP hBitmapHigh = NULL, HBITMAP hBitmapDisable = NULL);

//-------------------------------------------------------------------
//  ������������ʾ���ֵ�ɫ��
//	BOOL SetForceColor(COLORREF crColorNormal, COLORREF crColorMouseDown, COLORREF crColorHigh, BOOL bRepaint = TRUE);
//  ������
//	COLORREF crColorNormal		- ������ɫ
//	COLORREF crColorMouseDown	- ����
//	COLORREF crColorHigh		- ��̬
//	BOOL     bRepaint			- �Ƿ������ػ�;
//-------------------------------------------------------------------
	BOOL SetForceColor(COLORREF crColorNormal, COLORREF crColorMouseDown, COLORREF crColorHigh, BOOL bRepaint = TRUE);

//-------------------------------------------------------------------
//  �����������Ƿ���ʾ�����
//	BOOL SetDrawFocusRect(BOOL bDrawFlatFocus, BOOL bRepaint = TRUE);
//  ������
//	BOOL bDrawFlatFocus	- ��ʾ����� ?
//	BOOL bRepaint		- �Ƿ������ػ�
//-------------------------------------------------------------------
	BOOL SetDrawFocusRect(BOOL bDrawFlatFocus, BOOL bRepaint = TRUE);

//-------------------------------------------------------------------
//  ���������ý�����밴ť�߽�ľ���
//	BOOL SetFocusRectDeflateRect(int x, int y);
//  ������
//	int x	- x �߾�
//	int y	- y �߾�
//-------------------------------------------------------------------
	BOOL SetFocusRectDeflateRect(int x, int y);

//-------------------------------------------------------------------
//  �����������������ָ��
//	BOOL SetBtnCursor(int nCursorId = NULL, BOOL bRepaint = TRUE);
//  ������
//	int  nCursorId	- ָ��
//	BOOL bRepaint	- �Ƿ������ػ�
//-------------------------------------------------------------------
	BOOL SetBtnCursor(int nCursorId = NULL, BOOL bRepaint = TRUE);

//-------------------------------------------------------------------
//  ���������ð�ť�������з�ʽ
//	BOOL SetTextAlign(BYTE byAlign, BOOL bRepaint = TRUE);
//  ������
//	BYTE byAlign  - ��ʽ ������3��ֵ
//					0. NL_ALIGN_LEFT
//					1. NL_ALIGN_RIGHT
//					2. NL_ALIGN_CENTER
//
//	BOOL bRepaint	- �Ƿ������ػ�
//-------------------------------------------------------------------
	BOOL SetTextAlign(BYTE byAlign, BOOL bRepaint = TRUE);

//-------------------------------------------------------------------
//  �����������Ƿ���ʾ��ť����
//	virtual CBitButtonNL& SetDrawText(BOOL bDraw = TRUE, BOOL bRepaint = TRUE);
//  ������
//	BOOL bDraw  - ��ʾ ?
//	BOOL bRepaint	- �Ƿ������ػ�
//-------------------------------------------------------------------
	virtual CBitButtonNL& SetDrawText(BOOL bDraw = TRUE, BOOL bRepaint = TRUE);

//-------------------------------------------------------------------
//  ���������ð�ť����Ӧ��һ��λͼ��С
//	void SizeToContent(void);
//  ������
//	-
//-------------------------------------------------------------------
	void SizeToContent(void);

//-------------------------------------------------------------------
//  ���������������Ƿ�Ϊ����
//	virtual CBitButtonNL& SetFontBold(BOOL bBold, BOOL bRepaint = TRUE);
//  ������
//	BOOL bBold		- ���� ?
//	BOOL bRepaint	- �Ƿ������ػ�
//-------------------------------------------------------------------
	virtual CBitButtonNL& SetFontBold(BOOL bBold, BOOL bRepaint = TRUE);

//-------------------------------------------------------------------
//  ������������������
//	virtual CBitButtonNL& SetFontName(const CString& strFont, BYTE byCharSet = DEFAULT_CHARSET, BOOL bRepaint = TRUE);
//  ������
//	const CString& strFont	- ��������
//	BYTE byCharSet			- �ַ���
//	BOOL bRepaint			- �Ƿ������ػ�
//-------------------------------------------------------------------
	virtual CBitButtonNL& SetFontName(const CString& strFont, BYTE byCharSet = DEFAULT_CHARSET, BOOL bRepaint = TRUE);

//-------------------------------------------------------------------
//  ���������������»���
//	virtual CBitButtonNL& SetFontUnderline(BOOL bSet, BOOL bRepaint = TRUE);
//  ������
//	BOOL bSet		- �»��� ?
//	BOOL bRepaint	- �Ƿ������ػ�
//-------------------------------------------------------------------
	virtual CBitButtonNL& SetFontUnderline(BOOL bSet, BOOL bRepaint = TRUE);

//-------------------------------------------------------------------
//  �������������� б��
//	virtual CBitButtonNL& SetFontItalic(BOOL bSet, BOOL bRepaint = TRUE);
//  ������
//	BOOL bSet		- б�� ?
//	BOOL bRepaint	- �Ƿ������ػ�
//-------------------------------------------------------------------
	virtual CBitButtonNL& SetFontItalic(BOOL bSet, BOOL bRepaint = TRUE);

//-------------------------------------------------------------------
//  �������������� �ֺ�
//	virtual CBitButtonNL& SetFontSize(int nSize, BOOL bRepaint = TRUE);
//  ������
//	int nSize		- �ֺ�
//	BOOL bRepaint	- �Ƿ������ػ�
//-------------------------------------------------------------------
	virtual CBitButtonNL& SetFontSize(int nSize, BOOL bRepaint = TRUE);

//-------------------------------------------------------------------
//  ��������������
//	virtual CBitButtonNL& SetFont(LOGFONT lf, BOOL bRepaint = TRUE);
//  ������
//	LOGFONT lf		- ����
//	BOOL bRepaint	- �Ƿ������ػ�
//-------------------------------------------------------------------
	virtual CBitButtonNL& SetFont(LOGFONT lf, BOOL bRepaint = TRUE);

//-------------------------------------------------------------------
//  ���������� 3d ���� 
//	virtual CBitButtonNL& SetFont3D(BOOL bSet, int i3dx = 3, int i3dy = 2, BOOL bRepaint = TRUE);
//  ������
//	BOOL bSet		- 3d ?
//	int i3dx		- ��Ӱ�ľ��� x
//	int i3dy		- ��Ӱ�ľ��� y
//	BOOL bRepaint	- �Ƿ������ػ�
//-------------------------------------------------------------------
	virtual CBitButtonNL& SetFont3D(BOOL bSet, int i3dx = 3, int i3dy = 2, BOOL bRepaint = TRUE);

//-------------------------------------------------------------------
//  ���������� 3d ���� ��Ӱɫ��
//	virtual CBitButtonNL& SetText3DBKColor(COLORREF cr3DBKColor, BOOL bRepaint = TRUE);
//  ������
//	COLORREF cr3DBKColor - ��Ӱɫ��
//	BOOL bRepaint		 - �Ƿ������ػ�
//-------------------------------------------------------------------
	virtual CBitButtonNL& SetText3DBKColor(COLORREF cr3DBKColor, BOOL bRepaint = TRUE);	//Sets the 3D font hilite color

//-------------------------------------------------------------------
//  ���������� ʧЧ������ʾ��ʽ
//	virtual CBitButtonNL&  CBitButtonNL::SetDrawTextAsDisable(BOOL bSet, BOOL bRepaint = TRUE);
//  ������
//	BOOL bSet			- True  = �Զ���ʧЧ����
//						  False = �����趨ɫ�ʻ�����
//	BOOL bRepaint		- �Ƿ������ػ�
//-------------------------------------------------------------------
	virtual CBitButtonNL&  CBitButtonNL::SetDrawTextAsDisable(BOOL bSet, BOOL bRepaint = TRUE);

//-------------------------------------------------------------------
//  ���������� ��ť����
//	BOOL SetSound(LPCTSTR lpszSound, HMODULE hMod = NULL, BOOL bPlayOnClick = FALSE, BOOL bPlayAsync = TRUE);
//  ������
//	LPCTSTR lpszSound		- �����ļ�
//	HMODULE hMod			- ģʽ ��Դ or �ļ�
//	BOOL bPlayOnClick		- ��ʽ True = ����;		  False = ��̬
//	BOOL bPlayAsync			- ģʽ True = SND_ASYNC ; False = SND_SYNC
//-------------------------------------------------------------------

#ifdef	BTNNL_USE_SOUND
	BOOL SetSound(LPCTSTR lpszSound, HMODULE hMod = NULL, BOOL bPlayOnClick = FALSE, BOOL bPlayAsync = TRUE);
#endif

// Operations

public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBitButtonNL)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBitButtonNL();

	// Generated message map functions
protected:
	//{{AFX_MSG(CBitButtonNL)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnClicked();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	virtual void DrawTheBitmap(CDC* pDC, BOOL bHasTitle, RECT* rpItem, CRect* rpCaption, BOOL bIsPressed, BOOL bIsDisabled);
	virtual void DrawTheText(CDC* pDC, LPCTSTR lpszText, RECT* rpItem, CRect* rpCaption, BOOL bIsPressed, BOOL bIsDisabled);
	LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	void FreeResources(BOOL bCheckForNULL = TRUE);
	void CancelHover(void);
	void ReconstructFont(void);

private:
	typedef struct _STRUCT_BITMAPS
	{
		HBITMAP		hBitmap;		// Handle to bitmap
		DWORD		dwWidth;		// Width of bitmap
		DWORD		dwHeight;		// Height of bitmap
	} STRUCT_BITMAPS;
#ifdef	BTNNL_USE_SOUND
#pragma pack(1)
	typedef struct _STRUCT_SOUND
	{
		TCHAR		szSound[_MAX_PATH];
		LPCTSTR		lpszSound;
		HMODULE		hMod;
		DWORD		dwFlags;
	} STRUCT_SOUND;
#pragma pack()

	STRUCT_SOUND	m_csSounds[2];	// Index 0 = Over	1 = Clicked
#endif

private:
	BOOL		m_bDrawFlatFocus;	// Draw focus rectangle for flat button?
	BOOL		m_bDrawText;		// Draw Text for button?
	BOOL		m_bMouseOnButton;	// Is mouse over the button?
	BOOL		m_bIsPressed;		// Is button pressed?
	BOOL		m_bIsFocused;		// Is button focused?
	BOOL		m_bIsDisabled;		// Is button disabled?
	BOOL		m_bIsDefault;		// Is default button?
	BOOL		m_bDrawDisableText;	// is Draw text as disable?
	int			m_iDeflateRect_x;	// DrawFlateFouse deflate rect _ x
	int			m_iDeflateRect_y;	// DrawFlateFouse deflate rect _ y
	POINT		m_ptPressedOffset;
	UINT		m_nTypeStyle;		// Button style
	HCURSOR		m_hCursor;			// Handle to cursor
	STRUCT_BITMAPS	m_csBitmaps[4];	// Button bitmap
	COLORREF	m_crForceColors[3];	// Colors to be used
	BYTE		m_byTextAlign;		// Align text
	
	
	//Font
	LOGFONT		m_lf;
	CFont		m_font;
	BOOL		m_bFont3d;
	COLORREF	m_cr3DBKColor;
	int			m_iText3d_x, m_iText3d_y;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BITBUTTONNL_H__D6CCC57A_D357_41DA_ADC7_551F0726B3E8__INCLUDED_)
