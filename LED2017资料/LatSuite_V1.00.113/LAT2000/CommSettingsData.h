#pragma once
#include "DPSDefinition.h"
#include "LAT2000.h"


class CCommSettingsData
{
public:
	CCommSettingsData(void);
	~CCommSettingsData(void);

	//CCommSettingsData & operator = (CCommSettingsData & data);

	int GetIntegerCOM(CString strCOM);
	BOOL WriteToFile(CString strPathName);
	BOOL ReadFromFile(CString strPathName);
    //CCommSettingsData &operator= (const CCommSettingsData &data);
    void InitWatchPaneSetting();
public:
	// 2.DPS
	BOOL m_bHaveDPS;
	CString m_strCOMDPS;
	int m_iDPSType;
	
	//���β�������
	BOOL	m_bHaveMyLast;
	CString m_strMyLastCOM;
	int		m_iMyLastPowerType;
	
	//�����������
	BOOL	m_bHaveSaft_NYY;
	BOOL	m_bHaveSaft_JYDZ;
	BOOL	m_bHaveSaft_XLDL;
	int		m_iTypeSaftNyy;
	int		m_iTypeSaftJydz;
	int		m_iTypeSaftXLDL;
	CString m_strSaftNyyCOM;
	CString m_strSaftJydzCOM;
	CString m_strSaftXLDLCOM;
	CString m_strComNyy2; //�������Ĵ���
	CString m_strComJydz2;
	CString m_strComXldl2;

	// 3.EMS61000-11K
	BOOL m_bHaveEMS61000_11K;
	CString m_strCOMEMS61000_11K;

	// 4.EMS61000-5A
	BOOL m_bHaveEMS61000_5A;
	CString m_strCOMEMS61000_5A;

	// 5.Gauge
	BOOL m_bHaveGauge;
	CString m_strCOMGauge;
	CArray<BYTE, BYTE> m_ucGaugeAddress;

	// 6.LED indicator ָʾ��
	BOOL m_bHaveLEDIndicator;
	CString m_strCOMLEDIndicator;
    CString m_strIndicatorRange;

	// 7.PF2010A
	BOOL m_bHavePF2010A;
	CString m_strCOMPF2010A;

	// 8.SC1000
	BOOL m_bHaveTestChannelController;
	CString m_strCOMTestChannelController;
	int m_iTestChannelControlerType;

	// 9.Temperature controller
	BOOL m_bHaveTemperatureContrller;
	CString m_strCOMTemperature;
	CArray<BYTE, BYTE> m_ucTemperatureAddress;

	// 10.WY
	BOOL m_bStandardSupply;
	CString m_strStandardSupplyCOM;
    int m_iStandardSupplyType;

	// 11.A90
	BOOL m_bHaveA90;

	// 12.LRA
	BOOL m_bHaveLRA;
	CString m_strLRACOM;

	// 13.Thunder relay
	BOOL m_bHaveThunderRelay;
	CString m_strThunderRelayCOM;

	// 14.Line controller
	BOOL m_bHaveLineController;
	CString m_strLineControllerCOM;

    // 15.Bribe  ����
    BOOL m_bBribe;
    CString m_strBribeCOM;
    CString m_strBribeRange;
	int		m_iBribeAddr;	//������ַ�� ���ݵ�
	int		m_iBribeAddr2;	//������ַ�� �չ��

    // 16 PFType
    int		m_iPFType;

    // 17 WYType
    int		m_iWYType;

    // Scaner ɨ������
    CString m_strScanerCOM;
    BOOL	m_bHaveScaner;
    CString m_strScanerBaudRate;
    CString m_strScanerRange;

    //��е��
	BOOL	m_bHaveHandAuto;
	CString m_strHandAutoCOM;
	CString m_strHandAutoBaudRate;
	CString m_strHandAutoRange1;
	CString m_strHandAutoRange2;

    // Range
    CString m_strCalibrationRange;  

    // Total Board
    UINT m_iTotalBoard;
    int m_iLEDTestAndLEDDownRange;
    int m_iLEDOnAndLEDTestRange;
	int m_iSpectialLEDOnAndLEDTestRange;
	int m_iJydzLedTestRange;	//��Ե���蹤λ�����Թ�ɫ�繤λ
	int m_iNyyLedTestRange;		//��ѹ�ǹ�λ�����Թ�ɫ�繤λ
	int m_iXldlLedTestRange;	//й¶������λ�����Թ�ɫ�繤λ

    // for 4A 
    BOOL m_bfor4A; //4m�߱�־
    CString m_strAgePowerCOM[2];

};

