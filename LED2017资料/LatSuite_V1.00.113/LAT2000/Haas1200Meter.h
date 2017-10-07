// Haas1200Meter.h: interface for the CHaas1200Meter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HAAS1200METER_H__CCB14D5A_7629_48CC_B4EE_81D00BB11DCB__INCLUDED_)
#define AFX_HAAS1200METER_H__CCB14D5A_7629_48CC_B4EE_81D00BB11DCB__INCLUDED_

#include "NewTestColorData.h"
#include "ExV90DLL.h"
#include "ExCalcColorDLL.h"
#include "ExCalc_Color.h"

#define TEST_MODE_NORM      0
#define TEST_MODE_TRIG_IN   1

#define  COMM_TYPE_USB       0
#define  COMM_TYPE_RS232     1

#define TEST_BIN_RANGE_1     0   // High
#define TEST_BIN_RANGE_2     1   // Low

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCalSpectrumData;
class CWaveCorrectData;

class CHaas1200Meter  
{
	friend class CDlgCalSpectrum;
public:
	void SetCIEXYReCalculate(float fx, float fy, float & fu_, float & fv_, float & fTc);
	void SetCIEU_V_ReCalculate(float fu_, float fv_, float &fx, float &fy, float &fTc);

	/* 初始化 */
	BOOL InitMeter(char strCalPath[], BOOL bDemo);
	BOOL SetCommType(int iCommType);
	BOOL SetCom(char strCom[]);

	/* 相关信息 */
	int GetCCDPixNum();
	CString GetSerialNumber();
	float GetWL_Range1();
	float GetWL_Range2();
	float GetWL(int iPixel);

	/* 测试条件设置 */
	void SetTestMode(int iTestMode);

	// This function will reload the calibration data
	BOOL SetBinRange(int iBinRange);
	void SetTestAvgNum(int iAvgNum);
	void SetIntTime(float fIntTimems);

	/* 快门控制 */
	BOOL SetShutterOn();
	BOOL SetShutterOff();

	/* 采样AD */
	BOOL AutoIntegralTime(float & fIntegralTimems, float fMaxTimems = 60000, float fProperIp = 20000);
	BOOL SampleAD(float fAD[], BOOL bAutoGetDark = FALSE);

	/* 计算颜色参数及光度参数 */
	BOOL CalcColor(float fSetCalcInterval,  /* 0.1 or 0.2 0.5 1.0 */
		float fIntTimeMs, float fOnLampTimeMs, 
		float fDarkAD[], float fAD[], CNewTestColorData &data);

	/* 测试一次颜色数据 */
	BOOL TestOne(CNewTestColorData &data, float fAD[]);

	/* 光谱定标 */
	void ShowSpectrumCalDlg();

	// Spectrum test
	void ShowTestDialog();

	CHaas1200Meter();
	virtual ~CHaas1200Meter();

	CCalSpectrumData *m_pCalSpectrumData;
	CWaveCorrectData *m_pWaveCorrectData;

private:
//	BOOL SampleAD(int iTrigMode, int iRangeBin, float fIntTime, int iAvgNum);
	
	int m_iSetCommType;
	CString m_strSetCommCom;

	int m_iSetTestMode;
	float m_fSetIntTime;
	int m_iSetAvgNum;
	int m_iSetBinRange;

	float m_fSaveDarkAD[4096];
	float m_fSaveDarkIntTime;

	int m_iPixNum;

	CString m_strCalPath;
	BOOL m_bDemo;
};

#endif // !defined(AFX_HAAS1200METER_H__CCB14D5A_7629_48CC_B4EE_81D00BB11DCB__INCLUDED_)
