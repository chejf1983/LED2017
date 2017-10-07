// DlgSeleCT.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "DlgSeleCT.h"
#include "SDCM.h"
#include <afxtempl.h>
#include "ProcessData.h"
#include "Global_MySpec.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSeleCT dialog

CDlgSeleCT::CDlgSeleCT(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSeleCT::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSeleCT)
	m_iSDCM1 = 5;
	m_iSDCM2 = 6;
	//}}AFX_DATA_INIT

}


void CDlgSeleCT::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSeleCT)
	DDX_Control(pDX, IDC_LIST, m_cList);
	DDX_Text(pDX, IDC_EDIT_SDCM1, m_iSDCM1);
	DDV_MinMaxInt(pDX, m_iSDCM1, 1, 7);
	DDX_Text(pDX, IDC_EDIT_SDCM2, m_iSDCM2);
	DDV_MinMaxInt(pDX, m_iSDCM2, 1, 7);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSeleCT, CDialog)
	//{{AFX_MSG_MAP(CDlgSeleCT)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN5, OnDeltaposSpin5)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, OnDeltaposSpin1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSeleCT message handlers

BOOL CDlgSeleCT::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	int iSaveSele = m_iSele;
	
	m_iN = g_doData.m_sdcm.GetSize();

	for(int i = 0; i < m_iN; i++)
	{
		m_cList.InsertString(i,g_doData.m_sdcm.GetAt(i)->m_strName);
	}

	m_cList.InsertString(i,"Auto");

	m_iSele=iSaveSele;

	m_cList.SetCurSel(m_iSele);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSeleCT::OnOK() 
{
	// TODO: Add extra validation here
	if(UpdateData(TRUE)==FALSE)
		return;

	m_iSele=m_cList.GetCurSel();

	CDialog::OnOK();
}

void CDlgSeleCT::OnDeltaposSpin5(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(pNMUpDown->iDelta>0)
	{
		m_iSDCM2=m_iSDCM2-1;
		if(m_iSDCM2<=1)
			m_iSDCM2=1;
	}
	else
	{
		m_iSDCM2=m_iSDCM2+1;
		if(m_iSDCM2>=7)
			m_iSDCM2=7;
	}
	UpdateData(FALSE);		
	*pResult = 0;
}

void CDlgSeleCT::OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(pNMUpDown->iDelta>0)
	{
		m_iSDCM1=m_iSDCM1-1;
		if(m_iSDCM1<=1)
			m_iSDCM1=1;
	}
	else
	{
		m_iSDCM1=m_iSDCM1+1;
		if(m_iSDCM1>=7)
			m_iSDCM1=7;
	}
	UpdateData(FALSE);		
	*pResult = 0;
}
