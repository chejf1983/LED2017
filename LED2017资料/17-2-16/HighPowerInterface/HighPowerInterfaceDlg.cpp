// HighPowerInterfaceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HighPowerInterface.h"
#include "HighPowerInterfaceDlg.h"

#include "ChangePassword.h"
#include "Login.h"
#include "EngineerLogin.h"
#include "LevelDlg.h"

#include "RegistHandle.h"

#include "resFile\Barcode\Barcode.h"

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
// CHighPowerInterfaceDlg dialog
CHighPowerInterfaceDlg::CHighPowerInterfaceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHighPowerInterfaceDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHighPowerInterfaceDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHighPowerInterfaceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHighPowerInterfaceDlg)
//	DDX_Control(pDX, IDC_MSCOMM1, m_ctrlComm);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHighPowerInterfaceDlg, CDialog)
	//{{AFX_MSG_MAP(CHighPowerInterfaceDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_COMMAND(ID_ClearUp, OnClearUp)
	ON_COMMAND(ID_OpenFile, OnOpenFile)
	ON_COMMAND(ID_SaveFile, OnSaveFile)
	ON_COMMAND(ID_SaveAs, OnSaveAs)
	ON_COMMAND(ID_Shoot, OnShoot)
	ON_COMMAND(ID_Spectrum, OnSpectrum)
	ON_COMMAND(ID_ColorTemperature, OnColorTemperature)
	ON_COMMAND(ID_CheckLog, OnCheckLog)
	ON_COMMAND(ID_RegistInformation, OnRegistInformation)
	ON_COMMAND(ID_Manual, OnManual)
	ON_COMMAND(ID_About, OnAbout)
	ON_COMMAND(ID_Connect, OnConnect)
	ON_COMMAND(ID_Tool_OpenFile, OnToolOpenFile)
	ON_COMMAND(ID_Tool_SaveFile, OnToolSaveFile)
	ON_COMMAND(ID_Tool_SaveAs, OnToolSaveAs)
	ON_COMMAND(ID_Exit, OnExit)
	ON_COMMAND(ID_SetParameter, OnSetParameter)
	ON_COMMAND(ID_SystemSetting, OnSystemSetting)
	ON_COMMAND(ID_NewFile, OnNewFile)
	ON_COMMAND(ID_AddUsers, OnAddUsers)
	ON_COMMAND(ID_DeleteUsers, OnDeleteUsers)
	ON_COMMAND(ID_SetSpectrum, OnSetSpectrum)
	ON_COMMAND(ID_SaveTestedData, OnSaveTestedData)
	ON_COMMAND(ID_SettingParam, OnSettingParam)
	ON_COMMAND(ID_SetSpm, OnSetSpm)
	ON_COMMAND(ID_CheckShowSetting, OnCheckShowSetting)
	ON_COMMAND(ID_RADIOOneLine, OnRADIOOneLine)
	ON_COMMAND(ID_RADIOList, OnRADIOList)
	ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnToolTipNotify)
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	ON_COMMAND(ID_Resistance, OnResistance)
	ON_COMMAND(ID_Regist, OnRegist)
	ON_WM_MOUSEWHEEL()
	ON_COMMAND(ID_ExportBinCode, OnExportBinCode)
	ON_COMMAND(ID_ExportNewCIE, OnExportNewCIE)
	ON_COMMAND(ID_showLevelSet, OnshowLevelSet)
	ON_COMMAND(ID_SetPrint, OnSetPrint)
	ON_COMMAND(ID_ClearBinBox, OnClearBinBox)
	ON_COMMAND(ID_TestSingle, OnTestSingle)
	ON_COMMAND(ID_TestContinuous, OnTestContinuous)
	ON_COMMAND(ID_StopTest, OnStopTest)
	ON_COMMAND(ID_RestartTest, OnRestartTest)
	ON_COMMAND(ID_Guest, OnGuest)
	ON_COMMAND(ID_Engineer, OnEngineer)
	ON_COMMAND(ID_TestAuto, OnTestAuto)
	ON_COMMAND(ID_Operator, OnOperator)
//	ON_MESSAGE(OOI_DATAREADY,OnDataReady)
	ON_COMMAND(ID_StartClearBox, OnStartClearBox)
	ON_COMMAND(ID_StopClearBox, OnStopClearBox)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHighPowerInterfaceDlg message handlers
int screen_width=0, screen_height=0;
float change_width=1, change_height=1;
int after_width=0, after_height=0;
int after_top=0, after_left=0;

extern HWND hWnd;
extern HINSTANCE hInstance;

extern int intChip;
extern bool m_regedit;
extern XYLEVEL xylevel[3];

extern int binnum[MAXBIN];
extern int binBox[MAXBIN][2];
extern int MaxLedNum;

extern LEDNumStatistic ledStatistic;

extern CString CurrentFilePath;
extern CString CurrentFile;

threadInfo testInfo;
CWinThread* pThread;
bool continuetest = false;
bool spectrumcheck = true;
bool CIEDiagram = true;
bool showone = false;
bool showsetting = false;
bool engineer = false;
bool Operator = false;

int sequencenum = 0;   //显示测试的灯的序号
HACCEL hAcc;

bool highsignal = true;
/////用来计算测试速度的参数
int lastnum = 0;   
extern int leftTimeAft;

extern int intMixLight;
extern bool MixLedLight[3];

bool rectUpdate = true;  ///是否更新了分级

CArray<BYTE, BYTE> printdata;

extern int intBoxcar;
extern int intSampleAverage;

extern HANDLE hCom; //准备打开的串口句柄
extern unsigned char read_data[1024];
extern CArray<int, int> OldBoxStatusArray;
extern CArray<int, int> NewBoxStatusArray;
extern CArray<int, int> BoxStatusArray;
bool openCom = false;
bool testbusy = false;

extern CDC *print_pDC;

extern CArray<LedStatus, LedStatus> waitingCheckLed;
extern bool iftestpass;
extern CString MapBinFilePath;
extern CArray<int, int>feedingClowBox;
int handleOK1 = 81;
int handleOK2 = 81;

int realboxnum = 0;  ////当前抽出料盒内灯的实际数量
bool ifStartClearBox = false;

extern bool ifPrintVersion;

BOOL CHighPowerInterfaceDlg::OnInitDialog()
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
	screen_width = GetSystemMetrics(SM_CXSCREEN);
	screen_height = GetSystemMetrics(SM_CYSCREEN);
	change_width = (float)screen_width/1280;
	change_height = (float)screen_height/768;

	hInstance = AfxGetInstanceHandle();
	hWnd = m_hWnd;
	leftTimeAft = 365;

	//查看注册表
	int figureReg = 0;
	figureReg = IsRegisted();
// 	if(figureReg != 0)//如果未注册
// 	{
// 		if(1 == figureReg)
// 		{
// 			MessageBox("软件已过期!");
// 		}
// 		m_register.DoModal();
// 	}

	if(m_regedit)
	{
		m_initial.DoModal();
		if(!m_initial.inisuccess)
		{
			if(!m_initial.cancel)
			{
				MessageBox("初始化失败!");
			}	
			EndDialog(IDCANCEL);
			return false;
		}
	}
	else
	{
		EndDialog(IDCANCEL);
		return false;
	}
	
	/////////////////加载菜单
	InitMenu();

	m_menu.CheckMenuItem(ID_Spectrum, MF_CHECKED);
	m_menu.CheckMenuItem(ID_ColorTemperature, MF_CHECKED);
	m_menu.CheckMenuItem(ID_RADIOList, MF_CHECKED);
	HideMenu();

	if(ifPrintVersion)
	{
		InitComm(false);
	}
	else
	{
		m_menu.EnableMenuItem(ID_SetPrint, MF_GRAYED);
		m_menu.EnableMenuItem(ID_StartClearBox, MF_GRAYED);
		m_menu.EnableMenuItem(ID_StopClearBox, MF_GRAYED);
		m_menu.EnableMenuItem(ID_ClearBinBox, MF_GRAYED);
	}
	///////////////////////////////////工具栏处理
	InitToolBar();

	/////////////////////////////////////窗口初始化
	InitWindows();

	Mappingtestlevel();//分级项目与测试项目映射

	InitMultipleTest();//多线程测试初始化

	SystemParametersInfo(SPI_SETSCREENSAVEACTIVE, false, 0, SPIF_SENDWININICHANGE);

	if(leftTimeAft != 365)
	{
		if(leftTimeAft < 5)
		{
			CString str;
			str.Format("您的软件使用时间仅剩%d天, 为不影响生产, 请尽快与厂家联系!", leftTimeAft);
			MessageBox(str);
		}
		SetTimer(3, 6000, NULL);
	}
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}


