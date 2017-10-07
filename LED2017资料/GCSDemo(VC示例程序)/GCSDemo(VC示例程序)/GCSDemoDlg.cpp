// GCSDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GCSDemo.h"
#include "GCSDemoDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGCSDemoDlg dialog
extern CString g_strCurPath;

CGCSDemoDlg::CGCSDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGCSDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGCSDemoDlg)
	m_fIntTime = 100.0f;
	m_iAveNum = 1;
	m_fCCT = 2856.0f;
	m_fFlux = 100.0f;
	m_iFilterBW = 5;
	m_bUseTrig = FALSE;
	m_iTrigMode = 0;
	m_iPerIntTime = 0;
	m_iMaxIntTime = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGCSDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGCSDemoDlg)
	DDX_Control(pDX, IDC_BUTTON3, m_cTestL);
	DDX_Control(pDX, IDC_BUTTON4, m_cStop);
	DDX_Control(pDX, IDC_EDIT1, m_cData);
	DDX_Text(pDX, IDC_EDIT2, m_fIntTime);
	DDX_Text(pDX, IDC_EDIT3, m_iAveNum);
	DDX_Text(pDX, IDC_EDIT4, m_fCCT);
	DDX_Text(pDX, IDC_EDIT5, m_fFlux);
	DDX_Text(pDX, IDC_EDIT6, m_iFilterBW);
	DDX_Control(pDX, IDC_NTGRAPHCTRL, m_cSpectrum);
	DDX_Check(pDX, IDC_CHECK1, m_bUseTrig);
	DDX_CBIndex(pDX, IDC_COMBO1, m_iTrigMode);
	DDX_Text(pDX, IDC_EDIT7, m_iPerIntTime);
	DDX_Text(pDX, IDC_EDIT8, m_iMaxIntTime);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGCSDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CGCSDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_INIT, OnButtonInit)
	ON_BN_CLICKED(IDC_BUTTON_INIT_DARK, OnButtonInitDark)
	ON_BN_CLICKED(IDC_BUTTON_INIT_TEST, OnButtonInitTest)
	ON_BN_CLICKED(IDC_BUTTON_CALC, OnButtonCalc)
	ON_BN_CLICKED(IDC_BUTTON_INIT2, OnButtonInit2)
	ON_BN_CLICKED(IDC_BUTTON_AUTO, OnButtonAuto)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGCSDemoDlg message handlers

BOOL CGCSDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_bGetData = FALSE;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGCSDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGCSDemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGCSDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CGCSDemoDlg::OnOK() 
{
	// TODO: Add extra validation here
	
//	CDialog::OnOK();
}

void CGCSDemoDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	JK_Emission_Close();

	CDialog::OnCancel();
}

void CGCSDemoDlg::OnButtonInit() 
{
	// TODO: Add your control notification handler code here
	BeginWaitCursor();
	if(!UpdateData(TRUE))
	{
		return;
	}
	
	int iR;
	iR = JK_Emission_Init();
	if(iR == SA_API_SUCCESS)
	{
		AfxMessageBox("初始化成功!");
	}
	else
	{
		AfxMessageBox("初始化失败!");
	}
	EndWaitCursor();
}

void CGCSDemoDlg::OnButtonInitDark() 
{
	// TODO: Add your control notification handler code here
	BeginWaitCursor();
	if(!UpdateData(TRUE))
	{
		return;
	}
	int iR;
	LONGLONG start,end;   
	LARGE_INTEGER largeint; 
	double TotTime, freq; 
	
	QueryPerformanceFrequency(&largeint); 
	freq = (double)largeint.QuadPart;   
	QueryPerformanceCounter(&largeint);   
	start = largeint.QuadPart; 

	iR = JK_Emission_DarkStorage(m_fIntTime,m_iAveNum,m_iFilterBW);

	QueryPerformanceCounter(&largeint);   
	end = largeint.QuadPart; 
	TotTime = (double)(end - start) / freq; 
	TotTime = TotTime * 1000;

	CString sStr = "";
	CString strTemp;
	strTemp.Format("测试时间:%.4fms",TotTime);
	sStr = sStr + strTemp;
	m_cData.SetWindowText(sStr);
		
	if(iR == SA_API_SUCCESS)
	{
		AfxMessageBox("校零成功!");
	}
	else
	{
		AfxMessageBox("校零失败!");
	}
	EndWaitCursor();
}

