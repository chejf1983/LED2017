// DlgNewFluxCal.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "DlgNewFluxCal.h"
#include "SpectData.h"
#include "MainFrm.h"
#include "SPEC_PRO.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern BOOL g_bEnglish;
extern CCSPEC_PRO g_SPEC;

/////////////////////////////////////////////////////////////////////////////
// CDlgNewFluxCal dialog


CDlgNewFluxCal::CDlgNewFluxCal(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgNewFluxCal::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgNewFluxCal)
	m_fStaFlux = 1000.0f;
	m_strRemarks = _T("D204");
	m_strDate = _T("");
	//}}AFX_DATA_INIT
}


void CDlgNewFluxCal::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgNewFluxCal)
	DDX_Control(pDX, IDCANCEL, m_cExit);
	DDX_Control(pDX, IDC_BUTTON_SAVE_CAL, m_cSaveCal);
	DDX_Control(pDX, IDC_BUTTON_CAL, m_cCal);
	DDX_Control(pDX, IDC_EDIT_TEST_FLUX, m_cTestFlux);
	DDX_Text(pDX, IDC_EDIT_STA_FLUX, m_fStaFlux);
	DDV_MinMaxFloat(pDX, m_fStaFlux, 0.1f, 10000.f);
	DDX_Text(pDX, IDC_EDIT_REMARKS, m_strRemarks);
	DDX_Text(pDX, IDC_EDIT_DATE, m_strDate);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgNewFluxCal, CDialog)
	//{{AFX_MSG_MAP(CDlgNewFluxCal)
	ON_BN_CLICKED(IDC_BUTTON_CAL, OnButtonCal)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_CAL, OnButtonSaveCal)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgNewFluxCal message handlers

void CDlgNewFluxCal::OnOK() 
{
	// TODO: Add extra validation here
	
//	CDialog::OnOK();
}

extern BOOL g_Use_FluxLamp_SelfCal;

void CDlgNewFluxCal::OnButtonCal() 
{
	// TODO: Add your control notification handler code here
	if(UpdateData(TRUE) == FALSE)
		return;

	BOOL bR;
	BeginWaitCursor();

	g_Use_FluxLamp_SelfCal = FALSE;
	bR = Test();
	g_Use_FluxLamp_SelfCal = TRUE;
	EndWaitCursor();
	if(bR == FALSE)
		return;

	CString strTemp;
	strTemp.Format("%.5g", m_spData.m_fPh);
	m_cTestFlux.SetWindowText(strTemp);

	m_cSaveCal.EnableWindow(TRUE);
}

extern CString g_strCurPath;

void CDlgNewFluxCal::OnButtonSaveCal() 
{
	// TODO: Add your control notification handler code here
	if(UpdateData(TRUE) == FALSE)
		return;

	CString strTemp;
	m_cTestFlux.GetWindowText(strTemp);

	g_SPEC.m_fluxLampSelfCalData.m_strRemarks = m_strRemarks;
	g_SPEC.m_fluxLampSelfCalData.m_fStaFlux = m_fStaFlux;
	g_SPEC.m_fluxLampSelfCalData.m_fTestFlux = (float)atof(strTemp);
	g_SPEC.m_fluxLampSelfCalData.m_fCalK = m_fStaFlux / (float)atof(strTemp);

	CTime tNow = CTime::GetCurrentTime();
	m_strDate = tNow.Format("%Y-%m-%d %H:%M");
	g_SPEC.m_fluxLampSelfCalData.m_strDate = m_strDate;

	UpdateData(FALSE);

	g_SPEC.m_fluxLampSelfCalData.Save(g_strCurPath + "Cal\\FluxLampSelfCal.dat");

	m_cSaveCal.EnableWindow(FALSE);
}

void CDlgNewFluxCal::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL CDlgNewFluxCal::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	m_strRemarks = g_SPEC.m_fluxLampSelfCalData.m_strRemarks;
	m_fStaFlux = g_SPEC.m_fluxLampSelfCalData.m_fStaFlux;
	
	m_strDate = g_SPEC.m_fluxLampSelfCalData.m_strDate;

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDlgNewFluxCal::Test()
{
	m_spData.m_bHaveData=FALSE;
	m_spData.m_iDataType=TYPE_SCAN;

	float m_fIntTime = 100;

	if(g_bEnglish)
	{
		CMainFrame::ShowNote("Sample...");
	}
	else
	{
		CMainFrame::ShowNote("正在采样,请等待...");
	}

	CCmdTarget::BeginWaitCursor();
	float fMax;
	BOOL bR;

	bR = g_SPEC.SPEC_GetAutoTime(m_fIntTime, 30000, 0.3f);
	if(bR == FALSE)
		return FALSE;

	if(g_SPEC.m_fIntTimeDark!=m_fIntTime)
	{
		g_SPEC.SPEC_GetDark(m_fIntTime,1);
	}

	bR=g_SPEC.SPEC_DoScan(m_fIntTime*1.0f, 3, MY_TRIG_NORMAL,fMax,FALSE,m_spData.m_iDataType);
	if(!bR)
	{
		if(g_bEnglish)
		{
			MessageBox("Sample fail!",NULL,MB_ICONSTOP);
		}
		else
		{
			MessageBox("采样失败!",NULL,MB_ICONSTOP);
		}
		return FALSE;
	}
	CCmdTarget::EndWaitCursor();
	bR=g_SPEC.SPEC_OVER(fMax);
	if(bR)
	{
		AfxMessageBox("AD Overflow!");
		return FALSE;
	}

	g_SPEC.SPEC_GetSpectData(TRUE,m_spData);

	m_spData.m_fPH = 0;
	// 用光谱法的光度
	//////////用光谱仪的光度探头测试的光通量/////////////
	float fPhDetector;
	float fAD;
	fAD = fPhDetector = 0;
	CMainFrame::ShowNote("",TRUE,RGB(255,0,0));
	m_spData.m_bTestPH = TRUE;

	m_spData.m_bTestPH = TRUE;
	m_spData.m_fPH = m_spData.m_fPh;

	m_spData.DoPh_e(PH_F);

	CMainFrame::ShowNote("");

	return TRUE;
}
