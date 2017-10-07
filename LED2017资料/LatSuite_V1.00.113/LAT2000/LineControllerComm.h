#pragma once
#include "Serial.h"

class CLineControllerComm
{
public:
	CLineControllerComm(void);
	~CLineControllerComm(void);

	void Initialize(CString strCOM);
    void SetDemo(BOOL bDemo);

	int m_iSendData[10];

	BOOL SetShowLED(int iType);
	BOOL MoveLineContinuous();
	BOOL SetLinePause();
	BOOL MoveLineOneStep();
	BOOL SetOldTime(float fOnTimeSec, float fOffTimeSec);
	BOOL ReadLineState(BOOL & bInposition, BOOL & bManualStopped, BOOL & bLampTooHigh);
	BOOL ClearAllState();
	BOOL SetBuzzer(BOOL bBuzzer);
private:
	BOOL MoveLineContinuous_Sub();
	BOOL SetLinePause_Sub();
	BOOL MoveLineOneStep_Sub();
	BOOL SetOldTime_Sub(float fOnTimeSec, float fOffTimeSec);
	BOOL ReadLineState_Sub(BOOL & bInposition, BOOL & bManualStopped, BOOL & bLampTooHigh);
	BOOL ClearAllState_Sub();
	BOOL SetBuzzer_Sub(BOOL bBuzzer);

	Serial	m_ser;
	CString m_strCOM;
	int		m_iBaudRate;
    BOOL m_bDemo;
	CRITICAL_SECTION m_critical;
};

