// Debug4.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "Debug4.h"
#include "Global_MySpec.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDebug4 property page

extern BOOL g_bCalFlux;

IMPLEMENT_DYNCREATE(CDebug4, CPropertyPage)

CDebug4::CDebug4() : CPropertyPage(CDebug4::IDD)
{
	//{{AFX_DATA_INIT(CDebug4)
	m_iRange = 0;
	m_fZero  = 0.0f;
	m_fZero1 = 0.0f;
	m_fZero2 = 0.0f;
	m_fZero3 = 0.0f;
	m_fZero4 = 0.0f;
	m_iTmpType = 0;
	m_fR1 = 1.0f;
	m_fR2 = 1.1f;
	m_fR3 = 1.2f;
	m_fADCalc = 0;
	m_iRAD1 = 0;
	m_iRAD2 = 0;
	m_iRAD3 = 0;
	//}}AFX_DATA_INIT
}

CDebug4::~CDebug4()
{
}

void CDebug4::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDebug4)
	DDX_Control(pDX, IDC_EDIT_TMP_CALC, m_cTMPCalc);
	DDX_Control(pDX, IDC_BUTTON_SAMP, m_cSamp);
	DDX_Control(pDX, IDC_EDIT_R3, m_cR3);
	DDX_Control(pDX, IDC_EDIT_R_AD3, m_cRAD3);
	DDX_Control(pDX, IDC_BUTTON2, m_cTEMP);
	DDX_Control(pDX, IDC_EDIT_TMP, m_cTMP);
	DDX_Control(pDX, IDC_EDIT_R_AD2, m_cRAD2);
	DDX_Control(pDX, IDC_EDIT_R_AD1, m_cRAD1);
	DDX_Control(pDX, IDC_EDIT_R2, m_cR2);
	DDX_Control(pDX, IDC_EDIT_R1, m_cR1);
	DDX_Control(pDX, IDC_EDIT_K3, m_cK3);
	DDX_Control(pDX, IDC_EDIT_K2, m_cK2);
	DDX_Control(pDX, IDC_EDIT_K1, m_cK1);
	DDX_Control(pDX, IDC_EDIT_AD1, m_cAD);
	DDX_CBIndex(pDX, IDC_COMBO_RANGE, m_iRange);
	DDX_Text(pDX, IDC_EDIT_ZERO, m_fZero);
	DDX_Text(pDX, IDC_EDIT_ZERO1, m_fZero1);
	DDX_Text(pDX, IDC_EDIT_ZERO2, m_fZero2);
	DDX_Text(pDX, IDC_EDIT_ZERO3, m_fZero3);
	DDX_Text(pDX, IDC_EDIT_ZERO4, m_fZero4);
	DDX_Radio(pDX, IDC_RADIO1, m_iTmpType);
	DDX_Text(pDX, IDC_EDIT_R1, m_fR1);
	DDX_Text(pDX, IDC_EDIT_R2, m_fR2);
	DDX_Text(pDX, IDC_EDIT_R3, m_fR3);
	DDX_Text(pDX, IDC_EDIT_AD_CALC, m_fADCalc);
	DDX_Text(pDX, IDC_EDIT_R_AD1, m_iRAD1);
	DDX_Text(pDX, IDC_EDIT_R_AD2, m_iRAD2);
	DDX_Text(pDX, IDC_EDIT_R_AD3, m_iRAD3);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDebug4, CPropertyPage)
	//{{AFX_MSG_MAP(CDebug4)
	ON_BN_CLICKED(IDC_BUTTON_ZERO, OnButtonZero)
	ON_BN_CLICKED(IDC_BUTTON_SAMP, OnButtonSamp)
	ON_BN_CLICKED(IDC_BUTTON_GET, OnButtonGet)
	ON_BN_CLICKED(IDC_BUTTON_SEND, OnButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON_RESET, OnButtonReset)
	ON_BN_CLICKED(IDC_RADIO_COLOR1, OnRadioColor1)
	ON_BN_CLICKED(IDC_RADIO_COLOR2, OnRadioColor2)
	ON_BN_CLICKED(IDC_RADIO_COLOR3, OnRadioColor3)
	ON_BN_CLICKED(IDC_RADIO_COLOR4, OnRadioColor4)
	ON_BN_CLICKED(IDC_RADIO_COLOR5, OnRadioColor5)
	ON_BN_CLICKED(IDC_RADIO_COLOR6, OnRadioColor6)
	ON_BN_CLICKED(IDC_RADIO_COLOR7, OnRadioColor7)
	ON_BN_CLICKED(IDC_RADIO_COLOR8, OnRadioColor8)
	ON_BN_CLICKED(IDC_BUTTON_CALC, OnButtonCalc)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDebug4 message handlers

