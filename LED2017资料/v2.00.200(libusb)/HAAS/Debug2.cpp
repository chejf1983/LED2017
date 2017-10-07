// Debug2.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "Debug2.h"
#include "Global_MySpec.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDebug2 property page

extern float g_fSpect1;
extern float g_fSpect2;

IMPLEMENT_DYNCREATE(CDebug2, CPropertyPage)

CDebug2::CDebug2() : CPropertyPage(CDebug2::IDD)
{
	//{{AFX_DATA_INIT(CDebug2)
	m_iAvgN = 5;
	m_fIntTime = 40.0f;
	m_fPix = 500;
	m_iSeleStaWL = 0;
	m_iType = 0;
	m_fHalf = 30.0f;
	m_fSetDoLimitAD = 0.0f;
	m_fSetDoWL = 0.0f;
	m_iSR2AngleType = 0;
	//}}AFX_DATA_INIT
	CString strSection  = "Start_Debug2_A";

	CString strIntTime  = "IntTime";
	CString strAvgN     = "AvgN";
	CString strPix      = "Pix";
	CString strStaWL    = "StaWL";
	CString strPathName = "PathName";
	CString strHalf		= "HALF";

	CString strTemp;
	strTemp     = AfxGetApp()->GetProfileString(strSection,strIntTime,"100");
	m_fIntTime  = (float)atof(strTemp);
	m_iAvgN     = AfxGetApp()->GetProfileInt(strSection,strAvgN,1);
	strTemp     = AfxGetApp()->GetProfileString(strSection,strPix,"500");
	m_fPix		= (float)atof(strTemp);
	m_iSeleStaWL= AfxGetApp()->GetProfileInt(strSection,strStaWL,0);

	m_strPathName=AfxGetApp()->GetProfileString(strSection,strPathName,"");
	m_strPathName=g_strCurPath+"wavecor\\*.WLC";

	strTemp     = AfxGetApp()->GetProfileString(strSection,strHalf,"10");
	m_fHalf	    = (float)atof(strTemp);

}

CDebug2::~CDebug2()
{
}

void CDebug2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDebug2)
	DDX_Control(pDX, IDC_BUTTON_SAVE_COR, m_cSaveCor);
	DDX_Control(pDX, IDC_COMBO_STA_WL, m_cStaWL);
	DDX_Control(pDX, IDC_DRAW2, m_cDraw2);
	DDX_Control(pDX, IDC_LIST_WL, m_cWL);
	DDX_Control(pDX, IDC_EDIT_PIX, m_cPix);
	DDX_Control(pDX, IDC_EDIT_COR, m_cCor);
	DDX_Control(pDX, IDC_DRAW, m_cDraw);
	DDX_Text(pDX, IDC_EDIT_AVG_N, m_iAvgN);
	DDV_MinMaxInt(pDX, m_iAvgN, 1, 100);
	DDX_Text(pDX, IDC_EDIT_INT_TIME, m_fIntTime);
	DDV_MinMaxFloat(pDX, m_fIntTime, 1.e-002f, 60000.f);
	DDX_Text(pDX, IDC_EDIT_PIX, m_fPix);
	DDX_CBIndex(pDX, IDC_COMBO_STA_WL, m_iSeleStaWL);
	DDX_Radio(pDX, IDC_RADIO_TYPE1, m_iType);
	DDX_Text(pDX, IDC_EDIT_HALF, m_fHalf);
	DDV_MinMaxFloat(pDX, m_fHalf, 0.f, 100.f);
	DDX_Text(pDX, IDC_EDIT_SET_DO_LIMIT_AD, m_fSetDoLimitAD);
	DDV_MinMaxFloat(pDX, m_fSetDoLimitAD, 0.f, 500.f);
	DDX_Text(pDX, IDC_EDIT_SET_DO_WL, m_fSetDoWL);
	DDV_MinMaxFloat(pDX, m_fSetDoWL, 0.f, 50.f);
	DDX_CBIndex(pDX, IDC_COMBO_SR_2_ANGLE, m_iSR2AngleType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDebug2, CPropertyPage)
	//{{AFX_MSG_MAP(CDebug2)
	ON_BN_CLICKED(IDC_BUTTON_TEST, OnButtonTest)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_WM_LBUTTONDOWN()
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_1, OnDeltaposSpin1)
	ON_BN_CLICKED(IDC_BUTTON_PEAK, OnButtonPeak)
	ON_BN_CLICKED(IDC_BUTTON_CALC, OnButtonCalc)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, OnButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_DEL2, OnButtonDel2)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_COR, OnButtonSaveCor)
	ON_BN_CLICKED(IDC_RADIO_TYPE2, OnRadioType2)
	ON_BN_CLICKED(IDC_RADIO_TYPE1, OnRadioType1)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_EN_CHANGE(IDC_EDIT_HALF, OnChangeEditHalf)
	ON_BN_CLICKED(IDC_BUTTON_SAVE2, OnButtonSave2)
	ON_BN_CLICKED(IDC_BUTTON_OK_SET, OnButtonOkSet)
	ON_CBN_SELCHANGE(IDC_COMBO_SR_2_ANGLE, OnSelchangeComboSr2Angle)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, OnButtonLoad)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDebug2 message handlers

