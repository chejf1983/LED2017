/*########################################################################
	Filename: 	coolmenu.cpp
	----------------------------------------------------
	Remarks:	...
	----------------------------------------------------
	
  ########################################################################*/

#include "stdafx.h"
#include "CoolMenu.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif 

const TCHAR CoolMenu_oldProc[] = _T("CoolMenu_oldProc");

/*########################################################################
			  ------------------------------------------------
								Cool API 函数
			  ------------------------------------------------
  ########################################################################*/

HMODULE g_hUserDll = NULL;
#define WS_EX_LAYERED	0x00080000 //此扩展属性使窗口透明.
#define LWA_ALPHA		0x00000002

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
HBITMAP CCoolMenu::CreateImage(HBITMAP hbitmap, int nstyle, BOOL bAlpha, COLORREF crBackColor, COLORREF crMarkColor)
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
    bitmapinfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bitmapinfo.bmiHeader.biWidth = bm.bmWidth;
    bitmapinfo.bmiHeader.biHeight = bm.bmHeight;
    bitmapinfo.bmiHeader.biPlanes = 1;
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

    if (DirectBitmap != NULL)
    {
        HGDIOBJ oldObject = SelectObject(DirectDC, DirectBitmap);
        BitBlt(DirectDC, 0, 0, bm.bmWidth, bm.bmHeight, BufferDC, 0, 0, SRCCOPY);

		register int nbitcount = (bm.bmWidth * bm.bmHeight * 4);
        for (register int i = 0; i < nbitcount;  i += 4)
        {
			//透明区(alpha == 0)----------------------------------
			if (	( bAlpha && ptPixels[i + 3] == 0) 
				||  (!bAlpha && ptPixels[i + 2] == markRed	//red
							   && ptPixels[i + 1] == markGreen	//green
							   && ptPixels[i + 0] == markBlue	//blue
					)
			   ) 
			{
				ptPixels[i + 2] = 255;	//red
				ptPixels[i + 1] = 0;	//green
				ptPixels[i + 0] = 255;	//blue
			}
			else 
			{
				//灰度化位图--------------------------------------
				if (nstyle == 0 )
				{
					temp = (BYTE)(ptPixels[i + 2] * 0.299 + ptPixels[i + 1] * 0.587 + ptPixels[i] * 0.114);
					temp = (BYTE)(255 - (255 - temp) * 0.8); 
					ptPixels[i + 2] = ptPixels[i + 1] = ptPixels[i] = temp;
				}

				//淡化位图----------------------------------------
				else if (nstyle == 2)
				{
					ptPixels[i + 2] = (BYTE)(255 - (255 - ptPixels[i + 2]) * 0.9); 
					ptPixels[i + 1] = (BYTE)(255 - (255 - ptPixels[i + 1]) * 0.9); 
					ptPixels[i    ] = (BYTE)(255 - (255 - ptPixels[i + 0]) * 0.9); 
				}

				//Alpha混合--------------------------------------
				if (bAlpha)
				{
					ptPixels[i + 2] = (oldRed * (255 - ptPixels[i + 3]) + ptPixels[i + 2] * ptPixels[i + 3]) / 255; // Alpha取值范围从0到255
					ptPixels[i + 1] = (oldGreen * (255 - ptPixels[i + 3]) + ptPixels[i + 1] * ptPixels[i + 3]) / 255; // Alpha取值范围从0到255
					ptPixels[i    ] = (oldBlue * (255 - ptPixels[i + 3]) + ptPixels[i    ] * ptPixels[i + 3]) / 255; // Alpha取值范围从0到255
				}
			}
        }

        SelectObject(DirectDC, oldObject);
        RetBmp = DirectBitmap;
    }
    // 释放DC--------------------
    DeleteDC(DirectDC);
    DeleteDC(BufferDC);
 
	return RetBmp;
}

#ifndef SPI_GETDROPSHADOW
#define SPI_GETDROPSHADOW   0x1024
#endif

/*========================================================================
	说明:	用渐变色填充指定的矩形区域.
==========================================================================*/
void CCoolMenu::DrawGradsRect(CDC *pDC,  CRect &rect, COLORREF statColor, COLORREF endColor)
{//画梯度矩形,渐变的方式是从上到下再到上变化
	int r=GetRValue(statColor);
	int g=GetGValue(statColor);
	int b=GetBValue(statColor);//得到起始色的颜色分量

	//得到颜色分量的增量 
	float dr=(float)(2*(GetRValue(endColor)-GetRValue(statColor))/rect.Height());
	float dg=(float)(2*(GetGValue(endColor)-GetGValue(statColor))/rect.Height());
    float db=(float)(2*(GetBValue(endColor)-GetBValue(statColor))/rect.Height());
	//创建笔对象填充矩形
	for(int i=0;i<=rect.Height()/2;i++)
	{
        CPen pen(PS_SOLID,1,RGB(r+i*dr,g+i*dg,b+i*db)),*Oldpen;
		Oldpen=pDC->SelectObject(&pen);
		//画直线
		pDC->MoveTo(rect.left,rect.top+i);
		pDC->LineTo(rect.right,rect.top+i);
		pDC->MoveTo(rect.left,rect.bottom- i);
		pDC->LineTo(rect.right,rect.bottom-i);

		//恢复DC
		pDC->SelectObject(Oldpen);
		pen.DeleteObject();
	}
}

/*===================用指定的位图填充菜单背景=======================*/
void CCoolMenu::DrawBackGroundBmp(CDC*pDC,CRect rect,BOOL bFill)
{ 
	if(!bFill)
	{//若不填充则直接返回
       return ;
	}
	else//注意:位图的大小要大于rect的大小
	{//若填充则用指定的位图填充
        if(nBackGroundbmpID!=NULL)
		{//若位图不为空
			/*-------------------加载位图-----------------------*/
			CBitmap m_BkGndBmp;
            m_BkGndBmp.LoadBitmap(nBackGroundbmpID);//加载位图
			if(m_BkGndBmp.m_hObject!=NULL)
			{//加载位图成功
			   CDC MemDC;//定义内存DC来保存背景位图
	           MemDC.CreateCompatibleDC(pDC);//创建一个于pDC兼容的DC
	           MemDC.SelectObject(&m_BkGndBmp);//将位图对象选入内存中
	           pDC->BitBlt(0,0,rect.Width(),rect.Height(),&MemDC,0,0,SRCCOPY);
			}
		}
	}

}


/*########################################################################
			  ------------------------------------------------
						菜单子类化类 CCoolMenuHook
			  ------------------------------------------------
		用于截获拥有此菜单窗口的与菜单相关的消息，以便进行相应的处理.
  ########################################################################*/

LRESULT CCoolMenuHook::WindowProc(UINT uMesssage, WPARAM wparam, LPARAM lparam)
{
	switch (uMesssage) 
	{
	case WM_DRAWITEM:
		CCoolMenu::DrawItem(LPDRAWITEMSTRUCT(lparam));
		break;
	case WM_MEASUREITEM:
		CCoolMenu::MeasureItem(LPMEASUREITEMSTRUCT(lparam));
		break;
	case WM_NCDESTROY:
		CCoolMenu::UnSubClass();
		break;
	default:
		break;
	}
	
	return CSubclassWnd::WindowProc(uMesssage, wparam, lparam);
}

