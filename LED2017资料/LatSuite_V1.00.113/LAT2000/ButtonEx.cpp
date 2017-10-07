// ButtonEx.cpp : implementation file    
//    
   
////////////////////////////////////////////////////////    
// 功能:自定义按钮类    
// 作者: Lianglp    
// 日期: 2004-4-9 14:29:21    
// 版本: 1.0    
// 说明: 完全兼容CButton类    
////////////////////////////////////////////////////////    
   
   
#include "stdafx.h"    
#include "ButtonEx.h"    
   
#ifdef _DEBUG    
#define new DEBUG_NEW    
#undef THIS_FILE    
static char THIS_FILE[] = __FILE__;   
#endif    
   
/////////////////////////////////////////////////////////////////////////////    
// CButtonEx    
   
   
CList<CButtonSubclassStruct,CButtonSubclassStruct&> CButtonEx::m_listSubclassInfo;   
CToolTipCtrl CButtonEx::m_tooltipCtl;   
   
CButtonEx::CButtonEx()   
{
	m_bTransparent = FALSE;
}   
   
CButtonEx::~CButtonEx()   
{
}
   
   
BEGIN_MESSAGE_MAP(CButtonEx, CButton)   
    //{{AFX_MSG_MAP(CButtonEx)    
    ON_WM_MOUSEMOVE()   
    ON_WM_DESTROY()   
    ON_WM_SETCURSOR()   
    ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)   
    //}}AFX_MSG_MAP    
    ON_MESSAGE(WM_MOUSELEAVE,OnMouseLeave)   
END_MESSAGE_MAP()   
   
/////////////////////////////////////////////////////////////////////////////    
// CButtonEx message handlers    
   
void CButtonEx::PreSubclassWindow()    
{   
    CButton::PreSubclassWindow();   
    m_bFirstMouseEnter = TRUE;   
    m_nCheck = FALSE;   
    ///////////////////////////////////    
    //确定控件类型    
    m_nCtlType = GetPreCtlType();   
    if(m_nCtlType == CTL_TYPE_UNKNOW)   
    {   
        return;//未知按钮类型    
    }   
   
    ///////////////////////////////////////////////////    
    //确定是否要进行自画，无论如何按钮都为自画风格，    
    //其它类型控件如设置位图也设置自画风格，否则不    
    //进行设置    
    UINT uStyle = GetButtonStyle();   
    UINT uTemp = uStyle;   
    switch(m_nCtlType)   
    {   
    case CTL_TYPE_BUTTON:   
        uTemp |= BS_OWNERDRAW;   
        break;   
    case CTL_TYPE_CHECK:   
    case CTL_TYPE_RADIO:   
        if(GetHbitmapOf(NORMAL) || GetHiconOf(NORMAL))   
        {   
            uTemp |= BS_OWNERDRAW;   
        }   
        m_nCheck = CButton::GetCheck();   
        //////////////////////////////////////    
        //如果单选框控件设置子类化信息    
        if(m_nCtlType == CTL_TYPE_RADIO)   
        {   
            static int nPosOfRadioCtl = 0;   
            static int nGroupOfRadioCtl = -1;   
            if(GetStyle() & WS_GROUP)   
            {   
                nPosOfRadioCtl = 0;//在组里的位置;    
            }   
            if(nPosOfRadioCtl == 0)   
            {   
                nGroupOfRadioCtl++;//遇到新组自动加1;    
            }   
   
            CButtonSubclassStruct subclassInfo;   
            subclassInfo.hCtlWnd     = GetSafeHwnd();   
            subclassInfo.nButtonType = CTL_TYPE_RADIO;   
            subclassInfo.nPos        = nPosOfRadioCtl;   
            subclassInfo.nGroup      = nGroupOfRadioCtl;   
            AddSubclassInfo(&subclassInfo);   
   
            nPosOfRadioCtl++;//在组中的位置自动加1;    
        }   
        break;   
    }   
   
    if(uStyle != uTemp)   
    {   
        SetOwnerDraw();   
        SetBRgn(&m_buttonCtlInfo.rgnCtl);   
    }                                                                                                                                                         
   
    return;   
}   
   
BOOL CButtonEx::PreTranslateMessage(MSG* pMsg)    
{   
    if(m_tooltipCtl.GetSafeHwnd())   
    {   
        m_tooltipCtl.RelayEvent(pMsg);   
    }   
    return CButton::PreTranslateMessage(pMsg);   
}   
   
   
///////////////////////////////////////////////////////////////////////    
//    
// 函数名  : CButtonEx::SetTooltip    
// 功能描述: 设置提示信息    
// 参数    : CString strTooltipText提示信息文本    
// 返回值  : 成功设置返回TRUE，否则返回FALSE    
//    
///////////////////////////////////////////////////////////////////////    
BOOL CButtonEx::SetTooltip(CString strTooltipText)   
{   
    if(!GetSafeHwnd())   
    {   
        return FALSE;//如果按钮没有创建，则返失败    
    }   
    if(!m_tooltipCtl.GetSafeHwnd())   
    {   
        m_tooltipCtl.Create(GetParent());   
    } 
   
    m_tooltipCtl.DelTool(this);   
   
    m_tooltipCtl.AddTool(this,strTooltipText);   
    return TRUE;
}   
   
   
///////////////////////////////////////////////////////////////////////    
//    
// 函数名  : CButtonEx::GetTooltip    
// 功能描述: 取提示信息文本    
// 返回值  : CString 返回提示信息文本，没有则返回空    
//    
///////////////////////////////////////////////////////////////////////    
CString CButtonEx::GetTooltip()   
{   
    if(!m_tooltipCtl.GetSafeHwnd())   
    {   
        return "";   
    }   
   
    CString str;   
    m_tooltipCtl.GetText(str,this);   
    return str;   
}   
   
///////////////////////////////////////////////////////////////////////    
//    
// 函数名  : CButtonEx::GetPreCtlType    
// 功能描述: 分析按钮类型    
// 返回值  : int 返回按钮类型，未知返回CTL_TYPE_UNKNOW    
//    
///////////////////////////////////////////////////////////////////////    
int CButtonEx::GetPreCtlType()   
{   
    int nRet = CTL_TYPE_UNKNOW;   
    DWORD dwStyle = GetButtonStyle();   
    if((dwStyle & BS_AUTOCHECKBOX) == BS_AUTOCHECKBOX)//复选框控件    
    {   
        nRet = CTL_TYPE_CHECK;   
    }   
    else if((dwStyle & BS_AUTORADIOBUTTON) == BS_AUTORADIOBUTTON)//单选控件    
    {   
        nRet = CTL_TYPE_RADIO;   
    }   
    else//按钮控件    
    {   
        nRet = CTL_TYPE_BUTTON;   
    }   
    return nRet;   
}   
   
   
   
///////////////////////////////////////////////////////////////////////    
//    
// 函数名  : CButtonEx::AddSubclassInfo    
// 功能描述: 添加子类化信息到(m_listSubclassInfo)链表中    
// 参数    : CButtonSubclassStruct *pSubclassInfo传递信息指针    
// 返回值  : int 返回链表中已存在的总数    
//    
///////////////////////////////////////////////////////////////////////    
int CButtonEx::AddSubclassInfo(CButtonSubclassStruct *pSubclassInfo)   
{   
    if(pSubclassInfo)   
    {   
        ASSERT(pSubclassInfo->hCtlWnd);   
   
        if(!FindSubclassInfoPos(pSubclassInfo->hCtlWnd))   
        {   
            m_listSubclassInfo.AddTail(*pSubclassInfo);   
        }   
    }   
    return m_listSubclassInfo.GetCount();   
}   
   
   
   
