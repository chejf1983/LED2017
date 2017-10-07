// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "MySpec.h"

#include "MainFrm.h"
#include "Splash.h"
#include "ProcessData.h"

#include "SpectrumView.h"
#include "TenView.h"
#include "MySpecView.h"
#include "SPEC_PRO.h"

#include "DlgSpectrumCal.h"
#include "DlgSpectrumCalU.h"

#include "sheetothers.h"
#include "debug1.h"
#include "debug2.h"
#include "debug3.h"
#include "Debug4.h"  //调试4
#include "Debug5.h"
#include "Debug6.h"

#include "DebugLine.h"

#include "ExGetColorParaDLL.h"

#include "DlgFluxCal.h"
#include "LEDTypeCal.h"
#include "DlgCalAtt.h"

#include "SPEC_PRO.h"
#include "WYDlg.h"
#include "setup1.h"
#include "setup2.h"
#include "setup3.h"
#include "mysheet.h"
#include "WLCheck.h"
#include "ExWaitLampStableDLL.h"

#include "Note.h"

#include "Global_MySpec.h"

#include "DlgCalFlux.h"
#include "CalFluxList.h"

#include "DlgSelfPhK.h"

#include "DlgCalPLFlux.h"
#include "CalFluxPLList.h"

#include "DlgLEDClassEdit.h"
#include "DlgSelfPhK.h"

#include "DlgNewFluxCal.h"

#include "AccreditData.h"
#include "SpectraArsenal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame
extern BOOL g_bEnglish;
CString  g_strNote;
COLORREF g_NoteREF;
HWND     g_FrameWnd;

BOOL     g_bFunDebug;
BOOL     g_bRaShowNeg;//显示指数是否显示负数

BOOL     g_bPowerMod;
BOOL     g_bMoreGroup;
BOOL     g_bFluxMod;
BOOL     g_bModeSelf;
BOOL     g_bHaveUseHLK;
BOOL     g_bFluxSPMod;
int		 g_iLEDClass_Type;
int		 g_iTR80_or_90;
BOOL     g_bExDtr = FALSE;
extern float g_fSpect1;
extern float g_fSpect2;
extern BOOL g_bTest;
extern BOOL g_bHaveMode;

extern BOOL g_bHavePhoEff;

CString g_strListWhite;
CString g_strListLevel;
CString g_strListNewLevel;

CCalFluxList g_calFluxData;
int  g_iSeleCalFlux;

//光谱法多组光通量
BOOL g_bUseFluxPL;//使用多组系数
CCalFluxPLList g_CalFluxPLData;
int g_iSeleCalPLFlux;

BOOL g_bHaveFluxDec;
BOOL g_bHaveTMPDec;
BOOL g_bHaveCRI;

BOOL g_bOpenColorCorrectXY = FALSE;
BOOL g_bOpenMulitCalSpectrum = FALSE;
BOOL g_bUseExTestBox = FALSE;

BOOL g_bOpenWaitLamp = FALSE;
BOOL g_bOpenColorCorrect = FALSE;

BOOL g_bCorrectXY_mode1 = TRUE;
BOOL g_bCorrectXY_mode2 = FALSE;

/* 光通灯与色温灯分开定标 !!! 2012.2 */
BOOL g_Use_FluxLamp_SelfCal = FALSE;

#define PW_ON      "ON"        //

