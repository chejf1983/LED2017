
#include "stdafx.h"
#include "Comm.h"
#include "Serial.h"

CComm::CComm()
{
	m_strCOM = "COM1";
	m_iBaudrate = 9600;
	m_bDemo = FALSE;
}

CComm::~CComm()
{

}

void CComm::SetDemo(BOOL bDemo)
{
	m_bDemo = bDemo;
}

void CComm::SetBaudrate(int iBaudrate)
{
	m_iBaudrate = iBaudrate;
}

void CComm::SetCom(CString strCOM)
{
	m_strCOM = strCOM;
}

BOOL CComm::SetSV(int &iSTNo, float &fSV)
{
	BYTE Out[20], In[20];
	int iOutN;
	HANDLE comHandle;
	if(m_ser.Open(comHandle,m_strCOM, m_iBaudrate) == FALSE)
	{
		return FALSE;
	}
	
	iOutN = 0;
	
	// Station No.
	Out[iOutN] = iSTNo; 
	iOutN++;

	// Function Code
	Out[iOutN] = 0x06; 
	iOutN++;

	// Relative Address 			 
	Out[iOutN] = 0x03;
	iOutN++;
	Out[iOutN] = 0xEA;
	iOutN++;

	// Data: word
	int iTmp;
	WORD wyTmp;
	//	*10
	if (fSV >= 0)
	{
		iTmp = (int)((fSV+0.05)*10);
	}
	else
	{
		iTmp = (int)((fSV-0.05)*10);
	}
	wyTmp = iTmp;
	Out[iOutN] = wyTmp>>8;
	iOutN++;	
	Out[iOutN] = wyTmp & 0x00FF;
	iOutN++;

	// CRC
	WORD wdTmp = CalcCRC(iOutN, Out);
	if (wdTmp == 0xFFFF)
	{
		m_ser.Close(comHandle);
		return FALSE;
	}
	Out[iOutN] = wdTmp & 0x00FF;
	iOutN++;
	Out[iOutN] = wdTmp>>8;
	iOutN++;

	m_ser.Output(comHandle,Out, iOutN);
	m_ser.SetReadTime(comHandle,1000, 1, 1000);		
	m_ser.Input(comHandle,In, 7);

	if (In[0] != iSTNo)
	{
		m_ser.Close(comHandle);
		return FALSE;
	}

	if (In[1] != 0x06)
	{
		m_ser.Close(comHandle);
		return FALSE;
	}

	m_ser.Close(comHandle);
	return TRUE;
}

BOOL CComm::GetSV(int &iSTNo, float &fSV)
{
	BYTE Out[20], In[20];
	int iOutN;
	HANDLE comHandle;
	
	if(m_ser.Open(comHandle,m_strCOM, m_iBaudrate) == FALSE)
		return FALSE;
	
	iOutN = 0;
	
	// Station No.
	Out[iOutN] = iSTNo; 
	iOutN++;
	
	// Function Code
	Out[iOutN] = 0x03; 
	iOutN++;
	
	// Relative Address : 0002H 40003 
	Out[iOutN] = 0x03;
	iOutN++;
	Out[iOutN] = 0xEA;
	iOutN++;
				
	// Data: word
	Out[iOutN] = 0x00;
	iOutN++;
	Out[iOutN] = 0x01;
	iOutN++;
	
	// CRC
	WORD wdTmp = CalcCRC(iOutN, Out);
	if (wdTmp == 0xFFFF)
	{
		m_ser.Close(comHandle);
		return FALSE;
	}
	Out[iOutN] = wdTmp & 0x00FF;
	iOutN++;
	Out[iOutN] = wdTmp>>8;
	iOutN++;	
	
	
	m_ser.Output(comHandle,Out, iOutN);
	m_ser.SetReadTime(comHandle,1000, 1, 1000);	
	m_ser.Input(comHandle,In, 7);

	// Station No	
	if (In[0] != iSTNo)
	{
		m_ser.Close(comHandle);
		return FALSE;
	}

	// Function Code
	if (In[1] != 0x03)
	{
		m_ser.Close(comHandle);
		return FALSE;
	}

	// Byte Number
	if (In[2] != 2)
	{
		m_ser.Close(comHandle);
		return FALSE;
	}

	// Data
	// Data
	int i1,i2,i3,i4,iValue;
	i1 = In[3]>>4;
	i2 = In[3] & 0x0f;
	i3 = In[4]>>4;
	i4 = In[4] & 0x0f;
	iValue = i1*3364 + i2*256 + i3*16 + i4;
	fSV = iValue*1.0f/10;			
	
	m_ser.Close(comHandle);
	return TRUE;
}


