// DlgLEDClassSetPara.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "DlgLEDClassSetPara.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLEDClassSetPara dialog


CDlgLEDClassSetPara::CDlgLEDClassSetPara(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLEDClassSetPara::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLEDClassSetPara)
	m_iType = 0;
	//}}AFX_DATA_INIT
	m_pClassData = NULL;
}


void CDlgLEDClassSetPara::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLEDClassSetPara)
	DDX_Control(pDX, IDC_LIST, m_cList);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_cType);
	DDX_CBIndex(pDX, IDC_COMBO_TYPE, m_iType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLEDClassSetPara, CDialog)
	//{{AFX_MSG_MAP(CDlgLEDClassSetPara)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DEL, OnButtonDel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLEDClassSetPara message handlers

void CDlgLEDClassSetPara::OnButtonAdd() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	m_pClassData->Add_DataType(m_iListType[m_iType]);
	m_pClassData->ListDataPara(m_cList);
}

void CDlgLEDClassSetPara::OnButtonDel() 
{
	// TODO: Add your control notification handler code here
	int iSele = m_cList.GetCurSel();
	if(iSele < 0)
		return;

	m_pClassData->Del_DataType(iSele);
	m_pClassData->ListDataPara(m_cList);
}

BOOL CDlgLEDClassSetPara::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_pClassData->ListDataPara(m_cList);


	CLimitData::GetName(m_strListName,m_iListType);

	m_cType.ResetContent();
	for(int i = 0; i < m_strListName.GetSize(); i++)
		m_cType.AddString(m_strListName[i]);
	m_cType.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgLEDClassSetPara::OnCancel() 
{
	// TODO: Add extra cleanup here
	UpdateData(TRUE);

	CDialog::OnCancel();
}
