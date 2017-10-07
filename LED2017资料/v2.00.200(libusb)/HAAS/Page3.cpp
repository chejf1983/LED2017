// Page3.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "Page3.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPage3 dialog
IMPLEMENT_DYNCREATE(CPage3, CDialog);

CPage3::CPage3(CWnd* pParent /*=NULL*/)
	: CDialog(CPage3::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPage3)
	m_bShowCur = FALSE;
	//}}AFX_DATA_INIT
	m_bFir=TRUE;
	m_pSpData=NULL;

	m_drawData.bMouse	= FALSE;
	m_drawData.iCurSele	= 0;
	m_drawData.bShowCur	= TRUE;
	m_drawData.iDrawType= 0;
	m_drawData.iB=0;
	m_drawData.iE=0;

	CString strSection  = "Page3";

	CString strShowCur  = "ShowCur";
	CString strDrawType = "DrawType";

	m_bShowCur=AfxGetApp()->GetProfileInt(strSection,strShowCur,TRUE);
	m_drawData.bShowCur=m_bShowCur;
	m_drawData.iDrawType=AfxGetApp()->GetProfileInt(strSection,strDrawType,1);
}


void CPage3::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPage3)
	DDX_Control(pDX, IDC_BUTTON_RR, m_cRR);
	DDX_Control(pDX, IDC_BUTTON_R, m_cR);
	DDX_Control(pDX, IDC_BUTTON_LL, m_cLL);
	DDX_Control(pDX, IDC_BUTTON_L, m_cL);
	DDX_Control(pDX, IDC_DRAW, m_cDraw);
	DDX_Check(pDX, IDC_CHECK_CUR, m_bShowCur);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPage3, CDialog)
	//{{AFX_MSG_MAP(CPage3)
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_MESSAGE_VOID(WM_KICKIDLE, OnKickIdle)
	ON_BN_CLICKED(IDC_CHECK_CUR, OnCheckCur)
	ON_BN_CLICKED(IDC_BUTTON_LL, OnButtonLl)
	ON_BN_CLICKED(IDC_BUTTON_L, OnButtonL)
	ON_BN_CLICKED(IDC_BUTTON_R, OnButtonR)
	ON_BN_CLICKED(IDC_BUTTON_RR, OnButtonRr)
	ON_BN_CLICKED(IDC_BUTTON_TYPE, OnButtonType)
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPage3 message handlers

BOOL CPage3::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	m_cL.EnableWindow(m_bShowCur);
	m_cR.EnableWindow(m_bShowCur);
	m_cLL.EnableWindow(m_bShowCur);
	m_cRR.EnableWindow(m_bShowCur);

	SetPos();
	ReDraw();
	m_bFir=FALSE;
	SetPos();
	ReDraw();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPage3::SetPos()
{
	CRect clRect;
	GetClientRect(clRect);
	if(m_bFir)
	{
		clRect.left		= 0;
		clRect.right	= 1500;
		clRect.top		= 0;
		clRect.bottom	= 1500;
	}
	clRect.top=clRect.top+30;
	m_cDraw.MoveWindow(clRect);
}

void CPage3::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(!m_bFir)
	{
		SetPos();
		ReDraw();
	}	
}

void CPage3::ReDraw()
{
	if(m_pSpData==NULL)
	{
		CSpectData spTemp;
		m_cDraw.DrawSpect(spTemp,m_drawData,"");
	}
	else
	{
		m_cDraw.DrawSpect(*m_pSpData,m_drawData,"",TRUE);
	}
}


void CPage3::OnKickIdle()
{
	SendMessageToDescendants( WM_IDLEUPDATECMDUI );
}

void CPage3::OnCheckCur() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_drawData.bShowCur=m_bShowCur;
	ReDraw();

	m_cL.EnableWindow(m_bShowCur);
	m_cR.EnableWindow(m_bShowCur);
	m_cLL.EnableWindow(m_bShowCur);
	m_cRR.EnableWindow(m_bShowCur);
	SaveSet();
}

void CPage3::OnButtonLl() 
{
	// TODO: Add your control notification handler code here
	m_drawData.iCurSele=m_drawData.iCurSele-5;
		m_drawData.iB	= m_drawData.iCurSele;
		m_drawData.iE	= m_drawData.iCurSele;
		m_drawData.bMouse=FALSE;
	ReDraw();
}

