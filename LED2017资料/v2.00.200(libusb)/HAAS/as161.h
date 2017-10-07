//----------------------------------------------------------------------------
// (C) Copyright 2004, AVANTES B.V.
// Any reproduction without written permission is prohibited by law.
//----------------------------------------------------------------------------
//
// File type : C++ header
// Description : Main header file
//
//----------------------------------------------------------------------------
//
//
//----------------------------------------------------------------------------
#ifndef AVS_DLL_H
#define AVS_DLL_H

//----------------------------------------------------------------------------
// Export overview
//----------------------------------------------------------------------------
#ifdef DLL_EXPORTS
#define DLL_API extern "C" __declspec (dllexport)
#else
#define DLL_API extern "C" __declspec (dllimport)
#endif

// Device configuration data
const int NR_FIT_COEF               = 5;
const int VERSION_LEN               = 64;
const int MAX_NR_CHANNELS           = 8;
const int MAX_NR_PIXELS_PER_CHANNEL = 2048;
const int AVS_SERIAL_LEN            = 10;
const int ONE_CHANNEL               = 1;

// Return error codes
const int SUCCESS                   = 0;
const int UNCONFIGURED_DEVICE_OFFSET= 256;
const int INVALID_PARAMETER         = -1;
const int INVALID_PIXEL_RANGE       = -2;
const int NO_INT_DELAY_SUPPORT      = -3;
const int INVALID_NUMBER_OF_CHANNELS= -4;
const int DEVICE_NOT_FOUND          = -1000;
const int MEAS_NOT_ALLOWED          = -1001;
const int INVALID_MEAS_DATA         = -1011;
const int MEAS_INTERVAL_TOO_SHORT   = -1012;
const int INVALID_SMOOTHING_PARAM   = -1013;
const int INVALID_CHANNEL_ID        = -1100;
const int DEVICE_RET_UNKNOWN_ERROR  = -1101;
const int INVALID_PASSWORD          = -1102;
const int ERROR_IN_COMMUNICATION    = -1103;
const int INVALID_SPECTRA_NUMBER    = -1104;
const int EXT_TRIGGER_ENABLED       = -1105;
const int INVALID_DLL_VERSION       = -1106;

const long INVALID_AVS_HANDLE_VALUE = 1000L;
#define WM_MEAS_READY       (WM_USER + 1)


//----------------------------------------------------------------------------
typedef long        AvsHandle;

typedef enum
{
        UNKNOWN,
        AVAILABLE,
        IN_USE_BY_APPLICATION,
        IN_USE_BY_OTHER
} DEVICE_STATUS;


typedef struct
{
    char            SerialNumber[AVS_SERIAL_LEN];
    DEVICE_STATUS   Status;
} AvsIdentityType;

//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
//
// Name         : AVS_Init
//
// Description  : Tries to open com-port and ask spectrometer configuration
//
// Parameters   : a_COMPort   : -1, search for port to be used
//                              0, use USB port
//                              1-4, use COM port
//
// Returns      : integer     :  0..4, port successfully opened
//                               256..260 port opened, but device unconfigured
//                              -1, error occured
//
// Remark(s)    : Blocks application
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_Init
(
    int a_Port
);

//----------------------------------------------------------------------------
//
// Name         : AVS_Done
//
// Description  : Closes port and releases memory
//
// Parameters   : -
//
// Returns      : integer :  0, successfully closed
//                          -1, error occured
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_Done
(
    void
);

//----------------------------------------------------------------------------
//
// Name         : AVS_Measure
//
// Description  : Start measurement
//
// Parameters   : a_IntegrationTime : integration time in ms
//                a_Scans           : number of scans
//                a_hWnd            : handle of window to which ready message
//                                    should be sent
//
// Returns      : integer : 0, successfully started
//                          error code on error
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_Measure
(
    unsigned int    a_IntegrationTime,
    unsigned int    a_Scans,
    HWND            a_hWnd
);

//----------------------------------------------------------------------------
//
// Name         : AVS_GetLambda
//
// Description  : Returns the wavelength values corresponding to the pixels
//
// Parameters   : a_Channel : number of channel
//
// Returns      : integer       : 0, successfully started
//                                error code on error
//                a_pWaveLength : pointer to array of doubles,
//                                array size equal to number of pixels
//
// Remark(s)    : array size not checked
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_GetLambda
(
    unsigned char   a_Channel,
    double*         a_pWaveLength
);