///////////////////////////////////////////////////////////////////////    
//    
// 函数名  : CButtonEx::FindSubclassInfoPos    
// 功能描述: 查找子类化设置信息在链表中的位置    
// 参数    : HWND hWnd要查找的句柄    
// 返回值  : POSITION 成功找到返回指定位置，否则返回NULL    
//    
///////////////////////////////////////////////////////////////////////    
POSITION CButtonEx::FindSubclassInfoPos(HWND hWnd)   
{   
    POSITION pos = m_listSubclassInfo.GetHeadPosition();   
    while(pos)   
    {   
        CButtonSubclassStruct subclassInfo =   
            m_listSubclassInfo.GetAt(pos);   
        if(subclassInfo.hCtlWnd == hWnd)   
        {   
            return pos;   
        }   
        m_listSubclassInfo.GetNext(pos);   
    }   
    return NULL;   
}   
   
///////////////////////////////////////////////////////////////////////    
//    
// 函数名  : CButtonEx::RemoveSubclassInfo    
// 功能描述: 释放子类化信息    
// 参数    : HWND hWnd指定要释放的按钮句柄    
// 返回值  : int 返回子类化信息总数    
//    
///////////////////////////////////////////////////////////////////////    
int CButtonEx::RemoveSubclassInfo(HWND hWnd)   
{   
    POSITION pos = FindSubclassInfoPos(hWnd);   
    if(pos)   
    {   
        m_listSubclassInfo.RemoveAt(pos);   
    }   
    return m_listSubclassInfo.GetCount();   
}   
   
   
///////////////////////////////////////////////////////////////////////    
//    
// 函数名  : CButtonEx::DrawBState    
// 功能描述: 画按钮状态    
// 参数    : HDC hdc指定要画的设备句柄    
// 参数    : int nState指定要画的按钮状态    
//          (NORMAL,ENTER,FOCUS,PRESS,DISABLED,DEFAULT)    
// 返回值  : void     
//    
///////////////////////////////////////////////////////////////////////    
void CButtonEx::DrawBState(HDC hdc,int nState)   
{   
    DWORD dwHandle = NULL;   
    SetClipRgn(hdc);   
    ////////////////////////    
    //显示图片类型    
    int nDrawType = GetDrawType(nState,&dwHandle);   
    switch(nDrawType)   
    {   
    case DRAW_TYPE_BITMAP://画位图按钮
        DrawBBitmap(hdc,(HBITMAP)dwHandle);   
        break;   
    case DRAW_TYPE_ICON://画图标按钮    
        DrawBIcon(hdc,(HICON)dwHandle);   
        break;   
    default://没有图形画    
        DrawBNormal(hdc);   
        break;   
    }   
 
    /////////////////////////    
    //显示文字    
    if(IsDrawText())   
    {   
        DrawBText(hdc,nState);   
    }   
	
    /////////////////////////    
    //画按钮边框    
    if(IsDrawFrame())   
    {   
        DrawBFrame(hdc,nState);   
    }   
    return;   
}   
   
   
///////////////////////////////////////////////////////////////////////    
//    
// 函数名  : CButtonEx::GetDrawType    
// 功能描述: 指定状态的画方法    
// 参数    : int nState指定状态    
// 参数    : DWORD* pdwHandle返回图标或位图句柄如果有    
// 返回值  : int 返回状态的画方法    
//    
///////////////////////////////////////////////////////////////////////    
int CButtonEx::GetDrawType(int nState,DWORD* pdwHandle)   
{   
    int nRet = DRAW_TYPE_UNKNOW; 
       
    *pdwHandle = NULL;   
    switch(nState)   
    {   
    case NORMAL:   
        if(m_buttonCtlInfo.hBitmapOfNormal)   
        {   
            *pdwHandle = (DWORD)m_buttonCtlInfo.hBitmapOfNormal;   
            nRet = DRAW_TYPE_BITMAP;   
        }   
        else if(m_buttonCtlInfo.hIconOfNormal)   
        {   
            *pdwHandle = (DWORD)m_buttonCtlInfo.hIconOfNormal;   
            nRet = DRAW_TYPE_ICON;   
        }   
        break;   
    case ENTER:   
        if(m_buttonCtlInfo.hBitmapOfEnter)   
        {   
            *pdwHandle = (DWORD)m_buttonCtlInfo.hBitmapOfEnter;   
            nRet = DRAW_TYPE_BITMAP;   
        }   
        else if(m_buttonCtlInfo.hIconOfEnter)   
        {   
            *pdwHandle = (DWORD)m_buttonCtlInfo.hIconOfEnter;   
            nRet = DRAW_TYPE_ICON;   
        }   
        else    
        {   
            BOOL bFlags = TRUE;   
            int nCtlType = GetCtlType();   
            switch(nCtlType)   
            {   
            case CTL_TYPE_CHECK:   
            case CTL_TYPE_RADIO:   
                if(GetCheck())   
                {   
                    bFlags = FALSE;   
                    if(m_buttonCtlInfo.hBitmapOfPress)   
                    {   
                        *pdwHandle = (DWORD)m_buttonCtlInfo.hBitmapOfPress;   
                        nRet = DRAW_TYPE_BITMAP;   
                    }   
                    else if(m_buttonCtlInfo.hIconOfPress)   
                    {   
                        *pdwHandle = (DWORD)m_buttonCtlInfo.hBitmapOfPress;   
                        nRet = DRAW_TYPE_ICON;   
                    }   
                    else   
                    {   
                        bFlags = TRUE;   
                    }   
                }   
            }   
            if(bFlags)   
            {   
                if(m_buttonCtlInfo.hBitmapOfNormal)   
                {   
                    *pdwHandle = (DWORD)m_buttonCtlInfo.hBitmapOfNormal;   
                    nRet = DRAW_TYPE_BITMAP;   
                }   
                else if(m_buttonCtlInfo.hIconOfNormal)   
                {   
                    *pdwHandle = (DWORD)m_buttonCtlInfo.hIconOfNormal;   
                    nRet = DRAW_TYPE_ICON;   
                }   
            }   
        }   
        break;   
    case FOCUS:   
        if(m_buttonCtlInfo.hBitmapOfFocus)   
        {   
            *pdwHandle = (DWORD)m_buttonCtlInfo.hBitmapOfFocus;   
            nRet = DRAW_TYPE_BITMAP;   
        }   
        else if(m_buttonCtlInfo.hIconOfFocus)   
        {   
            *pdwHandle = (DWORD)m_buttonCtlInfo.hIconOfFocus;   
            nRet = DRAW_TYPE_ICON;   
        }   
        else if(m_buttonCtlInfo.hBitmapOfNormal)   
        {   
            *pdwHandle = (DWORD)m_buttonCtlInfo.hBitmapOfNormal;   
            nRet = DRAW_TYPE_BITMAP;   
        }   
        else if(m_buttonCtlInfo.hIconOfNormal)   
        {   
            *pdwHandle = (DWORD)m_buttonCtlInfo.hIconOfNormal;   
            nRet = DRAW_TYPE_ICON;   
        }   
        break;   
    case PRESS:   
        if(m_buttonCtlInfo.hBitmapOfPress)   
        {   
            *pdwHandle = (DWORD)m_buttonCtlInfo.hBitmapOfPress;   
            nRet = DRAW_TYPE_BITMAP;   
        }   
        else if(m_buttonCtlInfo.hIconOfPress)   
        {   
            *pdwHandle = (DWORD)m_buttonCtlInfo.hIconOfPress;   
            nRet = DRAW_TYPE_ICON;   
        }   
        else if(m_buttonCtlInfo.hBitmapOfNormal)   
        {   
            *pdwHandle = (DWORD)m_buttonCtlInfo.hBitmapOfNormal;   
            nRet = DRAW_TYPE_BITMAP;   
        }   
        else if(m_buttonCtlInfo.hIconOfNormal)   
        {   
            *pdwHandle = (DWORD)m_buttonCtlInfo.hIconOfNormal;   
            nRet = DRAW_TYPE_ICON;   
        }   
        break;   
    case DISABLED:   
        if(m_buttonCtlInfo.hBitmapOfDisable)   
        {   
            *pdwHandle = (DWORD)m_buttonCtlInfo.hBitmapOfDisable;   
            nRet = DRAW_TYPE_BITMAP;   
        }   
        else if(m_buttonCtlInfo.hIconOfDisable)   
        {   
            *pdwHandle = (DWORD)m_buttonCtlInfo.hIconOfDisable;   
            nRet = DRAW_TYPE_ICON;   
        }   
        else if(m_buttonCtlInfo.hBitmapOfNormal)   
        {   
            *pdwHandle = (DWORD)m_buttonCtlInfo.hBitmapOfNormal;   
            nRet = DRAW_TYPE_BITMAP;   
        }   
        else if(m_buttonCtlInfo.hIconOfNormal)   
        {   
            *pdwHandle = (DWORD)m_buttonCtlInfo.hIconOfNormal;   
            nRet = DRAW_TYPE_ICON;   
        }   
        break;   
    case DEFAULT:   
        if(m_buttonCtlInfo.hBitmapOfDefault)   
        {   
            *pdwHandle = (DWORD)m_buttonCtlInfo.hBitmapOfDefault;   
            nRet = DRAW_TYPE_BITMAP;   
        }   
        else if(m_buttonCtlInfo.hIconOfDefault)   
        {   
            *pdwHandle = (DWORD)m_buttonCtlInfo.hIconOfDefault;   
            nRet = DRAW_TYPE_ICON;   
        }   
        else if(m_buttonCtlInfo.hBitmapOfNormal)   
        {   
            *pdwHandle = (DWORD)m_buttonCtlInfo.hBitmapOfNormal;   
            nRet = DRAW_TYPE_BITMAP;   
        }   
        else if(m_buttonCtlInfo.hIconOfNormal)   
        {   
            *pdwHandle = (DWORD)m_buttonCtlInfo.hIconOfNormal;   
            nRet = DRAW_TYPE_ICON;   
        }   
        break;   
    }   
    return nRet;   
}   
   
   
///////////////////////////////////////////////////////////////////////    
//    
// 函数名  : CButtonEx::DrawBBitmap    
// 功能描述: 指定位图句柄在按钮上画    
// 参数    : HDC hdc指定设备上下文    
// 参数    : HBITMAP hBitmap指定位图句柄    
// 返回值  : void     
//    
///////////////////////////////////////////////////////////////////////    
void CButtonEx::DrawBBitmap(HDC hdc, HBITMAP hBitmap)   
{   
    CDC dc,memDC;   
    dc.Attach(hdc);   
    memDC.CreateCompatibleDC(&dc);   
    CBitmap bitmap,*pOldBitmap = NULL;   
    bitmap.Attach(hBitmap);   
    pOldBitmap = memDC.SelectObject(&bitmap);   
   
    HWND hWnd = ::WindowFromDC(hdc);   
    CWnd* pWnd = CWnd::FromHandle(hWnd);   
    CRect rc;   
    pWnd->GetClientRect(&rc);   
   
    dc.BitBlt(rc.left,rc.top,rc.Width(),rc.Height(),&memDC,0,0,SRCCOPY);   
   
    memDC.SelectObject(pOldBitmap);   
    memDC.DeleteDC();   
    bitmap.Detach();   
    dc.Detach();   
    return;   
}   
   
   
///////////////////////////////////////////////////////////////////////    
//    
// 函数名  : CButtonEx::DrawBIcon    
// 功能描述: 在指定的设备上下文上画图标    
// 参数    : HDC hdc指定设备上下文句柄    
// 参数    : HICON hIcon指定图标句柄    
// 返回值  : void     
//    
///////////////////////////////////////////////////////////////////////    
void CButtonEx::DrawBIcon(HDC hdc, HICON hIcon)   
{   
    CDC dc;   
    dc.Attach(hdc);   
    CRect rc;   
    CWnd* pWnd = dc.GetWindow();   
    pWnd->GetClientRect(&rc);   
    dc.DrawIcon(rc.left,rc.top,hIcon);   
    dc.Detach();   
    return;   
}   
   
   
   
