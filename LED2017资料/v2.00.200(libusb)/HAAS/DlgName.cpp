// DlgName.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "DlgName.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgName dialog


CDlgName::CDlgName(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgName::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgName)
	m_strName = _T("NEW");
	//}}AFX_DATA_INIT
}


void CDlgName::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgName)
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDV_MaxChars(pDX, m_strName, 14);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgName, CDialog)
	//{{AFX_MSG_MAP(CDlgName)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgName message handlers
