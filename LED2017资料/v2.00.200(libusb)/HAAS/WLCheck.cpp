// WLCheck.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "WLCheck.h"
#include "MainFrm.h"
#include "math.h"
#include "Global_MySpec.h"
#include "Note.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWLCheck dialog
extern BOOL g_bFunDebug;
extern float g_fSpect1;
extern float g_fSpect2;


CWLCheck::CWLCheck(CWnd* pParent /*=NULL*/)
	: CDialog(CWLCheck::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWLCheck)
	m_bAuto		= TRUE;
	m_iAvgN		= 1;
	m_fIntTime	= 100.0f;
	m_bShowCur	= FALSE;
	m_iType		= 0;
	m_fStaWL	= 0.0f;
	//}}AFX_DATA_INIT

	CString  strSection  = "Check";

	CString  strIntTime  = "IntTime";
	CString  strAutoTime = "AutoTime";
	CString  strAvgN     = "AvgN";

	CString strTemp;
	strTemp    = AfxGetApp()->GetProfileString(strSection,strIntTime,"100");
	m_fIntTime = (float)atof(strTemp);
	m_bAuto    = AfxGetApp()->GetProfileInt(strSection,strAutoTime,FALSE);
	m_iAvgN    = AfxGetApp()->GetProfileInt(strSection,strAvgN,1);

	m_drawData.bMouse	= FALSE;
	m_drawData.iCurSele	= 0;
	m_drawData.bShowCur	= TRUE;
	m_drawData.iDrawType= 0;
	m_drawData.iB		= 0;
	m_drawData.iE		= 0;

	CString strShowCur  = "ShowCur";
	CString strDrawType = "DrawType";

	m_bShowCur=AfxGetApp()->GetProfileInt(strSection,strShowCur,TRUE);
	m_drawData.bShowCur=m_bShowCur;
	m_drawData.iDrawType=AfxGetApp()->GetProfileInt(strSection,strDrawType,1);

	m_iPerTime=(int)(m_fIntTime);
}


void CWLCheck::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWLCheck)
	DDX_Control(pDX, IDC_EDIT_DW, m_cDW);
	DDX_Control(pDX, IDC_RADIO_TYPE1, m_cType1);
	DDX_Control(pDX, IDC_RADIO_TYPE2, m_cType2);
	DDX_Control(pDX, IDC_BUTTON_CORR, m_cCorr);
	DDX_Control(pDX, IDC_BUTTON_RR, m_cRR);
	DDX_Control(pDX, IDC_BUTTON_R, m_cR);
	DDX_Control(pDX, IDC_BUTTON_LL, m_cLL);
	DDX_Control(pDX, IDC_BUTTON_L, m_cL);
	DDX_Control(pDX, IDC_EV, m_cEV);
	DDX_Control(pDX, IDC_AVG_ERR, m_cAvgError);
	DDX_Control(pDX, IDC_EDIT_AVG_N, m_cAvgN);
	DDX_Control(pDX, IDC_EDIT_INT_TIME, m_cIntTime);
	DDX_Control(pDX, IDCANCEL, m_cExit);
	DDX_Control(pDX, IDC_LIST2, m_cListWL);
	DDX_Control(pDX, IDC_IP, m_cIP);
	DDX_Control(pDX, IDC_DRAW, m_cDraw);
	DDX_Control(pDX, IDC_CHECK_AUTO, m_cAuto);
	DDX_Control(pDX, IDC_BUTTON_TEST, m_cTest);
	DDX_Control(pDX, IDC_BUTTON_STOP, m_cStop);
	DDX_Control(pDX, IDC_BUTTON_START, m_cStart);
	DDX_Check(pDX, IDC_CHECK_AUTO, m_bAuto);
	DDX_Text(pDX, IDC_EDIT_AVG_N, m_iAvgN);
	DDV_MinMaxInt(pDX, m_iAvgN, 1, 50);
	DDX_Text(pDX, IDC_EDIT_INT_TIME, m_fIntTime);
	DDV_MinMaxFloat(pDX, m_fIntTime, 0.1f, 60000.f);
	DDX_Check(pDX, IDC_CHECK_CUR, m_bShowCur);
	DDX_Radio(pDX, IDC_RADIO_TYPE1, m_iType);
	DDX_Text(pDX, IDC_EDIT_PX, m_fStaWL);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWLCheck, CDialog)
	//{{AFX_MSG_MAP(CWLCheck)
	ON_BN_CLICKED(IDC_BUTTON_TEST, OnButtonTest)
	ON_BN_CLICKED(IDC_BUTTON_START, OnButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	ON_BN_CLICKED(IDC_CHECK_AUTO, OnCheckAuto)
	ON_BN_CLICKED(IDC_BUTTON_LL, OnButtonLl)
	ON_BN_CLICKED(IDC_BUTTON_L, OnButtonL)
	ON_BN_CLICKED(IDC_BUTTON_R, OnButtonR)
	ON_BN_CLICKED(IDC_BUTTON_RR, OnButtonRr)
	ON_BN_CLICKED(IDC_CHECK_CUR, OnCheckCur)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON_CORR, OnButtonCorr)
	ON_BN_CLICKED(IDC_RADIO_TYPE1, OnRadioType1)
	ON_BN_CLICKED(IDC_RADIO_TYPE2, OnRadioType2)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_NOTIFY(HDN_ITEMCHANGED, IDC_LIST2, OnItemchangedList2)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, OnItemchangedList2)
	ON_BN_CLICKED(IDC_BUTTON_TEST3, OnButtonTest3)
	//}}AFX_MSG_MAP
	ON_NOTIFY ( NM_CUSTOMDRAW, IDC_LIST2, OnCustomdrawMyList )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWLCheck message handlers

