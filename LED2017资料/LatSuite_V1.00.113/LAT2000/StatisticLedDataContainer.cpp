#include "StdAfx.h"
#include "StatisticLedDataContainer.h"
#include "LAT2000.h"
#include "LAT2000Doc.h"
#include "_column.h"
#include "math.h"

int g_iEveryDistribution_Oper[DISTRIBUTION_NUM - 1] = {- 2, -1, 0, 1, 2}; 

CStatisticLedDataContainer::CStatisticLedDataContainer(void)
{
    m_iCanStatisticParaNum = PARA_NUM;
    m_pParaStatistic = new BOOL[m_iCanStatisticParaNum];
    for (int i = 0; i < m_iCanStatisticParaNum; i++)
    {
        m_pParaStatistic[i] = TRUE;
    }

    m_StatisticPara.RemoveAll();
    toStatisticPara();
    m_StatisticParaMode = STATISTIC_ALL;
    m_iQLEDNum			= 0;
    m_iUnQLEDNum		= 0;
    m_iUnOnLEDNum		= 0;
    m_bStatisticQArray.RemoveAll();
    m_bStatisticUnONArray.RemoveAll();
}


CStatisticLedDataContainer::~CStatisticLedDataContainer(void)
{
    delete []m_pParaStatistic;
}



int CStatisticLedDataContainer::GetCanStatisticParaNum()
{
    return m_iCanStatisticParaNum;
}


int CStatisticLedDataContainer::GetStatisticParaNum()
{
    return m_StatisticPara.GetSize();
}


void CStatisticLedDataContainer::SetbStatisticPara(BOOL bStatistic[])
{
    for (int i = 0; i < m_iCanStatisticParaNum; i ++)
    {
        m_pParaStatistic[i] = bStatistic[i];
    }
}


void CStatisticLedDataContainer::SetbStatisticPara(int iPara, BOOL bStatistic)
{
    m_pParaStatistic[iPara] = bStatistic;
}


BOOL CStatisticLedDataContainer::IsSelectedToStatistic(int iPara)
{
    return m_pParaStatistic[iPara];
}


CString CStatisticLedDataContainer::GetStatisticParaName(StatisticParaIndex iPara, int iType)
{
    if (iType == 1)
    {
        switch(iPara)
        {
        case STATISTIC_CURR:
            {
                return "电流(mA)";
            }
        case STATISTIC_VOL:
            {
                return "电压(A)";
            }
        case STATISTIC_FRE:
            {
                return "频率(Hz)";
            }
        case STATISTIC_POW:
            {
                return "功率(W)";
            }
        case STATISTIC_FACTOR:
            {
                return "功率因数";
            }
        case STATISTIC_FLUX:
            {
                return "Flux(lm)";
            }
        case STATISTIC_TC:
            {
                return "Tc(K)";
            }
        case STATISTIC_CIE_X:
            {
                return "CIE-x";
            }
        case STATISTIC_CIE_Y:
            {
                return "CIE-y";
            }
        case STATISTIC_CIE_U:
            {
                return "CIE-u";
            }
        case STATISTIC_CIE_V:
            {
                return "CIE-v";
            }
        case STATISTIC_LD:
            {
                return "Ld(nm)";
            }
        case STATISTIC_HW:
            {
                return "HW(nm)";
            }
        case STATISTIC_LP:
            {
                return "Lp(nm)";
            }
        case STATISTIC_IP:
            {
                return "Ip";
            }
        case STATISTIC_PUR:
            {
                return "Pur(%)";
            }
        case STATISTIC_RA:
            {
                return "Ra";
            }
        case STATISTIC_EFFIC:
            {
                return "Eff(lm/W)";
            }
        case STATISTIC_R1:
            {
                return "R1"; 
            }
        case STATISTIC_R2:
            {
                return "R2"; 
            }
        case STATISTIC_R3:
            {
                return "R3"; 
            }
        case STATISTIC_R4:
            {
                return "R4"; 
            }
        case STATISTIC_R5:
            {
                return "R5"; 
            }
        case STATISTIC_R6:
            {
                return "R6"; 
            }
        case STATISTIC_R7:
            {
                return "R7"; 
            }
        case STATISTIC_R8:
            {
                return "R8"; 
            }
        case STATISTIC_R9:
            {
                return "R9"; 
            }
        case STATISTIC_RR:
            {
                return "红色比"; 
            }
        case STATISTIC_GR:
            {
                return "绿色比"; 
            }
        case STATISTIC_BR:
            {
                return "蓝色比"; 
            }
        default:
            return "";

        }
    }
    else  if(iType == 0)
    {
        switch(iPara)
        {
        case STATISTIC_CURR:
            {
                return "电流";
            }
        case STATISTIC_VOL:
            {
                return "电压";
            }
        case STATISTIC_FRE:
            {
                return "频率";
            }
        case STATISTIC_POW:
            {
                return "功率";
            }
        case STATISTIC_FACTOR:
            {
                return "功率因数";
            }
        case STATISTIC_FLUX:
            {
                return "Flux";
            }
        case STATISTIC_TC:
            {
                return "Tc";
            }
        case STATISTIC_CIE_X:
            {
                return "CIE-x";
            }
        case STATISTIC_CIE_Y:
            {
                return "CIE-y";
            }
        case STATISTIC_CIE_U:
            {
                return "CIE-u";
            }
        case STATISTIC_CIE_V:
            {
                return "CIE-v";
            }
        case STATISTIC_LD:
            {
                return "Ld";
            }
        case STATISTIC_HW:
            {
                return "HW";
            }
        case STATISTIC_LP:
            {
                return "Lp";
            }
        case STATISTIC_IP:
            {
                return "Ip";
            }
        case STATISTIC_PUR:
            {
                return "Pur";
            }
        case STATISTIC_RA:
            {
                return "Ra";
            }
        case STATISTIC_EFFIC:
            {
                return "Eff";
            }
        case STATISTIC_R1:
            {
                return "R1"; 
            }
        case STATISTIC_R2:
            {
                return "R2"; 
            }
        case STATISTIC_R3:
            {
                return "R3"; 
            }
        case STATISTIC_R4:
            {
                return "R4"; 
            }
        case STATISTIC_R5:
            {
                return "R5"; 
            }
        case STATISTIC_R6:
            {
                return "R6"; 
            }
        case STATISTIC_R7:
            {
                return "R7"; 
            }
        case STATISTIC_R8:
            {
                return "R8"; 
            }
        case STATISTIC_R9:
            {
                return "R9"; 
            }
        case STATISTIC_RR:
            {
                return "红色比"; 
            }
        case STATISTIC_GR:
            {
                return "绿色比"; 
            }
        case STATISTIC_BR:
            {
                return "蓝色比"; 
            }
        default:
            return "";

        }
    }
    else  if(iType == 2)
    {
        switch(iPara)
        {
        case STATISTIC_CURR:
            {
                return "电流 分布数";
            }
        case STATISTIC_VOL:
            {
                return "电压 分布数";
            }
        case STATISTIC_FRE:
            {
                return "频率 分布数";
            }
        case STATISTIC_POW:
            {
                return "功率 分布数";
            }
        case STATISTIC_FACTOR:
            {
                return "功率因数 分布数";
            }
        case STATISTIC_FLUX:
            {
                return "Flux 分布数";
            }
        case STATISTIC_TC:
            {
                return "Tc 分布数";
            }
        case STATISTIC_CIE_X:
            {
                return "CIE-x 分布数";
            }
        case STATISTIC_CIE_Y:
            {
                return "CIE-y 分布数";
            }
        case STATISTIC_CIE_U:
            {
                return "CIE-u 分布数";
            }
        case STATISTIC_CIE_V:
            {
                return "CIE-v 分布数";
            }
        case STATISTIC_LD:
            {
                return "Ld 分布数";
            }
        case STATISTIC_HW:
            {
                return "HW 分布数";
            }
        case STATISTIC_LP:
            {
                return "Lp 分布数";
            }
        case STATISTIC_IP:
            {
                return "Ip 分布数";
            }
        case STATISTIC_PUR:
            {
                return "Pur 分布数";
            }
        case STATISTIC_RA:
            {
                return "Ra 分布数";
            }
        case STATISTIC_EFFIC:
            {
                return "Eff 分布数";
            }
        case STATISTIC_R1:
            {
                return "R1 分布数"; 
            }
        case STATISTIC_R2:
            {
                return "R2 分布数"; 
            }
        case STATISTIC_R3:
            {
                return "R3 分布数"; 
            }
        case STATISTIC_R4:
            {
                return "R4 分布数"; 
            }
        case STATISTIC_R5:
            {
                return "R5 分布数"; 
            }
        case STATISTIC_R6:
            {
                return "R6 分布数"; 
            }
        case STATISTIC_R7:
            {
                return "R7 分布数"; 
            }
        case STATISTIC_R8:
            {
                return "R8 分布数"; 
            }
        case STATISTIC_R9:
            {
                return "R9 分布数"; 
            }
        case STATISTIC_RR:
            {
                return "红色比 分布数"; 
            }
        case STATISTIC_GR:
            {
                return "绿色比 分布数"; 
            }
        case STATISTIC_BR:
            {
                return "蓝色比 分布数"; 
            }
        default:
            return "";
        }   
    }
   
    return "";    

}
int  CStatisticLedDataContainer::GetQLEDNum()
{
    return m_iQLEDNum;
}


int  CStatisticLedDataContainer::GetUnQLEDNum()
{
    return m_iUnQLEDNum;
}


int  CStatisticLedDataContainer::GetUnONLEDNum()
{
    return m_iUnOnLEDNum;
}


float  CStatisticLedDataContainer::GetQLEDNumPer()
{
    return m_iQLEDNum * 100.0f / (m_iQLEDNum + m_iUnQLEDNum + m_iUnOnLEDNum);
}


float CStatisticLedDataContainer:: GetUnQLEDNumPer()
{
    return m_iUnQLEDNum * 100.0f / (m_iQLEDNum + m_iUnQLEDNum + m_iUnOnLEDNum);
}


float  CStatisticLedDataContainer::GetUnONLEDNumPer()
{
    return m_iUnOnLEDNum * 100.0f / (m_iQLEDNum + m_iUnQLEDNum + m_iUnOnLEDNum);
}


void CStatisticLedDataContainer::SetStatisticParaMode(StatisticParaMode Mode)
{
    m_StatisticParaMode = Mode; 
}


void CStatisticLedDataContainer::CalcStatisticMinMax(CArray<float, float> &fArray, float &fAvg, float &fMax, float &fMin,
    float &fMax_D, float &fTheta)
{
    fAvg = 0;
    fMax = 0;
    fMin = 0;
    fMax_D = 0;
    fTheta = 0;
    float fTotal = 0;
    for (int i  = 0; i < fArray.GetSize(); i ++)
    {
        if (i == 0)
        {
            fMax = fArray.GetAt(i);
            fMin = fArray.GetAt(i);
        }
        if (fArray.GetAt(i) > fMax)
        {
            fMax = fArray.GetAt(i);
        }
        if (fArray.GetAt(i) < fMin)
        {
            fMin = fArray.GetAt(i);
        }
        fTotal += fArray.GetAt(i);
    }
    fAvg = fTotal / fArray.GetSize();
    fTotal = 0;
    for (int i  = 0; i < fArray.GetSize(); i ++)
    {
        if (i == 0)
        {
            fMax_D = fabs(fArray.GetAt(i) - fAvg);
        }
        if (fabs(fArray.GetAt(i) - fAvg) > fMax_D)
        {
            fMax_D = fabs(fArray.GetAt(i) - fAvg);
        }
        fTotal += pow(fArray.GetAt(i) - fAvg , 2);
    }
    fTheta =  sqrtf(fTotal / (fArray.GetSize() - 1));
}   


void CStatisticLedDataContainer::CalcStatisticDistibutePara(CArray<float, float>&fArray, 
    float fAvg, float fTheta,  StatisticPara &para)
{
    for (int i = 0; i < DISTRIBUTION_NUM; i ++)
    {
        para.iEveryDistributionNum[i] = 0;
    }
    for (int i = 0; i < fArray.GetSize(); i++)
    {   
        if(fTheta == 0)
        {
            para.iEveryDistributionNum[(DISTRIBUTION_NUM + 1)/ 2] ++;
            continue;
        }

        for (int j = 0; j < DISTRIBUTION_NUM ; j ++)
        {     
            if (j == 0)
            {   
                if (fArray.GetAt(i) < fAvg + g_iEveryDistribution_Oper[j] * fTheta)
                {
                    para.iEveryDistributionNum[j] ++;                    
                    break;
                }
            }
            if (j == DISTRIBUTION_NUM - 1)
            {
                if (fArray.GetAt(i) >= fAvg + g_iEveryDistribution_Oper[j - 1] * fTheta)
                {
                    para.iEveryDistributionNum[j] ++;                    
                    break;
                }
            }
            else
            {
                if(fArray.GetAt(i) >= fAvg + g_iEveryDistribution_Oper[j - 1] * fTheta
                    && fArray.GetAt(i) < fAvg  + g_iEveryDistribution_Oper[j] * fTheta)
                {
                    para.iEveryDistributionNum[j] ++;                    
                    break;
                } 
            }              
        }
      /*
        if (fArray.GetAt(i) < fAvg - 2 * fTheta)
        {
            iLow2NegThetaNum ++;
        }
        else if(fArray.GetAt(i) >= fAvg - 2 * fTheta && fArray.GetAt(i) < fAvg - 1 * fTheta)
        {
            i2NegThetato1NegThetaNum ++;
        }
        else if(fArray.GetAt(i) >= fAvg - 1 * fTheta && fArray.GetAt(i) < fAvg)
        {
            i1NegThetato0Num ++;
        }
        else if(fArray.GetAt(i) >= fAvg && fArray.GetAt(i) < fAvg + 1 * fTheta)
        {
            i0to1OppThetaNum ++;
        }
        else if(fArray.GetAt(i) >= fAvg + 1 * fTheta && fArray.GetAt(i) < fAvg + 2 * fTheta)
        {
            i1OppThetato2ThetaNum ++;
        }
        else
        {
            iOver2OppThetaNum ++;
        }  
        */
    }
}


