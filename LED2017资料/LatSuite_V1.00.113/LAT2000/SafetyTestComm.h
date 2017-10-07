#pragma once
// ChangSheng CS2676CX绝缘电阻测试仪  Common instruction
class CSafetyTest_CSComm2676
{
public:
    CSafetyTest_CSComm2676(void);
    ~CSafetyTest_CSComm2676(void);
    enum TestMode
    {
        IR, //绝缘电阻
        LC, //泄露电流
    };
    enum VoltageWithstandTesterStatus
    {
        WAIT_TOTEST,
        TESTING,
        INTER_WAIT,
        CHARGING,
        DELAY,
        TESTED_Q,
        VOLTAGE_ABNORMITY,
        SHORT_CIRCUIT,
        LIMITUPPER_ALARM,
        LIMITLOWER_ALARM,
        ALARM_TEST,
    };
    struct SetFunctionPara
    {
        float fTestOverVoltage_V; 
        float fAlarmHigh;    
        float fAlarmLow;  
        float fTestTime_s;  
        float fDelayJudge_s;    
        float fInterTestTime_s;    
        float SetfailedTestTime_s;   
        void Serialize(CArchive & ar)
        {
            if (ar.IsStoring())
            {
                ar << fTestOverVoltage_V; 
                ar << fAlarmHigh;    
                ar << fAlarmLow;  
                ar << fTestTime_s;  
                ar << fDelayJudge_s;    
                ar << fInterTestTime_s;    
                ar << SetfailedTestTime_s;  
            }
            else
            {
                ar >> fTestOverVoltage_V; 
                ar >> fAlarmHigh;    
                ar >> fAlarmLow;  
                ar >> fTestTime_s;  
                ar >> fDelayJudge_s;    
                ar << fInterTestTime_s;    
                ar >> SetfailedTestTime_s;
            }
        }
    };
	BOOL m_bHaveInit_CS;
    void Initialize(CString strCOM, int iBaudRate = 9600);
    // PC Software 联调的第一条指令 
    BOOL SetConstructAddress(int ucAdress);
    // Enter Remote
    BOOL SetRemote();
    // Exit Remote
    BOOL SetLocal();
    // Test Start
    BOOL SetTestStart();
    // Test Stop
    BOOL SetTestStop();

    void SetTestType(int imode);

    // Get Test Status
    BOOL GetTestStatus(VoltageWithstandTesterStatus &status);
    // Get Test Data
    BOOL GetTestData(float &fValue);

    // Set Voltage
    BOOL SetTestVoltage_V(float fVlotage);
    // Set High
    BOOL SetAlarmValue_High(float fValue);
    // Set Low
    BOOL SetAlarmValue_Low(float fValue);
    // Set TestTime
    BOOL SetTestTime_s(float fTime);
    // Set DelayJudgeTime
    BOOL SetDelayJudgeTime_s(float fTime);
    // Set InterTestTime
    BOOL SetInterTestTime_s(float fTime);
    // Set FailedTestTime
    BOOL SetFailedTestTime_s(float fTime);
    BOOL SetCommandCode(CString strSerialcmd);

    // 直接调用
    void ShowTestSetDlg();
    BOOL SetAndTest(int iSelIndex);
    BOOL GetValue(float &fValue);

    BOOL SaveFile(CString strPathName);
    BOOL LoadFile(CString strPathName);
    BOOL Serialize(CArchive & ar);

	//要用到的命令
	BOOL CS_Init_IR(CString strCOM);
	BOOL CS_Setup_IR(float fVol,float fTime);
	BOOL CS_Test_IR(BOOL bTest);
	BOOL CS_GetData_IR(float &fIR);

    CArray<SetFunctionPara, SetFunctionPara&> m_paraArray;
private:
    CString m_strCOM;
    int m_iBaudrate;
    int m_iMode;
};

// ChangSheng 9912BI耐压仪  Common instruction
class CSafetyTest_CSComm9912
{
public:
	CSafetyTest_CSComm9912(void);
	~CSafetyTest_CSComm9912(void);