void CHighPowerInterfaceDlg::InitMenu()
{
	m_menu.LoadMenu(IDR_MENU1);

	m_menu.SubClass(this->GetSafeHwnd());//子类化
	m_menu.SetLogoText("分光分色软件", RGB(0, 0, 255));

//	CCoolMenu::SetLogoImage(IDB_MainBK2,0);
//	CCoolMenu::SetBackGroundBmp(IDB_MainBK2);
	
//  CCoolMenuTheme::SetTheme(MENU_STYLE_XP);
    m_menu.SetStyle(CCoolMenu::GetStyle() & ~CMS_ICONBAR);
	m_menu.SetMenuColor(RGB(255,255,255));//菜单背景色
	m_menu.SetIconBarColor(::GetSysColor(COLOR_3DFACE));
	
	m_menu.SetLightBarColor(RGB(61, 128, 152));//高亮栏的边框的颜色
	
	m_menu.SetLightBarStartColor(RGB(255, 255, 255));
	m_menu.SetLightBarEndColor(RGB(77,109, 120));
	
	m_menu.SetTextColor(RGB(0, 0, 0));
	m_menu.SetHighLightColor(RGB(20, 20, 50));
	
	CMenuWndHook::m_crFrame[0] = RGB(120, 120, 158);
	CMenuWndHook::m_crFrame[1] = RGB(48, 50, 48);
	CMenuWndHook::m_crFrame[2] = RGB(255, 255, 255);
	CMenuWndHook::m_crFrame[3] = RGB(168, 168, 210);
	
	SetMenu(&m_menu);
//	hAcc = ::LoadAccelerators(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR));	
	m_menu.EnableMenuItem(ID_StopTest, MF_GRAYED);
	m_menu.EnableMenuItem(ID_RestartTest, MF_GRAYED);
	m_menu.EnableMenuItem(ID_StopClearBox, MF_GRAYED);
	m_menu.EnableMenuItem(ID_ClearUp, MF_GRAYED);
}


bool CHighPowerInterfaceDlg::InitToolBar()
{
	if(!m_toolbar.CreateEx(this, TBSTYLE_FLAT,
		                WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS,
                        CRect(0,0,0,0)) || !m_toolbar.LoadToolBar(IDR_TOOLBAR1))
	{
		TRACE0("Failed to create toolbar\n");
		return false;
	}
	//工具栏按钮设置
	int i = 0;
	m_toolbar.GetToolBarCtrl().SetButtonSize(CSize(32,30));

	m_Imagelist.Create(32,28,ILC_COLOR24|ILC_MASK,0,1);
	for (i=0; i<5; i++)
	{
		m_Imagelist.Add(AfxGetApp()->LoadIcon(IDI_ICON1+i));
	}
	m_toolbar.GetToolBarCtrl().SetHotImageList(&m_Imagelist);	
	m_Imagelist.Detach();

	m_Imagelist.Create(28,25,ILC_COLOR24|ILC_MASK,0,1);
	for (i=0; i<5; i++)
	{
		m_Imagelist.Add(AfxGetApp()->LoadIcon(IDI_ICON1+i));
	}
	m_toolbar.GetToolBarCtrl().SetImageList(&m_Imagelist);	
	m_Imagelist.Detach();

	m_Imagelist.Create(15,15,ILC_COLOR24|ILC_MASK,0,1);
	for (i=0; i<5; i++)
	{
		m_Imagelist.Add(AfxGetApp()->LoadIcon(IDI_ICON1+i));
	}
	m_toolbar.GetToolBarCtrl().SetDisabledImageList(&m_Imagelist);	
	
	m_toolbar.GetToolBarCtrl().SetBitmapSize(CSize(32,30)); 

	//给工具栏添加背景图片	
/*	m_rebar.Create(this);	
	m_rebar.AddBar(&m_toolbar);
	m_rebar.RedrawWindow();
	REBARBANDINFO info;
	info.cbSize=sizeof(info);
	info.fMask = RBBIM_BACKGROUND;*/
	m_toolbar.ModifyStyle(0,TBSTYLE_TRANSPARENT);
//	info.hbmBack = ::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_ToolBar));
//	m_rebar.GetReBarCtrl().SetBandInfo(0,&info);
    //////
	m_toolbar.ShowWindow(SW_SHOW);
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);

	btn = (CToolBarCtrl*)&m_toolbar.GetToolBarCtrl();
	return true;
}


bool CHighPowerInterfaceDlg::InitWindows()
{
	m_authorityview.Create(IDD_AuthorityView);
	m_authorityview.ShowWindow(SW_SHOW);
	if(1)
	{
		m_authorityview.GetDlgItem(IDC_Showtemperature)->ShowWindow(SW_SHOW);
		m_authorityview.OnShowtemperature();
		SetTimer(0, 60000, NULL);
	}
	
	m_controlsdlg.Create(IDD_Controls);
	m_controlsdlg.ShowWindow(SW_SHOW);

	m_showtestdlg.Create(IDD_ShowTest);
	m_showtestdlg.ShowWindow(SW_SHOW);

	m_statisticdlg.Create(IDD_Statistic);
	m_statisticdlg.ShowWindow(SW_SHOW);

	m_bindlg.Create(IDD_Bin);
	m_bindlg.ShowWindow(SW_SHOW);

	m_spectrum.Create(IDD_Spectrum);
	m_spectrum.ShowWindow(SW_SHOW);

	m_CIEdiagram.Create(IDD_CIEDiagram);
	m_CIEdiagram.ShowWindow(SW_SHOW);
	
	m_status.Create(IDD_Status);
	m_status.ShowWindow(SW_SHOW);
	m_status.SetDlgItemText(IDC_ShowCurrentFile, CurrentFile);

	m_showlevel.Create(IDD_showLevel);

	return true;
}


bool CHighPowerInterfaceDlg::InitMultipleTest()
{
	testInfo.m_showtest = &m_showtestdlg;
	testInfo.m_control = &m_controlsdlg;
	testInfo.m_spectrum = &m_spectrum;
	testInfo.m_CIEdiagram = &m_CIEdiagram;
	testInfo.m_statistic = &m_statisticdlg;
	testInfo.m_bin = &m_bindlg;
	testInfo.m_shoot = &m_shootdiagram;
	testInfo.m_showlevel = &m_showlevel;
	testInfo.m_authorityview = &m_authorityview;

	return true;
}

bool CHighPowerInterfaceDlg::InitComm(bool response)
{
	if(response)
	{
		if(m_ctrlComm.GetPortOpen())
		{
			m_ctrlComm.SetPortOpen(false);
		}
		
		m_ctrlComm.SetCommPort(3); //选择com3
		m_ctrlComm. SetInBufferSize(1024); //设置输入缓冲区的大小,
		m_ctrlComm. SetOutBufferSize(1024); //设置输出缓冲区的大小, 
		
		if(!m_ctrlComm.GetPortOpen())
		{
			m_ctrlComm.SetPortOpen(TRUE);//打开串口
		}
		else
		{
			AfxMessageBox("cannot open serial port");
			return false;
		}
		m_ctrlComm.SetSettings("115200,n,8,1"); //波特率115200，无校验，8个数据位，1个停止位
		m_ctrlComm.SetInputMode(1); // 以二进制方式检取数据
		m_ctrlComm.SetRThreshold(1); //参数1表示每当串口接收缓冲区中有多于或等于1个字符时将引发一个接收数据的OnComm事件
		m_ctrlComm.SetInputLen(0); //设置当前接收区数据长度为0
		m_ctrlComm.GetInput();//先预读缓冲区以清除残留数据
		m_ctrlComm.SetInBufferCount(0);
	}
	else
	{
		CString str_com = "COM3";
		hCom=CreateFile(str_com,GENERIC_READ|GENERIC_WRITE,
			0,NULL,OPEN_EXISTING,0,NULL);   //打开串口
		if(hCom==(HANDLE)-1)
		{
			openCom = false;
			MessageBox("打开COM失败!");
		}
		else
		{
			openCom = true;
			SetupComm(hCom,1024,1024); //输入缓冲区和输出缓冲区的大小都是1024
			COMMTIMEOUTS TimeOuts;
			//设定读超时
			TimeOuts.ReadIntervalTimeout=MAXDWORD;
			TimeOuts.ReadTotalTimeoutMultiplier=0;
			TimeOuts.ReadTotalTimeoutConstant=0;
			//在读一次输入缓冲区的内容后读操作就立即返回，
			//而不管是否读入了要求的字符。
			
			//设定写超时
			TimeOuts.WriteTotalTimeoutMultiplier=100;
			TimeOuts.WriteTotalTimeoutConstant=500;
			SetCommTimeouts(hCom,&TimeOuts); //设置超时
			DCB dcb;
			GetCommState(hCom,&dcb);
			dcb.BaudRate=115200;
			dcb.ByteSize=8; //每个字节有8位
			dcb.Parity=NOPARITY; //无奇偶校验位
			dcb.StopBits=ONESTOPBIT; //停止位
			SetCommState(hCom,&dcb);
			PurgeComm(hCom,PURGE_TXCLEAR|PURGE_RXCLEAR);
		}
	}

	return true;
}

void CHighPowerInterfaceDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CString str, str2, str_temp;
	int num = 0;
	int figureReg = 0;
	extern bool regWinOpen;
	extern CString str_showcode;

	CString str_send, str_read, str_figure;
	int maxtimes = 50;
	int times = 0, times2 = 0;
	int length = 0;
	int stalen = 0;
	int outboxnum = 0;
	bool ifprint = false;
	
	switch(nIDEvent)
	{
	case 0:	
		m_authorityview.OnShowtemperature();
		break;
	case 1:
		if((Inport(0x250) & 1) != 0)
		{
			highsignal = true;
		}
		break;

	case 2:
		if(ledStatistic.ledtotalnum >= lastnum)
		{
			num = (ledStatistic.ledtotalnum - lastnum) * 60 / 1000;
			lastnum = ledStatistic.ledtotalnum;
			str.Format("%d", num);
			m_controlsdlg.SetDlgItemText(IDC_TestSpeed, str);
		}
		break;
	case 3:
		if(!regWinOpen)
		{
			figureReg = 0;
			figureReg = IsRegisted();
			if(figureReg != 0)//如果未注册
			{
				OnStopTest();
				if(1 == figureReg)
				{
					MessageBox("软件已过期!");
				}
				m_register.DoModal();
			}
		}
		break;
	case 4:
		if(!testbusy)
		{
			str_read = "";
			times = 0;
			stalen = 0;
			length = 0;
			
			///发消息询问是否有串口消息
			str_send = "EF";
			sendString(str_send);
			
			///读取回传消息，若无，则不操作；
			while(times<maxtimes)
			{
				str_read += readdata();
				length = strlen(str_read);
				str_showcode = str_read;
				m_showlevel.m_tempcode.SetWindowText(str_showcode);
				
				if(0 == stalen)
				{
					///若有，则判断是料盒核对信号，还是抽出料盒信号
					if(length > 1)
					{
						str_figure = str_read.Left(4); 
						if(str_figure == "F123")
						{	
							stalen = 24;
							times = 0;
						}
						else if(str_figure == "FBCD")
						{
							stalen = 540;
							maxtimes *= 9;
							times = 0;
						}
						else
						{
							////数据异常
							times = 50;
						}
					}
					else
					{
						Sleep(1);
						times++;
					}
				}
				else if(length == stalen)
				{
					if(24 == stalen)
					{
						ifprint = false;
						checkBoxStatus();
						outboxnum = BoxStatusArray.GetSize();

						str.Format("%d", outboxnum);
						m_showlevel.m_outboxnum.SetWindowText(str);
						str = "";
						for(int i=0; i<outboxnum; i++)
						{
							str2.Format(",   %d, %d", BoxStatusArray[i], binBox[BoxStatusArray[i]][1]);
							str += str2;
							m_showlevel.m_outboxdetail.SetWindowText(str);
							m_showlevel.UpdataExchangeParam();
							
						//	str2.Format("%d", binBox[BoxStatusArray[i]][1]);
						//	MessageBox(str2);

					//		int temptest = 0;
							realboxnum = getRealNumInBox(BoxStatusArray[i]);

							if(realboxnum >= MaxLedNum)//binBox[BoxStatusArray[i]][1]
							{
								str_temp.Format("%d", realboxnum);
								m_showlevel.m_temptest.SetWindowText(str_temp);

								ifprint = true;
								P_DrawBarCode(print_pDC, BoxStatusArray[i]);
								binBox[BoxStatusArray[i]][1] = 0;
								m_showlevel.updataBinMapList(BoxStatusArray[i]);
							}
						}

				//		checkprint(MaxLedNum);

						if(ifprint)
						{
							Outport(0x251, 0xFF);
							Sleep(1);
							Outport(0x251, handleOK1 ^ 0xFF);
						}
						
						times = maxtimes; 
					}
					else if(540 == stalen)
					{

						////此处回传信号给PLC, 通知核对成功，准备测试
						if(checkBoxnum())
						{
							m_showlevel.SetBinMapList();
							m_showlevel.UpdataExchangeParam();
							waitingCheckLed.RemoveAll();
							m_showlevel.m_codefromhardware.SetWindowText(str_showcode);
							
							//////初始化完成后，查看料盒状态
							//		checkprint(MaxLedNum);
							
							Outport(0x251, 0xFF);
							Sleep(1);
							Outport(0x251, handleOK2 ^ 0xFF);
						}
						times = maxtimes;
					}
				}
				else
				{
					Sleep(1);
					times++;
				}
			}
		}
		break;
	case 5:
		checkprint(1);
		break;
	default:
		break;

	}

	CDialog::OnTimer(nIDEvent);
}


bool CHighPowerInterfaceDlg::checkprint(int num)
{
	CString str_send = "EF", str_read = "";
	int times = 0;
	int length = 0;
	int outboxnum = 0;
	extern CString str_showcode;

	sendString(str_send);
	while(times < 50)
	{
		str_read += readdata();
		length = strlen(str_read);
		str_showcode = str_read;
		m_showlevel.m_tempcode.SetWindowText(str_showcode);
		
		if(24 == length)
		{
			checkBoxStatus();
			outboxnum = BoxStatusArray.GetSize();
			for(int i=0; i<outboxnum; i++)
			{
				realboxnum = getRealNumInBox(BoxStatusArray[i]);
				if(realboxnum >= num)
				{
					P_DrawBarCode(print_pDC, BoxStatusArray[i]);
					binBox[BoxStatusArray[i]][1] = 0;
					m_showlevel.updataBinMapList(BoxStatusArray[i]);
				}
			}

			times = 50;
/*			if(num == MaxLedNum)
			{
				checkprint(num);
			}*/
		}
		else
		{
			Sleep(1);
			times++;
		}
	}

	return false;
}

void CHighPowerInterfaceDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CHighPowerInterfaceDlg::OnPaint() 
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
HCURSOR CHighPowerInterfaceDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CHighPowerInterfaceDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	if(continuetest)
	{
		MessageBox("请先停止测试!");
	}
	else
	{
		if(AfxMessageBox("确定要关闭吗？", MB_OKCANCEL) == IDOK) 
		{
			KillTimer(0);
			initializeHardware();

			SystemParametersInfo(SPI_SETSCREENSAVEACTIVE, true, 0, SPIF_SENDWININICHANGE);
			EndDialog(IDCANCEL); 
		} 
	}
}

//////////////////////////////////////////////
////////////////////////菜单----文件
extern CString CSVFilePath;
extern CString CSVFile;
extern bool csvopen;
extern CString mainpath;
extern CList<XYLEVELItem, XYLEVELItem> tempBigRect[3];

void CHighPowerInterfaceDlg::OnNewFile() 
{
	// TODO: Add your command handler code here
	CString sz = "status file (*.Sta)|*.Sta|All File(*.*)|*.*||";
	//文件的打开与保存  为true时是打开  为false时是保存
	CFileDialog dlg(false, ".Sta", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, sz, this);

	if(IDOK==dlg.DoModal())
	{
		CString path = dlg.GetPathName();
		int flag = CopyFile(mainpath + "\\System\\Def.Sta", path, false);
		if(flag)
		{
			CStdioFile m_file;
			if(m_file.Open((LPCTSTR)path, CFile::modeReadWrite))
			{
				if(ReadStaFile(&m_file))
				{
					m_file.Close();
					CurrentFilePath = path;
					CurrentFile = m_file.GetFileName();
					m_status.SetDlgItemText(IDC_ShowCurrentFile, CurrentFilePath);
					
					csvopen = false;
					CSVFile = ".csv";
					Mappingtestlevel();
					seperateBincode();
				}
				else
				{
					m_file.Close();
					MessageBox("文件类型不正确!");
				}
			}
			else
			{
				MessageBox("文件打开失败!");
			}
		}
		else
		{
			MessageBox("新建文件失败!");
		}
	}
}

void CHighPowerInterfaceDlg::OnOpenFile() 
{
	// TODO: Add your command handler code here
	CString sz = "status file (*.Sta)|*.Sta|All File(*.*)|*.*||";
	CFileDialog dlg(true, ".Sta", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, sz, this);

	if(IDOK==dlg.DoModal())
	{
		CString path = dlg.GetPathName();
		CStdioFile m_file;
		if(m_file.Open((LPCTSTR)path, CFile::modeReadWrite))
		{
			if(ReadStaFile(&m_file))
			{
				m_file.Close();
				CurrentFilePath = path;
				CurrentFile = m_file.GetFileName();
				m_status.SetDlgItemText(IDC_ShowCurrentFile, CurrentFilePath);
				m_showtestdlg.Initshowtest();
				m_statisticdlg.Initstatistics();
				sequencenum = 0;
				
				csvopen = false;
				CSVFile = ".csv";
				Mappingtestlevel();
				seperateBincode();
				for(int i=0; i<3; i++)
				{		
					InitXYLEVELItem(i);
					GetRange(i);
				}

				rectUpdate = true;
				
				m_CIEdiagram.DrawPic();
				m_CIEdiagram.InvalidateRect(&m_CIEdiagram.rect, false);
			}
			else
			{
				m_file.Close();
				MessageBox("文件类型不正确!");
			}
		}
		else
		{
			MessageBox("文件打开失败!");
		}
	}
}