///////////////////////////////////////////////////////////////////////    
//    
// 函数名  : CButtonEx::DrawBNormal    
// 功能描述: 根据指定的颜色画背景色    
// 参数    : HDC hdc指定设备上下文    
// 返回值  : void     
//    
///////////////////////////////////////////////////////////////////////    
void CButtonEx::DrawBNormal(HDC hdc)   
{
    CDC dc;   
    dc.Attach(hdc);
	//dc.SetBkMode(TRANSPARENT);
    CBrush brush, brushEdge;    
    brush.CreateSolidBrush(m_buttonCtlInfo.clrBkColor); 
	brushEdge.CreateSolidBrush(RGB(0, 0, 0));
    if(m_buttonCtlInfo.rgnCtl.GetSafeHandle())   
    {
		if (m_bTransparent)
		{
			//dc.FillRgn(&m_buttonCtlInfo.rgnCtl,&brush);
			dc.FrameRgn(&m_buttonCtlInfo.rgnCtl, &brushEdge, 1, 1);
		}
		else
		{
			dc.FillRgn(&m_buttonCtlInfo.rgnCtl,&brush);
		}
    }
    else
    {
        CRect rc;
        CWnd* pWnd = dc.GetWindow();   
        pWnd->GetClientRect(&rc);  
		if (m_bTransparent)
		{
			//dc.FillRect(&rc, &brush);
			dc.FrameRect(&rc, &brushEdge);
		}
		else
		{
			dc.FillRect(&rc,&brush);
		}
    }   
    brush.DeleteObject();   
    dc.Detach();   
    return;   
}   
   
   
///////////////////////////////////////////////////////////////////////    
//    
// 函数名  : CButtonEx::DrawBFrame    
// 功能描述: 画指定框架    
// 参数    : HDC hdc指定设备上下文    
// 参数    : int nState指定状态    
// 返回值  : void     
//    
///////////////////////////////////////////////////////////////////////    
void CButtonEx::DrawBFrame(HDC hdc, int nState)   
{   
    BOOL bDrawFrame = TRUE;   
    UINT nFlags;   
    switch(nState)   
    {   
    case ENTER://进入状态时画     
    case FOCUS://有焦点状态    
        if(nState == FOCUS)   
        {   
            bDrawFrame = IsDrawFrameForState(FOCUS);   
        }   
        nFlags = BDR_RAISEDINNER;   
        break; 
    case PRESS://按下状态时画     
        nFlags = BDR_SUNKENOUTER;   
        break;   
    default:   
        bDrawFrame = FALSE;//其它状态不画边框       
        break;   
    }   
       
    if(bDrawFrame)   
    {   
        CDC dc;   
        dc.Attach(hdc);   
        CWnd* pWnd = dc.GetWindow(); 
        CRect rcClient;   
        pWnd->GetClientRect(&rcClient); 

        dc.DrawEdge(&rcClient,nFlags,BF_TOPLEFT);   
        dc.DrawEdge(&rcClient,nFlags,BF_BOTTOMRIGHT); 
        dc.Detach();   
    }   
    return;
}   
   
///////////////////////////////////////////////////////////////////////    
//    
// 函数名  : CButtonEx::DrawBText    
// 功能描述: 画文本    
// 参数    : HDC hdc指定设备上下文    
// 参数    : int nState指定状态    
// 返回值  : void     
//    
///////////////////////////////////////////////////////////////////////    
void CButtonEx::DrawBText(HDC hdc, int nState)   
{   
    CDC dc;   
    dc.Attach(hdc);   
    int nPreMode = dc.SetBkMode(TRANSPARENT);   
    COLORREF clrPreColor = dc.SetTextColor(m_buttonCtlInfo.clrTextColor);   
    CFont newFont,*pOldFont = dc.GetCurrentFont();   
    newFont.CreatePointFont(m_buttonCtlInfo.nFontSize,m_buttonCtlInfo.strFontName);   
    dc.SelectObject(&newFont);   
   
    CWnd* pWnd = dc.GetWindow();   
    CRect rc;   
    pWnd->GetClientRect(&rc);   
    CString strText;   
    pWnd->GetWindowText(strText);   
    CSize sizeText = dc.GetTextExtent(strText);   
    CPoint pt = CPoint((rc.Width()-sizeText.cx)/2,(rc.Height()-sizeText.cy)/2);   
    UINT nFlags = DST_PREFIXTEXT;   
	if (!m_bTransparent)
	{
		if(nState == PRESS)   
		{   
			pt.x++;   
			pt.y++;   
		}
		else if(nState == DISABLED)   
		{   
			nFlags |= DSS_DISABLED;   
		}
	}
    dc.DrawState(pt,sizeText,strText,nFlags,TRUE,NULL,(CBrush*)NULL);   
    dc.SelectObject(pOldFont);   
    dc.SetTextColor(clrPreColor);   
    dc.SetBkMode(nPreMode);   
    dc.Detach();   
    newFont.DeleteObject();   
    return;   
}   
   
