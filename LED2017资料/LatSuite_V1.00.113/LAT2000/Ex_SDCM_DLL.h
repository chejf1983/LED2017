#ifndef  _Ex_SDCM_DLL_H_
#define  _Ex_SDCM_DLL_H_
#define  API _stdcall   
//
// ��ʼ��
//
extern BOOL API  SDCM_DLL_Judge_Init(float fCIE_x, float fCIE_y, BOOL bEn);
extern BOOL API  SDCM_DLL_Judge_Init_Path(char* strPath, float fCIE_x, float fCIE_y, BOOL bEn);

//
// ����SDCM�ж��Ի���
//
extern void API  SDCM_DLL_Dlg_Domodal();


//
// ����SDCM���ж��Ƿ�����ѡͼ����
//
extern void API  SDCM_DLL_Calc(float fCIE_x, float fCIE_y);

//
// ������Բ������
// ����:bIN��1 ���ϣ�bIN��0 ���У�bCheck��1 ѡ��0 ����
//
extern int  API SDCM_DLL_GetAllEllipse_Num(BOOL bIN, BOOL bCheck);

//
// �õ���Բ��ID��piItemID ID����
// ����:bIN��1 ���ϣ�bIN��0 ���У�bCheck��1 ѡ��0 ����
extern void API  SDCM_DLL_GetAllEllipse_ID(int * piItemID, BOOL bIN, BOOL bCheck);

//
// �õ�ĳһID��Բ�Ĳ���,pstrName ��Բ������,fR1�뾶1��fR2�뾶2,fCIE_x��Բ����x,fCIE_y��Բ����y
// fCalcSDCM
// iItemID��ǰID
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
// ���ض���θ�����
// ����:bIN��1 ���ϣ�bIN��0 ���У�bCheck��1 ѡ��0 ����
//
extern int API  SDCM_DLL_GetAllPolygon_Num(BOOL bIN, BOOL bCheck);


//
// �õ�����ε�ID��piItemID ID����
// ����:bIN��1 ���ϣ�bIN��0 ���У�bCheck��1 ѡ��0 ����
//
extern void API  SDCM_DLL_GetAllPolygon_ID(int * piItemID, BOOL bIN, BOOL bCheck);

//
// �õ�ĳһID����εĲ���,pstrName ����ε�����
//
extern BOOL API  SDCM_DLL_GetOnePolygon_Para(int iItemID, 
	char * pstrName);

//
// ��ɫ�ݲ�ͼ����ʾiItemID��Բ
//
extern BOOL API  SDCM_DLL_SetEllipse_Dis(int iItemID,
	BOOL bDis);

//
// ��ɫ�ݲ�ͼ����ʾiItemID�����
//
extern BOOL API  SDCM_DLL_SetPolygon_Dis(int iItemID,
	BOOL bDis);
//
// ��ɫ�ݲ�ͼ,DrawRect����fCIE_x��fCIE_y���������
// bManuRange �Ƿ�ָ�����꣬0��ָ�����Զ�����1ָ��
// fCIE_xmin X��������С ��fCIE_xmax X���������
// fCIE_ymin X��������С ��fCIE_xmax Y���������
// bDisBBC�Ƿ���ʾ��������
extern BOOL API  SDCM_DLL_DrawSDCM_Picture(HDC &hDC, CRect DrawRect, float fCIE_x, float fCIE_y,
	BOOL bManuRange, float fCIE_xmin, float fCIE_xmax, float fCIE_ymin, float fCIE_ymax, BOOL bDisBBC,
	BOOL bPrint);

// ѡ����ʾһ����׼ͼ��
extern BOOL API SDCM_DLL_Dlg_Sel_Display_OneGra();

// ��һ��ͼ��
extern BOOL API SDCM_DLL_DrawSDCM_OneGra(HDC &hDC, CRect DrawRect, float fCIE_x, float fCIE_y, BOOL bDisBBC, BOOL bPrint);



// �õ���ǰѡ��ͼ�����ͼ�����
extern BOOL API  SDCM_DLL_GetSelSDCM_OneGraType(int &iType,  char * pstrName);

// �õ��Ƿ��ڶ������
extern BOOL API SDCM_DLL_GetSelSDCM_Polygon_WhetherIn();

// �õ���ԲSDCM
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