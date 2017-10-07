//ExGetColorParaDLL.h

#ifndef __EXGETCOLORPARADLL_H__
#define __EXGETCOLORPARADLL_H__

struct COLOR_PARA
{
	float fx;        //ɫ����
	float fy;
	float fu;
	float fv;

	float fCCT;      //���ɫ��(K)
	float dC;        //ɫ��dC
	float fLd;       //������(nm)
	float fPur;      //ɫ����(%)
	float fLp;       //��ֵ����(nm)
	float fHW;       //�벨��(nm)
	float fLav;      //ƽ������(nm)
	float fRa;       //��ɫ��ָ�� Ra
	float fRi[15];   //��ɫ��ָ�� R1-R15

	float fRR;       //��ɫ��
	float fGR;       //��ɫ��
	float fBR;       //��ɫ��
};

extern void __stdcall NH_GetSoftVer(CString &strVer);
extern BOOL __stdcall NH_Init(CString strPW1, CString strPW2, CString strPath);
extern void __stdcall NH_GetColorPara(float fWL[], float fPL[],int iN, COLOR_PARA &para);
extern float __stdcall NH_GetV(float fWL);
extern float __stdcall NH_GetCDI();



#endif
