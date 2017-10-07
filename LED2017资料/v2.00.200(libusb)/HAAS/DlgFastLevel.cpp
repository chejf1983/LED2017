// DlgFastLevel.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "DlgFastLevel.h"
#include "Global_MySpec.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgFastLevel dialog

CDlgFastLevel::CDlgFastLevel(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFastLevel::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgFastLevel)
	m_iN = 10;
	m_strName = _T("");
	m_fData1 = 0.0f;
	m_fData2 = 0.0f;
	//}}AFX_DATA_INIT

	for(int i=0;i<10;i++)
	{
		m_fLevel1[i]=0;
		m_fLevel2[i]=0;
	}
}

void CDlgFastLevel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFastLevel)
	DDX_Control(pDX, IDC_EDIT_N, m_cN);
	DDX_Control(pDX, IDC_STATIC_S2, m_cS2);
	DDX_Control(pDX, IDC_STATIC_S1, m_cS1);
	DDX_Control(pDX, IDC_LIST, m_cList);
	DDX_Text(pDX, IDC_EDIT_N, m_iN);
	DDV_MinMaxInt(pDX, m_iN, 1, 10);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Text(pDX, IDC_EDIT_DATA1, m_fData1);
	DDX_Text(pDX, IDC_EDIT_DATA2, m_fData2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgFastLevel, CDialog)
	//{{AFX_MSG_MAP(CDlgFastLevel)
	ON_EN_CHANGE(IDC_EDIT_N, OnChangeEditN)
	ON_BN_CLICKED(IDC_BUTTON_MOD, OnButtonMod)
	ON_LBN_SELCHANGE(IDC_LIST, OnSelchangeList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgFastLevel message handlers


BOOL CDlgFastLevel::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here	
	UpdateData(TRUE);
	CString strTemp;

	m_iCur=0;
	UpdateData(FALSE);
	Insert();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgFastLevel::OnChangeEditN() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	Insert();
}

void CDlgFastLevel::Insert()
{
	CString strTemp;
	m_cN.GetWindowText(strTemp);
	m_iN=atoi(strTemp);
	if(m_iN>10)
		m_iN=10;

	CString sTemp[10];
	m_cList.ResetContent();
	for(int i=0;i<m_iN;i++)
	{
		if(g_bEnglish)
			strTemp.Format("Level %d:",i);
		else
			strTemp.Format(" 第%2d 级",i);
		m_cList.InsertString(i,strTemp);
		m_cList.SetCurSel(m_iN-1);
	}
	OnSelchangeList();
	UpdateData(FALSE);
}

void CDlgFastLevel::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CDlgFastLevel::OnButtonSavedata() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlgFastLevel::OnButtonMod() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	m_fLevel1[m_iCur]=m_fData1;
	m_fLevel2[m_iCur]=m_fData2;

/*	if(m_iCur<(m_iN-1)&&m_iCur>0)
	{
		m_fLevel1[m_iCur+1]=m_fLevel2[m_iCur];
		m_fLevel2[m_iCur-1]=m_fLevel1[m_iCur];
	}
*/
	UpdateData(FALSE);
}

void CDlgFastLevel::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CDlgFastLevel::OnSelchangeList() 
{
	// TODO: Add your control notification handler code here
	m_iCur=m_cList.GetCurSel();
	if(m_iCur<0)
		return;

	m_fData1=m_fLevel1[m_iCur];
	m_fData2=m_fLevel2[m_iCur];
	CString sTemp;
	if(g_bEnglish)
		sTemp.Format("Level%d Min:",m_iCur);
	else
		sTemp.Format("第%d级最小:",m_iCur);
	m_cS1.SetWindowText(sTemp);

	if(g_bEnglish)
		sTemp.Format("Level%d Max:",m_iCur);
	else
		sTemp.Format("第%d级最大:",m_iCur);
	m_cS2.SetWindowText(sTemp);
	UpdateData(FALSE);
}