BOOL CComm::WriteDataCommand(int &iSTNo, WORD WAddress, WORD wData)
{
    BYTE Out[20], In[20];
    int iOutN;
	HANDLE comHandle;
    if(m_ser.Open(comHandle,m_strCOM, m_iBaudrate) == FALSE)
    {
        return FALSE;
    }

    iOutN = 0;

    // Station No.
    Out[iOutN] = iSTNo; 
    iOutN++;

    // Function Code
    Out[iOutN] = 0x06; 
    iOutN++;

    // Relative Address 			 
    Out[iOutN] = WAddress / 256;
    iOutN++;
    Out[iOutN] = WAddress % 256;
    iOutN++;

    // Data: word
 
    Out[iOutN] = wData / 256;
    iOutN++;	
    Out[iOutN] = wData % 256;
    iOutN++;

    // CRC
    WORD wdTmp = CalcCRC(iOutN, Out);
    if (wdTmp == 0xFFFF)
    {
        m_ser.Close(comHandle);
        return FALSE;
    }
    Out[iOutN] = wdTmp & 0x00FF;
    iOutN++;
    Out[iOutN] = wdTmp>>8;
    iOutN++;


    m_ser.Output(comHandle,Out, iOutN);
    m_ser.SetReadTime(comHandle,1000, 1, 1000);		
    m_ser.Input(comHandle,In, 7);

    if (In[0] != iSTNo)
    {
        m_ser.Close(comHandle);
        return FALSE;
    }

    if (In[1] != 0x06)
    {
        m_ser.Close(comHandle);
        return FALSE;
    }

    m_ser.Close(comHandle);
    return TRUE;
}


BOOL CComm::ReadDataCommand(int &iSTNo, WORD WAddress, WORD &wData)
{
    BYTE Out[20], In[20];
    int iOutN;
	HANDLE comHandle;

    if(m_ser.Open(comHandle,m_strCOM, m_iBaudrate) == FALSE)
        return FALSE;

    iOutN = 0;

    // Station No.
    Out[iOutN] = iSTNo; 
    iOutN++;

    // Function Code
    Out[iOutN] = 0x03; 
    iOutN++;

    // Relative Address : 0002H 40003 
    Out[iOutN] = WAddress / 256;
    iOutN++;
    Out[iOutN] = WAddress % 256;
    iOutN++;

    // Data: word
    Out[iOutN] = 0x00;
    iOutN++;
    Out[iOutN] = 0x01;
    iOutN++;

    // CRC
    WORD wdTmp = CalcCRC(iOutN, Out);
    if (wdTmp == 0xFFFF)
    {
        m_ser.Close(comHandle);
        return FALSE;
    }
    Out[iOutN] = wdTmp & 0x00FF;
    iOutN++;
    Out[iOutN] = wdTmp>>8;
    iOutN++;	


    m_ser.Output(comHandle,Out, iOutN);
    m_ser.SetReadTime(comHandle,1000, 1, 1000);	
    m_ser.Input(comHandle,In, 7);

    // Station No	
    if (In[0] != iSTNo)
    {
        m_ser.Close(comHandle);
        return FALSE;
    }

    // Function Code
    if (In[1] != 0x03)
    {
        m_ser.Close(comHandle);
        return FALSE;
    }

    // Byte Number
    if (In[2] != 2)
    {
        m_ser.Close(comHandle);
        return FALSE;
    }

    // Data
    // Data			
    wData =  In[3] * 256 + In[4];
    m_ser.Close(comHandle);
    return TRUE;
}


