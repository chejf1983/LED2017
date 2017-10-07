// DlgSelfPhK.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "DlgSelfPhK.h"
#include "Global_MySpec.h"
#include "DlgSelfKEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSelfPhK dialog


CDlgSelfPhK::CDlgSelfPhK(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSelfPhK::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSelfPhK)
	m_fSelfPhK = 1.0f;
	m_iType = 0;
	//}}AFX_DATA_INIT
}


void CDlgSelfPhK::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSelfPhK)
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_cSave);
	DDX_Control(pDX, IDC_BUTTON_SELE, m_cSele);
	DDX_Control(pDX, IDC_EDIT_SELF_PH_K, m_cSelfPhK);
	DDX_Control(pDX, IDC_EDIT_PH2, m_cPh2);
	DDX_Control(pDX, IDC_EDIT_PH1, m_cPh1);
	DDX_Control(pDX, IDC_EDIT_PH_K, m_cPhK);
	DDX_Text(pDX, IDC_EDIT_SELF_PH_K, m_fSelfPhK);
	DDX_CBIndex(pDX, IDC_COMBO_TYPE, m_iType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSelfPhK, CDialog)
	//{{AFX_MSG_MAP(CDlgSelfPhK)
	ON_BN_CLICKED(IDC_BUTTON_TEST1, OnButtonTest1)
	ON_BN_CLICKED(IDC_BUTTON_TEST2, OnButtonTest2)
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE, OnSelchangeComboType)
	ON_BN_CLICKED(IDC_BUTTON_SELE, OnButtonSele)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSelfPhK message handlers

BOOL CDlgSelfPhK::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	UpdateData(false);
	OnSelchangeComboType();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSelfPhK::OnOK() 
{
	// TODO: Add extra validation here
	if(UpdateData(TRUE)==FALSE)
		return;
	
	if(m_iType == 0 || m_iType == 1)
		m_fSelfPhK = 1.0f;

	UpdateData(FALSE);



	CDialog::OnOK();
}

void CDlgSelfPhK::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CDlgSelfPhK::OnButtonTest1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	float fPh;
	if(GetPh(fPh)==FALSE)
		return;
	CString strTemp;
	strTemp=g_SPEC.sFormat(fPh,5);
	m_cPh1.SetWindowText(strTemp);

	g_SPEC.m_selfCorrectData.m_iSaveRefNum = m_spData.m_fRelSpect.GetSize();
	for(int i = 0; i < g_SPEC.m_selfCorrectData.m_iSaveRefNum; i++)
	{
		g_SPEC.m_selfCorrectData.m_fSave_RefWL[i] = m_spData.m_fSpect1 + m_spData.m_fInterval * i;
		g_SPEC.m_selfCorrectData.m_fSave_RefPL[i] = m_spData.m_fRelSpect[i] * m_spData.m_fPlambda;
	}

	CalcPhK();
}

void CDlgSelfPhK::OnButtonTest2() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	float fPh;
	if(GetPh(fPh)==FALSE)
		return;
	CString strTemp;
	strTemp=g_SPEC.sFormat(fPh,5);
	m_cPh2.SetWindowText(strTemp);	

	g_SPEC.m_selfCorrectData.m_iSaveTestNum = m_spData.m_fRelSpect.GetSize();
	for(int i = 0; i < g_SPEC.m_selfCorrectData.m_iSaveRefNum; i++)
	{
		g_SPEC.m_selfCorrectData.m_fSave_TestWL[i] = m_spData.m_fSpect1 + m_spData.m_fInterval * i;
		g_SPEC.m_selfCorrectData.m_fSave_TestPL[i] = m_spData.m_fRelSpect[i] * m_spData.m_fPlambda;
	}

	CalcPhK();
}

BOOL CDlgSelfPhK::GetPh(float &fPh)
{
	CCmdTarget::BeginWaitCursor();
	UpdateData(TRUE);
	static float fIntTime = 100;

	float fMax;
	BOOL bR;
	bR=g_SPEC.Get_PL();
	if(!bR)
		return FALSE;

	CCmdTarget::BeginWaitCursor();
	bR = g_SPEC.SPEC_GetAutoTime(fIntTime,10000,0.3f,fIntTime);
	CCmdTarget::EndWaitCursor();
	if(!bR)
		return FALSE;

	CCmdTarget::BeginWaitCursor();
	bR = g_SPEC.SPEC_DoScan(fIntTime,1,MY_TRIG_NORMAL,fMax,TRUE,m_spData.m_iDataType);
	CCmdTarget::EndWaitCursor();
	if(!bR)
	{
		if(g_bEnglish)
			MessageBox("SPEC_DoScan Sample fail!",NULL,MB_ICONSTOP);
		else
			MessageBox("SPEC_DoScan 采样失败!",NULL,MB_ICONSTOP);
		return FALSE;
	}
	
	g_SPEC.SPEC_GetSpectData(TRUE,m_spData);

	fPh = m_spData.m_fPh;

	return TRUE;
}

void CDlgSelfPhK::CalcPhK()
{
	CString strTemp;
	
	m_cPh1.GetWindowText(strTemp);
	float fPh1;
	fPh1=(float)atof(strTemp);

	m_cPh2.GetWindowText(strTemp);
	float fPh2;
	fPh2=(float)atof(strTemp);

	if(fPh1!=0&&fPh2!=0)
	{
		m_fSelfPhK=fPh1/fPh2;
		strTemp.Format("%.4f",fPh1/fPh2);
		m_cPhK.SetWindowText(strTemp);

		if(m_iType == 2)
			m_cSelfPhK.SetWindowText(strTemp);
	}
	else
		m_cPhK.SetWindowText("");
}

void CDlgSelfPhK::OnSelchangeComboType() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	GetDlgItem(IDC_EDIT_SELF_PH_K)->EnableWindow(m_iType == 2);
	GetDlgItem(IDC_EDIT_PH_K)->EnableWindow(m_iType == 2);
	GetDlgItem(IDC_BUTTON_SELE)->EnableWindow(m_iType != 0);
	GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(m_iType != 0);

}

void CDlgSelfPhK::OnButtonSele() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if(m_iType == 1)
	{
		CString sPathName;
		static char szFilter[]="Self files(*.slf)|*.slf||";
		CFileDialog dOpen(TRUE,".slf",g_strCurPath+"cal\\*.slf",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter,NULL);
		if(dOpen.DoModal()==IDCANCEL)
			return;
		g_SPEC.m_selfCorrectData.Open(dOpen.GetPathName());
	}

	if(m_iType == 2)
	{
		CDlgSelfKEdit dlg;
		if(dlg.DoModal() == IDCANCEL)
			return;

		m_fSelfPhK = dlg.m_fK;
	}

	UpdateData(FALSE);
}

void CDlgSelfPhK::OnButtonSave() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString strTemp;

	if(m_iType == 1)
	{
		CString sPathName;
		static char szFilter[]="Self files(*.slf)|*.slf||";
		CFileDialog dOpen(FALSE,".slf",g_strCurPath+"cal\\*.slf",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter,NULL);
		if(dOpen.DoModal()==IDCANCEL)
			return;
		g_SPEC.m_selfCorrectData.Save(dOpen.GetPathName());
	}

	if(m_iType == 2)
	{
		m_cPhK.GetWindowText(strTemp);
		if(strTemp == "")
			return;

		CDlgSelfKEdit dlg;
		dlg.Load();
		dlg.m_fListK.Add((float)atof(strTemp));
		dlg.m_strListName.Add(_T("NewAdd"));
		dlg.Save();

		if(!g_bEnglish)
			AfxMessageBox("已增加自吸收数据!");
	}
}
