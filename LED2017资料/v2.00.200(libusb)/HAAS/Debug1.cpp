// Debug1.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "Debug1.h"
#include "Global_MySpec.h"
#include "MainFrm.h"
#include "math.h"
//杂散光修正的函数
#include <iostream>
#include <fstream> 
#include "SpectraArsenal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDebug1 property page
extern BOOL g_bHalfWL;
extern BOOL g_bHaveOpen;

IMPLEMENT_DYNCREATE(CDebug1, CPropertyPage)

CDebug1::CDebug1() : CPropertyPage(CDebug1::IDD)
{
	//{{AFX_DATA_INIT(CDebug1)
	m_iAvgN		= 1;
	m_fIntTime	= 100.0f;
	m_bLine		= FALSE;
	m_iPix		= 100;
	m_fWL		= 500.0f;
	m_bSetZoom	= FALSE;
	m_iX1		= 200;
	m_iX2		= 1000;
	m_bCro		= FALSE;
	m_iJType	= 0;
	m_bHalfWL	= FALSE;
	m_iLevel_ZS = 0;
	m_fWLPX = 546.07f;
	m_bNotUseColor = FALSE;
	m_iPer = 50;
	m_iPer2 = 10;
	m_iPerType = 0;
	m_iPixSele = 1000;
	m_fIntTime1 = 5.0f;
	m_fIntTime2 = 100.0f;
	m_fIntervalTime = 5.0f;
	m_iPixSele2 = 0;
	m_iStepType = 1;
	m_bMoveDark = FALSE;
	//}}AFX_DATA_INIT

	CString strSection  = "Start_Debug1_A";

	CString strIntTime  = "IntTime";
	CString strAvgN     = "AvgN";
	CString strPix      = "Pix";
	CString strLine     = "Line";
	CString strSetZ     = "SetZ";
	CString strX1       = "X1";
	CString strX2       = "X2";
	CString strPathName = "PathName";

	CString strTemp;
	strTemp    = AfxGetApp()->GetProfileString(strSection,strIntTime,"100");
	m_fIntTime = (float)atof(strTemp);
	m_iAvgN    = AfxGetApp()->GetProfileInt(strSection,strAvgN,1);
	m_iPix     = AfxGetApp()->GetProfileInt(strSection,strPix,500);
	m_bLine    = AfxGetApp()->GetProfileInt(strSection,strLine,TRUE);
	m_bSetZoom = AfxGetApp()->GetProfileInt(strSection,strSetZ,FALSE);
	m_iX1      = AfxGetApp()->GetProfileInt(strSection,strX1,400);
	m_iX2      = AfxGetApp()->GetProfileInt(strSection,strX2,1400);

	m_strPathName = AfxGetApp()->GetProfileString(strSection,strPathName,"");


	CString str_m_iPer = _T("m_iPer");
	CString str_m_iPer2 = _T("m_iPer2");
	CString str_m_iPerType = _T("m_iPerType");
	
	m_iPer = AfxGetApp()->GetProfileInt(strSection, str_m_iPer, 50);
	m_iPer2 = AfxGetApp()->GetProfileInt(strSection, str_m_iPer2, 10);
	m_iPerType = AfxGetApp()->GetProfileInt(strSection, str_m_iPerType, 0);

	CString str_m_iPixSele = _T("m_iPixSele");
	CString str_m_fIntTime1 = _T("m_fIntTime1");
	CString str_m_fIntTime2 = _T("m_fIntTime2");
	CString str_m_fIntervalTime = _T("m_fIntervalTime");
	CString str_m_iPixSele2 = _T("m_iPixSele2");
	
	m_iPixSele = AfxGetApp()->GetProfileInt(strSection, str_m_iPixSele, 1);
	strTemp = AfxGetApp()->GetProfileString(strSection, str_m_fIntTime1, _T("5"));
	m_fIntTime1 = (float)atof(strTemp);
	strTemp = AfxGetApp()->GetProfileString(strSection, str_m_fIntTime2, _T("100"));
	m_fIntTime2 = (float)atof(strTemp);
	strTemp = AfxGetApp()->GetProfileString(strSection, str_m_fIntervalTime, _T("10"));
	m_fIntervalTime = (float)atof(strTemp);
	m_iPixSele2 = AfxGetApp()->GetProfileInt(strSection, str_m_iPixSele2, 2);
}

CDebug1::~CDebug1()
{
	CString strSection  = "Start_Debug1_A";

	CString str_m_iPer = _T("m_iPer");
	CString str_m_iPer2 = _T("m_iPer2");
	CString str_m_iPerType = _T("m_iPerType");

	AfxGetApp()->WriteProfileInt(strSection, str_m_iPer, m_iPer);
	AfxGetApp()->WriteProfileInt(strSection, str_m_iPer2, m_iPer2);
	AfxGetApp()->WriteProfileInt(strSection, str_m_iPerType, m_iPerType);

	CString strTemp;
	CString str_m_iPixSele = _T("m_iPixSele");
	CString str_m_fIntTime1 = _T("m_fIntTime1");
	CString str_m_fIntTime2 = _T("m_fIntTime2");
	CString str_m_fIntervalTime = _T("m_fIntervalTime");
	CString str_m_iPixSele2 = _T("m_iPixSele2");
	
	AfxGetApp()->WriteProfileInt(strSection, str_m_iPixSele, m_iPixSele);
	strTemp.Format(_T("%g"), m_fIntTime1);
	AfxGetApp()->WriteProfileString(strSection, str_m_fIntTime1, strTemp);
	strTemp.Format(_T("%g"), m_fIntTime2);
	AfxGetApp()->WriteProfileString(strSection, str_m_fIntTime2, strTemp);
	strTemp.Format(_T("%g"), m_fIntervalTime);
	AfxGetApp()->WriteProfileString(strSection, str_m_fIntervalTime, strTemp);
	AfxGetApp()->WriteProfileInt(strSection, str_m_iPixSele2, m_iPixSele2);

	
	CString strIntTime  = "IntTime";
	CString strAvgN     = "AvgN";
	CString strPix      = "Pix";
	CString strLine     = "Line";
	CString strSetZ     = "SetZ";
	CString strX1       = "X1";
	CString strX2       = "X2";
	CString strPathName = "PathName";
	
	strTemp.Format("%f",m_fIntTime);
	AfxGetApp()->WriteProfileString(strSection,strIntTime,strTemp);
	AfxGetApp()->WriteProfileInt(strSection,strAvgN,m_iAvgN);
	AfxGetApp()->WriteProfileInt(strSection,strPix,m_iPix);
	AfxGetApp()->WriteProfileInt(strSection,strLine,m_bLine);
	AfxGetApp()->WriteProfileInt(strSection,strSetZ,m_bSetZoom);
	AfxGetApp()->WriteProfileInt(strSection,strX1,m_iX1);
	AfxGetApp()->WriteProfileInt(strSection,strX2,m_iX2);
	AfxGetApp()->WriteProfileString(strSection,strPathName,m_strPathName);
}