BOOL CComm::SetSelfTruningMode(int &iSTNo)
{
    return WriteDataCommand(iSTNo, 0x03E9, 0x0002);
    BYTE Out[20], In[20];
    int iOutN;
	HANDLE comHandle;

    if(m_ser.Open(comHandle,m_strCOM, m_iBaudrate) == FALSE)
    {
        return FALSE;
    }

    iOutN = 0;

    // Station No.
    Out[iOutN] = iSTNo; 
    iOutN++;

    // Function Code
    Out[iOutN] = 0x06; 
    iOutN++;

    // Relative Address 			 
    Out[iOutN] = 0x03;
    iOutN++;
    Out[iOutN] = 0xE9;
    iOutN++;

    // Data: word

    Out[iOutN] = 0x00;
    iOutN++;	
    Out[iOutN] = 0x02;
    iOutN++;

    // CRC
    WORD wdTmp = CalcCRC(iOutN, Out);
    if (wdTmp == 0xFFFF)
    {
        m_ser.Close(comHandle);
        return FALSE;
    }
    Out[iOutN] = wdTmp & 0x00FF;
    iOutN++;
    Out[iOutN] = wdTmp>>8;
    iOutN++;


    m_ser.Output(comHandle,Out, iOutN);
    m_ser.SetReadTime(comHandle,1000, 1, 1000);		
    m_ser.Input(comHandle,In, 7);

    if (In[0] != iSTNo)
    {
        m_ser.Close(comHandle);
        return FALSE;
    }

    if (In[1] != 0x06)
    {
        m_ser.Close(comHandle);
        return FALSE;
    }

    m_ser.Close(comHandle);
    return TRUE;
}


BOOL CComm::SetPIDTruning(int &iSTNo)
{
    return WriteDataCommand(iSTNo, 0x03EC, 0x0001);
    BYTE Out[20], In[20];
    int iOutN;
	HANDLE comHandle;

    if(m_ser.Open(comHandle,m_strCOM, m_iBaudrate) == FALSE)
    {
        return FALSE;
    }

    iOutN = 0;

    // Station No.
    Out[iOutN] = iSTNo; 
    iOutN++;

    // Function Code
    Out[iOutN] = 0x06; 
    iOutN++;

    // Relative Address 			 
    Out[iOutN] = 0x03;
    iOutN++;
    Out[iOutN] = 0xEC;
    iOutN++;

    // Data: word

    Out[iOutN] = 0x00;
    iOutN++;	
    Out[iOutN] = 0x01;
    iOutN++;

    // CRC
    WORD wdTmp = CalcCRC(iOutN, Out);
    if (wdTmp == 0xFFFF)
    {
        m_ser.Close(comHandle);
        return FALSE;
    }
    Out[iOutN] = wdTmp & 0x00FF;
    iOutN++;
    Out[iOutN] = wdTmp>>8;
    iOutN++;


    m_ser.Output(comHandle,Out, iOutN);
    m_ser.SetReadTime(comHandle,1000, 1, 1000);		
    m_ser.Input(comHandle,In, 7);

    if (In[0] != iSTNo)
    {
        m_ser.Close(comHandle);
        return FALSE;
    }

    if (In[1] != 0x06)
    {
        m_ser.Close(comHandle);
        return FALSE;
    }

    m_ser.Close(comHandle);
    return TRUE;
}


