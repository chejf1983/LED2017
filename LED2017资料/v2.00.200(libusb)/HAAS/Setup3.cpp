// Setup3.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "Setup3.h"
#include "Global_MySpec.h"
#include "My_iniFile.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetup3 property page
extern BOOL g_bEnglish;
extern float g_fSpect2;
extern float g_fSpect1;

IMPLEMENT_DYNCREATE(CSetup3, CPropertyPage)

CSetup3::CSetup3() : CPropertyPage(CSetup3::IDD)
{
	//{{AFX_DATA_INIT(CSetup3)
	m_iAutoTime2 = 0;
	m_iTestType  = 1;
	m_iBin       = 0;
	m_iMode      = 0;
	m_iLED       = -1;
	m_bAtt       = FALSE;
	m_iAtt       = 0;
	m_iLamp      = 0;
	m_iPEType    = 0;
	m_bPhoto     = FALSE;
	m_iTrigMode  = 0;
	m_bTrig      = FALSE;
	m_fDistance	 = 0.1f;
	m_fIntK		 = 1.0f;
	m_iSeleL	 = -1;
	m_iPulseNum  = 0;
	m_fPulseTime = 0.0f;
	m_fWL1 = 380.0f;
	m_fWL2 = 780.0f;
	m_iTestListCalSele = 0;
	m_bUseListCalSele = FALSE;
	m_iSigType = -1;
	//}}AFX_DATA_INIT
}
CSetup3::~CSetup3()
{
}