UINT CGCSDemoDlg::ThreadGetAsynData(LPVOID pPar)
{
	CGCSDemoDlg *pDlg = (CGCSDemoDlg *)pPar;
	int iR;

	COLOR_PARA dPara;
	LONGLONG start,end;   
	LARGE_INTEGER largeint; 
	double TotTime, freq; 

	//起始时间
	QueryPerformanceFrequency(&largeint); 
	freq = (double)largeint.QuadPart;   
	QueryPerformanceCounter(&largeint);   
	start = largeint.QuadPart;

	int pState;
	while(1)
	{
		//等待数据
		float fDx,fDy;
		fDx = 0;
		fDy = 0;
		iR = JK_GetSpectumAsyncSoftTrigger(pState, pDlg->m_fIntTime,pDlg->m_iAveNum,pDlg->m_iFilterBW,fDx,fDy,380.0f,780.0f, dPara);
		
		if (iR = SA_API_FAIL)
		{
			//测试失败
			break;
		}
		if (pState == 2)
		{
			//测试失败 或者 收到数据
			break;
		}
	}


	QueryPerformanceCounter(&largeint);   
	end = largeint.QuadPart; 
	TotTime = (double)(end - start) / freq; 
	TotTime = TotTime * 1000;
	
	CString sStr = "";
	CString strTemp;
	if(pState == 2)
	{
		pDlg->m_bGetData = TRUE;
		
		strTemp.Format("测试成功!\r\n IP = %.1f(%.1f%%)\r\n光通量=%.3flm  辐射通量 = %.1fmW\r\n",
			dPara.fIp, dPara.fIp/65535*100, dPara.fPh, dPara.fPhe*1000);
		sStr = sStr + strTemp;
		strTemp.Format("色坐标(x,y) = (%.4f, %.4f)\r\n",dPara.fx,dPara.fy);
		sStr = sStr + strTemp;
		strTemp.Format("峰值波长Lp = %.1fnm\r\n",dPara.fLp);
		sStr = sStr + strTemp;
		strTemp.Format("峰值波长Ld = %.1fnm\r\n",dPara.fLd);
		sStr = sStr + strTemp;
		strTemp.Format("测试时间:%.4fms",TotTime);
		sStr = sStr + strTemp;
		pDlg->m_cData.SetWindowText(sStr);
		
		pDlg->ReDraw(dPara);
	}
	else
	{
		strTemp = "测试失败!";
		pDlg->m_cData.SetWindowText(strTemp);
	}

	return 0;
}