void CStatisticLedDataContainer::toStatisticPara()
{
    int i, j;
    m_iQLEDNum = 0;
    m_iUnQLEDNum = 0;
    m_iUnOnLEDNum = 0;
    m_bStatisticQArray.RemoveAll();
    m_bStatisticUnONArray.RemoveAll();
    BOOL bMoveLineHaveAdd = FALSE;
	CArray<CLedData, CLedData&> data;
	data.RemoveAll();
    for (i = m_data.GetSize() - 1; i >= 0 ; i --)
    {
        if (bMoveLineHaveAdd)
        {
             if (m_data.GetAt(i).m_bNotMoveLine == FALSE)
            {
                bMoveLineHaveAdd = FALSE;
            }
            continue;
        }
        if (bMoveLineHaveAdd == FALSE)
        {
            if (m_data.GetAt(i).m_bNotMoveLine == TRUE)
            {
                bMoveLineHaveAdd = TRUE;
            }
        }
    
		CLedData dataTemp;
		dataTemp = m_data.GetAt(i); 
		data.Add(dataTemp);
        if (m_data.GetAt(i).IsLEDON())
        {
			int iTypeFail = 0;
            if (m_TestSettingsData.IsQulified(m_data.GetAt(i), iTypeFail))
            {
                m_bStatisticQArray.Add(TRUE);
                m_iQLEDNum ++;
            }
            else
            {
                m_bStatisticQArray.Add(FALSE);
                m_iUnQLEDNum ++;
            }
            m_bStatisticUnONArray.Add(FALSE);
        }
        else
        {
            m_bStatisticQArray.Add(FALSE); 
            m_bStatisticUnONArray.Add(TRUE);
            m_iUnOnLEDNum ++;
        }
    }
    m_StatisticPara.RemoveAll();
  
    CArray<float, float>fArray;
    float fAvg, fMax, fMin,
        fMax_D, fTheta;
    for (i = 0; i < m_iCanStatisticParaNum; i++)
    {     
        fArray.RemoveAll();
        if (m_pParaStatistic[i])
        {
            StatisticPara para;
            para.bStatistic = FALSE;
            para.iIndex = StatisticParaIndex(i);

            switch(para.iIndex)
            {
            case STATISTIC_CURR:
                {
                    for (j = 0; j < data.GetSize(); j ++)
                    {
                        if (!m_bStatisticUnONArray.GetAt(j))
                        {
                            if (m_StatisticParaMode == STATISTIC_ALL)
                            {
                                fArray.Add(data.GetAt(j).m_fCurrentA * 1000);
                            }
                            else
                            {
                                if (m_bStatisticQArray.GetAt(j))
                                {
                                    fArray.Add(data.GetAt(j).m_fCurrentA * 1000);
                                }
                            }
                        }
                    }
                    //calc
                    if (fArray.GetSize() < 2)
                    {
                        break;
                    }
                    para.bStatistic = TRUE;
                    CalcStatisticMinMax(fArray, fAvg, fMax, fMin,
                        fMax_D, fTheta);
                    para.strAvg.Format("%.1f", fAvg);
                    para.strMax.Format("%.1f", fMax);
                    para.strMin.Format("%.1f", fMin);
                    para.strMax_D.Format("%.1f", fMax_D);
                    para.strTheta.Format("%.1f", fTheta);

                    CalcStatisticDistibutePara(fArray, fAvg, fTheta,
                        para);
                    para.CalcDistributionPer();
                    break;
                }
            case STATISTIC_VOL:
                {
                    for (j = 0; j < data.GetSize(); j ++)
                    {
                        if (!m_bStatisticUnONArray.GetAt(j))
                        {
                            if (m_StatisticParaMode == STATISTIC_ALL)
                            {
                                fArray.Add(data.GetAt(j).m_fVoltageV);
                            }
                            else
                            {
                                if (m_bStatisticQArray.GetAt(j))
                                {
                                    fArray.Add(data.GetAt(j).m_fVoltageV);
                                }
                            }
                        }
                    }
                    //calc
                    if (fArray.GetSize() < 2)
                    {
                        break;
                    }
                    para.bStatistic = TRUE;
                    CalcStatisticMinMax(fArray, fAvg, fMax, fMin,
                        fMax_D, fTheta);
                    para.strAvg.Format("%.1f", fAvg);
                    para.strMax.Format("%.1f", fMax);
                    para.strMin.Format("%.1f", fMin);
                    para.strMax_D.Format("%.1f", fMax_D);
                    para.strTheta.Format("%.1f", fTheta);
                    CalcStatisticDistibutePara(fArray, fAvg, fTheta,
                        para);
                    para.CalcDistributionPer();
                    break;
                }
            case STATISTIC_FRE:
                {
                    for (j = 0; j < data.GetSize(); j ++)
                    {
                        if (!m_bStatisticUnONArray.GetAt(j))
                        {
                            if (m_StatisticParaMode == STATISTIC_ALL)
                            {
                                fArray.Add(data.GetAt(j).m_fFrequencyHz);
                            }
                            else
                            {
                                if (m_bStatisticQArray.GetAt(j))
                                {
                                    fArray.Add(data.GetAt(j).m_fFrequencyHz);
                                }
                            }
                        }
                    }
                    //calc
                    if (fArray.GetSize() < 2)
                    {
                        break;
                    }
                    para.bStatistic = TRUE;
                    CalcStatisticMinMax(fArray, fAvg, fMax, fMin,
                        fMax_D, fTheta);
                    para.strAvg.Format("%.0f", fAvg);
                    para.strMax.Format("%.0f", fMax);
                    para.strMin.Format("%.0f", fMin);
                    para.strMax_D.Format("%.0f", fMax_D);
                    para.strTheta.Format("%.0f", fTheta);
                    CalcStatisticDistibutePara(fArray, fAvg, fTheta,
                        para);
                    para.CalcDistributionPer();
                    break;
                }
            case STATISTIC_POW:
                {
                    for (j = 0; j < data.GetSize(); j ++)
                    {
                        if (!m_bStatisticUnONArray.GetAt(j))
                        {
                            if (m_StatisticParaMode == STATISTIC_ALL)
                            {
                                fArray.Add(data.GetAt(j).m_fPowerW);
                            }
                            else
                            {
                                if (m_bStatisticQArray.GetAt(j))
                                {
                                    fArray.Add(data.GetAt(j).m_fPowerW);
                                }
                            }
                        }
                    }
                    //calc
                    if (fArray.GetSize() < 2)
                    {
                        break;
                    }
                    para.bStatistic = TRUE;
                    CalcStatisticMinMax(fArray, fAvg, fMax, fMin,
                        fMax_D, fTheta);
                    para.strAvg.Format("%.2f", fAvg);
                    para.strMax.Format("%.2f", fMax);
                    para.strMin.Format("%.2f", fMin);
                    para.strMax_D.Format("%.2f", fMax_D);
                    para.strTheta.Format("%.2f", fTheta);
                    CalcStatisticDistibutePara(fArray, fAvg, fTheta,
                        para);
                    para.CalcDistributionPer();
                    break;
                }
            case STATISTIC_FACTOR:
                {
                    for (j = 0; j < data.GetSize(); j ++)
                    {
                        if (!m_bStatisticUnONArray.GetAt(j))
                        {
                            if (m_StatisticParaMode == STATISTIC_ALL)
                            {
                                fArray.Add(data.GetAt(j).m_fPowerFactor);
                            }
                            else
                            {
                                if (m_bStatisticQArray.GetAt(j))
                                {
                                    fArray.Add(data.GetAt(j).m_fPowerFactor);
                                }
                            }
                        }
                    }
                    //calc
                    if (fArray.GetSize() < 2)
                    {
                        break;
                    }
                    para.bStatistic = TRUE;
                    CalcStatisticMinMax(fArray, fAvg, fMax, fMin,
                        fMax_D, fTheta);
                    para.strAvg.Format("%.4f", fAvg);
                    para.strMax.Format("%.4f", fMax);
                    para.strMin.Format("%.4f", fMin);
                    para.strMax_D.Format("%.4f", fMax_D);
                    para.strTheta.Format("%.4f", fTheta);
                    CalcStatisticDistibutePara(fArray, fAvg, fTheta,
                        para);
                    para.CalcDistributionPer();
                    break;
                }
            case STATISTIC_FLUX:
                {
                    for (j = 0; j < data.GetSize(); j ++)
                    {
                        if (!m_bStatisticUnONArray.GetAt(j))
                        {
                            if (m_StatisticParaMode == STATISTIC_ALL)
                            {
                                fArray.Add(data.GetAt(j).m_ColorData.m_fPh);
                            }
                            else
                            {
                                if (m_bStatisticQArray.GetAt(j))
                                {
                                    fArray.Add(data.GetAt(j).m_ColorData.m_fPh);
                                }
                            }
                        }
                    }
                    //calc
                    if (fArray.GetSize() < 2)
                    {
                        break;
                    }
                    para.bStatistic = TRUE;
                    CalcStatisticMinMax(fArray, fAvg, fMax, fMin,
                        fMax_D, fTheta);
                    para.strAvg.Format("%.4f", fAvg);
                    para.strMax.Format("%.4f", fMax);
                    para.strMin.Format("%.4f", fMin);
                    para.strMax_D.Format("%.4f", fMax_D);
                    para.strTheta.Format("%.4f", fTheta);
                    CalcStatisticDistibutePara(fArray, fAvg, fTheta,
                        para);
                    para.CalcDistributionPer();                
                    break;
                }
            case STATISTIC_TC:
                {   
                    for (j = 0; j < data.GetSize(); j ++)
                    {
                        if (!m_bStatisticUnONArray.GetAt(j))
                        {
                            if (m_StatisticParaMode == STATISTIC_ALL)
                            {
                                fArray.Add(data.GetAt(j).m_ColorData.m_fTc);
                            }
                            else
                            {
                                if (m_bStatisticQArray.GetAt(j))
                                {
                                    fArray.Add(data.GetAt(j).m_ColorData.m_fTc);
                                }
                            }
                        }
                    }
                    //calc
                    if (fArray.GetSize() < 2)
                    {
                        break;
                    }
                    para.bStatistic = TRUE;
                    CalcStatisticMinMax(fArray, fAvg, fMax, fMin,
                        fMax_D, fTheta);
                    para.strAvg.Format("%.0f", fAvg);
                    para.strMax.Format("%.0f", fMax);
                    para.strMin.Format("%.0f", fMin);
                    para.strMax_D.Format("%.0f", fMax_D);
                    para.strTheta.Format("%.0f", fTheta);
                    CalcStatisticDistibutePara(fArray, fAvg, fTheta,
                        para);
                    para.CalcDistributionPer();
                    break;
                }
            case STATISTIC_CIE_X:
                {
                    for (j = 0; j < data.GetSize(); j ++)
                    {
                        if (!m_bStatisticUnONArray.GetAt(j))
                        {
                            if (m_StatisticParaMode == STATISTIC_ALL)
                            {
                                fArray.Add(data.GetAt(j).m_ColorData.m_fCIEx);
                            }
                            else
                            {
                                if (m_bStatisticQArray.GetAt(j))
                                {
                                    fArray.Add(data.GetAt(j).m_ColorData.m_fCIEx);
                                }
                            }
                        }
                    }
                    //calc
                    if (fArray.GetSize() < 2)
                    {
                        break;
                    }
                    para.bStatistic = TRUE;
                    CalcStatisticMinMax(fArray, fAvg, fMax, fMin,
                        fMax_D, fTheta);
                    para.strAvg.Format("%.4f", fAvg);
                    para.strMax.Format("%.4f", fMax);
                    para.strMin.Format("%.4f", fMin);
                    para.strMax_D.Format("%.4f", fMax_D);
                    para.strTheta.Format("%.4f", fTheta);
                    CalcStatisticDistibutePara(fArray, fAvg, fTheta,
                        para);
                    para.CalcDistributionPer();
                    break;
                }
            case STATISTIC_CIE_Y:
                {
                    for (j = 0; j < data.GetSize(); j ++)
                    {
                        if (!m_bStatisticUnONArray.GetAt(j))
                        {
                            if (m_StatisticParaMode == STATISTIC_ALL)
                            {
                                fArray.Add(data.GetAt(j).m_ColorData.m_fCIEy);
                            }
                            else
                            {
                                if (m_bStatisticQArray.GetAt(j))
                                {
                                    fArray.Add(data.GetAt(j).m_ColorData.m_fCIEy);
                                }
                            }
                        }
                    }
                    //calc
                    if (fArray.GetSize() < 2)
                    {
                        break;
                    }
                    para.bStatistic = TRUE;
                    CalcStatisticMinMax(fArray, fAvg, fMax, fMin,
                        fMax_D, fTheta);
                    para.strAvg.Format("%.4f", fAvg);
                    para.strMax.Format("%.4f", fMax);
                    para.strMin.Format("%.4f", fMin);
                    para.strMax_D.Format("%.4f", fMax_D);
                    para.strTheta.Format("%.4f", fTheta);
                    CalcStatisticDistibutePara(fArray, fAvg, fTheta,
                        para);
                    para.CalcDistributionPer();
                    break;
                }
            case STATISTIC_CIE_U:
                {
                    for (j = 0; j < data.GetSize(); j ++)
                    {
                        if (!m_bStatisticUnONArray.GetAt(j))
                        {
                            if (m_StatisticParaMode == STATISTIC_ALL)
                            {
                                fArray.Add(data.GetAt(j).m_ColorData.m_fCIEu_);
                            }
                            else
                            {
                                if (m_bStatisticQArray.GetAt(j))
                                {
                                    fArray.Add(data.GetAt(j).m_ColorData.m_fCIEu_);
                                }
                            }
                        }
                    }
                    //calc
                    if (fArray.GetSize() < 2)
                    {
                        break;
                    }
                    para.bStatistic = TRUE;
                    CalcStatisticMinMax(fArray, fAvg, fMax, fMin,
                        fMax_D, fTheta);
                    para.strAvg.Format("%.4f", fAvg);
                    para.strMax.Format("%.4f", fMax);
                    para.strMin.Format("%.4f", fMin);
                    para.strMax_D.Format("%.4f", fMax_D);
                    para.strTheta.Format("%.4f", fTheta);
                    CalcStatisticDistibutePara(fArray, fAvg, fTheta,
                        para);
                    para.CalcDistributionPer();
                    break;
                }
            case STATISTIC_CIE_V:
                {
                    for (j = 0; j < data.GetSize(); j ++)
                    {
                        if (!m_bStatisticUnONArray.GetAt(j))
                        {
                            if (m_StatisticParaMode == STATISTIC_ALL)
                            {
                                fArray.Add(data.GetAt(j).m_ColorData.m_fCIEv_);
                            }
                            else
                            {
                                if (m_bStatisticQArray.GetAt(j))
                                {
                                    fArray.Add(data.GetAt(j).m_ColorData.m_fCIEv_);
                                }
                            }
                        }
                    }
                    //calc
                    if (fArray.GetSize() < 2)
                    {
                        break;
                    }
                    para.bStatistic = TRUE;
                    CalcStatisticMinMax(fArray, fAvg, fMax, fMin,
                        fMax_D, fTheta);
                    para.strAvg.Format("%.4f", fAvg);
                    para.strMax.Format("%.4f", fMax);
                    para.strMin.Format("%.4f", fMin);
                    para.strMax_D.Format("%.4f", fMax_D);
                    para.strTheta.Format("%.4f", fTheta);
                    CalcStatisticDistibutePara(fArray, fAvg, fTheta,
                        para);
                    para.CalcDistributionPer();
                    break;
                }
            case STATISTIC_LD:
                {
                    for (j = 0; j < data.GetSize(); j ++)
                    {
                        if (!m_bStatisticUnONArray.GetAt(j))
                        {
                            if (m_StatisticParaMode == STATISTIC_ALL)
                            {
                                fArray.Add(data.GetAt(j).m_ColorData.m_fLd);
                            }
                            else
                            {
                                if (m_bStatisticQArray.GetAt(j))
                                {
                                    fArray.Add(data.GetAt(j).m_ColorData.m_fLd);
                                }
                            }
                        }
                    }
                    //calc
                    if (fArray.GetSize() < 2)
                    {
                        break;
                    }
                    para.bStatistic = TRUE;
                    CalcStatisticMinMax(fArray, fAvg, fMax, fMin,
                        fMax_D, fTheta);
                    para.strAvg.Format("%.1f", fAvg);
                    para.strMax.Format("%.1f", fMax);
                    para.strMin.Format("%.1f", fMin);
                    para.strMax_D.Format("%.1f", fMax_D);
                    para.strTheta.Format("%.1f", fTheta);
                    CalcStatisticDistibutePara(fArray, fAvg, fTheta,
                        para);
                    para.CalcDistributionPer();
                    break;
                }
            case STATISTIC_HW:
                {
                    for (j = 0; j < data.GetSize(); j ++)
                    {
                        if (!m_bStatisticUnONArray.GetAt(j))
                        {
                            if (m_StatisticParaMode == STATISTIC_ALL)
                            {
                                fArray.Add(data.GetAt(j).m_ColorData.m_fHW);
                            }
                            else
                            {
                                if (m_bStatisticQArray.GetAt(j))
                                {
                                    fArray.Add(data.GetAt(j).m_ColorData.m_fHW);
                                }
                            }
                        }
                    }
                    //calc
                    if (fArray.GetSize() < 2)
                    {
                        break;
                    }
                    para.bStatistic = TRUE;
                    CalcStatisticMinMax(fArray, fAvg, fMax, fMin,
                        fMax_D, fTheta);
                    para.strAvg.Format("%.1f", fAvg);
                    para.strMax.Format("%.1f", fMax);
                    para.strMin.Format("%.1f", fMin);
                    para.strMax_D.Format("%.1f", fMax_D);
                    para.strTheta.Format("%.1f", fTheta);
                    CalcStatisticDistibutePara(fArray, fAvg, fTheta,
                        para);
                    para.CalcDistributionPer();
                    break;
                }
            case STATISTIC_LP:
                {
                    for (j = 0; j < data.GetSize(); j ++)
                    {
                        if (!m_bStatisticUnONArray.GetAt(j))
                        {
                            if (m_StatisticParaMode == STATISTIC_ALL)
                            {
                                fArray.Add(data.GetAt(j).m_ColorData.m_fLp);
                            }
                            else
                            {
                                if (m_bStatisticQArray.GetAt(j))
                                {
                                    fArray.Add(data.GetAt(j).m_ColorData.m_fLp);
                                }
                            }
                        }
                    }
                    //calc
                    if (fArray.GetSize() < 2)
                    {
                        break;
                    }
                    para.bStatistic = TRUE;
                    CalcStatisticMinMax(fArray, fAvg, fMax, fMin,
                        fMax_D, fTheta);
                    para.strAvg.Format("%.1f", fAvg);
                    para.strMax.Format("%.1f", fMax);
                    para.strMin.Format("%.1f", fMin);
                    para.strMax_D.Format("%.1f", fMax_D);
                    para.strTheta.Format("%.1f", fTheta);
                    CalcStatisticDistibutePara(fArray, fAvg, fTheta,
                        para);
                    para.CalcDistributionPer();
                    break;
                }
            case STATISTIC_IP:
                {
                    for (j = 0; j < data.GetSize(); j ++)
                    {
                        if (!m_bStatisticUnONArray.GetAt(j))
                        {
                            if (m_StatisticParaMode == STATISTIC_ALL)
                            {
                                fArray.Add(data.GetAt(j).m_ColorData.m_fIp);
                            }
                            else
                            {
                                if (m_bStatisticQArray.GetAt(j))
                                {
                                    fArray.Add(data.GetAt(j).m_ColorData.m_fIp);
                                }
                            }
                        }
                    }
                    //calc
                    if (fArray.GetSize() < 2)
                    {
                        break;
                    }
                    para.bStatistic = TRUE;
                    CalcStatisticMinMax(fArray, fAvg, fMax, fMin,
                        fMax_D, fTheta);
                    para.strAvg.Format("%.0f", fAvg);
                    para.strMax.Format("%.0f", fMax);
                    para.strMin.Format("%.0f", fMin);
                    para.strMax_D.Format("%.0f", fMax_D);
                    para.strTheta.Format("%.0f", fTheta);
                    CalcStatisticDistibutePara(fArray, fAvg, fTheta,
                        para);
                    para.CalcDistributionPer();
                    break;
                }
            case STATISTIC_PUR:
                {
                    for (j = 0; j < data.GetSize(); j ++)
                    {
                        if (!m_bStatisticUnONArray.GetAt(j))
                        {
                            if (m_StatisticParaMode == STATISTIC_ALL)
                            {
                                fArray.Add(data.GetAt(j).m_ColorData.m_fPur);
                            }
                            else
                            {
                                if (m_bStatisticQArray.GetAt(j))
                                {
                                    fArray.Add(data.GetAt(j).m_ColorData.m_fPur);
                                }
                            }
                        }
                    }
                    //calc
                    if (fArray.GetSize() < 2)
                    {
                        break;
                    }
                    para.bStatistic = TRUE;
                    CalcStatisticMinMax(fArray, fAvg, fMax, fMin,
                        fMax_D, fTheta);
                    para.strAvg.Format("%.1f", fAvg);
                    para.strMax.Format("%.1f", fMax);
                    para.strMin.Format("%.1f", fMin);
                    para.strMax_D.Format("%.1f", fMax_D);
                    para.strTheta.Format("%.1f", fTheta);
                    CalcStatisticDistibutePara(fArray, fAvg, fTheta,
                        para);
                    para.CalcDistributionPer();
                    break;
                }
            case STATISTIC_RA:
                {
                    for (j = 0; j < data.GetSize(); j ++)
                    {
                        if (!m_bStatisticUnONArray.GetAt(j))
                        {
                            if (m_StatisticParaMode == STATISTIC_ALL)
                            {
                                fArray.Add(data.GetAt(j).m_ColorData.m_fRa);
                            }
                            else
                            {
                                if (m_bStatisticQArray.GetAt(j))
                                {
                                    fArray.Add(data.GetAt(j).m_ColorData.m_fRa);
                                }
                            }
                        }
                    }
                    //calc
                    if (fArray.GetSize() < 2)
                    {
                        break;
                    }
                    para.bStatistic = TRUE;
                    CalcStatisticMinMax(fArray, fAvg, fMax, fMin,
                        fMax_D, fTheta);
                    para.strAvg.Format("%.1f", fAvg);
                    para.strMax.Format("%.1f", fMax);
                    para.strMin.Format("%.1f", fMin);
                    para.strMax_D.Format("%.1f", fMax_D);
                    para.strTheta.Format("%.1f", fTheta);
                    CalcStatisticDistibutePara(fArray, fAvg, fTheta,
                        para);
                    para.CalcDistributionPer();
                    break;
                }
            case STATISTIC_EFFIC:
                {
                    for (j = 0; j < data.GetSize(); j ++)
                    {
                        if (!m_bStatisticUnONArray.GetAt(j))
                        {
                            if (m_StatisticParaMode == STATISTIC_ALL)
                            {
                                fArray.Add(data[j].m_ColorData.m_fPh
                                    / data[j].m_fPowerW);
                            }
                            else
                            {
                                if (m_bStatisticQArray.GetAt(j))
                                {
                                    fArray.Add(data[j].m_ColorData.m_fPh
                                        / data[j].m_fPowerW);
                                }
                            }
                        }
                    }
                    //calc
                    if (fArray.GetSize() < 2)
                    {
                        break;
                    }
                    para.bStatistic = TRUE;
                    CalcStatisticMinMax(fArray, fAvg, fMax, fMin,
                        fMax_D, fTheta);
                    para.strAvg.Format("%.1f", fAvg);
                    para.strMax.Format("%.1f", fMax);
                    para.strMin.Format("%.1f", fMin);
                    para.strMax_D.Format("%.1f", fMax_D);
                    para.strTheta.Format("%.1f", fTheta);
                    CalcStatisticDistibutePara(fArray, fAvg, fTheta,
                        para);
                    para.CalcDistributionPer();
                    break;
                }
            case STATISTIC_R1:
                {
                    for (j = 0; j < data.GetSize(); j ++)
                    {
                        if (!m_bStatisticUnONArray.GetAt(j))
                        {
                            if (m_StatisticParaMode == STATISTIC_ALL)
                            {
                                fArray.Add(data.GetAt(j).m_ColorData.m_fRi[0]);
                            }
                            else
                            {
                                if (m_bStatisticQArray.GetAt(j))
                                {
                                    fArray.Add(data.GetAt(j).m_ColorData.m_fRi[0]);
                                }
                            }
                        }
                    }
                    //calc
                    if (fArray.GetSize() < 2)
                    {
                        break;
                    }
                    para.bStatistic = TRUE;
                    CalcStatisticMinMax(fArray, fAvg, fMax, fMin,
                        fMax_D, fTheta);
                    para.strAvg.Format("%.1f", fAvg);
                    para.strMax.Format("%.1f", fMax);
                    para.strMin.Format("%.1f", fMin);
                    para.strMax_D.Format("%.1f", fMax_D);
                    para.strTheta.Format("%.1f", fTheta);

                    CalcStatisticDistibutePara(fArray, fAvg, fTheta,
                        para);
                    para.CalcDistributionPer();
                    break;
                }
            case STATISTIC_R2:
                {
                    for (j = 0; j < data.GetSize(); j ++)
                    {
                        if (!m_bStatisticUnONArray.GetAt(j))
                        {
                            if (m_StatisticParaMode == STATISTIC_ALL)
                            {
                                fArray.Add(data.GetAt(j).m_ColorData.m_fRi[1]);
                            }
                            else
                            {
                                if (m_bStatisticQArray.GetAt(j))
                                {
                                    fArray.Add(data.GetAt(j).m_ColorData.m_fRi[1]);
                                }
                            }
                        }
                    }
                    //calc
                    if (fArray.GetSize() < 2)
                    {
                        break;
                    }
                    para.bStatistic = TRUE;
                    CalcStatisticMinMax(fArray, fAvg, fMax, fMin,
                        fMax_D, fTheta);
                    para.strAvg.Format("%.1f", fAvg);
                    para.strMax.Format("%.1f", fMax);
                    para.strMin.Format("%.1f", fMin);
                    para.strMax_D.Format("%.1f", fMax_D);
                    para.strTheta.Format("%.1f", fTheta);

                    CalcStatisticDistibutePara(fArray, fAvg, fTheta,
                        para);
                    para.CalcDistributionPer();
                    break;
                }
            case STATISTIC_R3:
                {
                    for (j = 0; j < data.GetSize(); j ++)
                    {
                        if (!m_bStatisticUnONArray.GetAt(j))
                        {
                            if (m_StatisticParaMode == STATISTIC_ALL)
                            {
                                fArray.Add(data.GetAt(j).m_ColorData.m_fRi[2]);
                            }
                            else
                            {
                                if (m_bStatisticQArray.GetAt(j))
                                {
                                    fArray.Add(data.GetAt(j).m_ColorData.m_fRi[2]);
                                }
                            }
                        }
                    }
                    //calc
                    if (fArray.GetSize() < 2)
                    {
                        break;
                    }
                    para.bStatistic = TRUE;
                    CalcStatisticMinMax(fArray, fAvg, fMax, fMin,
                        fMax_D, fTheta);
                    para.strAvg.Format("%.1f", fAvg);
                    para.strMax.Format("%.1f", fMax);
                    para.strMin.Format("%.1f", fMin);
                    para.strMax_D.Format("%.1f", fMax_D);
                    para.strTheta.Format("%.1f", fTheta);

                    CalcStatisticDistibutePara(fArray, fAvg, fTheta,
                        para);
                    para.CalcDistributionPer();
                    break;
                }
            case STATISTIC_R4:
                {
                    for (j = 0; j < data.GetSize(); j ++)
                    {
                        if (!m_bStatisticUnONArray.GetAt(j))
                        {
                            if (m_StatisticParaMode == STATISTIC_ALL)
                            {
                                fArray.Add(data.GetAt(j).m_ColorData.m_fRi[3]);
                            }
                            else
                            {
                                if (m_bStatisticQArray.GetAt(j))
                                {
                                    fArray.Add(data.GetAt(j).m_ColorData.m_fRi[3]);
                                }
                            }
                        }
                    }
                    //calc
                    if (fArray.GetSize() < 2)
                    {
                        break;
                    }
                    para.bStatistic = TRUE;
                    CalcStatisticMinMax(fArray, fAvg, fMax, fMin,
                        fMax_D, fTheta);
                    para.strAvg.Format("%.1f", fAvg);
                    para.strMax.Format("%.1f", fMax);
                    para.strMin.Format("%.1f", fMin);
                    para.strMax_D.Format("%.1f", fMax_D);
                    para.strTheta.Format("%.1f", fTheta);

                    CalcStatisticDistibutePara(fArray, fAvg, fTheta,
                        para);
                    para.CalcDistributionPer();
                    break;
                }
            case STATISTIC_R5:
                {
                    for (j = 0; j < data.GetSize(); j ++)
                    {
                        if (!m_bStatisticUnONArray.GetAt(j))
                        {
                            if (m_StatisticParaMode == STATISTIC_ALL)
                            {
                                fArray.Add(data.GetAt(j).m_ColorData.m_fRi[4]);
                            }
                            else
                            {
                                if (m_bStatisticQArray.GetAt(j))
                                {
                                    fArray.Add(data.GetAt(j).m_ColorData.m_fRi[4]);
                                }
                            }
                        }
                    }
                    //calc
                    if (fArray.GetSize() < 2)
                    {
                        break;
                    }
                    para.bStatistic = TRUE;
                    CalcStatisticMinMax(fArray, fAvg, fMax, fMin,
                        fMax_D, fTheta);
                    para.strAvg.Format("%.1f", fAvg);
                    para.strMax.Format("%.1f", fMax);
                    para.strMin.Format("%.1f", fMin);
                    para.strMax_D.Format("%.1f", fMax_D);
                    para.strTheta.Format("%.1f", fTheta);

                    CalcStatisticDistibutePara(fArray, fAvg, fTheta,
                        para);
                    para.CalcDistributionPer();
                    break;
                }
            case STATISTIC_R6:
                {
                    for (j = 0; j < data.GetSize(); j ++)
                    {
                        if (!m_bStatisticUnONArray.GetAt(j))
                        {
                            if (m_StatisticParaMode == STATISTIC_ALL)
                            {
                                fArray.Add(data.GetAt(j).m_ColorData.m_fRi[5]);
                            }
                            else
                            {
                                if (m_bStatisticQArray.GetAt(j))
                                {
                                    fArray.Add(data.GetAt(j).m_ColorData.m_fRi[5]);
                                }
                            }
                        }
                    }
                    //calc
                    if (fArray.GetSize() < 2)
                    {
                        break;
                    }
                    para.bStatistic = TRUE;
                    CalcStatisticMinMax(fArray, fAvg, fMax, fMin,
                        fMax_D, fTheta);
                    para.strAvg.Format("%.1f", fAvg);
                    para.strMax.Format("%.1f", fMax);
                    para.strMin.Format("%.1f", fMin);
                    para.strMax_D.Format("%.1f", fMax_D);
                    para.strTheta.Format("%.1f", fTheta);

                    CalcStatisticDistibutePara(fArray, fAvg, fTheta,
                        para);
                    para.CalcDistributionPer();
                    break;
                }
            case STATISTIC_R7:
                {
                    for (j = 0; j < data.GetSize(); j ++)
                    {
                        if (!m_bStatisticUnONArray.GetAt(j))
                        {
                            if (m_StatisticParaMode == STATISTIC_ALL)
                            {
                                fArray.Add(data.GetAt(j).m_ColorData.m_fRi[6]);
                            }
                            else
                            {
                                if (m_bStatisticQArray.GetAt(j))
                                {
                                    fArray.Add(data.GetAt(j).m_ColorData.m_fRi[6]);
                                }
                            }
                        }
                    }
                    //calc
                    if (fArray.GetSize() < 2)
                    {
                        break;
                    }
                    para.bStatistic = TRUE;
                    CalcStatisticMinMax(fArray, fAvg, fMax, fMin,
                        fMax_D, fTheta);
                    para.strAvg.Format("%.1f", fAvg);
                    para.strMax.Format("%.1f", fMax);
                    para.strMin.Format("%.1f", fMin);
                    para.strMax_D.Format("%.1f", fMax_D);
                    para.strTheta.Format("%.1f", fTheta);

                    CalcStatisticDistibutePara(fArray, fAvg, fTheta,
                        para);
                    para.CalcDistributionPer();
                    break;
                }
            case STATISTIC_R8:
                {
                    for (j = 0; j < data.GetSize(); j ++)
                    {
                        if (!m_bStatisticUnONArray.GetAt(j))
                        {
                            if (m_StatisticParaMode == STATISTIC_ALL)
                            {
                                fArray.Add(data.GetAt(j).m_ColorData.m_fRi[7]);
                            }
                            else
                            {
                                if (m_bStatisticQArray.GetAt(j))
                                {
                                    fArray.Add(data.GetAt(j).m_ColorData.m_fRi[7]);
                                }
                            }
                        }
                    }
                    //calc
                    if (fArray.GetSize() < 2)
                    {
                        break;
                    }
                    para.bStatistic = TRUE;
                    CalcStatisticMinMax(fArray, fAvg, fMax, fMin,
                        fMax_D, fTheta);
                    para.strAvg.Format("%.1f", fAvg);
                    para.strMax.Format("%.1f", fMax);
                    para.strMin.Format("%.1f", fMin);
                    para.strMax_D.Format("%.1f", fMax_D);
                    para.strTheta.Format("%.1f", fTheta);

                    CalcStatisticDistibutePara(fArray, fAvg, fTheta,
                        para);
                    para.CalcDistributionPer();
                    break;
                }
            case STATISTIC_R9:
                {
                    for (j = 0; j < data.GetSize(); j ++)
                    {
                        if (!m_bStatisticUnONArray.GetAt(j))
                        {
                            if (m_StatisticParaMode == STATISTIC_ALL)
                            {
                                fArray.Add(data.GetAt(j).m_ColorData.m_fRi[8]);
                            }
                            else
                            {
                                if (m_bStatisticQArray.GetAt(j))
                                {
                                    fArray.Add(data.GetAt(j).m_ColorData.m_fRi[8]);
                                }
                            }
                        }
                    }
                    //calc
                    if (fArray.GetSize() < 2)
                    {
                        break;
                    }
                    para.bStatistic = TRUE;
                    CalcStatisticMinMax(fArray, fAvg, fMax, fMin,
                        fMax_D, fTheta);
                    para.strAvg.Format("%.1f", fAvg);
                    para.strMax.Format("%.1f", fMax);
                    para.strMin.Format("%.1f", fMin);
                    para.strMax_D.Format("%.1f", fMax_D);
                    para.strTheta.Format("%.1f", fTheta);

                    CalcStatisticDistibutePara(fArray, fAvg, fTheta,
                        para);
                    para.CalcDistributionPer();
                    break;
                }
            case STATISTIC_RR:
                {
                    for (j = 0; j < data.GetSize(); j ++)
                    {
                        if (!m_bStatisticUnONArray.GetAt(j))
                        {
                            if (m_StatisticParaMode == STATISTIC_ALL)
                            {
                                fArray.Add(data.GetAt(j).m_ColorData.m_fRR);
                            }
                            else
                            {
                                if (m_bStatisticQArray.GetAt(j))
                                {
                                    fArray.Add(data.GetAt(j).m_ColorData.m_fRR);
                                }
                            }
                        }
                    }
                    //calc
                    if (fArray.GetSize() < 2)
                    {
                        break;
                    }
                    para.bStatistic = TRUE;
                    CalcStatisticMinMax(fArray, fAvg, fMax, fMin,
                        fMax_D, fTheta);
                    para.strAvg.Format("%.1f", fAvg);
                    para.strMax.Format("%.1f", fMax);
                    para.strMin.Format("%.1f", fMin);
                    para.strMax_D.Format("%.1f", fMax_D);
                    para.strTheta.Format("%.1f", fTheta);

                    CalcStatisticDistibutePara(fArray, fAvg, fTheta,
                        para);
                    para.CalcDistributionPer();
                    break;
                }
            case STATISTIC_GR:
                {
                    for (j = 0; j < data.GetSize(); j ++)
                    {
                        if (!m_bStatisticUnONArray.GetAt(j))
                        {
                            if (m_StatisticParaMode == STATISTIC_ALL)
                            {
                                fArray.Add(data.GetAt(j).m_ColorData.m_fGR);
                            }
                            else
                            {
                                if (m_bStatisticQArray.GetAt(j))
                                {
                                    fArray.Add(data.GetAt(j).m_ColorData.m_fGR);
                                }
                            }
                        }
                    }
                    //calc
                    if (fArray.GetSize() < 2)
                    {
                        break;
                    }
                    para.bStatistic = TRUE;
                    CalcStatisticMinMax(fArray, fAvg, fMax, fMin,
                        fMax_D, fTheta);
                    para.strAvg.Format("%.1f", fAvg);
                    para.strMax.Format("%.1f", fMax);
                    para.strMin.Format("%.1f", fMin);
                    para.strMax_D.Format("%.1f", fMax_D);
                    para.strTheta.Format("%.1f", fTheta);

                    CalcStatisticDistibutePara(fArray, fAvg, fTheta,
                        para);
                    para.CalcDistributionPer();
                    break;
                }
            case STATISTIC_BR:
                {
                    for (j = 0; j < data.GetSize(); j ++)
                    {
                        if (!m_bStatisticUnONArray.GetAt(j))
                        {
                            if (m_StatisticParaMode == STATISTIC_ALL)
                            {
                                fArray.Add(data.GetAt(j).m_ColorData.m_fBR);
                            }
                            else
                            {
                                if (m_bStatisticQArray.GetAt(j))
                                {
                                    fArray.Add(data.GetAt(j).m_ColorData.m_fBR);
                                }
                            }
                        }
                    }
                    //calc
                    if (fArray.GetSize() < 2)
                    {
                        break;
                    }
                    para.bStatistic = TRUE;
                    CalcStatisticMinMax(fArray, fAvg, fMax, fMin,
                        fMax_D, fTheta);
                    para.strAvg.Format("%.1f", fAvg);
                    para.strMax.Format("%.1f", fMax);
                    para.strMin.Format("%.1f", fMin);
                    para.strMax_D.Format("%.1f", fMax_D);
                    para.strTheta.Format("%.1f", fTheta);

                    CalcStatisticDistibutePara(fArray, fAvg, fTheta,
                        para);
                    para.CalcDistributionPer();
                    break;
                }
            default:
                break;
            }

            m_StatisticPara.Add(para);
        }
    }
   
}