float g_fModSpect1;
BOOL g_bModeWL1;

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_COMMAND_EX(CG_ID_VIEW_MYTESTBAR1, OnBarCheck)
	ON_UPDATE_COMMAND_UI(CG_ID_VIEW_MYTESTBAR1, OnUpdateControlBarMenu)
	ON_COMMAND_EX(CG_ID_VIEW_MYTYPEBAR, OnBarCheck)
	ON_UPDATE_COMMAND_UI(CG_ID_VIEW_MYTYPEBAR, OnUpdateControlBarMenu)
	ON_COMMAND_EX(CG_ID_VIEW_MYNOTEBAR, OnBarCheck)
	ON_UPDATE_COMMAND_UI(CG_ID_VIEW_MYNOTEBAR, OnUpdateControlBarMenu)
	ON_COMMAND_EX(CG_ID_VIEW_MYTESTBAR, OnBarCheck)
	ON_UPDATE_COMMAND_UI(CG_ID_VIEW_MYTESTBAR, OnUpdateControlBarMenu)
	ON_COMMAND_EX(CG_ID_VIEW_MYLEDBAR, OnBarCheck)
	ON_UPDATE_COMMAND_UI(CG_ID_VIEW_MYLEDBAR, OnUpdateControlBarMenu)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_MODE, OnUpdateMode)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_CAL, OnUpdateCalList)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_COMMAND(ID_VIEW_SETBAR, OnViewSetbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SETBAR, OnUpdateViewSetbar)
	ON_WM_GETMINMAXINFO()
	ON_MESSAGE(WM_SHOW_NOTE,OnWMShowNote)
	ON_COMMAND(ID_DEBUG, OnDebug)
	ON_UPDATE_COMMAND_UI(ID_DEBUG, OnUpdateDebug)
	ON_COMMAND(ID_SPECTRUM_CAL, OnSpectrumCal)
	ON_UPDATE_COMMAND_UI(ID_SPECTRUM_CAL, OnUpdateSpectrumCal)
	ON_COMMAND(ID_SET_WY, OnSetWy)
	ON_UPDATE_COMMAND_UI(ID_SET_WY, OnUpdateSetWy)
	ON_BN_CLICKED(IDC_CHECK_AUTO, OnCheckAutoTime)
	ON_EN_CHANGE(IDC_EDIT_INT_TIME, OnChangeEditIntTime)
	ON_EN_CHANGE(IDC_EDIT_AVG_N, OnChangeEditAvgN)
	ON_COMMAND(ID_WL_CHECK, OnWlCheck)
	ON_UPDATE_COMMAND_UI(ID_WL_CHECK, OnUpdateWlCheck)
	ON_COMMAND(ID_DARK, OnDark)
	ON_UPDATE_COMMAND_UI(ID_DARK, OnUpdateDark)
	ON_COMMAND(ID_BUTTON_FLUX, OnButtonFlux)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_FLUX, OnUpdateButtonFlux)
	ON_COMMAND(ID_PARA, OnPara)
	ON_UPDATE_COMMAND_UI(ID_PARA, OnUpdatePara)
	ON_COMMAND(ID_CAL_FLUX, OnCalFlux)
	ON_UPDATE_COMMAND_UI(ID_CAL_FLUX, OnUpdateCalFlux)
	ON_COMMAND(ID_CAL_TYPE, OnCalType)
	ON_UPDATE_COMMAND_UI(ID_CAL_TYPE, OnUpdateCalType)
	ON_COMMAND(ID_TEST_UP, OnTestUp)
	ON_UPDATE_COMMAND_UI(ID_TEST_UP, OnUpdateTestUp)
	ON_COMMAND(ID_DEBUG_SOFT, OnDebugSoft)
	ON_UPDATE_COMMAND_UI(ID_DEBUG_SOFT, OnUpdateDebugSoft)
	ON_COMMAND(ID_EDIT_WHITE, OnEditWhite)
	ON_UPDATE_COMMAND_UI(ID_EDIT_WHITE, OnUpdateEditWhite)
	ON_COMMAND(ID_EDIT_LEVEL, OnEditLevel)
	ON_UPDATE_COMMAND_UI(ID_EDIT_LEVEL, OnUpdateEditLevel)
	ON_COMMAND(ID_SPECT_CAL_U, OnSpectCalU)
	ON_UPDATE_COMMAND_UI(ID_SPECT_CAL_U, OnUpdateSpectCalU)
	ON_WM_MEASUREITEM()
	ON_WM_INITMENUPOPUP()
	ON_WM_MENUCHAR()
	ON_COMMAND(ID_CAL_PL_FLUX, OnCalPlFlux)
	ON_UPDATE_COMMAND_UI(ID_CAL_PL_FLUX, OnUpdateCalPlFlux)
	ON_COMMAND(ID_POWER, OnPower)
	ON_UPDATE_COMMAND_UI(ID_POWER, OnUpdatePower)
	ON_COMMAND(ID_SELF_PH, OnSelfPh)
	ON_UPDATE_COMMAND_UI(ID_SELF_PH, OnUpdateSelfPh)
	ON_COMMAND(ID_GPIB_KEITHLEY_2420, OnGpibKeithley2420)
	ON_UPDATE_COMMAND_UI(ID_GPIB_KEITHLEY_2420, OnUpdateGpibKeithley2420)
	ON_COMMAND(ID_RS232_REMOTE_COMM, OnRs232RemoteComm)
	ON_UPDATE_COMMAND_UI(ID_RS232_REMOTE_COMM, OnUpdateRs232RemoteComm)
	ON_COMMAND(ID_WAIT_LAMP, OnWaitLamp)
	ON_UPDATE_COMMAND_UI(ID_WAIT_LAMP, OnUpdateWaitLamp)
	ON_WM_DESTROY()
	ON_COMMAND(ID_EXDTR, OnExdtr)
	ON_UPDATE_COMMAND_UI(ID_EXDTR, OnUpdateExdtr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAL,
	ID_INDICATOR_MODE,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

BOOL g_bDemo;

CProcessData g_doData;
CCSPEC_PRO g_SPEC;

BOOL	g_bHavePower;
BOOL    g_bManuP;
CString	g_strPowCom;
CString	g_strPowType;
//通讯模式选择
CString g_strHaasComm;

extern BOOL g_bUseHLK;
int g_iSeleMode;
BOOL g_bNotShowMode;
int g_iRange;	  //光度采样的档位
int g_iPerRange;  //光度采样的前一档位

//电源设置
int		g_iSouType;
CString	g_strSouComm;
BOOL	g_bAutoLamp;
int		g_iPerTime;	//预热时间
int		g_iSetType;
float	g_fSetVol;
float	g_fSetCurr;
int		g_iSetType2;
float	g_fSetVol2;
float	g_fSetCurr2;

BOOL  g_bPhoEffSetAuto;
float g_fSpectB1,g_fSpectB2,g_fSpectY1,g_fSpectY2;

BOOL CMainFrame::m_bEverySetColoCorrect = FALSE;
BOOL CMainFrame::m_bWaitLamp = FALSE;

CMainFrame::CMainFrame()
{
	m_iSetPassword1 = 0;
	m_iSetPassword2 = 0;

	BYTE haasMode = 0x01;
	BYTE ccdMode = 0x01;

	BYTE byte = (BYTE)((haasMode << 2) + ccdMode);

	m_iPerCur	= 0;
	g_iRange	= 0;
	g_iPerRange	= -1;

	CString strSection1  = "SeleMode1";
	CString strMode     = "Mode";
	CString strCOMM     = "COMM";
	CString strShow     = "SHOW RS232";
	
	g_iSeleMode			= AfxGetApp()->GetProfileInt(strSection1,strMode,0);
	g_strHaasComm		= AfxGetApp()->GetProfileString(strSection1,strCOMM,"COM1");
	g_bNotShowMode		= AfxGetApp()->GetProfileInt(strSection1,strShow,TRUE);

	CString strSection      = "MySpec Main";

	CString strSaveCY       = "CY2";
	CString strSetBar       = "SetBar";

	m_cyCur       = AfxGetApp()->GetProfileInt(strSection,strSaveCY,200);
	m_bShowCIEBar = AfxGetApp()->GetProfileInt(strSection,strSetBar,TRUE);

	g_SPEC.Set_Load(g_strCurPath+"cal\\set.dat");
	ReadPasswordFile(g_strCurPath + "set.pas");

			strSection      = "PowerSet";
	CString strHavePower    = "HavePower";
	CString strHaveManu     = "MANU";
	CString strPowType      = "PowType";
	CString strPowCom       = "PowCom";
	CString strSouType      = "SouType";
	CString strSouComm      = "SouComm";
	CString strAutoLamp     = "AutoLamp";
	CString strPerTime      = "PerTime";
	CString strSetType      = "SetType";
	CString strSetVol	    = "SetVol";
	CString strSetCurr      = "SetCurr";
	CString strSetType2     = "SetType2";
	CString strSetVol2	    = "SetVol2";
	CString strSetCurr2     = "SetCurr2";

	g_bHavePower = AfxGetApp()->GetProfileInt(strSection,strHavePower,FALSE);
	g_bManuP     = AfxGetApp()->GetProfileInt(strSection,strHaveManu,FALSE);
	g_strPowType = AfxGetApp()->GetProfileString(strSection,strPowType,"PM9805");
	g_strPowCom  = AfxGetApp()->GetProfileString(strSection,strPowCom,"COM1");
	g_iSouType   = AfxGetApp()->GetProfileInt(	 strSection,strSouType,2);
	g_strSouComm = AfxGetApp()->GetProfileString(strSection,strSouComm,"COM1");
	g_bAutoLamp  = AfxGetApp()->GetProfileInt(	 strSection,strAutoLamp,FALSE);
	g_iPerTime   = AfxGetApp()->GetProfileInt(	 strSection,strPerTime,100);
	g_iSetType   = AfxGetApp()->GetProfileInt(	 strSection,strSetType,1);

	CString sStr;
	sStr		 = AfxGetApp()->GetProfileString(strSection,strSetVol,"220");
	g_fSetVol	 = (float)atof(sStr);
	sStr		 = AfxGetApp()->GetProfileString(strSection,strSetCurr,"50");
	g_fSetCurr	 = (float)atof(sStr);

	g_iSetType2  = AfxGetApp()->GetProfileInt(	 strSection,strSetType2,1);

	sStr		 = AfxGetApp()->GetProfileString(strSection,strSetVol2,"0");
	g_fSetVol2	 = (float)atof(sStr);
	sStr		 = AfxGetApp()->GetProfileString(strSection,strSetCurr2,"0");
	g_fSetCurr2	 = (float)atof(sStr);

	g_SPEC.ReadInitData();
	g_SPEC.m_bPhoto = FALSE;

	CString sTemp;
	        strSection      = "WHITH PATH";
	CString strPathW        = "PathW";
	CString strPathL        = "Level";

	g_strListWhite			= g_strCurPath+"Class\\White_ANSI.WCL";
	sTemp					= g_strListWhite;
	g_strListWhite          = AfxGetApp()->GetProfileString(strSection,strPathW,sTemp);
	g_strListLevel			= g_strCurPath+"Class\\LED_LEVEL_1.sta";
	sTemp					= g_strListLevel;
	g_strListLevel          = AfxGetApp()->GetProfileString(strSection,strPathL,sTemp);

	CString strLEDClassType = "LEDClassType";
	g_strListNewLevel		= g_strCurPath+"Class\\New.NCL";
	sTemp					= g_strListNewLevel;
	g_strListNewLevel       = AfxGetApp()->GetProfileString(strSection,strLEDClassType,sTemp);

	CString strSeleCalFlux  = "SeleCalFlux";
	g_iSeleCalFlux			= AfxGetApp()->GetProfileInt(strSection,strSeleCalFlux,0);

	CString strUsePLFlux    = "UsePLFlux";
	CString strSelePLFlux   = "SelePLFlux";
	g_bUseFluxPL			= AfxGetApp()->GetProfileInt(strSection,strUsePLFlux,FALSE);
	g_iSeleCalPLFlux		= AfxGetApp()->GetProfileInt(strSection,strSelePLFlux,0);

	CString strModeFlux     = "ModeFlux";
	CString strModeFluxK    = "ModeFluxK";
	CString strModeFluxK2   = "ModeFluxK2";
	CString sTempK;
	sTempK					= AfxGetApp()->GetProfileString(strSection,strModeFluxK,"1.00");
	g_SPEC.m_fModeFluxK		= (float)atof(sTempK);
	sTempK					= AfxGetApp()->GetProfileString(strSection,strModeFluxK2,"1.00");
	g_SPEC.m_fModeSelfK		= (float)atof(sTempK);

		   strSection = "SHOW RS";
	CString strShowRS = "SHOW";
	g_bNotShowMode    = AfxGetApp()->GetProfileInt(strSection,strShowRS,TRUE);

	CString strSeleL  = "SeleL";
	g_SPEC.m_iSeleL   = AfxGetApp()->GetProfileInt(strSection,strSeleL,0);

		   strSection = "HLK";
	CString strUseHLK = "USE HLK";
	g_bUseHLK		  = AfxGetApp()->GetProfileInt(strSection,strUseHLK,0);

		strSection	= "PHO_EFF";
	CString strAuto = "Auto";	
	CString strB1	= "B1";
	CString strB2	= "B2";
	CString strY1	= "Y1";
	CString strY2	= "Y2";

	g_bPhoEffSetAuto = AfxGetApp()->GetProfileInt(strSection,strAuto,TRUE);
	sStr		 = AfxGetApp()->GetProfileString(strSection,strB1,"380");
	g_fSpectB1	 = (float)atof(sStr);
	sStr		 = AfxGetApp()->GetProfileString(strSection,strB2,"500");
	g_fSpectB2	 = (float)atof(sStr);
	sStr		 = AfxGetApp()->GetProfileString(strSection,strY1,"500");
	g_fSpectY1	 = (float)atof(sStr);
	sStr		 = AfxGetApp()->GetProfileString(strSection,strY2,"780");
	g_fSpectY2	 = (float)atof(sStr);

	CString strDateType = "DateType";
	g_SPEC.m_iDateType	= AfxGetApp()->GetProfileInt(strSection, strDateType, 1);

	CString strPrintPh_		= "PrintPh_";
	CSpectData::m_bPrintPh_ = AfxGetApp()->GetProfileInt(strSection, strPrintPh_, FALSE);

	CString strListCalSele		= "ListCalSele";
	g_SPEC.m_iTestListCalSele	= AfxGetApp()->GetProfileInt(strSection, strListCalSele, 0);

	CString strUseListCal		= "UseListCal";
	g_SPEC.m_bUseListCalSele	= AfxGetApp()->GetProfileInt(strSection, strUseListCal, FALSE);

	CString strUseColorCorrect	= "UseColorCorrect";
	g_SPEC.m_bUseColorCorrect	= AfxGetApp()->GetProfileInt(strSection, strUseColorCorrect, FALSE);

	CString strNewEveryCorrect	= "NewEveryCorrect";
	CMainFrame::m_bEverySetColoCorrect = AfxGetApp()->GetProfileInt(strSection, strNewEveryCorrect, FALSE);

	CString strUseStableLamp	= "UseStableLamp";
	CMainFrame::m_bWaitLamp		= AfxGetApp()->GetProfileInt(strSection, strUseStableLamp, FALSE);


	CString str_m_bHaveLEDTMPCtrl	= _T("m_bHaveLEDTMPCtrl");
	CString str_m_fSetLEDTMP		= _T("m_fSetLEDTMP");
	CString str_m_strLEDTMPCom		= _T("m_strLEDTMPCom");
	
	CString strTemp;
	g_SPEC.m_bHaveLEDTMPCtrl	= AfxGetApp()->GetProfileInt(strSection, str_m_bHaveLEDTMPCtrl, 0);
	strTemp						= AfxGetApp()->GetProfileString(strSection, str_m_fSetLEDTMP, _T("30.0"));
	g_SPEC.m_fSetLEDTMP			= (float)atof(strTemp);
	g_SPEC.m_strLEDTMPCom		= AfxGetApp()->GetProfileString(strSection, str_m_strLEDTMPCom, _T("COM5"));

	CString strSigType = "SigType";
	g_SPEC.m_iSigType = AfxGetApp()->GetProfileInt(strSection, strSigType, 0);

	CString strGeWL1		= "GEWL1";
	CString strGeWL2		= "GEWL2";
	sStr		 = AfxGetApp()->GetProfileString(strSection,strGeWL1,"380");
	g_SPEC.m_fReGeWL1	 = (float)atof(sStr);
	sStr		 = AfxGetApp()->GetProfileString(strSection,strGeWL2,"780");
	g_SPEC.m_fReGeWL2	 = (float)atof(sStr);

	if(!g_SPEC.m_bUseListCalSele)
	{
		g_SPEC.m_iTestListCalSele = 0;
	}

//	int iHaasSetType;
//	CString strName;
//	CString strDLLVer;
//	HAAS_GetTypeNameStr(iHaasSetType, strName, strDLLVer);
}

CMainFrame::~CMainFrame()
{
	CString strSection1  = "SeleMode1";
	CString strMode     = "Mode";
	CString strCOMM     = "COMM";
	CString strShow     = "SHOW RS232";
	
	AfxGetApp()->WriteProfileInt(strSection1,strMode,g_iSeleMode);
	AfxGetApp()->WriteProfileString(strSection1,strCOMM,g_strHaasComm);
	AfxGetApp()->WriteProfileInt(strSection1,strShow,g_bNotShowMode);

	CString strSection      = "MySpec Main";

	CString strSaveCY       = "CY2";
	CString strSetBar       = "SetBar";

	m_wndSplitter1.GetRowInfo( 0, m_cyCur, m_cyMin );
	AfxGetApp()->WriteProfileInt(strSection,strSaveCY,m_cyCur);
	AfxGetApp()->WriteProfileInt(strSection,strSetBar,m_bShowCIEBar);
	g_SPEC.Set_Save(g_strCurPath+"cal\\set.dat");

			strSection      = "PowerSet";
	CString strHavePower    = "HavePower";
	CString strHaveManu     = "MANU";
	CString strPowType      = "PowType";
	CString strPowCom       = "PowCom";
	CString strSouType      = "SouType";
	CString strSouComm      = "SouComm";
	CString strAutoLamp     = "AutoLamp";
	CString strPerTime      = "PerTime";
	CString strSetType      = "SetType";
	CString strSetVol	    = "SetVol";
	CString strSetCurr      = "SetCurr";

	CString strSetType2     = "SetType2";
	CString strSetVol2	    = "SetVol2";
	CString strSetCurr2     = "SetCurr2";

	AfxGetApp()->WriteProfileInt(strSection,strHavePower,	g_bHavePower);
	AfxGetApp()->WriteProfileInt(strSection,strHaveManu,	g_bManuP);
	AfxGetApp()->WriteProfileString(strSection,strPowType,	g_strPowType);
	AfxGetApp()->WriteProfileString(strSection,strPowCom,	g_strPowCom);
	AfxGetApp()->WriteProfileInt(	strSection,strSouType,	g_iSouType);
	AfxGetApp()->WriteProfileString(strSection,strSouComm,	g_strSouComm);
	AfxGetApp()->WriteProfileInt(	strSection,strAutoLamp,	g_bAutoLamp);
	AfxGetApp()->WriteProfileInt(	strSection,strPerTime,  g_iPerTime);
	AfxGetApp()->WriteProfileInt(	strSection,strSetType,  g_iSetType);
	CString sStr;
	sStr.Format("%f",g_fSetVol);
	AfxGetApp()->WriteProfileString(strSection,strSetVol,sStr);
	sStr.Format("%f",g_fSetCurr);
	AfxGetApp()->WriteProfileString(strSection,strSetCurr,sStr);

	AfxGetApp()->WriteProfileInt(	strSection,strSetType2, g_iSetType2);
	sStr.Format("%f",g_fSetVol2);
	AfxGetApp()->WriteProfileString(strSection,strSetVol2,sStr);
	sStr.Format("%f",g_fSetCurr2);
	AfxGetApp()->WriteProfileString(strSection,strSetCurr2,sStr);
	
	        strSection      = "WHITH PATH";
	CString strPathW        = "PathW";
	CString strPathL        = "Level";
	AfxGetApp()->WriteProfileString(strSection,strPathW,g_strListWhite);
	AfxGetApp()->WriteProfileString(strSection,strPathL,g_strListLevel);

	CString strLEDClassType = "LEDClassType";
	AfxGetApp()->WriteProfileString(strSection,strLEDClassType,g_strListNewLevel);

	CString strSeleCalFlux  = "SeleCalFlux";
	AfxGetApp()->WriteProfileInt(strSection,strSeleCalFlux,g_iSeleCalFlux);

	int iHave;
	iHave = g_CalFluxPLData.m_calData.GetSize();
	if(iHave <= 0)
	{
		g_bUseFluxPL = FALSE;
	}

	if(g_iSeleCalPLFlux >= iHave || g_iSeleCalPLFlux < 0)
	{
		g_iSeleCalPLFlux = 0;
	}

	CString strUsePLFlux    = "UsePLFlux";
	CString strSelePLFlux   = "SelePLFlux";
	AfxGetApp()->WriteProfileInt(strSection,strUsePLFlux,g_bUseFluxPL);
	AfxGetApp()->WriteProfileInt(strSection,strSelePLFlux,g_iSeleCalPLFlux);


	CString strModeFlux     = "ModeFlux";
	CString strModeFluxK    = "ModeFluxK";
	CString strModeFluxK2   = "ModeFluxK2";
	CString sTempK;
	sTempK.Format("%f",g_SPEC.m_fModeFluxK);
	AfxGetApp()->WriteProfileString(strSection,strModeFluxK,sTempK);
	sTempK.Format("%f",g_SPEC.m_fModeSelfK);
	AfxGetApp()->WriteProfileString(strSection,strModeFluxK2,sTempK);

		   strSection = "SHOW RS";
	CString strShowRS = "SHOW";
	AfxGetApp()->WriteProfileInt(strSection,strShowRS,g_bNotShowMode);

	CString strSeleL    = "SeleL";
	AfxGetApp()->WriteProfileInt(strSection,strSeleL,g_SPEC.m_iSeleL);

		   strSection = "HLK";
	CString strUseHLK = "USE HLK";
	AfxGetApp()->WriteProfileInt(strSection,strUseHLK,g_bUseHLK);

		strSection	= "PHO_EFF";
	CString strAuto = "Auto";	
	CString strB1	= "B1";
	CString strB2	= "B2";
	CString strY1	= "Y1";
	CString strY2	= "Y2";
	
	AfxGetApp()->WriteProfileInt(strSection,strAuto,g_bPhoEffSetAuto);
	sStr.Format("%f",g_fSpectB1);
	AfxGetApp()->WriteProfileString(strSection,strB1,sStr);
	sStr.Format("%f",g_fSpectB2);
	AfxGetApp()->WriteProfileString(strSection,strB2,sStr);
	sStr.Format("%f",g_fSpectY1);
	AfxGetApp()->WriteProfileString(strSection,strY1,sStr);
	sStr.Format("%f",g_fSpectY2);
	AfxGetApp()->WriteProfileString(strSection,strY2,sStr);

// 	CString strPathName;
// 	strPathName=g_strCurPath;
// 	strPathName=strPathName+"cal\\Patt.sta";
// 	g_doData.m_sData.SAVE(strPathName);

	// 保存视场角度
	g_SPEC.ViewL_Save(g_strCurPath+"CAL\\AngleView.dat");

	CString strDateType = "DateType";
	AfxGetApp()->WriteProfileInt(strSection, strDateType, g_SPEC.m_iDateType);

	CString strPrintPh_ = "PrintPh_";
	AfxGetApp()->WriteProfileInt(strSection, strPrintPh_, CSpectData::m_bPrintPh_);

	CString strListCalSele = "ListCalSele";
	AfxGetApp()->WriteProfileInt(strSection, strListCalSele, g_SPEC.m_iTestListCalSele);

	CString strUseListCal = "UseListCal";
	AfxGetApp()->WriteProfileInt(strSection, strUseListCal, g_SPEC.m_bUseListCalSele);

	CString strUseColorCorrect = "UseColorCorrect";
	AfxGetApp()->WriteProfileInt(strSection, strUseColorCorrect, g_SPEC.m_bUseColorCorrect);

	CString strNewEveryCorrect = "NewEveryCorrect";
	AfxGetApp()->WriteProfileInt(strSection, strNewEveryCorrect, CMainFrame::m_bEverySetColoCorrect);

	CString strUseStableLamp = "UseStableLamp";
	AfxGetApp()->WriteProfileInt(strSection, strUseStableLamp, CMainFrame::m_bWaitLamp);

	CString str_m_bHaveLEDTMPCtrl = _T("m_bHaveLEDTMPCtrl");
	CString str_m_fSetLEDTMP = _T("m_fSetLEDTMP");
	CString str_m_strLEDTMPCom = _T("m_strLEDTMPCom");

	CString strTemp;
	AfxGetApp()->WriteProfileInt(strSection, str_m_bHaveLEDTMPCtrl, g_SPEC.m_bHaveLEDTMPCtrl);
	strTemp.Format(_T("%g"), g_SPEC.m_fSetLEDTMP);
	AfxGetApp()->WriteProfileString(strSection, str_m_fSetLEDTMP, strTemp);
	AfxGetApp()->WriteProfileString(strSection, str_m_strLEDTMPCom, g_SPEC.m_strLEDTMPCom);

	CString strSigType = "SigType";
	AfxGetApp()->WriteProfileInt(strSection, strSigType,g_SPEC.m_iSigType);

	CString strGeWL1		= "GEWL1";
	CString strGeWL2		= "GEWL2";
	sStr.Format("%f",g_SPEC.m_fReGeWL1);
	AfxGetApp()->WriteProfileString(strSection,strGeWL1,sStr);
	sStr.Format("%f",g_SPEC.m_fReGeWL2);
	AfxGetApp()->WriteProfileString(strSection,strGeWL2,sStr);

	SA_CloseSpectrometers();
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
//	if(g_SPEC.m_iSetPassword1 != m_iSetPassword1 || g_SPEC.m_iSetPassword2 != m_iSetPassword2)
//		AfxBeginThread(threadConnectManager, this);

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		/*| CBRS_GRIPPER*/ | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	m_wndToolBar.SetWindowText("Spect");
	m_wndToolBar.SetButtonText(0,"新建");
	m_wndToolBar.SetButtonText(1,"打开");
	m_wndToolBar.SetButtonText(2,"保存");
	m_wndToolBar.SetButtonText(4,"测试");
	m_wndToolBar.SetButtonText(6,"连续测试");
	m_wndToolBar.SetButtonText(7,"停止测试");
	m_wndToolBar.SetButtonText(9,"删除");
	m_wndToolBar.SetButtonText(11,"暗电流测试");
	m_wndToolBar.SetButtonText(13,"光谱定标");
	m_wndToolBar.SetButtonText(15,"全选/反选");
	m_wndToolBar.SetButtonText(17,"导出数据");
	m_wndToolBar.SetButtonText(18,"导出光谱");
	m_wndToolBar.SetButtonText(19,"打印预览");
	m_wndToolBar.SetButtonText(20,"关于");
	/////////////调整工具条/////////////////
	CRect rc(10, 0, 10, 10);
	CSize sizeMax(0, 0);
	CToolBarCtrl& bar = m_wndToolBar.GetToolBarCtrl();
	int im=bar.GetButtonCount();
	
	for (int nIndex = bar.GetButtonCount() - 1; nIndex >= 0; nIndex--)
	{
		bar.GetItemRect(nIndex, rc);
		
		rc.NormalizeRect();
		sizeMax.cx = __max(rc.Size().cx, sizeMax.cx);
		sizeMax.cy = __max(rc.Size().cy, sizeMax.cy);
	}
	m_wndToolBar.SetSizes(sizeMax, CSize(16,15));
	

	//保存WND
	g_FrameWnd=m_hWnd;

	//分割条
	int cyCur;
	m_wndSplitter1.GetRowInfo( 0, cyCur, m_cyMin );
	m_wndSplitter1.SetRowInfo( 0, m_cyCur, m_cyMin );
	m_wndSplitter1.RecalcLayout();

	int iPerSeleMode = g_iSeleMode;
	
	InitSystem();

	BOOL bR;
	bR = g_SPEC.SPEC_Init();

	m_hMenuDefault = NewDefaultMenu();
	OnUpdateFrameMenu(m_hMenuDefault);


	CMenu *pMenu;
	pMenu=GetMenu();
	if(!g_bFunDebug)
	{
		pMenu->RemoveMenu(ID_SPECT_CAL_U, MF_BYCOMMAND);
		pMenu->RemoveMenu(ID_DEBUG, MF_BYCOMMAND);
		pMenu->RemoveMenu(ID_DEBUG_SOFT, MF_BYCOMMAND);
		pMenu->RemoveMenu(ID_CAL_ATT_K, MF_BYCOMMAND);
		pMenu->RemoveMenu(ID_EXPORT_LAMP_DAT, MF_BYCOMMAND);
	}

	if(g_bFunDebug&&g_SPEC.T_SPECT1 > 300)
	{
		pMenu->RemoveMenu(ID_SPECT_CAL_U, MF_BYCOMMAND);
	}

	if(!g_bPowerMod)
	{
		pMenu->RemoveMenu(ID_POWER, MF_BYCOMMAND);
	}

	if(!g_bHaveUseHLK)
	{
		pMenu->RemoveMenu(ID_USE_H_L_K, MF_BYCOMMAND);
	}

	if(!g_bFluxSPMod)
	{
		pMenu->RemoveMenu(ID_CAL_PL_FLUX, MF_BYCOMMAND);
	}

	if(!g_bModeSelf)
	{
		pMenu->RemoveMenu(ID_SELF_PH, MF_BYCOMMAND);
	}

	if(1)
	{
		FILE *fp;
		if((fp = fopen(g_strCurPath + "Cal\\BWCheck.dat","rt")) == 0)
		{
			pMenu->RemoveMenu(ID_CHECK_BW, MF_BYCOMMAND);
		}
	}

	//初始化
	InitBar();
	//初始化	
	InitTestBar();
	//初始化
	InitNoteBar();


	char szWorkPath[256];
	sprintf(szWorkPath, "%s", g_strCurPath);

// 	CString strPathName;
// 	strPathName=g_strCurPath;
// 	strPathName=strPathName+"cal\\Patt.sta";
// 	g_doData.m_sData.OPEN(strPathName);

	// 读取光通量多组定标文件
// 	g_calFluxData.F_Load(g_strCurPath+"Cal\\Flux_multi.cal");
// 	g_CalFluxPLData.F_Load(g_strCurPath+"Cal\\PLFlux.cal");


	// CG: The following line was added by the Splash Screen component.
	if(!g_bEnglish)
	{
		CSplashWnd::ShowSplashScreen(this);
		Sleep(500);
	}

//	g_SPEC.ReadData(g_strCurPath+"1.txt");
	SetTimer(11,100,NULL);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (!m_wndSplitter1.CreateStatic(this, 2, 1))
		return FALSE;

	if (!m_wndSplitter1.CreateView(0, 0, RUNTIME_CLASS(CSpectrumView), CSize(250,250), pContext))
	{
		m_wndSplitter1.DestroyWindow();
		return FALSE;
	}

	if (!m_wndSplitter1.CreateView(1, 0, RUNTIME_CLASS(CMySpecView), CSize(200, 300), pContext))
	{
		m_wndSplitter1.DestroyWindow();
		return FALSE;
	}

	return TRUE;
}

void CMainFrame::DockControlBarLeftOf(CToolBar *Bar, CToolBar *LeftOf)
{
	CRect rect;
	DWORD dw;
	UINT n;

	// get MFC to adjust the dimensions of all docked ToolBars
	// so that GetWindowRect will be accurate
	RecalcLayout();
	LeftOf->GetWindowRect(&rect);
	rect.OffsetRect(1,0);
	dw=LeftOf->GetBarStyle();
	n = 0;
	n = (dw&CBRS_ALIGN_TOP) ? AFX_IDW_DOCKBAR_TOP : n;
	n = (dw&CBRS_ALIGN_BOTTOM && n==0) ? AFX_IDW_DOCKBAR_BOTTOM : n;
	n = (dw&CBRS_ALIGN_LEFT && n==0) ? AFX_IDW_DOCKBAR_LEFT : n;
	n = (dw&CBRS_ALIGN_RIGHT && n==0) ? AFX_IDW_DOCKBAR_RIGHT : n;

	// When we take the default parameters on rect, DockControlBar will dock
	// each Toolbar on a seperate line.  By calculating a rectangle, we in effect
	// are simulating a Toolbar being dragged to that location and docked.
	DockControlBar(Bar,n,&rect);
}

void CMainFrame::ShowNote(CString strNote, BOOL bSet, COLORREF ref)
{
	//可以设置色彩的NOTE提示用
	if(bSet)
		g_NoteREF=ref;
	else
		g_NoteREF=RGB(0,0,0);
	g_strNote=strNote;
	::PostMessage(g_FrameWnd,WM_SHOW_NOTE,0,0);
}

void CMainFrame::OnWMShowNote(UINT wParam, LONG lParam)
{
	//提示信息消息
	CStatic *pStatic;

	pStatic=(CStatic *)m_wndMyNoteBar.GetDlgItem(IDC_NOTE);
	pStatic->SetWindowText(g_strNote);

	m_cNote.SetTextColor(g_NoteREF);
}

void CMainFrame::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent==11)
	{
		KillTimer(11);
		//远方标志
		// Add an indicator, with width, ..
		m_wndStatusBar.AddIndicator(0,INDICATOR_LOGO);

		int idx = m_wndStatusBar.CommandToIndex(INDICATOR_LOGO);
		if(g_bEnglish)
			m_wndStatusBar.SetPaneWidth(idx,80);
		else
			m_wndStatusBar.SetPaneWidth(idx,150);
		m_wndStatusBar.SetPaneStyle(idx, m_wndStatusBar.GetPaneStyle(idx) | SBPS_NOBORDERS );

		// Create a log pane window, and append it to status bar
		MPCLogoPane * pLogo = new MPCLogoPane;
		if(g_bEnglish)
			pLogo->Create("NAHON",WS_CHILD|WS_VISIBLE,&m_wndStatusBar,80);
		else
			pLogo->Create("纳宏光电 NAHON",WS_CHILD|WS_VISIBLE,&m_wndStatusBar,150);
		pLogo->SetLogoFont("Arial", 17);
		m_wndStatusBar.AddControl(pLogo,INDICATOR_LOGO);
	}
	
	if(nIDEvent == 112)
	{
		PostMessage(WM_QUIT,0,0);
	}
	CFrameWnd::OnTimer(nIDEvent);
}

