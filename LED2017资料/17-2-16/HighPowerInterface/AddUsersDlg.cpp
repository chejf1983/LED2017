// AddUsersDlg.cpp : implementation file
//

#include "stdafx.h"
#include "highpowerinterface.h"
#include "AddUsersDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddUsersDlg dialog


CAddUsersDlg::CAddUsersDlg(CWnd* pParent /*=NULL*/)
	: CResizingDialog(CAddUsersDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddUsersDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAddUsersDlg::DoDataExchange(CDataExchange* pDX)
{
	CResizingDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddUsersDlg)
	DDX_Control(pDX, IDC_Exit, m_addexit);
	DDX_Control(pDX, IDC_SURE, m_addsure);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddUsersDlg, CResizingDialog)
	//{{AFX_MSG_MAP(CAddUsersDlg)
	ON_BN_CLICKED(IDC_Exit, OnExit)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_SURE, OnSure)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddUsersDlg message handlers
extern CString PasswordFilePath;
extern CString mainpath;

BOOL CAddUsersDlg::OnInitDialog() 
{
	CResizingDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	MoveWindow(300, 200, 270, 250);
	CRgn rgn;
	rgn.CreateRoundRectRgn(0, 0, 270, 250, 10, 10);
	SetWindowRgn(rgn, true);

	SetDialogFace();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
/*
void OnEncrypt(CString *str)
{
	char *s;
	int i = 0;
	int *num;
	s = "";
	strcpy(s, *str);
	*str = "";
	while(s[i])
	{
		num[i] = s[i];
	}
}
*/
bool CAddUsersDlg::OnSure() 
{
	// TODO: Add your control notification handler code here
	CString str_new, str_password, str_ensurepd;
	GetDlgItemText(IDC_NewEngineer, str_new);
	GetDlgItemText(IDC_password, str_password);
	GetDlgItemText(IDC_EnsurePassword, str_ensurepd);

	bool add = true;
	bool addsuccess = false;

	if(str_new == "")
	{
		MessageBox("用户名不能为空!");
		return false;
	}
	else if(str_password == "")
	{
		MessageBox("请输入密码!");
		return false;
	}
	else if(str_ensurepd == "")
	{
		MessageBox("请确认密码!");
		return false;
	}
	else if(str_password!=str_ensurepd)
	{
		MessageBox("密码输入不一致!");
		return false;
	}
	else
	{
		CStdioFile m_file;
		CString filePath = PasswordFilePath;

		if(m_file.Open((LPCTSTR)filePath,
			CFile::modeCreate|CFile::modeNoTruncate|CFile::modeReadWrite|CFile::typeText))
		{
			CString str, str_name;
			int i = 0;
			while(m_file.ReadString(str))
			{
				sscanf(str,   "%[^,]",   str_name); 
				if((0==strcmp(str_name, str_new)) && (strlen(str_name)==strlen(str_new)))
				{
					MessageBox("用户名已存在!");
					add = false;
					m_file.Close();
					return false;
				}
				i++;
			}

			if(i >= 10)
			{
				MessageBox("最多添加10个用户 用户已满 不能再添加");
				m_file.Close();
				OnClose();
				return false;
			}

			else
			{
				m_file.WriteString(str_new + "," +str_password + "\n");
				m_file.Close();
			}
		    
		}
		else
		{
			MessageBox("文件打开失败!");
			return false;
		}

		if(m_file.Open((LPCTSTR)filePath, CFile::modeRead))
		{	
			CString str;
			CString str_name;
			while(m_file.ReadString(str))
			{
				sscanf(str,   "%[^,]",   str_name); 
				if((0==strcmp(str_name, str_new)) && (strlen(str_name)==strlen(str_new)))
				{
					addsuccess = true;
					break;	
				}
			}

			if(addsuccess)
			{
				MessageBox("用户"+str_new+"添加成功");	
				m_file.Close();
				OnClose();
				return true;
			}	
			else
			{
				MessageBox("用户"+str_new+"未添加成功");
				m_file.Close();
				return false;
			}
		}
		else
		{
			MessageBox("文件打开失败!");
			return false;
		}
	}
}

void CAddUsersDlg::OnExit() 
{
	// TODO: Add your control notification handler code here
	CResizingDialog::OnClose();
}

void CAddUsersDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, 0);
	CResizingDialog::OnLButtonDown(nFlags, point);
}

void CAddUsersDlg::SetDialogFace()
{
	m_addsure.SetBitmaps(IDB_Button_AddNormal, IDB_Button_AddDown,
		                 IDB_Button_AddHigh, IDB_Button_AddDisable);
	m_addsure.SizeToContent();

	m_addexit.SetBitmaps(IDB_Button_CancelNormal2, IDB_Button_CancelDown2,
		                 IDB_Button_CancelHigh2, IDB_Button_CancelDisable2);
	m_addexit.SizeToContent();
}

BOOL CAddUsersDlg::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return CResizingDialog::DrawBK(pDC, IDB_AddUserBK, 0);
}
