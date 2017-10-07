#pragma once

#include "LedData.h"
#include "AlarmSettingsData.h"
#include "AlarmRingData.h"

#define DATA_CAHNNEL_NUM 10  //通道

struct LimitStruct
{
    BOOL  m_bCheckJudge;
    int   m_iCurPara;
    float m_fLimitVal;
    // Upper
    float m_fLimitVal_Offset1;
    // Lower
    float m_fLimitVal_Offset2;
    LimitStruct()
    {
        m_bCheckJudge = FALSE;
        m_iCurPara = 0;
        m_fLimitVal = 5;
        m_fLimitVal_Offset1 = 5;
        m_fLimitVal_Offset2 = 5;
    }
    LimitStruct & operator = (LimitStruct &data)
    {
        if (this == &data)
        {
            return  * this;
        }
       m_bCheckJudge = data.m_bCheckJudge;
       m_iCurPara = data.m_iCurPara;
       m_fLimitVal = data.m_fLimitVal;
       m_fLimitVal_Offset1 = data.m_fLimitVal_Offset1;
       m_fLimitVal_Offset2 = data.m_fLimitVal_Offset2;
       return * this;
    }
    void Serialize(CArchive & ar)
    {
        if (ar.IsStoring())
        {
           ar << m_bCheckJudge;
           ar << m_iCurPara;
           ar << m_fLimitVal;
           ar << m_fLimitVal_Offset1;
           ar << m_fLimitVal_Offset2;
        }
        else
        {
            ar >> m_bCheckJudge;
            ar >> m_iCurPara;
            ar >> m_fLimitVal;
            ar >> m_fLimitVal_Offset1;
            ar >> m_fLimitVal_Offset2;
        }
    }
};

class CTestSettingsData
{
public:
	typedef enum CHECK_FLAG
	{
		CHECK_FLUX				= 0x00000001,
		CHECK_HW				= 0x00000002,
		CHECK_LD				= 0x00000004,
		CHECK_LP				= 0x00000008,
		CHECK_NAGETIVECURRENT	= 0x00000010,
		CHECK_NAGETIVEVOLTAGE	= 0x00000020,
		CHECK_POSITIVECURRENT	= 0x00000040,
		CHECK_POSITIVEVOLTAGE	= 0x00000080,
		CHECK_PUR				= 0x00000100,
		CHECK_RA				= 0x00000200,
		CHECK_TC				= 0x00000400,
		CHECK_U					= 0x00000800,
		CHECK_V					= 0x00001000,
		CHECK_X					= 0X00002000,
		CHECK_Y					= 0X00004000,
		CHECK_LUMINOUS_POWER	= 0X00008000,
        CHECK_P                 = 0X00010000,
        CHECK_PF                = 0X00020000,
        CHECK_FRE               = 0X00040000,
        CHECK_R1                = 0X00080000,
        CHECK_R2                = 0X00100000,
        CHECK_R3                = 0X00200000,
        CHECK_R4                = 0X00400000,
        CHECK_R5                = 0X00800000,
        CHECK_R6                = 0X01000000,
        CHECK_R7                = 0X02000000,
        CHECK_R8                = 0X04000000,
        CHECK_R9                = 0X08000000,
        CHECK_RR                = 0X10000000,
        CHECK_GR                = 0X20000000,
        CHECK_BR                = 0X40000000,

	}_CHECK_FLAG;

public:
	CTestSettingsData(void);
	~CTestSettingsData(void);

	BOOL IsQulified(CLedData & data,int &iTypeFail);
	BOOL IsQulified(int iCurPara, float fValue);

	BOOL Store(CString strPathName);
	BOOL Load(CString strPathName);
	BOOL Serialize(CArchive & ar);
	CTestSettingsData & operator = (CTestSettingsData & data);

    CTestSettingsData &LimitEqual(CTestSettingsData & data);
public:
	float m_fIntegralTimems;
	float m_fWarmUpTimems;
	float m_fTestFrquencyHz;
	float m_fTestVoltageV;

	int m_iRangeCF;
	int m_iRangeI;
	int m_iRangeU;
	
	int m_iEMC5ASelectIndex;
	int m_iEMC11KSelectIndex;
	
	int m_iBurnInONSeconds;
	int m_iBurnInOFFSeconds;
	
