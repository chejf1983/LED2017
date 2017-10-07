#pragma once
#include "NewTestColorData.h"

class CLedData : public CObject
{
public:
	CLedData(void);
	~CLedData(void);

	BOOL IsValid();
	BOOL SetValid(BOOL bValid);
	void Serialize(CArchive & ar);
	CString GetInfoString(BOOL bLedOn);
	BOOL IsLEDON();

	CLedData & operator = (CLedData & data);

public:
	ULONG m_ulID;
    // dimension code 
    CString m_strSN;
    BOOL m_bNotMoveLine;
    // add
    CString m_strLedModel;

	float m_fVoltageV;
	float m_fCurrentA;
	float m_fFrequencyHz;
	float m_fPowerW;
	float m_fPowerFactor;

	//安规数据记录
	BOOL m_bHaveTestSaft;
	BOOL m_bSaftOK; //安规合格与否
	float m_fSaft_R; //绝缘电阻
	float m_fSaftLimit_R;
	float m_fSaft_V; //耐压电流
	float m_fSaftLimit_V;
	float m_fSaft_C; //泄露电流
	float m_fSaftLimit_C;

	// Spectrum data
	CArray<float,float> m_fValue;
	CNewTestColorData   m_ColorData;

	//2014.5.5新增 色容差参数
	enum SDCMType
	{
		SDCMType_ELLI,
		SDCMType_PLOY,
	};
	int		m_iSDCMType;	//类型 椭圆还是多边形
	CString m_strSDCMSta;	//色容差选择的标准
	float	m_fSDCM;		//椭圆算出的色容差值
	BOOL	m_bInPoly;		//多边形 是否在内


private:
	BOOL m_bDataValid;
};

