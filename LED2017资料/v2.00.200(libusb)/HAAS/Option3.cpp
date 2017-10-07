// Option3.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "Option3.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COption3 property page
extern COLORREF g_ErrTextColor, g_ErrBkColor;

IMPLEMENT_DYNCREATE(COption3, CPropertyPage)

COption3::COption3() : CPropertyPage(COption3::IDD)
{
	//{{AFX_DATA_INIT(COption3)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

COption3::~COption3()
{
}

void COption3::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COption3)
	DDX_Control(pDX, IDC_STATIC_BK, m_cBK);
	DDX_Control(pDX, IDC_STATIC_TEXT, m_cText);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COption3, CPropertyPage)
	//{{AFX_MSG_MAP(COption3)
	ON_BN_CLICKED(IDC_BUTTON_SELE_TEXT, OnButtonSeleText)
	ON_BN_CLICKED(IDC_BUTTON_SELE_BK, OnButtonSeleBk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COption3 message handlers

void COption3::OnButtonSeleText() 
{
	// TODO: Add your control notification handler code here
	CColorDialog ColorDialogI(g_ErrTextColor);
	if(ColorDialogI.DoModal()==IDOK)
	{
		g_ErrTextColor=ColorDialogI.GetColor();

		m_cText.DrawBk(g_ErrTextColor);
	}
}

void COption3::OnButtonSeleBk() 
{
	// TODO: Add your control notification handler code here
	CColorDialog ColorDialogI(g_ErrBkColor);
	if(ColorDialogI.DoModal()==IDOK)
	{
		g_ErrBkColor=ColorDialogI.GetColor();

		m_cBK.DrawBk(g_ErrBkColor);
	}
}

BOOL COption3::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here

	m_cText.DrawBk(g_ErrTextColor);
	m_cBK.DrawBk(g_ErrBkColor);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
