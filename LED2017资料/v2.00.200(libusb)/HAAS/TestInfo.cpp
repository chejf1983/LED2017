// TestInfo.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "TestInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestInfo dialog


CTestInfo::CTestInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CTestInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestInfo)
	m_strDate = _T("");
	m_strFactory = _T("");
	m_strH = _T("");
	m_strModel = _T("");
	m_strNumber = _T("");
	m_strRemark = _T("");
	m_strT = _T("");
	m_strTester = _T("");
	m_strName = _T("");
	m_strStandard = _T("");
	m_strState = _T("");
	//}}AFX_DATA_INIT
}


void CTestInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestInfo)
	DDX_Text(pDX, IDC_EDIT_DATE, m_strDate);
	DDX_Text(pDX, IDC_EDIT_FACTORY, m_strFactory);
	DDX_Text(pDX, IDC_EDIT_H, m_strH);
	DDX_Text(pDX, IDC_EDIT_MODEL, m_strModel);
	DDX_Text(pDX, IDC_EDIT_NUMBER, m_strNumber);
	DDX_Text(pDX, IDC_EDIT_REMARK, m_strRemark);
	DDX_Text(pDX, IDC_EDIT_T, m_strT);
	DDX_Text(pDX, IDC_EDIT_TESTER, m_strTester);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Text(pDX, IDC_EDIT_STANDARD, m_strStandard);
	DDX_Text(pDX, IDC_EDIT_STATE, m_strState);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestInfo, CDialog)
	//{{AFX_MSG_MAP(CTestInfo)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestInfo message handlers