BOOL CStatisticLedDataContainer::IsAllStatisticPara(BOOL bMgsbox)
{
    if (m_StatisticPara.GetSize() > 0)
    {
        for (int i = 0; i < m_StatisticPara.GetSize(); i ++)
        {
            if (m_StatisticPara.GetAt(i).bStatistic == FALSE)
            {
				if (bMgsbox)
				{
					AfxMessageBox("参数未能完全统计!");
				}
                return FALSE;
            }
        }
    }
    return TRUE;           
}


CString CStatisticLedDataContainer::GetStatisticItemText(int iRow, int iCol)
{
    CString strTempRow[7] = {"", "标称值(Xsta)", "平均值(Xavg)", "最大值(Xmax)", "最小值(Xmin)", "最大偏差(Xes)", "标准差(σ)"};
    if (0 == iRow && iCol < m_StatisticPara.GetSize() + 1 && iCol > 0)
    {
        return GetStatisticParaName(m_StatisticPara.GetAt(iCol - 1).iIndex, 1);
    }
    if (0 == iCol && iRow < 7)
    {
        return strTempRow[iRow];
    }
    if (m_data.GetSize() < 2 )
    {
        return "";
    }
    if (1 <= iCol)
    {
         if (m_StatisticPara.GetAt(iCol - 1).bStatistic == FALSE)
         {
             return "";
         }           
    }
    if (0 < iRow && iCol < m_StatisticPara.GetSize() + 1 && iCol > 0)
    {
        if (iRow == 1)
        {
            CString strTemp;
            switch (m_StatisticPara.GetAt(iCol - 1).iIndex)
            {                 
            case STATISTIC_VOL:
                {
                    strTemp.Format("%g", m_TestSettingsData.m_fStaVol);
                    return  strTemp;
                }
            case STATISTIC_POW:
                {
                    strTemp.Format("%g", m_TestSettingsData.m_fStaPow);
                    return  strTemp;
                }
            case STATISTIC_TC:
                {
                    strTemp.Format("%g", m_TestSettingsData.m_fStaTc);
                    return  strTemp;
                }
            case STATISTIC_FLUX:
                {
                    strTemp.Format("%g", m_TestSettingsData.m_fStaFlux);
                    return  strTemp;
                }
            default:
                {
                    return "/";
                }
            }
        }

        if (iRow == 2)
        {
            return m_StatisticPara.GetAt(iCol - 1).strAvg;
        }

        if (iRow == 3)
        {
            return m_StatisticPara.GetAt(iCol - 1).strMax;
        }

        if (iRow == 4)
        {
            return m_StatisticPara.GetAt(iCol - 1).strMin;
        }

        if (iRow == 5)
        {
            return m_StatisticPara.GetAt(iCol - 1).strMax_D;
        }

        if (iRow == 6)
        {
            return m_StatisticPara.GetAt(iCol - 1).strTheta;
        }
    }
    return "";
}


