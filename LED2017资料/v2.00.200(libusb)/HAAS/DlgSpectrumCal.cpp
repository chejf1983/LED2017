// DlgSpectrumCal.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "DlgSpectrumCal.h"
#include "WYDlg.h"
#include "Note.h"
#include "math.h"
#include "GLobal_MySpec.h"
#include "MainFrm.h"
#include "ExGetColorParaDLL.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSpectrumCal dialog
extern BOOL g_bALL;
extern BOOL g_bUseHLK;
extern BOOL g_bStrong;

extern float g_fSpect1;
extern float g_fSpect2;

CDlgSpectrumCal::CDlgSpectrumCal(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSpectrumCal::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSpectrumCal)
	m_fIntTime = 80.0f;
	m_fStaCurr = 1.3542f;
	m_fStaTc   = 2856.0f;
	m_fStaPh   = 100.0f;
	m_iCalPhType = 1;
	m_fStaVol  = 0.0f;
	m_bWY      = FALSE;
	m_fDistance = 0.1f;
	m_iAveN = 0;
	m_bAll = FALSE;
	m_iLampType = 0;
	m_iLamp = 0;
	m_bAuto = TRUE;
	m_iListCalSele = 0;
	//}}AFX_DATA_INIT

	CString strSection = "Spectrum Cal";

	CString strPhType  = "PhType";
	CString strStaPh   = "StaPh";
	CString strStaCurr = "StaCurr";
	CString strStaVol  = "StaVol";
	CString strStaTc   = "StaTc";
	CString strIntTime = "IntTime";
	CString strDistance= "Distance";
	CString strAveN    = "AVE N";
	CString strALL	   = "ALL";

	CString strTemp;

	m_iCalPhType = AfxGetApp()->GetProfileInt(strSection,strPhType,1);
	strTemp      = AfxGetApp()->GetProfileString(strSection,strStaPh,"100");
	m_fStaPh     = (float)atof(strTemp);
	strTemp      = AfxGetApp()->GetProfileString(strSection,strStaCurr,"0.3");
	m_fStaCurr   = (float)atof(strTemp);
	strTemp      = AfxGetApp()->GetProfileString(strSection,strStaVol,"6");
	m_fStaVol    = (float)atof(strTemp);
	strTemp      = AfxGetApp()->GetProfileString(strSection,strStaTc,"2856");
	m_fStaTc     = (float)atof(strTemp);
	strTemp      = AfxGetApp()->GetProfileString(strSection,strIntTime,"50");
	m_fIntTime   = (float)atof(strTemp);
	strTemp      = AfxGetApp()->GetProfileString(strSection,strDistance,"0.1");
	m_fDistance  = (float)atof(strTemp);
	m_iAveN		 = AfxGetApp()->GetProfileInt(strSection,strAveN,10);
	m_bAll		 = AfxGetApp()->GetProfileInt(strSection,strALL,FALSE);

	m_iCurMode=0;
}

