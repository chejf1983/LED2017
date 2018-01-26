// SpectraArsenalEmission.h : SpectraArsenalEmission DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

#include "ExGetColorParaDLL.h"
#include "LITS.h"
#include "math.h"

// CSpectraArsenalEmissionApp
// �йش���ʵ�ֵ���Ϣ������� SpectraArsenalEmission.cpp
//

class CSpectraArsenalEmissionApp : public CWinApp
{
public:
	CSpectraArsenalEmissionApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};


// CSpectraArsenalEmissionApp
// �йش���ʵ�ֵ���Ϣ������� SpectraArsenalEmission.cpp
//

#define DLLEXP extern "C" __declspec(dllexport)

#define DLL_SUCCESS			0
#define FILE_OPEN_FAILED	1  //�ļ���ʧ��
#define DEV_OPEN_FAILED		2  //�豸����ʧ��
#define DEV_INIT_FAILED		3  //�豸��ʼ��ʧ��
#define DLL_INIT_FAILED		4  //dll��ʼ��ʧ��
#define DEV_NOT_INIT		5  //�豸û�г�ʼ��
#define INVALID_PAR			6  //��Ч�Ĳ���


#define TIME_TOO_SMALL		7  //����ʱ��̫С
#define TIME_TOO_BIG		8  //����ʱ��̫��

#define DLL_FAILED			-1 //ͨѶЭ�鷵��ʧ��


typedef struct TestMode {
	int LedMark;  //   ������˫��������
	int testMode; //   BIT0�����ײ���ʹ�� BIT1�������ʹ�� BIT2�����������
}STestMode;

typedef struct ElectricPar {
	int lednum;       //RGBͨ��ʹ�ܸ���

	float NeVoltage;  //���Ե�ѹ
	float NeCurrent;  //���Ե���
	float NeDelay;    //������ʱ
	float NeTime;     //����ʱ��

	float FVoltage[3]; //LED�����ѹ
	float FCurrent[3]; //LED�������
	float FDelay[3];   //LED������ʱ
	float FTime[3];    //LED�������ʱ��

	float RVoltage[3]; //LED�����ѹ
	float RCurrent[3]; //LED�������
	float RDelay[3];   //LED������ʱ
	float RTime[3];    //LED�������ʱ��

}SElectricPar;

typedef struct EleTestPar {
	int rgb_index;
	int test_mode;   //���� 0 ������� 1�����ѹ 2 ������� 3 �����ѹ
	float fVol;
	float fCurrent;	
	float fdelay;
	float ftime;	
}SEleTestPar;

typedef struct ElectricData {
	float NeType;   //���� 0 ���� 1����
	float fVol;		//V
	float fIr;	    //mA
}SElectricData;

typedef struct SpectralPar {
	TRIGGER_MODE TriggerMode;
	float fIntTime;
	int iAveNum;
	int iFilterBW;
}SSpectralPar;

//typedef void (*Pprint)(char*);

//DLLEXP void WINAPI DLL_PRINT_SET(void(*ptr)(char*));

/*********************************
* LED_LITS_SEARCH() �����ӣ��������豸
*���أ� ���������豸������ 0 ��ʾû���豸
*********************************/
DLLEXP int WINAPI LED_LITS_SEARCH();

/*********************************
* LED_LITS_SEARCH() �Ͽ�����
*int devnum ѡ��Ҫ��ʼ�����豸��
*���أ�DLL_SUCESS         ��ʼ���ɹ�
*      FILE_OPEN_FAILED   ����ļ���ʧ��
*      DEV_OPEN_FAILED    �豸����ʧ��
*      DEV_INIT_FAILED    �豸��ʼ��ʧ��
*      DLL_INIT_FAILED    ���dll��ʼ��ʧ��
*********************************/
DLLEXP int WINAPI LED_LITS_CONNECT(int devnum);

/*********************************
*LED_LITS_GetDevInfo(char* devserial, int* PixNum) ��ȡ�豸��Ϣ
*SDevInfo* devinfo �豸��Ϣ
*���أ�DLL_SUCESS         ִ�л��ɹ�
*********************************/
DLLEXP int WINAPI LED_LITS_GetDevInfo(char* devserial, int* PixNum);

/*********************************
* LED_LITS_SEARCH() �Ͽ�����
*���أ�
*********************************/
DLLEXP void WINAPI LED_LITS_CLOSE();


//��ȡ����������
DLLEXP int WINAPI LED_LITS_GetDarkData(SSpectralPar spar, double* fAdValue, int ADlen);
//��ȡԭʼ����
DLLEXP int WINAPI LED_LITS_GetOriginalData(SSpectralPar spar, float dkdata[], int dklen, double* fAdValue, int ADlen, double* IP);

//��ȡ������ɫ����
DLLEXP int WINAPI LED_LITS_GetData(SSpectralPar spar, float dkdata[], int dklen,
	float fDx, float fDy, COLOR_PARA &dPara);

//����LED����
DLLEXP int WINAPI LED_LITS_SetLEDType(int ledtype);

//���õ������������
DLLEXP int WINAPI LED_LITS_SetElectricPar(SElectricPar epar, int ledmode);

//��ȡ�������������
DLLEXP int WINAPI LED_LITS_GetElectricPar(SElectricPar& epar, int& ledmode);

//��ȡ����ʱ��
DLLEXP int WINAPI LED_LITS_GetSPPar(float * time1, float * time2, float * time3);

//���ù����
DLLEXP int WINAPI LED_LITS_SetSPPar(float time1, float time2, float time3, int avr);

//��ȡ�������3��ԭʼ����
DLLEXP int WINAPI LED_LITS_GetLEDOriginalData(
	TRIGGER_MODE mode,
	int filternum,
	float dkdata1[],
	float dkdata2[],
	float dkdata3[], int dklen,
	double* fAdValue1, 
	double* fAdValue2,
	double* fAdValue3,int ADlen,
	SElectricData & ePara1,
	SElectricData & ePara2,
	SElectricData & ePara3, int ledmode, int timeout);

//��ȡ�������3����ɫ����
DLLEXP int WINAPI LED_LITS_GetLEDData(
	SSpectralPar spar1,
	SSpectralPar spar2,
	SSpectralPar spar3,
	float dkdata1[],
	float dkdata2[],
	float dkdata3[], int dklen,
	float fDx[], float fDy[],
	COLOR_PARA& dPara1,
	COLOR_PARA& dPara2,
	COLOR_PARA& dPara3,
	ElectricData& ePara1,
	ElectricData& ePara2,
	ElectricData& ePara3, int ledmode, int timeout);

//����bin��
DLLEXP int WINAPI LED_LITS_SetBin(int bin);

//У׼������
DLLEXP int WINAPI LED_LITS_Calib(SSpectralPar spar, float dkdata[], int dklen,
	int iCalType,
	float fCCT,
	float fFlux,
	int iStaNum,
	float fStaWL[],
	float fStaPL[],
	float &fIp);

//����У׼
DLLEXP int WINAPI LED_LITS_ReCal(COLOR_PARA &dPara, float fDx, float fDy);

//����������������
DLLEXP int WINAPI LED_LITS_TestElcBord(EleTestPar spar, ElectricData& ret);

//�������ģʽ
DLLEXP int WINAPI LED_LITS_ResetModel();

DLLEXP int WINAPI LED_LITS_ResetModel_I(int index);