BOOL CDebug2::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_wlCorData.Load(g_strCurPath+"temp.WLC");

	int iSaveSele=m_iSeleStaWL;
	m_cStaWL.ResetContent();
	CString strTemp;
	for(int i=0;i<g_SPEC.m_arra_strSource.GetSize();i++)
	{
		strTemp.Format("%s %.3fnm",g_SPEC.m_arra_strSource[i],g_SPEC.m_arra_fStaWL[i]);
		m_cStaWL.InsertString(i,strTemp);
	}
	m_iSeleStaWL=iSaveSele;
	m_cStaWL.SetCurSel(m_iSeleStaWL);


	m_iN=g_SPEC.m_iPixN;
	for(i=0;i<m_iN;i++)
		m_fAD[i]=0;

	m_debugDrawPara.bMouse=FALSE;
	m_debugDrawPara.iCurSele=(int)(m_fPix);
	m_debugDrawPara.bSetZ=FALSE;
	m_debugDrawPara.X1=100;
	m_debugDrawPara.X2=500;
	ReDraw();

	m_cWL.SetExtendedStyle(m_cWL.GetExtendedStyle()  | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);

	ReList();

	m_fSetDoLimitAD = CSpectData::m_fSetDoLimitAD;
	m_fSetDoWL = CSpectData::m_fSetDoWL;

	m_iSR2AngleType = g_SPEC.m_iSR2AngleType;

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDebug2::ReDraw()
{
	m_debugDrawPara.bSetZ=FALSE;
	m_cDraw.DrawMyDebug(m_fAD,m_iN,TRUE,m_debugDrawPara);
	m_debugDrawPara.bSetZ=TRUE;
	m_debugDrawPara.X1=m_debugDrawPara.iCurSele-25;
	m_debugDrawPara.X2=m_debugDrawPara.iCurSele+25;
	if(m_iType==0)
		m_cDraw2.DrawMyDebug(m_fAD,m_iN,TRUE,m_debugDrawPara,0);
	else
		m_cDraw2.DrawMyDebug(m_fAD,m_iN,TRUE,m_debugDrawPara,m_fHalf);

	CString strTemp;
	
//	m_fPix=(float)(m_debugDrawPara.iCurSele);
	strTemp.Format("%.1f",m_fPix);
	m_cPix.SetWindowText(strTemp);
}

void CDebug2::OnButtonTest() 
{
	// TODO: Add your control notification handler code here
	if(UpdateData(TRUE)==FALSE)
		return;
	BOOL bR;
	bR=Test(m_fIntTime,m_iAvgN,m_fAD,m_iN);
	if(!bR)
		return;
	ReDraw();

	CString strSection  = "Start_Debug2_A";

	CString strIntTime  = "IntTime";
	CString strAvgN     = "AvgN";
	CString strPix      = "Pix";
	CString strStaWL    = "StaWL";
	CString strPathName = "PathName";
	CString strHalf		= "HALF";

	CString strTemp;
	strTemp.Format("%f",m_fIntTime);
	AfxGetApp()->WriteProfileString(strSection,strIntTime,strTemp);
	AfxGetApp()->WriteProfileInt(strSection,strAvgN,m_iAvgN);
	strTemp.Format("%f",m_fPix);
	AfxGetApp()->WriteProfileString(strSection,strPix,strTemp);
	AfxGetApp()->WriteProfileInt(strSection,strStaWL,m_iSeleStaWL);
	AfxGetApp()->WriteProfileString(strSection,strPathName,m_strPathName);
	strTemp.Format("%f",m_fHalf);
	AfxGetApp()->WriteProfileString(strSection,strHalf,strTemp);
}