void CWLCheck::OnOK() 
{
	// TODO: Add extra validation here
	
//	CDialog::OnOK();
}

BOOL CWLCheck::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	for(int i=0;i<4;i++)
		m_fErr[i]=0;

	m_cL.EnableWindow(m_bShowCur);
	m_cR.EnableWindow(m_bShowCur);
	m_cLL.EnableWindow(m_bShowCur);
	m_cRR.EnableWindow(m_bShowCur);
	
	m_spData.m_bHaveData=FALSE;
	m_spData.m_iDataType=TYPE_CHECK;

	m_drawData.iHave=0;
	if(g_bFunDebug)
	{
		m_cType1.ShowWindow(TRUE);
		m_cType2.ShowWindow(TRUE);
	}
	else
	{
		m_iType = 1;
		m_cType1.ShowWindow(FALSE);
		m_cType2.ShowWindow(FALSE);
	}

	m_cIntTime.EnableWindow(!m_bAuto);

	m_cIP.SetTextColor(RGB(0,0,255))
		.SetFontUnderline(TRUE);

	m_cIP.SetWindowText("");

	m_cAvgError.SetTextColor(RGB(0,0,255))
		.SetFontUnderline(TRUE);

	m_cAvgError.SetWindowText("");

	m_cListWL.SetExtendedStyle(m_cListWL.GetExtendedStyle()  | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP|LVS_EX_CHECKBOXES);

	m_cEV.SetLink(TRUE)
		.SetTextColor(RGB(0,0,255))
		.SetFontUnderline(TRUE)
		.SetLinkCursor(AfxGetApp()->LoadCursor(IDC_HAND));

	WLSET_Load();

	ReListWL();
	ReDraw();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CWLCheck::ReDraw()
{
	m_drawData.iChekStaN=0;


	for(int i=0;i<g_SPEC.m_arra_fStaWL.GetSize();i++)
	{
		BOOL bCheck=m_cListWL.GetCheck(i);
		float fWL=g_SPEC.m_arra_fStaWL[i];
		if(bCheck&&fWL>g_SPEC.T_SPECT1&&fWL<g_SPEC.T_SPECT2)
		{
			m_drawData.fCheckStaWL[m_drawData.iChekStaN] = fWL;
			m_drawData.iChekStaN++;
		}
	}

	m_cDraw.DrawSpect(m_spData,m_drawData,"");

	ShowErr();
}

