
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the HWELEOPTIC_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// HWELEOPTIC_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.

//#ifdef HWELEOPTIC_EXPORTS
//#define HWELEOPTIC_API __declspec(dllexport)
//#else
//#define HWELEOPTIC_API __declspec(dllimport)
//#endif

#include <windows.h>

#ifdef __cplusplus
#define export extern "C" __declspec(dllexport)
#else
#define export __declspec(dllexport)
#endif

export int WINAPI Inport(int Addr);

export bool WINAPI Outport(int Addr,int Data);

export bool WINAPI Delay(long m_Delay);

export double WINAPI check01();
export double WINAPI check05();
export double WINAPI check1();
export double WINAPI check10();
export double WINAPI checkC01mA();
export double WINAPI checkC200mA();
export double WINAPI checkV01mA();
export double WINAPI checkV200mA();
export double WINAPI checkIC01mA();
export double WINAPI checkIC200mA();


export double WINAPI   GetAD(long m_Delaytime);
export bool WINAPI GiveVoltage(double m_Voltage);
export bool WINAPI GiveCurrent(double m_Current);

export bool WINAPI Set_timeInit(void);
export bool WINAPI Set_timeTrigger(long v_timer);
export bool WINAPI Set_timeReset(void);

export bool WINAPI SelectChip(int m_Chip);
export bool WINAPI setBering(bool m_Bering);
export bool WINAPI getBering();

export double WINAPI setway(double m_Voltage,double m_Current,long delay_Time);
export double WINAPI getVF(double m_Voltage,double m_Current,long delay_Time);
export double WINAPI getVR(double m_Voltage,double m_Current,long delay_Time);
export double WINAPI getIF(double m_Voltage,double m_Current,long delay_Time);
export double WINAPI getIR(double m_Voltage,double m_Current,long delay_Time);
export double WINAPI getDVF(double m_SourceC,long delay_Time);
export double WINAPI getTHY(double m_Voltage,double m_Current);
export void WINAPI CloseOut();

//EXPORT double WINAPI hw_Std0_Optic_Cal(double m_Voltage,double m_Current,BYTE OpticGain);
//EXPORT double WINAPI hw_Std1_Optic_Cal(double m_Voltage,double m_Current,BYTE OpticGain);
//EXPORT double WINAPI hw_Std2_Optic_Cal(double m_Voltage,double m_Current,BYTE OpticGain);
//EXPORT double WINAPI hw_Std3_Optic_Cal(double m_Voltage,double m_Current,BYTE OpticGain);
//EXPORT double WINAPI hw_Std4_Optic_Cal(double m_Voltage,double m_Current,BYTE OpticGain);

export double WINAPI getYbit(long OpticGain,long ElecGain,double m_Voltage,double m_Current,long delay_Time);
export bool WINAPI OpenLight(double m_Voltage,double m_Current);
export bool WINAPI CloseLight();
//EXPORT bool WINAPI hw_Cal_After_Init();
export double WINAPI GetAD_New(long m_Delaytime);

export double WINAPI GetDualYbit(long OpticGain,long ElecGain,double m_Voltage,double m_Current,long delay_Time,long difference);