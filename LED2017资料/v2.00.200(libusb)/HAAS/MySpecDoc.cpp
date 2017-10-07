// MySpecDoc.cpp : implementation of the CMySpecDoc class
//

#include "stdafx.h"
#include "MySpec.h"

#include "MySpecDoc.h"
#include "Global_MySpec.h"

#include "MySheet.h"

#include "Option1.h"
#include "Option2.h"
#include "Option3.h"

#include "DlgSeleCT.h"
#include "afxdao.h"

#include "DlgInputPower.h"
#include "DlgCheckBW.h"
#include "MainFrm.h"
#include "ExWaitLampStableDLL.h"
#include "DlgExportLamp.h"

#include "DlgReGe.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMySpecDoc

CString g_strPrTitle_C;
CString g_strPrTitle_E;

CString g_strCompany;
CString g_strAddr;

extern BOOL g_bPowerMod;
extern COLORREF g_ErrTextColor;
extern COLORREF g_ErrBkColor;
extern int g_iLEDClass_Type;

extern int g_iPrintG;

extern int g_iSeleTc;
extern int g_iSDCM1;
extern int g_iSDCM2;

BOOL g_bPrintLogo;

IMPLEMENT_DYNCREATE(CMySpecDoc, CDocument)

BEGIN_MESSAGE_MAP(CMySpecDoc, CDocument)
	//{{AFX_MSG_MAP(CMySpecDoc)
	ON_COMMAND(ID_EXPORT_CSV, OnExportCsv)
	ON_UPDATE_COMMAND_UI(ID_EXPORT_CSV, OnUpdateExportCsv)
	ON_COMMAND(ID_TEST, OnTest)
	ON_UPDATE_COMMAND_UI(ID_TEST, OnUpdateTest)
	ON_COMMAND(ID_TEST_CON, OnTestCon)
	ON_UPDATE_COMMAND_UI(ID_TEST_CON, OnUpdateTestCon)
	ON_COMMAND(ID_EXPORT_SPEC_CAV, OnExportSpecCav)
	ON_UPDATE_COMMAND_UI(ID_EXPORT_SPEC_CAV, OnUpdateExportSpecCav)
	ON_COMMAND(ID_OPTION, OnOption)
	ON_UPDATE_COMMAND_UI(ID_OPTION, OnUpdateOption)
	ON_COMMAND(ID_SELE_SDCM, OnSeleSdcm)
	ON_UPDATE_COMMAND_UI(ID_SELE_SDCM, OnUpdateSeleSdcm)
	ON_COMMAND(ID_TEST_STOP, OnTestStop)
	ON_UPDATE_COMMAND_UI(ID_TEST_STOP, OnUpdateTestStop)
	ON_UPDATE_COMMAND_UI(ID_APP_EXIT, OnUpdateAppExit)
	ON_COMMAND(ID_SETUP, OnSetup)
	ON_UPDATE_COMMAND_UI(ID_SETUP, OnUpdateSetup)
	ON_COMMAND(ID_BUTTON_TRIG, OnButtonTrig)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_TRIG, OnUpdateButtonTrig)
	ON_COMMAND(ID_EXPORT_ACCESS, OnExportAccess)
	ON_UPDATE_COMMAND_UI(ID_EXPORT_ACCESS, OnUpdateExportAccess)
	ON_COMMAND(ID_POWER, OnPower)
	ON_UPDATE_COMMAND_UI(ID_POWER, OnUpdatePower)
	ON_COMMAND(ID_CHECK_BW, OnCheckBw)
	ON_UPDATE_COMMAND_UI(ID_CHECK_BW, OnUpdateCheckBw)
	ON_COMMAND(ID_EXPORT_ALL_SPEC, OnExportAllSpec)
	ON_UPDATE_COMMAND_UI(ID_EXPORT_ALL_SPEC, OnUpdateExportAllSpec)
	ON_COMMAND(ID_EXPORT_LAMP_DAT, OnExportLampDat)
	ON_UPDATE_COMMAND_UI(ID_EXPORT_LAMP_DAT, OnUpdateExportLampDat)
	ON_COMMAND(ID_MOD_GE, OnModGe)
	ON_UPDATE_COMMAND_UI(ID_MOD_GE, OnUpdateModGe)
	ON_COMMAND(ID_EXPORT_PHS, OnExportPhs)
	ON_UPDATE_COMMAND_UI(ID_EXPORT_PHS, OnUpdateExportPhs)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMySpecDoc construction/destruction

BOOL g_bTest;
BOOL g_bTestCancel;
int  g_iTestType;

extern BOOL g_bHaveMode;
extern CImageObject g_ImageCompany;

int		CMySpecDoc::m_iNType = 0;
CString	CMySpecDoc::m_strChecker = "";
BOOL	CMySpecDoc::m_bPrintChecker = FALSE;
CString CMySpecDoc::m_strNewT = "测 试 报 告";

