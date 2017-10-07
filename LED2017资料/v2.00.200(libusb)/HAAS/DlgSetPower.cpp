// DlgSetPower.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "DlgSetPower.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSetPower dialog

#define  WM_SET_CLOSE  WM_USER+0X4000


CDlgSetPower::CDlgSetPower(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSetPower::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSetPower)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgSetPower::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSetPower)
	DDX_Control(pDX, IDCANCEL, m_cCancel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSetPower, CDialog)
	//{{AFX_MSG_MAP(CDlgSetPower)
	ON_MESSAGE(WM_SET_CLOSE,OnSetClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSetPower message handlers

void CDlgSetPower::OnCancel() 
{
	// TODO: Add extra cleanup here
	pDlg->m_bCancel=TRUE;
	m_cCancel.EnableWindow(FALSE);	
//	CDialog::OnCancel();
}

afx_msg void CDlgSetPower::OnSetClose(UINT wParam, LONG lParam)
{
	CDialog::OnCancel();
}

UINT ThreadSetPower(LPVOID pParam)
{
    CDlgSetPower *pDlg=(CDlgSetPower*)pParam;
	pDlg->pDlg->m_bCancel=FALSE;
	pDlg->m_iR=pDlg->pDlg->WY_SetPower(pDlg->pDlg->m_strCom,pDlg->pDlg->m_iTypeWY,pDlg->pDlg->m_strAddr,pDlg->pDlg->m_iSeleUI,pDlg->pDlg->m_fSetVol,pDlg->pDlg->m_fSetCurr,pDlg->m_fVol,pDlg->m_fCurr,pDlg->m_strVol,pDlg->m_strCurr);
	if(pDlg->m_iR==2)
		pDlg->pDlg->WY_Reset(pDlg->pDlg->m_strCom,pDlg->pDlg->m_iTypeWY,pDlg->pDlg->m_strAddr);
	::PostMessage(pDlg->m_hWnd,WM_SET_CLOSE,0,0);
	return 0;
}

BOOL CDlgSetPower::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	Thread=AfxBeginThread(ThreadSetPower,this);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
