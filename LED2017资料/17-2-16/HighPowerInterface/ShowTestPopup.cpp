// ShowTestPopup.cpp : implementation file
//

#include "stdafx.h"
#include "highpowerinterface.h"
#include "ShowTestPopup.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ShowTestPopup dialog


ShowTestPopup::ShowTestPopup(CWnd* pParent /*=NULL*/)
	: CResizingDialog(ShowTestPopup::IDD, pParent)
{
	//{{AFX_DATA_INIT(ShowTestPopup)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	SetControlInfo(IDC_Popup, ANCHORE_RIGHT);
	SetControlInfo(IDC_Maximize, ANCHORE_RIGHT);
	SetControlInfo(IDC_ShowTest_List, RESIZE_BOTH);
}


void ShowTestPopup::DoDataExchange(CDataExchange* pDX)
{
	CResizingDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ShowTestPopup)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ShowTestPopup, CResizingDialog)
	//{{AFX_MSG_MAP(ShowTestPopup)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_Maximize, OnMaximize)
	ON_BN_CLICKED(IDC_Popup, OnPopup)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ShowTestPopup message handlers
int popup_max=0;
BOOL ShowTestPopup::OnInitDialog() 
{
	CResizingDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	MoveWindow(150,100,800,500);
	
//	m_showtestpopup_list.InsertColumn(0, "  Num", LVCFMT_CENTER, 70);
//	m_showtestpopup_list.InsertColumn(1, "BIN", LVCFMT_CENTER, 80);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void ShowTestPopup::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, 0);

	CResizingDialog::OnLButtonDown(nFlags, point);
}

void ShowTestPopup::OnMaximize() 
{
	// TODO: Add your control notification handler code here
	if(0 == popup_max)
	{
		PostMessage(WM_SYSCOMMAND, MAKEWPARAM(SC_MAXIMIZE,0),0);
		popup_max=1;
	}
	else
	{
		PostMessage(WM_SYSCOMMAND, MAKEWPARAM(SC_RESTORE,0),0);
		popup_max=0;
	}
}

void ShowTestPopup::OnPopup() 
{
	// TODO: Add your control notification handler code here
	ShowWindow(SW_HIDE);
}