void CStatisticLedDataContainer::ListStatisticData(C_Grid & m_grid)
{
    if (!IsWindow(m_grid.GetSafeHwnd()))
    {
        return;
    }

    //m_grid.SetAutoRedraw(FALSE);

    m_grid.SetCols(m_StatisticPara.GetSize() + 1);

    m_grid.Column(0).SetWidth(100);
    m_grid.SetRows(7);

  

 //   m_grid.SetFixedCols(1);

    //m_grid.Column(1).SetWidth(150);
    //m_grid.Column(1).SetCellType(5);
    //m_grid.Column(2).SetWidth(50);
    //m_grid.Column(3).SetWidth(80);
    //m_grid.Column(3).SetAlignment(10);

    //for (int i = 4; i < 24; i++)
    //{
    //	m_grid.Column(i).SetWidth(60);
    //	m_grid.Column(i).SetAlignment(10);
    //}
    //m_grid.Column(20).SetWidth(80);

    m_grid.ShowWindow(SW_SHOW);
}


CString CStatisticLedDataContainer::GetStatisticDistributeItemText(int iRow, int iCol)
{
    CString strTempRow[7] = {"区间", "<(Xavg-2σ)", "(Xavg-2σ,Xavg-σ)",
        "(Xavg-σ,Xavg)", "(Xavg,Xavg+σ)", "(Xavg+σ,Xavg+2σ)", ">(Xavg+2σ)"};

    if (0 == iRow)
    {  
        if (0 == iCol)
        return strTempRow[iCol];
        return GetEveryDistributionName(iCol - 1);
    }
    if (0 == iCol)
    {
        if (0 == iRow)
        {
            return "区间";
        }
        else
        {
            if (iRow < m_StatisticPara.GetSize() + 1)
            {
                return GetStatisticParaName(m_StatisticPara.GetAt(iRow - 1).iIndex, 2);
            }
        }
    }
    if (m_data.GetSize() < 2)
    {
        return "";
    }
    if (1 <= iRow)
    {
        if (m_StatisticPara.GetAt(iRow - 1).bStatistic == FALSE)
        {
            return "";
        }           
    }
    if (0 < iCol)
    {
        if (iRow >= 1 && iRow < m_StatisticPara.GetSize() + 1)
        {
            CString strTemp;   
            strTemp.Format("%5d (%.2f%%)", m_StatisticPara.GetAt(iRow - 1).iEveryDistributionNum[iCol - 1],
                m_StatisticPara.GetAt(iRow - 1).fEveryDistributionPer[iCol - 1]);
            return strTemp;
        }
    }
    return "";
}


