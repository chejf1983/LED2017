#pragma once
#include "Serial.h"


// 无锡高温箱通讯,与高低温不同的
// RS485, 有地址，9600bps

class CComm  
{
private:
	Serial m_ser;
	UINT m_iBaudrate;
	CString m_strCOM;
	BOOL m_bDemo;

public:		

    BOOL SetP_n2Type(int &iSTNo);
    BOOL SetP_dPType(int &iSTNo);

	BOOL StandbyOff(int &iSTNo);
	BOOL StandbyOn(int &iSTNo);
		
	BOOL StopHeater(int &iSTNo);
	BOOL StartHeater(int &iSTNo);

	BOOL GetPV(int &iSTNo, float &fPV);

	BOOL SetSV(int &iSTNo, float &fSV);
	BOOL GetSV(int &iSTNo, float &fSV);

    BOOL SetSelfTruningMode(int &iSTNo);
    BOOL SetPIDTruning(int &iSTNo);
    BOOL GetPIDTruningState(int &iSTNo, int &iState);
    BOOL GetPID(int &iSTNo, float &fP, float &fI, float &fD);


	WORD CalcCRC(int& iDataNum, BYTE* pOutArray);

	void SetDemo(BOOL bDemo);
	void SetBaudrate(int iBaudrate);
	void SetCom(CString strCOM);
			
    BOOL WriteDataCommand(int &iSTNo, WORD WAddress, WORD wData);
    BOOL ReadDataCommand(int &iSTNo, WORD WAddress, WORD &wData);

	CComm();
	virtual ~CComm();
};