/*========================================================================
	功能：	设置菜单项的名称,并把快捷键提示信息从菜单名中分离出来.
==========================================================================*/
void CCoolMenu::CCoolMenuItem::SetItemName(CString sname)
{
	//快捷键提示信息一般在'\t'字符之后.如"Open(&O)\tCtrl+O";
	int n = sname.Find('\t');
	if(n != -1)
	{
		strText = sname.Left(n);
		strKeyName = sname.Right(sname.GetLength() - n - 1);
	}
	else
	{
		strText = sname;
		strKeyName = "";
	}
}

/*########################################################################
					  ----------------------------------
								    构建菜单	
					  ----------------------------------
  ########################################################################*/

CUIntArray CCoolMenu::m_uIDArray;		//菜单项ID数组
//菜单图标图像列表-------------------------------
CImageList CCoolMenu::m_iImageList;
CImageList CCoolMenu::m_iHotImageList;
CImageList CCoolMenu::m_iDisabledImageList;
CString CCoolMenu::m_sLogoText;		//LOGO字符串
CCoolMenuHook CCoolMenu::m_MenuHook;

CSize CCoolMenu::m_szMenuLogo = CSize(0, 0);		//主菜单左LOGO图像栏大小
CSize CCoolMenu::m_szMenuIcon = CSize(16, 16);		//图标大小
UINT CCoolMenu::nBackGroundbmpID=0;         //要填充菜单背景的位图ID
UINT CCoolMenu::m_uLogoBmpID = 0;			//主菜单左LOGO图像ID
UINT CCoolMenu::m_uBitmapID = 0;			//图像列表图像资源ID
DWORD CCoolMenu::m_dwStyle = 0;
CRect CCoolMenu::m_rcMenuItem = CRect(0, 0, 0, 0);

COLORREF CCoolMenu::m_crLogoColor        = RGB(0, 0, 255);			//LOGO图像的背景颜色
COLORREF CCoolMenu::m_crTextColor        = ::GetSysColor(COLOR_MENUTEXT);//字体颜色
COLORREF CCoolMenu::m_crMenuColor        = ::GetSysColor(COLOR_MENU);	//菜单颜色
COLORREF CCoolMenu::m_crIconBarColor     = ::GetSysColor(COLOR_MENU);	//图标栏背景颜色
COLORREF CCoolMenu::m_crLightBarColor    = RGB(234, 240, 250);		//光标条颜色
COLORREF CCoolMenu::m_crLightBarStartColor = RGB(234, 240, 250);
COLORREF CCoolMenu::m_crLightBarEndColor = RGB(196, 212, 239);
COLORREF CCoolMenu::m_crMarkColor        = RGB(255, 0, 255);			//
COLORREF CCoolMenu::m_crHighLightColor   = ::GetSysColor(COLOR_HIGHLIGHTTEXT);

CCoolMenu::CCoolMenu()
{

}

CCoolMenu::~CCoolMenu()
{
	ClearData();
}

/*========================================================================
	功能：	清除相关数据
==========================================================================*/
void CCoolMenu::ClearData()
{
	POSITION pos = m_obMenuList.GetHeadPosition();
	while (pos)
	{
		LPCOOLMENU lpMenu = (LPCOOLMENU)m_obMenuList.GetNext(pos);
		if (lpMenu != NULL)
		{
			delete lpMenu;
			lpMenu = NULL;
		}
	}
	m_obMenuList.RemoveAll();
}

void CCoolMenu::UnSubClass()
{
	m_MenuHook.HookWindow(HWND(NULL));
	m_uIDArray.RemoveAll();
	m_iImageList.DeleteImageList();
	m_iHotImageList.DeleteImageList();
	m_iDisabledImageList.DeleteImageList();
}

/*========================================================================
	功能：	初始化自绘菜单
	-----------------------------------------------
	nlevel: 当前菜单项级别,它们只能是以下值:
	-----------------------------------------
	-	MDS_TOP_MENU:		顶级菜单项
	-	MDS_TOP_SUBMENU:	主菜单项
	-	MDS_TOP_ENDSUBMENU:	主菜单的最后一项
	-	MDS_SUBMENU:		其他子菜单项
==========================================================================*/
BOOL CCoolMenu::ModifyStyle(HMENU hMenu, int nlevel)
{
	CMenu *pMenu = CMenu::FromHandle(hMenu);
	if (pMenu == NULL) return FALSE;
	UINT n = pMenu->GetMenuItemCount();
	for(UINT i = 0; i < n; i ++)
	{
		LPCOOLMENU lpMenu = new COOLMENU;

		lpMenu->nMenuLevel = nlevel;
		lpMenu->nMenuID = pMenu->GetMenuItemID(i);
		CString strText;
		pMenu->GetMenuString(i, strText, MF_BYPOSITION);
		lpMenu->SetItemName(strText);
		lpMenu->hMenu = pMenu->GetSafeHmenu();

		pMenu->ModifyMenu(	i, 
							MF_BYPOSITION | MF_OWNERDRAW,
							lpMenu->nMenuID, 
							LPCTSTR(lpMenu));
		m_obMenuList.AddTail((CObject *)lpMenu);//保存到对象列表中

		CMenu *pSubMenu = pMenu->GetSubMenu(i);

		if (nlevel == MDS_TOP_MENU)
		{
			if (lpMenu->nMenuID < 0 )
			{
				lpMenu->nMenuID = -2;
			}
			if(pSubMenu)
			{
				ModifyStyle(pSubMenu->GetSafeHmenu(),MDS_TOP_SUBMENU);
			}
		}
		else if (nlevel == MDS_TOP_SUBMENU)
		{
			if (i == n-1) lpMenu->nMenuLevel = MDS_TOP_ENDSUBMENU;

			if (pSubMenu != NULL)
			{
				lpMenu->nMenuID = -1;
				ModifyStyle(pSubMenu->GetSafeHmenu(),MDS_SUBMENU);
			}
		}
		else  
		{
			if (pSubMenu != NULL)
			{
				lpMenu->nMenuID = -1;
			}
			if (pSubMenu)
			{
				ModifyStyle(pSubMenu->GetSafeHmenu(),MDS_SUBMENU );
			}
		}
	}//End For
	
	return TRUE;
}

/*========================================================================
	功能：		载入菜单资源
	--------------------------------------------
	uMenuID:	菜单资源ID
	uToolBarID: 工具栏资源ID,用来提取图标资源
==========================================================================*/
BOOL CCoolMenu::LoadMenu(UINT uMenuID, UINT uToolBarID)
{
	ClearData();
	BOOL bRet = CMenu::LoadMenu(uMenuID);
	if (bRet)
	{
		//依次设置菜单为自绘风格并设置相关信息-------------
		ModifyStyle(GetSafeHmenu(), MDS_TOP_MENU);
		//从工具栏中添加图标资源---------------------------
		SetImageList(uToolBarID);
	}
	return bRet;
}

/*========================================================================
	功能：		将Windows菜单句柄连接到CCoolMenu对象.
	------------------------------------------------
	hMenu:		要连接的菜单名柄
	uToolBarID: 对应工具栏资源ID,用来提取图标资源
==========================================================================*/
BOOL CCoolMenu::Attach(HMENU hMenu, UINT uToolBarID)
{
	ClearData();
	BOOL bRet = CMenu::Attach(hMenu);
	if (bRet)
	{
		//依次设置菜单为自绘风格并设置相关信息-------------
		ModifyStyle(GetSafeHmenu(), MDS_TOP_MENU);
		//从工具栏中添加图标资源---------------------------
		SetImageList(uToolBarID);
	}
	return bRet;
}

/*========================================================================
	功能：		断开与菜单句柄的连接并清除相关数据
==========================================================================*/
HMENU CCoolMenu::Detach()
{
	ClearData();
	return CMenu::Detach();
}

