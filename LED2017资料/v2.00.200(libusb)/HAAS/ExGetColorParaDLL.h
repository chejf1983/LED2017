//ExGetColorParaDLL.h

#ifndef __EXGETCOLORPARADLL_H__
#define __EXGETCOLORPARADLL_H__

struct COLOR_PARA
{
	float fx;        //色坐标
	float fy;
	float fu;
	float fv;

	float fCCT;      //相关色温(K)
	float dC;        //色差dC
	float fLd;       //主波长(nm)
	float fPur;      //色纯度(%)
	float fLp;       //峰值波长(nm)
	float fHW;       //半波宽(nm)
	float fLav;      //平均波长(nm)
	float fRa;       //显色性指数 Ra
	float fRi[15];   //显色性指数 R1-R15

	float fRR;       //红色比
	float fGR;       //绿色比
	float fBR;       //蓝色比
};

extern void __stdcall NH_GetSoftVer(CString &strVer);
extern BOOL __stdcall NH_Init(CString strPW1, CString strPW2, CString strPath);
extern void __stdcall NH_GetColorPara(float fWL[], float fPL[],int iN, COLOR_PARA &para);
extern float __stdcall NH_GetV(float fWL);
extern float __stdcall NH_GetCDI();



#endif
