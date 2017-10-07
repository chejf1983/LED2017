// DeleteUsersDlg.cpp : implementation file
//

#include "stdafx.h"
#include "highpowerinterface.h"
#include "DeleteUsersDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDeleteUsersDlg dialog


CDeleteUsersDlg::CDeleteUsersDlg(CWnd* pParent /*=NULL*/)
	: CResizingDialog(CDeleteUsersDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDeleteUsersDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDeleteUsersDlg::DoDataExchange(CDataExchange* pDX)
{
	CResizingDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDeleteUsersDlg)
	DDX_Control(pDX, IDC_Delete, m_delete);
	DDX_Control(pDX, IDC_Cancel, m_cancel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDeleteUsersDlg, CResizingDialog)
	//{{AFX_MSG_MAP(CDeleteUsersDlg)
	ON_BN_CLICKED(IDC_Delete, OnDelete)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_Cancel, OnCancel)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDeleteUsersDlg message handlers
extern CString PasswordFilePath;
extern CString mainpath;

BOOL CDeleteUsersDlg::OnInitDialog() 
{
	CResizingDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	MoveWindow(300, 200, 270, 200);
	CRgn rgn;
	rgn.CreateRoundRectRgn(0, 0, 270, 200, 10, 10);
	SetWindowRgn(rgn, true);

	SetDialogFace();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

bool CDeleteUsersDlg::OnDelete() 
{
	// TODO: Add your control notification handler code here
	CString str_engineer, str_password;
	GetDlgItemText(IDC_Engineer, str_engineer);
	GetDlgItemText(IDC_password, str_password);
	
	if(str_engineer == "")
	{
		MessageBox("请输入要删除的用户!");
		return false;
	}
	else if(str_password == "")
	{
		MessageBox("请输入要删除的用户的密码!");
		return false;
	}
	else
	{
		CStdioFile m_file;
		CString filePath = PasswordFilePath;

		if(m_file.Open((LPCTSTR)filePath, CFile::modeRead))
		{	
			CString str, str_name, str_savedpd;

			int linenum = 0;
			while(m_file.ReadString(str))
			{
				linenum++;
				sscanf(str, "%[^,]", str_name);
				if((0==strcmp(str_name, str_engineer)) && (strlen(str_name)==strlen(str_engineer)))
				{
					sscanf(str, "%*[^,],%[^,]",str_savedpd);
					if((0==strcmp(str_savedpd, str_password)) && (strlen(str_savedpd)==strlen(str_password)))
					{
						//删除文件中用户及密码
						CString file[100];
						int i=0;
						m_file.SeekToBegin();
						while(m_file.ReadString(file[i]))
						{
							i++;
						}
						m_file.Close();
						/////重写文件
						if(m_file.Open((LPCTSTR)filePath, CFile::modeCreate|CFile::modeReadWrite))
						{
							i=0;
							while(file[i]!="")
							{
								if(i!=linenum-1)
								{
									m_file.WriteString(file[i] + "\n");	
								}
								i++;
							}
							
							MessageBox("用户删除成功!");
							m_file.Close();
							OnClose();
							return true;
						}
						else
						{
							MessageBox("文件重写失败!");
						}
					}
					else
					{
						MessageBox("密码不正确!");
						return false;
					}
				}
			}
			MessageBox("要删除的用户不存在!");
			return false;
		}
		else
		{
			MessageBox("文件打开失败!");
			return false;
		}
	}
}

void CDeleteUsersDlg::OnCancel() 
{
	// TODO: Add your control notification handler code here
	OnClose();
}

void CDeleteUsersDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, 0);
	CResizingDialog::OnLButtonDown(nFlags, point);
}

void CDeleteUsersDlg::SetDialogFace()
{
	m_delete.SetBitmaps(IDB_Button_DelNormal, IDB_Button_DelDown,
		                IDB_Button_DelHigh, IDB_Button_DelDisable);
	m_delete.SizeToContent();
	
	m_cancel.SetBitmaps(IDB_Button_CancelNormal, IDB_Button_CancelDown,
		                IDB_Button_CancelHigh, IDB_Button_CancelDisable);
	m_cancel.SizeToContent();		
}

BOOL CDeleteUsersDlg::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return CResizingDialog::DrawBK(pDC, IDB_DelUserBK, 0);
//	return CResizingDialog::OnEraseBkgnd(pDC);
}