void CMainFrame::OnViewSetbar() 
{
	// TODO: Add your command handler code here
// 	BOOL  bVisible=((m_wndBar1.GetStyle()&WS_VISIBLE)!=0);
// 	ShowControlBar(&m_wndBar1,!bVisible,FALSE);
// 	m_bShowCIEBar=!bVisible;
}

void CMainFrame::OnUpdateViewSetbar(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
// 	BOOL  bVisible=((m_wndBar1.GetStyle()&WS_VISIBLE)!=0);
// 	pCmdUI->SetCheck(bVisible);
}

void CMainFrame::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	// TODO: Add your message handler code here and/or call default
	lpMMI->ptMinTrackSize=CPoint(lpMMI->ptMaxSize.x*8/10,lpMMI->ptMaxSize.y*8/10);
	
	CFrameWnd::OnGetMinMaxInfo(lpMMI);
}

void CMainFrame::OnDebug() 
{
	// TODO: Add your command handler code here
	CString strT;
	if(g_bEnglish)
		strT="Debug";
	else
		strT="调试";

	CSheetOthers sheet(strT);

	CDebug1 dPage1;
	CDebug2 dPage2;
//	CDebug3 dPage3;
	CDebugLine dPage4;

	sheet.AddPage(&dPage1);
	sheet.AddPage(&dPage2);
	sheet.AddPage(&dPage4);
//	sheet.AddPage(&dPage3);

	dPage1.m_bCro=g_SPEC.m_bCro;
	sheet.DoModal();
	g_SPEC.m_bCro=dPage1.m_bCro;
}

