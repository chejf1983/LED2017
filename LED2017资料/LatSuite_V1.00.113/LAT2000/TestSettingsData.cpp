#include "StdAfx.h"
#include "TestSettingsData.h"
#include "math.h"
#include "LAT2000.h"
#include "StatisticLedDataContainer.h"


CTestSettingsData::CTestSettingsData(void)
{
	m_fTestVoltageV		= 220.0f;
	m_fTestFrquencyHz	= 50;
	m_fIntegralTimems	= 100.0f;
    m_fWarmUpTimems		= 10.0f;
    m_iTestMinSeconds	= 20; 
	m_iBurnInONSeconds	= 1;
	m_iBurnInOFFSeconds = 1;

	m_ui32Flag			= CHECK_FLUX;

	for (int i = 0; i < DATA_CAHNNEL_NUM; i++)
	{
		m_pbTestChannel[i]		= TRUE;
		m_pbThunderChannel[i]	= TRUE;
		m_pfLuminosityK[i]		= 1;
		m_pfStandardFlux[i]		= 0.0f;
		m_pfTestFlux[i]			= 0.0f;
	}
    m_fLimitR9		= 50;
    m_fOffsetR9		= 50;
    m_fOffsetR9_	= 50;
    m_fBallHigh		= 150;

    m_fStaPow		= 9;
    m_fStaFlux		= 470;
    m_fStaTc		= 2700;
    m_fStaVol		= 220;
    m_fLEDUnOnPow	= 1.0f;
    m_fLEDUnOnFlux	= 3.0f;
}

CTestSettingsData::~CTestSettingsData(void)
{
}


BOOL CTestSettingsData::IsQulified(int iCurPara, float fValue)
{
	BOOL bR = TRUE;  
    LimitStruct LimitAllPara[50];
    for (int i = 0; i < m_Limit.GetSize(); i ++)
    {
        LimitAllPara[m_Limit.GetAt(i).m_iCurPara] = m_Limit.GetAt(i);
    }
    if (LimitAllPara[iCurPara].m_bCheckJudge)
    {
        bR = (fValue > LimitAllPara[iCurPara].m_fLimitVal - LimitAllPara[iCurPara].m_fLimitVal_Offset2) && 
            (fValue < LimitAllPara[iCurPara].m_fLimitVal + LimitAllPara[iCurPara].m_fLimitVal_Offset1);
    }  	
	return bR;
}


BOOL CTestSettingsData::IsQulified(CLedData & data,int &iTypeFail)
{
	BOOL  bR = TRUE;
	BOOL  bTemp;
    float fValue;
    LimitStruct LimitAllPara[PARA_NUM];
    float fValueArray[PARA_NUM];
    for (int i = 0; i < m_Limit.GetSize(); i ++)
    {
        LimitAllPara[m_Limit.GetAt(i).m_iCurPara] = m_Limit.GetAt(i);
    }
    if (1)
    {
		int iNum = 0;
		fValueArray[iNum++] = data.m_fSDCM;
        fValueArray[iNum++] = data.m_fCurrentA * 1000;
        fValueArray[iNum++] = data.m_fVoltageV;
        fValueArray[iNum++] = data.m_fFrequencyHz;
        fValueArray[iNum++] = data.m_fPowerW;
        fValueArray[iNum++] = data.m_fPowerFactor;
        fValueArray[iNum++] = data.m_ColorData.m_fPh;
        fValueArray[iNum++] = data.m_ColorData.m_fTc;
        fValueArray[iNum++] = data.m_ColorData.m_fCIEx;
        fValueArray[iNum++] = data.m_ColorData.m_fCIEy;
        fValueArray[iNum++] = data.m_ColorData.m_fCIEu_;
        fValueArray[iNum++] = data.m_ColorData.m_fCIEv_;
        fValueArray[iNum++] = data.m_ColorData.m_fLd;
        fValueArray[iNum++] = data.m_ColorData.m_fHW;
        fValueArray[iNum++] = data.m_ColorData.m_fLp;
        fValueArray[iNum++] = data.m_ColorData.m_fIp;
        fValueArray[iNum++] = data.m_ColorData.m_fPur;
        fValueArray[iNum++] = data.m_ColorData.m_fRa;
        fValueArray[iNum++] = data.m_ColorData.m_fPh / data.m_fPowerW;
        fValueArray[iNum++] = data.m_ColorData.m_fRi[0];
        fValueArray[iNum++] = data.m_ColorData.m_fRi[1];
        fValueArray[iNum++] = data.m_ColorData.m_fRi[2];
        fValueArray[iNum++] = data.m_ColorData.m_fRi[3];
        fValueArray[iNum++] = data.m_ColorData.m_fRi[4];
        fValueArray[iNum++] = data.m_ColorData.m_fRi[5];
        fValueArray[iNum++] = data.m_ColorData.m_fRi[6];
        fValueArray[iNum++] = data.m_ColorData.m_fRi[7];
        fValueArray[iNum++] = data.m_ColorData.m_fRi[8];
        fValueArray[iNum++] = data.m_ColorData.m_fRR;
        fValueArray[iNum++] = data.m_ColorData.m_fGR;
        fValueArray[iNum++] = data.m_ColorData.m_fBR;
    }
	int iFailNum = 0;
    for (int i = 0; i < PARA_NUM; i++)
    {    
        if (LimitAllPara[i].m_bCheckJudge)
        {
            fValue =  fValueArray[i];
			bTemp = (fValue > LimitAllPara[i].m_fLimitVal - LimitAllPara[i].m_fLimitVal_Offset2) && 
                (fValue < LimitAllPara[i].m_fLimitVal + LimitAllPara[i].m_fLimitVal_Offset1);
			if (i == 0)
			{
				if (!bTemp)
				{
					iTypeFail = 3;
					iFailNum++;
				}
			}
			else if (i == 1 || i== 2 || i== 3 || i == 4 || i == 5)
			{
				if (!bTemp)
				{
					if(iTypeFail!=1)
						iFailNum++;
					iTypeFail = 1;
				}
			}
			else if (i == 6)
			{
				if (!bTemp)
				{
					iTypeFail = 2;
					iFailNum++;
				}
			}
			else
			{
				if (!bTemp)
				{
					iTypeFail = 4;
				}
			}
            bR = bR && bTemp;
        }         
    }
	if(iFailNum > 1)
	{
		iTypeFail = 4;
	}
	if (bR)
	{
		iTypeFail = 0;
	}
	return bR;
}

