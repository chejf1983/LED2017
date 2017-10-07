/*******************************************************************************************************
**
** Copyright (C), 2011-2012, Nahon photoelectric technology CO., LTD.
** File Name:               SpectraArsenal.h
** Description:             
** Created By:             Monster
**
*********************************************************************************************************/

#ifdef SPECTRAARSENAL_EXPORTS
#define SPECTRAARSENAL_API __declspec(dllexport)
#else
#define SPECTRAARSENAL_API __declspec(dllimport)
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

#if 0
typedef struct
{
	int pixelNumber;
	double Spectum[2048];
}Spectum_Data;
#endif


SPECTRAARSENAL_API char* SA_GetAPIVersion(void);
SPECTRAARSENAL_API int SA_SetIntegrationTime (int spectrometerIndex, int usec);
SPECTRAARSENAL_API int SA_SetAverageTimes(int spectrometerIndex, int AverageTimes);
SPECTRAARSENAL_API int SA_GetWavelengthCalibrationCoefficients (int spectrometerIndex, double * WavelengthCalibration);

SPECTRAARSENAL_API int SA_OpenSpectrometers(void);
SPECTRAARSENAL_API int SA_OpenSpectrometersForSerial(void);
SPECTRAARSENAL_API  int SA_OpenSpectrometersSimplifyForSerial(int iComID);

SPECTRAARSENAL_API void SA_CloseSpectrometers(void);
SPECTRAARSENAL_API int SA_GetWavelength(int spectrometerIndex, double *pdWavelengthData, int &pSpectumNumber);
SPECTRAARSENAL_API int SA_GetSpectum(int spectrometerIndex, double *pdSpectumData, int &pSpectumNumber);
SPECTRAARSENAL_API int SA_GetSpectumHWTrigger(int spectrometerIndex, double *pdSpectumData, int &pSpectumNumber, int iTimeOut, TRIGGER_MODE TriggerMode);
SPECTRAARSENAL_API int SA_ScanStartAsyncSoftTrigger(int spectrometerIndex);
SPECTRAARSENAL_API int SA_GetSpectumAsyncSoftTrigger(int spectrometerIndex, int &pState, double *pdSpectumData, int &pSpectumNumber);
SPECTRAARSENAL_API int SA_NonlinearCalibration(int spectrometerIndex, double * pbSpectum, double * pbNewSpectum, int SpectumNumber);


SPECTRAARSENAL_API char * SA_GetSpectrometersName(int spectrometerIndex);
SPECTRAARSENAL_API int SA_GetMaxIntegrationTime (int spectrometerIndex);
SPECTRAARSENAL_API int SA_GetMinIntegrationTime (int spectrometerIndex);
SPECTRAARSENAL_API char * SA_GetSoftwareVersion(int spectrometerIndex);
SPECTRAARSENAL_API char SA_GetHardwareVersion(int spectrometerIndex);
SPECTRAARSENAL_API char * SA_GetSerialNumber(int spectrometerIndex);
SPECTRAARSENAL_API int SA_GetSpectrometerPixelsNumber (int spectrometerIndex);
SPECTRAARSENAL_API char * SA_GetManufacturingDate(int spectrometerIndex);

SPECTRAARSENAL_API int SA_WriteUserMemory(int spectrometerIndex, int Address, int length, BYTE * UserData);
SPECTRAARSENAL_API int SA_ReadUserMemory(int spectrometerIndex, int Address, int length, BYTE * UserData);


SPECTRAARSENAL_API int SA_SetWavelengthCalibrationCoefficients (int spectrometerIndex, double *WavelengthCalibration);
SPECTRAARSENAL_API int SA_SetNonlinearCalibrationPixel(int spectrometerIndex, float fPixelValue, int ParaNum, float *pfADValue, float *pfCalibrationCo);
SPECTRAARSENAL_API int SA_GetNonlinearCalibrationPixel(int spectrometerIndex, float &pfNonlinearCalibPixelOrWL, int &piNonlinearCalibCoNumber, float *pfNonlinearCalibAD, float *pfNonlinearCalibCo);

SPECTRAARSENAL_API int SA_SetMultiChannelIntegrationTime (int spectrometerIndex, int *usec);
SPECTRAARSENAL_API int SA_GetMultiChannelSpectum(int spectrometerIndex, double *pdSpectumData, int &pSpectumNumber, int iChannelNum);

SPECTRAARSENAL_API int SA_SetMissPixels(int spectrometerIndex, int iMissPixelNumber, int *piMissPixel);
SPECTRAARSENAL_API int SA_GetMissPixels(int spectrometerIndex, int *piMissPixel);

