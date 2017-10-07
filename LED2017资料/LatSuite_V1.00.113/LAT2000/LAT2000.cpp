
// LED850.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "LAT2000.h"
#include "MainFrm.h"
#include "MainTabWnd.h"
#include "ExNewCorrectColorParaDLL.h"
#include "LAT2000Doc.h"
#include "MainTestFormView.h"
#include "About_def.h"
#include "AccountDlg.h"
#include "Splash.h"
#include "DlgControlShow.h"
#include "DlgSeleLamp.h"
#include "AlarmSettingsDlg.h"
#include "ExEverLincese.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CHaas1200Meter	  g_Hass1200Meter;
CDPSPowerComm	  g_DPSComm;       //测试用电源
CDPSPowerComm	  g_DPSAgeComm[2]; //4m线老炼用DPS 特殊
CDPSPowerComm	  g_DPSComm_MyLast;
CGaugeComm		  g_GaugeComm;
CSC1000Comm		  g_SC1000Comm;
CLRAComm		  g_TestChannelControlComm;	// 0xEF

CPowerMeterComm	  g_PowerMeterComm;
CIndicatorComm	  g_IndicatorComm;
CEMS61000_5AComm  g_EMS61000_5AComm;
CEMS61000_11KComm g_EMS61000_11KComm;
CWYComm			  g_WYComm;
CHLS_200          g_HLS_200;

CLRAComm			g_LRAComm;			// 0xAF
CThunderRelayComm	g_ThunderRelayComm;	// 0xBF
CBribeComm			g_BribeComm;		// 0xCF
CContNyyComm		g_ContNyyComm;		// 0xBF 单片机程序同雷击 仅串口不太
CContJydzComm		g_ContJydzComm;		// 0xBF 单片机程序同雷击 仅串口不太
CContXldlComm		g_ContXldlComm;		// 0xBF 单片机程序同雷击 仅串口不太

CFujiTMPComm		g_FujiTMPComm;
CLineControllerComm g_LineControllerComm;
CHandAutoComm		g_HandAutoComm;

CScanerComm			g_ScanerComm;
CExTouchSrceenComm	g_TSrceenComm;

CSafetyTest_CSComm2676	g_SafetyTest_CS2676Comm;
CSafetyTest_CSComm9912	g_SafetyTest_CS9912Comm;
CSafetyTest_CSComm5505	g_SafetyTest_CS5505Comm;

CSafetyTest_TongHui_TH2683AComm		g_SafetyTest_TongHui_TH2683AComm;
CSafetyTest_TongHui_TH9310_20Comm	g_SafetyTest_TongHui_TH9310_20Comm;


CString g_strCurrentPath;
CString g_strLimitDataPath;
CString g_strRectificationPath;
CString g_strHistoryDataPath;

int		g_iExecutionLevel;
BOOL	g_bhaveSaveFile;


BOOL	g_bEnglish			= FALSE;
BOOL	g_bTMPControllerON	= FALSE;

COLORREF g_ColorGood = RGB(5, 165, 90);
COLORREF g_ColorBad = RGB(195, 95, 140);
COLORREF g_ColorNotTest = RGB(125, 125, 125);
COLORREF g_ColorInvalid = RGB(160, 155, 20);
COLORREF g_ColorBad_Codi = RGB(128, 0, 64);

BOOL g_bDisplayLimitOnly = FALSE;
//Pass Flag
BOOL	g_bDebug		= FALSE; 
BOOL	g_bStatistic	= FALSE;
BOOL	g_iDarkAD		= 5000;
int     g_iColomnNum	= 10;
int     g_iRowNum		= 3;
BOOL    g_bUnOnPopedom	= FALSE;

HWND	g_hDockablePaneDialog	= NULL;
HWND	g_hMainFrm;
float	g_fUnOnPowLimit			= 1;

BOOL	g_bHaveArea2;
BOOL	g_bUseArea2;
int		g_iHaveBribe;
int		g_iSeleTestLamp;

CString g_strListParaName[PARA_NUM] = {	"SDCM", "电流(mA)", "电压(V)", "频率(Hz)", "功率(W)", "功率因数", 
										"Flux(lm)", "Tc(K)","CIE-x", "CIE-y","CIE-u'", "CIE-v'",
										"Ld(nm)", "HW(nm)", "Lp(nm)","Ip", "Pur(%)", "Ra","Eff(lm/W)",
										"R1","R2","R3","R4","R5","R6","R7","R8","R9",
										"红色比","绿色比","蓝色比","安规"};

