//
#ifndef _NEW_POW_DLL_H_
#define _NEW_POW_DLL_H_
#include "Serial.h"

extern CString g_strCurrentPath;
//
// 获得功率的类型总数
//
extern int __stdcall NewPowDll_GetPowerMeterTypeCount();

//
// 获得各功率计的类型名称
//
extern int __stdcall NewPowDll_GetSelePowerMeterType(int iSele, char szName[]);

//
// 通讯指定的功率电参数
//
//    iPowNum:  一般返回1或2
//    如是1或2, fU1, fI1, fP1,fPf1有效
//    如是1，fU2,fI2,fP2,fPf2效
//
extern BOOL __stdcall NewPowDll_GetPower(int iCom, char szMeterType[], int &iPowNum, 
												 float &fU1,float &fI1,float &fP1,float &fPf1,
												 float &fU2,float &fI2,float &fP2,float &fPf2);

enum PowerMeterRangeU
{
	PM_URange_30V	= 0,
	PM_URange_60V	= 1,
	PM_URange_100V	= 2,
	PM_URange_200V	= 3,
	PM_URange_400V	= 4,
	PM_URange_600V	= 5,
};

enum PowerMeterRangeI
{
	PM_IRange_0_5A	= 0,
	PM_IRange_1A	= 1,
	PM_IRange_2A	= 2,
	PM_IRange_5A	= 3,
	PM_IRange_10A	= 4,
	PM_IRange_20A	= 5,
};

enum PowerMeterRangeCF
{
	PM_CFRange_CF3 = 0,
	PM_CFRange_CF6 = 0,
};

class CPowerMeterComm
{
public:
	inline CPowerMeterComm()
	{
		m_iCOM = 1;
		m_strTypeName = "PF2010A";
       m_bDemo = FALSE;
      

    
	}

	inline ~CPowerMeterComm()
	{
	}

public:
    void SetDemo(BOOL bDemo)
    {
        m_bDemo= bDemo;
    }
	inline int GetTypeCount()
	{
		return NewPowDll_GetPowerMeterTypeCount();
	}

	inline CString GetTypeName(int iSele)
	{
		char strName[256];
		NewPowDll_GetSelePowerMeterType(iSele, strName);
		CString strTemp = strName;

		return strTemp;
	}

	inline BOOL Initialize(CString strCOM, int iPFType = 0, int iCF = 0)
	{
		strCOM.Trim().MakeUpper();
		sscanf_s(strCOM.GetBuffer(), "COM%d", &m_iCOM);
        m_WT210VolRangeArray.RemoveAll();
        m_WT210CurRangeArray.RemoveAll();
		m_PF2010VolRangeArray.RemoveAll();
		m_PF2010CurRangeArray.RemoveAll();
        if (iPFType)
        {
            m_strTypeName = "WT210";
            if (iCF == 0)
            {
                float fWT210VolRangeArray[] = {15, 30 , 60, 100, 150, 300, 600};   // from3;
                float fWT210CurRangeArray[] = {0.5, 1 , 2, 5, 10, 20};      // from4;
                for (int i = 0; i < sizeof(fWT210VolRangeArray) / sizeof(float); i ++)
                {
                    m_WT210VolRangeArray.Add(fWT210VolRangeArray[i]);
                }   
                for (int i = 0; i < sizeof(fWT210CurRangeArray) / sizeof(float); i ++)
                {
                    m_WT210CurRangeArray.Add(fWT210CurRangeArray[i]);
                }
            }
            else
            {
                float fWT210VolRangeArray[] = {7.5, 15, 30, 75, 150, 300};
                float fWT210CurRangeArray[] = {0.25, 0.5 , 1, 2.5, 5, 10};
                for (int i = 0; i < sizeof(fWT210VolRangeArray) / sizeof(float); i ++)
                {
                    m_WT210VolRangeArray.Add(fWT210VolRangeArray[i]);
                }   
                for (int i = 0; i < sizeof(fWT210CurRangeArray) / sizeof(float); i ++)
                {
                    m_WT210CurRangeArray.Add(fWT210CurRangeArray[i]);
                }
            }
            if (!m_bDemo)
            {
                CString strTemp;
				HANDLE comHandle;
                BOOL bR;
                strTemp.Format("COM%d", m_iCOM);
                bR = m_ser.Open(comHandle,strTemp, 9600);
                if(!bR)
                    return FALSE;

                BYTE byteCMD[256];
                CString strSerialcmd;
                strSerialcmd.Format(_T("MN0"));
                int i;
                for (i = 0; i < strSerialcmd.GetLength(); i++)
                {
                    byteCMD[i]= (BYTE)strSerialcmd.GetAt(i);
                }
                byteCMD[i] = 0x0D;
                byteCMD[i + 1] = 0x0A;
                bR = m_ser.Output(comHandle,byteCMD, strSerialcmd.GetLength() + 2);
                bR = m_ser.Output(comHandle,byteCMD, strSerialcmd.GetLength() + 2);
                bR = m_ser.Output(comHandle,byteCMD, strSerialcmd.GetLength() + 2);
				m_ser.Close(comHandle);
                if(!bR)
                    return FALSE;
            }
        }
        else
        {
            float fPF2010VolRangeArray[] = {30, 60 , 100, 200, 400, 600};   // from3;
            float fPF2010CurRangeArray[] = {0.5, 1 , 2, 5, 10, 20};      // from4;
            m_strTypeName = "TYPE 8 BITS";
            for (int i = 0; i < sizeof(fPF2010VolRangeArray) / sizeof(float); i ++)
            {
                m_PF2010VolRangeArray.Add(fPF2010VolRangeArray[i]);
            }   
            for (int i = 0; i < sizeof(fPF2010CurRangeArray) / sizeof(float); i ++)
            {
                m_PF2010CurRangeArray.Add(fPF2010CurRangeArray[i]);
            }
        }
		return TRUE;
	}

