// Setup4.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "Setup4.h"
#include "Global_MySpec.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetup4 property page

IMPLEMENT_DYNCREATE(CSetup4, CPropertyPage)

CSetup4::CSetup4() : CPropertyPage(CSetup4::IDD)
{
	//{{AFX_DATA_INIT(CSetup4)
	m_iNum = 10;
	m_iT = 5;
	m_bCheckTimeTest = FALSE;
	m_bSame = FALSE;
	//}}AFX_DATA_INIT
}

CSetup4::~CSetup4()
{
}

void CSetup4::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetup4)
	DDX_Control(pDX, IDC_LIST, m_cList);
	DDX_Control(pDX, IDC_BUTTON_SET_OK, m_cSetOk);
	DDX_Control(pDX, IDC_BUTTON_SET, m_cSet);
	DDX_Text(pDX, IDC_EDIT_NUM, m_iNum);
	DDX_Text(pDX, IDC_EDIT_T, m_iT);
	DDX_Check(pDX, IDC_CHECK_TIME_TEST, m_bCheckTimeTest);
	DDX_Check(pDX, IDC_CHECK1, m_bSame);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetup4, CPropertyPage)
	//{{AFX_MSG_MAP(CSetup4)
	ON_BN_CLICKED(IDC_BUTTON_SET_OK, OnButtonSetOk)
	ON_BN_CLICKED(IDC_BUTTON_SET, OnButtonSet)
	ON_NOTIFY(NM_CLICK, IDC_LIST, OnClickList)
	ON_EN_CHANGE(IDC_EDIT_NUM, OnChangeEditNum)
	ON_EN_CHANGE(IDC_EDIT_T, OnChangeEditT)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetup4 message handlers

BOOL CSetup4::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_cList.ModifyStyle(0,LVS_REPORT|LVS_SINGLESEL|LVS_SHOWSELALWAYS);
	m_cList.SetExtendedStyle(m_cList.GetExtendedStyle()  | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	
	m_iCur=0;
	if(g_bEnglish)
		m_cList.InsertColumn(0,"Number");
	else
		m_cList.InsertColumn(0,"第几次");
	m_cList.SetColumnWidth(0,60);

	if(g_bEnglish)
		m_cList.InsertColumn(1,"time after on(min)");
	else
		m_cList.InsertColumn(1,"点亮后(分)");
	m_cList.SetColumnWidth(1,80);

	m_iNum=g_SPEC.m_arra_iTimeNum.GetSize();
	if(m_iNum>0)
		m_iT=g_SPEC.m_arra_iTimeNum[0];
	else
		m_iT=5;
	ReList();
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSetup4::OnButtonSetOk() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	int iNum=g_SPEC.m_arra_iTimeNum.GetSize();
	if(m_iNum>iNum)
	{
		for(int i=0;i<(m_iNum-iNum);i++)
			g_SPEC.m_arra_iTimeNum.Add(m_iT);
	}
	if(m_iNum<iNum)
	{
		for(int i=0;i<(iNum-m_iNum);i++)
			g_SPEC.m_arra_iTimeNum.RemoveAt(iNum-1-i);
	}
	ReList();
	
	m_cSet.EnableWindow(FALSE);
}

void CSetup4::OnButtonSet() 
{
	// TODO: Add your control notification handler code here
	if(UpdateData(TRUE)==FALSE)
		return;

	if (m_bSame)
	{
		int iNum=g_SPEC.m_arra_iTimeNum.GetSize();
		if(iNum>=1)
		{
			g_SPEC.m_arra_iTimeNum[0] = 0;
			for (int i = 1; i < iNum; i++)
			{
				g_SPEC.m_arra_iTimeNum[i]=g_SPEC.m_arra_iTimeNum[i - 1] + m_iT;
			}
		}
	}
	else
	{
		int iNum=g_SPEC.m_arra_iTimeNum.GetSize();
		if(iNum>=1)
		{
			if(m_iCur>iNum-1)
				m_iCur=iNum-1;
			if(m_iCur<0)
				m_iCur=0;
			g_SPEC.m_arra_iTimeNum[m_iCur]=m_iT;
		}
	}
	ReList();

	m_cSetOk.EnableWindow(FALSE);
}

void CSetup4::ReList()
{
	m_cList.DeleteAllItems();

	CString strTemp;
	int iNum=g_SPEC.m_arra_iTimeNum.GetSize();
	for(int i=0;i<iNum;i++)
	{
		strTemp.Format(" %2d",i+1);
		m_cList.InsertItem(i,strTemp);

		strTemp.Format(" %3d",g_SPEC.m_arra_iTimeNum[i]);
		m_cList.SetItemText(i,1,strTemp);
	}
}

void CSetup4::OnClickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	int iNum=g_SPEC.m_arra_iTimeNum.GetSize();
	if(iNum>=1)
	{
		if(pNMListView->iItem>iNum-1)
			pNMListView->iItem=iNum-1;
		if(pNMListView->iItem<0)
			pNMListView->iItem=0;
		m_iT=g_SPEC.m_arra_iTimeNum[pNMListView->iItem];
	}
	m_iCur=pNMListView->iItem;

	UpdateData(FALSE);

	*pResult = 0;
}

void CSetup4::OnChangeEditNum() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	m_cSetOk.EnableWindow(TRUE);
}

void CSetup4::OnChangeEditT() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	m_cSet.EnableWindow(TRUE);
}