BOOL	g_bListPara[PARA_NUM];
CString g_strTestSettingFileName;
BOOL	g_bCorrectPh;   
float	g_fCorrectPhK0dot2nm[4096];

CString GetCalProtectPassword()
{
    CString strSection = "Password";
    return AfxGetApp()->GetProfileString(strSection, "CalibrationProtectVoltage", "123456");
}

BOOL SetCalProtectPassword(CString strPassword)
{
    CString strSection = "Password";
    return AfxGetApp()->WriteProfileString(strSection, "CalibrationProtectVoltage", strPassword);
}

CString GetAdminExcutionPassword()
{
    CString strSection = "Password";
    return AfxGetApp()->GetProfileString(strSection, "AdminExcutionPassword", "EVERFINE_EVERFINE");
}

BOOL SetAdminExcutionPassword(CString strPassword)
{
    CString strSection = "Password";
    return AfxGetApp()->WriteProfileString(strSection, "AdminExcutionPassword", strPassword);
}

CString GetHighExcutionPassword()
{
    CString strSection = "Password";
    return AfxGetApp()->GetProfileString(strSection, "HighExcutionPassword", "123456");
}

BOOL SetHighExcutionPassword(CString strPassword)
{
    CString strSection = "Password";
    return AfxGetApp()->WriteProfileString(strSection, "HighExcutionPassword", strPassword);
}


BOOL Haas1200CorrectColor(CNewTestColorData &data)
{
    float fdx = 0, fdy = 0;
    float fLp = 0, fRa = 0;
    float fPhK = 1.0f, fPheK = 1.0f;

    if (NewCorrectColorParaDLL_GetCorrectdXdY(fdx, fdy))
    {
        float fPrecision = 0.000001f;
        if (fdx <= fPrecision * (-1) || fdx >= fPrecision ||
            fdy <= fPrecision * (-1) || fdy >= fPrecision)
        {
            data.m_fCIEx += fdx;
            data.m_fCIEy += fdy;
            data.m_fCIEu_ = (4 * data.m_fCIEx) / (-2 * data.m_fCIEx + 12 * data.m_fCIEy + 3);
            data.m_fCIEv_ = (9 * data.m_fCIEy) / (-2 * data.m_fCIEx + 12 * data.m_fCIEy + 3);

            float fU_, fV_, fTc;
            g_Hass1200Meter.SetCIEXYReCalculate(data.m_fCIEx, data.m_fCIEy, fU_, fV_, fTc);
            data.m_fTc = fTc;
        }
    }

    if (NewCorrectColorParaDLL_GetCorrectdLp(fLp))
    {
        data.m_fLp += fLp;
    }

    if (NewCorrectColorParaDLL_GetCorrectRa(fRa))
    {
        data.m_fRa += fRa;
    }

    if (NewCorrectColorParaDLL_GetCorrectPhK(fPhK))
    {
        data.m_fPh *= fPhK;
    }

    if (NewCorrectColorParaDLL_GetCorrectPheK(fPheK))
    {
        data.m_fPh_e *= fPheK;
    }

    return TRUE;
}

// CLAT2000App

BEGIN_MESSAGE_MAP(CLAT2000App, CWinAppEx)
    ON_COMMAND(ID_APP_ABOUT, &CLAT2000App::OnAppAbout)
    // 基于文件的标准文档命令
    ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
    ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
    // 标准打印设置命令
    ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()


// CLAT2000App 构造