BOOL CTestSettingsData::Load(CString strPathName)
{
    m_AlarmSettingsData.InitAlarmSettings();

	CFile file;
	if (!file.Open(strPathName, CFile::modeRead))
	{
		return FALSE;
	}

	CArchive ar(&file, CArchive::load);
	if (Serialize(ar))
	{
		ar.Close();
		file.Close();

		return TRUE;
	}

	ar.Close();
	file.Close();

	return FALSE;
}

BOOL CTestSettingsData::Store(CString strPathName)
{
	CFile file;
	if (!file.Open(strPathName, CFile::modeWrite | CFile::modeCreate))
	{
		return FALSE;
	}

	CArchive ar(&file, CArchive::store);
	if (Serialize(ar))
	{
		ar.Close();
		file.Close();

		return TRUE;
	}

	ar.Close();
	file.Close();

	return FALSE;
}

BOOL CTestSettingsData::Serialize(CArchive & ar)
{
	int i,iN;
	CString strTitle;
	if (ar.IsStoring())
	{
		strTitle = "LIMIT_DATA_A7";
		ar<<strTitle;

		m_AlarmSettingsData.Serialize(ar);

		for (i = 0; i < DATA_CAHNNEL_NUM; i++)
		{
			ar<<m_pbTestChannel[i];
			ar<<m_pbThunderChannel[i];
			ar<<m_pfLuminosityK[i];
			ar<<m_pfStandardFlux[i];
			ar<<m_pfTestFlux[i];
		}

		ar<<m_iBurnInOFFSeconds;
		ar<<m_iBurnInONSeconds;
		ar<<m_iEMC11KSelectIndex;
		ar<<m_iEMC5ASelectIndex;

		ar<<m_fIntegralTimems;
		ar<<m_ui32Flag;
		ar<<m_fTestFrquencyHz;
		ar<<m_fTestVoltageV;
		ar<<m_fWarmUpTimems;

		ar<<m_iRangeCF;
		ar<<m_iRangeI;
		ar<<m_iRangeU;

		ar<<m_fBallHigh;
		ar<<m_strDateTime;
		ar<<m_strLedModel;
		ar<<m_strPersonName;
		ar<<m_strRemarks;

        ar <<  m_bTestLightning;
        ar <<  m_bTestVoltageUpAndDips;
        ar <<  m_bTestBurnIn;
        ar <<  m_iTestMinSeconds;
        ar <<  m_bTestDirectionOpposite;
		for (i = 0; i < DATA_CAHNNEL_NUM; i++)
		{
			ar << m_pfTestFlux2[i];
		}
        ar << m_Limit.GetSize();
        for (i = 0; i < m_Limit.GetSize(); i ++)
        {
            m_Limit.GetAt(i).Serialize(ar);
        }
        ar << m_fStaPow;
        ar << m_fStaFlux;
        ar << m_fStaTc;
        ar << m_fStaVol;
        ar << m_fLEDUnOnPow;
        ar << m_fLEDUnOnFlux;

		ar << m_bTestMyLast;
		ar << m_fVolMyLast.GetSize();
		for (i = 0; i < m_fVolMyLast.GetSize(); i ++)
		{
			ar << m_fVolMyLast[i];
			ar << m_fFreqMyLast[i];
			ar << m_iTimeMyLast[i];
		}

		ar << m_bTestSaft;
		ar << m_fSetVolNYY;
		ar << m_fSetTimeNYY;
		ar << m_fNYYLimit;
		ar << m_fSetVolJYDZ;
		ar << m_fSetTimeJYDZ;
		ar << m_fJYDZLimit;
		ar << m_fSetVolXLDL;
		ar << m_fSetTimeXLDL;
		ar << m_fXLDLLimit;
		ar << m_iTypeNYY;

		ar << m_bTestAutoHand;
	}
	else
	{
		ar>>strTitle;
		if ("LIMIT_DATA" != strTitle 
			&& "LIMIT_DATA_A1" != strTitle 
			&& "LIMIT_DATA_A2" != strTitle 
			&& "LIMIT_DATA_A3" != strTitle 
			&& "LIMIT_DATA_A4" != strTitle
			&& "LIMIT_DATA_A5" != strTitle
			&& "LIMIT_DATA_A6" != strTitle 
			&& "LIMIT_DATA_A7" != strTitle )
		{
			AfxMessageBox("文件格式不正确！" + strTitle);
			
			return FALSE;
		}
		m_AlarmSettingsData.Serialize(ar);
	
		for (i = 0; i < DATA_CAHNNEL_NUM; i++)
		{
			ar>>m_pbTestChannel[i];
			ar>>m_pbThunderChannel[i];
			ar>>m_pfLuminosityK[i];
			ar>>m_pfStandardFlux[i];
			ar>>m_pfTestFlux[i];
		}

		ar>>m_iBurnInOFFSeconds;
		ar>>m_iBurnInONSeconds;
		ar>>m_iEMC11KSelectIndex;
		ar>>m_iEMC5ASelectIndex;

		ar>>m_fIntegralTimems;
		ar>>m_ui32Flag;
		ar>>m_fTestFrquencyHz;
		ar>>m_fTestVoltageV;
		ar>>m_fWarmUpTimems;

		ar>>m_iRangeCF;
		ar>>m_iRangeI;
		ar>>m_iRangeU;

        if ("LIMIT_DATA" == strTitle || "LIMIT_DATA_A1" == strTitle || "LIMIT_DATA_A2" == strTitle)
        {
            ar>>m_fLimitFlux;
            ar>>m_fLimitHW;
            ar>>m_fLimitLd;
            ar>>m_fLimitLp;
            ar>>m_fLimitPositiveCurrent;
            ar>>m_fLimitPositiveVoltage;
            ar>>m_fLimitPur;
            ar>>m_fLimitRa;
            ar>>m_fLimitTc;
            ar>>m_fLimitU;
            ar>>m_fLimitV;
            ar>>m_fLimitX;
            ar>>m_fLimitY;
            ar>>m_fLimitLuminousPower;

            ar>>m_fOffsetFlux;
            ar>>m_fOffsetHW;
            ar>>m_fOffsetLd;
            ar>>m_fOffsetLp;
            ar>>m_fOffsetPositveCurrent;
            ar>>m_fOffsetPositiveVoltage;
            ar>>m_fOffsetPur;
            ar>>m_fOffsetRa;
            ar>>m_fOffsetTc;
            ar>>m_fOffsetU;
            ar>>m_fOffsetV;
            ar>>m_fOffsetX;
            ar>>m_fOffsetY;
            ar>>m_fOffsetLuminousPower;

            ar>>m_fOffsetFlux_;
            ar>>m_fOffsetHW_;
            ar>>m_fOffsetLd_;
            ar>>m_fOffsetLp_;
            ar>>m_fOffsetPositveCurrent_;
            ar>>m_fOffsetPositiveVoltage_;
            ar>>m_fOffsetPur_;
            ar>>m_fOffsetRa_;
            ar>>m_fOffsetTc_;
            ar>>m_fOffsetU_;
            ar>>m_fOffsetV_;
            ar>>m_fOffsetX_;
            ar>>m_fOffsetY_;
            ar>>m_fOffsetLuminousPower_;
        }

		ar>>m_fBallHigh;
		ar>>m_strDateTime;
		ar>>m_strLedModel;
		ar>>m_strPersonName;
		ar>>m_strRemarks;

        if ("LIMIT_DATA_A1" == strTitle || "LIMIT_DATA_A2" == strTitle)
        {
            ar >> m_fLimitPow;
            ar >> m_fOffsetPow;
            ar >> m_fOffsetPow_;
            ar >> m_fLimitPowFactor;
            ar >> m_fOffsetPowFactor;
            ar >> m_fOffsetPowFactor_;
            ar >> m_fLimitFre;
            ar >> m_fOffsetFre;
            ar >> m_fOffsetFre_;
        }
        else
        {
            m_fLimitPow = 0;
            m_fOffsetPow = 0;
            m_fOffsetPow_ = 0;
            m_fLimitPowFactor = 0;
            m_fOffsetPowFactor = 0;
            m_fOffsetPowFactor_ = 0;
            m_fLimitFre = 0;
            m_fOffsetFre = 0;
            m_fOffsetFre_ = 0;  
     
        }
        if ("LIMIT_DATA_A1" != strTitle)
        {    
            ar >>  m_bTestLightning;
            ar >>  m_bTestVoltageUpAndDips;
            ar >>  m_bTestBurnIn;
            ar >>  m_iTestMinSeconds;
            ar >>  m_bTestDirectionOpposite;
			for (int i = 0; i < DATA_CAHNNEL_NUM; i++)
			{
				ar >> m_pfTestFlux2[i];
			}
        }
        else
        {
            m_bTestLightning		= 0;
            m_bTestVoltageUpAndDips = 0;
            m_bTestBurnIn			= 0;
            m_iTestMinSeconds		= 1;
            m_bTestDirectionOpposite= 0;

			m_pfTestFlux2[0] = m_pfTestFlux[0] * 1.01f;
            m_pfTestFlux2[1] = m_pfTestFlux[1] * 1.02f;
            m_pfTestFlux2[2] = m_pfTestFlux[2] * 0.99f;
            m_pfTestFlux2[3] = m_pfTestFlux[3] * 1.00f;
            m_pfTestFlux2[4] = m_pfTestFlux[4] * 0.98f;
            m_pfTestFlux2[5] = m_pfTestFlux[5] * 1.00f;
            m_pfTestFlux2[6] = m_pfTestFlux[6] * 1.02f;
            m_pfTestFlux2[7] = m_pfTestFlux[7] * 1.01f;
            m_pfTestFlux2[8] = m_pfTestFlux[8] * 1.02f;
            m_pfTestFlux2[9] = m_pfTestFlux[9] * 0.98f;
        }
        m_Limit.RemoveAll();
        LimitStruct temp;
        temp.m_bCheckJudge = CHECK_FLUX & m_ui32Flag ? 1 : 0;
        temp.m_iCurPara = STATISTIC_FLUX;
        temp.m_fLimitVal = m_fLimitFlux;
        temp.m_fLimitVal_Offset1 = m_fOffsetFlux;
        temp.m_fLimitVal_Offset2 = m_fOffsetFlux_;
        AddtoLimit(temp);

        temp.m_bCheckJudge = CHECK_HW & m_ui32Flag ? 1 : 0;
        temp.m_iCurPara = STATISTIC_HW;
        temp.m_fLimitVal = m_fLimitHW;
        temp.m_fLimitVal_Offset1 = m_fOffsetHW;
        temp.m_fLimitVal_Offset2 = m_fOffsetHW_;
        AddtoLimit(temp);

        temp.m_bCheckJudge = CHECK_LD & m_ui32Flag ? 1 : 0;
        temp.m_iCurPara = STATISTIC_LD;
        temp.m_fLimitVal = m_fLimitLd;
        temp.m_fLimitVal_Offset1 = m_fOffsetLd;
        temp.m_fLimitVal_Offset2 = m_fOffsetLd_;
        AddtoLimit(temp);

        temp.m_bCheckJudge = CHECK_LP & m_ui32Flag ? 1 : 0;
        temp.m_iCurPara = STATISTIC_LP;
        temp.m_fLimitVal = m_fLimitLp;
        temp.m_fLimitVal_Offset1 = m_fOffsetLp;
        temp.m_fLimitVal_Offset2 = m_fOffsetLp_;
        AddtoLimit(temp);

        temp.m_bCheckJudge = CHECK_POSITIVECURRENT & m_ui32Flag ? 1 : 0;
        temp.m_iCurPara = STATISTIC_CURR;
        temp.m_fLimitVal = m_fLimitPositiveCurrent;
        temp.m_fLimitVal_Offset1 = m_fOffsetPositveCurrent;
        temp.m_fLimitVal_Offset2 = m_fOffsetPositveCurrent_;
        AddtoLimit(temp);

        temp.m_bCheckJudge = CHECK_POSITIVEVOLTAGE & m_ui32Flag ? 1 : 0;
        temp.m_iCurPara = STATISTIC_VOL;
        temp.m_fLimitVal = m_fLimitPositiveVoltage;
        temp.m_fLimitVal_Offset1 = m_fOffsetPositiveVoltage;
        temp.m_fLimitVal_Offset2 = m_fOffsetPositiveVoltage_;
        AddtoLimit(temp);

        temp.m_bCheckJudge = CHECK_PUR & m_ui32Flag ? 1 : 0;
        temp.m_iCurPara = STATISTIC_PUR;
        temp.m_fLimitVal = m_fLimitPur;
        temp.m_fLimitVal_Offset1 = m_fOffsetPur;
        temp.m_fLimitVal_Offset2 = m_fOffsetPur_;
        AddtoLimit(temp);

        temp.m_bCheckJudge = CHECK_RA & m_ui32Flag ? 1 : 0;
        temp.m_iCurPara = STATISTIC_RA;
        temp.m_fLimitVal = m_fLimitRa;
        temp.m_fLimitVal_Offset1 = m_fOffsetRa;
        temp.m_fLimitVal_Offset2 = m_fOffsetRa_;
        AddtoLimit(temp);
        
        temp.m_bCheckJudge = CHECK_TC & m_ui32Flag ? 1 : 0;
        temp.m_iCurPara = STATISTIC_TC;
        temp.m_fLimitVal = m_fLimitTc;
        temp.m_fLimitVal_Offset1 = m_fOffsetTc;
        temp.m_fLimitVal_Offset2 = m_fOffsetTc_;
        AddtoLimit(temp);

        temp.m_bCheckJudge = CHECK_U & m_ui32Flag ? 1 : 0;
        temp.m_iCurPara = STATISTIC_CIE_U;
        temp.m_fLimitVal = m_fLimitU;
        temp.m_fLimitVal_Offset1 = m_fOffsetU;
        temp.m_fLimitVal_Offset2 = m_fOffsetU_;
        AddtoLimit(temp);

        temp.m_bCheckJudge = CHECK_V & m_ui32Flag ? 1 : 0;
        temp.m_iCurPara = STATISTIC_CIE_V;
        temp.m_fLimitVal = m_fLimitV;
        temp.m_fLimitVal_Offset1 = m_fOffsetV;
        temp.m_fLimitVal_Offset2 = m_fOffsetV_;
        AddtoLimit(temp);

        temp.m_bCheckJudge = CHECK_X & m_ui32Flag ? 1 : 0;
        temp.m_iCurPara = STATISTIC_CIE_X;
        temp.m_fLimitVal = m_fLimitX;
        temp.m_fLimitVal_Offset1 = m_fOffsetX;
        temp.m_fLimitVal_Offset2 = m_fOffsetX_;
        AddtoLimit(temp);

        temp.m_bCheckJudge = CHECK_Y & m_ui32Flag ? 1 : 0;
        temp.m_iCurPara = STATISTIC_CIE_Y;
        temp.m_fLimitVal = m_fLimitY;
        temp.m_fLimitVal_Offset1 = m_fOffsetY;
        temp.m_fLimitVal_Offset2 = m_fOffsetY_;
        AddtoLimit(temp);

        temp.m_bCheckJudge = CHECK_LUMINOUS_POWER & m_ui32Flag ? 1 : 0;
        temp.m_iCurPara = STATISTIC_EFFIC;
        temp.m_fLimitVal = m_fLimitLuminousPower;
        temp.m_fLimitVal_Offset1 = m_fOffsetLuminousPower;
        temp.m_fLimitVal_Offset2 = m_fOffsetLuminousPower_;
        AddtoLimit(temp);

        temp.m_bCheckJudge = CHECK_P & m_ui32Flag ? 1 : 0;
        temp.m_iCurPara = STATISTIC_POW;
        temp.m_fLimitVal = m_fLimitPow;
        temp.m_fLimitVal_Offset1 = m_fOffsetPow;
        temp.m_fLimitVal_Offset2 = m_fOffsetPow_;
        AddtoLimit(temp);

        temp.m_bCheckJudge = CHECK_PF & m_ui32Flag ? 1 : 0;
        temp.m_iCurPara = STATISTIC_FACTOR;
        temp.m_fLimitVal = m_fLimitPowFactor;
        temp.m_fLimitVal_Offset1 = m_fOffsetPowFactor;
        temp.m_fLimitVal_Offset2 = m_fOffsetPowFactor_;
        AddtoLimit(temp);

        temp.m_bCheckJudge = CHECK_FRE & m_ui32Flag ? 1 : 0;
        temp.m_iCurPara = STATISTIC_FRE;
        temp.m_fLimitVal = m_fLimitFre;
        temp.m_fLimitVal_Offset1 = m_fOffsetFre;
        temp.m_fLimitVal_Offset2 = m_fOffsetFre_;
        AddtoLimit(temp);

        if ("LIMIT_DATA_A1" != strTitle && "LIMIT_DATA_A2" != strTitle)
        {
            m_Limit.RemoveAll();
            int iN;
            ar >> iN;
            for (int i = 0; i < iN; i ++)
            {
                LimitStruct *pTemp = new LimitStruct;
                pTemp->Serialize(ar);
                AddtoLimit(*pTemp);
            }
        }
        if ("LIMIT_DATA_A1" != strTitle && "LIMIT_DATA_A2" != strTitle && "LIMIT_DATA_A3" != strTitle)
        {
            ar >> m_fStaPow;
            ar >> m_fStaFlux;
            ar >> m_fStaTc;
            ar >> m_fStaVol;
            ar >> m_fLEDUnOnPow;
            ar >> m_fLEDUnOnFlux;
        }

		if ("LIMIT_DATA_A1" != strTitle && "LIMIT_DATA_A2" != strTitle && "LIMIT_DATA_A3" != strTitle && "LIMIT_DATA_A4" != strTitle)
		{
			ar >> m_bTestMyLast;
			ar >> iN;
			m_fVolMyLast.RemoveAll();
			m_fFreqMyLast.RemoveAll();
			m_iTimeMyLast.RemoveAll();
			for (int i = 0; i < iN; i ++)
			{
				float fTemp;

				ar >> fTemp;
				m_fVolMyLast.Add(fTemp);

				ar >> fTemp;
				m_fFreqMyLast.Add(fTemp);

				int iTemp;
				ar >> iTemp;
				m_iTimeMyLast.Add(iTemp);
			}

			ar >> m_bTestSaft;

			ar >> m_fSetVolNYY;
			ar >> m_fSetTimeNYY;
			ar >> m_fNYYLimit;
			ar >> m_fSetVolJYDZ;
			ar >> m_fSetTimeJYDZ;
			ar >> m_fJYDZLimit;
			ar >> m_fSetVolXLDL;
			ar >> m_fSetTimeXLDL;
			ar >> m_fXLDLLimit;
		}
		else
		{
			m_bTestMyLast	= FALSE;
			m_bTestSaft		= FALSE;

			m_fSetVolJYDZ	= 500;
			m_fSetTimeJYDZ	= 1;
			m_fJYDZLimit	= 20;

			m_fSetVolNYY	= 100;
			m_fSetTimeNYY	= 1;
			m_fNYYLimit		= 2;
			m_iTypeNYY		= 0;
			
			m_fSetVolXLDL	= 220;
			m_fSetTimeXLDL	= 1;
			m_fXLDLLimit	= 2;
		}

		if ("LIMIT_DATA_A1" != strTitle 
			&& "LIMIT_DATA_A2" != strTitle 
			&& "LIMIT_DATA_A3" != strTitle 
			&& "LIMIT_DATA_A4" != strTitle
			&& "LIMIT_DATA_A5" != strTitle)
		{
			ar >> m_iTypeNYY;
		}
		else
		{
			m_iTypeNYY = 0;
		}

		if ("LIMIT_DATA" != strTitle 
			&& "LIMIT_DATA_A1" != strTitle 
			&& "LIMIT_DATA_A2" != strTitle 
			&& "LIMIT_DATA_A3" != strTitle 
			&& "LIMIT_DATA_A4" != strTitle
			&& "LIMIT_DATA_A5" != strTitle
			&& "LIMIT_DATA_A6" != strTitle )
		{
			ar >> m_bTestAutoHand;
		}
		else
		{
			m_bTestAutoHand = FALSE;
		}
	}

	return TRUE;
}