void CDebug1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDebug1)
	DDX_Control(pDX, IDC_BUTTON_START2, m_cStart2);
	DDX_Control(pDX, IDC_BUTTON_STOP2, m_cStop2);
	DDX_Control(pDX, IDC_STATIC_BW, m_cBW);
	DDX_Control(pDX, IDC_STATIC_WL_HF, m_cWLHF);
	DDX_Control(pDX, IDC_STATIC_LEVEL, m_cLevel);
	DDX_Control(pDX, IDC_STATIC_HALF, m_cHalf);
	DDX_Control(pDX, IDC_STATIC_SETUP, m_cSet);
	DDX_Control(pDX, IDC_EDIT_X2, m_cX2);
	DDX_Control(pDX, IDC_EDIT_X1, m_cX1);
	DDX_Control(pDX, IDC_STATIC_X12, m_cX12);
	DDX_Control(pDX, IDC_BUTTON_OK, m_cOK);
	DDX_Control(pDX, IDC_EDIT_WL, m_cWL);
	DDX_Control(pDX, IDC_EDIT_PIX, m_cPix);
	DDX_Control(pDX, IDC_EDIT_AD, m_cAD);
	DDX_Control(pDX, IDC_EDIT_INT_TIME, m_cIntTime);
	DDX_Control(pDX, IDC_EDIT_AVG_N, m_cAvgN);
	DDX_Control(pDX, IDC_BUTTON_TEST, m_cTest);
	DDX_Control(pDX, IDC_BUTTON_STOP, m_cStop);
	DDX_Control(pDX, IDC_BUTTON_START, m_cStart);
	DDX_Control(pDX, IDC_BUTTON_EXIT, m_cExit);
	DDX_Control(pDX, IDC_DRAW, m_cDraw);
	DDX_Text(pDX, IDC_EDIT_AVG_N, m_iAvgN);
	DDX_Text(pDX, IDC_EDIT_INT_TIME, m_fIntTime);
	DDV_MinMaxFloat(pDX, m_fIntTime, 0.1f, 60000);
	DDX_Check(pDX, IDC_CHECK_LINE, m_bLine);
	DDX_Text(pDX, IDC_EDIT_PIX, m_iPix);
	DDV_MinMaxInt(pDX, m_iPix, 0, 5000);
	DDX_Text(pDX, IDC_EDIT_WL, m_fWL);
	DDX_Check(pDX, IDC_CHECK_ZOOM, m_bSetZoom);
	DDX_Text(pDX, IDC_EDIT_X1, m_iX1);
	DDV_MinMaxInt(pDX, m_iX1, 0, 10000);
	DDX_Text(pDX, IDC_EDIT_X2, m_iX2);
	DDV_MinMaxInt(pDX, m_iX2, 0, 10000);
	DDX_Check(pDX, IDC_CHECK_CRO, m_bCro);
	DDX_CBIndex(pDX, IDC_COMBO1, m_iJType);
	DDX_Check(pDX, IDC_CHECK_HALF_WL, m_bHalfWL);
	DDX_Radio(pDX, IDC_RADIO3, m_iLevel_ZS);
	DDX_Text(pDX, IDC_EDIT_PX, m_fWLPX);
	DDX_Check(pDX, IDC_CHECK_NOT_USE_COLOR, m_bNotUseColor);
	DDX_Text(pDX, IDC_EDIT_PER, m_iPer);
	DDV_MinMaxInt(pDX, m_iPer, 10, 90);
	DDX_Text(pDX, IDC_EDIT_PER2, m_iPer2);
	DDV_MinMaxInt(pDX, m_iPer2, 5, 90);
	DDX_Radio(pDX, IDC_RADIO_TYPE1, m_iPerType);
	DDX_Text(pDX, IDC_EDIT_PIX_SELE, m_iPixSele);
	DDV_MinMaxInt(pDX, m_iPixSele, 0, 2047);
	DDX_Text(pDX, IDC_EDIT_INTTIME_1, m_fIntTime1);
	DDV_MinMaxFloat(pDX, m_fIntTime1, 1.f, 10000.f);
	DDX_Text(pDX, IDC_EDIT_INTTIME_2, m_fIntTime2);
	DDV_MinMaxFloat(pDX, m_fIntTime2, 1.f, 10000.f);
	DDX_Text(pDX, IDC_EDIT_INTTIME_INTERVAL, m_fIntervalTime);
	DDV_MinMaxFloat(pDX, m_fIntervalTime, 1.f, 1000.f);
	DDX_Text(pDX, IDC_EDIT_PIX_SELE2, m_iPixSele2);
	DDV_MinMaxInt(pDX, m_iPixSele2, 0, 2047);
	DDX_CBIndex(pDX, IDC_COMBO_STEP_TYPE, m_iStepType);
	DDX_Check(pDX, IDC_CHECK_DARK_MOVE, m_bMoveDark);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDebug1, CPropertyPage)
	//{{AFX_MSG_MAP(CDebug1)
	ON_BN_CLICKED(IDC_BUTTON_TEST, OnButtonTest)
	ON_BN_CLICKED(IDC_BUTTON_START, OnButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)
	ON_BN_CLICKED(IDC_CHECK_LINE, OnCheckLine)
	ON_WM_LBUTTONDOWN()
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_1, OnDeltaposSpin1)
	ON_BN_CLICKED(IDC_BUTTON_OK, OnButtonOk)
	ON_BN_CLICKED(IDC_CHECK_ZOOM, OnCheckZoom)
	ON_EN_CHANGE(IDC_EDIT_X1, OnChangeEditX1)
	ON_EN_CHANGE(IDC_EDIT_X2, OnChangeEditX2)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_ZERO, OnButtonZero)
	ON_BN_CLICKED(IDC_STATIC_SETUP, OnStaticSetup)
	ON_BN_CLICKED(IDC_BUTTON_ZERO_C, OnButtonZeroC)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON_TEST_J, OnButtonTestJ)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_CHECK_HALF_WL, OnCheckHalfWl)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_BN_CLICKED(IDC_BUTTON_GET_HF, OnButtonOk2)
	ON_BN_CLICKED(IDC_BUTTON_START2, OnButtonStart2)
	ON_BN_CLICKED(IDC_BUTTON_STOP2, OnButtonStop2)
	ON_BN_CLICKED(IDC_BUTTON_INIT, OnButtonInit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDebug1 message handlers

void CDebug1::OnButtonTest() 
{
	// TODO: Add your control notification handler code here
	if(UpdateData(TRUE)==FALSE)
		return;

	g_SPEC.m_bCro=m_bCro;
	BOOL bR;
	bR = Test(m_fIntTime,m_iAvgN,m_fAD,m_iN);
	if(!bR)
		return;

	ReDraw();
}

UINT ThreadDebugStart(LPVOID pParam)
{
	//测试副线程
	//很重要的一部分

	CDebug1* pDlg=(CDebug1*)pParam;
	BOOL bR;
	int iN = 0;
	CString strTemp;
	while(!pDlg->m_bCancel)
	{
		iN++;
		if(g_bEnglish)
		{
			strTemp.Format("Sampling[%d]...",iN);
		}
		else
		{
			strTemp.Format("正在采样数据[%d]...",iN);
		}

		CMainFrame::ShowNote(strTemp,TRUE,RGB(0,0,255));
		bR = pDlg->Test(pDlg->m_fIntTime,pDlg->m_iAvgN,pDlg->m_fAD,pDlg->m_iN);
		if(!bR)
		{
			if(g_bEnglish)
			{
				CMainFrame::ShowNote("Sampling fail,exit test!",TRUE,RGB(255,0,0));
			}
			else
			{
				CMainFrame::ShowNote("采样失败,退出测试!",TRUE,RGB(255,0,0));
			}
			break;
		}
		if(g_bEnglish)
		{
			CMainFrame::ShowNote("Complete,Drawing...",TRUE,RGB(0,0,0));
		}
		else
		{
			CMainFrame::ShowNote("完成采样,画图...",TRUE,RGB(0,0,0));
		}

		pDlg->ReDraw();
//		Sleep(100);

		if(0)
		{
			float fAve = 0;
			for(int i = 0; i < g_SPEC.m_iPixN; i++)
			{
				fAve = fAve + g_SPEC.m_fAD[i];
			}
			fAve = fAve / g_SPEC.m_iPixN;
			FILE *fp;
			CString strPathName;
			strPathName.Format("data%04d(%.0f).dat", iN, fAve);
			strPathName = g_strCurPath +"Files\\" + strPathName;
			if((fp = fopen(strPathName,"wt")) == NULL)
			{
			}
			else
			{
				for(i = 0; i < g_SPEC.m_iPixN; i++)
				{
					fprintf(fp,"%4d %.3f\n",i,g_SPEC.m_fAD[i]);
				}
			}
			fclose(fp);
		}
	}
	if(pDlg->m_bCancel)
	{
		if(g_bEnglish)
		{
			CMainFrame::ShowNote("Cancel!",TRUE,RGB(0,0,0));
		}
		else
		{
			CMainFrame::ShowNote("取消测试!",TRUE,RGB(0,0,0));
		}
	}

	pDlg->OVER();
	return 0;
}

void CDebug1::OnButtonStart() 
{
	// TODO: Add your control notification handler code here
	if(UpdateData(TRUE)==FALSE)
	{
		return;
	}

	EnableShow(TRUE);
	//开副线程
	m_bCancel = FALSE;
	AfxBeginThread(ThreadDebugStart,this);	
}

void CDebug1::OnButtonStop() 
{
	// TODO: Add your control notification handler code here
	m_bCancel = TRUE;
	m_cStop.EnableWindow(FALSE);
}

void CDebug1::OnButtonExit() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	::PostMessage(GetParent()->m_hWnd,WM_CLOSE,0,0);
	

}

