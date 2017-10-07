/*########################################################################
	Filename: 	coolmenu.h
	----------------------------------------------------
	Remarks:	...
	----------------------------------------------------
	
  ########################################################################*/
#if !defined(_ANYOU_COOLMENU_H)
#define _ANYOU_COOLMENU_H

#if _MSC_VER > 1000
#pragma once
#endif 

#include "..\\autocomplete\\SubClass.h"
#include <afxtempl.h>
#include "..\\Tools\\tools.h"

//Menu Level:------------------------------
#define MDS_TOP_MENU		 1	//顶部菜单
#define MDS_SUBMENU		     0	//其他子菜单
#define MDS_TOP_SUBMENU		-1	//主菜单
#define MDS_TOP_ENDSUBMENU	-2	//主菜单最后一项

//Menu Style:------------------------------
#define CMS_ICONBAR			0x00000001
#define CMS_LOGOBAR			0x00000002
#define CMS_32IMAGELIST     0x00000010

#define MENU_SPACE 3

#if !defined(ODS_HOTLIGHT)
#define	ODS_HOTLIGHT	    0x0040
#endif

/*########################################################################
			  ------------------------------------------------
						  菜单子类化类 CCoolMenuHook
			  ------------------------------------------------
  ########################################################################*/
class CCoolMenuHook : public CSubclassWnd
{
protected:
	LRESULT WindowProc(UINT uMesssage, WPARAM wparam, LPARAM lparam);
};

/*########################################################################
			  ------------------------------------------------
								CoolMenu 类
			  ------------------------------------------------
  ########################################################################*/
class CCoolMenu : public CMenu  
{
	//菜单项类-----------------------------------
	typedef class CCoolMenuItem
	{
	public:
		void SetItemName(CString sname);
	public:
		CString strText;			//菜单文本
		CString strKeyName;			//快捷键提示文本
		int		nMenuLevel;			//菜单级别
		int     nMenuID;			//菜单ID,-2:顶级菜单,-1:弹出菜单,0:分隔条 
		HMENU	hMenu;
	}COOLMENU, *LPCOOLMENU;

	friend class CCoolMenuHook;
	friend class CMenuWndHook;
	
//成员函数------------------------------------------------------
public:
	CCoolMenu();
	virtual ~CCoolMenu();
	
	BOOL LoadMenu(UINT uMenuID, UINT uToolBarID = 0);
	BOOL Attach(HMENU hMenu, UINT uToolBarID = 0);
	BOOL ModifyStyle(HMENU hMenu, int nlevel = MDS_SUBMENU);
	void AppendMenu(UINT uFlags, UINT uNewMenuItemID, CString strNewMenuItem, int nStyle = MDS_SUBMENU);
	void ClearData();
	HMENU Detach();

//操作----------------------------------------------------------
public:
	static void SubClass(HWND hwnd);
	static void UnSubClass();
	static BOOL InitImageList();
    static HBITMAP CreateImage(HBITMAP hbitmap, int nstyle, BOOL bAlpha, COLORREF crBackColor, COLORREF crMarkColor);
//属性-----------------------------------------------------------
public:
	//图像列表---------------------------------
	static int SetImageList(UINT uToolBarID,UINT uBitmapID = NULL, BOOL bAlpha = FALSE);
	
	//菜单外观---------------------------------
	static BOOL SetLogoImage(UINT uBitmapID = NULL, int nwidth = 0);
	static void SetLogoText(CString strText, COLORREF color);

	//菜单颜色-------------------------------------
	static void SetBackGroundBmp(UINT nBitmapID){nBackGroundbmpID=nBitmapID;}
	static void SetMenuColor(COLORREF color)       {m_crMenuColor        = color;}
	static void SetTextColor(COLORREF color)       {m_crTextColor        = color;}
	static void SetIconBarColor(COLORREF color)    {m_crIconBarColor     = color;}
	static void SetLightBarColor(COLORREF color)   {m_crLightBarColor    = color;}
	static void SetLightBarStartColor(COLORREF color){m_crLightBarStartColor = color;}
	static void SetLightBarEndColor(COLORREF color){m_crLightBarEndColor = color;}
	static void SetHighLightColor(COLORREF color)  {m_crHighLightColor   = color;}
	static COLORREF GetMenuColor()		 {return m_crMenuColor;}
	static COLORREF GetTextColor()		 {return m_crTextColor;}
	static COLORREF GetIconBarColor()	 {return m_crIconBarColor;}
	static COLORREF GetLightBarColor()   {return m_crLightBarColor;}
	static COLORREF GetLightBarStartColor(){return m_crLightBarStartColor;}
	static COLORREF GetLightBarEndColor(){return m_crLightBarEndColor;}
	static COLORREF GetHighLightColor()  {return m_crHighLightColor;}
	
