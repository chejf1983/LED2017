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
#define MDS_TOP_MENU		 1	//�����˵�
#define MDS_SUBMENU		     0	//�����Ӳ˵�
#define MDS_TOP_SUBMENU		-1	//���˵�
#define MDS_TOP_ENDSUBMENU	-2	//���˵����һ��

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
						  �˵����໯�� CCoolMenuHook
			  ------------------------------------------------
  ########################################################################*/
class CCoolMenuHook : public CSubclassWnd
{
protected:
	LRESULT WindowProc(UINT uMesssage, WPARAM wparam, LPARAM lparam);
};

/*########################################################################
			  ------------------------------------------------
								CoolMenu ��
			  ------------------------------------------------
  ########################################################################*/
class CCoolMenu : public CMenu  
{
	//�˵�����-----------------------------------
	typedef class CCoolMenuItem
	{
	public:
		void SetItemName(CString sname);
	public:
		CString strText;			//�˵��ı�
		CString strKeyName;			//��ݼ���ʾ�ı�
		int		nMenuLevel;			//�˵�����
		int     nMenuID;			//�˵�ID,-2:�����˵�,-1:�����˵�,0:�ָ��� 
		HMENU	hMenu;
	}COOLMENU, *LPCOOLMENU;

	friend class CCoolMenuHook;
	friend class CMenuWndHook;
	
//��Ա����------------------------------------------------------
public:
	CCoolMenu();
	virtual ~CCoolMenu();
	
	BOOL LoadMenu(UINT uMenuID, UINT uToolBarID = 0);
	BOOL Attach(HMENU hMenu, UINT uToolBarID = 0);
	BOOL ModifyStyle(HMENU hMenu, int nlevel = MDS_SUBMENU);
	void AppendMenu(UINT uFlags, UINT uNewMenuItemID, CString strNewMenuItem, int nStyle = MDS_SUBMENU);
	void ClearData();
	HMENU Detach();

//����----------------------------------------------------------
public:
	static void SubClass(HWND hwnd);
	static void UnSubClass();
	static BOOL InitImageList();
    static HBITMAP CreateImage(HBITMAP hbitmap, int nstyle, BOOL bAlpha, COLORREF crBackColor, COLORREF crMarkColor);
//����-----------------------------------------------------------
public:
	//ͼ���б�---------------------------------
	static int SetImageList(UINT uToolBarID,UINT uBitmapID = NULL, BOOL bAlpha = FALSE);
	
	//�˵����---------------------------------
	static BOOL SetLogoImage(UINT uBitmapID = NULL, int nwidth = 0);
	static void SetLogoText(CString strText, COLORREF color);

	//�˵���ɫ-------------------------------------
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
	
	//�˵����-------------------------------------
	static void SetStyle(DWORD dwStyle) {m_dwStyle = dwStyle;}
	static DWORD GetStyle() {return m_dwStyle;}

//ʵ��-----------------------------------------------------------
protected:
	//���ƺ���--------------------------------------
	static void DrawLightBar(CDC *pDC, CRect rect, BOOL bfill = TRUE);
	static void DrawLogoBar(CDC *pDC, CRect rect);
	static void DrawMenuBar(CDC* pDC, CRect rect);
	static void DrawGradsRect(CDC *pDC,  CRect &rect, COLORREF statColor, COLORREF endColor);
	static void DrawBackGroundBmp(CDC*pDC,CRect rect,BOOL nFill=false);
	
	//��������--------------------------------------
	static int  GetIDFromToolBar(UINT uToolBarID, CUIntArray *uIDArray);
	static int  GetIndex(UINT uID);

//��Ϣ������---------------------------------------------------
public:
	static void DrawItem(LPDRAWITEMSTRUCT lpDIS);
	static void MeasureItem(LPMEASUREITEMSTRUCT lpMIS);
	
//����-----------------------------------------------------------
protected:
	CObList m_obMenuList;				//�˵�������б�.

	static DWORD m_dwStyle;
	static CCoolMenuHook m_MenuHook;
	
	//�˵�ͼ��ͼ���б�-------------------------------
	static CImageList m_iImageList;
	static CImageList m_iHotImageList;
	static CImageList m_iDisabledImageList;

	static CUIntArray m_uIDArray;		//�˵���ID����.

	static CSize m_szMenuLogo;			//���˵���LOGOͼ������С.
	static CSize m_szMenuIcon;			//ͼ���С.
    static UINT nBackGroundbmpID;       //Ҫ���˵�������λͼID
	static UINT m_uLogoBmpID;			//���˵���LOGOͼ��ID.
	static UINT m_uBitmapID;			//ͼ���б�ͼ����ԴID.
	static CString m_sLogoText;			//LOGO�ַ���.
	static CRect m_rcMenuItem;			//��ǰѡ��Ķ����˵���ľ�������.
    
	static COLORREF m_crLogoColor;			//LOGOͼ��ı�����ɫ.
	static COLORREF m_crTextColor;			//������ɫ.
	static COLORREF m_crMenuColor;			//�˵���ɫ.
	static COLORREF m_crIconBarColor;		//ͼ����������ɫ.
	static COLORREF m_crLightBarColor;		//�������ɫ.
	static COLORREF m_crLightBarStartColor;
	static COLORREF m_crLightBarEndColor;	//�������ɫ.
	static COLORREF m_crMarkColor;			//ͼƬ͸��ɫ.
	static COLORREF m_crHighLightColor;		//����������ɫ.
};

#define MENU_STYLE_XP		0x00000001
#define MENU_STYLE_XP2		0x00000006
#define MENU_STYLE_DEFAULT  0x00000002
#define MENU_STYLE_SNOW		0x00000003
#define MENU_STYLE_GREEN	0x00000004
#define MENU_STYLE_BLUE		0x00000005

/*########################################################################
			  ------------------------------------------------
						    CCoolMenuTheme ��
			  ------------------------------------------------
  ########################################################################*/
class CCoolMenuTheme : public CObject
{
//����---------------------------------------------------------
public:
	static void SetTheme(DWORD dwstyle);
	CCoolMenuTheme();
	~CCoolMenuTheme();
};
/*########################################################################
			  ------------------------------------------------
							 CMenuWndHook ��
			  ------------------------------------------------
  ########################################################################*/
class CMenuWndHook
{
//����---------------------------------------------------------
public:
    CMenuWndHook(HWND hWnd);
	~CMenuWndHook();
	static void InstallHook();
	static void UnInstallHook();

//��Ϣ----------------------------------------------------------
public:
	static LRESULT CALLBACK CoolMenuProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK WindowHook (int code, WPARAM wParam, LPARAM lParam);

	void OnNcCalcsize(NCCALCSIZE_PARAMS* lpncsp);
	void OnShowWindow(BOOL bShow);
	void OnNcDestroy();
	void OnPrint(CDC* pDC);
	void OnNcPaint();
	void OnWindowPosChanging(WINDOWPOS* pWindowPos);

//����----------------------------------------------------------
public:
	static CMenuWndHook* AddWndHook(HWND hwnd);
	static CMenuWndHook* GetWndHook(HWND hwnd);

//����-----------------------------------------------------------
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
