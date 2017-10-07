// SPEC_HAAS.h: interface for the CSPEC_HAAS class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPEC_HAAS_H__748562F4_CC49_4381_87EC_AB5EDF851C6A__INCLUDED_)
#define AFX_SPEC_HAAS_H__748562F4_CC49_4381_87EC_AB5EDF851C6A__INCLUDED_

#include "Serial.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSPEC_HAAS  
{
public:
	BOOL LoadWaveToGCS(double dc[]);
	float Tof(BYTE *bb);
	BOOL SaveEppData();
	BOOL ReadEppData();
	//�������к��޸Ķ�ȡ
	BOOL ReadSN(CString &strSN);
	BOOL SetSN(CString strSN,int iBaudRate);

	BOOL   PRO_ModAD(int iN,float fAD[]);
	double PRO_NewInt(double *xa,double *ya,int n,double x);
	float  PRO_ADtoTMP(int iType, int iAD);
	
	BOOL m_bShutter;
	int  m_iPixN;
	int  m_iPixS[10];
	int  m_iPixE[10];
	int  m_iWLInter;   //�����ֽ��ĸ���
	float m_fWLInter[10];//�����ֽ��


	BOOL UnInit();
	BOOL Init(int &iPixN,int &AD);
	//����ɫ��������
	BOOL Scan(float fIntTime, int iAveN, float fAD[],BOOL &bOverAD, BOOL bNote);
	//ֻ����
	BOOL HAAS_Scan(float fIntTime, float fAD[], BOOL &bOverAD);

	CSPEC_HAAS();
	virtual ~CSPEC_HAAS();

private:
	//����У������
//	double m_Icor,m_C1cor,m_C2cor,m_C3cor;//
};

#endif // !defined(AFX_SPEC_HAAS_H__748562F4_CC49_4381_87EC_AB5EDF851C6A__INCLUDED_)