void CDebug4::OnOK() 
{
	// TODO: Add extra validation here
	
	CPropertyPage::OnOK();
}

BOOL CDebug4::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	bSamp	= FALSE;
	bTmp	= FALSE;
	
	CString sTemp;
	sTemp.Format("%f",g_SPEC.m_fRangeK[0]);
	m_cK1.SetWindowText(sTemp);
	
	sTemp.Format("%f",g_SPEC.m_fRangeK[1]);
	m_cK2.SetWindowText(sTemp);
	
	sTemp.Format("%f",g_SPEC.m_fRangeK[2]);
	m_cK3.SetWindowText(sTemp);
	
	sTemp.Format("%f",g_SPEC.m_fRangeK[0]);
	m_cK1.SetWindowText(sTemp);
	
	m_fZero1 = g_SPEC.m_fZero[0];
	m_fZero2 = g_SPEC.m_fZero[1];
	m_fZero3 = g_SPEC.m_fZero[2];
	m_fZero4 = g_SPEC.m_fZero[3];
	sTemp.Format("%.2f",g_SPEC.m_fR1);
	m_cR1.SetWindowText(sTemp);
	sTemp.Format("%.2f",g_SPEC.m_fR2);
	m_cR2.SetWindowText(sTemp);
	sTemp.Format("%.2f",g_SPEC.m_fR3);
	m_cR3.SetWindowText(sTemp);
	
	sTemp.Format("%d",g_SPEC.m_iRAD1);
	m_cRAD1.SetWindowText(sTemp);
	sTemp.Format("%d",g_SPEC.m_iRAD2);
	m_cRAD2.SetWindowText(sTemp);
	sTemp.Format("%d",g_SPEC.m_iRAD3);
	m_cRAD3.SetWindowText(sTemp);
	m_iRAD1 = g_SPEC.m_iRAD1;
	m_iRAD2 = g_SPEC.m_iRAD2;
	m_iRAD3 = g_SPEC.m_iRAD3;
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDebug4::OnButtonZero() 
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
				AfxMessageBox("Communication fail!");
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

void CDebug4::OnButtonSamp() 
{
	// TODO: Add your control notification handler code here
	BOOL bR=UpdateData(TRUE);
	if(!bR)
		return;
	if(!bSamp)
	{
		bSamp=TRUE;
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
					AfxMessageBox("Communication fail!");
				else
					AfxMessageBox("通讯失败!");
				bSamp=FALSE;
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
			m_cSamp.SetWindowText("Stop");
		}
		else
		{
			m_cSamp.SetWindowText("停止");
		}
		SetTimer(1,10,NULL);
	}
	else
	{
		bSamp=FALSE;
		if (g_bEnglish)
			m_cSamp.SetWindowText("Sample");
		else
			m_cSamp.SetWindowText("采样");
		KillTimer(1);
	}
}

