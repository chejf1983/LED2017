// DlgControlKEY.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "DlgControlKEY.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgControlKEY dialog


CDlgControlKEY::CDlgControlKEY(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgControlKEY::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgControlKEY)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgControlKEY::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgControlKEY)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgControlKEY, CDialog)
	//{{AFX_MSG_MAP(CDlgControlKEY)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgControlKEY message handlers