void CDlgSpectrumCal::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSpectrumCal)
	DDX_Control(pDX, IDC_STATIC_LIST_S, m_cListS);
	DDX_Control(pDX, IDC_COMBO_LIST_CAL_SELE, m_cListCalSele);
	DDX_Control(pDX, IDC_PROGRESS1, m_cPro);
	DDX_Control(pDX, IDC_CHECK_AUTO, m_cAuto);
	DDX_Control(pDX, IDC_COMBO_LAMP, m_cLamp);
	DDX_Control(pDX, IDC_COMBO_LAMP_TYPE, m_cLampType);
	DDX_Control(pDX, IDC_CHECK_ALL, m_cAll);
	DDX_Control(pDX, IDC_EDIT_AVE_N, m_cAveN);
	DDX_Control(pDX, IDC_STATIC_I_S1, m_cIS1);
	DDX_Control(pDX, IDC_EDIT_DISTANCE, m_cDistance);
	DDX_Control(pDX, IDC_CHECK_WY, m_cWY);
	DDX_Control(pDX, IDC_STATIC_SETUP, m_cSet);
	DDX_Control(pDX, IDC_BUTTON_STOP, m_cStop);
	DDX_Control(pDX, IDC_LIST, m_cList);
	DDX_Control(pDX, IDC_EDIT_STA_VOL, m_cStaVol);
	DDX_Control(pDX, IDC_STATIC_STA_PH, m_cStaPhS);
	DDX_Control(pDX, IDCANCEL, m_cExit);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_cSave);
	DDX_Control(pDX, IDC_BUTTON_ON, m_cON);
	DDX_Control(pDX, IDC_BUTTON_OFF, m_cOFF);
	DDX_Control(pDX, IDC_BUTTON_CAL, m_cCal);
	DDX_Control(pDX, IDC_IP, m_cIP);
	DDX_Control(pDX, IDC_EDIT_STA_TC, m_cStaTc);
	DDX_Control(pDX, IDC_EDIT_STA_PH, m_cStaPh);
	DDX_Control(pDX, IDC_EDIT_STA_CURR, m_cStaCurr);
	DDX_Control(pDX, IDC_EDIT_INT_TIME, m_cIntTime);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_cCalPhType);
	DDX_Control(pDX, IDC_DRAW, m_cDraw);
	DDX_Text(pDX, IDC_EDIT_INT_TIME, m_fIntTime);
	DDX_Text(pDX, IDC_EDIT_STA_CURR, m_fStaCurr);
	DDX_Text(pDX, IDC_EDIT_STA_TC, m_fStaTc);
	DDV_MinMaxFloat(pDX, m_fStaTc, 100.f, 10000.f);
	DDX_Text(pDX, IDC_EDIT_STA_PH, m_fStaPh);
	DDX_CBIndex(pDX, IDC_COMBO_TYPE, m_iCalPhType);
	DDX_Text(pDX, IDC_EDIT_STA_VOL, m_fStaVol);
	DDX_Check(pDX, IDC_CHECK_WY, m_bWY);
	DDX_Text(pDX, IDC_EDIT_DISTANCE, m_fDistance);
	DDX_Text(pDX, IDC_EDIT_AVE_N, m_iAveN);
	DDV_MinMaxInt(pDX, m_iAveN, 1, 50);
	DDX_Check(pDX, IDC_CHECK_ALL, m_bAll);
	DDX_CBIndex(pDX, IDC_COMBO_LAMP_TYPE, m_iLampType);
	DDX_CBIndex(pDX, IDC_COMBO_LAMP, m_iLamp);
	DDX_Check(pDX, IDC_CHECK_AUTO, m_bAuto);
	DDX_CBIndex(pDX, IDC_COMBO_LIST_CAL_SELE, m_iListCalSele);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgSpectrumCal, CDialog)
	//{{AFX_MSG_MAP(CDlgSpectrumCal)
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE, OnSelchangeComboType)
	ON_BN_CLICKED(IDC_BUTTON_CAL, OnButtonCal)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_ON, OnButtonOn)
	ON_BN_CLICKED(IDC_BUTTON_OFF, OnButtonOff)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnItemchangedList)
	ON_BN_CLICKED(IDC_CHECK_WY, OnCheckWy)
	ON_BN_CLICKED(IDC_STATIC_SETUP, OnStaticSetup)
	ON_BN_CLICKED(IDC_CHECK_ALL, OnCheckAll)
	ON_CBN_SELCHANGE(IDC_COMBO_LAMP, OnSelchangeComboLamp)
	ON_CBN_SELCHANGE(IDC_COMBO_LAMP_TYPE, OnSelchangeComboLampType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSpectrumCal message handlers

void CDlgSpectrumCal::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}

extern BOOL g_bOpenMulitCalSpectrum;

BOOL CDlgSpectrumCal::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	GetDlgItem(IDC_STATIC_LIST_S)->ShowWindow(g_bOpenMulitCalSpectrum == TRUE);
	GetDlgItem(IDC_COMBO_LIST_CAL_SELE)->ShowWindow(g_bOpenMulitCalSpectrum == TRUE);

	BOOL bR;
	bR=GetLampName();

	m_cLamp.ResetContent();
	if(bR)
	{
		for(int i=0;i<m_strListCtrlFile.GetSize();i++)
		{
			m_cLamp.InsertString(i,m_strListCtrlFile.GetAt(i));
		}
	}
	if(m_iLamp>m_strListCtrlFile.GetSize())
		m_iLamp=m_strListCtrlFile.GetSize();
	if(m_iLamp<0)
		m_iLamp=0;
	UpdateData(FALSE);
	OnSelchangeComboLamp();

	m_iLampType = 0;

	m_cSet.SetLink(TRUE)
		.SetTextColor(RGB(0,0,255))
		.SetFontUnderline(TRUE)
		.SetLinkCursor(AfxGetApp()->LoadCursor(IDC_HAND));

	SetShowIcon(TRUE);
	Show();

	m_fTempSP1 = g_fSpect1;
	m_fTempSP2 = g_fSpect2;
	m_iTempBin = g_SPEC.m_iBin;
	m_iTempMode= g_SPEC.m_iMode;

	m_spData[0].m_bHaveData = FALSE;
	m_spData[0].m_iDataType = TYPE_CAL;

	m_drawData.bMouse	= FALSE;
	m_drawData.iCurSele	= 0;
	m_drawData.bShowCur	= FALSE;
	m_drawData.iDrawType= 0;

	ReDraw();

	m_cIP.SetTextColor(RGB(0,0,255))
		.SetFontUnderline(TRUE);

	m_cIP.SetWindowText("");

	//图标
	m_SmallImageList.Create(IDB_SMALLICONS, 16, 1, RGB(255, 255, 255));
	m_cList.SetImageList(&m_SmallImageList, LVSIL_SMALL);

	m_cList.SetExtendedStyle(m_cList.GetExtendedStyle()  | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);

	ReList();

	m_iCur = 40;

	m_iCalPhType = g_SPEC.m_iTestType;
	if(m_iCalPhType != 3)
	{
		m_cIS1.ShowWindow(FALSE);
		m_cDistance.ShowWindow(FALSE);
	}
	else
	{
		m_cIS1.ShowWindow(TRUE);
		m_cDistance.ShowWindow(TRUE);
	}
	UpdateData(FALSE);
	if(m_iLampType==0)
		m_cLamp.EnableWindow(FALSE);
	else
		m_cLamp.EnableWindow(TRUE);

	OnSelchangeComboType();

	CString strTemp;
	m_cListCalSele.ResetContent();
	m_cListCalSele.AddString("000: Def");
	for(int i = 0; i < 100; i++)
	{
		strTemp.Format("%03d", i + 1);
		m_cListCalSele.InsertString(i + 1, strTemp);
	}

	m_cListCalSele.SetCurSel(0);

	m_cListS.EnableWindow(g_SPEC.m_bUseListCalSele);
	m_cListCalSele.EnableWindow(g_SPEC.m_bUseListCalSele);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSpectrumCal::ReDraw()
{
	m_cDraw.DrawSpect(m_spData[m_iCurMode],m_drawData,"");
}

