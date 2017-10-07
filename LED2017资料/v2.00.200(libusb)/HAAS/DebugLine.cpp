// DebugLine.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "DebugLine.h"
#include "DaXinPowerComm.h"
#include "Global_MySpec.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDebugLine property page
extern CString	g_strSouComm;
extern BOOL		g_bAutoLamp;
extern CDaXinPowerComm g_cPower;

IMPLEMENT_DYNCREATE(CDebugLine, CPropertyPage)

CDebugLine::CDebugLine() : CPropertyPage(CDebugLine::IDD)
{
	//{{AFX_DATA_INIT(CDebugLine)
	m_iCroPix1 = 355;
	m_iCroPix2 = 365;
	m_iT1 = 1;
	m_iT2 = 67;
	m_iT3 = 2;
	m_iJsPix1 = 355;
	m_iJsPix2 = 365;
	//}}AFX_DATA_INIT
}

CDebugLine::~CDebugLine()
{
}

void CDebugLine::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDebugLine)
	DDX_Control(pDX, IDC_EDIT_DATA, m_cData);
	DDX_Text(pDX, IDC_EDIT_CRO_PIX1, m_iCroPix1);
	DDX_Text(pDX, IDC_EDIT_CRO_PIX2, m_iCroPix2);
	DDX_Text(pDX, IDC_EDIT_CRO_T1, m_iT1);
	DDX_Text(pDX, IDC_EDIT_CRO_T2, m_iT2);
	DDX_Text(pDX, IDC_EDIT_CRO_T3, m_iT3);
	DDX_Text(pDX, IDC_EDIT_JS_PIX1, m_iJsPix1);
	DDX_Text(pDX, IDC_EDIT_JS_PIX2, m_iJsPix2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDebugLine, CPropertyPage)
	//{{AFX_MSG_MAP(CDebugLine)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDebugLine message handlers

void CDebugLine::OnOK() 
{
	// TODO: Add extra validation here
	
//	CPropertyPage::OnOK();
}

void CDebugLine::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CPropertyPage::OnCancel();
}

void CDebugLine::OnButton1() 
{
	// TODO: Add your control notification handler code here
	//自动计算非线性数据
	//第一步 关灯 测试暗电流数据
	CCmdTarget::BeginWaitCursor();

	BOOL bR;
	bR = UpdateData(TRUE);
	if (!bR)
	{
		return;
	}

	int iCOM;
	sscanf(g_strSouComm,"COM%d", &iCOM);
	bR = g_cPower.DX_Power_Init(iCOM);
	if(!bR)
	{
		AfxMessageBox("FAIL !");
		return;
	}

	bR = g_cPower.DX_Power_SetPara(4, 20); //4V 20mA
	if(!bR)
	{
		AfxMessageBox("FAIL !");
		return;
	}

	bR = g_cPower.DX_Power_Output(FALSE);
	if (!bR)
	{
		AfxMessageBox("FAIL !");
	}

	float fDarkAD[100];
	float fDataAD[100];

	float fMax;
	float fIntTime;
	int iN = 0;
	while(1)
	{
		fIntTime = m_iT1 + m_iT3 * iN * 1.0f;
		bR = g_SPEC.SPEC_DoScan(fIntTime, 10, MY_TRIG_NORMAL, fMax, FALSE, TYPE_SCAN, TRUE);
		if (!bR)
		{
			AfxMessageBox("FAIL !");
			return;
		}

		//取出像素波段内暗电流
		fDarkAD[iN] = 0;
		for (int i = m_iCroPix1; i <= m_iCroPix2; i++)
		{
			fDarkAD[iN] = fDarkAD[iN] + g_SPEC.m_fAD[i];
		}
		fDarkAD[iN] = fDarkAD[iN]/i;

		iN++;
		if (fIntTime >= m_iT2)
		{
			break;
		}
	}

	AfxMessageBox("b");
	//点亮LED
	bR = g_cPower.DX_Power_Output(TRUE);
	if (!bR)
	{
		AfxMessageBox("FAIL !");
	}
	
	iN = 0;
	while(1)
	{
		fIntTime = m_iT1 + m_iT3 * iN * 1.0f;
		bR = g_SPEC.SPEC_DoScan(fIntTime, 10, MY_TRIG_NORMAL, fMax, FALSE, TYPE_SCAN, TRUE);
		if (!bR)
		{
			AfxMessageBox("FAIL !");
			return;
		}
		
		//取出像素波段内AD
		fDataAD[iN] = 0;
		for (int i = m_iCroPix1; i <= m_iCroPix2; i++)
		{
			fDataAD[iN] = fDataAD[iN] + g_SPEC.m_fAD[i];
		}
		fDataAD[iN] = fDataAD[iN]/i;
		
		iN++;		
		if (fIntTime >= m_iT2)
		{
			break;
		}
	}

	CString strTemp,sStr;
	sStr = "";
	strTemp = "Type:4\r\n";
	sStr = sStr + strTemp;
	strTemp = "ModeNum:1\r\n";
	sStr = sStr + strTemp;
	strTemp.Format("WL:%.1f\r\n",(m_iCroPix1 + m_iCroPix2) / 2);
	sStr = sStr + strTemp;
	strTemp.Format("KNum:%d\r\n",iN);
	sStr = sStr + strTemp;

	for (int i = 0; i < iN; i++)
	{
		float fD1 = fDataAD[i] - fDarkAD[i];
		float fD0 = fDataAD[iN - 1] - fDarkAD[iN - 1];
		strTemp.Format("%.3f#%.7f\r\n",fD1, (fD1/(m_iT1 + m_iT3 * i)) / (fD0/m_iT2) );
		sStr = sStr + strTemp;
	}
	m_cData.SetWindowText(sStr);
}

void CDebugLine::OnButton2() 
{
	// TODO: Add your control notification handler code here
	
}
