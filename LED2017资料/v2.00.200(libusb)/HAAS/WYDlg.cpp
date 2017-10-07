// WYDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "WYDlg.h"
#include "DlgSetPower.h"
#include "Serial.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWYDlg dialog

extern BOOL g_bEnglish;
extern BOOL g_bDemo;

CWYDlg::CWYDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWYDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWYDlg)
	m_strCom	= _T("");
	m_strCurr	= _T("");
	m_fSetCurr	= 0.0f;
	m_fSetVol	= 0.0f;
	m_strVol	= _T("");
	m_iSeleUI	= -1;
	m_iTypeWY	= 1;
	//}}AFX_DATA_INIT

	CString strSection     =  "WY";
	CString strCom         =  "COM";
	CString strSetVol      =  "SetVol";
	CString strSetCurr     =  "SetCurr";
	CString strSeleUI      =  "SeleUI";
	CString strTypeWY      =  "TypeWY";

	CString strTemp;

	m_strCom	= AfxGetApp()->GetProfileString(strSection,strCom,"COM1");
	strTemp		= AfxGetApp()->GetProfileString(strSection,strSetVol,"1.000");
	m_fSetVol	= (float)atof(strTemp);
	strTemp		= AfxGetApp()->GetProfileString(strSection,strSetCurr,"0.100");
	m_fSetCurr	= (float)atof(strTemp);
	m_iSeleUI	= AfxGetApp()->GetProfileInt(strSection,strSeleUI,0);
	m_iTypeWY	= AfxGetApp()->GetProfileInt(strSection,strTypeWY,1);

	m_fVolR1	= 0;
	m_fVolR2	= 120;
	m_fCurrR1	= 0;
	m_fCurrR2	= 10.0f;

	char Path[256];
	GetModuleFileName(NULL,Path,250);   
	* ( strrchr( Path, '\\' ) + 1 ) = '\0';	
	m_strCurPath=Path;
	
	GetRangeFile();

	m_strAddr="100";
}


void CWYDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWYDlg)
	DDX_Control(pDX, IDC_RANGE, m_cRange);
	DDX_CBString(pDX, IDC_COMBO_COM, m_strCom);
	DDX_Text(pDX, IDC_EDIT_CURR, m_strCurr);
	DDX_Text(pDX, IDC_EDIT_SET_CURR, m_fSetCurr);
	DDX_Text(pDX, IDC_EDIT_SET_VOL, m_fSetVol);
	DDX_Text(pDX, IDC_EDIT_VOL, m_strVol);
	DDX_Radio(pDX, IDC_RADIO1, m_iSeleUI);
	DDX_CBIndex(pDX, IDC_COMBO_WY_TYPE, m_iTypeWY);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWYDlg, CDialog)
	//{{AFX_MSG_MAP(CWYDlg)
	ON_BN_CLICKED(IDC_BUTTON_GET, OnButtonGet)
	ON_BN_CLICKED(IDC_BUTTON_SET, OnButtonSet)
	ON_BN_CLICKED(IDC_BUTTON_RESET, OnButtonReset)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, OnDeltaposSpin1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, OnDeltaposSpin2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWYDlg message handlers

void CWYDlg::OnButtonGet() 
{
	// TODO: Add your control notification handler code here
	if(UpdateData(TRUE)==FALSE)
		return;
	CString strVol,strCurr;
	float fVol,fCurr;
	BOOL bR;
	CCmdTarget::BeginWaitCursor();
	bR=WY_GetPower(m_strCom,m_iTypeWY,m_strAddr,fVol,fCurr,strVol,strCurr);
	CCmdTarget::EndWaitCursor();
	if(!bR)
	{
		//MessageBox("通讯失败!",NULL,MB_ICONSTOP);
		return;
	}
	m_strVol  = strVol;
	m_strCurr = strCurr;

	UpdateData(FALSE);	
}

void CWYDlg::OnButtonSet() 
{
	// TODO: Add your control notification handler code here
	if(UpdateData(TRUE)==FALSE)
		return;
	if(CheckLimit()==FALSE)
	{
		if(g_bEnglish)
			MessageBox("Set Range Error!",NULL,MB_ICONSTOP);
		else
			MessageBox("设定输入范围错误,请修改!",NULL,MB_ICONSTOP);
		return;
	}
	CDlgSetPower dlg;
	dlg.pDlg=this;
	dlg.DoModal();


	if(dlg.m_iR==1)
	{
		//MessageBox("通讯失败!",NULL,MB_ICONSTOP);
		return;
	}

	m_strVol  = dlg.m_strVol;
	m_strCurr = dlg.m_strCurr;

	UpdateData(FALSE);	
	
}