BOOL ReadPassFile(CString strPathName)
{
    CFile file;
    if (!file.Open(strPathName, CFile::modeRead))
    {
        return FALSE;
    }

    int iLength = (int)file.GetLength();
    CString strTemp, strTemp2;

    strTemp.GetBufferSetLength(iLength + 1);
    file.Read(strTemp.GetBuffer(), iLength);


    int iIndex = 0;
    iIndex = strTemp.Find("Debug:", iIndex);
    if (-1 != iIndex)
    {
        strTemp2 = strTemp.Mid(iIndex, 32);
        sscanf_s(strTemp2, "Debug:%d", &g_bDebug);
    }

    iIndex = iIndex > 0? iIndex + 1 : 0;
    iIndex = strTemp.Find("Dark AD:", iIndex);
    if (-1 != iIndex)
    {
        strTemp2 = strTemp.Mid(iIndex, 32);
        sscanf_s(strTemp2, "Dark AD:%d", &g_iDarkAD);
    }

    iIndex = iIndex > 0? iIndex + 1 : 0;
    iIndex = strTemp.Find("Statistic:", iIndex);
    if (-1 != iIndex)
    {
        strTemp2 = strTemp.Mid(iIndex, 32);
        sscanf_s(strTemp2, "Statistic:%d", &g_bStatistic); //统计窗口开放
    }
    iIndex = iIndex > 0? iIndex + 1 : 0;
    iIndex = strTemp.Find("Column:", iIndex);
    if (-1 != iIndex)
    {
        strTemp2 = strTemp.Mid(iIndex, 32);
        sscanf_s(strTemp2, "Column:%d", &g_iColomnNum);
    }
    iIndex = iIndex > 0? iIndex + 1 : 0;
    iIndex = strTemp.Find("Row:", iIndex);
    if (-1 != iIndex)
    {
        strTemp2 = strTemp.Mid(iIndex, 32);
        sscanf_s(strTemp2, "Row:%d", &g_iRowNum);
    }
    iIndex = iIndex > 0? iIndex + 1 : 0;
    iIndex = strTemp.Find("Row:", iIndex);
    if (-1 != iIndex)
    {
        strTemp2 = strTemp.Mid(iIndex, 32);
        sscanf_s(strTemp2, "Row:%d", &g_iRowNum);
    }
    strTemp.ReleaseBuffer();
    iIndex = iIndex > 0? iIndex + 1 : 0;
    iIndex = strTemp.Find("UnOnPopedom:", iIndex);
    if (-1 != iIndex)
    {
        strTemp2 = strTemp.Mid(iIndex, 32);
        sscanf_s(strTemp2, "UnOnPopedom:%d", &g_bUnOnPopedom);
    }
    strTemp.ReleaseBuffer();

	iIndex = iIndex > 0? iIndex + 1 : 0;
	iIndex = strTemp.Find("HaveArea2:", iIndex);
	if (-1 != iIndex)
	{
		strTemp2 = strTemp.Mid(iIndex, 32);
		sscanf_s(strTemp2, "HaveArea2:%d", &g_bHaveArea2);
	}
	strTemp.ReleaseBuffer();
	
	iIndex = iIndex > 0? iIndex + 1 : 0;
	iIndex = strTemp.Find("HaveBribe2:", iIndex);
	if (-1 != iIndex)
	{
		strTemp2 = strTemp.Mid(iIndex, 32);
		sscanf_s(strTemp2, "HaveBribe2:%d", &g_iHaveBribe);
	}
	strTemp.ReleaseBuffer();

	file.Close();

    return TRUE;
}


float NewInt_float(float *xa, float *ya, int n, float x)
{
    //牛顿插值

    int i, k;
    float u;
    k=1;
    for(i=1; i<=n-2; i++)
    {
        if( x <= xa[i] )
        {
            k=i;
            break;
        }
        else
            k=n-1;
    }
    u=(x-xa[k-1])/(xa[k]-xa[k-1]);
    return ya[k-1]+u*(ya[k]-ya[k-1]);
}


BOOL ReadCorrectSpectrumFile(CString strPathName)
{
    FILE *fp;
    float m_Wavelength[401];
    float m_CorrectK[401];
    int iNum = 0;
    if (fopen_s(&fp, strPathName, "rt"))
    {
        return FALSE;
    }
    else
    {
        float fWaveLength, fCorrectK;
        while(1)
        {
            fscanf_s(fp, "CorrectPh:%d\n", &g_bCorrectPh);
            fscanf_s(fp, "%g %g\n", &fWaveLength, &fCorrectK);
            if (fWaveLength == -1.0f && fCorrectK == -1.0f)
            {
                break;
            }
            m_Wavelength[iNum] = fWaveLength;
            m_CorrectK[iNum] = fCorrectK;   
            iNum ++;
        }
        float fWL1 = g_Hass1200Meter.GetWL_Range1();
        float fWL2 = g_Hass1200Meter.GetWL_Range2();
        int iPhCorrNum = int((g_Hass1200Meter.GetWL_Range2() - g_Hass1200Meter.GetWL_Range1()) / 0.2f + 1 + 0.5f);
        for (int i = 0; i < iPhCorrNum; i ++)
        {
            float fWL = g_Hass1200Meter.GetWL_Range1() + 0.2f * i;
            g_fCorrectPhK0dot2nm[i] = NewInt_float(m_Wavelength, m_CorrectK, iNum, fWL); 
        }

        fclose(fp);
        return TRUE;
    }
    return TRUE;
}


