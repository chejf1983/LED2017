////ExTmpDLL.h
//��Ȩ���� 2014 ����Զ�������Ϣ�ɷ����޹�˾(EVERFINE)

#ifndef _EXTMPDLL_H_
#define _EXTMPDLL_H_

extern BOOL __stdcall TMP_InitAddress(CArray<BYTE, BYTE> &ucAddress);
extern BOOL __stdcall TMP_InitCOM(int iCom,int iBuadRate);
extern BOOL __stdcall TMP_ReadData(BYTE bAddr,  float &fTmp,int &iAlam);//iAlam :1 ���ޱ��� 2���ޱ��� 3��ƫ��� 4��ƫ���
extern BOOL __stdcall TMP_WriteData(BYTE bAddr,  float fTMP, float fTmpDown, float fTmpUp);
extern BOOL __stdcall TMP_SetState(BYTE ucAdress, WORD dwState);//�¿���״̬dwState 0������ 1��ֹͣ 2:��ͣ
#endif
