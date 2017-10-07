
// LAT2000Doc.h : CLAT2000Doc 类的接口
//
#pragma once
#include "TestSettingsData.h"
#include "SpectrumCommDemo.h"
#include "EditLimitDlg.h"
#include "Haas1200Meter.h"
#include "LedSpectrumData.h"
#include "RegionToolDLL.h"
#include "LEDDataContainer.h"
#include "TestContainer.h"
#include "CommSettingsData.h"
#include "IndicatorComm.h"
#include "AlarmSettingsData.h"
#include "AlarmRingData.h"
#include "StaticOtherInfo.h"
#include "DlgShowOldingTime.h"
#include "LAT2000.h"
#include "StatisticLedDataContainer.h"

#define MAX_CHANNEL_NUM	30

#define MY_FLAG_FAIL		-1
#define MY_FLAG_WAIT		0
#define MY_FLAG_OK			1
#define MY_FLAG_OVER		2
#define MY_FLAG_WY_OK		3

enum AlarmType
{
	AT_NOME				= 0,
	AT_LAMP_TOO_HIGH	= 1,
	AT_MANUAL_STOP		= 2,
	AT_TMP1				= 3,
	AT_REGION1			= 20,
    AT_SCANEROVERTIME   = 40,
};

extern CString	g_strLimitDataPath;
extern CString	g_strCurrentPath;
extern CString	g_strRectificationPath;
extern CString  g_strHistoryDataPath;


extern BOOL g_bEnglish;

struct SystemSettingsData
{
	float	m_fOldLineT_Times;
	BOOL	m_bLineNotMove;
    int		m_iCurrentLEDID;
	BOOL	m_bAutoSave;
	int		m_iSaveFileDataNum;
	CString m_strFileName;
	CString m_strFilePath;
	int		m_iStatisticMode;
    int		m_iSaveType;
    int		m_iPrefixInputMode;
    int		m_iCurrentBoardID;
    BOOL	m_bDemo;
	int		m_iLEDOnPos;
	int		m_iTestHaveScanedMode;

	void ReadRegistry()
	{
		m_bLineNotMove		= FALSE;

		CString strSection	= "SystemSettingsData";
		m_bAutoSave			= AfxGetApp()->GetProfileIntA(strSection, "m_bAutoSave", FALSE);
		m_iSaveFileDataNum	= AfxGetApp()->GetProfileIntA(strSection, "m_iSaveFileDataNum", 10000);
		m_strFileName		= AfxGetApp()->GetProfileString(strSection, "m_strFileName", "");
		m_strFilePath		= AfxGetApp()->GetProfileStringA(strSection, "m_strFilePath", "");

        CString strTemp;
        CString str_m_iCurrentLEDID		= _T("m_iCurrentLEDID");
        m_iCurrentLEDID					= AfxGetApp()->GetProfileInt(strSection, str_m_iCurrentLEDID, 1);
		CString str_m_iStatisticMode	= _T("m_iStatisticMode");
		m_iStatisticMode				= AfxGetApp()->GetProfileInt(strSection, str_m_iStatisticMode, 1);
		CString str_m_fOldLineT_Times	= _T("m_fOldLineT_Times");
		strTemp							= AfxGetApp()->GetProfileString(strSection, str_m_fOldLineT_Times, "5");
		m_fOldLineT_Times				= (float)atof(strTemp);
        CString str_m_iSaveType			= _T("m_iSaveType");
        CString str_m_iPrefixInputMode	= _T("m_iPrefixInputMode");
        m_iSaveType						= AfxGetApp()->GetProfileInt(strSection, str_m_iSaveType, 0);
        m_iPrefixInputMode				= AfxGetApp()->GetProfileInt(strSection, str_m_iPrefixInputMode, 0);
        CString str_m_iCurrentBoardID	= _T("m_iCurrentBoardID");

        m_iCurrentBoardID				= AfxGetApp()->GetProfileInt(strSection, str_m_iCurrentBoardID, 1);
		
        CString str_m_bDemo				= _T("m_bDemo");

        m_bDemo							= AfxGetApp()->GetProfileInt(strSection, str_m_bDemo, 0);
		CString str_m_iLEDOnPos			= _T("m_iLEDOnPos");
		m_iLEDOnPos						= AfxGetApp()->GetProfileInt(strSection, str_m_iLEDOnPos, 0);

		CString str_m_iTestHaveScanedMode	= _T("m_iTestHaveScanedMode");
		m_iTestHaveScanedMode				= AfxGetApp()->GetProfileInt(strSection, str_m_iTestHaveScanedMode, 0);
    }

