#pragma once
class CLAT_SaftComm
{
public:
	void InitSaftComm(int iType, int iCom);
	int m_iCom;     //����
	int m_iDevType; //�豸����
	CLAT_SaftComm(void);
	~CLAT_SaftComm(void);
};

