
// LAT2000.h : LED850 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

extern float	g_fUnOnPowLimit;

#include "resource.h"       // 主符号
#include "Haas1200Meter.h"		// 1.A90(USB)
#include "DPSPowerComm.h"		// 3.DPS1020
#include "GaugeComm.h"			// 4.Gauge
#include "SC1000Comm.h"			// 5.SC1000
#include "ExNewPowDLL.h"		// 6.PF2010A
#include "IndicatorComm.h"		// 7.Indicator
#include "ExEmc5AMeterDLL.h"	// 8.EMS61000-5A
#include "ExEmc11kMeterDLL.h"	// 9.EMS61000-11K
#include "LRAComm.h"
#include "BribeComm.h"
#include "ThunderRelayComm.h"
#include "FujiTMPComm.h"
#include "LineControllerComm.h"
#include "ScanerComm.h"
#include "HLS-200DLLComm.h"
#include "SafetyTestComm.h"
#include "ContNyyComm.h"
#include "ContJydzComm.h"
#include "ContXldlComm.h"
#include "HandAutoComm.h"
#include "Ex_TouchSrceenDLL.h"
#include "Ex_SDCM_DLL.h"


extern  int		g_iExecutionLevel;
extern BOOL		g_bDisplayLimitOnly;
extern BOOL		g_bhaveSaveFile;


enum ExecutionLevelType
{
    LOW_EXECUTION_LEVEL,
    HIGH_EXECUTION_LEVEL,
    ADMIN_EXECUTION_LEVEL
};

#include "ExWYDll.h"			// 10.WY305

#define MSG_TEST_STARTED					(WM_USER + 0x0001)		// Post when test started
#define MSG_LED_RELIST						(WM_USER + 0x0002)		// Post when LED number changed
#define MSG_TEST_ENDED						(WM_USER + 0x0003)		// Post by the three test thread when test ended
#define MSG_REGION_RELIST					(WM_USER + 0x0004)		// When region data has been changed
#define MSG_LIMIT_FILE_RELIST				(WM_USER + 0x0005)		// Limit file in the combo box of test form view need to be update
#define MSG_DATA_CONTAINER_DRAW				(WM_USER + 0x0006)		// Post when grid control selected row changed
#define MSG_GRID_EXPORT_DATA				(WM_USER + 0x0007)
#define MSG_GRID_RELIST_DATA				(WM_USER + 0x0008)
#define MSG_CONTAINER_DRAW_PRINT			(WM_USER + 0x0009)
#define MSG_MAINTABVIEW_RELIST				(WM_USER + 0x000A)
#define MSG_DOCKABLE_PANE_UPDATE_INFO		(WM_USER + 0x000B)
#define MSG_SHOW_NONE_BRODER_MESSAGE		(WM_USER + 0x000C)
#define MSG_STATISTIC_GRID_RELIST_DATA		(WM_USER + 0x000D)
#define MSG_STATISTIC_DIS_GRID_RELIST_DATA  (WM_USER + 0x000E)
#define MSG_SAVE_CSV_DATA					(WM_USER + 0x000F)
#define MSG_DOCKABLE_PANE_UPDATE_TMP		(WM_USER + 0x0011)




#define  PARA_NUM                       32


// CLAT2000App:
// 有关此类的实现，请参阅 LED850.cpp
//

class CLAT2000App : public CWinAppEx
{
public:
	CLAT2000App();

// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual CDocument* OpenDocumentFile(LPCTSTR lpszFileName);
    virtual BOOL PreTranslateMessage(MSG* pMsg);
};


extern CLAT2000App		theApp;

// Communication instance
extern CHaas1200Meter	 g_Hass1200Meter;
extern CDPSPowerComm	 g_DPSComm;
extern CDPSPowerComm	 g_DPSComm_MyLast;
extern CDPSPowerComm	 g_DPSAgeComm[2];
extern CGaugeComm		 g_GaugeComm;

extern CSC1000Comm		 g_SC1000Comm;
extern CLRAComm			 g_TestChannelControlComm;	// 0xBF

extern CPowerMeterComm		g_PowerMeterComm;
extern CIndicatorComm		g_IndicatorComm;
extern CEMS61000_5AComm		g_EMS61000_5AComm;
extern CEMS61000_11KComm	g_EMS61000_11KComm;
extern CWYComm				g_WYComm;
extern CHLS_200				g_HLS_200;

extern CLRAComm				g_LRAComm;				// 0xAF
extern CThunderRelayComm	g_ThunderRelayComm;		// 0xBF
extern CBribeComm			g_BribeComm;			// 0xCF
extern CContNyyComm			g_ContNyyComm;			// 0xBF 单片机程序同雷击 仅串口不太
extern CContJydzComm		g_ContJydzComm;			// 0xBF 单片机程序同雷击 仅串口不太
extern CContXldlComm		g_ContXldlComm;			// 0xBF 单片机程序同雷击 仅串口不太

extern CFujiTMPComm			g_FujiTMPComm;
extern CLineControllerComm	g_LineControllerComm;
extern CHandAutoComm		g_HandAutoComm;
extern CScanerComm			g_ScanerComm;
extern CExTouchSrceenComm	g_TSrceenComm;

extern CSafetyTest_CSComm2676 g_SafetyTest_CS2676Comm;
extern CSafetyTest_CSComm9912 g_SafetyTest_CS9912Comm;
extern CSafetyTest_CSComm5505 g_SafetyTest_CS5505Comm;
extern CSafetyTest_TongHui_TH2683AComm g_SafetyTest_TongHui_TH2683AComm;
extern CSafetyTest_TongHui_TH9310_20Comm g_SafetyTest_TongHui_TH9310_20Comm;

//Debug
extern BOOL	g_bDebug;
//Dark AD
extern BOOL	g_iDarkAD;
//Statistic  Right
extern BOOL	g_bStatistic;
// Colomn Num
extern int  g_iColomnNum;
// Row Num
extern int  g_iRowNum;

// UnOn Popedom
extern BOOL g_bUnOnPopedom;

// ListParaName
extern CString g_strListParaName[PARA_NUM];
// ListParaYesorNo
extern BOOL g_bListPara[PARA_NUM];

extern CString g_strTestSettingFileName;

extern HWND g_hDockablePaneDialog;

extern HWND g_hMainFrm;

// 光谱校正
extern BOOL g_bCorrectPh;


extern float g_fCorrectPhK0dot2nm[4096];

extern int g_iGaugeNum;
extern int g_iTMPControlNum;

extern CBrush g_brBackBlack;
extern CBrush g_brBackBlue;
extern CBrush g_brBackGreen;
extern CBrush g_brSilver;

extern COLORREF g_ColorGood;
extern COLORREF g_ColorBad;
extern COLORREF g_ColorInvalid;
extern COLORREF g_ColorNotTest;
extern COLORREF g_ColorBad_Codi;

