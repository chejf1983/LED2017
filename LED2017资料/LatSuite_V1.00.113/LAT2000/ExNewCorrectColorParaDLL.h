#ifndef _NEWCORRECT_COLOR_PARA_DLL_H_
#define  _NEWCORRECT_COLOR_PARA_DLL_H_

extern BOOL __stdcall NewCorrectColorParaDLL_Init(char szPathPathName[], BOOL bEnglish);

extern BOOL __stdcall NewCorrectColorParaDLL_Edit();

extern BOOL __stdcall NewCorrectColorParaDLL_Select();

extern BOOL __stdcall NewCorrectColorParaDLL_GetCorrectdXdY(float &dx, float &dy);

extern BOOL __stdcall NewCorrectColorParaDLL_GetCorrectdLp(float &dLp);

extern BOOL __stdcall NewCorrectColorParaDLL_GetCorrectPhK(float &fPhK);

extern BOOL __stdcall NewCorrectColorParaDLL_GetCorrectPheK(float &fPheK);

extern BOOL __stdcall NewCorrectColorParaDLL_GetCorrectRa(float &dRa);

extern BOOL __stdcall NewCorrectColorParaDLL_SetUseCorrect(BOOL bSetUse);

#endif
