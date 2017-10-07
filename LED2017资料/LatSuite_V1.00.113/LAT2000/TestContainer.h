#pragma once
#include "LedData.h"
#include "MyCheckLED.h"

// CTestContainer ����Ŀ��

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
    CArray<CString, CString> m_strLEDSN; //ɨ���� ����
    int m_iRowSN; //���
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
////�ϵ�
struct HAND_InLamp
{
	CArray<BOOL, BOOL> m_bInLamp; //ɨ���� ����
	BOOL m_bHaveInLamp;		//�Ƿ��Ѳ��
	int m_iCurrBroad;		//��ǰ���
	int m_iHaveInLampNum;	//�Ѿ��ϵƵİ�����
};
////�µ�
struct HAND_OutLamp
{
	BOOL m_bHaveOutLamp;	//�Ƿ��Ѱε�
	int m_iCurrBroad;		//��ǰ���
	int m_iHaveOutLampNum;	//�Ѿ��µƵİ�����
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
	int m_iLEDRowCount;    //�ܹ��Ĳ��Թ�λ��
	int m_iLEDColumnCount; //����
	int m_iCurrentIndex;
	int m_iCurrentThunderChannel;

public:
	//����Ϊɨ����ӵ�
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
	int		GetCurrentScanBoard();		//��ǰɨ����
	int		GetCurrentScanIDNum();		//��ǰɨ�����Ѿ�ɨ�����
	int		GetCurrentTestBoard();		//��ǰ���԰��
    BOOL	CurrentTestRowIsScaned();  //����λ�Ƿ���ɨ��

	BOOL	CurrentTestRowIsSafted();  //����λ�Ƿ��Ѳ��Թ�����
	//����Ϊ���µƻ�е����ӵ�
	HAND_InLamp m_tempInLampLED;
	void	SetCurrentRowInLamped(BOOL bInLamped); //���õ�ǰ���ϵ�״̬
	BOOL	HaveLastRowLEDInLamped();
	int		GetCurrentInLampBoard();	//��ǰ�ϵư��
	int		GetCurrentInLampIDNum();	//��ǰ���ϵư���
	int		GetCurrentTest2Board();		//��ǰ�ϵƺ�Ĳ��԰��
	BOOL	CurrentTestRowIsInLamped(); //����λ�Ƿ����ϵ�

    int GetCurrentTestRow(); //��ȡ���Ե�λ��1-10
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

	BOOL	m_bRowScaned;	//�Ƿ���ɨ��
    int		m_iCurrentTestRow;
    BOOL	m_bCurrentRowNeedTest;

	BOOL	m_bRowInLamped;
};