void CDebug2::OnButtonAdd() 
{
	// TODO: Add your control notification handler code here
	if(UpdateData(TRUE)==FALSE)
		return;

	if(m_iSeleStaWL>=0&&m_iSeleStaWL<g_SPEC.m_arra_fStaWL.GetSize())
	{
		float fStaWL=g_SPEC.m_arra_fStaWL[m_iSeleStaWL];
		m_wlCorData.m_iPixN=g_SPEC.m_iPixN;

		m_wlCorData.Add(fStaWL,m_fPix);
		ReList();

		m_wlCorData.Save(g_strCurPath+"temp.WLC",FALSE);
	}
}

BOOL CDebug2::Test(float fIntTime, int iAvgN, float fData[], int &iN)
{
	CCmdTarget::BeginWaitCursor();
	float fMax;
	BOOL bR;
	if(g_SPEC.m_iMode==0)
		bR=g_SPEC.SPEC_DoScan(fIntTime,iAvgN,MY_TRIG_NORMAL,fMax,FALSE,TYPE_CHECK,TRUE);
	else
		bR=g_SPEC.SPEC_DoScan(fIntTime,iAvgN,MY_TRIG_NORMAL,fMax,FALSE,TYPE_CHECK,TRUE);
	if(!bR)
	{
		if(g_bEnglish)
			MessageBox("Sample fail!",NULL,MB_ICONSTOP);
		else
			MessageBox("采样失败!",NULL,MB_ICONSTOP);
		return FALSE;
	}
	iN=g_SPEC.m_iPixN;
	for(int i=0;i<iN;i++)
	{
		fData[i]=g_SPEC.m_fAD[i]-g_SPEC.m_fDarkAD[i];
	}
	CCmdTarget::BeginWaitCursor();
	return TRUE;
}

void CDebug2::OnLButtonDown(UINT nFlags, CPoint point) 
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

void CDebug2::OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	if(pNMUpDown->iDelta<0)
		m_fPix=m_fPix+1;
	else
		m_fPix=m_fPix-1;
	UpdateData(FALSE);

	m_debugDrawPara.iCurSele=(int)(m_fPix);
	ReDraw();
	
	*pResult = 0;
}

void CDebug2::OnButtonPeak() 
{
	// TODO: Add your control notification handler code here
/*	UpdateData(TRUE);
	float fMax=0;
	int i;
	int iMaxPos=m_debugDrawPara.X1;
	for(i=m_debugDrawPara.X1;i<=m_debugDrawPara.X2;i++)
	{
		if(m_fAD[i]>fMax)
		{
			iMaxPos=i;
			fMax=m_fAD[i];
		}
	}
	if(m_iType==0)
	{
		m_debugDrawPara.iCurSele=iMaxPos;
		m_fPix=(float)(iMaxPos);
	}
	else
	{
		int iN=100;
		int iL=0;
		for(i=0;i<=iN;i++)
		{
			if(m_fAD[iMaxPos-i]>=(fMax*0.3f))
			{
				iL=i;
			}
			else
				break;
		}
		int iR=0;
		for(i=0;i<=iN;i++)
		{
			if(m_fAD[iMaxPos+i]>=(fMax*0.3f))
			{
				iR=i;
			}
			else
				break;
		}
		
		float fSum1,fSum2;
		fSum1=0;
		for(i=iL;i<iR;i++)
		{
			fSum1=m_fAD[i+iMaxPos]+fSum1;
		}
		fSum2=0;
		for(i=iL;i<iR;i++)
		{
			fSum2=m_fAD[i+iMaxPos]+fSum2;
			if(fSum2>=(fSum1/2))
			{
				iMaxPos=i+(iMaxPos-iL);
				break;
			}
		}
//		iMaxPos=iMaxPos+(iR-iL)/2;
		m_debugDrawPara.iCurSele=iMaxPos;
	}
	ReDraw();*/
	UpdateData(TRUE);
	float fMax=0;
	int i;
	int iMaxPos=m_debugDrawPara.X1;
	for(i=m_debugDrawPara.X1;i<=m_debugDrawPara.X2;i++)
	{
		if(m_fAD[i]>fMax)
		{
			iMaxPos=i;
			fMax=m_fAD[i];
		}
	}
	if(m_iType==0)
	{
		m_debugDrawPara.iCurSele=iMaxPos;
		m_fPix=(float)(iMaxPos);
	}
	else
	{
		int MM=100;
		int iN=(m_debugDrawPara.X2-m_debugDrawPara.X1)*MM;
		float fData[10001];
		//插值为0.1个像素点的数据
		for(int i=0;i<iN;i++)
		{
			float d2,d1;
			d1=m_fAD[m_debugDrawPara.X1+i/MM];
			d2=m_fAD[m_debugDrawPara.X1+i/MM+1];

			fData[i]=(float)(d1+(d2-d1)*(i%MM)/MM);
		}
		//找左边0.1位置
		int iL=(iMaxPos-m_debugDrawPara.X1)*MM;
		for(i=(iMaxPos-m_debugDrawPara.X1)*MM;i>=0;i--)
		{
			if(fData[i]>=(fMax*m_fHalf/100))
			{
				iL=i;
			}
			else
				break;
		}
		//找右边0.1位置
		int iR=(iMaxPos-m_debugDrawPara.X1)*MM;
		for(i=(iMaxPos-m_debugDrawPara.X1)*MM;i<=iN;i++)
		{
			if(fData[i]>=(fMax*m_fHalf/100))
			{
				iR=i;
			}
			else
				break;
		}
		
		float fSum1,fSum2;
		fSum1=0;
		for(i=iL;i<=iR;i++)
		{
			fSum1=fData[i]+fSum1;
		}
		fSum2=0;
		for(i=iL;i<=iR;i++)
		{
			fSum2=fData[i]+fSum2;
			if(fSum2>=(fSum1/2))
			{
				iMaxPos=i;
				break;
			}
		}
//		float fAdd;
//		fAdd=(fSum2-fSum1/2)/m_fAD[iMaxPos];
		m_fPix=(float)(iMaxPos*1.0f/MM+m_debugDrawPara.X1);
		m_debugDrawPara.iCurSele=(int)(m_fPix);
		m_debugDrawPara.fCurSele=m_fPix;
	}
	ReDraw();
}