void CWLCheck::ReListWL()
{
	m_cListWL.DeleteAllItems();
	while(1)
	{
		if(m_cListWL.DeleteColumn(0)==FALSE)
			break;
	}

	int iN=0;

	CString strTemp;

	if(g_bEnglish)
		strTemp="Lamp";
	else
		strTemp="标准灯";
	m_cListWL.InsertColumn(iN,strTemp);
	m_cListWL.SetColumnWidth(iN,100);
	iN++;

	if(g_bEnglish)
		strTemp="WL(nm)";
	else
		strTemp="谱线(nm)";
	m_cListWL.InsertColumn(iN,strTemp);
	m_cListWL.SetColumnWidth(iN,70);
	iN++;

	if(g_bEnglish)
		strTemp="Error(nm)";
	else
		strTemp="误差(nm)";
	m_cListWL.InsertColumn(iN,strTemp);
	m_cListWL.SetColumnWidth(iN,70);
	iN++;

	if(g_bFunDebug == TRUE)
	{
		if(g_bEnglish)
			strTemp="Bandwidth(nm)";
		else
			strTemp="带宽(nm)";
		m_cListWL.InsertColumn(iN,strTemp);
		m_cListWL.SetColumnWidth(iN,70);
		iN++;
	}

	int NN=g_SPEC.m_arra_strSource.GetSize();
	for(int i=0;i<NN;i++)
	{
		iN=0;

		strTemp=g_SPEC.m_arra_strSource[i];
		m_cListWL.InsertItem(i,strTemp,5);
		iN++;

		strTemp.Format("%7.2f",g_SPEC.m_arra_fStaWL[i]);
		m_cListWL.SetItemText(i,iN,strTemp);
		iN++;


		for(int j=0;j<m_drawData.iChekStaN;j++)
		{
			if(g_SPEC.m_arra_fStaWL[i]==m_drawData.fCheckStaWL[j])
			{
				m_cListWL.SetCheck(i,TRUE);
				break;
			}
		}
	}
}

UINT ThreadWLCheck(LPVOID pParam)
{
	CWLCheck* pDlg=(CWLCheck*)pParam;
	BOOL bR;
	CString strTemp;
	int iN=0;
	while(1)
	{
		bR=pDlg->Test();
		if(!bR)
		{
			break;
		}
		if(g_bEnglish)
			CMainFrame::ShowNote("Complete!");
		else
			CMainFrame::ShowNote("完成!");
		if(pDlg->m_iTestType==0)
			break;
		iN++;

		if(pDlg->m_bCancel)
		{
			if(g_bEnglish)
				CMainFrame::ShowNote("Cancel!");
			else
				CMainFrame::ShowNote("取消测试!");
			break;
		}
		Sleep(100);
	}
	pDlg->ShowEnable(FALSE);
	return 0;
}

void CWLCheck::OnButtonTest() 
{
	// TODO: Add your control notification handler code here
	if(UpdateData(TRUE)==FALSE)
		return;
	m_iTestType=0;
	m_bCancel=FALSE;
	ShowEnable(TRUE);
	//开副线程
	AfxBeginThread(ThreadWLCheck,this);
}

void CWLCheck::OnButtonStart() 
{
	// TODO: Add your control notification handler code here
	if(UpdateData(TRUE)==FALSE)
		return;
	m_iTestType=1;
	m_bCancel=FALSE;
	g_SPEC.m_fInterval=0.1f;
	ShowEnable(TRUE);
	//开副线程
	AfxBeginThread(ThreadWLCheck,this);
}

