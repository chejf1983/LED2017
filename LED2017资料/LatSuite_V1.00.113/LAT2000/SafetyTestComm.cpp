#include "StdAfx.h"
#include "SafetyTestComm.h"
#include "Serial.h"
//#include "DlgSaftyLCExaminationSet.h"
//#include "DlgSaftyIRExaminationSet.h"
//#include "DlgSaftyVoltageWithStandExaminationSet.h"

extern BOOL g_bDemo;

CSafetyTest_CSComm2676::CSafetyTest_CSComm2676(void)
{
	m_iMode = IR;
	m_strCOM = "COM1";
	m_iBaudrate = 9600;
	SetTestType(IR);

	m_bHaveInit_CS = FALSE;
}


CSafetyTest_CSComm2676::~CSafetyTest_CSComm2676(void)
{

}

void CSafetyTest_CSComm2676::Initialize(CString strCOM, int iBaudRate)
{
    m_strCOM = strCOM;
    m_iBaudrate = iBaudRate;
}

BOOL CSafetyTest_CSComm2676::SetConstructAddress(int ucAdress)
{
	if(!m_bHaveInit_CS)
	{
		CString strSerialcmd;
		strSerialcmd.Format(_T("COMMunication:SADDress %03d"), ucAdress);
		BOOL bR;
		bR = SetCommandCode(strSerialcmd);
		if(bR)
		{
			m_bHaveInit_CS = TRUE;
		}
		return bR;
	}
	return TRUE;
}

BOOL CSafetyTest_CSComm2676::SetRemote()
{
	BOOL bR;
	bR = SetCommandCode("COMMunication:REMote");
    return bR;
}

BOOL CSafetyTest_CSComm2676::SetLocal()
{
	BOOL bR;
	bR = SetCommandCode("COMMunication:LOCal");
	if(bR)
		m_bHaveInit_CS = FALSE;
    return bR;
}

// Test Start
BOOL CSafetyTest_CSComm2676::SetTestStart()
{

    return SetCommandCode("SOURce:TEST:STARt");
}


BOOL CSafetyTest_CSComm2676::SetTestStop()
{
	SetLocal();
    return SetCommandCode("SOURce:TEST:STOP");
}

void CSafetyTest_CSComm2676::SetTestType(int imode)
{
    m_iMode = imode;
}

BOOL CSafetyTest_CSComm2676::SetTestVoltage_V(float fVlotage)
{
    CString strSerialcmd;
    if (m_iMode == IR)
    {
        if (fVlotage <= 1000.0)
        {
            strSerialcmd.Format(_T("STEP:IR:VOLTage %.0f V"), fVlotage);
        }
        else
        {
            strSerialcmd.Format(_T("STEP:IR:VOLTage %.0f kV"), fVlotage / 1000);
        }
    }
    else
    {
        if (fVlotage <= 1000.0)
        {
            strSerialcmd.Format(_T("STEP:LC:VOLTage %f V"), fVlotage);
        }
        else
        {
            strSerialcmd.Format(_T("STEP:LC:VOLTage %f kV"), fVlotage / 1000);
        }
    }

    return SetCommandCode(strSerialcmd);
}

BOOL CSafetyTest_CSComm2676::SetAlarmValue_High(float fValue)
{
    CString strSerialcmd;
    if (m_iMode == IR)
    {
        strSerialcmd.Format(_T("STEP:IR:HIGH %f Mohm"), fValue);
    }
    else
    {
        strSerialcmd.Format(_T("STEP:LC:HIGH %f mA"), fValue);
    }
    return SetCommandCode(strSerialcmd);
}

BOOL CSafetyTest_CSComm2676::SetAlarmValue_Low(float fValue)
{
    CString strSerialcmd;
    if (m_iMode == IR)
    {
        strSerialcmd.Format(_T("STEP:IR:LOW %f Mohm"), fValue);
    }
    else
    {
        strSerialcmd.Format(_T("STEP:LC:LOW %f mA"), fValue);
    }
    return SetCommandCode(strSerialcmd);
}

BOOL CSafetyTest_CSComm2676::SetTestTime_s(float fTime)
{
    CString strSerialcmd;
    if (m_iMode == IR)
    {
        strSerialcmd.Format(_T("STEP:IR:TTIMe %f s"), fTime);
    }
    else
    {
        strSerialcmd.Format(_T("STEP:LC:TTIMe %f s"), fTime);
    }
    return SetCommandCode(strSerialcmd);
}

BOOL CSafetyTest_CSComm2676::SetDelayJudgeTime_s(float fTime)
{
    CString strSerialcmd;
    if (m_iMode == IR)
    {
        strSerialcmd.Format(_T("STEP:IR:DTIMe %f s"), fTime);
    }
    else
    {
        strSerialcmd.Format(_T("STEP:LC:DTIMe %f s"), fTime);
    }
    return SetCommandCode(strSerialcmd);
}

BOOL CSafetyTest_CSComm2676::SetInterTestTime_s(float fTime)
{
    CString strSerialcmd;
    if (m_iMode == IR)
    {
        strSerialcmd.Format(_T("STEP:IR:ITIMe %f s"), fTime);
    }
    else
    {
        strSerialcmd.Format(_T("STEP:LC:ITIMe %f s"), fTime);
    }
    return SetCommandCode(strSerialcmd);
}

BOOL CSafetyTest_CSComm2676::SetFailedTestTime_s(float fTime)
{
    CString strSerialcmd;
    if (m_iMode == IR)
    {
        strSerialcmd.Format(_T("STEP:IR:FTIMe %f s"), fTime);
    }
    else
    {
        strSerialcmd.Format(_T("STEP:LC:FTIMe %f s"), fTime);
    }
    return SetCommandCode(strSerialcmd);
}

BOOL CSafetyTest_CSComm2676::GetTestStatus(VoltageWithstandTesterStatus &status)
{

    Serial ser;
    HANDLE handle;
    if (!ser.Open(handle, m_strCOM, m_iBaudrate))
    {
        return FALSE;
    }
    ser.SetReadTime(handle, 2000, 1, 2000);
    CString strTemp;
    int i;
    BYTE byteCMD[256];
    BYTE byteSumCheck = 0;
    CString strSerialcmd = "SOURce:TEST:STATus?";
    int iCheckoutNum = 0;
    BYTE byteCheckout;
    for (i = 0; i < strSerialcmd.GetLength(); i++)
    {
        if (i == 0)
        {
            byteCheckout = (BYTE)strSerialcmd.GetAt(i);
            iCheckoutNum ++;
        }
        else
        {
            if (byteCheckout == (BYTE)strSerialcmd.GetAt(i))
            {
                iCheckoutNum ++;
            }
        }
        byteCMD[i]= (BYTE)strSerialcmd.GetAt(i);
        byteSumCheck += byteCMD[i]; 
    }

	byteCMD[i] = byteSumCheck|0x80;
	byteCMD[i + 1] = 0x0D;
    byteCMD[i + 2] = 0x0A;
    ser.Output(handle, byteCMD, i + 3);
    // Receive Code 

    return TRUE;
}

BOOL CSafetyTest_CSComm2676::GetTestData(float &fValue)
{
    Serial ser;
    HANDLE handle;
    if (!ser.Open(handle, m_strCOM, m_iBaudrate))
    {
        return FALSE;
    }
    ser.SetReadTime(handle, 2000, 1, 2000);
    CString strTemp;
    int i;
    BYTE byteCMD[256];
    BYTE byteSumCheck = 0;
    CString strSerialcmd = "SOURce:TEST:FETCh?";
    int iCheckoutNum = 0;
    BYTE byteCheckout;
    for (i = 0; i < strSerialcmd.GetLength(); i++)
    {
        if (i == 0)
        {
            byteCheckout = (BYTE)strSerialcmd.GetAt(i);
            iCheckoutNum ++;
        }
        else
        {
            if (byteCheckout == (BYTE)strSerialcmd.GetAt(i))
            {
                iCheckoutNum ++;
            }
        }
        byteCMD[i]= (BYTE)strSerialcmd.GetAt(i);
        byteSumCheck += byteCMD[i]; 
    }
    if (iCheckoutNum % 2 == 0)
    {
        byteCMD[i] = byteSumCheck;
    }
    else
    {
        byteCMD[i] = byteSumCheck + 0x80;
    }
    byteCMD[i + 1] = 0x0D;
    byteCMD[i + 2] = 0x0A;
    ser.Output(handle, byteCMD, i + 3);
    // Receive Code 
    DWORD dwTime = GetCurrentTime();
    BYTE bb[1];
    int iErrN = 0;
    CString strReturn = "";
    while(GetCurrentTime() - dwTime <= 5000)
    {
        if (!ser.Input(handle, bb, 1))
        {
            iErrN ++;
            if(iErrN >= 3)
            {
                ser.Close(handle);
                return FALSE;
            }
        }
        strReturn += bb[0]; 
        if (bb[0] == '\n')
        {  
            break;
        }
    }
    int iIndex = 0;
    iIndex = strReturn.Find("V,", iIndex);
    CString strValue;
    if (-1 == iIndex)
    {
        return FALSE;
    }
    else
    {
       strValue = strReturn.Mid(iIndex, 12);
       sscanf_s(strValue, "V,%f", &fValue);

    }
    return TRUE;
}

