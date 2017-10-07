//ExCalcColorDLL.h
#include "ExCalc_Color.h"

extern void __stdcall CC_GetVer(CString &strVer);
extern BOOL __stdcall CC_Init(CString strPW1, CString strPW2, CString strPath);
extern void __stdcall CC_CalcColor(float fWL[], float fPL[],
										  int iN, COLOR_PARA &para,BOOL bXY2CCT,float xx,float yy);
extern float __stdcall CC_GetV(float fWL);