void CMainFrame::OnUpdateDebug(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!g_bTest);
}

void CMainFrame::OnSpectrumCal() 
{
	// TODO: Add your command handler code here

	// huyubing
	int iTemp	= g_SPEC.m_iTestType;
	int iTemp1	= g_SPEC.m_iLamp;

	if(1)//g_SPEC.m_iMode!=2)
	{
		CDlgSpectrumCal dlg;
		dlg.DoModal();
	}
	else
	{
		CLEDTypeCal dlg;
		dlg.DoModal();
	}

	// huyubing
	CMySpecDoc* pDoc = (CMySpecDoc*)GetActiveDocument();
	if((g_SPEC.m_iTestType != iTemp || g_SPEC.m_iLamp != iTemp1) && pDoc->m_ledData.m_listData.GetSize() > 0)
	{
		g_SPEC.m_iTestType	= iTemp;
		g_SPEC.m_iLamp		= iTemp1;
		if(g_bEnglish)
		{
			AfxMessageBox("can not modify select,pleae new a file and select!",MB_ICONINFORMATION);
		}
		else
		{
			AfxMessageBox("你只能在空文档时,才能修改光度测量类型及光源类型!\n以确保同个文件中测试参数类型一致!",MB_ICONINFORMATION);
		}
		return;
	}
	else
	{
		if(g_SPEC.m_iTestType == 1 || g_SPEC.m_iTestType == 0)
		{
			pDoc->m_ledData.m_iPhType = PH_F;
		}
		if(g_SPEC.m_iTestType == 2)
		{
			pDoc->m_ledData.m_iPhType = PH_E;
		}
		if(g_SPEC.m_iTestType == 3)
		{
			pDoc->m_ledData.m_iPhType = PH_I;
		}
		if(g_SPEC.m_iTestType == 4)
		{
			pDoc->m_ledData.m_iPhType = PH_L;
		}
		if(pDoc->m_ledData.m_listData.GetSize() <= 0)
		{
			::PostMessage(g_MainWnd,WM_RE_HEAD,0,0);
		}
	}
}

void CMainFrame::OnUpdateSpectrumCal(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!g_bTest);
}

void CMainFrame::OnSpectCalU() 
{
	// TODO: Add your command handler code here
	CDlgSpectrumCalU dlg;
	dlg.DoModal();
}

void CMainFrame::OnUpdateSpectCalU(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!g_bTest);
}

void CMainFrame::OnSetWy() 
{
	// TODO: Add your command handler code here
	CWYDlg dlg;
	dlg.DoModal();
}

void CMainFrame::OnUpdateSetWy(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!g_bTest);
}

