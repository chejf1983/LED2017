///////////////BWTEK///////////////////
#define DLLIMPORT extern "C" __declspec(dllimport)
#define CALLINGWAY __stdcall

DLLIMPORT int CALLINGWAY bwtekTestUSB(int nUSBType, int nPixelNo, int nInputMode, int nChannel, void *pExtraData);
DLLIMPORT int CALLINGWAY bwtekSetTimeUSB(long  lTime, int nChannel);
DLLIMPORT int CALLINGWAY bwtekDataReadUSB(int  nTriggerMode, USHORT* pArray, int nChannel);
DLLIMPORT int CALLINGWAY bwtekCloseUSB(int nChannel);

typedef struct tagRS232Params {
	 int nPort;
	 int nBautRate;
	 int nAverage;
	 int nTimeDelay;
	 int nReserve;
	double fCoefficient[4];
} RS232Params, *PRS232Params;
//////////////////////////////////////