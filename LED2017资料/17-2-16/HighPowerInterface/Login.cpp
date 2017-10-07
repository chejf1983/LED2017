// Login.cpp : implementation file
//

#include "stdafx.h"
#include "HighPowerInterface.h"
#include "Login.h"

#include "HighPowerInterfaceDlg.h"
#include "AuthorityView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CLogin dialog


CLogin::CLogin(CWnd* pParent /*=NULL*/)
	: CResizingDialog(CLogin::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLogin)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CLogin::DoDataExchange(CDataExchange* pDX)
{
	CResizingDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLogin)
	DDX_Control(pDX, IDC_Login, m_login);
	DDX_Control(pDX, IDC_Exit, m_exit);
	DDX_Control(pDX, IDC_changepassword, m_changePsd);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLogin, CResizingDialog)
	//{{AFX_MSG_MAP(CLogin)
	ON_BN_CLICKED(IDC_Exit, OnExit)
	ON_BN_CLICKED(IDC_changepassword, Onchangepassword)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_Login, OnLogin)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_enterEngineer, OnenterEngineer)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogin message handlers
extern CString PasswordFilePath;
extern CString mainpath;
bool enterE = TRUE;
BOOL CLogin::OnInitDialog() 
{
	CResizingDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	login = false;
	MoveWindow(300, 200, 270, 200);
	CRgn rgn;
	rgn.CreateRoundRectRgn(0, 0, 270, 200, 10, 10);
	SetWindowRgn(rgn, true);

	enterE =TRUE;// false;
	SetDialogFace();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

bool CLogin::OnLogin() 
{
	// TODO: Add your control notification handler code here
	CString str_engineer, str_password;
	GetDlgItemText(IDC_Engineer, str_engineer);
	GetDlgItemText(IDC_password, str_password);
	if((str_engineer == "")||(str_password ==""))
	{
		MessageBox("用户名或密码未填写");
		return false;
	}
	else if((str_engineer == "holychipengineer")
		&& (str_password == "holychippassword"))
	{
		login = true;
		MessageBox("成功登陆!");
		OnClose();
		return true;
	}
	else
	{
		CStdioFile m_file;
		CString filePath = PasswordFilePath;

		if(m_file.Open((LPCTSTR)filePath, CFile::modeRead))
		{	
			CString str;
			CString str_name;
			CString str_savedpd;

			while(m_file.ReadString(str))
			{
				sscanf(str, "%[^,]", str_name);
				if((0==strcmp(str_name, str_engineer)) 
					&& (strlen(str_name)==strlen(str_engineer)))
				{
					sscanf(str, "%*[^,],%[^,]",str_savedpd);
					if((0==strcmp(str_savedpd, str_password)) 
						&& (strlen(str_savedpd)==strlen(str_password)))
					{
						login = true;
						MessageBox("成功登陆!");
						m_file.Close();
					    OnClose();
					    return true;
					}
					else
					{
						MessageBox("密码不正确!");
						m_file.Close();
						return false;
					}
				}
			}

			MessageBox("用户名不存在!");
			m_file.Close();
			return false;
		}
		else
		{
			MessageBox("文件打开失败!");
			return false;
		}
	}
}

void CLogin::Onchangepassword() 
{
	// TODO: Add your control notification handler code here
	m_changepassword.DoModal();
}

void CLogin::OnExit() 
{
	// TODO: Add your control notification handler code here	
	CResizingDialog::OnClose();
}

void CLogin::SetDialogFace()
{
	m_changePsd.SetBitmaps(IDB_Button_ChangePsdNormal, IDB_Button_ChangePsdDown,
		                   IDB_Button_ChangePsdHigh, IDB_Button_ChangePsdDisable);
	m_changePsd.SizeToContent();

	m_login.SetBitmaps(IDB_Button_LoginNormal, IDB_Button_LoginDown,
		                   IDB_Button_LoginHigh, IDB_Button_LoginDisable);
	m_login.SizeToContent();

	m_exit.SetBitmaps(IDB_Button_ExitNormal, IDB_Button_ExitDown,
		                 IDB_Button_ExitHigh, IDB_Button_ExitDisable);
	m_exit.SizeToContent();	
}

void CLogin::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, 0);
	CResizingDialog::OnLButtonDown(nFlags, point);
}

BOOL CLogin::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return CResizingDialog::DrawBK(pDC, IDB_LoginBK, 0);
//	return CResizingDialog::OnEraseBkgnd(pDC);
}

void CLogin::OnenterEngineer() 
{
	// TODO: Add your control notification handler code here
	enterE = true;
	OnClose();
}