void CGCSDemoDlg::OnButtonInitTest() 
{
	// TODO: Add your control notification handler code here
	BeginWaitCursor();
	if(!UpdateData(TRUE))
	{
		return;
	}
	if (m_bUseTrig)
	{
		//触发模式测试
		int iT1= GetCurrentTime();
		int iR;
		int spectrometerIndex = 0;
		COLOR_PARA dPara;
		
		LONGLONG start,end;   
		LARGE_INTEGER largeint; 
		double TotTime, freq; 
		
		QueryPerformanceFrequency(&largeint); 
		freq = (double)largeint.QuadPart;   
		QueryPerformanceCounter(&largeint);   
		start = largeint.QuadPart;

		TRIGGER_MODE TriggerMode;
		if (m_iTrigMode == 0)
		{
	 		TriggerMode = SOFTWARE_SYNCHRONOUS;	//软件同步模式
		}
		else if (m_iTrigMode == 1)
		{
			TriggerMode = SOFTWARE_ASYNCHRONOUS;//软件异步模式
		}
		else if (m_iTrigMode == 2)
		{
			TriggerMode = SOFTWARE_AUTO;		//自动采样模式
		}
		else if (m_iTrigMode == 3)
		{
			TriggerMode = EXINT_RISING_EDGE;	//上升沿触发
		}
		else if (m_iTrigMode == 4)
		{
			TriggerMode = EXINT_FALLING_EDGE;	//下降沿触发
		}
		else if (m_iTrigMode == 5)
		{
			TriggerMode = EXINT_HIGH_LEVEL;		//高电平触发模式
		}
		else
		{
			TriggerMode = EXINT_LOW_LEVEL;		//低电平触发模式
		}
		
		if (m_iTrigMode == 1)
		{
			iR = JK_ScanStartAsyncSoftTrigger();
			if(iR == SA_API_SUCCESS)
			{
				AfxBeginThread(ThreadGetAsynData, this);
			}
		}
		else
		{
			float fDx,fDy;
			fDx = 0;
			fDy = 0;
			iR = JK_Emission_GetData(TriggerMode, m_fIntTime,m_iAveNum,m_iFilterBW, fDx,fDy,380.0f,780.0f,dPara);
			QueryPerformanceCounter(&largeint);   
			end = largeint.QuadPart; 
			TotTime = (double)(end - start) / freq; 
			TotTime = TotTime * 1000;
			
			CString sStr = "";
			CString strTemp;
			if(iR == SA_API_SUCCESS)
			{
				//演示 偏置随意设置了0.01
				JK_Emission_CalcDxy(dPara,0.01f,0.01f);
				m_bGetData = TRUE;
				
				strTemp.Format("测试成功!\r\n IP = %.1f(%.1f%%)\r\n光通量=%.3flm  辐射通量 = %.1fmW\r\n",
					dPara.fIp, dPara.fIp/65535*100, dPara.fPh, dPara.fPhe*1000);
				sStr = sStr + strTemp;
				strTemp.Format("色坐标(x,y) = (%.4f, %.4f)\r\n",dPara.fx,dPara.fy);
				sStr = sStr + strTemp;
				strTemp.Format("峰值波长Lp = %.1fnm\r\n",dPara.fLp);
				sStr = sStr + strTemp;
				strTemp.Format("峰值波长Ld = %.1fnm\r\n",dPara.fLd);
				sStr = sStr + strTemp;
				strTemp.Format("测试时间:%.4fms",TotTime);
				sStr = sStr + strTemp;
				m_cData.SetWindowText(sStr);
				
				ReDraw(dPara);
			}
			else
			{
				strTemp = "测试失败!";
				m_cData.SetWindowText(strTemp);
			}
			EndWaitCursor();
		}		
	}
	else
	{
		//正常测试
		int iT1= GetCurrentTime();
		int iR;
		int spectrometerIndex = 0;
		COLOR_PARA dPara;
		
		LONGLONG start,end;   
		LARGE_INTEGER largeint; 
		double TotTime, freq; 
		
		QueryPerformanceFrequency(&largeint); 
		freq = (double)largeint.QuadPart;   
		QueryPerformanceCounter(&largeint);   
		start = largeint.QuadPart; 
		
		float fDx,fDy;
		fDx = 0;
		fDy = 0;
		iR = JK_Emission_GetData(SOFTWARE_SYNCHRONOUS,m_fIntTime,m_iAveNum,m_iFilterBW, fDx,fDy,380.0f,780.0f,dPara);
		
		QueryPerformanceCounter(&largeint);   
		end = largeint.QuadPart; 
		TotTime = (double)(end - start) / freq; 
		TotTime = TotTime * 1000;
		
		CString sStr = "";
		CString strTemp;
		if(iR == SA_API_SUCCESS)
		{
			strTemp.Format("LD = %.4f %.4f ",dPara.fLd, dPara.fPur);
//			AfxMessageBox(strTemp);
			dPara.fx = 0.7102f;
			dPara.fy = 0.2885f;
			//演示 偏置随意设置了0.01
			JK_Emission_CalcDxy(dPara,0.0001f,0.0001f);
			strTemp.Format("LD = %.4f %.4f ",dPara.fLd,dPara.fPur);
	//		AfxMessageBox(strTemp);

			m_bGetData = TRUE;
			
			strTemp.Format("测试成功!\r\n IP = %.1f(%.1f%%)\r\n光通量=%.3flm  辐射通量 = %.1fmW\r\n",
				dPara.fIp, dPara.fIp/65535*100, dPara.fPh, dPara.fPhe*1000);
			sStr = sStr + strTemp;
			strTemp.Format("色坐标(x,y) = (%.4f, %.4f)\r\n",dPara.fx,dPara.fy);
			sStr = sStr + strTemp;
			strTemp.Format("峰值波长Lp = %.1fnm\r\n",dPara.fLp);
			sStr = sStr + strTemp;
			strTemp.Format("主波长Ld = %.1fnm\r\n",dPara.fLd);
			sStr = sStr + strTemp;
			strTemp.Format("测试时间:%.4fms",TotTime);
			sStr = sStr + strTemp;

			sStr = sStr + "\r\n";
			sStr = sStr + "\r\n";
			sStr = sStr + "\r\n";
			sStr = sStr + "WL(nm)  Rel\r\n";
			int iN;
			iN = (int)((dPara.fSpect2 - dPara.fSpect1) / dPara.fInterval+1+0.5f);
			for (int i = 0; i < iN; i++)
			{
				strTemp.Format("%.1f  %6.5f\r\n", dPara.fSpect1 + dPara.fInterval*i, dPara.fPL[i]);
				sStr = sStr + strTemp;
			}
			m_cData.SetWindowText(sStr);
			
			ReDraw(dPara);
		}
		else
		{
			strTemp = "测试失败!";
			m_cData.SetWindowText(strTemp);
		}
		EndWaitCursor();
	}
	
}