/*========================================================================
	功能:		添加菜单项
	-------------------------------------------
	uID:		菜单ID
	strText:	菜单文本
	nlevel:		菜单级别,请参考相关函数
==========================================================================*/
void CCoolMenu::AppendMenu(UINT uFlags, UINT uNewMenuItemID, CString strNewMenuItem, int nlevel)
{
	LPCOOLMENU lpMenu = new COOLMENU;
	lpMenu->nMenuID = uNewMenuItemID;
	lpMenu->strText = strNewMenuItem;
	lpMenu->nMenuLevel = nlevel;
	CMenu::AppendMenu(MF_BYPOSITION | MF_OWNERDRAW | uFlags, lpMenu->nMenuID, LPCTSTR(lpMenu));
	m_obMenuList.AddTail((CObject *)lpMenu);
}

/*========================================================================
	功能:	子类化指定窗口
==========================================================================*/
void CCoolMenu::SubClass(HWND hwnd)
{
	m_MenuHook.HookWindow(hwnd);
}

/*########################################################################
					-----------------------
							绘制菜单	
					-----------------------
  ########################################################################*/

/*========================================================================
	功能：	计算菜单大小
	--------------------------------------------
	lpMIS:	LPMEASUREITEMSTRUCT结构体
==========================================================================*/
void CCoolMenu::MeasureItem(LPMEASUREITEMSTRUCT lpMIS)
{
	LPCOOLMENU lpMenu = (LPCOOLMENU)(lpMIS->itemData);
	
	//分隔条---------------------------------
	if(lpMenu->nMenuID == 0)
	{
		lpMIS->itemHeight = 5;
		lpMIS->itemWidth = 50;
		return;
	}

	//非分隔条-------------------------------
	lpMIS->itemWidth = 50; // default width
	lpMIS->itemHeight = 19;

	CString strText = lpMenu->strText + lpMenu->strKeyName;
	int nLen = strText.GetLength();
	if (nLen > 0)
	{
	//计算绘制菜单文本所需宽度-------------------
		
		CFont fontMenu;
		LOGFONT lf;
		ZeroMemory(&lf, sizeof(LOGFONT));
		NONCLIENTMETRICS nm;
		nm.cbSize = sizeof(NONCLIENTMETRICS);
		VERIFY(SystemParametersInfo(SPI_GETNONCLIENTMETRICS, nm.cbSize, &nm, 0)); 
		lf = nm.lfMenuFont;
		fontMenu.CreateFontIndirect(&lf);
		
		CDC *pDC = AfxGetMainWnd()->GetDC();
		CFont *old = pDC->SelectObject(&fontMenu);
		CSize sz = pDC->GetTextExtent(lpMenu->strText);  
		pDC->SelectObject(&old);
		AfxGetMainWnd()->ReleaseDC(pDC);
		fontMenu.DeleteObject();

		//调整有快捷键提示的菜单的宽度，使宽度适中-------------
		if (lpMenu->strKeyName != "") sz.cx += (62 - (strText.GetLength() % 8) * (sz.cx/strText.GetLength()));
		
		if(lpMenu->nMenuID == -2)
		{
			//顶级菜单宽度---------------------------
			lpMIS->itemWidth = sz.cx - 6;
		}
		else if (lpMenu->nMenuLevel <= MDS_TOP_SUBMENU)
		{
			//主菜单项宽度---------------------------
			lpMIS->itemWidth = sz.cx + m_szMenuLogo.cx + m_szMenuIcon.cx + MENU_SPACE * 5;
		}
		else 
		{
			//普通菜单宽度---------------------------
			lpMIS->itemWidth = sz.cx  + m_szMenuIcon.cx + MENU_SPACE * 5;
		}
	}

}

/*========================================================================
	功能：		获取菜单命令ID对应的图标序列号
	----------------------------------------------
	uID:		菜单命令ID
==========================================================================*/
int CCoolMenu::GetIndex(UINT uID)
{
	for(int i = 0; i < m_uIDArray.GetSize(); i ++)
	{
		if(uID == m_uIDArray[i])
		{
			if (i >= m_iImageList.GetImageCount()) return -1;
			return i;
		}
	}
	return -1;
}

/*========================================================================
	功能:		绘制菜单
	------------------------------------------------
	lpDIS:		自绘信息结构体
==========================================================================*/
void CCoolMenu::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
	LPCOOLMENU lpMenu = (LPCOOLMENU)(lpDIS->itemData);
	if(!AfxIsValidAddress(lpMenu, sizeof(COOLMENU))) return ;

	CDC *pdc = CDC::FromHandle(lpDIS->hDC);
	const CRect rect = lpDIS->rcItem;
//#ifdef _DEBUG
//    CMemoryState oldmem,newmem,diff;
//	oldmem.Checkpoint();
//#endif
	//建立内存上下文---------------------------------------	
	CDC *pDC = new CDC();
//#ifdef _DEBUG
//	newmem.Checkpoint();
//	if(diff.Difference(oldmem,newmem))
//	{
//		ASSERT(0);
//	}
//#endif
	pDC->CreateCompatibleDC(pdc);
	CBitmap *bitmap, *oldbitmap;
	bitmap = new CBitmap;
	bitmap->CreateCompatibleBitmap(pdc,rect.right, rect.bottom);//improtant
	oldbitmap = pDC->SelectObject(bitmap);

	//把菜单字体选入内存设备上下文-----------------------------
	CFont fontMenu, *oldfont;
	LOGFONT lf;
	ZeroMemory(&lf, sizeof(LOGFONT));
	NONCLIENTMETRICS nm;
	nm.cbSize = sizeof(NONCLIENTMETRICS);
	VERIFY(SystemParametersInfo(SPI_GETNONCLIENTMETRICS, nm.cbSize, &nm, 0)); 
	lf = nm.lfMenuFont;
//	lf.lfUnderline=true; 

	fontMenu.CreateFontIndirect(&lf);
	oldfont = pDC->SelectObject(&fontMenu);

	pDC->SetBkColor(m_crMenuColor);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SelectStockObject(NULL_BRUSH);

    //用位图填充菜单背景