void CDlgSpectrumCal::OnCancel() 
{
	// TODO: Add extra cleanup here
	UpdateData(TRUE);
	g_bALL = m_bAll;
	SaveSet();

	if(!g_bALL)
	{
		g_fSpect1 = m_fTempSP1;
		g_fSpect2 = m_fTempSP2;
		g_SPEC.m_iBin  = m_iTempBin;
		g_SPEC.m_iMode = m_iTempMode;
	}
	
	CDialog::OnCancel();
}

extern BOOL g_Use_FluxLamp_SelfCal;

void CDlgSpectrumCal::OnSelchangeComboType() 
{
	// TODO: Add your control notification handler code here
	if(UpdateData(TRUE)==FALSE)
		return;
	g_SPEC.m_iTestType=m_iCalPhType;

	if(g_Use_FluxLamp_SelfCal == TRUE && m_iCalPhType == 1)
	{
		GetDlgItem(IDC_STATIC_STA_PH)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_STA_PH)->ShowWindow(SW_HIDE);
	}
	else
	{
		GetDlgItem(IDC_STATIC_STA_PH)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_STA_PH)->ShowWindow(SW_SHOW);

	}

	if(m_iCalPhType!=3)
	{
		m_cIS1.ShowWindow(FALSE);
		m_cDistance.ShowWindow(FALSE);
	}
	else
	{
		m_cIS1.ShowWindow(TRUE);
		m_cDistance.ShowWindow(TRUE);
	}
	m_cStaPhS.EnableWindow(m_iCalPhType!=0 && m_iLampType == 0);
	m_cStaPh.EnableWindow(m_iCalPhType!=0 && m_iLampType == 0);
	if(g_bEnglish)
	{
		if(m_iCalPhType==1)
			m_cStaPhS.SetWindowText("Flux(lm):");
		if(m_iCalPhType==2)
			m_cStaPhS.SetWindowText("Lum(lx):");
		if(m_iCalPhType==3)
			m_cStaPhS.SetWindowText("I(cd):");
		if(m_iCalPhType==4)
			m_cStaPhS.SetWindowText("L(cd/m2):");
	}
	else
	{
		if(m_iCalPhType==1)
			m_cStaPhS.SetWindowText("标定光通量(lm):");
		if(m_iCalPhType==2)
			m_cStaPhS.SetWindowText("标定照度(lx):");
		if(m_iCalPhType==3)
			m_cStaPhS.SetWindowText("标定光强(cd):");
		if(m_iCalPhType==4)
			m_cStaPhS.SetWindowText("光亮度(cd/m2):");
	}

	OnSelchangeComboLamp();
}

UINT ThreadSpectrumCal(LPVOID pParam)
{
    CDlgSpectrumCal* pDlg=(CDlgSpectrumCal*)pParam;
	BOOL bR;
	CString strTemp;
	CString sTemp;
	if(pDlg->m_bAll)//多模式定标
	{
		if(g_SPEC.m_Have_iBin==2)
			g_SPEC.m_iBin=1;
		g_SPEC.m_fInterval=0.1f;
		CString strTemp, sTemp;
		pDlg->m_cPro.SetRange32(0,g_SPEC.m_Have_iBin*2*4);
		pDlg->m_cPro.ShowWindow(SW_SHOW);
		for(pDlg->m_iCurMode=0;pDlg->m_iCurMode<g_SPEC.m_Have_iBin*2;pDlg->m_iCurMode++)
		{
			pDlg->m_spData[pDlg->m_iCurMode].m_bHaveData=FALSE;	
			pDlg->m_spData[pDlg->m_iCurMode].m_iDataType=TYPE_CAL;

			g_SPEC.m_iBin=pDlg->m_iCurMode%g_SPEC.m_Have_iBin;
			if(pDlg->m_iCurMode<g_SPEC.m_Have_iBin)
				g_SPEC.m_iMode=0;
			else
				g_SPEC.m_iMode=1;

			bR=pDlg->AllModeTest();
			if(!bR)
				break;
//			pDlg->m_cPro.SetPos(pDlg->m_iCurMode);
		}
	}
	else
	{
		while(!pDlg->m_bCancel)
		{
			bR=pDlg->Test();
			if(!bR)
				break;
			Sleep(100);
		}
	}
	pDlg->m_cPro.SetPos(0);
	pDlg->m_cPro.ShowWindow(SW_HIDE);

	pDlg->m_cSave.EnableWindow(TRUE);
	pDlg->EnableShow(FALSE);
	if(g_bEnglish)
		strTemp="Complete Calibration!";
	else
		strTemp="定标完成,请保存!";
	if(bR)
		AfxMessageBox(strTemp);
	pDlg->m_bCancel=FALSE;
	return 0;
}

