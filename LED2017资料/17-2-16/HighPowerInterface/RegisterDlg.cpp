// RegisterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "highpowerinterface.h"
#include "RegisterDlg.h"
#include "HardDisk.h"
#include "RegistHandle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRegisterDlg dialog


CRegisterDlg::CRegisterDlg(CWnd* pParent /*=NULL*/)
	: CResizingDialog(CRegisterDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRegisterDlg)
	m_code1 = _T("");
	m_code2 = _T("");
	m_code3 = _T("");
	m_code4 = _T("");
	//}}AFX_DATA_INIT
}


void CRegisterDlg::DoDataExchange(CDataExchange* pDX)
{
	CResizingDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRegisterDlg)
	DDX_Control(pDX, IDC_Register, m_register);
	DDX_Control(pDX, IDC_Cancel, m_cancel);
	DDX_Text(pDX, IDC_RegCode1, m_code1);
	DDX_Text(pDX, IDC_RegCode2, m_code2);
	DDX_Text(pDX, IDC_RegCode3, m_code3);
	DDX_Text(pDX, IDC_RegCode4, m_code4);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRegisterDlg, CResizingDialog)
	//{{AFX_MSG_MAP(CRegisterDlg)
	ON_BN_CLICKED(IDC_Register, OnRegister)
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_EN_CHANGE(IDC_RegCode1, OnChangeRegCode1)
	ON_EN_CHANGE(IDC_RegCode2, OnChangeRegCode2)
	ON_EN_CHANGE(IDC_RegCode3, OnChangeRegCode3)
	ON_BN_CLICKED(IDC_Cancel, OnCancel)
	ON_EN_CHANGE(IDC_RegCode4, OnChangeRegCode4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRegisterDlg message handlers
bool m_regedit = true;
extern int leftTimeAft;
bool regWinOpen = false;

BOOL CRegisterDlg::OnInitDialog() 
{
	CResizingDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	MoveWindow(400, 300, 550, 200);
	CRgn rgn;
	rgn.CreateRoundRectRgn(0, 0, 550, 200, 10, 10);
	SetWindowRgn(rgn, true);
	m_regedit = false;
	regWinOpen = true;

	CString CharacCode;
	CharacCode = GetCharacterCode();
	SetDlgItemText(IDC_CharacCode, CharacCode);

	SetDlgItemText(IDC_RegCode1, "");
	SetDlgItemText(IDC_RegCode2, "");
	SetDlgItemText(IDC_RegCode3, "");
	SetDlgItemText(IDC_RegCode4, "");

	registTime = 0;

	SetDialogFace();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRegisterDlg::OnRegister() 
{
	// TODO: Add your control notification handler code here
	leftTimeAft = 365;
	m_regedit = true;

	return;
	CString str[4], strRegCode, strCharacCode;
	int i = 0;
	regWinOpen = false;

	registTime ++;

	GetDlgItemText(IDC_RegCode1, str[0]);
	GetDlgItemText(IDC_RegCode2, str[1]);
	GetDlgItemText(IDC_RegCode3, str[2]);
	GetDlgItemText(IDC_RegCode4, str[3]);

	for(i=0; i<4; i++)
	{
		if(strlen(str[i]) != 8)
		{
			MessageBox("输入序列号位数不对!");
			
			if(registTime == 3)
			{
				MessageBox("输入次数超过3次");
				OnClose();
				return;
			}

			return;
		}
	}

	strRegCode = str[0] + str[1] + str[2] + str[3];
	GetDlgItemText(IDC_CharacCode, strCharacCode);

	if(strRegCode == Encrypt(strCharacCode, 0))
	{
		DeleteRegedit();
		if(WriteRegFile(InsertDays(strCharacCode, 0), 0) && WriteRegester(strCharacCode, 0))
		{
			MessageBox("永久注册成功!");
			m_regedit = true;
			OnClose();
			return;
		}
		else 
		{
			MessageBox("注册失败, 请重试!");
			return;
		}
	}

	for(i=1; i<91; i++)
	{
		if(strRegCode == Encrypt(strCharacCode, i))
		{
			DeleteRegedit();
			if(WriteRegFile(InsertDays(strCharacCode, i), i) && WriteRegester(strCharacCode, i))
			{
				CString registdays;
				registdays.Format("注册%d天成功!", i);
				MessageBox(registdays);
				leftTimeAft = i;
				m_regedit = true;
				OnClose();
				return;
			}
			else 
			{
				MessageBox("注册失败, 请重试!");
				return;
			}
		}
	}

	MessageBox("输入的序列号不正确!");

	if(registTime == 3)
	{
		MessageBox("输入次数超过3次");
		OnClose();
	}
}

void CRegisterDlg::OnCancel() 
{
	// TODO: Add your control notification handler code here
	regWinOpen = false;
	OnClose();
}


void CRegisterDlg::OnChangeRegCode1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CResizingDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();

	int length = 0;
	length = strlen(m_code1);
	if(length == 8)
	{
		GetDlgItem(IDC_RegCode2)->SetFocus();
	}
	else if(length > 8)
	{
		CString str;
		str = m_code1;
		m_code1 = str.Left(8);
		if(length >= 16)
		{
			m_code2 = str.Mid(8, 8);
			if(length >= 24)
			{
				m_code3 = str.Mid(16, 8);
				if(length >= 32)
				{
					m_code4 = str.Mid(24, 8);
					GetDlgItem(IDC_Register)->SetFocus();
				}
				else
				{
					m_code4 = str.Right(length - 24);
					GetDlgItem(IDC_RegCode4)->SetFocus();
				}
			}
			else
			{
				m_code3 = str.Right(length - 16);
				GetDlgItem(IDC_RegCode3)->SetFocus();
			}
		}
		else
		{
			m_code2 = str.Right(length - 8);
			GetDlgItem(IDC_RegCode2)->SetFocus();
		}
	}

	UpdateData(false);
}

void CRegisterDlg::OnChangeRegCode2() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CResizingDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();

	int length = 0;
	length = strlen(m_code2);
	if(length == 8)
	{
		GetDlgItem(IDC_RegCode3)->SetFocus();
	}
	else if(length > 8)
	{
		CString str;
		str = m_code2;
		m_code2 = str.Left(8);
		if(length >= 16)
		{
			m_code3 = str.Mid(8, 8);
			if(length >= 24)
			{
				m_code4 = str.Mid(16, 8);
				GetDlgItem(IDC_Register)->SetFocus();
			}
			else
			{
				m_code4 = str.Right(length - 16);
				GetDlgItem(IDC_RegCode4)->SetFocus();
			}
		}
		else
		{
			m_code3 = str.Right(length - 8);
			GetDlgItem(IDC_RegCode3)->SetFocus();
		}
	}

	UpdateData(false);
}