	//要用到的命令
	BOOL CS_Init_NYY(CString strCOM);
	BOOL CS_Setup_NYY(int iType,float fVol,float fTime,float fLimit);
	BOOL CS_Test_NYY(BOOL bTest);
	BOOL CS_GetData_NYY(int iType,BOOL &bOK, float &fIR);
private:
	CString m_strCOM;
	int m_iBaudrate;
	BYTE m_bAD;
};

// ChangSheng 5505泄露电流  Common instruction
class CSafetyTest_CSComm5505
{
public:
	CSafetyTest_CSComm5505(void);
	~CSafetyTest_CSComm5505(void);

	enum VoltageWithstandTesterStatus
	{
		WAIT_TOTEST,
		TESTING,
		INTER_WAIT,
		CHARGING,
		DELAY,
		TESTED_Q,
		VOLTAGE_ABNORMITY,
		SHORT_CIRCUIT,
		LIMITUPPER_ALARM,
		LIMITLOWER_ALARM,
		ALARM_TEST,
	};
	struct SetFunctionPara
	{
		float fTestOverVoltage_V; 
		float fAlarmHigh;    
		float fAlarmLow;  
		float fTestTime_s;  
		float fDelayJudge_s;    
		float fInterTestTime_s;    
		float SetfailedTestTime_s;   
		void Serialize(CArchive & ar)
		{
			if (ar.IsStoring())
			{
				ar << fTestOverVoltage_V; 
				ar << fAlarmHigh;    
				ar << fAlarmLow;  
				ar << fTestTime_s;  
				ar << fDelayJudge_s;    
				ar << fInterTestTime_s;    
				ar << SetfailedTestTime_s;  
			}
			else
			{
				ar >> fTestOverVoltage_V; 
				ar >> fAlarmHigh;    
				ar >> fAlarmLow;  
				ar >> fTestTime_s;  
				ar >> fDelayJudge_s;    
				ar << fInterTestTime_s;    
				ar >> SetfailedTestTime_s;
			}
		}
	};
	BOOL m_bHaveInit_CS;
	void Initialize(CString strCOM, int iBaudRate = 9600);
	// PC Software 联调的第一条指令 
	BOOL SetConstructAddress(int ucAdress);
	// Enter Remote
	BOOL SetRemote();
	// Exit Remote
	BOOL SetLocal();
	// Test Start
	BOOL SetTestStart();
	// Test Stop
	BOOL SetTestStop();

	// Get Test Status
	BOOL GetTestStatus(VoltageWithstandTesterStatus &status);
	// Get Test Data
	BOOL GetTestData(float &fValue);

	// Set Voltage
	BOOL SetTestVoltage_V(float fVlotage);
	// Set High
	BOOL SetAlarmValue_High(float fValue);
	// Set Low
	BOOL SetAlarmValue_Low(float fValue);
	// Set TestTime
	BOOL SetTestTime_s(float fTime);
	// Set DelayJudgeTime
	BOOL SetDelayJudgeTime_s(float fTime);
	// Set InterTestTime
	BOOL SetInterTestTime_s(float fTime);
	// Set FailedTestTime
	BOOL SetFailedTestTime_s(float fTime);
	BOOL SetCommandCode(CString strSerialcmd);

	// 直接调用
	BOOL SetAndTest(int iSelIndex);
	BOOL GetValue(float &fValue);

	//要用到的命令
	BOOL CS_Init_XL(CString strCOM);
	BOOL CS_Setup_XL(float fVol,float fTime);
	BOOL CS_Test_XL(BOOL bTest);
	BOOL CS_GetData_XL(float &fLC,BOOL &bOK);

	CArray<SetFunctionPara, SetFunctionPara&> m_paraArray;
private:
	CString m_strCOM;
	int m_iBaudrate;
	int m_iMode;
};