CMySpecDoc::CMySpecDoc()
:PAGE_N(25)
{
	m_bTemp_PreheatTimeMode = FALSE;
	g_bTest			= FALSE;
	g_iTestType		= 0;
	g_bTestCancel	= FALSE;

	m_nActive = 0;
	m_iB      = 0;

	m_ledData.m_opData.Open(g_strCurPath+"op.dat");
	m_bReList = FALSE;

	//读取公司徵标
	CString strTemp;
	strTemp = g_strCurPath;
	if(g_bEnglish)
		strTemp = strTemp+"Logo1.bmp";
	else
		strTemp = strTemp+"Logo.bmp";
	g_ImageLogo.Load(strTemp);

	strTemp	= g_strCurPath;
	strTemp	= strTemp+"Company.tu";
	g_ImageCompany.Load(strTemp);

	m_ledData.m_opData.m_iShowCIE=0;

	m_fSet_IntTime  = 100;
	m_bSet_AutoTime = TRUE;
	m_iSet_AvgN     = 1;

	CString  strSection  = "Test_NEW_Haas2";

	CString  strIntTime  = "IntTime";
	CString  strAutoTime = "AutoTime";
	CString  strAvgN     = "AvgN";

	strTemp				 = AfxGetApp()->GetProfileString(strSection,strIntTime,"100");
	m_fSet_IntTime		 = (float)atof(strTemp);
	m_bSet_AutoTime		 = AfxGetApp()->GetProfileInt(strSection,strAutoTime,TRUE);
	m_iSet_AvgN			 = AfxGetApp()->GetProfileInt(strSection,strAvgN,1);

			 strSection  = "OP_SET_Haas";
	CString  strTitle_E  = "Title_E";
	CString  strTitle_C  = "Title_C";
	CString  strPrintG   = "PrintG";
	CString  strCompany  = "Company";
	CString  strAddr	 = "Addr";

	g_strPrTitle_E		 = AfxGetApp()->GetProfileString(strSection,strTitle_E,"SpectraNexus Test Report");
	g_strPrTitle_C		 = AfxGetApp()->GetProfileString(strSection,strTitle_C,"SpectraNexus 光色电测试报告");
	g_iPrintG			 = AfxGetApp()->GetProfileInt(strSection,strPrintG,0);
	g_strCompany		 = AfxGetApp()->GetProfileString(strSection,strCompany,"SpectraNexus CORPORATION");
	g_strAddr			 = AfxGetApp()->GetProfileString(strSection,strAddr,"http://www.NAHON.cn");

			 strSection  = "ERR_COLO_NewHaas";
	CString  strTextColor= "TextColor";
	CString  strBkColor  = "BkColor";

	g_ErrTextColor		 = AfxGetApp()->GetProfileInt(strSection,strTextColor,RGB(0,0,0));
	g_ErrBkColor		 = AfxGetApp()->GetProfileInt(strSection,strBkColor,RGB(255,255,255));

	CString str_m_iNType		= _T("m_iNType");
	CString str_m_strChecker	= _T("m_strChecker");
	CString str_m_bPrintChecker = _T("m_bPrintChecker");
	CString str_m_strNewT		= _T("m_strNewT");
	
	m_iNType		= AfxGetApp()->GetProfileInt(strSection, str_m_iNType, 0);
	m_strChecker	= AfxGetApp()->GetProfileString(strSection, str_m_strChecker, _T("damin"));
	m_bPrintChecker = AfxGetApp()->GetProfileInt(strSection, str_m_bPrintChecker, 1);
	m_strNewT		= AfxGetApp()->GetProfileString(strSection, str_m_strNewT, _T("Report Title"));
}

CMySpecDoc::~CMySpecDoc()
{
	m_ledData.m_opData.Save(g_strCurPath+"op.dat");

	CString  strSection  = "Test_NEW_Haas2";

	CString  strIntTime  = "IntTime";
	CString  strAutoTime = "AutoTime";
	CString  strAvgN     = "AvgN";

	CString strTemp;
	strTemp.Format("%f",m_fSet_IntTime);
	AfxGetApp()->WriteProfileString(strSection,strIntTime,strTemp);
	AfxGetApp()->WriteProfileInt(strSection,strAutoTime,m_bSet_AutoTime);
	AfxGetApp()->WriteProfileInt(strSection,strAvgN,m_iSet_AvgN);

			 strSection  = "OP_SET_Haas";
	CString  strTitle_E  = "Title_E";
	CString  strTitle_C  = "Title_C";
	CString  strPrintG   = "PrintG";
	CString  strCompany  = "Company";
	CString  strAddr	 = "Addr";

	AfxGetApp()->WriteProfileString(strSection,strTitle_E,g_strPrTitle_E);
	AfxGetApp()->WriteProfileString(strSection,strTitle_C,g_strPrTitle_C);
	AfxGetApp()->WriteProfileInt(strSection,strPrintG,g_iPrintG);
	AfxGetApp()->WriteProfileString(strSection,strCompany,g_strCompany);
	AfxGetApp()->WriteProfileString(strSection,strAddr,g_strAddr);

			 strSection  = "ERR_COLOR_NewHaas";
	CString  strTextColor= "TextColor";
	CString  strBkColor  = "BkColor";
	AfxGetApp()->WriteProfileInt(strSection,strTextColor,g_ErrTextColor);
	AfxGetApp()->WriteProfileInt(strSection,strBkColor,g_ErrBkColor);

	CString str_m_iNType		= _T("m_iNType");
	CString str_m_strChecker	= _T("m_strChecker");
	CString str_m_bPrintChecker = _T("m_bPrintChecker");
	CString str_m_strNewT		= _T("m_strNewT");
	
	AfxGetApp()->WriteProfileInt(strSection,	str_m_iNType,		m_iNType);
	AfxGetApp()->WriteProfileString(strSection, str_m_strChecker,	m_strChecker);
	AfxGetApp()->WriteProfileInt(strSection,	str_m_bPrintChecker, m_bPrintChecker);
	AfxGetApp()->WriteProfileString(strSection, str_m_strNewT,		m_strNewT);
}

BOOL CMySpecDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
	{
		return FALSE;
	}

	m_ledData.New();
	m_tempData.m_spData.Init();
	m_tempData.m_spData.RD_Info();

	m_strNumber=m_tempData.m_spData.m_strNumber;

	if(g_SPEC.m_iTestType == 1 || g_SPEC.m_iTestType == 0)
	{
		m_ledData.m_iPhType = PH_F;
	}
	if(g_SPEC.m_iTestType == 2)
	{
		m_ledData.m_iPhType = PH_E;
	}
	if(g_SPEC.m_iTestType == 3)
	{
		m_ledData.m_iPhType = PH_I;
	}
	if(g_SPEC.m_iTestType == 4)
	{
		m_ledData.m_iPhType = PH_L;
	}

	m_nActive	= 0;
	m_iB		= 0;

	g_iSeleTc  = m_ledData.m_opData.m_iSeleTc;
	g_iSDCM1 = m_ledData.m_opData.m_iSDCM1;
	g_iSDCM2 = m_ledData.m_opData.m_iSDCM2;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMySpecDoc serialization

void CMySpecDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		m_ledData.Serialize(ar);

		DeleteFileA(g_strCurPath + "\\Files\\temp.haas");
	}
	else
	{
		// TODO: add loading code here
		m_ledData.Serialize(ar);

		if(m_ledData.m_listData.GetSize() > 0)
		{
			m_tempData = *m_ledData.m_listData[0];
			int iType = m_ledData.m_listData[0]->m_spData.m_iTestType;
			if(g_SPEC.m_iTestType != iType)
			{
				g_SPEC.m_iTestType = iType;
				::PostMessage(g_MainWnd,WM_RE_HEAD,0,0);
			}
		}
	}

}

/////////////////////////////////////////////////////////////////////////////
// CMySpecDoc diagnostics

#ifdef _DEBUG
void CMySpecDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMySpecDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMySpecDoc commands

void CMySpecDoc::OnExportCsv() 
{
	// TODO: Add your command handler code here
	//从文件中路径中读取文件名
	CString strTemp;
	strTemp=GetPathName();
	int iP=strTemp.Find(".",0);
	strTemp=strTemp.Left(iP);

	//选择导出路径
	static char BASED_CODE szFilter[]="Excel Files(*.xls)|*.xls||";
	CFileDialog mOpenFile(FALSE, ".xls",strTemp,  OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);
	if(mOpenFile.DoModal()==IDCANCEL) 
		return;
	CString strPathName=mOpenFile.GetPathName();	

	//导出文件
	BOOL bR;
	bR=m_ledData.Export_CSV(strPathName);
	if(!bR)
	{
		if(g_bEnglish)
			AfxMessageBox("Export fail!",MB_ICONSTOP);
		else
			AfxMessageBox("导出文件失败!",MB_ICONSTOP);
		return;
	}
}

void CMySpecDoc::OnUpdateExportCsv(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_ledData.m_listData.GetSize()>0);
}

void CMySpecDoc::OnTest() 
{
	// TODO: Add your command handler code here

	m_bInt = FALSE;
	g_iTestType	= 0;
	if(!g_bTest)
	{
		::PostMessage(g_MainWnd,WM_TEST_START,0,0);
	}
}

void CMySpecDoc::OnUpdateTest(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(g_bTest)
	{
		pCmdUI->SetCheck(g_iTestType==0);
	}
	else
	{
		pCmdUI->SetCheck(0);
	}
//	pCmdUI->Enable(!g_bTest&&!g_SPEC.m_bTrig);
}

void CMySpecDoc::OnTestCon() 
{
	// TODO: Add your command handler code here
	g_iTestType = 1;
	if(!g_bTest)
	{
		::PostMessage(g_MainWnd,WM_TEST_START,0,0);
	}
}

void CMySpecDoc::OnUpdateTestCon(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(g_bTest)
	{
		pCmdUI->SetCheck(g_iTestType == 1);
	}
	else
	{
		pCmdUI->SetCheck(0);
	}
//	pCmdUI->Enable(!g_bTest&&!g_SPEC.m_bTrig);
}

void CMySpecDoc::Calc_B_Active(int iSele)
{
	//计算出iSele是 Begin 及 Active
	int iN = m_ledData.m_listData.GetSize();
	if(iSele < 0 || iSele > (iN - 1))
	{
		return;
	}
	m_nActive=iSele%PAGE_N;
	m_iB=(iSele-m_nActive);
}

void CMySpecDoc::OnExportSpecCav() 
{
	// TODO: Add your command handler code here
	CString sStr;
	sStr=GetPathName();
	int iP=sStr.Find(".",0);
	sStr=sStr.Left(iP)+"_"+m_tempData.m_spData.m_strNumber;

	//选择导出路径
	static char BASED_CODE szFilter[]="Excel Files(*.xls)|*.xls||";
	CFileDialog mOpenFile(FALSE, ".xls",sStr,  OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);
	if(mOpenFile.DoModal()==IDCANCEL) 
		return;

	CString strPathName=mOpenFile.GetPathName();

	BOOL bR;
	bR=m_tempData.m_spData.Export_CSV(strPathName,m_ledData.m_opData.m_fExportIntervalWL);
	if(!bR)
	{
		if(g_bEnglish)
			AfxMessageBox("Export fail!",MB_ICONINFORMATION);
		else
			AfxMessageBox("导出数据文件失败!",MB_ICONINFORMATION);
	}
	return;
}

void CMySpecDoc::OnUpdateExportSpecCav(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_tempData.m_spData.m_bHaveData);
}

