// MyMFC_Lib.h
// 

namespace MyMFC_Lib
{
	BOOL Gauss_EQU(float fk[],float fz[],int iN,float a[]);	
	BOOL Gauss2XF_Calc(float fx[],float fy[],int iN,int iMN,float a[]);

	BOOL Export_List(CListCtrl &list, CString strPathName);

	CString StrAddSpace(CString strTemp, int iMaxN, BOOL bAddLast);
}