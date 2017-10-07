// ButtonEx.cpp : implementation file    
//    
   
////////////////////////////////////////////////////////    
// ����:�Զ��尴ť��    
// ����: Lianglp    
// ����: 2004-4-9 14:29:21    
// �汾: 1.0    
// ˵��: ��ȫ����CButton��    
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
    //ȷ���ؼ�����    
    m_nCtlType = GetPreCtlType();   
    if(m_nCtlType == CTL_TYPE_UNKNOW)   
    {   
        return;//δ֪��ť����    
    }   
   
    ///////////////////////////////////////////////////    
    //ȷ���Ƿ�Ҫ�����Ի���������ΰ�ť��Ϊ�Ի����    
    //�������Ϳؼ�������λͼҲ�����Ի���񣬷���    
    //��������    
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
        //�����ѡ��ؼ��������໯��Ϣ    
        if(m_nCtlType == CTL_TYPE_RADIO)   
        {   
            static int nPosOfRadioCtl = 0;   
            static int nGroupOfRadioCtl = -1;   
            if(GetStyle() & WS_GROUP)   
            {   
                nPosOfRadioCtl = 0;//�������λ��;    
            }   
            if(nPosOfRadioCtl == 0)   
            {   
                nGroupOfRadioCtl++;//���������Զ���1;    
            }   
   
            CButtonSubclassStruct subclassInfo;   
            subclassInfo.hCtlWnd     = GetSafeHwnd();   
            subclassInfo.nButtonType = CTL_TYPE_RADIO;   
            subclassInfo.nPos        = nPosOfRadioCtl;   
            subclassInfo.nGroup      = nGroupOfRadioCtl;   
            AddSubclassInfo(&subclassInfo);   
   
            nPosOfRadioCtl++;//�����е�λ���Զ���1;    
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
// ������  : CButtonEx::SetTooltip    
// ��������: ������ʾ��Ϣ    
// ����    : CString strTooltipText��ʾ��Ϣ�ı�    
// ����ֵ  : �ɹ����÷���TRUE�����򷵻�FALSE    
//    
///////////////////////////////////////////////////////////////////////    
BOOL CButtonEx::SetTooltip(CString strTooltipText)   
{   
    if(!GetSafeHwnd())   
    {   
        return FALSE;//�����ťû�д�������ʧ��    
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
// ������  : CButtonEx::GetTooltip    
// ��������: ȡ��ʾ��Ϣ�ı�    
// ����ֵ  : CString ������ʾ��Ϣ�ı���û���򷵻ؿ�    
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
// ������  : CButtonEx::GetPreCtlType    
// ��������: ������ť����    
// ����ֵ  : int ���ذ�ť���ͣ�δ֪����CTL_TYPE_UNKNOW    
//    
///////////////////////////////////////////////////////////////////////    
int CButtonEx::GetPreCtlType()   
{   
    int nRet = CTL_TYPE_UNKNOW;   
    DWORD dwStyle = GetButtonStyle();   
    if((dwStyle & BS_AUTOCHECKBOX) == BS_AUTOCHECKBOX)//��ѡ��ؼ�    
    {   
        nRet = CTL_TYPE_CHECK;   
    }   
    else if((dwStyle & BS_AUTORADIOBUTTON) == BS_AUTORADIOBUTTON)//��ѡ�ؼ�    
    {   
        nRet = CTL_TYPE_RADIO;   
    }   
    else//��ť�ؼ�    
    {   
        nRet = CTL_TYPE_BUTTON;   
    }   
    return nRet;   
}   
   
   
   
///////////////////////////////////////////////////////////////////////    
//    
// ������  : CButtonEx::AddSubclassInfo    
// ��������: ������໯��Ϣ��(m_listSubclassInfo)������    
// ����    : CButtonSubclassStruct *pSubclassInfo������Ϣָ��    
// ����ֵ  : int �����������Ѵ��ڵ�����    
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
// ������  : CButtonEx::FindSubclassInfoPos    
// ��������: �������໯������Ϣ�������е�λ��    
// ����    : HWND hWndҪ���ҵľ��    
// ����ֵ  : POSITION �ɹ��ҵ�����ָ��λ�ã����򷵻�NULL    
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
// ������  : CButtonEx::RemoveSubclassInfo    
// ��������: �ͷ����໯��Ϣ    
// ����    : HWND hWndָ��Ҫ�ͷŵİ�ť���    
// ����ֵ  : int �������໯��Ϣ����    
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
// ������  : CButtonEx::DrawBState    
// ��������: ����ť״̬    
// ����    : HDC hdcָ��Ҫ�����豸���    
// ����    : int nStateָ��Ҫ���İ�ť״̬    
//          (NORMAL,ENTER,FOCUS,PRESS,DISABLED,DEFAULT)    
// ����ֵ  : void     
//    
///////////////////////////////////////////////////////////////////////    
void CButtonEx::DrawBState(HDC hdc,int nState)   
{   
    DWORD dwHandle = NULL;   
    SetClipRgn(hdc);   
    ////////////////////////    
    //��ʾͼƬ����    
    int nDrawType = GetDrawType(nState,&dwHandle);   
    switch(nDrawType)   
    {   
    case DRAW_TYPE_BITMAP://��λͼ��ť
        DrawBBitmap(hdc,(HBITMAP)dwHandle);   
        break;   
    case DRAW_TYPE_ICON://��ͼ�갴ť    
        DrawBIcon(hdc,(HICON)dwHandle);   
        break;   
    default://û��ͼ�λ�    
        DrawBNormal(hdc);   
        break;   
    }   
 
    /////////////////////////    
    //��ʾ����    
    if(IsDrawText())   
    {   
        DrawBText(hdc,nState);   
    }   
	
    /////////////////////////    
    //����ť�߿�    
    if(IsDrawFrame())   
    {   
        DrawBFrame(hdc,nState);   
    }   
    return;   
}   
   
   
///////////////////////////////////////////////////////////////////////    
//    
// ������  : CButtonEx::GetDrawType    
// ��������: ָ��״̬�Ļ�����    
// ����    : int nStateָ��״̬    
// ����    : DWORD* pdwHandle����ͼ���λͼ��������    
// ����ֵ  : int ����״̬�Ļ�����    
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
// ������  : CButtonEx::DrawBBitmap    
// ��������: ָ��λͼ����ڰ�ť�ϻ�    
// ����    : HDC hdcָ���豸������    
// ����    : HBITMAP hBitmapָ��λͼ���    
// ����ֵ  : void     
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
// ������  : CButtonEx::DrawBIcon    
// ��������: ��ָ�����豸�������ϻ�ͼ��    
// ����    : HDC hdcָ���豸�����ľ��    
// ����    : HICON hIconָ��ͼ����    
// ����ֵ  : void     
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
// ������  : CButtonEx::DrawBNormal    
// ��������: ����ָ������ɫ������ɫ    
// ����    : HDC hdcָ���豸������    
// ����ֵ  : void     
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
// ������  : CButtonEx::DrawBFrame    
// ��������: ��ָ�����    
// ����    : HDC hdcָ���豸������    
// ����    : int nStateָ��״̬    
// ����ֵ  : void     
//    
///////////////////////////////////////////////////////////////////////    
void CButtonEx::DrawBFrame(HDC hdc, int nState)   
{   
    BOOL bDrawFrame = TRUE;   
    UINT nFlags;   
    switch(nState)   
    {   
    case ENTER://����״̬ʱ��     
    case FOCUS://�н���״̬    
        if(nState == FOCUS)   
        {   
            bDrawFrame = IsDrawFrameForState(FOCUS);   
        }   
        nFlags = BDR_RAISEDINNER;   
        break; 
    case PRESS://����״̬ʱ��     
        nFlags = BDR_SUNKENOUTER;   
        break;   
    default:   
        bDrawFrame = FALSE;//����״̬�����߿�       
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
// ������  : CButtonEx::DrawBText    
// ��������: ���ı�    
// ����    : HDC hdcָ���豸������    
// ����    : int nStateָ��״̬    
// ����ֵ  : void     
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
// ������  : CButtonEx::IsDrawText    
// ��������: �����Ƿ�Ҫ���ı�    
// ����ֵ  : BOOL����TRUE����ʾ�������򲻻�    
//    
///////////////////////////////////////////////////////////////////////    
BOOL CButtonEx::IsDrawText()   
{   
    return m_buttonCtlInfo.bDrawText;   
}   
   
///////////////////////////////////////////////////////////////////////    
//    
// ������  : CButtonEx::IsDrawFrame    
// ��������: �����Ƿ񻭱߿�    
// ����ֵ  : BOOL ����TRUE����ʾ�������򲻻�    
//    
///////////////////////////////////////////////////////////////////////    
BOOL CButtonEx::IsDrawFrame()   
{   
    return m_buttonCtlInfo.bDrawFrame;   
}   
   
   
   
///////////////////////////////////////////////////////////////////////    
//    
// ������  : CButtonEx::SetTransparentKeyColor    
// ��������: ����ͼƬ�ؼ�ɫ    
// ����    : COLORREF clrKeyColorָ����ɫ    
// ����ֵ  : COLORREF ������ǰ���õ���ɫ    
//    
///////////////////////////////////////////////////////////////////////    
COLORREF CButtonEx::SetTransparentKeyColor(COLORREF clrKeyColor)   
{   
    COLORREF clrPre = m_buttonCtlInfo.clrTransparentKeyColor ;   
    m_buttonCtlInfo.clrTransparentKeyColor = clrKeyColor;   
    SetBRgn(&m_buttonCtlInfo.rgnCtl);//���ð�ť����    
    if(GetSafeHwnd())   
    {   
        RedrawWindow();   
    }   
    return clrPre;   
}   
   
///////////////////////    
//������������    
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
// ������  : CButtonEx::SetBRgn    
// ��������: ���ð�ť����    
// ����    : CRgn *pRgn���������õ�����    
// ����ֵ  : void     
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
                    if(clrPixel == clrKey)//ȥ���ؼ�ɫ    
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
// ������  : CButtonEx::GetHbitmapOf    
// ��������: ȡָ�����͵�λͼ    
// ����    : int nStateָ��״̬����    
// ����ֵ  : HBITMAP �ɹ��õ�����λͼ��������򷵻�NULL    
//    
///////////////////////////////////////////////////////////////////////    
HBITMAP CButtonEx::GetHbitmapOf(int nState)   
{   
    HBITMAP hRet = NULL;   
    switch(nState)   
    {   
    case NORMAL://������ʾʱλͼ    
        hRet = m_buttonCtlInfo.hBitmapOfNormal;   
        break;   
    case FOCUS://�н���ʱλͼ    
        hRet = m_buttonCtlInfo.hBitmapOfFocus;   
        break;   
    case PRESS://����ʱλͼ    
        hRet = m_buttonCtlInfo.hBitmapOfPress;   
        break;   
    case DISABLED://��Чʱλͼ    
        hRet = m_buttonCtlInfo.hBitmapOfDisable;   
        break;   
    case ENTER://������ʱλͼ    
        hRet = m_buttonCtlInfo.hBitmapOfEnter;   
        break;   
    case DEFAULT://Ĭ��λͼ    
        hRet = m_buttonCtlInfo.hBitmapOfDefault;   
        break;   
    }   
    return hRet;   
}   
   
   
///////////////////////////////////////////////////////////////////////    
//    
// ������  : CButtonEx::GetTransparentKeyColor    
// ��������: ȡ͸���ؼ�ɫ    
// ����ֵ  : COLORREF ���عؼ�ɫ    
//    
///////////////////////////////////////////////////////////////////////    
COLORREF CButtonEx::GetTransparentKeyColor()   
{   
    return m_buttonCtlInfo.clrTransparentKeyColor;   
}   
   
   
///////////////////////////////////////////////////////////////////////    
//    
// ������  : CButtonEx::SetBitmapFromID    
// ��������: ����Դװ��λͼ    
// ����    : UINT nIDָ����ԴID    
// ����    : int nStateָ��Ҫ���õ�״̬    
// ����ֵ  : BOOL �ɹ����÷���TRUE�����򷵻�FALSE    
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
// ������  : CButtonEx::SetBitmapFromFile    
// ��������: ���ļ�װ��λͼ    
// ����    : CString strFileName    
// ����    : int nStateָ��Ҫ���õ�״̬    
// ����ֵ  : BOOL �ɹ����÷���TRUE�����򷵻�FALSE    
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
// ������  : CButtonEx::SetBitmapFromHbitmap    
// ��������: ֱ�ӴӾ��װ��λͼ    
// ����    : HBITMAP hBitmapָ��λͼ���    
// ����    : int nStateָ��Ҫ���õ�״̬    
// ����ֵ  : BOOL �ɹ����÷���TRUE�����򷵻�FALSE    
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
   
    return (BOOL)hBitmap;//(��ȫ����hBitmapֵ)    
}   
   
///////////////////////////////////////////////////////////////////////    
//    
// ������  : CButtonEx::SetIconFromID    
// ��������: ����Դװ��ͼ��    
// ����    : UINT nIDָ����ԴID    
// ����    : int nStateָ��Ҫ���õ�״̬    
// ����ֵ  : BOOL �ɹ����÷���TRUE�����򷵻�FALSE    
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
// ������  : CButtonEx::SetIconFromFile    
// ��������:  ���ļ�װ��ͼ��    
// ����    : CString strFileNameָ���ļ���(Ӧ����·��)    
// ����    : int nStateָ��Ҫ���õ�״̬    
// ����ֵ  : BOOL �ɹ����÷���TRUE�����򷵻�FALSE    
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
// ������  : CButtonEx::SetIconFromHicon    
// ��������: ֱ�ӴӾ��װ��ͼ��    
// ����    : HICON hIconָ��ͼ����    
// ����    : int nStateָ��Ҫ���õ�״̬    
// ����ֵ  : BOOL �ɹ����÷���TRUE�����򷵻�FALSE    
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
    return (BOOL)hIcon;//(��ȫ����hIconֵ)    
}   
   
   
///////////////////////////////////////////////////////////////////////    
//    
// ������  : CButtonEx::SetBBitmap    
// ��������: ����ָ��״̬λͼ״̬��(m_buttonCtlInfo)��    
// ����    : HBITMAP hBitmapָ��λͼ���    
// ����    : int nStateָ��Ҫ���õ�״̬    
// ����ֵ  : void     
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
// ������  : CButtonEx::SetBIcon    
// ��������: ����ָ��״̬ͼ��״̬��(m_buttonCtlInfo)��    
// ����    : HICON hIconָ��ͼ���    
// ����    : int nStateָ��Ҫ���õ�״̬    
// ����ֵ  : void     
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
// ������  : CButtonEx::GetHiconOf    
// ��������: �������ͷ���ָ��ͼ�����    
// ����    : int nStateָ������״̬    
// ����ֵ  : HICON ����ͼ����    
//    
///////////////////////////////////////////////////////////////////////    
HICON CButtonEx::GetHiconOf(int nState)   
{   
    HICON hRet = NULL;   
    switch(nState)   
    {   
    case NORMAL://������ʾʱͼ��    
        hRet = m_buttonCtlInfo.hIconOfNormal;   
        break;   
    case FOCUS://�н���ʱͼ��    
        hRet = m_buttonCtlInfo.hIconOfFocus;   
        break;   
    case PRESS://����ʱͼ��    
        hRet = m_buttonCtlInfo.hIconOfPress;   
        break;   
    case DISABLED://��Чʱͼ��    
        hRet = m_buttonCtlInfo.hIconOfDisable;   
        break;   
    case ENTER://������ʱͼ��    
        hRet = m_buttonCtlInfo.hIconOfEnter;   
        break;   
    case DEFAULT://Ĭ��ͼ��    
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
// ������  : CButtonEx::OnMouseLeave    
// ��������: ����뿪��ťʱִ����Ϣ    
// ����    : WPARAM wParam    
// ����    : LPARAM lParam    
// ����ֵ  : LRESULT ���겿����NULL    
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
            DrawBState(hdc,DISABLED);//��Ч״̬     
        }   
        else if(nState & ODS_FOCUS)   
        {   
            if(nState & ODS_SELECTED)   
            {   
                DrawBState(hdc,PRESS);//ѡ�񲢰���״̬    
            }   
            else   
            {   
                DrawBState(hdc,FOCUS);//���ѡ��״̬    
            }   
        }   
        else if(nState & DEFAULT)//Ĭ�ϰ�ť״̬    
        {   
            DrawBState(hdc,DEFAULT);   
        }   
        else   
        {   
            DrawBState(hdc,NORMAL);//����״̬    
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
    //���λͼ���    
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
    //���ͼ����    
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
    //��������     
    if(m_buttonCtlInfo.hCursor)   
    {   
        ::DestroyCursor(m_buttonCtlInfo.hCursor);   
        m_buttonCtlInfo.hCursor = NULL;   
    }   
    return;   
}   
   
   
///////////////////////////////////////////////////////////////////////    
//    
// ������  : CButtonEx::ShowText    
// ��������: ָ���Ƿ���ʾ��ť����    
// ����    : BOOL bShowText����TRUE��ʾ��ʾ��������ʾ    
// ����ֵ  : void     
//    
///////////////////////////////////////////////////////////////////////    
void CButtonEx::ShowText(BOOL bShowText)   
{   
    m_buttonCtlInfo.bDrawText = bShowText;   
    return;   
}   
   
   
///////////////////////////////////////////////////////////////////////    
//    
// ������  : CButtonEx::ShowFrame    
// ��������: ָ���Ƿ���ʾ�߿�    
// ����    : BOOL bShowFrame����TRUE��ʾ��ʾ��������ʾ    
// ����ֵ  : void     
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
// ������  : CButtonEx::GetHcursor    
// ��������: ȡ���밴ťʱ�Ĺ��ָ��    
// ����ֵ  : HCURSOR ������NULLʱĬ��ϵͳָ�룬�����û��Զ���ָ��    
//    
///////////////////////////////////////////////////////////////////////    
HCURSOR CButtonEx::GetHcursor()   
{   
    return m_buttonCtlInfo.hCursor;   
}   
   
///////////////////////////////////////////////////////////////////////    
//    
// ������  : CButtonEx::SetCursorFromHcursor    
// ��������: ���õ������밴ť����ʾ������    
// ����    : HCURSOR hCursorָ�������    
// ����ֵ  : HCURSOR ������ǰ�Ĺ����    
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
// ������  : CButtonEx::SetCursorFromFile    
// ��������: ���ļ�װ����    
// ����    : CString strFileNameָ���ļ���    
// ����ֵ  : BOOL �ɹ�װ�뷵��TRUE�����򷵻�FALSE    
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
// ������  : CButtonEx::SetCursorFromID    
// ��������: ����Դװ����    
// ����    : UINT nIDָ����ԴID    
// ����ֵ  : BOOL �ɹ�װ�뷵��TRUE�����򷵻�FALSE    
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
    //����ǵ�ѡ��ѡ�ؼ�    
    int nCtlType = GetCtlType();   
    switch(nCtlType)   
    {   
    case CTL_TYPE_CHECK:   
    case CTL_TYPE_RADIO:   
        SetCheck((nCtlType==CTL_TYPE_CHECK) ? !m_nCheck : TRUE);   
        break;   
    }   
   
    /////////////////////////////////    
    //���ø������еĵ����������    
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
// ������  : CButtonEx::SetCheck    
// ��������: ���ø�ѡ��ѡ�ؼ�ֵ    
// ����    : int nCheck���õ�ֵ    
// ����ֵ  : void     
// ˵��    : �˺����԰�ť�ؼ���Ч���˺�������CButton����    
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
// ������  : CButtonEx::GetCheck    
// ��������: ȡ����ֵ    
// ����ֵ  : int ����ѡ��ֵ    
// ˵��    : �˺����԰�ť�ؼ���Ч���˺�������CButton����    
///////////////////////////////////////////////////////////////////////    
int CButtonEx::GetCheck()   
{   
    return m_nCheck;   
}   
   
   
///////////////////////////////////////////////////////////////////////    
//    
// ������  : CButtonEx::AdjustRadioValue    
// ��������: ������ѡ�ؼ�����ֵ    
// ����    : HWND hRadioCtlָ���ĵ�ѡ�ؼ����������    
// ����ֵ  : void     
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
// ������  : CButtonEx::RefreshShell    
// ��������: ����ֵˢ�¿ؼ�������ʾ    
// ����ֵ  : void     
// ˵��    : �˺����԰�ť�ؼ���Ч    
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
// ������  : CButtonEx::GetSubclassInfo    
// ��������: ȡ���໯��Ϣ    
// ����    : HWND hWndָ��Ҫȡ�Ŀؼ����    
// ����    : CButtonSubclassStruct *pSubclassInfo�������໯��Ϣ    
// ����ֵ  : BOOL �ɹ��õ�����TRUE�����򷵻�FALSE    
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
// ������  : CButtonEx::SetCheckValue    
// ��������: ���õ�ѡ��ѡ�ؼ�ֵ    
// ����    : int nCheckҪ���õ�״̬    
// ����ֵ  : void     
// ˵��    : �˺���ֻ����AdjustRadioValue()����    
///////////////////////////////////////////////////////////////////////    
void CButtonEx::SetCheckValue(int nCheck)   
{   
    m_nCheck = nCheck;   
    return;   
}   
   
   
///////////////////////////////////////////////////////////////////////    
//    
// ������  : CButtonEx::IsOwnerDraw    
// ��������: ȷ���Ƿ����Ի��ؼ�    
// ����ֵ  : BOOL ����TRUE��ʾ�Ի���������    
//    
///////////////////////////////////////////////////////////////////////    
BOOL CButtonEx::IsOwnerDraw()   
{   
    UINT nStyle = GetButtonStyle();   
    return (nStyle & BS_OWNERDRAW) == BS_OWNERDRAW;   
}   
   
   
///////////////////////////////////////////////////////////////////////    
//    
// ������  : CButtonEx::GetCtlType    
// ��������: ȡ�õ�ǰ�ؼ�������    
// ����ֵ  : int ����ֵ��CTL_TYPE_BUTTON,CTL_TYPE_RADIO,CTL_TYPE_CHECK    
//    
///////////////////////////////////////////////////////////////////////    
int CButtonEx::GetCtlType()   
{   
    return m_nCtlType;   
}   
   
///////////////////////////////////////////////////////////////////////    
//    
// ������  : CButtonEx::SetTransparent
// ��������: ���ð�ť�Ƿ�͸�����ޱ���ɫ��    
// ����    : BOOL bTransparentָ���Ƿ�͸��
// ����ֵ  : void 
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
// ������  : CButtonEx::SetTextColor    
// ��������: ����������ɫ    
// ����    : COLORREF clrTextColorָ����ɫֵ    
// ����ֵ  : COLORREF ������ǰ����ɫֵ    
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
// ������  : CButtonEx::SetButtonBkColor    
// ��������: ���ð�ť������ɫ    
// ����    : COLORREF clrBkColorָ����ɫֵ    
// ����ֵ  : COLORREF ������ǰ����ɫֵ    
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
// ������  : CButtonEx::SetFontInfo    
// ��������: ����������Ϣ    
// ����    : CString strFontNameָ��������    
// ����    : int nSizeָ�������С    
// ����    : int *pPreSize������ǰ�������С    
// ����ֵ  : CString ������ǰ������    
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
// ������  : CButtonEx::SetOwnerDraw    
// ��������: ���ÿؼ�Ϊ�Ի�    
// ����ֵ  : void     
//    
///////////////////////////////////////////////////////////////////////    
void CButtonEx::SetOwnerDraw()   
{   
    UINT uStyle = GetButtonStyle() | BS_OWNERDRAW;   
    SetButtonStyle(uStyle,FALSE);//�ı䰴ť���Ϊ�Ի�;    
    return;   
}   
   
   
//----------------------------------------------------------------------    
//    
// ������  : CButtonEx::IsDrawFrameForState    
// ��������: ָ����״̬�Ƿ�Ҫ���߿�    
// ����    : int nStateָ��״̬    
// ����ֵ  : BOOL ����TRUE��ʾҪ���߿򣬷��򲻻�    
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