void CRegisterDlg::OnChangeRegCode3() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CResizingDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();

	int length = 0;
	length = strlen(m_code3);
	if(length == 8)
	{
		GetDlgItem(IDC_RegCode4)->SetFocus();
	}
	else if(length > 8)
	{
		CString str;
		str = m_code3;
		m_code3 = str.Left(8);
		if(length >= 16)
		{
			m_code4 = str.Mid(8, 8);
			GetDlgItem(IDC_Register)->SetFocus();
		}
		else
		{
			m_code4 = str.Right(length - 8);
			GetDlgItem(IDC_RegCode4)->SetFocus();
		}
	}

	UpdateData(false);
}

void CRegisterDlg::OnChangeRegCode4() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CResizingDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();

	int length = 0;
	length = strlen(m_code4);
	if(length == 8)
	{
		GetDlgItem(IDC_Register)->SetFocus();
	}
	else if(length > 8)
	{
		CString str;
		str = m_code4;
		m_code4 = str.Left(8);
		GetDlgItem(IDC_Register)->SetFocus();
	}

	UpdateData(false);
}


void CRegisterDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, 0);

	CResizingDialog::OnLButtonDown(nFlags, point);
}

void CRegisterDlg::SetDialogFace()
{
	m_register.SetBitmaps(IDB_RegisterBTNormal, IDB_RegisterBTDown,
		                IDB_RegisterBTHigh, IDB_RegisterBTDown);
	m_register.SizeToContent();

	m_cancel.SetBitmaps(IDB_RegisterCancelNormal, IDB_RegisterCancelDown,
		                IDB_RegisterCancelHigh, IDB_RegisterCancelDown);
	m_cancel.SizeToContent();
}

BOOL CRegisterDlg::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return CResizingDialog::DrawBK(pDC, IDB_RegistBK, 0);
//	return CResizingDialog::OnEraseBkgnd(pDC);
}


HBRUSH CRegisterDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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