BOOL CComm::GetPIDTruningState(int &iSTNo, int &iState)
{
    WORD wRetrun;
    if (!ReadDataCommand(iSTNo, 0x03EC, wRetrun))
    {
        return FALSE;
    }
    else
    {
        iState = wRetrun;
        return TRUE;
    }

    BYTE Out[20], In[20];
    int iOutN;
	HANDLE comHandle;
    if(m_ser.Open(comHandle,m_strCOM, m_iBaudrate) == FALSE)
        return FALSE;

    iOutN = 0;

    // Station No.
    Out[iOutN] = iSTNo; 
    iOutN++;

    // Function Code
    Out[iOutN] = 0x03; 
    iOutN++;

    // Relative Address 
    Out[iOutN] = 0x03;
    iOutN++;
    Out[iOutN] = 0xEC;
    iOutN++;

    // Data: word
    Out[iOutN] = 0x00;
    iOutN++;
    Out[iOutN] = 0x01;
    iOutN++;

    // CRC
    WORD wdTmp = CalcCRC(iOutN, Out);
    if (wdTmp == 0xFFFF)
    {
        m_ser.Close(comHandle);
        return FALSE;
    }
    Out[iOutN] = wdTmp & 0x00FF;
    iOutN++;
    Out[iOutN] = wdTmp>>8;
    iOutN++;	


    m_ser.Output(comHandle,Out, iOutN);
    m_ser.SetReadTime(comHandle,1000, 1, 1000);	
    m_ser.Input(comHandle,In, 7);

    // Station No	
    if (In[0] != iSTNo)
    {
        m_ser.Close(comHandle);
        return FALSE;
    }

    // Function Code
    if (In[1] != 0x03)
    {
        m_ser.Close(comHandle);
        return FALSE;
    }

    // Byte Number
    if (In[2] != 2)
    {
        m_ser.Close(comHandle);
        return FALSE;
    }

    // Data
    // Data
    int i1,i2,i3,i4,iValue;
    i1 = In[3]>>4;
    i2 = In[3] & 0x0f;
    i3 = In[4]>>4;
    i4 = In[4] & 0x0f;
    iValue = i1*3364 + i2*256 + i3*16 + i4;
    iState = iValue;			

    m_ser.Close(comHandle);
    return TRUE;
}


BOOL CComm::GetPID(int &iSTNo, float &fP, float &fI, float &fD)
{
    WORD wRetrun;
    int i1,i2,i3,i4,iValue;
    if (!ReadDataCommand(iSTNo, 0x03ED, wRetrun))
    {
        return FALSE;
    }
    i1 = wRetrun / 3364;
    i2 = wRetrun % 3364 / 256;
    i3 = wRetrun % 256 / 16;
    i4 = wRetrun % 16;
    iValue = i1*3364 + i2*256 + i3*16 + i4;
    fP =  iValue * 1.0f / 10;
    if (!ReadDataCommand(iSTNo, 0x03EE, wRetrun))
    {
        return FALSE;
    }
    i1 = wRetrun / 3364;
    i2 = wRetrun % 3364 / 256;
    i3 = wRetrun % 256 / 16;
    i4 = wRetrun % 16;
    iValue = i1*3364 + i2*256 + i3*16 + i4;
    fI =  iValue * 1.0f / 10;
    if (!ReadDataCommand(iSTNo, 0x03EF, wRetrun))
    {
        return FALSE;
    }
    i1 = wRetrun / 3364;
    i2 = wRetrun % 3364 / 256;
    i3 = wRetrun % 256 / 16;
    i4 = wRetrun % 16;
    iValue = i1*3364 + i2*256 + i3*16 + i4;
    fD =  iValue * 1.0f / 10;
    return TRUE;    
}


