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
								Cool API ����
			  ------------------------------------------------
  ########################################################################*/

HMODULE g_hUserDll = NULL;
#define WS_EX_LAYERED	0x00080000 //����չ����ʹ����͸��.
#define LWA_ALPHA		0x00000002

/*========================================================================
	���ܣ�			������Ӧ��ͼ���б������ͼ��
	-------------------------------------------------------------
	hbitmap:		ԭʼλͼ���
	crBackColor:	����ɫ
	nstyle:			Ҫ������ͼ��ķ��,����Ϊ����ֵ֮һ:
	----------------------------------------------------
		-	0:		������ֹͼ���б�ͼ��
		-	1:		��������ͼ���б�ͼ��
		-	2:		������ͼ���б�ͼ��
==========================================================================*/
HBITMAP CCoolMenu::CreateImage(HBITMAP hbitmap, int nstyle, BOOL bAlpha, COLORREF crBackColor, COLORREF crMarkColor)
{
	HBITMAP RetBmp = NULL;
    if (hbitmap == NULL)
    {  
		return NULL;
	}

	//ԴλͼDC------------------------------------
    HDC BufferDC = CreateCompatibleDC(NULL);      
    if (BufferDC == NULL)
    {
		return NULL;
	}
    SelectObject(BufferDC, hbitmap);

	//Ŀ��DC--------------------------------------
    HDC DirectDC = CreateCompatibleDC(NULL);      
    if (DirectDC == NULL)
    {
		  DeleteDC(BufferDC);
		  return NULL;
	}

    // ��ȡԴλͼ��С----------------------------
    BITMAP bm;
    GetObject(hbitmap, sizeof(bm), &bm);

	// ��ʼ��BITMAPINFO��Ϣ----------------------
    BITMAPINFO bitmapinfo; 
    ZeroMemory(&bitmapinfo, sizeof(BITMAPINFO));
    bitmapinfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bitmapinfo.bmiHeader.biWidth = bm.bmWidth;
    bitmapinfo.bmiHeader.biHeight = bm.bmHeight;
    bitmapinfo.bmiHeader.biPlanes = 1;
    bitmapinfo.bmiHeader.biBitCount = 32;
	
	//ָ��������ָ��--------
	BYTE *ptPixels;    
    HBITMAP DirectBitmap = CreateDIBSection(DirectDC, (BITMAPINFO*)&bitmapinfo, 
                                  DIB_RGB_COLORS, (void**)&ptPixels, NULL, 0);
	
	//������ɫ--------------
	BYTE	oldRed   = GetRValue(crBackColor);
	BYTE	oldGreen = GetGValue(crBackColor);
	BYTE	oldBlue  = GetBValue(crBackColor);

	//͸��ɫ----------------
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
			//͸����(alpha == 0)----------------------------------
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
				//�ҶȻ�λͼ--------------------------------------
				if (nstyle == 0 )
				{
					temp = (BYTE)(ptPixels[i + 2] * 0.299 + ptPixels[i + 1] * 0.587 + ptPixels[i] * 0.114);
					temp = (BYTE)(255 - (255 - temp) * 0.8); 
					ptPixels[i + 2] = ptPixels[i + 1] = ptPixels[i] = temp;
				}

				//����λͼ----------------------------------------
				else if (nstyle == 2)
				{
					ptPixels[i + 2] = (BYTE)(255 - (255 - ptPixels[i + 2]) * 0.9); 
					ptPixels[i + 1] = (BYTE)(255 - (255 - ptPixels[i + 1]) * 0.9); 
					ptPixels[i    ] = (BYTE)(255 - (255 - ptPixels[i + 0]) * 0.9); 
				}

				//Alpha���--------------------------------------
				if (bAlpha)
				{
					ptPixels[i + 2] = (oldRed * (255 - ptPixels[i + 3]) + ptPixels[i + 2] * ptPixels[i + 3]) / 255; // Alphaȡֵ��Χ��0��255
					ptPixels[i + 1] = (oldGreen * (255 - ptPixels[i + 3]) + ptPixels[i + 1] * ptPixels[i + 3]) / 255; // Alphaȡֵ��Χ��0��255
					ptPixels[i    ] = (oldBlue * (255 - ptPixels[i + 3]) + ptPixels[i    ] * ptPixels[i + 3]) / 255; // Alphaȡֵ��Χ��0��255
				}
			}
        }

        SelectObject(DirectDC, oldObject);
        RetBmp = DirectBitmap;
    }
    // �ͷ�DC--------------------
    DeleteDC(DirectDC);
    DeleteDC(BufferDC);
 
	return RetBmp;
}