//	CRect rect2;
//	rect2.left+=m_szMenuLogo.cx;
//    DrawBackGroundBmp(pdc,rect2,true);

	//当当前菜单为主菜单时，空出左边用于绘制LOGO图片----------
	int nMenuLogoBarcx = 0;	//左边LOGO栏宽度
	if (lpMenu->nMenuLevel <= MDS_TOP_SUBMENU) nMenuLogoBarcx = m_szMenuLogo.cx;

	//绘制LOGO图片----------------------------
	if (nMenuLogoBarcx > 0 && (lpDIS->itemAction & ODA_DRAWENTIRE) 
		&& lpMenu->nMenuLevel != MDS_TOP_SUBMENU)
	{
		DrawLogoBar(pdc, CRect(0, 0, m_szMenuLogo.cx, rect.bottom));
	}

	//取得菜单状态----------------------------
	BOOL bIsSelected = (lpDIS->itemState & ODS_SELECTED);
	BOOL bIsChecked  = (lpDIS->itemState & ODS_CHECKED);
	BOOL bIsGrayed   = (lpDIS->itemState & ODS_GRAYED);
	BOOL bIsHotLight  = (lpDIS->itemState & ODS_HOTLIGHT );

	//擦除背景---------------------------------
	CRect rc = rect;
	rc.left += nMenuLogoBarcx;
	if (lpMenu->nMenuID == -2)//顶级菜单-------
	{
		CBrush Brush(::GetSysColor(COLOR_3DFACE));//即是非弹出菜单
		pDC->FillRect(rc, &Brush);
	}
	else//非顶级菜单---------------------------
	{
		CBrush Brush(m_crMenuColor);
		pDC->FillRect(rc, &Brush);
	}

	//绘制Office XP风格的图标栏灰色背景------------
	if (lpMenu->nMenuID != -2 && (GetStyle() & CMS_ICONBAR != 0) && nMenuLogoBarcx == 0)
	{
		rc.right = rc.left + m_szMenuIcon.cx + MENU_SPACE*2 - 1;
		pDC->FillSolidRect(rc,m_crIconBarColor);
	}

	//绘制分隔条-----------------------------------
	if(lpMenu->nMenuID == 0)
	{
		rc = rect;
		rc.top += rect.Height()/2; //居矩形区域中间
		rc.bottom = rc.top + 2;	//高两个象素
		rc.left += (nMenuLogoBarcx + MENU_SPACE); //空出左边LOGO栏区
		if ((GetStyle() & CMS_ICONBAR != 0) && nMenuLogoBarcx == 0) 
		{
			//在XP风格下空出左边图标栏区域----------
			rc.left += (m_szMenuIcon.cx + MENU_SPACE);
		}

		pDC->Draw3dRect(rc, ::GetSysColor(COLOR_GRAYTEXT), RGB(240, 240, 240));
	}
	else
	{
	//显示菜单文字-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

		//禁止菜单========================================================
		if(bIsGrayed) 
		{
			rc = rect;
			rc.left += nMenuLogoBarcx; //空出左边LOGO栏区域
			
			// 菜单被选择----------------------------------
			if(bIsSelected) 
			{
			//	DrawLightBar(pDC, rc, FALSE);
			}

			//菜单文本----------------------------
			if(lpMenu->strText.GetLength() > 0)
			{
				rc.left += (m_szMenuIcon.cx + MENU_SPACE*3 + 1); 
				rc.top += 2;
				rc.right -= 11;//调节快捷方式的宽度"ctrl+o"
				//绘制立体字---------------------------
				pDC->SetTextColor(::GetSysColor(COLOR_3DLIGHT));
				pDC->DrawText(lpMenu->strText, &rc, DT_EXPANDTABS | DT_VCENTER | DT_SINGLELINE);
				pDC->DrawText(lpMenu->strKeyName, &rc, DT_EXPANDTABS | DT_VCENTER | DT_SINGLELINE | DT_RIGHT);
			
				pDC->SetTextColor(::GetSysColor(COLOR_GRAYTEXT));
				rc.InflateRect(1,1,-1,-1);
				pDC->DrawText(lpMenu->strText, &rc, DT_EXPANDTABS | DT_VCENTER | DT_SINGLELINE);
				pDC->DrawText(lpMenu->strKeyName, &rc, DT_EXPANDTABS | DT_VCENTER | DT_SINGLELINE | DT_RIGHT);
			}
			
		}
	//非禁止菜单==========================================================
		else 
		{
			//顶层菜单------------------------------------------
			if (lpMenu->nMenuID == -2) 
			{
				rc = rect;
				rc.right -= 4;
				
				m_rcMenuItem = rect;

				//选择状态----------------------------
				if (bIsSelected) 
				{
					DrawMenuBar(pDC, rect);
					pDC->SetTextColor(::GetSysColor(COLOR_MENUTEXT));
					m_rcMenuItem = rect;
					CRect rcFram; 
					AfxGetMainWnd()->GetWindowRect(&rcFram);
					m_rcMenuItem.OffsetRect(rcFram.TopLeft());
				}

				//焦点状态----------------------------
				else if (bIsHotLight)  
				{
					DrawLightBar(pDC, rc);
					pDC->SetTextColor(m_crHighLightColor);
					m_rcMenuItem.SetRectEmpty();
				}

				//正常状态----------------------------
				else 
				{
					pDC->SetTextColor(::GetSysColor(COLOR_MENUTEXT));
					m_rcMenuItem.SetRectEmpty();
				}

				//菜单文本----------------------------
				if(lpMenu->strText.GetLength() > 0)
				{
					pDC->DrawText(lpMenu->strText, &rc, DT_EXPANDTABS | DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
			}
			//非顶层菜单,是弹出菜单或者一个菜单项目---------------
			else 
			{
				rc = rect;
				rc.left += nMenuLogoBarcx;
				//选择状态-----------------------------
				if(bIsSelected)
				{
					DrawLightBar(pDC, rc);
					pDC->SetTextColor(m_crHighLightColor);
				}
				//非选择状态---------------------------
				else
				{
					pDC->SetTextColor(m_crTextColor);
				}

				//菜单文本----------------------------
				if(lpMenu->strText.GetLength() > 0)
				{
					rc.left += (m_szMenuIcon.cx + MENU_SPACE*3);
					rc.right -= 12;
					pDC->DrawText(lpMenu->strText, &rc, DT_EXPANDTABS |
						DT_VCENTER | DT_SINGLELINE);
					pDC->DrawText(lpMenu->strKeyName, &rc, DT_EXPANDTABS | 
						DT_VCENTER | DT_SINGLELINE | DT_RIGHT);
				}
			}
		}

	//<<绘制图标或Check标志-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

		rc = rect;
		rc.left += (nMenuLogoBarcx + MENU_SPACE -1);
		rc.top += ((rect.Height() - m_szMenuIcon.cy)/2 + 1);
		rc.right = rc.left + m_szMenuIcon.cx;
		rc.bottom = rc.top + m_szMenuIcon.cy;

		int nIndex = GetIndex(lpMenu->nMenuID);

		//如果有图标------------------------------------------
		if(nIndex >= 0) 
		{
			//画图标Check框-----------------------------------
			if(bIsChecked)
			{
				CRect rcc = rect;
				rcc.left += nMenuLogoBarcx;
				rcc.right = rcc.left + rect.Height() + 1;
				if (bIsSelected)
				{
				//	rcc.InflateRect(-1,-1);
				//	pDC->FillSolidRect(rcc,m_crMenuColor);
				//	pDC->Draw3dRect(rcc, RGB(255,255,255), TOP_COLOR);
				}
				else 
				{
					pDC->FillSolidRect(rcc,RGB(235,235,235));
					pDC->Draw3dRect(rc, RGB(160,170,210), RGB(160,170,210));
				}
			}

			
			//绘制图标-------------------------------------
			if (bIsGrayed)
			{
				m_iDisabledImageList.Draw(pDC, nIndex, CPoint(rc.left, rc.top), ILD_TRANSPARENT);
			}
			else if(bIsSelected)
			{
				m_iHotImageList.Draw(pDC, nIndex, CPoint(rc.left, rc.top), ILD_TRANSPARENT);
			}
			else
			{
				m_iImageList.Draw(pDC, nIndex, CPoint(rc.left, rc.top), ILD_TRANSPARENT);
			}
		}

		//如果没有图标---------------------------------------
		else 
		{
			// 绘制Check标志-------------------------
			if(bIsChecked)
			{
				rc.InflateRect(-1, 0, 0, -1);

				if(bIsSelected)
				{
					pDC->FillSolidRect(rc,RGB(255,255,255));
					pDC->Draw3dRect(rc, RGB(160,170,210), RGB(160,170,210));
				}
				else
				{
					pDC->FillSolidRect(rc,RGB(235,235,235));
					pDC->Draw3dRect(rc, RGB(160,170,210), RGB(160,170,210));
				}

				//画勾号----------------------------
				pDC->MoveTo(rc.left + 4,  rc.top + 6);
				pDC->LineTo(rc.left + 6,  rc.top + 8);
				pDC->LineTo(rc.left + 11, rc.top + 3);
				pDC->MoveTo(rc.left + 4,  rc.top + 7);
				pDC->LineTo(rc.left + 6,  rc.top + 9);
				pDC->LineTo(rc.left + 11, rc.top + 4);
			}
		}
		//---------结束绘制图标或Check标志>>>
	}

	//扫尾工作-------------------------------------------
	pdc->BitBlt(rect.left + nMenuLogoBarcx, rect.top, rect.Width() - nMenuLogoBarcx, rect.Height(), 
					pDC, rect.left + nMenuLogoBarcx, rect.top, SRCCOPY);
	pDC->SelectObject(&oldfont);
	pDC->SelectObject(oldbitmap);
	if (pDC != NULL) delete pDC;
	if (bitmap != NULL) delete bitmap;

}

void CCoolMenu::DrawMenuBar(CDC *pDC, CRect rect)
{
	rect.right -= 4;
	
//	pDC->FillSolidRect(rect, m_crIconBarColor);
	pDC->Draw3dRect(rect, ::GetSysColor(COLOR_3DDKSHADOW), ::GetSysColor(COLOR_3DDKSHADOW));

	//Draw shadow----------------------------------------->>
	COLORREF oldcolor = ::GetSysColor(COLOR_3DFACE);
	BYTE AlphaArray[] ={90,210, 222, 240};
	
	for (int i = 0; i < 4; i++)
	{
		BYTE newR = GetRValue(oldcolor) * AlphaArray[i] / 255;  
		BYTE newG = GetGValue(oldcolor) * AlphaArray[i] / 255;  
		BYTE newB = GetBValue(oldcolor) * AlphaArray[i] / 255;  
		CPen pen(0, 1, RGB(newR, newG, newB));
		CPen *oldpen = pDC->SelectObject(&pen);
		pDC->MoveTo(rect.right + i, rect.top + i + 3);
		pDC->LineTo(rect.right + i, rect.bottom );
		pDC->SelectObject(oldpen);
	}
}

/*========================================================================
	功能：	绘制光标条
	-----------------------------------------
	rect:	绘制范围
==========================================================================*/
void CCoolMenu::DrawLightBar(CDC *pDC, CRect rect, BOOL bfill)
{
	if (bfill)
	{
		//绘制渐变色----------------------------------------
		FillGradient(pDC, rect, m_crLightBarStartColor, m_crLightBarEndColor);
//		DrawGradsRect(pDC,rect,m_crLightBarStartColor,m_crLightBarEndColor);
	}

	pDC->Draw3dRect(rect, m_crLightBarColor, m_crLightBarColor);
}

/*========================================================================
	功能：	绘制LOGO栏
	--------------------------------------------
	pDC:	设备上下文
	rect:	绘制范围
==========================================================================*/
void CCoolMenu::DrawLogoBar(CDC *pDC, CRect rect)
{
	if (m_szMenuLogo.cx > 0)
	{
		//如果设置了LOGO图片------------------------------------
		if(m_uLogoBmpID != NULL)
		{
			CDC memDC;
			memDC.CreateCompatibleDC(pDC);
			CBitmap bitmap, *oldbitmap;
			bitmap.LoadBitmap(m_uLogoBmpID);
			if (bitmap.GetSafeHandle() != NULL)
			{
				oldbitmap = memDC.SelectObject(&bitmap);
				pDC->BitBlt(rect.left, rect.bottom-m_szMenuLogo.cy, m_szMenuLogo.cx, m_szMenuLogo.cy,
							&memDC, 0, 0, SRCCOPY);	
				memDC.SelectObject(oldbitmap);
				bitmap.DeleteObject();
				memDC.DeleteDC();
				//如果图片比要填充的矩形小，则继续用此图片填充剩下的矩形，直到填满为止----------
				if(rect.Height() > m_szMenuLogo.cy) DrawLogoBar(pDC, CRect(0, 0, rect.right, (rect.Height() - m_szMenuLogo.cy)));
			}
		}

		//如果没有设置LOGO图片，则以渐变色和LOGO字串绘制LOGO栏--
		else 
		{
			//绘制渐变色--------------------------------
			FillGradient(pDC, rect, RGB(90, 90, 90), m_crLogoColor);
					
			//绘制LOGO字串---------------------------------
			CFont	vertFont;
			vertFont.CreateFont(14, 0, 900, 900, FW_BOLD,
				0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
				CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
				DEFAULT_PITCH, "Arial");
			CFont *pOldFont = pDC->SelectObject(&vertFont);
			pDC->SetTextColor(RGB(255, 255, 255));
			pDC->SetBkMode(TRANSPARENT);
			pDC->TextOut(rect.left+3, rect.bottom-4, m_sLogoText);
			pDC->SelectObject(pOldFont);
			vertFont.DeleteObject();
		}
	}
}

/*########################################################################
						-----------------------
							设置菜单LOGO栏	
						-----------------------
  ########################################################################*/

/*========================================================================
	功能:	设置LOGO字串及背景渐变色
==========================================================================*/
void CCoolMenu::SetLogoText(CString strText, COLORREF color)
{
	m_sLogoText  = strText;
	m_crLogoColor = color;
	m_szMenuLogo.cx = 20;
}

/*========================================================================
	功能：			设置LOGO图片
	--------------------------------------------
	uID：			LOGO图片ID
	width：			LOGO栏宽度，如果为0，则把图片的宽度作为LGOG栏宽度
==========================================================================*/
BOOL CCoolMenu::SetLogoImage(UINT uBitmapID, int nwidth)
{
	if (uBitmapID == NULL) 
	{
		m_uLogoBmpID = 0;
		return FALSE;
	}
	CBitmap bitmap;
	bitmap.LoadBitmap(uBitmapID);
	if(bitmap.GetSafeHandle() != NULL)
	{
		BITMAP bm;
		bitmap.GetBitmap(&bm);
		if (nwidth == 0) m_szMenuLogo.cx = bm.bmWidth;
		else m_szMenuLogo.cx = nwidth;
		m_szMenuLogo.cy = bm.bmHeight;
		m_uLogoBmpID = uBitmapID;
		bitmap.DeleteObject();
	}
	else
	{
		m_uLogoBmpID = 0;
		m_szMenuLogo = CSize(0, 0);
	}
	return TRUE;
}

/*########################################################################
					-----------------------
						设置菜单图像列表	
					-----------------------
  ########################################################################*/

/*========================================================================
	功能:			设置菜单图像列表.
	------------------------------------------------------------	
	uToolBarID:		对应用来提取命令ID工具栏资源的ID.
	uBitmapID:		图像资源ID.
	bAlpha:			是否有alpha通道.
==========================================================================*/
int CCoolMenu::SetImageList(UINT uToolBarID, UINT uBitmapID, BOOL bAlpha)
{
	if (uToolBarID != NULL)
	{
		if (uBitmapID == NULL)
		{
			m_uBitmapID = uToolBarID;
			m_crMarkColor = RGB(192, 192, 192);
		}
		else
		{
			m_uBitmapID = uBitmapID;
			m_crMarkColor = RGB(255, 0, 255);
		}
		
		if (bAlpha) 
		{
			m_dwStyle |= CMS_32IMAGELIST;
		}
		else 
		{
			m_dwStyle &= ~CMS_32IMAGELIST;
		}
		InitImageList();
		m_uIDArray.RemoveAll();
		return GetIDFromToolBar(uToolBarID, &m_uIDArray);
	}
	return -1;
}

/*========================================================================
	功能:	初始化图像列表
==========================================================================*/
BOOL CCoolMenu::InitImageList()
{
	CBitmap bitmap, tempbitmap;
	CSize szIcon(16, 16);

	bitmap.LoadBitmap(m_uBitmapID);
	if (bitmap.GetSafeHandle() == NULL)
	{
		return FALSE;
	}
	
	m_iImageList.DeleteImageList();
	m_iHotImageList.DeleteImageList();
	m_iDisabledImageList.DeleteImageList();

	m_iImageList.Create(szIcon.cx, szIcon.cy, ILC_COLOR24 | ILC_MASK, 16, 16);
	m_iHotImageList.Create(szIcon.cx, szIcon.cy, ILC_COLOR24 | ILC_MASK, 16, 16);
	m_iDisabledImageList.Create(szIcon.cx, szIcon.cy, ILC_COLOR24 |ILC_MASK, 16, 16);

	BOOL bAlpha = ((GetStyle() & CMS_32IMAGELIST) == CMS_32IMAGELIST);

	//创建正常图像列表----------------------------------------
	HBITMAP bm = NULL;

	
	if ((GetStyle() & CMS_ICONBAR) == 0)
	{
		bm =CCoolMenu::CreateImage(HBITMAP(bitmap), 1, bAlpha, m_crMenuColor, m_crMarkColor);
	}
	else
	{
		bm = CCoolMenu::CreateImage(HBITMAP(bitmap), 1, bAlpha, m_crIconBarColor, m_crMarkColor);
	}
	tempbitmap.Attach(bm);
	m_iImageList.Add(&tempbitmap, RGB(255, 0, 255));
	
	//创建禁止图像列表----------------------------------------
	tempbitmap.DeleteObject();
	if (GetStyle() & CMS_ICONBAR == 0)
	{
		bm = CCoolMenu::CreateImage(HBITMAP(bitmap), 0, bAlpha, m_crMenuColor, m_crMarkColor);
	}
	else
	{
		bm = CCoolMenu::CreateImage(HBITMAP(bitmap), 0, bAlpha, m_crIconBarColor, m_crMarkColor);
	}
	tempbitmap.Attach(bm);
	m_iDisabledImageList.Add(&tempbitmap, RGB(255, 0, 255));

	//创建热图像列表----------------------------------------
	tempbitmap.DeleteObject();

	bm = CCoolMenu::CreateImage(HBITMAP(bitmap), 2, bAlpha, m_crLightBarStartColor, m_crMarkColor);
	tempbitmap.Attach(bm);
	m_iHotImageList.Add(&tempbitmap, RGB(255, 0, 255));

	bitmap.DeleteObject();
	return TRUE;
}

/*========================================================================
	功能：			从工具栏资源中提取命令ID
	---------------------------------------------
	uToolBarID：	工具栏资源ID
	uIDArray：		用于存贮ID列表的数组指针
==========================================================================*/
int CCoolMenu::GetIDFromToolBar(UINT uToolBarID, CUIntArray *uIDArray)
{
	if (uToolBarID <= 0 || uIDArray == NULL) return -1;

	struct CToolBarData
	{
		WORD wVersion;
		WORD wWidth;
		WORD wHeight;
		WORD wItemCount;
		WORD* items()
		{
			return (WORD*)(this + 1); 
		}
	};
	
	ASSERT(MAKEINTRESOURCE(uToolBarID) != NULL);

	HINSTANCE hInst = AfxFindResourceHandle(MAKEINTRESOURCE(uToolBarID), RT_TOOLBAR);
	HRSRC hRsrc = ::FindResource(hInst, MAKEINTRESOURCE(uToolBarID), RT_TOOLBAR);
	if (hRsrc == NULL)
	{
		return -1;
	}

	HGLOBAL hGlobal = LoadResource(hInst, hRsrc);
	if (hGlobal == NULL)
	{
		return -1;
	}

	CToolBarData* pData = (CToolBarData*)LockResource(hGlobal);
	if (pData == NULL)
	{
		return -1;
	}
	ASSERT(pData->wVersion == 1);
	UINT uID;
	for (int i = 0; i < pData->wItemCount; i++)
	{
		uID = pData->items()[i];
		if (uID != ID_SEPARATOR)
		{
			uIDArray->Add(uID);
		}
	}

	UnlockResource(hGlobal);
	FreeResource(hGlobal);

	return uIDArray->GetSize();
}

/*########################################################################
			  ------------------------------------------------
								class CMenuWndHook
			  ------------------------------------------------
  ########################################################################*/
CMap <HWND, HWND, CMenuWndHook*, CMenuWndHook*> CMenuWndHook::m_WndMenuMap;
HHOOK CMenuWndHook::m_hMenuHook = NULL;
COLORREF CMenuWndHook::m_crFrame[4] = {::GetSysColor(COLOR_3DDKSHADOW), ::GetSysColor(COLOR_3DDKSHADOW), ::GetSysColor(COLOR_WINDOW), ::GetSysColor(COLOR_WINDOW)};

CMenuWndHook::CMenuWndHook (HWND hWnd)
: m_hWnd(hWnd), m_rcMenu(0, 0, 0, 0), m_ptMenu(-0xFFFF, -0xFFFF)
{

}

CMenuWndHook::~CMenuWndHook ()
{
    WNDPROC oldWndProc = (WNDPROC)::GetProp(m_hWnd, CoolMenu_oldProc);
    if (oldWndProc != NULL)
    {
        ::SetWindowLong(m_hWnd, GWL_WNDPROC, (DWORD)(ULONG)oldWndProc);
        ::RemoveProp(m_hWnd, CoolMenu_oldProc);
    }
    m_WndMenuMap.RemoveKey(m_hWnd);
}

void CMenuWndHook::InstallHook()
{
    if (m_hMenuHook == NULL )
    {
        m_hMenuHook = ::SetWindowsHookEx(WH_CALLWNDPROC, WindowHook, 
						AfxGetApp()->m_hInstance, ::GetCurrentThreadId());
    }
}

void CMenuWndHook::UnInstallHook()
{
    POSITION pos = m_WndMenuMap.GetStartPosition();
    while (pos != NULL)
    {
        HWND hwnd;
        CMenuWndHook* pMenuWndHook;
        m_WndMenuMap.GetNextAssoc(pos, hwnd, pMenuWndHook);
        delete pMenuWndHook;
		pMenuWndHook = NULL;
    }
    m_WndMenuMap.RemoveAll();
	
    if (m_hMenuHook != NULL)
    {
        ::UnhookWindowsHookEx(m_hMenuHook);
    }
}

CMenuWndHook* CMenuWndHook::GetWndHook(HWND hwnd)
{
    CMenuWndHook* pWnd = NULL;
    if (m_WndMenuMap.Lookup(hwnd, pWnd))
    {
        return pWnd;
    }
    return NULL;
}

CMenuWndHook* CMenuWndHook::AddWndHook(HWND hwnd)
{
	CMenuWndHook* pWnd = NULL;
	if (m_WndMenuMap.Lookup(hwnd, pWnd))
	{
	   return pWnd;
	}

	pWnd = new CMenuWndHook(hwnd);
	if (pWnd != NULL)
	{
		m_WndMenuMap.SetAt(hwnd, pWnd);
	}
	return pWnd;
}
/*########################################################################
			  ------------------------------------------------
								  消息过程
			  ------------------------------------------------
  ########################################################################*/
LRESULT CALLBACK CMenuWndHook::WindowHook(int code, WPARAM wParam, LPARAM lParam)
{
    CWPSTRUCT* pStruct = (CWPSTRUCT*)lParam;
	
    while (code == HC_ACTION)
    {
        HWND hWnd = pStruct->hwnd;
		
        if (pStruct->message != WM_CREATE && pStruct->message != 0x01E2)
        {
            break;
        }

        // 是否为菜单类 ----------------------------------------
        TCHAR strClassName[10];
        int Count = ::GetClassName (hWnd, strClassName, sizeof(strClassName) / sizeof(strClassName[0]));
        if (Count != 6 || _tcscmp(strClassName, _T("#32768")) != 0 )
        {
            break;
        }
		
		// 是否已经被子类化 ------------------------------------
        if (::GetProp(pStruct->hwnd, CoolMenu_oldProc) != NULL )
        {
            break;
        }
        VERIFY(AddWndHook(pStruct->hwnd) != NULL);

        // 取得原来的窗口过程 ----------------------------------
        WNDPROC oldWndProc = (WNDPROC)(long)::GetWindowLong(pStruct->hwnd, GWL_WNDPROC);
        if (oldWndProc == NULL)
        {
            break;
        }
		
        ASSERT(oldWndProc != CoolMenuProc);
        // 保存到窗口的属性中 ----------------------------------
        if (!SetProp(pStruct->hwnd, CoolMenu_oldProc, oldWndProc) )
        {
            break;
        }

        // 子类化 ----------------------------------------------
        if (!SetWindowLong(pStruct->hwnd, GWL_WNDPROC,(DWORD)(ULONG)CoolMenuProc) )
        {
            ::RemoveProp(pStruct->hwnd, CoolMenu_oldProc);
            break;
        }
        break;
    }
    return CallNextHookEx (m_hMenuHook, code, wParam, lParam);
}

LRESULT CALLBACK CMenuWndHook::CoolMenuProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	WNDPROC oldWndProc = (WNDPROC)::GetProp(hWnd, CoolMenu_oldProc);
    CMenuWndHook* pWnd = NULL;
	
    switch (uMsg)
    {
		case WM_NCCALCSIZE:
			{
				LRESULT lResult = CallWindowProc(oldWndProc, hWnd, uMsg, wParam, lParam);
				if ((pWnd = GetWndHook(hWnd)) != NULL)
				{
					pWnd->OnNcCalcsize((NCCALCSIZE_PARAMS*)lParam);
				}
				return lResult;
			}
			break;
		case WM_WINDOWPOSCHANGING:
			{
				if ((pWnd = GetWndHook(hWnd)) != NULL)
				{
					pWnd->OnWindowPosChanging((LPWINDOWPOS)lParam);
				}
			}
			break;
		case WM_PRINT:
			{
				LRESULT lResult = CallWindowProc(oldWndProc, hWnd, uMsg, wParam, lParam);
				if ((pWnd = GetWndHook(hWnd)) != NULL)
				{
					pWnd->OnPrint(CDC::FromHandle((HDC)wParam));
				}
				return lResult;
			}
			break;
		case WM_NCPAINT:
			{
				if ((pWnd = GetWndHook(hWnd)) != NULL)
				{
					pWnd->OnNcPaint();
					return 0;
				}
			}
			break;
		case WM_SHOWWINDOW:
			{
				if ((pWnd = GetWndHook(hWnd)) != NULL)
				{
					pWnd->OnShowWindow(wParam != NULL);
				}
			}
			break;
		case WM_NCDESTROY:
			{
				if ((pWnd = GetWndHook(hWnd)) != NULL)
				{
					pWnd->OnNcDestroy();
				}
			}
			break;
    }
    return CallWindowProc(oldWndProc, hWnd, uMsg, wParam, lParam);
}

