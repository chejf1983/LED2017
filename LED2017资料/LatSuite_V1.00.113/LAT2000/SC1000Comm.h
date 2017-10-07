//
#pragma  once
#include "Serial.h"

#define SC1000_LAMP_NUM		10

class CSC1000Comm
{
public:
	CSC1000Comm();
	~CSC1000Comm();

public:
	void Initialize(CString strCOM, int iAddr = 0x01, BOOL bEnglish = FALSE);

	BOOL SetOnOff(BOOL bOn[]);

	//
	// 退出远程, 退出远程才能手动操作SC1000仪器面板上的按键
	//
	BOOL ExitRemoteMode();

	// Set iCannel to -1 to turn off all channel
	BOOL SwitchChannel(int iChannel);

	BOOL SetBuzzer(BOOL bOn);

	BOOL SwitchAllLamp(BOOL bON);

	WORD Pri_SC1000_TestState2WORD(BOOL bOnFlag[]);

	BYTE Pri_SC1000_Output2BYTE(BOOL bOutputFlag[]);

	void Pri_SC1000_BYTE2Input(BYTE byte, BOOL bInputFlag[]);

protected:
	BOOL Communicate(BOOL bOn[], BOOL bOutputFlag[], BOOL bInputFlag[], BOOL bRemote);

private:
	Serial	m_ser;
	CString m_strCOM;
	int		m_iBaudRate;
	BOOL	m_bEnglish;
	BYTE	m_ucPCAddress;
	BYTE	m_ucDeviceAddress;

	BOOL	m_bSaveOnFlag[16];
	BOOL	m_bSaveOutFlag[8];
	BOOL	m_bSaveInputFlag[8];
};