void CStatisticLedDataContainer::ListStatisticDistributeData(C_Grid & m_grid)
{
    if (!IsWindow(m_grid.GetSafeHwnd()))
    {
        return;
    }

    //m_grid.SetAutoRedraw(FALSE);
  //  m_grid.SetRowHeight(0, 31);
    m_grid.SetCols(7);
  //  m_grid.SetFixedCols(1);
    for (int i = 0; i < 7; i++)
    {
 
        m_grid.Column(i).SetWidth(150);

    }

    //m_grid.Column(2).SetWidth(50);
    //m_grid.Column(3).SetWidth(80);
    //m_grid.Column(3).SetAlignment(10);

    //for (int i = 4; i < 24; i++)
    //{
    //	m_grid.Column(i).SetWidth(60);
    //	m_grid.Column(i).SetAlignment(10);
    //}
    //m_grid.Column(20).SetWidth(80);
    m_grid.SetRows(m_StatisticPara.GetSize() + 1);

    m_grid.ShowWindow(SW_SHOW);
}


void CStatisticLedDataContainer::printHead(CDC *pDC, CRect printRect)
{

    CFont font;
    if (printRect.Height() > printRect.Width())
    {
        font.CreateFont((printRect.Height() / 64), 0, 0, 0, 400, FALSE, FALSE, 0,
            ANSI_CHARSET, OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
            DEFAULT_PITCH | FF_MODERN, _T("宋体"));
    }
    else
    {
        font.CreateFont((printRect.Width() / 64), 0, 0, 0, 400, FALSE, FALSE, 0,
            ANSI_CHARSET, OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
            DEFAULT_PITCH | FF_MODERN, _T("宋体"));
    }

    CFont* pOldFont = (CFont*)(pDC->SelectObject(&font));

    TEXTMETRIC  tm;
    pDC->GetTextMetrics(&tm);
    int nfontHeight = tm.tmHeight + tm.tmExternalLeading;
    nfontHeight = (int)(nfontHeight * 1.2f); 
    int nfontWidth = tm.tmAveCharWidth;


    pDC->SetTextAlign(TA_LEFT);  
    pDC->TextOut(printRect.left + 2 * nfontWidth, printRect.top - nfontHeight, 
        m_TestInfoData.m_strPageHeadCap);
    {
        //GetFileVersionInfo
        pDC->SetTextAlign(TA_RIGHT);
        pDC->TextOut(printRect.right  - 2 * nfontWidth, printRect.top - nfontHeight, 
            m_TestInfoData.m_strPageHeadCapInfo);
    }		
    CPen Pen;
    CPen *PtrOldPen;
    Pen.CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
    PtrOldPen = pDC->SelectObject(&Pen);
    pDC->MoveTo(printRect.left, printRect.top);
    pDC->LineTo(printRect.right, printRect.top);

    pDC->SelectObject(pOldFont);
    pDC->SelectObject(PtrOldPen);
    if(!m_TestInfoData.m_bPrintPageHeadLogo)
        return;
    //打印图片标志

    CBitmap	m_ImagePrint;
    HBITMAP hBitMap = (HBITMAP)LoadImage(NULL, g_strCurrentPath + _T("logo.bmp"), 
        IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
    m_ImagePrint.Attach(hBitMap);

    BITMAP bm;
    m_ImagePrint.GetBitmap(&bm);

    CRect compRect;
    CBrush BrushBack;
    BrushBack.CreateSolidBrush(RGB(255, 255, 255));
    CRect Rect;

    compRect.left = printRect.left;
    compRect.right = printRect.left + printRect.Width() / 4;
    compRect.bottom = printRect.top - nfontHeight ;
    compRect.top = compRect.bottom - bm.bmHeight * compRect.Width() / bm.bmWidth;


    CDC dcImange;
    dcImange.CreateCompatibleDC(pDC);
    dcImange.SelectObject(m_ImagePrint);
    if(m_TestInfoData.m_iPageHeadLogoPos == 0)
    {
        // 自己画图  
        pDC->StretchBlt(compRect.left, compRect.top, compRect.Width(), compRect.Height(), 
            &dcImange, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);

        pDC->SetBkMode(OPAQUE);
        Rect.left = compRect.left;
        Rect.right = compRect.right;
        Rect.top = compRect.top;
        Rect.bottom = compRect.top + nfontHeight / 2;
        pDC->FillRect(&Rect, &BrushBack);
    }


    compRect.left = printRect.right - printRect.Width() / 4;
    compRect.right = printRect.right;

    if(m_TestInfoData.m_iPageHeadLogoPos == 1)
    {
        pDC->StretchBlt(compRect.left, compRect.top, compRect.Width(), compRect.Height(), 
            &dcImange, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
        pDC->SetBkMode(OPAQUE);
        Rect.left = compRect.left;
        Rect.right = compRect.right;
        Rect.top = compRect.top;
        Rect.bottom = compRect.top + nfontHeight / 2;
        pDC->FillRect(&Rect,&BrushBack);
    }
    pDC->SelectObject(PtrOldPen);
    pDC->SelectObject(pOldFont);
}


void CStatisticLedDataContainer::printReport(CDC *pDC,CRect printRect, int iCur)
{
    CFont *pOldFont;
    CFont Font1;
    CFont Font2;
    CFont Font3;
    CFont Font4;
    CString strTemp;
    int i;       
    if (printRect.Height() > printRect.Width())
    {
        Font1.CreateFont(printRect.Height() / 30, 0, 0, 0, 600, FALSE, FALSE, 0,
            ANSI_CHARSET, OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
            DEFAULT_PITCH | FF_MODERN, _T("宋体"));

        Font2.CreateFont(printRect.Height() / 42, 0, 0, 0, 600, FALSE, FALSE, 0,
            ANSI_CHARSET, OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
            DEFAULT_PITCH | FF_MODERN, _T("宋体"));
        Font3.CreateFont(printRect.Height() / 54, 0, 0, 0, 400, FALSE, FALSE, 0,
            ANSI_CHARSET, OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
            DEFAULT_PITCH | FF_MODERN, _T("宋体"));
        Font4.CreateFont(printRect.Height() / 64, 0, 0, 0, 400, FALSE, FALSE, 0,
            ANSI_CHARSET, OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
            DEFAULT_PITCH | FF_MODERN, _T("宋体"));
    }
    else
    {
        Font1.CreateFont(printRect.Width() / 30, 0, 0, 0, 600, FALSE, FALSE, 0,
            ANSI_CHARSET, OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
            DEFAULT_PITCH | FF_MODERN, _T("宋体"));

        Font2.CreateFont(printRect.Width() / 42, 0, 0, 0, 600, FALSE, FALSE, 0,
            ANSI_CHARSET, OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
            DEFAULT_PITCH | FF_MODERN, _T("宋体"));
        Font3.CreateFont(printRect.Width() / 54, 0, 0, 0, 400, FALSE, FALSE, 0,
            ANSI_CHARSET, OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
            DEFAULT_PITCH | FF_MODERN, _T("宋体"));
        Font4.CreateFont(printRect.Width() / 64, 0, 0, 0, 400, FALSE, FALSE, 0,
            ANSI_CHARSET, OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
            DEFAULT_PITCH | FF_MODERN, _T("宋体"));
    }


    CPen  Pen1, *pOldPen;
    Pen1.CreatePen(PS_SOLID,1,RGB(0,0,0));
    pOldPen = pDC->SelectObject(&Pen1);
    int iFontH1, iFontW1, iFontH2, iFontW2, iFontH3, iFontW3, iFontH4, iFontW4;;
    TEXTMETRIC  tm;
    pOldFont = pDC->SelectObject(&Font1);
    pDC->SetTextAlign(TA_CENTER);
    pDC->GetTextMetrics(&tm);
    iFontH1 = tm.tmHeight + tm.tmExternalLeading;
    iFontW1 = tm.tmAveCharWidth;
    iFontH1 = (int)(iFontH1 * 1.1f);

    pOldFont = pDC->SelectObject(&Font2);
    pDC->SetTextAlign(TA_CENTER);
    pDC->GetTextMetrics(&tm);
    iFontH2 = tm.tmHeight + tm.tmExternalLeading;
    iFontW2 = tm.tmAveCharWidth;
    iFontH2 = (int)(iFontH2 * 1.1f);

    pOldFont = pDC->SelectObject(&Font3);
    pDC->SetTextAlign(TA_CENTER);
    pDC->GetTextMetrics(&tm);
    iFontH3 = tm.tmHeight + tm.tmExternalLeading;
    iFontW3 = tm.tmAveCharWidth;
    iFontH3 = (int)(iFontH3 * 1.1f);

    pOldFont = pDC->SelectObject(&Font4);
    pDC->SetTextAlign(TA_CENTER);
    pDC->GetTextMetrics(&tm);
    iFontH4 = tm.tmHeight + tm.tmExternalLeading;
    iFontW4 = tm.tmAveCharWidth;
    iFontH4 = (int)(iFontH4 * 1.1f);

    int iTextPosX, iTextPosY;

    if (iCur == 1)
    {
        pDC->SelectObject(&Font1);   
        pDC->SetTextAlign(TA_CENTER);
        iTextPosX = (printRect.left + printRect.right) / 2;
        iTextPosY = printRect.top + iFontH1 / 2;
        pDC->TextOut(iTextPosX, iTextPosY, m_TestInfoData.m_strPrintCap); 
        iTextPosY += iFontH1;   

        if (m_TestInfoData.m_bPrintSubCap)
        {
            iTextPosY += iFontH4 / 2;
            pDC->SelectObject(&Font4); 
            pDC->TextOut(iTextPosX, iTextPosY, 
                m_TestInfoData.m_strPrintSubCap);
            iTextPosY += iFontH4;
        }      

        iTextPosY += iFontH3 / 2;
        pDC->SelectObject(&Font2); 
        iTextPosX = printRect.left;
        pDC->SetTextAlign(TA_LEFT);
        pDC->TextOut(iTextPosX, iTextPosY, _T("1.被测") + 
            m_TestInfoData.m_strLampName +
            _T("说明"));
        iTextPosY += iFontH3;


        iTextPosY += iFontH3 / 2;
        pDC->SelectObject(&Font3); 
        pDC->TextOut(iTextPosX, iTextPosY, _T("1.1 提供厂商: ") +
            m_TestInfoData.m_strFactory); 
        iTextPosY += iFontH3;

        iTextPosY += iFontH3 / 2;
        pDC->TextOut(iTextPosX, iTextPosY, _T("1.2 型号: ") +
            m_TestSettingsData.m_strLedModel); 

        pDC->TextOut(iTextPosX + printRect.Width() / 2, iTextPosY, _T("编号: ") +
            m_TestInfoData.m_strLampNum); 
        iTextPosY += iFontH3;



        iTextPosY += iFontH3 / 2;
        pDC->TextOut(iTextPosX, iTextPosY, _T("1.3 规格: ") +
            m_TestInfoData.m_strLampRule); 
        iTextPosY += iFontH3;

        iTextPosY += iFontH3 / 2;
        pDC->TextOut(iTextPosX, iTextPosY, _T("1.4 标称参数"));
        iTextPosY += iFontH3;

        iTextPosY += iFontH3 / 2;
        iTextPosX = printRect.left + 6 * iFontW3;
        strTemp.Format(_T("额定电压: %g V"), 
            m_TestSettingsData.m_fStaVol);
        pDC->TextOut(iTextPosX, iTextPosY, strTemp);

        strTemp.Format(_T("额定功率: %g W"), 
            m_TestSettingsData.m_fStaPow);
        pDC->TextOut(printRect.left + printRect.Width() / 2, iTextPosY, strTemp);

        iTextPosY += iFontH3;

        iTextPosY += iFontH3 / 2;
        strTemp.Format(_T("标称光通量 %g lm"), 
            m_TestSettingsData.m_fStaFlux);
        pDC->TextOut(iTextPosX, iTextPosY, strTemp);

        strTemp.Format(_T("标称色温: %g K"), 
            m_TestSettingsData.m_fStaTc);
        pDC->TextOut(printRect.left + printRect.Width() / 2, iTextPosY, strTemp);

        iTextPosY += iFontH3;

        iTextPosY += iFontH3 / 2;
        iTextPosX = printRect.left;
        pDC->TextOut(iTextPosX, iTextPosY, _T("1.5 接口方式: ") + 
            m_TestInfoData.m_strComboInerface);
        iTextPosY += iFontH3;


        iTextPosY += iFontH3 / 2;
        iTextPosX = printRect.left;
        pDC->TextOut(iTextPosX, iTextPosY, _T("1.6 其他说明"));
        iTextPosY += iFontH3;
        CArray<CString, CString>strArray;
        strArray.RemoveAll();
        strTemp = m_TestInfoData.m_strLampNote;
        int istrNum = 0;
        for (i = 0; i < strTemp.GetLength(); i ++)
        {
            if (strTemp.GetAt(i) == 13)
            {
                istrNum ++;
            }
        }
        for (i = 0; i < strTemp.GetLength(); i ++)
        {
            CString strOne;
            //13为换行符
            if (strTemp.GetAt(i) == 13)
            {
                strOne = strTemp.Left(i);
                strArray.Add(strOne);
                strTemp = strTemp.Right(strTemp.GetLength() - i - 2);
                i = 0;
                istrNum --;
                if (istrNum == 0)
                {
                    break;
                }
            }
        }
        strArray.Add(strTemp);
        for (i = 0; i < strArray.GetSize(); i ++)
        {
            iTextPosY += iFontH3 / 2;
            iTextPosX = printRect.left + 6 * iFontW3;
            pDC->TextOut(iTextPosX, iTextPosY,strArray.GetAt(i));
            iTextPosY += iFontH3;
        }

        pDC->SelectObject(&Font2);
        iTextPosY += iFontH2 / 2;
        iTextPosX = printRect.left;
        pDC->TextOut(iTextPosX, iTextPosY, _T("2.测试条件"));
        iTextPosY += iFontH2;

        pDC->SelectObject(&Font3);
        iTextPosY += iFontH3 / 2;
        strTemp.Format("2.1 环境条件: 温度: %s ℃; 湿度: %s %%",
            m_TestInfoData.m_strTMP, m_TestInfoData.m_strWet);
        pDC->TextOut(iTextPosX, iTextPosY, strTemp);
        iTextPosY += iFontH3;

        iTextPosY += iFontH3 / 2;
        strTemp.Format("2.2 测试设备: %s",
            m_TestInfoData.m_strTestMachine);
        pDC->TextOut(iTextPosX, iTextPosY, strTemp);
        iTextPosY += iFontH3;


        iTextPosY += iFontH3 / 2;
        strTemp.Format("2.3 老化试验项目");
        pDC->TextOut(iTextPosX, iTextPosY, strTemp);
        iTextPosY += iFontH3;

        strArray.RemoveAll();
        if (m_TestInfoData.m_bNormalTMP_Aging)
        {
            strTemp = "常温老化";
            strArray.Add(strTemp);
        }
        if (m_TestInfoData.m_bHighTMP_Aging)
        {
            strTemp = "高温老化";
            strArray.Add(strTemp);
        }
        if (m_TestInfoData.m_bStaVol_Aging)
        {
            strTemp = "额定电压老化";
            strArray.Add(strTemp);
        }
        if (m_TestInfoData.m_bHighLowVol_Aging)
        {
            strTemp = "高低压老化";
            strArray.Add(strTemp);
        }
        if (m_TestInfoData.m_bSwitch_Aging)
        {
            strTemp = "开关老化";
            strArray.Add(strTemp);
        }
        if (m_TestInfoData.m_bCustomVol_Aging)
        {
            strTemp = "市电漫游老化";
            strArray.Add(strTemp);
        }
        if (m_TestInfoData.m_bEMC_Test)
        {
            strTemp = "EMC试验";
            strArray.Add(strTemp);
        }

        for (i = 0; i < strArray.GetSize(); i ++)
        {
            if (i % 4 == 0)
            {
                iTextPosY += iFontH3 / 2;
            }
            iTextPosX = printRect.left + 6 * iFontW3
                + (i % 4) * (printRect.right - printRect.left - 6 * iFontW3) / 4;
            pDC->TextOut(iTextPosX, iTextPosY, strArray.GetAt(i));
            if (i % 4 == 3)
            {
                iTextPosY += iFontH3;
            }
        }
        if (i % 4 != 0)
        {
            iTextPosY += iFontH3;   
        }

        iTextPosX = printRect.left;
        iTextPosY += iFontH3 / 2;
        strTemp.Format("2.4 老化测试速度: %.1f 只/小时", 
            m_TestInfoData.m_fTestRate);
        pDC->TextOut(iTextPosX, iTextPosY, strTemp);
        iTextPosY += iFontH3;

        iTextPosY += iFontH3 / 2;
        strTemp.Format("2.5 测试人员: %s", 
            m_TestInfoData.m_strTester);
        pDC->TextOut(iTextPosX, iTextPosY, strTemp);
        strTemp.Format("测试日期: %s", 
            m_TestInfoData.m_strTestDate);
        pDC->TextOut(iTextPosX + printRect.Width() / 2, iTextPosY, strTemp);

        iTextPosY += iFontH3;



        iTextPosY += iFontH3 / 2;
        iTextPosX = printRect.left;
        pDC->TextOut(iTextPosX, iTextPosY, _T("2.6 其他条件"));
        iTextPosY += iFontH3;

        strArray.RemoveAll();
        strTemp = m_TestInfoData.m_strRemark;
        istrNum = 0;
        for (i = 0; i < strTemp.GetLength(); i ++)
        {
            if (strTemp.GetAt(i) == 13)
            {
                istrNum ++;
            }
        }
        for (i = 0; i < strTemp.GetLength(); i ++)
        {
            CString strOne;
            //13为换行符
            if (strTemp.GetAt(i) == 13)
            {
                strOne = strTemp.Left(i);
                strArray.Add(strOne);
                strTemp = strTemp.Right(strTemp.GetLength() - i - 2);
                i = 0;
                istrNum --;
                if (istrNum == 0)
                {
                    break;
                }
            }
        }
        strArray.Add(strTemp);
        for (i = 0; i < strArray.GetSize(); i ++)
        {
            iTextPosY += iFontH3 / 2;
            iTextPosX = printRect.left + 6 * iFontW3;
            pDC->TextOut(iTextPosX, iTextPosY, strArray.GetAt(i));
            iTextPosY += iFontH3;
        }
    }
    else 
    {
        if (iCur == 2)
        {    
            iTextPosX = printRect.left;
            iTextPosY = printRect.top;
            pDC->SetTextAlign(TA_LEFT);
            pDC->SelectObject(&Font2);
            iTextPosY += iFontH2 / 2;   
            pDC->TextOut(iTextPosX, iTextPosY, "3.测试结果数据分析");
            iTextPosY += iFontH2;

            pDC->SelectObject(&Font3);
            iTextPosX = printRect.left;
            iTextPosY += iFontH3 / 2;
            strTemp.Format("3.1 总测试数: %d 只", 
                m_data.GetSize());
            pDC->TextOut(iTextPosX, iTextPosY, strTemp); 
            iTextPosY += iFontH3; 

            iTextPosX = printRect.left;
            iTextPosY += iFontH3 / 2;
            strTemp.Format("3.2 状态数据分析:合格数 %d 只(%.1f%%); 不合格(超限值)数 %d 只(%.1f%%); 不合格(无灯或未亮)数 %d 只(%.1f%%)",
                m_iQLEDNum, GetQLEDNumPer(), m_iUnOnLEDNum, GetUnQLEDNumPer(), m_iUnOnLEDNum, GetUnONLEDNumPer());
            pDC->TextOut(iTextPosX, iTextPosY, strTemp); 
            iTextPosY += iFontH3;   

            pDC->SelectObject(&Font3);
            iTextPosX = printRect.left;
            iTextPosY += iFontH3 / 2;
            strTemp.Format("3.3 统计参数数据分析列表如下:", 
                m_data.GetSize());
            pDC->TextOut(iTextPosX, iTextPosY, strTemp); 
            pDC->SetTextAlign(TA_RIGHT);
            pDC->SelectObject(&Font4);
            m_StatisticParaMode == 0 ? strTemp.Format("统计方式:统计全部(灯亮)"): 
                strTemp.Format("统计方式:统计合格(灯亮)");
            pDC->TextOut(printRect.right, iTextPosY + iFontH3 * 3 / 4, strTemp); 
            iTextPosY += iFontH3; 
            pDC->SetTextAlign(TA_LEFT);


            iTextPosY += iFontH3 / 2; 

            CRect listRect;
            listRect.top = iTextPosY;
            listRect.left = printRect.left;
            listRect.right = printRect.right;
            pDC->SelectObject(&Font4);
            iFontH4 = int(iFontH4 * 1.4);
            for (i = 0; i < 7; i ++)
            {
                pDC->MoveTo(printRect.left, iTextPosY);
                pDC->LineTo(printRect.right, iTextPosY);
                iTextPosY += iFontH4;
            }
            pDC->MoveTo(printRect.left, iTextPosY);
            pDC->LineTo(printRect.right, iTextPosY);
            listRect.bottom = iTextPosY;
            pDC->MoveTo(listRect.left, listRect.top);
            pDC->LineTo(listRect.left, listRect.bottom);
            pDC->MoveTo(listRect.right, listRect.top);
            pDC->LineTo(listRect.right, listRect.bottom);

            int W;
            float fAddH = 0.2f;
            int iCurWPos;
            CArray<int,int> saveW; 
            iCurWPos = printRect.left;
            iTextPosY = listRect.top;
            pDC->SetTextAlign(TA_CENTER);
            int iStatisticParaNum = 0;
            iTextPosY += int(iFontH4 * 0.2);
            BOOL bOvre10StatisticPara = FALSE;
            for (i = 0; i < m_StatisticPara.GetSize() + 1; i ++)
            {
                if (i > 10)
                {
                    bOvre10StatisticPara = TRUE;
                    continue;
                }
                if (i == 0)
                {
                    W = 16 * iFontW4;
                    saveW.Add(W);
                    iCurWPos = iCurWPos + W;
                    pDC->MoveTo(iCurWPos,listRect.top);
                    pDC->LineTo(iCurWPos,listRect.bottom);
                    pDC->TextOut(iCurWPos - W / 2, iTextPosY,
                        "");
                }
                else
                {
                    W = 10 * iFontW4;
                    saveW.Add(W);
                    iCurWPos = iCurWPos + W;
                    pDC->MoveTo(iCurWPos,listRect.top);
                    pDC->LineTo(iCurWPos,listRect.bottom);
                    pDC->TextOut(iCurWPos - W / 2, iTextPosY,
                        GetStatisticParaName(m_StatisticPara.GetAt(i - 1).iIndex, 1));	
                    iStatisticParaNum ++;
                } 
            }
            iTextPosY += iFontH4;
            iCurWPos = printRect.left;
            if (1)
            {
                for (i = 0; i < iStatisticParaNum + 1; i ++)
                {
                    if (i == 0)
                    {
                        iCurWPos = iCurWPos + saveW.GetAt(i);
                        pDC->TextOut(iCurWPos - saveW.GetAt(i) / 2, iTextPosY, "标称值Xsta");
                    }
                    else
                    {
                        iCurWPos = iCurWPos + saveW.GetAt(i);
                        switch (m_StatisticPara.GetAt(i - 1).iIndex)
                        {
                        case STATISTIC_VOL:
                            {
                                strTemp.Format("%g", m_TestInfoData.m_fStaVol);
                                break;
                            }

                        case STATISTIC_POW:
                            {
                                strTemp.Format("%g", m_TestInfoData.m_fStaPow);
                                break;
                            }
                        case STATISTIC_FLUX:
                            {
                                strTemp.Format("%g", m_TestInfoData.m_fStaFlux);
                                break;
                            }
                        case STATISTIC_TC:
                            {
                                strTemp.Format("%g", m_TestInfoData.m_fStaTc);
                                break;
                            }
                        default:
                            {
                                strTemp.Format("/");
                                break;
                            }   
                        }                 
                        pDC->TextOut(iCurWPos - saveW.GetAt(i) / 2, iTextPosY, strTemp);
                    }
                }
            }
            iTextPosY += iFontH4;
            iCurWPos = printRect.left;
            if (1)
            {
                for (i = 0; i < iStatisticParaNum + 1; i ++)
                {
                    if (i == 0)
                    {
                        iCurWPos = iCurWPos + saveW.GetAt(i);
                        pDC->TextOut(iCurWPos - saveW.GetAt(i) / 2, iTextPosY, "平均值Xavg");
                    }
                    else
                    {
                        iCurWPos = iCurWPos + saveW.GetAt(i);
                        pDC->TextOut(iCurWPos - saveW.GetAt(i) / 2, iTextPosY,
                            m_StatisticPara.GetAt(i - 1).strAvg);
                    }
                }
            }
            iTextPosY += iFontH4;
            iCurWPos = printRect.left;
            if (1)
            {
                for (i = 0; i < iStatisticParaNum + 1; i ++)
                {
                    if (i == 0)
                    {
                        iCurWPos = iCurWPos + saveW.GetAt(i);
                        pDC->TextOut(iCurWPos - saveW.GetAt(i) / 2, iTextPosY, "最大值Xmax");
                    }
                    else
                    {
                        iCurWPos = iCurWPos + saveW.GetAt(i);
                        pDC->TextOut(iCurWPos - saveW.GetAt(i) / 2, iTextPosY,
                            m_StatisticPara.GetAt(i - 1).strMax);
                    }
                }
            }

            iTextPosY += iFontH4;
            iCurWPos = printRect.left;
            if (1)
            {
                for (i = 0; i < iStatisticParaNum + 1; i ++)
                {
                    if (i == 0)
                    {
                        iCurWPos = iCurWPos + saveW.GetAt(i);
                        pDC->TextOut(iCurWPos - saveW.GetAt(i) / 2, iTextPosY, "最小值Xmin");
                    }
                    else
                    {
                        iCurWPos = iCurWPos + saveW.GetAt(i);
                        pDC->TextOut(iCurWPos - saveW.GetAt(i) / 2, iTextPosY,
                            m_StatisticPara.GetAt(i - 1).strMin);
                    }
                }
            }

            iTextPosY += iFontH4;
            iCurWPos = printRect.left;
            if (1)
            {
                for (i = 0; i < iStatisticParaNum + 1; i ++)
                {
                    if (i == 0)
                    {
                        iCurWPos = iCurWPos + saveW.GetAt(i);
                        pDC->TextOut(iCurWPos - saveW.GetAt(i) / 2, iTextPosY, "最大偏差Xes");
                    }
                    else
                    {
                        iCurWPos = iCurWPos + saveW.GetAt(i);
                        pDC->TextOut(iCurWPos - saveW.GetAt(i) / 2, iTextPosY,
                            m_StatisticPara.GetAt(i - 1).strMax_D);
                    }
                }
            }

            iTextPosY += iFontH4;
            iCurWPos = printRect.left;
            if (1)
            {
                for (i = 0; i < iStatisticParaNum + 1; i ++)
                {
                    if (i == 0)
                    {
                        iCurWPos = iCurWPos + saveW.GetAt(i);
                        pDC->TextOut(iCurWPos - saveW.GetAt(i) / 2, iTextPosY, "标准差σ");
                    }
                    else
                    {
                        iCurWPos = iCurWPos + saveW.GetAt(i);
                        pDC->TextOut(iCurWPos - saveW.GetAt(i) / 2, iTextPosY,
                            m_StatisticPara.GetAt(i - 1).strTheta);
                    }
                }
            }
            if (bOvre10StatisticPara)
            {
                iTextPosY += iFontH4 * 2;
                listRect.top = iTextPosY;
                listRect.left = printRect.left;
                listRect.right = printRect.right;
                for (i = 0; i < 7; i ++)
                {
                    pDC->MoveTo(printRect.left, iTextPosY);
                    pDC->LineTo(printRect.right, iTextPosY);
                    iTextPosY += iFontH4;
                }
                pDC->MoveTo(printRect.left, iTextPosY);
                pDC->LineTo(printRect.right, iTextPosY);
                listRect.bottom = iTextPosY;
                pDC->MoveTo(listRect.left, listRect.top);
                pDC->LineTo(listRect.left, listRect.bottom);
                pDC->MoveTo(listRect.right, listRect.top);
                pDC->LineTo(listRect.right, listRect.bottom);

                saveW.RemoveAll();
                iCurWPos = printRect.left;
                iTextPosY = listRect.top;
                pDC->SetTextAlign(TA_CENTER);
                iStatisticParaNum = 0;
                iTextPosY += int(iFontH4 * 0.2);
                for (i = 10; i < m_StatisticPara.GetSize() + 1; i ++)
                {
                    if (i == 10)
                    {
                        W = 16 * iFontW4;
                        saveW.Add(W);
                        iCurWPos = iCurWPos + W;
                        pDC->MoveTo(iCurWPos,listRect.top);
                        pDC->LineTo(iCurWPos,listRect.bottom);
                        pDC->TextOut(iCurWPos - W / 2, iTextPosY,
                            "");
                    }
                    else
                    {
                        W = 10 * iFontW4;
                        saveW.Add(W);
                        iCurWPos = iCurWPos + W;
                        pDC->MoveTo(iCurWPos,listRect.top);
                        pDC->LineTo(iCurWPos,listRect.bottom);
                        pDC->TextOut(iCurWPos - W / 2, iTextPosY,
                            GetStatisticParaName(m_StatisticPara.GetAt(i - 1).iIndex, 1));	
                        iStatisticParaNum ++;
                        if (iStatisticParaNum == 10)
                        {
                            break;
                        }
                    } 
                }
                iTextPosY += iFontH4;
                iCurWPos = printRect.left;
                if (1)
                {
                    for (i = 0; i < iStatisticParaNum + 1; i ++)
                    {
                        if (i == 0)
                        {
                            iCurWPos = iCurWPos + saveW.GetAt(i);
                            pDC->TextOut(iCurWPos - saveW.GetAt(i) / 2, iTextPosY, "标称值Xsta");
                        }
                        else
                        {
                            iCurWPos = iCurWPos + saveW.GetAt(i);
                            switch (m_StatisticPara.GetAt(10 + i - 1).iIndex)
                            {
                            case STATISTIC_VOL:
                                {
                                    strTemp.Format("%g", m_TestInfoData.m_fStaVol);
                                    break;
                                }

                            case STATISTIC_POW:
                                {
                                    strTemp.Format("%g", m_TestInfoData.m_fStaPow);
                                    break;
                                }
                            case STATISTIC_FLUX:
                                {
                                    strTemp.Format("%g", m_TestInfoData.m_fStaFlux);
                                    break;
                                }
                            case STATISTIC_TC:
                                {
                                    strTemp.Format("%g", m_TestInfoData.m_fStaTc);
                                    break;
                                }
                            default:
                                {
                                    strTemp.Format("/");
                                    break;
                                }   
                            }                 
                            pDC->TextOut(iCurWPos - saveW.GetAt(i) / 2, iTextPosY, strTemp);
                        }
                    }
                }
                iTextPosY += iFontH4;
                iCurWPos = printRect.left;
                if (1)
                {
                    for (i = 0; i < iStatisticParaNum + 1; i ++)
                    {
                        if (i == 0)
                        {
                            iCurWPos = iCurWPos + saveW.GetAt(i);
                            pDC->TextOut(iCurWPos - saveW.GetAt(i) / 2, iTextPosY, "平均值Xavg");
                        }
                        else
                        {
                            iCurWPos = iCurWPos + saveW.GetAt(i);
                            pDC->TextOut(iCurWPos - saveW.GetAt(i) / 2, iTextPosY,
                                m_StatisticPara.GetAt(10 + i - 1).strAvg);
                        }
                    }
                }
                iTextPosY += iFontH4;
                iCurWPos = printRect.left;
                if (1)
                {
                    for (i = 0; i < iStatisticParaNum + 1; i ++)
                    {
                        if (i == 0)
                        {
                            iCurWPos = iCurWPos + saveW.GetAt(i);
                            pDC->TextOut(iCurWPos - saveW.GetAt(i) / 2, iTextPosY, "最大值Xmax");
                        }
                        else
                        {
                            iCurWPos = iCurWPos + saveW.GetAt(i);
                            pDC->TextOut(iCurWPos - saveW.GetAt(i) / 2, iTextPosY,
                                m_StatisticPara.GetAt(10 + i - 1).strMax);
                        }
                    }
                }

                iTextPosY += iFontH4;
                iCurWPos = printRect.left;
                if (1)
                {
                    for (i = 0; i < iStatisticParaNum + 1; i ++)
                    {
                        if (i == 0)
                        {
                            iCurWPos = iCurWPos + saveW.GetAt(i);
                            pDC->TextOut(iCurWPos - saveW.GetAt(i) / 2, iTextPosY, "最小值Xmin");
                        }
                        else
                        {
                            iCurWPos = iCurWPos + saveW.GetAt(i);
                            pDC->TextOut(iCurWPos - saveW.GetAt(i) / 2, iTextPosY,
                                m_StatisticPara.GetAt(10 + i - 1).strMin);
                        }
                    }
                }

                iTextPosY += iFontH4;
                iCurWPos = printRect.left;
                if (1)
                {
                    for (i = 0; i < iStatisticParaNum + 1; i ++)
                    {
                        if (i == 0)
                        {
                            iCurWPos = iCurWPos + saveW.GetAt(i);
                            pDC->TextOut(iCurWPos - saveW.GetAt(i) / 2, iTextPosY, "最大偏差Xes");
                        }
                        else
                        {
                            iCurWPos = iCurWPos + saveW.GetAt(i);
                            pDC->TextOut(iCurWPos - saveW.GetAt(i) / 2, iTextPosY,
                                m_StatisticPara.GetAt(10 + i - 1).strMax_D);
                        }
                    }
                }

                iTextPosY += iFontH4;
                iCurWPos = printRect.left;
                if (1)
                {
                    for (i = 0; i < iStatisticParaNum + 1; i ++)
                    {
                        if (i == 0)
                        {
                            iCurWPos = iCurWPos + saveW.GetAt(i);
                            pDC->TextOut(iCurWPos - saveW.GetAt(i) / 2, iTextPosY, "标准差σ");
                        }
                        else
                        {
                            iCurWPos = iCurWPos + saveW.GetAt(i);
                            pDC->TextOut(iCurWPos - saveW.GetAt(i) / 2, iTextPosY,
                                m_StatisticPara.GetAt(10 + i - 1).strTheta);
                        }
                    }
                }
            }
        }
        if (iCur == 3 && m_StatisticPara.GetSize() >= 20)
        {
            iTextPosY = printRect.top;
            iTextPosY += iFontH3 / 2; 

            CRect listRect;
            listRect.top = iTextPosY;
            listRect.left = printRect.left;
            listRect.right = printRect.right;
            pDC->SelectObject(&Font4);
            iFontH4 = int(iFontH4 * 1.4);
            for (i = 0; i < 7; i ++)
            {
                pDC->MoveTo(printRect.left, iTextPosY);
                pDC->LineTo(printRect.right, iTextPosY);
                iTextPosY += iFontH4;
            }
            pDC->MoveTo(printRect.left, iTextPosY);
            pDC->LineTo(printRect.right, iTextPosY);
            listRect.bottom = iTextPosY;
            pDC->MoveTo(listRect.left, listRect.top);
            pDC->LineTo(listRect.left, listRect.bottom);
            pDC->MoveTo(listRect.right, listRect.top);
            pDC->LineTo(listRect.right, listRect.bottom);

            int W;
            float fAddH = 0.2f;
            int iCurWPos;
            CArray<int,int> saveW; 
            iCurWPos = printRect.left;
            iTextPosY = listRect.top;
            pDC->SetTextAlign(TA_CENTER);
            int iStatisticParaNum = 0;
            iTextPosY += int(iFontH4 * 0.2);
            for (i = 20; i < m_StatisticPara.GetSize() + 1; i ++)
            {
                if (i == 20)
                {
                    W = 16 * iFontW4;
                    saveW.Add(W);
                    iCurWPos = iCurWPos + W;
                    pDC->MoveTo(iCurWPos,listRect.top);
                    pDC->LineTo(iCurWPos,listRect.bottom);
                    pDC->TextOut(iCurWPos - W / 2, iTextPosY,
                        "");
                }
                else
                {
                    W = 10 * iFontW4;
                    saveW.Add(W);
                    iCurWPos = iCurWPos + W;
                    pDC->MoveTo(iCurWPos,listRect.top);
                    pDC->LineTo(iCurWPos,listRect.bottom);
                    pDC->TextOut(iCurWPos - W / 2, iTextPosY,
                        GetStatisticParaName(m_StatisticPara.GetAt(i - 1).iIndex, 1));	
                    iStatisticParaNum ++;
                } 
  
            }
            iTextPosY += iFontH4;
            iCurWPos = printRect.left;
            if (1)
            {
                for (i = 0; i < iStatisticParaNum + 1; i ++)
                {
                    if (i == 0)
                    {
                        iCurWPos = iCurWPos + saveW.GetAt(i);
                        pDC->TextOut(iCurWPos - saveW.GetAt(i) / 2, iTextPosY, "标称值Xsta");
                    }
                    else
                    {
                        iCurWPos = iCurWPos + saveW.GetAt(i);
                        switch (m_StatisticPara.GetAt(20 + i - 1).iIndex)
                        {
                        case STATISTIC_VOL:
                            {
                                strTemp.Format("%g", m_TestInfoData.m_fStaVol);
                                break;
                            }

                        case STATISTIC_POW:
                            {
                                strTemp.Format("%g", m_TestInfoData.m_fStaPow);
                                break;
                            }
                        case STATISTIC_FLUX:
                            {
                                strTemp.Format("%g", m_TestInfoData.m_fStaFlux);
                                break;
                            }
                        case STATISTIC_TC:
                            {
                                strTemp.Format("%g", m_TestInfoData.m_fStaTc);
                                break;
                            }
                        default:
                            {
                                strTemp.Format("/");
                                break;
                            }   
                        }                 
                        pDC->TextOut(iCurWPos - saveW.GetAt(i) / 2, iTextPosY, strTemp);
                    }
                }
            }
            iTextPosY += iFontH4;
            iCurWPos = printRect.left;
            if (1)
            {
                for (i = 0; i < iStatisticParaNum + 1; i ++)
                {
                    if (i == 0)
                    {
                        iCurWPos = iCurWPos + saveW.GetAt(i);
                        pDC->TextOut(iCurWPos - saveW.GetAt(i) / 2, iTextPosY, "平均值Xavg");
                    }
                    else
                    {
                        iCurWPos = iCurWPos + saveW.GetAt(i);
                        pDC->TextOut(iCurWPos - saveW.GetAt(i) / 2, iTextPosY,
                            m_StatisticPara.GetAt(20 + i - 1).strAvg);
                    }
                }
            }
            iTextPosY += iFontH4;
            iCurWPos = printRect.left;
            if (1)
            {
                for (i = 0; i < iStatisticParaNum + 1; i ++)
                {
                    if (i == 0)
                    {
                        iCurWPos = iCurWPos + saveW.GetAt(i);
                        pDC->TextOut(iCurWPos - saveW.GetAt(i) / 2, iTextPosY, "最大值Xmax");
                    }
                    else
                    {
                        iCurWPos = iCurWPos + saveW.GetAt(i);
                        pDC->TextOut(iCurWPos - saveW.GetAt(i) / 2, iTextPosY,
                            m_StatisticPara.GetAt(20 + i - 1).strMax);
                    }
                }
            }

            iTextPosY += iFontH4;
            iCurWPos = printRect.left;
            if (1)
            {
                for (i = 0; i < iStatisticParaNum + 1; i ++)
                {
                    if (i == 0)
                    {
                        iCurWPos = iCurWPos + saveW.GetAt(i);
                        pDC->TextOut(iCurWPos - saveW.GetAt(i) / 2, iTextPosY, "最小值Xmin");
                    }
                    else
                    {
                        iCurWPos = iCurWPos + saveW.GetAt(i);
                        pDC->TextOut(iCurWPos - saveW.GetAt(i) / 2, iTextPosY,
                            m_StatisticPara.GetAt(20 + i - 1).strMin);
                    }
                }
            }

            iTextPosY += iFontH4;
            iCurWPos = printRect.left;
            if (1)
            {
                for (i = 0; i < iStatisticParaNum + 1; i ++)
                {
                    if (i == 0)
                    {
                        iCurWPos = iCurWPos + saveW.GetAt(i);
                        pDC->TextOut(iCurWPos - saveW.GetAt(i) / 2, iTextPosY, "最大偏差Xes");
                    }
                    else
                    {
                        iCurWPos = iCurWPos + saveW.GetAt(i);
                        pDC->TextOut(iCurWPos - saveW.GetAt(i) / 2, iTextPosY,
                            m_StatisticPara.GetAt(20 + i - 1).strMax_D);
                    }
                }
            }

            iTextPosY += iFontH4;
            iCurWPos = printRect.left;
            if (1)
            {
                for (i = 0; i < iStatisticParaNum + 1; i ++)
                {
                    if (i == 0)
                    {
                        iCurWPos = iCurWPos + saveW.GetAt(i);
                        pDC->TextOut(iCurWPos - saveW.GetAt(i) / 2, iTextPosY, "标准差σ");
                    }
                    else
                    {
                        iCurWPos = iCurWPos + saveW.GetAt(i);
                        pDC->TextOut(iCurWPos - saveW.GetAt(i) / 2, iTextPosY,
                            m_StatisticPara.GetAt(20 + i - 1).strTheta);
                    }
                }
            }
        }
        if ((iCur == 3 && m_StatisticPara.GetSize() <= 20) || (iCur == 4 && m_StatisticPara.GetSize() > 20))
        {
            iTextPosX = printRect.left;
            iTextPosY = printRect.top;
            pDC->SetTextAlign(TA_LEFT);
            pDC->SelectObject(&Font2);
            iTextPosY += iFontH2 / 2;   
            pDC->TextOut(iTextPosX, iTextPosY, "4.统计参数区间分布统计");

            pDC->SelectObject(&Font4);
            pDC->SetTextAlign(TA_RIGHT);
            m_StatisticParaMode == 0 ? strTemp.Format("统计方式:统计全部(灯亮)"): 
                strTemp.Format("统计方式:统计合格(灯亮)");
            pDC->TextOut(printRect.right, iTextPosY + iFontH2 * 4 / 5, strTemp); 
            pDC->SetTextAlign(TA_LEFT);

            iTextPosY += iFontH2;

            iTextPosY += iFontH3 / 2; 
            CRect listRect;
            listRect.top = iTextPosY;
            listRect.left = printRect.left;
            listRect.right = printRect.right;
            pDC->SelectObject(&Font4);
            iFontH4 = int(iFontH4 * 1.4);
            for (i = 0; i < m_StatisticPara.GetSize() + 1; i ++)
            {
                pDC->MoveTo(printRect.left, iTextPosY);
                pDC->LineTo(printRect.right, iTextPosY);
                iTextPosY += iFontH4;
                if (i == 20)
                {
                    break;
                }
            }
            pDC->MoveTo(printRect.left, iTextPosY);
            pDC->LineTo(printRect.right, iTextPosY);
            listRect.bottom = iTextPosY;
            pDC->MoveTo(listRect.left, listRect.top);
            pDC->LineTo(listRect.left, listRect.bottom);
            pDC->MoveTo(listRect.right, listRect.top);
            pDC->LineTo(listRect.right, listRect.bottom);


            iTextPosY += iFontH4;  

            int W;
            float fAddH = 0.2f;
            int iCurWPos;
            CArray<int,int> saveW; 
            iCurWPos = printRect.left;
            iTextPosY = listRect.top;
            pDC->SetTextAlign(TA_CENTER);
            int iStatisticParaNum = 0;
            iTextPosY += int(iFontH4 * 0.2);
            if (1)
            {
                W = 16 * iFontW4;
                saveW.Add(W);
                iCurWPos = iCurWPos + W;
                pDC->MoveTo(iCurWPos,listRect.top);
                pDC->LineTo(iCurWPos,listRect.bottom);
                pDC->TextOut(iCurWPos - W / 2, iTextPosY,
                    "区间");
            } 

            for (int i = 0; i < DISTRIBUTION_NUM; i ++)
            {
                if (DISTRIBUTION_NUM - 1  == i)
                {
                    W = printRect.right - iCurWPos;
                    saveW.Add(W);
                    iCurWPos = iCurWPos + W;
                    pDC->MoveTo(iCurWPos,listRect.top);
                    pDC->LineTo(iCurWPos,listRect.bottom);
                    pDC->TextOut(iCurWPos - W / 2, iTextPosY,
                        GetEveryDistributionName(i));
                } 
                else
                {
                    CSize sizeText = pDC->GetOutputTextExtent(GetEveryDistributionName(i));
                    W = sizeText.cx + pDC->GetOutputTextExtent("aa").cx;
                    saveW.Add(W);
                    iCurWPos = iCurWPos + W;
                    pDC->MoveTo(iCurWPos,listRect.top);
                    pDC->LineTo(iCurWPos,listRect.bottom);
                    pDC->TextOut(iCurWPos - W / 2, iTextPosY,
                        GetEveryDistributionName(i));
                }      
            }
            iTextPosY += iFontH4;
            for (int i = 0; i < m_StatisticPara.GetSize(); i ++)
            {
                int saveWCurPos = 0;
                iCurWPos = printRect.left;
                iCurWPos = iCurWPos + saveW.GetAt(saveWCurPos);
                pDC->TextOut(iCurWPos - saveW.GetAt(saveWCurPos) / 2, iTextPosY,
                    GetStatisticParaName(m_StatisticPara.GetAt(i).iIndex, 2)); 
                saveWCurPos ++;     

                for (int j = 0; j < DISTRIBUTION_NUM; j ++)
                {
                    iCurWPos = iCurWPos + saveW.GetAt(saveWCurPos);
                    strTemp.Format("%d (%.2f%%)", m_StatisticPara.GetAt(i).iEveryDistributionNum[j],
                        m_StatisticPara.GetAt(i).fEveryDistributionPer[j]);
                    pDC->TextOut(iCurWPos - saveW.GetAt(saveWCurPos) / 2, iTextPosY,
                        strTemp); 
                    saveWCurPos ++;
                }
                iTextPosY += iFontH4;
                if (i == 19)
                {
                    break;
                }
            }
        }
        if (iCur == 5)
        {
            iTextPosX = printRect.left;
            iTextPosY = printRect.top;
            pDC->SetTextAlign(TA_LEFT);
            iTextPosY += iFontH3 / 2; 
            CRect listRect;
            listRect.top = iTextPosY;
            listRect.left = printRect.left;
            listRect.right = printRect.right;
            pDC->SelectObject(&Font4);
            iFontH4 = int(iFontH4 * 1.4);
            for (i = 20; i < m_StatisticPara.GetSize() + 1; i ++)
            {
                pDC->MoveTo(printRect.left, iTextPosY);
                pDC->LineTo(printRect.right, iTextPosY);
                iTextPosY += iFontH4;
            }
            pDC->MoveTo(printRect.left, iTextPosY);
            pDC->LineTo(printRect.right, iTextPosY);
            listRect.bottom = iTextPosY;
            pDC->MoveTo(listRect.left, listRect.top);
            pDC->LineTo(listRect.left, listRect.bottom);
            pDC->MoveTo(listRect.right, listRect.top);
            pDC->LineTo(listRect.right, listRect.bottom);


            iTextPosY += iFontH4;  

            int W;
            float fAddH = 0.2f;
            int iCurWPos;
            CArray<int,int> saveW; 
            iCurWPos = printRect.left;
            iTextPosY = listRect.top;
            pDC->SetTextAlign(TA_CENTER);
            int iStatisticParaNum = 0;
            iTextPosY += int(iFontH4 * 0.2);
            if (1)
            {
                W = 16 * iFontW4;
                saveW.Add(W);
                iCurWPos = iCurWPos + W;
                pDC->MoveTo(iCurWPos,listRect.top);
                pDC->LineTo(iCurWPos,listRect.bottom);
                pDC->TextOut(iCurWPos - W / 2, iTextPosY,
                    "区间");
            } 

            for (int i = 0; i < DISTRIBUTION_NUM; i ++)
            {
                if (DISTRIBUTION_NUM - 1  == i)
                {
                    W = printRect.right - iCurWPos;
                    saveW.Add(W);
                    iCurWPos = iCurWPos + W;
                    pDC->MoveTo(iCurWPos,listRect.top);
                    pDC->LineTo(iCurWPos,listRect.bottom);
                    pDC->TextOut(iCurWPos - W / 2, iTextPosY,
                        GetEveryDistributionName(i));
                } 
                else
                {
                    CSize sizeText = pDC->GetOutputTextExtent(GetEveryDistributionName(i));
                    W = sizeText.cx + pDC->GetOutputTextExtent("aa").cx;
                    saveW.Add(W);
                    iCurWPos = iCurWPos + W;
                    pDC->MoveTo(iCurWPos,listRect.top);
                    pDC->LineTo(iCurWPos,listRect.bottom);
                    pDC->TextOut(iCurWPos - W / 2, iTextPosY,
                        GetEveryDistributionName(i));
                }      
            }
            iTextPosY += iFontH4;
            for (int i = 20; i < m_StatisticPara.GetSize(); i ++)
            {
                int saveWCurPos = 0;
                iCurWPos = printRect.left;
                iCurWPos = iCurWPos + saveW.GetAt(saveWCurPos);
                pDC->TextOut(iCurWPos - saveW.GetAt(saveWCurPos) / 2, iTextPosY,
                    GetStatisticParaName(m_StatisticPara.GetAt(i).iIndex, 2)); 
                saveWCurPos ++;     

                for (int j = 0; j < DISTRIBUTION_NUM; j ++)
                {
                    iCurWPos = iCurWPos + saveW.GetAt(saveWCurPos);
                    strTemp.Format("%d (%.2f%%)", m_StatisticPara.GetAt(i).iEveryDistributionNum[j],
                        m_StatisticPara.GetAt(i).fEveryDistributionPer[j]);
                    pDC->TextOut(iCurWPos - saveW.GetAt(saveWCurPos) / 2, iTextPosY,
                        strTemp); 
                    saveWCurPos ++;
                }
                iTextPosY += iFontH4;
            }
        }
    }
    pDC->SelectObject(pOldPen);
    pDC->SelectObject(pOldFont);
    pDC->SetTextAlign(TA_LEFT);
}





void CStatisticLedDataContainer::printFoot(CDC *pDC, CRect printRect, int iCur, int iMax)
{

    CFont font; 
    if (printRect.Height() > printRect.Width())
    {
        font.CreateFont((printRect.Height() / 64), 0, 0, 0, 400, FALSE, FALSE, 0,
            ANSI_CHARSET, OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
            DEFAULT_PITCH | FF_MODERN, _T("宋体"));
    }
    else
    {
        font.CreateFont((printRect.Width() / 64), 0, 0, 0, 400, FALSE, FALSE, 0,
            ANSI_CHARSET, OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
            DEFAULT_PITCH | FF_MODERN, _T("宋体"));
    }


    CFont* pOldFont = (CFont*)(pDC->SelectObject(&font));

    TEXTMETRIC  tm;
    pDC->GetTextMetrics(&tm);
    int nfontHeight = tm.tmHeight + tm.tmExternalLeading;
    int nfontWidth = tm.tmAveCharWidth;
    nfontWidth = (int)(nfontWidth * 1.2f);
    int firstline = printRect.bottom + nfontHeight / 2;
    pDC->SetTextAlign(TA_CENTER);

    CString strTemp;
    strTemp.Format(_T("第%d页 共%d页"), 
        iCur, iMax);
    pDC->TextOut((printRect.left + printRect.right) / 2, firstline, strTemp);

    pDC->SelectObject(pOldFont);
}