BOOL CSafetyTest_CSComm2676::SetCommandCode(CString strSerialcmd)
{
    Serial ser;
    HANDLE handle;
    if (!ser.Open(handle, m_strCOM, m_iBaudrate))
    {
        return FALSE;
    }
    ser.SetReadTime(handle, 2000, 1, 2000);
    CString strTemp;
    int i;
    BYTE byteCMD[256];
    BYTE byteIn[256];
    BYTE byteSumCheck = 0;
      for (i = 0; i < strSerialcmd.GetLength(); i++)
    {
        byteCMD[i]= (BYTE)strSerialcmd.GetAt(i);
        byteSumCheck += byteCMD[i]; 
    }
    byteCMD[i] = byteSumCheck|0x80;

	byteCMD[i + 1] = 0x0D;
    byteCMD[i + 2] = 0x0A;
    ser.Output(handle, byteCMD, i + 3);
    // Receive Code
	BYTE bPerIn = 0x00;
	BYTE bCurIn = 0x00;
	BYTE bTempIn[1];
	bTempIn[0] = 0x00;
	int iNum = 0;
	while (1)
	{
		bPerIn = bTempIn[0];
		if (!ser.Input(handle, bTempIn, 1))
		{
			ser.Close(handle);
			return FALSE;
		}
		byteIn[iNum++] = bTempIn[0];
		bCurIn = bTempIn[0];
		if(bPerIn == 0x0D && bCurIn == 0x0A)
		{
			break;
		}
	}

    if (byteIn[0] == 0x2D)
    {
		ser.Close(handle);
		return FALSE;
    }
	ser.Close(handle);
	return TRUE;
}

void CSafetyTest_CSComm2676::ShowTestSetDlg()
{
//    CDlgSaftyLCExaminationSet dlg;
 //   dlg.DoModal();
}
BOOL CSafetyTest_CSComm2676::SetAndTest(int iSelIndex)
{
    SetFunctionPara para;
    if (iSelIndex > m_paraArray.GetSize() - 1 || iSelIndex < 0)
    {

    }
    else
    {
        para = m_paraArray.GetAt(iSelIndex);
    }
    if (!SetRemote())
    {
        return FALSE;
    }
    if (!SetTestVoltage_V(para.fTestOverVoltage_V))
    {
        return FALSE;
    }
    if (!SetAlarmValue_High(para.fAlarmHigh))
    {
        return FALSE;
    }
    if (!SetAlarmValue_Low(para.fAlarmLow))
    {
        return FALSE;
    }
    if (!SetTestTime_s(para.fTestTime_s))
    {
        return FALSE;
    }
    if (!SetDelayJudgeTime_s(para.fDelayJudge_s))
    {
        return FALSE;
    }
    if (!SetInterTestTime_s(para.fInterTestTime_s))
    {
        return FALSE;
    }
    if (!SetFailedTestTime_s(para.SetfailedTestTime_s))
    {
        return FALSE;
    }
    if (!SetTestStart())
    {
        return FALSE;
    }
    return TRUE;
}
BOOL CSafetyTest_CSComm2676::GetValue(float &fValue)
{
     if (!GetTestData(fValue))
     {
         return FALSE;
     }
     return TRUE;
}

BOOL CSafetyTest_CSComm2676::SaveFile(CString strPathName)
{
    CFile file;
    if (!file.Open(strPathName, CFile::modeWrite | CFile::modeCreate))
    {
        return FALSE;
    }

    CArchive ar(&file, CArchive::store);
    if (!Serialize(ar))
    {
        ar.Close();
        file.Close();
        return FALSE;
    }

    ar.Close();
    file.Close();

    return TRUE;
}
BOOL CSafetyTest_CSComm2676::LoadFile(CString strPathName)
{
    CFile file;
    if (!file.Open(strPathName, CFile::modeRead))
    {
        return FALSE;
    }

    CArchive ar(&file, CArchive::load);
    if (!Serialize(ar))
    {
        ar.Close();
        file.Close();
        return FALSE;
    }

    ar.Close();
    file.Close();

    return TRUE;
}
BOOL CSafetyTest_CSComm2676::Serialize(CArchive & ar)
{
    CString strDev;
    if (ar.IsStoring())
    {
        strDev = "SafetyTest_ChangShengComm";
        ar << strDev;
        ar << m_paraArray.GetSize();
        for (int i = 0; i < m_paraArray.GetSize(); i++)
        {
            m_paraArray.GetAt(i).Serialize(ar);
        }
    }
    else
    {
        ar >> strDev;
        if (strDev != "SafetyTest_ChangShengComm")
        {
            return FALSE;
        }
        int iN;
        ar >> iN;
        m_paraArray.RemoveAll();
        for (int i = 0; i < iN; i++)
        {
            SetFunctionPara para;
            para.Serialize(ar);
            m_paraArray.Add(para);
        }
    }
   return TRUE;
}

BOOL CSafetyTest_CSComm2676::CS_Init_IR(CString strCOM)
{
	//初始化 设置地址 并进入远程模式
	Initialize(strCOM);
	BOOL bR;
	SetLocal();
	bR = SetConstructAddress(1);
	if(!bR)
		return FALSE;
	bR = SetRemote();
	if(!bR)
		return FALSE;
	return TRUE;
}

BOOL CSafetyTest_CSComm2676::CS_Setup_IR(float fVol,float fTime)
{
	if(g_bDemo)
	{
		return TRUE;
	}
	//设置电压和时间
	BOOL bR;
	bR = SetTestVoltage_V(fVol);
	if(!bR)
		return FALSE;

	bR = SetTestTime_s(fTime);
	if(!bR)
		return FALSE;
	return TRUE;

}

BOOL CSafetyTest_CSComm2676::CS_Test_IR(BOOL bTest)
{
	BOOL bR;
	if(bTest)
		bR = SetTestStart();
	else
		bR = SetTestStop();
	if(!bR)
		return FALSE;

	return TRUE;
}

