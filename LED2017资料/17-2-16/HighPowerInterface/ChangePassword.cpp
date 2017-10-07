// ChangePassword.cpp : implementation file
//

#include "stdafx.h"
#include "HighPowerInterface.h"
#include "ChangePassword.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChangePassword dialog


CChangePassword::CChangePassword(CWnd* pParent /*=NULL*/)
	: CResizingDialog(CChangePassword::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChangePassword)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CChangePassword::DoDataExchange(CDataExchange* pDX)
{
	CResizingDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChangePassword)
	DDX_Control(pDX, IDC_Exit, m_changeexit);
	DDX_Control(pDX, IDC_SURE, m_changesure);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChangePassword, CResizingDialog)
	//{{AFX_MSG_MAP(CChangePassword)
	ON_BN_CLICKED(IDC_Exit, OnExit)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_SURE, OnSure)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChangePassword message handlers
extern CString PasswordFilePath;
extern CString mainpath;

BOOL CChangePassword::OnInitDialog() 
{
	CResizingDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	MoveWindow(300, 200, 270, 270);
	CRgn rgn;
	rgn.CreateRoundRectRgn(0, 0, 270, 270, 10, 10);
	SetWindowRgn(rgn, true);

	SetDialogFace();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

bool CChangePassword::OnSure() 
{
	// TODO: Add your control notification handler code here
	CString str_engineer, str_Oldpd, str_Newpd, str_Ensurepd;
	GetDlgItemText(IDC_Engineer, str_engineer);
	GetDlgItemText(IDC_Oldpd, str_Oldpd);
	GetDlgItemText(IDC_newpd, str_Newpd);
	GetDlgItemText(IDC_Ensurepd, str_Ensurepd);
	if(str_engineer == "")
	{
		MessageBox("请输入用户名!");
		return false;
	}
	else if(str_Oldpd == "")
	{
		MessageBox("请输入原密码!");
		return false;
	}
	else if(str_Newpd == "")
	{
		MessageBox("请输入新密码!");
		return false;
	}
	else if(str_Ensurepd == "")
	{
		MessageBox("请确认新密码!");
		return false;
	}
	else if(str_Newpd ==str_Oldpd)
	{
		MessageBox("新旧密码不能相同!");
		return false;
	}
	else if(str_Newpd != str_Ensurepd)
	{
		MessageBox("两次新密码输入不一致!");
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
					if((0==strcmp(str_savedpd, str_Oldpd)) && (strlen(str_savedpd)==strlen(str_Oldpd)))
					{
						//此处修改文件中的密码
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
								if(i==linenum-1)
								{
									CString change_str;
									change_str = str_engineer+","+str_Newpd;
									m_file.WriteString(change_str + "\n");
								}
								else
								{
									m_file.WriteString(file[i] + "\n");
								}
								i++;
							}
							
						//	m_file.Close();
							MessageBox("密码修改成功!");
							m_file.Close();
							OnClose();
							return true;
						}
					}
					else
					{
						MessageBox("密码不正确!");
						m_file.Close();
						return false;
					}
				}
			}

			MessageBox("用户不存在!");
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

void CChangePassword::OnExit() 
{
	// TODO: Add your control notification handler code here
	CResizingDialog::OnClose();
}

void CChangePassword::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, 0);
	CResizingDialog::OnLButtonDown(nFlags, point);
}

void CChangePassword::SetDialogFace()
{
	m_changesure.SetBitmaps(IDB_Button_SureNormal2, IDB_Button_SureDown2,
		                 IDB_Button_SureHigh2, IDB_Button_SureDisable2);
	m_changesure.SizeToContent();

	m_changeexit.SetBitmaps(IDB_Button_CancelNormal3, IDB_Button_CancelDown3,
		                 IDB_Button_CancelHigh3, IDB_Button_CancelDisable3);
	m_changeexit.SizeToContent();
}

BOOL CChangePassword::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return CResizingDialog::DrawBK(pDC, IDB_ChangePsdBK, 0);	
//	return CResizingDialog::OnEraseBkgnd(pDC);
}

HBRUSH CChangePassword::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CResizingDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if(nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		hbr=(HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}
