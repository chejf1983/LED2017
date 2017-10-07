// Note.cpp : implementation file
//

#include "stdafx.h"
#include "Note.h"
#include "resource.h"
#include "Global_MySpec.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNote

CNote * CNote::c_Note;
CString CNote::m_String;

CNote::CNote()
{
}

CNote::~CNote()
{
	ASSERT(c_Note==this);
	c_Note=NULL;
}


BEGIN_MESSAGE_MAP(CNote, CStatic)
	//{{AFX_MSG_MAP(CNote)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNote message handlers

void CNote::Show(CWnd * pParentWnd)
{
	if(c_Note!=NULL)
		return;
	c_Note=new CNote;
	if(!c_Note->Create(pParentWnd))
		delete c_Note;
	else 	
		c_Note->UpdateWindow();
}

void CNote::Destroy()
{
	if(c_Note==NULL)
		return;
	c_Note->Hide();
}

void CNote::Hide()
{
	DestroyWindow();
	AfxGetMainWnd()->UpdateWindow();
}

void CNote::Draw()
{
	c_Note->RedrawWindow();
}

void CNote::Passtext(CString String)
{
	m_String=String;
}

BOOL CNote::Create(CWnd * pParentWnd)
{
	CRect rect;
	pParentWnd->GetClientRect(&rect);
	int xleft=rect.left+rect.Width()/2-150;
	int dx=300;
	int ytop=rect.top+rect.Height()/2-75;
	int dy=150;

	CString strT;
	if(g_bEnglish)
		strT="Information";
	else
		strT="пео╒";
	return CWnd::Create(AfxRegisterWndClass(0,AfxGetApp()->LoadStandardCursor(IDC_ARROW)),
		strT,WS_VISIBLE|WS_DLGFRAME|WS_CAPTION, CRect(xleft,ytop,xleft+dx,ytop+dy),pParentWnd, ID_WIN, NULL);

}

void CNote::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CRect clRect;
	GetClientRect(clRect);
	CBrush BrushBack;
	BrushBack.CreateSolidBrush(RGB(192,192,192));
	dc.FillRect(&clRect,&BrushBack);

	COLORREF bk=RGB(192,192,192);
	dc.SetBkColor(bk);

	dc.SetTextAlign(TA_CENTER);

	dc.TextOut(clRect.left+clRect.Width()/2,clRect.top+clRect.Height()/3,m_String);
	
	// Do not call CStatic::OnPaint() for painting messages
}

void CNote::PostNcDestroy()
{
	delete this;
}