// Tong hui  Special instruction 绝缘电阻
class CSafetyTest_TongHui_TH2683AComm
{
public:
    CSafetyTest_TongHui_TH2683AComm();
    ~CSafetyTest_TongHui_TH2683AComm();
    void Initialize(CString strCOM, int iBaudRate = 9600);
    struct SetFunctionPara
    {
        BOOL  bClearZero;			// 1 clear zero on; 0 clear zero off
        float fTestOverVoltage_V;	// test voltage value 输出电压
        int   iTestMode;			// 0 sigle; 1 continus
        int   iTestSpeed;			// 0 slow; 1 fast 
        BOOL  bCheckSwitch;			// 0 off 1; 1 on
        float fChargeTime_s;		// charge time value;precision is 0.1s
        float fWaitTime_s;			// wait time value;precision is 0.1s
        float fTestTime_s;			// test time;precision is 0.1s
        float fDischargeTime_s;		// discharge time;precision is 0.1s 
        int   iTestAvgNum;			// test average num;
        int   iRange;				//range; iRange can be 0, 1, 2, 3, 4, 5;relate to 1mA, 100uA, 10uA, 1uA, 100nA, 10nA
        BOOL  bAutoRange;			//auto range
        BOOL  bDisplay;				//screen display

        void Serialize(CArchive & ar)
        {
            if (ar.IsStoring())
            {
                ar << bClearZero; 
                ar << fTestOverVoltage_V;    
                ar << iTestMode;  
                ar << iTestSpeed;  
                ar << bCheckSwitch;    
                ar << fChargeTime_s;    
                ar << fWaitTime_s;  
                ar << fTestTime_s; 
                ar << fDischargeTime_s;    
                ar << iTestAvgNum;  
                ar << iRange;  
                ar << bAutoRange;    
                ar << bDisplay;    
            }
            else
            {
                ar >> bClearZero; 
                ar >> fTestOverVoltage_V;    
                ar >> iTestMode;  
                ar >> iTestSpeed;  
                ar >> bCheckSwitch;    
                ar >> fChargeTime_s;    
                ar >> fWaitTime_s;  
                ar >> fTestTime_s; 
                ar >> fDischargeTime_s;    
                ar >> iTestAvgNum;  
                ar >> iRange;  
                ar >> bAutoRange;    
                ar >> bDisplay;   
            }
        }

        CString GetClearZeroString()
        {
            CString strTemp;
            if (bClearZero)
            {
                strTemp = "FUNC:CZER ON";
            }
            else
            {
                strTemp = "FUNC:CZER OFF";
            }
            return strTemp + '\r' + '\n';
        }
        CString GetTestOverVoltageString()
        {
            CString strTemp;
			strTemp.Format("FUNC:OVOL %.2f", fTestOverVoltage_V);
            return strTemp + '\r' + '\n';
        }
        CString GetTestModeString()
        {
            CString strTemp;
            if (iTestMode == 1)
            {
                strTemp = "FUNC:MMOD CONT";
            }
            else
            {
                strTemp = "FUNC:MMOD SING";
            }
            return strTemp + '\r' + '\n';
        }

        CString GetTestSpeedString()
        {
            CString strTemp;
            if (iTestSpeed)
            {
                strTemp = "FUNC:MSP FAST";
            }
            else
            {
                strTemp = "FUNC:MSP SLOW";
            }
            return strTemp + '\r' + '\n';
        }

        CString GetCheckSwitchString()
        {
            CString strTemp;
            if (bCheckSwitch)
            {
                strTemp = "FUNC:CCH ON";
            }
            else
            {
                strTemp = "FUNC:CCH OFF";
            }
            return strTemp + '\r' + '\n';
        }

        CString GetChargeTimeString()
        {
            CString strTemp;
            strTemp.Format("FUNC:CTIM %.1f", fChargeTime_s);
            return strTemp + '\r' + '\n';
        }

        CString GetWaitTimeString()
        {
            CString strTemp;
            strTemp.Format("FUNC:WTIM %.1f", fWaitTime_s);
            return strTemp + '\r' + '\n';
        }

        CString GetTestTimeString()
        {
            CString strTemp;
            strTemp.Format("FUNC:MTIM %.1f", fTestTime_s);
            return strTemp + '\r' + '\n';
        }

        CString GetDischargeTimeString()
        {
            CString strTemp;
            strTemp.Format("FUNC:DTIM %.1f", fDischargeTime_s);
            return strTemp + '\r' + '\n';
        }

