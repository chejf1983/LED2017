/*########################################################################
	Filename: 	tools.cpp
	----------------------------------------------------
	Remarks:	...
	----------------------------------------------------
  ########################################################################*/
#include "stdafx.h"
//#include "resource.h"
#include "tools.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

typedef struct tagCOLOR
{
	BYTE blue;
	BYTE green;
	BYTE red;
	BYTE alpha;
}COLOR;

COLORREF WINAPI AlphaBlendColor(COLORREF color, BYTE byAlpha)
{
	COLOR *oldcolor = (COLOR*)(&color);
	oldcolor->alpha = 0; 
	oldcolor->red   = oldcolor->red   * byAlpha / 255;
	oldcolor->green = oldcolor->green * byAlpha / 255;
	oldcolor->blue  = oldcolor->blue  * byAlpha / 255;
	return color;
}

/*===============================================================
		名称:	设置分层窗口透明或半透明属性.
		hWnd:	分层窗口句柄.
		crKey:	要显示为透明区域的颜色.当dwFlags为LWA_COLORKEY有效.
		bAlpha: 窗口的半透明度.当dwFlags为LWA_ALPHA有效.
		说明:   当窗口被设置了WS_EX_LAYERED扩展风格才有效.
=================================================================*/
BOOL SetLayeredWindow(HWND hWnd, COLORREF crKey, BYTE bAlpha, DWORD dwFlags)
{
	BOOL bRet = FALSE;

	//load USER32.dll-------------------------------------------------
	HMODULE	hUserDll = NULL;
	hUserDll = ::LoadLibrary(_T("USER32.dll"));
	
	// Check that "USER32.dll" library has been loaded successfully...
	if (hUserDll != NULL)
	{
		typedef BOOL (WINAPI* lpfnSetAttributes)(HWND hWnd, COLORREF crKey, BYTE bAlpha, DWORD dwFlags);
		lpfnSetAttributes pFnlpfnSetAttributes  = NULL;
		pFnlpfnSetAttributes  = (lpfnSetAttributes)GetProcAddress(hUserDll, "SetLayeredWindowAttributes");
		if (pFnlpfnSetAttributes )
		{
			bRet = pFnlpfnSetAttributes(hWnd, crKey, bAlpha, dwFlags);
		}
	} 
	
	if (hUserDll != NULL) ::FreeLibrary(hUserDll);
	return bRet;
} 

/*========================================================================
	说明:	检测系统是否开启了菜单阴影(主要针对于Windows XP, Windows 2003
		及他更高的版本).	
==========================================================================*/
BOOL WINAPI IsShadowEnabled()
{
	BOOL bEnabled = FALSE;
	if (SystemParametersInfo(SPI_GETDROPSHADOW, 0, &bEnabled, 0))
	{
		return bEnabled;
	}
	return FALSE;
}

DWORD WINAPI GetWinVersion()
{
    static DWORD WindowsVer = UnKnowWindowsVer;

    if (WindowsVer != UnKnowWindowsVer)
    {
        return WindowsVer;
    }

    OSVERSIONINFO osvi;
    ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	
    if (!GetVersionEx (&osvi))
    {
        return WindowsVer = UnKnowWindowsVer;
    }

    if (osvi.dwPlatformId == VER_PLATFORM_WIN32s)
    {
        return WindowsVer = Windows32s;
    }

    else if(osvi.dwPlatformId == VER_PLATFORM_WIN32_NT)
    {
        if (osvi.dwMajorVersion == 4L)
        {
            return WindowsVer = WindowsNT4;
        }
        else if (osvi.dwMajorVersion == 5L) 
        {
			if (osvi.dwMinorVersion == 0L)
			{
				return WindowsVer = Windows2000;
			}
			else if (osvi.dwMinorVersion == 1L)
			{
				return WindowsVer = WindowsXP;
			}
			else
			{
				return WindowsVer = Windows2003;
			}
        }
        return WindowsVer = WindowsNT3;
    }
    ASSERT(osvi.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS);
	
    if (osvi.dwMajorVersion == 4L && osvi.dwMinorVersion == 10L)
    {
        return WindowsVer = Windows98;
    }
    if (osvi.dwMajorVersion == 4L && osvi.dwMinorVersion == 90L)
    {
        return WindowsVer = WindowsME;
    }
    return WindowsVer = Windows95;
}

