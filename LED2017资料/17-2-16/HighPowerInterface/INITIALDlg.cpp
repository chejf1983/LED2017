// INITIALDlg.cpp : implementation file
//

#include "stdafx.h"
#include "highpowerinterface.h"
#include "INITIALDlg.h"

#include "HolyChipOptics.h"
#include "Functions.h"
#include "RegisterDlg.h"
#include "SpectraArsenalEmissionAPI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CINITIALDlg dialog

CINITIALDlg::CINITIALDlg(CWnd* pParent /*=NULL*/)
	: CResizingDialog(CINITIALDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CINITIALDlg)
	m_spectrumstyle = 0;
	//}}AFX_DATA_INIT
}


void CINITIALDlg::DoDataExchange(CDataExchange* pDX)
{
	CResizingDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CINITIALDlg)
	DDX_Control(pDX, IDC_Cancel, m_cancel);
	DDX_Control(pDX, IDC_iniAll, m_iniAll);
	DDX_Control(pDX, IDC_LeftTime, m_leftTime);
	DDX_Control(pDX, IDC_ShowProgress, m_showprogress);
	DDX_Control(pDX, IDC_PROGRESS, m_progress);
	DDX_Radio(pDX, IDC_SelUSB2000, m_spectrumstyle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CINITIALDlg, CResizingDialog)
	//{{AFX_MSG_MAP(CINITIALDlg)
	ON_BN_CLICKED(IDC_iniAll, OniniAll)
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_SelUSB2000, OnSelUSB2000)
	ON_BN_CLICKED(IDC_SelPC2000, OnSelPC2000)
	ON_BN_CLICKED(IDC_Cancel, OnCancel)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CINITIALDlg message handlers

//extern float *DataArray[MAX_BUF];
extern int leftTimeAft;
CString mainpath;
CString CurrentFilePath;
CString CurrentFile;
CString PasswordFilePath;
CString MapBinFilePath;

CPrintDialog cp(FALSE, PD_ALLPAGES | PD_COLLATE | PD_NOPAGENUMS | PD_HIDEPRINTTOFILE);
HDC print_hDC;
CDC *print_pDC;

extern CArray<int, int>feedingClowBox;

bool ifPrintVersion = false;

