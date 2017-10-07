////ExEmc11kMeterDLL.h
//版权所有 2013 杭州远方光电信息股份有限公司(EVERFINE)

#ifndef _EXEMC11KMETERDLL_H_
#define _EXMC11KMETERDLL_H_

typedef struct tag_RE_11K_Data
{
	char	strRe[256];
	int		m_iResult;
	int		m_iTime;
}EMC11KREData;

//初始化 读取文件路径
extern BOOL __stdcall EMC_InitEMC11K(char strPathName[], int iCOM);
//显示设置对话框
extern void __stdcall EMC_ShowEmc11KSetDlg(int &iSeleCur, BOOL bReadOnly);
//起动命令
extern BOOL __stdcall EMC_EMC11KStart(int iSeleCur);
//读取状态 是否结束等
//-1 测试中
//0 测试完成
//1失败
//2复位
//3复位
extern int  __stdcall EMC_EMC11KRead(EMC11KREData &ReData);
//复位仪器
extern BOOL __stdcall EMC_EMC11KReset();
//EUT控制
extern BOOL __stdcall EMC_EMC11KEutOnOrOff(BOOL bOn);


class CEMS61000_11KComm
{
public:
	CEMS61000_11KComm()
	{
		InitializeCriticalSection(&m_critical);
	}
	inline BOOL Initialize(CString strPathName, CString strCOM)
	{
	
		int iCOM;
		strCOM.MakeUpper();
		strCOM.Trim();
		sscanf_s(strCOM, "COM%d", &iCOM);
		EnterCriticalSection(&m_critical);
		BOOL bR = EMC_InitEMC11K(strPathName.GetBuffer(), iCOM);
		LeaveCriticalSection(&m_critical);
		return bR;
	}

	inline void ShowSettingsDialog(int & iCurSele, BOOL bReadOnly)
	{
		EMC_ShowEmc11KSetDlg(iCurSele, bReadOnly);
	}

	inline BOOL Start(int iCurSele)
	{
		EnterCriticalSection(&m_critical);
		Sleep(100);
		EMC_EMC11KEutOnOrOff(TRUE);
		Sleep(1000);
		BOOL bR =  EMC_EMC11KStart(iCurSele);
		LeaveCriticalSection(&m_critical);
		return bR;
	}

	inline BOOL Reset()
	{
		EnterCriticalSection(&m_critical);
		BOOL bR =  EMC_EMC11KReset();
		LeaveCriticalSection(&m_critical);
		return bR;
	}

	inline int Read(EMC11KREData & data)
	{
		EnterCriticalSection(&m_critical);
		BOOL bR =  EMC_EMC11KRead(data);
		LeaveCriticalSection(&m_critical);
		return bR;
	
	}

	inline BOOL SetEUT(BOOL bON)
	{
		EnterCriticalSection(&m_critical);
		EMC_EMC11KReset();
		Sleep(1000);
		BOOL bR = EMC_EMC11KEutOnOrOff(bON);
		LeaveCriticalSection(&m_critical);
		return bR;
	}

private:
	CRITICAL_SECTION m_critical;
};

#endif