/*========================================================================
	说明:		截取屏幕上指定区域内的图像.
==========================================================================*/
HBITMAP WINAPI GetScreenBitmap(LPCRECT pRect)
{
    HDC     hDC;
    HDC     hMemDC;
    HBITMAP hNewBitmap = NULL;
	
    if ((hDC = ::GetDC(NULL)) != NULL )
    {
        if ((hMemDC = ::CreateCompatibleDC(hDC)) != NULL)
        {
            if ((hNewBitmap = ::CreateCompatibleBitmap(hDC, pRect->right - pRect->left, pRect->bottom - pRect->top)) != NULL)
            {
                HBITMAP hOldBitmap = (HBITMAP)::SelectObject(hMemDC, hNewBitmap);
                ::BitBlt(hMemDC, 0, 0, pRect->right - pRect->left, pRect->bottom - pRect->top,
					hDC, pRect->left, pRect->top, SRCCOPY);
                ::SelectObject(hMemDC, (HGDIOBJ)hOldBitmap);
            }
            ::DeleteDC(hMemDC);
        }
        ::ReleaseDC(NULL, hDC);
    }
    return hNewBitmap;
}

/*========================================================================
	说明:	指定Windows菜单句柄是否为自画风格菜单.
==========================================================================*/
BOOL WINAPI IsOwnerDrawMenu(HMENU hMenu)
{
    MENUITEMINFO mii = {sizeof MENUITEMINFO, MIIM_TYPE };
    ::GetMenuItemInfo(hMenu, 0, TRUE, &mii);
    return (mii.fType & MFT_OWNERDRAW) != 0;
}

/*========================================================================
	功能：			创建相应的图像列表所需的图像
	-------------------------------------------------------------
	hbitmap:		原始位图句柄
	crBackColor:	背景色
	nstyle:			要创建的图像的风格,它们为下列值之一:
	----------------------------------------------------
		-	0:		创建禁止图像列表图像
		-	1:		创建正常图像列表图像
		-	2:		创建热图像列表图像
==========================================================================*/
HBITMAP WINAPI CreateImage(HBITMAP hbitmap, int nstyle, BOOL bAlpha, COLORREF crBackColor, COLORREF crMarkColor, BOOL bFillMarkColor)
{
	HBITMAP RetBmp = NULL;
    if (hbitmap == NULL)
    {  
		return NULL;
	}

	//源位图DC------------------------------------
    HDC BufferDC = CreateCompatibleDC(NULL);      
    if (BufferDC == NULL)
    {
		return NULL;
	}
    SelectObject(BufferDC, hbitmap);

	//目标DC--------------------------------------
    HDC DirectDC = CreateCompatibleDC(NULL);      
    if (DirectDC == NULL)
    {
		  DeleteDC(BufferDC);
		  return NULL;
	}

    // 获取源位图大小----------------------------
    BITMAP bm;
    GetObject(hbitmap, sizeof(bm), &bm);

	// 初始化BITMAPINFO信息----------------------
    BITMAPINFO bitmapinfo; 
    ZeroMemory(&bitmapinfo, sizeof(BITMAPINFO));
    bitmapinfo.bmiHeader.biSize     = sizeof(BITMAPINFOHEADER);
    bitmapinfo.bmiHeader.biWidth    = bm.bmWidth;
    bitmapinfo.bmiHeader.biHeight   = bm.bmHeight;
    bitmapinfo.bmiHeader.biPlanes   = 1;
    bitmapinfo.bmiHeader.biBitCount = 32;
	
	//指向像素区指针--------
	BYTE *ptPixels;    
    HBITMAP DirectBitmap = CreateDIBSection(DirectDC, (BITMAPINFO*)&bitmapinfo, 
                                  DIB_RGB_COLORS, (void**)&ptPixels, NULL, 0);
	
	//背景颜色--------------
	BYTE	oldRed   = GetRValue(crBackColor);
	BYTE	oldGreen = GetGValue(crBackColor);
	BYTE	oldBlue  = GetBValue(crBackColor);

	//透明色----------------
	BYTE	markRed   = GetRValue(crMarkColor);
	BYTE	markGreen = GetGValue(crMarkColor);
	BYTE	markBlue  = GetBValue(crMarkColor);

	BYTE	temp = 0;
	COLOR* ptPixel = (COLOR*)ptPixels;
	
    if (DirectBitmap != NULL)
    {
        HGDIOBJ oldObject = SelectObject(DirectDC, DirectBitmap);
        BitBlt(DirectDC, 0, 0, bm.bmWidth, bm.bmHeight, BufferDC, 0, 0, SRCCOPY);
		
		register int nbitcount = (bm.bmWidth * bm.bmHeight * 4);
        for (register int i = 0; i < nbitcount;  i += 4)
        {
			//透明区(alpha == 0)----------------------------------
			if (( bAlpha && ptPixel->alpha == 0) 
			||  (!bAlpha && ptPixel->red   == markRed	//red
						 && ptPixel->green == markGreen	//green
						 && ptPixel->blue  == markBlue	//blue
					)
			   ) 
			{
				if (bFillMarkColor)
				{
					ptPixel->blue  = 255;
					ptPixel->green = 0;
					ptPixel->red   = 255;
				}
				else
				{
					ptPixel->blue  = oldRed;
					ptPixel->green = oldGreen;
					ptPixel->red   = oldBlue;
				}
			}
			else 
			{
				//灰度化位图--------------------------------------
				if (nstyle == 0 )
				{
					temp = (BYTE)(ptPixel->red * 0.299 + ptPixel->green * 0.587 + ptPixels[i] * 0.114);
					temp = (BYTE)(255 - (255 - temp) * 0.8); 
					ptPixel->red = ptPixel->green = ptPixels[i] = temp;
				}

				//淡化位图----------------------------------------
				else if (nstyle == 2)
				{
					ptPixel->red   = (BYTE)(255 - (255 - ptPixel->red)   * 0.9); 
					ptPixel->green = (BYTE)(255 - (255 - ptPixel->green) * 0.9); 
					ptPixel->blue  = (BYTE)(255 - (255 - ptPixel->blue)  * 0.9); 
				}

				//Alpha混合(Alpha blend)---------------------------
				if (bAlpha)
				{
					ptPixel->red   = (oldRed   * (255 - ptPixel->alpha) + ptPixel->red   * ptPixel->alpha) / 255; 
					ptPixel->green = (oldGreen * (255 - ptPixel->alpha) + ptPixel->green * ptPixel->alpha) / 255; 
					ptPixel->blue  = (oldBlue  * (255 - ptPixel->alpha) + ptPixel->blue  * ptPixel->alpha) / 255; 
				}
			}
			ptPixel++;
        }

        SelectObject(DirectDC, oldObject);
        RetBmp = DirectBitmap;
    }
    // 释放DC--------------------
    DeleteDC(DirectDC);
    DeleteDC(BufferDC);
 
	return RetBmp;
}

