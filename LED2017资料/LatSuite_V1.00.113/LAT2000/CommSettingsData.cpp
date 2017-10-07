#include "StdAfx.h"
#include "CommSettingsData.h"


CCommSettingsData::CCommSettingsData(void)
{
	// 2.DPS
	m_bHaveDPS				= TRUE;
	m_strCOMDPS				= "COM2";
    m_iDPSType				= DPS_1010;
	// 3.EMS61000-11K
	m_bHaveEMS61000_11K		= FALSE;
	m_strCOMEMS61000_11K	= "COM3";

	// 4.EMX61000-5A
	m_bHaveEMS61000_5A		= FALSE;
	m_strCOMEMS61000_5A		= "COM4";

	// 5.Gauge
	m_bHaveGauge			= TRUE;
	m_strCOMGauge			= "COM5";

	// 6.LED indicator
	m_bHaveLEDIndicator		= TRUE;
	m_strCOMLEDIndicator	= "COM6";

	// 7.PF2010A
	m_bHavePF2010A			= TRUE;
	m_strCOMPF2010A			= "COM7";

	// 8.SC1000
	m_bHaveTestChannelController	= TRUE;
	m_strCOMTestChannelController	= "COM8";

	// 9.Temperature controller
	m_bHaveTemperatureContrller = TRUE;
	m_strCOMTemperature			= "COM9";

	// 10.WY
	m_bStandardSupply		= TRUE;
	m_strStandardSupplyCOM	= "COM10";
    m_iStandardSupplyType	= 0;

	// 11.A90
	m_bHaveA90				= TRUE;;
	
	// 12.LRA
	m_bHaveLRA				= TRUE;
	m_strLRACOM				= "COM12";

	// 13.Thunder relay
	m_bHaveThunderRelay		= FALSE;
	m_strThunderRelayCOM	= "COM13";

	// 14.Line controller
	m_bHaveLineController	= TRUE;
	m_strLineControllerCOM	= "COM14";

    // 15.Bribe 
	m_bBribe				= FALSE;
    m_strBribeCOM			= "COM16";
    m_strBribeRange			= "3";
	m_iBribeAddr			= 0x01;
	m_iBribeAddr2			= 0x02;

    m_iWYType				= 1;
    m_strIndicatorRange		= "4";
    m_strCalibrationRange	= "8";

    m_iPFType				= 0;

    m_strScanerCOM				= _T("COM15");
    m_bHaveScaner				= 0;
    m_strScanerBaudRate			= _T("19200");
    m_strScanerRange			= _T("80");
    m_iLEDOnAndLEDTestRange		= 190;
    m_iLEDTestAndLEDDownRange	= 10;
    m_iTotalBoard					= 200;
	m_iSpectialLEDOnAndLEDTestRange = 90;

    m_strHandAutoCOM			= _T("COM16");
    m_bHaveHandAuto				= 0;
    m_strHandAutoBaudRate		= _T("9600");
    m_strHandAutoRange1			= _T("80");
	m_strHandAutoRange2			= _T("81");

    m_bfor4A					= FALSE;
    m_strAgePowerCOM[0]			= _T("COM15");
    m_strAgePowerCOM[1]			= _T("COM15");
	m_iTestChannelControlerType = 1;

	m_bHaveSaft_NYY		= FALSE;
	m_bHaveSaft_JYDZ	= FALSE;
	m_bHaveSaft_XLDL	= FALSE;
	m_iTypeSaftNyy		= 0;
	m_iTypeSaftJydz		= 0;
	m_iTypeSaftXLDL		= 0;
	m_strSaftNyyCOM		= "COM1";
	m_strSaftJydzCOM	= "COM1";
	m_strSaftXLDLCOM	= "COM1";
	m_strComNyy2		= "COM1";
	m_strComJydz2		= "COM1";
	m_strComXldl2		= "COM1";
	m_iMyLastPowerType	= 0;
	m_bHaveMyLast		= FALSE;
	m_strMyLastCOM		= "COM1";

}


