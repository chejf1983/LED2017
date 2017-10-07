#pragma once
class CCalibrationData
{
public:
	CCalibrationData(void);
	~CCalibrationData(void);

	int GetNoneZeroIk();
	int GetNoneZeroUk();
	BOOL SaveFile(CString strPathName);
	BOOL OpenFile(CString strPathName);
	
public:
#define MAX_RANGE		8
#define CAL_DA_NUM		2

	float m_fI[MAX_RANGE][CAL_DA_NUM];
	float m_fDAI[MAX_RANGE][CAL_DA_NUM];
	float m_fStdI[MAX_RANGE][CAL_DA_NUM];
	float m_fkI[MAX_RANGE];
	float m_fbI[MAX_RANGE];

	float m_fU[MAX_RANGE][CAL_DA_NUM];
	float m_fDAU[MAX_RANGE][CAL_DA_NUM];
	float m_fStdU[MAX_RANGE][CAL_DA_NUM];
	float m_fkU[MAX_RANGE];
	float m_fbU[MAX_RANGE];

protected:
	BOOL Serialize(CArchive & ar);
};