void CWYDlg::OnButtonReset() 
{
	// TODO: Add your control notification handler code here
	if(UpdateData(TRUE)==FALSE)
		return;
	BOOL bR;
	CCmdTarget::BeginWaitCursor();
	bR=WY_Reset(m_strCom,m_iTypeWY,m_strAddr);
	CCmdTarget::EndWaitCursor();	
	if(!bR)
	{
		//MessageBox("通讯失败!",NULL,MB_ICONSTOP);
		return;
	}	
}

void CWYDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	if(UpdateData(TRUE)==FALSE)
		return;

	CString strSection     =  "WY";
	CString strCom         =  "COM";
	CString strSetVol      =  "SetVol";
	CString strSetCurr     =  "SetCurr";
	CString strSeleUI      =  "SeleUI";
	CString strTypeWY      =  "TypeWY";

	CString strTemp;

	AfxGetApp()->WriteProfileString(strSection,strCom,m_strCom);
	strTemp.Format("%f",m_fSetVol);
	AfxGetApp()->WriteProfileString(strSection,strSetVol,strTemp);
	strTemp.Format("%f",m_fSetCurr);
	AfxGetApp()->WriteProfileString(strSection,strSetCurr,strTemp);
	AfxGetApp()->WriteProfileInt(strSection,strSeleUI,m_iSeleUI);
	AfxGetApp()->WriteProfileInt(strSection,strTypeWY,m_iTypeWY);
	
	CDialog::OnCancel();
}

void CWYDlg::OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(pNMUpDown->iDelta>0)
	{
		m_fSetVol=m_fSetVol-1;
		if(m_fSetVol<=m_fVolR1)
			m_fSetVol=m_fVolR1;
	}
	else
	{
		m_fSetVol=m_fSetVol+1;
		if(m_fSetVol>=m_fVolR2)
			m_fSetVol=m_fVolR2;
	}
	UpdateData(FALSE);
	*pResult = 0;
}

void CWYDlg::OnDeltaposSpin2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(pNMUpDown->iDelta>0)
	{
		m_fSetCurr=m_fSetCurr-0.1f;
		if(m_fSetCurr<=m_fCurrR1)
			m_fSetCurr=m_fCurrR1;
	}
	else
	{
		m_fSetCurr=m_fSetCurr+0.1f;
		if(m_fSetCurr>=m_fCurrR2)
			m_fSetCurr=m_fCurrR2;
	}
	UpdateData(FALSE);
	*pResult = 0;
}

BOOL CWYDlg::GetRangeFile()
{
	FILE *fp;
	CString sTitle;
	sTitle="range.dat";
	if((fp=fopen(m_strCurPath+sTitle,"rt"))==0)
	{
		if(g_bEnglish)
			MessageBox("Can not fild rang.dat file!",NULL,MB_ICONSTOP);
		else
			MessageBox("未找到相应rang.dat文件!",NULL,MB_ICONSTOP);
		return FALSE;
	}
	else
	{
		fscanf(fp,"U RANGE:%f %f\n",&m_fVolR1,&m_fVolR2);
		fscanf(fp,"I RANGE:%f %f\n",&m_fCurrR1,&m_fCurrR2);
		fclose(fp);
		return TRUE;
	}
}