///////////////////////////////////////////////////////////////////////    
//    
// 函数名  : CButtonEx::IsDrawText    
// 功能描述: 测试是否要画文本    
// 返回值  : BOOL返回TRUE，表示画，否则不画    
//    
///////////////////////////////////////////////////////////////////////    
BOOL CButtonEx::IsDrawText()   
{   
    return m_buttonCtlInfo.bDrawText;   
}   
   
///////////////////////////////////////////////////////////////////////    
//    
// 函数名  : CButtonEx::IsDrawFrame    
// 功能描述: 测试是否画边框    
// 返回值  : BOOL 返回TRUE，表示画，否则不画    
//    
///////////////////////////////////////////////////////////////////////    
BOOL CButtonEx::IsDrawFrame()   
{   
    return m_buttonCtlInfo.bDrawFrame;   
}   
   
   
   
///////////////////////////////////////////////////////////////////////    
//    
// 函数名  : CButtonEx::SetTransparentKeyColor    
// 功能描述: 设置图片关键色    
// 参数    : COLORREF clrKeyColor指定颜色    
// 返回值  : COLORREF 返回以前设置的颜色    
//    
///////////////////////////////////////////////////////////////////////    
COLORREF CButtonEx::SetTransparentKeyColor(COLORREF clrKeyColor)   
{   
    COLORREF clrPre = m_buttonCtlInfo.clrTransparentKeyColor ;   
    m_buttonCtlInfo.clrTransparentKeyColor = clrKeyColor;   
    SetBRgn(&m_buttonCtlInfo.rgnCtl);//设置按钮区域    
    if(GetSafeHwnd())   
    {   
        RedrawWindow();   
    }   
    return clrPre;   
}   
   
///////////////////////    
//建立剪切区域    
void CButtonEx::SetClipRgn(HDC hdc)   
{   
    CRgn rgn;   
    if(m_buttonCtlInfo.rgnCtl.GetSafeHandle())   
    {   
        rgn.CreateRectRgn(0,0,1,1);   
        rgn.CombineRgn(&m_buttonCtlInfo.rgnCtl,NULL,RGN_COPY);   
    }   
    else   
    {   
        CWnd* pWnd = CWnd::FromHandle(::WindowFromDC(hdc));   
        CRect rc;   
        pWnd->GetClientRect(&rc);   
        rgn.CreateRectRgnIndirect(&rc);   
    }   
    ::SelectClipRgn(hdc,rgn);   
    rgn.DeleteObject();   
    return;   
}   
 
 
///////////////////////////////////////////////////////////////////////    
//    
// 函数名  : CButtonEx::SetBRgn    
// 功能描述: 设置按钮区域    
// 参数    : CRgn *pRgn返回已设置的区域    
// 返回值  : void     
//    
///////////////////////////////////////////////////////////////////////    
void CButtonEx::SetBRgn(CRgn *pRgn)   
{   
    if(pRgn->GetSafeHandle())   
    {   
        pRgn->DeleteObject();   
    }   
   
    HBITMAP hBitmap = GetHbitmapOf(NORMAL);   
    HWND hWnd = GetSafeHwnd();   
    if(hBitmap && hWnd)   
    {   
        CBitmap bitmap;   
        bitmap.Attach(hBitmap);   
        BITMAP bitmapInfo;   
        bitmap.GetBitmap(&bitmapInfo);   
        int nRow = bitmapInfo.bmHeight;   
        int nCol = bitmapInfo.bmWidth;   
   
        SetWindowPos(NULL,NULL,NULL,nCol,nRow,   
            SWP_NOMOVE|SWP_NOZORDER|SWP_NOACTIVATE);   
   
        COLORREF clrKey = GetTransparentKeyColor();   
        if(clrKey != INVAILD_TRANSPARENT_KEY_COLOR)   
        {   
            CDC memDC,*pDC = GetDC();   
            memDC.CreateCompatibleDC(pDC);   
            CBitmap* pOldBitmap = memDC.SelectObject(&bitmap);   
            pRgn->CreateRectRgn(0,0,nCol,nRow);   
            for(int y = 0; y < nRow; y++)   
            {   
                for(int x = 0; x < nCol; x++)   
                {   
                    COLORREF clrPixel = memDC.GetPixel(y,x);   
                    if(clrPixel == clrKey)//去除关键色    
                    {   
                        CRgn rgnTemp;   
                        rgnTemp.CreateRectRgn(y,x,y+1,x+1);   
                        pRgn->CombineRgn(pRgn,&rgnTemp,RGN_XOR);   
                        rgnTemp.DeleteObject();   
                    }   
                }   
            }   
            ReleaseDC(pDC);   
            memDC.SelectObject(pOldBitmap);   
            memDC.DeleteDC();   
               
            CRgn rgnWnd;   
            rgnWnd.CreateRectRgn(0,0,1,1);   
            rgnWnd.CombineRgn(pRgn,NULL,RGN_COPY);   
            SetWindowRgn(rgnWnd,FALSE);   
            rgnWnd.Detach();   
        }   
        bitmap.Detach();   
    }   
    return;   
}   
   
///////////////////////////////////////////////////////////////////////    
//    
// 函数名  : CButtonEx::GetHbitmapOf    
// 功能描述: 取指定类型的位图    
// 参数    : int nState指定状态类型    
// 返回值  : HBITMAP 成功得到返回位图句柄，否则返回NULL    
//    
///////////////////////////////////////////////////////////////////////    
HBITMAP CButtonEx::GetHbitmapOf(int nState)   
{   
    HBITMAP hRet = NULL;   
    switch(nState)   
    {   
    case NORMAL://正常显示时位图    
        hRet = m_buttonCtlInfo.hBitmapOfNormal;   
        break;   
    case FOCUS://有焦点时位图    
        hRet = m_buttonCtlInfo.hBitmapOfFocus;   
        break;   
    case PRESS://按下时位图    
        hRet = m_buttonCtlInfo.hBitmapOfPress;   
        break;   
    case DISABLED://无效时位图    
        hRet = m_buttonCtlInfo.hBitmapOfDisable;   
        break;   
    case ENTER://光标进入时位图    
        hRet = m_buttonCtlInfo.hBitmapOfEnter;   
        break;   
    case DEFAULT://默认位图    
        hRet = m_buttonCtlInfo.hBitmapOfDefault;   
        break;   
    }   
    return hRet;   
}   
   
   
///////////////////////////////////////////////////////////////////////    
//    
// 函数名  : CButtonEx::GetTransparentKeyColor    
// 功能描述: 取透明关键色    
// 返回值  : COLORREF 返回关键色    
//    
///////////////////////////////////////////////////////////////////////    
COLORREF CButtonEx::GetTransparentKeyColor()   
{   
    return m_buttonCtlInfo.clrTransparentKeyColor;   
}   
   
   
///////////////////////////////////////////////////////////////////////    
//    
// 函数名  : CButtonEx::SetBitmapFromID    
// 功能描述: 从资源装入位图    
// 参数    : UINT nID指定资源ID    
// 参数    : int nState指定要设置的状态    
// 返回值  : BOOL 成功设置返回TRUE，否则返回FALSE    
//    
///////////////////////////////////////////////////////////////////////    
BOOL CButtonEx::SetBitmapFromID(UINT nID, int nState)   
{   
    CBitmap bitmap;   
    BOOL bRet = bitmap.LoadBitmap(nID);   
    if(bRet)   
    {   
        SetBBitmap((HBITMAP)bitmap.Detach(),nState);   
        if(GetSafeHwnd())   
        {   
            if(nState == NORMAL)   
            {   
                SetBRgn(&m_buttonCtlInfo.rgnCtl);   
                if(!IsOwnerDraw())   
                {   
                    SetOwnerDraw();   
                }   
            }   
            RedrawWindow();   
        }   
    }   
    return bRet;   
}   
   
   
///////////////////////////////////////////////////////////////////////    
//    
// 函数名  : CButtonEx::SetBitmapFromFile    
// 功能描述: 从文件装入位图    
// 参数    : CString strFileName    
// 参数    : int nState指定要设置的状态    
// 返回值  : BOOL 成功设置返回TRUE，否则返回FALSE    
//    
///////////////////////////////////////////////////////////////////////    
BOOL CButtonEx::SetBitmapFromFile(CString strFileName, int nState)   
{   
    HBITMAP hBitmap = (HBITMAP)    
        ::LoadImage(NULL,strFileName,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);   
    if(hBitmap)   
    {   
        SetBBitmap(hBitmap,nState);   
        if(GetSafeHwnd())   
        {   
            if(nState == NORMAL)   
            {   
                SetBRgn(&m_buttonCtlInfo.rgnCtl);   
                if(!IsOwnerDraw())   
                {   
                    SetOwnerDraw();   
                }   
            }   
            RedrawWindow();   
        }          
    }   
    return (BOOL)hBitmap;   
}   
   
   
///////////////////////////////////////////////////////////////////////    
//    
// 函数名  : CButtonEx::SetBitmapFromHbitmap    
// 功能描述: 直接从句柄装入位图    
// 参数    : HBITMAP hBitmap指定位图句柄    
// 参数    : int nState指定要设置的状态    
// 返回值  : BOOL 成功设置返回TRUE，否则返回FALSE    
//    
///////////////////////////////////////////////////////////////////////    
BOOL CButtonEx::SetBitmapFromHbitmap(HBITMAP hBitmap, int nState)   
{   
    SetBBitmap(hBitmap,nState);   
    if(GetSafeHwnd())   
    {   
        if(nState == NORMAL && hBitmap)   
        {   
            SetBRgn(&m_buttonCtlInfo.rgnCtl);   
            if(!IsOwnerDraw())   
            {   
                SetOwnerDraw();   
            }   
        }   
        RedrawWindow();   
    }   
   
    return (BOOL)hBitmap;//(暂全返回hBitmap值)    
}   
   