#ifndef SPI_GETDROPSHADOW
#define SPI_GETDROPSHADOW   0x1024
#endif

/*========================================================================
	˵��:	�ý���ɫ���ָ���ľ�������.
==========================================================================*/
void CCoolMenu::DrawGradsRect(CDC *pDC,  CRect &rect, COLORREF statColor, COLORREF endColor)
{//���ݶȾ���,����ķ�ʽ�Ǵ��ϵ����ٵ��ϱ仯
	int r=GetRValue(statColor);
	int g=GetGValue(statColor);
	int b=GetBValue(statColor);//�õ���ʼɫ����ɫ����

	//�õ���ɫ���������� 
	float dr=(float)(2*(GetRValue(endColor)-GetRValue(statColor))/rect.Height());
	float dg=(float)(2*(GetGValue(endColor)-GetGValue(statColor))/rect.Height());
    float db=(float)(2*(GetBValue(endColor)-GetBValue(statColor))/rect.Height());
	//�����ʶ���������
	for(int i=0;i<=rect.Height()/2;i++)
	{
        CPen pen(PS_SOLID,1,RGB(r+i*dr,g+i*dg,b+i*db)),*Oldpen;
		Oldpen=pDC->SelectObject(&pen);
		//��ֱ��
		pDC->MoveTo(rect.left,rect.top+i);
		pDC->LineTo(rect.right,rect.top+i);
		pDC->MoveTo(rect.left,rect.bottom- i);
		pDC->LineTo(rect.right,rect.bottom-i);

		//�ָ�DC
		pDC->SelectObject(Oldpen);
		pen.DeleteObject();
	}
}

/*===================��ָ����λͼ���˵�����=======================*/
void CCoolMenu::DrawBackGroundBmp(CDC*pDC,CRect rect,BOOL bFill)
{ 
	if(!bFill)
	{//���������ֱ�ӷ���
       return ;
	}
	else//ע��:λͼ�Ĵ�СҪ����rect�Ĵ�С
	{//���������ָ����λͼ���
        if(nBackGroundbmpID!=NULL)
		{//��λͼ��Ϊ��
			/*-------------------����λͼ-----------------------*/
			CBitmap m_BkGndBmp;
            m_BkGndBmp.LoadBitmap(nBackGroundbmpID);//����λͼ
			if(m_BkGndBmp.m_hObject!=NULL)
			{//����λͼ�ɹ�
			   CDC MemDC;//�����ڴ�DC�����汳��λͼ
	           MemDC.CreateCompatibleDC(pDC);//����һ����pDC���ݵ�DC
	           MemDC.SelectObject(&m_BkGndBmp);//��λͼ����ѡ���ڴ���
	           pDC->BitBlt(0,0,rect.Width(),rect.Height(),&MemDC,0,0,SRCCOPY);
			}
		}
	}

}