void CMySpecDoc::OnOption() 
{
	// TODO: Add your command handler code here
	CString strT;
	if(g_bEnglish)
		strT="Option";
	else
		strT="选项";
	CMySheet sheet(strT);

	COption1 dPage1;
	COption2 dPage2;
	COption3 dPage3;

	sheet.AddPage(&dPage1);
	sheet.AddPage(&dPage2);
	sheet.AddPage(&dPage3);

	dPage1.m_strIntervalWL.Format("%.1f nm",m_ledData.m_opData.m_fExportIntervalWL);
	dPage1.m_bPrintLogo		= m_ledData.m_opData.m_bPrintLogo;

	dPage1.m_strAddr		= g_strAddr;
	dPage1.m_strCompany		= g_strCompany;

	dPage1.m_iPrintLogoPos	= m_ledData.m_opData.m_iPrintLogoPos;
	dPage1.m_iReportType	= m_ledData.m_opData.m_iReportType;
	dPage1.m_bPrintPage		= m_ledData.m_opData.m_bPrintPage;

	if(g_bEnglish)
	{
		dPage1.m_strPrTitle = g_strPrTitle_E;
	}
	else
	{
		dPage1.m_strPrTitle = g_strPrTitle_C;
	}
	dPage1.m_iShowCIE	= m_ledData.m_opData.m_iShowCIE;

	dPage1.m_iNType = m_iNType;
	dPage1.m_bPrintChecker = m_bPrintChecker;
	dPage1.m_strChecker = m_strChecker;
	dPage1.m_strNewT = m_strNewT;

	dPage2.m_bNote		= m_ledData.m_opData.m_bNote;
	dPage2.m_bVF		= m_ledData.m_opData.m_bVF;
	dPage2.m_bIF		= m_ledData.m_opData.m_bIF;
	dPage2.m_bP			= m_ledData.m_opData.m_bP;
	dPage2.m_bIp		= m_ledData.m_opData.m_bIp;
	dPage2.m_bXY		= m_ledData.m_opData.m_bXY;
	dPage2.m_bUV		= m_ledData.m_opData.m_bUV;
	dPage2.m_bTc		= m_ledData.m_opData.m_bTc;
	dPage2.m_bLd		= m_ledData.m_opData.m_bLd;
	dPage2.m_bPur		= m_ledData.m_opData.m_bPur;
	dPage2.m_bLp		= m_ledData.m_opData.m_bLp;
	dPage2.m_bHW		= m_ledData.m_opData.m_bHW;
	dPage2.m_bRR		= m_ledData.m_opData.m_bRR;
	dPage2.m_bRa		= m_ledData.m_opData.m_bRa;
	dPage2.m_bRO		= m_ledData.m_opData.m_bRO;
	dPage2.m_bPH		= m_ledData.m_opData.m_bPH;
	dPage2.m_bLevel		= m_ledData.m_opData.m_bLevel;
	dPage2.m_bWhite		= m_ledData.m_opData.m_bWhite;
	dPage2.m_bInfo		= m_ledData.m_opData.m_bInfo;
	dPage2.m_bPhoEff	= m_ledData.m_opData.m_bPhoEff;
	
	dPage2.m_bdC = m_ledData.m_opData.m_bdC;
	dPage2.m_bColorCorrectStr = m_ledData.m_opData.m_bColorCorrectStr;

	if(g_SPEC.T_SPECT1 == 200)
		dPage2.m_bZW = m_ledData.m_opData.m_bZW;
	else
		dPage2.m_bZW = FALSE;

	dPage2.m_bPhSP = m_ledData.m_opData.m_bPhSP;

	dPage2.m_bPrintPh_ = CSpectData::m_bPrintPh_;
	
	dPage1.m_iPrintG = g_iPrintG;

	if(sheet.DoModal() == IDCANCEL)
		return;

	m_ledData.m_opData.m_fExportIntervalWL = (float)atof(dPage1.m_strIntervalWL);

	g_bPrintLogo = dPage1.m_bPrintLogo;
	g_strAddr    = dPage1.m_strAddr;
	g_strCompany = dPage1.m_strCompany;


	m_ledData.m_opData.m_bPrintLogo    = dPage1.m_bPrintLogo;
	m_ledData.m_opData.m_iPrintLogoPos = dPage1.m_iPrintLogoPos;
	m_ledData.m_opData.m_iReportType   = 0;//dPage1.m_iReportType;
	m_ledData.m_opData.m_bPrintPage    = dPage1.m_bPrintPage;
	m_ledData.m_opData.m_iShowCIE      = dPage1.m_iShowCIE;

	m_iNType = dPage1.m_iNType;
	m_bPrintChecker = dPage1.m_bPrintChecker;
	m_strChecker = dPage1.m_strChecker;
	m_strNewT = dPage1.m_strNewT;

	m_ledData.m_opData.m_bNote  = dPage2.m_bNote;
	m_ledData.m_opData.m_bVF    = dPage2.m_bVF;
	m_ledData.m_opData.m_bIF    = dPage2.m_bIF;
	m_ledData.m_opData.m_bP     = dPage2.m_bP;
	m_ledData.m_opData.m_bIp    = dPage2.m_bIp;
	m_ledData.m_opData.m_bXY    = dPage2.m_bXY;
	m_ledData.m_opData.m_bUV    = dPage2.m_bUV;
	m_ledData.m_opData.m_bTc    = dPage2.m_bTc;
	m_ledData.m_opData.m_bLd    = dPage2.m_bLd;
	m_ledData.m_opData.m_bPur   = dPage2.m_bPur;
	m_ledData.m_opData.m_bLp    = dPage2.m_bLp;
	m_ledData.m_opData.m_bHW    = dPage2.m_bHW;
	m_ledData.m_opData.m_bRR    = dPage2.m_bRR;
	m_ledData.m_opData.m_bRa    = dPage2.m_bRa;
	m_ledData.m_opData.m_bRO    = dPage2.m_bRO;
	m_ledData.m_opData.m_bPH    = dPage2.m_bPH;
	m_ledData.m_opData.m_bLevel = dPage2.m_bLevel;
	m_ledData.m_opData.m_bWhite = dPage2.m_bWhite;
	m_ledData.m_opData.m_bInfo  = dPage2.m_bInfo;
	m_ledData.m_opData.m_bPhoEff= dPage2.m_bPhoEff;
	m_ledData.m_opData.m_bPhSP  = dPage2.m_bPhSP;

	m_ledData.m_opData.m_bdC = dPage2.m_bdC;
	m_ledData.m_opData.m_bColorCorrectStr = dPage2.m_bColorCorrectStr;

	CSpectData::m_bPrintPh_ = dPage2.m_bPrintPh_;

	if(g_SPEC.T_SPECT1 == 200)
	{
		m_ledData.m_opData.m_bZW = dPage2.m_bZW;
	}
	else
	{
		m_ledData.m_opData.m_bZW = FALSE;
	}

	if(g_bEnglish)
	{
		g_strPrTitle_E = dPage1.m_strPrTitle;
	}
	else
	{
		g_strPrTitle_C = dPage1.m_strPrTitle;
	}
	g_iPrintG = dPage1.m_iPrintG;
	dPage2.m_bColorCorrectStr = m_ledData.m_opData.m_bColorCorrectStr;

	//读取公司徵标
	CString strTemp;
	strTemp = g_strCurPath;
	if(g_bEnglish)
		strTemp = strTemp+"Logo1.bmp";
	else
		strTemp = strTemp+"Logo.bmp";
	g_ImageLogo.Load(strTemp);
	
	::PostMessage(g_MainWnd,WM_RE_HEAD,0,0);
}

