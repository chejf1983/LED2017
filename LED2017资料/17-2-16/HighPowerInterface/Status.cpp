// Status.cpp : implementation file
//

#include "stdafx.h"
#include "highpowerinterface.h"
#include "Status.h"
#include "HighPowerInterfaceDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStatus dialog


CStatus::CStatus(CWnd* pParent /*=NULL*/)
	: CResizingDialog(CStatus::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStatus)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CStatus::DoDataExchange(CDataExchange* pDX)
{
	CResizingDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStatus)
	DDX_Control(pDX, IDC_ShowCurrentFile, m_staFilePath);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CStatus, CResizingDialog)
	//{{AFX_MSG_MAP(CStatus)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatus message handlers
BOOL CStatus::OnInitDialog() 
{
	CResizingDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	extern int screen_width, screen_height;
	extern float change_width, change_height;
	extern int after_width, after_height;
	extern int after_top, after_left;
	
	after_left = (int)(0*change_width);
	after_top = (int)(667*change_height);
	after_width = (int)(1280*change_width);
	after_height = (int)(30*change_height);

//	MoveWindow(0, 667, 1280, 30);
	MoveWindow(after_left, after_top, after_width, after_height);

	CResizingDialog::ChangeSize(IDC_ShowCurrentFile, change_width, change_height);
	m_staFilePath.SetBitmaps(IDB_StaFilePath, IDB_StaFilePath,
		              IDB_StaFilePath, IDB_StaFilePath);
	m_staFilePath.SizeToContent();
	m_staFilePath.SetDrawText(true, false)
			.SetFont3D(true, 1, 0, false)
		    .SetFontSize(20, false)
			.SetForceColor(RGB(248, 224, 79), RGB(255, 255, 255), RGB(255, 255, 255), false);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CStatus::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return true;
}

HBRUSH CStatus::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CResizingDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here

	// TODO: Return a different brush if the default is not desired

	return hbr;
}

BOOL CStatus::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message == WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
		case VK_F5:
			return true;
		}
	}
	return CResizingDialog::PreTranslateMessage(pMsg);
}