void CGCSDemoDlg::OnButtonCalc() 
{
	// TODO: Add your control notification handler code here
	BeginWaitCursor();
	if(!UpdateData(TRUE))
	{
		return;
	}
	int iR;
	float fIp;
	int iCalType = 0; //注意：0相对定标 输入色温光通量即可
						//    1绝对定标，输入绝对光谱数据
	int iStaNum = 0;
	float fStaWL[10001];
	float fStaPL[10001];
	iR = JK_Emission_Calib(m_fIntTime,m_iAveNum,m_iFilterBW,iCalType, m_fCCT, m_fFlux,iStaNum,fStaWL,fStaPL,fIp);
	if(iR == SA_API_SUCCESS)
	{
		AfxMessageBox("光谱仪定标成功!");
	}
	else
	{
		AfxMessageBox("光谱仪定标失败!");
	}
	EndWaitCursor();
	
}

void CGCSDemoDlg::OnButtonInit2() 
{
	// TODO: Add your control notification handler code here
	JK_Emission_Close();

}

void CGCSDemoDlg::ReDraw(COLOR_PARA &dPara)
{
	CString strTemp;
	float x,y;	
	int i;
//	float fMax;

	m_cSpectrum.ClearGraph();
//	m_cSpectrum.AddElement();
	
	m_cSpectrum.SetXLabel("波 长(nm)");
	m_cSpectrum.SetYLabel("相 对 光 谱");
	m_cSpectrum.SetCaption("相 对 光 谱 曲 线");

	m_cSpectrum.SetXGridNumber(5);
	m_cSpectrum.SetYGridNumber(6);

	m_cSpectrum.SetElement(0);
	m_cSpectrum.SetElementName("");
	m_cSpectrum.SetElementLineColor(RGB(0,0,255));
	m_cSpectrum.SetElementIdentify(TRUE);
	m_cSpectrum.SetElementPointColor(RGB(0,0,255));
	m_cSpectrum.SetElementPointSymbol(0);
	m_cSpectrum.SetElementWidth (2);
	m_cSpectrum.SetElementSolidPoint(TRUE);
	m_cSpectrum.SetElementLinetype(0);

	if (m_bGetData)
	{
		int iN;
		iN = (int)((dPara.fSpect2 - dPara.fSpect1) / dPara.fInterval + 1 + 0.5f);
		for (i=0;i<iN;i++)
		{
			x = dPara.fSpect1 + i * dPara.fInterval;
			y = dPara.fPL[i];
			m_cSpectrum.PlotXY(x,y ,0);
		}	
		
		float fWL1 = dPara.fSpect1;
		float fWL2 = dPara.fSpect2;
		
		m_cSpectrum.SetRange(fWL1,fWL2,0,1.2f);		
	}
	else
	{
		m_cSpectrum.SetRange(380.0f,780.0f,0,1.2f);
	}
}