///////////////////////////////////////////////////////////////////////    
//    
// 函数名  : CButtonEx::SetIconFromID    
// 功能描述: 从资源装入图标    
// 参数    : UINT nID指定资源ID    
// 参数    : int nState指定要设置的状态    
// 返回值  : BOOL 成功设置返回TRUE，否则返回FALSE    
//    
///////////////////////////////////////////////////////////////////////    
BOOL CButtonEx::SetIconFromID(UINT nID,int nState)   
{   
    HICON hIcon = ::LoadIcon(::AfxGetInstanceHandle(),MAKEINTRESOURCE(nID));   
    if(hIcon)   
    {   
        SetBIcon(hIcon,nState);   
        if(GetSafeHwnd())   
        {   
            if(nState == NORMAL && !IsOwnerDraw())   
            {   
                SetOwnerDraw();   
            }   
            RedrawWindow();   
        }   
    }   
    return (BOOL)hIcon;   
}   
   
///////////////////////////////////////////////////////////////////////    
//    
// 函数名  : CButtonEx::SetIconFromFile    
// 功能描述:  从文件装入图标    
// 参数    : CString strFileName指定文件名(应包含路径)    
// 参数    : int nState指定要设置的状态    
// 返回值  : BOOL 成功设置返回TRUE，否则返回FALSE    
//    
///////////////////////////////////////////////////////////////////////    
BOOL CButtonEx::SetIconFromFile(CString strFileName, int nState)   
{   
    HICON hIcon = (HICON)      
        ::LoadImage(NULL,strFileName,IMAGE_ICON,0,0,LR_LOADFROMFILE);   
    if(hIcon)   
    {   
        SetBIcon(hIcon,nState);   
        if(GetSafeHwnd())   
        {   
            if(nState == NORMAL && !IsOwnerDraw())   
            {   
                SetOwnerDraw();   
            }              
            RedrawWindow();   
        }   
    }   
    return (BOOL)hIcon;   
}   
   
///////////////////////////////////////////////////////////////////////    
//    
// 函数名  : CButtonEx::SetIconFromHicon    
// 功能描述: 直接从句柄装入图标    
// 参数    : HICON hIcon指定图标句柄    
// 参数    : int nState指定要设置的状态    
// 返回值  : BOOL 成功设置返回TRUE，否则返回FALSE    
//    
///////////////////////////////////////////////////////////////////////    
BOOL CButtonEx::SetIconFromHicon(HICON hIcon, int nState)   
{   
    SetBIcon(hIcon,nState);   
    if(GetSafeHwnd())   
    {   
        if(nState == NORMAL && !IsOwnerDraw() && hIcon)   
        {   
            SetOwnerDraw();   
        }   
        RedrawWindow();   
    }   
    return (BOOL)hIcon;//(暂全返回hIcon值)    
}   
   
   
///////////////////////////////////////////////////////////////////////    
//    
// 函数名  : CButtonEx::SetBBitmap    
// 功能描述: 设置指定状态位图状态到(m_buttonCtlInfo)中    
// 参数    : HBITMAP hBitmap指定位图句柄    
// 参数    : int nState指定要设置的状态    
// 返回值  : void     
//    
///////////////////////////////////////////////////////////////////////    
void CButtonEx::SetBBitmap(HBITMAP hBitmap, int nState)   
{   
    switch(nState)   
    {   
    case NORMAL:   
        m_buttonCtlInfo.hBitmapOfNormal = hBitmap;   
        break;   
    case ENTER:   
        m_buttonCtlInfo.hBitmapOfEnter = hBitmap;   
        break;   
    case FOCUS:   
        m_buttonCtlInfo.hBitmapOfFocus = hBitmap;   
        break;   
    case PRESS:   
        m_buttonCtlInfo.hBitmapOfPress = hBitmap;   
        break;   
    case DISABLED:   
        m_buttonCtlInfo.hBitmapOfDisable = hBitmap;   
        break;   
    case DEFAULT:   
        m_buttonCtlInfo.hBitmapOfDefault = hBitmap;   
        break;   
    }   
    return;   
}   
   
   
///////////////////////////////////////////////////////////////////////    
//    
// 函数名  : CButtonEx::SetBIcon    
// 功能描述: 设置指定状态图标状态到(m_buttonCtlInfo)中    
// 参数    : HICON hIcon指定图句柄    
// 参数    : int nState指定要设置的状态    
// 返回值  : void     
//    
///////////////////////////////////////////////////////////////////////    
void CButtonEx::SetBIcon(HICON hIcon, int nState)   
{   
    switch(nState)   
    {   
    case NORMAL:   
        m_buttonCtlInfo.hIconOfNormal = hIcon;   
        break;   
    case ENTER:   
        m_buttonCtlInfo.hIconOfEnter = hIcon;   
        break;   
    case FOCUS:   
        m_buttonCtlInfo.hIconOfFocus = hIcon;   
        break;   
    case PRESS:   
        m_buttonCtlInfo.hIconOfPress = hIcon;   
        break;   
    case DISABLED:   
        m_buttonCtlInfo.hIconOfDisable = hIcon;   
        break;   
    case DEFAULT:   
        m_buttonCtlInfo.hIconOfDefault = hIcon;   
        break;   
    }   
    return;   
}   
   
   
///////////////////////////////////////////////////////////////////////    
//    
// 函数名  : CButtonEx::GetHiconOf    
// 功能描述: 根据类型返回指定图标句现    
// 参数    : int nState指定类型状态    
// 返回值  : HICON 返回图标句柄    
//    
///////////////////////////////////////////////////////////////////////    
HICON CButtonEx::GetHiconOf(int nState)   
{   
    HICON hRet = NULL;   
    switch(nState)   
    {   
    case NORMAL://正常显示时图标    
        hRet = m_buttonCtlInfo.hIconOfNormal;   
        break;   
    case FOCUS://有焦点时图标    
        hRet = m_buttonCtlInfo.hIconOfFocus;   
        break;   
    case PRESS://按下时图标    
        hRet = m_buttonCtlInfo.hIconOfPress;   
        break;   
    case DISABLED://无效时图标    
        hRet = m_buttonCtlInfo.hIconOfDisable;   
        break;   
    case ENTER://光标进入时图标    
        hRet = m_buttonCtlInfo.hIconOfEnter;   
        break;   
    case DEFAULT://默认图标    
        hRet = m_buttonCtlInfo.hIconOfDefault;   
        break;   
    }   
    return NULL;   
}   
   
   
void CButtonEx::OnMouseMove(UINT nFlags, CPoint point)    
{   
    if(IsOwnerDraw() && m_bFirstMouseEnter)   
    {   
        m_bFirstMouseEnter = FALSE;   
        TRACKMOUSEEVENT mouseEvent;   
        mouseEvent.cbSize = sizeof(TRACKMOUSEEVENT);   
        mouseEvent.hwndTrack = GetSafeHwnd();   
        mouseEvent.dwFlags = TME_LEAVE;    
        ::_TrackMouseEvent(&mouseEvent);   
           
        HDC hdc = ::GetDC(GetSafeHwnd());   
        DrawBState(hdc,ENTER);   
        ::ReleaseDC(GetSafeHwnd(),hdc);   
    }   
    CButton::OnMouseMove(nFlags, point);   
}   
   
   
///////////////////////////////////////////////////////////////////////    
//    
// 函数名  : CButtonEx::OnMouseLeave    
// 功能描述: 光标离开按钮时执行消息    
// 参数    : WPARAM wParam    
// 参数    : LPARAM lParam    
// 返回值  : LRESULT 暂完部返回NULL    
//    
///////////////////////////////////////////////////////////////////////    
LRESULT CButtonEx::OnMouseLeave(WPARAM wParam, LPARAM lParam)   
{   
    if(!m_bFirstMouseEnter)   
    {   
        m_bFirstMouseEnter = TRUE;   
        if(IsDrawFrame())   
        {   
            RedrawWindow();   
        }   
    }   
    return NULL;   
}   
   