        CString GetTestAvgNumString()
        {
            CString strTemp;
            strTemp.Format("FUNC:AVER %d", iTestAvgNum);
            return strTemp + '\r' + '\n';
        }

        CString GetRangeString()
        {
            CString strTemp;
            switch (iRange)
            {
            case  0:
                strTemp = "1mA";
                break;
            case  1:
                strTemp = "100uA";
                break;
            case  2:
                strTemp = "10uA";
                break;
            case  3:
                strTemp = "1uA";
                break;
            case  4:
                strTemp = "100nA";
                break;
            case  5:
                strTemp = "10nA";
                break;
            default: 
                strTemp = "1mA";
                break;
            }
            return "FUNC:RANG " + strTemp + '\r' + '\n';
        }

       CString GetAutoRangeString()
       {
          CString strTemp;
          if (bAutoRange)
          {
              strTemp = "FUNC:RANG AUTO ON";
          }
          else
          {
              strTemp = "FUNC:RANG AUTO OFF";
          }
          return strTemp + '\r' + '\n';
       }

       CString GetDisplayString()
       {
           CString strTemp;
           if (bDisplay)
           {
               strTemp = "FUNC:MDIS ON";
           }
           else
           {
               strTemp = "FUNC:MDIS OFF";
           }
           return strTemp + '\r' + '\n';
       }
            
	};

	BOOL m_bHaveSetPara;
	SetFunctionPara m_PerData;

    BOOL SetTestFunctionPara(SetFunctionPara &para);
	
	BOOL TH_Setup_IR(float fVol,float fTime);
    BOOL TH_SetTestStart_IR(BOOL bTest);
    BOOL TH_GetTestResult_IR(float &fIR, float &fLC, float &fTime);

	BOOL SetTestDisCharge();
    BOOL SetCommandCode(CString strSerialcmd);
    BOOL SetBeep(BOOL bBeepOn);

    // 直接调用
    void ShowTestSetDlg();
    BOOL SetAndTest(int iSelIndex);
    BOOL GetValue(float &fValue);

    BOOL SaveFile(CString strPathName);
    BOOL LoadFile(CString strPathName);
    BOOL Serialize(CArchive & ar);
    CArray<SetFunctionPara, SetFunctionPara&> m_paraArray;
private:
    CString m_strCOM;
    int m_iBaudrate;
};
//同惠耐压仪
class CSafetyTest_TongHui_TH9310_20Comm
{
public:
    CSafetyTest_TongHui_TH9310_20Comm();
    ~CSafetyTest_TongHui_TH9310_20Comm();  
    struct SetFunctionACPara
    {
       int iVoltage_V;
       float fUpperCurrent_mA;
       float fLowerCurrent_mA;
       float fTestTime_s;     //0.1s precsion
       float fRaiseTime_s;
       float fFallTime_s;
       float fArcweldingCurrent_mA;
       float fFrequency_Hz;
       SetFunctionACPara()
       {
           iVoltage_V		= 1000;
           fUpperCurrent_mA = 0.01f;
           fLowerCurrent_mA = 0.01f;
           fTestTime_s		= 10;    
           fRaiseTime_s		= 10;
           fFallTime_s		= 10;
           fArcweldingCurrent_mA = 1;
           fFrequency_Hz	= 50;
       }
       void Serialize(CArchive & ar)
       {
           if (ar.IsStoring())
           {
               ar << iVoltage_V;
               ar << fUpperCurrent_mA;
               ar << fLowerCurrent_mA;
               ar << fTestTime_s;     //0.1s precsion
               ar << fRaiseTime_s;
               ar << fFallTime_s;
               ar << fArcweldingCurrent_mA;
               ar << fFrequency_Hz;
           }
           else
           {
               ar >> iVoltage_V;
               ar >> fUpperCurrent_mA;
               ar >> fLowerCurrent_mA;
               ar >> fTestTime_s;     //0.1s precsion
               ar >> fRaiseTime_s;
               ar >> fFallTime_s;
               ar >> fArcweldingCurrent_mA;
               ar >> fFrequency_Hz;
           }
       }