void CDebug1::ReDraw()
{
	m_cDraw.DrawMyDebug(m_fAD, m_iN, m_bLine, m_debugDrawPara);
//	m_cDraw.DrawMyDebug_2();

	m_iPix	= m_debugDrawPara.iCurSele;
	m_fWL	= g_SPEC.SPEC_Pix2WL(m_iPix);
	float fAD = m_fAD[m_iPix];
	CString strTemp;
	strTemp.Format("%.1f",fAD);
	m_cAD.SetWindowText(strTemp);
	strTemp.Format("%d",m_iPix);
	m_cPix.SetWindowText(strTemp);
	strTemp.Format("%.2f",m_fWL);
	m_cWL.SetWindowText(strTemp);
}

BOOL CDebug1::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_cSet.SetLink(TRUE)
		.SetTextColor(RGB(0,0,255))
		.SetFontUnderline(TRUE)
		.SetLinkCursor(AfxGetApp()->LoadCursor(IDC_HAND));

	m_iN = g_SPEC.m_iPixN;
	for(int i = 0; i < m_iN; i++)
	{
		m_fAD[i] = 0;
	}

	m_debugDrawPara.bMouse	= FALSE;
	m_debugDrawPara.iCurSele= m_iPix;
	m_debugDrawPara.bSetZ	= m_bSetZoom;
	m_debugDrawPara.X1		= m_iX1;
	m_debugDrawPara.X2		= m_iX2;

