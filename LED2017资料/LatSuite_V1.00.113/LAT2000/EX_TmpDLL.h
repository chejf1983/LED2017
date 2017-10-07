////ExTmpDLL.h
//版权所有 2014 杭州远方光电信息股份有限公司(EVERFINE)

#ifndef _EXTMPDLL_H_
#define _EXTMPDLL_H_

extern BOOL __stdcall TMP_InitAddress(CArray<BYTE, BYTE> &ucAddress);
extern BOOL __stdcall TMP_InitCOM(int iCom,int iBuadRate);
extern BOOL __stdcall TMP_ReadData(BYTE bAddr,  float &fTmp,int &iAlam);//iAlam :1 上限报警 2下限报警 3正偏差报警 4负偏差报警
extern BOOL __stdcall TMP_WriteData(BYTE bAddr,  float fTMP, float fTmpDown, float fTmpUp);
extern BOOL __stdcall TMP_SetState(BYTE ucAdress, WORD dwState);//温控仪状态dwState 0：运行 1：停止 2:暂停
#endif
