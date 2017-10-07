// Debug6.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "Debug6.h"
#include "Global_MySpec.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDebug6 property page

IMPLEMENT_DYNCREATE(CDebug6, CPropertyPage)

CDebug6::CDebug6() : CPropertyPage(CDebug6::IDD)
{
	//{{AFX_DATA_INIT(CDebug6)
	m_fZero1 = 0.0f;
	m_fZero2 = 0.0f;
	m_fZero3 = 0.0f;
	m_fZero4 = 0.0f;
	m_iRange = 0;
	m_strNumber = _T("");
	m_fAD11 = 0.0f;
	m_fAD12 = 0.0f;
	m_fAD21 = 0.0f;
	m_fAD22 = 0.0f;
	m_fAD31 = 0.0f;
	m_fAD32 = 0.0f;
	m_fK1 = 0.0f;
	m_fK2 = 0.0f;
	m_fK3 = 0.0f;
	//}}AFX_DATA_INIT
}

CDebug6::~CDebug6()
{
}

void CDebug6::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDebug6)
	DDX_Control(pDX, IDC_BUTTON_SAMP, m_cCheck);
	DDX_Control(pDX, IDC_EDIT_AD, m_cAD);
	DDX_Control(pDX, ID_SAVE_EXIT, m_cSave);
	DDX_Control(pDX, IDC_CAL_34, m_cCal34);
	DDX_Control(pDX, IDC_CAL_23, m_cCal23);
	DDX_Control(pDX, IDC_CAL_12, m_cCal12);
	DDX_Text(pDX, IDC_EDIT_Z1, m_fZero1);
	DDX_Text(pDX, IDC_EDIT_Z2, m_fZero2);
	DDX_Text(pDX, IDC_EDIT_Z3, m_fZero3);
	DDX_Text(pDX, IDC_EDIT_Z4, m_fZero4);
	DDX_CBIndex(pDX, IDC_COMBO_RANGE, m_iRange);
	DDX_Text(pDX, IDC_NUMBER, m_strNumber);
	DDX_Text(pDX, IDC_SHOW_AD11, m_fAD11);
	DDX_Text(pDX, IDC_SHOW_AD12, m_fAD12);
	DDX_Text(pDX, IDC_SHOW_AD21, m_fAD21);
	DDX_Text(pDX, IDC_SHOW_AD22, m_fAD22);
	DDX_Text(pDX, IDC_SHOW_AD31, m_fAD31);
	DDX_Text(pDX, IDC_SHOW_AD32, m_fAD32);
	DDX_Text(pDX, IDC_SHOW_K1, m_fK1);
	DDX_Text(pDX, IDC_SHOW_K2, m_fK2);
	DDX_Text(pDX, IDC_SHOW_K3, m_fK3);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDebug6, CPropertyPage)
	//{{AFX_MSG_MAP(CDebug6)
	ON_BN_CLICKED(ID_SAVE_EXIT, OnSaveExit)
	ON_BN_CLICKED(IDC_BUTTON_SAMP, OnButtonSamp)
	ON_BN_CLICKED(IDC_GET_ZERO, OnGetZero)
	ON_BN_CLICKED(IDC_CAL_12, OnCal12)
	ON_BN_CLICKED(IDC_CAL_23, OnCal23)
	ON_BN_CLICKED(IDC_CAL_34, OnCal34)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDebug6 message handlers

BOOL CDebug6::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDebug6::OnOK() 
{
	// TODO: Add extra validation here
	
//	CPropertyPage::OnOK();
}

void CDebug6::OnSaveExit() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
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
	g_SPEC.m_fRangeK[0]=m_fK1;
	g_SPEC.m_fRangeK[1]=m_fK2;
	g_SPEC.m_fRangeK[2]=m_fK3;

	////保存
	g_SPEC.FLUX_SaveRangeK(g_strCurPath);
}

void CDebug6::OnCancel() 
{
	// TODO: Add extra cleanup here
	::PostMessage(GetParent()->m_hWnd,WM_CLOSE,0,0);
	
//	CPropertyPage::OnCancel();
}