void CWLCheck::OnButtonStop() 
{
	// TODO: Add your control notification handler code here
	m_bCancel=TRUE;
	m_cStop.EnableWindow(FALSE);
}

void CWLCheck::OnCancel() 
{
	// TODO: Add extra cleanup here
	CString  strSection  = "Check";

	CString  strIntTime  = "IntTime";
	CString  strAutoTime = "AutoTime";
	CString  strAvgN     = "AvgN";

	CString strTemp;
	strTemp.Format("%f",m_fIntTime);
	AfxGetApp()->WriteProfileString(strSection,strIntTime,strTemp);
	AfxGetApp()->WriteProfileInt(strSection,strAutoTime,m_bAuto);
	AfxGetApp()->WriteProfileInt(strSection,strAvgN,m_iAvgN);
	
	CString strShowCur  = "ShowCur";
	CString strDrawType = "DrawType";

	AfxGetApp()->WriteProfileInt(strSection,strShowCur,m_bShowCur);
	AfxGetApp()->WriteProfileInt(strSection,strDrawType,m_drawData.iDrawType);

	WLSET_Save();

	CDialog::OnCancel();
}

BOOL CWLCheck::Test()
{
	BOOL bR;
	CString strTemp;
	int iTemp=g_SPEC.m_iMode;
	if(m_bAuto)
	{
		//Auto
		if(g_bEnglish)
			strTemp.Format("Auto Time...");
		else
			strTemp.Format("自动积分...");
		CMainFrame::ShowNote(strTemp,TRUE,RGB(255,0,255));

		float fIntTime;
		int iLimitTime=g_SPEC.m_iAutoLimitTime2;
		float fLK=0.2f;
		//对于HAAS-2000的不同点
		fLK=0.36f;

		bR=g_SPEC.SPEC_GetAutoTime(fIntTime,iLimitTime,fLK,m_fIntTime);  //0.2f;
		if(!bR)
		{
			if(g_bEnglish)
				strTemp.Format("");
			else
				strTemp.Format("");
			CMainFrame::ShowNote(strTemp,TRUE,RGB(255,0,255));
			return FALSE;
		}

		if(fIntTime<=g_SPEC.m_fIntTime1)
			fIntTime=g_SPEC.m_fIntTime1;
		if(fIntTime>=iLimitTime)
			fIntTime=iLimitTime*1.0f;
		m_fIntTime=fIntTime;
	}

	//光谱测试
	float fMax;
	if(g_bEnglish)
		strTemp.Format("Scan Spectrum[%.0fms]...",m_fIntTime);
	else
		strTemp.Format("正在光谱扫描[%.0fms]...",m_fIntTime);
	CMainFrame::ShowNote(strTemp,TRUE,RGB(255,0,0));
// 	if(m_iPerTime!=(int)(m_fIntTime))
// 		bR=g_SPEC.SPEC_DoScan(m_fIntTime,m_iAvgN,MY_TRIG_NORMAL,fMax,TRUE,TYPE_CHECK);
// 	else
		bR=g_SPEC.SPEC_DoScan(m_fIntTime,m_iAvgN,MY_TRIG_NORMAL,fMax,FALSE,TYPE_CHECK);
	if(!bR)
	{
		if(g_bEnglish)
			strTemp.Format("Fail[Spectrum]!");
		else
			strTemp.Format("控制光谱仪失败!");
		CMainFrame::ShowNote(strTemp,TRUE,RGB(255,0,0));
		g_SPEC.MyBeep(750);
		return FALSE;   
	}
	if(m_fIntTime<1)
		strTemp.Format("%.2f",m_fIntTime);
	else
		strTemp.Format("%.0f",m_fIntTime);
	m_iPerTime=(int)(m_fIntTime);
	m_cIntTime.SetWindowText(strTemp);

	strTemp.Format("%.0f(%.0f%%)",fMax,fMax*100/(g_SPEC.m_nADW-1));
	m_cIP.SetWindowText(strTemp);
	m_cIP.SetFontUnderline(TRUE);
	if((fMax/(g_SPEC.m_nADW-1))<T_L||(fMax>=(g_SPEC.m_nADW-1)))
		m_cIP.SetTextColor(RGB(255,0,0));
	else
		m_cIP.SetTextColor(RGB(0,0,255));

	//信号溢出
	bR=g_SPEC.SPEC_OVER(fMax);
	if(bR)
	{
		if(g_bEnglish)
			strTemp.Format("Ip Overflow,please retry...");
		else
			strTemp.Format("Ip 溢出,请减少积分时间,再重新测试...");
		CMainFrame::ShowNote(strTemp,TRUE,RGB(255,0,0));
		g_SPEC.MyBeep(750);
		if(g_bEnglish)
			CNote::Passtext(CString(_T("Overflow!please adjust...")));
		else
			CNote::Passtext(CString(_T("信号溢出!请调节...")));
		CNote::Show(this);
		Sleep(800);
		CNote::Destroy();

		//溢出时调整积分时间
		/////////////////////////////////
		if(m_bAuto)
		{
			if(m_fIntTime<100)
				m_fIntTime=m_fIntTime*0.9f;
			else
				m_fIntTime=m_fIntTime*0.5f;
			if(m_fIntTime<g_SPEC.m_fIntTime1)
				m_fIntTime=g_SPEC.m_fIntTime1;
		}
		/////////////////////////////////

		//溢出不返回FALSE
///		return TRUE;  //overflow
	}

	//计算色度
	if(g_bEnglish)
		strTemp.Format("calculating...");
	else
		strTemp.Format("正在计算...");
	CMainFrame::ShowNote(strTemp);
	g_SPEC.SPEC_GetSpectData(FALSE,m_spData,FALSE);

	//没有溢出时调整积分时间
	/////////////////////////////////
	if(m_bAuto)
	{
		if(m_spData.m_fIp/(m_spData.m_nADW-1)<=(g_SPEC.m_fOverK*0.8f))
		{
			float fTemp1=m_spData.m_nADW*(g_SPEC.m_fOverK*0.7f)-g_SPEC.m_iDark;
			float fTemp2=m_spData.m_fIp-g_SPEC.m_iDark;
			m_fIntTime=(fTemp1*m_fIntTime)/fTemp2;
		}
		if(m_fIntTime>g_SPEC.m_iAutoLimitTime2)
			m_fIntTime=g_SPEC.m_iAutoLimitTime2*1.0f;
		if(m_fIntTime>=1.0f)
			m_fIntTime=(int)(m_fIntTime)*1.0f;
	}
	/////////////////////////////////
	m_cCorr.EnableWindow(TRUE);

	ReDraw();
	g_SPEC.m_iMode=iTemp;


	float fDW;
	bR = m_spData.GetDW(546.07f, fDW);
	if(bR)
		strTemp.Format("%.1f", fDW);
	else
		strTemp = "";
	m_cDW.SetWindowText(strTemp);

	return TRUE;
}