//----------------------------------------------------------------------------
//
// Name         : AVS_GetScopeData
//
// Description  : Returns the values for each pixel
//
// Parameters   : a_Channel : number of channel
//
// Returns      : integer       : 0, successfully started
//                                error code on error
//                a_pSpectrum   : pointer to array of doubles containing dark
//                                values, array size equal to number of pixels
//
// Remark(s)    : array size not checked
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_GetScopeData
(
    unsigned char   a_Channel,
    double*         a_pSpectrum
);

//----------------------------------------------------------------------------
//
// Name         : AVS_GetNumPixels
//
// Description  : Returns the number of pixels
//
// Parameters   : -
//
// Returns      : integer       : 0, number of pixels available
//                                error code on error
//                a_pNrOfPixels : number of pixels
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_GetNumPixels
(
    unsigned int*    a_pNrOfPixels
);

//----------------------------------------------------------------------------
//
// Name         : AVS_GetNumChannels
//
// Description  : Returns the number of channels
//
// Parameters   : -
//
// Returns      : integer         : 0, number of channels available
//                                  error code on error
//                a_pNrOfChannels : number of channels
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_GetNumChannels
(
    unsigned char*    a_pNrOfChannels
);

//----------------------------------------------------------------------------
//
// Name         : AVS_GetGain
//
// Description  : Returns the gain of specified channel
//
// Parameters   : a_Channel       : channel identification
//
// Returns      : integer         : 0, ok
//                                  error code on error
//                a_pGain         : pointer to float to store gain
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_GetGain
(
    unsigned char   a_Channel,
    float*          a_pGain
);

//----------------------------------------------------------------------------
//
// Name         : AVS_GetWLCoef
//
// Description  : Returns the WaveLength Coefficients of specified channel
//
// Parameters   : a_Channel       : channel identification
//
// Returns      : integer         : 0, ok
//                                  error code on error
//                a_pFit         : pointer to float to store Fit parameters
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------

DLL_API int __stdcall AVS_GetWLCoef
(
    unsigned char   a_Channel,
    float*          a_pFit
);

//----------------------------------------------------------------------------
//
// Name         : AVS_GetStartStopPixel
//
// Description  : Returns the StartPixel and Stoppixel of specified channel
//
// Parameters   : a_Channel       : channel identification
//
// Returns      : integer         : 0, ok
//                                  error code on error
//                a_pStartPixel   : pointer to unsigned short to store startpixel
//                a_pStopPixel   : pointer to unsigned short to store startpixel
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_GetStartStopPixel
(
    unsigned char   a_Channel,
    unsigned short* a_pStartpixel,
    unsigned short* a_pStoppixel
);

//----------------------------------------------------------------------------
//
// Name         : AVS_GetDetectorType
//
// Description  : Returns the Detectortype (ID and name) that is stored
//
// Parameters   :
//
// Returns      : integer         : 0, ok
//                                  error code on error
//                a_pDetectorID   : pointer to unsigned char to store ID
//                a_pDetectorName : pointer to char to store name
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------

DLL_API int __stdcall AVS_GetDetectorType
(
    unsigned char*  a_pDetectorID,
    char*           a_pDetectorName
);

//----------------------------------------------------------------------------
//
// Name         : AVS_GetSerialNumber
//
// Description  : Returns the Detectortype (ID and name) that is stored
//
// Parameters   :
//
// Returns      : integer         : 0, ok
//                                  error code on error
//
//                a_pSerialNumber : pointer to char to store name
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------

DLL_API int __stdcall AVS_GetSerialNumber
(
    char*           a_pSerialNumber
);




//----------------------------------------------------------------------------
//
// Name         : AVS_GetOffset
//
// Description  : Returns the offset of specified channel
//
// Parameters   : a_Channel       : channel identification
//
// Returns      : integer         : 0, ok
//                                  error code on error
//                a_pOffset       : pointer to float to store offset
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_GetOffset
(
    unsigned char   a_Channel,
    float*          a_pOffset
);

//----------------------------------------------------------------------------
//
// Name         : AVS_GetDigIn
//
// Description  : Returns the state of the digital input pin DI1
//
// Parameters   : -
//
// Returns      : integer         : 0, ok
//                                  -1, communication error
//                a_pDigIn        : unsigned char pointer
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_GetDigIn
(
    unsigned char* a_pDigIn
);

//----------------------------------------------------------------------------
//
// Name         : AVS_SetGain
//
// Description  : Sets gain of specified channel
//
// Parameters   : a_Channel   : channel identification
//                a_Gain      : gain to be set
//                a_pPassword : password needed to write eeprom
//
// Returns      : integer         : 0, ok
//                                  error code, communication error
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_SetGain
(
    unsigned char   a_Channel,
    float           a_Gain,
    char*           a_pPassword
);