/*	m_cX12.EnableWindow(m_bSetZoom);
	m_cX1.EnableWindow(m_bSetZoom);
	m_cX2.EnableWindow(m_bSetZoom);
	if(!m_bSetZoom)
		m_cOK.EnableWindow(FALSE);*/

	UpdateData(FALSE);

	m_bCancel = FALSE;
	ReDraw();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDebug1::Test(float fIntTime, int iAvgN, float fData[], int &iN)
{
	g_SPEC.m_bCro = m_bCro;
	CCmdTarget::BeginWaitCursor();
	float fMax;
	BOOL bR;
	if(g_SPEC.m_iMode == 0)
	{
		bR = g_SPEC.SPEC_DoScan(fIntTime, iAvgN, MY_TRIG_NORMAL, fMax, FALSE, TYPE_SCAN, FALSE);
	}
	else
	{
		bR = g_SPEC.SPEC_DoScan(fIntTime, iAvgN, MY_TRIG_NORMAL, fMax, FALSE, TYPE_SCAN, TRUE);
	}

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
	g_SPEC.SPEC_GetSpectData(FALSE,m_spData);
	iN=g_SPEC.m_iPixN;

	for(int i = 0; i < iN; i++)
	{
		if (m_bMoveDark)
		{
			fData[i] = g_SPEC.m_fAD[i];
		}
		else
		{
			fData[i] = g_SPEC.m_fAD[i] + g_SPEC.m_fDarkAD[i];
		}
	}
	CCmdTarget::EndWaitCursor();

	GetBW();
	GetPX();
	GetZSG();

	return TRUE;
}

void CDebug1::EnableShow(BOOL bStart)
{
	m_cIntTime.EnableWindow(!bStart);
	m_cAvgN.EnableWindow(!bStart);
	m_cTest.EnableWindow(!bStart);
	m_cStart.EnableWindow(!bStart);
	m_cStop.EnableWindow(bStart);
	m_cExit.EnableWindow(!bStart);

	CMenu *pMenu=GetParentOwner()->GetSystemMenu(FALSE);
	if(bStart)
	{
		pMenu->EnableMenuItem(SC_CLOSE,MF_BYCOMMAND|MF_DISABLED);	
	}
	else
	{
		pMenu->EnableMenuItem(SC_CLOSE,MF_BYCOMMAND|MF_ENABLED);	
	}
}

void CDebug1::OnCheckLine() 
{
	// TODO: Add your control notification handler code here
	if(UpdateData(TRUE)==FALSE)
	{
		return;
	}

	ReDraw();
}

void CDebug1::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CRect Rect1,Rect2;
	GetClientRect(&Rect1);
	ClientToScreen(&Rect1);
	m_cDraw.GetClientRect(&Rect2);
	m_cDraw.ClientToScreen(&Rect2);
	if(((point.y+Rect1.top)>=Rect2.top)&&((point.y+Rect1.top)<=Rect2.bottom)&&((point.x+Rect1.left)>=Rect2.left)&&((point.x+Rect1.left)<=Rect2.right))
	{
		m_debugDrawPara.pt.x=point.x-(Rect2.left-Rect1.left);
		m_debugDrawPara.bMouse=TRUE;
		ReDraw();
	}

	CPropertyPage::OnLButtonDown(nFlags, point);
}

void CDebug1::OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	if(pNMUpDown->iDelta < 0)
	{
		m_iPix = m_iPix + 1;
	}
	else
	{
		m_iPix = m_iPix - 1;
	}
	UpdateData(FALSE);

	m_debugDrawPara.iCurSele=m_iPix;
	ReDraw();

	*pResult = 0;
}

void CDebug1::OnButtonOk() 
{
	// TODO: Add your control notification handler code here
	if(UpdateData(TRUE)==FALSE)
	{
		return;
	}

	m_debugDrawPara.bSetZ = m_bSetZoom;
	m_debugDrawPara.X1    = m_iX1;
	m_debugDrawPara.X2    = m_iX2;
	ReDraw();
	m_cOK.EnableWindow(FALSE);
}

void CDebug1::OnCheckZoom() 
{
	// TODO: Add your control notification handler code here
	if(UpdateData(TRUE)==FALSE)
	{
		return;
	}
/*	m_cX12.EnableWindow(m_bSetZoom);
	m_cX1.EnableWindow(m_bSetZoom);
	m_cX2.EnableWindow(m_bSetZoom);
	if(!m_bSetZoom)
		m_cOK.EnableWindow(FALSE);*/

	OnButtonOk();
}

void CDebug1::OnChangeEditX1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here

	m_cOK.EnableWindow(TRUE);
}

void CDebug1::OnChangeEditX2() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	m_cOK.EnableWindow(TRUE);	
}

void CDebug1::OnButtonSave() 
{
	// TODO: Add your control notification handler code here
	static char szFilter[]="Excel Files(*.xls)|*.xls||";
	CFileDialog dSave(FALSE,".xls", m_strPathName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);
	if(dSave.DoModal() == IDCANCEL)
	{
		return;	
	}

	m_strPathName = dSave.GetPathName();

	FILE *fp;
	if((fp = fopen(m_strPathName,"wt")) == 0)
	{
		return;
	}
	else
	{
		for(int i = 0; i < m_iN; i++)
		{
			CString strTemp;
			strTemp.Format("%d",i);
			fprintf(fp,strTemp);

			strTemp.Format("%.4f",g_SPEC.SPEC_Pix2WL(i));
			fprintf(fp,"	");
			fprintf(fp,strTemp);

			strTemp.Format("%.3f",m_fAD[i]);
			fprintf(fp,"	");
			fprintf(fp,strTemp);
			fprintf(fp,"\n");
		}
		fclose(fp);
		return;
	}
}

void CDebug1::OVER()
{
	SetTimer(1, 1, NULL);
}

void CDebug1::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent == 1)
	{
		KillTimer(1);
		EnableShow(FALSE);
	}

	CPropertyPage::OnTimer(nIDEvent);
}

