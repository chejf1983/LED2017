// DlgExportLamp.cpp : implementation file
//

#include "stdafx.h"
#include "MySpec.h"
#include "DlgExportLamp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgExportLamp dialog


CDlgExportLamp::CDlgExportLamp(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgExportLamp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgExportLamp)
	m_strCurr = _T("");
	m_fPH = 0.0f;
	m_strModel = _T("");
	m_strSN = _T("");
	m_strUnit = _T("");
	m_strVol = _T("");
	m_iInterval = -1;
	//}}AFX_DATA_INIT
	CString strSection1		= "CDlgExportLamp";

	CString strm_strCurr    = "m_strCurr";
	CString strm_fPH		= "m_fPH";
	CString strm_strModel   = "m_strModel";
	CString strm_strSN		= "m_strSN";
	CString strm_strUnit    = "m_strUnit";
	CString strm_strVol     = "m_strVol";
	CString strm_iInterval  = "m_iInterval";
	
	m_strCurr		= AfxGetApp()->GetProfileString(strSection1,strm_strCurr,"");
	CString strTemp;
	strTemp			= AfxGetApp()->GetProfileString(strSection1,strm_fPH,"1000");
	m_fPH			= (float)(atof(strTemp));
	m_strModel		= AfxGetApp()->GetProfileString(strSection1,strm_strModel,"D215S");
	m_strSN			= AfxGetApp()->GetProfileString(strSection1,strm_strSN,"G119786CN1321121");
	m_strUnit		= AfxGetApp()->GetProfileString(strSection1,strm_strUnit,"W/nm");
	m_strVol		= AfxGetApp()->GetProfileString(strSection1,strm_strVol,"12.2345");
	m_iInterval		= AfxGetApp()->GetProfileInt(strSection1,strm_iInterval,2);
}


void CDlgExportLamp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgExportLamp)
	DDX_Text(pDX, IDC_EDIT_CURR, m_strCurr);
	DDX_Text(pDX, IDC_EDIT_MOD_PH, m_fPH);
	DDX_Text(pDX, IDC_EDIT_MODEL, m_strModel);
	DDX_Text(pDX, IDC_EDIT_SN, m_strSN);
	DDX_Text(pDX, IDC_EDIT_UNIT, m_strUnit);
	DDX_Text(pDX, IDC_EDIT_VOL, m_strVol);
	DDX_CBIndex(pDX, IDC_COMBO_INTERVAL_WL, m_iInterval);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgExportLamp, CDialog)
	//{{AFX_MSG_MAP(CDlgExportLamp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgExportLamp message handlers

void CDlgExportLamp::OnOK() 
{
	// TODO: Add extra validation here
	BOOL bR;
	bR = UpdateData(TRUE);
	if(!bR)
	{
		return;
	}

	static char szFilter[]="lamp Files(*.lamp)|*.lamp||";
	CFileDialog dSave(FALSE,".lamp", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);
	if(dSave.DoModal() == IDCANCEL)
	{
		return;	
	}

	
	FILE *fp;
	if((fp = fopen(dSave.GetPathName(),"wt")) == 0)
	{
		return;
	}
	else
	{
		fprintf(fp,"Model:%s SN:%s\n",m_strModel,m_strSN);
		fprintf(fp,"Voltage:%sV Current:%sA\n",m_strVol, m_strCurr);
		float fStaDis = 0.5f;
		fprintf(fp,"Distance:%.2fm  Uint:%s\n", fStaDis, m_strUnit);
		
		float fInterval = 0.1f;
		int NN = 1;
		if(m_iInterval == 0)
		{
			fInterval = 0.1f;
			NN =1;
		}
		else if(m_iInterval == 1)
		{
			fInterval = 1.0f;
			NN = 10;
		}
		else
		{
			fInterval = 5.0f;
			NN = 50;
		}
		float fPhK = m_fPH / m_spData.m_fPH;
		if(m_strUnit.GetAt(0) != 'm')
		{
			fPhK = fPhK / 1000;
		}
		int iNum = (int)((m_spData.m_fSpect2 - m_spData.m_fSpect1) / fInterval + 1 + 0.5f);
		for(int i = 0; i < iNum; i++)
		{
			fprintf(fp,"%.1f %.3e\n",m_spData.m_fSpect1 + fInterval * i, m_spData.m_fRelSpect[i * NN] * fPhK * m_spData.m_fPlambda);
		}
		fprintf(fp,"-1 -1");
		fclose(fp);
		
		return;
	}
	
//	CDialog::OnOK();
}

void CDlgExportLamp::OnCancel() 
{
	// TODO: Add extra cleanup here
	UpdateData(TRUE);
	CString strSection1		= "CDlgExportLamp";
	
	CString strm_strCurr    = "m_strCurr";
	CString strm_fPH		= "m_fPH";
	CString strm_strModel   = "m_strModel";
	CString strm_strSN		= "m_strSN";
	CString strm_strUnit    = "m_strUnit";
	CString strm_strVol     = "m_strVol";
	CString strm_iInterval  = "m_iInterval";
	
	AfxGetApp()->WriteProfileString(strSection1,strm_strCurr,m_strCurr);
	CString strTemp;
	strTemp.Format("%f",m_fPH);
	AfxGetApp()->GetProfileString(strSection1,strm_fPH,strTemp);
	AfxGetApp()->GetProfileString(strSection1,strm_strModel,m_strModel);
	AfxGetApp()->GetProfileString(strSection1,strm_strSN,m_strSN);
	AfxGetApp()->GetProfileString(strSection1,strm_strUnit,m_strUnit);
	AfxGetApp()->GetProfileString(strSection1,strm_strVol,m_strVol);
	AfxGetApp()->GetProfileInt(strSection1,strm_iInterval,m_iInterval);
	
	CDialog::OnCancel();
}

BOOL CDlgExportLamp::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