void CWLCheck::ShowEnable(BOOL bStart)
{
	if(!m_bAuto)
		m_cIntTime.EnableWindow(!bStart);
	m_cAuto.EnableWindow(!bStart);
	m_cAvgN.EnableWindow(!bStart);
	m_cTest.EnableWindow(!bStart);
	m_cStart.EnableWindow(!bStart);
	if(m_iTestType==1)
		m_cStop.EnableWindow(bStart);
	m_cExit.EnableWindow(!bStart);
}

void CWLCheck::OnCheckAuto() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_cIntTime.EnableWindow(!m_bAuto);
}

void CWLCheck::ShowErr()
{
	float fWL[10001];
	float fPL[10001];
	int iN = m_spData.m_fRelSpect.GetSize();
	int i;
	int j;
	int iPeak;

	float fTemp = 0;
	
	float fMax = 0;
	for(i = 0; i < iN; i++)
	{
		fWL[i] = m_spData.m_fSpect1 + m_spData.m_fInterval * i;
		fPL[i] = m_spData.m_fRelSpect[i];
		if(fPL[i]>fMax)
		{
			fMax=fPL[i];
		}
	}

	for(j=0;j<g_SPEC.m_arra_fStaWL.GetSize();j++)
	{
		m_cListWL.SetItemText(j,2,"");
	}

	float fAvgErr=0;
	int   iErrN=0;
	CString strTemp;

	for(j = 0; j < m_drawData.iChekStaN; j++)
	{
		float fBW;
		iPeak = g_SPEC.GetWL12peakPos(fWL, fPL, iN, m_drawData.fCheckStaWL[j] - 3, m_drawData.fCheckStaWL[j] + 3, fBW);
		if(m_drawData.fCheckStaWL[j] > 760 && m_drawData.fCheckStaWL[j] < 764)
		{
			float fTempWL[10001];
			float fTempPL[10001];
			//763.51 特殊计算
			for(i = 0; i < iN; i++)
			{
				if(fWL[i] >= 760)
				{
					fTemp = fPL[i];
					break;
				}
			}

			for(i = 0; i < iN; i++)
			{
				fTempWL[i] = fWL[i];
				fTempPL[i] = fPL[i] - fTemp;
			}

			//注意
			float fHalf = 0.5f;
			iPeak=g_SPEC.GetWL12peakPos(fTempWL,fTempPL,iN,m_drawData.fCheckStaWL[j]-3,m_drawData.fCheckStaWL[j]+3, fBW,fHalf);
		}


		if(g_bFunDebug && m_iType == 0)
		{
			iPeak=0;
			float fMax=0;
			for(int i=0;i<iN;i++)
			{
				if(fWL[i]>=m_drawData.fCheckStaWL[j]-3&&fWL[i]<=m_drawData.fCheckStaWL[j]+3)
				{
					if(fPL[i]>fMax)
					{
						fMax=fPL[i];
						iPeak=i;
					}
				}
			}
		}

		float fError;
		fError=m_drawData.fCheckStaWL[j] - (iPeak * g_SPEC.m_fInterval+m_spData.m_fSpect1);
		strTemp.Format("%7.2f",fError);
		int iSele=-1;
		for(int t=0;t<g_SPEC.m_arra_fStaWL.GetSize();t++)
		{
			if(g_SPEC.m_arra_fStaWL[t]==m_drawData.fCheckStaWL[j])
			{
				iSele=t;
				break;
			}
		}
		if(iSele!=-1)
		{
			if(fabs(fError)>=3.0f)
			{
				m_cListWL.SetItemText(iSele,2,"   ---");
			}
			else
			{
				m_cListWL.SetItemText(iSele,2,strTemp);
			}

			if(g_bFunDebug == TRUE)
			{
				float fDW;
				BOOL bR;
				bR = m_spData.GetDW(g_SPEC.m_arra_fStaWL[t], fDW);
				if(bR ==TRUE)
					strTemp.Format("%4.1f",fDW);
				else
					strTemp = "";
				m_cListWL.SetItemText(iSele,3,strTemp);
			}
		}
	}

	if(iErrN>0)
	{
		fAvgErr=fAvgErr/iErrN;
		strTemp.Format("%.2f nm",fAvgErr);
	}
	else
		strTemp="";
	m_cAvgError.SetWindowText(strTemp);
}