CTestSettingsData & CTestSettingsData::operator = (CTestSettingsData & data)
{
    if (&data == this)
    {
        return *this;
    }
	this->m_fIntegralTimems = data.m_fIntegralTimems;
	this->m_fWarmUpTimems	= data.m_fWarmUpTimems;
	this->m_fTestFrquencyHz = data.m_fTestFrquencyHz;
	this->m_fTestVoltageV	= data.m_fTestVoltageV;

	this->m_iRangeCF	= data.m_iRangeCF;
	this->m_iRangeI		= data.m_iRangeI;
	this->m_iRangeU		= data.m_iRangeU;

	this->m_iEMC11KSelectIndex	= data.m_iEMC11KSelectIndex;
	this->m_iEMC5ASelectIndex	= data.m_iEMC5ASelectIndex;
	this->m_iBurnInOFFSeconds	= data.m_iBurnInOFFSeconds;
	this->m_iBurnInONSeconds	= data.m_iBurnInONSeconds;
	
	for (int i = 0; i < DATA_CAHNNEL_NUM; i++)
	{
		this->m_pbTestChannel[i]	= data.m_pbTestChannel[i];
		this->m_pbThunderChannel[i] = data.m_pbThunderChannel[i];
		this->m_pfLuminosityK[i]	= data.m_pfLuminosityK[i];
		this->m_pfStandardFlux[i]	= data.m_pfStandardFlux[i];
		this->m_pfTestFlux[i]		= data.m_pfTestFlux[i];
		this->m_pfTestFlux2[i]		= data.m_pfTestFlux2[i];
	}

	this->m_ui32Flag			= data.m_ui32Flag;

	this->m_AlarmSettingsData	= data.m_AlarmSettingsData;

	this->m_fLimitFlux			= data.m_fLimitFlux;
	this->m_fOffsetFlux			= data.m_fOffsetFlux;
	this->m_fOffsetFlux_		= data.m_fOffsetFlux_;

	this->m_fLimitHW	= data.m_fLimitHW;
	this->m_fOffsetHW	= data.m_fOffsetHW;
	this->m_fOffsetHW_	= data.m_fOffsetHW_;

	this->m_fLimitLd	= data.m_fLimitLd;
	this->m_fOffsetLd	= data.m_fOffsetLd;
	this->m_fOffsetLd_	= data.m_fOffsetLd_;

	this->m_fLimitLp	= data.m_fLimitLp;
	this->m_fOffsetLp	= data.m_fOffsetLp;
	this->m_fOffsetLp_	= data.m_fOffsetLp_;

	this->m_fLimitPositiveCurrent	= data.m_fLimitPositiveCurrent;
	this->m_fOffsetPositiveVoltage	= data.m_fOffsetPositiveVoltage;
	this->m_fOffsetPositiveVoltage_ = data.m_fOffsetPositiveVoltage_;

	this->m_fLimitPositiveVoltage	= data.m_fLimitPositiveVoltage;
	this->m_fOffsetPositveCurrent	= data.m_fOffsetPositveCurrent;
	this->m_fOffsetPositveCurrent_	= data.m_fOffsetPositveCurrent_;

	this->m_fLimitPur	= data.m_fLimitPur;
	this->m_fOffsetPur	= data.m_fOffsetPur;
	this->m_fOffsetPur_ = data.m_fOffsetPur_;

	this->m_fLimitRa	= data.m_fLimitRa;
	this->m_fOffsetRa	= data.m_fOffsetRa;
	this->m_fOffsetRa_	= data.m_fOffsetRa_;

	this->m_fLimitTc	= data.m_fLimitTc;
	this->m_fOffsetTc	= data.m_fOffsetTc;
	this->m_fOffsetTc_	= data.m_fOffsetTc_;

	this->m_fLimitU		= data.m_fLimitU;
	this->m_fOffsetU	= data.m_fOffsetU;
	this->m_fOffsetU_	= data.m_fOffsetU_;

	this->m_fLimitV		= data.m_fLimitV;
	this->m_fOffsetV	= data.m_fOffsetV;
	this->m_fOffsetV_	= data.m_fOffsetV_;

	this->m_fLimitX		= data.m_fLimitX;
	this->m_fOffsetX	= data.m_fOffsetX;
	this->m_fOffsetX_	= data.m_fOffsetX_;

	this->m_fLimitY		= data.m_fLimitY;
	this->m_fOffsetY	= data.m_fOffsetY;
	this->m_fOffsetY_	= data.m_fOffsetY_;

	this->m_strDateTime = data.m_strDateTime;
	this->m_strLedModel = data.m_strLedModel;
	this->m_strPersonName = data.m_strPersonName;
	this->m_strRemarks	= data.m_strRemarks;

    this->m_fLimitPow	= data.m_fLimitPow;
    this->m_fOffsetPow	= data.m_fOffsetPow;
    this->m_fOffsetPow_ = data.m_fOffsetPow_;

    this->m_fLimitPowFactor		= data.m_fLimitPowFactor;
    this->m_fOffsetPowFactor	= data.m_fOffsetPowFactor;
    this->m_fOffsetPowFactor_	= data.m_fOffsetPowFactor_;

	this->m_fLimitLuminousPower		= data.m_fLimitLuminousPower;
	this->m_fOffsetLuminousPower	= data.m_fOffsetLuminousPower;
	this->m_fOffsetLuminousPower_	= data.m_fOffsetLuminousPower_;

    this->m_fLimitFre	= data.m_fLimitFre;
    this->m_fOffsetFre	= data.m_fOffsetFre;
    this->m_fOffsetFre_ = data.m_fOffsetFre_;

    this->m_bTestLightning			= data.m_bTestLightning;
    this->m_bTestVoltageUpAndDips	= data.m_bTestVoltageUpAndDips;
    this->m_bTestBurnIn				= data.m_bTestBurnIn;
    this->m_iTestMinSeconds			= data.m_iTestMinSeconds;
    this->m_bTestDirectionOpposite	= data.m_bTestDirectionOpposite;

	this->m_fBallHigh		= data.m_fBallHigh;
	this->m_strDateTime		= data.m_strDateTime;
	this->m_strPersonName	= data.m_strPersonName;
	this->m_strLedModel		= data.m_strLedModel;
	this->m_strRemarks		= data.m_strRemarks;

    this->m_fLimitR9	= data.m_fLimitR9;
    this->m_fOffsetR9	= data.m_fOffsetR9;
    this->m_fOffsetR9_	= data.m_fOffsetR9_;
    m_Limit.RemoveAll();
    for (int i = 0; i < data.m_Limit.GetSize(); i ++)
    {
        AddtoLimit(data.m_Limit.GetAt(i));
    }
	//安规
	this->m_bTestSaft	= data.m_bTestSaft;
	this->m_bTestAutoHand = data.m_bTestAutoHand;

	this->m_fSetVolNYY	= data.m_fSetVolNYY;
	this->m_fSetTimeNYY = data.m_fSetTimeNYY;
	this->m_fNYYLimit	= data.m_fNYYLimit;
	this->m_iTypeNYY	= data.m_iTypeNYY;

	this->m_fSetVolJYDZ  = data.m_fSetVolJYDZ;
	this->m_fSetTimeJYDZ= data.m_fSetTimeJYDZ;
	this->m_fJYDZLimit	= data.m_fJYDZLimit;

	this->m_fSetVolXLDL = data.m_fSetVolXLDL;
	this->m_fSetTimeXLDL= data.m_fSetTimeXLDL;
	this->m_fXLDLLimit  = data.m_fXLDLLimit;

	//漫游
	this->m_bTestMyLast		= data.m_bTestMyLast;
	this->m_fVolMyLast.RemoveAll();
	for (int i = 0; i < data.m_fVolMyLast.GetSize(); i ++)
	{
		this->m_fVolMyLast.Add(data.m_fVolMyLast[i]);
	}

	this->m_fFreqMyLast.RemoveAll();
	for (int i = 0; i < data.m_fFreqMyLast.GetSize(); i ++)
	{
		this->m_fFreqMyLast.Add(data.m_fFreqMyLast[i]);
	}

	this->m_iTimeMyLast.RemoveAll();
	for (int i = 0; i < data.m_iTimeMyLast.GetSize(); i ++)
	{
		this->m_iTimeMyLast.Add(data.m_iTimeMyLast[i]);
	}

    m_fStaPow	= data.m_fStaPow;
    m_fStaFlux	= data.m_fStaFlux;
    m_fStaTc	= data.m_fStaTc;
    m_fStaVol	= data.m_fStaVol;
    m_fLEDUnOnPow = data.m_fLEDUnOnPow;
    m_fLEDUnOnFlux = data.m_fLEDUnOnFlux;
	return *this;
}