	void WriteRegistry()
	{
		CString strSection = "SystemSettingsData";
 
		AfxGetApp()->WriteProfileInt(strSection, "m_bAutoSave", m_bAutoSave);
		AfxGetApp()->WriteProfileInt(strSection, "m_iSaveFileDataNum", m_iSaveFileDataNum);

        AfxGetApp()->WriteProfileString(strSection, "m_strFileName", m_strFileName);

		AfxGetApp()->WriteProfileStringA(strSection, "m_strFilePath", m_strFilePath);

        CString strTemp;

        CString str_m_iCurrentLEDID = _T("m_iCurrentLEDID");

        AfxGetApp()->WriteProfileInt(strSection, str_m_iCurrentLEDID, m_iCurrentLEDID);
		CString str_m_iStatisticMode = _T("m_iStatisticMode");
		AfxGetApp()->WriteProfileInt(strSection, str_m_iStatisticMode, m_iStatisticMode);	

		CString str_m_fOldLineT_Times = _T("m_fOldLineT_Times");
		strTemp.Format(_T("%g"), m_fOldLineT_Times);
		AfxGetApp()->WriteProfileString(strSection, str_m_fOldLineT_Times, strTemp);

        CString str_m_iSaveType = _T("m_iSaveType");
        CString str_m_iPrefixInputMode = _T("m_iPrefixInputMode");

        AfxGetApp()->WriteProfileInt(strSection, str_m_iSaveType, m_iSaveType);
        AfxGetApp()->WriteProfileInt(strSection, str_m_iPrefixInputMode, m_iPrefixInputMode);

        CString str_m_iCurrentBoardID = _T("m_iCurrentBoardID");

        AfxGetApp()->WriteProfileInt(strSection, str_m_iCurrentBoardID, m_iCurrentBoardID);

        CString str_m_bDemo = _T("m_bDemo");

        AfxGetApp()->WriteProfileInt(strSection, str_m_bDemo, m_bDemo);

		CString str_m_iLEDOnPos = _T("m_iLEDOnPos");
		AfxGetApp()->WriteProfileInt(strSection, str_m_iLEDOnPos, m_iLEDOnPos);

		CString str_m_iTestHaveScanedMode = _T("m_iTestHaveScanedMode");
		AfxGetApp()->WriteProfileInt(strSection, str_m_iTestHaveScanedMode, m_iTestHaveScanedMode);
    }
};
enum  Statistics_DataType
{
    DT_LEDQ,
    DT_LEDUNQ,
    DT_TESTFAIL,
    DT_LEDUNON
};

struct TestStatisticsData
{
    int m_iTotalLEDNum;
    int m_iQualifiedLEDNum;
    int m_iUnqualifiedLEDNum;
    int m_iTestFailedLEDNum;
    int m_iLEDUnONNum;
    int *m_iLastStatisticsDataType;

    TestStatisticsData()
    {
        m_iQualifiedLEDNum		= 0;
        m_iTestFailedLEDNum		= 0;
        m_iTotalLEDNum			= 0;
        m_iUnqualifiedLEDNum	= 0;
        m_iLEDUnONNum			= 0;
		m_iLastStatisticsDataType = new int[g_iColomnNum]; 
		for (int i = 0; i < g_iColomnNum; i ++)
		{
			m_iLastStatisticsDataType[i] = -1;
		}
    }