void CDlgSpectrumCal::OnButtonCal() 
{
	// TODO: Add your control notification handler code here
	if(UpdateData(TRUE)==FALSE)
		return;
	if(m_iCalPhType==3)
	{
		if(m_fDistance==0)
		{
			if(g_bEnglish)
				AfxMessageBox("Please input the right distance!");
			else
				AfxMessageBox("请输入正确的测量距离！");
			return;
		}
	}
	SaveSet();
	m_cWY.EnableWindow(FALSE);

	m_fTempSP1 = g_fSpect1;
	m_fTempSP2 = g_fSpect2;

	g_fSpect1  = g_SPEC.T_SPECT1;
	g_fSpect2  = g_SPEC.T_SPECT2;

	if(!m_bAll)
	{
		m_iNum=0;
		m_iCurMode=0;
		CCmdTarget::BeginWaitCursor();
		CString strTemp;
		if(g_bEnglish)
			strTemp.Format("Auto Time...");
		else
			strTemp.Format("自动积分...");
		CMainFrame::ShowNote(strTemp,TRUE,RGB(255,0,255));

		BOOL bR;
		g_SPEC.m_fInterval=0.1f;
		if(0)//m_bAuto)
		{
			bR=g_SPEC.SPEC_GetAutoTime(m_fIntTime,g_SPEC.m_iAutoLimitTime2,0.6f,m_fIntTime);
		}
		else
		{
			bR=TRUE;
		}
		if(!bR)
		{
			if(g_SPEC.m_iBin==0&&g_bStrong)
			{
				g_bUseHLK=TRUE;
			}
			if(g_bEnglish)
				strTemp.Format("Fail[Spectrum]!");
			else
				strTemp.Format("光谱仪自动积分失败!");
			CMainFrame::ShowNote(strTemp,TRUE,RGB(255,0,0));
			return;
		}
		if(bR&&g_SPEC.m_iBin==0)
		{
			g_bStrong=FALSE;
			g_bUseHLK=FALSE;
		}
		UpdateData(FALSE);
		CCmdTarget::BeginWaitCursor();
	}
	SaveSet();
	EnableShow(TRUE);
	m_bCancel=FALSE;
	AfxBeginThread(ThreadSpectrumCal,this);
}