void CDebug1::OnButtonZero() 
{
	// TODO: Add your control notification handler code here
	if(UpdateData(TRUE)==FALSE)
	{
		return;	
	}

	g_SPEC.m_bNotUseColorDark = m_bNotUseColor;

	CCmdTarget::BeginWaitCursor();
	BOOL bR;
	bR = g_SPEC.SPEC_GetDark(m_fIntTime,m_iAvgN);

	g_SPEC.m_bNotUseColorDark = FALSE;

	if(!bR)
	{
		if(g_bEnglish)
		{
			AfxMessageBox("Communication fail!");
		}
		else
		{
			AfxMessageBox("关灯校零失败!");
		}
	}
	CCmdTarget::EndWaitCursor();
}

void CDebug1::OnStaticSetup() 
{
	// TODO: Add your control notification handler code here
	CCmdTarget::BeginWaitCursor();
	g_SPEC.m_bCal = TRUE;
	g_SPEC.SPEC_Setting();
	g_SPEC.m_bCal = FALSE;
	CCmdTarget::EndWaitCursor();
}

void CDebug1::OnButtonZeroC() 
{
	// TODO: Add your control notification handler code here
	
}

void CDebug1::OnOK() 
{
	// TODO: Add extra validation here
	
//	CPropertyPage::OnOK();
}

void CDebug1::OnButton1() 
{
	// TODO: Add your control notification handler code here
	//选择导出路径
	CString strTemp;
	static char BASED_CODE szFilter[]="Excel Files(*.xls)|*.xls||";
	CFileDialog mOpenFile(TRUE, ".xls",strTemp,  OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);
	if(mOpenFile.DoModal()==IDCANCEL)
	{
		return;
	}
	strTemp = mOpenFile.GetPathName();
	float fWL[4096];
	FILE *fp;
	if((fp=fopen(strTemp,"rt"))==NULL)
	{
		return;
	}
	else
	{
		m_iN = g_SPEC.m_iPixN;
		int iTemp;
		CString strTemp;
		for(int i = 0; i < m_iN; i++)
		{
			fscanf(fp,"%d	%f	%f\n", &iTemp, &fWL[i], &m_fAD[i]);
		}

		for(i = 0; i < m_iN; i++)
		{
			g_SPEC.m_fAD[i] = m_fAD[i];
		}
	}
	fclose(fp);

	double fData[2001];
	for(int i = 0; i < 2001; i++)
	{
		float fLamda;
		fLamda	= 200 + 0.1f * i;
		fData[i]= g_doData.NewInt_float(fWL, m_fAD, g_SPEC.m_iPixN, fLamda);
	}
//	g_SPEC.DoProAvg(fData,m_iN,5);
	ReDraw();

	if((fp = fopen(strTemp + "_1.xls", "wt")) == NULL)
	{
		return;
	}
	else
	{
		float c1 = (float)(3.741844E19*9.58378/8.071367);
		float c2 = (float)(1.438833E7/2856);
		for(int i=0;i<2001;i++)
		{
			if(0)
			{
				/*氘灯
				float fLamda;
				fLamda=200+0.1f*i;
				CString strTemp;

				strTemp.Format("%.1f",fLamda);
				fprintf(fp,strTemp);
				fprintf(fp,"	");

				strTemp.Format("%.1f",fData[i]);
				fprintf(fp,strTemp);
				fprintf(fp,"	");

				strTemp.Format("%.1f",g_doData.m_uvpl[i]);
				fprintf(fp,strTemp);
				fprintf(fp,"\n");*/
			}
			if(1)
			{
				float fLamda;
				fLamda=200+0.1f*i;

				strTemp.Format("%.1f",fLamda);
				fprintf(fp,strTemp);
				fprintf(fp,"	");

				strTemp.Format("%.1f",fData[i]);
				fprintf(fp,strTemp);
				fprintf(fp,"	");

				double fTemp;
				fTemp=(double)((c1/pow(fLamda,5)/(exp(c2/fLamda)-1))*1000);
				strTemp.Format("%.6f",fTemp);
				fprintf(fp,strTemp);
				fprintf(fp,"	");

				strTemp.Format("%.6f",fTemp/fData[i]);
				fprintf(fp,strTemp);
				fprintf(fp,"	");
				fprintf(fp,"\n");
			}
		}
	}
		fclose(fp);
}