    void Reset()
    {
        m_iQualifiedLEDNum		= 0;
        m_iTestFailedLEDNum		= 0;
        m_iTotalLEDNum			= 0;
        m_iUnqualifiedLEDNum	= 0;
        m_iLEDUnONNum			= 0;
    }
    void Delete(int iDataType)
    {
        switch (iDataType)
        {
        case DT_LEDQ: 
            m_iQualifiedLEDNum --;
			break;
        case DT_LEDUNQ:
            m_iUnqualifiedLEDNum --;
			break;
        case DT_TESTFAIL:
            m_iTestFailedLEDNum --;
			break;
        case DT_LEDUNON:
            m_iLEDUnONNum --;
			break;
        default: 
            break;
        }
    }
    void Add(int iDataType)
    {
        switch (iDataType)
        {
        case DT_LEDQ: 
            AddQualified();
			break;
        case DT_LEDUNQ:
            AddUnqualified();
			break;
        case DT_TESTFAIL:
            AddTestFailed();
			break;
        case DT_LEDUNON:
            AddLEDUnON();
			break;
        default: 
            break;
        }
    }
    void  StatisticsData(CLEDDataContainer &data,int iRowChannel,int iDataType)
    {
        if (data.GetSize() >= g_iColomnNum + 1)
        {
            if (data.GetAt(data.GetSize() - 1 - g_iColomnNum).m_ulID
                == data.GetAt(data.GetSize() - 1).m_ulID)
            {
                Delete(m_iLastStatisticsDataType[iRowChannel]);
                Add(iDataType); 
            }
            else
            {
                Add(iDataType);  
            }
        }
        else
        {
            Add(iDataType);
        }
        m_iLastStatisticsDataType[iRowChannel] = iDataType;
    }

    void AddQualified()
    {
        m_iQualifiedLEDNum++;
        m_iTotalLEDNum = m_iQualifiedLEDNum + m_iUnqualifiedLEDNum + m_iTestFailedLEDNum + m_iLEDUnONNum;
    }

    void AddUnqualified()
    {
        m_iUnqualifiedLEDNum++;
        m_iTotalLEDNum = m_iQualifiedLEDNum + m_iUnqualifiedLEDNum + m_iTestFailedLEDNum + m_iLEDUnONNum;
    }
    void AddTestFailed()
    {
        m_iTestFailedLEDNum++;
        m_iTotalLEDNum = m_iQualifiedLEDNum + m_iUnqualifiedLEDNum + m_iTestFailedLEDNum + m_iLEDUnONNum;
    }

    void AddLEDUnON()
    {
        m_iLEDUnONNum++;
        m_iTotalLEDNum = m_iQualifiedLEDNum + m_iUnqualifiedLEDNum + m_iTestFailedLEDNum + m_iLEDUnONNum;
    }
};

class CLAT2000Doc : public CDocument
{
	friend class CMainTestFormView;
protected: // 仅从序列化创建
	CLAT2000Doc();                         
	DECLARE_DYNCREATE(CLAT2000Doc)

// 操作
public:
	CArray<CString,CString> m_strListCtrlFile;
	void GetCtrlFileList(CString strPathName);
    BOOL ReadFlagFile(CString strPathName);
    BOOL WriteFlagFile(CString strPathName);
    BOOL ReadWatchPaneFile(CString strPathName);
	void OnMenuSystemSettings();
	void OnMenuTest();
	BOOL IsRunning();
	BOOL IsContinueMoveOneStepRunning();
	int  GetCOM(CString strCOM);
	BOOL InitializeComm();
	BOOL IsAllDeviceConnected();
	void ShowMessageDialog(CString strInfo, AlarmType eType = AT_NOME);
	void GetCurrentData();

// 特性
public:
	int m_iHaveInLampBroadNum;//已插灯的板个数
	int m_iStartInLampBroad;	//起始插灯板号
	int m_iCurrentInLampBroad;	//起始插灯板号

	BOOL  m_bInposition;
	int m_iNumSaftR; //起始编号
	int m_iNumSaftV; //起始编号
	int m_iNumSaftC; //起始编号
	int m_iHaveBoradSaftR; //绝缘电阻已经测试了几块
	int m_iHaveBoradSaftV; //绝缘电阻已经测试了几块
	int m_iHaveBoradSaftC; //绝缘电阻已经测试了几块
	//安规数据记录
	BOOL  m_bHaveTestSaft[2000];
	BOOL  m_bSaftOK[2000]; //安规合格与否
	float m_fSaft_R[2000]; //绝缘电阻
	float m_fSaftLimit_R[2000];
	float m_fSaft_V[2000]; //耐压电流
	float m_fSaftLimit_V[2000];
	float m_fSaft_C[2000]; //泄露电流
	float m_fSaftLimit_C[2000];

