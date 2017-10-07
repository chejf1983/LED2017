#ifndef  _Ex_SDCM_DLL_H_
#define  _Ex_SDCM_DLL_H_
#define  API _stdcall   
//
// 初始化
//
extern BOOL API  SDCM_DLL_Judge_Init(float fCIE_x, float fCIE_y, BOOL bEn);
extern BOOL API  SDCM_DLL_Judge_Init_Path(char* strPath, float fCIE_x, float fCIE_y, BOOL bEn);

//
// 跳出SDCM判定对话框
//
extern void API  SDCM_DLL_Dlg_Domodal();


//
// 计算SDCM及判定是否在所选图形内
//
extern void API  SDCM_DLL_Calc(float fCIE_x, float fCIE_y);

//
// 返回椭圆个数；
// 条件:bIN：1 符合，bIN：0 所有；bCheck：1 选择，0 所有
//
extern int  API SDCM_DLL_GetAllEllipse_Num(BOOL bIN, BOOL bCheck);

//
// 得到椭圆的ID，piItemID ID数组
// 条件:bIN：1 符合，bIN：0 所有；bCheck：1 选择，0 所有
extern void API  SDCM_DLL_GetAllEllipse_ID(int * piItemID, BOOL bIN, BOOL bCheck);

//
// 得到某一ID椭圆的参数,pstrName 椭圆的名称,fR1半径1，fR2半径2,fCIE_x椭圆中心x,fCIE_y椭圆中心y
// fCalcSDCM
// iItemID当前ID
//
extern BOOL API  SDCM_DLL_GetOneEllipse_Para(int iItemID, 
	char * pstrName,
	float &fR1,
	float &fR2,
	float &fCIE_x,
	float &fCIE_y,
	float &fCalcSDCM
	);



//
// 返回多边形个数；
// 条件:bIN：1 符合，bIN：0 所有；bCheck：1 选择，0 所有
//
extern int API  SDCM_DLL_GetAllPolygon_Num(BOOL bIN, BOOL bCheck);


//
// 得到多边形的ID，piItemID ID数组
// 条件:bIN：1 符合，bIN：0 所有；bCheck：1 选择，0 所有
//
extern void API  SDCM_DLL_GetAllPolygon_ID(int * piItemID, BOOL bIN, BOOL bCheck);

//
// 得到某一ID多边形的参数,pstrName 多边形的名称
//
extern BOOL API  SDCM_DLL_GetOnePolygon_Para(int iItemID, 
	char * pstrName);

//
// 在色容差图中显示iItemID椭圆
//
extern BOOL API  SDCM_DLL_SetEllipse_Dis(int iItemID,
	BOOL bDis);

//
// 在色容差图中显示iItemID多边形
//
extern BOOL API  SDCM_DLL_SetPolygon_Dis(int iItemID,
	BOOL bDis);
//
// 画色容差图,DrawRect区域，fCIE_x，fCIE_y计算坐标点
// bManuRange 是否指定坐标，0不指定（自动），1指定
// fCIE_xmin X轴坐标最小 ，fCIE_xmax X轴坐标最大
// fCIE_ymin X轴坐标最小 ，fCIE_xmax Y轴坐标最大
// bDisBBC是否显示黑体曲线
extern BOOL API  SDCM_DLL_DrawSDCM_Picture(HDC &hDC, CRect DrawRect, float fCIE_x, float fCIE_y,
	BOOL bManuRange, float fCIE_xmin, float fCIE_xmax, float fCIE_ymin, float fCIE_ymax, BOOL bDisBBC,
	BOOL bPrint);

// 选择显示一个标准图形
extern BOOL API SDCM_DLL_Dlg_Sel_Display_OneGra();

// 画一个图形
extern BOOL API SDCM_DLL_DrawSDCM_OneGra(HDC &hDC, CRect DrawRect, float fCIE_x, float fCIE_y, BOOL bDisBBC, BOOL bPrint);



// 得到当前选择图形类型及名称
extern BOOL API  SDCM_DLL_GetSelSDCM_OneGraType(int &iType,  char * pstrName);

// 得到是否在多边形内
extern BOOL API SDCM_DLL_GetSelSDCM_Polygon_WhetherIn();

// 得到椭圆SDCM
extern float API SDCM_DLL_GetSelSDCM_Ellipse_SDCMValue();

/*
inline BOOL SDCM_GetEllipseSDCM(float fx, float fy, CString &strSDCMsta, float &fSDCM)
{
	CString strSDCM, strTemp;
	SDCM_DLL_Calc(fx, fy);
	int iNum = SDCM_DLL_GetAllEllipse_Num(FALSE, TRUE);
	if (iNum <= 0)
	{
		return FALSE;
	}
	int * piID = new int[iNum];
	SDCM_DLL_GetAllEllipse_ID(piID, FALSE, TRUE);	
	char strName[256];
	float fR1, fR2, fCIEx, fCIEy;
	BOOL bR = SDCM_DLL_GetOneEllipse_Para(piID[0], strName, fR1, fR2, fCIEx, fCIEy, fSDCM);
	delete[] piID;
	if (!bR)
	{
		return FALSE;		
	}
	strSDCMsta = strName;
	return TRUE;
}
*/
inline BOOL SDCM_GetPloyonSDCM(float fx, float fy, CString &strSDCMsta, BOOL &bIn)
{
	bIn = FALSE;
	CString strSDCM, strTemp;
	SDCM_DLL_Calc(fx, fy);
	int iNum = SDCM_DLL_GetAllPolygon_Num(FALSE, TRUE);
	if (iNum <= 0)
	{
		return FALSE;
	}
	int * piID = new int[iNum];
	int iCurPolyID;
	SDCM_DLL_GetAllPolygon_ID(piID, FALSE, TRUE);	
	char strName[256];
	BOOL bR = SDCM_DLL_GetOnePolygon_Para(piID[0], strName);
	iCurPolyID = piID[0];
	delete[] piID;
	if (!bR)
	{
		return FALSE;		
	}
	strSDCMsta = strName;
	iNum = SDCM_DLL_GetAllPolygon_Num(TRUE, TRUE);
	if (iNum <= 0)
	{
		return FALSE;
	}
	int * piInID = new int[iNum];
	SDCM_DLL_GetAllPolygon_ID(piInID, TRUE, TRUE);	
	if (piInID[0] != iCurPolyID)
	{
		delete[] piInID;
		return TRUE;
	}
	bIn = TRUE;
	delete[] piInID;
	return TRUE;
}
inline CString SDCM_GetEllipseSDCMString(float fx, float fy)
{
	CString strSDCM, strTemp;
	SDCM_DLL_Calc(fx, fy);
	int iNum = SDCM_DLL_GetAllEllipse_Num(TRUE, TRUE);
	if (iNum <= 0)
	{
		return "";
	}

	int * piID = new int[iNum];
	SDCM_DLL_GetAllEllipse_ID(piID, TRUE, TRUE);
	for (int i = 0; i < iNum; i++)
	{
		char strName[256];
		float fR1, fR2, fCIEx, fCIEy, fSDCM;
		BOOL bR = SDCM_DLL_GetOneEllipse_Para(piID[i], strName, fR1, fR2, fCIEx, fCIEy, fSDCM);
		if (bR)
		{
			strTemp.Format("%s(%.4g);", strName, fSDCM);
			strSDCM += strTemp;
		}
	}

	return strSDCM;
}

#endif