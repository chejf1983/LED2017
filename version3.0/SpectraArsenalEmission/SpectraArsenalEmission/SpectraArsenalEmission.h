// SpectraArsenalEmission.h : SpectraArsenalEmission DLL 的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号

#include "ExGetColorParaDLL.h"
#include "LITS.h"
#include "math.h"

// CSpectraArsenalEmissionApp
// 有关此类实现的信息，请参阅 SpectraArsenalEmission.cpp
//

class CSpectraArsenalEmissionApp : public CWinApp
{
public:
	CSpectraArsenalEmissionApp();

// 重写
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};


// CSpectraArsenalEmissionApp
// 有关此类实现的信息，请参阅 SpectraArsenalEmission.cpp
//

#define DLLEXP extern "C" __declspec(dllexport)

#define DLL_SUCCESS			0
#define FILE_OPEN_FAILED	1  //文件打开失败
#define DEV_OPEN_FAILED		2  //设备连接失败
#define DEV_INIT_FAILED		3  //设备初始化失败
#define DLL_INIT_FAILED		4  //dll初始化失败
#define DEV_NOT_INIT		5  //设备没有初始化
#define INVALID_PAR			6  //无效的参数


#define TIME_TOO_SMALL		7  //积分时间太小
#define TIME_TOO_BIG		8  //积分时间太大

#define DLL_FAILED			-1 //通讯协议返回失败


typedef struct TestMode {
	int LedMark;  //   单晶，双晶，三晶
	int testMode; //   BIT0：光谱测试使能 BIT1：电测试使能 BIT2：电参数测试
}STestMode;

typedef struct ElectricPar {
	int lednum;       //RGB通道使能个数

	float NeVoltage;  //极性电压
	float NeCurrent;  //极性电流
	float NeDelay;    //测量延时
	float NeTime;     //测量时间

	float FVoltage[3]; //LED正向电压
	float FCurrent[3]; //LED正向电流
	float FDelay[3];   //LED正向延时
	float FTime[3];    //LED正向测试时间

	float RVoltage[3]; //LED反向电压
	float RCurrent[3]; //LED反向电流
	float RDelay[3];   //LED反向延时
	float RTime[3];    //LED反向测试时间

}SElectricPar;

typedef struct EleTestPar {
	int rgb_index;
	int test_mode;   //极性 0 正向电流 1正向电压 2 反向电流 3 反向电压
	float fVol;
	float fCurrent;	
	float fdelay;
	float ftime;	
}SEleTestPar;

typedef struct ElectricData {
	float NeType;   //极性 0 正向 1反向
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
* LED_LITS_SEARCH() 打开连接，并搜索设备
*返回： 搜索到的设备个数， 0 表示没有设备
*********************************/
DLLEXP int WINAPI LED_LITS_SEARCH();

/*********************************
* LED_LITS_SEARCH() 断开连接
*int devnum 选择要初始化的设备号
*返回：DLL_SUCESS         初始化成功
*      FILE_OPEN_FAILED   相关文件打开失败
*      DEV_OPEN_FAILED    设备连接失败
*      DEV_INIT_FAILED    设备初始化失败
*      DLL_INIT_FAILED    相关dll初始化失败
*********************************/
DLLEXP int WINAPI LED_LITS_CONNECT(int devnum);

/*********************************
*LED_LITS_GetDevInfo(char* devserial, int* PixNum) 获取设备信息
*SDevInfo* devinfo 设备信息
*返回：DLL_SUCESS         执行化成功
*********************************/
DLLEXP int WINAPI LED_LITS_GetDevInfo(char* devserial, int* PixNum);

/*********************************
* LED_LITS_SEARCH() 断开连接
*返回：
*********************************/
DLLEXP void WINAPI LED_LITS_CLOSE();


//获取暗电流数据
DLLEXP int WINAPI LED_LITS_GetDarkData(SSpectralPar spar, double* fAdValue, int ADlen);
//获取原始数据
DLLEXP int WINAPI LED_LITS_GetOriginalData(SSpectralPar spar, float dkdata[], int dklen, double* fAdValue, int ADlen, double* IP);

//获取单次颜色数据
DLLEXP int WINAPI LED_LITS_GetData(SSpectralPar spar, float dkdata[], int dklen,
	float fDx, float fDy, COLOR_PARA &dPara);

//设置LED类型
DLLEXP int WINAPI LED_LITS_SetLEDType(int ledtype);

//设置电参数测试条件
DLLEXP int WINAPI LED_LITS_SetElectricPar(SElectricPar epar, int ledmode);

//读取电参数测试条件
DLLEXP int WINAPI LED_LITS_GetElectricPar(SElectricPar& epar, int& ledmode);

//获取积分时间
DLLEXP int WINAPI LED_LITS_GetSPPar(float * time1, float * time2, float * time3);

//设置光参数
DLLEXP int WINAPI LED_LITS_SetSPPar(float time1, float time2, float time3, int avr);

//获取电参数和3晶原始数据
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

//获取电参数和3晶颜色数据
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

//设置bin号
DLLEXP int WINAPI LED_LITS_SetBin(int bin);

//校准光谱仪
DLLEXP int WINAPI LED_LITS_Calib(SSpectralPar spar, float dkdata[], int dklen,
	int iCalType,
	float fCCT,
	float fFlux,
	int iStaNum,
	float fStaWL[],
	float fStaPL[],
	float &fIp);

//重新校准
DLLEXP int WINAPI LED_LITS_ReCal(COLOR_PARA &dPara, float fDx, float fDy);

//电参数板子输出测试
DLLEXP int WINAPI LED_LITS_TestElcBord(EleTestPar spar, ElectricData& ret);

//重置软件模式
DLLEXP int WINAPI LED_LITS_ResetModel();

DLLEXP int WINAPI LED_LITS_ResetModel_I(int index);

