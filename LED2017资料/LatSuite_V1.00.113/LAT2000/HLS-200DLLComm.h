/*
*	HLS200DLLComm.h
*	EVERFINE 2013-9-16
*	V1.00
*/


#ifndef __HLS200DLL__
#define __HLS200DLL__

/*
*函数名称HLS200_Init
*函数功能: 设置仪器通讯口,工作模式，语言
*参数:
*nCom:		与仪器通讯的串行口(1:COM1,2:COM2,3:COM3),默认1
*nBaud:		与仪器通讯的波特率 默认4800
*bDemo:		TRUE，演示模式，FALSE，正常模式
*bEnglish:	TRUE,英语提示，FALSE，中文提示
返回值: 无
*/
extern void __stdcall HLS200_Init(int nCom,int nBaud,BOOL bDemo,BOOL bEnglish);

extern BOOL __stdcall HLS200_Start();

extern BOOL __stdcall HLS200_Reset();

extern BOOL __stdcall HLS200_ReadState(int &OutState,int &OpenState,int &ShortState);

extern BOOL __stdcall HLS200_SetI(USHORT fI);

class CHLS_200
{
public:
    BOOL SetCom(int iCom)
    {
        HLS200_Init(iCom,4800,FALSE,FALSE);
		return TRUE;
    }

    BOOL OpenOutput()
    {
        return HLS200_Start();
    }

    BOOL CloseOutput()
    {
        return HLS200_Reset();
    }

	BOOL SetCurr(float fCurr)
	{
		USHORT uCurr;
		uCurr = (USHORT)(fCurr);
		return HLS200_SetI(uCurr);
	}

    BOOL GetState(BOOL &Output,BOOL &Load,BOOL &Warning)
    {
        return HLS200_ReadState(Output,Load,Warning);
    }

};

#endif

