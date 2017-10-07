#pragma once
#include "LEDDataContainer.h"
#include "_grid.h"
#include "TestSettingsData.h"
#include "TestInfoData.h"
enum StatisticParaIndex
{
    STATISTIC_CURR,
    STATISTIC_VOL,
    STATISTIC_FRE,
    STATISTIC_POW,
    STATISTIC_FACTOR,
    STATISTIC_FLUX,
    STATISTIC_TC,
    STATISTIC_CIE_X,
    STATISTIC_CIE_Y,
    STATISTIC_CIE_U,
    STATISTIC_CIE_V,
    STATISTIC_LD,
    STATISTIC_HW,
    STATISTIC_LP,
    STATISTIC_IP,
    STATISTIC_PUR,
    STATISTIC_RA,
    STATISTIC_EFFIC,
    STATISTIC_R1,
    STATISTIC_R2,
    STATISTIC_R3,
    STATISTIC_R4,
    STATISTIC_R5,
    STATISTIC_R6,
    STATISTIC_R7,
    STATISTIC_R8,
    STATISTIC_R9,
    STATISTIC_RR,
    STATISTIC_GR,
    STATISTIC_BR,
};

enum StatisticParaMode
{
    STATISTIC_ALL,
    STATISTIC_Q

};


extern int g_iEveryDistribution_Oper[DISTRIBUTION_NUM - 1]; 


struct StatisticPara
{
    BOOL bStatistic;
    StatisticParaIndex iIndex;  
    CString strAvg;
    CString strMax;
    CString strMin;
    CString strMax_D;
    CString strTheta;

    float fAvg;
    float fMax;
    float fMin;
    float fMax_D;
    float fTheta;
    int m_iTotalNum;

    int iEveryDistributionNum[DISTRIBUTION_NUM];
    float fEveryDistributionPer[DISTRIBUTION_NUM];
    int GetTotalNum()
    {
        m_iTotalNum = 0;
        for (int i = 0; i < DISTRIBUTION_NUM; i++)
        {
            m_iTotalNum += iEveryDistributionNum[i];
        }
        return m_iTotalNum;
    }
    void CalcDistributionPer()
    {  
        for (int i = 0; i < DISTRIBUTION_NUM; i++)
        {
            fEveryDistributionPer[i] = iEveryDistributionNum[i]* 1.0f * 100/ GetTotalNum(); 
        }

    }
    StatisticPara()
    {
        iIndex = STATISTIC_CURR;
        m_iTotalNum = 0;
    }
};
class CStatisticLedDataContainer
{
public:
    CStatisticLedDataContainer(void);
    ~CStatisticLedDataContainer(void);

    int GetCanStatisticParaNum();

    int GetStatisticParaNum();

    void SetbStatisticPara(int iPara, BOOL bStatistic);

    void SetbStatisticPara(BOOL bStatistic[]);

    BOOL IsSelectedToStatistic(int iPara);

    // StatisticPara Name
    CString GetStatisticParaName(StatisticParaIndex iPara, int iType); 

    void toStatisticPara();
    BOOL IsAllStatisticPara(BOOL bMgsbox);


    void CalcStatisticMinMax(CArray<float, float> &fArray, float &fAvg, float &fMax, float &fMin,
        float &fMax_D, float &fTheta);

    void SetStatisticParaMode(StatisticParaMode Mode);

    CString GetStatisticItemText(int iRow, int iCol); 
    void ListStatisticData(C_Grid & m_grid);

    CString GetStatisticDistributeItemText(int iRow, int iCol);
    void ListStatisticDistributeData(C_Grid & m_grid);


    int GetQLEDNum();

    int GetUnQLEDNum();

    int GetUnONLEDNum();

    float GetQLEDNumPer();

    float GetUnQLEDNumPer();

    float GetUnONLEDNumPer();

    void printHead(CDC *pDC, CRect printRect);
    void printReport(CDC *pDC, CRect printRect, int iCur);
    void printFoot(CDC *pDC, CRect printRect, int iCur, int iMax);

    CString GetEveryDistributionName(int iCur)
    {
        CString strTemp;     
        CString str;
        if (iCur == 0)
        {
            strTemp.Format("(-﹢,Xavg%d考)", g_iEveryDistribution_Oper[0]);
            return strTemp;
        }
        if (iCur == DISTRIBUTION_NUM - 1)
        {
            strTemp.Format("[Xavg+%d考,+﹢)", g_iEveryDistribution_Oper[DISTRIBUTION_NUM - 2]);
            return strTemp;
        }
        if (g_iEveryDistribution_Oper[iCur - 1] < -1)
        {
            str.Format("[Xavg%d考,", g_iEveryDistribution_Oper[iCur - 1]);
        }
        else if (g_iEveryDistribution_Oper[iCur - 1] == -1)
        {
            str.Format("[Xavg-考,");

        }
        else if (g_iEveryDistribution_Oper[iCur - 1] == 0)
        {
            str.Format("[Xavg,");
        }
        else if (g_iEveryDistribution_Oper[iCur - 1] == 1)
        {
            str.Format("[Xavg+考,");
        }
        else
        {
            str.Format("[Xavg+%d考,", g_iEveryDistribution_Oper[iCur - 1]);
        }
        strTemp += str; 
        if (g_iEveryDistribution_Oper[iCur] < -1)
        {
            str.Format("Xavg%d考)", g_iEveryDistribution_Oper[iCur]);
        }
        else if (g_iEveryDistribution_Oper[iCur] == -1)
        {
            str.Format("Xavg-考)");  
        }
        else if (g_iEveryDistribution_Oper[iCur] == 0)
        {
            str.Format("Xavg)");  
        }
        else if (g_iEveryDistribution_Oper[iCur] == 1)
        {
            str.Format("Xavg+考)");  
        }
        else
        {
            str.Format("Xavg+%d考)", g_iEveryDistribution_Oper[iCur]);
        }
        strTemp += str; 
        return strTemp;
    }

    StatisticPara&  GetCurSelStatisticPara(int Row)
    {
        return m_StatisticPara.GetAt(Row);
    }

    CTestInfoData & GetTestInfoData()
    {
        return m_TestInfoData;
    }


    CTestSettingsData &	GetTestSettingData()
    {
        return m_TestSettingsData;
    }

    void AddLedData(CLedData &data)
    {
        CLedData *pTemp = new CLedData;
        *pTemp = data; 
        m_data.Add(*pTemp);
    }

    void RemoveAllLedData()
    {
        m_data.RemoveAll();
    }

    int GetSize()
    {
        return m_data.GetSize();
    }
private:
    int m_iCanStatisticParaNum;
    BOOL *m_pParaStatistic;    
    StatisticParaMode m_StatisticParaMode;  


    void CalcStatisticDistibutePara(CArray<float, float>&fArray, 
        float fAvg, float fTheta, StatisticPara &para);
    CArray<StatisticPara, StatisticPara &> m_StatisticPara;
    CArray<BOOL, BOOL > m_bStatisticQArray;
    CArray<BOOL, BOOL > m_bStatisticUnONArray;
    int m_iQLEDNum;
    int m_iUnQLEDNum;
    int m_iUnOnLEDNum;
    CArray<CLedData, CLedData &> m_data;
    CTestSettingsData m_TestSettingsData;
    CTestInfoData m_TestInfoData;
};

