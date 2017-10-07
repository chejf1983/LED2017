// DlgSpectrumCalU.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "DlgSpectrumCalU.h"

#include "Note.h"
#include "math.h"
#include "GLobal_MySpec.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSpectrumCalU dialog
extern float g_fSpect1;
extern float g_fSpect2;

CDlgSpectrumCalU::CDlgSpectrumCalU(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSpectrumCalU::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSpectrumCalU)
	m_fIntTime = 80.0f;
	m_iAveN = 0;
	m_bAll = TRUE;
	//}}AFX_DATA_INIT
	CString strSection = "Spectrum Cal_U";

	CString strIntTime = "IntTime";
	CString strAveN    = "AVE_N";
	CString strALL	   = "ALL";

	CString strTemp;
	strTemp      = AfxGetApp()->GetProfileString(strSection,strIntTime,"100");
	m_fIntTime   = (float)atof(strTemp);
	m_iAveN		 = AfxGetApp()->GetProfileInt(strSection,strAveN,10);
	m_bAll		 = AfxGetApp()->GetProfileInt(strSection,strALL,FALSE);

	m_iCurMode	 = 0;
}

void CDlgSpectrumCalU::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSpectrumCalU)
	DDX_Control(pDX, IDC_EDIT_AVE_N, m_cAveN);
	DDX_Control(pDX, IDC_CHECK_ALL, m_cAll);
	DDX_Control(pDX, IDC_STATIC_SETUP, m_cSet);
	DDX_Control(pDX, IDC_BUTTON_STOP, m_cStop);
	DDX_Control(pDX, IDC_LIST, m_cList);
	DDX_Control(pDX, IDCANCEL, m_cExit);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_cSave);
	DDX_Control(pDX, IDC_BUTTON_OFF, m_cOFF);
	DDX_Control(pDX, IDC_BUTTON_CAL, m_cCal);
	DDX_Control(pDX, IDC_IP, m_cIP);
	DDX_Control(pDX, IDC_EDIT_INT_TIME, m_cIntTime);
	DDX_Control(pDX, IDC_DRAW, m_cDraw);
	DDX_Check(pDX, IDC_CHECK_ALL, m_bAll);
	DDX_Text(pDX, IDC_EDIT_INT_TIME, m_fIntTime);
	DDX_Text(pDX, IDC_EDIT_AVE_N, m_iAveN);
	DDV_MinMaxInt(pDX, m_iAveN, 1, 50);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgSpectrumCalU, CDialog)
	//{{AFX_MSG_MAP(CDlgSpectrumCalU)
	ON_BN_CLICKED(IDC_BUTTON_CAL, OnButtonCal)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_OFF, OnButtonOff)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnItemchangedList)
	ON_BN_CLICKED(IDC_STATIC_SETUP, OnStaticSetup)
	ON_BN_CLICKED(IDC_CHECK_ALL, OnCheckAll)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSpectrumCalU message handlers

void CDlgSpectrumCalU::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}

BOOL CDlgSpectrumCalU::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_cSet.SetLink(TRUE)
		.SetTextColor(RGB(0,0,255))
		.SetFontUnderline(TRUE)
		.SetLinkCursor(AfxGetApp()->LoadCursor(IDC_HAND));

	SetShowIcon(TRUE);

	m_fTempSP1 = g_fSpect1;
	m_fTempSP2 = g_fSpect2;
	m_iTempBin = g_SPEC.m_iBin;
	m_iTempMode= g_SPEC.m_iMode;

	m_spData[0].m_fSpect1=g_fSpect1;
	m_spData[0].m_fSpect2=g_fSpect2;
	g_fSpect1  = 200;
	g_fSpect2  = 400;

	g_SPEC.m_iMode=0;

	m_spData[0].m_bHaveData=FALSE;	
	m_spData[0].m_iDataType=TYPE_CAL;

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

	m_iCur=40;
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSpectrumCalU::ReDraw()
{
	m_cDraw.DrawSpect(m_spData[m_iCurMode],m_drawData,"");
}

void CDlgSpectrumCalU::OnCancel() 
{
	// TODO: Add extra cleanup here
	UpdateData(TRUE);
	SaveSet();
	g_fSpect1	   = m_fTempSP1;
	g_fSpect2	   = m_fTempSP2;
	g_SPEC.m_iBin  = m_iTempBin;
	g_SPEC.m_iMode = m_iTempMode;
	
	CDialog::OnCancel();
}