/*========================================================================
	说明:	用渐变色填充指定的矩形区域.
==========================================================================*/
void FillGradient(CDC *pDC, CRect rect, const COLORREF& StartColor, const COLORREF& EndColor, BOOL bHor)
{
	//绘制渐变色--------------------------------
	int r1 = GetRValue(StartColor);
	int g1 = GetGValue(StartColor);
	int b1 = GetBValue(StartColor);
	
	int r2 = GetRValue(EndColor);
	int g2 = GetGValue(EndColor);
	int b2 = GetBValue(EndColor);
	
	if (bHor)
	{
		float dr = ((float)(r2 - r1)) / (float)(rect.Width());
		float dg = ((float)(g2 - g1)) / (float)(rect.Width());
		float db = ((float)(b2 - b1)) / (float)(rect.Width());
		for (int i = rect.left; i < rect.right; i ++)
		{
			int r = r1 + (int)(dr*((float)(i - rect.left)));
			int g = g1 + (int)(dg*((float)(i - rect.left)));
			int b = b1 + (int)(db*((float)(i - rect.left)));
			CPen pen(PS_SOLID, 1, RGB(r, g, b));
			CPen *old = pDC->SelectObject(&pen);
			pDC->MoveTo(i, rect.top);
			pDC->LineTo(i, rect.bottom);
			pDC->SelectObject(old);
		}
	}
	else
	{
		float dr = ((float)(r2 - r1)) / (float)(rect.Height());
		float dg = ((float)(g2 - g1)) / (float)(rect.Height());
		float db = ((float)(b2 - b1)) / (float)(rect.Height());
		for (int i = rect.top; i < rect.bottom; i ++)
		{
			int r = r1 + (int)(dr*((float)(i - rect.top)));
			int g = g1 + (int)(dg*((float)(i - rect.top)));
			int b = b1 + (int)(db*((float)(i - rect.top)));
			CPen pen(PS_SOLID, 1, RGB(r, g, b));
			CPen *old = pDC->SelectObject(&pen);
			pDC->MoveTo(rect.left, i);
			pDC->LineTo(rect.right, i);
			pDC->SelectObject(old);
		}
	}
}