void CDlgSpectrumCal::OnButtonSave() 
{
	// TODO: Add your control notification handler code here
	CString strTemp="";
	CMainFrame::ShowNote(strTemp,TRUE,RGB(0,0,0));
	int iR;
	if(g_bEnglish)
		iR=MessageBox("Are you sure?",NULL,MB_OKCANCEL|MB_ICONINFORMATION);
	else
		iR=MessageBox("确定保存定标数据?",NULL,MB_OKCANCEL|MB_ICONINFORMATION);
	if(iR==IDCANCEL)
		return;
	UpdateData(TRUE);
	int i;

	float c1 = (float)(3.741844E19*9.58378/8.071367);
	float c2 = (float)(1.438833E7/m_fStaTc);

	g_SPEC.m_SP_fSpect1   = m_spData[0].m_fSpect1;
	g_SPEC.m_SP_fSpect2   = m_spData[0].m_fSpect2;
	g_SPEC.m_fInterval	  = m_spData[0].m_fInterval;

	g_SPEC.m_SP_fStaTc    = m_fStaTc;
	g_SPEC.m_SP_fIntTime  = m_fIntTime;
	g_SPEC.m_CAL_fIntTime[0] = m_fIntTime;
	g_SPEC.m_CAL_fStaFlux[0] = m_fStaPh;

	CTime tNow;
	tNow = CTime::GetCurrentTime();
	CString sNow = tNow.Format("%Y-%m-%d,%H:%M");
	g_SPEC.m_SP_strDate = sNow;

	int iN = m_spData[0].m_fRelSpect.GetSize();
	m_spData[0].DoADSpecForCal(CSpectData::m_fSetDoWL, CSpectData::m_fSetDoLimitAD);
	for(i=0;i<iN;i++)
	{
		float lamda=m_spData[0].m_fSpect1+i*m_spData[0].m_fInterval;
		float fRel;
		double fTemp;
		fRel=m_spData[0].m_fRelSpect[i];
		if(fRel<=0)
			fTemp=0;
		else
		{
			if(m_iLampType==0)
			{
				fTemp=(double)((c1/pow(lamda,5)/(exp(c2/lamda)-1))/fRel);
				g_SPEC.m_SP_fK[i]=(float)(fTemp);
			}
			else
			{
				float fTempRel;
				fTempRel=(float)(g_SPEC.Lagrange_New(g_SPEC.m_fD65_WL,g_SPEC.m_fD65_PL,g_SPEC.m_iStaLampN,lamda));
				fTemp=(double)(fTempRel/fRel);
				g_SPEC.m_SP_fK[i]=(float)(fTemp);
			}
		}
	}

	//根据光通量积分公式计算定标数据
	double d=0;
	for(i=0;i<401;i++)
	{
		float lamda=380+i*1.0f;
		d=d+(c1/pow(lamda,5)/(exp(c2/lamda)-1))* NH_GetV(lamda); 
	}
	
	// 光强到照度计算
	float fTempPh;
	fTempPh=m_fStaPh;
	if(m_iCalPhType==3)
	{
		if(m_fDistance!=0)
			m_fStaPh=(float)m_fStaPh/(m_fDistance*m_fDistance);
	}

	if(m_iLampType==0)
	{
		if(d>0)
			g_SPEC.m_CAL_fFluxK[0] = (float)(m_fStaPh/(d));
		else
			g_SPEC.m_CAL_fFluxK[0] = 1.0f;
	}
	else
	{
		g_SPEC.m_CAL_fFluxK[0] =683.0f;//注意 和相对光谱区分开
	}
	m_fStaPh=fTempPh;

	CString sTemp;
	sTemp="spectrumcal.cal";   //低
	CString strL = "";
	if(g_SPEC.m_iTestType==0)
	{
	}
	if(g_SPEC.m_iTestType==1)
	{
	}
	if(g_SPEC.m_iTestType==2)
	{
		strL="LX_";
	}
	if(g_SPEC.m_iTestType==3)
	{
		strL="I_";
	}

	sTemp=g_strCurPath+"Cal\\Li_" + strL + sTemp;
	/* AAA.新建目录 */
	CString strPosName;
	if(m_iListCalSele > 0)
	{
		strPosName.Format("CAL_%03d", m_iListCalSele);
		CString strPathName = g_strCurPath +  "Cal\\" + strPosName  + "\\";
		g_SPEC.CreateDirectoryMy(strPathName);
	}
	
	/* BBB.保存到新目录 */
	if(m_iListCalSele > 0)
		sTemp.Replace(g_strCurPath+"Cal", g_strCurPath+"Cal\\" + strPosName);

	g_SPEC.SP_Save(sTemp);

	UpdateData(FALSE);

	if(g_bEnglish)
		AfxMessageBox("Save the data succeed!");
	else
		AfxMessageBox("数据保存成功!");
}

void CDlgSpectrumCal::OnButtonOn() 
{
	// TODO: Add your control notification handler code here
	if(UpdateData(TRUE)==FALSE)
		return;
	CCmdTarget::BeginWaitCursor();
	if(g_bAutoLamp)
	{
		BOOL bR;
		int iCOM;
		sscanf(g_strSouComm,"COM%d", &iCOM);
		bR = g_cPower.DX_Power_Init(iCOM);
		if (!bR)
		{
			AfxMessageBox("FAIL !");
			return;
		}
		bR = g_cPower.DX_Power_SetPara(m_fStaVol,m_fStaCurr * 1000);
		if (!bR)
		{
			AfxMessageBox("FAIL !");
			return;
		}
		bR = g_cPower.DX_Power_Output(TRUE);
		if (!bR)
		{
			AfxMessageBox("FAIL !");
		}
	}
	CCmdTarget::EndWaitCursor();
}

void CDlgSpectrumCal::OnButtonOff() 
{
	// TODO: Add your control notification handler code here
	if(UpdateData(TRUE)==FALSE)
		return;	
	CCmdTarget::BeginWaitCursor();
	BOOL bR;
	if (g_bAutoLamp)
	{
		int iCOM;
		sscanf(g_strSouComm,"COM%d", &iCOM);
		bR = g_cPower.DX_Power_Init(iCOM);
		if (!bR)
		{
			AfxMessageBox("FAIL !");
			return;
		}
		bR = g_cPower.DX_Power_Output(FALSE);
		if (!bR)
		{
			AfxMessageBox("FAIL !");
		}
		Sleep(1000);
	}
	bR=g_SPEC.SPEC_GetDark(m_fIntTime,10);
	if(!bR)
	{
		if(g_bEnglish)
			AfxMessageBox("Communication fail!");
		else
			AfxMessageBox("关灯校零失败!");
	}
	CCmdTarget::EndWaitCursor();
}