BOOL CComm::GetPV(int &iSTNo, float &fPV)
{
	HANDLE comHandle = NULL;
	BYTE Out[20], In[20];
	int iOutN;
	BOOL bR;
	
	bR = m_ser.Open(comHandle, m_strCOM, m_iBaudrate);
	if (!bR)
	{
		return FALSE;
	}

	iOutN = 0;
	
	// Station No.
	Out[iOutN] = iSTNo; 
	iOutN++;
	
	// Function Code
	Out[iOutN] = 0x04; 
	iOutN++;
	
	// Relative Address
	Out[iOutN] = 0x03;
	iOutN++;
	Out[iOutN] = 0xE8;
	iOutN++;
	
	// Data: word
	Out[iOutN] = 0x00;
	iOutN++;
	Out[iOutN] = 0x01;
	iOutN++;
	
	// CRC
	WORD wdTmp = CalcCRC(iOutN, Out);
	if (wdTmp == 0xFFFF)
	{
		m_ser.Close(comHandle);
		return FALSE;
	}
	
	Out[iOutN] = wdTmp & 0x00FF;
	iOutN++;
	Out[iOutN] = wdTmp>>8;
	iOutN++;			
	
	bR = m_ser.Output(comHandle,Out, iOutN);
	bR = m_ser.SetReadTime(comHandle,2000, 1, 2000);	
	bR = m_ser.Input(comHandle,In, 7);
	
	// Station No	
	if (In[0] != iSTNo)
	{
		m_ser.Close(comHandle);
		return FALSE;
	}
	
	// Function Code
	if (In[1] != 0x04)
	{
		m_ser.Close(comHandle);
		return FALSE;
	}
	
	// Byte Number
	if (In[2] != 2)
	{
		m_ser.Close(comHandle);
		return FALSE;
	}
	
	// Data
	int i1,i2,i3,i4,iValue;
	i1 = In[3]>>4;
	i2 = In[3] & 0x0f;
	i3 = In[4]>>4;
	i4 = In[4] & 0x0f;
	iValue = i1*3364 + i2*256 + i3*16 + i4;
	fPV = iValue*1.0f/10;			

	m_ser.Close(comHandle);
	return TRUE;
}

BOOL CComm::StartHeater(int &iSTNo)
{
	HANDLE comHandle = NULL;
	BYTE Out[20], In[20];
	int iOutN;
	BOOL bR;
	
	bR = m_ser.Open(comHandle,m_strCOM, m_iBaudrate);
	if (!bR)
	{
		return FALSE;
	}
	
	iOutN = 0;
	
	// Station No.
	Out[iOutN] = iSTNo; 
	iOutN++;
	
	// Function Code
	Out[iOutN] = 0x06; 
	iOutN++;
	
	// Relative Address
	Out[iOutN] = 0x04;
	iOutN++;
	Out[iOutN] = 0x39;
	iOutN++;
	
	// Data: word
	Out[iOutN] = 0x00;
	iOutN++;
	Out[iOutN] = 0x01;
	iOutN++;
	
	// CRC
	WORD wdTmp = CalcCRC(iOutN, Out);
	if (wdTmp == 0xFFFF)
	{
		m_ser.Close(comHandle);
		return FALSE;
	}
	
	Out[iOutN] = wdTmp & 0x00FF;
	iOutN++;
	Out[iOutN] = wdTmp>>8;
	iOutN++;			
	
	bR = m_ser.Output(comHandle,Out, iOutN);
	bR = m_ser.SetReadTime(comHandle,2000, 1, 2000);	
	bR = m_ser.Input(comHandle,In, 7);
	
	// Station No	
	if (In[0] != iSTNo)
	{
		m_ser.Close(comHandle);
		return FALSE;
	}
	
	// Function Code
	if (In[1] != 0x06)
	{
		m_ser.Close(comHandle);
		return FALSE;
	}
	
	// Byte Number
/*
	if (In[2] != 2)
	{
		m_ser.Close(hCommDev);
		return FALSE;
	}*/

	
	// Data

	
	m_ser.Close(comHandle);
	return TRUE;
}

BOOL CComm::StopHeater(int &iSTNo)
{
	return TRUE;
}