BOOL CWYDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CString strTemp;
	strTemp.Format("U:%.3fV-%.0fV I:%.3fA-%.0fA",m_fVolR1,m_fVolR2,m_fCurrR1,m_fCurrR2);
	m_cRange.SetWindowText(strTemp);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CWYDlg::WY_GetPower(CString strCom,int iTypeWY,CString strAddr, float &fVol, float &fCurr, CString &strVol, CString &strCurr)
{
	if(g_bDemo)
	{
		fVol	= 3.0f;
		fCurr	= 1.0f;
		strVol	= "3.0";
		strCurr	= "1.0";
		Sleep(1000);
		return TRUE;
	}
	//通讯数据
	Serial Ser;
	HANDLE CommDev;
	BOOL bR;
	BYTE Out[1],In[40];      //
	bR=Ser.Open(CommDev,strCom,2400);
	if(!bR)
	{
		if(g_bEnglish)
			MessageBox("Can not open this serial port!",NULL,MB_ICONSTOP);
		else
			MessageBox("打开串口失败!",NULL,MB_ICONSTOP);
		return FALSE;
	}
	if(iTypeWY==1)
	{
		bR=Ser.SetAd(CommDev,strAddr);
		if(!bR)
		{
			if(g_bEnglish)
				MessageBox("SetAd Error or Com port!",NULL,MB_ICONSTOP);
			else
				MessageBox("地址握手不正确，请确认仪器地址码!",NULL,MB_ICONSTOP);
			Ser.Close(CommDev);
			return FALSE;
		}
	}
	Ser.SetReadTime(CommDev,5000,2,5000);
	Out[0]='G';
	Ser.Output(CommDev,Out,1);
	bR=Ser.Input(CommDev,In,1);
	if(!bR)
	{
		if(g_bEnglish)
			MessageBox("Can not read byte!",NULL,MB_ICONSTOP);
		else
			MessageBox("没有读取到反码!",NULL,MB_ICONSTOP);
		Ser.Close(CommDev);
		return FALSE;
	}
	if(In[0]!=BYTE(~Out[0]))
	{
		if(g_bEnglish)
			MessageBox("byte error!",NULL,MB_ICONSTOP);
		else
			MessageBox("读取到反码不正确!",NULL,MB_ICONSTOP);
		Ser.Close(CommDev);
		return FALSE;
	}
	bR=Ser.Input(CommDev,In,14);
	if(!bR)
	{
		if(g_bEnglish)
			MessageBox("Can not read all data!",NULL,MB_ICONSTOP);
		else
			MessageBox("没有读取到指定个数!",NULL,MB_ICONSTOP);
		Ser.Close(CommDev);
		return FALSE;
	}
	int i;
	BYTE bb[10];
	
	for(i=0;i<6;i++)
		bb[i]=In[i];
	fVol=Ser.ASCIItof(bb,6,strVol);

	for(i=0;i<6;i++)
		bb[i]=In[7+i];
	fCurr=Ser.ASCIItof(bb,6,strCurr);

	Ser.Close(CommDev);
	return TRUE;
}

BOOL CWYDlg::WY_Reset(CString strCom,int iTypeWY,CString strAddr)
{
	//复位,可以是在设定调节过程中使用复位
	if(g_bDemo)
	{
		Sleep(1000);
		return TRUE;
	}

	Serial Ser;
	HANDLE CommDev;
	BOOL bR;
	BYTE Out[1];      //
	bR=Ser.Open(CommDev,strCom,2400);
	if(!bR)
	{
		if(g_bEnglish)
			MessageBox("Can not open this serial port!",NULL,MB_ICONSTOP);
		else
			MessageBox("打开串口失败!",NULL,MB_ICONSTOP);
		return FALSE;
	}
	if(iTypeWY==1)
	{
		bR=Ser.SetAd(CommDev,strAddr);
		if(!bR)
		{
			if(g_bEnglish)
				MessageBox("SetAd Error or Com port!",NULL,MB_ICONSTOP);
			else
				MessageBox("地址握手不正确，请确认仪器地址码!",NULL,MB_ICONSTOP);
			Ser.Close(CommDev);
			return FALSE;
		}
	}
	Out[0]='R';
	Ser.Output(CommDev,Out,1);
	Ser.Close(CommDev);
	Sleep(1000);
	return TRUE;
}