void CMainFrame::SetTreeParameter(int iCur, CTreeCtrl &m_cTree, CLED300Data &data,int iPhType)
{
	m_cTree.ShowWindow(SW_HIDE);
	CSpectData *sp = &data.m_spData;
	if(iCur == m_iPerCur && m_iPerCur != 0 && !g_bHaveMode)
	{
		if(!data.m_spData.m_bHaveData)
		{
			m_cTree.DeleteAllItems();
		}
		m_cTree.ShowWindow(SW_SHOW);
		return;
	}

	m_iPerCur = iCur;
	m_cTree.DeleteAllItems();
	if(!data.m_spData.m_bHaveData)
	{
		m_cTree.ShowWindow(SW_SHOW);
		return;
	}
	HTREEITEM hti2,hti3;

	CString sTemp;
	CString strTemp;
	if(g_bEnglish)
		hti2 = m_cTree.InsertItem(_T("Colorimetric Quantities"),5,5);
	else
		hti2 = m_cTree.InsertItem(_T("色度参数"),5,5);
	if(sp->m_bHaveColorPara)
	{
		sTemp.Format("x = %.4f,y = %.4f",sp->m_x,sp->m_y);
		m_cTree.InsertItem(sTemp,4,4, hti2);
		sTemp.Format("u'= %.4f,v'= %.4f",sp->m_u,sp->m_v);
		m_cTree.InsertItem(sTemp,4,4, hti2);
		if(g_bEnglish)
		{
			if(sp->m_fCCT>1000.0f&&sp->m_fCCT<100000.0f)
				sTemp.Format("CCT = %.0f K",sp->m_fCCT);
			else if(sp->m_fCCT<=1000.0f)
				sTemp.Format("CCT < 1000 K");
			else
				sTemp.Format("CCT >= 100000 K");
			m_cTree.InsertItem(sTemp,4,4, hti2);
			sTemp.Format("Prcp WaveLength = %.1f nm",sp->m_fMainlambda);
			m_cTree.InsertItem(sTemp,4,4, hti2);
			sTemp.Format("Purity = %.1f%%",sp->m_fPurity);
			m_cTree.InsertItem(sTemp,4,4, hti2);
		}
		else
		{
			if(sp->m_fCCT>1000.0f&&sp->m_fCCT<100000.0f)
				sTemp.Format("相关色温 CCT = %.0f K",sp->m_fCCT);
			else if(sp->m_fCCT<=1000.0f)
				sTemp.Format("相关色温 CCT < 1000 K");
			else
				sTemp.Format("相关色温 CCT >= 100000 K");
			m_cTree.InsertItem(sTemp,4,4, hti2);

			sTemp.Format("色差 Duv = %.4f",sp->m_fdc);
			m_cTree.InsertItem(sTemp,4,4, hti2);

			sTemp.Format("主波长 λd  = %.1f nm",sp->m_fMainlambda);
			m_cTree.InsertItem(sTemp,4,4, hti2);
			sTemp.Format("色纯度 Pur  = %.1f %%",sp->m_fPurity);
			m_cTree.InsertItem(sTemp,4,4, hti2);
		}
	}
	if(g_bEnglish)
	{
		sTemp.Format("Peak WaveL = %.1f nm",sp->m_fMaxlambda);
		m_cTree.InsertItem(sTemp,4,4, hti2);
		sTemp.Format("FWHM = %.1f nm",sp->m_fHalflambda);
		m_cTree.InsertItem(sTemp,4,4, hti2);
	}
	else
	{
		sTemp.Format("峰值波长λp = %.1f nm",sp->m_fMaxlambda);
		m_cTree.InsertItem(sTemp,4,4, hti2);
		sTemp.Format("半宽度FWHM  = %.1f nm",sp->m_fHalflambda);
		m_cTree.InsertItem(sTemp,4,4, hti2);
	}
	if(sp->m_bHaveColorPara)
	{
		if(g_bEnglish)
		{
			sTemp.Format("Red Ratio = %.1f %%",sp->m_fRedRatio);
			m_cTree.InsertItem(sTemp,4,4, hti2);
			sTemp.Format("Green Ratio = %.1f %%",sp->m_fGreenRatio);
			m_cTree.InsertItem(sTemp,4,4, hti2);
			sTemp.Format("Blue Ratio = %.1f %%",sp->m_fBlueRatio);
			m_cTree.InsertItem(sTemp,4,4, hti2);

			if(g_bHaveCRI)
			{
				float fCRI=0;
				for(int i=0;i<14;i++)
				{
					fCRI=fCRI+sp->m_fRi[i];
				}
				fCRI=fCRI/14;
				sTemp.Format("Rendering Index CRI= %.1f",fCRI);
				hti3=m_cTree.InsertItem(sTemp,4,4,hti2);
			}

			sTemp.Format("Rendering Index Ra = %.1f",sp->m_fRa);
			hti3=m_cTree.InsertItem(sTemp,4,4,hti2);
		}
		else
		{
			sTemp.Format("红色比   R  = %.1f %%",sp->m_fRedRatio);
			m_cTree.InsertItem(sTemp,4,4, hti2);
			sTemp.Format("绿色比   G  = %.1f %%",sp->m_fGreenRatio);
			m_cTree.InsertItem(sTemp,4,4, hti2);
			sTemp.Format("蓝色比   B  = %.1f %%",sp->m_fBlueRatio);
			m_cTree.InsertItem(sTemp,4,4, hti2);

			if(g_bHaveCRI)
			{
				float fCRI=0;
				for(int i=0;i<14;i++)
				{
					fCRI=fCRI+sp->m_fRi[i];
				}
				fCRI=fCRI/14;
				sTemp.Format("显色指数 CRI= %.1f",fCRI);
				hti3=m_cTree.InsertItem(sTemp,4,4,hti2);
			}

			sTemp.Format("显色指数 Ra = %.1f",sp->m_fRa);
			hti3=m_cTree.InsertItem(sTemp,4,4,hti2);
		}
		for(int i=0;i<15;i++)
		{
			sTemp.Format("R%-2d = %.0f",i+1,sp->m_fRi[i]);
			m_cTree.InsertItem(sTemp,4,4, hti3);
		}
	}
	m_cTree.Expand(hti2,TVE_EXPAND);
	if(sp->m_bTestPH)
	{
		if(g_bEnglish)
			hti2 = m_cTree.InsertItem(_T("Photo Parameter"),5,5);
		else
			hti2 = m_cTree.InsertItem(_T("光度&辐射度参数"),5,5);

		CString strUnit,strPH;
		if(sp->m_bTestPH)
		{
			strPH=CSpectData::PH_Name(sp->m_iLamp,iPhType,strUnit,TRUE);

			strTemp=g_SPEC.sFormat(sp->m_fPH,5);
			m_cTree.InsertItem(strPH+" = "+strTemp+" "+strUnit,4,4, hti2);
		}
		if(sp->m_iLamp==0)
		{
			if(sp->m_bTestPH&&iPhType==PH_F)
			{
				strPH=CSpectData::PH_Name(sp->m_iLamp,PH_Fe,strUnit,TRUE);
				if(sp->m_fPh_e>1)
				{
					strTemp=g_SPEC.sFormat(sp->m_fPh_e,5);
					m_cTree.InsertItem(strPH+"= "+strTemp+" W",4,4, hti2);
				}
				else
				{
					strTemp=g_SPEC.sFormat(sp->m_fPh_e*1000,5);
					m_cTree.InsertItem(strPH+"= "+strTemp+" "+strUnit,4,4, hti2);
				}
			}

			if(iPhType==PH_I||iPhType==PH_Ie)
			{
				if(sp->m_fPh_e>1)
				{
					strTemp=g_SPEC.sFormat(sp->m_fPh_e,5);
					m_cTree.InsertItem("Ie = "+strTemp+" W/sr",4,4, hti2);
				}
				else
				{
					strTemp=g_SPEC.sFormat(sp->m_fPh_e*1000,5);
					m_cTree.InsertItem("Ie = "+strTemp+" mW/sr",4,4, hti2);
				}

				CString sStr;
				if(g_bEnglish)
				{
					if(sp->m_fDistance==0.316f)
						sStr="Condition = CIE A";
					else if(sp->m_fDistance==0.100f)
						sStr="Condition = CIE B";
					else
						sStr.Format("Condition = %.3f m",sp->m_fDistance);
				}
				else
				{
					if(sp->m_fDistance==0.316f)
						sStr="测试条件 = CIE A";
					else if(sp->m_fDistance==0.100f)
						sStr="测试条件 = CIE B";
					else
						sStr.Format("测试条件 = %.3f m",sp->m_fDistance);
				}
				m_cTree.InsertItem(sStr,4,4, hti2);
			}

			if(sp->m_bTestPH&&iPhType==PH_E)
			{
				strPH=CSpectData::PH_Name(sp->m_iLamp,PH_Ee,strUnit,TRUE);
				strTemp=g_SPEC.sFormat(sp->m_fPh_e,5);
				m_cTree.InsertItem(strPH+"= "+strTemp+" "+strUnit,4,4, hti2);
			}
			if(sp->m_bTestPH&&sp->m_bTestF)
			{
				float fEff;
				if(sp->m_fPow<=0)
					fEff=0;
				else
					fEff=sp->m_fPH/(sp->m_fPow);
				if(g_bEnglish)
					strTemp.Format("Eff. = %.2f lm/W",fEff);
				else
					strTemp.Format("光效η = %.2f lm/W",fEff);
				m_cTree.InsertItem(strTemp,4,4, hti2);
			}

			if(g_bHavePhoEff)
			{
				float fMol  = 0;
				float fEff1 = 0;
				float fEff2 = 0;
				
				BOOL bPho = sp->CalcPhoEff(fMol,fEff1,fEff2, iPhType);
				
				CString strTemp;
				CString sStr="";
				if(g_bEnglish)
				{
					strTemp = "Fmol(umol/s): ";
					if(iPhType == PH_E)
						strTemp = "Fmol(umol/m2/s): ";
				}
				else
				{
					strTemp = "光量子数(umol/s): ";
					if(iPhType == PH_E)
						strTemp = "光量子数(umol/m2/s): ";
				}
				sStr = sStr + strTemp;
				strTemp.Format("%.5g",fMol);
				if(bPho == FALSE)
					strTemp = "   ";
				sStr = sStr + strTemp;
				m_cTree.InsertItem(sStr,4,4, hti2);
				
				sStr="";
				if(g_bEnglish)
				{
					strTemp="Fluorescence and blue light ratio: ";
				}
				else
				{
					strTemp="荧光蓝光比: ";
				}
				sStr = sStr + strTemp;
				strTemp = g_SPEC.sFormat(fEff1,4);
				if(bPho == FALSE)
					strTemp = "   ";
				sStr = sStr + strTemp;
				m_cTree.InsertItem(sStr,4,4, hti2);
				
				sStr="";
				
				if(g_bEnglish)
				{
					strTemp="Fluorescent efficiency: ";
				}
				else
				{
					strTemp="荧光效能: ";
				}
				sStr = sStr + strTemp;
				strTemp = g_SPEC.sFormat(fEff2,4);
				if(bPho == FALSE)
					strTemp = "   ";
				sStr = sStr + strTemp;
				m_cTree.InsertItem(sStr,4,4, hti2);			
			}

			if(sp->m_fSpect1<300.0f)
			{
				if(sp->m_bHaveData)
				{
					strTemp=g_SPEC.sFormat(sp->m_fKuv,4);
					strTemp="UVC = "+strTemp;
				}
				m_cTree.InsertItem(strTemp,4,4, hti2);

				if(sp->m_bHaveData)
				{
					strTemp=g_SPEC.sFormat(sp->m_fK1,4);
					strTemp="UVB  = "+strTemp;
				}
				m_cTree.InsertItem(strTemp,4,4, hti2);

				if(sp->m_bHaveData)
				{
					strTemp=g_SPEC.sFormat(sp->m_fK2,4);
					strTemp="UVA  = "+strTemp;
				}
				m_cTree.InsertItem(strTemp,4,4, hti2);
			}
		}
		m_cTree.Expand(hti2,TVE_EXPAND);
	}

	if(sp->m_bTestF)
	{
		if(g_bEnglish)
			hti2 = m_cTree.InsertItem(_T("Electricity Parameter"),5,5);
		else
			hti2 = m_cTree.InsertItem(_T("电参数"),5,5);

		if(g_bEnglish)
		{
			strTemp=g_SPEC.sFormat(sp->m_fVF,4);
			m_cTree.InsertItem("U = "+strTemp+" V",4,4, hti2);
			strTemp=g_SPEC.sFormat(sp->m_fIF,4);
			m_cTree.InsertItem("I = "+strTemp+" A",4,4, hti2);
			strTemp=g_SPEC.sFormat(sp->m_fPow,4);
			m_cTree.InsertItem("P = "+strTemp+" W",4,4, hti2);
			strTemp=g_SPEC.sFormat(sp->m_fPF,4);
			m_cTree.InsertItem("PF = "+strTemp,4,4, hti2);
		}
		else
		{
			strTemp=g_SPEC.sFormat(sp->m_fVF,4);
			m_cTree.InsertItem("电压U = "+strTemp+" V",4,4, hti2);
			strTemp=g_SPEC.sFormat(sp->m_fIF,4);
			m_cTree.InsertItem("电流I = "+strTemp+" A",4,4, hti2);
			strTemp=g_SPEC.sFormat(sp->m_fPow,4);
			m_cTree.InsertItem("功率P = "+strTemp+" W",4,4, hti2);
			strTemp=g_SPEC.sFormat(sp->m_fPF,4);
			m_cTree.InsertItem("功率因数PF = "+strTemp,4,4, hti2);
		}

		m_cTree.Expand(hti2,TVE_EXPAND);
	}

	if (1)
	{
		if(g_bEnglish)
			hti2 = m_cTree.InsertItem(_T("Parameter"),5,5);
		else
			hti2 = m_cTree.InsertItem(_T("仪器参数"),5,5);
		
		if(g_bEnglish)
		{
		}
		else
		{
			if (sp->m_fIntTime >= 1)
			{
				strTemp.Format("%.0fms",sp->m_fIntTime);
			}
			else
			{
				strTemp.Format("%.1fms",sp->m_fIntTime);
			}
			m_cTree.InsertItem("积分时间 = "+strTemp,4,4, hti2);

			m_cTree.InsertItem("仪器编号 = "+sp->m_strSN,4,4, hti2);
		}
		
		m_cTree.Expand(hti2,TVE_EXPAND);
	}
	m_cTree.Expand(hti2,TVE_EXPAND);
	m_cTree.ShowWindow(SW_SHOW);
}