//----------------------------------------------------------------------------
//
// Name         : AVS_SetOffset
//
// Description  : Sets offset of specified channel
//
// Parameters   : a_Channel   : channel identification
//                a_Offset    : offset to be set
//                a_pPassword : password needed to write eeprom
//
// Returns      : integer         : 0, ok
//                                  error code, communication error
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_SetOffset
(
    unsigned char   a_Channel,
    float           a_Offset,
    char*           a_pPassword
);


//----------------------------------------------------------------------------
//
// Name         : AVS_SetWLCoef
//
// Description  : Sets XFit of specified channel
//
// Parameters   : a_Channel   : channel identification
//                a_XFit      : fitparameters to be set
//                a_pPassword : password needed to write eeprom
//
// Returns      : integer         : 0, ok
//                                  error code, communication error
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_SetWLCoef
(
    unsigned char   a_Channel,
    float*          a_XFit,
    char*           a_pPassword
);

//----------------------------------------------------------------------------
//
// Name         : AVS_SetStartStopPixel
//
// Description  : Sets Start and StopPixel of specified channel
//
// Parameters   : a_Channel   : channel identification
//                a_StartPixel: startpixel to be set
//                a_StartPixel: stoppixel to be set
//                a_pPassword : password needed to write eeprom
//
// Returns      : integer         : 0, ok
//                                  error code, communication error
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_SetStartStopPixel
(
    unsigned char   a_Channel,
    unsigned short  a_StartPixel,
    unsigned short  a_StopPixel,
    char*           a_pPassword
);


//----------------------------------------------------------------------------
//
// Name         : AVS_SetNumChannels
//
// Description  : Sets Nr Of Channels
//
// Parameters   :
//                a_NrOfChannels     : Nr Of Channels to be set
//                a_pPassword : password needed to write eeprom
//
// Returns      : integer         : 0, ok
//                                  error code, communication error
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_SetNumChannels
(
    unsigned char   a_NrOfChannels,
    char*           a_pPassword
);

//----------------------------------------------------------------------------
//
// Name         : AVS_SetNumPixels
//
// Description  : Sets Nr Of Pixels
//
// Parameters   :
//                a_NrOfPixels     : Nr Of Pixels to be set
//                a_pPassword : password needed to write eeprom
//
// Returns      : integer         : 0, ok
//                                  error code, communication error
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_SetNumPixels
(
    unsigned short  a_NrOfPixels,
    char*           a_pPassword
);



//----------------------------------------------------------------------------
//
// Name         : AVS_SetDigOut
//
// Description  : Sets state of digital output
//
// Parameters   : a_PortId  : digital output id.
//                a_Status  : new state digital output
//
// Returns      : integer         : 0, ok
//                                  error code, communication error
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_SetDigOut
(
    unsigned char a_PortId,
    unsigned char a_Status
);

//----------------------------------------------------------------------------
//
// Name         : AVS_SetPixelSelection
//
// Description  : Sets range of pixels that have to be transmitted to the PC
//
// Parameters   : a_Channel    : channel for which range is valid
//                a_StartPixel : start pixel index
//                a_StopPixel  : stop pixel index (included)
//
// Returns      : integer         : 0, ok
//                                  error code, communication error
//
// Remark(s)    : if (a_StartPixel > a_StopPixel) than channel disabled
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_SetPixelSelection
(
    unsigned char   a_Channel,
    unsigned int    a_StartPixel,
    unsigned int    a_StopPixel
);

//----------------------------------------------------------------------------
//
// Name         : AVS_SetExternalTrigger
//
// Description  : Sets external trigger mode
//
// Parameters   : a_Status  : new state external trigger mode
//
// Returns      : integer         : 0, ok
//                                  error code, communication error
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_SetExternalTrigger
(
    unsigned char   a_Status
);

//----------------------------------------------------------------------------
//
// Name         : AVS_SetStrobeControl
//
// Description  : Sets strobe control mode
//
// Parameters   : a_NrFlashes  : number of flashes during scan
//
// Returns      : integer         : 0, ok
//                                  error code, communication error
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_SetStrobeControl
(
    unsigned int    a_NrFlashes
);

//----------------------------------------------------------------------------
//
// Name         : AVS_SetFixedStrobe
//
// Description  : Sets fixed strobe mode
//
// Parameters   : a_Status  : new state fixed strobemode
//
// Returns      : integer         : 0, ok
//                                  error code, communication error
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_SetFixedStrobe
(
    unsigned char   a_Status
);


