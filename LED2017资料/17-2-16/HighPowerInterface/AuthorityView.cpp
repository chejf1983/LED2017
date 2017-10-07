// AuthorityView.cpp : implementation file
//

#include "stdafx.h"
#include "HighPowerInterface.h"
#include "AuthorityView.h"
#include "Login.h"
#include "HighPowerInterfaceDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAuthorityView dialog
CAuthorityView::CAuthorityView(CWnd* pParent /*=NULL*/)
	: CResizingDialog(CAuthorityView::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAuthorityView)
	//}}AFX_DATA_INIT
}

void CAuthorityView::DoDataExchange(CDataExchange* pDX)
{
	CResizingDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAuthorityView)
	DDX_Control(pDX, IDC_Chiptype, m_chiptype);
	DDX_Control(pDX, IDC_Showtemperature, m_temperature);
	DDX_Control(pDX, IDC_ShowAuthority, m_showAuthority);
	DDX_Control(pDX, IDC_authoritychange, m_authoritychange);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAuthorityView, CResizingDialog)
	//{{AFX_MSG_MAP(CAuthorityView)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_authoritychange, Onauthoritychange)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_Showtemperature, OnShowtemperature)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAuthorityView message handlers
//extern Wrapper wrapper;

BOOL CAuthorityView::OnInitDialog() 
{
	CResizingDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	extern int screen_width, screen_height;
	extern float change_width, change_height;
	extern int after_width, after_height;
	extern int after_top, after_left;
	
	after_left = (int)(225*change_width);
	after_top = (int)(0*change_height);
	after_width = (int)(1055*change_width);
	after_height = (int)(40*change_height);

	MoveWindow(after_left, after_top, after_width, after_height);

	CResizingDialog::ChangeSize(IDC_authoritychange, change_width, change_height);
	CResizingDialog::ChangeSize(IDC_ShowAuthority, change_width, change_height);
	CResizingDialog::ChangeSize(IDC_Showtemperature, change_width, change_height);

	SetDlgItemText(IDC_ShowAuthority, "普通用户");

	m_authoritychange.SetBitmaps(IDB_Button_AuthorityNormal, IDB_Button_AuthorityDown,
		              IDB_Button_AuthorityHigh, IDB_Button_AuthorityDisable);
	m_authoritychange.SizeToContent();

	m_showAuthority.SetBitmaps(IDB_ShowAuthority, IDB_ShowAuthority,
		                       IDB_ShowAuthority, IDB_ShowAuthority);
	m_showAuthority.SizeToContent();
	m_showAuthority.SetDrawText(true, false)
			.SetFont3D(true, 3, 2, false)
		    .SetFontSize(20, false)
			.SetForceColor(RGB(255, 255, 255), RGB(255, 255, 255), RGB(255, 255, 255), false);

	m_temperature.SetBitmaps(IDB_Temperature, IDB_Temperature,
		                     IDB_Temperature, IDB_Temperature);
	m_temperature.SizeToContent();
	m_temperature.SetDrawText(true, false)
			.SetFont3D(true, 0, 0, false)
		    .SetFontSize(21, false)
			.SetForceColor(RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0), false);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAuthorityView::Onauthoritychange() 
{
	// TODO: Add your control notification handler code here
	CString str;
    GetDlgItemText(IDC_ShowAuthority, str);
	CHighPowerInterfaceDlg *pmain = (CHighPowerInterfaceDlg*)GetParent();
	if(str == "普通用户")
	{	
		pmain->OnOperator();
	}
	else
	{
		pmain->OnGuest();
	}
}

void CAuthorityView::OnShowtemperature() 
{
	// TODO: Add your control notification handler code here
// 	if(wrapper.isFeatureSupportedBoardTemperature(0))
// 	{
// 		BoardTemperature boardTemp;
// 		boardTemp = wrapper.getFeatureControllerBoardTemperature(0);
// 		double tempCelsius = 0;
// 		tempCelsius = boardTemp.getBoardTemperatureCelsius();
// 		CString str;
// 		str.Format("                                      %0.2f ℃", tempCelsius);
// 		SetDlgItemText(IDC_Showtemperature, str);
// 	}
}

BOOL CAuthorityView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return true;
}

HBRUSH CAuthorityView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CResizingDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	// TODO: Return a different brush if the default is not desired
	return hbr;
}


BOOL CAuthorityView::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message == WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
		case VK_F5:
			CHighPowerInterfaceDlg *pmain = (CHighPowerInterfaceDlg*)GetParent();
			pmain->OnTestSingle();
			return true;
		}
	}

	return CResizingDialog::PreTranslateMessage(pMsg);
}
