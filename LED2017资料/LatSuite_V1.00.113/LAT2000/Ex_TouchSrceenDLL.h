//Ex_TouchSrceenDll.h
//远方(EVERFINE)台达触摸屏扫码显示部分机通讯DLL开发库
//版本:   V1.00
//时间:   2014.2 yhb

#ifndef _EX_TOUCHSRCEENDLL_H_
#define _EX_TOUCHSRCEENDLL_H_

extern BOOL __stdcall TS_Initialize(int iCom, int iBaudRate);
extern BOOL __stdcall TS_SendShowData(int iAddrStart,int iNum, char strData[]);

class CExTouchSrceenComm
{
public:
	inline BOOL Initialize(int iCom, int iBaudRate)
	{
		return TS_Initialize(iCom, iBaudRate);
	}

	inline BOOL SendShowData(int iAddrStart, CString sSendData)
	{
		int iNum = sSendData.GetLength();
		char strData[100];
		int i;
		for (i = 0; i < iNum; i++)
		{
			strData[i] = sSendData.GetAt(i);
		}
		strData[i] = 0x00;

		BOOL bR;
		bR = TS_SendShowData(iAddrStart,iNum,strData);
		if (!bR)
		{
			Sleep(100);
			bR = TS_SendShowData(iAddrStart,iNum,strData);
			if (!bR)
			{
				Sleep(100);
				bR = TS_SendShowData(iAddrStart,iNum,strData);
				if (!bR)
				{
					return FALSE;
				}
			}
		}
		return TRUE;
	}
};

#endif