//----------------------------------------------------------------------------
//
// Name         : AVS_CorrectDynamicDark
//
// Description  : Sets dynamic dark correction mode and parameters
//
// Parameters   : a_Status  : new state dynamic dark correction
//                a_ForgetPercentage : percentage of new dark values used
//
// Returns      : integer         : 0, ok
//                                  error code, communication error
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_CorrectDynamicDark
(
    unsigned char   a_Status,
    unsigned int    a_ForgetPercentage
);


//----------------------------------------------------------------------------
//
// Name         : AVS_PollScan
//
// Description  : Poll advent of new data (e.g. for VB)
//
// Parameters   : -
//
// Returns      : Integer, 0 when data are not ready
//                         1 when data are available
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_PollScan
(
    void
);


DLL_API int __stdcall AVS_SetIntegrationDelay
(
    unsigned int a_IntegrationDelay
);

//----------------------------------------------------------------------------
//
// Name         : AVS_SetSaturationDetection
//
// Description  : Sets Saturation detection mode
//
// Parameters   : a_Status        : new state Saturation detection
//                                : 0 = No detection
//                                : 1 = Detects pixels with Scopedata 16383 counts
//                                      regardless the dyndarkcorrection
//                                : 2 = Only Sony: detects and corrects also saturated pixels
//                                      with values < 16383 (peak inversion)
//
// Returns      : integer         : 0, ok
//                                  error code, communication error
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_SetSaturationDetection
(
    unsigned char   a_Status
);

//----------------------------------------------------------------------------
//
// Name         : AVS_GetSaturatedPixels
//
// Description  : Returns for each pixel the number of scans (out of a total
//                of NrOfAverage scans) for which the pixel was saturated
//
// Parameters   : a_Channel : number of channel
//
// Returns      : integer       : 0, successfully started
//                                error code on error
//                a_pSaturated  : pointer to array of integers containing
//                                number of scans saturated,
//                                array size equal to number of pixels
//
// Remark(s)    : array size not checked
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_GetSaturatedPixels
(
    unsigned char   a_Channel,
    unsigned int*   a_pSaturated
);


//----------------------------------------------------------------------------
//
// Name         : AVS_GetList
//
// Description  : Returns device information for each spectrometer connected
//                to the ports indicated at AVS_Init
//
// Parameters   : a_ListSize    : number of bytes allocated by the caller to
//                                store the a_pList data
//                a_pRequiredSize : Number of bytes needed to store information
//                a_pList       : pointer to allocated buffer to store information
//
// Returns      : int           : number of devices in list
//                                (if 0 and a_pRequiredSize > a_ListSize,
//                                 then allocate larger buffer
//                                )
// Remark(s)    : -
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_GetList
(
    unsigned int        a_ListSize,
    unsigned int*       a_pRequiredSize,
    AvsIdentityType*    a_pList
);

//----------------------------------------------------------------------------
//
// Name         : AVS_Activate
//
// Description  : Activates selected spectrometer for communication
//
// Parameters   : a_pDeviceId   : AvsIdentity of desired spectrometer
//
// Returns      : AvsHandle     : handle to be used in subsequent calls
//                INVALID_HANDLE_VALUE  : in case of error
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------
DLL_API AvsHandle __stdcall AVS_Activate
(
    AvsIdentityType*    a_pDeviceId
);


//----------------------------------------------------------------------------
//
// Name         : AVS_Deactivate
//
// Description  : De-activates selected spectrometer for communication
//
// Parameters   : a_hHandle    : Device handle from AVS_Activate
//
// Returns      : -
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------
DLL_API bool  __stdcall AVS_Deactivate
(
    AvsHandle    a_hHandle
);

//----------------------------------------------------------------------------
//
// Name         : AVS_Register
//
// Description  : Installs an application windows handle to which device
//                attachment/removal messages have to be sent
//
// Parameters   : a_hWnd    : application window handle
//
// Returns      : -
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------
DLL_API bool  __stdcall AVS_Register
(
    HWND    a_hWnd
);

//----------------------------------------------------------------------------
//
// Name         : AVS_M_Measure
//
// Description  : Start measurement
//
// Parameters   : a_IntegrationTime : integration time in ms
//                a_Scans           : number of scans
//                a_hWnd            : handle of window to which ready message
//                                    should be sent
//
// Returns      : integer : 0, successfully started
//                          error code on error
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_M_Measure
(
    AvsHandle       a_hHandle,
    unsigned int    a_IntegrationTime,
    unsigned int    a_Scans,
    HWND            a_hWnd
);