void CDebug2::ReList()
{
	m_cWL.DeleteAllItems();
	while(1)
	{
		if(m_cWL.DeleteColumn(0)==FALSE)
			break;
	}

	int iN=0;

	CString strTemp;

	strTemp="SN.";
	m_cWL.InsertColumn(iN,strTemp);
	m_cWL.SetColumnWidth(iN,20);
	iN++;

	if(g_bEnglish)
		strTemp="WL(nm)";
	else
		strTemp="波长(nm)";
	m_cWL.InsertColumn(iN,strTemp);
	m_cWL.SetColumnWidth(iN,60);
	iN++;

	if(g_bEnglish)
		strTemp="Pix";
	else
		strTemp="像素";
	m_cWL.InsertColumn(iN,strTemp);
	m_cWL.SetColumnWidth(iN,50);
	iN++;

	int NN=m_wlCorData.m_arra_fStaWL.GetSize();
	for(int i=0;i<NN;i++)
	{
		iN=0;

		strTemp.Format("%d",i+1);
		m_cWL.InsertItem(i,strTemp,6);
		iN++;

		strTemp.Format("%8.3f",m_wlCorData.m_arra_fStaWL[i]);
		m_cWL.SetItemText(i,iN,strTemp);
		iN++;

		strTemp.Format("%4.1f",m_wlCorData.m_arra_fPix[i]);
		m_cWL.SetItemText(i,iN,strTemp);
		iN++;
	}
}

void CDebug2::OnButtonCalc() 
{
	// TODO: Add your control notification handler code here
	m_wlCorData.CalcCor(m_fC,m_iCN);

	CString strRe="";
	CString strTemp;
	for(int i=0;i<m_iCN;i++)
	{
		strTemp.Format("%e ",m_fC[i]);
		strRe=strRe+strTemp;
	}
	m_cCor.SetWindowText(strRe);

	m_cSaveCor.EnableWindow(m_iCN>0);

	m_wlCorData.Save(g_strCurPath+"temp.WLC");
}

void CDebug2::OnButtonOpen() 
{
	// TODO: Add your control notification handler code here
	static char szFilter[]="WLC Files(*.WLC)|*.WLC||";
	CFileDialog dOpen(TRUE,".WLC",m_strPathName,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter,NULL);
	if(dOpen.DoModal()==IDCANCEL)
		return;	

	m_strPathName=dOpen.GetPathName();

	m_wlCorData.Load(m_strPathName);
	ReList();
}