void CDebug1::OnButtonTestJ() 
{
	// TODO: Add your control notification handler code here
	CCmdTarget::BeginWaitCursor();
	float fMax;
	BOOL bR;
	bR=UpdateData(TRUE);
	if(!bR)
		return;
	int iN=g_SPEC.m_iPixN;
	double fData_1[2000];

	bR=g_SPEC.SPEC_GetDark(m_fIntTime,m_iAvgN);
	if(!bR)
	{
		if(g_bEnglish)
			AfxMessageBox("Communication fail!");
		else
			AfxMessageBox("关灯校零失败!");
	}

	if(g_SPEC.m_iMode==0)
		bR=g_SPEC.SPEC_DoScan(m_fIntTime,m_iAvgN,MY_TRIG_NORMAL,fMax,FALSE,TYPE_SCAN,FALSE);
	else
		bR=g_SPEC.SPEC_DoScan(m_fIntTime,m_iAvgN,MY_TRIG_NORMAL,fMax,FALSE,TYPE_SCAN,TRUE);
	if(!bR)
	{
		if(g_bEnglish)
			MessageBox("Sample fail!",NULL,MB_ICONSTOP);
		else
			MessageBox("采样失败!",NULL,MB_ICONSTOP);
		return;
	}
	for(int i=0;i<iN;i++)
	{
		fData_1[i]=g_SPEC.m_fAD[i]-g_SPEC.m_fDarkAD[i];
	}

	CString sTemp;
	FILE *fp;
	sTemp.Format("%02d_1.txt",m_iJType+1);
	sTemp=g_strCurPath+"\\Files\\"+sTemp;
	if((fp=fopen(sTemp,"wt"))==NULL)
		return;
	else
	{
		m_iN=g_SPEC.m_iPixN;
		for(int i=0;i<m_iN;i++)
		{
			CString strTemp;
			strTemp.Format("%d",i);
			fprintf(fp,strTemp);
			fprintf(fp,"	");

			strTemp.Format("%.2f",g_SPEC.SPEC_Pix2WL(i));
			fprintf(fp,strTemp);
			fprintf(fp,"	");

			strTemp.Format("%.1f",fData_1[i]);
			fprintf(fp,strTemp);
			fprintf(fp,"\n");
		}
		fclose(fp);
	}

	ReDraw();
	//保存第二组数据
	bR=g_SPEC.SPEC_GetDark(m_fIntTime*10,m_iAvgN);
	if(!bR)
	{
		if(g_bEnglish)
			AfxMessageBox("Communication fail!");
		else
			AfxMessageBox("关灯校零失败!");
	}

	if(g_SPEC.m_iMode==0)
		bR=g_SPEC.SPEC_DoScan(m_fIntTime*10,m_iAvgN,MY_TRIG_NORMAL,fMax,FALSE,TYPE_SCAN,FALSE);
	else
		bR=g_SPEC.SPEC_DoScan(m_fIntTime*10,m_iAvgN,MY_TRIG_NORMAL,fMax,FALSE,TYPE_SCAN,TRUE);
	if(!bR)
	{
		if(g_bEnglish)
			MessageBox("Sample fail!",NULL,MB_ICONSTOP);
		else
			MessageBox("采样失败!",NULL,MB_ICONSTOP);
		return;
	}
	for(i=0;i<iN;i++)
	{
		fData_1[i]=g_SPEC.m_fAD[i]-g_SPEC.m_fDarkAD[i];
	}

	sTemp.Format("%02d_2.txt",m_iJType+1);
	sTemp=g_strCurPath+"\\Files\\"+sTemp;
	if((fp=fopen(sTemp,"wt"))==NULL)
		return;
	else
	{
		m_iN=g_SPEC.m_iPixN;
		for(int i=0;i<m_iN;i++)
		{
			CString strTemp;
			strTemp.Format("%d",i);
			fprintf(fp,strTemp);
			fprintf(fp,"	");

			strTemp.Format("%.2f",g_SPEC.SPEC_Pix2WL(i));
			fprintf(fp,strTemp);
			fprintf(fp,"	");

			strTemp.Format("%.1f",fData_1[i]);
			fprintf(fp,strTemp);
			fprintf(fp,"\n");
		}
		fclose(fp);
	}
	CCmdTarget::EndWaitCursor();
}

void CDebug1::OnButton2() 
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

	strTemp=mOpenFile.GetPathName();
	FILE *fp;
	if((fp=fopen(strTemp,"rt"))==NULL)
		return;
	else
	{
		int iTemp;
		float fTemp;
		CString strTemp;
		for(int i=0;i<501;i++)
		{
			fscanf(fp,"%d",&iTemp);
			m_cDraw.m_fWL[i]=iTemp;
			for(int j=0;j<40;j++)
			{
				fscanf(fp,"%f",&fTemp);
				m_cDraw.m_fPL[j][i]=fTemp;
			}
			fscanf(fp,"\n");
		}
	}
	fclose(fp);

	ReDraw();
}

void CDebug1::OnCheckHalfWl() 
{
	// TODO: Add your control notification handler code here
	if(UpdateData(TRUE) == FALSE)
		return;

//	g_bHalfWL = m_bHalfWL;
//	ReDraw();
	GetBW();
}

void CDebug1::OnRadio3() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	GetZSG();
}

void CDebug1::OnRadio4() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	GetZSG();
}

void CDebug1::OnButtonOk2() 
{
	// TODO: Add your control notification handler code here
	BOOL bR;
	bR = UpdateData(TRUE);
	if(!bR)
		return;

	GetPX();
}

BOOL CDebug1::GetBW()
{
	if(!m_spData.m_bHaveData)
	{
		m_cBW.SetWindowText("");
		return FALSE;
	}
	
	float fBW = 10.0f; //左右10nm查找
	
	int iBW1 = 0;
	int iBW2 = 0;
	
	CString strTemp,sStr;
	sStr	= "";
	strTemp = "";
	int i,j;

	// 差值为0.1nm 因为直接用像素点表示的话误差偏大
	int iN = (int)((g_SPEC.T_SPECT2 - g_SPEC.T_SPECT1) / 0.1f + 1 + 0.5f);
	float fTemp;
	float fPL[10001];
	float fWL[10001];
	double fAD[4096];
	for(i = 0; i < g_SPEC.m_HAAS.m_iPixN; i++)
	{
		fAD[i] = m_fAD[i];
	}
	for(i=0;i<iN;i++)
	{
		float fLamda = g_SPEC.T_SPECT1 + 0.1f * i;
		fTemp = (float)g_doData.NewInt_double(g_SPEC.m_fLambdaPos, fAD, m_iN, fLamda);
		//外插清零 如果外插的数据小于0直接清零
		if(fLamda < g_SPEC.m_fLambdaPos[0] || fLamda > g_SPEC.m_fLambdaPos[m_iN - 1])
		{
			if(fTemp <= 0)
			{
				fTemp = 0;
			}
		}
		fPL[i] = fTemp;
		fWL[i] = fLamda;
	}

	for(j = 0; j < 3; j++)
	{
		float fLamba;
		if(j == 0)
		{
			fLamba = 404.66f;
		}
		if(j == 1)
		{
			fLamba = 435.88f;
		}
		if(j == 2)
		{
			fLamba = 546.07f;
		}

		for(i = 0; i < iN; i++)
		{
			if(fWL[i] >= (fLamba - fBW))
			{
				iBW1 = i;
				break;
			}
		}
		
		for(i = 0; i < iN; i++)
		{
			if(fWL[i] >= (fLamba + fBW))
			{
				iBW2 = i;
				break;
			}
		}
		
		
		float fPer = 0.5f;
		if(m_iPerType == 0)
			fPer = m_iPer / 100.0f;
		else
			fPer = m_iPer2 / 100.0f;

		float fMax = fPL[iBW1];
		int iMax = iBW1;
		for(i = iBW1; i < iBW2; i++)
		{
			if(fMax < fPL[i])
			{
				fMax = fPL[i];
				iMax = i;
			}
		}
		
		int iL = iBW1;
		int iR = iBW2;
		for(i = iMax; i > iBW1; i--)
		{
			if(fPL[i] < (fMax * fPer))
			{
				iL = i + 1;
				break;
			}
		}
		
		for(i = iMax; i < iBW2; i++)
		{
			if(fPL[i] < (fMax * fPer))
			{
				iR = i - 1;
				break;
			}
		}

		float fTemp;
		if(m_iPerType == 0)
			fTemp = (float)(fWL[iR] - fWL[iL]);
		else
		{
			float fS = 0;
			for(i = iL; i <= iR; i++)
				fS = fS + fPL[i] * (fWL[i + 1] - fWL[i]);
			
			float fW = 0;
			if(fMax > 0)
				fW = fS / fMax;
			else
				fW = 0;

			fTemp = fW;
		}

		/* 用最新带宽计算方法 */
		float fDW;
		m_spData.GetDW(fLamba, 	fDW);
		fTemp = fDW;

		strTemp.Format("%.1f ",fTemp);
		sStr = sStr + strTemp;
	}
	
	m_cBW.SetWindowText(sStr);
	return TRUE;
}