//----------------------------------------------------------------------------
//
// Name         : AVS_M_GetLambda
//
// Description  : Returns the wavelength values corresponding to the pixels
//
// Parameters   : a_Channel : number of channel
//
// Returns      : integer       : 0, successfully started
//                                error code on error
//                a_pWaveLength : pointer to array of doubles,
//                                array size equal to number of pixels
//
// Remark(s)    : array size not checked
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_M_GetLambda
(
    AvsHandle       a_hHandle,
    unsigned char   a_Channel,
    double*         a_pWaveLength
);

//----------------------------------------------------------------------------
//
// Name         : AVS_M_GetScopeData
//
// Description  : Returns the values for each pixel
//
// Parameters   : a_Channel : number of channel
//
// Returns      : integer       : 0, successfully started
//                                error code on error
//                a_pSpectrum   : pointer to array of doubles containing dark
//                                values, array size equal to number of pixels
//
// Remark(s)    : array size not checked
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_M_GetScopeData
(
    AvsHandle       a_hHandle,
    unsigned char   a_Channel,
    double*         a_pSpectrum
);

//----------------------------------------------------------------------------
//
// Name         : AVS_M_GetNumPixels
//
// Description  : Returns the number of pixels
//
// Parameters   : -
//
// Returns      : integer       : 0, number of pixels available
//                                error code on error
//                a_pNrOfPixels : number of pixels
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_M_GetNumPixels
(
    AvsHandle       a_hHandle,
    unsigned int*    a_pNrOfPixels
);

//----------------------------------------------------------------------------
//
// Name         : AVS_M_GetNumChannels
//
// Description  : Returns the number of channels
//
// Parameters   : -
//
// Returns      : integer         : 0, number of channels available
//                                  error code on error
//                a_pNrOfChannels : number of channels
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_M_GetNumChannels
(
    AvsHandle       a_hHandle,
    unsigned char*    a_pNrOfChannels
);

//----------------------------------------------------------------------------
//
// Name         : AVS_M_GetGain
//
// Description  : Returns the gain of specified channel
//
// Parameters   : a_Channel       : channel identification
//
// Returns      : integer         : 0, ok
//                                  error code on error
//                a_pGain         : pointer to float to store gain
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_M_GetGain
(
    AvsHandle       a_hHandle,
    unsigned char   a_Channel,
    float*          a_pGain
);


//----------------------------------------------------------------------------
//
// Name         : AVS_M_GetWLCoef
//
// Description  : Returns the WaveLength Coefficients of specified channel
//
// Parameters   : a_Channel       : channel identification
//
// Returns      : integer         : 0, ok
//                                  error code on error
//                a_pFit         : pointer to float to store Fit parameters
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------

DLL_API int __stdcall AVS_M_GetWLCoef
(
    AvsHandle       a_hHandle,
    unsigned char   a_Channel,
    float*          a_pFit
);

//----------------------------------------------------------------------------
//
// Name         : AVS_M_GetStartStopPixel
//
// Description  : Returns the StartPixel and Stoppixel of specified channel
//
// Parameters   : a_Channel       : channel identification
//
// Returns      : integer         : 0, ok
//                                  error code on error
//                a_pStartPixel   : pointer to unsigned short to store startpixel
//                a_pStopPixel   : pointer to unsigned short to store startpixel
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_M_GetStartStopPixel
(
    AvsHandle       a_hHandle,
    unsigned char   a_Channel,
    unsigned short* a_pStartpixel,
    unsigned short* a_pStoppixel
);

//----------------------------------------------------------------------------
//
// Name         : AVS_M_GetDetectorType
//
// Description  : Returns the Detectortype (ID and name) that is stored
//
// Parameters   :
//
// Returns      : integer         : 0, ok
//                                  error code on error
//                a_pDetectorID   : pointer to unsigned char to store ID
//                a_pDetectorName : pointer to char to store name
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------

DLL_API int __stdcall AVS_M_GetDetectorType
(
    AvsHandle       a_hHandle,
    unsigned char*  a_pDetectorID,
    char*           a_pDetectorName
);

//----------------------------------------------------------------------------
//
// Name         : AVS_M_GetSerialNumber
//
// Description  : Returns the Detectortype (ID and name) that is stored
//
// Parameters   :
//
// Returns      : integer         : 0, ok
//                                  error code on error
//
//                a_pSerialNumber : pointer to char to store name
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------

DLL_API int __stdcall AVS_M_GetSerialNumber
(
    AvsHandle       a_hHandle,
    char*           a_pSerialNumber
);