/*########################################################################
			  ------------------------------------------------
						�˵����໯�� CCoolMenuHook
			  ------------------------------------------------
		���ڽػ�ӵ�д˲˵����ڵ���˵���ص���Ϣ���Ա������Ӧ�Ĵ���.
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
	���ܣ�	���ò˵��������,���ѿ�ݼ���ʾ��Ϣ�Ӳ˵����з������.
==========================================================================*/
void CCoolMenu::CCoolMenuItem::SetItemName(CString sname)
{
	//��ݼ���ʾ��Ϣһ����'\t'�ַ�֮��.��"Open(&O)\tCtrl+O";
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
								    �����˵�	
					  ----------------------------------
  ########################################################################*/

CUIntArray CCoolMenu::m_uIDArray;		//�˵���ID����
//�˵�ͼ��ͼ���б�-------------------------------
CImageList CCoolMenu::m_iImageList;
CImageList CCoolMenu::m_iHotImageList;
CImageList CCoolMenu::m_iDisabledImageList;
CString CCoolMenu::m_sLogoText;		//LOGO�ַ���
CCoolMenuHook CCoolMenu::m_MenuHook;

CSize CCoolMenu::m_szMenuLogo = CSize(0, 0);		//���˵���LOGOͼ������С
CSize CCoolMenu::m_szMenuIcon = CSize(16, 16);		//ͼ���С
UINT CCoolMenu::nBackGroundbmpID=0;         //Ҫ���˵�������λͼID
UINT CCoolMenu::m_uLogoBmpID = 0;			//���˵���LOGOͼ��ID
UINT CCoolMenu::m_uBitmapID = 0;			//ͼ���б�ͼ����ԴID
DWORD CCoolMenu::m_dwStyle = 0;
CRect CCoolMenu::m_rcMenuItem = CRect(0, 0, 0, 0);

COLORREF CCoolMenu::m_crLogoColor        = RGB(0, 0, 255);			//LOGOͼ��ı�����ɫ
COLORREF CCoolMenu::m_crTextColor        = ::GetSysColor(COLOR_MENUTEXT);//������ɫ
COLORREF CCoolMenu::m_crMenuColor        = ::GetSysColor(COLOR_MENU);	//�˵���ɫ
COLORREF CCoolMenu::m_crIconBarColor     = ::GetSysColor(COLOR_MENU);	//ͼ����������ɫ
COLORREF CCoolMenu::m_crLightBarColor    = RGB(234, 240, 250);		//�������ɫ
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
	���ܣ�	����������
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
	���ܣ�	��ʼ���Ի�˵�
	-----------------------------------------------
	nlevel: ��ǰ�˵����,����ֻ��������ֵ:
	-----------------------------------------
	-	MDS_TOP_MENU:		�����˵���
	-	MDS_TOP_SUBMENU:	���˵���
	-	MDS_TOP_ENDSUBMENU:	���˵������һ��
	-	MDS_SUBMENU:		�����Ӳ˵���
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
		m_obMenuList.AddTail((CObject *)lpMenu);//���浽�����б���

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
	���ܣ�		����˵���Դ
	--------------------------------------------
	uMenuID:	�˵���ԴID
	uToolBarID: ��������ԴID,������ȡͼ����Դ
==========================================================================*/
BOOL CCoolMenu::LoadMenu(UINT uMenuID, UINT uToolBarID)
{
	ClearData();
	BOOL bRet = CMenu::LoadMenu(uMenuID);
	if (bRet)
	{
		//�������ò˵�Ϊ�Ի������������Ϣ-------------
		ModifyStyle(GetSafeHmenu(), MDS_TOP_MENU);
		//�ӹ����������ͼ����Դ---------------------------
		SetImageList(uToolBarID);
	}
	return bRet;
}

/*========================================================================
	���ܣ�		��Windows�˵�������ӵ�CCoolMenu����.
	------------------------------------------------
	hMenu:		Ҫ���ӵĲ˵�����
	uToolBarID: ��Ӧ��������ԴID,������ȡͼ����Դ
==========================================================================*/
BOOL CCoolMenu::Attach(HMENU hMenu, UINT uToolBarID)
{
	ClearData();
	BOOL bRet = CMenu::Attach(hMenu);
	if (bRet)
	{
		//�������ò˵�Ϊ�Ի������������Ϣ-------------
		ModifyStyle(GetSafeHmenu(), MDS_TOP_MENU);
		//�ӹ����������ͼ����Դ---------------------------
		SetImageList(uToolBarID);
	}
	return bRet;
}

/*========================================================================
	���ܣ�		�Ͽ���˵���������Ӳ�����������
==========================================================================*/
HMENU CCoolMenu::Detach()
{
	ClearData();
	return CMenu::Detach();
}

/*========================================================================
	����:		��Ӳ˵���
	-------------------------------------------
	uID:		�˵�ID
	strText:	�˵��ı�
	nlevel:		�˵�����,��ο���غ���
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
	����:	���໯ָ������
==========================================================================*/
void CCoolMenu::SubClass(HWND hwnd)
{
	m_MenuHook.HookWindow(hwnd);
}

/*########################################################################
					-----------------------
							���Ʋ˵�	
					-----------------------
  ########################################################################*/

/*========================================================================
	���ܣ�	����˵���С
	--------------------------------------------
	lpMIS:	LPMEASUREITEMSTRUCT�ṹ��
==========================================================================*/
void CCoolMenu::MeasureItem(LPMEASUREITEMSTRUCT lpMIS)
{
	LPCOOLMENU lpMenu = (LPCOOLMENU)(lpMIS->itemData);
	
	//�ָ���---------------------------------
	if(lpMenu->nMenuID == 0)
	{
		lpMIS->itemHeight = 5;
		lpMIS->itemWidth = 50;
		return;
	}

	//�Ƿָ���-------------------------------
	lpMIS->itemWidth = 50; // default width
	lpMIS->itemHeight = 19;

	CString strText = lpMenu->strText + lpMenu->strKeyName;
	int nLen = strText.GetLength();
	if (nLen > 0)
	{
	//������Ʋ˵��ı�������-------------------
		
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

		//�����п�ݼ���ʾ�Ĳ˵��Ŀ�ȣ�ʹ�������-------------
		if (lpMenu->strKeyName != "") sz.cx += (62 - (strText.GetLength() % 8) * (sz.cx/strText.GetLength()));
		
		if(lpMenu->nMenuID == -2)
		{
			//�����˵����---------------------------
			lpMIS->itemWidth = sz.cx - 6;
		}
		else if (lpMenu->nMenuLevel <= MDS_TOP_SUBMENU)
		{
			//���˵�����---------------------------
			lpMIS->itemWidth = sz.cx + m_szMenuLogo.cx + m_szMenuIcon.cx + MENU_SPACE * 5;
		}
		else 
		{
			//��ͨ�˵����---------------------------
			lpMIS->itemWidth = sz.cx  + m_szMenuIcon.cx + MENU_SPACE * 5;
		}
	}

}

/*========================================================================
	���ܣ�		��ȡ�˵�����ID��Ӧ��ͼ�����к�
	----------------------------------------------
	uID:		�˵�����ID
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
	����:		���Ʋ˵�
	------------------------------------------------
	lpDIS:		�Ի���Ϣ�ṹ��
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
	//�����ڴ�������---------------------------------------	
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

	//�Ѳ˵�����ѡ���ڴ��豸������-----------------------------
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

    //��λͼ���˵�����
//	CRect rect2;
//	rect2.left+=m_szMenuLogo.cx;
//    DrawBackGroundBmp(pdc,rect2,true);

	//����ǰ�˵�Ϊ���˵�ʱ���ճ�������ڻ���LOGOͼƬ----------
	int nMenuLogoBarcx = 0;	//���LOGO�����
	if (lpMenu->nMenuLevel <= MDS_TOP_SUBMENU) nMenuLogoBarcx = m_szMenuLogo.cx;

	//����LOGOͼƬ----------------------------
	if (nMenuLogoBarcx > 0 && (lpDIS->itemAction & ODA_DRAWENTIRE) 
		&& lpMenu->nMenuLevel != MDS_TOP_SUBMENU)
	{
		DrawLogoBar(pdc, CRect(0, 0, m_szMenuLogo.cx, rect.bottom));
	}

	//ȡ�ò˵�״̬----------------------------
	BOOL bIsSelected = (lpDIS->itemState & ODS_SELECTED);
	BOOL bIsChecked  = (lpDIS->itemState & ODS_CHECKED);
	BOOL bIsGrayed   = (lpDIS->itemState & ODS_GRAYED);
	BOOL bIsHotLight  = (lpDIS->itemState & ODS_HOTLIGHT );

	//��������---------------------------------
	CRect rc = rect;
	rc.left += nMenuLogoBarcx;
	if (lpMenu->nMenuID == -2)//�����˵�-------
	{
		CBrush Brush(::GetSysColor(COLOR_3DFACE));//���Ƿǵ����˵�
		pDC->FillRect(rc, &Brush);
	}
	else//�Ƕ����˵�---------------------------
	{
		CBrush Brush(m_crMenuColor);
		pDC->FillRect(rc, &Brush);
	}

	//����Office XP����ͼ������ɫ����------------
	if (lpMenu->nMenuID != -2 && (GetStyle() & CMS_ICONBAR != 0) && nMenuLogoBarcx == 0)
	{
		rc.right = rc.left + m_szMenuIcon.cx + MENU_SPACE*2 - 1;
		pDC->FillSolidRect(rc,m_crIconBarColor);
	}

	//���Ʒָ���-----------------------------------
	if(lpMenu->nMenuID == 0)
	{
		rc = rect;
		rc.top += rect.Height()/2; //�Ӿ��������м�
		rc.bottom = rc.top + 2;	//����������
		rc.left += (nMenuLogoBarcx + MENU_SPACE); //�ճ����LOGO����
		if ((GetStyle() & CMS_ICONBAR != 0) && nMenuLogoBarcx == 0) 
		{
			//��XP����¿ճ����ͼ��������----------
			rc.left += (m_szMenuIcon.cx + MENU_SPACE);
		}

		pDC->Draw3dRect(rc, ::GetSysColor(COLOR_GRAYTEXT), RGB(240, 240, 240));
	}
	else
	{
	//��ʾ�˵�����-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

		//��ֹ�˵�========================================================
		if(bIsGrayed) 
		{
			rc = rect;
			rc.left += nMenuLogoBarcx; //�ճ����LOGO������
			
			// �˵���ѡ��----------------------------------
			if(bIsSelected) 
			{
			//	DrawLightBar(pDC, rc, FALSE);
			}

			//�˵��ı�----------------------------
			if(lpMenu->strText.GetLength() > 0)
			{
				rc.left += (m_szMenuIcon.cx + MENU_SPACE*3 + 1); 
				rc.top += 2;
				rc.right -= 11;//���ڿ�ݷ�ʽ�Ŀ��"ctrl+o"
				//����������---------------------------
				pDC->SetTextColor(::GetSysColor(COLOR_3DLIGHT));
				pDC->DrawText(lpMenu->strText, &rc, DT_EXPANDTABS | DT_VCENTER | DT_SINGLELINE);
				pDC->DrawText(lpMenu->strKeyName, &rc, DT_EXPANDTABS | DT_VCENTER | DT_SINGLELINE | DT_RIGHT);
			
				pDC->SetTextColor(::GetSysColor(COLOR_GRAYTEXT));
				rc.InflateRect(1,1,-1,-1);
				pDC->DrawText(lpMenu->strText, &rc, DT_EXPANDTABS | DT_VCENTER | DT_SINGLELINE);
				pDC->DrawText(lpMenu->strKeyName, &rc, DT_EXPANDTABS | DT_VCENTER | DT_SINGLELINE | DT_RIGHT);
			}
			
		}
	//�ǽ�ֹ�˵�==========================================================
		else 
		{
			//����˵�------------------------------------------
			if (lpMenu->nMenuID == -2) 
			{
				rc = rect;
				rc.right -= 4;
				
				m_rcMenuItem = rect;

				//ѡ��״̬----------------------------
				if (bIsSelected) 
				{
					DrawMenuBar(pDC, rect);
					pDC->SetTextColor(::GetSysColor(COLOR_MENUTEXT));
					m_rcMenuItem = rect;
					CRect rcFram; 
					AfxGetMainWnd()->GetWindowRect(&rcFram);
					m_rcMenuItem.OffsetRect(rcFram.TopLeft());
				}

				//����״̬----------------------------
				else if (bIsHotLight)  
				{
					DrawLightBar(pDC, rc);
					pDC->SetTextColor(m_crHighLightColor);
					m_rcMenuItem.SetRectEmpty();
				}

				//����״̬----------------------------
				else 
				{
					pDC->SetTextColor(::GetSysColor(COLOR_MENUTEXT));
					m_rcMenuItem.SetRectEmpty();
				}

				//�˵��ı�----------------------------
				if(lpMenu->strText.GetLength() > 0)
				{
					pDC->DrawText(lpMenu->strText, &rc, DT_EXPANDTABS | DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
			}
			//�Ƕ���˵�,�ǵ����˵�����һ���˵���Ŀ---------------
			else 
			{
				rc = rect;
				rc.left += nMenuLogoBarcx;
				//ѡ��״̬-----------------------------
				if(bIsSelected)
				{
					DrawLightBar(pDC, rc);
					pDC->SetTextColor(m_crHighLightColor);
				}
				//��ѡ��״̬---------------------------
				else
				{
					pDC->SetTextColor(m_crTextColor);
				}

				//�˵��ı�----------------------------
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

	//<<����ͼ���Check��־-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

		rc = rect;
		rc.left += (nMenuLogoBarcx + MENU_SPACE -1);
		rc.top += ((rect.Height() - m_szMenuIcon.cy)/2 + 1);
		rc.right = rc.left + m_szMenuIcon.cx;
		rc.bottom = rc.top + m_szMenuIcon.cy;

		int nIndex = GetIndex(lpMenu->nMenuID);

		//�����ͼ��------------------------------------------
		if(nIndex >= 0) 
		{
			//��ͼ��Check��-----------------------------------
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

			
			//����ͼ��-------------------------------------
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

		//���û��ͼ��---------------------------------------
		else 
		{
			// ����Check��־-------------------------
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

				//������----------------------------
				pDC->MoveTo(rc.left + 4,  rc.top + 6);
				pDC->LineTo(rc.left + 6,  rc.top + 8);
				pDC->LineTo(rc.left + 11, rc.top + 3);
				pDC->MoveTo(rc.left + 4,  rc.top + 7);
				pDC->LineTo(rc.left + 6,  rc.top + 9);
				pDC->LineTo(rc.left + 11, rc.top + 4);
			}
		}
		//---------��������ͼ���Check��־>>>
	}

	//ɨβ����-------------------------------------------
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
	���ܣ�	���ƹ����
	-----------------------------------------
	rect:	���Ʒ�Χ
==========================================================================*/
void CCoolMenu::DrawLightBar(CDC *pDC, CRect rect, BOOL bfill)
{
	if (bfill)
	{
		//���ƽ���ɫ----------------------------------------
		FillGradient(pDC, rect, m_crLightBarStartColor, m_crLightBarEndColor);
//		DrawGradsRect(pDC,rect,m_crLightBarStartColor,m_crLightBarEndColor);
	}

	pDC->Draw3dRect(rect, m_crLightBarColor, m_crLightBarColor);
}

/*========================================================================
	���ܣ�	����LOGO��
	--------------------------------------------
	pDC:	�豸������
	rect:	���Ʒ�Χ
==========================================================================*/
void CCoolMenu::DrawLogoBar(CDC *pDC, CRect rect)
{
	if (m_szMenuLogo.cx > 0)
	{
		//���������LOGOͼƬ------------------------------------
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
				//���ͼƬ��Ҫ���ľ���С��������ô�ͼƬ���ʣ�µľ��Σ�ֱ������Ϊֹ----------
				if(rect.Height() > m_szMenuLogo.cy) DrawLogoBar(pDC, CRect(0, 0, rect.right, (rect.Height() - m_szMenuLogo.cy)));
			}
		}

		//���û������LOGOͼƬ�����Խ���ɫ��LOGO�ִ�����LOGO��--
		else 
		{
			//���ƽ���ɫ--------------------------------
			FillGradient(pDC, rect, RGB(90, 90, 90), m_crLogoColor);
					
			//����LOGO�ִ�---------------------------------
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
							���ò˵�LOGO��	
						-----------------------
  ########################################################################*/

/*========================================================================
	����:	����LOGO�ִ�����������ɫ
==========================================================================*/
void CCoolMenu::SetLogoText(CString strText, COLORREF color)
{
	m_sLogoText  = strText;
	m_crLogoColor = color;
	m_szMenuLogo.cx = 20;
}

/*========================================================================
	���ܣ�			����LOGOͼƬ
	--------------------------------------------
	uID��			LOGOͼƬID
	width��			LOGO����ȣ����Ϊ0�����ͼƬ�Ŀ����ΪLGOG�����
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
						���ò˵�ͼ���б�	
					-----------------------
  ########################################################################*/

/*========================================================================
	����:			���ò˵�ͼ���б�.
	------------------------------------------------------------	
	uToolBarID:		��Ӧ������ȡ����ID��������Դ��ID.
	uBitmapID:		ͼ����ԴID.
	bAlpha:			�Ƿ���alphaͨ��.
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
	����:	��ʼ��ͼ���б�
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

	//��������ͼ���б�----------------------------------------
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
	
	//������ֹͼ���б�----------------------------------------
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

	//������ͼ���б�----------------------------------------
	tempbitmap.DeleteObject();

	bm = CCoolMenu::CreateImage(HBITMAP(bitmap), 2, bAlpha, m_crLightBarStartColor, m_crMarkColor);
	tempbitmap.Attach(bm);
	m_iHotImageList.Add(&tempbitmap, RGB(255, 0, 255));

	bitmap.DeleteObject();
	return TRUE;
}

/*========================================================================
	���ܣ�			�ӹ�������Դ����ȡ����ID
	---------------------------------------------
	uToolBarID��	��������ԴID
	uIDArray��		���ڴ���ID�б������ָ��
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
								  ��Ϣ����
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

        // �Ƿ�Ϊ�˵��� ----------------------------------------
        TCHAR strClassName[10];
        int Count = ::GetClassName (hWnd, strClassName, sizeof(strClassName) / sizeof(strClassName[0]));
        if (Count != 6 || _tcscmp(strClassName, _T("#32768")) != 0 )
        {
            break;
        }
		
		// �Ƿ��Ѿ������໯ ------------------------------------
        if (::GetProp(pStruct->hwnd, CoolMenu_oldProc) != NULL )
        {
            break;
        }
        VERIFY(AddWndHook(pStruct->hwnd) != NULL);

        // ȡ��ԭ���Ĵ��ڹ��� ----------------------------------
        WNDPROC oldWndProc = (WNDPROC)(long)::GetWindowLong(pStruct->hwnd, GWL_WNDPROC);
        if (oldWndProc == NULL)
        {
            break;
        }
		
        ASSERT(oldWndProc != CoolMenuProc);
        // ���浽���ڵ������� ----------------------------------
        if (!SetProp(pStruct->hwnd, CoolMenu_oldProc, oldWndProc) )
        {
            break;
        }

        // ���໯ ----------------------------------------------
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
								��Ϣ������	
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
	����:			���ò˵�Ԥ�÷��
	----------------------------------------------------------
	dwstyle:		�����,ֻ��������ֵ֮һ:
	-------------------------------------------
	-	MENU_STYLE_DEFAULT:		Ĭ�Ϸ��
	-	MENU_STYLE_XP:			Office XP ���
	-	MENU_STYLE_XP2:			��һ�� Office XP ���
	-	MENU_STYLE_SNOW:		��ɫ���
	-	MENU_STYLE_GREEN:		��ɫ���
	-	MENU_STYLE_BLUE:		��ɫ���
	-	...				...
	----------------------------------------------------------
	˵��:			�����������������Ӵ��룬��Ӹ�����Զ���
			����Ա���ʹ�ò˵�ʱ�����Ժܿ���л�����Ҫ�Ĳ˵�
			���
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