int CMainFrame::InitBar()
{
	/////////////创建控制条///////////////
// 	if (!m_wndBar1.Create(_T("CIE and SDCM Bar"), this, CSize(250,300),TRUE,123))
// 	{
// 		TRACE0("Failed to create mybar\n");
// 			return -1;
// 	}
	if (!m_wndBar2.Create(_T("Parameters Bar"), this,CSize(250,100),TRUE,124))
	{
		TRACE0("Failed to create mybar\n");
			return -1;
	}

	////////////创建TAB Control，并把它加入到ControlBar中////////
	/// 需要注意的是:同一个ControlBar只能加入一个"一级子窗口"
//	m_TabCtrl.Create(TCS_DOWN|WS_CHILD|WS_VISIBLE,CRect(0,0,100,100),&m_wndBar1,125);

// 	if(g_bEnglish)
// 	{
// 		m_pPage1=(CPage1*)m_TabCtrl.AddPage(RUNTIME_CLASS(CPage1),IDD_PAGE1,"SDCM",IDI_SDCM);
// 		m_pPage2=(CPage2*)m_TabCtrl.AddPage(RUNTIME_CLASS(CPage2),IDD_PAGE2,"CIE1931",IDI_CIE);
// 		m_pPage4=(CPage4*)m_TabCtrl.AddPage(RUNTIME_CLASS(CPage4),IDD_PAGE4,"CIE1976",IDI_CIE_UV);
// 		m_pPage3=(CPage3*)m_TabCtrl.AddPage(RUNTIME_CLASS(CPage3),IDD_PAGE3,"SPECT",IDI_SPEC);
//		m_pPage5=(CPage5*)m_TabCtrl.AddPage(RUNTIME_CLASS(CPage5),IDD_PAGE5,"PASS", 0);
// 	}
// 	else
// 	{
// 		m_pPage1=(CPage1*)m_TabCtrl.AddPage(RUNTIME_CLASS(CPage1),IDD_PAGE1,"色容差",IDI_SDCM);
// 		m_pPage2=(CPage2*)m_TabCtrl.AddPage(RUNTIME_CLASS(CPage2),IDD_PAGE2,"CIE1931",IDI_CIE);
// 		m_pPage4=(CPage4*)m_TabCtrl.AddPage(RUNTIME_CLASS(CPage4),IDD_PAGE4,"CIE1976",IDI_CIE_UV);
// 		m_pPage3=(CPage3*)m_TabCtrl.AddPage(RUNTIME_CLASS(CPage3),IDD_PAGE3,"相对光谱",IDI_SPEC);
//		m_pPage5=(CPage5*)m_TabCtrl.AddPage(RUNTIME_CLASS(CPage5),IDD_PAGE5,"判定", 0);
// 	}
// 	m_TabCtrl.UpdateWindow();

	if (!m_wndTree.Create(WS_CHILD|WS_VISIBLE|
		TVS_HASLINES|TVS_HASBUTTONS|TVS_LINESATROOT,
		CRect(0, 0, 0, 0), &m_wndBar2, 100))
	{
		TRACE0("Failed to create instant bar child\n");
		return -1;
	}

	m_SmallImageList.Create(IDB_SMALLICONS, 16, 1, RGB(255, 255, 0));

	// ** set the tree control to use the image list
	m_wndTree.SetImageList(&m_SmallImageList,TVSIL_NORMAL);

	m_wndTree.SetBkColor(RGB(232, 255, 255));
	m_wndTree.SetTextColor(RGB(128, 0, 64));
	m_wndTree.ModifyStyleEx(0, WS_EX_CLIENTEDGE|TVS_TRACKSELECT);
	m_wndTree.ModifyStyle(0, TVS_TRACKSELECT);



	//往树型控件添加内容
/*	HTREEITEM hti;
	if(g_bEnglish)
		hti = m_wndTree.InsertItem(_T("Colorimetric Quantities"));
	else
		hti = m_wndTree.InsertItem(_T("色度参数"));
	m_wndTree.InsertItem(_T("x = 0.3421"), hti);
	m_wndTree.InsertItem(_T("y = 0.5321"), hti);

	if(g_bEnglish)
		hti = m_wndTree.InsertItem(_T("Photo Parameter"));
	else
		hti = m_wndTree.InsertItem(_T("光度参数"));
	m_wndTree.InsertItem(_T("x = 0.3421"), hti);
	m_wndTree.InsertItem(_T("y = 0.5321"), hti);

	if(g_bEnglish)
	{
		hti = m_wndTree.InsertItem(_T("Test Type"));
		m_wndTree.InsertItem(_T("Accuracy Test"), hti);
	}
	else
	{
		hti = m_wndTree.InsertItem(_T("测量类型"));
		m_wndTree.InsertItem(_T("精确测试"), hti);
	}
*/
	///////////////停靠控制///////////////////
// 	m_wndBar1.SetBarStyle(m_wndBar1.GetBarStyle() |
// 		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	m_wndBar2.SetBarStyle(m_wndBar2.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

//	m_wndBar1.EnableDocking(CBRS_ALIGN_ANY);
	m_wndBar2.EnableDocking(CBRS_ALIGN_ANY);

	EnableDocking(CBRS_ALIGN_ANY);
//	DockControlBar(&m_wndBar1, AFX_IDW_DOCKBAR_RIGHT);
	DockControlBar(&m_wndBar2, AFX_IDW_DOCKBAR_LEFT);

//	DockControlBarLeftOf((CToolBar*)&m_wndBar2, (CToolBar*)&m_wndBar1);

// 	if(!m_bShowCIEBar)
// 		ShowControlBar(&m_wndBar1,m_bShowCIEBar,FALSE);		

	return 0;
}

int CMainFrame::InitNoteBar()
{
	// TODO: Add a menu item that will toggle the visibility of the
	// dialog bar named "My Note Bar":
	//   1. In ResourceView, open the menu resource that is used by
	//      the CMainFrame class
	//   2. Select the View submenu
	//   3. Double-click on the blank item at the bottom of the submenu
	//   4. Assign the new item an ID: CG_ID_VIEW_MYNOTEBAR
	//   5. Assign the item a Caption: My Note Bar

	// TODO: Change the value of CG_ID_VIEW_MYNOTEBAR to an appropriate value:
	//   1. Open the file resource.h
	// CG: The following block was inserted by the 'Dialog Bar' component
	{
		// Initialize dialog bar m_wndMyNoteBar
		if (!m_wndMyNoteBar.Create(this, CG_IDD_MYNOTEBAR,
			CBRS_ALIGN_TOP|CBRS_GRIPPER|CBRS_SIZE_DYNAMIC, AFX_IDW_DIALOGBAR))
		{
			TRACE0("Failed to create dialog bar m_wndMyNoteBar\n");
			return -1;		// fail to create
		}

		m_wndMyNoteBar.EnableDocking(CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM);
		EnableDocking(CBRS_ALIGN_ANY);
		DockControlBar(&m_wndMyNoteBar);

	}
	DockControlBarLeftOf((CToolBar*)&m_wndMyNoteBar, (CToolBar*)&m_wndMyTestBar);

	//Note
	m_cNote.SubclassDlgItem(IDC_NOTE, &this->m_wndMyNoteBar);
	m_cNote.SetTextColor(g_NoteREF);

	//初始化
	ShowNote("",TRUE,RGB(255,0,0));

	return 0;
}

int CMainFrame::InitSystem()
{
	CSpectData::ReadV2(g_strCurPath + "v_2.dat");
	g_SPEC.SPEC_Init();
	
	BOOL bR;
	//读取新的色度计算文件
	bR = NH_Init("NAHONG_TECH_NAHONG","GET_COLOR_PARA",g_strCurPath);
	
	g_SPEC.GetTimeTestData(g_strCurPath+"MutiTime.dat");
	
	//读取标准文件
	bR=g_doData.GetStandardRen(g_strCurPath);
	g_SPEC.STAWL_Load(g_strCurPath+"WL.dat");
	
	bR=g_doData.ReadSdcmData(g_strCurPath);
	//读取光谱定标
	bR=g_SPEC.Get_PL();
	GetPasFun(g_strCurPath);
	
	return 0;
}

int CMainFrame::InitTestBar()
{
	// TODO: Add a menu item that will toggle the visibility of the
	// dialog bar named "My Test Bar":
	//   1. In ResourceView, open the menu resource that is used by
	//      the CMainFrame class
	//   2. Select the View submenu
	//   3. Double-click on the blank item at the bottom of the submenu
	//   4. Assign the new item an ID: CG_ID_VIEW_MYTESTBAR1
	//   5. Assign the item a Caption: My Test Bar

	// TODO: Change the value of CG_ID_VIEW_MYTESTBAR1 to an appropriate value:
	//   1. Open the file resource.h
	// CG: The following block was inserted by the 'Dialog Bar' component
	{
		// Initialize dialog bar m_wndMyTestBar
		if (!m_wndMyTestBar.Create(this, CG_IDD_MYTESTBAR,
			CBRS_ALIGN_TOP|CBRS_GRIPPER|CBRS_SIZE_DYNAMIC, AFX_IDW_DIALOGBAR))
		{
			TRACE0("Failed to create dialog bar m_wndMyTestBar\n");
			return -1;		// fail to create
		}

		m_wndMyTestBar.EnableDocking(CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM);
		EnableDocking(CBRS_ALIGN_ANY);
		DockControlBar(&m_wndMyTestBar);

	//	DockControlBarLeftOf((CToolBar*)&m_wndMyTestBar, (CToolBar*)&m_wndToolBar);

	}
	return 0;
}

void CMainFrame::SetDlgBarSet(int iSele)
{
	CString strTemp;
	CMySpecDoc* pDoc = (CMySpecDoc*)GetActiveDocument();

	if(iSele == 0)
	{
		CEdit *pIntTime = (CEdit *)m_wndMyTestBar.GetDlgItem(IDC_EDIT_INT_TIME);
		if(pDoc->m_fSet_IntTime < 1)
		{
			pDoc->m_fSet_IntTime = 1;
			strTemp.Format("%.0f", pDoc->m_fSet_IntTime);
		}
		else
			strTemp.Format("%.0f", pDoc->m_fSet_IntTime);
		pIntTime->SetWindowText(strTemp);
		pIntTime->EnableWindow(!pDoc->m_bSet_AutoTime);

		if(g_bTest)
		{
			pIntTime->EnableWindow(FALSE);
		}
	}

	if(iSele == 1)
	{
		CButton *pAuto = (CButton *)m_wndMyTestBar.GetDlgItem(IDC_CHECK_AUTO);
		pAuto->SetCheck(pDoc->m_bSet_AutoTime);
		pAuto->EnableWindow(g_bTest == FALSE);
	}

	if(iSele == 2)
	{
		CEdit *pAvgN = (CEdit *)m_wndMyTestBar.GetDlgItem(IDC_EDIT_AVG_N);
		strTemp.Format("%d",pDoc->m_iSet_AvgN);
		pAvgN->SetWindowText(strTemp);
		pAvgN->EnableWindow(g_bTest == FALSE);
	}
}

afx_msg void CMainFrame::OnCheckAutoTime()
{
	CString strTemp;
	CMySpecDoc* pDoc = (CMySpecDoc*)GetActiveDocument();

	pDoc->m_bSet_AutoTime=!pDoc->m_bSet_AutoTime;
	CEdit *pIntTime=(CEdit *)m_wndMyTestBar.GetDlgItem(IDC_EDIT_INT_TIME);
	pIntTime->EnableWindow(!pDoc->m_bSet_AutoTime);
}

afx_msg void CMainFrame::OnChangeEditIntTime() 
{
	CMySpecDoc* pDoc = (CMySpecDoc*)GetActiveDocument();

	CEdit *pInt=(CEdit *)m_wndMyTestBar.GetDlgItem(IDC_EDIT_INT_TIME);
	CString strTemp;
	pInt->GetWindowText(strTemp);
	float fInt=(float)atof(strTemp);
//	if(fInt>=g_SPEC.m_fIntTime1&&fInt<=g_SPEC.m_fIntTime2)
//	{
		pDoc->m_fSet_IntTime=fInt;
//	}
//	else
//	{
//		Sleep(500);
//		CString sTemp;
//		sTemp.Format("积分时间设置错误,应在%.fms-%.fms间",g_SPEC.m_fIntTime1,g_SPEC.m_fIntTime2);
//		AfxMessageBox(sTemp);
//		pInt->SetWindowText("5");
//	}*/
}

afx_msg void CMainFrame::OnChangeEditAvgN() 
{
	CMySpecDoc* pDoc = (CMySpecDoc*)GetActiveDocument();

	CEdit *pAvgN=(CEdit *)m_wndMyTestBar.GetDlgItem(IDC_EDIT_AVG_N);
	CString strTemp;
	pAvgN->GetWindowText(strTemp);
	int iAvgN=atoi(strTemp);
	pDoc->m_iSet_AvgN=iAvgN;
}

void CMainFrame::OnWlCheck() 
{
	// TODO: Add your command handler code here
	CWLCheck dlg;
	dlg.DoModal();
}

void CMainFrame::OnUpdateWlCheck(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!g_bTest);
}

void CMainFrame::OnDark() 
{
	// TODO: Add your command handler code here
	CMySpecDoc* pDoc = (CMySpecDoc*)GetActiveDocument();
	CCmdTarget::BeginWaitCursor();
	BOOL bR;
	bR=g_SPEC.SPEC_GetDark(pDoc->m_fSet_IntTime,pDoc->m_iSet_AvgN);
	if(!bR)
	{
		if(g_bEnglish)
			MessageBox("Sample fail!",NULL,MB_ICONSTOP);
		else
			MessageBox("采样失败!",NULL,MB_ICONSTOP);
		return;
	}
}

void CMainFrame::OnUpdateDark(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!g_bTest);
}

void CMainFrame::OnButtonFlux() 
{
	// TODO: Add your command handler code here
	CDlgFluxCal dlg;
	dlg.DoModal();	
}

void CMainFrame::OnUpdateButtonFlux(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!g_bTest);
}

