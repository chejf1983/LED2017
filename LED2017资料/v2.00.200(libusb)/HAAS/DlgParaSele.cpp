// DlgParaSele.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "DlgParaSele.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgParaSele dialog


CDlgParaSele::CDlgParaSele(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgParaSele::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgParaSele)
	m_iName = -1;
	//}}AFX_DATA_INIT
}


void CDlgParaSele::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgParaSele)
	DDX_Control(pDX, IDC_COMBO_NAME, m_cName);
	DDX_CBIndex(pDX, IDC_COMBO_NAME, m_iName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgParaSele, CDialog)
	//{{AFX_MSG_MAP(CDlgParaSele)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgParaSele message handlers

BOOL CDlgParaSele::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_cName.ResetContent();

	int iN=m_arraName.GetSize();
	for(int i=0;i<iN;i++)
		m_cName.InsertString(i,m_arraName[i]);
	m_iName=0;
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
