/*
*	HLS200DLLComm.h
*	EVERFINE 2013-9-16
*	V1.00
*/


#ifndef __HLS200DLL__
#define __HLS200DLL__

/*
*��������HLS200_Init
*��������: ��������ͨѶ��,����ģʽ������
*����:
*nCom:		������ͨѶ�Ĵ��п�(1:COM1,2:COM2,3:COM3),Ĭ��1
*nBaud:		������ͨѶ�Ĳ����� Ĭ��4800
*bDemo:		TRUE����ʾģʽ��FALSE������ģʽ
*bEnglish:	TRUE,Ӣ����ʾ��FALSE��������ʾ
����ֵ: ��
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

