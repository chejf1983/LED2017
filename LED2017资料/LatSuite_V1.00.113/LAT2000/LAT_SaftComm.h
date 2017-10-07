#pragma once
class CLAT_SaftComm
{
public:
	void InitSaftComm(int iType, int iCom);
	int m_iCom;     //串口
	int m_iDevType; //设备类型
	CLAT_SaftComm(void);
	~CLAT_SaftComm(void);
};