    CDlgShowOldingTime *m_pShowOldTime;
	CTestContainer m_TestContainer;

	CArray<ChannelState, ChannelState> m_IndicatorColorData;
    CArray<BOOL, BOOL> m_bNotMoveLine;

	CLEDDataContainer m_dataContainer;
    CStatisticLedDataContainer m_StatisticLedDataContainer;
    int  m_iGridCurrentItem;				// Indicate which data in data container to be shown

	TestStatisticsData m_testStatisticsData;

	HWND m_hWndTestFormView;
	HWND m_hWndDataListView;
	HWND m_hWndDataContainerGridView;
    HWND m_hWndStatisticGridView;
    HWND m_hWndStatisticDisbuteGridView;

	HWND m_hWndDataContainerDrawView;
	HWND m_hWndMainTabView;

	CCommSettingsData m_CommSettingsData; //所有的通讯串口、仪器型号、功能勾选设置
	SystemSettingsData m_systemSettingsData;
	//CAlarmSettingsData m_AlarmSettingsData;	// Include in CTestSettingsData
	CAlarmRingData	m_AlarmRingData;

	int m_iTotalCountInRegion;
	int m_iPointNumberOfRegion[64];		// Stores the point number of a region, the maximum of region is 64 
	
	LineState m_lineState;
	int	m_iWaitRemainSeconds;		// -1 if ThreadTest is waiting, otherwise none negative
									// MainTestForm use this to update production line information

	CString m_strNoneBorderMsg;

	CString	m_strLimitDataFilePathName;
    void AddBoardID();
	
protected:
	static UINT ThreadTest(LPVOID pPar);
	static UINT _ThreadSpectrum(LPVOID pPar);
	static UINT _ThreadElectrical(LPVOID pPar);
	static UINT _ThreadVoltageDipsAndUP(LPVOID pPar);
	static UINT _ThreadMyLastTest(LPVOID pPar);
	static UINT _ThreadSaftJYDZTest(LPVOID pPar);
	static UINT _ThreadSaftNYYTest(LPVOID pPar);
	static UINT _ThreadSaftXLDLTest(LPVOID pPar);
	//自动上下灯控制
	static UINT _ThreadHandAutoLamp(LPVOID pPar);

	static UINT _ThreadLightningSurge(LPVOID pPar);
	
	static UINT _ThreadGauge(LPVOID pPar);
	static UINT _ThreadGaugeTMP(LPVOID pPar);

	static UINT _ThreadLineControlerMoveOneStep(LPVOID lPar);
    static UINT _ThreadScaner(LPVOID pPar);
	
private:
	BOOL m_bNeedSetTMP;
	BOOL m_bFirstTime; //
	BOOL m_bLineHaveMoved;				//产线移动标志
	BOOL m_bPauseLine;					//产线暂停标志
	BOOL m_bIsElectricalRunning;		//
	BOOL m_bIsSpectrumRunning;			//光谱仪测试中标志
	BOOL m_bIsVoltageDipsAndUPRunning;	//跌落测试标志
	BOOL m_bIsLightningSurgeRunning;	//雷击测试标志
	BOOL m_bIsLineControlRunning;		//产线控制标志
	BOOL m_bComtinueMoveRunning;		//继续标志
	BOOL m_bIsScanerRunning;			//扫码标志
	BOOL m_bIsMyLastRunning;
	BOOL m_bIsSaftJYDZRunning;			//扫码标志
	BOOL m_bIsSaftNYYRunning;			//扫码标志
	BOOL m_bIsSaftXLDLRunning;			//扫码标志
	BOOL m_bIsHandAutoRunning;			//机械手在运行标志
	
	CEvent m_eventTest;					// Manual reset to control test start or pause
	CEvent m_eventStartOne;				// Manual reset, signaled when a round of test start

	CEvent m_eventVoltageDipsAndUPEnd;	// Signaled when voltage dips and up one test end
	CEvent m_eventLightningSurgeEnd;	// Signaled when lightning surge one test end
	CEvent m_eventElectricalEnd;		// Signaled when electrical one test end
	CEvent m_eventSpectrumEnd;			// Signaled when spectrum one test end
    CEvent m_eventScanerEnd;			// Signaled when scaner one test end