BOOL CDebug1::GetZSG()
{
	UpdateData(TRUE);
	//A光源加JB510检验杂散光 或者检验LED
	int i;
	int iMax = 0;
	m_iN = g_SPEC.m_HAAS.m_iPixN;
	float fMax = m_fAD[0];
	for(i = 0; i < m_iN; i++)
	{
		if(fMax < m_fAD[i])
		{
			fMax = m_fAD[i];
			iMax = i;
		}
	}
	
	float fAve = 0;
	for(i = 0; i < m_iN; i++)
	{
		if(m_iLevel_ZS == 0)
		{
			if(g_SPEC.SPEC_Pix2WL(i) <= 450.0f)
			{
				fAve = fAve + m_fAD[i];
			}
			else
			{
				break;
			}
		}
		else
		{
			if(g_SPEC.SPEC_Pix2WL(i) <= g_SPEC.SPEC_Pix2WL(iMax) - 150.0f)
			{
				fAve = fAve + m_fAD[i];
			}
			else
			{
				break;
			}
		}
	}
	if(i > 0)
	{
		fAve = fAve / i;
	}
	CString sTemp = "";
	if(fMax > 0)
	{
		sTemp.Format("%.3E", (fabs)(fAve / fMax));
	}
	m_cLevel.SetWindowText(sTemp);
	m_cLevel.SetFontSize(25);
	return TRUE;
}

void CDebug1::GetPX()
{
	int i;
	int iPos = 0; //谱线的位置
	m_iN = g_SPEC.m_iPixN;
	
	//差值为0.1nm 因为直接用像素点表示的话误差偏大
	int iN = (int)((g_SPEC.T_SPECT2 - g_SPEC.T_SPECT1) / 0.1f + 1 + 0.5f);
	float fTemp;
	float fPL[10001];
	float fWL[10001];
	double fAD[4096];
	for(i = 0; i < m_iN; i++)
	{
		fAD[i] = m_fAD[i];
	}
	
	for(i = 0; i < iN; i++)
	{
		float fLamda = g_SPEC.T_SPECT1 + 0.1f * i;
		fTemp = (float)g_doData.NewInt_double(g_SPEC.m_fLambdaPos, fAD, m_iN, fLamda);
		//外插清零 如果外插的数据小于0直接清零
		if(fLamda < g_SPEC.m_fLambdaPos[0] || fLamda > g_SPEC.m_fLambdaPos[m_iN - 1])
		{
			if(fTemp <= 0)
			{
				fTemp = 0;
			}
		}
		fPL[i] = fTemp;
		fWL[i] = fLamda;
	}
	
	for(i = 0; i < iN - 1; i++)
	{
		if(fWL[i] < m_fWLPX && fWL[i + 1] >= m_fWLPX)
		{
			iPos = i;
			break;
		}
	}
	
	int iMax = iPos;
	int iL;
	int iR;
	float fMax;
	fMax = fPL[iPos];
	for(i = iPos - 10; i < iPos + 10; i++)
	{
		if(i < 0)
		{
			i = 0;
		}
		if(i > iN)
		{
			i = iN;
		}
		if(fMax < fPL[i])
		{
			fMax = fPL[i];
			iMax = i;
		}
	}
	
	float fHalf;
	if(m_iPerType == 0)
		fHalf = m_iPer / 100.0f;
	else
		fHalf = m_iPer2 / 100.0f;

	iL = iMax;
	for(i = iMax; i > 0; i--)
	{
		if(fPL[i] < (fMax * fHalf))
		{
			iL = i + 1;
			break;
		}
	}
	
	iR = iMax;
	for(i = iMax; i < iN; i++)
	{
		if(fPL[i] < (fMax * fHalf))
		{
			iR = i - 1;
			break;
		}
	}
	
	CString sTemp;
	if(m_iPerType == 0)
		sTemp.Format("%.1fnm",fWL[iR] - fWL[iL]);
	else
	{
		float fS = 0;
		for(i = iL; i <= iR; i++)
			fS = fS + fPL[i] * (fWL[i + 1] - fWL[i]);

		float fW = 0;
		if(fMax > 0)
			fW = fS / fMax;
		else
			fW = 0;
		sTemp.Format("%.1fnm", fW);
	}

	float fDW;
	m_spData.GetDW(m_fWLPX, fDW);
	sTemp.Format("%.1fnm", fDW);
	m_cWLHF.SetWindowText(sTemp);
}

void CDebug1::OnButtonStart2() 
{
	// TODO: Add your control notification handler code here
	if(UpdateData(TRUE) == FALSE)
		return;

	if(m_iPixSele > m_iPixSele2)
	{
		if(g_bEnglish)
			AfxMessageBox("Error!");
		else
			AfxMessageBox("第1个像素不能比第2个大！");
		return;
	}

	m_bCancel = FALSE;
	EnableShowNew(TRUE);

	AfxBeginThread(Thread, this);
}

void CDebug1::OnButtonStop2() 
{
	// TODO: Add your control notification handler code here
	m_bCancel = TRUE;
}