void CSetup3::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetup3)
	DDX_Control(pDX, IDC_CHECK_TRIG, m_cuseTrig);
	DDX_Control(pDX, IDC_COMBO_LIST_CAL_SELE, m_cTestListCalSele);
	DDX_Control(pDX, IDC_EDIT_WL2, m_cWL2);
	DDX_Control(pDX, IDC_EDIT_WL1, m_cWL1);
	DDX_Control(pDX, IDC_EDIT_PLUSE_TIME, m_cPulseTime);
	DDX_Control(pDX, IDC_EDIT_PLUSE_NUM, m_cPulseNum);
	DDX_Control(pDX, IDC_STATIC_P_S2, m_cPulseNumS);
	DDX_Control(pDX, IDC_STATIC_P_S, m_cPulseTimeS);
	DDX_Control(pDX, IDC_STATIC_L_SELE, m_cSeleLS);
	DDX_Control(pDX, IDC_COMBO_L_SELE, m_cSeleL);
	DDX_Control(pDX, IDC_STATIC_I_S3, m_cIS3);
	DDX_Control(pDX, IDC_EDIT_I_K, m_cIntK);
	DDX_Control(pDX, IDC_EDIT_DISTANCE, m_cDistance);
	DDX_Control(pDX, IDC_STATIC_I_S2, m_cIS2);
	DDX_Control(pDX, IDC_STATIC_I_S1, m_cIS1);
	DDX_Control(pDX, IDC_RADIO2, m_cTrigMode2);
	DDX_Control(pDX, IDC_STATIC_TRIG, m_cTrig);
	DDX_Control(pDX, IDC_RADIO1, m_cTrigMode1);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_cTestType);
	DDX_Control(pDX, IDC_STATIC_PE, m_cPES);
	DDX_Control(pDX, IDC_COMBO_PE, m_cPE);
	DDX_Control(pDX, IDC_COMBO_LAMP, m_cLamp);
	DDX_Control(pDX, IDC_CHECK_ATT, m_cAtt);
	DDX_Control(pDX, IDC_RADIO_ATT2, m_cAtt2);
	DDX_Control(pDX, IDC_STATIC_A1, m_cA1);
	DDX_Control(pDX, IDC_RADIO_ATT1, m_cAtt1);
	DDX_Control(pDX, IDC_STATIC_S1, m_cS1);
	DDX_Control(pDX, IDC_COMBO1, m_cMode);
	DDX_Control(pDX, IDC_COMBO_LED, m_cLED);
	DDX_Control(pDX, IDC_COMBO_BIN, m_cBin);
	DDX_Text(pDX, IDC_EDIT_AUTO_TIME2, m_iAutoTime2);
	DDV_MinMaxInt(pDX, m_iAutoTime2, 1000, 60000);
	DDX_CBIndex(pDX, IDC_COMBO_TYPE, m_iTestType);
	DDX_CBIndex(pDX, IDC_COMBO_BIN, m_iBin);
	DDX_CBIndex(pDX, IDC_COMBO1, m_iMode);
	DDX_CBIndex(pDX, IDC_COMBO_LED, m_iLED);
	DDX_Check(pDX, IDC_CHECK_ATT, m_bAtt);
	DDX_Radio(pDX, IDC_RADIO_ATT1, m_iAtt);
	DDX_CBIndex(pDX, IDC_COMBO_LAMP, m_iLamp);
	DDX_CBIndex(pDX, IDC_COMBO_PE, m_iPEType);
	DDX_Check(pDX, IDC_CHECK_FLUX_APP, m_bPhoto);
	DDX_Radio(pDX, IDC_RADIO1, m_iTrigMode);
	DDX_Check(pDX, IDC_CHECK_TRIG, m_bTrig);
	DDX_Text(pDX, IDC_EDIT_DISTANCE, m_fDistance);
	DDX_Text(pDX, IDC_EDIT_I_K, m_fIntK);
	DDX_CBIndex(pDX, IDC_COMBO_L_SELE, m_iSeleL);
	DDX_Text(pDX, IDC_EDIT_PLUSE_NUM, m_iPulseNum);
	DDX_Text(pDX, IDC_EDIT_PLUSE_TIME, m_fPulseTime);
	DDX_Text(pDX, IDC_EDIT_WL1, m_fWL1);
	DDX_Text(pDX, IDC_EDIT_WL2, m_fWL2);
	DDX_CBIndex(pDX, IDC_COMBO_LIST_CAL_SELE, m_iTestListCalSele);
	DDX_Check(pDX, IDC_CHECK_LIST_CAL, m_bUseListCalSele);
	DDX_CBIndex(pDX, IDC_COMBO_SIG_TYPE, m_iSigType);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSetup3, CPropertyPage)
	//{{AFX_MSG_MAP(CSetup3)
	ON_CBN_SELCHANGE(IDC_COMBO_LED, OnSelchangeComboLed)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_BN_CLICKED(IDC_CHECK_TYPE, OnCheckType)
	ON_BN_CLICKED(IDC_CHECK_ATT, OnCheckAtt)
	ON_BN_CLICKED(IDC_RADIO_ATT1, OnRadioAtt1)
	ON_BN_CLICKED(IDC_RADIO_ATT2, OnRadioAtt2)
	ON_CBN_SELCHANGE(IDC_COMBO_LAMP, OnSelchangeComboLamp)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_CHECK_TRIG, OnCheckTrig)
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE, OnSelchangeComboType)
	ON_BN_CLICKED(IDC_CHECK_LIST_CAL, OnCheckListCal)
	ON_CBN_SELCHANGE(IDC_COMBO_SIG_TYPE, OnSelchangeComboSigType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetup3 message handlers

extern BOOL g_bOpenMulitCalSpectrum;

BOOL CSetup3::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here

	GetDlgItem(IDC_CHECK_LIST_CAL)->ShowWindow(g_bOpenMulitCalSpectrum == TRUE);
	GetDlgItem(IDC_STATIC_LIST_S)->ShowWindow(g_bOpenMulitCalSpectrum == TRUE);
	GetDlgItem(IDC_COMBO_LIST_CAL_SELE)->ShowWindow(g_bOpenMulitCalSpectrum == TRUE);

	if(1)
	{
		int iSave = m_iTestListCalSele;
		CString strTemp;
		m_cTestListCalSele.ResetContent();
		m_cTestListCalSele.AddString("000: Def");
		for(int i = 0; i < 100; i++)
		{
			strTemp.Format("%03d", i + 1);
			m_cTestListCalSele.InsertString(i + 1, strTemp);
		}
		
		m_cTestListCalSele.SetCurSel(iSave);

		m_cTestListCalSele.EnableWindow(m_bUseListCalSele);
	}

	CString strTemp;
	int iSaveSeleL =  m_iSeleL;
	m_cSeleL.ResetContent();
	for(int j=0;j<g_SPEC.m_iViewL_Num;j++)
	{
		if(g_bEnglish)
			strTemp.Format("%s Deg",g_SPEC.m_strViewL_Name[j]);
		else
			strTemp.Format("%s 度",g_SPEC.m_strViewL_Name[j]);
		m_cSeleL.InsertString(j,strTemp);
	}
	m_iSeleL = iSaveSeleL;

	//定标模式
	m_cMode.ResetContent();
	if(g_SPEC.T_SPECT1==200.0f&&g_SPEC.T_SPECT2==400.0f)
	{
		if(g_bEnglish)
		{
			m_cMode.InsertString(0,"Fast");
		}
		else
		{
			m_cMode.InsertString(0,"快速测试");
		}
		m_cMode.EnableWindow(FALSE);
		g_SPEC.m_iMode=0;
	}
	else
	{
		if(g_bEnglish)
		{
			if(g_SPEC.m_bCal)
			{
				m_cMode.InsertString(0,"Fast");
				m_cMode.InsertString(1,"Precise");
			}
			else
			{
				m_cMode.InsertString(0,"Fast");
				m_cMode.InsertString(1,"Precise");
				m_cMode.InsertString(2,"Typical");
			}
		}
		else
		{
			if(g_SPEC.m_bCal)
			{
				m_cMode.InsertString(0,"快速测试");
				m_cMode.InsertString(1,"精确测试");
			}
			else
			{
				m_cMode.InsertString(0,"快速测试");
				m_cMode.InsertString(1,"精确测试");
				m_cMode.InsertString(2,"典型测试");
			}
		}
	}

	if(g_SPEC.m_bCal&&g_SPEC.m_iMode>1)
		g_SPEC.m_iMode=0;

	//
	m_cBin.ResetContent();
	if(g_bEnglish)
	{
		if(g_SPEC.m_Have_iBin==1)
		{
			m_cBin.InsertString(0,"01(High)");
		}
		if(g_SPEC.m_Have_iBin==2)
		{
			m_cBin.InsertString(0,"01(High)");
			m_cBin.InsertString(1,"02(Low)");
		}
		if(g_SPEC.m_Have_iBin==3)
		{
			m_cBin.InsertString(0,"01(High)");
			m_cBin.InsertString(1,"02");
			m_cBin.InsertString(2,"03(Low)");
		}
		if(g_SPEC.m_Have_iBin==4)
		{
			m_cBin.InsertString(0,"01(High)");
			m_cBin.InsertString(1,"02");
			m_cBin.InsertString(2,"03");
			m_cBin.InsertString(2,"04(Low)");
		}
	}
	else
	{
		CString strTemp;
		for(int i=0;i<g_SPEC.m_Have_iBin;i++)
		{
			strTemp.Format("%02d",i+1);
			if(i==0)
				m_cBin.InsertString(i,strTemp+"(高)");
			else if(i==(g_SPEC.m_Have_iBin-1))
				m_cBin.InsertString(i,strTemp+"(低)");
			else
				m_cBin.InsertString(i,strTemp);
		}
	}
	m_iBin=g_SPEC.m_iBin;
	UpdateData(FALSE);
	OnSelchangeComboType();
	OnSelchangeCombo1();
	int iN=g_doData.m_sData.m_listLamp.GetSize();
	for(int i=0;i<iN;i++)
	{
		m_cLED.InsertString(i,g_doData.m_sData.m_listLamp[i]->m_strName);
	}

	if(m_iMode==0)
	{
		m_cAtt.EnableWindow(TRUE);
		m_bAtt=g_SPEC.m_bAtt;
		m_iAtt=g_SPEC.m_iAtt;

		if(g_SPEC.T_SPECT2>780)//红外仪器没有深色片
		{
			m_cAtt1.EnableWindow(FALSE);
			m_cAtt2.EnableWindow(TRUE);
			m_iAtt=1;
		}
		else
		{
			m_cAtt1.EnableWindow(TRUE);
			m_cAtt2.EnableWindow(TRUE);
		}
	}
	else
	{
		m_cAtt.EnableWindow(FALSE);
		m_cAtt1.EnableWindow(FALSE);
		m_cAtt2.EnableWindow(FALSE);
		m_bAtt=FALSE;
	}

	UpdateData(FALSE);
	OnCheckAtt();

	//荧光粉
	OnSelchangeComboLamp();
	UpdateData(FALSE);

	if(m_iSigType == 0)
	{
		m_cuseTrig.EnableWindow(TRUE);
	}
	else
	{
		m_cuseTrig.EnableWindow(FALSE);
		m_bTrig = FALSE;
	}

	if(m_bTrig)
	{
		m_iMode=0;
		m_cMode.EnableWindow(FALSE);
		m_cTrig.EnableWindow(TRUE);
		m_cTrigMode1.EnableWindow(TRUE);
		m_cTrigMode2.EnableWindow(TRUE);

		m_cPulseTimeS.EnableWindow(TRUE);
		m_cPulseTime.EnableWindow(TRUE);
		m_cPulseNumS.EnableWindow(TRUE);
		m_cPulseNum.EnableWindow(TRUE);
	}
	else
	{
		if(!m_bAtt)
		{
			if(g_SPEC.T_SPECT1==200.0f&&g_SPEC.T_SPECT2==400.0f)
				m_cMode.EnableWindow(FALSE);
			else
				m_cMode.EnableWindow(TRUE);
		}
		m_cTrig.EnableWindow(FALSE);
		m_cTrigMode1.EnableWindow(FALSE);
		m_cTrigMode2.EnableWindow(FALSE);

		m_cPulseTimeS.EnableWindow(FALSE);
		m_cPulseTime.EnableWindow(FALSE);
		m_cPulseNumS.EnableWindow(FALSE);
		m_cPulseNum.EnableWindow(FALSE);
	}

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSetup3::OnSelchangeComboLed() 
{
	// TODO: Add your control notification handler code here
	
}

void CSetup3::OnSelchangeCombo1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if(m_iMode!=0)
		m_cAtt.EnableWindow(FALSE);
	else
		m_cAtt.EnableWindow(TRUE);

	if(m_iMode==2)
	{
		m_cLED.EnableWindow(TRUE);
		m_cS1.ShowWindow(TRUE);
	}
	else
	{
		m_cLED.EnableWindow(FALSE);
		m_cS1.ShowWindow(FALSE);
	}
	int iN=g_doData.m_sData.m_listLamp.GetSize();
	if(iN<=0)
		m_iLED=0;
	else
		m_iLED=g_SPEC.m_iParType;
	if(m_iMode==2&&iN<=0)
	{
		if(g_bEnglish)
			AfxMessageBox("Can't test before you have a typical calibration!");
		else
			AfxMessageBox("您还没有典型样品定标数据，不能开始典型测试!");
		m_iMode=0;
	}
	if(iN>0&&m_iLED<0)
		m_iLED=0;
	UpdateData(FALSE);
}