	CEvent m_eventSaftJYDZEnd;			// 安规测试完成标志
	CEvent m_eventSaftNYYEnd;			// 安规测试完成标志
	CEvent m_eventSaftXLDLEnd;			// 安规测试完成标志
	CEvent m_eventHandAutoEnd;			// 安规测试完成标志

	CEvent m_eventOneLEDON;
	CEvent m_eventOneLEDSpectrumOK;

	BOOL	m_bSetStop;
	BOOL	m_bDemo;
	CString m_strInfo;

	BOOL	m_bCloseDocument;
	CWinThread * m_pThreadGauge;
    CTime	m_LastTime;

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CLAT2000Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnUpdateButtonTest(CCmdUI *pCmdUI);
	afx_msg void OnButtonEditLimit();
	afx_msg void OnButtonSpectrumCal();
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	afx_msg void OnUpdateFileSaveAs(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFileOpen(CCmdUI *pCmdUI);
	afx_msg void OnMenuStop();
	afx_msg void OnUpdateButtonPause(CCmdUI *pCmdUI);
	afx_msg void OnUpdateIndicatorTestInfo(CCmdUI *pCmdUI);
	afx_msg void OnUpdateIndicatorStatisticInfo(CCmdUI *pCmdUI);
	afx_msg void OnDebug();
	afx_msg void OnUpdateDebug(CCmdUI *pCmdUI);
	afx_msg void OnUpdateButtonSpectrumCal(CCmdUI *pCmdUI);
	afx_msg void OnUpdateModifyProtectPassword(CCmdUI *pCmdUI);
	afx_msg void OnModifyProtectPassword();
	afx_msg void OnMakeRegion();
	afx_msg void OnUpdateMakeRegion(CCmdUI *pCmdUI);
	afx_msg void OnColorOffsetEdit();
	afx_msg void OnUpdateColorOffsetEdit(CCmdUI *pCmdUI);
	afx_msg void OnColorOffsetSelect();
	afx_msg void OnUpdateColorOffsetSelect(CCmdUI *pCmdUI);
	afx_msg void OnUpdateCommSettings(CCmdUI *pCmdUI);
	afx_msg void OnCommSettings();
	afx_msg void OnUpdateButtonEditLimit(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSpectrumTest(CCmdUI *pCmdUI);
	afx_msg void OnSpectrumTest();
	afx_msg void OnAlarmRingEdit();
	afx_msg void OnResetStatistics();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	afx_msg void OnImportLastData();
	afx_msg void OnClearAllData();
	afx_msg void OnUpdateImportLastData(CCmdUI *pCmdUI);
	afx_msg void OnUpdateClearAllData(CCmdUI *pCmdUI);
	virtual void OnCloseDocument();
	afx_msg void OnStdLampInPosition();
	afx_msg void OnStatistic();
	afx_msg void OnUpdateStatistic(CCmdUI *pCmdUI);
	afx_msg void OnTestinfo();
	afx_msg void OnUpdateTestinfo(CCmdUI *pCmdUI);
	afx_msg void OnStatisticParaChoose();
	afx_msg void OnUpdateStatisticParaChoose(CCmdUI *pCmdUI);
	afx_msg void OnLineControl();
	afx_msg void OnUpdateLineControl(CCmdUI *pCmdUI);
	afx_msg void OnViewCurSetPara();
	afx_msg void OnBeforeChangeLamp();
	afx_msg void OnUpdateBeforeChangeLamp(CCmdUI *pCmdUI);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	afx_msg void OnUpdateStdLampInPosition(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAlarmRingEdit(CCmdUI *pCmdUI);
	afx_msg void OnChangeAccount();
	afx_msg void OnUpdateChangeAccount(CCmdUI *pCmdUI);
	afx_msg void OnListparaChoose();
	afx_msg void OnUpdateExportStatisticData(CCmdUI *pCmdUI);
	afx_msg void OnSeleSdcmStd();
	afx_msg void OnUpdateSeleSdcmStd(CCmdUI *pCmdUI);
};
extern CLAT2000Doc * g_pDoc;
