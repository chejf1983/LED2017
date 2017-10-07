/*******************************************************************************************************
**
** Copyright (C), 2011-2012, Nahon photoelectric technology CO., LTD.
** File Name:               SpectraArsenal.h
** Description:             
** Created By:             Monster
**
*********************************************************************************************************/

#ifdef LITS_EXPORTS
#define LITS_API __declspec(dllexport)
#else
#define LITS_API __declspec(dllimport)
#endif

#define SA_API_SUCCESS   0
#define SA_API_FAIL      -1


typedef enum
{
    SOFTWARE_SYNCHRONOUS,
	SOFTWARE_ASYNCHRONOUS,
	SOFTWARE_AUTO,
	EXINT_RISING_EDGE,
	EXINT_FALLING_EDGE,
	EXINT_HIGH_LEVEL,
	EXINT_LOW_LEVEL,
}TRIGGER_MODE;



typedef enum
{
    AUTO_INTEGRATION_DISABLE,
	AUTO_INTEGRATION_ENABLE,
}AUTO_INTEGRATION_MODE;

#define LED_CHANNEL1    0x00
#define LED_CHANNEL2    0x01
#define LED_CHANNEL3    0x02



LITS_API int LITS_Search(int CommIndex);
LITS_API int LITS_SystemOpen(void);
LITS_API void LITS_SystemClose(void);
LITS_API int LITS_SetIntegrationTime (int LITSIndex, int usec);
LITS_API int LITS_SetChannelIntegrationTime (int LITSIndex, int LedRusec, int LedGusec, int LedBusec);

LITS_API int LITS_SetAverageTimes(int LITSIndex, int AverageTimes);
LITS_API int LITS_GetWavelengthCalibrationCoefficients (int LITSIndex, double * WavelengthCalibration);
LITS_API char * LITS_GetSoftwareVersion(int LITSIndex);
LITS_API char LITS_GetHardwareVersion(int LITSIndex);
LITS_API char * LITS_GetSerialNumber(int LITSIndex);
LITS_API char * LITS_GetManufacturingDate(int LITSIndex);
LITS_API int LITS_NonlinearCalibration(int LITSIndex, double * pbSpectum, double * pbNewSpectum, int SpectumNumber);
LITS_API int LITS_GetNonlinearCalibrationPixel(int LITSIndex, 
										 float *pfNonlinearCalibPixelOrWL, int *piNonlinearCalibCoNumber,
	                                     float *pfNonlinearCalibAD, float *pfNonlinearCalibCo);
LITS_API int LITS_GetMeasureData(int LITSIndex, double *pdSpectumData1, float *pdElectricalData1, 
							 double *pdSpectumData2, float *pdElectricalData2, 
							 double *pdSpectumData3, float *pdElectricalData3);
LITS_API int LITS_GetMeasureDataHWTrigger(int LITSIndex, double *pdSpectumData1, float *pdElectricalData1, 
										 double *pdSpectumData2, float *pdElectricalData2, 
										 double *pdSpectumData3, float *pdElectricalData3, 
										 TRIGGER_MODE TriggerMode, int iTimeOut);
LITS_API int LITS_SetMode(int LITSIndex, char cMode, char cLedType);
LITS_API int LITS_GetMode(int LITSIndex, char *pcMode, char *pcLedType);
LITS_API int LITS_SetPolarityJudgmentPara(int LITSIndex, float fVoltage , float fCurrent, float fDelay, float fTime);
LITS_API int LITS_SetLedNegativePara(int LITSIndex, float fVoltage , float fCurrent, float fDelay, float fTime, int iChannelID);
LITS_API int LITS_SetLedPositivePara(int LITSIndex, float fVoltage , float fCurrent, float fDelay, float fTime, int iChannelID);
LITS_API int LITS_GetPolarityJudgmentPara(int LITSIndex, float *pfVoltage , float *pfCurrent, float *pfDelay, float *pfTime);
LITS_API int LITS_GetLedPositivePara(int LITSIndex, float *pfVoltage , float *pfCurrent, float *pfDelay, float *pfTime, int iChannelID);
LITS_API int LITS_GetLedNegativePara(int LITSIndex, float *pfVoltage , float *pfCurrent, float *pfDelay, float *pfTime, int iChannelID);

LITS_API int LITS_SetBinOutput(int LITSIndex, int iBin);
LITS_API int LITS_GetSpectralData(int LITSIndex, double *pdSpectumData);
LITS_API int LITS_GetPixelNumber(int LITSIndex);