void CSetup3::OnCheckType() 
{
	// TODO: Add your control notification handler code here
	
}

void CSetup3::OnCheckAtt() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CCmdTarget::BeginWaitCursor();
	if(m_bAtt)
	{
	//	AfxMessageBox("注意: 使用衰减片请注意要求在当前选择的\n滤色片下进行一次光谱定标!");
		if(m_iMode!=0)
			m_iMode=0;
		m_cMode.EnableWindow(FALSE);
		m_cA1.EnableWindow(TRUE);
		m_cAtt2.EnableWindow(TRUE);

//		g_SPEC.m_HAAS.SetColor(2+m_iAtt); //滤色片深或浅
	}
	else
	{
		if(g_SPEC.T_SPECT1==200.0f&&g_SPEC.T_SPECT2==400.0f)
			m_cMode.EnableWindow(FALSE);
		else
			m_cMode.EnableWindow(TRUE);
		m_cA1.EnableWindow(FALSE);
		m_cAtt1.EnableWindow(FALSE);
		m_cAtt2.EnableWindow(FALSE);
//		g_SPEC.m_HAAS.SetColor(1); //色盘开
	}
	CCmdTarget::EndWaitCursor();
	g_SPEC.m_bAtt=m_bAtt;
	UpdateData(FALSE);
}

