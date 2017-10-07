// DlgSetHaas.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "DlgSetHaas.h"
#include "Global_MySpec.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSetHaas dialog


CDlgSetHaas::CDlgSetHaas(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSetHaas::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSetHaas)
	m_iBin  = -1;
	m_iMode = -1;
	//}}AFX_DATA_INIT
	CString strSection   = "SET_HAAS_TR";
	
	CString strBIN		 = "BIN";
	CString strMODE      = "MODE";

	m_iBin	= AfxGetApp()->GetProfileInt(strSection,strBIN,0);
	m_iMode	= AfxGetApp()->GetProfileInt(strSection,strMODE,0);
}


void CDlgSetHaas::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSetHaas)
	DDX_Control(pDX, IDC_COMBO_MODE, m_cMode);
	DDX_Control(pDX, IDC_COMBO_BIN, m_cBin);
	DDX_CBIndex(pDX, IDC_COMBO_BIN, m_iBin);
	DDX_CBIndex(pDX, IDC_COMBO_MODE, m_iMode);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSetHaas, CDialog)
	//{{AFX_MSG_MAP(CDlgSetHaas)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSetHaas message handlers

BOOL CDlgSetHaas::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//
	m_cBin.ResetContent();
	if(g_bEnglish)
	{
		if(g_SPEC.m_Have_iBin==1)
		{
			m_cBin.InsertString(0,"01(High)");
		}
		if(g_SPEC.m_Have_iBin==2)
		{
			m_cBin.InsertString(0,"01(High)");
			m_cBin.InsertString(1,"02(Low)");
		}
		if(g_SPEC.m_Have_iBin==3)
		{
			m_cBin.InsertString(0,"01(High)");
			m_cBin.InsertString(1,"02");
			m_cBin.InsertString(2,"03(Low)");
		}
		if(g_SPEC.m_Have_iBin==4)
		{
			m_cBin.InsertString(0,"01(High)");
			m_cBin.InsertString(1,"02");
			m_cBin.InsertString(2,"03");
			m_cBin.InsertString(2,"04(Low)");
		}
	}
	else
	{
		CString strTemp;
		for(int i=0;i<g_SPEC.m_Have_iBin;i++)
		{
			strTemp.Format("%02d",i+1);
			if(i==0)
				m_cBin.InsertString(i,strTemp+"(ธ฿)");
			else if(i==(g_SPEC.m_Have_iBin-1))
				m_cBin.InsertString(i,strTemp+"(ตอ)");
			else
				m_cBin.InsertString(i,strTemp);
		}
	}
	m_iBin=g_SPEC.m_iBin;
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
