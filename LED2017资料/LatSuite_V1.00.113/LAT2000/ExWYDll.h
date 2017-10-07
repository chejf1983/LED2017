//ExWYDll.h
//远方(EVERFINE)WY系列电源 DLL开发库
//版本:   V1.02
//时间:   2012.9

#ifndef _EXWYDLL_H_
#define _EXWYDLL_H_


struct ExPowerSettings
{
	BOOL m_bUse;
	BOOL m_iPowerType;
	int	 m_iCOM;
	int	 m_iAddr;
	int	 m_iMode;

	BOOL m_bManualControl;
	int  m_iRangeU;
	float m_fRangeI;

	ExPowerSettings()
	{
		m_bManualControl = FALSE;
		m_iPowerType = 0;
		m_iAddr = 0x64;
		
		m_bUse = TRUE;
		m_iCOM = 1;
		m_iMode = 1;
		m_fRangeI = 5;
		m_iRangeU = 30;
	}

	void ReadRegister()
	{
		CString strSection  = "ExPowerSettings";
		m_iCOM = AfxGetApp()->GetProfileInt(strSection, "m_iCOM", 1);
		m_iMode = AfxGetApp()->GetProfileInt(strSection, "m_iMode", 1);
		m_bUse = AfxGetApp()->GetProfileInt(strSection, "m_bUse", 1);
		m_bUse = TRUE;		// Force to use external power
		m_iRangeU = AfxGetApp()->GetProfileInt(strSection, "m_iRangeU", 30);

		m_fRangeI = (float)atof(AfxGetApp()->GetProfileString(strSection, "m_fRangeI", "5"));
	}

	void WriteRegister()
	{
		CString strSection  = "ExPowerSettings";
		AfxGetApp()->WriteProfileInt(strSection, "m_iCOM", m_iCOM);
		AfxGetApp()->WriteProfileInt(strSection, "m_iMode", m_iMode);
		AfxGetApp()->WriteProfileInt(strSection, "m_bUse", m_bUse);
		AfxGetApp()->WriteProfileInt(strSection, "m_iRangeU", m_iRangeU);

		CString strTemp;
		strTemp.Format("%f", m_fRangeI);
		AfxGetApp()->WriteProfileString(strSection, "m_fRangeI", strTemp);
	}
};


//调节模式
enum ModeWY{
	WY_M = 0,   //精调模式
	WY_K = 1,   //慢调模式
};

//工作状态
enum sele_ui{
	sele_u = 0,      //稳压
	sele_i = 1,      //稳流
};


//初始化 iCom串行号 1:COM1 2:COM2....
//       iTypeWY    0:表示早期仪器8位,1:表示现在多机9位模式 
//       iAddr:     多机模式的地址码,要与仪器地址码对应 
extern BOOL      __stdcall WY_Init(int iCom,int iTypeWY,int iAddr);
//设定工作模式  对于早期WY仪器无效, bShowError是否提示出错对话框
extern BOOL      __stdcall WY_SetMode(ModeWY mode,BOOL bShowError);
//复位仪器   即电压电流输出为零
extern BOOL      __stdcall WY_Reset(BOOL bShowError);
//读取当前的电压电流计数
extern BOOL      __stdcall WY_GetPower(float &fVol, float &fCurr, BOOL bShowError);

//设定稳压或稳流
//seleUI  :  稳压或稳流
//fSetVol :　设定电压
//fSetCurr:  设定电流
//fVol    :  调节完成后返回的电压读数
//fCurr   :  调节完成后返回的电流读数
//设定返回值
enum result_wy{
	re_ok      = 0,     //设定成功
	re_fail    = 1,     //通讯失败
	re_cancel  = 2,     //被取消
	re_setfail = 3,     //设定错误，不能稳压或不能稳流
};
extern result_wy __stdcall WY_SetPower(sele_ui seleUI, float fSetVol, float fSetCurr, float &fVol, float &fCurr, BOOL bShowError);


// 设置OVP电压
extern BOOL __stdcall WY_SetOVP(float fSafeVol);

inline result_wy WY_SetPowerOVP(sele_ui seleUI, float fSetVol, float fSetCurr, float &fVol, float &fCurr, BOOL bShowError)
{
	if (!WY_SetOVP(fSetVol + 5))
	{
		if (ADMIN_EXECUTION_LEVEL == g_iExecutionLevel)
		{
			CString strTemp;
			strTemp.Format("设置OVP电压%.2fV失败！", 
				fSetVol + 5);
			AfxMessageBox(strTemp);
		}
		
		return re_fail;
	}

	Sleep(500);
	result_wy result = WY_SetPower(seleUI, fSetVol, fSetCurr, fVol, fCurr, bShowError);
	if (ADMIN_EXECUTION_LEVEL == g_iExecutionLevel && re_ok != result)
	{
		CString strTemp;
		strTemp.Format("WY设置错误代码：%d", 
			result);
		AfxMessageBox(strTemp);
	}
	if (re_ok != result)
	{
		WY_Reset(FALSE);
	}

	return result;
}

class CWYComm
{
public:
	inline BOOL Initialize(int iCom,int iTypeWY,int iAddr = 0x64)
	{
		return WY_Init(iCom, iTypeWY, iAddr);
	}

	inline BOOL Reset(BOOL bShowError)
	{
		return WY_Reset(bShowError);
	}

	inline BOOL GetPower(float &fVol, float &fCurr, BOOL bShowError)
	{
		return WY_GetPower(fVol, fCurr, bShowError);
	}

	inline result_wy SetPower(sele_ui seleUI, float fSetVol, float fSetCurr, float &fVol, float &fCurr, BOOL bShowError)
	{
		return WY_SetPower(seleUI, fSetVol, fSetCurr, fVol, fCurr, bShowError);
	}
};

#endif