void CDebug4::OnButtonGet() 
{
	// TODO: Add your control notification handler code here
	BOOL bR;
	CCmdTarget::BeginWaitCursor();
	bR=g_SPEC.m_HAAS.ReadEppData();
	if(!bR)
	{
		if(g_bEnglish)
			AfxMessageBox("Communication fail!");
		else
			AfxMessageBox("通讯失败!");
		return;
	}
	CCmdTarget::EndWaitCursor();

	CString sTemp;
	sTemp.Format("%f",g_SPEC.m_fRangeK[0]);
	m_cK1.SetWindowText(sTemp);

	sTemp.Format("%f",g_SPEC.m_fRangeK[1]);
	m_cK2.SetWindowText(sTemp);

	sTemp.Format("%f",g_SPEC.m_fRangeK[2]);
	m_cK3.SetWindowText(sTemp);
	
	sTemp.Format("%f",g_SPEC.m_fRangeK[0]);
	m_cK1.SetWindowText(sTemp);

	m_fZero1 = g_SPEC.m_fZero[0];
	m_fZero2 = g_SPEC.m_fZero[1];
	m_fZero3 = g_SPEC.m_fZero[2];
	m_fZero4 = g_SPEC.m_fZero[3];
	sTemp.Format("%.2f",g_SPEC.m_fR1);
	m_cR1.SetWindowText(sTemp);
	sTemp.Format("%.2f",g_SPEC.m_fR2);
	m_cR2.SetWindowText(sTemp);
	sTemp.Format("%.2f",g_SPEC.m_fR3);
	m_cR3.SetWindowText(sTemp);

	sTemp.Format("%d",g_SPEC.m_iRAD1);
	m_cRAD1.SetWindowText(sTemp);
	sTemp.Format("%d",g_SPEC.m_iRAD2);
	m_cRAD2.SetWindowText(sTemp);
	sTemp.Format("%d",g_SPEC.m_iRAD3);
	m_cRAD3.SetWindowText(sTemp);
	m_iRAD1 = g_SPEC.m_iRAD1;
	m_iRAD2 = g_SPEC.m_iRAD2;
	m_iRAD3 = g_SPEC.m_iRAD3;
	UpdateData(FALSE);
	AfxMessageBox("OK");
}

void CDebug4::OnButtonSend() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CCmdTarget::BeginWaitCursor();
	g_SPEC.m_fZero[0] = m_fZero1;
	g_SPEC.m_fZero[1] = m_fZero2;
	g_SPEC.m_fZero[2] = m_fZero3;
	g_SPEC.m_fZero[3] = m_fZero4;

	CString sTemp;
	m_cK1.GetWindowText(sTemp);
	g_SPEC.m_fRangeK[0] = (float)atof(sTemp);
	
	m_cK2.GetWindowText(sTemp);
	g_SPEC.m_fRangeK[1] = (float)atof(sTemp);

	m_cK3.GetWindowText(sTemp);
	g_SPEC.m_fRangeK[2] = (float)atof(sTemp);

	g_SPEC.m_fR1 = m_fR1;
	g_SPEC.m_fR2 = m_fR2;
	g_SPEC.m_fR3 = m_fR3;

	m_cRAD1.GetWindowText(sTemp);
	g_SPEC.m_iRAD1 = (int)atof(sTemp);
	m_cRAD2.GetWindowText(sTemp);
	g_SPEC.m_iRAD2 = (int)atof(sTemp);
	m_cRAD3.GetWindowText(sTemp);
	g_SPEC.m_iRAD3 = (int)atof(sTemp);

	BOOL bR;
	bR=g_SPEC.m_HAAS.SaveEppData();
	if(!bR)
	{
		if(g_bEnglish)
			AfxMessageBox("Communication fail!");
		else
			AfxMessageBox("通讯失败!");
		return;
	}

	if(1)
	{
		//比较数据是否正确
		float fTempK1 = g_SPEC.m_fRangeK[0];
		float fTempK2 = g_SPEC.m_fRangeK[1];
		float fTempK3 = g_SPEC.m_fRangeK[2];

		bR=g_SPEC.m_HAAS.ReadEppData();
		if(!bR)
		{
			if(g_bEnglish)
				AfxMessageBox("Communication fail!");
			else
				AfxMessageBox("通讯失败!");
			return;
		}
		BOOL bOK = TRUE;
		if(m_fZero1 != g_SPEC.m_fZero[0])
		{
			bOK = FALSE;
		}
		if(m_fZero2 != g_SPEC.m_fZero[1])
		{
			bOK = FALSE;
		}
		if(m_fZero3 != g_SPEC.m_fZero[2])
		{
			bOK = FALSE;
		}
		if(m_fZero4 != g_SPEC.m_fZero[3])
		{
			bOK = FALSE;
		}

		if(g_SPEC.m_fRangeK[0] != fTempK1)
		{
			bOK = FALSE;
		}
		
		if(g_SPEC.m_fRangeK[1] != fTempK2)
		{
			bOK = FALSE;
		}

		if(g_SPEC.m_fRangeK[2] != fTempK3)
		{
			bOK = FALSE;
		}
		
		if(g_SPEC.m_fR1 != m_fR1)
		{
			bOK = FALSE;
		}
		if(g_SPEC.m_fR2 != m_fR2)
		{
			bOK = FALSE;
		}
		if(g_SPEC.m_fR3 != m_fR3)
		{
			bOK = FALSE;
		}
		
		CString sTemp;
		int iTemp;
		m_cRAD1.GetWindowText(sTemp);
		iTemp = (int)atof(sTemp);
		if(g_SPEC.m_iRAD1 != iTemp)
		{
			bOK = FALSE;
		}
		
		m_cRAD2.GetWindowText(sTemp);
		iTemp = (int)atof(sTemp);
		if(g_SPEC.m_iRAD2 != iTemp)
		{
			bOK = FALSE;
		}

		m_cRAD3.GetWindowText(sTemp);
		iTemp = (int)atof(sTemp);
		if(g_SPEC.m_iRAD3 != iTemp)
		{
			bOK = FALSE;
		}

		if(!bOK)
		{
			AfxMessageBox("FAIL!");
			return;
		}
	}

	AfxMessageBox("OK!");
	CCmdTarget::EndWaitCursor();
}