void CHighPowerInterfaceDlg::OnSaveFile() 
{
	// TODO: Add your command handler code here
	CString path;
	path = CurrentFilePath;

	CStdioFile m_file;
	if(m_file.Open((LPCTSTR)path, CFile::modeReadWrite))
	{
		WriteStaFile(&m_file);
		m_file.Close();
	}
	else
	{
		MessageBox("文件保存失败!");
	}
}

void CHighPowerInterfaceDlg::OnSaveAs() 
{
	// TODO: Add your command handler code here
	CString sz = "status file (*.Sta)|*.Sta|All File(*.*)|*.*||";
	CFileDialog dlg(false, ".Sta", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, sz, this);

	if(IDOK==dlg.DoModal())
	{
		CString path = dlg.GetPathName();
		CStdioFile m_file;
		if(m_file.Open((LPCTSTR)path, CFile::modeCreate|CFile::modeReadWrite))
		{
			WriteStaFile(&m_file);
			m_file.Close();
		}
		else
		{
			MessageBox("文件另存失败!");
		}
	}
}

void CHighPowerInterfaceDlg::OnSaveTestedData() 
{
	// TODO: Add your command handler code here
	CString sz = "DataLog file (*.Log)|*.Log|All File(*.*)|*.*||";
	CFileDialog dlg(false, ".Log", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, sz, this);

	if(IDOK==dlg.DoModal())
	{
		CString path = dlg.GetPathName();
		CStdioFile m_file;
		if(m_file.Open((LPCTSTR)path, CFile::modeCreate|CFile::modeReadWrite))
		{
			m_bindlg.Savebin();
			m_statisticdlg.Savestatistics();
			m_showtestdlg.Saveshowtest();
			m_controlsdlg.Savepasspercent();

			WriteLogFile(&m_file);
			m_file.Close();
		}
		else
		{
			MessageBox("测试数据保存失败!");
		}
	}
}

void CHighPowerInterfaceDlg::OnExportBinCode() 
{
	// TODO: Add your command handler code here
	GetCIECode();
	
	CString sz = "CSV file (*.csv)|*.csv|All File(*.*)|*.*||";
	CFileDialog dlg(false, ".csv", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, sz, this);

	if(IDOK==dlg.DoModal())
	{
		CString path = dlg.GetPathName();
		CStdioFile m_file;
		if(m_file.Open((LPCTSTR)path, CFile::modeCreate|CFile::modeReadWrite))
		{
			WriteBinCodeCSVFile(&m_file);
			m_file.Close();
		}
		else
		{
			MessageBox("分级代码导出失败!");
		}
	}
}

void CHighPowerInterfaceDlg::OnExportNewCIE() 
{
	// TODO: Add your command handler code here
	CString sz = "CSV file (*.csv)|*.csv|All File(*.*)|*.*||";
	CFileDialog dlg(false, ".csv", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, sz, this);

	if(IDOK==dlg.DoModal())
	{
		CString path = dlg.GetPathName();
		CStdioFile m_file;
		if(m_file.Open((LPCTSTR)path, CFile::modeCreate|CFile::modeReadWrite))
		{
			WriteNewCIECSVFile(&m_file);
			m_file.Close();
		}
		else
		{
			MessageBox("分级代码导出失败!");
		}
	}
}

void CHighPowerInterfaceDlg::OnExit() 
{
	// TODO: Add your command handler code here
	OnClose();
}

///////////////////////////////////////////////
//////////////////////菜单----设置

void CHighPowerInterfaceDlg::OnInitDlgs() 
{
	extern bool changeset;
	if(changeset)
	{	
		resetparam();
		m_showtestdlg.Initshowtest();
		m_statisticdlg.Initstatistics();
		m_bindlg.Initbin();
	//	m_bindlg.ShowResults();
		sequencenum = 0;
		
/*		if(showone)
		{
			m_showtestdlg.m_showtest_list.InsertItem(0, "0");
		}*/
		
		if(showsetting)
		{
			int chipnum = 3;
			if(0 == intChip)
			{
				chipnum = 1;
			}
			else if(intChip < 4)
			{
				chipnum = 2;
			}
			
		/*	if(showone)
			{
				m_showtestdlg.ShowSetting(chipnum, 1);
			}
			else
			{*/
				m_showtestdlg.ShowSetting(chipnum, 0);
		 	//}		
		}
		
		m_controlsdlg.ShowResults(0, 0);
	}
}

void CHighPowerInterfaceDlg::OnSystemSetting() 
{
	// TODO: Add your command handler code here	
	m_systemsetting.DoModal();
	m_bindlg.Initbin();
}

void CHighPowerInterfaceDlg::OnSetSpectrum() 
{
	// TODO: Add your command handler code here
	m_spectrumsetting.DoModal();
	extern bool savespec;
	if(savespec)
	{
		if(1)
		{
			KillTimer(0);
//			wrapper.closeAllSpectrometers();
		}
		initializeHardware();
		
		SystemParametersInfo(SPI_SETSCREENSAVEACTIVE, true, 0, SPIF_SENDWININICHANGE);
		EndDialog(IDCANCEL); 
	}
}

void CHighPowerInterfaceDlg::OnSetSpm() 
{
	// TODO: Add your command handler code here
	CWizard SetSpmWizard("标准灯文件设置", this, 1);
	CSetSpmReadParam readParam;
	CSetSpmSaveRefer saveRefer;
	CSetSpmSaveDark saveDark;
	CSetSpmReadLmp readlmp;
	CSetSpmCompen compen;

	SetSpmWizard.AddPage(&readParam);
	SetSpmWizard.AddPage(&saveRefer);
	SetSpmWizard.AddPage(&saveDark);
	SetSpmWizard.AddPage(&readlmp);
	SetSpmWizard.AddPage(&compen);

	SetSpmWizard.SetWizardMode();
	SetSpmWizard.SetActivePage(&readParam);
	SetSpmWizard.DoModal();
	
	extern bool saveReferParam;
	if(saveReferParam)
	{
		if(1)
		{
			KillTimer(0);
//			wrapper.closeAllSpectrometers();
		}
		initializeHardware();
		
		SystemParametersInfo(SPI_SETSCREENSAVEACTIVE, true, 0, SPIF_SENDWININICHANGE);
		EndDialog(IDCANCEL); 
	}
}

void CHighPowerInterfaceDlg::OnSetParameter() 
{
	// TODO: Add your command handler code here
	CSettingDlg m_setting;
	m_setting.DoModal();	
	OnInitDlgs(); 
	for(int i=0; i<3; i++)
	{
		InitXYLEVELItem(i);
		GetRange(i);
	}
	m_CIEdiagram.DrawPic();
	m_CIEdiagram.InvalidateRect(&m_CIEdiagram.rect, false);
}

void CHighPowerInterfaceDlg::OnSetPrint() 
{
	// TODO: Add your command handler code here
	CSetPrint m_setprint;
	m_setprint.DoModal();
}

//////////////////////////////////////////////
/////////////菜单----窗口
bool showshoot = false;
void CHighPowerInterfaceDlg::OnShoot() 
{
	// TODO: Add your command handler code here
	CShootDiagram m_shootdiagram;
	int i = 0;

	for(i=0; i<3; i++)
	{
		InitXYLEVELItem(i);
		GetRange(i);
	}
	CalculateShootBin();

	showshoot = true;
	m_shootdiagram.DoModal();
	showshoot = false;

	for(i=0; i<3; i++)
	{
		InitXYLEVELItem(i);
		GetRange(i);
	}

	m_CIEdiagram.DrawPic();
	m_CIEdiagram.InvalidateRect(&m_CIEdiagram.rect, false);
}

void CHighPowerInterfaceDlg::OnSpectrum() 
{
	// TODO: Add your command handler code here
	if(IfMenuCheck(&m_menu, ID_Spectrum))
	{	
		m_menu.CheckMenuItem(ID_Spectrum, MF_UNCHECKED);
		spectrumcheck = false;
	}
	else
	{	
		m_menu.CheckMenuItem(ID_Spectrum, MF_CHECKED);
		spectrumcheck = true;
	}
}

void CHighPowerInterfaceDlg::OnColorTemperature() 
{
	// TODO: Add your command handler code here
	if(IfMenuCheck(&m_menu, ID_ColorTemperature))
	{
		m_menu.CheckMenuItem(ID_ColorTemperature, MF_UNCHECKED);
		CIEDiagram = false;
	}
	else
	{
		m_menu.CheckMenuItem(ID_ColorTemperature, MF_CHECKED);
		CIEDiagram = true;
	}
}

void CHighPowerInterfaceDlg::OnCheckShowSetting() 
{
	// TODO: Add your command handler code here
	int nCount = 0;
	nCount = m_showtestdlg.m_showtest_list.GetItemCount();

	if(IfMenuCheck(&m_menu, ID_CheckShowSetting))
	{
		showsetting = false;
		m_menu.CheckMenuItem(ID_CheckShowSetting, MF_UNCHECKED);
		for(int i=1; i<7; i++)
		{
			m_showtestdlg.m_showtest_list.DeleteItem(nCount-i);
		}
		m_showtestdlg.m_showtest_list.Invalidate();
	}
	else
	{
		showsetting = true;
		m_menu.CheckMenuItem(ID_CheckShowSetting, MF_CHECKED);
	
		int chipnum = 3;
		if(0 == intChip)
		{
			chipnum = 1;
		}
		else if(intChip < 4)
		{
			chipnum = 2;
		}
		m_showtestdlg.ShowSetting(chipnum, nCount);
	}
}