CCommSettingsData::~CCommSettingsData(void)
{
}

int CCommSettingsData::GetIntegerCOM(CString strCOM)
{
	int iCOM = -1;
	strCOM.Trim();
	strCOM.MakeUpper();
	sscanf_s(strCOM.GetBuffer(), "COM%d", &iCOM);

	ASSERT(-1 != iCOM);

	return iCOM;
}


BOOL CCommSettingsData::WriteToFile(CString strPathName)
{
	CFile file;
	BOOL bR = file.Open(strPathName, CFile::modeWrite | CFile::modeCreate);
	if (!bR)
	{
		return FALSE;
	}

	CArchive ar(&file, CArchive::store);
	CString strEdition = "Communication Settings_V105";
	ar << strEdition;
	ar << m_bHaveA90;
	ar << m_bHaveDPS;
	ar << m_bHaveEMS61000_11K;

	ar << m_bHaveEMS61000_5A;
	ar << m_bHaveGauge;
	ar << m_bHaveLEDIndicator;
	ar << m_bHavePF2010A;
	ar << m_bHaveTestChannelController;

	ar << m_bHaveTemperatureContrller;
	ar << m_bStandardSupply;
	ar << m_bHaveLineController;
	ar << m_bHaveLRA;
	ar << m_bHaveThunderRelay;

	ar << m_strCOMDPS;
	ar << m_strCOMEMS61000_11K;
	ar << m_strCOMEMS61000_5A;
	ar << m_strCOMGauge;
	ar << m_iDPSType;

	ar << m_strCOMLEDIndicator;
	ar << m_strCOMPF2010A;
	ar << m_strCOMTestChannelController;
	ar << m_strCOMTemperature;
	ar << m_strStandardSupplyCOM;

	ar << m_strLineControllerCOM;
	ar << m_strLRACOM;
	ar << m_strThunderRelayCOM;
	ar << g_iGaugeNum;
	ar << g_iTMPControlNum;
    for (int i = 0; i < g_iGaugeNum; i++)
    {
        ar<<m_ucGaugeAddress[i];
    }

    for (int i = 0; i < g_iTMPControlNum; i++)
    {
        ar<<m_ucTemperatureAddress[i];
    }

    ar << m_strBribeCOM;
    ar << m_bBribe;
    ar << m_strBribeRange;

    ar << m_iWYType;
    ar << m_strIndicatorRange;
    ar << m_strCalibrationRange;

    ar << m_iPFType;
     
    ar << m_strScanerCOM;
    ar << m_bHaveScaner;
    ar << m_strScanerBaudRate;
    ar << m_strScanerRange;
    ar << m_iTotalBoard;    

    ar << m_bHaveHandAuto;
    ar << m_strHandAutoCOM;
    ar << m_strHandAutoBaudRate;
    ar << m_strHandAutoRange1;

    ar << m_iStandardSupplyType;

    ar << m_bfor4A;
    ar << m_strAgePowerCOM[0];
    ar << m_strAgePowerCOM[1];
    ar << m_iLEDTestAndLEDDownRange;
    ar << m_iLEDOnAndLEDTestRange;
	ar << m_iTestChannelControlerType;
	ar << m_iSpectialLEDOnAndLEDTestRange;

	ar << m_bHaveSaft_NYY;
	ar << m_bHaveSaft_JYDZ;
	ar << m_bHaveSaft_XLDL;
	ar << m_iTypeSaftNyy;
	ar << m_iTypeSaftJydz;
	ar << m_iTypeSaftXLDL;
	ar << m_strSaftNyyCOM;
	ar << m_strSaftJydzCOM;
	ar << m_strSaftXLDLCOM;

	ar << m_iMyLastPowerType;
	ar << m_bHaveMyLast;
	ar << m_strMyLastCOM;

	ar << m_strComNyy2; //控制器的串口
	ar << m_strComJydz2;
	ar << m_strComXldl2;

	ar << m_iJydzLedTestRange;	//绝缘电阻工位到测试光色电工位
	ar << m_iNyyLedTestRange;	//耐压仪工位到测试光色电工位
	ar << m_iXldlLedTestRange;	//泄露电流工位到测试光色电工位
	//2014.3.3 增加两路打点装置
	ar << m_iBribeAddr;
	ar << m_iBribeAddr2;
	//2014.4.30增加下灯机械手 和上灯有可能是同一个 为了位置
// 	ar << m_bHaveHandAuto2;
// 	ar << m_strHandAutoCOM2;
// 	ar << m_strHandAutoBaudRate2;
	ar << m_strHandAutoRange2;

	return TRUE;
}

