#include "StdAfx.h"
#include "HandAutoComm.h"

extern BOOL g_bDemo;


CHandAutoComm::CHandAutoComm(void)
{
	m_iBaudRate		= 9600;
	InitializeCriticalSection(&m_critical);
}

CHandAutoComm::~CHandAutoComm(void)
{
}

void CHandAutoComm::Initialize(CString strCOM)
{
	m_strCOM = strCOM;
}

void CHandAutoComm::SetDemo(BOOL bDemo)
{
    m_bDemo = bDemo;
}

BOOL CHandAutoComm::WriteToHandInpos(BOOL bInpos)
{
	//写到位信息
	if (g_bDemo)
	{
		return TRUE;
	}
	EnterCriticalSection(&m_critical);
	Sleep(100);
	HANDLE comHandle;
	if (!m_ser.Open(comHandle,m_strCOM, m_iBaudRate))
	{
		LeaveCriticalSection(&m_critical);
		return FALSE;
	}
	m_ser.SetReadTime(comHandle,5000, 1, 5000);
	CString strTemp;
	if (bInpos)
	{
		strTemp = "@00WD0400000156*";
	}
	else
	{
		strTemp = "@00WD0400000057*";
	}
	BYTE ucOut[256];
	BYTE ucIn[256];
	int i;
	for (i = 0; i < strTemp.GetLength(); i++)
	{
		ucOut[i] = strTemp.GetAt(i);
	}
	ucOut[i] = 0x0D;
	m_ser.Output(comHandle,ucOut, strTemp.GetLength() + 1);
	//先收命令反码数据
	if (!m_ser.Input(comHandle,ucIn, 11))
	{
		LeaveCriticalSection(&m_critical);
		m_ser.Close(comHandle);
		return FALSE;
	}
	strTemp = ucIn;
	CString strRe;
	if (bInpos)
		strRe = "@00WD0053*";
	else
		strRe = "@00WD0053*";
// 	if(strRe != strTemp)
// 	{
// 		LeaveCriticalSection(&m_critical);
// 		m_ser.Close(comHandle);
// 		return FALSE;
// 	}
	
	m_ser.Close(comHandle);
	Sleep(500);
	LeaveCriticalSection(&m_critical);
	return TRUE;
}

BOOL CHandAutoComm::ReadHandState(BOOL &bAllowMove)
{
	//读机械手状态 是否允许移动
	if (g_bDemo)
	{
		Sleep(500);
		bAllowMove = TRUE;
		return TRUE;
	}
	EnterCriticalSection(&m_critical);
	Sleep(100);
	HANDLE comHandle;
	if (!m_ser.Open(comHandle,m_strCOM, m_iBaudRate))
	{
		LeaveCriticalSection(&m_critical);
		return FALSE;
	}
	m_ser.SetReadTime(comHandle,5000, 1, 5000);
	CString strTemp;
	strTemp = "@00RD0402000151*";
	BYTE ucOut[256];
	BYTE ucIn[256];
	int i;
	for (i = 0; i < strTemp.GetLength(); i++)
	{
		ucOut[i] = strTemp.GetAt(i);
	}
	ucOut[i] = 0x0D;
	m_ser.Output(comHandle,ucOut, strTemp.GetLength() + 1);
	//先收命令反码数据
	if (!m_ser.Input(comHandle,ucIn, 15))
	{
		LeaveCriticalSection(&m_critical);
		m_ser.Close(comHandle);
		return FALSE;
	}
	strTemp = ucIn;
	bAllowMove = FALSE;
	if(ucIn[10] == '1')//strTemp == "@00RD00000157*")
	{
		bAllowMove = TRUE;
	}
	else// if(//strTemp == "@00RD00000056*")
	{
		bAllowMove = FALSE;
	}
// 	else
// 	{
// 		LeaveCriticalSection(&m_critical);
// 		m_ser.Close(comHandle);
// 		return FALSE;
// 	}

	m_ser.Close(comHandle);
	Sleep(500);
	LeaveCriticalSection(&m_critical);
	return TRUE;
}