BOOL CMainFrame::GetPasFun(CString strCurPath)
{
	BOOL b1,b2;
	FILE *fp;
	if((fp = fopen(strCurPath + "SpectraNexus.pas", "r++"))==NULL)
	{
		b1 = FALSE;
		g_bFunDebug = FALSE;
	}
	else
	{
		char a[256];
		CString strTemp;
		fscanf(fp, "DEBUG:%s\n", a);
		strTemp = a;
		if(strTemp == PW_ON)
			g_bFunDebug = TRUE;
		else
			g_bFunDebug = FALSE;
		fclose(fp);
		b1 = TRUE;
	}

	if((fp=fopen(strCurPath+"Cal\\Ra.cal","r++"))==NULL)
	{
		g_bRaShowNeg=FALSE;//不显示负数
	}
	else
	{
		char a2[256];
		int iR;
		iR=fscanf(fp,"RaShowNeg:%s\n",a2);
		if(iR==0)
		{
			g_bRaShowNeg=FALSE;
		}
		else
		{
			CString strTemp;
			strTemp=a2;
			if(strTemp==PW_ON)
				g_bRaShowNeg=TRUE;//显示负数
			else
				g_bRaShowNeg=FALSE;
		}

		fclose(fp);
	}

	if((fp=fopen(strCurPath+"mod.dat","r++"))==NULL)
	{
		b2=FALSE;
		g_bPowerMod		= FALSE;
		g_bFluxMod		= FALSE;
		g_bMoreGroup	= FALSE;
		g_bModeSelf		= FALSE;
		g_bHaveUseHLK	= FALSE;
		g_bFluxSPMod	= FALSE;//光谱法修正
		g_iLEDClass_Type= 0;
		g_bHaveFluxDec	= FALSE;
		g_bHaveTMPDec	= FALSE;
//		return FALSE;
	}
	else
	{
		b2=TRUE;
		char a1[256];
		char a2[256];
		char a3[256];
		char a4[256];
		char a5[256];
		char a6[256];
		CString strTemp;
		//电参数修正
		fscanf(fp,"POWER MODIFIC:%s\n",a1);
		strTemp=a1;
		if(strTemp==PW_ON)
		{
			g_bPowerMod=TRUE;
		}
		else
		{
			g_bPowerMod=FALSE;
		}

		g_bFluxMod  = FALSE;
		g_bMoreGroup = FALSE;
		//光通量修正
		fscanf(fp,"FLUX  MODIFIC:%s\n",a2);
		strTemp=a2;
		if(strTemp==PW_ON)
		{
			g_bFluxMod=TRUE;
		}
		else
		{
			g_bFluxMod=FALSE;
		}

		//多组光通量功能
		fscanf(fp,"FLUX GROUP:%s\n",a3);
		strTemp=a3;
		if(strTemp==PW_ON)
		{
			g_bMoreGroup=TRUE;
		}
		else
		{
			g_bMoreGroup=FALSE;
		}

		//多组光通量功能
		fscanf(fp,"SELF MODEK:%s\n",a4);
		strTemp=a4;
		if(strTemp==PW_ON)
		{
			g_bModeSelf=TRUE;
		}
		else
		{
			g_bModeSelf=FALSE;
		}

		//使用高低模式系数
		BOOL bR=TRUE;
		bR=fscanf(fp,"UseHLK:%s\n",a5);
		strTemp=a5;
		if(strTemp==PW_ON)
		{
			g_bHaveUseHLK=TRUE;
		}
		else
		{
			g_bHaveUseHLK=FALSE;
		}

		//使用光谱法修正光通量
		bR=fscanf(fp,"FLUX_PL_MODIFIC:%s\n",a6);
		if(bR)
		{
			strTemp=a6;
			if(strTemp==PW_ON)
			{
				g_bFluxSPMod=TRUE;
			}
			else
			{
				g_bFluxSPMod=FALSE;
			}
		}
		else
		{
			g_bFluxSPMod=FALSE;
		}

		//使用新的分级方法
		bR=fscanf(fp,"Level:%d\n",&g_iLEDClass_Type);
		if(!bR)
		{
			g_iLEDClass_Type=0;
		}

		fscanf(fp,"FluxDec:%d\n",&g_bHaveFluxDec);
		fscanf(fp,"TMPDec:%d\n",&g_bHaveTMPDec);
		fscanf(fp,"CRI:%d\n",&g_bHaveCRI);
		fscanf(fp,"TR80_or_90:%d\n",&g_iTR80_or_90);

		fscanf(fp,"Use_FluxLamp_SelfCal:%d\n",&g_Use_FluxLamp_SelfCal);
		if(g_bHaveFluxDec == TRUE)
			g_Use_FluxLamp_SelfCal = FALSE;

		fscanf(fp,"OpenColorCorrectXY:%d\n",&g_bOpenColorCorrectXY);

		if(g_bOpenColorCorrectXY == FALSE)
			g_SPEC.m_bUseColorCorrect = TRUE;

		fscanf(fp,"OpenMultiCalSpectrum:%d\n",&g_bOpenMulitCalSpectrum);
		
		if(g_bOpenMulitCalSpectrum == FALSE)
		{
			g_SPEC.m_bUseListCalSele = FALSE;
			g_SPEC.m_iTestListCalSele = 0;
		}
		fscanf(fp,"UseExTestBox:%d\n",&g_bUseExTestBox);

		fscanf(fp,"OpenWaitLamp:%d\n", &g_bOpenWaitLamp);
		fscanf(fp,"OpenColorCorrect:%d\n", &g_bOpenColorCorrect);
		fscanf(fp,"ExDtr:%d\n", &g_bExDtr);

		fscanf(fp,"CorrectXY_mode1:%d\n", &g_bCorrectXY_mode1);
		fscanf(fp,"CorrectXY_mode2:%d\n", &g_bCorrectXY_mode2);

		fclose(fp);
//		return TRUE;
	}
	if(!b1&&!b2)
		return FALSE;
	else
		return TRUE;
}

void CMainFrame::OnPara() 
{
	// TODO: Add your command handler code here
	BOOL  bVisible=((m_wndBar2.GetStyle()&WS_VISIBLE)!=0);
	ShowControlBar(&m_wndBar2,!bVisible,FALSE);
	m_bShowCIEBar=!bVisible;
}

void CMainFrame::OnUpdatePara(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	BOOL  bVisible=((m_wndBar2.GetStyle()&WS_VISIBLE)!=0);
	pCmdUI->SetCheck(bVisible);

}

void CMainFrame::OnCalFlux() 
{
	// TODO: Add your command handler code here

	if(g_bHaveFluxDec == FALSE && g_Use_FluxLamp_SelfCal == TRUE && g_SPEC.m_iTestType == 1)
	{
		CDlgNewFluxCal dlg;
		dlg.DoModal();
		return;
	}

	if(!g_bMoreGroup||g_SPEC.m_iTestType==2)  //照度
	{
		CDlgFluxCal dlg;
		dlg.m_fModeFluxK = g_SPEC.m_fModeFluxK;
		dlg.m_fModeSelfK = g_SPEC.m_fModeSelfK;
		dlg.DoModal();
	}
	else
	{
		CDlgCalFlux dlg;
		dlg.m_fModeFluxK = g_SPEC.m_fModeFluxK;
		dlg.m_fModeSelfK = g_SPEC.m_fModeSelfK;
		dlg.m_iSele		 = g_iSeleCalFlux;

		dlg.DoModal();

		g_iSeleCalFlux	= dlg.m_iSele;

		int iType=g_SPEC.m_iTestType;
		if(g_iSeleCalFlux>=0)
		{
			g_SPEC.m_CAL_fFluxK[iType] = g_calFluxData.m_calData.GetAt(g_iSeleCalFlux)->m_fK;
		}
	}
}

void CMainFrame::OnUpdateCalFlux(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( !g_bTest && g_SPEC.m_iTestType!=3 && g_SPEC.m_iTestType!=4
		&& g_bHaveFluxDec == TRUE);

	if(g_bHaveFluxDec == FALSE && g_Use_FluxLamp_SelfCal == TRUE && g_SPEC.m_iTestType == 1)
	{
		pCmdUI->Enable(TRUE);
	}
}

void CMainFrame::OnCalType() 
{
	// TODO: Add your command handler code here
	CLEDTypeCal dlg;
	dlg.DoModal();
}

void CMainFrame::OnUpdateCalType(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!g_bTest);
}

afx_msg void CMainFrame::OnUpdateMode(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(1);

	CString strTemp;
	strTemp.Format(" SN.:%s ",g_SPEC.m_strSN);
	pCmdUI->SetText(strTemp);
}

void CMainFrame::OnCalAttK() 
{
	// TODO: Add your command handler code here
	CDlgCalAtt dlg;
	dlg.DoModal();
}

void CMainFrame::OnUpdateCalAttK(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

BOOL CMainFrame::SetPassFile()
{
	FILE *fp;
	CString sTitle;
	sTitle="fip.pas";
	if((fp=fopen(g_strCurPath+sTitle,"wt"))==0)
	{
		return FALSE;
	}
	else
	{
		int iTemp;
		iTemp=2357;
		fprintf(fp,"%d\n",iTemp);
		fclose(fp);
		return TRUE;
	}
}

void CMainFrame::OnTestUp() 
{
	// TODO: Add your command handler code here
	STARTUPINFO StartupInfo={0};
	PROCESS_INFORMATION ProcessInfo;

	StartupInfo.cb=sizeof(STARTUPINFO);
	CString m_sExePath=g_strCurPath;
	m_sExePath=m_sExePath+"fip.exe";
	char a[256];
	int iN;
	iN=m_sExePath.GetLength();
	for(int i=0;i<iN;i++)
	{
		a[i]=m_sExePath.GetAt(i);
	}
	a[i]='\0';
	SetPassFile();
	if(CreateProcess(NULL,a,NULL,NULL,FALSE,0,NULL,NULL,&StartupInfo,&ProcessInfo))
	{
		ShowWindow(SW_HIDE);
		WaitForSingleObject(ProcessInfo.hProcess,INFINITE);
		ShowWindow(SW_SHOW);
	}
	else
	{
		if(g_bEnglish)
			MessageBox("Can not run this file."+m_sExePath,NULL,MB_ICONSTOP);
		else
			MessageBox("没有找到运行文件."+m_sExePath,NULL,MB_ICONSTOP);
	}
}

void CMainFrame::OnUpdateTestUp(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!g_bTest);
}

void CMainFrame::OnDebugSoft() 
{
	// TODO: Add your command handler code here
}

void CMainFrame::OnUpdateDebugSoft(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!g_bTest);
}

void CMainFrame::OnEditWhite() 
{
	// TODO: Add your command handler code here
	CDlgWhite dlg;
	dlg.DoModal();

	CMySpecDoc* pDoc = (CMySpecDoc*)GetActiveDocument();

	pDoc->m_ledData.m_xyZone.WZ_Load(g_strListWhite);

	pDoc->UpdateAllViews(NULL);
	::PostMessage(g_MainWnd,WM_RE_HEAD,0,0);
}

void CMainFrame::OnUpdateEditWhite(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!g_bTest);
}

void CMainFrame::OnEditLevel() 
{
	// TODO: Add your command handler code here
	if(g_iLEDClass_Type==1)
	{
		CDlgLEDClassEdit dlg;
		dlg.DoModal();
	}
	else
	{
		CDlgLevel dlg;
		dlg.DoModal();
	}

	CMySpecDoc* pDoc = (CMySpecDoc*)GetActiveDocument();
	pDoc->m_bReList=TRUE;
	if(g_iLEDClass_Type==1)
		pDoc->m_ledData.m_newClassLimit.NC_Load(g_strListNewLevel);
	else
		pDoc->m_ledData.m_levelLimit.Open(g_strListLevel);
	pDoc->UpdateAllViews(NULL);
	::PostMessage(g_MainWnd,WM_RE_HEAD,0,0);
}

void CMainFrame::OnUpdateEditLevel(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!g_bTest);
}

HMENU CMainFrame::NewDefaultMenu()
{
	m_default.LoadMenu(IDR_MAINFRAME);
	m_default.LoadToolbar(IDR_MAINFRAME);
	return(m_default.Detach());
}

void CMainFrame::OnMeasureItem(int nIDCtl, 
							   LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	BOOL setflag=FALSE;
	if(lpMeasureItemStruct->CtlType==ODT_MENU){
		if(IsMenu((HMENU)lpMeasureItemStruct->itemID)){
			CMenu* cmenu = 
				CMenu::FromHandle((HMENU)lpMeasureItemStruct->itemID);
			
			if(m_default.IsMenu(cmenu)){
				m_default.MeasureItem(lpMeasureItemStruct);
				setflag=TRUE;
			}
		}
	}
	
	if(!setflag)CFrameWnd::OnMeasureItem(nIDCtl, 
		lpMeasureItemStruct);
}