void CHighPowerInterfaceDlg::OnRADIOOneLine() 
{
	// TODO: Add your command handler code here
	if(!IfMenuCheck(&m_menu, ID_RADIOOneLine))
	{
		showone = true;
		m_menu.CheckMenuItem(ID_RADIOOneLine, MF_CHECKED);
		m_menu.CheckMenuItem(ID_RADIOList, MF_UNCHECKED);
		if(showsetting)
		{
			int chipnum = 3;
			if(0 == intChip)
			{
				chipnum = 1;
			}
			else if(intChip < 4)
			{
				chipnum = 2;
			}
			m_showtestdlg.ShowSetting(chipnum, 1);
		}
	}
}

void CHighPowerInterfaceDlg::OnRADIOList() 
{
	// TODO: Add your command handler code here
	if(!IfMenuCheck(&m_menu, ID_RADIOList))
	{
		showone = false;
		m_menu.CheckMenuItem(ID_RADIOOneLine, MF_UNCHECKED);
		m_menu.CheckMenuItem(ID_RADIOList, MF_CHECKED);
		if(showsetting)
		{
			int nCount = 0, chipnum = 3;
			nCount = m_showtestdlg.m_showtest_list.GetItemCount();
			if(0 == intChip)
			{
				chipnum = 1;
			}
			else if(intChip < 4)
			{
				chipnum = 2;
			}
			m_showtestdlg.ShowSetting(chipnum, nCount);
		}
	}
}

void CHighPowerInterfaceDlg::OnCheckLog() 
{
	// TODO: Add your command handler code here
	CString sz = "DataLog file (*.Log)|*.Log|All File(*.*)|*.*||";
	CFileDialog dlg(true, ".Log", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, sz, this);

	if(IDOK==dlg.DoModal())
	{
		CString path = dlg.GetPathName();
		ShellExecute(this->m_hWnd, "open", path, NULL, NULL, SW_SHOW);
/*		CStdioFile m_file;
		if(m_file.Open((LPCTSTR)path, CFile::modeReadWrite))
		{
			ReadLogFile(&m_file);
			m_file.Close();
		}
		else
		{
			MessageBox("历史数据文件打开失败!");
		}*/
	}
	//文件打开后   初始化各listcontrol  显示历史数据 
}

void CHighPowerInterfaceDlg::OnshowLevelSet() 
{
	// TODO: Add your command handler code here
	m_showlevel.initdlg();
	m_showlevel.ShowWindow(SW_SHOW);
}

//////////////////////////////////////////////
/////////////菜单----测试
extern SystemSet systemset;
extern double x[3], y[3];
extern bool ifDead;

void CHighPowerInterfaceDlg::OnResistance() 
{
	// TODO: Add your command handler code here
	CLight light;
	light.DoModal();
}

void CHighPowerInterfaceDlg::OnTestSingle() 
{
	// TODO: Add your command handler code here	
	m_menu.EnableMenuItem(ID_TestSingle, MF_ENABLED);
	m_menu.EnableMenuItem(ID_TestContinuous, MF_ENABLED);
	m_menu.EnableMenuItem(ID_TestAuto, MF_ENABLED);
	m_menu.EnableMenuItem(ID_StopTest, MF_GRAYED);
	m_menu.EnableMenuItem(ID_RestartTest, MF_ENABLED);
	m_menu.EnableMenuItem(ID_ClearUp, MF_ENABLED);

	m_controlsdlg.m_retest.EnableWindow(true);
	
	KillTimer(0);
	Mappingtestlevel();
	StartSingleTest();
	SetTimer(0, 60000, NULL);
}

void CHighPowerInterfaceDlg::OnTestContinuous() 
{
	// TODO: Add your command handler code here
	m_menu.EnableMenuItem(0, MF_GRAYED|MF_BYPOSITION); 
	m_menu.EnableMenuItem(1, MF_GRAYED|MF_BYPOSITION); 
	m_menu.EnableMenuItem(4, MF_GRAYED|MF_BYPOSITION); 
	
	m_menu.EnableMenuItem(ID_TestSingle, MF_GRAYED);
	m_menu.EnableMenuItem(ID_TestContinuous, MF_GRAYED);
	m_menu.EnableMenuItem(ID_TestAuto, MF_GRAYED);
	m_menu.EnableMenuItem(ID_StopTest, MF_ENABLED);	
	m_menu.EnableMenuItem(ID_RestartTest, MF_GRAYED);
	m_menu.EnableMenuItem(ID_Resistance, MF_GRAYED);
	m_menu.EnableMenuItem(ID_ClearUp, MF_GRAYED);
	
	m_menu.EnableMenuItem(ID_LightOn, MF_GRAYED);
	m_menu.EnableMenuItem(ID_LightOff, MF_GRAYED);

	btn->EnableButton(ID_Tool_OpenFile, false);
	btn->EnableButton(ID_SettingParam, false);

	m_controlsdlg.m_minusdark.EnableWindow(false);
	m_controlsdlg.m_single.EnableWindow(false);
	m_controlsdlg.m_continue.EnableWindow(false);
	m_controlsdlg.m_auto.EnableWindow(false);
	m_controlsdlg.m_retest.EnableWindow(false);
	m_controlsdlg.m_stop.EnableWindow(true);
	
	m_authorityview.m_authoritychange.EnableWindow();
	
	//////////////////////////
	KillTimer(0);
	Mappingtestlevel();
	UpdateData(true);
	continuetest = true;
	pThread = AfxBeginThread(StartContinuousTest, &testInfo);
}


void CHighPowerInterfaceDlg::OnTestAuto() 
{
	// TODO: Add your command handler code here
	if(ifStartClearBox)
	{
		MessageBox("请先停止手动清料!");
	}
	else
	{
		if(leftTimeAft < 5)
		{
			CString str;
			str.Format("您的软件使用时间仅剩%d天, 为不影响生产, 请尽快与厂家联系!", leftTimeAft);
			MessageBox(str);
		}
		
		m_menu.CheckMenuItem(ID_TestAuto, MF_CHECKED);
		
		m_menu.EnableMenuItem(0, MF_GRAYED|MF_BYPOSITION); 
		m_menu.EnableMenuItem(1, MF_GRAYED|MF_BYPOSITION); 
		m_menu.EnableMenuItem(4, MF_GRAYED|MF_BYPOSITION); 
		
		m_menu.EnableMenuItem(ID_TestSingle, MF_GRAYED);
		m_menu.EnableMenuItem(ID_TestContinuous, MF_GRAYED);
		m_menu.EnableMenuItem(ID_TestAuto, MF_GRAYED);
		m_menu.EnableMenuItem(ID_StopTest, MF_ENABLED);	
		m_menu.EnableMenuItem(ID_RestartTest, MF_GRAYED);
		m_menu.EnableMenuItem(ID_Resistance, MF_GRAYED);
		m_menu.EnableMenuItem(ID_ClearUp, MF_GRAYED);
		m_menu.EnableMenuItem(ID_ClearBinBox, MF_GRAYED);
		m_menu.EnableMenuItem(ID_StartClearBox, MF_GRAYED);
		
		m_menu.EnableMenuItem(ID_LightOn, MF_GRAYED);
		m_menu.EnableMenuItem(ID_LightOff, MF_GRAYED);
		
		btn->EnableButton(ID_Tool_OpenFile, false);
		btn->EnableButton(ID_SettingParam, false);
		
		m_controlsdlg.m_minusdark.EnableWindow(false);	
		m_controlsdlg.m_single.EnableWindow(false);
		m_controlsdlg.m_continue.EnableWindow(false);
		m_controlsdlg.m_auto.EnableWindow(false);
		m_controlsdlg.m_retest.EnableWindow(false);
		m_controlsdlg.m_stop.EnableWindow(true);
		
		m_authorityview.m_authoritychange.EnableWindow(false);
		
		/////////////////////////////
		KillTimer(0);
		Mappingtestlevel();
		UpdateData(true);
		continuetest = true;
		SetTimer(1, 1, NULL);
		if(openCom)
		{
			SetTimer(4, 1, NULL);
		}
		pThread = AfxBeginThread(StartAutoTest, &testInfo);	
	}
}