/*########################################################################
			  ------------------------------------------------
								消息处理函数	
			  ------------------------------------------------
  ########################################################################*/
void CMenuWndHook::OnWindowPosChanging(WINDOWPOS *pWindowPos)
{
	if (!IsShadowEnabled())
	{
		pWindowPos->cx += 4;
		pWindowPos->cy += 4;
	}
	pWindowPos->cx -= 2;
	pWindowPos->cy -= 2;

    pWindowPos->y--;
    m_ptMenu.x = pWindowPos->x;
    m_ptMenu.y = pWindowPos->y;
	
	if (!IsWindowVisible(m_hWnd))
    {
		CRect rc;
		GetClientRect(m_hWnd, &rc);
		
        if (m_bmpBack.m_hObject != NULL )
        {
            m_bmpBack.DeleteObject();
        }
        m_bmpBack.Attach(GetScreenBitmap(CRect(m_ptMenu.x, m_ptMenu.y, rc.right + m_ptMenu.x + 10,
			rc.bottom + m_ptMenu.y + 10)));
    }
}

void CMenuWndHook::OnNcPaint()
{
    CWindowDC dc(CWnd::FromHandle(m_hWnd));
	OnPrint(&dc);
}

void CMenuWndHook::OnPrint(CDC *pDC)
{
	CRect rc;
	GetWindowRect(m_hWnd, &rc);
    rc.OffsetRect(-rc.TopLeft());
	
    if (rc != m_rcMenu)
    {
        m_rcMenu = rc;
		if (!IsShadowEnabled())
		{
			CDC cMemDC;
			cMemDC.CreateCompatibleDC (pDC);
			HGDIOBJ hOldBitmap = ::SelectObject (cMemDC.m_hDC, m_bmpBack);
			pDC->BitBlt (0, rc.bottom - 4, rc.Width() - 4, 4, &cMemDC, 0, rc.bottom - 4, SRCCOPY);
			pDC->BitBlt (rc.right - 4, 0, 4, rc.Height(), &cMemDC, rc.right - 4, 0, SRCCOPY);
			
			DrawShadow(pDC, rc);
			rc.right -= 4;
			rc.bottom -= 4;
		}
		pDC->Draw3dRect(rc, m_crFrame[0], m_crFrame[1]);
		
		rc.DeflateRect (1, 1);
		pDC->Draw3dRect(rc, m_crFrame[2], m_crFrame[3]);
		
		#if defined(_ANYOU_COOLMENU_H)
		if (CCoolMenu::m_rcMenuItem.bottom == (m_ptMenu.y + 1) && CCoolMenu::m_rcMenuItem.Width() > 0)
		{
			CPen pen(0, 1, ::GetSysColor(COLOR_3DFACE));
			CPen *oldpen = pDC->SelectObject(&pen);
			pDC->MoveTo(m_rcMenu.left + 1, m_rcMenu.top);
			pDC->LineTo(CCoolMenu::m_rcMenuItem.Width() - 5, m_rcMenu.top);
			pDC->SelectObject(oldpen);
		}
		#endif
    }
}