CTestSettingsData& CTestSettingsData::LimitEqual(CTestSettingsData & data)
{
    if (&data == this)
    {
      return *this;
    }
    m_Limit.RemoveAll();
    for (int i = 0; i < data.m_Limit.GetSize(); i ++)
    {
        AddtoLimit(data.m_Limit.GetAt(i));
    }
    return *this;
}

void CTestSettingsData::Relist(CListCtrl &cList, BOOL bCanCheck)
{
   cList.DeleteAllItems();
   while(1)
   {
       if (cList.DeleteColumn(0) == FALSE)
       {
           break;
       }
   }
   CString strTemp;
   int iN = 0; 
   strTemp = _T("选择判定");
   cList.InsertColumn(iN,strTemp);
   cList.SetColumnWidth(iN,100);
   iN ++;
   strTemp = _T("参数名");
   cList.InsertColumn(iN,strTemp);
   cList.SetColumnWidth(iN,100);
   iN ++;
   strTemp = _T("参考值");
   cList.InsertColumn(iN,strTemp);
   cList.SetColumnWidth(iN,100); 

   iN ++;
   strTemp = _T("向下偏差");
   cList.InsertColumn(iN,strTemp);
   cList.SetColumnWidth(iN,100); 

   iN ++;
   strTemp = _T("向上偏差");
   cList.InsertColumn(iN,strTemp);
   cList.SetColumnWidth(iN,100); 

   for (int i = 0; i < m_Limit.GetSize(); i ++)
   {   
       iN = 0;  
       strTemp = "";
       cList.InsertItem(i,strTemp);
       if (bCanCheck)
       {
           if (m_Limit.GetAt(i).m_bCheckJudge)
           {
                   cList.SetCheck(i);
           }  
       }
       else
       {
           if (m_Limit.GetAt(i).m_bCheckJudge)
           {
               strTemp.Format(_T("%s"), _T("是"));
               cList.SetItemText(i,iN,strTemp); 
           }
           else
           {
               strTemp.Format(_T("%s"), _T("否"));
               cList.SetItemText(i,iN,strTemp);
           }
       }
       iN ++;
       strTemp.Format(_T("%s"), g_strListParaName[m_Limit.GetAt(i).m_iCurPara]);
       cList.SetItemText(i,iN,strTemp); 
       iN ++;
       strTemp.Format(_T("%g"), m_Limit.GetAt(i).m_fLimitVal) ;
       cList.SetItemText(i,iN,strTemp);
       iN ++;
       strTemp.Format(_T("%g"), m_Limit.GetAt(i).m_fLimitVal_Offset2) ;
       cList.SetItemText(i,iN,strTemp);  
       iN ++;
       strTemp.Format(_T("%g"), m_Limit.GetAt(i).m_fLimitVal_Offset1) ;
       cList.SetItemText(i,iN,strTemp); 
   }
}


void CTestSettingsData::AddtoLimit(LimitStruct &ParaLimit)
{
    int i = 0;
    for (i = 0; i < m_Limit.GetSize(); i++)
    {
        if (ParaLimit.m_iCurPara < m_Limit.GetAt(i).m_iCurPara)
        {
            break;
        }
    }
    m_Limit.InsertAt(i, ParaLimit);
}

int CTestSettingsData::ModifytoLimit(LimitStruct &ParaLimit)
{
    int i = 0;
    for ( i = 0; i < m_Limit.GetSize(); i++)
    {
        if (ParaLimit.m_iCurPara == m_Limit.GetAt(i).m_iCurPara)
        {
            m_Limit.GetAt(i)  = ParaLimit;
            return i;
        }
    }
    return -1;
}

int CTestSettingsData::GetAllTestChannelNum()
{
    int iNum = 0;
    for (int i = 0;i < g_iColomnNum; i ++)
    {
        if (m_pbTestChannel[i])
        {
            iNum ++;
        }
    }
    return iNum;
}