void CButtonEx::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)    
{
    HDC hdc = lpDrawItemStruct->hDC;   
    UINT nState = lpDrawItemStruct->itemState;   
   
    int nCtlType = GetCtlType();   
    switch(nCtlType)   
    {   
    case CTL_TYPE_CHECK:   
    case CTL_TYPE_RADIO:   
        if(nState & ODS_SELECTED)   
        {   
            RefreshShell(hdc,TRUE);   
        }   
        else   
        {   
            RefreshShell(hdc,FALSE);   
        }   
        break;   
    default:   
        if((nState & ODS_DISABLED) || (nState & ODS_GRAYED))    
        {   
            DrawBState(hdc,DISABLED);//无效状态     
        }   
        else if(nState & ODS_FOCUS)   
        {   
            if(nState & ODS_SELECTED)   
            {   
                DrawBState(hdc,PRESS);//选择并按下状态    
            }   
            else   
            {   
                DrawBState(hdc,FOCUS);//如果选择状态    
            }   
        }   
        else if(nState & DEFAULT)//默认按钮状态    
        {   
            DrawBState(hdc,DEFAULT);   
        }   
        else   
        {   
            DrawBState(hdc,NORMAL);//正常状态    
        }   
        break;   
    }   
    return;       
}   
   
void CButtonEx::OnDestroy()    
{   
    CButton::OnDestroy();   
    RemoveSubclassInfo(GetSafeHwnd());   
    if(m_buttonCtlInfo.rgnCtl.GetSafeHandle())   
    {   
        m_buttonCtlInfo.rgnCtl.DeleteObject();   
    }   
    /////////////////////////////////    
    //清除位图句柄    
    if(m_buttonCtlInfo.hBitmapOfDefault)   
    {   
        ::DeleteObject(m_buttonCtlInfo.hBitmapOfDefault);   
        m_buttonCtlInfo.hBitmapOfDefault = NULL;   
    }   
    if(m_buttonCtlInfo.hBitmapOfDisable)   
    {   
        ::DeleteObject(m_buttonCtlInfo.hBitmapOfDisable);   
        m_buttonCtlInfo.hBitmapOfDisable = NULL;   
    }   
    if(m_buttonCtlInfo.hBitmapOfEnter)   
    {   
        ::DeleteObject(m_buttonCtlInfo.hBitmapOfEnter);   
        m_buttonCtlInfo.hBitmapOfEnter = NULL;   
    }   
    if(m_buttonCtlInfo.hBitmapOfFocus)   
    {   
        ::DeleteObject(m_buttonCtlInfo.hBitmapOfFocus);   
        m_buttonCtlInfo.hBitmapOfFocus = NULL;   
    }   
    if(m_buttonCtlInfo.hBitmapOfNormal)   
    {   
        ::DeleteObject(m_buttonCtlInfo.hBitmapOfNormal);   
        m_buttonCtlInfo.hBitmapOfNormal = NULL;   
    }   
    if(m_buttonCtlInfo.hBitmapOfPress)   
    {   
        ::DeleteObject(m_buttonCtlInfo.hBitmapOfPress);   
        m_buttonCtlInfo.hBitmapOfPress = NULL;   
    }   
   
    ////////////////////////////////////    
    //清除图标句柄    
    if(m_buttonCtlInfo.hIconOfDefault)   
    {   
        ::DestroyIcon(m_buttonCtlInfo.hIconOfDefault);   
        m_buttonCtlInfo.hIconOfDefault = NULL;   
    }   
    if(m_buttonCtlInfo.hIconOfDisable)   
    {   
        ::DestroyIcon(m_buttonCtlInfo.hIconOfDisable);   
        m_buttonCtlInfo.hIconOfDisable = NULL;   
    }   
    if(m_buttonCtlInfo.hIconOfEnter)   
    {   
        ::DestroyIcon(m_buttonCtlInfo.hIconOfEnter);   
        m_buttonCtlInfo.hIconOfEnter = NULL;   
    }   
    if(m_buttonCtlInfo.hIconOfFocus)    
    {   
        ::DestroyIcon(m_buttonCtlInfo.hIconOfFocus);   
        m_buttonCtlInfo.hIconOfFocus = NULL;   
    }   
    if(m_buttonCtlInfo.hIconOfNormal)   
    {   
        ::DestroyIcon(m_buttonCtlInfo.hIconOfNormal);   
        m_buttonCtlInfo.hIconOfNormal = NULL;   
    }   
    if(m_buttonCtlInfo.hIconOfPress)   
    {   
        ::DestroyIcon(m_buttonCtlInfo.hIconOfPress);   
        m_buttonCtlInfo.hIconOfPress = NULL;   
    }   
   
    /////////////////////////    
    //清除光标句柄     
    if(m_buttonCtlInfo.hCursor)   
    {   
        ::DestroyCursor(m_buttonCtlInfo.hCursor);   
        m_buttonCtlInfo.hCursor = NULL;   
    }   
    return;   
}   
   
   
///////////////////////////////////////////////////////////////////////    
//    
// 函数名  : CButtonEx::ShowText    
// 功能描述: 指定是否显示按钮标题    
// 参数    : BOOL bShowText设置TRUE表示显示，否则不显示    
// 返回值  : void     
//    
///////////////////////////////////////////////////////////////////////    
void CButtonEx::ShowText(BOOL bShowText)   
{   
    m_buttonCtlInfo.bDrawText = bShowText;   
    return;   
}   
   
   
///////////////////////////////////////////////////////////////////////    
//    
// 函数名  : CButtonEx::ShowFrame    
// 功能描述: 指定是否显示边框    
// 参数    : BOOL bShowFrame设置TRUE表示显示，否则不显示    
// 返回值  : void     
//    
///////////////////////////////////////////////////////////////////////    
void CButtonEx::ShowFrame(BOOL bShowFrame)   
{   
    m_buttonCtlInfo.bDrawFrame = bShowFrame;   
    return;   
}   
   
   
   