BOOL CINITIALDlg::OnInitDialog() 
{
	CResizingDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	MoveWindow(250, 250, 500, 200);
	CRgn rgn;
	rgn.CreateRoundRectRgn(0, 0, 500, 200, 10, 10);
	SetWindowRgn(rgn, true);
	inisuccess = false;
	cancel = false;

	CString str;
	if(365 == leftTimeAft)
	{
		GetDlgItem(IDC_LeftTime)->ShowWindow(SW_HIDE);
	}
	else
	{	
		str.Format("����ʱ��ʣ��%d��", leftTimeAft);
		SetDlgItemText(IDC_LeftTime, str);
	}

	m_progress.SetRange(0, 100);
	m_progress.SetColor(RGB(64, 64, 255));
	m_progress.SetStep(1);
	m_progress.SetPos(1);
	m_progress.SetIndeterminate(false);

	SetDialogFace();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CINITIALDlg::OnSelUSB2000() 
{
	// TODO: Add your control notification handler code here
//	spectro = true;
}

void CINITIALDlg::OnSelPC2000() 
{
	// TODO: Add your control notification handler code here
//	spectro = false;
}

void CINITIALDlg::OniniAll() 
{
	// TODO: Add your control notification handler code here
	CStdioFile m_file;
	CString filePath;

	char fullpath[200];
	::GetModuleFileName(NULL, fullpath, 200);
	mainpath = fullpath;
	mainpath = mainpath.Left(mainpath.ReverseFind(TEXT('\\')));
//	mainpath = mainpath.Left(mainpath.ReverseFind(TEXT('\\')));
	CurrentFilePath = mainpath + "\\System\\Def.Sta";
    CurrentFile = "Def.Sta";
	MapBinFilePath = mainpath + "\\System\\Bin.binmap";
    PasswordFilePath = mainpath + "\\System\\UsersInfo.ps";

	m_showprogress.SetWindowText("��ʼ��:�������...");
	double hardware = 0;
	hardware = initializeHardware();
	m_progress.SetPos(10);
	if(hardware > 0)
	{
		CString str;
		str.Format("%f", hardware);

		if(hardware <= 10)
		{
			MessageBox("�����ѹУ�����!  " + str);
		}
		else if((hardware > 10) && (hardware < 15))
		{
			MessageBox("����100uAУ�����!  " + str);
		}
		else if((hardware > 20) && (hardware < 25))
		{
			MessageBox("����20mAУ�����!  " + str);
		}
		else if((hardware > 30) && (hardware < 35))
		{
			MessageBox("����200mAУ�����!  " + str);
		}
		else if((hardware > 40) && (hardware < 45))
		{
			MessageBox("����2000mAУ�����!  " + str);
		}
		else if((hardware > 50) && (hardware <1000))
		{
			MessageBox("��ѹ����У�����!  " + str);
		}
		else if(1000 == hardware)
		{
			MessageBox("���Ƴ���, Ȼ������У��!");
		}
	}
	else
	{
		m_showprogress.SetWindowText("��ʼ��:�����ļ�...");
		filePath = "System\\System.sys";
		if(m_file.Open((LPCTSTR)filePath, CFile::modeReadWrite))
		{
			ReadSysFile(&m_file);
			m_file.Close();
			m_progress.SetPos(20);
			
			if(1)
			{
				filePath = "System\\SpectrumSet.sys";
			}
			else
			{
				filePath = "System\\SpectrumSetPC2000.sys";
			}
			
			if(m_file.Open((LPCTSTR)filePath, CFile::modeReadWrite))
			{
				ReadSpectrumSetFile(&m_file);
				m_file.Close();
				m_progress.SetPos(30);
				
				filePath = "System\\Calibration.Spm";
				if(m_file.Open((LPCTSTR)filePath, CFile::modeReadWrite))
				{
					ReadReferFile(&m_file);
					m_file.Close();
					m_progress.SetPos(40);
					
					filePath = "System\\CalDark.Dat";
					if(m_file.Open((LPCTSTR)filePath, CFile::modeReadWrite))
					{
						ReadCalDarkFile(&m_file);
						m_file.Close();
						m_progress.SetPos(50);
					}
					else
					{
						MessageBox("�ļ�CalDark.Dat��ʧ��!");
					}
					
					filePath = "System\\Def.Sta";
					if(m_file.Open((LPCTSTR)filePath, CFile::modeReadWrite))
					{
						ReadStaFile(&m_file);
						m_file.Close();
						m_progress.SetPos(60);

						for(int i=0; i<3; i++)
						{
							InitXYLEVELItem(i);
							GetRange(i);
						}
					}
					else
					{
						MessageBox("��׼�ļ���ʧ��!");
					}
					
					///��ʼ����ӡ����
					if(ifPrintVersion)
					{
						filePath = "System\\Bin.binmap";
						if(m_file.Open((LPCTSTR)filePath, CFile::modeReadWrite))
						{
							ReadBinMapFile(&m_file);
							m_file.Close();
							m_progress.SetPos(65);
						}
						else
						{
							MessageBox("�Ϻзּ���Ӧ�ļ���ʧ��!");
						}
						
						for(int i=0; i<105; i++)
						{
							feedingClowBox.Add(80);
						}
						
						filePath = "System\\PrintSet.print";
						if(m_file.Open((LPCTSTR)filePath, CFile::modeReadWrite))
						{
							ReadPrintSetFile(&m_file);
							m_file.Close();
							m_progress.SetPos(70);
						}
						else
						{
							MessageBox("��ӡ�����ļ���ʧ��!");
						}
						
						m_showprogress.SetWindowText("��ʼ����ӡ��...");
						if(cp.GetDefaults())
						{
							print_hDC=cp.GetPrinterDC();	
							print_pDC=CDC::FromHandle(print_hDC);
							m_progress.SetPos(90);
						}	
					}

					BinCodeList();//////��ʼ����CIE��������

					m_showprogress.SetWindowText("��ʼ��:�����Ǽ��...");
					int iR;
					iR = JK_Emission_Init();
					if(iR != SA_API_SUCCESS)
					{
						AfxMessageBox("δ��⵽������!");
						OnClose();
						return;
					}

					InitBlackXY();
					resetparam();
					seperateBincode();
					inisuccess = true;
					m_progress.SetPos(100);			
				}
				else
				{
					MessageBox("�ļ�Calibration.Spm��ʧ��!");
				}
			}
			else
			{
				MessageBox("�ļ�SpectrumSet.sys��ʧ��!");
			}	
		}
		else
		{
			MessageBox("�ļ�System.sys��ʧ��!");
		}
	}
	
	OnClose();
}

void CINITIALDlg::OnCancel() 
{
	// TODO: Add your control notification handler code here
	cancel = true;
	OnClose();
}
void CINITIALDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, 0);

	CResizingDialog::OnLButtonDown(nFlags, point);
}


void CINITIALDlg::SetDialogFace()
{
	m_showprogress.SetBitmaps(IDB_InitText, IDB_InitText, IDB_InitText, IDB_InitText);
	m_showprogress.SizeToContent();
	m_showprogress.SetDrawText(true, false)
			.SetFont3D(true, 0, 0, false)
		    .SetFontSize(20, false)
			.SetForceColor(RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0), false);

	m_leftTime.SetBitmaps(IDB_LeftTime, IDB_LeftTime, IDB_LeftTime, IDB_LeftTime);
	m_leftTime.SizeToContent();
	m_leftTime.SetDrawText(true, false)
			.SetFont3D(true, 1, 1, false)
		    .SetFontSize(20, false)
			.SetForceColor(RGB(255, 0, 0), RGB(255, 0, 0), RGB(255, 0, 0), false);

	m_iniAll.SetBitmaps(IDB_InitBTNormal, IDB_InitBTDown, IDB_InitBTHigh, IDB_InitBTDown);
	m_iniAll.SizeToContent();

	m_cancel.SetBitmaps(IDB_InitCancelNormal, IDB_InitCancelDown,
		                IDB_InitCancelHigh, IDB_InitCancelDown);
	m_cancel.SizeToContent();
}

BOOL CINITIALDlg::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return CResizingDialog::DrawBK(pDC, IDB_InitialBK, 0);
//	return CResizingDialog::OnEraseBkgnd(pDC);
}

HBRUSH CINITIALDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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