       CString GetTestVoltageString()
       {
           CString strTemp;
           strTemp.Format(":AC:VOLT %d", iVoltage_V);
           return strTemp + '\r' + '\n';
       }                                    
       CString GetUpperCurrentString()
       {
           CString strTemp;
           strTemp.Format(":AC:UPPC %f", fUpperCurrent_mA);
           return strTemp + '\r' + '\n';
       }
       CString GetLowerCurrentString()
       {
           CString strTemp;
           strTemp.Format(":AC:LOWC %f", fLowerCurrent_mA);
           return strTemp + '\r' + '\n';
       }
       CString GetTestTimeString()
       {
           CString strTemp;
           strTemp.Format(":AC:TTIM %f", fTestTime_s);
           return strTemp + '\r' + '\n';
       }
       CString GetRaiseTimeString()
       {
           CString strTemp;
           strTemp.Format(":AC:RTIM %f", fRaiseTime_s);
           return strTemp + '\r' + '\n';
       }
       CString GetFallTimeString()
       {
           CString strTemp;
           strTemp.Format(":AC:FTIM %f", fFallTime_s);
           return strTemp + '\r' + '\n';
       }
       CString GetArcweldingString()
       {
           CString strTemp;
           strTemp.Format(":AC:ARC %f", fArcweldingCurrent_mA);
           return strTemp + '\r' + '\n';
       }
       CString GetFrequencyString()
       {
           CString strTemp;
           strTemp.Format(":AC:FREQ:%f", fFrequency_Hz);
           return strTemp + '\r' + '\n';
       }
    };

    struct SetFunctionDCPara
    {
        int iVoltage_V;
        float fUpperCurrent_mA;
        float fLowerCurrent_mA;
        float fTestTime_s;
        float fRaiseTime_s;
        float fFallTime_s;
        float fWaitTime_s;
        float fArcweldingCurrent_A;
        BOOL bRangetoPeak;
        SetFunctionDCPara()
        {
            iVoltage_V = 1000;
            fUpperCurrent_mA = 0.01f;
            fLowerCurrent_mA = 0.01f;
            fTestTime_s = 10;    
            fRaiseTime_s = 10;
            fFallTime_s = 10;
            fWaitTime_s = 10;
            fArcweldingCurrent_A = 0.001f;
            bRangetoPeak = FALSE;
        }
        void Serialize(CArchive & ar)
        {
            if (ar.IsStoring())
            {
                ar << iVoltage_V;
                ar << fUpperCurrent_mA;
                ar << fLowerCurrent_mA;
                ar << fTestTime_s;
                ar << fRaiseTime_s;
                ar << fFallTime_s;
                ar << fWaitTime_s;
                ar << fArcweldingCurrent_A;
                ar << bRangetoPeak;
            }
            else
            {
                ar >> iVoltage_V;
                ar >> fUpperCurrent_mA;
                ar >> fLowerCurrent_mA;
                ar >> fTestTime_s;
                ar >> fRaiseTime_s;
                ar >> fFallTime_s;
                ar >> fWaitTime_s;
                ar >> fArcweldingCurrent_A;
                ar >> bRangetoPeak;
            }
        }
        CString GetTestVoltageString()
        {
            CString strTemp;
            strTemp.Format(":DC:VOLT %d", iVoltage_V);
            return strTemp + '\r' + '\n';
        }                                    
        CString GetUpperCurrentString()
        {
            CString strTemp;
            strTemp.Format(":DC:UPPC %f", fUpperCurrent_mA);
            return strTemp + '\r' + '\n';
        }
        CString GetLowerCurrentString()
        {
            CString strTemp;
            strTemp.Format(":DC:LOWC %f", fLowerCurrent_mA);
            return strTemp + '\r' + '\n';
        }
        CString GetTestTimeString()
        {
            CString strTemp;
            strTemp.Format(":DC:TTIM %f", fTestTime_s);
            return strTemp + '\r' + '\n';
        }
        CString GetRaiseTimeString()
        {
            CString strTemp;
            strTemp.Format(":DC:RTIM %f", fRaiseTime_s);
            return strTemp + '\r' + '\n';
        }
        CString GetFallTimeString()
        {
            CString strTemp;
            strTemp.Format(":DC:FTIM %f", fFallTime_s);
            return strTemp + '\r' + '\n';
        }
        CString GetWaitTimeString()
        {
            CString strTemp;
            strTemp.Format(":DC:WTIM %f", fWaitTime_s);
            return strTemp + '\r' + '\n';
        }
        CString GetArcweldingString()
        {
            CString strTemp;
            strTemp.Format(":DC:ARC %f", fArcweldingCurrent_A);
            return strTemp + '\r' + '\n';
        }
        CString GetRangetoPeakString()
        {
            CString strTemp;
            if (bRangetoPeak)
            {
                strTemp.Format(":DC:RAMP ON");                
            }
            else
            {
                strTemp.Format(":DC:RAMP OFF");
            }
            return strTemp + '\r' + '\n';
        }
    };
	SetFunctionDCPara m_dPerParaDC;
	SetFunctionACPara m_dPerParaAC;
	BOOL m_bHaveSetAC;
	BOOL m_bHaveSetDC;

