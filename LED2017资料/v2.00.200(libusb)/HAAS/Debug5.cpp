// Debug5.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "Debug5.h"
#include "Global_MySpec.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDebug5 property page

IMPLEMENT_DYNCREATE(CDebug5, CPropertyPage)

CDebug5::CDebug5() : CPropertyPage(CDebug5::IDD)
{
	//{{AFX_DATA_INIT(CDebug5)
	m_iRange = 0;
	m_fZero1 = 0.0f;
	m_fZero2 = 0.0f;
	m_fZero3 = 0.0f;
	m_fZero4 = 0.0f;
	m_fZero = 0.0f;
	m_bConSample = FALSE;
	m_fI1 = 0.0f;
	m_fI2 = 0.0f;
	m_fI3 = 0.0f;
	m_fI4 = 0.0f;
	m_fAD1 = 0.0f;
	m_fAD2 = 0.0f;
	m_fAD3 = 0.0f;
	m_fAD4 = 0.0f;
	m_strNumber = _T("");
	//}}AFX_DATA_INIT
}

CDebug5::~CDebug5()
{
}

void CDebug5::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDebug5)
	DDX_Control(pDX, IDC_EDIT_K3, m_cK3);
	DDX_Control(pDX, IDC_EDIT_K2, m_cK2);
	DDX_Control(pDX, IDC_EDIT_K1, m_cK1);
	DDX_Control(pDX, IDC_EDIT_AD1, m_cAD);
	DDX_CBIndex(pDX, IDC_COMBO_RANGE, m_iRange);
	DDX_Text(pDX, IDC_EDIT_ZERO1, m_fZero1);
	DDX_Text(pDX, IDC_EDIT_ZERO2, m_fZero2);
	DDX_Text(pDX, IDC_EDIT_ZERO3, m_fZero3);
	DDX_Text(pDX, IDC_EDIT_ZERO4, m_fZero4);
	DDX_Text(pDX, IDC_EDIT_ZERO, m_fZero);
	DDX_Check(pDX, IDC_CHECK_SAMPLE, m_bConSample);
	DDX_Text(pDX, IDC_EDIT_I1, m_fI1);
	DDX_Text(pDX, IDC_EDIT_I2, m_fI2);
	DDX_Text(pDX, IDC_EDIT_I3, m_fI3);
	DDX_Text(pDX, IDC_EDIT_I4, m_fI4);
	DDX_Text(pDX, IDC_SHOW_AD1, m_fAD1);
	DDX_Text(pDX, IDC_SHOW_AD2, m_fAD2);
	DDX_Text(pDX, IDC_SHOW_AD3, m_fAD3);
	DDX_Text(pDX, IDC_SHOW_AD4, m_fAD4);
	DDX_Text(pDX, IDC_NUMBER, m_strNumber);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDebug5, CPropertyPage)
	//{{AFX_MSG_MAP(CDebug5)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_ZERO, OnButtonZero)
	ON_BN_CLICKED(IDC_BUTTON_SAMP, OnButtonSamp)
	ON_BN_CLICKED(IDC_CHECK_SAMPLE, OnCheckSample)
	ON_BN_CLICKED(IDC_BUTTON_GET, OnButtonGet)
	ON_BN_CLICKED(IDC_BUTTON_SEND, OnButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_CALC, OnButtonCalc)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDebug5 message handlers

void CDebug5::OnButtonSave() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	float fK1,fK2,fK3;
	CString sTemp;
	m_cK1.GetWindowText(sTemp);
	fK1=(float)(atof(sTemp));

	m_cK2.GetWindowText(sTemp);
	fK2=(float)(atof(sTemp));

	m_cK3.GetWindowText(sTemp);
	fK3=(float)(atof(sTemp));

	if(fK1<=0)
		fK1=1;
	if(fK2<=0)
		fK2=1;
	if(fK3<=0)
		fK3=1;

	if(m_fZero1<=0)
		m_fZero1=0;
	if(m_fZero2<=0)
		m_fZero2=0;
	if(m_fZero3<=0)
		m_fZero3=0;
	if(m_fZero4<=0)
		m_fZero4=0;

	g_SPEC.m_fZero[0]=m_fZero1;
	g_SPEC.m_fZero[1]=m_fZero2;
	g_SPEC.m_fZero[2]=m_fZero3;
	g_SPEC.m_fZero[3]=m_fZero4;
	g_SPEC.m_fRangeK[0]=fK1;
	g_SPEC.m_fRangeK[1]=fK2;
	g_SPEC.m_fRangeK[2]=fK3;

	////保存
	FILE *fp;
	sTemp=g_strCurPath;
	if((fp=fopen(sTemp+"Cal\\FluxK.dat","wt"))==0)
	{
		if(g_bEnglish)
			AfxMessageBox("Can't save the file!",MB_ICONINFORMATION);
		else
			AfxMessageBox("保存失败!",MB_ICONINFORMATION);
		return;
	}
	else
	{
		fprintf(fp,"Zero1:%10.6f\n",m_fZero1);
		fprintf(fp,"Zero2:%10.6f\n",m_fZero2);
		fprintf(fp,"Zero3:%10.6f\n",m_fZero3);
		fprintf(fp,"Zero4:%10.6f\n",m_fZero4);

		fprintf(fp,"K12:%10.6f\n",fK1);
		fprintf(fp,"K23:%10.6f\n",fK2);
		fprintf(fp,"K34:%10.6f\n",fK3);

		fprintf(fp,"SN.:"+m_strNumber);

		fclose(fp);
		if(g_bEnglish)
			AfxMessageBox("Save succeed!",MB_ICONINFORMATION);
		else
			AfxMessageBox("保存成功!",MB_ICONINFORMATION);
		return;
	}
}