void CMySpecDoc::OnUpdateOption(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMySpecDoc::OnSeleSdcm() 
{
	// TODO: Add your command handler code here
	CDlgSeleCT dlg;

	dlg.m_iSele  = m_ledData.m_opData.m_iSeleTc;
	dlg.m_iSDCM1 = m_ledData.m_opData.m_iSDCM1;
	dlg.m_iSDCM2 = m_ledData.m_opData.m_iSDCM2;
	
	if(dlg.DoModal() == IDCANCEL)
		return;
	
	m_ledData.m_opData.m_iSeleTc = dlg.m_iSele;
	m_ledData.m_opData.m_iSDCM1  = dlg.m_iSDCM1;
	m_ledData.m_opData.m_iSDCM2  = dlg.m_iSDCM2;

	g_iSeleTc = dlg.m_iSele;
	g_iSDCM1 = dlg.m_iSDCM1;
	g_iSDCM2 = dlg.m_iSDCM2;


	::PostMessage(g_MainWnd,WM_UPDATE,0,0);
}

void CMySpecDoc::OnUpdateSeleSdcm(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
}

void CMySpecDoc::OnTestStop() 
{
	// TODO: Add your command handler code here
	g_bTestCancel = TRUE;

}

void CMySpecDoc::OnUpdateTestStop(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable((g_bTest && g_iTestType == 1) || m_bTemp_PreheatTimeMode);
}

void CMySpecDoc::OnUpdateAppExit(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!g_bTest);
}

void CMySpecDoc::OnSetup() 
{
	// TODO: Add your command handler code here
	CCmdTarget::BeginWaitCursor();
	int iTemp	= g_SPEC.m_iTestType;
	int iTemp1	= g_SPEC.m_iLamp;
	g_SPEC.SPEC_Setting();
	if((g_SPEC.m_iTestType != iTemp || g_SPEC.m_iLamp != iTemp1) && m_ledData.m_listData.GetSize() > 0)
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
			m_ledData.m_iPhType = PH_F;
		}
		if(g_SPEC.m_iTestType == 2)
		{
			m_ledData.m_iPhType = PH_E;
		}
		if(g_SPEC.m_iTestType == 3)
		{
			m_ledData.m_iPhType = PH_I;
		}
		if(g_SPEC.m_iTestType == 4)
		{
			m_ledData.m_iPhType = PH_L;
		}
		if(m_ledData.m_listData.GetSize() <= 0)
		{
			::PostMessage(g_MainWnd,WM_RE_HEAD,0,0);
		}
	}
	CCmdTarget::EndWaitCursor();
}

void CMySpecDoc::OnUpdateSetup(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!g_bTest);
}

void CMySpecDoc::OnButtonTrig() 
{
	// TODO: Add your command handler code here
	if(m_bSet_AutoTime)
	{
		if(g_bEnglish)
		{
			AfxMessageBox("Please cancel auto,you must manu input the integral time!",MB_ICONINFORMATION);
		}
		else
		{
			AfxMessageBox("请取消自动积分模式,触发测试需要手动输入积分时间!",MB_ICONINFORMATION);
		}
		return;
	}
	m_bInt      = FALSE;
	g_iTestType = 0;
	if(!g_bTest)
	{
		::PostMessage(g_MainWnd,WM_TEST_START,0,0);
	}
}

void CMySpecDoc::OnUpdateButtonTrig(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(g_bTest)
	{
		pCmdUI->SetCheck(g_iTestType==0);
	}
	else
	{
		pCmdUI->SetCheck(0);
	}
	pCmdUI->Enable(!g_bTest&&g_SPEC.m_bTrig);
}

