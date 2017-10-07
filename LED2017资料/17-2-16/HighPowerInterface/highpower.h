#include <windows.h>

#ifdef __cplusplus
#define EXPORTS extern "C" __declspec(dllexport)
#else
#define EXPORTS __declspec(dllexport)
#endif

EXPORTS int WINAPI Inport(int Addr);
EXPORTS bool WINAPI Outport(int Addr,int Data);
EXPORTS bool WINAPI Delay(long m_Delay);

EXPORTS bool WINAPI GiveVoltage(double m_Voltage);
EXPORTS bool WINAPI GiveCurrent(double m_Current);
EXPORTS double WINAPI GetAD_New(long m_Delaytime);

EXPORTS double WINAPI checkC100uA(void);
EXPORTS double WINAPI checkC20mA(void);
EXPORTS double WINAPI checkC200mA(void);
EXPORTS double WINAPI checkC2000mA(void);
EXPORTS double getvalue(int n);

EXPORTS double WINAPI checkDAC(void);
EXPORTS double getDAC(int n);
EXPORTS double WINAPI checkVR(void);
EXPORTS double getVRvalue(int n);

EXPORTS bool WINAPI OpenLight(double m_Voltage,double m_Current);
EXPORTS bool WINAPI CloseLight(int times, int delay);

EXPORTS double WINAPI setway0(double m_Voltage,double m_Current,long delay_Time);
EXPORTS double WINAPI setway1(double m_Voltage,double m_Current,long delay_Time);
EXPORTS bool WINAPI getBering(void);
EXPORTS bool WINAPI setBering(bool m_Bearing);
EXPORTS bool WINAPI SelectChip(int m_Chip);
EXPORTS int SetChip(int n);
EXPORTS int GetChip(void);
EXPORTS int SetCommonfoot(int n);
bool WINAPI OpenSupply(int chip);

EXPORTS double WINAPI getIF(double m_Voltage,double m_Current,long delay_Time);
EXPORTS double WINAPI getIR(double m_Voltage,double m_Current,long delay_Time);
EXPORTS double WINAPI getVF(double m_Voltage,double m_Current,long delay_Time);
EXPORTS double WINAPI getVR(double m_Voltage,double m_Current,long delay_Time);
EXPORTS double WINAPI getTHY(double m_Voltage,double m_Current);
EXPORTS double WINAPI getDVF(double m_SourceC,long delay_Time);
EXPORTS double WINAPI getYbit(bool mix, long OpticGain,double m_Voltage,double m_Current,long delay_Time, bool show);
EXPORTS double getbit(int x);
EXPORTS double WINAPI getDualYbit(bool mix, long OpticGain,double m_Voltage,double m_Current,long delay_Time,long difference);
EXPORTS void SetSupplyParam(double voltage1, double voltage2, double current1, double current2);

EXPORTS void WINAPI Supply(double m_Voltage,double m_Current,int n);

EXPORTS double WINAPI initializeHardware(void);

EXPORTS double KeepLight_getIF(long delay_Time);
EXPORTS double KeepLight_getIR(long delay_Time);
EXPORTS double KeepLight_getVF(long delay_Time);
EXPORTS double KeepLight_getVR(long delay_Time);

EXPORTS double calibration();

EXPORTS double WINAPI checkC20mA2(void);

EXPORTS bool WINAPI InitVar(void);

EXPORTS bool getVFRoffset();
EXPORTS double outportOffset(bool bering, int i);
EXPORTS double outportResult(bool bering, int i);

EXPORTS bool WINAPI set_timeInit(void);
EXPORTS bool WINAPI set_timeTrigger(long v_timer);
EXPORTS bool WINAPI set_timeReset(void);