//----------------------------------------------------------------------------
//
// Name         : AVS_M_GetOffset
//
// Description  : Returns the offset of specified channel
//
// Parameters   : a_Channel       : channel identification
//
// Returns      : integer         : 0, ok
//                                  error code on error
//                a_pOffset       : pointer to float to store offset
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_M_GetOffset
(
    AvsHandle       a_hHandle,
    unsigned char   a_Channel,
    float*          a_pOffset
);

//----------------------------------------------------------------------------
//
// Name         : AVS_M_GetDigIn
//
// Description  : Returns the state of the digital input pin DI1
//
// Parameters   : -
//
// Returns      : integer         : 0, ok
//                                  -1, communication error
//                a_pDigIn        : unsigned char pointer
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_M_GetDigIn
(
    AvsHandle       a_hHandle,
    unsigned char* a_pDigIn
);

//----------------------------------------------------------------------------
//
// Name         : AVS_M_SetGain
//
// Description  : Sets gain of specified channel
//
// Parameters   : a_Channel   : channel identification
//                a_Gain      : gain to be set
//                a_pPassword : password needed to write eeprom
//
// Returns      : integer         : 0, ok
//                                  error code, communication error
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_M_SetGain
(
    AvsHandle       a_hHandle,
    unsigned char   a_Channel,
    float           a_Gain,
    char*           a_pPassword
);

//----------------------------------------------------------------------------
//
// Name         : AVS_M_SetOffset
//
// Description  : Sets offset of specified channel
//
// Parameters   : a_Channel   : channel identification
//                a_Offset    : offset to be set
//                a_pPassword : password needed to write eeprom
//
// Returns      : integer         : 0, ok
//                                  error code, communication error
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_M_SetOffset
(
    AvsHandle       a_hHandle,
    unsigned char   a_Channel,
    float           a_Offset,
    char*           a_pPassword
);


//----------------------------------------------------------------------------
//
// Name         : AVS_M_SetWLCoef
//
// Description  : Sets XFit of specified channel
//
// Parameters   : a_Channel   : channel identification
//                a_XFit      : fitparameters to be set
//                a_pPassword : password needed to write eeprom
//
// Returns      : integer         : 0, ok
//                                  error code, communication error
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_M_SetWLCoef
(
    AvsHandle       a_hHandle,
    unsigned char   a_Channel,
    float*          a_XFit,
    char*           a_pPassword
);

//----------------------------------------------------------------------------
//
// Name         : AVS_M_SetStartStopPixel
//
// Description  : Sets Start and StopPixel of specified channel
//
// Parameters   : a_Channel   : channel identification
//                a_StartPixel: startpixel to be set
//                a_StartPixel: stoppixel to be set
//                a_pPassword : password needed to write eeprom
//
// Returns      : integer         : 0, ok
//                                  error code, communication error
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_M_SetStartStopPixel
(
    AvsHandle       a_hHandle,
    unsigned char   a_Channel,
    unsigned short  a_StartPixel,
    unsigned short  a_StopPixel,
    char*           a_pPassword
);


//----------------------------------------------------------------------------
//
// Name         : AVS_M_SetNumChannels
//
// Description  : Sets Nr Of Channels
//
// Parameters   :
//                a_NrOfChannels     : Nr Of Channels to be set
//                a_pPassword : password needed to write eeprom
//
// Returns      : integer         : 0, ok
//                                  error code, communication error
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_M_SetNumChannels
(
    AvsHandle       a_hHandle,
    unsigned char   a_NrOfChannels,
    char*           a_pPassword
);

//----------------------------------------------------------------------------
//
// Name         : AVS_M_SetNumPixels
//
// Description  : Sets Nr Of Pixels
//
// Parameters   :
//                a_NrOfPixels     : Nr Of Pixels to be set
//                a_pPassword : password needed to write eeprom
//
// Returns      : integer         : 0, ok
//                                  error code, communication error
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_M_SetNumPixels
(
    AvsHandle       a_hHandle,
    unsigned short  a_NrOfPixels,
    char*           a_pPassword
);



//----------------------------------------------------------------------------
//
// Name         : AVS_M_SetDigOut
//
// Description  : Sets state of digital output
//
// Parameters   : a_PortId  : digital output id.
//                a_Status  : new state digital output
//
// Returns      : integer         : 0, ok
//                                  error code, communication error
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_M_SetDigOut
(
    AvsHandle       a_hHandle,
    unsigned char a_PortId,
    unsigned char a_Status
);

