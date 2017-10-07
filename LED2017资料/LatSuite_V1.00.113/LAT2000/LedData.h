#pragma once
#include "NewTestColorData.h"

class CLedData : public CObject
{
public:
	CLedData(void);
	~CLedData(void);

	BOOL IsValid();
	BOOL SetValid(BOOL bValid);
	void Serialize(CArchive & ar);
	CString GetInfoString(BOOL bLedOn);
	BOOL IsLEDON();

	CLedData & operator = (CLedData & data);

public:
	ULONG m_ulID;
    // dimension code 
    CString m_strSN;
    BOOL m_bNotMoveLine;
    // add
    CString m_strLedModel;

	float m_fVoltageV;
	float m_fCurrentA;
	float m_fFrequencyHz;
	float m_fPowerW;
	float m_fPowerFactor;

	//�������ݼ�¼
	BOOL m_bHaveTestSaft;
	BOOL m_bSaftOK; //����ϸ����
	float m_fSaft_R; //��Ե����
	float m_fSaftLimit_R;
	float m_fSaft_V; //��ѹ����
	float m_fSaftLimit_V;
	float m_fSaft_C; //й¶����
	float m_fSaftLimit_C;

	// Spectrum data
	CArray<float,float> m_fValue;
	CNewTestColorData   m_ColorData;

	//2014.5.5���� ɫ�ݲ����
	enum SDCMType
	{
		SDCMType_ELLI,
		SDCMType_PLOY,
	};
	int		m_iSDCMType;	//���� ��Բ���Ƕ����
	CString m_strSDCMSta;	//ɫ�ݲ�ѡ��ı�׼
	float	m_fSDCM;		//��Բ�����ɫ�ݲ�ֵ
	BOOL	m_bInPoly;		//����� �Ƿ�����


private:
	BOOL m_bDataValid;
};

