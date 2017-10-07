#pragma once
#include "LedData.h"
#include "MyCheckLED.h"

// CTestContainer 命令目标

enum LED_State
{
	NotTest = 0,
	Successful = 1,
	Failed = 2,
};

struct LEDState
{
	LED_State ElectricalTestState;
	LED_State SpectrumTestState;

	LEDState()
	{
		ElectricalTestState = NotTest;
		SpectrumTestState = NotTest;
	}

	BOOL IsSuccessful()
	{
		return (Successful == ElectricalTestState && Successful == SpectrumTestState);
	}

	BOOL IsTested()
	{
		return (NotTest != ElectricalTestState && NotTest != SpectrumTestState);
	}
};

struct RowLEDSN  
{
    CArray<CString, CString> m_strLEDSN; //扫码数 编码
    int m_iRowSN; //板号
    RowLEDSN()
    {
        m_iRowSN = 1;
        m_strLEDSN.RemoveAll();
    }

	~RowLEDSN()
    {

    }

    void SetRowSN(int iSN)
    {
        m_iRowSN = iSN;
    }
    int GetRowSN()
    {
        return m_iRowSN;
    }

    int GetSNNum()
    {
        return m_strLEDSN.GetSize();
    }
    void AddLEDSN(CString strSN)
    {
        m_strLEDSN.Add(strSN);
    }
    CString GetLEDSN(int iCur)
    {
        if (iCur < 0 || iCur > m_strLEDSN.GetSize() - 1)
        {
            return "";
        }
        return m_strLEDSN.GetAt(iCur);
    }
    RowLEDSN& operator = (RowLEDSN &data)
    {
        if (this == &data)
        {
            return *this;
        }
        m_iRowSN = data.m_iRowSN;
        m_strLEDSN.RemoveAll();
        for (int i = 0; i < data.m_strLEDSN.GetSize(); i ++)
        {
            m_strLEDSN.Add(data.m_strLEDSN.GetAt(i));
        }
        return *this;
    }
};
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
////上灯
struct HAND_InLamp
{
	CArray<BOOL, BOOL> m_bInLamp; //扫码数 编码
	BOOL m_bHaveInLamp;		//是否已插灯
	int m_iCurrBroad;		//当前板号
	int m_iHaveInLampNum;	//已经上灯的板总数
};
////下灯
struct HAND_OutLamp
{
	BOOL m_bHaveOutLamp;	//是否已拔灯
	int m_iCurrBroad;		//当前板号
	int m_iHaveOutLampNum;	//已经下灯的板总数
};
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

class CTestContainer : public CObject
{
public:
	CTestContainer();
	virtual ~CTestContainer();

public:
	BOOL SetLEDMatrix(int iRowCount, int iColumnCount);

	// Only the channel set to be TRUE will be tested
	BOOL SetTestChannel(BOOL bTest[]);

	void SetDirectionOpposite(BOOL bOpposite = TRUE);

public:	
	void ResetLEDState();
	void StartNewRow();
	void ResetCurrentRow();
    void ResetAllRows();  
public:
	void MoveToFirst();
	BOOL MoveToNext();
	void MoveToLast();
public:
	BOOL SetCurrentLED(int iIndex);
	void SetCurrentLEDState(LEDState state);
	void SetLEDState(int iIndex, LEDState state);
	LEDState & GetCurrentLEDState();
	int  GetCurrentLEDIndex();
	BOOL IsLEDUpdated(int iRowIndex, int iColumnIndex);
	BOOL IsOppositeDirection();
	void SetLEDUpdated(int iRowIndex, int iColumnIndex, BOOL bUpdated);
	void SetLEDUpdated(int iIndex, BOOL bUpdated);
	void SetCurrentLEDUpdated(BOOL bUpdated = FALSE);
	int GetIndex(int iRowIndex, int iColumnIndex);
	int GetLEDRowSize();
	int GetLEDColumnSize();
	int GetLEDCount();
	LEDState & GetLEDState(int iRowIndex, int iColumnIndex);
	LEDState & GetLEDState(int iIndex);
	CLedData & GetLEDData(int iRowIndex, int iColumnIndex);
	CLedData & GetLEDData(int iIndex);
	CLedData & GetCurrentLEDData();
	BOOL IsTestHalfway();
	BOOL HaveTestedLED();
	BOOL IsAllLEDTest();
	int HaveElectricalUntestedLED();
	int HaveSpectrumUntestedLED();
	CString GetInfoString(int iRowIndex, int iColumnIndex, BOOL bLedOn);

	BOOL m_bOppositeDirection;
	int m_iLEDRowCount;    //总共的测试工位数
	int m_iLEDColumnCount; //列数
	int m_iCurrentIndex;
	int m_iCurrentThunderChannel;

public:
	//以下为扫码添加的
	RowLEDSN m_tempRowLEDSN;
    RowLEDSN &GetRowLEDSN(int iIndex);
    BOOL	IsCurBoardIDInRowLEDSN(int iIndex);
    void	InsertRowLEDSN(int iIndex, RowLEDSN &data);
    int		GetRowLEDSNCount();
    BOOL	SaveALlRowLEDSNFile(CString strPathName);
    BOOL	LoadALlRowLEDSNFile(CString strPathName);
    BOOL	SerializeALlRowLEDSN(CArchive & ar);
    void	SetCurrentRowScaned(BOOL bScaned);
    BOOL	HaveLastRowLEDScaned();
	int		GetCurrentScanBoard();		//当前扫码板号
	int		GetCurrentScanIDNum();		//当前扫码板号已经扫描个数
	int		GetCurrentTestBoard();		//当前测试板号
    BOOL	CurrentTestRowIsScaned();  //测试位是否已扫码

	BOOL	CurrentTestRowIsSafted();  //测试位是否已测试过安规
	//以下为上下灯机械手添加的
	HAND_InLamp m_tempInLampLED;
	void	SetCurrentRowInLamped(BOOL bInLamped); //设置当前板上灯状态
	BOOL	HaveLastRowLEDInLamped();
	int		GetCurrentInLampBoard();	//当前上灯板号
	int		GetCurrentInLampIDNum();	//当前已上灯板数
	int		GetCurrentTest2Board();		//当前上灯后的测试板号
	BOOL	CurrentTestRowIsInLamped(); //测试位是否已上灯

    int GetCurrentTestRow(); //读取测试的位置1-10
    void SetCurrentRowNeedTest(BOOL bNeedTest);

    BOOL IsLastRowNeedTest();

 
	int GetRemoveBoard();
    void RemoveLEDDownRow();
private:
	CTime m_testTime;
	CCriticalSection m_critialUpdate;

	CArray<LEDState, LEDState> m_LEDState;
	CArray<CLedData, CLedData &> m_LEDData;
	CArray<BOOL, BOOL> m_LEDUpdated;
	CArray<BOOL, BOOL> m_ChannelNeedTest;
    CArray<RowLEDSN, RowLEDSN&> m_strRowLEDSN;

	BOOL	m_bRowScaned;	//是否已扫码
    int		m_iCurrentTestRow;
    BOOL	m_bCurrentRowNeedTest;

	BOOL	m_bRowInLamped;
};