void CHighPowerInterfaceDlg::OnStopTest() 
{
	// TODO: Add your command handler code here
	if(IfMenuCheck(&m_menu, ID_TestAuto))
	{	
		m_menu.CheckMenuItem(ID_TestAuto, MF_UNCHECKED);		
		KillTimer(1);
		KillTimer(4);
	}

	continuetest = false;

	m_menu.EnableMenuItem(ID_TestSingle, MF_ENABLED);
	m_menu.EnableMenuItem(ID_TestContinuous, MF_ENABLED);
	m_menu.EnableMenuItem(ID_TestAuto, MF_ENABLED);	
	m_menu.EnableMenuItem(ID_StopTest, MF_GRAYED);
	m_menu.EnableMenuItem(ID_RestartTest, MF_ENABLED);
	m_menu.EnableMenuItem(ID_Resistance, MF_ENABLED);
	m_menu.EnableMenuItem(ID_ClearUp, MF_ENABLED);
	
	if(ifPrintVersion)
	{
		m_menu.EnableMenuItem(ID_ClearBinBox, MF_ENABLED);
		m_menu.EnableMenuItem(ID_StartClearBox, MF_ENABLED);
	}
	
	m_menu.EnableMenuItem(0, MF_ENABLED|MF_BYPOSITION); 
	m_menu.EnableMenuItem(1, MF_ENABLED|MF_BYPOSITION); 
	m_menu.EnableMenuItem(4, MF_ENABLED|MF_BYPOSITION); 
	
	m_menu.EnableMenuItem(ID_LightOn, MF_ENABLED);
	m_menu.EnableMenuItem(ID_LightOff, MF_ENABLED);
	
	btn->EnableButton(ID_Tool_OpenFile, true);
	btn->EnableButton(ID_SettingParam, true);
	
	m_controlsdlg.m_minusdark.EnableWindow(true);
	m_controlsdlg.m_single.EnableWindow(true);
	m_controlsdlg.m_continue.EnableWindow(true);
	m_controlsdlg.m_auto.EnableWindow(true);
	m_controlsdlg.m_retest.EnableWindow(true);
	m_controlsdlg.m_stop.EnableWindow(false);
	
	m_authorityview.m_authoritychange.EnableWindow(true);
	SetTimer(0, 60000, NULL);
}

void CHighPowerInterfaceDlg::OnRestartTest() 
{
	// TODO: Add your command handler code here
	m_menu.EnableMenuItem(0, MF_DISABLED|MF_BYPOSITION|MF_GRAYED); 
	m_menu.EnableMenuItem(1, MF_DISABLED|MF_BYPOSITION|MF_GRAYED); 
	m_menu.EnableMenuItem(4, MF_DISABLED|MF_BYPOSITION|MF_GRAYED); 
	
	m_menu.EnableMenuItem(ID_TestSingle, MF_GRAYED);
	m_menu.EnableMenuItem(ID_TestContinuous, MF_GRAYED);
	m_menu.EnableMenuItem(ID_TestAuto, MF_GRAYED);
	m_menu.EnableMenuItem(ID_StopTest, MF_ENABLED);	
	m_menu.EnableMenuItem(ID_RestartTest, MF_GRAYED);
	m_menu.EnableMenuItem(ID_Resistance, MF_GRAYED);
	m_menu.EnableMenuItem(ID_ClearUp, MF_GRAYED);	
	
	m_menu.EnableMenuItem(ID_LightOn, MF_GRAYED);
	m_menu.EnableMenuItem(ID_LightOff, MF_GRAYED);
	
	btn->EnableButton(ID_Tool_OpenFile, false);
	btn->EnableButton(ID_SettingParam, false);

	m_controlsdlg.m_minusdark.EnableWindow(false);
	m_controlsdlg.m_single.EnableWindow(false);
	m_controlsdlg.m_continue.EnableWindow(false);
	m_controlsdlg.m_retest.EnableWindow(false);
	m_controlsdlg.m_stop.EnableWindow(true);
	
	m_authorityview.m_authoritychange.EnableWindow(false);
	
	m_showtestdlg.Initshowtest();
	sequencenum = 0;
	resetparam();
	
	KillTimer(0);
	Mappingtestlevel();
	UpdateData(true);
	continuetest = true;
	SetTimer(2, 60000, NULL);
	pThread = AfxBeginThread(StartContinuousTest, &testInfo);
}

/////////////手动清料
void CHighPowerInterfaceDlg::OnStartClearBox() 
{
	// TODO: Add your command handler code here
	if(continuetest)
	{
		MessageBox("请先停止自动测试!");
	}
	else
	{
		bool checksuccess = false;
		int startclearsign = 90;
		
		m_menu.EnableMenuItem(ID_StartClearBox, MF_GRAYED);
		m_menu.EnableMenuItem(ID_StopClearBox, MF_ENABLED);
		m_menu.EnableMenuItem(ID_TestAuto, MF_GRAYED);
		
		m_showlevel.m_startclear.EnableWindow(false);
		m_showlevel.m_stopclear.EnableWindow(true);
		
		CString str_send = "EF", str_read = "", str_figure = "", str_showcode;
		int times = 0;
		int length = 0;
		int maxtimes = 450;
		int stalen = 0;
		if(openCom)
		{
			Outport(0x251, 0xFF);
			Sleep(1);
			Outport(0x251, startclearsign ^ 0xFF);
			
			///发消息询问是否有串口消息
			str_send = "EF";
			sendString(str_send);
			
			///读取回传消息，若无，则不操作；
			while(times<maxtimes)
			{
				str_read += readdata();
				length = strlen(str_read);
				
				///若有，则判断是料盒核对信号，还是抽出料盒信号
				if(0 == stalen)
				{
					if(length > 1)
					{
						str_figure = str_read.Left(4); 
						if(str_figure == "FBCD")
						{
							stalen = 540;
							times = 0;
						}
						else
						{
							str_read = "";
						}
					}
					else
					{
						Sleep(1);
						times++;
					}
				}
				else
				{
					if(540 == length)
					{
						times = maxtimes;
						
						OldBoxStatusArray.RemoveAll();
						NewBoxStatusArray.RemoveAll();
						BoxStatusArray.RemoveAll();
						SetTimer(5, 50, NULL);
						
						checksuccess = true;
						ifStartClearBox = true;

						str_showcode = str_read;
						m_showlevel.m_tempcode.SetWindowText(str_showcode);

						if(checkBoxnum())
						{
							m_showlevel.SetBinMapList();
							m_showlevel.UpdataExchangeParam();
							waitingCheckLed.RemoveAll();
							m_showlevel.m_codefromhardware.SetWindowText(str_showcode);
						}
					}
					else
					{
						Sleep(1);
						times++;
					}
				}
			}
		}
		
		if(!checksuccess)
		{
			OnStopClearBox();
			MessageBox("数据异常!");
		}
	}
}

void CHighPowerInterfaceDlg::OnStopClearBox() 
{
	// TODO: Add your command handler code here
	int stopclearsign = 91;

	Outport(0x251, 0xFF);
	Sleep(1);
	Outport(0x251, stopclearsign ^ 0xFF);

	ifStartClearBox = false;
	
	KillTimer(5);
	m_menu.EnableMenuItem(ID_StartClearBox, MF_ENABLED);
	m_menu.EnableMenuItem(ID_StopClearBox, MF_GRAYED);
	m_menu.EnableMenuItem(ID_TestAuto, MF_ENABLED);

	m_showlevel.m_startclear.EnableWindow(true);
	m_showlevel.m_stopclear.EnableWindow(false);
}

void CHighPowerInterfaceDlg::OnClearUp() 
{
	// TODO: Add your command handler code here
	m_menu.EnableMenuItem(ID_TestSingle, MF_ENABLED);
	m_menu.EnableMenuItem(ID_TestContinuous, MF_ENABLED);
	m_menu.EnableMenuItem(ID_StopTest, MF_GRAYED);
	m_menu.EnableMenuItem(ID_RestartTest, MF_GRAYED);
	m_menu.EnableMenuItem(ID_ClearUp, MF_GRAYED);
	m_controlsdlg.m_retest.EnableWindow(false);
	m_showtestdlg.m_showtest_list.DeleteAllItems();//清空

	resetparam();
	m_showtestdlg.Initshowtest();
	m_statisticdlg.Initstatistics();
	m_bindlg.Initbin();
	m_bindlg.ShowResults();
	
	m_menu.CheckMenuItem(ID_CheckShowSetting, MF_UNCHECKED);
	sequencenum = 0;
	m_controlsdlg.ShowResults(0, 0);
}

void CHighPowerInterfaceDlg::OnClearBinBox() 
{
	// TODO: Add your command handler code here
	for(int i=0; i<MAXBIN; i++)
	{
		binBox[i][0] = 80;
		binBox[i][1] = 0;
	}
	m_showlevel.SetBinMapList();
}

