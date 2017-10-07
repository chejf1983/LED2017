// ProcessData.h: interface for the CProcessData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROCESSDATA_H__1AE6C0E3_4D24_11D6_80F1_52544CBE8249__INCLUDED_)
#define AFX_PROCESSDATA_H__1AE6C0E3_4D24_11D6_80F1_52544CBE8249__INCLUDED_

#include "SDCM.h"
#include <afxtempl.h>
#include "ImageObject.h"
#include "MusterData.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CProcessData  
{
public:
	CMusterData m_sData;

	int   m_iSUV_N;
	float m_arra_fWAL[200];
	float m_arra_fSUV[200];
    //标准灯光谱数据
	float m_uvpl[2001];//200-400nm

	CImageObject m_ImageCIE_xy;
	CImageObject m_ImageCIE_uv;
	CTypedPtrArray<CObArray,SDCM*> m_sdcm;

	void ProGetTc(int interv, float *flamda, float *RelSpec, float &fx, float &fy, float &fu, float &fv, float &fRedRatio,int &iMaxslamda,float &fHaveWidth,float &fCCT, float &fRa, float *fRi,float fTox,float fToy,float fToX,float fToY,float fToZ,int iToType);
	void GetRGB(float fSpect,int &R,int &G,int &B);
	int	 iHalfWave(float f[],int iN);
	BOOL GetMaxWaveAndQuality(float x,float y,float &fMaxWave,float &fQuality);
	void Getxy(float fLamda,float &x,float &y);
	void Process51(int iN,float fWL[],float fPL[],float &fx, float &fy, float &fu, float &fv, 
					float &fRedRatio,float &fGreenRatio,float &fBlueRatio,float &fMaxslamda,float &fHaveWidth,
					float &fCCT,float &fdc, float &fRa, float *fRi,float &fMainWave, float &fQuality);
	BOOL GetStandardRen(CString sPathName);
	void XYZTOxyz(float X,float Y,float Z,float& x,float& y,float& z);
	void uvTOxy(float u,float v,float& x,float& y);//uvw--->xyz
	void xyTOuv(float x,float y,float& u,float& v);//xyz--->uvw
	float x001ex[40001],y001ex[40001];//file xy01.ex
	CProcessData();
	virtual ~CProcessData();

public:
	float	Fun(float fC[], float fD1, float fD2, float fD3);
	void	CIE_xLuv(float x,float y,float x0,float y0,float &xL,float &xu,float &xv,float &xSuv,float &xCuv,float &xHuv);
	float	CIE_DEuv(float x1,float y1,float x2,float y2,float x0,float y0);
	float	fHalfWave(CArray<float,float> &f);
	float	fMax(CArray<float,float> &f, int &iMax,BOOL bForNew=FALSE);
	BOOL	ReadSdcmData(CString strPath);

	double	NewInt_double(double *xa, double *ya, int n, double x);
	float	NewInt_float(float *xa, float *ya, int n, float x);

	double	Lagrange(double x0,double h,int n,double y[],double t);
	float	g_fMax(float f[], int iN, int &iMax);
	void	TwoPointGetLine(float x1,float y1,float x2,float y2,float &a,float &b,float &c);
	double	GetPointToLineDistance(float xPoint, float yPoint, float aLine, float bLine,float cLine);
	float	maximums(float arr[],float *pt1,int *pt2,int n);

	float	s15[81][15],ustar[75][15],vstar[75][15],wstar[75][15];
	float	x5[81],y5[81],z5[81],s5[81];
	float	x1[421],y1[421],z1[421],s1[401],t1[401];
	float	up[75],vp[75],mired[75];

	int		m_mired_iN;
	float	m_mired_fMin;
	int		m_mired_iAddN;
	double	x001[40001],y001[40001],z001[40001];
};

#endif // !defined(AFX_PROCESSDATA_H__1AE6C0E3_4D24_11D6_80F1_52544CBE8249__INCLUDED_)
