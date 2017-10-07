#include "StdAfx.h"
#include "LedData.h"
#include <afx.h>
#include "LAT2000Doc.h"

//CArray<float,float> CLedData::m_fWaveLength;

CLedData::CLedData(void)
{
	m_ulID			= 0;
	m_bDataValid	= FALSE;

	m_fCurrentA		= 0;
	m_fVoltageV		= 0;
	m_fPowerFactor	= 1;
	m_fPowerW		= 0;

	m_fSDCM			= 0;
	m_strSDCMSta	= "";
	m_iSDCMType		= SDCMType_ELLI;
	m_bInPoly		= FALSE;

	m_fValue.RemoveAll();
    m_bNotMoveLine = FALSE;
}


CLedData::~CLedData(void)
{
}



BOOL CLedData::IsValid()
{
	return m_bDataValid;
}

BOOL CLedData::SetValid(BOOL bValid)
{
	m_bDataValid = bValid;

	return TRUE;
}

BOOL CLedData::IsLEDON()
{

	if (m_fPowerW > g_pDoc->m_dataContainer.GetTestSettingData().m_fLEDUnOnPow
        && m_ColorData.m_fPh > g_pDoc->m_dataContainer.GetTestSettingData().m_fLEDUnOnFlux 
       )
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}

}

CString CLedData::GetInfoString(BOOL bLedOn)
{
	if (!m_ColorData.m_bHaveColorData)
	{
		return "";
	}

	CString strTemp, strInfo;

    if (bLedOn)
    {
        strTemp.Format("Current:%.1f mA\n",m_fCurrentA * 1000);
        strInfo += strTemp;

        strTemp.Format("Model:%s\n", m_strLedModel);
        strInfo += strTemp;

        strTemp.Format("Voltage:%.1f V\n", m_fVoltageV);
        strInfo += strTemp;

        strTemp.Format("x  = %.4f, y  = %.4f\n", m_ColorData.m_fCIEx, m_ColorData.m_fCIEy);
        strInfo += strTemp;

        strTemp.Format("u' = %.4f, v' = %.4f\n", m_ColorData.m_fCIEu_, m_ColorData.m_fCIEv_);
        strInfo += strTemp;

        strTemp.Format("Flux: %.4g lm\n", m_ColorData.m_fPh);
        strInfo += strTemp;

        strTemp.Format("Tc:   %.0f K\n", m_ColorData.m_fTc);
        strInfo += strTemp;

        strTemp.Format("Ld:   %.1f nm\n", m_ColorData.m_fLd);
        strInfo += strTemp;

        strTemp.Format("Ra:   %.1f nm\n", m_ColorData.m_fRa);
        strInfo += strTemp;

        strTemp.Format("Ip:   %.1f \n", m_ColorData.m_fIp);
        strInfo += strTemp;
    }
	else
    {
        strTemp.Format("Current:%.1f mA\n",m_fCurrentA * 1000);
        strInfo += strTemp;

        strTemp.Format("Model:%s\n", m_strLedModel);
        strInfo += strTemp;

        strTemp.Format("Voltage:%.1f V\n", m_fVoltageV);
        strInfo += strTemp;

        strTemp.Format("x  = %4s, y  = %4s\n", "----", "----");
        strInfo += strTemp;

        strTemp.Format("u' = %4s, v' = %4s\n", "----", "----");
        strInfo += strTemp;

        strTemp.Format("Flux: %.4g lm\n", m_ColorData.m_fPh);
        strInfo += strTemp;

        strTemp.Format("Tc:   %4s\n", "----");
        strInfo += strTemp;

        strTemp.Format("Ld:   %4s\n", "----");
        strInfo += strTemp;

        strTemp.Format("Ra:   %4s\n", "----");
        strInfo += strTemp;

        strTemp.Format("Ip:   %.1f \n", m_ColorData.m_fIp);
        strInfo += strTemp;
    }

	return strInfo;
}