void CDebug6::OnButtonSamp() 
{
	// TODO: Add your control notification handler code here
	BOOL bR;
	if(!bGo)
	{
		bGo=TRUE;

		float fFlux;
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

		if (g_bEnglish)
		{
			m_cCheck.SetWindowText("Stop");
		}
		else
		{
			m_cCheck.SetWindowText("停止");
		}
		if(!bR)
		{
			bGo=FALSE;
			if (g_bEnglish)
				m_cCheck.SetWindowText("Sample");
			else
				m_cCheck.SetWindowText("采样");
		}
		else
			SetTimer(1,1,NULL);
	}
	else
	{
		bGo=FALSE;
		if (g_bEnglish)
			m_cCheck.SetWindowText("Sample");
		else
			m_cCheck.SetWindowText("采样");
		KillTimer(1);
	}

	UpdateData(TRUE);
}

void CDebug6::OnGetZero() 
{
	// TODO: Add your control notification handler code here
	CCmdTarget::BeginWaitCursor();
	UpdateData(TRUE);
	BOOL bR;
	int iN=2;
	float fZero;
	int i,j;
	for(i=0;i<4;i++)
	{
		bR=g_SPEC.SPEC_FluxAD(i,fZero);
		bR=g_SPEC.SPEC_FluxAD(i,fZero);
		bR=g_SPEC.SPEC_FluxAD(i,fZero);
		bR=g_SPEC.SPEC_FluxAD(i,fZero);
		Sleep(1000);

		float fSum=0;
		for(j=0;j<iN;j++)
		{
			bR=g_SPEC.SPEC_FluxAD(i,fZero);
			if(!bR)
			{
				if(g_bEnglish)
					AfxMessageBox("Communication Fail!");
				else
					AfxMessageBox("通讯失败!");
				return;
			}
			fSum=fSum+fZero;
		}
		fZero=fSum/iN;

		if(i==0)
			m_fZero1=fZero;
		else if(i==1)
			m_fZero2=fZero;
		else if(i==2)
			m_fZero3=fZero;
		else
			m_fZero4=fZero;
		UpdateData(FALSE);
	}
	m_cCal12.EnableWindow(TRUE);
	CCmdTarget::EndWaitCursor();
}

void CDebug6::OnCal12() 
{
	// TODO: Add your control notification handler code here
	CCmdTarget::BeginWaitCursor();
	UpdateData(TRUE);
	BOOL bR;
	int iN=2;
	int i;
	//得到第一档的AD值
	bR=g_SPEC.SPEC_FluxAD(0,m_fAD11);
	bR=g_SPEC.SPEC_FluxAD(0,m_fAD11);
	bR=g_SPEC.SPEC_FluxAD(0,m_fAD11);
	bR=g_SPEC.SPEC_FluxAD(0,m_fAD11);
	Sleep(1000);

	float fSum=0;
	for(i=0;i<iN;i++)
	{
		bR=g_SPEC.SPEC_FluxAD(0,m_fAD11);
		if(!bR)
		{
			if(g_bEnglish)
				AfxMessageBox("Communication Fail!");
			else
				AfxMessageBox("通讯失败!");
			return;
		}
		fSum=fSum+m_fAD11;
	}
	m_fAD11=fSum/iN;

	//得到第二档的AD值
	bR=g_SPEC.SPEC_FluxAD(1,m_fAD12);
	bR=g_SPEC.SPEC_FluxAD(1,m_fAD12);
	bR=g_SPEC.SPEC_FluxAD(1,m_fAD12);
	bR=g_SPEC.SPEC_FluxAD(1,m_fAD12);
	Sleep(1000);

	fSum=0;
	for(i=0;i<iN;i++)
	{
		bR=g_SPEC.SPEC_FluxAD(1,m_fAD12);
		if(!bR)
		{
			if(g_bEnglish)
				AfxMessageBox("Communication Fail!");
			else
				AfxMessageBox("通讯失败!");
			return;
		}
		fSum=fSum+m_fAD12;
	}
	m_fAD12=fSum/iN;

	if(m_fAD12!=m_fZero2)
		m_fK1=(float)(m_fAD11-m_fZero1)/(m_fAD12-m_fZero2);
	else
		m_fK1=0;
	UpdateData(FALSE);
	m_cCal23.EnableWindow(TRUE);
	CCmdTarget::EndWaitCursor();
}