	inline BOOL SetCurrentAutoRange(BOOL bAuto)
	{
		if (m_bDemo)
		{
			return TRUE;
		}
		if (m_strTypeName == "WT210")
		{     
			HANDLE comHandle;
			Serial ser;
			int i;
			BOOL bR;  
			CString strCom;
			strCom.Format(_T("COM%d"),m_iCOM);
			bR = ser.Open(comHandle,strCom, 9600);
			if (bR == FALSE)
			{
				return FALSE;
			}
			CString strSerialcmd;
			BYTE byteCMD[256];

			strSerialcmd.Format(_T("AA%d"), bAuto);
			for (i = 0; i < strSerialcmd.GetLength(); i++)
			{
				byteCMD[i]= (BYTE)strSerialcmd.GetAt(i);
			}
			byteCMD[i] = 0x0D;
			byteCMD[i + 1] = 0x0A;
			bR = ser.Output(comHandle,byteCMD, strSerialcmd.GetLength() + 2);
			bR = ser.Output(comHandle,byteCMD, strSerialcmd.GetLength() + 2);
			bR = ser.Output(comHandle,byteCMD, strSerialcmd.GetLength() + 2);
			ser.Close(comHandle);
		}
		return TRUE;
	}


	inline BOOL GetCurrentAutoRange(int &iCurSel)
	{
		if (m_bDemo)
		{
			return TRUE;
		}
		if (m_strTypeName == "WT210")
		{
			BYTE	In[200];
			BYTE	Out[10];
			BOOL	bR;
			/*~~~~~~~~~~~~*/
			HANDLE comHandle;
			CString strTemp;
			int i = 0;
			strTemp.Format("COM%d", m_iCOM);
			bR = m_ser.Open(comHandle, strTemp, 9600);
			if(!bR)
				return FALSE;

			Out[0] = 'O';
			Out[1] = 'S';
			Out[2] = ' ';
			Out[3] = 0X0D;
			Out[4] = 0X0A;
			bR = m_ser.Output(comHandle, Out, 5);
			if(!bR)
			{
				return FALSE;
			}

			m_ser.SetReadTime(comHandle, 2000, 2, 2000);

			/*~~~~~~~~~~*/
			int iErrN = 0;
			int iIn = 0;
			/*~~~~~~~~~~*/
            strTemp = "";
			DWORD dwTime = ::GetCurrentTime();
			while(1 && ((DWORD)(::GetCurrentTime()) - dwTime < 2000))
			{
					/*~~~~~~~~~~*/
					BYTE	bb[1];
					/*~~~~~~~~~~*/

					bR = m_ser.Input(comHandle, bb, 1);
					In[iIn] = bb[0];
					if(iIn > 3)
					{
						if(In[iIn - 2] == 'E' && In[iIn - 1] == 'N' && In[iIn] == 'D') break;
					}

					iIn++;
					if(iIn > 120) break;
					if(bR == FALSE)
					{
						iErrN++;
						if(iErrN >= 3)
						{
							m_ser.Close(comHandle);
							return FALSE;
						}
					}
                    strTemp += char(bb[0]);
			}

			m_ser.Close(comHandle);               
			if(!bR)
				return FALSE;
            int iIndex = 0;
            iIndex = strTemp.Find("RA", iIndex);
            CString strTemp2;
            if (-1 != iIndex)
            {
                strTemp2 = strTemp.Mid(iIndex, 8);
                sscanf_s(strTemp2, "RA%d", &iCurSel);
            }
            if (iCurSel < 4 || iCurSel > 9)
            {
                iCurSel = 4;
            }
            iCurSel -= 4;
		}
		return TRUE;		
	}
    inline BOOL CommWT210Data(float &fVoltage, float &fCurrentA, float &fPower, float &fPowerFactor)
    {
        BYTE	In[200];
        BYTE	Out[10];
        BOOL	bR;
        /*~~~~~~~~~~~~*/
        HANDLE comHandle;
        CString strTemp;
        int i = 0;
        BOOL bDataError = FALSE;
        
        bDataError = FALSE;
        strTemp.Format("COM%d", m_iCOM);
        bR = m_ser.Open(comHandle, strTemp, 9600);
        if(!bR)
            return FALSE;

        Out[0] = 'O';
        Out[1] = 'D';
        Out[2] = ' ';
        Out[3] = 0X0D;
        Out[4] = 0X0A;
        bR = m_ser.Output(comHandle, Out, 5);
        if(!bR)
        {
            return FALSE;
        }

        m_ser.SetReadTime(comHandle, 2000, 2, 2000);

        /*~~~~~~~~~~*/
        int iIn = 0;
        /*~~~~~~~~~~*/
        DWORD dwTime = ::GetCurrentTime();
        while(1 && ((DWORD)(::GetCurrentTime()) - dwTime < 5000))
        {
            {
                /*~~~~~~~~~~*/
                BYTE	bb[1];
                /*~~~~~~~~~~*/

                bR = m_ser.Input(comHandle, bb, 1);
                if(bR == FALSE)
                {
                    m_ser.Close(comHandle);
                    return FALSE;
                }
                In[iIn] = bb[0];
                if(iIn > 3)
                {
                    if(In[iIn - 2] == 'E' && In[iIn - 1] == 'N' && In[iIn] == 'D') break;
                }
                iIn++;
                if(iIn > 120) break;

            }
        }

        m_ser.Close(comHandle);               
        if(!bR)
            return FALSE;

        /*~~~~~~~~~~~*/
        BYTE	bb[10];
        int		iB = 0;
        /*~~~~~~~~~~~*/

        while(1)
        {
            if(In[iB] == 'V')
            {
                break;
            }
            else  
            {
                iB++;
                if (iB > iIn)
                {
                    bDataError = TRUE;
                    break;
                }
            }
        }


        for(i = 0; i < 10; i++) bb[i] = In[i + 7 + iB];
        fVoltage = m_ser.ASCIItof(bb, 10, strTemp);
        while(1)
        {
            if(In[iB] == 'A')
            {
                break;
            }
            else
            {
                iB++;
                if (iB > iIn)
                {   
                    bDataError = TRUE;
                    break;
                }
            }
        }


        for(i = 0; i < 10; i++) bb[i] = In[i + iB + 7];
        fCurrentA = m_ser.ASCIItof(bb, 10, strTemp);
        while(1)
        {
            if(In[iB] == 'W')
            {
                break;
            }
            else
            {
                iB++;
                if (iB > iIn)
                {  
                    bDataError = TRUE;
                    break;
                }
            }
        }



        if (bDataError == TRUE)
        {
            return FALSE;
        }

        for(i = 0; i < 10; i++) bb[i] = In[i + iB + 7];
        fPower = m_ser.ASCIItof(bb, 10, strTemp);
        if(fVoltage * fCurrentA != 0)
            fPowerFactor = fPower / (fVoltage * fCurrentA);
        else
            fPowerFactor = 1;
        return TRUE;
    }
	inline BOOL Read(float &fVoltage, float &fCurrentA, float &fPower, float &fPowerFactor)
	{
        if (m_bDemo)
        {
            fVoltage	= 220.0f;
            fCurrentA	= 0.02f;
            fPower		= 4.0f;
            fPowerFactor = fPower / (fVoltage * fCurrentA); 
            return TRUE;
        }
		int iPowerNumber;
		float fVoltage1, fCurrent1, fPower1, fPowerFactor1;
        BOOL bR;
		//FILE *fp;
 	//	if ((fopen_s(&fp,g_strCurrentPath + ".txt", "a")))
 	//	{
 	//	}
 	//	else
 	//	{
 	//		fprintf(fp,"1\n");
 	//	}
        if (m_strTypeName == "WT210")
        {
            int iErrorNum = 0;
            while(1)
            {
                bR = CommWT210Data(fVoltage, fCurrentA, fPower, fPowerFactor);
                if (bR)
                {
                    if (fCurrentA <= 0.001f)
                    {
                        bR = CommWT210Data(fVoltage, fCurrentA, fPower, fPowerFactor);
                    }
                    break;
                }
                else
                {
                    iErrorNum ++;
                    if (iErrorNum > 5)
                    {
                        return FALSE;
                    }
                }
            }

        }
        else
        {
		    bR = NewPowDll_GetPower(m_iCOM, m_strTypeName.GetBuffer(), iPowerNumber,
			    fVoltage, fCurrentA, fPower, fPowerFactor,
			    fVoltage1, fCurrent1, fPower1, fPowerFactor1);

            if (!bR)
            {    
                bR = NewPowDll_GetPower(m_iCOM, m_strTypeName.GetBuffer(), iPowerNumber,
                    fVoltage, fCurrentA, fPower, fPowerFactor,
                    fVoltage1, fCurrent1, fPower1, fPowerFactor1);
                if (!bR)
                {
                    return FALSE;
                }
            }
            if (fCurrentA > 0.001 && fPower < g_fUnOnPowLimit)
            {
                bR = NewPowDll_GetPower(m_iCOM, m_strTypeName.GetBuffer(), iPowerNumber,
                    fVoltage, fCurrentA, fPower, fPowerFactor,
                    fVoltage1, fCurrent1, fPower1, fPowerFactor1);
                if (!bR)
                {
                    return FALSE;
                }
            }
        }

        return TRUE;
	}

	
	inline BOOL SetRange(int iRangeU, int iRangeI, int iRangeCF)
	{
        if (m_bDemo)
        {
            return TRUE;
        }
        if (m_strTypeName == "WT210")
        {     
			HANDLE comHandle;
            Serial ser;
            int i;
            BOOL bR;  
            CString strCom;
            strCom.Format(_T("COM%d"),m_iCOM);
            bR = ser.Open(comHandle,strCom, 9600);
            if (bR == FALSE)
            {
                return FALSE;
            }
            CString strSerialcmd;
            BYTE byteCMD[256];
            
            strSerialcmd.Format(_T("CF%d"), iRangeCF);
            for (i = 0; i < strSerialcmd.GetLength(); i++)
			{
				byteCMD[i]= (BYTE)strSerialcmd.GetAt(i);
			}
			byteCMD[i] = 0x0D;
			byteCMD[i + 1] = 0x0A;
			bR = ser.Output(comHandle,byteCMD, strSerialcmd.GetLength() + 2);
            Sleep(10);
			bR = ser.Output(comHandle,byteCMD, strSerialcmd.GetLength() + 2);
            Sleep(10);
			bR = ser.Output(comHandle,byteCMD, strSerialcmd.GetLength() + 2);
            if (bR == FALSE)
            {
                ser.Close(comHandle);
                return FALSE;
            }  
            Sleep(100);
            int iIndex  = 0;
            if (iRangeCF == 0)
            {               
                iIndex = iRangeU + 3;          
            }
            else
            {
                 if (iRangeU <= 2)
                 {
                     iIndex = iRangeU + 3;
                 }
                 else
                 {
                     iIndex = iRangeU + 4;
                 }
               
            }
         
            strSerialcmd.Format(_T("RV%d"), iIndex);
            for (i = 0; i < strSerialcmd.GetLength(); i++)
            {
                byteCMD[i]= (BYTE)strSerialcmd.GetAt(i);
            }
            byteCMD[i] = 0x0D;
            byteCMD[i + 1] = 0x0A;
            bR = ser.Output(comHandle,byteCMD, strSerialcmd.GetLength() + 2);
            Sleep(10);
            bR = ser.Output(comHandle,byteCMD, strSerialcmd.GetLength() + 2);
            Sleep(10);
            bR = ser.Output(comHandle,byteCMD, strSerialcmd.GetLength() + 2);

            if (bR == FALSE)
            {
                ser.Close(comHandle);
                return FALSE;
            }     
            Sleep(100);
            iIndex = iRangeI + 4;  
            strSerialcmd.Format(_T("RA%d"), iIndex);
            for (i = 0; i < strSerialcmd.GetLength(); i++)
            {
                byteCMD[i]= (BYTE)strSerialcmd.GetAt(i);
            }
            byteCMD[i] = 0x0D;
            byteCMD[i + 1] = 0x0A;
            bR = ser.Output(comHandle,byteCMD, strSerialcmd.GetLength() + 2);
            Sleep(10);
            bR = ser.Output(comHandle,byteCMD, strSerialcmd.GetLength() + 2);
            Sleep(10);
            bR = ser.Output(comHandle,byteCMD, strSerialcmd.GetLength() + 2);


            if (bR == FALSE)
            {
                ser.Close(comHandle);
                return FALSE;
            }       

            
           ser.Close(comHandle);   
           return TRUE;

        }
        else
        {
			HANDLE comHandle;
            CString strTemp;
            strTemp.Format("COM%d", m_iCOM);

            BOOL bR = m_ser.Open(comHandle,strTemp, 2400);
            if (!bR)
            {
                return FALSE;
            }

            m_ser.SetReadTime(comHandle,1000, 1, 1000);

            BYTE ucOut[16];
            BYTE ucIn[16];
            ucOut[0] = 0xA1;
            m_ser.Output(comHandle,ucOut, 1);
            Sleep(10);
            bR = m_ser.Input(comHandle,ucIn, 1);
            if (!bR || ucIn[0] != (BYTE)~ucOut[0])
            {
                m_ser.Close(comHandle);
                return FALSE;
            }

            ucOut[0] = (BYTE)iRangeCF;
            ucOut[1] = (BYTE)iRangeU;
            ucOut[2] = (BYTE)iRangeI;
            m_ser.Output(comHandle,ucOut, 3);
            m_ser.Input(comHandle,ucIn, 1);
            if (!bR || ucIn[0] == 0x01)
            {
                m_ser.Close(comHandle);
                return FALSE;
            }

            m_ser.Close(comHandle);
            Sleep(1000);
            return TRUE;
        }
        return TRUE;

	}