void CGCSDemoDlg::OnButtonAuto() 
{
	// TODO: Add your control notification handler code here
	
}

void CGCSDemoDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	BeginWaitCursor();
	if(!UpdateData(TRUE))
	{
		return;
	}
	int iR;
	LONGLONG start,end;   
	LARGE_INTEGER largeint; 
	double TotTime, freq; 
	
	QueryPerformanceFrequency(&largeint); 
	freq = (double)largeint.QuadPart;   
	QueryPerformanceCounter(&largeint);   
	start = largeint.QuadPart; 
	
	ORI_PARA dPara;
	iR = JK_Emission_DarkStorage_3LED(0,m_fIntTime,m_iAveNum,m_iFilterBW,dPara);
	
	QueryPerformanceCounter(&largeint);   
	end = largeint.QuadPart; 
	TotTime = (double)(end - start) / freq; 
	TotTime = TotTime * 1000;
	
	CString sStr = "";
	CString strTemp;
	strTemp.Format("测试时间:%.4fms",TotTime);
	sStr = sStr + strTemp;
	//	m_cData.SetWindowText(sStr);
	
	sStr = sStr + "\r\n";
	sStr = sStr + "\r\n";
	sStr = sStr + "\r\n";
	for (int i = 0; i < dPara.iPixN; i++)
	{
		strTemp.Format("%04d  %6.1f %6.1f\r\n",i,dPara.fDecWL[i],dPara.fDecAD[i]);
		sStr = sStr + strTemp;
	}
	m_cData.SetWindowText(sStr);
	
	if(iR == SA_API_SUCCESS)
	{
		AfxMessageBox("校零成功!");
	}
	else
	{
		AfxMessageBox("校零失败!");
	}
	EndWaitCursor();
}

void CGCSDemoDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	BeginWaitCursor();
	if(!UpdateData(TRUE))
	{
		return;
	}
	int iT1= GetCurrentTime();
	int iR;
	int spectrometerIndex = 0;
	
	LONGLONG start,end;   
	LARGE_INTEGER largeint; 
	double TotTime, freq; 
	
	QueryPerformanceFrequency(&largeint); 
	freq = (double)largeint.QuadPart;   
	QueryPerformanceCounter(&largeint);   
	start = largeint.QuadPart; 
	
	COLOR_PARA dPara;
	ORI_PARA dOriPara;
	float fDx,fDy;
	fDx = 0.001f;
	fDy = 0.002f;
	iR = JK_Emission_GetData_3LED(SOFTWARE_SYNCHRONOUS,0, m_fIntTime,m_iAveNum,m_iFilterBW, fDx,fDy,380.0f,780.0f,dPara, dOriPara);
	
	QueryPerformanceCounter(&largeint);   
	end = largeint.QuadPart; 
	TotTime = (double)(end - start) / freq; 
	TotTime = TotTime * 1000;
	
	CString sStr = "";
	CString strTemp;
	if(iR == SA_API_SUCCESS)
	{		
		strTemp.Format("测试成功!\r\n IP = %.1f(%.1f%%)\r\n光通量=%.3flm  辐射通量 = %.1fmW\r\n",
			dPara.fIp, dPara.fIp/65535*100, dPara.fPh, dPara.fPhe*1000);
		sStr = sStr + strTemp;
		strTemp.Format("色温CCT = %.0fK\r\n",dPara.fCCT);
		sStr = sStr + strTemp;
		strTemp.Format("色坐标(x,y) = (%.4f, %.4f)\r\n",dPara.fx,dPara.fy);
		sStr = sStr + strTemp;
		strTemp.Format("峰值波长Lp = %.1fnm\r\n",dPara.fLp);
		sStr = sStr + strTemp;
		strTemp.Format("峰值波长Ld = %.1fnm\r\n",dPara.fLd);
		sStr = sStr + strTemp;
		strTemp.Format("测试时间:%.4fms",TotTime);
		sStr = sStr + strTemp;
		
		sStr = sStr + "\r\n";
		sStr = sStr + "\r\n";
		sStr = sStr + "\r\n";
		for (int i = 0; i < dOriPara.iPixN; i++)
		{
			strTemp.Format("%04d  %6.1f %6.1f %6.1f\r\n",i,dOriPara.fDecWL[i],dOriPara.fDecAD[i],dOriPara.fDecPL[i]);
			sStr = sStr + strTemp;
		}
		m_cData.SetWindowText(sStr);
		ReDraw(dPara);
	}
	else
	{
		strTemp = "测试失败!";
		m_cData.SetWindowText(strTemp);
	}
	EndWaitCursor();	
}