//----------------------------------------------------------------------------
//
// Name         : AVS_M_SetPixelSelection
//
// Description  : Sets range of pixels that have to be transmitted to the PC
//
// Parameters   : a_Channel    : channel for which range is valid
//                a_StartPixel : start pixel index
//                a_StopPixel  : stop pixel index (included)
//
// Returns      : integer         : 0, ok
//                                  error code, communication error
//
// Remark(s)    : if (a_StartPixel > a_StopPixel) than channel disabled
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_M_SetPixelSelection
(
    AvsHandle       a_hHandle,
    unsigned char   a_Channel,
    unsigned int    a_StartPixel,
    unsigned int    a_StopPixel
);

//----------------------------------------------------------------------------
//
// Name         : AVS_M_SetExternalTrigger
//
// Description  : Sets external trigger mode
//
// Parameters   : a_Status  : new state external trigger mode
//
// Returns      : integer         : 0, ok
//                                  error code, communication error
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_M_SetExternalTrigger
(
    AvsHandle       a_hHandle,
    unsigned char   a_Status
);

//----------------------------------------------------------------------------
//
// Name         : AVS_M_SetStrobeControl
//
// Description  : Sets strobe control mode
//
// Parameters   : a_NrFlashes  : number of flashes during scan
//
// Returns      : integer         : 0, ok
//                                  error code, communication error
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_M_SetStrobeControl
(
    AvsHandle       a_hHandle,
    unsigned int    a_NrFlashes
);

//----------------------------------------------------------------------------
//
// Name         : AVS_M_SetFixedStrobe
//
// Description  : Sets fixed strobe mode
//
// Parameters   : a_Status  : new state fixed strobemode
//
// Returns      : integer         : 0, ok
//                                  error code, communication error
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_M_SetFixedStrobe
(
    AvsHandle       a_hHandle,
    unsigned char   a_Status
);


//----------------------------------------------------------------------------
//
// Name         : AVS_M_CorrectDynamicDark
//
// Description  : Sets dynamic dark correction mode and parameters
//
// Parameters   : a_Status  : new state dynamic dark correction
//                a_ForgetPercentage : percentage of new dark values used
//
// Returns      : integer         : 0, ok
//                                  error code, communication error
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_M_CorrectDynamicDark
(
    AvsHandle       a_hHandle,
    unsigned char   a_Status,
    unsigned int    a_ForgetPercentage
);


//----------------------------------------------------------------------------
//
// Name         : AVS_M_PollScan
//
// Description  : Poll advent of new data (e.g. for VB)
//
// Parameters   : -
//
// Returns      : Integer, 0 when data are not ready
//                         1 when data are available
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_M_PollScan
(
    AvsHandle       a_hHandle
);


DLL_API int __stdcall AVS_M_SetIntegrationDelay
(
    AvsHandle       a_hHandle,
    unsigned int a_IntegrationDelay
);

//----------------------------------------------------------------------------
//
// Name         : AVS_M_SetSaturationDetection
//
// Description  : Sets Saturation detection mode
//
// Parameters   : a_Status        : new state Saturation detection
//                                : 0 = No detection
//                                : 1 = Detects pixels with Scopedata 16383 counts
//                                      regardless the dyndarkcorrection
//                                : 2 = Only Sony: detects and corrects also saturated pixels
//                                      with values < 16383 (peak inversion)
//
// Returns      : integer         : 0, ok
//                                  error code, communication error
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_M_SetSaturationDetection
(
    AvsHandle       a_hHandle,
    unsigned char   a_Status
);

//----------------------------------------------------------------------------
//
// Name         : AVS_M_GetSaturatedPixels
//
// Description  : Returns for each pixel the number of scans (out of a total
//                of NrOfAverage scans) for which the pixel was saturated
//
// Parameters   : a_Channel : number of channel
//
// Returns      : integer       : 0, successfully started
//                                error code on error
//                a_pSaturated  : pointer to array of integers containing
//                                number of scans saturated,
//                                array size equal to number of pixels
//
// Remark(s)    : array size not checked
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_M_GetSaturatedPixels
(
    AvsHandle       a_hHandle,
    unsigned char   a_Channel,
    unsigned int*   a_pSaturated
);


//----------------------------------------------------------------------------
//
// Name         : AVS_MeasureByInterval
//
// Description  : Starts continuous measurement and returns result every
//                a_IntervalTime ms.
//
// Parameters   : a_IntegrationTime : integration time in ms
//                a_Scans           : number of scans
//                a_IntervalTime    : interval time in ms
//                a_hWnd            : handle of window to which ready message
//                                    should be sent
//
// Returns      : integer : 0, successfully started
//                          error code on error
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_MeasureByInterval
(
    unsigned int    a_IntegrationTime,
    unsigned int    a_Scans,
    unsigned int    a_IntervalTime,
    HWND            a_hWnd
);