UINT ThreadSpectrumCal_U(LPVOID pParam)
{
    CDlgSpectrumCalU* pDlg=(CDlgSpectrumCalU*)pParam;
	BOOL bR;
	CString strTemp;
	CString sTemp;
	if(pDlg->m_bAll)//多模式定标
	{
		if(g_SPEC.m_Have_iBin==2)
			g_SPEC.m_iBin=1;
		g_SPEC.m_fInterval=0.1f;
		CString strTemp, sTemp;
		for(pDlg->m_iCurMode=0;pDlg->m_iCurMode<g_SPEC.m_Have_iBin;pDlg->m_iCurMode++)
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

void CDlgSpectrumCalU::OnButtonCal() 
{
	// TODO: Add your control notification handler code here
	if(UpdateData(TRUE)==FALSE)
		return;

	SaveSet();

	m_fTempSP1 = g_fSpect1;
	m_fTempSP2 = g_fSpect2;

	//紫外定标定200-400
	g_fSpect1  = g_SPEC.T_SPECT1;//注意有可能不是从200开始的
	g_fSpect2  = 400;

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
		bR=g_SPEC.SPEC_GetAutoTime(m_fIntTime,g_SPEC.m_iAutoLimitTime2,0.6f,m_fIntTime);
		if(!bR)
		{
			if(g_bEnglish)
				strTemp.Format("Fail[Spectrum]!");
			else
				strTemp.Format("光谱仪自动积分失败!");
			CMainFrame::ShowNote(strTemp,TRUE,RGB(255,0,0));
			return;
		}

		UpdateData(FALSE);
		CCmdTarget::BeginWaitCursor();
	}
	SaveSet();
	EnableShow(TRUE);
	m_bCancel=FALSE;
	AfxBeginThread(ThreadSpectrumCal_U,this);
}

void CDlgSpectrumCalU::OnButtonSave() 
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
	int iN;
	//保存紫外定标数据 200-380nm
	if(m_bAll)
	{
		for(m_iCurMode=0;m_iCurMode<g_SPEC.m_Have_iBin;m_iCurMode++)
		{
			g_SPEC.m_iBin=m_iCurMode%g_SPEC.m_Have_iBin;
			g_SPEC.m_iMode=0;

			g_SPEC.m_SP_fSpect1_UV   = m_spData[m_iCurMode].m_fSpect1;
			g_SPEC.m_SP_fSpect2_UV   = m_spData[m_iCurMode].m_fSpect2;
			g_SPEC.m_fInterval		 = m_spData[m_iCurMode].m_fInterval;
			g_SPEC.m_SP_fIntTime_UV  = m_spData[m_iCurMode].m_fIntTime;

			CTime tNow;
			tNow = CTime::GetCurrentTime();
			CString sNow = tNow.Format("%Y-%m-%d,%H:%M");
			g_SPEC.m_SP_strDate_UV = sNow;

			iN=(int)((g_SPEC.m_SP_fSpect2_UV-g_SPEC.m_SP_fSpect1_UV)/g_SPEC.m_fInterval+1+0.5f);
			m_spData[m_iCurMode].DoADSpecForCal(CSpectData::m_fSetDoWL, CSpectData::m_fSetDoLimitAD);

			for(int i=0;i<iN;i++)
			{
				float lamda=m_spData[m_iCurMode].m_fSpect1+i*m_spData[m_iCurMode].m_fInterval;
				float fRel;
				double fTemp;
				fRel=m_spData[m_iCurMode].m_fRelSpect[i];
				if(fRel<=0)
					fTemp=0;
				else
					fTemp=g_doData.m_uvpl[i]/fRel;
				g_SPEC.m_SP_fK_UV[i]=(float)fTemp;
			}

			g_SPEC.m_CAL_fFluxK[0]=1.0f;

			CString sTemp,sTemp_LI,sTemp_PH;
			if(g_SPEC.m_iBin==0)
			{
				sTemp="Stad_FULL_U.cal";  //高
				sTemp_LI=g_strCurPath+"Cal\\Li_"+sTemp;
				sTemp_PH=g_strCurPath+"Cal\\Ph_"+sTemp;
				g_SPEC.SP_Save_UV(sTemp_LI);
				g_SPEC.SP_Save_UV(sTemp_PH);
			}
			if(g_SPEC.m_iBin==1)
			{
				sTemp="Stad_TEN_U.cal";   //中
				sTemp_LI=g_strCurPath+"Cal\\Li_"+sTemp;
				sTemp_PH=g_strCurPath+"Cal\\Ph_"+sTemp;
				g_SPEC.SP_Save_UV(sTemp_LI);
				g_SPEC.SP_Save_UV(sTemp_PH);
			}
			if(g_SPEC.m_iBin==2)
			{
				sTemp="Stad_ONE_U.cal";   //低
				sTemp_LI=g_strCurPath+"Cal\\Li_"+sTemp;
				sTemp_PH=g_strCurPath+"Cal\\Ph_"+sTemp;
				g_SPEC.SP_Save_UV(sTemp_LI);
				g_SPEC.SP_Save_UV(sTemp_PH);
			}
			if(g_SPEC.m_iBin==3)
			{
				sTemp="Stad_3_U.cal";   //低
				sTemp_LI=g_strCurPath+"Cal\\Li_"+sTemp;
				sTemp_PH=g_strCurPath+"Cal\\Ph_"+sTemp;
				g_SPEC.SP_Save_UV(sTemp_LI);
				g_SPEC.SP_Save_UV(sTemp_PH);
			}
		}
		UpdateData(FALSE);
	}
	else
	{
		g_SPEC.m_SP_fSpect1_UV   = m_spData[0].m_fSpect1;
		g_SPEC.m_SP_fSpect2_UV   = m_spData[0].m_fSpect2;
		g_SPEC.m_fInterval		 = m_spData[0].m_fInterval;
		g_SPEC.m_SP_fIntTime_UV  = m_fIntTime;

		CTime tNow;
		tNow = CTime::GetCurrentTime();
		CString sNow = tNow.Format("%Y-%m-%d,%H:%M");
		g_SPEC.m_SP_strDate_UV   = sNow;

		iN=(int)((g_SPEC.m_SP_fSpect2_UV-g_SPEC.m_SP_fSpect1_UV)/g_SPEC.m_fInterval+1+0.5f);
		m_spData[0].DoADSpecForCal(CSpectData::m_fSetDoWL, CSpectData::m_fSetDoLimitAD);
		for(int i=0;i<iN;i++)
		{
			float lamda=m_spData[0].m_fSpect1+i*m_spData[0].m_fInterval;
			float fRel;
			double fTemp;
			fRel=m_spData[0].m_fRelSpect[i];
			if(fRel<=0)
				fTemp=0;
			else
				fTemp=g_doData.m_uvpl[i]/fRel;
			g_SPEC.m_SP_fK_UV[i]=(float)fTemp;
		}

		g_SPEC.m_CAL_fFluxK[0]=1.0f;

		CString sTemp,sTemp_LI,sTemp_PH;
		if(g_SPEC.m_iBin==0)
		{
			sTemp="Stad_FULL_U.cal";  //高
			sTemp_LI=g_strCurPath+"Cal\\Li_"+sTemp;
			sTemp_PH=g_strCurPath+"Cal\\Ph_"+sTemp;
			g_SPEC.SP_Save_UV(sTemp_LI);
			g_SPEC.SP_Save_UV(sTemp_PH);
		}

		if(g_SPEC.m_iBin==1)
		{
			sTemp="Stad_TEN_U.cal";   //中
			sTemp_LI=g_strCurPath+"Cal\\Li_"+sTemp;
			sTemp_PH=g_strCurPath+"Cal\\Ph_"+sTemp;
			g_SPEC.SP_Save_UV(sTemp_LI);
			g_SPEC.SP_Save_UV(sTemp_PH);
		}

		if(g_SPEC.m_iBin==2)
		{
			sTemp="Stad_ONE_U.cal";   //低
			sTemp_LI=g_strCurPath+"Cal\\Li_"+sTemp;
			sTemp_PH=g_strCurPath+"Cal\\Ph_"+sTemp;
			g_SPEC.SP_Save_UV(sTemp_LI);
			g_SPEC.SP_Save_UV(sTemp_PH);
		}

		if(g_SPEC.m_iBin==3)
		{
			sTemp="Stad_3_U.cal";   //低
			sTemp_LI=g_strCurPath+"Cal\\Li_"+sTemp;
			sTemp_PH=g_strCurPath+"Cal\\Ph_"+sTemp;
			g_SPEC.SP_Save_UV(sTemp_LI);
			g_SPEC.SP_Save_UV(sTemp_PH);
		}
		UpdateData(FALSE);
	}
	if(g_bEnglish)
		AfxMessageBox("Save the data succeed!");
	else
		AfxMessageBox("数据保存成功!");
}