BOOL CWLCheck::WLSET_Load()
{
	FILE *fp;
	if((fp=fopen(g_strCurPath+"wlcheck.dat","rt"))==0)
		return FALSE;
	else
	{
		fscanf(fp,"N:%d\n",&m_drawData.iChekStaN);
		for(int i=0;i<m_drawData.iChekStaN;i++)
			fscanf(fp,"%f\n",&m_drawData.fCheckStaWL[i]);
		fclose(fp);
		return TRUE;
	}
}

BOOL CWLCheck::WLSET_Save()
{
	FILE *fp;
	if((fp=fopen(g_strCurPath+"wlcheck.dat","wt"))==0)
		return FALSE;
	else
	{
		fprintf(fp,"N:%d\n",m_drawData.iChekStaN);
		for(int i=0;i<m_drawData.iChekStaN;i++)
			fprintf(fp,"%.2f\n",m_drawData.fCheckStaWL[i]);
		fclose(fp);
		return TRUE;
	}
}

void CWLCheck::OnCustomdrawMyList ( NMHDR* pNMHDR, LRESULT* pResult )
{
	//This code based on Michael Dunn's excellent article on
	//list control custom draw at http://www.codeproject.com/listctrl/lvcustomdraw.asp

	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>( pNMHDR );

	// Take the default processing unless we set this to something else below.
	*pResult = CDRF_DODEFAULT;

	// First thing - check the draw stage. If it's the control's prepaint
	// stage, then tell Windows we want messages for every item.
	if ( CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage )
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
	}
	else if ( CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage )
	{
		// This is the notification message for an item.  We'll request
		// notifications before each subitem's prepaint stage.

		*pResult = CDRF_NOTIFYSUBITEMDRAW;
	}
	else if ( (CDDS_ITEMPREPAINT | CDDS_SUBITEM) == pLVCD->nmcd.dwDrawStage )
	{
		
		COLORREF clrNewTextColor, clrNewBkColor;

		int    nItem = static_cast<int>( pLVCD->nmcd.dwItemSpec );

//		CString strTemp = m_ctListCtrl.GetItemText(nItem,pLVCD->iSubItem);

		if(pLVCD->iSubItem==2&&m_cListWL.GetCheck(nItem))//strTemp == m_strName)
		{
			clrNewTextColor = RGB(255,0,0);		//Set the text to red
			clrNewBkColor = RGB(190, 223, 255);		//Set the bkgrnd color to blue
		}
		else
		{
			
			clrNewTextColor = RGB(0,0,0);		//Leave the text black
			clrNewBkColor = RGB(255,255,255);	//leave the bkgrnd color white
		}

		pLVCD->clrText = clrNewTextColor;
		pLVCD->clrTextBk = clrNewBkColor;

		// Tell Windows to paint the control itself.
		*pResult = CDRF_DODEFAULT;
	}
}

