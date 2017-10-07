// SpectrumSetting.cpp : implementation file
//

#include "stdafx.h"
#include "highpowerinterface.h"
#include "SpectrumSetting.h"

#include "Functions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpectrumSetting dialog


CSpectrumSetting::CSpectrumSetting(CWnd* pParent /*=NULL*/)
	: CResizingDialog(CSpectrumSetting::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSpectrumSetting)
	//}}AFX_DATA_INIT
}


void CSpectrumSetting::DoDataExchange(CDataExchange* pDX)
{
	CResizingDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSpectrumSetting)
	DDX_Control(pDX, IDC_getSpectraPara, m_getSpecParam);
	DDX_Control(pDX, IDC_Exit, m_exit);
	DDX_Control(pDX, IDC_SpectrumSet, m_spectrumset);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSpectrumSetting, CResizingDialog)
	//{{AFX_MSG_MAP(CSpectrumSetting)
	ON_BN_CLICKED(IDC_Exit, OnExit)
	ON_BN_CLICKED(IDC_SpectrumSet, OnSpectrumSet)
	ON_BN_CLICKED(IDC_getSpectraPara, OngetSpectraPara)
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpectrumSetting message handlers
extern CalCoeff calcoeff;
extern int iniTimeRate;
//extern Wrapper wrapper;
extern bool Operator;
extern bool engineer;

extern int WaitInteDelay;
extern CString mainpath;

bool savespec = false;
BOOL CSpectrumSetting::OnInitDialog() 
{
	CResizingDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	MoveWindow(200, 150, 330, 415);
	CRgn rgn;
	rgn.CreateRoundRectRgn(0, 0, 330, 415, 15, 15);
	SetWindowRgn(rgn, true);

	CString str;
	str.Format("%d", calcoeff.pixels);
	SetDlgItemText(IDC_Pixels, str);

	str.Format("%f", calcoeff.intercept);
	SetDlgItemText(IDC_Intercept, str);

	str.Format("%f", calcoeff.firstCoeff);
	SetDlgItemText(IDC_firstCoeff, str);

	str.Format("%f", calcoeff.secondCoeff);
	SetDlgItemText(IDC_secondCoeff, str);

	str.Format("%f", calcoeff.thirdCoeff);
	SetDlgItemText(IDC_thirdCoeff, str);

	str.Format("%d", iniTimeRate);
	SetDlgItemText(IDC_iniTimeRate, str);

	str.Format("%d  ms", WaitInteDelay);
	SetDlgItemText(IDC_WaitInteDelay, str);

	if(engineer || Operator)
	{
		m_spectrumset.EnableWindow(true);
	}
	else
	{
		m_spectrumset.EnableWindow(false);
	}
	
	GetDlgItem(IDC_getSpectraPara)->EnableWindow(TRUE);
	
	SetDialogFace();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSpectrumSetting::OngetSpectraPara() 
{
	// TODO: Add your control notification handler code here
// 	if(0 == wrapper.openAllSpectrometers())
// 	{
// 		MessageBox("未找到光谱仪!");
// 	}
// 	else
// 	{
// 		double inter = 0, first = 0, second = 0, third = 0;
// 		inter = wrapper.getWavelengthIntercept(0);
// 		first = wrapper.getWavelengthFirst(0);
// 		second = wrapper.getWavelengthSecond(0);
// 		third = wrapper.getWavelengthThird(0);
// 		
// 		CString str;
// 		str.Format("%f", inter);
// 		SetDlgItemText(IDC_Intercept, str);
// 		
// 		str.Format("%f", first);
// 		SetDlgItemText(IDC_firstCoeff, str);
// 		
// 		str.Format("%f", second);
// 		SetDlgItemText(IDC_secondCoeff, str);
// 		
// 		str.Format("%f", third);
// 		SetDlgItemText(IDC_thirdCoeff, str);
// 	}
}

void CSpectrumSetting::OnSpectrumSet() 
{
	// TODO: Add your control notification handler code here
	CString str_parameter;
	int i=1;

	GetDlgItemText(IDC_Pixels, str_parameter);
	while(str_parameter != "")
	{
		switch(i)
		{
		    case 1:
				calcoeff.pixels = atoi(str_parameter);
				GetDlgItemText(IDC_Intercept, str_parameter);
				break;
    		case 2:
				calcoeff.intercept = atof(str_parameter);
				GetDlgItemText(IDC_firstCoeff, str_parameter);
				break;
    		case 3:
				calcoeff.firstCoeff = atof(str_parameter);
				GetDlgItemText(IDC_secondCoeff, str_parameter);
				break;
	    	case 4:
				calcoeff.secondCoeff = atof(str_parameter);
				GetDlgItemText(IDC_thirdCoeff, str_parameter);
				break;
	    	case 5:	
				calcoeff.thirdCoeff = atof(str_parameter);
				GetDlgItemText(IDC_iniTimeRate, str_parameter);
				break;
			case 6:
				iniTimeRate = atoi(str_parameter);
				GetDlgItemText(IDC_WaitInteDelay, str_parameter);
				break;
			case 7:
				WaitInteDelay = atoi(str_parameter);
				str_parameter = "";
				break;
			default:
				str_parameter = "";
				break;
		}
		i++;
	}
	
	if(8 == i)
	{
		CStdioFile m_file;
		CString filePath;
		CString str_write;

		if(1)
		{
			filePath = mainpath + "\\System\\SpectrumSet.sys";
		}
		else
		{
			filePath = mainpath + "\\System\\SpectrumSetPC2000.sys";
		}
	
		CFileException e;
		if(!m_file.Open((LPCTSTR)filePath, CFile::modeReadWrite, &e))
		{
			CString sss;
			sss.Format("%d", e.m_cause);
			MessageBox(sss);
			MessageBox("文件保存失败!");
		}
		else
		{
			WriteSpectrumSetFile(&m_file);
			m_file.Close();
			savespec = true;
			OnClose();
		}
	}
	else
	{
		MessageBox("参数填写不完整");
	}
}

void CSpectrumSetting::OnExit() 
{
	// TODO: Add your control notification handler code here
	OnClose();
}

void CSpectrumSetting::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, 0);
	CResizingDialog::OnLButtonDown(nFlags, point);
}


void CSpectrumSetting::SetDialogFace()
{
	m_getSpecParam.SetBitmaps(IDB_Button_GetSpecParamNormal, IDB_Button_GetSpecParamfigDown,
		              IDB_Button_GetSpecParamHigh, IDB_Button_GetSpecParamDisable);
	m_getSpecParam.SizeToContent();

	m_spectrumset.SetBitmaps(IDB_Button_SaveNormal2, IDB_Button_SaveDown2,
		              IDB_Button_SaveHigh2, IDB_Button_SaveDisable2);
	m_spectrumset.SizeToContent();

	m_exit.SetBitmaps(IDB_Button_CancelNormal4, IDB_Button_CancelDown4,
		                 IDB_Button_CancelHigh4, IDB_Button_CancelDisable4);
	m_exit.SizeToContent();
}

HBRUSH CSpectrumSetting::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CResizingDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if(nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		hbr=(HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

BOOL CSpectrumSetting::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return CResizingDialog::DrawBK(pDC, IDB_SetSpectrumBK, 0);	
//	return CResizingDialog::OnEraseBkgnd(pDC);
}


