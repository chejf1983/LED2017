// FullList.cpp : implementation file
// A ListCtrl that allows you to select full lines

#include "stdafx.h"
#include "FullList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFullList

CFullList::CFullList()
{
}

CFullList::~CFullList()
{
}


BEGIN_MESSAGE_MAP(CFullList, CListCtrl)
        //{{AFX_MSG_MAP(CFullList)
        ON_WM_LBUTTONDOWN()
        ON_WM_LBUTTONUP()
        ON_WM_LBUTTONDBLCLK()
        ON_WM_PAINT()
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFullList message handlers
// The idea is that when you click,
// we move the mouse coordinates to the far left
// However, you can't move it to 0 since that
// isn't a legit value. Also, MFC doesn't really
// use the values you pass to the base class when
// it defers to the default window handler!
// It uses the last message values. So, if
// the base class uses MFC, we can just change the
// point argument, but if it goes directly to
// windows (and it does) we have to modify the
// m_lastMsgSent in the thread state.
// This code does both just in case one day MS
// adds MFC code to the base class.
void CFullList::GoMargin(UINT &nFlags, CPoint &point)
  {
        int margin;
        CRect r;
        GetItemRect(0,&r,LVIR_LABEL);
        margin=r.left;
        point.x=margin; // fool MFC
        // fool everyone else
        _AFX_THREAD_STATE* pThreadState = AfxGetThreadState();
        pThreadState->m_lastSentMsg.lParam=
          MAKELONG(point.x,HIWORD(pThreadState->
           m_lastSentMsg.lParam));
  }

void CFullList::OnLButtonDown(UINT nFlags, CPoint point)
{
        GoMargin(nFlags,point);
        CListCtrl::OnLButtonDown(nFlags, point);
}

// Same logic here
void CFullList::OnLButtonUp(UINT nFlags, CPoint point)
{
        GoMargin(nFlags,point);
        CListCtrl::OnLButtonUp(nFlags, point);
}


void CFullList::OnLButtonDblClk(UINT nFlags, CPoint point)
{
        GoMargin(nFlags,point);
        CListCtrl::OnLButtonDblClk(nFlags, point);
}

void CFullList::OnPaint()
{
        CRect r;
        int n,n0,n1;
        CListCtrl::OnPaint(); // Let control draw itself
// find out first and last line
        n0=GetTopIndex();
        n1=GetCountPerPage();
        n1+=n0;
        CDC *dc=GetDC(); // don't use CPaintDC
// If we have a selected item, draw a rect around it
        for (n=n0;n!=n1;n++)
                {
                if (GetItemState(n,LVIS_SELECTED)!=LVIS_SELECTED) continue;
                GetItemRect(n,&r,LVIR_BOUNDS);
                r.InflateRect(-2,0);  // shrink a bit
                dc->SelectStockObject(HOLLOW_BRUSH);
                dc->Rectangle(&r);
                }
}