void CMySpecDoc::OnExportAccess() 
{
	// TODO: Add your command handler code here
	CString strTemp;
	strTemp		= GetPathName();
	int iLength = strTemp.GetLength();
	int iP		= strTemp.Find(".",iLength - 6);
	strTemp		= strTemp.Left(iP);
//	strTemp = g_strCurPath.Left(g_strCurPath.GetLength()-1);

	//选择导出路径
	static char BASED_CODE szFilter[] = "Access Files(*.mdb)|*.mdb||";
	CFileDialog mOpenFile(TRUE, ".mdb",strTemp,  OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);
	if(mOpenFile.DoModal() == IDCANCEL)
	{
		return;
	}
//	strTemp=mOpenFile.GetFileName();
//	m_database->m_pDatabase->Create(strTemp);
	strTemp=mOpenFile.GetPathName();

	CDaoDatabase m_Db;    //DAO数据库对象；
	CDaoTableDefInfo tinfo;
	CDaoFieldInfo fi;
	CString nDb;
	short m_Nt;           //表的数目；
	int i,j;
	m_Db.Open(strTemp);
	nDb=m_Db.GetName();
	m_Nt=m_Db.GetTableDefCount();
	if(m_Nt!=0)
	{
		CDaoTableDef td(&m_Db);
		if(1)//for(i=0;i<m_Nt;i++)
		{
			i=0;
			m_Db.GetTableDefInfo(i,tinfo);
			if (tinfo.m_lAttributes&dbSystemObject)
			{
//				continue;
			}
			//读取每一个表的字段信息：
			td.Open(tinfo.m_strName);
			short nFields = td.GetFieldCount();
			for(i=0;i<nFields;i++)
			{
				td.GetFieldInfo(i,fi);
				fi.m_nType=0;
			}
			td.Close();
		}
		//读取表名：
		CString tn;
		tn=tinfo.m_strName;
		CDaoRecordset m_set;  //记录集对象
		td.Open(tn);
		m_set.Open(&td);
		//2. 各个项目 各行
		CString str;
		COleVariant var;
		LPCTSTR sTemp;

		m_set.MoveLast();
//		m_set.Edit();
		m_set.AddNew();
		for(j=0;j<m_ledData.m_listData.GetSize();j++)
		{
			CLED300Data *temp=m_ledData.m_listData[j];
//
//			m_set.Update();
//			m_set.AddNew();
//3. 设置各个子项的字符串
			m_set.MoveLast();
			m_set.AddNew();
			int iNTemp=0;
			CString strTemp;
			strTemp.Format("%04d",j+1);
			td.GetFieldInfo(iNTemp,fi);
			sTemp=strTemp;
			m_set.SetFieldValue(iNTemp,sTemp);
			iNTemp++;

			if(1)//m_ledData.m_opData.m_bNote)
			{
				td.GetFieldInfo(iNTemp,fi);
				strTemp=temp->m_spData.m_strNumber;
				sTemp=strTemp;
				m_set.SetFieldValue(iNTemp,sTemp);
				iNTemp++;
			}
			if(1)
			{
				COLORREF color;
				if(g_iLEDClass_Type == 1)
					strTemp = m_ledData.m_newClassLimit.GetLevel(*temp,m_ledData.m_iPhType, color);
				else
					strTemp = m_ledData.m_levelLimit.GetLevel(*temp,m_ledData.m_iPhType);
				sTemp=strTemp;
				m_set.SetFieldValue(iNTemp,sTemp);
				iNTemp++;
			}
			if(1)
			{
				if(temp->m_spData.m_bHaveData)
					strTemp=m_ledData.m_xyZone.IN_ZONE(temp->m_spData.m_x,temp->m_spData.m_y);
				else
					strTemp="";
				sTemp=strTemp;
				m_set.SetFieldValue(iNTemp,sTemp);
				iNTemp++;
			}
			if(1)//if(m_ledData.m_opData.m_bIF)
			{
				if(temp->m_spData.m_bTestF)
					strTemp=g_SPEC.sFormat(temp->m_spData.m_fIF,4);
				else
					strTemp="0.0";
				sTemp=strTemp;
				m_set.SetFieldValue(iNTemp,sTemp);
				iNTemp++;
			}
			if(1)//if(m_ledData.m_opData.m_bVF)
			{
				if(temp->m_spData.m_bTestF)
					strTemp=g_SPEC.sFormat(temp->m_spData.m_fVF,4);
				else
					strTemp="0.0";
			sTemp=strTemp;
			m_set.SetFieldValue(iNTemp,sTemp);
				iNTemp++;
			}
			if(1)//if(m_ledData.m_opData.m_bP)
			{
				if(temp->m_spData.m_bTestF)
					strTemp=g_SPEC.sFormat(temp->m_spData.m_fPow,4);
				else
					strTemp="0.0";
			sTemp=strTemp;
			m_set.SetFieldValue(iNTemp,sTemp);
				iNTemp++;

				if(temp->m_spData.m_bTestF)
					strTemp=g_SPEC.sFormat(temp->m_spData.m_fPF,4);
				else
					strTemp="0.0";
			sTemp=strTemp;
			m_set.SetFieldValue(iNTemp,sTemp);
				iNTemp++;
			}
			if(1)//if(m_ledData.m_opData.m_bPH)
			{
				if(temp->m_spData.m_bTestPH&&temp->m_spData.m_bHaveColorPara)
					strTemp=g_SPEC.sFormat(temp->m_spData.m_fPH,4);
				else
					strTemp="0.0";
			sTemp=strTemp;
			m_set.SetFieldValue(iNTemp,sTemp);
				iNTemp++;
			}
			if(1)//if(m_ledData.m_iPhType==PH_F)
			{
				if(temp->m_spData.m_bTestPH)
					strTemp=g_SPEC.sFormat(temp->m_spData.m_fPh_e*1000,4);
				else
					strTemp="0.0";
			sTemp=strTemp;
			m_set.SetFieldValue(iNTemp,sTemp);
				iNTemp++;
			}
			if(1)//if(m_ledData.m_iPhType==PH_F)   //不一样的地方
			{
				float fEff;
				if(temp->m_spData.m_bTestF&&temp->m_spData.m_bTestPH&&temp->m_spData.m_bHaveColorPara)
				{
					if(temp->m_spData.m_fPow<=0 || temp->m_spData.m_fIF <= 0)
						fEff=0;
					else
						fEff=temp->m_spData.m_fPH/(temp->m_spData.m_fPow);
					strTemp.Format("%.2f",fEff);
				}
				else
					strTemp="0.0";
			sTemp=strTemp;
			m_set.SetFieldValue(iNTemp,sTemp);
				iNTemp++;
			}
			if(1)//if(m_ledData.m_opData.m_bIp)
			{
				if(temp->m_spData.m_bHaveData)
					strTemp.Format("%.0f",temp->m_spData.m_fIp);
				else
					strTemp="0.0";
			sTemp=strTemp;
			m_set.SetFieldValue(iNTemp,sTemp);
				iNTemp++;
			}
			if(1)//if(m_ledData.m_opData.m_bXY)
			{
				if(temp->m_spData.m_bHaveData&&temp->m_spData.m_bHaveColorPara)
					strTemp.Format("%.4f",temp->m_spData.m_x);
				else
					strTemp="0.0000";
				sTemp=strTemp;
				m_set.SetFieldValue(iNTemp,sTemp);
				iNTemp++;

				if(temp->m_spData.m_bHaveData&&temp->m_spData.m_bHaveColorPara)
					strTemp.Format("%.4f",temp->m_spData.m_y);
				else
					strTemp="0.0000";
				sTemp=strTemp;
				m_set.SetFieldValue(iNTemp,sTemp);
				iNTemp++;

				if(temp->m_spData.m_bHaveData&&temp->m_spData.m_bHaveColorPara)
					strTemp.Format("%.4f",temp->m_spData.m_u);
				else
					strTemp="0.0000";
				sTemp=strTemp;
				m_set.SetFieldValue(iNTemp,sTemp);
				iNTemp++;

				if(temp->m_spData.m_bHaveData&&temp->m_spData.m_bHaveColorPara)
					strTemp.Format("%.4f",temp->m_spData.m_v);
				else
					strTemp="0.0000";
				sTemp=strTemp;
				m_set.SetFieldValue(iNTemp,sTemp);
				iNTemp++;
			}
			if(1)//if(m_ledData.m_opData.m_bTc)
			{
				if(temp->m_spData.m_bHaveData&&temp->m_spData.m_bHaveColorPara)
					strTemp.Format("%.0f",temp->m_spData.m_fCCT);
				else
					strTemp="0.0000";
			sTemp=strTemp;
			m_set.SetFieldValue(iNTemp,sTemp);
				iNTemp++;
			}
			if(1)//if(m_ledData.m_opData.m_bLd)
			{
				if(temp->m_spData.m_bHaveData&&temp->m_spData.m_bHaveColorPara)
					strTemp.Format("%.1f",temp->m_spData.m_fMainlambda);
				else
					strTemp="0.0000";
			sTemp=strTemp;
			m_set.SetFieldValue(iNTemp,sTemp);
				iNTemp++;
			}
			if(1)//if(m_ledData.m_opData.m_bPur)
			{
				if(temp->m_spData.m_bHaveData&&temp->m_spData.m_bHaveColorPara)
					strTemp.Format("%.1f",temp->m_spData.m_fPurity);
				else
					strTemp="0.0000";
			sTemp=strTemp;
			m_set.SetFieldValue(iNTemp,sTemp);
				iNTemp++;
			}
			if(1)//if(m_ledData.m_opData.m_bLp)
			{
				if(temp->m_spData.m_bHaveData)
					strTemp.Format("%.1f",temp->m_spData.m_fMaxlambda);
				else
					strTemp="0.0000";
			sTemp=strTemp;
			m_set.SetFieldValue(iNTemp,sTemp);
				iNTemp++;
			}
			if(1)//if(m_ledData.m_opData.m_bHW)
			{
				if(temp->m_spData.m_bHaveData)
					strTemp.Format("%.1f",temp->m_spData.m_fHalflambda);
				else
					strTemp="0.0000";
				sTemp=strTemp;
				m_set.SetFieldValue(iNTemp,sTemp);
				iNTemp++;
			}
			if(1)//if(m_ledData.m_opData.m_bRR)
			{
				if(temp->m_spData.m_bHaveData&&temp->m_spData.m_bHaveColorPara)
					strTemp.Format("%.1f",temp->m_spData.m_fRedRatio);
				else
					strTemp="0.0000";
				sTemp=strTemp;
				m_set.SetFieldValue(iNTemp,sTemp);
				iNTemp++;
			}
			if(1)//if(m_ledData.m_opData.m_bRa)
			{
				if(temp->m_spData.m_bHaveData&&temp->m_spData.m_bHaveColorPara)
					strTemp.Format("%.1f",temp->m_spData.m_fRa);
				else
					strTemp="0.0000";
				sTemp=strTemp;
				m_set.SetFieldValue(iNTemp,sTemp);
				iNTemp++;
			}
			//导出测试信息
			if(1)//if(m_ledData.m_opData.m_bRa)
			{
				sTemp=temp->m_spData.m_strModel;
				m_set.SetFieldValue(iNTemp,sTemp);
				iNTemp++;

				sTemp=temp->m_spData.m_strNumber;
				m_set.SetFieldValue(iNTemp,sTemp);
				iNTemp++;

				sTemp=temp->m_spData.m_strFactory;
				m_set.SetFieldValue(iNTemp,sTemp);
				iNTemp++;

				sTemp=temp->m_spData.m_strT;
				m_set.SetFieldValue(iNTemp,sTemp);
				iNTemp++;

				sTemp=temp->m_spData.m_strH;
				m_set.SetFieldValue(iNTemp,sTemp);
				iNTemp++;

				sTemp=temp->m_spData.m_strTester;
				m_set.SetFieldValue(iNTemp,sTemp);
				iNTemp++;

				sTemp=temp->m_spData.m_strDate;
				m_set.SetFieldValue(iNTemp,sTemp);
				iNTemp++;

				sTemp=temp->m_spData.m_strRemark;
				m_set.SetFieldValue(iNTemp,sTemp);
				iNTemp++;
			}
			m_set.Update();
			m_set.MoveLast();
			m_set.AddNew();
		}
		m_set.MoveLast();
		m_set.Close();
	}
	if(g_bEnglish)
		AfxMessageBox("Save the data succeed!");
	else
		AfxMessageBox("数据保存成功!");
}