void CWLCheck::OnButtonLl() 
{
	// TODO: Add your control notification handler code here
	m_drawData.iCurSele=m_drawData.iCurSele-5;
	m_drawData.iB	= m_drawData.iCurSele;
	m_drawData.iE	= m_drawData.iCurSele;
	m_drawData.bMouse=FALSE;
	ReDraw();
}

void CWLCheck::OnButtonL() 
{
	// TODO: Add your control notification handler code here
	m_drawData.iCurSele=m_drawData.iCurSele-1;
	m_drawData.iB	= m_drawData.iCurSele;
	m_drawData.iE	= m_drawData.iCurSele;
	m_drawData.bMouse=FALSE;
	ReDraw();
}

void CWLCheck::OnButtonR() 
{
	// TODO: Add your control notification handler code here
	m_drawData.iCurSele=m_drawData.iCurSele+1;
	m_drawData.iB	= m_drawData.iCurSele;
	m_drawData.iE	= m_drawData.iCurSele;
	m_drawData.bMouse=FALSE;
	ReDraw();
}

void CWLCheck::OnButtonRr() 
{
	// TODO: Add your control notification handler code here
	m_drawData.iCurSele=m_drawData.iCurSele+5;
	m_drawData.iB	= m_drawData.iCurSele;
	m_drawData.iE	= m_drawData.iCurSele;
	m_drawData.bMouse=FALSE;
	ReDraw();
}

