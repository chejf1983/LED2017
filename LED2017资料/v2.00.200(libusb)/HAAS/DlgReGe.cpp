// DlgReGe.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "DlgReGe.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgReGe dialog


CDlgReGe::CDlgReGe(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgReGe::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgReGe)
	m_fGeWL1 = 380.0f;
	m_fGeWL2 = 780.0f;
	//}}AFX_DATA_INIT
}


void CDlgReGe::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgReGe)
	DDX_Text(pDX, IDC_EDIT1, m_fGeWL1);
	DDX_Text(pDX, IDC_EDIT2, m_fGeWL2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgReGe, CDialog)
	//{{AFX_MSG_MAP(CDlgReGe)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgReGe message handlers
