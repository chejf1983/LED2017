// DlgInputPower.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "DlgInputPower.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgInputPower dialog
extern BOOL    g_bManuP;


CDlgInputPower::CDlgInputPower(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInputPower::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgInputPower)
	m_fI = 0.0f;
	m_fP = 0.0f;
	m_fPF = 0.0f;
	m_fU = 0.0f;
	//}}AFX_DATA_INIT
}


void CDlgInputPower::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgInputPower)
	DDX_Text(pDX, IDC_EDIT_I, m_fI);
	DDX_Text(pDX, IDC_EDIT_P, m_fP);
	DDX_Text(pDX, IDC_EDIT_PF, m_fPF);
	DDX_Text(pDX, IDC_EDIT_U, m_fU);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgInputPower, CDialog)
	//{{AFX_MSG_MAP(CDlgInputPower)
	ON_EN_CHANGE(IDC_EDIT_U, OnChangeEditU)
	ON_EN_CHANGE(IDC_EDIT_I, OnChangeEditI)
	ON_EN_CHANGE(IDC_EDIT_PF, OnChangeEditPf)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_EN_KILLFOCUS(IDC_EDIT_PF, OnKillfocusEditPf)
	ON_EN_KILLFOCUS(IDC_EDIT_P, OnKillfocusEditP)
	ON_EN_KILLFOCUS(IDC_EDIT_U, OnKillfocusEditU)
	ON_EN_KILLFOCUS(IDC_EDIT_I, OnKillfocusEditI)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgInputPower message handlers

void CDlgInputPower::OnChangeEditU() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
}

void CDlgInputPower::OnChangeEditI() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
}

void CDlgInputPower::OnChangeEditPf() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
}

void CDlgInputPower::OnOK() 
{
	// TODO: Add extra validation here
	if(g_bManuP)
	{
		UpdateData(TRUE);
		m_fP = m_fI * m_fU * m_fPF;
		UpdateData(FALSE);
	}
}

void CDlgInputPower::OnButton1() 
{
	// TODO: Add your control notification handler code here
	if(UpdateData(TRUE) == FALSE)
		return;

	if((m_fP - 0.0001f) > (m_fU * m_fI))
	{
		if(g_bEnglish)
			AfxMessageBox("Input error!");
		else
			AfxMessageBox("输入电参数有误!");
		return;
	}

	if(m_fU > 0 && m_fI > 0 && m_fP > 0)
	{

	}

	CDialog::OnOK();
}

void CDlgInputPower::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CDlgInputPower::OnKillfocusEditPf() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_fP = m_fU * m_fI * m_fPF;
	UpdateData(FALSE);
}

void CDlgInputPower::OnKillfocusEditP() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_fU > 0 && m_fI > 0)
		m_fPF = m_fP / (m_fU * m_fI);
	UpdateData(FALSE);
}

void CDlgInputPower::OnKillfocusEditU() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_fP = m_fU * m_fI * m_fPF;
	UpdateData(FALSE);	
}

void CDlgInputPower::OnKillfocusEditI() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_fP = m_fU * m_fI * m_fPF;
	UpdateData(FALSE);	
}