void CLedData::Serialize(CArchive & ar)
{
    int iVer = 0;
	if (ar.IsStoring())
	{
        iVer = 103;
        ar << iVer;
		ar << m_bDataValid;
        ar << m_strSN;
        ar << m_bNotMoveLine;

		ar << m_ulID;

		ar << m_fCurrentA;
		ar << m_fPowerFactor;
		ar << m_fPowerW;
		ar << m_fVoltageV;
		ar << m_fFrequencyHz;

		///////////////////////////////////////////////
		ar << m_ColorData.m_bHaveColorData;
		ar << m_ColorData.m_fAbsPL_K;
		ar << m_ColorData.m_fBR;
		ar << m_ColorData.m_fCIEu_;
		ar << m_ColorData.m_fCIEv_;
		ar << m_ColorData.m_fCIEx;
		ar << m_ColorData.m_fCIEy;
		ar << m_ColorData.m_fduv;
		ar << m_ColorData.m_fGR;
		ar << m_ColorData.m_fHW;
		ar << m_ColorData.m_fIntervalWL;
		ar << m_ColorData.m_fIntTime;
		ar << m_ColorData.m_fIp;
		ar << m_ColorData.m_fIp_removeDark;
		ar << m_ColorData.m_fLav;
		ar << m_ColorData.m_fLd;
		ar << m_ColorData.m_fLp;
		ar << m_ColorData.m_fPh;
		ar << m_ColorData.m_fPh_e;
		ar << m_ColorData.m_fPur;
		ar << m_ColorData.m_fRa;
		ar << m_ColorData.m_fRR;
		ar << m_ColorData.m_fTc;
		ar << m_ColorData.m_fWL1;
		ar << m_ColorData.m_fWL2;

		for (int i = 0; i < 15; i++)
		{
			ar << m_ColorData.m_fRi[i];
		}

		ar << m_ColorData.m_iPLLength;
		for (int j = 0; j < m_ColorData.m_iPLLength; j++)
		{
			ar << m_ColorData.m_fPL[j];
		}
		//////////////////////////////////////////////////
		
		int iCount = m_fValue.GetSize();
		ar<<iCount;
		for (int i = 0; i < iCount; i++)
		{
			ar << m_fValue[i];
		}
        ar << m_strLedModel;

		ar << m_bHaveTestSaft;
		ar << m_bSaftOK; //安规合格与否
		ar << m_fSaft_R; //绝缘电阻
		ar << m_fSaftLimit_R;
		ar << m_fSaft_V; //耐压电流
		ar << m_fSaftLimit_V;
		ar << m_fSaft_C; //泄露电流
		ar << m_fSaftLimit_C;

		ar << m_iSDCMType;
		ar << m_strSDCMSta;
		ar << m_fSDCM;
		ar << m_bInPoly;
	}
	else 
	{
        ar>>iVer;
        if(iVer < 100)
        {
            m_bDataValid = iVer;
        }
        else
        {
            if(iVer > 103)
                return;
            ar>>m_bDataValid;
            if (iVer >= 101)
            {
                ar >> m_strSN;
                ar >> m_bNotMoveLine;
            }
        }
		
		ar >> m_ulID;
		ar >> m_fCurrentA;
		ar >> m_fPowerFactor;
		ar >> m_fPowerW;
		ar >> m_fVoltageV;
		ar >> m_fFrequencyHz;
	
//		m_ColorData.SerializeAr(ar);
		//////////////////////////////////////////////////
		ar >> m_ColorData.m_bHaveColorData;
		ar >> m_ColorData.m_fAbsPL_K;
		ar >> m_ColorData.m_fBR;
		ar >> m_ColorData.m_fCIEu_;
		ar >> m_ColorData.m_fCIEv_;
		ar >> m_ColorData.m_fCIEx;
		ar >> m_ColorData.m_fCIEy;
		ar >> m_ColorData.m_fduv;
		ar >> m_ColorData.m_fGR;
		ar >> m_ColorData.m_fHW;
		ar >> m_ColorData.m_fIntervalWL;
		ar >> m_ColorData.m_fIntTime;
		ar >> m_ColorData.m_fIp;
		ar >> m_ColorData.m_fIp_removeDark;
		ar >> m_ColorData.m_fLav;
		ar >> m_ColorData.m_fLd;
		ar >> m_ColorData.m_fLp;
		ar >> m_ColorData.m_fPh;
		ar >> m_ColorData.m_fPh_e;
		ar >> m_ColorData.m_fPur;
		ar >> m_ColorData.m_fRa;
		ar >> m_ColorData.m_fRR;
		ar >> m_ColorData.m_fTc;
		ar >> m_ColorData.m_fWL1;
		ar >> m_ColorData.m_fWL2;

		for (int i = 0; i < 15; i++)
		{
			ar >> m_ColorData.m_fRi[i];
		}

		ar >> m_ColorData.m_iPLLength;

		for (int j = 0; j < m_ColorData.m_iPLLength; j++)
		{
			float fValue;
			ar >> fValue;
			m_ColorData.m_fPL[j] = fValue;
		}
		////////////////////////////////////////////

		int iCount = 0;
		ar>>iCount;
		m_fValue.RemoveAll();
		for (int i = 0; i < iCount; i++)
		{
			float fTemp;

			ar>>fTemp;
			m_fValue.Add(fTemp);
		}

        if(iVer >= 100)
        {
            ar >> m_strLedModel;
        }
        else
        {
            m_strLedModel = _T("");
        }

		if(iVer >= 102)
		{
			ar >> m_bHaveTestSaft;
			ar >> m_bSaftOK; //安规合格与否
			ar >> m_fSaft_R; //绝缘电阻
			ar >> m_fSaftLimit_R;
			ar >> m_fSaft_V; //耐压电流
			ar >> m_fSaftLimit_V;
			ar >> m_fSaft_C; //泄露电流
			ar >> m_fSaftLimit_C;
		}
		else
		{
			m_bHaveTestSaft = FALSE;
		}
		if(iVer >= 103)
		{
			ar >> m_iSDCMType;
			ar >> m_strSDCMSta;
			ar >> m_fSDCM;
			ar >> m_bInPoly;
		}
	}
}

