// DlgRS232RemoteComm.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "DlgRS232RemoteComm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRS232RemoteComm dialog


CDlgRS232RemoteComm::CDlgRS232RemoteComm(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRS232RemoteComm::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRS232RemoteComm)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgRS232RemoteComm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRS232RemoteComm)
	DDX_Control(pDX, IDCANCEL, m_cExit);
	DDX_Control(pDX, IDC_BUTTON_STOP, m_cStop);
	DDX_Control(pDX, IDC_BUTTON_START, m_cStart);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRS232RemoteComm, CDialog)
	//{{AFX_MSG_MAP(CDlgRS232RemoteComm)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRS232RemoteComm message handlers