BOOL CButtonEx::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)    
{   
    HCURSOR hCursor = GetHcursor();   
    if(hCursor)   
    {   
        ::SetCursor(hCursor);   
        return TRUE;   
    }   
    return CButton::OnSetCursor(pWnd, nHitTest, message);   
}   
   
   
///////////////////////////////////////////////////////////////////////    
//    
// 函数名  : CButtonEx::GetHcursor    
// 功能描述: 取进入按钮时的光标指针    
// 返回值  : HCURSOR 当返回NULL时默认系统指针，否则用户自定义指针    
//    
///////////////////////////////////////////////////////////////////////    
HCURSOR CButtonEx::GetHcursor()   
{   
    return m_buttonCtlInfo.hCursor;   
}   
   
///////////////////////////////////////////////////////////////////////    
//    
// 函数名  : CButtonEx::SetCursorFromHcursor    
// 功能描述: 设置当光标进入按钮的显示的样子    
// 参数    : HCURSOR hCursor指定光标句柄    
// 返回值  : HCURSOR 返回以前的光标句柄    
//    
///////////////////////////////////////////////////////////////////////    
HCURSOR CButtonEx::SetCursorFromHcursor(HCURSOR hCursor)   
{   
    HCURSOR hPreCursor = m_buttonCtlInfo.hCursor;   
    m_buttonCtlInfo.hCursor = hCursor;   
    return hPreCursor;   
}   
   
///////////////////////////////////////////////////////////////////////    
//    
// 函数名  : CButtonEx::SetCursorFromFile    
// 功能描述: 从文件装入光标    
// 参数    : CString strFileName指定文件名    
// 返回值  : BOOL 成功装入返回TRUE，否则返回FALSE    
//    
///////////////////////////////////////////////////////////////////////    
BOOL CButtonEx::SetCursorFromFile(CString strFileName)   
{   
    HCURSOR hCursor = (HCURSOR)   
        ::LoadImage(NULL,strFileName,IMAGE_CURSOR,0,0,LR_LOADFROMFILE);   
    if(hCursor)   
    {   
        m_buttonCtlInfo.hCursor = hCursor;   
    }   
    return (BOOL)hCursor;   
}   
   
   
///////////////////////////////////////////////////////////////////////    
//    
// 函数名  : CButtonEx::SetCursorFromID    
// 功能描述: 从资源装入光标    
// 参数    : UINT nID指定资源ID    
// 返回值  : BOOL 成功装入返回TRUE，否则返回FALSE    
//    
///////////////////////////////////////////////////////////////////////    
BOOL CButtonEx::SetCursorFromID(UINT nID)   
{   
    HCURSOR hCursor = ::LoadCursor(::AfxGetInstanceHandle(),MAKEINTRESOURCE(nID));   
    if(hCursor)   
    {   
        m_buttonCtlInfo.hCursor = hCursor;   
    }   
    return (BOOL)hCursor;   
}   
   
void CButtonEx::OnClicked()    
{ 
    /////////////////////////////////    
    //如果是单选或复选控件    
    int nCtlType = GetCtlType();   
    switch(nCtlType)   
    {   
    case CTL_TYPE_CHECK:   
    case CTL_TYPE_RADIO:   
        SetCheck((nCtlType==CTL_TYPE_CHECK) ? !m_nCheck : TRUE);   
        break;   
    }   
   
    /////////////////////////////////    
    //调用父窗口中的单击处理过程    
    HWND hParentWnd = ::GetParent(GetSafeHwnd());   
    CButtonEx* pParentWnd = (CButtonEx*)CWnd::FromHandlePermanent(hParentWnd);   
    if(!pParentWnd)   
    {   
        return ;   
    }   
   
    const AFX_MSGMAP* pMsgMap = pParentWnd->GetMessageMap();   
    const AFX_MSGMAP_ENTRY* pMsgEntry = NULL;   
    BOOL bLoop = TRUE;   
    while(pMsgMap && bLoop)   
    {   
        int nIndex = 0;   
        pMsgEntry = pMsgMap->lpEntries;   
        do   
        {   
            if(pMsgEntry[nIndex].nMessage == 0 &&   
                pMsgEntry[nIndex].nCode == 0 &&   
                pMsgEntry[nIndex].nID == 0 &&   
                pMsgEntry[nIndex].nLastID == 0 &&   
                pMsgEntry[nIndex].nSig == AfxSig_end &&   
                pMsgEntry[nIndex].pfn == 0)   
            {   
                break;   
            }   
   
            UINT nID = GetDlgCtrlID();   
            if(pMsgEntry[nIndex].nMessage == WM_COMMAND &&    
                pMsgEntry[nIndex].nCode == BN_CLICKED &&   
                pMsgEntry[nIndex].nID == nID &&    
                pMsgEntry[nIndex].nLastID == nID &&   
                pMsgEntry[nIndex].nSig == AfxSigCmd_v) // The value in MFC10.0 has changed from AfxSig_vv(12) to AfxSigCmd_v(57)
				//pMsgEntry[nIndex].nSig == AfxSig_vv) // MFC6.0 should use AfxSig_vv instead of AfxSigCmd_v
            {   
                (pParentWnd->*pMsgEntry[nIndex].pfn)();   
                bLoop = FALSE;   
                break;   
            }   
   
            nIndex++;
        }while(TRUE);   
#ifdef _AFXDLL    
		if (NULL == pMsgMap->pfnGetBaseMap)
		{
			break;
		}
		pMsgMap = (pMsgMap->pfnGetBaseMap)();   
#else    
        pMsgMap = pMsgMap->pBaseMap;   
#endif    
    }   
   
    return;   
}   
   
   
///////////////////////////////////////////////////////////////////////    
//    
// 函数名  : CButtonEx::SetCheck    
// 功能描述: 设置复选或单选控件值    
// 参数    : int nCheck设置的值    
// 返回值  : void     
// 说明    : 此函数对按钮控件无效，此函数重载CButton父类    
///////////////////////////////////////////////////////////////////////    
void CButtonEx::SetCheck(int nCheck)   
{   
    int nCtlType = GetCtlType();   
    if(nCtlType == CTL_TYPE_BUTTON)   
    {   
        return;   
    }   
   
    m_nCheck = nCheck;   
    if(nCtlType == CTL_TYPE_RADIO)   
    {   
        AdjustRadioValue(GetSafeHwnd());   
    }   
    if(IsOwnerDraw())   
    {   
        HDC hdc = ::GetDC(m_hWnd);   
        RefreshShell(hdc);   
        ::ReleaseDC(m_hWnd,hdc);   
    }   
    else   
    {   
        CButton::SetCheck(m_nCheck);   
    }   
    return;   
}   
   
   
///////////////////////////////////////////////////////////////////////    
//    
// 函数名  : CButtonEx::GetCheck    
// 功能描述: 取设置值    
// 返回值  : int 返回选择值    
// 说明    : 此函数对按钮控件无效，此函数重载CButton父类    
///////////////////////////////////////////////////////////////////////    
int CButtonEx::GetCheck()   
{   
    return m_nCheck;   
}   
   
   
///////////////////////////////////////////////////////////////////////    
//    
// 函数名  : CButtonEx::AdjustRadioValue    
// 功能描述: 调整单选控件设置值    
// 参数    : HWND hRadioCtl指定的单选控件句柄不设置    
// 返回值  : void     
//    
///////////////////////////////////////////////////////////////////////    
void CButtonEx::AdjustRadioValue(HWND hRadioCtl)   
{   
    CButtonSubclassStruct subclassInfo;   
    if(!GetSubclassInfo(hRadioCtl,&subclassInfo))   
    {   
        return;   
    }   
   
    int nGroup = subclassInfo.nGroup;   
//  int nPos = subclassInfo.nPos;    
   
    POSITION pos = m_listSubclassInfo.GetHeadPosition();   
    while(pos)   
    {   
        CButtonSubclassStruct tempSubclassInfo = m_listSubclassInfo.GetNext(pos);   
        if(tempSubclassInfo.nButtonType == CTL_TYPE_RADIO &&   
            tempSubclassInfo.nGroup == nGroup &&   
            tempSubclassInfo.hCtlWnd != hRadioCtl)   
        {   
            HWND hWnd = tempSubclassInfo.hCtlWnd;   
            CButtonEx* pButton = (CButtonEx*)CWnd::FromHandlePermanent(hWnd);   
            if(pButton && pButton->GetCheck())   
            {   
                pButton->SetCheckValue(FALSE);   
                if(pButton->IsOwnerDraw())   
                {   
                    HDC hdc = ::GetDC(hWnd);   
                    pButton->RefreshShell(hdc);   
                    ::ReleaseDC(hWnd,hdc);   
                }   
                else   
                {   
                    pButton->CButton::SetCheck(FALSE);   
                }   
                break;   
            }   
        }   
    }   
    return;   
}   
   
   
///////////////////////////////////////////////////////////////////////    
//    
// 函数名  : CButtonEx::RefreshShell    
// 功能描述: 根据值刷新控件界面显示    
// 返回值  : void     
// 说明    : 此函数对按钮控件无效    
///////////////////////////////////////////////////////////////////////    
void CButtonEx::RefreshShell(HDC hdc,BOOL bPress) 
{   
    if(GetCheck() || bPress)   
    {   
        DrawBState(hdc,PRESS);   
    }   
    else if(!IsWindowEnabled())   
    {   
        DrawBState(hdc,DISABLED);   
    }   
    else   
    {   
        DrawBState(hdc,NORMAL);   
    }   
   
    return;   
}   
   
   
///////////////////////////////////////////////////////////////////////    
//    
// 函数名  : CButtonEx::GetSubclassInfo    
// 功能描述: 取子类化信息    
// 参数    : HWND hWnd指定要取的控件句柄    
// 参数    : CButtonSubclassStruct *pSubclassInfo返回子类化信息    
// 返回值  : BOOL 成功得到返回TRUE，否则返回FALSE    
//    
///////////////////////////////////////////////////////////////////////    
BOOL CButtonEx::GetSubclassInfo(HWND hWnd, CButtonSubclassStruct *pSubclassInfo)   
{   
    POSITION pos = FindSubclassInfoPos(hWnd);   
    if(pos)   
    {   
        *pSubclassInfo = m_listSubclassInfo.GetAt(pos);   
    }   
    return (BOOL)pos;   
}   
   
   
///////////////////////////////////////////////////////////////////////    
//    
// 函数名  : CButtonEx::SetCheckValue    
// 功能描述: 设置单选或复选控件值    
// 参数    : int nCheck要设置的状态    
// 返回值  : void     
// 说明    : 此函数只能由AdjustRadioValue()调用    
///////////////////////////////////////////////////////////////////////    
void CButtonEx::SetCheckValue(int nCheck)   
{   
    m_nCheck = nCheck;   
    return;   
}   
   
   
///////////////////////////////////////////////////////////////////////    
//    
// 函数名  : CButtonEx::IsOwnerDraw    
// 功能描述: 确定是否是自画控件    
// 返回值  : BOOL 返回TRUE表示自画，否则不是    
//    
///////////////////////////////////////////////////////////////////////    
BOOL CButtonEx::IsOwnerDraw()   
{   
    UINT nStyle = GetButtonStyle();   
    return (nStyle & BS_OWNERDRAW) == BS_OWNERDRAW;   
}   
   
   
///////////////////////////////////////////////////////////////////////    
//    
// 函数名  : CButtonEx::GetCtlType    
// 功能描述: 取得当前控件的类型    
// 返回值  : int 返回值有CTL_TYPE_BUTTON,CTL_TYPE_RADIO,CTL_TYPE_CHECK    
//    
///////////////////////////////////////////////////////////////////////    
int CButtonEx::GetCtlType()   
{   
    return m_nCtlType;   
}   
   