void CSetup3::OnRadioAtt1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CCmdTarget::BeginWaitCursor();
	g_SPEC.m_iAtt=m_iAtt;
//	g_SPEC.m_HAAS.SetColor(2+m_iAtt); //滤色片深或浅
	CCmdTarget::EndWaitCursor();
}

void CSetup3::OnRadioAtt2() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CCmdTarget::BeginWaitCursor();
	g_SPEC.m_iAtt=m_iAtt;
//	g_SPEC.m_HAAS.SetColor(2+m_iAtt); //滤色片深或浅
	CCmdTarget::EndWaitCursor();
}

void CSetup3::OnSelchangeComboLamp() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_iLamp==1)
	{
		m_cTestType.EnableWindow(FALSE);
		m_cPES.EnableWindow(TRUE);
		m_cPE.EnableWindow(TRUE);
	}
	else
	{
		m_cTestType.EnableWindow(TRUE);
		m_cPES.EnableWindow(FALSE);
		m_cPE.EnableWindow(FALSE);
	}
}

void CSetup3::OnRadio1() 
{
	// TODO: Add your control notification handler code here
}

void CSetup3::OnRadio2() 
{
	// TODO: Add your control notification handler code here
}

void CSetup3::OnCheckTrig() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_bTrig)
	{
		m_iMode=0;
		m_cMode.EnableWindow(FALSE);
		m_cTrig.EnableWindow(TRUE);
		m_cTrigMode1.EnableWindow(TRUE);
		if(g_SPEC.m_HAAS_iVer>2)
			m_cTrigMode2.EnableWindow(TRUE);

		m_cPulseTimeS.EnableWindow(TRUE);
		m_cPulseTime.EnableWindow(TRUE);
		m_cPulseNumS.EnableWindow(TRUE);
		m_cPulseNum.EnableWindow(TRUE);
	}
	else
	{
		if(!m_bAtt)
		{
			if(g_SPEC.T_SPECT1==200.0f&&g_SPEC.T_SPECT2==400.0f)
				m_cMode.EnableWindow(FALSE);
			else
				m_cMode.EnableWindow(TRUE);
		}
		m_cTrig.EnableWindow(FALSE);
		m_cTrigMode1.EnableWindow(FALSE);
		m_cTrigMode2.EnableWindow(FALSE);

		m_cPulseTimeS.EnableWindow(FALSE);
		m_cPulseTime.EnableWindow(FALSE);
		m_cPulseNumS.EnableWindow(FALSE);
		m_cPulseNum.EnableWindow(FALSE);
	}
	UpdateData(FALSE);
}