void CDebug6::OnCal23() 
{
	// TODO: Add your control notification handler code here
	CCmdTarget::BeginWaitCursor();
	UpdateData(TRUE);
	BOOL bR;
	int iN=2;
	int i;
	//得到第2档的AD值
	bR=g_SPEC.SPEC_FluxAD(1,m_fAD21);
	bR=g_SPEC.SPEC_FluxAD(1,m_fAD21);
	bR=g_SPEC.SPEC_FluxAD(1,m_fAD21);
	bR=g_SPEC.SPEC_FluxAD(1,m_fAD21);
	Sleep(1000);

	float fSum=0;
	for(i=0;i<iN;i++)
	{
		bR=g_SPEC.SPEC_FluxAD(1,m_fAD21);
		if(!bR)
		{
			if(g_bEnglish)
				AfxMessageBox("Communication Fail!");
			else
				AfxMessageBox("通讯失败!");
			return;
		}
		fSum=fSum+m_fAD21;
	}
	m_fAD21=fSum/iN;

	//得到第3档的AD值
	bR=g_SPEC.SPEC_FluxAD(2,m_fAD22);
	bR=g_SPEC.SPEC_FluxAD(2,m_fAD22);
	bR=g_SPEC.SPEC_FluxAD(2,m_fAD22);
	bR=g_SPEC.SPEC_FluxAD(2,m_fAD22);
	Sleep(1000);

	fSum=0;
	for(i=0;i<iN;i++)
	{
		bR=g_SPEC.SPEC_FluxAD(2,m_fAD22);
		if(!bR)
		{
			if(g_bEnglish)
				AfxMessageBox("Communication Fail!");
			else
				AfxMessageBox("通讯失败!");
			return;
		}
		fSum=fSum+m_fAD22;
	}
	m_fAD22=fSum/iN;

	if(m_fAD22!=m_fZero3)
		m_fK2=(float)(m_fAD21-m_fZero2)/(m_fAD22-m_fZero3);
	else
		m_fK2=0;
	UpdateData(FALSE);
	m_cCal34.EnableWindow(TRUE);
	CCmdTarget::EndWaitCursor();
}

void CDebug6::OnCal34() 
{
	// TODO: Add your control notification handler code here
	CCmdTarget::BeginWaitCursor();
	UpdateData(TRUE);
	BOOL bR;
	int iN=2;
	int i;
	//得到第3档的AD值
	bR=g_SPEC.SPEC_FluxAD(2,m_fAD31);
	bR=g_SPEC.SPEC_FluxAD(2,m_fAD31);
	bR=g_SPEC.SPEC_FluxAD(2,m_fAD31);
	bR=g_SPEC.SPEC_FluxAD(2,m_fAD31);
	Sleep(1000);

	float fSum=0;
	for(i=0;i<iN;i++)
	{
		bR=g_SPEC.SPEC_FluxAD(2,m_fAD31);
		if(!bR)
		{
			if(g_bEnglish)
				AfxMessageBox("Communication Fail!");
			else
				AfxMessageBox("通讯失败!");
			return;
		}
		fSum=fSum+m_fAD31;
	}
	m_fAD31=fSum/iN;

	//得到第4档的AD值
	bR=g_SPEC.SPEC_FluxAD(3,m_fAD32);
	bR=g_SPEC.SPEC_FluxAD(3,m_fAD32);
	bR=g_SPEC.SPEC_FluxAD(3,m_fAD32);
	bR=g_SPEC.SPEC_FluxAD(3,m_fAD32);
	Sleep(1000);

	fSum=0;
	for(i=0;i<iN;i++)
	{
		bR=g_SPEC.SPEC_FluxAD(3,m_fAD32);
		if(!bR)
		{
			if(g_bEnglish)
				AfxMessageBox("Communication Fail!");
			else
				AfxMessageBox("通讯失败!");
			return;
		}
		fSum=fSum+m_fAD32;
	}
	m_fAD32=fSum/iN;

	if(m_fAD32!=m_fZero2)
		m_fK3=(float)(m_fAD31-m_fZero3)/(m_fAD32-m_fZero4);
	else
		m_fK3=0;
	UpdateData(FALSE);
	m_cSave.EnableWindow(TRUE);
	CCmdTarget::EndWaitCursor();
}

void CDebug6::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(bGo&&nIDEvent==1)
	{
		KillTimer(1);
		CCmdTarget::BeginWaitCursor();
		BOOL bR;
		float fFlux;
		int iN=2;
		float fSum=0;
		bR=g_SPEC.SPEC_FluxAD(m_iRange,fFlux);
		for(int i=0;i<iN;i++)
		{
			bR=g_SPEC.SPEC_FluxAD(m_iRange,fFlux);
			if(!bR)
			{
				bGo=FALSE;
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

		CCmdTarget::EndWaitCursor();
		SetTimer(1,500,NULL);
	}
	
	CPropertyPage::OnTimer(nIDEvent);
}