void CDebug4::OnCancel() 
{
	// TODO: Add extra cleanup here
	::PostMessage(GetParent()->m_hWnd,WM_CLOSE,0,0);
}

void CDebug4::OnButtonSave() 
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

	g_SPEC.m_fZero[0]	= m_fZero1;
	g_SPEC.m_fZero[1]	= m_fZero2;
	g_SPEC.m_fZero[2]	= m_fZero3;
	g_SPEC.m_fZero[3]	= m_fZero4;
	g_SPEC.m_fRangeK[0]	= fK1;
	g_SPEC.m_fRangeK[1]	= fK2;
	g_SPEC.m_fRangeK[2]	= fK3;

	g_SPEC.FLUX_SaveRangeK(g_strCurPath);
}

void CDebug4::OnButton1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	BOOL bR;
	float fTMP;
	int iTMPAD;
	bR=g_SPEC.SPEC_GetTMP(m_iTmpType,5,fTMP,iTMPAD);
	CString sTemp;
	sTemp.Format("%d",iTMPAD);
	m_cRAD1.SetWindowText(sTemp);
}

void CDebug4::OnButton3() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	BOOL bR;
	float fTMP;
	int iTMPAD;
	bR=g_SPEC.SPEC_GetTMP(m_iTmpType,5,fTMP,iTMPAD);
	CString sTemp;
	sTemp.Format("%d",iTMPAD);
	m_cRAD2.SetWindowText(sTemp);
}

void CDebug4::OnButton2() 
{
	// TODO: Add your control notification handler code here
	BOOL bR=UpdateData(TRUE);
	if(!bR)
		return;
	if(!bTmp)
	{
		bTmp=TRUE;
		BOOL bR;
		float fTMP;
		int iTMP,iAve;
		if(m_iTmpType==3)
			iAve=1;
		else
			iAve=10;

		bR=g_SPEC.SPEC_GetTMP(m_iTmpType,iAve,fTMP,iTMP);
		if(!bR)
		{
			if(g_bEnglish)
				AfxMessageBox("Fail");
			else
				AfxMessageBox("采样温度失败!");
			bTmp=FALSE;
			return;
		}
		CString sTemp;
		if(m_iTmpType!=2)
			sTemp.Format("%.4f",fTMP);
		else
			sTemp.Format("%.2f",fTMP);
		m_cTMP.SetWindowText(sTemp);
		if(g_bEnglish)
			m_cTEMP.SetWindowText("Stop");
		else
			m_cTEMP.SetWindowText("停止");
//		m_cADTMP.SetWindowText(sTemp);
//		m_cAveTime.SetReadOnly(1);
		SetTimer(2,10,NULL);
	}
	else
	{
		bTmp=FALSE;
		if(g_bEnglish)
			m_cTEMP.SetWindowText("Sample");
		else
			m_cTEMP.SetWindowText("采样");
		KillTimer(2);
	}
}