void CDebug5::OnButtonZero() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	BOOL bR;
	int iN=2;
	float fSum=0;
	bR=g_SPEC.SPEC_FluxAD(m_iRange,m_fZero);
	Sleep(10);
	for(int i=0;i<iN;i++)
	{
		bR=g_SPEC.SPEC_FluxAD(m_iRange,m_fZero);
		if(!bR)
		{
			if(g_bEnglish)
				AfxMessageBox("Communication Fail!");
			else
				AfxMessageBox("通讯失败!");
			return;
		}
		fSum=fSum+m_fZero;
	}
	m_fZero=fSum/iN;

	if(m_iRange==0)
		m_fZero1=m_fZero;
	else if(m_iRange==1)
		m_fZero2=m_fZero;
	else if(m_iRange==2)
		m_fZero3=m_fZero;
	else
		m_fZero4=m_fZero;

	UpdateData(FALSE);
}

void CDebug5::OnButtonSamp() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	float fFlux;
	BOOL bR;
	int iN=2;
	float fSum=0;
	bR=g_SPEC.SPEC_FluxAD(m_iRange,fFlux);
	for(int i=0;i<iN;i++)
	{
		bR=g_SPEC.SPEC_FluxAD(m_iRange,fFlux);
		if(!bR)
		{
			if(g_bEnglish)
				AfxMessageBox("Communication Fail!");
			else
				AfxMessageBox("通讯失败!");
			return;
		}
		fSum=fSum+fFlux;
	}
	fFlux=fSum/iN;

	CString sTemp;
	sTemp.Format("%.2f",fFlux);
	m_cAD.SetWindowText(sTemp);

	if(m_iRange==0)
		m_fAD1=fFlux;
	if(m_iRange==1)
		m_fAD2=fFlux;
	if(m_iRange==2)
		m_fAD3=fFlux;
	if(m_iRange==3)
		m_fAD4=fFlux;
	UpdateData(FALSE);
}

void CDebug5::OnCheckSample() 
{
	// TODO: Add your control notification handler code here
	
}

void CDebug5::OnButtonGet() 
{
	// TODO: Add your control notification handler code here
	
}

void CDebug5::OnButtonSend() 
{
	// TODO: Add your control notification handler code here
	
}

void CDebug5::OnCancel() 
{
	// TODO: Add extra cleanup here
	::PostMessage(GetParent()->m_hWnd,WM_CLOSE,0,0);
	
//	CPropertyPage::OnCancel();
}

void CDebug5::OnButtonCalc() 
{
	// TODO: Add your control notification handler code here
	BOOL bR;
	bR=UpdateData(TRUE);
	if(!bR)
		return;
	float fK1,fK2,fK3;
	if(m_fAD1!=m_fZero1)
		fK1=(float)((m_fI1*(m_fAD2-m_fZero2))/(m_fI2*(m_fAD1-m_fZero1)));
	else
		fK1=1;
	fK1=1/fK1;
	if(m_fAD2!=m_fZero2)
		fK2=(float)((m_fI2*(m_fAD3-m_fZero3))/(m_fI3*(m_fAD2-m_fZero2)));
	else
		fK2=1;
	fK2=1/fK2;
	if(m_fAD3!=m_fZero3)
		fK3=(float)((m_fI3*(m_fAD4-m_fZero4))/(m_fI4*(m_fAD3-m_fZero3)));
	else
		fK3=1;
	fK3=1/fK3;

	CString sTemp;
	sTemp.Format("%.6f",fK1);
	m_cK1.SetWindowText(sTemp);

	sTemp.Format("%.6f",fK2);
	m_cK2.SetWindowText(sTemp);

	sTemp.Format("%.6f",fK3);
	m_cK3.SetWindowText(sTemp);
}

BOOL CDebug5::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	CString sTemp;
	sTemp.Format("%.3f",g_SPEC.m_fRangeK[0]);
	m_cK1.SetWindowText(sTemp);
	sTemp.Format("%.3f",g_SPEC.m_fRangeK[1]);
	m_cK2.SetWindowText(sTemp);
	sTemp.Format("%.3f",g_SPEC.m_fRangeK[2]);
	m_cK3.SetWindowText(sTemp);
	
	SetTimer(1,1500,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDebug5::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	CPropertyPage::OnTimer(nIDEvent);
}