void CDlgSpectrumCalU::OnCheckAll() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}

void CDlgSpectrumCalU::OnStaticSetup() 
{
	// TODO: Add your control notification handler code here
	CCmdTarget::BeginWaitCursor();
	g_SPEC.m_bCal=TRUE;
	g_SPEC.SPEC_Setting();
	g_SPEC.m_bCal=FALSE;
	CCmdTarget::EndWaitCursor();
}

void CDlgSpectrumCalU::OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	m_iCur=pNMListView->iItem;
	
	*pResult = 0;
}

void CDlgSpectrumCalU::OnButtonStop() 
{
	// TODO: Add your control notification handler code here
	m_bCancel=TRUE;
	m_cStop.EnableWindow(FALSE);
}


void CDlgSpectrumCalU::ReList()
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

void CDlgSpectrumCalU::EnableShow(BOOL bStart)
{
	m_cIntTime.EnableWindow(!bStart);

	m_cOFF.EnableWindow(!bStart);
	m_cCal.EnableWindow(!bStart);
	m_cStop.EnableWindow(bStart);
	m_cExit.EnableWindow(!bStart);
	m_cSet.EnableWindow(!bStart);

	m_cAveN.EnableWindow(!bStart);

	m_cAll.EnableWindow(!bStart);
}