//----------------------------------------------------------------------------
//
// Name         : AVS_M_MeasureByInterval
//
// Description  : Starts continuous measurement and returns result every
//                a_IntervalTime ms.
//
// Parameters   : a_hHandle         : device handle
//                a_IntegrationTime : integration time in ms
//                a_Scans           : number of scans
//                a_IntervalTime    : interval time in ms
//                a_hWnd            : handle of window to which ready message
//                                    should be sent
//
// Returns      : integer : 0, successfully started
//                          error code on error
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_M_MeasureByInterval
(
    AvsHandle       a_hHandle,
    unsigned int    a_IntegrationTime,
    unsigned int    a_Scans,
    unsigned int    a_IntervalTime,
    HWND            a_hWnd
);

//----------------------------------------------------------------------------
//
// Name         : AVS_StopInterval
//
// Description  : Stops continuous measurement
//
// Parameters   : -
//
// Returns      : -
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------
DLL_API void __stdcall AVS_StopInterval
(
    void
);

//----------------------------------------------------------------------------
//
// Name         : AVS_M_StopInterval
//
// Description  : Stops continuous measurement
//
// Parameters   : a_Handle  : device handle
//
// Returns      : -
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------
DLL_API void __stdcall AVS_M_StopInterval
(
    AvsHandle   a_Handle
);
//----------------------------------------------------------------------------
//
// Name         : AVS_SetStoreToRAM
//
// Description  : Start measurement
//
// Parameters   : a_pNrOfSpectras    : number of spectras
//                                    that should be sotred
//                                    into the XRAM
//
//
// Returns      : integer : actual Number of spectras or
//                          error code on error
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_SetStoreToRAM
(
    unsigned int*    a_pNrOfSpectras
);

//----------------------------------------------------------------------------
//
// Name         : AVS_M_SetStoreToRAM
//
// Description  : allocate desired memoryspace in RAM
//
// Parameters   : a_pNrOfSpectras     : number of spectras
//                                     that should be stored
//                                     into XRAM
//
//
// Returns      : integer : actual Number of spactras,
//                          error code on error
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_M_SetStoreToRAM
(
    AvsHandle        a_hHandle,
    unsigned int*    a_pNrOfSpectras
);
//----------------------------------------------------------------------------
//
// Name         : AVS_M_SetStoreToRAM
//
// Description  : allocate desired memoryspace in RAM
//
// Parameters   : a_pNrOfSpectras     : number of spectras
//                                     that should be stored
//                                     into XRAM
//
//
// Returns      : integer : actual Number of spactras,
//                          error code on error
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_GetMultiScopeData
(
    unsigned int    a_SpectraNumber,
    unsigned int*   a_Timestamp,
    double*         a_pSpectrum
);
//----------------------------------------------------------------------------
//
// Name         : AVS_M_GetMultiScopeData
//
// Description  : allocate desired memoryspace in RAM
//
// Parameters   : a_pNrOfSpectras     : number of spectras
//                                     that should be stored
//                                     into XRAM
//
//
// Returns      : integer : actual Number of spactras,
//                          error code on error
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_M_GetMultiScopeData
(
    AvsHandle       a_hHandle,
    unsigned int    a_SpectraNumber,
    unsigned int*   a_Timestamp,
    double*         a_pSpectrum
);
//----------------------------------------------------------------------------
//
// Name         : AVS_GetFirmwareVersion
//
// Description  : gets firmware version
//
// Parameters   : a_pVersionString    : pointer of a string 
//										where the version info 
//                                      is copied to.
//
//
// Returns      : 
//
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_GetFirmwareVersion
(
    char*    a_pVersionString
);
//----------------------------------------------------------------------------
//
// Name         : AVS_M_GetFirmwareVersion
//
// Description  : gets firmware version
//
// Parameters   : a_pVersionString    : pointer of a string 
//										where the version info 
//                                      is copied to.
//
//
// Returns      : 
//
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_M_GetFirmwareVersion
(
    AvsHandle       a_hHandle,
    char*   a_pVersionString
);
//----------------------------------------------------------------------------
//
// Name         : AVS_GetDLLVersion
//
// Description  : gets the Dll version
//
// Parameters   : a_pVersionString    : pointer of a string 
//										where the version info 
//                                      is copied to.
//
//
// Returns      : 
//                
//
// Remark(s)    : -
//
//----------------------------------------------------------------------------
DLL_API int __stdcall AVS_GetDLLVersion
(
    char*    a_pVersionString
);








//----------------------------------------------------------------------------
// End of definitions
//----------------------------------------------------------------------------



#endif  // AVS_DLL_H