///////////////////////////////////////////////////////////////////////    
//    
// 函数名  : CButtonEx::SetTransparent
// 功能描述: 设置按钮是否透明（无背景色）    
// 参数    : BOOL bTransparent指定是否透明
// 返回值  : void 
//    
///////////////////////////////////////////////////////////////////////    
void CButtonEx::SetTransparent(BOOL bTransparent)
{ 
	m_bTransparent = TRUE;
    if(GetSafeHwnd())   
    {   
        RedrawWindow();   
    }   
}
   
///////////////////////////////////////////////////////////////////////    
//    
// 函数名  : CButtonEx::SetTextColor    
// 功能描述: 设置文字颜色    
// 参数    : COLORREF clrTextColor指定颜色值    
// 返回值  : COLORREF 返回先前的颜色值    
//    
///////////////////////////////////////////////////////////////////////    
COLORREF CButtonEx::SetTextColor(COLORREF clrTextColor)   
{   
    COLORREF clrPre = m_buttonCtlInfo.clrTextColor;   
    m_buttonCtlInfo.clrTextColor = clrTextColor;   
    if(GetSafeHwnd())   
    {   
        RedrawWindow();   
    }   
    return clrPre;   
}

///////////////////////////////////////////////////////////////////////
//
// 函数名  : CButtonEx::SetButtonBkColor    
// 功能描述: 设置按钮背景颜色    
// 参数    : COLORREF clrBkColor指定颜色值    
// 返回值  : COLORREF 返回先前的颜色值    
//
///////////////////////////////////////////////////////////////////////
COLORREF CButtonEx::SetButtonBkColor(COLORREF clrBkColor)
{
	m_bTransparent = FALSE;
	COLORREF clrPre = m_buttonCtlInfo.clrBkColor;
	m_buttonCtlInfo.clrBkColor = clrBkColor;
	if (GetSafeHwnd())
	{
		RedrawWindow();
	}

	return clrPre;
}
   
   
///////////////////////////////////////////////////////////////////////    
//    
// 函数名  : CButtonEx::SetFontInfo    
// 功能描述: 设置字体信息    
// 参数    : CString strFontName指定字体名    
// 参数    : int nSize指定字体大小    
// 参数    : int *pPreSize返回先前的字体大小    
// 返回值  : CString 返回先前字体名    
//    
///////////////////////////////////////////////////////////////////////    
CString CButtonEx::SetFontInfo(CString strFontName, int nSize, int *pPreSize)   
{   
    CString strPreFontName = m_buttonCtlInfo.strFontName;   
    int nPreFontSize = m_buttonCtlInfo.nFontSize;   
    m_buttonCtlInfo.strFontName = strFontName;   
    m_buttonCtlInfo.strFontName.ReleaseBuffer();   
    m_buttonCtlInfo.nFontSize = nSize;   
    if(pPreSize)   
    {   
        *pPreSize = nPreFontSize;   
    }   
    if(GetSafeHwnd())   
    {   
        RedrawWindow();   
    }   
    return strPreFontName;   
}   
   
   
///////////////////////////////////////////////////////////////////////    
//    
// 函数名  : CButtonEx::SetOwnerDraw    
// 功能描述: 设置控件为自画    
// 返回值  : void     
//    
///////////////////////////////////////////////////////////////////////    
void CButtonEx::SetOwnerDraw()   
{   
    UINT uStyle = GetButtonStyle() | BS_OWNERDRAW;   
    SetButtonStyle(uStyle,FALSE);//改变按钮风格为自画;    
    return;   
}   
   
   
//----------------------------------------------------------------------    
//    
// 函数名  : CButtonEx::IsDrawFrameForState    
// 功能描述: 指定的状态是否要画边框    
// 参数    : int nState指定状态    
// 返回值  : BOOL 返回TRUE表示要画边框，否则不画    
//    
//----------------------------------------------------------------------    
BOOL CButtonEx::IsDrawFrameForState(int nState)   
{  
    BOOL bRet;   
    switch(nState)   
    {   
    case FOCUS:   
        bRet = m_buttonCtlInfo.bDrawFrameForFocusState;   
        break;   
    default:   
        bRet = FALSE;   
    }   
    return bRet;   
}  