BOOL CDlgSpectrumCalU::Test()
{
	CCmdTarget::BeginWaitCursor();
	if(g_SPEC.m_iMode==2)
	{
		if(g_bEnglish)
			AfxMessageBox("Please select speediness or Precision!");
		else
			AfxMessageBox("请选择快速测试模式或精确测试模式!");
		return FALSE;
	}
	float fMax;
	BOOL bR;
	if(m_iNum==0)
		bR=g_SPEC.SPEC_DoScan(m_fIntTime*1.0f,m_iAveN,MY_TRIG_NORMAL,fMax,TRUE,m_spData[m_iCurMode].m_iDataType);
	else
		bR=g_SPEC.SPEC_DoScan(m_fIntTime*1.0f,m_iAveN,MY_TRIG_NORMAL,fMax,FALSE,m_spData[m_iCurMode].m_iDataType);
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

	g_SPEC.SPEC_GetSpectData(FALSE,m_spData[m_iCurMode]);
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

	ReDraw();
	ReList();

	return TRUE;
}

void CDlgSpectrumCalU::SetShowIcon(BOOL bNotTest)
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
			SetWindowText("UV Spectrum Calibration");
		else
			SetWindowText("紫外光谱定标");
		hicon= AfxGetApp()->LoadIcon( IDI_SPECT_CAL_U);

		ASSERT( hicon != NULL );
	}

	// 2 - Associate the icon with the dialog box
	SetIcon( hicon, TRUE );
}

void CDlgSpectrumCalU::OnButtonOff() 
{
	// TODO: Add your control notification handler code here
	if(UpdateData(TRUE)==FALSE)
		return;	
	CCmdTarget::BeginWaitCursor();
	BOOL bR;
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

void CDlgSpectrumCalU::SaveSet()
{
	CString strSection = "Spectrum Cal";

	CString strIntTime = "IntTime";
	CString strAveN    = "AVE N";
	CString strALL	   = "ALL";

	CString strTemp;
	strTemp.Format("%f",m_fIntTime);
	AfxGetApp()->WriteProfileString(strSection,strIntTime,strTemp);
	AfxGetApp()->WriteProfileInt(strSection,strAveN,m_iAveN);
	AfxGetApp()->WriteProfileInt(strSection,strALL,m_bAll);
}

BOOL CDlgSpectrumCalU::AllModeTest()
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
		strTemp.Format("紫外定标快速模式 %d：自动积分...",g_SPEC.m_iBin+1);
	}
	CMainFrame::ShowNote(strTemp,TRUE,RGB(255,0,255));

	bR=g_SPEC.SPEC_GetAutoTime(m_fIntTime,g_SPEC.m_iAutoLimitTime2,0.6f,m_fIntTime);
	if(!bR)
	{
		if(g_bEnglish)
			strTemp.Format("Fail[Spectrum]!");
		else
			strTemp.Format("光谱仪自动积分失败!");
		CMainFrame::ShowNote(strTemp,TRUE,RGB(255,0,0));
		m_bCancel=FALSE;
		EnableShow(FALSE);
		return 0;
	}

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
	bR=Test();
	if(!bR)
		return FALSE;
	if(m_bCancel)
		return FALSE;
	bR=Test();
	if(!bR)
		return FALSE;
	if(m_bCancel)
		return FALSE;
	bR=Test();
	if(!bR)
		return FALSE;
	if(m_bCancel)
		return FALSE;
	Sleep(100);
	if(g_bEnglish)
		strTemp="Complete Calibration!";
	else
		strTemp="完成定标,请保存!";
	CMainFrame::ShowNote(strTemp,TRUE,RGB(0,0,0));
	return TRUE;
}