/*========================================================================
	说明:	在指定的矩形区域内绘制阴影.	
==========================================================================*/
void DrawShadow(CDC *pDC, CRect rect)
{
	COLORREF oldcolor = RGB(255, 255, 255);
	BYTE newValR, newValG, newValB;
	BYTE AlphaArray[] = {140, 170, 212, 240};
	BYTE AlphaArray2[] = {170, 205, 220, 240, 240, 250, 255};
	
	// 底部的阴影 -----------------------------------------
	int i, j;
	for (j = 0; j < 4; j++)
	{
		for (i = 6; i <= rect.right - 5; i++)
		{
			oldcolor = pDC->GetPixel(i, rect.bottom - (4 - j));
			newValR = GetRValue(oldcolor) * AlphaArray[j] / 255;  
			newValG = GetGValue(oldcolor) * AlphaArray[j] / 255;  
			newValB = GetBValue(oldcolor) * AlphaArray[j] / 255;  
			pDC->SetPixel(i, rect.bottom - (4 - j), RGB(newValR, newValG, newValB));
		}
	}
	
	// 右边的阴影 -----------------------------------------
	for (i = 0; i < 4; i++)
	{
		for (j = 6; j <= rect.bottom - 5; j++)
		{
			oldcolor = pDC->GetPixel(rect.right - (4 - i), j);
			newValR = GetRValue(oldcolor) * AlphaArray[i] / 255;  
			newValG = GetGValue(oldcolor) * AlphaArray[i] / 255;  
			newValB = GetBValue(oldcolor) * AlphaArray[i] / 255;  
			pDC->SetPixel(rect.right - (4 - i), j, RGB(newValR, newValG, newValB));
		}
	}
	
	// 其他部位的阴影 --------------------------------------
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if ((i + j) > 6) break;
			BYTE alpha = AlphaArray2[i + j];
			oldcolor = pDC->GetPixel(rect.right - 4 + i, rect.bottom - 4 + j);
			newValR = GetRValue(oldcolor) * alpha / 255;  
			newValG = GetGValue(oldcolor) * alpha / 255;  
			newValB = GetBValue(oldcolor) * alpha / 255;  
			pDC->SetPixel(rect.right - 4 + i, rect.bottom - 4 + j, RGB(newValR, newValG, newValB));
			
			oldcolor = pDC->GetPixel(rect.right - 4 + i, rect.top + 5 - j);
			newValR = GetRValue(oldcolor) * alpha / 255;  
			newValG = GetGValue(oldcolor) * alpha / 255;  
			newValB = GetBValue(oldcolor) * alpha / 255;  
			pDC->SetPixel(rect.right - 4 + i, rect.top + 5 - j, RGB(newValR, newValG, newValB));
			
			oldcolor = pDC->GetPixel(rect.left - i + 5, rect.bottom - 4 + j);
			newValR = GetRValue(oldcolor) * alpha / 255;  
			newValG = GetGValue(oldcolor) * alpha / 255;  
			newValB = GetBValue(oldcolor) * alpha / 255;  
			pDC->SetPixel(rect.left - i + 5, rect.bottom - 4 + j, RGB(newValR, newValG, newValB));
		}
	}
}

CString GetPathText(CString strPathName)
{
	int count = strPathName.GetLength();
	for (int i = count - 1; i >= 0; i--)
	{
		if (strPathName[i] == '\\')
		{
			break;
		}
	}
	return strPathName.Left(i + 1);
}

CString GetFileName(CString strPathName)
{
	int count = strPathName.GetLength();
	for (int i = count - 1; i >= 0; i--)
	{
		if (strPathName[i] == '\\')
		{
			break;
		}
	}
	return strPathName.Right(count - i - 1);
}

CString GetExFileName(CString strPathName)
{
	int count = strPathName.GetLength();
	for (int i = count - 1; i >= 0; i--)
	{
		if (strPathName[i] == '\\')
		{
			return CString("");
		}
		else if (strPathName[i] == '.')
		{
			break;
		}
	}
	return strPathName.Right(count - i - 1);
}