void CMainFrame::OnInitMenuPopup(CMenu* pPopupMenu, 
								 UINT nIndex, BOOL bSysMenu) 
{
	CFrameWnd::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);
	if(!bSysMenu){
		if(m_default.IsMenu(pPopupMenu))
			BCMenu::UpdateMenu(pPopupMenu);
	}
}

//////////////////////////////////////////////////////////////////////////////
//This handler ensures that keyboard shortcuts work
LRESULT CMainFrame::OnMenuChar(UINT nChar, UINT nFlags, 
							   CMenu* pMenu) 
{
	LRESULT lresult;
	if(m_default.IsMenu(pMenu))
		lresult=BCMenu::FindKeyboardShortcut(nChar, nFlags, pMenu);
	else
		lresult=CFrameWnd::OnMenuChar(nChar, nFlags, pMenu);
	return(lresult);
}

void CMainFrame::OnTpsMeters() 
{
	// TODO: Add your command handler code here
	STARTUPINFO StartupInfo={0};
	PROCESS_INFORMATION ProcessInfo;

	StartupInfo.cb=sizeof(STARTUPINFO);
	CString m_sExePath=g_strCurPath;
	m_sExePath=m_sExePath+"TPS_Cal.exe";
	char a[256];
	int iN;
	iN=m_sExePath.GetLength();
	for(int i=0;i<iN;i++)
	{
		a[i]=m_sExePath.GetAt(i);
	}
	a[i]='\0';
	if(CreateProcess(NULL,a,NULL,NULL,FALSE,0,NULL,NULL,&StartupInfo,&ProcessInfo))
	{
//		GetParentFrame()->ShowWindow(SW_HIDE);
//		WaitForSingleObject(ProcessInfo.hProcess,INFINITE);
//		GetParentFrame()->ShowWindow(SW_SHOW);
	}
	else
	{
		if(g_bEnglish)
			MessageBox("Can not run this file."+m_sExePath,NULL,MB_ICONSTOP);
		else
			MessageBox("没有找到运行文件."+m_sExePath,NULL,MB_ICONSTOP);
	}
}

void CMainFrame::OnUpdateTpsMeters(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!g_bTest);
	
}

void CMainFrame::OnVpsMeters() 
{
	// TODO: Add your command handler code here
	STARTUPINFO StartupInfo={0};
	PROCESS_INFORMATION ProcessInfo;

	StartupInfo.cb=sizeof(STARTUPINFO);
	CString m_sExePath=g_strCurPath;
	m_sExePath=m_sExePath+"VPS_Cal.exe";
	char a[256];
	int iN;
	iN=m_sExePath.GetLength();
	for(int i=0;i<iN;i++)
	{
		a[i]=m_sExePath.GetAt(i);
	}
	a[i]='\0';
	if(CreateProcess(NULL,a,NULL,NULL,FALSE,0,NULL,NULL,&StartupInfo,&ProcessInfo))
	{
//		GetParentFrame()->ShowWindow(SW_HIDE);
//		WaitForSingleObject(ProcessInfo.hProcess,INFINITE);
//		GetParentFrame()->ShowWindow(SW_SHOW);
	}
	else
	{
		if(g_bEnglish)
			MessageBox("Can not run this file."+m_sExePath,NULL,MB_ICONSTOP);
		else
			MessageBox("没有找到运行文件."+m_sExePath,NULL,MB_ICONSTOP);
	}
}

void CMainFrame::OnUpdateVpsMeters(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!g_bTest);
	
}

void CMainFrame::OnCalPlFlux() 
{
	// TODO: Add your command handler code here
	CDlgCalPLFlux dlg;
	dlg.m_bUseFluxPL=g_bUseFluxPL;
	dlg.DoModal();
	g_bUseFluxPL=dlg.m_bUseFluxPL;

	int iHave;
	iHave=g_CalFluxPLData.m_calData.GetSize();
	if(iHave<=0)
		g_bUseFluxPL=FALSE;

	if(g_bUseFluxPL)
	{
		g_iSeleCalPLFlux=dlg.m_iSele;
	}
}

void CMainFrame::OnUpdateCalPlFlux(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMainFrame::OnPower() 
{
	// TODO: Add your command handler code here
}

void CMainFrame::OnUpdatePower(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
}

void CMainFrame::OnSelfPh() 
{
	// TODO: Add your command handler code here
	CDlgSelfPhK dlg;
	dlg.m_fSelfPhK = g_SPEC.m_fModeSelfK;
	dlg.m_iType = g_SPEC.m_selfCorrectData.m_iType;

	dlg.DoModal();

	g_SPEC.m_selfCorrectData.m_iType = dlg.m_iType;

	g_SPEC.m_fModeSelfK = dlg.m_fSelfPhK;

	g_SPEC.m_selfCorrectData.Save(g_strCurPath + "Cal\\selfCal.dat");
}

void CMainFrame::OnUpdateSelfPh(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMainFrame::OnUpdateCalList(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(TRUE);

	CString strTemp;
	strTemp.Format("--CAL:%03d--", g_SPEC.m_iTestListCalSele);
	pCmdUI->SetText(strTemp);
}

void CMainFrame::OnGpibKeithley2420() 
{
	// TODO: Add your command handler code here
	STARTUPINFO StartupInfo={0};
	PROCESS_INFORMATION ProcessInfo;
	
	StartupInfo.cb=sizeof(STARTUPINFO);
	CString m_sExePath=g_strCurPath;
	m_sExePath=m_sExePath+"KEITHLEY.exe";
	char a[256];
	int iN;
	iN=m_sExePath.GetLength();
	for(int i=0;i<iN;i++)
	{
		a[i]=m_sExePath.GetAt(i);
	}
	a[i]='\0';
	if(CreateProcess(NULL,a,NULL,NULL,FALSE,0,NULL,NULL,&StartupInfo,&ProcessInfo))
	{
	}
	else
	{
		if(g_bEnglish)
			MessageBox("Can not run this file."+m_sExePath,NULL,MB_ICONSTOP);
		else
			MessageBox("没有找到运行文件."+m_sExePath,NULL,MB_ICONSTOP);
	}	
}

void CMainFrame::OnUpdateGpibKeithley2420(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!g_bTest);
	
}

void CMainFrame::OnRs232RemoteComm() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnUpdateRs232RemoteComm(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}


void CMainFrame::OnWaitLamp() 
{
	// TODO: Add your command handler code here
	m_bWaitLamp = !m_bWaitLamp;
}

void CMainFrame::OnUpdateWaitLamp(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(CMainFrame::m_bWaitLamp);

	if(g_bOpenWaitLamp == FALSE)
	{
		pCmdUI->SetText(" --- ");
		pCmdUI->Enable(FALSE);
	}
}

void CMainFrame::OnDestroy() 
{
	CFrameWnd::OnDestroy();
	
	// TODO: Add your message handler code here

}

UINT CMainFrame::threadConnectManager(LPVOID pPar)
{
	return 0;
	CMainFrame * pMain = (CMainFrame *)pPar;
	CAccreditData AccreditData;
	BOOL bR;

	char szName[256];
	char szNewName[256];
	
	sprintf(szName, _T("%s"), "SpectraNexus");
	CAccreditData::Name2NewName(szName, szNewName);
	CString strName = szNewName;
	
	CString strPathName = "C:\\Windows\\inf\\" + strName + ".PNF";		

	bR = AccreditData.Open(strPathName);
	if(bR == FALSE)
	{

		pMain->SetTimer(112, 30000, NULL);
		if(g_bEnglish == FALSE)
			::MessageBox(pMain->m_hWnd, "T1:软件试用已过期，请联系远方公司提供正式版软件!", NULL, MB_ICONWARNING);
		else
			::MessageBox(pMain->m_hWnd, "T1:Software exceed the trail time, please registe!", NULL, MB_ICONWARNING);
		pMain->PostMessage(WM_QUIT,0,0);
		return 0;
	}

	while(1)
	{
		AccreditData.Add(CTime::GetCurrentTime());
		bR = AccreditData.Save(strPathName);
		if(bR == FALSE)
		{
			pMain->SetTimer(112, 30000, NULL);
			if(g_bEnglish == FALSE)
				::MessageBox(pMain->m_hWnd, "T2:软件试用已过期，请联系远方公司提供正式版软件!", NULL, MB_ICONWARNING);
			else
				::MessageBox(pMain->m_hWnd, "T2:Software exceed the trail time, please registe!", NULL, MB_ICONWARNING);
			pMain->PostMessage(WM_QUIT,0,0);
			return 0;
		}

		if (AccreditData.CanUse() == FALSE)
		{
			pMain->SetTimer(112, 30000, NULL);
			if(g_bEnglish == FALSE)
				::MessageBox(pMain->m_hWnd, "T3:软件试用已过期，请联系远方公司提供正式版软件!", NULL, MB_ICONWARNING);
			else
				::MessageBox(pMain->m_hWnd, "T3:Software exceed the trail time, please registe!", NULL, MB_ICONWARNING);
			pMain->PostMessage(WM_QUIT,0,0);
			return 0;
			
		}

		Sleep(1000 * 60 * 5);
	}
	
	return 0;

}


BOOL CMainFrame::ReadPasswordFile(CString strPathName)
{
	FILE *fp;
    CString sTitle;
    if((fp=fopen(strPathName,"rt"))==0)
		return FALSE;
    else
	{
		fscanf(fp,"%d %d", &m_iSetPassword2, &m_iSetPassword1);
		fclose(fp);
		return TRUE;
	}
}

void CMainFrame::OnDpsPc() 
{
	// TODO: Add your command handler code here
	STARTUPINFO StartupInfo={0};
	PROCESS_INFORMATION ProcessInfo;
	
	StartupInfo.cb=sizeof(STARTUPINFO);
	CString m_sExePath=g_strCurPath;
	m_sExePath=m_sExePath+"DPS_PC.exe";
	char a[256];
	int iN;
	iN=m_sExePath.GetLength();
	for(int i=0;i<iN;i++)
	{
		a[i]=m_sExePath.GetAt(i);
	}
	a[i]='\0';
	if(CreateProcess(NULL,a,NULL,NULL,FALSE,0,NULL,NULL,&StartupInfo,&ProcessInfo))
	{
	}
	else
	{
		if(g_bEnglish)
			MessageBox("Can not run this file."+m_sExePath,NULL,MB_ICONSTOP);
		else
			MessageBox("没有找到运行文件."+m_sExePath,NULL,MB_ICONSTOP);
	}}

void CMainFrame::OnUpdateDpsPc(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!g_bTest);
	
}

void CMainFrame::OnExdtr() 
{
	// TODO: Add your command handler code here
	STARTUPINFO StartupInfo={0};
	PROCESS_INFORMATION ProcessInfo;
	
	StartupInfo.cb = sizeof(STARTUPINFO);
	CString m_sExePath = g_strCurPath;
	m_sExePath = m_sExePath + "ExDtr.exe";
	char a[256];
	int iN;
	iN = m_sExePath.GetLength();
	for(int i = 0; i < iN; i++)
		a[i] = m_sExePath.GetAt(i);
	a[i] = '\0';

	if(CreateProcess(NULL,a,NULL,NULL,FALSE,0,NULL,NULL,&StartupInfo,&ProcessInfo))
	{
		
	}
	else
	{
		if(g_bEnglish)
			MessageBox("Can not run this file."+m_sExePath,NULL,MB_ICONSTOP);
		else
			MessageBox("没有找到运行文件."+m_sExePath,NULL,MB_ICONSTOP);
	}
}

void CMainFrame::OnUpdateExdtr(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(g_bExDtr == FALSE)
	{
		pCmdUI->Enable(FALSE);
		pCmdUI->SetText(" --- ");
	}
	else
		pCmdUI->Enable(TRUE);
}