void CMySpecDoc::OnUpdateExportAccess(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_ledData.m_listData.GetSize()>0);
}

void CMySpecDoc::OnPower() 
{
	// TODO: Add your command handler code here
	if(1)
	{
		int iCur=m_nActive+m_iB;
		if(iCur>=0&&iCur<m_ledData.m_listData.GetSize())
		{
			CDlgInputPower dlg;

			dlg.m_fI   = m_ledData.m_listData[iCur]->m_spData.m_fIF;
			dlg.m_fU   = m_ledData.m_listData[iCur]->m_spData.m_fVF;
			dlg.m_fP   = m_ledData.m_listData[iCur]->m_spData.m_fPow;
			dlg.m_fPF  = m_ledData.m_listData[iCur]->m_spData.m_fPF;

			if(dlg.DoModal()==IDOK)
			{
				m_ledData.m_listData[iCur]->m_spData.m_bTestF=TRUE;
				m_ledData.m_listData[iCur]->m_spData.m_fIF  = dlg.m_fI;
				m_ledData.m_listData[iCur]->m_spData.m_fVF  = dlg.m_fU;
				m_ledData.m_listData[iCur]->m_spData.m_fPow = dlg.m_fP;
				m_ledData.m_listData[iCur]->m_spData.m_fPF  = dlg.m_fPF;

				//更新界面
				m_tempData.m_spData.m_fIF  = dlg.m_fI;
				m_tempData.m_spData.m_fVF  = dlg.m_fU;
				m_tempData.m_spData.m_fPow = dlg.m_fP;
				m_tempData.m_spData.m_fPF  = dlg.m_fPF;

				g_bHaveMode	= TRUE;
				m_bReList	= TRUE;
				UpdateAllViews(NULL);
				g_bHaveMode	= FALSE;

				SetModifiedFlag(TRUE);
			}
		}
	}
}