    int GetVolRangeNum()
    {
        if (m_strTypeName == "WT210")
        {
            return m_WT210VolRangeArray.GetSize();
        }
        else
        {
            return m_PF2010VolRangeArray.GetSize();
        }
    }
    float GetVolRange(int iCurRange)
    {
        if (m_strTypeName == "WT210")
        {
            return m_WT210VolRangeArray.GetAt(iCurRange);
        }
        else
        {
            return m_PF2010VolRangeArray.GetAt(iCurRange);
        }
    }
    int GetCurRangeNum()
    {
        if (m_strTypeName == "WT210")
        {
            return m_WT210CurRangeArray.GetSize();
        }
        else
        {
            return m_PF2010CurRangeArray.GetSize();
        }
    }
    float GetCurRange(int iCurRange)
    {
        if (m_strTypeName == "WT210")
        {
            return m_WT210CurRangeArray.GetAt(iCurRange);
        }
        else
        {
            return m_PF2010CurRangeArray.GetAt(iCurRange);
        }
    }

    
private:
    BOOL m_bDemo;
    int m_iCF; 
	int m_iCOM;
	Serial m_ser;
	CString m_strTypeName;
    CArray<float, float> m_WT210VolRangeArray;
    CArray<float, float>m_WT210CurRangeArray;
    CArray<float, float>m_PF2010VolRangeArray;
    CArray<float, float>m_PF2010CurRangeArray;


};

#endif