CLAT2000App::CLAT2000App()
{
    m_bHiColorIcons = TRUE;

    // 支持重新启动管理器
    m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
    // 如果应用程序是利用公共语言运行时支持(/clr)构建的，则:
    //     1) 必须有此附加设置，“重新启动管理器”支持才能正常工作。
    //     2) 在您的项目中，您必须按照生成顺序向 System.Windows.Forms 添加引用。
    System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

    // TODO: 将以下应用程序 ID 字符串替换为唯一的 ID 字符串；建议的字符串格式
    //为 CompanyName.ProductName.SubProduct.VersionInformation
    SetAppID(_T("Everfine.LAT2000.V1.00"));

    // TODO: 在此处添加构造代码，
    // 将所有重要的初始化放置在 InitInstance 中

    char Path[256];
    GetModuleFileName(NULL,Path,250);
    * ( strrchr( Path, '\\' ) + 1 ) = '\0';
    g_strCurrentPath = Path;

    g_strLimitDataPath = g_strCurrentPath + "LED Limit\\";
    CreateDirectory(g_strLimitDataPath, NULL);

    g_strRectificationPath = g_strCurrentPath + "Rectification\\";
    CreateDirectory(g_strRectificationPath, NULL);

    g_strHistoryDataPath = g_strCurrentPath + "History Data\\";
    CreateDirectory(g_strHistoryDataPath, NULL);

    g_ThunderRelayComm.SetAddress(0xEE, 0xBF);
	g_TestChannelControlComm.SetAddress(0xEE, 0xBF);

    ReadPassFile(g_strCurrentPath + "LatSuite.pas");

	//注意 老版的仪器地址码不能修改
	if (1)
	{
	}
	g_BribeComm.SetAddress(0xEE, 0xCF);
    g_bCorrectPh = FALSE;
}

// 唯一的一个 CLAT2000App 对象

CLAT2000App theApp;


// CLAT2000App 初始化