	//菜单风格-------------------------------------
	static void SetStyle(DWORD dwStyle) {m_dwStyle = dwStyle;}
	static DWORD GetStyle() {return m_dwStyle;}

//实现-----------------------------------------------------------
protected:
	//绘制函数--------------------------------------
	static void DrawLightBar(CDC *pDC, CRect rect, BOOL bfill = TRUE);
	static void DrawLogoBar(CDC *pDC, CRect rect);
	static void DrawMenuBar(CDC* pDC, CRect rect);
	static void DrawGradsRect(CDC *pDC,  CRect &rect, COLORREF statColor, COLORREF endColor);
	static void DrawBackGroundBmp(CDC*pDC,CRect rect,BOOL nFill=false);
	
	//铺助函数--------------------------------------
	static int  GetIDFromToolBar(UINT uToolBarID, CUIntArray *uIDArray);
	static int  GetIndex(UINT uID);

//消息处理函数---------------------------------------------------
public:
	static void DrawItem(LPDRAWITEMSTRUCT lpDIS);
	static void MeasureItem(LPMEASUREITEMSTRUCT lpMIS);
	
//数据-----------------------------------------------------------
protected:
	CObList m_obMenuList;				//菜单项对象列表.

	static DWORD m_dwStyle;
	static CCoolMenuHook m_MenuHook;
	
	//菜单图标图像列表-------------------------------
	static CImageList m_iImageList;
	static CImageList m_iHotImageList;
	static CImageList m_iDisabledImageList;

	static CUIntArray m_uIDArray;		//菜单项ID数组.

	static CSize m_szMenuLogo;			//主菜单左LOGO图像栏大小.
	static CSize m_szMenuIcon;			//图标大小.
    static UINT nBackGroundbmpID;       //要填充菜单背景的位图ID
	static UINT m_uLogoBmpID;			//主菜单左LOGO图像ID.
	static UINT m_uBitmapID;			//图像列表图像资源ID.
	static CString m_sLogoText;			//LOGO字符串.
	static CRect m_rcMenuItem;			//当前选择的顶级菜单项的矩形区域.
    
	static COLORREF m_crLogoColor;			//LOGO图像的背景颜色.
	static COLORREF m_crTextColor;			//字体颜色.
	static COLORREF m_crMenuColor;			//菜单颜色.
	static COLORREF m_crIconBarColor;		//图标栏背景颜色.
	static COLORREF m_crLightBarColor;		//光标条颜色.
	static COLORREF m_crLightBarStartColor;
	static COLORREF m_crLightBarEndColor;	//光标条颜色.
	static COLORREF m_crMarkColor;			//图片透明色.
	static COLORREF m_crHighLightColor;		//高亮字体颜色.
};

#define MENU_STYLE_XP		0x00000001
#define MENU_STYLE_XP2		0x00000006
#define MENU_STYLE_DEFAULT  0x00000002
#define MENU_STYLE_SNOW		0x00000003
#define MENU_STYLE_GREEN	0x00000004
#define MENU_STYLE_BLUE		0x00000005

/*########################################################################
			  ------------------------------------------------
						    CCoolMenuTheme 类
			  ------------------------------------------------
  ########################################################################*/
class CCoolMenuTheme : public CObject
{
//建构---------------------------------------------------------
public:
	static void SetTheme(DWORD dwstyle);
	CCoolMenuTheme();
	~CCoolMenuTheme();
};
/*########################################################################
			  ------------------------------------------------
							 CMenuWndHook 类
			  ------------------------------------------------
  ########################################################################*/
class CMenuWndHook
{
//建构---------------------------------------------------------
public:
    CMenuWndHook(HWND hWnd);
	~CMenuWndHook();
	static void InstallHook();
	static void UnInstallHook();

//消息----------------------------------------------------------
public:
	static LRESULT CALLBACK CoolMenuProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK WindowHook (int code, WPARAM wParam, LPARAM lParam);

	void OnNcCalcsize(NCCALCSIZE_PARAMS* lpncsp);
	void OnShowWindow(BOOL bShow);
	void OnNcDestroy();
	void OnPrint(CDC* pDC);
	void OnNcPaint();
	void OnWindowPosChanging(WINDOWPOS* pWindowPos);

//操作----------------------------------------------------------
public:
	static CMenuWndHook* AddWndHook(HWND hwnd);
	static CMenuWndHook* GetWndHook(HWND hwnd);

//数据-----------------------------------------------------------
protected:
	CRect m_rcMenu;
	CPoint m_ptMenu;
	HWND m_hWnd;
	CBitmap m_bmpBack;

	static CMap<HWND, HWND, CMenuWndHook*, CMenuWndHook*> m_WndMenuMap;
    static HHOOK m_hMenuHook;
public:
	static COLORREF m_crFrame[4];
};
#endif // !defined(_ANYOU_COOLMENU_H)