void CDebug2::OnButtonSave() 
{
	// TODO: Add your control notification handler code here
	static char szFilter[]="WLC Files(*.WLC)|*.WLC||";
	CFileDialog dSave(FALSE,".WLC",m_strPathName,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter,NULL);
	if(dSave.DoModal()==IDCANCEL)
		return;

	m_strPathName=dSave.GetPathName();

	m_wlCorData.Save(m_strPathName);
}

void CDebug2::OnButtonDel2() 
{
	// TODO: Add your control notification handler code here
	POSITION p = m_cWL.GetFirstSelectedItemPosition();
	CString msg = _T("");
	while (p)
	{
		int nSelected = m_cWL.GetNextSelectedItem(p);
		if (msg.IsEmpty())
			msg = _T("The following items are selected: ");

		CString str;
		str.Format(_T("%s"), m_cWL.GetItemText(nSelected, 0));
		int iSele=atoi(str)-1;
		if(iSele>=0&&iSele<m_wlCorData.m_arra_fPix.GetSize())
		{
			int iR;
			iR=MessageBox("确定删除所选择的波长与像素?",NULL,MB_OKCANCEL|MB_ICONINFORMATION);
			if(iR==IDCANCEL)
				break;
			m_wlCorData.m_arra_fStaWL.RemoveAt(iSele);
			m_wlCorData.m_arra_fPix.RemoveAt(iSele);
			ReList();
		}
		break;
	}
}

void CDebug2::OnButtonSaveCor() 
{
	// TODO: Add your control notification handler code here
	if(m_iCN > 0)
	{
		g_SPEC.m_Icor  = m_fC[0];
		g_SPEC.m_C1cor = m_fC[1];
		g_SPEC.m_C2cor = m_fC[2];
		g_SPEC.m_C3cor = m_fC[3];

		g_SPEC.SaveWaveData();
	}
}

void CDebug2::OnRadioType2() 
{
	// TODO: Add your control notification handler code here
	
}

void CDebug2::OnRadioType1() 
{
	// TODO: Add your control notification handler code here
	
}

void CDebug2::OnButton1() 
{
	// TODO: Add your control notification handler code here
	CString strTemp;
	static char BASED_CODE szFilter[]="TXT Files(*.dat)|*.dat||";
	CFileDialog mOpenFile(TRUE, ".dat",strTemp,  OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);
	if(mOpenFile.DoModal()==IDCANCEL)
		return;
	strTemp=mOpenFile.GetPathName();
	FILE *fp;
	if((fp=fopen(strTemp,"rt"))==NULL)
		return;
	else
	{
		int iTemp;
		for(int i=0;i<2048;i++)
			fscanf(fp,"%d %f\n",&iTemp,&m_fAD[i]);
		m_iN=2048;
	for(i=0;i<m_iN;i++)
		g_SPEC.m_fAD[i]=m_fAD[i];
	}
	fclose(fp);
	ReDraw();
}

void CDebug2::OnChangeEditHalf() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	ReDraw();
}

void CDebug2::OnButtonSave2() 
{
	// TODO: Add your control notification handler code here
	static char szFilter[]="Excel Files(*.xls)|*.xls||";
	CFileDialog dSave(FALSE,".xls",m_strPathName,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter,NULL);
	if(dSave.DoModal()==IDCANCEL)
		return;	

	m_strPathName=dSave.GetPathName();

	FILE *fp;
	if((fp=fopen(m_strPathName,"wt"))==0)
		return;
	else
	{
		for(int i=0;i<m_iN;i++)
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

void CDebug2::OnButtonOkSet() 
{
	// TODO: Add your control notification handler code here
	if(UpdateData(TRUE) == FALSE)
		return;
	CSpectData::m_fSetDoLimitAD = m_fSetDoLimitAD;
	CSpectData::m_fSetDoWL = m_fSetDoWL;
}

void CDebug2::OnSelchangeComboSr2Angle() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	g_SPEC.m_iSR2AngleType  = m_iSR2AngleType;
}

void CDebug2::OnButtonLoad() 
{
	// TODO: Add your control notification handler code here
	BOOL bR;
	
	bR = g_SPEC.m_HAAS.LoadWaveToGCS(m_fC);
	if (!bR)
	{
		AfxMessageBox("FAIL");
	}
	else
	{
		AfxMessageBox("OK");
	}
}