void CCommSettingsData::InitWatchPaneSetting()
{
    m_ucGaugeAddress.SetSize(g_iGaugeNum);
    m_ucTemperatureAddress.SetSize(g_iTMPControlNum);
    for (int i = 0; i < g_iGaugeNum; i ++)
    {
        m_ucGaugeAddress[i] = i;
    }
    for (int i = 0; i < g_iTMPControlNum; i ++)
    {
        m_ucTemperatureAddress[i] = i;
    }
}

BOOL CCommSettingsData::ReadFromFile(CString strPathName)
{
    InitWatchPaneSetting();
	CFile file;
	BOOL bR = file.Open(strPathName, CFile::modeRead);
	if (!bR)
	{
		return FALSE;
	}
	int i;
	CArchive ar(&file, CArchive::load);
	CString strEdition;
	ar>>strEdition;
	if (	 "Communication Settings_B" != strEdition 
		  && "Communication Settings_C" != strEdition
          && "Communication Settings_D" != strEdition 
		  && "Communication Settings_E" != strEdition
          && "Communication Settings_F" != strEdition
		  && "Communication Settings_V100" != strEdition
		  && "Communication Settings_V101" != strEdition
		  && "Communication Settings_V102" != strEdition
		  && "Communication Settings_V103" != strEdition
		  && "Communication Settings_V104" != strEdition
		  && "Communication Settings_V105" != strEdition)
	{
		AfxMessageBox("文件格式错误!");
		return FALSE;
	}

	ar >> m_bHaveA90;
	ar >> m_bHaveDPS;
	ar >> m_bHaveEMS61000_11K;

	ar>>m_bHaveEMS61000_5A;
	ar>>m_bHaveGauge;
	ar>>m_bHaveLEDIndicator;
	ar>>m_bHavePF2010A;
	ar>>m_bHaveTestChannelController;

	ar>>m_bHaveTemperatureContrller;
	ar>>m_bStandardSupply;
	ar>>m_bHaveLineController;
	ar>>m_bHaveLRA;
	ar>>m_bHaveThunderRelay;

	ar>>m_strCOMDPS;
	ar>>m_strCOMEMS61000_11K;
	ar>>m_strCOMEMS61000_5A;
	ar>>m_strCOMGauge;
	ar>>m_iDPSType;

	ar>>m_strCOMLEDIndicator;
	ar>>m_strCOMPF2010A;
	ar>>m_strCOMTestChannelController;
	ar>>m_strCOMTemperature;
	ar>>m_strStandardSupplyCOM;

	ar>>m_strLineControllerCOM;
	ar>>m_strLRACOM;
	ar>>m_strThunderRelayCOM;

	int iTempGaugeNum;
	if (   "Communication Settings_B" != strEdition 
		&& "Communication Settings_C" != strEdition
		&& "Communication Settings_D" != strEdition 
		&& "Communication Settings_E" != strEdition
		&& "Communication Settings_F" != strEdition)
	{
		ar >> iTempGaugeNum;
	}
	else
	{
		iTempGaugeNum = g_iGaugeNum;
	}

	int iTempTMPNum;
	if (   "Communication Settings_B" != strEdition 
		&& "Communication Settings_C" != strEdition
		&& "Communication Settings_D" != strEdition 
		&& "Communication Settings_E" != strEdition
		&& "Communication Settings_F" != strEdition
		&& "Communication Settings_V100" != strEdition
		&& "Communication Settings_V101" != strEdition
		&& "Communication Settings_V102" != strEdition
		&& "Communication Settings_V103" != strEdition)
	{
		ar >> iTempTMPNum;

	}
	else
	{
		iTempTMPNum = g_iTMPControlNum;
	}
	BYTE bTemp;
   
	if(iTempGaugeNum < g_iGaugeNum)
	{
		for (i = 0; i < iTempGaugeNum; i++)
		{
			ar >> bTemp;
			m_ucGaugeAddress[i] = bTemp;
		}
		for (i = 0; i < g_iGaugeNum - iTempGaugeNum; i++)
		{
			m_ucGaugeAddress[i] = bTemp;
		}
	}
	else
	{
		m_ucGaugeAddress.SetSize(iTempGaugeNum);
		for (i = 0; i < iTempGaugeNum; i++)
		{
			ar >> bTemp;
			if(i < g_iGaugeNum)
			{
				m_ucGaugeAddress[i] = bTemp;
			}
		}
	}

	if (iTempTMPNum < g_iTMPControlNum)
	{
		for (i = 0; i < g_iTMPControlNum; i++)
		{
			if (i < iTempTMPNum)
			{
				ar >> bTemp;
				m_ucTemperatureAddress[i] = bTemp;
			}
			else
			{
				m_ucTemperatureAddress[i] = i;
			}
		}
	}
	else
	{
		m_ucTemperatureAddress.SetSize(iTempTMPNum);
		for (i = 0; i < iTempTMPNum; i++)
		{
			ar >> bTemp;
			m_ucTemperatureAddress[i] = bTemp;
		}
	}
    char cLastChar;
    cLastChar = strEdition.GetAt(strEdition.GetLength() - 1);
	if ("Communication Settings_B" != strEdition )
    {
        ar >> m_strBribeCOM;
        ar >> m_bBribe;
        ar >> m_strBribeRange;
    }
	if ("Communication Settings_B" != strEdition && "Communication Settings_C" != strEdition)
    {
        ar >> m_iWYType;
        ar >> m_strIndicatorRange;
        ar >> m_strCalibrationRange;
    }
	if (   "Communication Settings_B" != strEdition 
		&& "Communication Settings_C" != strEdition
		&& "Communication Settings_D" != strEdition) 
    {
        ar >> m_iPFType;
        ar >> m_strScanerCOM;
        ar >> m_bHaveScaner;
        ar >> m_strScanerBaudRate;
        ar >> m_strScanerRange;
        ar >> m_iTotalBoard;
        ar >> m_bHaveHandAuto;
        ar >> m_strHandAutoCOM;
        ar >> m_strHandAutoBaudRate;
        ar >> m_strHandAutoRange1;
    }
	if (   "Communication Settings_B" != strEdition 
		&& "Communication Settings_C" != strEdition
		&& "Communication Settings_D" != strEdition 
		&& "Communication Settings_E" != strEdition)
    {
        ar >> m_iStandardSupplyType;
        ar >> m_bfor4A;
        ar >> m_strAgePowerCOM[0];
        ar >> m_strAgePowerCOM[1];
        ar >> m_iLEDTestAndLEDDownRange;
        ar >> m_iLEDOnAndLEDTestRange;
		ar >> m_iTestChannelControlerType;
		ar >> m_iSpectialLEDOnAndLEDTestRange;
	}

	if (   "Communication Settings_B" != strEdition 
		&& "Communication Settings_C" != strEdition
		&& "Communication Settings_D" != strEdition 
		&& "Communication Settings_E" != strEdition
		&& "Communication Settings_F" != strEdition)
	{
		ar >> m_bHaveSaft_NYY;
		ar >> m_bHaveSaft_JYDZ;
		ar >> m_bHaveSaft_XLDL;
		ar >> m_iTypeSaftNyy;
		ar >> m_iTypeSaftJydz;
		ar >> m_iTypeSaftXLDL;
		ar >> m_strSaftNyyCOM;
		ar >> m_strSaftJydzCOM;
		ar >> m_strSaftXLDLCOM;

		ar >> m_iMyLastPowerType;
		ar >> m_bHaveMyLast;
		ar >> m_strMyLastCOM;
	}
	else
	{
		m_bHaveSaft_NYY		= FALSE;
		m_bHaveSaft_JYDZ	= FALSE;
		m_bHaveSaft_XLDL	= FALSE;
		m_iTypeSaftNyy		= 0;
		m_iTypeSaftJydz		= 0;
		m_iTypeSaftXLDL		= 0;
		m_strSaftNyyCOM		= "COM1";
		m_strSaftJydzCOM	= "COM1";
		m_strSaftXLDLCOM	= "COM1";

		m_iMyLastPowerType	= 0;
		m_bHaveMyLast		= FALSE;
		m_strMyLastCOM		= "COM1";
	}

	if (   "Communication Settings_B" != strEdition 
		&& "Communication Settings_C" != strEdition
		&& "Communication Settings_D" != strEdition 
		&& "Communication Settings_E" != strEdition
		&& "Communication Settings_F" != strEdition
		&& "Communication Settings_V100" != strEdition)
	{
		ar >> m_strComNyy2; //控制器的串口
		ar >> m_strComJydz2;
		ar >> m_strComXldl2;
	}
	else
	{
		m_strComNyy2  = "COM1"; //控制器的串口
		m_strComJydz2 = "COM1";
		m_strComXldl2 = "COM1";
	}

	if (   "Communication Settings_B" != strEdition 
		&& "Communication Settings_C" != strEdition
		&& "Communication Settings_D" != strEdition 
		&& "Communication Settings_E" != strEdition
		&& "Communication Settings_F" != strEdition
		&& "Communication Settings_V100" != strEdition
		&& "Communication Settings_V101" != strEdition)
	{
		ar >> m_iJydzLedTestRange;	//绝缘电阻工位到测试光色电工位
		ar >> m_iNyyLedTestRange;	//耐压仪工位到测试光色电工位
		ar >> m_iXldlLedTestRange;	//泄露电流工位到测试光色电工位
	}
	else
	{
		m_iJydzLedTestRange = 10;
		m_iNyyLedTestRange  = 8;
		m_iXldlLedTestRange = 9;
	}

	if (   "Communication Settings_B" != strEdition 
		&& "Communication Settings_C" != strEdition
		&& "Communication Settings_D" != strEdition 
		&& "Communication Settings_E" != strEdition
		&& "Communication Settings_F" != strEdition
		&& "Communication Settings_V100" != strEdition
		&& "Communication Settings_V101" != strEdition
		&& "Communication Settings_V102" != strEdition)
	{
		ar >> m_iBribeAddr;
		ar >> m_iBribeAddr2;
	}
	else
	{
		m_iBribeAddr  = 0xCF;
		m_iBribeAddr2 = 0xCF;
	}

	//2014.4.30增加下灯机械手 和上灯有可能是同一个 为了位置
	if (   "Communication Settings_B" != strEdition 
		&& "Communication Settings_C" != strEdition
		&& "Communication Settings_D" != strEdition 
		&& "Communication Settings_E" != strEdition
		&& "Communication Settings_F" != strEdition
		&& "Communication Settings_V100" != strEdition
		&& "Communication Settings_V101" != strEdition
		&& "Communication Settings_V102" != strEdition
		&& "Communication Settings_V103" != strEdition
		&& "Communication Settings_V104" != strEdition)
	{
// 		ar >> m_bHaveHandAuto2;
// 		ar >> m_strHandAutoCOM2;
// 		ar >> m_strHandAutoBaudRate2;
		ar >> m_strHandAutoRange2;
	}
	return TRUE;
}

