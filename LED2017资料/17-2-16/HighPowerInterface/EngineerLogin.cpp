// EngineerLogin.cpp : implementation file
//

#include "stdafx.h"
#include "highpowerinterface.h"
#include "EngineerLogin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEngineerLogin dialog


CEngineerLogin::CEngineerLogin(CWnd* pParent /*=NULL*/)
	: CResizingDialog(CEngineerLogin::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEngineerLogin)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CEngineerLogin::DoDataExchange(CDataExchange* pDX)
{
	CResizingDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEngineerLogin)
	DDX_Control(pDX, IDC_Exit, m_exit);
	DDX_Control(pDX, IDC_Login, m_login);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEngineerLogin, CResizingDialog)
	//{{AFX_MSG_MAP(CEngineerLogin)
	ON_BN_CLICKED(IDC_Login, OnLogin)
	ON_BN_CLICKED(IDC_Exit, OnExit)
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEngineerLogin message handlers
BOOL CEngineerLogin::OnInitDialog() 
{
	CResizingDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	login = false;
	MoveWindow(300, 200, 270, 200);
	CRgn rgn;
	rgn.CreateRoundRectRgn(0, 0, 270, 200, 10, 10);
	SetWindowRgn(rgn, true);

	SetDialogFace();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEngineerLogin::OnLogin() 
{
	// TODO: Add your control notification handler code here
	CString str_engineer, str_password;
	GetDlgItemText(IDC_Engineer, str_engineer);
	GetDlgItemText(IDC_password, str_password);
	if((str_engineer == "")||(str_password ==""))
	{
		MessageBox("用户名或密码未填写");
	}
	else if((str_engineer == "0")//"holychipengineer")
		&& (str_password == "0"))//"holychippassword"))
	{
		login = true;
		MessageBox("成功登陆!");
		OnClose();
	}
	else
	{
		MessageBox("用户名或密码不正确!");
	}
}

void CEngineerLogin::OnExit() 
{
	// TODO: Add your control notification handler code here
	CResizingDialog::OnClose();
}

void CEngineerLogin::SetDialogFace()
{
	m_login.SetBitmaps(IDB_Button_LoginNormal, IDB_Button_LoginDown,
		                   IDB_Button_LoginHigh, IDB_Button_LoginDisable);
	m_login.SizeToContent();

	m_exit.SetBitmaps(IDB_Button_CancelNormal, IDB_Button_CancelDown,
		                IDB_Button_CancelHigh, IDB_Button_CancelDisable);
	m_exit.SizeToContent();	
}

void CEngineerLogin::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, 0);
	CResizingDialog::OnLButtonDown(nFlags, point);
}

BOOL CEngineerLogin::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return CResizingDialog::DrawBK(pDC, IDB_EngineerBK, 0);
//	return CResizingDialog::OnEraseBkgnd(pDC);
}