void CDlgSpectrumCal::SaveSet()
{
	CString strSection	= "Spectrum Cal";
	CString strPhType	= "PhType";
	CString strStaPh	= "StaPh";
	CString strStaCurr	= "StaCurr";
	CString strStaVol	= "StaVol";
	CString strStaTc	= "StaTc";
	CString strIntTime	= "IntTime";
	CString strDistance	= "Distance";
	CString strAveN		= "AVE N";
	CString strALL		= "ALL";

	CString strTemp;
	AfxGetApp()->WriteProfileInt(strSection,strPhType,m_iCalPhType);
	strTemp.Format("%f",m_fStaPh);
	AfxGetApp()->WriteProfileString(strSection,strStaPh,strTemp);
	strTemp.Format("%f",m_fStaCurr);
	AfxGetApp()->WriteProfileString(strSection,strStaCurr,strTemp);
	strTemp.Format("%f",m_fStaVol);
	AfxGetApp()->WriteProfileString(strSection,strStaVol,strTemp);
	strTemp.Format("%f",m_fStaTc);
	AfxGetApp()->WriteProfileString(strSection,strStaTc,strTemp);
	strTemp.Format("%f",m_fIntTime);
	AfxGetApp()->WriteProfileString(strSection,strIntTime,strTemp);
	strTemp.Format("%f",m_fDistance);
	AfxGetApp()->WriteProfileString(strSection,strDistance,strTemp);
	AfxGetApp()->WriteProfileInt(strSection,strAveN,m_iAveN);
	AfxGetApp()->WriteProfileInt(strSection,strALL,m_bAll);
}

void CDlgSpectrumCal::ReList()
{
	m_cList.DeleteAllItems();
	while(1)
	{
		if(m_cList.DeleteColumn(0)==FALSE)
			break;
	}
	CString strTemp;
	int iN=0;

	if(g_bEnglish)
		strTemp="WL(nm)";
	else
		strTemp="波长(nm)";
	m_cList.InsertColumn(iN,strTemp);
	m_cList.SetColumnWidth(iN,60);
	iN++;

	if(g_bEnglish)
		strTemp="AD";
	else
		strTemp="AD值";
	m_cList.InsertColumn(iN,strTemp);
	m_cList.SetColumnWidth(iN,80);
	iN++;

	for(int i=0;i<m_spData[m_iCurMode].m_fRelSpect.GetSize();i++)
	{
		if((i*5)>=m_spData[m_iCurMode].m_fRelSpect.GetSize())
			break;
		iN=0;
		strTemp.Format("%6.1f",m_spData[m_iCurMode].m_fSpect1+i*5*m_spData[m_iCurMode].m_fInterval);
		m_cList.InsertItem(i,strTemp,2);
		iN++;

		strTemp.Format("%6.0f",m_spData[m_iCurMode].m_fRelSpect[i*5]);
		m_cList.SetItemText(i,iN,strTemp);
		iN++;
	}

	//选择到当前位置
//	m_cList.SetItemState(m_iCur, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
//	m_cList.EnsureVisible(m_iCur, FALSE);
}

void CDlgSpectrumCal::EnableShow(BOOL bStart)
{
	m_cCalPhType.EnableWindow(!bStart);
	m_cStaVol.EnableWindow(!bStart);
	m_cStaCurr.EnableWindow(!bStart);
	m_cStaTc.EnableWindow(!bStart);
	if(m_iCalPhType!=0)
		m_cStaPh.EnableWindow(!bStart);
	m_cIntTime.EnableWindow(!bStart);

	m_cON.EnableWindow(g_bAutoLamp&&!bStart);
	m_cOFF.EnableWindow(!bStart);
	m_cCal.EnableWindow(!bStart);
	m_cStop.EnableWindow(bStart);
	m_cExit.EnableWindow(!bStart);
	m_cSet.EnableWindow(!bStart);
	m_cDistance.EnableWindow(!bStart);
	m_cAveN.EnableWindow(!bStart);

	m_cAll.EnableWindow(!bStart);

	m_cAuto.EnableWindow(!bStart);
}