BOOL DoEXE(CString strPathName)
{
    STARTUPINFO StartupInfo = {0};
    PROCESS_INFORMATION ProcessInfo;
    StartupInfo.cb = sizeof(STARTUPINFO);
    CString m_sExePath = strPathName;
    char a[256];
    int iN;
    iN = m_sExePath.GetLength();
    int i = 0;
    for(i = 0; i < iN; i++)
    {
        a[i] = m_sExePath.GetAt(i);
    }

    a[i] = '\0';
    if(CreateProcess(NULL,a,NULL,NULL,FALSE,0,NULL,NULL,&StartupInfo,&ProcessInfo))
    {
        WaitForSingleObject(ProcessInfo.hProcess,INFINITE);
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

BOOL CLAT2000App::InitInstance()
{
    HANDLE hMutex=::CreateMutex(NULL,TRUE,"LatSuite");
    if(hMutex)
    {
        if(::GetLastError()==ERROR_ALREADY_EXISTS)
        {
            if (g_bEnglish)
            {
                AfxMessageBox("LatSuite is running!");
            }
            else
            {
                AfxMessageBox("LatSuite 软件正在运行!");
            }
			exit(0);
            return FALSE;//do not start this instance
        }
    }

    // 如果一个运行在 Windows XP 上的应用程序清单指定要
    // 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
    //则需要 InitCommonControlsEx()。否则，将无法创建窗口。
    INITCOMMONCONTROLSEX InitCtrls;
    InitCtrls.dwSize = sizeof(InitCtrls);
    // 将它设置为包括所有要在应用程序中使用的
    // 公共控件类。
    InitCtrls.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&InitCtrls);

    CWinAppEx::InitInstance();


    // 初始化 OLE 库
    if (!AfxOleInit())
    {
        AfxMessageBox(IDP_OLE_INIT_FAILED);
        return FALSE;
    }

    AfxEnableControlContainer();

    EnableTaskbarInteraction(FALSE);

    // 使用 RichEdit 控件需要  AfxInitRichEdit2()	
    // AfxInitRichEdit2();

    // 标准初始化
    // 如果未使用这些功能并希望减小
    // 最终可执行文件的大小，则应移除下列
    // 不需要的特定初始化例程
    // 更改用于存储设置的注册表项
    // TODO: 应适当修改该字符串，
    // 例如修改为公司或组织名
    SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
    LoadStdProfileSettings(4);  // 加载标准 INI 文件选项(包括 MRU)

    InitContextMenuManager();

    InitKeyboardManager();

    InitTooltipManager();
    CMFCToolTipInfo ttParams;
    ttParams.m_bVislManagerTheme = TRUE;
    theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
        RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

    // 注册应用程序的文档模板。文档模板
    // 将用作文档、框架窗口和视图之间的连接
    CSingleDocTemplate* pDocTemplate;
    pDocTemplate = new CSingleDocTemplate(
        IDR_MAINFRAME,
        RUNTIME_CLASS(CLAT2000Doc),
        RUNTIME_CLASS(CMainFrame),       // 主 SDI 框架窗口
        RUNTIME_CLASS(CMainTabWnd));
    if (!pDocTemplate)
        return FALSE;
    AddDocTemplate(pDocTemplate);


    // 分析标准 shell 命令、DDE、打开文件操作的命令行
    CCommandLineInfo cmdInfo;
    ParseCommandLine(cmdInfo);

    CSplashWnd::EnableSplashScreen(cmdInfo.m_bShowSplash);

    // 启用“DDE 执行”
    EnableShellOpen();
    RegisterShellFileTypes(TRUE);

    if(1)
    {
        CString strSection = "Reg";
        CString strFlag = "Flag";
        int iFlag = AfxGetApp()->GetProfileInt(strSection, strFlag, 12345);
        if(iFlag == 12345)
        {
            SetCurrentDirectory(g_strCurrentPath + "Controls\\Iocomp\\");
            DoEXE(g_strCurrentPath + "Controls\\Iocomp\\RegIocomp.bat");

            AfxGetApp()->WriteProfileInt(strSection, strFlag, 0);
        }

    }

    HINSTANCE hocx;
    hocx = ::LoadLibrary(_T("Controls\\NTGraph.ocx"));
    if(hocx!=NULL)
    {
        FARPROC lpfn=::GetProcAddress(hocx,_T("DllRegisterServer"));
        if(lpfn!=NULL)
        {
            (*lpfn)();
        }
        ::FreeLibrary(hocx);
    }

    hocx = ::LoadLibrary(_T("Controls\\FlexCell.ocx"));
    if(hocx!=NULL)
    {
        FARPROC lpfn=::GetProcAddress(hocx,_T("DllRegisterServer"));
        if(lpfn!=NULL)
        {
            (*lpfn)();
        }

        ::FreeLibrary(hocx);
    }

    hocx = ::LoadLibrary(_T("Controls\\NTGraph.ocx"));
    if(hocx!=NULL)
    {
        FARPROC lpfn=::GetProcAddress(hocx,_T("DllRegisterServer"));
        if(lpfn!=NULL)
        {
            (*lpfn)();
        }
        ::FreeLibrary(hocx);
    }

    hocx = ::LoadLibrary(_T("Controls\\AX_CIE_XYZ.ocx"));
    if(hocx!=NULL)
    {
        FARPROC lpfn=::GetProcAddress(hocx,_T("DllRegisterServer"));
        if(lpfn!=NULL)
        {
            (*lpfn)();
        }
        ::FreeLibrary(hocx);
    }

    hocx = ::LoadLibrary(_T("Controls\\AX_SpectrumDraw.ocx"));
    if(hocx!=NULL)
    {
        FARPROC lpfn=::GetProcAddress(hocx,_T("DllRegisterServer"));
        if(lpfn!=NULL)
        {
            (*lpfn)();
        }
        ::FreeLibrary(hocx);
    }

	if (1)
	{
		//读取产品授权码
		int i;
		char cModel[256];
		char cSN[256];
		CString strModel;
		strModel = "LatSuite";
		for (i = 0; i < strModel.GetLength(); i++)
		{
			cModel[i] = strModel.GetAt(i);
		}
		cModel[i] = 0;

		CString strSN;
		strSN = "EVERFINE_EVERFINE_SN";

		for (i = 0; i < strSN.GetLength(); i++)
		{
			cSN[i] = strSN.GetAt(i);
		}
		cSN[i] = 0;

		int iR;
		iR = EVER_Lincese(cModel, cSN);
		if (iR != 0)
		{
			if (iR == -1)
			{
				AfxMessageBox("未读取到授权文件,请联系远方公司!");
			}
			if (iR == 1)
			{
				AfxMessageBox("授权文件 产品型号不匹配,请联系远方公司!");
			}
			if (iR == 2)
			{
				AfxMessageBox("授权文件 产品编号不匹配,请联系远方公司!");
			}
			if (iR == 3)
			{
				AfxMessageBox("产品授权起始时间和电脑不匹配,请联系远方公司!");
			}
			if (iR == 4)
			{
				AfxMessageBox("产品授权已过期,请联系远方公司!");
			}
			if (iR == 5)
			{
				AfxMessageBox("产品授权已过期,请联系远方公司!");
			}
			//关闭软件
			return FALSE;
		}
	}


	if (g_iHaveBribe == 2)
	{
		//选择打点灯
		CDlgSeleLamp dlg;
		dlg.m_iSeleTestLamp = g_iSeleTestLamp;
		if(IDCANCEL == dlg.DoModal())
		{
			return FALSE;
		}
		g_iSeleTestLamp = dlg.m_iSeleTestLamp;

		if (g_iSeleTestLamp == 1)
		{
			g_iColomnNum	= 3;
			g_iRowNum		= 2;
		}
	}

	if(g_bHaveArea2)
	{
		CDlgControlShow dlg;
		if(IDCANCEL == dlg.DoModal())
		{
			return FALSE;
		}
		if (dlg.m_iSeleControl == 0)
		{
			g_bUseArea2 = FALSE;
		}
		else
		{
			g_bUseArea2 = TRUE;
		}
	}

    CAccountDlg dlg;
    if(IDCANCEL == dlg.DoModal())
    {
        return FALSE;
    }
    g_iExecutionLevel = dlg.m_iExecutionLevel;
    if (TRUE == g_bDebug)
    {
        g_iExecutionLevel = ADMIN_EXECUTION_LEVEL;
    }
    // 调度在命令行中指定的命令。如果
    // 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
    if (!ProcessShellCommand(cmdInfo))
        return FALSE;

    // 唯一的一个窗口已初始化，因此显示它并对其进行更新
    m_pMainWnd->ShowWindow(SW_SHOW);
    m_pMainWnd->UpdateWindow();
    // 仅当具有后缀时才调用 DragAcceptFiles
    //  在 SDI 应用程序中，这应在 ProcessShellCommand 之后发生
    // 启用拖/放
    m_pMainWnd->DragAcceptFiles();

    return TRUE;
}

int CLAT2000App::ExitInstance()
{
    //TODO: 处理可能已添加的附加资源
    AfxOleTerm(FALSE);

    CleanState();
    return CWinAppEx::ExitInstance();
}

// CLAT2000App 消息处理程序


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
    CAboutDlg();

    // 对话框数据
    enum { IDD = IDD_ABOUTBOX };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

    // 实现
protected:
    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnPaint();
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
    ON_WM_PAINT()
    ON_WM_CREATE()
END_MESSAGE_MAP()

// 用于运行对话框的应用程序命令
void CLAT2000App::OnAppAbout()
{
    CString strNote;
    AboutDll_SetLang(LANG_CN);
    AboutDll_SetString(ABOUT_NAME, "LatSuite 远方LED灯自动老炼测试线软件");
    AboutDll_SetString(ABOUT_VER, "版本:  V1.00.111");
    AboutDll_SetString(ABOUT_COMPANY, "版权所有 2002-2014 杭州远方光电信息股份有限公司");
    AboutDll_SetString(ABOUT_COPYRIGHT, "保留所有权利.");

    AboutDll_SetString(ABOUT_ADD_NOTE, "中文版.");
    strNote.ReleaseBuffer();

    AboutDll_ShowAboutDlg();
}

// CLAT2000App 自定义加载/保存方法

void CLAT2000App::PreLoadState()
{
    BOOL bNameValid;
    CString strName;
    bNameValid = strName.LoadString(IDS_EDIT_MENU);
    ASSERT(bNameValid);
    GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CLAT2000App::LoadCustomState()
{
}

void CLAT2000App::SaveCustomState()
{
}

// CLAT2000App 消息处理程序





void CAboutDlg::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    // TODO: 在此处添加消息处理程序代码
    // 不为绘图消息调用 CDialogEx::OnPaint()
}


int CAboutDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CDialogEx::OnCreate(lpCreateStruct) == -1)
        return -1;

    // TODO:  在此添加您专用的创建代码
    return 0;
}


CDocument* CLAT2000App::OpenDocumentFile(LPCTSTR lpszFileName)
{
    // TODO: 在此添加专用代码和/或调用基类

    return CWinAppEx::OpenDocumentFile(lpszFileName);
}


BOOL CLAT2000App::PreTranslateMessage(MSG* pMsg)
{
    // TODO: 在此添加专用代码和/或调用基类
    if (CSplashWnd::PreTranslateAppMessage(pMsg))
        return TRUE;
    return CWinAppEx::PreTranslateMessage(pMsg);
}