void CDebug4::OnButton4() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString sTitle;
	sTitle=g_strCurPath+"CAL\\TMP.dat";
	FILE *fp;
	if((fp=fopen(sTitle,"wt"))==0)
		return;
	else
	{
		fprintf(fp,"R1:%.1f AD1:%d\n",m_fR1,m_iRAD1);
		fprintf(fp,"R2:%.1f AD2:%d\n",m_fR2,m_iRAD2);
		fprintf(fp,"R3:%.1f AD3:%d\n",m_fR3,m_iRAD3);
		fclose(fp);

		g_SPEC.m_fR1   = m_fR1;
		g_SPEC.m_fR2   = m_fR2;
		g_SPEC.m_fR3   = m_fR3;
		g_SPEC.m_iRAD1 = m_iRAD1;
		g_SPEC.m_iRAD2 = m_iRAD2;
		g_SPEC.m_iRAD3 = m_iRAD3;

		if(g_bEnglish)
			AfxMessageBox("OK!");
		else
			AfxMessageBox("保存成功!");
		return;
	}
}

void CDebug4::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(bTmp)
	{
		KillTimer(2);
		CCmdTarget::BeginWaitCursor();
		BOOL bR;
		float fTMP;
		int iTMP;
		bR=g_SPEC.SPEC_GetTMP(m_iTmpType,10,fTMP,iTMP);
		if(!bR)
		{
			bTmp=FALSE;
			if(g_bEnglish)
				AfxMessageBox("Fail!");
			else
				AfxMessageBox("采样温度失败!");
			return;
		}
		CString sTemp;	
		if(m_iTmpType!=2)
			sTemp.Format("%.4f",fTMP);
		else
			sTemp.Format("%.2f",fTMP);
		m_cTMP.SetWindowText(sTemp);
//		m_cADTMP.SetWindowText(sTemp);
		CCmdTarget::EndWaitCursor();
		SetTimer(2,10,NULL);
	}
	if(bSamp)
	{
		KillTimer(1);
		CCmdTarget::BeginWaitCursor();
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
				bSamp=FALSE;
				if(g_bEnglish)
					AfxMessageBox("Communication fail!");
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
		SetTimer(1,10,NULL);
	}

	CPropertyPage::OnTimer(nIDEvent);
}

void CDebug4::OnButton5() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	BOOL bR;
	float fTMP;
	int iTMPAD;
	bR=g_SPEC.SPEC_GetTMP(m_iTmpType,5,fTMP,iTMPAD);
	CString sTemp;
	sTemp.Format("%d",iTMPAD);
	m_cRAD3.SetWindowText(sTemp);
}

void CDebug4::OnButtonReset() 
{
	// TODO: Add your control notification handler code here
	CCmdTarget::BeginWaitCursor();
//	g_SPEC.m_HAAS.SetColor(0,TRUE);
	CCmdTarget::EndWaitCursor();
}

void CDebug4::OnRadioColor1() 
{
	// TODO: Add your control notification handler code here
	CCmdTarget::BeginWaitCursor();
//	g_SPEC.m_HAAS.SetColor(0,FALSE);
	CCmdTarget::EndWaitCursor();
}

void CDebug4::OnRadioColor2() 
{
	// TODO: Add your control notification handler code here
	CCmdTarget::BeginWaitCursor();
//	g_SPEC.m_HAAS.SetColor(1,FALSE);
	CCmdTarget::EndWaitCursor();
}

void CDebug4::OnRadioColor3() 
{
	// TODO: Add your control notification handler code here
	CCmdTarget::BeginWaitCursor();
//	g_SPEC.m_HAAS.SetColor(2,FALSE);
	CCmdTarget::EndWaitCursor();
}

void CDebug4::OnRadioColor4() 
{
	// TODO: Add your control notification handler code here
	CCmdTarget::BeginWaitCursor();
//	g_SPEC.m_HAAS.SetColor(3,FALSE);
	CCmdTarget::EndWaitCursor();
}

void CDebug4::OnRadioColor5() 
{
	// TODO: Add your control notification handler code here
	CCmdTarget::BeginWaitCursor();
//	g_SPEC.m_HAAS.SetColor(4,FALSE);
	CCmdTarget::EndWaitCursor();
}

void CDebug4::OnRadioColor6() 
{
	// TODO: Add your control notification handler code here
	CCmdTarget::BeginWaitCursor();
//	g_SPEC.m_HAAS.SetColor(5,FALSE);
	CCmdTarget::EndWaitCursor();
}