BOOL CDlgSpectrumCal::Test()
{
	CCmdTarget::BeginWaitCursor();
	if(g_SPEC.m_iMode==2)
	{
		if(g_bEnglish)
			AfxMessageBox("Please select Fast or Precise!");
		else
			AfxMessageBox("请选择快速测试模式或精确测试模式!");
		return FALSE;
	}
	float fMax;
	BOOL bR;
	if(m_iNum==0)
	{
		bR=g_SPEC.SPEC_DoScan(m_fIntTime*1.0f,m_iAveN,MY_TRIG_NORMAL,fMax,FALSE,m_spData[m_iCurMode].m_iDataType);
	}
	else
	{
		bR=g_SPEC.SPEC_DoScan(m_fIntTime*1.0f,m_iAveN,MY_TRIG_NORMAL,fMax,FALSE,m_spData[m_iCurMode].m_iDataType);
	}
	if(!bR)
	{
		if(g_bEnglish)
			MessageBox("Sample fail!",NULL,MB_ICONSTOP);
		else
			MessageBox("采样失败!",NULL,MB_ICONSTOP);
		return FALSE;
	}
	else
		m_iNum=1;
	CString strTemp;
	strTemp.Format("%.0f(%.0f%%)",fMax,fMax*100/(g_SPEC.m_nADW-1));
	m_cIP.SetWindowText(strTemp);
	m_cIP.SetFontUnderline(TRUE);
	if((fMax/(g_SPEC.m_nADW-1))<T_L||(fMax>=(g_SPEC.m_nADW-1)))
		m_cIP.SetTextColor(RGB(255,0,0));
	else
		m_cIP.SetTextColor(RGB(0,0,255));

	CCmdTarget::EndWaitCursor();
	bR=g_SPEC.SPEC_OVER(fMax);
	if(bR)
	{
		if(g_bEnglish)
			CNote::Passtext(CString(_T("Overflow!please adjust...")));
		else
			CNote::Passtext(CString(_T("信号溢出!请调节...")));
		CNote::Show(this);
		Sleep(800);
		CNote::Destroy();
	}

	g_SPEC.SPEC_GetSpectData(FALSE,m_spData[m_iCurMode]);

	ReDraw();
	ReList();

	return TRUE;
}

void CDlgSpectrumCal::OnButtonStop() 
{
	// TODO: Add your control notification handler code here
	m_bCancel=TRUE;
	m_cStop.EnableWindow(FALSE);
}

void CDlgSpectrumCal::OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	m_iCur=pNMListView->iItem;
	
	*pResult = 0;
}

void CDlgSpectrumCal::OnCheckWy() 
{
	// TODO: Add your control notification handler code here
	Show();
}

void CDlgSpectrumCal::Show()
{
	UpdateData(TRUE);
	m_cON.EnableWindow(g_bAutoLamp);
	m_cStaCurr.EnableWindow(g_bAutoLamp);
	m_cStaVol.EnableWindow(g_bAutoLamp);
}

void CDlgSpectrumCal::OnStaticSetup() 
{
	// TODO: Add your control notification handler code here
	CCmdTarget::BeginWaitCursor();
	g_SPEC.m_bCal=TRUE;
	g_SPEC.SPEC_Setting();
	g_SPEC.m_bCal=FALSE;
	CCmdTarget::EndWaitCursor();
}

void CDlgSpectrumCal::OnCheckAll() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	g_bALL=m_bAll;
}

BOOL CDlgSpectrumCal::AllModeTest()
{
	CString strTemp;
	BOOL bR;
	m_iNum=0;
	if(g_bEnglish)
	{
		strTemp.Format("Mode %d:Auto Time...",g_SPEC.m_iMode+1);
	}
	else
	{
		if(g_SPEC.m_iMode==0)
			strTemp.Format("快速模式 %d：自动积分...",g_SPEC.m_iBin+1);
		else
			strTemp.Format("精确模式 %d：自动积分...",g_SPEC.m_iBin+1);
	}
	CMainFrame::ShowNote(strTemp,TRUE,RGB(255,0,255));

	if(m_bAuto)
	{
		bR=g_SPEC.SPEC_GetAutoTime(m_fIntTime,g_SPEC.m_iAutoLimitTime2,0.6f,m_fIntTime);
		if(g_SPEC.m_iMode == 1)
		{
			m_fIntTime = (float)((int)(m_fIntTime * 0.9f));
		}
	}
	else
	{
		bR=TRUE;
	}
	if(!bR)
	{
		if(g_SPEC.m_iBin==0&&g_bStrong)
		{
			g_bUseHLK=TRUE;
		}
		if(g_bEnglish)
			strTemp.Format("Fail[Spectrum]!");
		else
			strTemp.Format("光谱仪自动积分失败!");
		CMainFrame::ShowNote(strTemp,TRUE,RGB(255,0,0));
		m_bCancel=FALSE;
		EnableShow(FALSE);
		return 0;
	}
	if(bR&&g_SPEC.m_iBin==0)
	{
		g_bStrong=FALSE;
		g_bUseHLK=FALSE;
	}
	Sleep(1000);
	CString sTemp;
	sTemp.Format("%.0f",m_fIntTime);
	m_cIntTime.SetWindowText(sTemp);
	m_spData[m_iCurMode].m_fIntTime=m_fIntTime;	

	if(m_bCancel)
		return FALSE;
	bR=Test();
	if(!bR)
		return FALSE;
	if(m_bCancel)
		return FALSE;
	m_cPro.SetPos(m_iCurMode*4+1);
	bR=Test();
	if(!bR)
		return FALSE;
	if(m_bCancel)
		return FALSE;
	m_cPro.SetPos(m_iCurMode*4+2);
	bR=Test();
	if(!bR)
		return FALSE;
	if(m_bCancel)
		return FALSE;
	m_cPro.SetPos(m_iCurMode*4+3);
	bR=Test();
	if(!bR)
		return FALSE;
	if(m_bCancel)
		return FALSE;
	m_cPro.SetPos(m_iCurMode*4+4);
	Sleep(100);
	if(g_bEnglish)
		strTemp="Complete Calibration!";
	else
		strTemp="完成定标,请保存!";
	CMainFrame::ShowNote(strTemp,TRUE,RGB(0,0,0));
	return TRUE;
}

