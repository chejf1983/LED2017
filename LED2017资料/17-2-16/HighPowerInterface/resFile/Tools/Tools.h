/*########################################################################
	Filename: 	tools.h
	----------------------------------------------------
	Remarks:	...
	----------------------------------------------------

  ########################################################################*/

#if !defined(_ANYOU_COOLTOOLS_H)
#define _ANYOU_COOLTOOLS_H

#if _MSC_VER > 1000
#pragma once
#endif

#define WM_UPDATEVIEW		(WM_USER + 139)

#define UnKnowWindowsVer	0x00000000
#define Windows32s			0x00000001
#define Windows95			0x00000E02
#define Windows98			0x00000E03
#define WindowsME			0x00000E04
#define WindowsNT3			0x000E0005
#define WindowsNT4			0x000E0006
#define Windows2000			0x000E0007
#define WindowsXP			0x000E0008
#define Windows2003			0x000E0009
#define Windows2004			0x000E000A


DWORD WINAPI GetWinVersion();

COLORREF WINAPI AlphaBlendColor(COLORREF color, BYTE byAlpha);

#if !defined(WS_EX_LAYERED)
#define WS_EX_LAYERED		0x00080000
#define LWA_COLORKEY        0x00000001
#define LWA_ALPHA			0x00000002
#endif
BOOL SetLayeredWindow(HWND hWnd, COLORREF crKey, BYTE bAlpha, DWORD dwFlags);

#ifndef SPI_GETDROPSHADOW
#define SPI_GETDROPSHADOW   0x1024
#endif
BOOL WINAPI IsShadowEnabled();

HBITMAP WINAPI GetScreenBitmap(LPCRECT pRect);
BOOL WINAPI IsOwnerDrawMenu(HMENU hMenu);

HBITMAP WINAPI CreateImage(HBITMAP hbitmap, int nstyle, BOOL bAlpha, COLORREF crBackColor, COLORREF crMarkColor, BOOL bFillMarkColor = TRUE);
void FillGradient(CDC *pDC, CRect rect, const COLORREF& StartColor, const COLORREF& EndColor, BOOL bHor = FALSE);
void DrawShadow(CDC *pDC, CRect rect);

CString GetExFileName(CString strPathName);
CString GetFileName(CString strPathName);
CString GetPathText(CString strPathName);
/*####################################################################
			------------------------------------------------
							   CMemDC class
			------------------------------------------------
  ####################################################################*/
/*
class CMemDC : public CDC 
{
private:
	CBitmap*	m_bitmap;
	CBitmap*	m_oldBitmap;
	CDC*		m_pDC;
	CRect		m_rcBounds;
public:
	CMemDC(CDC* pDC, const CRect& rcBounds= NULL) : CDC()
	{
		CreateCompatibleDC(pDC);
		m_bitmap = new CBitmap;
		m_bitmap->CreateCompatibleBitmap(pDC, rcBounds.Width(), rcBounds.Height());
		m_oldBitmap = SelectObject(m_bitmap);
		m_pDC = pDC;
		m_rcBounds = rcBounds;
        //For some reason the background color is not correct,
        //so we use the button face color.
        DWORD	color = ::GetSysColor(COLOR_BTNFACE);
        CBrush bkg(color);
        FillRect(rcBounds, &bkg);

	}
	
	~CMemDC() 
	{
		m_pDC->BitBlt(m_rcBounds.left, m_rcBounds.top, m_rcBounds.Width(), m_rcBounds.Height(), 
					this, 0, 0, SRCCOPY);
		SelectObject(m_oldBitmap);
		if (m_bitmap != NULL) delete m_bitmap;
	}

	CMemDC* operator->() 
	{
		return this;
	}
};*/

#endif // !defined(_ANYOU_COOLTOOLS_H)