void CDebug4::OnRadioColor7() 
{
	// TODO: Add your control notification handler code here
	CCmdTarget::BeginWaitCursor();
//	g_SPEC.m_HAAS.SetColor(6,FALSE);
	CCmdTarget::EndWaitCursor();
}

void CDebug4::OnRadioColor8() 
{
	// TODO: Add your control notification handler code here
	CCmdTarget::BeginWaitCursor();
//	g_SPEC.m_HAAS.SetColor(7,FALSE);
	CCmdTarget::EndWaitCursor();
}

void CDebug4::OnButtonCalc() 
{
	// TODO: Add your control notification handler code here
	BOOL bR;
	bR = UpdateData(TRUE);
	if(!bR)
	{
		return;
	}

	double fR[1500],fT[1500];
	int iTMPN;
	iTMPN=1500;
	float B=3840;
	float T1=298;
	double R = m_fADCalc;
	float fTMP;
	for(int i = 0; i < iTMPN; i++)
	{
		fT[i] = i * 0.1 - 0;
		if(fT[i] == 25.0f)
		{
			fR[i] = 50;
		}
		else
		{
			fR[i] = (double)(50.0f / (exp(B * (1 / T1 - 1 / (fT[i] + 273)))));
		}
	}

	fTMP=(float)(g_SPEC.m_HAAS.PRO_NewInt(fR, fT, iTMPN, R));//

	CString strTemp;
	strTemp.Format("%.2f",fTMP);
	m_cTMPCalc.SetWindowText(strTemp);

	if(1)
	{
		////保存
		FILE *fp;
		CString sTemp = g_strCurPath;
		if((fp = fopen(sTemp + "CalcTMP.dat", "wt")) == 0)
		{
			return;
		}
		else
		{
			fprintf(fp,"R T\n");
			for(i = 0; i < iTMPN; i++)
			{
				fprintf(fp,"%10.6f %10.6f\n", fR[i],fT[i]);	
			}
	
			fclose(fp);
		}
	}
}

void CDebug4::OnButton6() 
{
	// TODO: Add your control notification handler code here
	//选择导出路径
	CString strTemp;
	static char BASED_CODE szFilter[]="TXT Files(*.txt)|*.txt||";
	CFileDialog mOpenFile(TRUE, ".txt",strTemp,  OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);
	if(mOpenFile.DoModal()==IDCANCEL)
	{
		return;
	}

	strTemp = mOpenFile.GetPathName();

	CArray<float, float> fAd;
	CArray<float, float> fPh;
	CArray<float, float> fTMP;

	FILE *fp;
	if((fp = fopen(strTemp, "rt")) == NULL)
	{
		return;
	}
	else
	{
		while(1)
		{
			float fTemp1;
			float fTemp2;
			fscanf(fp,"%f	%f\n", &fTemp1, &fTemp2);
			if(fTemp1 == -1)
			{
				break;
			}
			fAd.Add(fTemp1);
			fPh.Add(fTemp2);
		}
	}
	fclose(fp);

	double fR[1500],fT[1500];
	int iTMPN;
	iTMPN=1500;
	float B=3840;
	float T1=298;
	for(int i = 0; i < iTMPN; i++)
	{
		fT[i] = i * 0.1 - 0;
		if(fT[i] == 25.0f)
		{
			fR[i] = 50;
		}
		else
		{
			fR[i] = (double)(50.0f / (exp(B * (1 / T1 - 1 / (fT[i] + 273)))));
		}
	}
	

	for (i = 0; i < fAd.GetSize(); i++)
	{
		float fTemp3;
		fTemp3 = (float)(fAd[i] * 10 * 5 / 65535 / (2.5f - fAd[i] * 5 / 65535));
		float fTemp4;
		fTemp4 = (float)(g_SPEC.m_HAAS.PRO_NewInt(fR, fT, iTMPN, fTemp3));//
		fTMP.Add(fTemp4);
	}

	if((fp = fopen(strTemp + "_2.txt", "wt")) == NULL)
	{
		return;
	}
	else
	{
		for (i = 0; i < fAd.GetSize(); i++)
		{
			fprintf(fp,"%f	%f	%f\n", fAd[i], fPh[i], fTMP[i]);
		}
	}
	fclose(fp);
}