void CWLCheck::OnCheckCur() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_drawData.bShowCur=m_bShowCur;
	ReDraw();

	m_cL.EnableWindow(m_bShowCur);
	m_cR.EnableWindow(m_bShowCur);
	m_cLL.EnableWindow(m_bShowCur);
	m_cRR.EnableWindow(m_bShowCur);
}

void CWLCheck::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CRect Rect1,Rect2;
	GetClientRect(&Rect1);
	ClientToScreen(&Rect1);
	m_cDraw.GetClientRect(&Rect2);
	m_cDraw.ClientToScreen(&Rect2);
	if(((point.y+Rect1.top)>=Rect2.top)&&((point.y+Rect1.top)<=Rect2.bottom)&&((point.x+Rect1.left)>=Rect2.left)&&((point.x+Rect1.left)<=Rect2.right))
	{
		m_drawData.pt.x=point.x-(Rect2.left-Rect1.left);
		m_drawData.iB=m_drawData.pt.x;
		m_drawData.iE=m_drawData.pt.x;
		m_drawData.bMouse=TRUE;
		ReDraw();
		m_drawData.bMouse=FALSE;
		ReDraw();
	}
	CDialog::OnLButtonDown(nFlags, point);
}

void CWLCheck::OnButtonCorr() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int iR;
	if(g_bEnglish)
		iR = MessageBox("Are you sure?",NULL,MB_OKCANCEL|MB_ICONINFORMATION);
	else
		iR = MessageBox("确定校正?",NULL,MB_OKCANCEL|MB_ICONINFORMATION);
	if(iR == IDCANCEL)
		return;

	float fErr=0;
	for(int i=0;i<4;i++)
	{
		fErr=fErr+m_fErr[i];
	}
	fErr=fErr/4;

	g_SPEC.m_Icor=g_SPEC.m_Icor+fErr;
	g_SPEC.SaveWaveData();
}

void CWLCheck::OnRadioType1() 
{
	// TODO: Add your control notification handler code here
	m_iType=0;
	ReDraw();
}

void CWLCheck::OnRadioType2() 
{
	// TODO: Add your control notification handler code here
	m_iType=1;
	ReDraw();
}

void CWLCheck::OnButtonAdd() 
{
	// TODO: Add your control notification handler code here
	BOOL bR;
	bR = UpdateData(TRUE);
	if(!bR)
	{
		return;
	}
	BOOL bHave = FALSE;
	for (int i = 0; i < g_SPEC.m_arra_fStaWL.GetSize(); i++)
	{
		if(m_fStaWL == g_SPEC.m_arra_fStaWL[i])
		{
			bHave = TRUE;
			break;
		}
	}
	if(!bHave)
	{
		g_SPEC.m_arra_strSource.Add("Lamp");
		g_SPEC.m_arra_fStaWL.Add(m_fStaWL);
	}
	else
	{
		if(g_bEnglish)
			AfxMessageBox("Add error!");
		else
			AfxMessageBox("已经有此波长，请重新添加！");
	}
	
	ReListWL();
	ShowErr();
	ReDraw();
}

void CWLCheck::OnButtonDelete() 
{
	// TODO: Add your control notification handler code here
	//删除选择的谱线
	if(UpdateData(TRUE)==FALSE)
	{
		return;
	}
	g_SPEC.m_arra_strSource.RemoveAt(m_iSele);
	g_SPEC.m_arra_fStaWL.RemoveAt(m_iSele);
	
	ReListWL();
	ShowErr();
	ReDraw();
}

void CWLCheck::OnItemchangedList2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	m_iSele = pNMListView->iItem;
	
	*pResult = 0;
}

void CWLCheck::OnButtonTest3() 
{
	// TODO: Add your control notification handler code here
	CCmdTarget::BeginWaitCursor();
	BOOL bR;
	bR = g_SPEC.SPEC_GetDark(m_fIntTime,m_iAvgN);
	CCmdTarget::EndWaitCursor();
	
}
