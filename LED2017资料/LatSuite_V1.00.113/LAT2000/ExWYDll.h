//ExWYDll.h
//Զ��(EVERFINE)WYϵ�е�Դ DLL������
//�汾:   V1.02
//ʱ��:   2012.9

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


//����ģʽ
enum ModeWY{
	WY_M = 0,   //����ģʽ
	WY_K = 1,   //����ģʽ
};

//����״̬
enum sele_ui{
	sele_u = 0,      //��ѹ
	sele_i = 1,      //����
};


//��ʼ�� iCom���к� 1:COM1 2:COM2....
//       iTypeWY    0:��ʾ��������8λ,1:��ʾ���ڶ��9λģʽ 
//       iAddr:     ���ģʽ�ĵ�ַ��,Ҫ��������ַ���Ӧ 
extern BOOL      __stdcall WY_Init(int iCom,int iTypeWY,int iAddr);
//�趨����ģʽ  ��������WY������Ч, bShowError�Ƿ���ʾ����Ի���
extern BOOL      __stdcall WY_SetMode(ModeWY mode,BOOL bShowError);
//��λ����   ����ѹ�������Ϊ��
extern BOOL      __stdcall WY_Reset(BOOL bShowError);
//��ȡ��ǰ�ĵ�ѹ��������
extern BOOL      __stdcall WY_GetPower(float &fVol, float &fCurr, BOOL bShowError);

//�趨��ѹ������
//seleUI  :  ��ѹ������
//fSetVol :���趨��ѹ
//fSetCurr:  �趨����
//fVol    :  ������ɺ󷵻صĵ�ѹ����
//fCurr   :  ������ɺ󷵻صĵ�������
//�趨����ֵ
enum result_wy{
	re_ok      = 0,     //�趨�ɹ�
	re_fail    = 1,     //ͨѶʧ��
	re_cancel  = 2,     //��ȡ��
	re_setfail = 3,     //�趨���󣬲�����ѹ��������
};
extern result_wy __stdcall WY_SetPower(sele_ui seleUI, float fSetVol, float fSetCurr, float &fVol, float &fCurr, BOOL bShowError);


// ����OVP��ѹ
extern BOOL __stdcall WY_SetOVP(float fSafeVol);

inline result_wy WY_SetPowerOVP(sele_ui seleUI, float fSetVol, float fSetCurr, float &fVol, float &fCurr, BOOL bShowError)
{
	if (!WY_SetOVP(fSetVol + 5))
	{
		if (ADMIN_EXECUTION_LEVEL == g_iExecutionLevel)
		{
			CString strTemp;
			strTemp.Format("����OVP��ѹ%.2fVʧ�ܣ�", 
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
		strTemp.Format("WY���ô�����룺%d", 
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