void CPage3::OnButtonL() 
{
	// TODO: Add your control notification handler code here
	m_drawData.iCurSele=m_drawData.iCurSele-1;
	m_drawData.iB	= m_drawData.iCurSele;
	m_drawData.iE	= m_drawData.iCurSele;
	m_drawData.bMouse=FALSE;

	ReDraw();	
}

void CPage3::OnButtonR() 
{
	// TODO: Add your control notification handler code here
	m_drawData.iCurSele=m_drawData.iCurSele+1;
		m_drawData.iB	= m_drawData.iCurSele;
		m_drawData.iE	= m_drawData.iCurSele;
		m_drawData.bMouse=FALSE;
	ReDraw();		
}

void CPage3::OnButtonRr() 
{
	// TODO: Add your control notification handler code here
	m_drawData.iCurSele=m_drawData.iCurSele+5;
		m_drawData.iB	= m_drawData.iCurSele;
		m_drawData.iE	= m_drawData.iCurSele;
		m_drawData.bMouse=FALSE;
	ReDraw();			
}

void CPage3::OnButtonType() 
{
	// TODO: Add your control notification handler code here
	if(m_drawData.iDrawType==0)
		m_drawData.iDrawType=1;
	else
		m_drawData.iDrawType=0;
	ReDraw();	
	SaveSet();
}

void CPage3::SaveSet()
{
	CString strSection  =  "Page3";

	CString strShowCur  =  "ShowCur";
	CString strDrawType =  "DrawType";

	AfxGetApp()->WriteProfileInt(strSection,strShowCur,m_bShowCur);
	AfxGetApp()->WriteProfileInt(strSection,strDrawType,m_drawData.iDrawType);
}

void CPage3::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CRect Rect1,Rect2;
 	GetClientRect(&Rect1);
 	ClientToScreen(&Rect1);
 	m_cDraw.GetClientRect(&Rect2);
 	m_cDraw.ClientToScreen(&Rect2);
	if(((point.y+Rect1.top)>=Rect2.top)&&((point.y+Rect1.top)<=Rect2.bottom)&&((point.x+Rect1.left)>=Rect2.left)&&((point.x+Rect1.left)<=Rect2.right))
	{
		m_drawData.pt.x	= point.x-(Rect2.left-Rect1.left);
		m_drawData.iB	= point.x-(Rect2.left-Rect1.left);
		m_drawData.iE	= point.x-(Rect2.left-Rect1.left);
	}
	CDialog::OnLButtonDown(nFlags, point);
}

void CPage3::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CRect Rect1,Rect2;
 	GetClientRect(&Rect1);
 	ClientToScreen(&Rect1);
 	m_cDraw.GetClientRect(&Rect2);
 	m_cDraw.ClientToScreen(&Rect2);

	if(((point.y+Rect1.top)>=Rect2.top)&&((point.y+Rect1.top)<=Rect2.bottom)
		&&((point.x+Rect1.left)>=Rect2.left)&&((point.x+Rect1.left)<=Rect2.right))
	{
		m_drawData.iE=point.x-(Rect2.left-Rect1.left);
		m_drawData.pt.x=m_drawData.iE;
		m_drawData.bMouse=TRUE;
		ReDraw();
//		m_drawData.bMouse=FALSE;
//		ReDraw();
	}
	CDialog::OnLButtonUp(nFlags, point);
}

void CPage3::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CRect Rect1,Rect2;
 	GetClientRect(&Rect1);
 	ClientToScreen(&Rect1);
 	m_cDraw.GetClientRect(&Rect2);
 	m_cDraw.ClientToScreen(&Rect2);

	if(((point.y+Rect1.top)>=Rect2.top)&&((point.y+Rect1.top)<=Rect2.bottom)
		&&((point.x+Rect1.left)>=Rect2.left)&&((point.x+Rect1.left)<=Rect2.right))
	{
//		m_drawData.iB=point.x-(Rect2.left-Rect1.left);
//		m_drawData.pt.x=m_drawData.iB;
	}
	
	CDialog::OnMouseMove(nFlags, point);
}