CLedData & CLedData::operator = (CLedData & data)
{
	if (this == &data)
	{
		return * this;
	}

	this->m_bDataValid		= data.m_bDataValid;

	this->m_ulID			= data.m_ulID;
	this->m_fCurrentA		= data.m_fCurrentA;
	this->m_fPowerFactor	= data.m_fPowerFactor;
	this->m_fPowerW			= data.m_fPowerW;
	this->m_fVoltageV		= data.m_fVoltageV;
	this->m_fFrequencyHz	= data.m_fFrequencyHz;

	this->m_ColorData		= data.m_ColorData;
    this->m_strLedModel		= data.m_strLedModel;

	this->m_fValue.RemoveAll();
	this->m_fValue.Copy(data.m_fValue);
    this->m_bNotMoveLine = data.m_bNotMoveLine;
    this->m_strSN = data.m_strSN;

	this->m_bHaveTestSaft	= data.m_bHaveTestSaft;
	this->m_bSaftOK			= data.m_bSaftOK; //安规合格与否
	this->m_fSaft_R			= data.m_fSaft_R; //绝缘电阻
	this->m_fSaftLimit_R	= data.m_fSaftLimit_R;
	this->m_fSaft_V			= data.m_fSaft_V; //耐压电流
	this->m_fSaftLimit_V	= data.m_fSaftLimit_V;
	this->m_fSaft_C			= data.m_fSaft_C; //泄露电流
	this->m_fSaftLimit_C	= data.m_fSaftLimit_C;

	this->m_iSDCMType		= data.m_iSDCMType;	//类型 椭圆还是多边形
	this->m_strSDCMSta		= data.m_strSDCMSta;//色容差选择的标准
	this->m_fSDCM			= data.m_fSDCM;		//椭圆算出的色容差值
	this->m_bInPoly			= data.m_bInPoly;	//多边形 是否在内

	return *this;
}