UINT CDebug1::Thread(LPVOID pPar)
{
	CDebug1 *pDlg = (CDebug1 *)pPar;

	int iN;
	if(pDlg->m_iStepType == 0)
		iN = (int)((pDlg->m_fIntTime2-pDlg->m_fIntTime1)/pDlg->m_fIntervalTime + 1 + 0.5f);
	else
	{
		iN = 40;
	}

	double dTemp_s = 1.0f;
	if(pDlg->m_iStepType == 1)
	{
		// T1 * s ^ n = T2
		dTemp_s = pow(pDlg->m_fIntTime2 / pDlg->m_fIntTime1, 1.0 / iN);
		iN++;
	}

	CString strTemp;
	float fTime[1000];
	float fAD[1000];
	float fAD_Dark[1000];

	int i;
	BOOL bR;
	AfxMessageBox("请开灯!");
	for(i = 0; i < iN; i++)
	{
		if(pDlg->m_bCancel == TRUE)
			break;

		float fIntTIme;
		if(pDlg->m_iStepType == 0)
			fIntTIme = pDlg->m_fIntTime2 - pDlg->m_fIntervalTime * i;
		else
			fIntTIme = pDlg->m_fIntTime1 * pow(dTemp_s, iN - 1 - i);

		if(fIntTIme > 1.0f)
		{
			strTemp.Format("%.0f", fIntTIme);
			fIntTIme = (float)atof(strTemp);
		}

		if(fIntTIme < pDlg->m_fIntTime1)
			fIntTIme = pDlg->m_fIntTime1;
	
		g_SPEC.m_bCro = pDlg->m_bCro;
		bR = pDlg->Test(fIntTIme, pDlg->m_iAvgN, pDlg->m_fAD, pDlg->m_iN);
		if(!bR)
			break;

		fTime[i] = fIntTIme;

		float fTempAD = 0;
		int iTempNum = 0;
		for(int s = pDlg->m_iPixSele; s <= pDlg->m_iPixSele2; s++)
		{
			fTempAD += pDlg->m_fAD[s];
			iTempNum++;
		}

		if(iTempNum > 0)
			fTempAD /= iTempNum;

		fAD[i] = fTempAD;
	}

	//请关灯
	AfxMessageBox("请关灯!");
	for(i = 0; i < iN; i++)
	{
		if(pDlg->m_bCancel == TRUE)
			break;

		float fIntTIme;
		if(pDlg->m_iStepType == 0)
			fIntTIme = pDlg->m_fIntTime2 - pDlg->m_fIntervalTime * i;
		else
			fIntTIme = pDlg->m_fIntTime1 * pow(dTemp_s, iN - 1 - i);

		if(fIntTIme > 1.0f)
		{
			strTemp.Format("%.0f", fIntTIme);
			fIntTIme = (float)atof(strTemp);
		}

		if(fIntTIme < pDlg->m_fIntTime1)
			fIntTIme = pDlg->m_fIntTime1;
	
		g_SPEC.m_bCro = pDlg->m_bCro;
		bR = pDlg->Test(fIntTIme, pDlg->m_iAvgN, pDlg->m_fAD, pDlg->m_iN);
		if(!bR)
			break;

		fTime[i] = fIntTIme;

		float fTempAD = 0;
		int iTempNum = 0;
		for(int s = pDlg->m_iPixSele; s <= pDlg->m_iPixSele2; s++)
		{
			fTempAD += pDlg->m_fAD[s];
			iTempNum++;
		}

		if(iTempNum > 0)
			fTempAD /= iTempNum;

		fAD_Dark[i] = fTempAD;
	}


	FILE *fp;
	if((fp=fopen(g_strCurPath + "temp_Ad_line.txt", "wt"))==NULL)
	{

	}
	else
	{	
		for(i = 0; i < iN; i++)
			fprintf(fp,"%g\t %g %g\n", fTime[i], fAD[i],fAD_Dark[i]);
		fclose(fp);
	}


	float fMaxTime = 0;
	float fMaxAD = -100;
	for(i = 0; i < iN; i++)
	{
		fAD[i] = fAD[i] - fAD_Dark[i];
		if(fAD[i] >= 50000 && fAD[i] <= 62000)
		{
			if(fAD[i] > fMaxAD)
			{
				fMaxAD = fAD[i];
				fMaxTime = fTime[i];
			}
		}
	}

	if(fMaxAD >= 50000)
	{
		FILE *fp;
		if((fp=fopen(g_strCurPath + "cal\\temp_ModePhe.dat", "wt"))==NULL)
		{
			
		}
		else
		{	
			for(i = 0; i < iN; i++)
			{
				if(fAD[i] <= 62000)
					fprintf(fp,"%g %.4f\n", fAD[i], (fMaxAD/ fMaxTime) / (fAD[i] /fTime[i]));
			}

			fprintf(fp,"-1 -1\n");
			fclose(fp);

			if(!g_bEnglish)
				AfxMessageBox("Cal 目录下已产生文件 temp_ModePhe.dat");
			else
				AfxMessageBox("FAIL");

		}
	}
	else
	{
		if(!g_bEnglish)
			AfxMessageBox("没有AD超过50000，不能产生temp_ModePhe.dat文件!");
		else
			AfxMessageBox("FAIL");
	}

	pDlg->EnableShowNew(FALSE);
	return 0;
}

void CDebug1::EnableShowNew(BOOL bStart)
{
	m_cStart2.EnableWindow(!bStart);
	m_cStop.EnableWindow(bStart);
}

void CDebug1::OnButtonInit() 
{
	// TODO: Add your control notification handler code here
	int iR = SA_OpenSpectrometers();
	if(iR >= 0)
	{
	}
	else
	{
		AfxMessageBox("打开GCS失败!");
	}
/*
	if(1)//!g_bHaveOpen)
	{
		CCmdTarget::BeginWaitCursor();
		int iPixN;
		int fAD;
		BOOL bR;
		bR = g_SPEC.m_HAAS.Init(iPixN,fAD);
		if(!bR)
		{
			AfxMessageBox("打开GCS失败!");
		}
		CCmdTarget::EndWaitCursor();
	}*/
}
