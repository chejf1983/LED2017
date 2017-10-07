// DlgSelePara.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "DlgSelePara.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSelePara dialog


CDlgSelePara::CDlgSelePara(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSelePara::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSelePara)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_iPara=PARA_x;
	m_refC=RGB(255,255,0);
}


void CDlgSelePara::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSelePara)
	DDX_Control(pDX, IDC_LIST, m_cList);
	DDX_Control(pDX, IDC_C, m_cC);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSelePara, CDialog)
	//{{AFX_MSG_MAP(CDlgSelePara)
	ON_BN_CLICKED(IDC_C, OnC)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSelePara message handlers

BOOL CDlgSelePara::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_iN=0;

	m_iList[m_iN]=PARA_None;
	m_iN++;
	m_iList[m_iN]=PARA_VF;
	m_iN++;
	m_iList[m_iN]=PARA_IF;
	m_iN++;
	m_iList[m_iN]=PARA_P;
	m_iN++;
	m_iList[m_iN]=PARA_VR;
	m_iN++;
	m_iList[m_iN]=PARA_IR;
	m_iN++;
	m_iList[m_iN]=PARA_Ip;
	m_iN++;
	m_iList[m_iN]=PARA_PH;
	m_iN++;
	m_iList[m_iN]=PARA_EFF;
	m_iN++;
	m_iList[m_iN]=PARA_x;
	m_iN++;
	m_iList[m_iN]=PARA_y;
	m_iN++;
	m_iList[m_iN]=PARA_u;
	m_iN++;
	m_iList[m_iN]=PARA_v;
	m_iN++;
	m_iList[m_iN]=PARA_Tc;
	m_iN++;
	m_iList[m_iN]=PARA_Ld;
	m_iN++;
	m_iList[m_iN]=PARA_Pur;
	m_iN++;
	m_iList[m_iN]=PARA_Lp;
	m_iN++;
	m_iList[m_iN]=PARA_HW;
	m_iN++;
	m_iList[m_iN]=PARA_RR;
	m_iN++;
	m_iList[m_iN]=PARA_Ra;
	m_iN++;

	CString strTemp;
	for(int i=0;i<m_iN;i++)
	{
		if(m_iList[i]==PARA_None)
			strTemp="NONE";
		strTemp=CSpectData::DATA_Name(m_iList[i],0);
		m_cList.InsertString(i,"   "+strTemp);

		if(m_iList[i]==m_iPara)
			m_cList.SetCurSel(i);
	}
	m_cC.DrawC(m_refC);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSelePara::OnOK() 
{
	// TODO: Add extra validation here
	int iSele=m_cList.GetCurSel();
	if(iSele>=0&&iSele<m_iN)
		m_iPara=m_iList[iSele];
	CDialog::OnOK();
}

void CDlgSelePara::OnC() 
{
	// TODO: Add your control notification handler code here
	CColorDialog dC(m_refC);
	if(dC.DoModal()==IDOK)
	{
		m_refC=dC.GetColor();
		m_cC.DrawC(m_refC);
	}				
}