UINT ThreadTestStart(LPVOID pPar)
{
	CGCSDemoDlg *pDlg = (CGCSDemoDlg *)pPar;

	if (pDlg->m_iTrigMode == 1)
	{
		pDlg->m_iTrigMode = 0;
	}
	while(1)
	{
		if (pDlg->m_bUseTrig)
		{
			//触发模式测试
			int iT1= GetCurrentTime();
			int iR;
			int spectrometerIndex = 0;
			COLOR_PARA dPara;
			
			LONGLONG start,end;   
			LARGE_INTEGER largeint; 
			double TotTime, freq; 
			
			QueryPerformanceFrequency(&largeint); 
			freq = (double)largeint.QuadPart;   
			QueryPerformanceCounter(&largeint);   
			start = largeint.QuadPart;

			TRIGGER_MODE TriggerMode;
			if (pDlg->m_iTrigMode == 0)
			{
	 			TriggerMode = SOFTWARE_SYNCHRONOUS;	//软件同步模式
			}
			else if (pDlg->m_iTrigMode == 1)
			{
				TriggerMode = SOFTWARE_ASYNCHRONOUS;//软件异步模式
			}
			else if (pDlg->m_iTrigMode == 2)
			{
				TriggerMode = SOFTWARE_AUTO;		//自动采样模式
			}
			else if (pDlg->m_iTrigMode == 3)
			{
				TriggerMode = EXINT_RISING_EDGE;	//上升沿触发
			}
			else if (pDlg->m_iTrigMode == 4)
			{
				TriggerMode = EXINT_FALLING_EDGE;	//下降沿触发
			}
			else if (pDlg->m_iTrigMode == 5)
			{
				TriggerMode = EXINT_HIGH_LEVEL;		//高电平触发模式
			}
			else
			{
				TriggerMode = EXINT_LOW_LEVEL;		//低电平触发模式
			}
			
			if (pDlg->m_iTrigMode == 1)
			{
			
			}
			else
			{
				float fDx,fDy;
				fDx = 0;
				fDy = 0;
				iR = JK_Emission_GetData(TriggerMode, pDlg->m_fIntTime,pDlg->m_iAveNum,pDlg->m_iFilterBW, fDx,fDy,380.0f,780.0f,dPara);
				QueryPerformanceCounter(&largeint);   
				end = largeint.QuadPart; 
				TotTime = (double)(end - start) / freq; 
				TotTime = TotTime * 1000;
				
				CString sStr = "";
				CString strTemp;
				if(iR == SA_API_SUCCESS)
				{
					pDlg->m_bGetData = TRUE;
					
					strTemp.Format("测试成功!\r\n IP = %.1f(%.1f%%)\r\n光通量=%.3flm  辐射通量 = %.1fmW\r\n",
						dPara.fIp, dPara.fIp/65535*100, dPara.fPh, dPara.fPhe*1000);
					sStr = sStr + strTemp;
					strTemp.Format("色坐标(x,y) = (%.4f, %.4f)\r\n",dPara.fx,dPara.fy);
					sStr = sStr + strTemp;
					strTemp.Format("峰值波长Lp = %.1fnm\r\n",dPara.fLp);
					sStr = sStr + strTemp;
					strTemp.Format("峰值波长Ld = %.1fnm\r\n",dPara.fLd);
					sStr = sStr + strTemp;
					strTemp.Format("测试时间:%.4fms",TotTime);
					sStr = sStr + strTemp;
					pDlg->m_cData.SetWindowText(sStr);
					
					pDlg->ReDraw(dPara);
				}
				else
				{
					strTemp = "测试失败!";
					pDlg->m_cData.SetWindowText(strTemp);
				}
				
			}		
		}
		else
		{
			//正常测试
			int iT1= GetCurrentTime();
			int iR;
			int spectrometerIndex = 0;
			COLOR_PARA dPara;
			
			LONGLONG start,end;   
			LARGE_INTEGER largeint; 
			double TotTime, freq; 
			
			QueryPerformanceFrequency(&largeint); 
			freq = (double)largeint.QuadPart;   
			QueryPerformanceCounter(&largeint);   
			start = largeint.QuadPart; 
			
			float fDx,fDy;
			fDx = 0;
			fDy = 0;
			iR = JK_Emission_GetData(SOFTWARE_SYNCHRONOUS,pDlg->m_fIntTime,pDlg->m_iAveNum,pDlg->m_iFilterBW, fDx,fDy,380.0f,780.0f,dPara);
			
			QueryPerformanceCounter(&largeint);   
			end = largeint.QuadPart; 
			TotTime = (double)(end - start) / freq; 
			TotTime = TotTime * 1000;
			
			CString sStr = "";
			CString strTemp;
			if(iR == SA_API_SUCCESS)
			{
				pDlg->m_bGetData = TRUE;
				
				strTemp.Format("测试成功!\r\n IP = %.1f(%.1f%%)\r\n光通量=%.3flm  辐射通量 = %.1fmW\r\n",
					dPara.fIp, dPara.fIp/65535*100, dPara.fPh, dPara.fPhe*1000);
				sStr = sStr + strTemp;
				strTemp.Format("色坐标(x,y) = (%.4f, %.4f)\r\n",dPara.fx,dPara.fy);
				sStr = sStr + strTemp;
				strTemp.Format("峰值波长Lp = %.1fnm\r\n",dPara.fLp);
				sStr = sStr + strTemp;
				strTemp.Format("峰值波长Ld = %.1fnm\r\n",dPara.fLd);
				sStr = sStr + strTemp;
				strTemp.Format("测试时间:%.4fms",TotTime);
				sStr = sStr + strTemp;

				sStr = sStr + "\r\n";
				sStr = sStr + "\r\n";
				sStr = sStr + "\r\n";
				sStr = sStr + "WL(nm)  Rel\r\n";
				int iN;
				iN = (int)((dPara.fSpect2 - dPara.fSpect1) / dPara.fInterval+1+0.5f);
				for (int i = 0; i < iN; i++)
				{
					strTemp.Format("%.1f  %6.5f\r\n", dPara.fSpect1 + dPara.fInterval*i, dPara.fPL[i]);
					sStr = sStr + strTemp;
				}
				pDlg->m_cData.SetWindowText(sStr);
				
				pDlg->ReDraw(dPara);
			}
			else
			{
				strTemp = "测试失败!";
				pDlg->m_cData.SetWindowText(strTemp);
			}
		}

		Sleep(10);
		if (pDlg->m_bStop)
		{
			break;
		}
	}

	pDlg->m_cStop.EnableWindow(FALSE);
	pDlg->m_cTestL.EnableWindow(TRUE);
	return 0;
}

void CGCSDemoDlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
	if(UpdateData(TRUE)==FALSE)
	{
		return;
	}
	m_cStop.EnableWindow(TRUE);
	m_cTestL.EnableWindow(FALSE);
	//开副线程
	m_bStop = FALSE;
	AfxBeginThread(ThreadTestStart,this);	
}

void CGCSDemoDlg::OnButton4() 
{
	// TODO: Add your control notification handler code here
	m_bStop = TRUE;
}