void CMenuWndHook::OnNcDestroy()
{
	delete this;
}

void CMenuWndHook::OnShowWindow(BOOL bShow)
{
    if (!bShow)
    {
        delete this;
    }
}

void CMenuWndHook::OnNcCalcsize(NCCALCSIZE_PARAMS* lpncsp)
{
	if (!IsShadowEnabled())
	{
		 lpncsp->rgrc[0].right -= 4;
		 lpncsp->rgrc[0].bottom -= 4;
	}
	lpncsp->rgrc[0].top -= 1;
	lpncsp->rgrc[0].left -= 1;
	lpncsp->rgrc[0].right += 1;
	lpncsp->rgrc[0].bottom += 1;
}


CCoolMenuTheme::CCoolMenuTheme()
{

}

CCoolMenuTheme::~CCoolMenuTheme()
{
	
}

/*========================================================================
	功能:			设置菜单预置风格
	----------------------------------------------------------
	dwstyle:		风格名,只能是以下值之一:
	-------------------------------------------
	-	MENU_STYLE_DEFAULT:		默认风格
	-	MENU_STYLE_XP:			Office XP 风格
	-	MENU_STYLE_XP2:			另一种 Office XP 风格
	-	MENU_STYLE_SNOW:		白色风格
	-	MENU_STYLE_GREEN:		绿色风格
	-	MENU_STYLE_BLUE:		蓝色风格
	-	...				...
	----------------------------------------------------------
	说明:			可以在这个函数里添加代码，添加更多的自定义
			风格，以便在使用菜单时，可以很快地切换成想要的菜单
			风格。
==========================================================================*/
void CCoolMenuTheme::SetTheme(DWORD dwstyle)
{
	if (dwstyle == MENU_STYLE_DEFAULT)
	{
		CCoolMenu::SetStyle(CCoolMenu::GetStyle() & ~CMS_ICONBAR);
		CCoolMenu::SetMenuColor(::GetSysColor(COLOR_MENU));
		CCoolMenu::SetIconBarColor(::GetSysColor(COLOR_3DFACE));
		CCoolMenu::SetLightBarColor(RGB(10, 36, 106));
		CCoolMenu::SetLightBarStartColor(RGB(10, 36, 106));
		CCoolMenu::SetLightBarEndColor(RGB(10, 36, 106));
		CCoolMenu::SetTextColor(::GetSysColor(COLOR_MENUTEXT));
		CCoolMenu::SetHighLightColor(RGB(255, 255, 255));
		
		CMenuWndHook::m_crFrame[0] = RGB(148, 150, 148);
		CMenuWndHook::m_crFrame[1] = RGB(48, 50, 48);
		CMenuWndHook::m_crFrame[2] = RGB(255, 255, 255);
		CMenuWndHook::m_crFrame[3] = RGB(180, 180, 180);
	}
	else if (dwstyle == MENU_STYLE_XP)
	{
		CCoolMenu::SetStyle(CCoolMenu::GetStyle() | CMS_ICONBAR);
		CCoolMenu::SetMenuColor(RGB(255,255,255));
		CCoolMenu::SetIconBarColor(::GetSysColor(COLOR_3DFACE));
		CCoolMenu::SetLightBarColor(RGB(155,155,185));
		CCoolMenu::SetLightBarStartColor(RGB(234, 240, 250));
		CCoolMenu::SetLightBarEndColor(RGB(196, 212, 239));
		CCoolMenu::SetTextColor(::GetSysColor(COLOR_MENUTEXT));
		CCoolMenu::SetHighLightColor(RGB(20, 20, 50));
		
CMenuWndHook::m_crFrame[0] = RGB(48, 50, 48);
		CMenuWndHook::m_crFrame[1] = RGB(48, 50, 48);
		CMenuWndHook::m_crFrame[2] = RGB(255, 255, 255);
		CMenuWndHook::m_crFrame[3] = RGB(255, 255, 255);
	}
	else if (dwstyle == MENU_STYLE_SNOW)
	{
		CCoolMenu::SetStyle(CCoolMenu::GetStyle() & ~CMS_ICONBAR);
		CCoolMenu::SetMenuColor(RGB(255,255,255));
		CCoolMenu::SetIconBarColor(::GetSysColor(COLOR_3DFACE));
		CCoolMenu::SetLightBarColor(RGB(155,155,185));
		CCoolMenu::SetLightBarStartColor(RGB(234, 240, 250));
		CCoolMenu::SetLightBarEndColor(RGB(196, 212, 239));
		CCoolMenu::SetTextColor(RGB(0, 0, 0));
		CCoolMenu::SetHighLightColor(RGB(0, 0, 0));

		CMenuWndHook::m_crFrame[0] = RGB(48, 50, 48);
		CMenuWndHook::m_crFrame[1] = RGB(48, 50, 48);
		CMenuWndHook::m_crFrame[2] = RGB(255, 255, 255);
		CMenuWndHook::m_crFrame[3] = RGB(255, 255, 255);
	}
	else if (dwstyle == MENU_STYLE_GREEN)
	{
		CCoolMenu::SetStyle(CCoolMenu::GetStyle() & ~CMS_ICONBAR);
		CCoolMenu::SetMenuColor(RGB(220,235,220));
		CCoolMenu::SetIconBarColor(::GetSysColor(COLOR_3DFACE));
		CCoolMenu::SetLightBarColor(RGB(155,185,155));
		CCoolMenu::SetLightBarStartColor(RGB(240, 250, 234));
		CCoolMenu::SetLightBarEndColor(RGB(212, 239, 196));
		CCoolMenu::SetTextColor(RGB(10, 80, 10));
		CCoolMenu::SetHighLightColor(RGB(20, 20, 50));
		
		CMenuWndHook::m_crFrame[0] = RGB(128, 150, 128);
		CMenuWndHook::m_crFrame[1] = RGB(48, 50, 48);
		CMenuWndHook::m_crFrame[2] = RGB(255, 255, 255);
		CMenuWndHook::m_crFrame[3] = RGB(168, 210, 168);
	}
	else if (dwstyle == MENU_STYLE_BLUE)
	{
		CCoolMenu::SetStyle(CCoolMenu::GetStyle() & ~CMS_ICONBAR);
		CCoolMenu::SetMenuColor(RGB(225,225,235));
		CCoolMenu::SetIconBarColor(::GetSysColor(COLOR_3DFACE));
		CCoolMenu::SetLightBarColor(RGB(155,155,185));
		CCoolMenu::SetLightBarStartColor(RGB(234, 240, 250));
		CCoolMenu::SetLightBarEndColor(RGB(196, 212, 239));
		CCoolMenu::SetTextColor(RGB(10, 10, 80));
		CCoolMenu::SetHighLightColor(RGB(20, 20, 50));
		
		CMenuWndHook::m_crFrame[0] = RGB(120, 120, 158);
		CMenuWndHook::m_crFrame[1] = RGB(48, 50, 48);
		CMenuWndHook::m_crFrame[2] = RGB(255, 255, 255);
		CMenuWndHook::m_crFrame[3] = RGB(168, 168, 210);
	}
	else if (dwstyle == MENU_STYLE_XP2)
	{
		CCoolMenu::SetStyle(CCoolMenu::GetStyle() | CMS_ICONBAR);
		CCoolMenu::SetMenuColor(::GetSysColor(COLOR_3DFACE));
		CCoolMenu::SetIconBarColor(RGB(255,255,255));
		CCoolMenu::SetLightBarColor(RGB(155,155,185));
		CCoolMenu::SetLightBarStartColor(RGB(234, 240, 250));
		CCoolMenu::SetLightBarEndColor(RGB(196, 212, 239));
		CCoolMenu::SetTextColor(::GetSysColor(COLOR_MENUTEXT));
		CCoolMenu::SetHighLightColor(RGB(20, 20, 50));
		
		CMenuWndHook::m_crFrame[0] = RGB(48, 50, 48);
		CMenuWndHook::m_crFrame[1] = RGB(48, 50, 48);
		CMenuWndHook::m_crFrame[2] = RGB(255, 255, 255);
		CMenuWndHook::m_crFrame[3] = RGB(255, 255, 255);
	}
	CCoolMenu::InitImageList();
}