void CHighPowerInterfaceDlg::StartSingleTest()
{
	clock_t start, finish;   
	double duration = 0;  
	CString str;
	int *bin = (int*)malloc(sizeof(int)*2);
	int chipnum = 3;
	if(0 == intChip)
	{
		chipnum = 1;
	}
	else if(intChip < 4)
	{
		chipnum = 2;
	}

	start = clock();  

	if(0 == intChip)   //双脚单晶
	{	
		Handle2Pin1Chip();
	}
	else if(1 == intChip)//双脚双晶
	{
		Handle2Pin2Chip();
	}
	else if(2 == intChip)//三脚双晶
	{
		Handle3Pin2Chip();
	}
	else if(3 == intChip)//四脚双晶
	{
		Handle4Pin2Chip();
	}
	else if(4 == intChip)//四脚三晶
	{
		Handle4Pin3Chip();
	}
	else if(5 == intChip)//六脚三晶
	{
		Handle6Pin3Chip();
	}
	
	bin = CalculateBin(false);
	if(bin[0] >= systemset.intMachineType)
	{
		bin[0] = 0;
	}

	//将测试结果显示在listcontrol上
	if(ifDead)
	{
		m_showtestdlg.ShowNULL(chipnum, sequencenum++, bin[0]);
		ifDead = false;
	}
	else
	{	
		m_showtestdlg.ShowResults(chipnum, sequencenum++, bin[0]);
	}
	
	//显示已测试的灯的个数  合格数  不合格数  合格率
	m_controlsdlg.ShowResults(ledStatistic.ledtotalnum++, ledStatistic.ledpassnum);
	/////若有需要 绘制光谱图和CIE图
	m_spectrum.InvalidateRect(&m_spectrum.rect, false);
	if(((1 == intMixLight) && MixLedLight[0] && MixLedLight[1] && MixLedLight[2])
		|| (0 == intMixLight))
	{
		AddTail(x[0], y[0]);
	}
	m_CIEdiagram.InvalidateRect(&m_CIEdiagram.rect, false);

	m_statisticdlg.ShowResults();
	m_bindlg.ShowResults();

	finish = clock();   
	duration = (double)(finish - start);
	if(duration != 0)
	{
		str.Format("%0.2f", duration);
		m_controlsdlg.SetDlgItemText(IDC_TestTime, str);
	}

	free(bin);
}

UINT StartContinuousTest(LPVOID lpParam)
{
	threadInfo* pInfo = (threadInfo*)lpParam;
	ASSERT(pInfo);
	CString  str;
	clock_t start, finish; 
	double duration = 0;
	int *bin = (int*)malloc(sizeof(int)*2);
	int i =0, j = 0;
	int chipnum = 3;
	if(0 == intChip)
	{
		chipnum = 1;
	}
	else if(intChip < 4)
	{
		chipnum = 2;
	}

	while(continuetest)
	{  
		start = clock(); 
		
		if(0 == intChip)   //双脚单晶
		{	
			Handle2Pin1Chip();
		}
		else if(1 == intChip)//双脚双晶
		{
			Handle2Pin2Chip();
		}
		else if(2 == intChip)//三脚双晶
		{
			Handle3Pin2Chip();
		}
		else if(3 == intChip)//四脚双晶
		{
			Handle4Pin2Chip();
		}
		else if(4 == intChip)//四脚三晶
		{
			Handle4Pin3Chip();
		}
		else if(5 == intChip)//六脚三晶
		{
			Handle6Pin3Chip();
		}
		
		bin = CalculateBin(false);
		if(bin[0] >= systemset.intMachineType)
		{
			bin[0] = 0;
		}
		finish = clock();

		pInfo->m_bin->UpdateData(bin[0]);

		//显示已测试的灯的个数  合格数  不合格数  合格率
		pInfo->m_control->ShowResults(ledStatistic.ledtotalnum++, ledStatistic.ledpassnum);

		/////若有需要 绘制光谱图和CIE图
		pInfo->m_spectrum->InvalidateRect(&pInfo->m_spectrum->rect, false);
		
		if(((1 == intMixLight) && MixLedLight[0] && MixLedLight[1] && MixLedLight[2])
			|| (0 == intMixLight))
		{
			AddTail(x[0], y[0]);
		}
		
		pInfo->m_CIEdiagram->InvalidateRect(&pInfo->m_CIEdiagram->rect, false);

		/////////将测试结果显示在listcontrol上
		if(ifDead)
		{
			pInfo->m_showtest->ShowNULL(chipnum, sequencenum++, bin[0]);
			ifDead = false;
		}
		else
		{
			pInfo->m_showtest->ShowResults(chipnum, sequencenum++, bin[0]);
		}

		duration = (double)(finish - start);		
		if(duration != 0)
		{
			str.Format("%0.2f", duration);
			pInfo->m_control->SetDlgItemText(IDC_TestTime, str);
//			str.Format("%0.2f", 3600/duration);
//			pInfo->m_control->SetDlgItemText(IDC_TestSpeed, str);
		}

	/*	if(duration > 100)
		{
			MessageBeep(1);
			AfxMessageBox("Appear");
		}*/

		Delay(200000);
	}

	free(bin);

	pInfo->m_statistic->ShowResults();
	pInfo->m_bin->ShowResults();

	DWORD dwExitCode;
	GetExitCodeThread(pThread->m_hThread, &dwExitCode);
	AfxEndThread(dwExitCode, true);

	return 0;
}


UINT StartAutoTest(LPVOID lpParam)
{
	threadInfo* pInfo = (threadInfo*)lpParam;
	ASSERT(pInfo);
	CString  str;
	LedStatus ledsta;

	clock_t start, finish; 
	double duration = 0;
	int *bin = (int*)malloc(sizeof(int)*2);
	int chipnum = 3;
	if(0 == intChip)
	{
		chipnum = 1;
	}
	else if(intChip < 4)
	{
		chipnum = 2;
	}

	CStdioFile m_file;
	CString path;
	path = MapBinFilePath;

	while(continuetest)
	{
		if(highsignal && (0 == (Inport(0x250) & 1)))
		{
			testbusy = true;
			highsignal = false;
		
			if(ifPrintVersion)
			{
				////机器移位
				feedingClowBox.RemoveAt(104);
				feedingClowBox.InsertAt(0, 80);
				feedingClowBox[3] = feedingClowBox[2];
				feedingClowBox[2] = 80;
				
				if(8 == waitingCheckLed.GetSize())
				{
					/////此处获取光纤位置是否有灯
					if((Inport(0x250) & 0x80) != 0)
					{
						///若无灯，则需要减去对应分级和对应料盒数量，以及测试的总数量
						binnum[waitingCheckLed[0].bin]--;
						binBox[waitingCheckLed[0].boxnum][1]--;
						ledStatistic.ledtotalnum--;
						if(ledsta.pass)
						{
							ledStatistic.ledpassnum--;
						}
						feedingClowBox[9] = 80;  ///料爪此处无灯
					}
					
					waitingCheckLed.RemoveAt(0);
				}
			}

			start = clock(); 
			
			Outport(0x250, 0xFF);
			Outport(0x251, 0xFF);
			
			if(0 == intChip)   //双脚单晶
			{	
				Handle2Pin1Chip();
			}
			else if(1 == intChip)//双脚双晶
			{
				Handle2Pin2Chip();
			}
			else if(2 == intChip)//三脚双晶
			{
				Handle3Pin2Chip();
			}
			else if(3 == intChip)//四脚双晶
			{
				Handle4Pin2Chip();
			}
			else if(4 == intChip)//四脚三晶
			{
				Handle4Pin3Chip();
			}
			else if(5 == intChip)//六脚三晶
			{
				Handle6Pin3Chip();
			}
			
			bin = CalculateBin(ifPrintVersion);
			if(bin[0] >= systemset.intMachineType)
			{
				bin[0] = 0;
			}

			finish = clock();
			duration = (double)(finish - start);
			
			if(duration < systemset.mintesttime)
			{
				int time = 0;
				time = systemset.mintesttime - (int)duration;
				Delay(time * 1000);
			}

			Outport(0x251, bin[1] ^ 0xFF);
			Delay (systemset.sentBinDelay * 1000);
			Outport(0x250, 0xFE);

			if(ifPrintVersion)
			{
				ledsta.bin = bin[0];
				ledsta.boxnum = bin[1];
				ledsta.pass = iftestpass;
				waitingCheckLed.Add(ledsta);
				iftestpass = false;
				
				feedingClowBox[0] = bin[1];////测试完成后，给测试位料爪的灯分配料盒
				
				if(m_file.Open((LPCTSTR)path, CFile::modeReadWrite))
				{
					WriteBinMapFile(&m_file);
					m_file.Close();
				}
				else
				{
					AfxMessageBox("文件保存失败!");
				}
			}

			if(duration != 0)
			{
				str.Format("%0.2f", duration);
				pInfo->m_control->SetDlgItemText(IDC_TestTime, str);
			}	
			
			pInfo->m_bin->UpdateData(bin[0]);
			pInfo->m_showlevel->updataBinMapList(bin[1]);

			//显示已测试的灯的个数  合格数  不合格数  合格率
			pInfo->m_control->ShowResults(ledStatistic.ledtotalnum++, ledStatistic.ledpassnum);
			/////若有需要 绘制光谱图和CIE图
			pInfo->m_spectrum->InvalidateRect(&pInfo->m_spectrum->rect, false);
			
			if(((1 == intMixLight) && MixLedLight[0] && MixLedLight[1] && MixLedLight[2])
				|| (0 == intMixLight))
			{
				AddTail(x[0], y[0]);
			}

			pInfo->m_CIEdiagram->InvalidateRect(&pInfo->m_CIEdiagram->rect, false);
			
			/////////将测试结果显示在listcontrol上	
			if(ifDead)
			{
				pInfo->m_showtest->ShowNULL(chipnum, sequencenum++, bin[0]);
				ifDead = false;
			}
			else
			{
				pInfo->m_showtest->ShowResults(chipnum, sequencenum++, bin[0]);
			}
			
			testbusy = false;
		}
	}

	free(bin);

	pInfo->m_statistic->ShowResults();
	pInfo->m_bin->ShowResults();

	DWORD dwExitCode;
	GetExitCodeThread(pThread->m_hThread, &dwExitCode);
	AfxEndThread(dwExitCode, true);

	return 0;
}
//////////////////////////////////////////////////////////////////////
/////////////////////菜单----权限
bool CHighPowerInterfaceDlg::HideMenu()
{
	m_menu.RemoveMenu(ID_SystemSetting, MF_BYCOMMAND);
	m_menu.RemoveMenu(ID_SetSpectrum, MF_BYCOMMAND);
	m_menu.RemoveMenu(ID_SetSpm, MF_BYCOMMAND);

	return true;
}

