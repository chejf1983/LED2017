// DlgFluxCal.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "DlgFluxCal.h"
#include "Global_MySpec.h"
#include "WYDlg.h"
#include "DlgSpectrumCal.h"
#include "DlgSelfPhK.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgFluxCal dialog
extern BOOL g_bFluxMod;
extern BOOL g_bModeSelf;

extern	int g_iRange;	  //光度采样的档位
extern	int g_iPerRange;  //光度采样的前一档位

CDlgFluxCal::CDlgFluxCal(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFluxCal::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgFluxCal)
	m_fStaFlux = 1000.0f;
	m_fModeFluxK = 1.0f;
	m_fModeSelfK = 1.0f;
	//}}AFX_DATA_INIT
	CString strSection = "FLUX CAL";
	CString strSta     = "STA";
	CString sTemp;
	sTemp = AfxGetApp()->GetProfileString(strSection,strSta,"1000");
	m_fStaFlux=(float)atof(sTemp);
}


void CDlgFluxCal::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFluxCal)
	DDX_Control(pDX, IDC_TEST_SELF_K, m_cTestSelfK);
	DDX_Control(pDX, IDC_STATIC_MOD_S2, m_cModeS2);
	DDX_Control(pDX, IDC_EDIT_MODE_K2, m_cModeSelfK);
	DDX_Control(pDX, IDC_STATIC_MOD, m_cModeS);
	DDX_Control(pDX, IDC_EDIT1, m_cModeK);
	DDX_Control(pDX, IDC_BUTTON_CAL, m_cCal);
	DDX_Control(pDX, IDC_BUTTON_CHECK, m_cCheck);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_cSave);
	DDX_Control(pDX, IDC_EDIT_FLUX, m_cFlux);
	DDX_Control(pDX, IDC_EDIT_STA_FLUX, m_cStaFlux);
	DDX_Control(pDX, IDC_STATIC_S6, m_cS6);
	DDX_Control(pDX, IDC_STATIC_S5, m_cS5);
	DDX_Control(pDX, IDC_STATIC_S4, m_cS4);
	DDX_Control(pDX, IDC_STATIC_S3, m_cS3);
	DDX_Control(pDX, IDC_STATIC_S2, m_cS2);
	DDX_Control(pDX, IDC_STATIC_S1, m_cS1);
	DDX_Text(pDX, IDC_EDIT_STA_FLUX, m_fStaFlux);
	DDX_Text(pDX, IDC_EDIT1, m_fModeFluxK);
	DDX_Text(pDX, IDC_EDIT_MODE_K2, m_fModeSelfK);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgFluxCal, CDialog)
	//{{AFX_MSG_MAP(CDlgFluxCal)
	ON_BN_CLICKED(IDC_BUTTON_CAL, OnButtonCal)
	ON_BN_CLICKED(IDC_BUTTON_CHECK, OnButtonCheck)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_ZERO, OnButtonZero)
	ON_BN_CLICKED(IDC_BUTTON_WY, OnButtonWy)
	ON_BN_CLICKED(IDC_TEST_SELF_K, OnTestSelfK)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgFluxCal message handlers