BOOL CComm::StandbyOn(int &iSTNo)
{
	BYTE Out[20], In[20];
	int iOutN;
	BOOL bR;
	HANDLE comHandle = NULL;
	
	if(!m_ser.Open(comHandle,m_strCOM, m_iBaudrate))
	{
		return FALSE;
	}
	
	iOutN = 0;
	
	// Station No.
	Out[iOutN] = iSTNo; 
	iOutN++;
	
	// Function Code
	Out[iOutN] = 0x06; 
	iOutN++;
	
	// Relative Address : 0003H 40004 
	Out[iOutN] = 0x03;
	iOutN++;
	Out[iOutN] = 0xEB;
	iOutN++;
	
	// Data : Validate standby STby
	Out[iOutN] = 0x00;
	iOutN++;
	Out[iOutN] = 0x01;
	iOutN++;	
	
	// CRC
	WORD wdTmp = CalcCRC(iOutN, Out);
	if (wdTmp == 0xFFFF)
	{
		m_ser.Close(comHandle);
		return FALSE;
	}
	Out[iOutN] = wdTmp & 0x00FF;
	iOutN++;
	Out[iOutN] = wdTmp>>8;
	iOutN++;	
	
	bR = m_ser.Output(comHandle,Out, iOutN);
	bR = m_ser.SetReadTime(comHandle,2000, 1, 2000);		
	bR =m_ser.Input(comHandle,In, 8);
	
	if (In[0] != iSTNo)
	{
		m_ser.Close(comHandle);
		return FALSE;
	}
	
	if (In[1] != 0x06)
	{
		m_ser.Close(comHandle);
		return FALSE;
	}
	
	m_ser.Close(comHandle);
	return TRUE;
}

BOOL CComm::StandbyOff(int &iSTNo)
{
	BYTE Out[20], In[20];
	int iOutN;
	BOOL bR;
	HANDLE comHandle = NULL;
	
	if(!m_ser.Open(comHandle,m_strCOM, m_iBaudrate))
	{
		return FALSE;
	}
	
	iOutN = 0;
	
	// Station No.
	Out[iOutN] = iSTNo; 
	iOutN++;
	
	// Function Code
	Out[iOutN] = 0x06; 
	iOutN++;
	
	// Relative Address : 0003H 40004 
	Out[iOutN] = 0x03; 
	iOutN++;
	Out[iOutN] = 0xEB; 
	iOutN++;
	
	// Data: 0 Invalidate standby (RUN)
	Out[iOutN] = 0x00;
	iOutN++;
	Out[iOutN] = 0x00;
	iOutN++;
	
	// CRC
	WORD wdTmp = CalcCRC(iOutN, Out);
	if (wdTmp == 0xFFFF)
	{
		m_ser.Close(comHandle);
		return FALSE;
	}
	Out[iOutN] = wdTmp & 0x00FF;
	iOutN++;
	Out[iOutN] = wdTmp>>8;
	iOutN++;	
	
	bR = m_ser.Output(comHandle,Out, iOutN);
	bR = m_ser.SetReadTime(comHandle,2000, 1, 2000);		
	bR = m_ser.Input(comHandle,In, 8);
	
	if (In[0] != iSTNo)
	{
		m_ser.Close(comHandle);
		return FALSE;
	}
	
	if (In[1] != 0x06)
	{
		m_ser.Close(comHandle);
		return FALSE;
	}
	
	m_ser.Close(comHandle);
	return TRUE;
}

WORD CComm::CalcCRC(int& iDataNum, BYTE* pOutArray)
{
	WORD CR = 0xFFFF;

	if (pOutArray == NULL)
		return CR;

	int i, j;
	
	for (i = 0; i < iDataNum; i++)
	{		
		CR = CR ^ *(pOutArray + i);

		for (j = 0; j < 8; j++)
		{						
			if ((CR & 0x0001) == 1)
			{
				CR >>= 1;
				CR = CR ^ 0xA001;
			}
			else			
				CR >>= 1;			
		}					
	}

	return CR;
}


BOOL CComm::SetP_n2Type(int &iSTNo)
{
    Sleep(100);
    return WriteDataCommand(iSTNo, 0x03F7, 3);
}


BOOL CComm::SetP_dPType(int &iSTNo)
{
 //   return WriteDataCommand(iSTNo, 0x0013, 0);
    Sleep(200);
    // set Decimal point place 1
    if (!WriteDataCommand(iSTNo, 0x03FB, 1))
    {
        return FALSE;
    }
    Sleep(200);
    // set P_SU 
    if (!WriteDataCommand(iSTNo, 0x03FA, 1500))
    {
        return FALSE;
    }
    return TRUE; 
    
}