int CWYDlg::WY_SetPower(CString strCom,int iTypeWY,CString strAddr, int iSeleUI, float fSetVol, float fSetCurr, float &fVol, float &fCurr, CString &strVol, CString &strCurr)
{
	if(g_bDemo)
	{
		fVol	= 3.0f;
		fCurr	= 1.0f;
		strVol	= "3.0";
		strCurr	= "1.0";
		Sleep(3000);
		return 0;
	}

	//设定稳压稳流数据
	//retrun : 0:OK 1:Fail 2:Reset
	Serial Ser;
	HANDLE CommDev;
	BOOL bR;
	BYTE Out[100],In[40];      //
	bR=Ser.Open(CommDev,strCom,2400);
	if(!bR)
	{
		if(g_bEnglish)
			MessageBox("Can not open this serial port!",NULL,MB_ICONSTOP);
		else
			MessageBox("打开串口失败!",NULL,MB_ICONSTOP);
		return 1;
	}
	if(iTypeWY==1)
	{
		bR=Ser.SetAd(CommDev,strAddr);
		if(!bR)
		{
			if(g_bEnglish)
				MessageBox("SetAd Error or Com port!",NULL,MB_ICONSTOP);
			else
				MessageBox("地址握手不正确，请确认仪器地址码!",NULL,MB_ICONSTOP);
			Ser.Close(CommDev);
			return 1;
		}
	}
	Ser.SetReadTime(CommDev,5000,2,5000);
	if(iSeleUI==0)
		Out[0]='U';
	else
		Out[0]='I';
	Ser.Output(CommDev,Out,1);
	bR=Ser.Input(CommDev,In,1);
	if(!bR)
	{
		if(g_bEnglish)
			MessageBox("Can not read byte!",NULL,MB_ICONSTOP);
		else
			MessageBox("没有读取到反码!",NULL,MB_ICONSTOP);
		Ser.Close(CommDev);
		return 1;
	}
	if(In[0]!=BYTE(~Out[0]))
	{
		if(g_bEnglish)
			MessageBox("byte error!",NULL,MB_ICONSTOP);
		else
			MessageBox("读取到反码不正确!",NULL,MB_ICONSTOP);
		Ser.Close(CommDev);
		return 1;
	}
	int i,N,iTempN;
	BYTE bb[100];
	CString strTemp;

	Out[0]=':';
	N=1;

	strTemp.Format("%.4f",fSetVol);
	Ser.StrToByte(strTemp,bb,iTempN);
	if(iTempN>=6)
		iTempN=6;
	for(i=0;i<iTempN;i++)
		Out[N+i]=bb[i];
	N=N+iTempN;

	Out[N]=':';
	N++;

	strTemp.Format("%.4f",fSetCurr);
	Ser.StrToByte(strTemp,bb,iTempN);
	if(iTempN>=6)
		iTempN=6;
	for(i=0;i<iTempN;i++)
		Out[N+i]=bb[i];
	N=N+iTempN;

	Out[N]='/';
	N++;

	Ser.Output(CommDev,Out,N);

	Ser.SetReadTime(CommDev,50,2,50);
	while(!m_bCancel)
	{
		bR=Ser.Input(CommDev,In,14);
		if(!bR&&In[0]==0x46)
		{
			Ser.Close(CommDev);
			if(g_bEnglish)
				MessageBox("Set Error,please set again!",NULL,MB_ICONSTOP);
			else
				MessageBox("设定错误,请重新设定!",NULL,MB_ICONSTOP);
			return 1;
		}
		if(bR)
		{
			for(i=0;i<6;i++)
				bb[i]=In[i];
			fVol=Ser.ASCIItof(bb,6,strVol);

			for(i=0;i<6;i++)
				bb[i]=In[7+i];
			fCurr=Ser.ASCIItof(bb,6,strCurr);

			Ser.Close(CommDev);
			return 0;
		}
	}
	Ser.Close(CommDev);
	return 2;

}

BOOL CWYDlg::CheckLimit()
{
	BOOL bR=TRUE;
	if(UpdateData(TRUE)==FALSE)
		return FALSE;
	if(m_fSetVol<m_fVolR1)
	{
		m_fSetVol=m_fVolR1;
		bR=FALSE;
	}
	if(m_fSetVol>m_fVolR2)
	{
		m_fSetVol=m_fVolR2;
		bR=FALSE;
	}
	if(m_fSetCurr<m_fCurrR1)
	{
		m_fSetCurr=m_fCurrR1;
		bR=FALSE;
	}
	if(m_fSetCurr>m_fCurrR2)
	{
		m_fSetCurr=m_fCurrR2;
		bR=FALSE;
	}
	UpdateData(FALSE);
	return bR;
}

void CWYDlg::OnOK() 
{
	// TODO: Add extra validation here
	OnButtonSet();
//	CDialog::OnOK();
}