BOOL CDlgFluxCal::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	HICON hicon;
	hicon= AfxGetApp()->LoadIcon( IDI_FLUX_CAL);
	SetIcon( hicon, TRUE );

	m_fModeFluxK=g_SPEC.m_fModeFluxK;
	if(g_bFluxMod)
	{
		m_cModeS.ShowWindow(TRUE);
		m_cModeK.ShowWindow(TRUE);
	}
	else
	{
		m_cModeS.ShowWindow(FALSE);
		m_cModeK.ShowWindow(FALSE);
		m_fModeFluxK=1;
	}
	if(g_bModeSelf)
	{
		m_cTestSelfK.ShowWindow(TRUE);
		m_cModeS2.ShowWindow(TRUE);
		m_cModeSelfK.ShowWindow(TRUE);
	}
	else
	{
		m_cTestSelfK.ShowWindow(FALSE);
		m_cModeS2.ShowWindow(FALSE);
		m_cModeSelfK.ShowWindow(FALSE);
	}
	UpdateData(FALSE);
	bGo=FALSE;
	m_cStaFlux.SetFont(&Font1);
	m_cFlux.SetFont(&Font1);
	if(g_bEnglish)
	{
		if(g_SPEC.m_iTestType==2)
			SetWindowText("Illumination Calibration");
		if(g_SPEC.m_iTestType==2)
		{
			m_cS1.SetWindowText("1.After turn off the lamp,press 'Zero Adjust' key..");
			m_cS2.SetWindowText("2.After turn on the lamp,Input the standard illumination,Please Waiting after the lamp is stable (about 30min).");
			m_cS3.SetWindowText("Standard illumination:");
			m_cS4.SetWindowText("lx");
			m_cS5.SetWindowText("Check:");
			m_cS6.SetWindowText("lx");
			m_cCal.SetWindowText("Calibration");
			m_cCheck.SetWindowText("Check");
		}
	}
	else
	{
		if(g_SPEC.m_iTestType==1)
			SetWindowText("光通量定标");
		if(g_SPEC.m_iTestType==2)
			SetWindowText("光照度定标");

		if(g_SPEC.m_iTestType==2)
		{
			m_cS1.SetWindowText("1.开灯后,输入标准灯光照度,请等待标准灯稳定(约30分).");
			m_cS2.SetWindowText("2.稳定后按'光照度标定'键.");
			m_cS3.SetWindowText("标准光照度:");
			m_cS4.SetWindowText("lx");
			m_cS5.SetWindowText("光照度检验:");
			m_cS6.SetWindowText("lx");

			m_cCal.SetWindowText("光照度标定");
			m_cCheck.SetWindowText("光照度检验");
		}
	}
	int iType=g_SPEC.m_iTestType;
	if(iType>2)
		iType=2;
	m_fTempFluxK=g_SPEC.m_CAL_fFluxK[iType];

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgFluxCal::OnButtonCal() 
{
	// TODO: Add your control notification handler code here
	CCmdTarget::BeginWaitCursor();
	UpdateData(TRUE);
	float fFlux,fFluxAD;
	BOOL bR;
	if(g_SPEC.m_bPhoto)
	{
		bR=g_SPEC.SPEC_FluxAD(g_iRange,fFlux);
		if(!bR)
		{
			if(g_bEnglish)
				AfxMessageBox("Communication fail!");
			else
				AfxMessageBox("通讯失败!");
			return;
		}
		m_fFluxK=(float)(m_fStaFlux/fFlux);
	}
	else
	{
	while(1)
	{
		int iN=2;
		float fSum=0;
		bR=g_SPEC.SPEC_FluxAD(g_iRange,fFlux);
		for(int i=0;i<iN;i++)
		{
			bR=g_SPEC.SPEC_FluxAD(g_iRange,fFlux);
			if(!bR)
			{
				if(g_bEnglish)
					AfxMessageBox("Communication fail!");
				else
					AfxMessageBox("通讯失败!");
				return;
			}
			fSum=fSum+fFlux;
		}
		fFlux=fSum/iN;
		if(fFlux>AD_FLUX_MAX)
		{
			Sleep(20);
			g_iRange++;
		}
		else if(fFlux<AD_FLUX_MIN)
		{
			Sleep(20);
			g_iRange--;
		}
		else
			break;

		if(g_iRange<0)
		{
			g_iRange=0;
			bR=g_SPEC.SPEC_FluxAD(g_iRange,fFlux);
			if(!bR)
			{
				if(g_bEnglish)
					AfxMessageBox("Communication fail!");
				else
					AfxMessageBox("通讯失败!");
				return;
			}
			break;
		}
		if(g_iRange>=3)
		{
			g_iRange=3;
			bR=g_SPEC.SPEC_FluxAD(g_iRange,fFlux);
			if(!bR)
			{
				if(g_bEnglish)
					AfxMessageBox("Communication fail!");
				else
					AfxMessageBox("通讯失败!");
				return;
			}
			break;
		}
	}
	fFluxAD=fFlux;
	fFlux=fFlux-g_SPEC.m_fZero[g_iRange];
	if(fFlux==0)
		m_fFluxK=1;
	else
	{
		if(g_iRange==0)
			fFlux=(float)(fFlux/g_SPEC.m_fRangeK[0]);
		else if(g_iRange==1)
			fFlux=(float)(fFlux);
		else if(g_iRange==2)
			fFlux=(float)(fFlux*g_SPEC.m_fRangeK[1]);
		else
			fFlux=(float)(fFlux*g_SPEC.m_fRangeK[1]*g_SPEC.m_fRangeK[2]);

		m_fFluxK=(float)(m_fStaFlux/fFlux);
	}
	}

	int iType=g_SPEC.m_iTestType;
	g_SPEC.m_CAL_fFluxK[iType]   = m_fFluxK;

	CString sTemp;
	sTemp.Format("AD:%.1f",fFluxAD);
	if(g_bEnglish)
		MessageBox("OK!",sTemp,MB_ICONINFORMATION);
	else
		MessageBox("完成定标!",sTemp,MB_ICONINFORMATION);
	m_cSave.EnableWindow(TRUE);
	CCmdTarget::EndWaitCursor();
}

void CDlgFluxCal::OnButtonCheck() 
{
	// TODO: Add your control notification handler code here
	BOOL bR;
	if(!bGo)
	{
		bGo=TRUE;
		bR=FluxCheck();
		if(g_bEnglish)
			m_cCheck.SetWindowText("Stop");
		else
			m_cCheck.SetWindowText("停止检验");
		if(!bR)
		{
			bGo=FALSE;
			if(g_bEnglish)
			{
				if(g_SPEC.m_iTestType==1)
					m_cCheck.SetWindowText("Check");
				else
					m_cCheck.SetWindowText("Check");
			}
			else
			{
				if(g_SPEC.m_iTestType==1)
					m_cCheck.SetWindowText("光通量检验");
				else
					m_cCheck.SetWindowText("光照度检验");
			}
		}
		else
		{
			SetTimer(1,1,NULL);
		}
	}
	else
	{
		bGo=FALSE;
		if(g_bEnglish)
		{
			if(g_SPEC.m_iTestType==1)
				m_cCheck.SetWindowText("Check");
			else
				m_cCheck.SetWindowText("Check");
		}
		else
		{
			if(g_SPEC.m_iTestType==1)
				m_cCheck.SetWindowText("光通量检验");
			else
				m_cCheck.SetWindowText("光照度检验");
		}
		KillTimer(1);
	}
}