bool CHighPowerInterfaceDlg::showMenu()
{
	CMenu *pSubmenu = m_menu.GetSubMenu(1);
	pSubmenu->InsertMenu(0, MF_BYPOSITION|MF_STRING, ID_SystemSetting, "    系统设置");
	pSubmenu->InsertMenu(1, MF_BYPOSITION|MF_STRING, ID_SetSpectrum, "    光谱仪参数设置");
	pSubmenu->InsertMenu(2, MF_BYPOSITION|MF_STRING, ID_SetSpm, "    标准灯文件设置");

	return true;
}

void CHighPowerInterfaceDlg::OnRegist() 
{
	// TODO: Add your command handler code here
	m_register.DoModal();
}

void CHighPowerInterfaceDlg::OnGuest()
{
	// TODO: Add your command handler code here
	m_authorityview.SetDlgItemText(IDC_ShowAuthority, "普通用户");
//	m_menu.EnableMenuItem(ID_Operator, MF_ENABLED);
//	m_menu.EnableMenuItem(ID_Engineer, MF_ENABLED);
	engineer = false;
	Operator = false;
	
	HideMenu();
}

void CHighPowerInterfaceDlg::OnOperator() 
{
	// TODO: Add your command handler code here
	CLogin m_login;;
	m_login.DoModal();

	extern bool enterE;
	if(enterE)
	{
		if(!engineer)
		{
			OnEngineer();
		}
	}
	else
	{
		if(m_login.login)
		{
			m_authorityview.SetDlgItemText(IDC_ShowAuthority, "操作员");
//			m_menu.EnableMenuItem(ID_Operator, MF_GRAYED);
//			m_menu.EnableMenuItem(ID_Engineer, MF_ENABLED);
			Operator = true;
			engineer = false;
			
			HideMenu();
		}
	}
}

void CHighPowerInterfaceDlg::OnEngineer() 
{
	// TODO: Add your command handler code here
	CEngineerLogin m_Elogin;
	m_Elogin.DoModal();
	if(m_Elogin.login)
	{
		m_authorityview.SetDlgItemText(IDC_ShowAuthority, "工程师");
//		m_menu.EnableMenuItem(ID_Engineer, MF_GRAYED);
//		m_menu.EnableMenuItem(ID_Operator, MF_ENABLED);
		engineer = true;
		Operator = false;
		
		showMenu();
	}
}

void CHighPowerInterfaceDlg::OnRegistInformation() 
{
	// TODO: Add your command handler code here
	CChangePassword m_changepassword;
	m_changepassword.DoModal();
}

void CHighPowerInterfaceDlg::OnAddUsers() 
{
	// TODO: Add your command handler code here
	if(Operator || engineer)
	{
		m_addusers.DoModal();
	}
	else
	{
		MessageBox("请先登录再添加用户!");
	}
}

void CHighPowerInterfaceDlg::OnDeleteUsers() 
{
	// TODO: Add your command handler code here
	m_deleteusers.DoModal();
}

//////////////////////////////////////////////////
/////////////////菜单----帮助
void CHighPowerInterfaceDlg::OnManual() 
{
	// TODO: Add your command handler code here
}

void CHighPowerInterfaceDlg::OnConnect() 
{
	// TODO: Add your command handler code here
//	ShellExecute(NULL, NULL, _T("http://www.chinashengxin.com.cn/"), NULL, NULL, SW_SHOWNORMAL);
}

void CHighPowerInterfaceDlg::OnAbout() 
{
	// TODO: Add your command handler code here
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}
///////////////////////////////////////////////////
////////////////工具栏
bool CHighPowerInterfaceDlg::OnToolTipNotify(UINT id, NMHDR *pNMHDR, LRESULT *pResult)
{
    TOOLTIPTEXT *pTTT = (TOOLTIPTEXT *)pNMHDR;
    UINT nID = pNMHDR->idFrom; //获取工具栏按钮ID
	int index = m_toolbar.GetToolBarCtrl().CommandToIndex(nID);//根据ID获取按钮索引
	switch(index)
	{
	case 0:
		pTTT->lpszText = "打开";
		break;
	case 1:
		pTTT->lpszText = "保存";
		break;
	case 2:
		pTTT->lpszText = "另存为";
		break;
	case 3:
		pTTT->lpszText = "参数设置";
		break;
	default:
		break;
	}	
    pTTT->hinst = AfxGetResourceHandle();

    return true;
}

void CHighPowerInterfaceDlg::OnToolOpenFile() 
{
	// TODO: Add your command handler code here
	OnOpenFile();
}

void CHighPowerInterfaceDlg::OnToolSaveFile() 
{
	// TODO: Add your command handler code here
	OnSaveFile();
}

void CHighPowerInterfaceDlg::OnToolSaveAs() 
{
	// TODO: Add your command handler code here
	OnSaveAs(); 
}


void CHighPowerInterfaceDlg::OnSettingParam() 
{
	// TODO: Add your command handler code here	
	OnSetParameter(); 
}

///////////////////////

BOOL CHighPowerInterfaceDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message == WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
		case VK_F5:
			OnTestSingle();
			return true;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}
///////////////////////////////////////////
///////////界面
BOOL CHighPowerInterfaceDlg::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	CBitmap bmp;
	CBitmap *ptrBmpOld;
	BITMAP bm;

	bmp.LoadBitmap(IDB_MainBK2);
	bmp.GetBitmap(&bm);

	CRect rect;
	GetClientRect(rect);

	int w,h;
	w=rect.Width()/bm.bmWidth+1;
	h=rect.Height()/bm.bmHeight+1;

	CDC dcMemory;
	dcMemory.CreateCompatibleDC(pDC);
	ptrBmpOld=dcMemory.SelectObject(&bmp);

//	pDC->StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMemory, 0,0, bm.bmWidth, bm.bmHeight, SRCCOPY);
	for(int i=0;i<w;i++)
	{
		for(int j=0;j<h;j++)
		{
			pDC->BitBlt
				(
				i*bm.bmWidth,
				j*bm.bmHeight,
				bm.bmWidth,
				bm.bmHeight,
				&dcMemory,
				0,
				0,
				SRCCOPY
				);
		}
	}
	return true;
}
// 
// afx_msg LONG CHighPowerInterfaceDlg::OnDataReady(UINT wParam,LONG lParam)
// {               
// 	// all UM_DREADY messages arrive at one time, not in sequence
// 	OOI_BufferEmpty(hInstance,wParam);
// 	return 1;
// }

BOOL CHighPowerInterfaceDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	// TODO: Add your message handler code here and/or call default
	if((pt.x >= 735) && (pt.x <= 1070) 
		&& (pt.y >= 356) && (pt.y <= 668))
	{
/*		if(zDelta == 120)
		{
			m_CIEdiagram.enlarge(0, 0); 
		}
		else if(zDelta == -120)
		{
			m_CIEdiagram.smaller(0, 0); 
		}*/
	}
	return CDialog::OnMouseWheel(nFlags, zDelta, pt);
}


//BEGIN_EVENTSINK_MAP(CHighPowerInterfaceDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CHighPowerInterfaceDlg)
//	ON_EVENT(CHighPowerInterfaceDlg, IDC_MSCOMM1, 1 /* OnComm */, OnOnCommMscomm1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
//END_EVENTSINK_MAP()
/*
void CHighPowerInterfaceDlg::OnOnCommMscomm1() 
{
	// TODO: Add your control notification handler code here
	BYTE data[31];
	VARIANT m_input1;
	COleSafeArray m_input2;
	long length = 0, i = 0;

	if(m_ctrlComm.GetCommEvent()==2)//接收缓冲区内有字符
	{
		m_input1 = m_ctrlComm.GetInput();//读取缓冲区内的数据
		m_input2=m_input1;//将VARIANT型变量转换为ColeSafeArray型变量
		length=m_input2.GetOneDimSize();//确定数据长度

		for(i=0;i<length;i++)
		{
			m_input2.GetElement(&i,data+i);//将数据转换为BYTE型数组
			printdata.Add(data[i]);
		}
	}
}*/