	BOOL  m_pbTestChannel[DATA_CAHNNEL_NUM];
	BOOL  m_pbThunderChannel[DATA_CAHNNEL_NUM];
	float m_pfLuminosityK[DATA_CAHNNEL_NUM];
	float m_pfStandardFlux[DATA_CAHNNEL_NUM];
	float m_pfTestFlux[DATA_CAHNNEL_NUM];
	float m_pfTestFlux2[DATA_CAHNNEL_NUM];

	UINT32 m_ui32Flag;
	CAlarmSettingsData m_AlarmSettingsData;
	CAlarmRingData	m_AlarmRingData;

public:
	float m_fLimitFlux;
	float m_fOffsetFlux;	// +
	float m_fOffsetFlux_;	// -

	float m_fLimitHW;
	float m_fOffsetHW;
	float m_fOffsetHW_;
	
	float m_fLimitLd;
	float m_fOffsetLd;
	float m_fOffsetLd_;
	
	float m_fLimitLp;
	float m_fOffsetLp;
	float m_fOffsetLp_;
	
    float m_fLimitPositiveCurrent;
    float m_fOffsetPositveCurrent;
    float m_fOffsetPositveCurrent_;

    float m_fLimitPositiveVoltage;
    float m_fOffsetPositiveVoltage;
    float m_fOffsetPositiveVoltage_;

	float m_fLimitPur;
	float m_fOffsetPur;
	float m_fOffsetPur_;

	float m_fLimitRa;
	float m_fOffsetRa;
	float m_fOffsetRa_;

	float m_fLimitTc;
	float m_fOffsetTc;
	float m_fOffsetTc_;

    float m_fLimitX;
    float m_fOffsetX;
    float m_fOffsetX_;

    float m_fLimitY;
    float m_fOffsetY;
    float m_fOffsetY_;

    float m_fLimitU;
    float m_fOffsetU;
    float m_fOffsetU_;

    float m_fLimitV;
    float m_fOffsetV;
    float m_fOffsetV_;
	
	float m_fLimitLuminousPower;
	float m_fOffsetLuminousPower;
	float m_fOffsetLuminousPower_;

	float   m_fBallHigh;
	CString m_strDateTime;
	CString m_strLedModel;
	CString m_strPersonName;
	CString m_strRemarks;


    float m_fLimitPow;
    float m_fOffsetPow;
    float m_fOffsetPow_;

    float m_fLimitPowFactor;
    float m_fOffsetPowFactor;
    float m_fOffsetPowFactor_;

    float m_fLimitFre;
    float m_fOffsetFre;
    float m_fOffsetFre_;

    BOOL m_bTestLightning;			//雷击测试标志
    BOOL m_bTestVoltageUpAndDips;	//跌落测试标志
    BOOL m_bTestBurnIn;				//开关老炼标志
	BOOL m_bTestAutoHand;
    int m_iTestMinSeconds;			//测试时间设置
    BOOL m_bTestDirectionOpposite;	//测试顺序反的标志
	//
	BOOL	m_bTestSaft; //安规的三个标志合一
	int		m_iTypeNYY; // 0:AC 1:DC
	float	m_fSetVolNYY;
	float	m_fSetTimeNYY;
	float	m_fNYYLimit;
	float	m_fSetVolJYDZ;
	float   m_fSetTimeJYDZ;
	float	m_fJYDZLimit;
	float	m_fSetVolXLDL;
	float	m_fSetTimeXLDL;
	float	m_fXLDLLimit;

	//漫游参数设置
	BOOL m_bTestMyLast;
	CArray<float, float> m_fVolMyLast;
	CArray<float, float> m_fFreqMyLast;
	CArray<int, int> m_iTimeMyLast;

    float m_fLimitR9;
    float m_fOffsetR9;
    float m_fOffsetR9_;

    CArray<LimitStruct, LimitStruct>m_Limit;
    void Relist(CListCtrl &cList, BOOL bCanCheck);
    void AddtoLimit(LimitStruct &ParaLimit);
    int ModifytoLimit(LimitStruct &ParaLimit);
    int GetAllTestChannelNum();

    float m_fStaPow;
    float m_fStaFlux;
    float m_fStaTc;
    float m_fStaVol;

    float m_fLEDUnOnPow;
    float m_fLEDUnOnFlux;


};