void CDlgFluxCal::OnButtonSave() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	g_SPEC.m_fModeFluxK	 = m_fModeFluxK;
	g_SPEC.m_fModeSelfK  = m_fModeSelfK;
	int iType=g_SPEC.m_iTestType;
	if(iType>2)
		iType=2;
	g_SPEC.m_CAL_fStaFlux[iType] = m_fStaFlux;
	g_SPEC.m_CAL_iRange[iType]   = g_iRange;
	g_SPEC.m_CAL_fFluxK[iType]   = m_fFluxK;

	m_fTempFluxK=g_SPEC.m_CAL_fFluxK[iType];

	g_SPEC.FLUX_SaveCalK(g_strCurPath+"CAL\\Flux.cal");
	if(g_bEnglish)
		AfxMessageBox("Save the data succeed!");
	else
		AfxMessageBox("数据保存成功!");
}

void CDlgFluxCal::OnCancel() 
{
	// TODO: Add extra cleanup here
	UpdateData(TRUE);

	CString strSection = "FLUX CAL";
	CString strSta     = "STA";

	CString sTemp;
	m_cStaFlux.GetWindowText(sTemp);//.Format("%.2f",m_fStaFlux);
	AfxGetApp()->WriteProfileString(strSection,strSta,sTemp);

	g_SPEC.m_fModeFluxK = m_fModeFluxK;
	g_SPEC.m_fModeSelfK = m_fModeSelfK;

	int iType=g_SPEC.m_iTestType;
	if(iType>2)
		iType=2;
	g_SPEC.m_CAL_fFluxK[iType]=m_fTempFluxK;
	
	CDialog::OnCancel();
}

void CDlgFluxCal::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(bGo)
	{
		KillTimer(1);
		CCmdTarget::BeginWaitCursor();
		FluxCheck();
		CCmdTarget::EndWaitCursor();
		SetTimer(1,500,NULL);
	}
	
	CDialog::OnTimer(nIDEvent);
}

BOOL CDlgFluxCal::FluxCheck()
{
	CCmdTarget::BeginWaitCursor();
	UpdateData(TRUE);
	g_SPEC.m_fModeFluxK	= m_fModeFluxK;
	g_SPEC.m_fModeSelfK	= m_fModeSelfK;

	float fFlux1,fAD;
	BOOL bR=g_SPEC.SPEC_FluxAuto(fAD,fFlux1);
	if(!bR)
	{
		return FALSE;
	}

//	fFlux1=fFlux1*m_fModeFluxK;
	CString sTemp;
	sTemp=g_SPEC.sFormat(fFlux1,5);
	m_cFlux.SetWindowText(sTemp);
	return TRUE;
}

void CDlgFluxCal::OnButtonZero() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CCmdTarget::BeginWaitCursor();
	float fFluxAD;
	int i;
	BOOL bR;
	float fZero[4];
	for(int t=0;t<4;t++)
	{
		fZero[t]=0;
		for(i=0;i<10;i++)
		{
			bR=g_SPEC.SPEC_FluxAD(t,fFluxAD);
			if(!bR)
			{
				if(g_bEnglish)
					AfxMessageBox("Communication Fail!");
				else
					AfxMessageBox("通讯失败!");
				return;
			}
			fZero[t]+=fFluxAD;
		}
		fZero[t]=fZero[t]/10;
	}
	CCmdTarget::EndWaitCursor();

	CString sStr;
	sStr.Format("REF1:%.1f,REF2:%.1f,REF3:%.1f,REF4:%.1f",fZero[0],fZero[1],fZero[2],fZero[3]);
	if(g_bEnglish)
		MessageBox("Adjusting Zero Succeed,Please Turn on Lamp,After Lamp Stable,go to Calibrate!",sStr,MB_ICONINFORMATION);
	else
		MessageBox("校零成功,请开灯,等灯稳定以后,再进行标定!",sStr,MB_ICONINFORMATION);
	UpdateData(FALSE);

	for(t=0;t<4;t++)
		g_SPEC.m_fZero[t]=fZero[t];

	////保存暗电流
	g_SPEC.FLUX_SaveRangeK(g_strCurPath);
}

void CDlgFluxCal::OnButtonWy() 
{
	// TODO: Add your control notification handler code here
	CWYDlg dlg;
	dlg.DoModal();
}

void CDlgFluxCal::OnTestSelfK() 
{
	// TODO: Add your control notification handler code here
	CDlgSelfPhK dlg;
	dlg.m_fSelfPhK	= m_fModeSelfK;
	dlg.DoModal();
	m_fModeSelfK	= dlg.m_fSelfPhK;
	g_SPEC.m_fModeSelfK = dlg.m_fSelfPhK;
	UpdateData(FALSE);
}