void CMySpecDoc::OnUpdatePower(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(g_bPowerMod)
	{
		int iCur=m_nActive+m_iB;
		if(iCur>=0&&iCur<m_ledData.m_listData.GetSize())
			pCmdUI->Enable(g_bPowerMod);
		else
			pCmdUI->Enable(FALSE);
	}
}

void CMySpecDoc::OnCheckBw() 
{
	// TODO: Add your command handler code here
	CDlgCheckBW dlg;
	dlg.DoModal();
}

void CMySpecDoc::OnUpdateCheckBw(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!g_bTest);
	
}

void CMySpecDoc::OnExportAllSpec() 
{
	// TODO: Add your command handler code here
	CString strTemp;
	strTemp=GetPathName();
	int iP=strTemp.Find(".",0);
	strTemp=strTemp.Left(iP);
	
	static char BASED_CODE szFilter[]="Excel Files(*.CSV)|*.CSV||";
	CFileDialog mOpenFile(FALSE, ".CSV", strTemp,  OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);
	if(mOpenFile.DoModal()==IDCANCEL) 
		return;
	
	CString strPathName = mOpenFile.GetPathName();
	
	BOOL bR;
	bR = m_ledData.Export_CSV_ALL(strPathName, m_ledData.m_opData.m_fExportIntervalWL);
	if(!bR)
	{
		if(g_bEnglish)
			AfxMessageBox("Export fail!",MB_ICONINFORMATION);
		else
			AfxMessageBox("导出数据文件失败!",MB_ICONINFORMATION);
	}
	return;
}

void CMySpecDoc::OnUpdateExportAllSpec(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_ledData.m_listData.GetSize() > 0);		
}

void CMySpecDoc::OnExportLampDat() 
{
	// TODO: Add your command handler code here
	CDlgExportLamp dlg;
	dlg.m_spData = m_tempData.m_spData;//m_ledData.m_listData[m_nActive]->m_spData;
	dlg.DoModal();
}

void CMySpecDoc::OnUpdateExportLampDat(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMySpecDoc::OnModGe() 
{
	// TODO: Add your command handler code here
	CDlgReGe dlg;
	int iR;
	dlg.m_fGeWL1 = g_SPEC.m_fReGeWL1;
	dlg.m_fGeWL2 = g_SPEC.m_fReGeWL2;
	
	iR = dlg.DoModal();
	if(iR == IDCANCEL)
	{
		return;
	}
	g_SPEC.m_fReGeWL1 = dlg.m_fGeWL1;
	g_SPEC.m_fReGeWL2 = dlg.m_fGeWL2;
	
	m_bReList = TRUE;
	UpdateAllViews(NULL);
}

void CMySpecDoc::OnUpdateModGe(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_ledData.m_listData.GetSize()>0);
}

void CMySpecDoc::OnExportPhs() 
{
	// TODO: Add your command handler code here
	//导出PHS格式文件

	CString sPathName;
	static char szFilter[]="PHS Files(*.p5)|*.p5||";
	CFileDialog dOpen(FALSE,".p5",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter,NULL);
	if(dOpen.DoModal()==IDCANCEL)
		return;
	sPathName=dOpen.GetPathName();
	CFile sFile;
	if(!sFile.Open(sPathName,CFile::modeCreate|CFile::modeReadWrite))
	{
		return;
	}
	CArchive ar(&sFile,CArchive::store);
	
	int i;
	float sct1,sct2,Rp;
	int sct,Ip;
	int Rm,Rf,darkms,darkrs;
	float vol,cur,power,pf,vol2,cur2,power2,pf2;
	int hval,signs;
	float ys1,ys2,effic;
	CString m_date,m_temperature,m_operator,m_hum,m_type,m_manufacture;
	
	hval	=0;
	Rp		=0;
	Ip		=0;
	Rm		=0;
	Rf		=0;
	darkms	=0;
	darkrs	=0;
	vol		=0;
	cur		=0;
	power	=0;
	pf		=0;
	vol2	=0;
	cur2	=0;
	power2	=0;
	pf2		=0;
	ys1		=0;
	ys2		=0;
	effic	=0;
	m_date	="";
	m_temperature="";
	m_operator	 ="";
	m_type		 ="";
	m_manufacture="";
	
	CString sStr;
	sStr="PMSW";
	ar<<sStr;
	sct=0;
	signs=0;
	ar<<signs;
	sct1=380.0f;
	sct2=780.0f;
	sct=85;
	ar<<sct1<<sct2<<sct<<Rm<<Rf<<darkms<<darkrs<<Ip<<Rp<<hval;
	int iN=m_tempData.m_spData.m_fRelSpect.GetSize();
	int MM = 50;
	
	float fTemp;
	for(i = 0; i < sct; i++)
	{
		fTemp = m_tempData.m_spData.m_fRelSpect[iN-1-i*MM];
		ar << fTemp;
	}
	ar<<ys1<<effic;
	ar<<ys2;
	ar<<vol<<cur<<power<<pf;
	ar<<vol2<<cur2<<power2<<pf2;
	ar<<m_type<<m_operator<<m_hum<<m_temperature<<m_manufacture<<m_date;
	
	ar.Close();
	sFile.Close();
}

void CMySpecDoc::OnUpdateExportPhs(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_ledData.m_listData.GetSize()>0);
}