void CDlgSpectrumCal::SetShowIcon(BOOL bNotTest)
{
	// 1 - Load the icon from the application's resources
	HICON hicon;
	if(!bNotTest)
	{
		hicon= AfxGetApp()->LoadIcon( IDR_MAINFRAME );
	}
	else
	{
		if(g_bEnglish)
			SetWindowText("Spectrum Calibration");
		else
			SetWindowText("光谱定标");
		hicon= AfxGetApp()->LoadIcon( IDI_SPECT_CAL);

		ASSERT( hicon != NULL );
	}

	// 2 - Associate the icon with the dialog box
	SetIcon( hicon, TRUE );
}

void CDlgSpectrumCal::OnSelchangeComboLamp() 
{
	// TODO: Add your control notification handler code here
	BOOL bR;
	bR=UpdateData(TRUE);
	if(!bR)
		return;

	if(m_iLampType == 0)
		return;

	int iType = 1;
	if(m_iCalPhType == 2)
		iType = 0;

	CString sTemp;
	m_cLamp.GetWindowText(sTemp);
	g_SPEC.GetYFStaLamp(g_strCurPath+"Lamp\\"+sTemp+".lamp", iType);
	sTemp.Format("%.2f",g_SPEC.m_fStaVol);
	m_cStaVol.SetWindowText(sTemp);
	sTemp.Format("%.3f",g_SPEC.m_fStaCurr);
	m_cStaCurr.SetWindowText(sTemp);
}

void CDlgSpectrumCal::OnSelchangeComboLampType() 
{
	// TODO: Add your control notification handler code here
	BOOL bR;
	bR=UpdateData(TRUE);
	if(!bR)
		return;

	if(m_iLampType == 0)
	{
		m_cLamp.EnableWindow(FALSE);
		m_cStaPh.EnableWindow(TRUE);
		m_cStaTc.EnableWindow(TRUE);
	}
	else
	{
		m_cLamp.EnableWindow(TRUE);
		m_cStaPh.EnableWindow(FALSE);
		m_cStaTc.EnableWindow(FALSE);

		int iType = 1;
		if(m_iCalPhType == 2)
			iType = 0;

		CString sTemp;
		m_cLamp.GetWindowText(sTemp);
		g_SPEC.GetYFStaLamp(g_strCurPath+"Lamp\\"+sTemp+".lamp", iType);
		sTemp.Format("%.2f",g_SPEC.m_fStaVol);
		m_cStaVol.SetWindowText(sTemp);
		sTemp.Format("%.3f",g_SPEC.m_fStaCurr);
		m_cStaCurr.SetWindowText(sTemp);
	}
}

BOOL CDlgSpectrumCal::GetLampName()
{
	CString sPathName;
	sPathName=g_strCurPath+"Lamp\\";
	m_strListCtrlFile.RemoveAll();
	CFileFind myFinder;
	CStringList myList;
	CString FileName;
	myList.AddTail(sPathName+"");
	CString sFileName;
	sFileName=sPathName+"Temp.dat";
	CStdioFile myFile(sFileName,CFile::modeCreate|CFile::modeWrite|CFile::typeText); //打开文件

	while (!myList.IsEmpty())
	{
		CString strTemp;
		FileName=myList.GetHead()+_T("\\*.LAMP");

		if (myFinder.FindFile(LPCTSTR(FileName)))
		{
			while (myFinder.FindNextFile())
			{
				if (myFinder.IsDots())
					continue;
				myFile.WriteString(Pro(myFinder.GetFilePath())+"\n");
				{
					strTemp=Pro(myFinder.GetFilePath());
					m_strListCtrlFile.Add(strTemp);
				}
				if(myFinder.IsDirectory())
					myList.AddTail(myFinder.GetFilePath());
			}
			myFile.WriteString(Pro(myFinder.GetFilePath())+"\n");
			{
				strTemp=Pro(myFinder.GetFilePath());
				m_strListCtrlFile.Add(strTemp);
			}
		}
		myList.RemoveHead();
	}
	if(m_strListCtrlFile.GetSize()==0)
		return FALSE;
	return TRUE;
}

CString CDlgSpectrumCal::Pro(CString sStr)
{
	int iP=0;
	int iN=0;
	iN=sStr.GetLength();
	for(int i=0;i<iN;i++)
	{
		iP=sStr.Find(".lamp\r",i);
	}
	sStr.Replace(g_strCurPath+"Lamp\\","");
	CString sTemp;
	sTemp=sStr;
	sTemp.Replace(".lamp","");
	return sTemp;
}