void CSetup3::OnSelchangeComboType() 
{
	// TODO: Add your control notification handler code here
	BOOL bR;
	bR=UpdateData(TRUE);
	if(!bR)
		return;
	if(m_iTestType!=3)
	{
		m_cIS1.EnableWindow(FALSE);
		m_cIS2.EnableWindow(FALSE);
		m_cIS3.EnableWindow(FALSE);
		m_cDistance.EnableWindow(FALSE);
		m_cIntK.EnableWindow(FALSE);
	}
	else
	{
		m_cIS1.EnableWindow(TRUE);
		m_cIS2.EnableWindow(TRUE);
		m_cIS3.EnableWindow(TRUE);
		m_cDistance.EnableWindow(TRUE);
		m_cIntK.EnableWindow(TRUE);
	}

	m_cSeleLS.EnableWindow(m_iTestType==4);
	m_cSeleL.EnableWindow(m_iTestType==4);
}

void CSetup3::OnCheckListCal() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_cTestListCalSele.EnableWindow(m_bUseListCalSele);

	if(m_bUseListCalSele == FALSE)
	{
		m_iTestListCalSele = 0;
	}

	UpdateData(FALSE);
}

void CSetup3::OnSelchangeComboSigType() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_iSigType == 0)
	{
		m_cuseTrig.EnableWindow(TRUE);
	}
	else
	{
		m_cuseTrig.EnableWindow(FALSE);
		m_bTrig = FALSE;
	}

	if(m_bTrig)
	{
		m_iMode=0;
		m_cMode.EnableWindow(FALSE);
		m_cTrig.EnableWindow(TRUE);
		m_cTrigMode1.EnableWindow(TRUE);
		if(g_SPEC.m_HAAS_iVer>2)
			m_cTrigMode2.EnableWindow(TRUE);
		
		m_cPulseTimeS.EnableWindow(TRUE);
		m_cPulseTime.EnableWindow(TRUE);
		m_cPulseNumS.EnableWindow(TRUE);
		m_cPulseNum.EnableWindow(TRUE);
	}
	else
	{
		if(!m_bAtt)
		{
			if(g_SPEC.T_SPECT1==200.0f&&g_SPEC.T_SPECT2==400.0f)
				m_cMode.EnableWindow(FALSE);
			else
				m_cMode.EnableWindow(TRUE);
		}
		m_cTrig.EnableWindow(FALSE);
		m_cTrigMode1.EnableWindow(FALSE);
		m_cTrigMode2.EnableWindow(FALSE);
		
		m_cPulseTimeS.EnableWindow(FALSE);
		m_cPulseTime.EnableWindow(FALSE);
		m_cPulseNumS.EnableWindow(FALSE);
		m_cPulseNum.EnableWindow(FALSE);
	}
}
