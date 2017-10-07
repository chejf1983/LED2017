// Page5.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "Page5.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPage5 dialog

IMPLEMENT_DYNCREATE(CPage5, CDialog);

CPage5::CPage5(CWnd* pParent /*=NULL*/)
	: CDialog(CPage5::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPage5)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_bFir = TRUE;
}


void CPage5::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPage5)
	DDX_Control(pDX, IDC_COLOR, m_cColor);
	DDX_Control(pDX, IDC_PASS, m_cPass);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPage5, CDialog)
	//{{AFX_MSG_MAP(CPage5)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPage5 message handlers

void CPage5::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(m_bFir == FALSE)
		SetPos();
}

BOOL CPage5::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	m_cPass.SetBkColor(GetSysColor(COLOR_3DFACE));
	m_cPass.SetTextColor(RGB(0, 0, 255));
	m_cPass.SetWindowText("PASS");
	m_cPass.SetFontSize(40);

	m_cColor.SetBkColor(RGB(255, 0, 255));
	m_cColor.SetTextColor(~RGB(255, 0, 255));
	m_cColor.SetWindowText("BIN COLOR");
	m_cColor.SetFontSize(20);

	m_bFir = FALSE;
	SetPos();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPage5::SetPos()
{
	CRect clRect;
	GetClientRect(clRect);

	CRect passRect;
	CRect colorRect;
	passRect.left = clRect.left + 5;
	passRect.right = clRect.right - 5;
	passRect.top = clRect.top + 5;
	passRect.bottom = clRect.bottom - 60;
	m_cPass.MoveWindow(passRect);

	colorRect = passRect;
	colorRect.top = passRect.bottom + 2;
	colorRect.bottom = clRect.bottom - 5;
	m_cColor.MoveWindow(colorRect);
}