	BOOL TH_Init_NYY(CString strCOM);
	BOOL TH_Setup_NYY(int iTestType,float fVol,float fTime);
	BOOL TH_SetTestStart_NYY(BOOL bTest);
	BOOL TH_GetTestResult_NYY(float &fLC);
	BOOL TH_GetTestResult_NYY_N(float &fLC);

    void Initialize(CString strCOM, int iBaudRate = 9600);
    // Set Voltage
    BOOL SetTestFunctionACPara(int iStep, SetFunctionACPara &para);
    BOOL SetTestFunctionDCPara(int iStep, SetFunctionDCPara &para);
    BOOL SetCommandCode(CString strSerialcmd);
    BOOL SetTestStart(int iStep);
    BOOL SetTestStop(int iStep);
    BOOL AllStepNew();
    BOOL AddOneStep();
    BOOL DelOneStep(int iStep);

    // 直接调用
    struct SetFunctionPara
    {
        CArray<SetFunctionACPara, SetFunctionACPara&> m_ACparaArray;
        CArray<SetFunctionDCPara, SetFunctionDCPara&> m_DCparaArray;
        SetFunctionPara &operator = (SetFunctionPara &data)
        {
            if (this == &data)
            {
                return *this;
            }
            m_ACparaArray.RemoveAll();
            m_DCparaArray.RemoveAll();
            for (int i = 0; i < m_ACparaArray.GetSize(); i ++)
            {
                m_ACparaArray.Add(data.m_ACparaArray.GetAt(i));
            }
            for (int i = 0; i < m_DCparaArray.GetSize(); i ++)
            {
                m_DCparaArray.Add(data.m_DCparaArray.GetAt(i));
            }
            return *this;
        }
        void Serialize(CArchive &ar)
        {
            if (ar.IsStoring())
            {
                ar << m_ACparaArray.GetSize();
                for (int i = 0; i < m_ACparaArray.GetSize(); i ++)
                {
                    m_ACparaArray.Serialize(ar);
                }
                ar << m_DCparaArray.GetSize();
                for (int i = 0; i < m_DCparaArray.GetSize(); i ++)
                {
                    m_DCparaArray.Serialize(ar);
                }
            }
            else
            {
                int iN;
                ar >> iN;
                m_ACparaArray.RemoveAll();
                for (int i = 0; i < iN; i ++)
                {
                    SetFunctionACPara para;
                    para.Serialize(ar);
                    m_ACparaArray.Add(para);
                }
                m_DCparaArray.RemoveAll();
                ar >> iN;
                for (int i = 0; i < iN; i ++)
                {
                    SetFunctionDCPara para;
                    para.Serialize(ar);
                    m_DCparaArray.Add(para);
                }
            }
        }
    };
    void ShowTestSetDlg();
    BOOL SetAndTest(int iSelIndex);

    BOOL SaveFile(CString strPathName);
    BOOL LoadFile(CString strPathName);
    BOOL Serialize(CArchive & ar);
    CArray<SetFunctionPara, SetFunctionPara&> m_paraArray;

private:
    CString m_strCOM;
    int m_iBaudrate;
};