BOOL CSafetyTest_CSComm2676::CS_GetData_IR(float &fIR)
{
	if(g_bDemo)
	{
		fIR = 500;
		return TRUE;
	}
	BOOL bR;
	bR = GetTestData(fIR);
	if(!bR)
		return FALSE;
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
//长盛耐压仪设置
CSafetyTest_CSComm9912::CSafetyTest_CSComm9912()
{
	m_strCOM = "COM1";
	m_iBaudrate = 9600;
	m_bAD = 0xA2;
}

CSafetyTest_CSComm9912::~CSafetyTest_CSComm9912()
{

}

BOOL CSafetyTest_CSComm9912::CS_Init_NYY(CString strCOM)
{
	if(g_bDemo)
	{
		return TRUE;
	}
	//不停止不能重新开始测试 会通讯失败
	//初始化 设置地址 并进入远程模式
	m_strCOM = strCOM;

	Serial ser;
	HANDLE handle;
	if (!ser.Open(handle, m_strCOM, m_iBaudrate))
	{
		return FALSE;
	}
	ser.SetAd(handle,m_bAD,FALSE);
	ser.SetReadTime(handle, 2000, 1, 2000);
	CString strTemp;
	int i,iN = 0;
	BYTE bOut[256];
	BYTE bIn[256];
	bOut[iN] = 0xAA;
	iN++;
	bOut[iN] = 0x55;
	iN++;
	bOut[iN] = 0x01; //联机命令
	iN++;

	for (i = 0; i< 29; i++)
	{
		bOut[iN] = 0x00;
		iN++;
	}
	bOut[iN] = 0x00;
	for (i = 0; i < iN; i++)
	{
		bOut[iN] = (BYTE)(bOut[i] + bOut[iN]);
	}
	iN++;
	ser.Output(handle, bOut, iN);
	// Receive Code
	if (!ser.Input(handle, bIn, 39))
	{
		ser.Close(handle);
		return FALSE;
	}
	ser.Close(handle);
	if (bIn[2] != bOut[2] + 0x10)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CSafetyTest_CSComm9912::CS_Setup_NYY(int iType, float fVol,float fTime,float fLimit)
{
	//不停止不能重新开始测试 会通讯失败
	//设置电压和时间 iType == 0 AC; == 1 DC
	Serial ser;
	CString strTemp;
	int i,iN = 0;

	HANDLE handle;
	if (!ser.Open(handle, m_strCOM, m_iBaudrate))
	{
		return FALSE;
	}
	ser.SetAd(handle,m_bAD,FALSE);
	ser.SetReadTime(handle, 2000, 1, 2000);
	BYTE bOut[256];
	BYTE bIn[256];
	bOut[iN] = 0xAA;
	iN++;
	bOut[iN] = 0x55;
	iN++;
	bOut[iN] = 0x07; //设置命令
	iN++;
	bOut[iN] = 0x01; //记忆组为第一组
	iN++;
	if(iType == 0)
		bOut[iN] = 0x00; //测试模式为直流
	else
		bOut[iN] = 0x01; //测试模式为直流
	iN++;
	bOut[iN] = 0x00; //蜂鸣器设置
	iN++;
	if(iType == 0)
	{
		bOut[iN] = 0x01; //交流步数为1
		iN++;
		bOut[iN] = 0x00; //直流步数为0
		iN++;
	}
	else
	{
		bOut[iN] = 0x00; //交流步数为0
		iN++;
		bOut[iN] = 0x01; //直流步数为1
		iN++;
	}
	for (i = 0; i< 24; i++)
	{
		bOut[iN] = 0x00;
		iN++;
	}
	bOut[iN] = 0x00;
	for (i = 0; i < iN; i++)
	{
		bOut[iN] = (BYTE)(bOut[i] + bOut[iN]);
	}
	iN++;
	ser.Output(handle, bOut, iN);
	// Receive Code
	if (!ser.Input(handle, bIn, 39))
	{
		ser.Close(handle);
		return FALSE;
	}

	if (bIn[2] != bOut[2] + 0x10)
	{
		ser.Close(handle);
		return FALSE;
	}

	//设置电压电流
	iN = 0;
	bOut[iN] = 0xAA;
	iN++;
	bOut[iN] = 0x55;
	iN++;
	if(iType == 0)
		bOut[iN] = 0x08; //设置AC参数命令
	else
		bOut[iN] = 0x09; //设置DC参数命令
	iN++;
	bOut[iN] = 0x01; //第一步
	iN++;
	int iVol = (int)(fVol);
	bOut[iN] = iVol / 256; //电压高位
	iN++;
	bOut[iN] = iVol; //电压低位
	iN++;
	int iCurrLimitH;
	if(iType == 0)
		iCurrLimitH = (int)(fLimit*100);
	else
		iCurrLimitH = (int)(fLimit*1000);
	bOut[iN] = iCurrLimitH / 256; //电流上限高位
	iN++;
	bOut[iN] = iCurrLimitH; //电流上限低位
	iN++;

	int iCurrLimitL = 0;
	bOut[iN] = iCurrLimitL / 256; //电流上限高位
	iN++;
	bOut[iN] = iCurrLimitL; //电流上限低位
	iN++;
	//上升时间
	bOut[iN] = 0x00;
	iN++;
	bOut[iN] = 0x00;
	iN++;

	int iTime = (int)(fTime * 10);
	bOut[iN] = iTime / 256; //测试时间高位
	iN++;
	bOut[iN] = iTime; //测试时间低位
	iN++;
	//下降时间
	bOut[iN] = 0x00;
	iN++;
	bOut[iN] = 0x00;
	iN++;
	//间隔时间
	bOut[iN] = 0x00;
	iN++;
	bOut[iN] = 0x00;
	iN++;
	//电弧侦测
	bOut[iN] = 0x00;
	iN++;
	bOut[iN] = 0x00;
	iN++;
	//电弧侦测时间
	bOut[iN] = 0x00;
	iN++;
	bOut[iN] = 0x00;
	iN++;

	for (i = 0; i< 10; i++)
	{
		bOut[iN] = 0x00;
		iN++;
	}

	bOut[iN] = 0x00;
	for (i = 0; i < iN; i++)
	{
		bOut[iN] = (BYTE)(bOut[i] + bOut[iN]);
	}
	iN++;
	ser.SetAd(handle,m_bAD,FALSE);
	ser.Output(handle, bOut, iN);
	// Receive Code
	if (!ser.Input(handle, bIn, 39))
	{
		ser.Close(handle);
		return FALSE;
	}
	ser.Close(handle);
	if (bIn[2] != bOut[2] + 0x10)
	{
		return FALSE;
	}

	return TRUE;

}

BOOL CSafetyTest_CSComm9912::CS_Test_NYY(BOOL bTest)
{
	//不停止不能重新开始测试 会通讯失败
	Serial ser;
	HANDLE handle;
	if (!ser.Open(handle, m_strCOM, m_iBaudrate))
	{
		return FALSE;
	}
	ser.SetAd(handle,m_bAD,FALSE);
	ser.SetReadTime(handle, 2000, 1, 2000);
	CString strTemp;
	int i,iN = 0;
	BYTE bOut[256];
	BYTE bIn[256];
	bOut[iN] = 0xAA;
	iN++;
	bOut[iN] = 0x55;
	iN++;
	if(bTest)
		bOut[iN] = 0x0B; //开始测试命令
	else
		bOut[iN] = 0x0C; //停止测试命令
	iN++;

	for (i = 0; i< 29; i++)
	{
		bOut[iN] = 0x00;
		iN++;
	}
	bOut[iN] = 0x00;
	for (i = 0; i < iN; i++)
	{
		bOut[iN] = (BYTE)(bOut[i] + bOut[iN]);
	}
	iN++;
	ser.Output(handle, bOut, iN);
	// Receive Code
	if (!ser.Input(handle, bIn, 39))
	{
		ser.Close(handle);
		return FALSE;
	}
	ser.Close(handle);
	if (bIn[2] != bOut[2] + 0x10)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSafetyTest_CSComm9912::CS_GetData_NYY(int iType,BOOL &bOK, float &fIR)
{
	if(g_bDemo)
	{
		return TRUE;
	}
	//必须要启动测试才能读取数据
	Serial ser;
	HANDLE handle;
	if (!ser.Open(handle, m_strCOM, m_iBaudrate))
	{
		return FALSE;
	}
	ser.SetAd(handle,m_bAD,FALSE);
	ser.SetReadTime(handle, 2000, 1, 2000);
	CString strTemp;
	int i,iN = 0;
	BYTE bOut[256];
	BYTE bIn[256];
	bOut[iN] = 0xAA;
	iN++;
	bOut[iN] = 0x55;
	iN++;
	bOut[iN] = 0x0D; //读取数据命令
	iN++;

	for (i = 0; i< 29; i++)
	{
		bOut[iN] = 0x00;
		iN++;
	}
	bOut[iN] = 0x00;
	for (i = 0; i < iN; i++)
	{
		bOut[iN] = (BYTE)(bOut[i] + bOut[iN]);
	}
	iN++;
	ser.Output(handle, bOut, iN);
	// Receive Code
	if (!ser.Input(handle, bIn, 39))
	{
		ser.Close(handle);
		return FALSE;
	}
	ser.Close(handle);
	if (bIn[2] != bOut[2] + 0x10)
	{
		return FALSE;
	}
	if(bIn[5] != 0x00)
		bOK = TRUE;
	else
		bOK = FALSE;
	if(iType == 0) //交流和直流的数据结果不一样
		fIR = (float)(bIn[8] * 256 + bIn[9])/100.0f; //转化为mA
	else
		fIR = (float)(bIn[8] * 256 + bIn[9])/1000.0f; //转化为mA
	if(fIR < 0)
		fIR = 0;
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
//长盛耐压仪设置
CSafetyTest_CSComm5505::CSafetyTest_CSComm5505(void)
{
	m_strCOM = "COM1";
	m_iBaudrate = 9600;

	m_bHaveInit_CS = FALSE;
}


CSafetyTest_CSComm5505::~CSafetyTest_CSComm5505(void)
{

}

void CSafetyTest_CSComm5505::Initialize(CString strCOM, int iBaudRate)
{
	m_strCOM = strCOM;
	m_iBaudrate = iBaudRate;
}

BOOL CSafetyTest_CSComm5505::SetConstructAddress(int ucAdress)
{
	if(!m_bHaveInit_CS)
	{
		CString strSerialcmd;
		strSerialcmd.Format(_T("COMMunication:SADDress %03d"), ucAdress);
		BOOL bR;
		bR = SetCommandCode(strSerialcmd);
		if(bR)
		{
			m_bHaveInit_CS = TRUE;
		}
		return bR;
	}
	return TRUE;
}

BOOL CSafetyTest_CSComm5505::SetRemote()
{
	BOOL bR;
	bR = SetCommandCode("COMMunication:REMote");
	return bR;
}

BOOL CSafetyTest_CSComm5505::SetLocal()
{
	BOOL bR;
	bR = SetCommandCode("COMMunication:LOCal");
	if(bR)
		m_bHaveInit_CS = FALSE;
	return bR;
}

// Test Start
BOOL CSafetyTest_CSComm5505::SetTestStart()
{
	return SetCommandCode("SOURce:TEST:STARt");
}

BOOL CSafetyTest_CSComm5505::SetTestStop()
{
	return SetCommandCode("SOURce:TEST:STOP");
}

BOOL CSafetyTest_CSComm5505::SetTestVoltage_V(float fVlotage)
{
	CString strSerialcmd;
	if (fVlotage <= 1000.0)
	{
		strSerialcmd.Format(_T("STEP:LC:VOLTage %f V"), fVlotage);
	}
	else
	{
		strSerialcmd.Format(_T("STEP:LC:VOLTage %f kV"), fVlotage / 1000);
	}

	return SetCommandCode(strSerialcmd);
}

BOOL CSafetyTest_CSComm5505::SetAlarmValue_High(float fValue)
{
	CString strSerialcmd;
	strSerialcmd.Format(_T("STEP:LC:HIGH %f mA"), fValue);
	return SetCommandCode(strSerialcmd);
}

BOOL CSafetyTest_CSComm5505::SetAlarmValue_Low(float fValue)
{
	CString strSerialcmd;
	strSerialcmd.Format(_T("STEP:LC:LOW %f mA"), fValue);
	return SetCommandCode(strSerialcmd);
}

BOOL CSafetyTest_CSComm5505::SetTestTime_s(float fTime)
{
	CString strSerialcmd;
	strSerialcmd.Format(_T("STEP:LC:TTIMe %f s"), fTime);
	return SetCommandCode(strSerialcmd);
}

BOOL CSafetyTest_CSComm5505::SetDelayJudgeTime_s(float fTime)
{
	CString strSerialcmd;
	strSerialcmd.Format(_T("STEP:LC:DTIMe %f s"), fTime);

	return SetCommandCode(strSerialcmd);
}

BOOL CSafetyTest_CSComm5505::SetInterTestTime_s(float fTime)
{
	CString strSerialcmd;
	strSerialcmd.Format(_T("STEP:LC:ITIMe %f s"), fTime);
	return SetCommandCode(strSerialcmd);
}

BOOL CSafetyTest_CSComm5505::SetFailedTestTime_s(float fTime)
{
	CString strSerialcmd;
	strSerialcmd.Format(_T("STEP:LC:FTIMe %f s"), fTime);

	return SetCommandCode(strSerialcmd);
}

BOOL CSafetyTest_CSComm5505::GetTestStatus(VoltageWithstandTesterStatus &status)
{

	Serial ser;
	HANDLE handle;
	if (!ser.Open(handle, m_strCOM, m_iBaudrate))
	{
		return FALSE;
	}
	ser.SetReadTime(handle, 2000, 1, 2000);
	CString strTemp;
	int i;
	BYTE byteCMD[256];
	BYTE byteSumCheck = 0;
	CString strSerialcmd = "SOURce:TEST:STATus?";
	int iCheckoutNum = 0;
	BYTE byteCheckout;
	for (i = 0; i < strSerialcmd.GetLength(); i++)
	{
		if (i == 0)
		{
			byteCheckout = (BYTE)strSerialcmd.GetAt(i);
			iCheckoutNum ++;
		}
		else
		{
			if (byteCheckout == (BYTE)strSerialcmd.GetAt(i))
			{
				iCheckoutNum ++;
			}
		}
		byteCMD[i]= (BYTE)strSerialcmd.GetAt(i);
		byteSumCheck += byteCMD[i]; 
	}

	byteCMD[i] = byteSumCheck|0x80;
	byteCMD[i + 1] = 0x0D;
	byteCMD[i + 2] = 0x0A;
	ser.Output(handle, byteCMD, i + 3);
	// Receive Code 

	return TRUE;
}

BOOL CSafetyTest_CSComm5505::GetTestData(float &fValue)
{
	Serial ser;
	HANDLE handle;
	if (!ser.Open(handle, m_strCOM, m_iBaudrate))
	{
		return FALSE;
	}
	ser.SetReadTime(handle, 2000, 1, 2000);
	CString strTemp;
	int i;
	BYTE byteCMD[256];
	BYTE byteSumCheck = 0;
	CString strSerialcmd = "SOURce:TEST:FETCh?";
	int iCheckoutNum = 0;
	BYTE byteCheckout;
	for (i = 0; i < strSerialcmd.GetLength(); i++)
	{
		if (i == 0)
		{
			byteCheckout = (BYTE)strSerialcmd.GetAt(i);
			iCheckoutNum ++;
		}
		else
		{
			if (byteCheckout == (BYTE)strSerialcmd.GetAt(i))
			{
				iCheckoutNum ++;
			}
		}
		byteCMD[i]= (BYTE)strSerialcmd.GetAt(i);
		byteSumCheck += byteCMD[i]; 
	}
	if (iCheckoutNum % 2 == 0)
	{
		byteCMD[i] = byteSumCheck;
	}
	else
	{
		byteCMD[i] = byteSumCheck + 0x80;
	}
	byteCMD[i + 1] = 0x0D;
	byteCMD[i + 2] = 0x0A;
	ser.Output(handle, byteCMD, i + 3);
	// Receive Code 
	DWORD dwTime = GetCurrentTime();
	BYTE bb[1];
	int iErrN = 0;
	CString strReturn = "";
	while(GetCurrentTime() - dwTime <= 5000)
	{
		if (!ser.Input(handle, bb, 1))
		{
			iErrN ++;
			if(iErrN >= 3)
			{
				ser.Close(handle);
				return FALSE;
			}
		}
		strReturn += bb[0]; 
		if (bb[0] == '\n')
		{  
			break;
		}
	}
	int iIndex = 0;
	iIndex = strReturn.Find("V,", iIndex);
	CString strValue;
	if (-1 == iIndex)
	{
		return FALSE;
	}
	else
	{
		strValue = strReturn.Mid(iIndex, 12);
		sscanf_s(strValue, "V,%f", &fValue);

	}
	return TRUE;
}

BOOL CSafetyTest_CSComm5505::SetCommandCode(CString strSerialcmd)
{
	Serial ser;
	HANDLE handle;
	if (!ser.Open(handle, m_strCOM, m_iBaudrate))
	{
		return FALSE;
	}
	ser.SetReadTime(handle, 2000, 1, 2000);
	CString strTemp;
	int i;
	BYTE byteCMD[256];
	BYTE byteIn[256];
	BYTE byteSumCheck = 0;
	for (i = 0; i < strSerialcmd.GetLength(); i++)
	{
		byteCMD[i]= (BYTE)strSerialcmd.GetAt(i);
		byteSumCheck += byteCMD[i]; 
	}
	byteCMD[i] = byteSumCheck|0x80;

	byteCMD[i + 1] = 0x0D;
	byteCMD[i + 2] = 0x0A;
	ser.Output(handle, byteCMD, i + 3);
	// Receive Code
	BYTE bPerIn = 0x00;
	BYTE bCurIn = 0x00;
	BYTE bTempIn[1];
	bTempIn[0] = 0x00;
	int iNum = 0;
	while (1)
	{
		bPerIn = bTempIn[0];
		if (!ser.Input(handle, bTempIn, 1))
		{
			ser.Close(handle);
			return FALSE;
		}
		byteIn[iNum++] = bTempIn[0];
		bCurIn = bTempIn[0];
		if(bPerIn == 0x0D && bCurIn == 0x0A)
		{
			break;
		}
	}

	if (byteIn[0] == 0x2D)
	{
		ser.Close(handle);
		return FALSE;
	}
	ser.Close(handle);
	return TRUE;
}

BOOL CSafetyTest_CSComm5505::SetAndTest(int iSelIndex)
{
	SetFunctionPara para;
	if (iSelIndex > m_paraArray.GetSize() - 1 || iSelIndex < 0)
	{

	}
	else
	{
		para = m_paraArray.GetAt(iSelIndex);
	}
	if (!SetRemote())
	{
		return FALSE;
	}
	if (!SetTestVoltage_V(para.fTestOverVoltage_V))
	{
		return FALSE;
	}
	if (!SetAlarmValue_High(para.fAlarmHigh))
	{
		return FALSE;
	}
	if (!SetAlarmValue_Low(para.fAlarmLow))
	{
		return FALSE;
	}
	if (!SetTestTime_s(para.fTestTime_s))
	{
		return FALSE;
	}
	if (!SetDelayJudgeTime_s(para.fDelayJudge_s))
	{
		return FALSE;
	}
	if (!SetInterTestTime_s(para.fInterTestTime_s))
	{
		return FALSE;
	}
	if (!SetFailedTestTime_s(para.SetfailedTestTime_s))
	{
		return FALSE;
	}
	if (!SetTestStart())
	{
		return FALSE;
	}
	return TRUE;
}
BOOL CSafetyTest_CSComm5505::GetValue(float &fValue)
{
	if (!GetTestData(fValue))
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CSafetyTest_CSComm5505::CS_Init_XL(CString strCOM)
{
	//初始化 设置地址 并进入远程模式
	Initialize(strCOM);
	BOOL bR;
	SetLocal();
	bR = SetConstructAddress(1);
	if(!bR)
		return FALSE;
	bR = SetRemote();
	if(!bR)
		return FALSE;
	return TRUE;
}

BOOL CSafetyTest_CSComm5505::CS_Setup_XL(float fVol,float fTime)
{
	if(g_bDemo)
	{
		return TRUE;
	}
	//设置电压和时间 5505为手动调压
	BOOL bR;
	//bR = SetTestVoltage_V(fVol);
	//if(!bR)
	//	return FALSE;

	bR = SetTestTime_s(fTime);
	if(!bR)
		return FALSE;
	return TRUE;

}

BOOL CSafetyTest_CSComm5505::CS_Test_XL(BOOL bTest)
{
	BOOL bR;
	if(bTest)
		bR = SetTestStart();
	else
		bR = SetTestStop();
	if(!bR)
		return FALSE;

	return TRUE;
}

BOOL CSafetyTest_CSComm5505::CS_GetData_XL(float &fLC,BOOL &bOK)
{
	if(g_bDemo)
	{
		fLC = 500;
		return TRUE;
	}
	Serial ser;
	HANDLE handle;
	if (!ser.Open(handle, m_strCOM, m_iBaudrate))
	{
		return FALSE;
	}
	ser.SetReadTime(handle, 2000, 1, 2000);
	CString strTemp;
	int i;
	BYTE byteCMD[256];
	BYTE byteSumCheck = 0;
	CString strSerialcmd = "SOURce:TEST:FETCh?";
	int iCheckoutNum = 0;
	BYTE byteCheckout;
	for (i = 0; i < strSerialcmd.GetLength(); i++)
	{
		if (i == 0)
		{
			byteCheckout = (BYTE)strSerialcmd.GetAt(i);
			iCheckoutNum ++;
		}
		else
		{
			if (byteCheckout == (BYTE)strSerialcmd.GetAt(i))
			{
				iCheckoutNum ++;
			}
		}
		byteCMD[i]= (BYTE)strSerialcmd.GetAt(i);
		byteSumCheck += byteCMD[i]; 
	}
	if (iCheckoutNum % 2 == 0)
	{
		byteCMD[i] = byteSumCheck;
	}
	else
	{
		byteCMD[i] = byteSumCheck + 0x80;
	}
	byteCMD[i + 1] = 0x0D;
	byteCMD[i + 2] = 0x0A;
	ser.Output(handle, byteCMD, i + 3);
	// Receive Code 
	DWORD dwTime = GetCurrentTime();
	BYTE bb[1];
	int iErrN = 0;
	CString strReturn = "";
	while(GetCurrentTime() - dwTime <= 5000)
	{
		if (!ser.Input(handle, bb, 1))
		{
			iErrN ++;
			if(iErrN >= 3)
			{
				ser.Close(handle);
				return FALSE;
			}
		}
		strReturn += bb[0]; 
		if (bb[0] == '\n')
		{  
			break;
		}
	}
	ser.Close(handle);
	//找泄露电流值
	int iIndex = 0;
	iIndex = strReturn.Find("A,", iIndex);
	CString strValue;
	if (-1 == iIndex)
	{
		return FALSE;
	}
	else
	{
		strValue = strReturn.Mid(iIndex-7, 10);
		sscanf_s(strValue, ",%fmA,", &fLC);
	}

	//找结束标志
	iIndex = 0;
	iIndex = strReturn.Find("L,", iIndex);
	if (-1 == iIndex)
	{
	}
	else
	{
		strValue = strReturn.Mid(iIndex, 5);
		int iRe;
		sscanf_s(strValue, "L,%d", &iRe);
		bOK = FALSE;
		if(iRe == 2)
		{
			bOK = TRUE;
		}
	}
	//或者N项
	iIndex = 0;
	iIndex = strReturn.Find("N,", iIndex);
	if (-1 == iIndex)
	{
	}
	else
	{
		strValue = strReturn.Mid(iIndex, 5);
		int iRe;
		sscanf_s(strValue, "N,%d", &iRe);
		bOK = FALSE;
		if(iRe == 2)
		{
			bOK = TRUE;
		}
	}
	return TRUE;
}
//////////////////////////////////////////////////////////////////////////

CSafetyTest_TongHui_TH2683AComm::CSafetyTest_TongHui_TH2683AComm()
{
    m_strCOM = "COM1";
    m_iBaudrate = 9600;
	m_bHaveSetPara = FALSE;

}

CSafetyTest_TongHui_TH2683AComm::~CSafetyTest_TongHui_TH2683AComm()
{

}

void CSafetyTest_TongHui_TH2683AComm::Initialize(CString strCOM, int iBaudRate)
{
    m_strCOM = strCOM;
    m_iBaudrate = iBaudRate;
	m_bHaveSetPara = FALSE;

	SetTestDisCharge();
	Sleep(100);
}

BOOL CSafetyTest_TongHui_TH2683AComm::SetTestFunctionPara(SetFunctionPara &para)
{
	//先设置为总线模式
	SetCommandCode("TRIG:SOUR BUS");

    Serial ser;
    HANDLE handle;
    if (!ser.Open(handle, m_strCOM, m_iBaudrate))
    {
        return FALSE;
    }
    ser.SetReadTime(handle, 2000, 1, 2000);
    int i;
    BYTE byteCMD[512];
    int iTotalbyteNum;

	iTotalbyteNum = 0;
	if(m_PerData.iTestMode != para.iTestMode || !m_bHaveSetPara)
	{
		for (i = 0; i < para.GetTestModeString().GetLength(); i ++)
		{
			byteCMD[iTotalbyteNum] = para.GetTestModeString().GetAt(i);
			iTotalbyteNum ++;
		}
		Sleep(100);
		ser.Output(handle, byteCMD, iTotalbyteNum);
	}

	iTotalbyteNum = 0;
	if(m_PerData.bClearZero != para.bClearZero || !m_bHaveSetPara)
	{
		for (i = 0; i < para.GetClearZeroString().GetLength(); i ++)
		{
			byteCMD[iTotalbyteNum] = para.GetClearZeroString().GetAt(i);
			iTotalbyteNum ++;
		}
		Sleep(100);
		ser.Output(handle, byteCMD, iTotalbyteNum);
	}
	iTotalbyteNum = 0;
	if(m_PerData.fTestOverVoltage_V != para.fTestOverVoltage_V || !m_bHaveSetPara)
	{
		for (i = 0; i < para.GetTestOverVoltageString().GetLength(); i ++)
		{
			byteCMD[iTotalbyteNum] = para.GetTestOverVoltageString().GetAt(i);
			iTotalbyteNum++;
		}
		Sleep(100);
		ser.Output(handle, byteCMD, iTotalbyteNum);
	}
	
	iTotalbyteNum = 0;
	if(m_PerData.iTestSpeed != para.iTestSpeed || !m_bHaveSetPara)
	{
		for (i = 0; i < para.GetTestSpeedString().GetLength(); i ++)
		{
			byteCMD[iTotalbyteNum] = para.GetTestSpeedString().GetAt(i);
			iTotalbyteNum ++;
		}
		Sleep(100);
		ser.Output(handle, byteCMD, iTotalbyteNum);
	}
	iTotalbyteNum = 0;
	if(m_PerData.bCheckSwitch != para.bCheckSwitch || !m_bHaveSetPara)
	{
		for (i = 0; i < para.GetCheckSwitchString().GetLength(); i ++)
		{
			byteCMD[iTotalbyteNum] = para.GetCheckSwitchString().GetAt(i);
			iTotalbyteNum ++;
		}
		Sleep(100);
		ser.Output(handle, byteCMD, iTotalbyteNum);
	}
	iTotalbyteNum = 0;
	if(m_PerData.fChargeTime_s != para.fChargeTime_s || !m_bHaveSetPara)
	{
		for (i = 0; i < para.GetChargeTimeString().GetLength(); i ++)
		{
			byteCMD[iTotalbyteNum] = para.GetChargeTimeString().GetAt(i);
			iTotalbyteNum ++;
		}
		Sleep(100);
		ser.Output(handle, byteCMD, iTotalbyteNum);
	}
	iTotalbyteNum = 0;
	if(m_PerData.fWaitTime_s != para.fWaitTime_s || !m_bHaveSetPara)
	{
		for (i = 0; i < para.GetWaitTimeString().GetLength(); i ++)
		{
			byteCMD[iTotalbyteNum] = para.GetWaitTimeString().GetAt(i);
			iTotalbyteNum ++;
		}
		Sleep(100);
		ser.Output(handle, byteCMD, iTotalbyteNum);
	}
	iTotalbyteNum = 0;
	if(m_PerData.fTestTime_s != para.fTestTime_s || !m_bHaveSetPara)
	{
		for (i = 0; i < para.GetTestTimeString().GetLength(); i ++)
		{
			byteCMD[iTotalbyteNum] = para.GetTestTimeString().GetAt(i);
			iTotalbyteNum ++;
		}
		Sleep(100);
		ser.Output(handle, byteCMD, iTotalbyteNum);
	}
	iTotalbyteNum = 0;
	if(m_PerData.fDischargeTime_s != para.fDischargeTime_s || !m_bHaveSetPara)
	{
		for (i = 0; i < para.GetDischargeTimeString().GetLength(); i ++)
		{
			byteCMD[iTotalbyteNum] = para.GetDischargeTimeString().GetAt(i);
			iTotalbyteNum ++;
		}
		Sleep(100);
		ser.Output(handle, byteCMD, iTotalbyteNum);
	}
	iTotalbyteNum = 0;
	if(m_PerData.iTestAvgNum != para.iTestAvgNum || !m_bHaveSetPara)
	{
		for (i = 0; i < para.GetTestAvgNumString().GetLength(); i ++)
		{
			byteCMD[iTotalbyteNum] = para.GetTestAvgNumString().GetAt(i);
			iTotalbyteNum ++;
		}
		Sleep(100);
		ser.Output(handle, byteCMD, iTotalbyteNum);
	}
	iTotalbyteNum = 0;
	if(m_PerData.iRange != para.iRange || !m_bHaveSetPara)
	{
		for (i = 0; i < para.GetRangeString().GetLength(); i ++)
		{
			byteCMD[iTotalbyteNum] = para.GetRangeString().GetAt(i);
			iTotalbyteNum ++;
		}
		Sleep(100);
		ser.Output(handle, byteCMD, iTotalbyteNum);
	}
	iTotalbyteNum = 0;
	if(m_PerData.bAutoRange != para.bAutoRange || !m_bHaveSetPara)
	{
		for (i = 0; i < para.GetAutoRangeString().GetLength(); i ++)
		{
			byteCMD[iTotalbyteNum] = para.GetAutoRangeString().GetAt(i);
			iTotalbyteNum ++;
		}
		Sleep(100);
		ser.Output(handle, byteCMD, iTotalbyteNum);
	}
	iTotalbyteNum = 0;
	if(m_PerData.bDisplay != para.bDisplay || !m_bHaveSetPara)
	{
		for (i = 0; i < para.GetDisplayString().GetLength(); i ++)
		{
			byteCMD[iTotalbyteNum] = para.GetDisplayString().GetAt(i);
			iTotalbyteNum ++;
		}
		Sleep(100);
		ser.Output(handle, byteCMD, iTotalbyteNum);
	}
	
    ser.Close(handle);
	Sleep(100);
	
	m_PerData = para;
	m_bHaveSetPara = TRUE;
	return TRUE;
}

BOOL CSafetyTest_TongHui_TH2683AComm::SetCommandCode(CString strSerialcmd)
{
	Serial ser;
	HANDLE handle;
	if (!ser.Open(handle, m_strCOM, m_iBaudrate))
	{
		return FALSE;
	}
	ser.SetReadTime(handle, 2000, 1, 2000);
	int i;
	BYTE byteCMD[512];
	int iTotalbyteNum = 0;
	for (i = 0; i < strSerialcmd.GetLength(); i ++)
	{
		byteCMD[iTotalbyteNum] = strSerialcmd.GetAt(i);
		iTotalbyteNum ++;
	}
	byteCMD[iTotalbyteNum] = '\r';
	iTotalbyteNum ++;
	byteCMD[iTotalbyteNum] = '\n';
	iTotalbyteNum ++;
	ser.Output(handle, byteCMD, iTotalbyteNum);
	ser.Close(handle);
	return TRUE;
}

BOOL CSafetyTest_TongHui_TH2683AComm::TH_SetTestStart_IR(BOOL bTest)
{
	if(g_bDemo)
	{
		return TRUE;
	}

	if(bTest)
		return SetCommandCode("TRIG");
	else
		return SetTestDisCharge();
}

BOOL CSafetyTest_TongHui_TH2683AComm::TH_Setup_IR(float fVol,float fTime)
{
	if(g_bDemo)
	{
		return TRUE;
	}
	BOOL bR;
	SetFunctionPara data;
	data.bClearZero			= FALSE;		// 1 clear zero on; 0 clear zero off
	data.fTestOverVoltage_V = fVol;			// test voltage value 输出电压
	data.iTestMode			= 0;			// 0 sigle; 1 continus
	data.iTestSpeed			= 1;			// 0 slow; 1 fast 
	data.bCheckSwitch		= 0;			// 0 off 1; 1 on
	data.fChargeTime_s		= 0.1f;			// charge time value;precision is 0.1s
	data.fWaitTime_s		= 0.1f;			// wait time value;precision is 0.1s
	data.fTestTime_s		= fTime;		// test time;precision is 0.1s
	data.fDischargeTime_s	= 0.1f;			// discharge time;precision is 0.1s 
	data.iTestAvgNum		= 1;			// test average num;
	data.iRange				= 0;			// range; iRange can be 0, 1, 2, 3, 4, 5;relate to 1mA, 100uA, 10uA, 1uA, 100nA, 10nA
	data.bAutoRange			= FALSE;			// auto range
	data.bDisplay			= TRUE;		// screen display
	bR = SetTestFunctionPara(data);
	return bR;
}

BOOL CSafetyTest_TongHui_TH2683AComm::TH_GetTestResult_IR(float &fIR, float &fLC, float &fTime)
{
	if(g_bDemo)
	{
		fIR = 500;
		fLC = 0.1f;
		fTime = 0;
		return TRUE;
	}
    Serial ser;
    HANDLE handle;
    if (!ser.Open(handle, m_strCOM, m_iBaudrate))
    {
       return FALSE;
    }
    ser.SetReadTime(handle, 100, 1, 100);
    int i;
    BYTE byteCMD[512];
    int iTotalbyteNum = 0;
    CString strSerialcmd = "FETC?";
    for (i = 0; i < strSerialcmd.GetLength(); i ++)
    {
        byteCMD[iTotalbyteNum] = strSerialcmd.GetAt(i);
        iTotalbyteNum ++;
    }
    byteCMD[iTotalbyteNum] = '\r';
    iTotalbyteNum ++;
    byteCMD[iTotalbyteNum] = '\n';
    iTotalbyteNum ++;
    ser.Output(handle, byteCMD, iTotalbyteNum);
    DWORD dwTime = (DWORD)::GetCurrentTime();
    BYTE byteIN[256];
    int iErrN = 0;
    BYTE	bb[1]; 
    int iReceiveNum = 0;
    while(GetCurrentTime() - dwTime <= 5000)
    {
        if (!ser.Input(handle, bb, 1))
        {
            iErrN ++;
            if(iErrN >= 3)
            {
                ser.Close(handle);
                return FALSE;
            }
        }
        byteIN[iReceiveNum] = bb[0]; 
        if (bb[0] == '\n')
        {  
            byteIN[iReceiveNum] = bb[0]; 
            iReceiveNum ++;
            break;
        }
        iReceiveNum ++;
    }
    ser.Close(handle);

    int iB = 0;
    BOOL bStartValue = FALSE;
    CString strValue = "";
    for (i = iB; i < iReceiveNum; i ++)
    {
        if (byteIN[i] == '+')
        {
            bStartValue = TRUE;
        }
        if (byteIN[i] == ',')
        {
            bStartValue = FALSE;
            break;
        }
        if (bStartValue)
        {
            strValue += byteIN[i];
        }
    }
    iB = i;
    iB ++;
    if (bStartValue == TRUE)
    {
		fIR = 1000 * 1000 * 1000;
        return TRUE;
    }
    fIR = (float)atof(strValue);
   /* strValue = "";
    for (i = iB; i < iReceiveNum; i ++)
    {
        if (byteIN[i] == '+')
        {
            bStartValue = TRUE;
        }
        if (byteIN[i] == ',')
        {
            bStartValue = FALSE;
            break;
        }
        if (bStartValue)
        {
            strValue += byteIN[i];
        }
    }
    iB = i;
    iB ++;
    if (bStartValue == TRUE)
    {
        return TRUE;
    }
    fLC = (float)atof(strValue);
    strValue = "";
    for (i = iB; i < iReceiveNum; i ++)
    {
        if (byteIN[i] == '+')
        {
            bStartValue = TRUE;
        }
        if (byteIN[i] == '\n')
        {
            bStartValue = FALSE;
            break;
        }
        if (bStartValue)
        {
            strValue += byteIN[i];
        }
    }
    if (bStartValue == TRUE)
    {
        return FALSE;
    }
    fTime = (float)atof(strValue);
	*/
	return TRUE;
}

BOOL CSafetyTest_TongHui_TH2683AComm::SetTestDisCharge()
{
    return SetCommandCode("DISC");
}

BOOL CSafetyTest_TongHui_TH2683AComm::SetBeep(BOOL bBeepOn)
{
    if (bBeepOn)
    {
        return SetCommandCode("SYST:BEEP 1");
    }
    else
    {
        return SetCommandCode("SYST:BEEP 0");
    }
}

void CSafetyTest_TongHui_TH2683AComm::ShowTestSetDlg()
{
//    CDlgSaftyIRExaminationSet dlg;
 //   dlg.DoModal();
}
BOOL CSafetyTest_TongHui_TH2683AComm::SetAndTest(int iSelIndex)
{
    SetFunctionPara para;
    if (iSelIndex > m_paraArray.GetSize() - 1 || iSelIndex < 0)
    {

    }
    else
    {
        para = m_paraArray.GetAt(iSelIndex);
    }
    if (!SetTestFunctionPara(para))
    {
        return FALSE;
    }
    if (!TH_SetTestStart_IR(TRUE))
    {
        return FALSE;
    }
    return TRUE;
}
BOOL CSafetyTest_TongHui_TH2683AComm::GetValue(float &fValue)
{
    float fIR, fLC, fTime;
   if (!TH_GetTestResult_IR(fIR, fLC, fTime))
   {
       return FALSE;
   }
   fValue = fIR;
   return TRUE;
}

BOOL CSafetyTest_TongHui_TH2683AComm::SaveFile(CString strPathName)
{
    CFile file;
    if (!file.Open(strPathName, CFile::modeWrite | CFile::modeCreate))
    {
        return FALSE;
    }

    CArchive ar(&file, CArchive::store);
    if (!Serialize(ar))
    {
        ar.Close();
        file.Close();
        return FALSE;
    }

    ar.Close();
    file.Close();

    return TRUE;
}
BOOL CSafetyTest_TongHui_TH2683AComm::LoadFile(CString strPathName)
{
    CFile file;
    if (!file.Open(strPathName, CFile::modeRead))
    {
        return FALSE;
    }

    CArchive ar(&file, CArchive::load);
    if (!Serialize(ar))
    {
        ar.Close();
        file.Close();
        return FALSE;
    }

    ar.Close();
    file.Close();

    return TRUE;
}
BOOL CSafetyTest_TongHui_TH2683AComm::Serialize(CArchive & ar)
{
    CString strDev;
    if (ar.IsStoring())
    {
        strDev = "SafetyTest_TongHui_TH2683AComm";
        ar << strDev;
        ar << m_paraArray.GetSize();
        for (int i = 0; i < m_paraArray.GetSize(); i++)
        {
            m_paraArray.GetAt(i).Serialize(ar);
        }
    }
    else
    {
        ar >> strDev;
        if (strDev != "SafetyTest_TongHui_TH2683AComm")
        {
            return FALSE;
        }
        int iN;
        ar >> iN;
        m_paraArray.RemoveAll();
        for (int i = 0; i < iN; i++)
        {
            SetFunctionPara para;
            para.Serialize(ar);
            m_paraArray.Add(para);
        }
    }
    return TRUE;
}

CSafetyTest_TongHui_TH9310_20Comm::CSafetyTest_TongHui_TH9310_20Comm()
{
    m_strCOM = "COM1";
    m_iBaudrate = 9600;
	m_bHaveSetAC = FALSE;
	m_bHaveSetDC = FALSE;
}

CSafetyTest_TongHui_TH9310_20Comm::~CSafetyTest_TongHui_TH9310_20Comm()
{

}

void CSafetyTest_TongHui_TH9310_20Comm::Initialize(CString strCOM, int iBaudRate)
{
    m_strCOM = strCOM;
    m_iBaudrate = iBaudRate;
}

BOOL CSafetyTest_TongHui_TH9310_20Comm::SetTestFunctionACPara(int iStep, SetFunctionACPara &para)
{
    CString strFunctionHead;
    strFunctionHead.Format("FUNC:SOUR:STEP %d", iStep);
    Serial ser;
    HANDLE handle;
    if (!ser.Open(handle, m_strCOM, m_iBaudrate))
    {
        return FALSE;
    }
    ser.SetReadTime(handle, 2000, 1, 2000);
    BYTE byteCMD[512];
    int iTotalbyteNum = 0;
    CString strCommand;
	iTotalbyteNum = 0;
	if(m_dPerParaAC.iVoltage_V != para.iVoltage_V || !m_bHaveSetDC)
	{
		strCommand = strFunctionHead + para.GetTestVoltageString();
		for (int i = 0; i < strCommand.GetLength(); i ++)
		{
			byteCMD[iTotalbyteNum] = strCommand.GetAt(i);
			iTotalbyteNum ++;
		}
		ser.Output(handle, byteCMD, iTotalbyteNum);
		Sleep(100);
	}

	iTotalbyteNum = 0;
	if(m_dPerParaAC.fUpperCurrent_mA != para.fUpperCurrent_mA || !m_bHaveSetDC)
	{
		strCommand = strFunctionHead + para.GetUpperCurrentString();
		for (int i = 0; i < strCommand.GetLength(); i ++)
		{
			byteCMD[iTotalbyteNum] = strCommand.GetAt(i);
			iTotalbyteNum ++;
		}
		ser.Output(handle, byteCMD, iTotalbyteNum);
		Sleep(100);
	}

	iTotalbyteNum = 0;
	if(m_dPerParaAC.fLowerCurrent_mA != para.fLowerCurrent_mA || !m_bHaveSetDC)
	{
		strCommand = strFunctionHead + para.GetLowerCurrentString();
		for (int i = 0; i < strCommand.GetLength(); i ++)
		{
			byteCMD[iTotalbyteNum] = strCommand.GetAt(i);
			iTotalbyteNum ++;
		}
		ser.Output(handle, byteCMD, iTotalbyteNum);
		Sleep(100);
	}

	iTotalbyteNum = 0;
	if(m_dPerParaAC.fTestTime_s != para.fTestTime_s || !m_bHaveSetDC)
	{
		strCommand = strFunctionHead + para.GetTestTimeString();
		for (int i = 0; i < strCommand.GetLength(); i ++)
		{
			byteCMD[iTotalbyteNum] = strCommand.GetAt(i);
			iTotalbyteNum ++;
		}
		ser.Output(handle, byteCMD, iTotalbyteNum);
		Sleep(100);
	}

	iTotalbyteNum = 0;
	if(m_dPerParaAC.fRaiseTime_s != para.fRaiseTime_s || !m_bHaveSetDC)
	{
		strCommand = strFunctionHead + para.GetRaiseTimeString();
		for (int i = 0; i < strCommand.GetLength(); i ++)
		{
			byteCMD[iTotalbyteNum] = strCommand.GetAt(i);
			iTotalbyteNum ++;
		}

		ser.Output(handle, byteCMD, iTotalbyteNum);
		Sleep(100);
	}
	
	iTotalbyteNum = 0;
	if(m_dPerParaAC.fFallTime_s != para.fFallTime_s || !m_bHaveSetDC)
	{
		strCommand = strFunctionHead + para.GetFallTimeString();
		for (int i = 0; i < strCommand.GetLength(); i ++)
		{
			byteCMD[iTotalbyteNum] = strCommand.GetAt(i);
			iTotalbyteNum ++;
		}

		ser.Output(handle, byteCMD, iTotalbyteNum);
		Sleep(100);
	}

	iTotalbyteNum = 0;
	if(m_dPerParaAC.fArcweldingCurrent_mA != para.fArcweldingCurrent_mA || !m_bHaveSetDC)
	{
		strCommand = strFunctionHead + para.GetArcweldingString();
		for (int i = 0; i < strCommand.GetLength(); i ++)
		{
			byteCMD[iTotalbyteNum] = strCommand.GetAt(i);
			iTotalbyteNum ++;
		}

		ser.Output(handle, byteCMD, iTotalbyteNum);
		Sleep(100);
	}
    
	iTotalbyteNum = 0;
	if(m_dPerParaAC.fFrequency_Hz != para.fFrequency_Hz || !m_bHaveSetAC)
	{
		strCommand = strFunctionHead + para.GetFrequencyString();
		for (int i = 0; i < strCommand.GetLength(); i ++)
		{
			byteCMD[iTotalbyteNum] = strCommand.GetAt(i);
			iTotalbyteNum ++;
		}

		ser.Output(handle, byteCMD, iTotalbyteNum);
		Sleep(100);
	}

	ser.Close(handle);
    return TRUE;
}

BOOL CSafetyTest_TongHui_TH9310_20Comm::SetTestFunctionDCPara(int iStep, SetFunctionDCPara &para)
{
    CString strFunctionHead;
    strFunctionHead.Format("FUNC:SOUR:STEP %d", iStep);
    Serial ser;
    HANDLE handle;
    if (!ser.Open(handle, m_strCOM, m_iBaudrate))
    {
        return FALSE;
    }
    ser.SetReadTime(handle, 2000, 1, 2000);
    BYTE byteCMD[512];
    int iTotalbyteNum = 0;
    CString strCommand;
	iTotalbyteNum = 0;
	if(m_dPerParaDC.iVoltage_V != para.iVoltage_V || !m_bHaveSetDC)
	{
		strCommand = strFunctionHead + para.GetTestVoltageString();
		for (int i = 0; i < strCommand.GetLength(); i ++)
		{
			byteCMD[iTotalbyteNum] = strCommand.GetAt(i);
			iTotalbyteNum ++;
		}

		ser.Output(handle, byteCMD, iTotalbyteNum);
		Sleep(100);
	}
    
	iTotalbyteNum = 0;
	if(m_dPerParaDC.fUpperCurrent_mA != para.fUpperCurrent_mA || !m_bHaveSetDC)
	{
		strCommand = strFunctionHead + para.GetUpperCurrentString();
		for (int i = 0; i < strCommand.GetLength(); i ++)
		{
			byteCMD[iTotalbyteNum] = strCommand.GetAt(i);
			iTotalbyteNum ++;
		}

		ser.Output(handle, byteCMD, iTotalbyteNum);
		Sleep(100);
	}

	iTotalbyteNum = 0;
	if(m_dPerParaDC.fLowerCurrent_mA != para.fLowerCurrent_mA || !m_bHaveSetDC)
	{
		strCommand = strFunctionHead + para.GetLowerCurrentString();
		for (int i = 0; i < strCommand.GetLength(); i ++)
		{
			byteCMD[iTotalbyteNum] = strCommand.GetAt(i);
			iTotalbyteNum ++;
		}

		ser.Output(handle, byteCMD, iTotalbyteNum);
		Sleep(100);
	}
    
	iTotalbyteNum = 0;
	if(m_dPerParaDC.fTestTime_s != para.fTestTime_s || !m_bHaveSetDC)
	{
		strCommand = strFunctionHead + para.GetTestTimeString();
		for (int i = 0; i < strCommand.GetLength(); i ++)
		{
			byteCMD[iTotalbyteNum] = strCommand.GetAt(i);
			iTotalbyteNum ++;
		}

		ser.Output(handle, byteCMD, iTotalbyteNum);
		Sleep(100);
	}
    
	iTotalbyteNum = 0;
	if(m_dPerParaDC.fRaiseTime_s != para.fRaiseTime_s || !m_bHaveSetDC)
	{
		strCommand = strFunctionHead + para.GetRaiseTimeString();
		for (int i = 0; i < strCommand.GetLength(); i ++)
		{
			byteCMD[iTotalbyteNum] = strCommand.GetAt(i);
			iTotalbyteNum ++;
		}

		ser.Output(handle, byteCMD, iTotalbyteNum);
		Sleep(100);
	}

	iTotalbyteNum = 0;
	if(m_dPerParaDC.fFallTime_s != para.fFallTime_s || !m_bHaveSetDC)
	{
		strCommand = strFunctionHead + para.GetFallTimeString();
		for (int i = 0; i < strCommand.GetLength(); i ++)
		{
			byteCMD[iTotalbyteNum] = strCommand.GetAt(i);
			iTotalbyteNum ++;
		}

		ser.Output(handle, byteCMD, iTotalbyteNum);
		Sleep(100);
	}
    
	iTotalbyteNum = 0;
	if(m_dPerParaDC.fWaitTime_s != para.fWaitTime_s || !m_bHaveSetDC)
	{
		strCommand = strFunctionHead + para.GetWaitTimeString();
		for (int i = 0; i < strCommand.GetLength(); i ++)
		{
			byteCMD[iTotalbyteNum] = strCommand.GetAt(i);
			iTotalbyteNum ++;
		}

		ser.Output(handle, byteCMD, iTotalbyteNum);
		Sleep(100);
	}
	
	iTotalbyteNum = 0;
	if(m_dPerParaDC.fArcweldingCurrent_A != para.fArcweldingCurrent_A || !m_bHaveSetDC)
	{
		strCommand = strFunctionHead + para.GetArcweldingString();
		for (int i = 0; i < strCommand.GetLength(); i ++)
		{
			byteCMD[iTotalbyteNum] = strCommand.GetAt(i);
			iTotalbyteNum ++;
		}

		ser.Output(handle, byteCMD, iTotalbyteNum);
		Sleep(100);
	}
	
	iTotalbyteNum = 0;
	if(m_dPerParaDC.bRangetoPeak != para.bRangetoPeak || !m_bHaveSetDC)
	{
		strCommand = strFunctionHead + para.GetRangetoPeakString();
		for (int i = 0; i < strCommand.GetLength(); i ++)
		{
			byteCMD[iTotalbyteNum] = strCommand.GetAt(i);
			iTotalbyteNum ++;
		}

		ser.Output(handle, byteCMD, iTotalbyteNum);
		Sleep(100);
	}

	ser.Close(handle);
    return TRUE;
}


BOOL CSafetyTest_TongHui_TH9310_20Comm::SetTestStart(int iStep)
{
    return SetCommandCode("FUNC:STAR");
}

BOOL CSafetyTest_TongHui_TH9310_20Comm::SetTestStop(int iStep)
{
    return SetCommandCode("FUNC:STOP");
}

BOOL CSafetyTest_TongHui_TH9310_20Comm::AllStepNew()
{
    return SetCommandCode("FUNC:SOUR:STEP NEW");
}

BOOL CSafetyTest_TongHui_TH9310_20Comm::AddOneStep()
{
    return SetCommandCode("FUNC:SOUR:STEP INS");
}

BOOL CSafetyTest_TongHui_TH9310_20Comm::DelOneStep(int iStep)
{
    CString strCommand;
    strCommand.Format("FUNC:SOUR:STEP DEL %d", iStep);
    return SetCommandCode(strCommand);
}

BOOL CSafetyTest_TongHui_TH9310_20Comm::SetCommandCode(CString strSerialcmd)
{
    Serial ser;
    HANDLE handle;
    if (!ser.Open(handle, m_strCOM, m_iBaudrate))
    {
        return FALSE;
    }
    ser.SetReadTime(handle, 2000, 1, 2000);
    int i;
    BYTE byteCMD[512];
    int iTotalbyteNum = 0;
    for (i = 0; i < strSerialcmd.GetLength(); i ++)
    {
        byteCMD[iTotalbyteNum] = strSerialcmd.GetAt(i);
        iTotalbyteNum ++;
    }
    byteCMD[iTotalbyteNum] = '\r';
    iTotalbyteNum ++;
    byteCMD[iTotalbyteNum] = '\n';
    iTotalbyteNum ++;
    ser.Output(handle, byteCMD, iTotalbyteNum);
    ser.Close(handle);
    return TRUE;
}


void CSafetyTest_TongHui_TH9310_20Comm::ShowTestSetDlg()
{
//    CDlgSaftyVoltageWithStandExaminationSet dlg;
 //   dlg.DoModal();
}

BOOL CSafetyTest_TongHui_TH9310_20Comm::SetAndTest(int iSelIndex)
{

    return TRUE;
}

BOOL CSafetyTest_TongHui_TH9310_20Comm::SaveFile(CString strPathName)
{
    CFile file;
    if (!file.Open(strPathName, CFile::modeWrite | CFile::modeCreate))
    {
        return FALSE;
    }

    CArchive ar(&file, CArchive::store);
    if (!Serialize(ar))
    {
        ar.Close();
        file.Close();
        return FALSE;
    }

    ar.Close();
    file.Close();

    return TRUE;
}
BOOL CSafetyTest_TongHui_TH9310_20Comm::LoadFile(CString strPathName)
{
    CFile file;
    if (!file.Open(strPathName, CFile::modeRead))
    {
        return FALSE;
    }

    CArchive ar(&file, CArchive::load);
    if (!Serialize(ar))
    {
        ar.Close();
        file.Close();
        return FALSE;
    }

    ar.Close();
    file.Close();

    return TRUE;
}
BOOL CSafetyTest_TongHui_TH9310_20Comm::Serialize(CArchive & ar)
{
    CString strDev;
    if (ar.IsStoring())
    {
        strDev = "SafetyTest_TongHui_TH9310_20Comm";
        ar << strDev;
        ar << m_paraArray.GetSize();
        for (int i = 0; i < m_paraArray.GetSize(); i++)
        {
            m_paraArray.GetAt(i).Serialize(ar);
        }
    }
    else
    {
        ar >> strDev;
        if (strDev != "SafetyTest_TongHui_TH9310_20Comm")
        {
            return FALSE;
        }
        int iN;
        ar >> iN;
        m_paraArray.RemoveAll();
        for (int i = 0; i < iN; i++)
        {
            SetFunctionPara para;
            para.Serialize(ar);
            m_paraArray.Add(para);
        }
    }
    return TRUE;
}
BOOL CSafetyTest_TongHui_TH9310_20Comm::TH_Init_NYY(CString strCOM)
{
	Initialize(strCOM);
	return TRUE;
}

BOOL CSafetyTest_TongHui_TH9310_20Comm::TH_Setup_NYY(int iTestType,float fVol,float fTime)
{
	if(g_bDemo)
	{
		return TRUE;
	}
	BOOL bR;
	if(iTestType == 0)
	{
		SetFunctionACPara data;
		data.iVoltage_V = (int)(fVol);
		data.fUpperCurrent_mA = 2;
		data.fLowerCurrent_mA = 0;
		data.fTestTime_s = fTime;
		data.fRaiseTime_s = 0;
		data.fFallTime_s = 0;
		data.fArcweldingCurrent_mA = 0;
		data.fFrequency_Hz = 50;
		bR = SetTestFunctionACPara(1,data);
		if(bR)
		{
			m_dPerParaAC = data;
			m_bHaveSetAC = TRUE;
			m_bHaveSetDC = FALSE;
		}
	}
	else
	{
		SetFunctionDCPara data;
		data.iVoltage_V = (int)(fVol);
		data.fUpperCurrent_mA = 2;
		data.fLowerCurrent_mA = 0;
		data.fTestTime_s = fTime;
		data.fRaiseTime_s = 0;
		data.fFallTime_s = 0;
		data.fWaitTime_s = 0;
		data.fArcweldingCurrent_A = 0;
		data.bRangetoPeak = FALSE;
		bR = SetTestFunctionDCPara(1,data);
		if(bR)
		{
			m_dPerParaDC = data;
			m_bHaveSetDC = TRUE;
			m_bHaveSetAC = FALSE;
		}
	}
	return bR;

	return TRUE;
}

BOOL CSafetyTest_TongHui_TH9310_20Comm::TH_SetTestStart_NYY(BOOL bTest)
{
	if(g_bDemo)
	{
		return TRUE;
	}
	int iErr = 0;
	BOOL bR;
	while (1)
	{
		if(bTest)
			bR = SetTestStart(1);
		else
			bR = SetTestStop(1);
		Sleep(100);
		if(bR)
			break;
		else
		{
			iErr++;
			if(iErr > 10)
				return FALSE;
		}
	}
	
	return TRUE;
}

BOOL CSafetyTest_TongHui_TH9310_20Comm::TH_GetTestResult_NYY(float &fLC)
{
	//增加多次通讯
	BOOL bR;
	int iErr = 0;
	while(1)
	{
		bR = TH_GetTestResult_NYY_N(fLC);
		if(bR || iErr > 10)
		{
			break;
		}
		else
		{
			iErr++;
			Sleep(100);
		}
	}
	return bR;
}

BOOL CSafetyTest_TongHui_TH9310_20Comm::TH_GetTestResult_NYY_N(float &fLC)
{
	if(g_bDemo)
	{
		fLC = 0.01f;
		return TRUE;
	}
	Serial ser;
	HANDLE handle;
	if (!ser.Open(handle, m_strCOM, m_iBaudrate))
	{
		return FALSE;
	}
	ser.SetReadTime(handle, 100, 1, 100);
	int i;
	BYTE byteCMD[512];
	int iTotalbyteNum = 0;
	CString strSerialcmd = "FETC?";
	for (i = 0; i < strSerialcmd.GetLength(); i ++)
	{
		byteCMD[iTotalbyteNum] = strSerialcmd.GetAt(i);
		iTotalbyteNum ++;
	}
	byteCMD[iTotalbyteNum] = '\r';
	iTotalbyteNum ++;
	byteCMD[iTotalbyteNum] = '\n';
	iTotalbyteNum ++;
	ser.Output(handle, byteCMD, iTotalbyteNum);
	DWORD dwTime = (DWORD)::GetCurrentTime();
	BYTE byteIN[256];
	int iErrN = 0;
	BYTE	bb[1]; 
	int iReceiveNum = 0;
	while(GetCurrentTime() - dwTime <= 5000)
	{
		if (!ser.Input(handle, bb, 1))
		{
			iErrN ++;
			if(iErrN >= 3)
			{
				ser.Close(handle);
				return FALSE;
			}
		}
		byteIN[iReceiveNum] = bb[0]; 
		if (bb[0] == '\n')
		{  
			byteIN[iReceiveNum] = bb[0]; 
			iReceiveNum ++;
			break;
		}
		iReceiveNum ++;
	}
	ser.Close(handle);

	int iB = 0;
	BOOL bStartValue = FALSE;
	CString strValue = "";
	int iStart[10];
	int iHaveDot = 0;
	for (i = iB; i < iReceiveNum; i ++)
	{
		if (byteIN[i] == ',')
		{
			iStart[iHaveDot] = i;
			iHaveDot++;
			bStartValue = FALSE;
		}
	}

	strValue = "";
	for (i = iStart[0]+1; i < iStart[1]; i ++)
	{
		strValue += byteIN[i];
	}
	fLC = (float)atof(strValue);
	if(fLC < 0)
		fLC = 0;
	return TRUE;
}