BOOL CHandAutoComm::WriteToHandLamp(int iChannelOK[])
{
	//写合格与否信息到PLC中
	if (g_bDemo)
	{
		return TRUE;
	}
	EnterCriticalSection(&m_critical);
	Sleep(100);
	HANDLE comHandle;
	if (!m_ser.Open(comHandle,m_strCOM, m_iBaudRate))
	{
		LeaveCriticalSection(&m_critical);
		return FALSE;
	}
	m_ser.SetReadTime(comHandle,5000, 1, 5000);
	//颠倒一下
	
	BYTE ucOut[256];
	BYTE ucIn[256];
	int iIn = 0;
	if (1)
	{
		//说明 合格和不合格信号有多种
		//D404 放合格与否信号 如果全是0 说明合格
		ucOut[0] = '@';
		ucOut[1] = '0';
		ucOut[2] = '0';
		ucOut[3] = 'W';
		ucOut[4] = 'D';
		ucOut[5] = '0';
		ucOut[6] = '4';
		ucOut[7] = '0';
		ucOut[8] = '4';
		BYTE bTemp1 = 0x00;
		BYTE bTemp2 = 0x00;
		bTemp1 = 0x00;	//12-15
		bTemp1 |= iChannelOK[9] == 0 ? 1 << 1 : 0;	//8-10 大于0 都是不合格
		bTemp1 |= iChannelOK[8] == 0 ? 1 << 0 : 0;
		bTemp2 |= iChannelOK[7] == 0 ? 1 << 7 : 0;	//4-7
		bTemp2 |= iChannelOK[6] == 0 ? 1 << 6 : 0;
		bTemp2 |= iChannelOK[5] == 0 ? 1 << 5 : 0;
		bTemp2 |= iChannelOK[4] == 0 ? 1 << 4 : 0;
		bTemp2 |= iChannelOK[3] == 0 ? 1 << 3 : 0;	//0-3
		bTemp2 |= iChannelOK[2] == 0 ? 1 << 2 : 0;
		bTemp2 |= iChannelOK[1] == 0 ? 1 << 1 : 0;
		bTemp2 |= iChannelOK[0] == 0 ? 1 << 0 : 0;
		BYTE bb;
		bb = bTemp1/16;
		if (bb > 9)
		{
			ucOut[9]  = bb + 0x37;
		}
		else
		{
			ucOut[9]  = bb + 0x30;
		}

		bb = bTemp1%16;
		if (bb > 9)
		{
			ucOut[10]  = bb + 0x37;
		}
		else
		{
			ucOut[10]  = bb + 0x30;
		}

		bb = bTemp2/16;
		if (bb > 9)
		{
			ucOut[11]  = bb + 0x37;
		}
		else
		{
			ucOut[11]  = bb + 0x30;
		}
		bb = bTemp2%16;
		if (bb > 9)
		{
			ucOut[12]  = bb + 0x37;
		}
		else
		{
			ucOut[12]  = bb + 0x30;
		}
		BYTE bSum = 0;
		for (int i = 0; i < 13; i++)
		{
			bSum = bSum ^ ucOut[i];
		}
		bb =  bSum/16;
		if (bb > 9)
		{
			ucOut[13]  = bb + 0x37;
		}
		else
		{
			ucOut[13]  = bb + 0x30;
		}
		bb =  bSum%16;
		if (bb > 9)
		{
			ucOut[14]  = bb + 0x37;
		}
		else
		{
			ucOut[14]  = bb + 0x30;
		}
		ucOut[15] = '*';
		ucOut[16] = 0x0D;
		m_ser.Output(comHandle,ucOut, 17);
		//先收命令反码数据
		if (!m_ser.Input(comHandle,ucIn, 11))
		{
			LeaveCriticalSection(&m_critical);
			m_ser.Close(comHandle);
			return FALSE;
		}
		CString strTemp;
		strTemp = ucIn;
// 		if(strTemp == "@00WD0053*")
// 		{
// 			//OK
// 		}
// 		else
// 		{
// 			LeaveCriticalSection(&m_critical);
// 			m_ser.Close(comHandle);
// 			return FALSE;
// 		}
	}
	
	if (1)
	{
		//D406 不合格种类1 电参数不合格（合格为0）
		ucOut[0] = '@';
		ucOut[1] = '0';
		ucOut[2] = '0';
		ucOut[3] = 'W';
		ucOut[4] = 'D';
		ucOut[5] = '0';
		ucOut[6] = '4';
		ucOut[7] = '0';
		ucOut[8] = '6';
		BYTE bTemp1 = 0x00;
		BYTE bTemp2 = 0x00;
		bTemp1 = 0x00;	//12-15
		bTemp1 |= iChannelOK[9] == 1 ? 1 << 1 : 0;	//8-10 大于0 都是不合格
		bTemp1 |= iChannelOK[8] == 1 ? 1 << 0 : 0;
		bTemp2 |= iChannelOK[7] == 1 ? 1 << 7 : 0;	//4-7
		bTemp2 |= iChannelOK[6] == 1 ? 1 << 6 : 0;
		bTemp2 |= iChannelOK[5] == 1 ? 1 << 5 : 0;
		bTemp2 |= iChannelOK[4] == 1 ? 1 << 4 : 0;
		bTemp2 |= iChannelOK[3] == 1 ? 1 << 3 : 0;	//0-3
		bTemp2 |= iChannelOK[2] == 1 ? 1 << 2 : 0;
		bTemp2 |= iChannelOK[1] == 1 ? 1 << 1 : 0;
		bTemp2 |= iChannelOK[0] == 1 ? 1 << 0 : 0;
		BYTE bb;
		bb = bTemp1/16;
		if (bb > 9)
		{
			ucOut[9]  = bb + 0x37;
		}
		else
		{
			ucOut[9]  = bb + 0x30;
		}

		bb = bTemp1%16;
		if (bb > 9)
		{
			ucOut[10]  = bb + 0x37;
		}
		else
		{
			ucOut[10]  = bb + 0x30;
		}

		bb = bTemp2/16;
		if (bb > 9)
		{
			ucOut[11]  = bb + 0x37;
		}
		else
		{
			ucOut[11]  = bb + 0x30;
		}
		bb = bTemp2%16;
		if (bb > 9)
		{
			ucOut[12]  = bb + 0x37;
		}
		else
		{
			ucOut[12]  = bb + 0x30;
		}

		BYTE bSum = 0;
		for (int i = 0; i < 13; i++)
		{
			bSum = bSum ^ ucOut[i];
		}
		bb =  bSum/16;
		if (bb > 9)
		{
			ucOut[13]  = bb + 0x37;
		}
		else
		{
			ucOut[13]  = bb + 0x30;
		}
		bb =  bSum%16;
		if (bb > 9)
		{
			ucOut[14]  = bb + 0x37;
		}
		else
		{
			ucOut[14]  = bb + 0x30;
		}
		ucOut[15] = '*';
		ucOut[16] = 0x0D;
		m_ser.Output(comHandle,ucOut, 17);
		//先收命令反码数据
		if (!m_ser.Input(comHandle,ucIn, 11))
		{
			LeaveCriticalSection(&m_critical);
			m_ser.Close(comHandle);
			return FALSE;
		}
		CString strTemp;
		strTemp = ucIn;
// 		if(strTemp == "@00WD0053* ")
// 		{
// 		}
// 		else
// 		{
// 			LeaveCriticalSection(&m_critical);
// 			m_ser.Close(comHandle);
// 			return FALSE;
// 		}
	}

	if (1)
	{
		//D408 不合格种类2 光通量不合格（合格为0）
		ucOut[0] = '@';
		ucOut[1] = '0';
		ucOut[2] = '0';
		ucOut[3] = 'W';
		ucOut[4] = 'D';
		ucOut[5] = '0';
		ucOut[6] = '4';
		ucOut[7] = '0';
		ucOut[8] = '8';
		BYTE bTemp1 = 0x00;
		BYTE bTemp2 = 0x00;
		bTemp1 = 0x00;	//12-15
		bTemp1 |= iChannelOK[9] == 2 ? 1 << 1 : 0;	//8-10 大于0 都是不合格
		bTemp1 |= iChannelOK[8] == 2 ? 1 << 0 : 0;
		bTemp2 |= iChannelOK[7] == 2 ? 1 << 7 : 0;	//4-7
		bTemp2 |= iChannelOK[6] == 2 ? 1 << 6 : 0;
		bTemp2 |= iChannelOK[5] == 2 ? 1 << 5 : 0;
		bTemp2 |= iChannelOK[4] == 2 ? 1 << 4 : 0;
		bTemp2 |= iChannelOK[3] == 2 ? 1 << 3 : 0;	//0-3
		bTemp2 |= iChannelOK[2] == 2 ? 1 << 2 : 0;
		bTemp2 |= iChannelOK[1] == 2 ? 1 << 1 : 0;
		bTemp2 |= iChannelOK[0] == 2 ? 1 << 0 : 0;
		BYTE bb;
		bb = bTemp1/16;
		if (bb > 9)
		{
			ucOut[9]  = bb + 0x37;
		}
		else
		{
			ucOut[9]  = bb + 0x30;
		}

		bb = bTemp1%16;
		if (bb > 9)
		{
			ucOut[10]  = bb + 0x37;
		}
		else
		{
			ucOut[10]  = bb + 0x30;
		}

		bb = bTemp2/16;
		if (bb > 9)
		{
			ucOut[11]  = bb + 0x37;
		}
		else
		{
			ucOut[11]  = bb + 0x30;
		}
		bb = bTemp2%16;
		if (bb > 9)
		{
			ucOut[12]  = bb + 0x37;
		}
		else
		{
			ucOut[12]  = bb + 0x30;
		}
		BYTE bSum = 0;
		for (int i = 0; i < 13; i++)
		{
			bSum = bSum ^ ucOut[i];
		}
		bb =  bSum/16;
		if (bb > 9)
		{
			ucOut[13]  = bb + 0x37;
		}
		else
		{
			ucOut[13]  = bb + 0x30;
		}
		bb =  bSum%16;
		if (bb > 9)
		{
			ucOut[14]  = bb + 0x37;
		}
		else
		{
			ucOut[14]  = bb + 0x30;
		}
		ucOut[15] = '*';
		ucOut[16] = 0x0D;
		m_ser.Output(comHandle,ucOut, 17);
		//先收命令反码数据
		if (!m_ser.Input(comHandle,ucIn, 11))
		{
			LeaveCriticalSection(&m_critical);
			m_ser.Close(comHandle);
			return FALSE;
		}
		CString strTemp;
		strTemp = ucIn;
// 		if(strTemp == "@00WD0053* ")
// 		{
// 		}
// 		else
// 		{
// 			LeaveCriticalSection(&m_critical);
// 			m_ser.Close(comHandle);
// 			return FALSE;
// 		}
	}

	if (1)
	{
		//D410 不合格种类3 色容差不合格（合格为0）
		ucOut[0] = '@';
		ucOut[1] = '0';
		ucOut[2] = '0';
		ucOut[3] = 'W';
		ucOut[4] = 'D';
		ucOut[5] = '0';
		ucOut[6] = '4';
		ucOut[7] = '1';
		ucOut[8] = '0';
		BYTE bTemp1 = 0x00;
		BYTE bTemp2 = 0x00;
		bTemp1 = 0x00;	//12-15
		bTemp1 |= iChannelOK[9] == 3 ? 1 << 1 : 0;	//8-10 大于0 都是不合格
		bTemp1 |= iChannelOK[8] == 3 ? 1 << 0 : 0;
		bTemp2 |= iChannelOK[7] == 3 ? 1 << 7 : 0;	//4-7
		bTemp2 |= iChannelOK[6] == 3 ? 1 << 6 : 0;
		bTemp2 |= iChannelOK[5] == 3 ? 1 << 5 : 0;
		bTemp2 |= iChannelOK[4] == 3 ? 1 << 4 : 0;
		bTemp2 |= iChannelOK[3] == 3 ? 1 << 3 : 0;	//0-3
		bTemp2 |= iChannelOK[2] == 3 ? 1 << 2 : 0;
		bTemp2 |= iChannelOK[1] == 3 ? 1 << 1 : 0;
		bTemp2 |= iChannelOK[0] == 3 ? 1 << 0 : 0;
		BYTE bb;
		bb = bTemp1/16;
		if (bb > 9)
		{
			ucOut[9]  = bb + 0x37;
		}
		else
		{
			ucOut[9]  = bb + 0x30;
		}

		bb = bTemp1%16;
		if (bb > 9)
		{
			ucOut[10]  = bb + 0x37;
		}
		else
		{
			ucOut[10]  = bb + 0x30;
		}

		bb = bTemp2/16;
		if (bb > 9)
		{
			ucOut[11]  = bb + 0x37;
		}
		else
		{
			ucOut[11]  = bb + 0x30;
		}
		bb = bTemp2%16;
		if (bb > 9)
		{
			ucOut[12]  = bb + 0x37;
		}
		else
		{
			ucOut[12]  = bb + 0x30;
		}
		BYTE bSum = 0;
		for (int i = 0; i < 13; i++)
		{
			bSum = bSum ^ ucOut[i];
		}
		bb =  bSum/16;
		if (bb > 9)
		{
			ucOut[13]  = bb + 0x37;
		}
		else
		{
			ucOut[13]  = bb + 0x30;
		}
		bb =  bSum%16;
		if (bb > 9)
		{
			ucOut[14]  = bb + 0x37;
		}
		else
		{
			ucOut[14]  = bb + 0x30;
		}
		ucOut[15] = '*';
		ucOut[16] = 0x0D;
		m_ser.Output(comHandle,ucOut, 17);
		//先收命令反码数据
		if (!m_ser.Input(comHandle,ucIn, 11))
		{
			LeaveCriticalSection(&m_critical);
			m_ser.Close(comHandle);
			return FALSE;
		}
		CString strTemp;
		strTemp = ucIn;
// 		if(strTemp == "@00WD0053* ")
// 		{
// 		}
// 		else
// 		{
// 			LeaveCriticalSection(&m_critical);
// 			m_ser.Close(comHandle);
// 			return FALSE;
// 		}
	}
	if (1)
	{
		//D412 不合格种类4 其他参数不合格（合格为0）
		ucOut[0] = '@';
		ucOut[1] = '0';
		ucOut[2] = '0';
		ucOut[3] = 'W';
		ucOut[4] = 'D';
		ucOut[5] = '0';
		ucOut[6] = '4';
		ucOut[7] = '1';
		ucOut[8] = '2';
		BYTE bTemp1 = 0x00;
		BYTE bTemp2 = 0x00;
		bTemp1 = 0x00;	//12-15
		bTemp1 |= iChannelOK[9] == 4 ? 1 << 1 : 0;	//8-10 大于0 都是不合格
		bTemp1 |= iChannelOK[8] == 4 ? 1 << 0 : 0;
		bTemp2 |= iChannelOK[7] == 4 ? 1 << 7 : 0;	//4-7
		bTemp2 |= iChannelOK[6] == 4 ? 1 << 6 : 0;
		bTemp2 |= iChannelOK[5] == 4 ? 1 << 5 : 0;
		bTemp2 |= iChannelOK[4] == 4 ? 1 << 4 : 0;
		bTemp2 |= iChannelOK[3] == 4 ? 1 << 3 : 0;	//0-3
		bTemp2 |= iChannelOK[2] == 4 ? 1 << 2 : 0;
		bTemp2 |= iChannelOK[1] == 4 ? 1 << 1 : 0;
		bTemp2 |= iChannelOK[0] == 4 ? 1 << 0 : 0;
		BYTE bb;
		bb = bTemp1/16;
		if (bb > 9)
		{
			ucOut[9]  = bb + 0x37;
		}
		else
		{
			ucOut[9]  = bb + 0x30;
		}

		bb = bTemp1%16;
		if (bb > 9)
		{
			ucOut[10]  = bb + 0x37;
		}
		else
		{
			ucOut[10]  = bb + 0x30;
		}

		bb = bTemp2/16;
		if (bb > 9)
		{
			ucOut[11]  = bb + 0x37;
		}
		else
		{
			ucOut[11]  = bb + 0x30;
		}
		bb = bTemp2%16;
		if (bb > 9)
		{
			ucOut[12]  = bb + 0x37;
		}
		else
		{
			ucOut[12]  = bb + 0x30;
		}
		BYTE bSum = 0;
		for (int i = 0; i < 13; i++)
		{
			bSum = bSum ^ ucOut[i];
		}
		bb =  bSum/16;
		if (bb > 9)
		{
			ucOut[13]  = bb + 0x37;
		}
		else
		{
			ucOut[13]  = bb + 0x30;
		}
		bb =  bSum%16;
		if (bb > 9)
		{
			ucOut[14]  = bb + 0x37;
		}
		else
		{
			ucOut[14]  = bb + 0x30;
		}
		ucOut[15] = '*';
		ucOut[16] = 0x0D;
		m_ser.Output(comHandle,ucOut, 17);
		//先收命令反码数据
		if (!m_ser.Input(comHandle,ucIn, 11))
		{
			LeaveCriticalSection(&m_critical);
			m_ser.Close(comHandle);
			return FALSE;
		}
		CString strTemp;
		strTemp = ucIn;
// 		if(strTemp == "@00WD0053* ")
// 		{
// 		}
// 		else
// 		{
// 			LeaveCriticalSection(&m_critical);
// 			m_ser.Close(comHandle);
// 			return FALSE;
// 		}
	}

	m_ser.Close(comHandle);
	Sleep(500);
	LeaveCriticalSection(&m_critical);
	return TRUE;
}
