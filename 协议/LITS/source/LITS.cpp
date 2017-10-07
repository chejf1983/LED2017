/*******************************************************************************************************
**
** Copyright (C), 2011-2012, Nahon photoelectric technology CO., LTD.
** File Name:               SpectraArsenal.cpp
** Description:             
** Created By:             Monster
**
*********************************************************************************************************/
#include <Windows.h>
#include "stdafx.h"
#include "stdlib.h"
#include "malloc.h"
#include "stdio.h"
#include "USB_Driver.h"
#include "MIGP.h"
#include "LITS.h"



BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}




COMM_PARA_ST *apCommParaST[32];
int g_iCommIndex = -1;

float LITS_NewtonDifference(float *xa, float *ya, int n, float x)
{

	int i = 0;
	int k = 1;
	float fTemp = 0;

	for(i = 1; i <= n - 2; i ++)
	{
		if( x <= xa[i] )
		{
			k=i;
			break;
		}
		else
			k=n-1;
	}
	
	fTemp=(x - xa[k - 1]) / (xa[k] - xa[k - 1]);
	
	return ya[k - 1] + fTemp * (ya[k] - ya[k - 1]);
}




int LITS_Search(int CommIndex)
{
	BYTE *pbTemp;
	int i = 0;
	int j = 0;
	int CommFlag = 0;
	int iTemp;
	UN_TYPE unTemp;
	UN_32TYPE un32Temp;
	int iLengthTemp = 0;

	for(i = 0; i < 3; i++)
	{
		if(MIGP_RegArea_Read(apCommParaST[CommIndex], EIA, 0x0000, 0x40, &pbTemp, 500) == TRUE)
		{
			for(i = 0; i < 16; i ++)
			{
				apCommParaST[CommIndex]->stEIA.aucEquipmentInfo[i] = pbTemp[i + 4]; 
			}
			apCommParaST[CommIndex]->stEIA.aucEquipmentInfo[16] = '\0';

			apCommParaST[CommIndex]->stEIA.ucHardWareVersion = pbTemp[0x10 + 4];
			apCommParaST[CommIndex]->stEIA.aucSoftWareVersion[0] = pbTemp[0x18 + 4];
			apCommParaST[CommIndex]->stEIA.aucSoftWareVersion[1] = pbTemp[0x19 + 4];
			apCommParaST[CommIndex]->stEIA.aucSoftWareVersion[2] = pbTemp[0x1A + 4];
			apCommParaST[CommIndex]->stEIA.aucSoftWareVersion[3] = pbTemp[0x1B + 4];
			apCommParaST[CommIndex]->stEIA.aucSoftWareVersion[4] = '\0';

			for(i = 0; i < 16; i ++)
			{
				apCommParaST[CommIndex]->stEIA.aucSerialNumber[i] = pbTemp[EIA_SERIAL_NUMBER_ADDR + i + 4]; 
			}
			apCommParaST[CommIndex]->stEIA.aucSerialNumber[16] = '\0';

			for(i = 0; i < 16; i ++)
			{
				apCommParaST[CommIndex]->stEIA.aucManufacturingDate[i] = pbTemp[EIA_MANUFACTURING_DATE_ADDR + i + 4]; 
			}
			apCommParaST[CommIndex]->stEIA.aucManufacturingDate[16] = '\0';

			CommFlag = 1;
			break;
		}
	}

	if(CommFlag == 0)
	{
		//printf_debug("LITS_Search:: Read EIA Error\r\n");
		return FALSE;
	}

	if(MIGP_RegArea_Read(apCommParaST[CommIndex], NVPA, 0x0000, 112, &pbTemp, 1000) == TRUE)
	{
		iTemp = (int)pbTemp[4 + NVPA_MIN_WAVELENGTH_ADDR] << 8;
		iTemp |= (int)pbTemp[4 + NVPA_MIN_WAVELENGTH_ADDR + 1];
		apCommParaST[CommIndex]->stSpectrometerPara.iStartWavelength = iTemp;
		
		iTemp = (int)pbTemp[4 + NVPA_MAX_WAVELENGTH_ADDR] << 8;
		iTemp |= (int)pbTemp[4 + NVPA_MAX_WAVELENGTH_ADDR + 1];
		apCommParaST[CommIndex]->stSpectrometerPara.iEndWavelength = iTemp;
		
		iTemp = (int)pbTemp[4 + NVPA_MIN_INTEGRAL_TIME_ADDR] << 24;
		iTemp |= (int)pbTemp[5 + NVPA_MIN_INTEGRAL_TIME_ADDR] << 16;
		iTemp |= (int)pbTemp[6 + NVPA_MIN_INTEGRAL_TIME_ADDR] << 8;
		iTemp |= (int)pbTemp[7 + NVPA_MIN_INTEGRAL_TIME_ADDR];
		apCommParaST[CommIndex]->stSpectrometerPara.iMinIntegrationTimeUS = iTemp;
		
		iTemp = (int)pbTemp[4 + NVPA_MAX_INTEGRAL_TIME_ADDR] << 24;
		iTemp |= (int)pbTemp[5 + NVPA_MAX_INTEGRAL_TIME_ADDR] << 16;
		iTemp |= (int)pbTemp[6 + NVPA_MAX_INTEGRAL_TIME_ADDR] << 8;
		iTemp |= (int)pbTemp[7 + NVPA_MAX_INTEGRAL_TIME_ADDR];
		apCommParaST[CommIndex]->stSpectrometerPara.iMaxIntegrationTimeUS = iTemp;
		
		iTemp = (int)pbTemp[4 + NVPA_PIXELS_NUMBER_ADDR] << 8;
		iTemp |= (int)pbTemp[4 + NVPA_PIXELS_NUMBER_ADDR + 1];
		apCommParaST[CommIndex]->stSpectrometerPara.iPixelNumber = iTemp;

		for(i = 0; i < 4; i++)
		{
			unTemp.ab8Data[7] = (int)pbTemp[4 + (i * 8) + NVPA_WAVELENGTH_CALIB_ADDR];
			unTemp.ab8Data[6] = (int)pbTemp[5 + (i * 8) + NVPA_WAVELENGTH_CALIB_ADDR];
			unTemp.ab8Data[5] = (int)pbTemp[6 + (i * 8) + NVPA_WAVELENGTH_CALIB_ADDR];
			unTemp.ab8Data[4] = (int)pbTemp[7 + (i * 8) + NVPA_WAVELENGTH_CALIB_ADDR];
			unTemp.ab8Data[3] = (int)pbTemp[8 + (i * 8) + NVPA_WAVELENGTH_CALIB_ADDR];
			unTemp.ab8Data[2] = (int)pbTemp[9 + (i * 8) + NVPA_WAVELENGTH_CALIB_ADDR];
			unTemp.ab8Data[1] = (int)pbTemp[10 + (i * 8) + NVPA_WAVELENGTH_CALIB_ADDR];
			unTemp.ab8Data[0] = (int)pbTemp[11 + (i * 8) + NVPA_WAVELENGTH_CALIB_ADDR];
			apCommParaST[CommIndex]->stSpectrometerPara.adWavelengthCalib[i] = unTemp.d64Data;
		}
	}
	else
	{
		return FALSE;
	}

	if(MIGP_RegArea_Read(apCommParaST[CommIndex], VPA, VPA_RUN_MODE_ADDR, 10, &pbTemp, 1000) == TRUE)
	{
		apCommParaST[CommIndex]->stSpectrometerPara.cTriggerMode = pbTemp[4 + VPA_RUN_MODE_ADDR];
		iTemp = (int)pbTemp[4 + VPA_INTE_TIME_ADDR] << 24;
		iTemp |= (int)pbTemp[5 + VPA_INTE_TIME_ADDR] << 16;
		iTemp |= (int)pbTemp[6 + VPA_INTE_TIME_ADDR] << 8;
		iTemp |= (int)pbTemp[7 + VPA_INTE_TIME_ADDR];
		apCommParaST[CommIndex]->stSpectrometerPara.iIntegrationTime = iTemp;
		iTemp = (int)pbTemp[4] << 8;
		iTemp |= (int)pbTemp[5];
		apCommParaST[CommIndex]->stSpectrometerPara.iAverageTimes = iTemp;
		iTemp = (int)pbTemp[6] << 8;
		iTemp |= (int)pbTemp[7];
		apCommParaST[CommIndex]->stSpectrometerPara.iTriggerDelay = iTemp;
		//apCommParaST[g_iCommIndex + 1]->stSpectrometerPara.cAutoIntegrationFlag = pbTemp[8];
		
	}
	else
	{
		return FALSE;
	}

	if(MIGP_RegArea_Read(apCommParaST[CommIndex], VPA, 112, 64, &pbTemp, 1000) == TRUE)
	{

		for(i = 0; i < 16; i++)
		{
			iTemp = (int)pbTemp[4 + (i * 4)] << 24;
			iTemp |= (int)pbTemp[5 + (i * 4)] << 16;
			iTemp |= (int)pbTemp[6 + (i * 4)] << 8;
			iTemp |= (int)pbTemp[7 + (i * 4)];
			apCommParaST[CommIndex]->stSpectrometerPara.iChannelIntegrationTime[i] = iTemp;
		}
		
	}
	else
	{
		return FALSE;
	}

	if(MIGP_RegArea_Read(apCommParaST[CommIndex], NVPA, 0x0040, 1, &pbTemp, 500) == TRUE)
	{
		apCommParaST[CommIndex]->stSpectrometerPara.cNonlinearCalibType = pbTemp[4];

		//printf("cNonlinearCalibType %d \r\n", (int)apCommParaST[g_iCommIndex + 1]->stSpectrometerPara.cNonlinearCalibType);

		if(apCommParaST[CommIndex]->stSpectrometerPara.cNonlinearCalibType != NONLINEAR_CALIB_DISABLE &&
		   apCommParaST[CommIndex]->stSpectrometerPara.cNonlinearCalibType != NONLINEAR_CALIB_WAVELENGTH &&
		   apCommParaST[CommIndex]->stSpectrometerPara.cNonlinearCalibType != NONLINEAR_CALIB_PIXEL &&
		   apCommParaST[CommIndex]->stSpectrometerPara.cNonlinearCalibType != NONLINEAR_CALIB_WAVELENGTH_II &&
		   apCommParaST[CommIndex]->stSpectrometerPara.cNonlinearCalibType != NONLINEAR_CALIB_PIXEL_II)
		{
			apCommParaST[CommIndex]->stSpectrometerPara.cNonlinearCalibType = NONLINEAR_CALIB_DISABLE;
		}

		if(apCommParaST[CommIndex]->stSpectrometerPara.cNonlinearCalibType == NONLINEAR_CALIB_DISABLE)
		{
			return TRUE;
		}
	}
	else
	{
		return FALSE;
	}

	if(MIGP_RegArea_Read(apCommParaST[CommIndex], NVPA, 0x0041, 760, &pbTemp, 2000) == TRUE)
	{
		un32Temp.ab8Data[3] = (int)pbTemp[4];
		un32Temp.ab8Data[2] = (int)pbTemp[5];
		un32Temp.ab8Data[1] = (int)pbTemp[6];
		un32Temp.ab8Data[0] = (int)pbTemp[7];
		apCommParaST[CommIndex]->stSpectrometerPara.iNonlinearCalibLength = (int)un32Temp.f32Data;

		if(apCommParaST[CommIndex]->stSpectrometerPara.iNonlinearCalibLength < 1 ||
		   apCommParaST[CommIndex]->stSpectrometerPara.iNonlinearCalibLength > 8)
		{
			apCommParaST[CommIndex]->stSpectrometerPara.cNonlinearCalibType = NONLINEAR_CALIB_DISABLE;
			return TRUE;
		}
		//printf("iNonlinearCalibLength %d\r\n", (int)apCommParaST[g_iCommIndex + 1]->stSpectrometerPara.iNonlinearCalibLength);

		if(apCommParaST[CommIndex]->stSpectrometerPara.cNonlinearCalibType == NONLINEAR_CALIB_WAVELENGTH ||
		   apCommParaST[CommIndex]->stSpectrometerPara.cNonlinearCalibType == NONLINEAR_CALIB_PIXEL)
		{
			for(i = 0; i < apCommParaST[CommIndex]->stSpectrometerPara.iNonlinearCalibLength; i++)
			{
				un32Temp.ab8Data[3] = (int)pbTemp[8 + (i * 88)];
				un32Temp.ab8Data[2] = (int)pbTemp[9 + (i * 88)];
				un32Temp.ab8Data[1] = (int)pbTemp[10 + (i * 88)];
				un32Temp.ab8Data[0] = (int)pbTemp[11 + (i * 88)];
				apCommParaST[CommIndex]->stSpectrometerPara.fNonlinearCalibPixelOrWL[i] = un32Temp.f32Data;
				//printf("NonlinearCalibPixelOrWL %f\r\n", un32Temp.f32Data);
				un32Temp.ab8Data[3] = (int)pbTemp[12 + (i * 88)];
				un32Temp.ab8Data[2] = (int)pbTemp[13 + (i * 88)];
				un32Temp.ab8Data[1] = (int)pbTemp[14 + (i * 88)];
				un32Temp.ab8Data[0] = (int)pbTemp[15 + (i * 88)];
				apCommParaST[CommIndex]->stSpectrometerPara.iNonlinearCalibCoNumber[i] = (int)un32Temp.f32Data;
				if(apCommParaST[CommIndex]->stSpectrometerPara.iNonlinearCalibCoNumber[i] < 1 ||
			   	   apCommParaST[CommIndex]->stSpectrometerPara.iNonlinearCalibCoNumber[i] > 10)
				{
					apCommParaST[CommIndex]->stSpectrometerPara.cNonlinearCalibType = NONLINEAR_CALIB_DISABLE;
					return TRUE;
				}
				
				//printf("fNonlinearCalibCoNumber %d\r\n", (int)apCommParaST[g_iCommIndex + 1]->stSpectrometerPara.iNonlinearCalibCoNumber[i]);
				for(j = 0; j < apCommParaST[CommIndex]->stSpectrometerPara.iNonlinearCalibCoNumber[i]; j++)
				{
					un32Temp.ab8Data[3] = (int)pbTemp[16 + (i * 88) + (j * 8)];
					un32Temp.ab8Data[2] = (int)pbTemp[17 + (i * 88) + (j * 8)];
					un32Temp.ab8Data[1] = (int)pbTemp[18 + (i * 88) + (j * 8)];
					un32Temp.ab8Data[0] = (int)pbTemp[19 + (i * 88) + (j * 8)];
					apCommParaST[CommIndex]->stSpectrometerPara.afNonlinearCalibAD[i][j] = un32Temp.f32Data;
					//printf("AD %f ", apCommParaST[g_iCommIndex + 1]->stSpectrometerPara.afNonlinearCalibAD[i][j]);
					un32Temp.ab8Data[3] = (int)pbTemp[20 + (i * 88) + (j * 8)];
					un32Temp.ab8Data[2] = (int)pbTemp[21 + (i * 88) + (j * 8)];
					un32Temp.ab8Data[1] = (int)pbTemp[22 + (i * 88) + (j * 8)];
					un32Temp.ab8Data[0] = (int)pbTemp[23 + (i * 88) + (j * 8)];
					apCommParaST[CommIndex]->stSpectrometerPara.afNonlinearCalibCo[i][j] = un32Temp.f32Data;
				    //printf("CalibCo %f\r\n", apCommParaST[g_iCommIndex + 1]->stSpectrometerPara.afNonlinearCalibCo[i][j]);
				}
				
			}
		}
		else if(apCommParaST[CommIndex]->stSpectrometerPara.cNonlinearCalibType == NONLINEAR_CALIB_WAVELENGTH_II ||
		        apCommParaST[CommIndex]->stSpectrometerPara.cNonlinearCalibType == NONLINEAR_CALIB_PIXEL_II)
		{
			iLengthTemp = 8;
			for(i = 0; i < apCommParaST[CommIndex]->stSpectrometerPara.iNonlinearCalibLength; i++)
			{
				un32Temp.ab8Data[3] = (int)pbTemp[0 + iLengthTemp];
				un32Temp.ab8Data[2] = (int)pbTemp[1 + iLengthTemp];
				un32Temp.ab8Data[1] = (int)pbTemp[2 + iLengthTemp];
				un32Temp.ab8Data[0] = (int)pbTemp[3 + iLengthTemp];
				iLengthTemp = iLengthTemp + 4;
				apCommParaST[CommIndex]->stSpectrometerPara.fNonlinearCalibPixelOrWL[i] = un32Temp.f32Data;
				//printf("NonlinearCalibPixelOrWL %f\r\n", un32Temp.f32Data);
				un32Temp.ab8Data[3] = (int)pbTemp[0 + iLengthTemp];
				un32Temp.ab8Data[2] = (int)pbTemp[1 + iLengthTemp];
				un32Temp.ab8Data[1] = (int)pbTemp[2 + iLengthTemp];
				un32Temp.ab8Data[0] = (int)pbTemp[3 + iLengthTemp];
				iLengthTemp = iLengthTemp + 4;
				apCommParaST[CommIndex]->stSpectrometerPara.iNonlinearCalibCoNumber[i] = (int)un32Temp.f32Data;
				
				//printf("fNonlinearCalibCoNumber %d\r\n", (int)apCommParaST[g_iCommIndex + 1]->stSpectrometerPara.iNonlinearCalibCoNumber[i]);
				for(j = 0; j < apCommParaST[CommIndex]->stSpectrometerPara.iNonlinearCalibCoNumber[i]; j++)
				{
					un32Temp.ab8Data[3] = (int)pbTemp[0 + iLengthTemp];
					un32Temp.ab8Data[2] = (int)pbTemp[1 + iLengthTemp];
					un32Temp.ab8Data[1] = (int)pbTemp[2 + iLengthTemp];
					un32Temp.ab8Data[0] = (int)pbTemp[3 + iLengthTemp];
					iLengthTemp = iLengthTemp + 4;
					apCommParaST[CommIndex]->stSpectrometerPara.afNonlinearCalibAD[i][j] = un32Temp.f32Data;
					//printf("AD %f ", apCommParaST[g_iCommIndex + 1]->stSpectrometerPara.afNonlinearCalibAD[i][j]);
					un32Temp.ab8Data[3] = (int)pbTemp[0 + iLengthTemp];
					un32Temp.ab8Data[2] = (int)pbTemp[1 + iLengthTemp];
					un32Temp.ab8Data[1] = (int)pbTemp[2 + iLengthTemp];
					un32Temp.ab8Data[0] = (int)pbTemp[3 + iLengthTemp];
					iLengthTemp = iLengthTemp + 4;
					apCommParaST[CommIndex]->stSpectrometerPara.afNonlinearCalibCo[i][j] = un32Temp.f32Data;
					//printf("CalibCo %f\r\n", apCommParaST[g_iCommIndex + 1]->stSpectrometerPara.afNonlinearCalibCo[i][j]);
					if(iLengthTemp > 760)
					{
						apCommParaST[CommIndex]->stSpectrometerPara.cNonlinearCalibType = NONLINEAR_CALIB_DISABLE;
						return TRUE;
					}
				}
				
			}
		}
	}
	else
	{
		return FALSE;
	}

	return TRUE;
}


int LITS_SystemOpen(void)
{
	//BYTE *pbTemp;
	//UN_TYPE unTemp;
	//UN_32TYPE un32Temp;
	COMM_PARA_ST *pstMigpPara = NULL;
	//HANDLE CommDev;
	int DevNum;
	int i = 0;
	int ret = 0;
	//int iTemp;
	
	g_iCommIndex = -1;
 
	DevNum = USBScanDev(1);

	if(DevNum == 0)
	{
		//printf_debug("LITS_SystemOpen:: NO USB Device");
		return g_iCommIndex;
	}

	for(i = 0; i < DevNum; i++)
	{
		ret = USBOpenDev(i);
		if(USBOpenDev(i) != SEVERITY_ERROR)
		{
			//printf_debug("OPEN USB device SUCCESS£¡\n");
			apCommParaST[g_iCommIndex + 1] = (COMM_PARA_ST *)malloc(sizeof(COMM_PARA_ST));
			if(apCommParaST[g_iCommIndex + 1] == NULL)
			{
				//printf_debug("LITS_SystemOpen:: malloc NULL");
				USBCloseDev(i);
				free(apCommParaST[g_iCommIndex + 1]);
			}
			else
			{
				apCommParaST[g_iCommIndex + 1]->enCommType = USB_WINLIB;
				apCommParaST[g_iCommIndex + 1]->stComPara.iUSBDevNum = i;
				apCommParaST[g_iCommIndex + 1]->stMIGP.bMasterAddress = 0xFE;
				apCommParaST[g_iCommIndex + 1]->stMIGP.bSlaveAddress = 0x00;

				if(LITS_Search(g_iCommIndex + 1) == TRUE)
				{
					g_iCommIndex++;
				}
				else
				{					
				    //printf_debug("LITS_SystemOpen:: MIGP_RegArea_Read FAIL");
					USBCloseDev(i);
					free(apCommParaST[g_iCommIndex + 1]);
				}
			}
		}

		
	}

	return g_iCommIndex;
}

void LITS_SystemClose(void)
{
	int i = 0;
	
	if(g_iCommIndex != -1)
	{
		for(i = 0; i < g_iCommIndex + 1; i++)
		{
			USBCloseDev(apCommParaST[g_iCommIndex]->stComPara.iUSBDevNum);
			free(apCommParaST[g_iCommIndex]);
			
		}
	}
}



int LITS_SetIntegrationTime (int LITSIndex, int usec)
{
	BYTE bTemp[4];
	unsigned long ulTemp = 0;
	int i = 0;
	//HANDLE CommDev;
	
	if(LITSIndex > g_iCommIndex)
	{	
		return SA_API_FAIL;
	}

	if(usec < apCommParaST[LITSIndex]->stSpectrometerPara.iMinIntegrationTimeUS ||
	   usec > apCommParaST[LITSIndex]->stSpectrometerPara.iMaxIntegrationTimeUS)
	{
		return SA_API_FAIL;
	}


	ulTemp = (unsigned long)(usec);
	bTemp[0] = (BYTE)(ulTemp >> 24 & 0x000000ff);
	bTemp[1] = (BYTE)(ulTemp >> 16 & 0x000000ff);
	bTemp[2] = (BYTE)(ulTemp >> 8 & 0x000000ff);
	bTemp[3] = (BYTE)(ulTemp & 0x000000ff);


	if(MIGP_RegArea_Write(apCommParaST[LITSIndex], VPA, 0x0001, 4, bTemp, MIGP_ACK_RX_ENABLE) == FALSE)
	{

		return SA_API_FAIL;
	}

	
	apCommParaST[LITSIndex]->stSpectrometerPara.iIntegrationTime = usec;
	
	return SA_API_SUCCESS;
}

int LITS_SetChannelIntegrationTime (int LITSIndex, int LedRusec, int LedGusec, int LedBusec)
{
	BYTE bTemp[12];
	unsigned long ulTemp = 0;
	int i = 0;
	//HANDLE CommDev;
	
	if(LITSIndex > g_iCommIndex)
	{	
		return SA_API_FAIL;
	}


	ulTemp = (unsigned long)(LedRusec);
	bTemp[0] = (BYTE)(ulTemp >> 24 & 0x000000ff);
	bTemp[1] = (BYTE)(ulTemp >> 16 & 0x000000ff);
	bTemp[2] = (BYTE)(ulTemp >> 8 & 0x000000ff);
	bTemp[3] = (BYTE)(ulTemp & 0x000000ff);

	ulTemp = (unsigned long)(LedGusec);
	bTemp[4] = (BYTE)(ulTemp >> 24 & 0x000000ff);
	bTemp[5] = (BYTE)(ulTemp >> 16 & 0x000000ff);
	bTemp[6] = (BYTE)(ulTemp >> 8 & 0x000000ff);
	bTemp[7] = (BYTE)(ulTemp & 0x000000ff);

	ulTemp = (unsigned long)(LedBusec);
	bTemp[8] = (BYTE)(ulTemp >> 24 & 0x000000ff);
	bTemp[9] = (BYTE)(ulTemp >> 16 & 0x000000ff);
	bTemp[10] = (BYTE)(ulTemp >> 8 & 0x000000ff);
	bTemp[11] = (BYTE)(ulTemp & 0x000000ff);


	if(MIGP_RegArea_Write(apCommParaST[LITSIndex], VPA, 112, 12, bTemp, MIGP_ACK_RX_ENABLE) == FALSE)
	{

		return SA_API_FAIL;
	}

	
	return SA_API_SUCCESS;
}


int LITS_SetAverageTimes(int LITSIndex, int AverageTimes)
{
	BYTE bTemp[2];
	int i = 0;
	//HANDLE CommDev;
	
	if(LITSIndex > g_iCommIndex)
	{	
		return SA_API_FAIL;
	}

	if(AverageTimes < 1 || AverageTimes > 1000)
	{	
		return SA_API_FAIL;
	}

	if(AverageTimes == apCommParaST[LITSIndex]->stSpectrometerPara.iAverageTimes)
	{
		return SA_API_SUCCESS;
	}

	bTemp[0] = AverageTimes >> 8 & 0x000000ff;
	bTemp[1] = AverageTimes & 0x000000ff;


	if(MIGP_RegArea_Write(apCommParaST[LITSIndex], VPA, VPA_AVERAGE_TIME_ADDR, 2, bTemp, MIGP_ACK_RX_ENABLE) == FALSE)
	{
		return SA_API_FAIL;
	}
	
	apCommParaST[LITSIndex]->stSpectrometerPara.iAverageTimes = AverageTimes;

	return SA_API_SUCCESS;
}



int LITS_GetWavelengthCalibrationCoefficients (int LITSIndex, double * WavelengthCalibration)
{
	if(LITSIndex > g_iCommIndex)
	{	
		return SA_API_FAIL;
	}

	WavelengthCalibration[0] = apCommParaST[LITSIndex]->stSpectrometerPara.adWavelengthCalib[0];
	WavelengthCalibration[1] = apCommParaST[LITSIndex]->stSpectrometerPara.adWavelengthCalib[1];
	WavelengthCalibration[2] = apCommParaST[LITSIndex]->stSpectrometerPara.adWavelengthCalib[2];
	WavelengthCalibration[3] = apCommParaST[LITSIndex]->stSpectrometerPara.adWavelengthCalib[3];

	return SA_API_SUCCESS;
}



char * LITS_GetSoftwareVersion(int LITSIndex)
{
	if(LITSIndex > g_iCommIndex)
	{	
		return NULL;
	}

	return apCommParaST[LITSIndex]->stEIA.aucSoftWareVersion;
}

char LITS_GetHardwareVersion(int LITSIndex)
{
	if(LITSIndex > g_iCommIndex)
	{	
		return NULL;
	}

	return apCommParaST[LITSIndex]->stEIA.ucHardWareVersion;
}


char * LITS_GetSerialNumber(int LITSIndex)
{
	if(LITSIndex > g_iCommIndex)
	{	
		return NULL;
	}

	return apCommParaST[LITSIndex]->stEIA.aucSerialNumber;
}

char * LITS_GetManufacturingDate(int LITSIndex)
{
	if(LITSIndex > g_iCommIndex)
	{	
		return NULL;
	}

	return apCommParaST[LITSIndex]->stEIA.aucManufacturingDate;
}

int LITS_GetPixelNumber(int LITSIndex)
{

	return apCommParaST[LITSIndex]->stSpectrometerPara.iPixelNumber;
}

int LITS_NonlinearCalibration(int LITSIndex, double * pbSpectum, double * pbNewSpectum, int SpectumNumber)
{
	int i = 0;
	int j = 0;
	float fTemp = 0;
	float fTemp2 = 0;
	float fCoTemp = 0;
	int iMaxPixelOrWL = 0;
	float fWL = 0;
	
	if(LITSIndex > g_iCommIndex)
	{	
		return SA_API_FAIL;
	}

	if(apCommParaST[LITSIndex]->stSpectrometerPara.cNonlinearCalibType == NONLINEAR_CALIB_DISABLE )
	{
		for(i = 0; i < SpectumNumber; i++)
		{
			pbNewSpectum[i] = pbSpectum[i];
		}
	}
	else if(apCommParaST[LITSIndex]->stSpectrometerPara.cNonlinearCalibType == NONLINEAR_CALIB_WAVELENGTH || 
		    apCommParaST[LITSIndex]->stSpectrometerPara.cNonlinearCalibType == NONLINEAR_CALIB_WAVELENGTH_II)
	{ 
		if(apCommParaST[LITSIndex]->stSpectrometerPara.iNonlinearCalibLength < 1 ||
		   apCommParaST[LITSIndex]->stSpectrometerPara.iNonlinearCalibLength > 8)
		{
			for(i = 0; i < SpectumNumber; i++)
			{
				pbNewSpectum[i] = pbSpectum[i];
			}
		}
		else if(apCommParaST[LITSIndex]->stSpectrometerPara.iNonlinearCalibLength == 1)
		{
			for(i = 0; i < SpectumNumber; i++)
			{
				fTemp = LITS_NewtonDifference(apCommParaST[LITSIndex]->stSpectrometerPara.afNonlinearCalibAD[0],
										    apCommParaST[LITSIndex]->stSpectrometerPara.afNonlinearCalibCo[0], 
										    apCommParaST[LITSIndex]->stSpectrometerPara.iNonlinearCalibCoNumber[0], 
										    (float)pbSpectum[i]);
				pbNewSpectum[i] = pbSpectum[i] * fTemp;
			}
			
		}
		else
		{
			iMaxPixelOrWL = apCommParaST[LITSIndex]->stSpectrometerPara.iNonlinearCalibLength - 1;
			for(i = 0; i < SpectumNumber; i++)
			{
				fWL = (float)(apCommParaST[LITSIndex]->stSpectrometerPara.adWavelengthCalib[0] + 
					  (apCommParaST[LITSIndex]->stSpectrometerPara.adWavelengthCalib[1] * i) + 
					  (apCommParaST[LITSIndex]->stSpectrometerPara.adWavelengthCalib[2] * i * i) + 
					  (apCommParaST[LITSIndex]->stSpectrometerPara.adWavelengthCalib[3] * i * i * i));
				if(fWL <= apCommParaST[LITSIndex]->stSpectrometerPara.fNonlinearCalibPixelOrWL[0])
				{
					fTemp = LITS_NewtonDifference(apCommParaST[LITSIndex]->stSpectrometerPara.afNonlinearCalibAD[0],
										        apCommParaST[LITSIndex]->stSpectrometerPara.afNonlinearCalibCo[0], 
										        apCommParaST[LITSIndex]->stSpectrometerPara.iNonlinearCalibCoNumber[0], 
											    (float)pbSpectum[i]);
					pbNewSpectum[i] = pbSpectum[i] * fTemp;
				}
				else if(fWL >= apCommParaST[LITSIndex]->stSpectrometerPara.fNonlinearCalibPixelOrWL[iMaxPixelOrWL])
				{
					fTemp = LITS_NewtonDifference(apCommParaST[LITSIndex]->stSpectrometerPara.afNonlinearCalibAD[iMaxPixelOrWL],
										        apCommParaST[LITSIndex]->stSpectrometerPara.afNonlinearCalibCo[iMaxPixelOrWL], 
										        apCommParaST[LITSIndex]->stSpectrometerPara.iNonlinearCalibCoNumber[iMaxPixelOrWL], 
											    (float)pbSpectum[i]);
					pbNewSpectum[i] = pbSpectum[i] * fTemp;
				}
				else
				{
					for(j = 1; j < apCommParaST[LITSIndex]->stSpectrometerPara.iNonlinearCalibLength; j++)
					{
						if(fWL < apCommParaST[LITSIndex]->stSpectrometerPara.fNonlinearCalibPixelOrWL[j])
						{
							break;
						}
					}

					fTemp = LITS_NewtonDifference(apCommParaST[LITSIndex]->stSpectrometerPara.afNonlinearCalibAD[j-1],
										        apCommParaST[LITSIndex]->stSpectrometerPara.afNonlinearCalibCo[j-1], 
										        apCommParaST[LITSIndex]->stSpectrometerPara.iNonlinearCalibCoNumber[j-1], 
											    (float)pbSpectum[i]);
					fTemp2 = LITS_NewtonDifference(apCommParaST[LITSIndex]->stSpectrometerPara.afNonlinearCalibAD[j],
										        apCommParaST[LITSIndex]->stSpectrometerPara.afNonlinearCalibCo[j], 
										        apCommParaST[LITSIndex]->stSpectrometerPara.iNonlinearCalibCoNumber[j], 
											    (float)pbSpectum[i]);
					fCoTemp = fWL - apCommParaST[LITSIndex]->stSpectrometerPara.fNonlinearCalibPixelOrWL[j-1];
					fCoTemp = fCoTemp / (apCommParaST[LITSIndex]->stSpectrometerPara.fNonlinearCalibPixelOrWL[j] - 
						      apCommParaST[LITSIndex]->stSpectrometerPara.fNonlinearCalibPixelOrWL[j-1]);
					fCoTemp = (fCoTemp * (fTemp2 - fTemp)) + fTemp;
					pbNewSpectum[i] = pbSpectum[i] * fCoTemp;
					
				}
				
			}
		}
	}
	else if(apCommParaST[LITSIndex]->stSpectrometerPara.cNonlinearCalibType == NONLINEAR_CALIB_PIXEL || 
			apCommParaST[LITSIndex]->stSpectrometerPara.cNonlinearCalibType == NONLINEAR_CALIB_PIXEL_II)
	{ 
		if(apCommParaST[LITSIndex]->stSpectrometerPara.iNonlinearCalibLength < 1 ||
		   apCommParaST[LITSIndex]->stSpectrometerPara.iNonlinearCalibLength > 8)
		{
			for(i = 0; i < SpectumNumber; i++)
			{
				pbNewSpectum[i] = pbSpectum[i];
			}
		}
		else if(apCommParaST[LITSIndex]->stSpectrometerPara.iNonlinearCalibLength == 1)
		{
			for(i = 0; i < SpectumNumber; i++)
			{
				fTemp = LITS_NewtonDifference(apCommParaST[LITSIndex]->stSpectrometerPara.afNonlinearCalibAD[0],
										    apCommParaST[LITSIndex]->stSpectrometerPara.afNonlinearCalibCo[0], 
										    apCommParaST[LITSIndex]->stSpectrometerPara.iNonlinearCalibCoNumber[0], 
										    (float)pbSpectum[i]);
				pbNewSpectum[i] = pbSpectum[i] * fTemp;
			}
			
		}
		else
		{
			iMaxPixelOrWL = apCommParaST[LITSIndex]->stSpectrometerPara.iNonlinearCalibLength - 1;
			for(i = 0; i < SpectumNumber; i++)
			{
				if(i <= apCommParaST[LITSIndex]->stSpectrometerPara.fNonlinearCalibPixelOrWL[0])
				{
					fTemp = LITS_NewtonDifference(apCommParaST[LITSIndex]->stSpectrometerPara.afNonlinearCalibAD[0],
										        apCommParaST[LITSIndex]->stSpectrometerPara.afNonlinearCalibCo[0], 
										        apCommParaST[LITSIndex]->stSpectrometerPara.iNonlinearCalibCoNumber[0], 
											    (float)pbSpectum[i]);
					pbNewSpectum[i] = pbSpectum[i] * fTemp;
				}
				else if(i >= apCommParaST[LITSIndex]->stSpectrometerPara.fNonlinearCalibPixelOrWL[iMaxPixelOrWL])
				{
					fTemp = LITS_NewtonDifference(apCommParaST[LITSIndex]->stSpectrometerPara.afNonlinearCalibAD[iMaxPixelOrWL],
										        apCommParaST[LITSIndex]->stSpectrometerPara.afNonlinearCalibCo[iMaxPixelOrWL], 
										        apCommParaST[LITSIndex]->stSpectrometerPara.iNonlinearCalibCoNumber[iMaxPixelOrWL], 
											    (float)pbSpectum[i]);
					pbNewSpectum[i] = pbSpectum[i] * fTemp;
				}
				else
				{
					for(j = 1; j < apCommParaST[LITSIndex]->stSpectrometerPara.iNonlinearCalibLength; j++)
					{
						if(i < apCommParaST[LITSIndex]->stSpectrometerPara.fNonlinearCalibPixelOrWL[j])
						{
							break;
						}
					}

					fTemp = LITS_NewtonDifference(apCommParaST[LITSIndex]->stSpectrometerPara.afNonlinearCalibAD[j-1],
										        apCommParaST[LITSIndex]->stSpectrometerPara.afNonlinearCalibCo[j-1], 
										        apCommParaST[LITSIndex]->stSpectrometerPara.iNonlinearCalibCoNumber[j-1], 
											    (float)pbSpectum[i]);
					fTemp2 = LITS_NewtonDifference(apCommParaST[LITSIndex]->stSpectrometerPara.afNonlinearCalibAD[j],
										        apCommParaST[LITSIndex]->stSpectrometerPara.afNonlinearCalibCo[j], 
										        apCommParaST[LITSIndex]->stSpectrometerPara.iNonlinearCalibCoNumber[j], 
											    (float)pbSpectum[i]);
					fCoTemp = i - apCommParaST[LITSIndex]->stSpectrometerPara.fNonlinearCalibPixelOrWL[j-1];
					fCoTemp = fCoTemp / (apCommParaST[LITSIndex]->stSpectrometerPara.fNonlinearCalibPixelOrWL[j] - 
						      apCommParaST[LITSIndex]->stSpectrometerPara.fNonlinearCalibPixelOrWL[j-1]);
					fCoTemp = (fCoTemp * (fTemp2 - fTemp)) + fTemp;
					pbNewSpectum[i] = pbSpectum[i] * fCoTemp;
					
				}
				
			}
		}
	}
	else
	{
		for(i = 0; i < SpectumNumber; i++)
		{
			pbNewSpectum[i] = pbSpectum[i];
		}
	}

	return SA_API_SUCCESS;
}


int LITS_GetNonlinearCalibrationPixel(int LITSIndex, 
										 float *pfNonlinearCalibPixelOrWL, int *piNonlinearCalibCoNumber,
	                                     float *pfNonlinearCalibAD, float *pfNonlinearCalibCo)
{
	BYTE *pbTemp;
	int i = 0;
	int j = 0;
	//UN_TYPE unTemp;
	UN_32TYPE un32Temp;
	int iLengthTemp = 0;
	
	float *pfTempAD = &apCommParaST[LITSIndex]->stSpectrometerPara.afNonlinearCalibAD[0][0];
	float *pfTempCo = &apCommParaST[LITSIndex]->stSpectrometerPara.afNonlinearCalibCo[0][0];

	if(LITSIndex > g_iCommIndex)
	{	
		return SA_API_FAIL;
	}

	if(MIGP_RegArea_Read(apCommParaST[LITSIndex], NVPA, 0x0041, 760, &pbTemp, 2000) == TRUE)
	{
		un32Temp.ab8Data[3] = (int)pbTemp[4];
		un32Temp.ab8Data[2] = (int)pbTemp[5];
		un32Temp.ab8Data[1] = (int)pbTemp[6];
		un32Temp.ab8Data[0] = (int)pbTemp[7];
		apCommParaST[LITSIndex]->stSpectrometerPara.iNonlinearCalibLength = (int)un32Temp.f32Data;
		printf("iNonlinearCalibLength %d\r\n", (int)apCommParaST[g_iCommIndex + 1]->stSpectrometerPara.iNonlinearCalibLength);

		if(apCommParaST[LITSIndex]->stSpectrometerPara.iNonlinearCalibLength < 1 ||
		   apCommParaST[LITSIndex]->stSpectrometerPara.iNonlinearCalibLength > 8)
		{
			apCommParaST[LITSIndex]->stSpectrometerPara.cNonlinearCalibType = NONLINEAR_CALIB_DISABLE;
			return TRUE;
		}
		

		if(apCommParaST[LITSIndex]->stSpectrometerPara.cNonlinearCalibType == NONLINEAR_CALIB_WAVELENGTH ||
		   apCommParaST[LITSIndex]->stSpectrometerPara.cNonlinearCalibType == NONLINEAR_CALIB_PIXEL)
		{
			for(i = 0; i < apCommParaST[LITSIndex]->stSpectrometerPara.iNonlinearCalibLength; i++)
			{
				un32Temp.ab8Data[3] = (int)pbTemp[8 + (i * 88)];
				un32Temp.ab8Data[2] = (int)pbTemp[9 + (i * 88)];
				un32Temp.ab8Data[1] = (int)pbTemp[10 + (i * 88)];
				un32Temp.ab8Data[0] = (int)pbTemp[11 + (i * 88)];
				apCommParaST[LITSIndex]->stSpectrometerPara.fNonlinearCalibPixelOrWL[i] = un32Temp.f32Data;
				printf("NonlinearCalibPixelOrWL %f\r\n", un32Temp.f32Data);
				un32Temp.ab8Data[3] = (int)pbTemp[12 + (i * 88)];
				un32Temp.ab8Data[2] = (int)pbTemp[13 + (i * 88)];
				un32Temp.ab8Data[1] = (int)pbTemp[14 + (i * 88)];
				un32Temp.ab8Data[0] = (int)pbTemp[15 + (i * 88)];
				apCommParaST[LITSIndex]->stSpectrometerPara.iNonlinearCalibCoNumber[i] = (int)un32Temp.f32Data;
				if(apCommParaST[LITSIndex]->stSpectrometerPara.iNonlinearCalibCoNumber[i] < 1 ||
			   	   apCommParaST[LITSIndex]->stSpectrometerPara.iNonlinearCalibCoNumber[i] > 10)
				{
					apCommParaST[LITSIndex]->stSpectrometerPara.cNonlinearCalibType = NONLINEAR_CALIB_DISABLE;
					return TRUE;
				}
				
				printf("fNonlinearCalibCoNumber %d\r\n", (int)apCommParaST[g_iCommIndex + 1]->stSpectrometerPara.iNonlinearCalibCoNumber[i]);
				for(j = 0; j < apCommParaST[LITSIndex]->stSpectrometerPara.iNonlinearCalibCoNumber[i]; j++)
				{
					un32Temp.ab8Data[3] = (int)pbTemp[16 + (i * 88) + (j * 8)];
					un32Temp.ab8Data[2] = (int)pbTemp[17 + (i * 88) + (j * 8)];
					un32Temp.ab8Data[1] = (int)pbTemp[18 + (i * 88) + (j * 8)];
					un32Temp.ab8Data[0] = (int)pbTemp[19 + (i * 88) + (j * 8)];
					apCommParaST[LITSIndex]->stSpectrometerPara.afNonlinearCalibAD[i][j] = un32Temp.f32Data;
					printf("AD %f ", apCommParaST[g_iCommIndex + 1]->stSpectrometerPara.afNonlinearCalibAD[i][j]);
					un32Temp.ab8Data[3] = (int)pbTemp[20 + (i * 88) + (j * 8)];
					un32Temp.ab8Data[2] = (int)pbTemp[21 + (i * 88) + (j * 8)];
					un32Temp.ab8Data[1] = (int)pbTemp[22 + (i * 88) + (j * 8)];
					un32Temp.ab8Data[0] = (int)pbTemp[23 + (i * 88) + (j * 8)];
					apCommParaST[LITSIndex]->stSpectrometerPara.afNonlinearCalibCo[i][j] = un32Temp.f32Data;
				    printf("CalibCo %f\r\n", apCommParaST[g_iCommIndex + 1]->stSpectrometerPara.afNonlinearCalibCo[i][j]);
				}
				
			}
		}
		else if(apCommParaST[LITSIndex]->stSpectrometerPara.cNonlinearCalibType == NONLINEAR_CALIB_WAVELENGTH_II ||
		        apCommParaST[LITSIndex]->stSpectrometerPara.cNonlinearCalibType == NONLINEAR_CALIB_PIXEL_II)
		{
			iLengthTemp = 8;
			for(i = 0; i < apCommParaST[LITSIndex]->stSpectrometerPara.iNonlinearCalibLength; i++)
			{
				un32Temp.ab8Data[3] = (int)pbTemp[0 + iLengthTemp];
				un32Temp.ab8Data[2] = (int)pbTemp[1 + iLengthTemp];
				un32Temp.ab8Data[1] = (int)pbTemp[2 + iLengthTemp];
				un32Temp.ab8Data[0] = (int)pbTemp[3 + iLengthTemp];
				iLengthTemp = iLengthTemp + 4;
				apCommParaST[LITSIndex]->stSpectrometerPara.fNonlinearCalibPixelOrWL[i] = un32Temp.f32Data;
				printf("NonlinearCalibPixelOrWL %f\r\n", un32Temp.f32Data);
				un32Temp.ab8Data[3] = (int)pbTemp[0 + iLengthTemp];
				un32Temp.ab8Data[2] = (int)pbTemp[1 + iLengthTemp];
				un32Temp.ab8Data[1] = (int)pbTemp[2 + iLengthTemp];
				un32Temp.ab8Data[0] = (int)pbTemp[3 + iLengthTemp];
				iLengthTemp = iLengthTemp + 4;
				apCommParaST[LITSIndex]->stSpectrometerPara.iNonlinearCalibCoNumber[i] = (int)un32Temp.f32Data;
				
				printf("fNonlinearCalibCoNumber %d\r\n", (int)apCommParaST[g_iCommIndex + 1]->stSpectrometerPara.iNonlinearCalibCoNumber[i]);
				for(j = 0; j < apCommParaST[LITSIndex]->stSpectrometerPara.iNonlinearCalibCoNumber[i]; j++)
				{
					un32Temp.ab8Data[3] = (int)pbTemp[0 + iLengthTemp];
					un32Temp.ab8Data[2] = (int)pbTemp[1 + iLengthTemp];
					un32Temp.ab8Data[1] = (int)pbTemp[2 + iLengthTemp];
					un32Temp.ab8Data[0] = (int)pbTemp[3 + iLengthTemp];
					iLengthTemp = iLengthTemp + 4;
					apCommParaST[LITSIndex]->stSpectrometerPara.afNonlinearCalibAD[i][j] = un32Temp.f32Data;
					printf("AD %f ", apCommParaST[g_iCommIndex + 1]->stSpectrometerPara.afNonlinearCalibAD[i][j]);
					un32Temp.ab8Data[3] = (int)pbTemp[0 + iLengthTemp];
					un32Temp.ab8Data[2] = (int)pbTemp[1 + iLengthTemp];
					un32Temp.ab8Data[1] = (int)pbTemp[2 + iLengthTemp];
					un32Temp.ab8Data[0] = (int)pbTemp[3 + iLengthTemp];
					iLengthTemp = iLengthTemp + 4;
					apCommParaST[LITSIndex]->stSpectrometerPara.afNonlinearCalibCo[i][j] = un32Temp.f32Data;
					printf("CalibCo %f\r\n", apCommParaST[g_iCommIndex + 1]->stSpectrometerPara.afNonlinearCalibCo[i][j]);
					if(iLengthTemp > 760)
					{
						apCommParaST[LITSIndex]->stSpectrometerPara.cNonlinearCalibType = NONLINEAR_CALIB_DISABLE;
						return TRUE;
					}
				}
				
			}
		}
	}
	
	
	

    *pfNonlinearCalibPixelOrWL = apCommParaST[LITSIndex]->stSpectrometerPara.fNonlinearCalibPixelOrWL[0];
    *piNonlinearCalibCoNumber = apCommParaST[LITSIndex]->stSpectrometerPara.iNonlinearCalibCoNumber[0];

	for(i = 0; i < apCommParaST[LITSIndex]->stSpectrometerPara.iNonlinearCalibCoNumber[0]; i++)
	{
		pfNonlinearCalibAD[i] = pfTempAD[i];
	    pfNonlinearCalibCo[i] = pfTempCo[i];
	}

	
	return SA_API_SUCCESS;
}


int LITS_GetSpectralData(int LITSIndex, double *pdSpectumData)
	{
		BYTE *pbTemp;
		int i = 0;
		int iTimeOut;
		//UN_32TYPE un32Temp;
		int iTemp = 0;
		//HANDLE CommDev;
	
			
		if(LITSIndex > g_iCommIndex)
		{	
			return SA_API_FAIL;
		}
	
		if(apCommParaST[LITSIndex]->stSpectrometerPara.cTriggerMode != SOFTWARE_SYNCHRONOUS && 
		   apCommParaST[LITSIndex]->stSpectrometerPara.cTriggerMode != SOFTWARE_AUTO)
		{
			return SA_API_FAIL;
		}
			
		iTimeOut = (int)(apCommParaST[LITSIndex]->stSpectrometerPara.iIntegrationTime / 1000) + 20;
	
		if(apCommParaST[LITSIndex]->stSpectrometerPara.iAverageTimes <= 0)
		{
			apCommParaST[LITSIndex]->stSpectrometerPara.iAverageTimes = 1;
		}
	
		iTimeOut = apCommParaST[LITSIndex]->stSpectrometerPara.iAverageTimes * iTimeOut * 3;
	
		if(MIGP_RegArea_Read(apCommParaST[LITSIndex], MDA, 0x0000, apCommParaST[LITSIndex]->stSpectrometerPara.iPixelNumber * 2, &pbTemp, iTimeOut) == FALSE)
		{
			return SA_API_FAIL;
		}
		
		//*pSpectumNumber = apCommParaST[LITSIndex]->stSpectrometerPara.iPixelNumber;
		for(i = 0; i < apCommParaST[LITSIndex]->stSpectrometerPara.iPixelNumber; i++)
		{
			pdSpectumData[i] = (double)(((double)pbTemp[4 + (i * 2)] * 256) + pbTemp[4 + (i * 2) + 1]);
		}
		
		return SA_API_SUCCESS;
	}



int LITS_GetMeasureData(int LITSIndex, double *pdSpectumData1, float *pdElectricalData1, 
							 double *pdSpectumData2, float *pdElectricalData2, 
							 double *pdSpectumData3, float *pdElectricalData3)
{
	BYTE *pbTemp;
	int i = 0;
	int iTimeOut;
	UN_32TYPE un32Temp;
	int iTemp = 0;
	//HANDLE CommDev;

		
	if(LITSIndex > g_iCommIndex)
	{	
		return SA_API_FAIL;
	}

	if(apCommParaST[LITSIndex]->stSpectrometerPara.cTriggerMode != SOFTWARE_SYNCHRONOUS && 
	   apCommParaST[LITSIndex]->stSpectrometerPara.cTriggerMode != SOFTWARE_AUTO)
	{
		return SA_API_FAIL;
	}
		
	iTimeOut = (int)((apCommParaST[LITSIndex]->stSpectrometerPara.iChannelIntegrationTime[0] + apCommParaST[LITSIndex]->stSpectrometerPara.iChannelIntegrationTime[1] + 
	                 apCommParaST[LITSIndex]->stSpectrometerPara.iChannelIntegrationTime[2]) / 1000) + 200;

	if(apCommParaST[LITSIndex]->stSpectrometerPara.iAverageTimes <= 0)
	{
		apCommParaST[LITSIndex]->stSpectrometerPara.iAverageTimes = 1;
	}

	iTimeOut = apCommParaST[LITSIndex]->stSpectrometerPara.iAverageTimes * iTimeOut;

	if(MIGP_RegArea_Read(apCommParaST[LITSIndex], MDA, 0x0000, ((apCommParaST[LITSIndex]->stSpectrometerPara.iPixelNumber * 2) + 32) * 3, &pbTemp, iTimeOut) == FALSE)
	{
		return SA_API_FAIL;
	}
	
	//*pSpectumNumber = apCommParaST[LITSIndex]->stSpectrometerPara.iPixelNumber;
	for(i = 0; i < apCommParaST[LITSIndex]->stSpectrometerPara.iPixelNumber; i++)
	{
		pdSpectumData1[i] = (double)(((double)pbTemp[4 + (i * 2)] * 256) + pbTemp[4 + (i * 2) + 1]);
	}

	iTemp = apCommParaST[LITSIndex]->stSpectrometerPara.iPixelNumber * 2;

	for(i = 0; i < 8; i++)
	{
		un32Temp.ab8Data[3] = (int)pbTemp[4 + iTemp + (i * 4)];
		un32Temp.ab8Data[2] = (int)pbTemp[5 + iTemp + (i * 4)];
		un32Temp.ab8Data[1] = (int)pbTemp[6 + iTemp + (i * 4)];
		un32Temp.ab8Data[0] = (int)pbTemp[7 + iTemp + (i * 4)];
		pdElectricalData1[i] = un32Temp.f32Data;
	}

	iTemp = apCommParaST[LITSIndex]->stSpectrometerPara.iPixelNumber * 2 + 32;

	for(i = 0; i < apCommParaST[LITSIndex]->stSpectrometerPara.iPixelNumber; i++)
	{
		pdSpectumData2[i] = (double)(((double)pbTemp[4 + (i * 2) + iTemp] * 256) + pbTemp[4 + (i * 2) + iTemp + 1]);
	}

	iTemp = apCommParaST[LITSIndex]->stSpectrometerPara.iPixelNumber * 4 + 32;

	for(i = 0; i < 8; i++)
	{
		un32Temp.ab8Data[3] = (int)pbTemp[4 + iTemp + (i * 4)];
		un32Temp.ab8Data[2] = (int)pbTemp[5 + iTemp + (i * 4)];
		un32Temp.ab8Data[1] = (int)pbTemp[6 + iTemp + (i * 4)];
		un32Temp.ab8Data[0] = (int)pbTemp[7 + iTemp + (i * 4)];
		pdElectricalData2[i] = un32Temp.f32Data;
	}

	iTemp = apCommParaST[LITSIndex]->stSpectrometerPara.iPixelNumber * 4 + 64;

	for(i = 0; i < apCommParaST[LITSIndex]->stSpectrometerPara.iPixelNumber; i++)
	{
		pdSpectumData3[i] = (double)(((double)pbTemp[4 + (i * 2) + iTemp] * 256) + pbTemp[4 + (i * 2) + iTemp + 1]);
	}

	iTemp = apCommParaST[LITSIndex]->stSpectrometerPara.iPixelNumber * 6 + 64;

	for(i = 0; i < 8; i++)
	{
		un32Temp.ab8Data[3] = (int)pbTemp[4 + iTemp + (i * 4)];
		un32Temp.ab8Data[2] = (int)pbTemp[5 + iTemp + (i * 4)];
		un32Temp.ab8Data[1] = (int)pbTemp[6 + iTemp + (i * 4)];
		un32Temp.ab8Data[0] = (int)pbTemp[7 + iTemp + (i * 4)];
		pdElectricalData3[i] = un32Temp.f32Data;
	}
	
	return SA_API_SUCCESS;
}


int LITS_GetMeasureDataHWTrigger(int LITSIndex, double *pdSpectumData1, float *pdElectricalData1, 
										 double *pdSpectumData2, float *pdElectricalData2, 
										 double *pdSpectumData3, float *pdElectricalData3, 
										 TRIGGER_MODE TriggerMode, int iTimeOut)
{
	BYTE *pbTemp;
	BYTE bTemp[1];
	int i = 0;
	int iTemp = 0;
	UN_32TYPE un32Temp;

		
	if(LITSIndex > g_iCommIndex)
	{	
		return SA_API_FAIL;
	}
	
	switch(TriggerMode)
	{
		case EXINT_RISING_EDGE:
			bTemp[0] = 0x04;
			break;
		case EXINT_FALLING_EDGE:
			bTemp[0] = 0x05;
			break;
		case EXINT_HIGH_LEVEL:
			bTemp[0] = 0x08;
			break;
		case EXINT_LOW_LEVEL:
			bTemp[0] = 0x09;
			break;
		default:
			return SA_API_FAIL;
	}

	if(MIGP_RegArea_Write(apCommParaST[LITSIndex], VPA, 0x0000, 1, bTemp, MIGP_ACK_RX_ENABLE) == FALSE)
	{
		return SA_API_FAIL;
	}


	if(MIGP_RegArea_Read_NoRequest(apCommParaST[LITSIndex], MDA, 0x0000, ((apCommParaST[LITSIndex]->stSpectrometerPara.iPixelNumber * 2) + 32) * 3,
			   &pbTemp, iTimeOut) == FALSE)
	{
		return SA_API_FAIL;
	}

	//*pSpectumNumber = apCommParaST[LITSIndex]->stSpectrometerPara.iPixelNumber;
	for(i = 0; i < apCommParaST[LITSIndex]->stSpectrometerPara.iPixelNumber; i++)
	{
		pdSpectumData1[i] = (double)(((double)pbTemp[4 + (i * 2)] * 256) + pbTemp[4 + (i * 2) + 1]);
	}

	iTemp = apCommParaST[LITSIndex]->stSpectrometerPara.iPixelNumber * 2;

	for(i = 0; i < 8; i++)
	{
		un32Temp.ab8Data[3] = (int)pbTemp[4 + iTemp + (i * 4)];
		un32Temp.ab8Data[2] = (int)pbTemp[5 + iTemp + (i * 4)];
		un32Temp.ab8Data[1] = (int)pbTemp[6 + iTemp + (i * 4)];
		un32Temp.ab8Data[0] = (int)pbTemp[7 + iTemp + (i * 4)];
		pdElectricalData1[i] = un32Temp.f32Data;
	}

	iTemp = apCommParaST[LITSIndex]->stSpectrometerPara.iPixelNumber * 2 + 32;

	for(i = 0; i < apCommParaST[LITSIndex]->stSpectrometerPara.iPixelNumber; i++)
	{
		pdSpectumData2[i] = (double)(((double)pbTemp[4 + (i * 2) + iTemp] * 256) + pbTemp[4 + (i * 2) + iTemp + 1]);
	}

	iTemp = apCommParaST[LITSIndex]->stSpectrometerPara.iPixelNumber * 4 + 32;

	for(i = 0; i < 8; i++)
	{
		un32Temp.ab8Data[3] = (int)pbTemp[4 + iTemp + (i * 4)];
		un32Temp.ab8Data[2] = (int)pbTemp[5 + iTemp + (i * 4)];
		un32Temp.ab8Data[1] = (int)pbTemp[6 + iTemp + (i * 4)];
		un32Temp.ab8Data[0] = (int)pbTemp[7 + iTemp + (i * 4)];
		pdElectricalData2[i] = un32Temp.f32Data;
	}

	iTemp = apCommParaST[LITSIndex]->stSpectrometerPara.iPixelNumber * 4 + 64;

	for(i = 0; i < apCommParaST[LITSIndex]->stSpectrometerPara.iPixelNumber; i++)
	{
		pdSpectumData3[i] = (double)(((double)pbTemp[4 + (i * 2) + iTemp] * 256) + pbTemp[4 + (i * 2) + iTemp + 1]);
	}

	iTemp = apCommParaST[LITSIndex]->stSpectrometerPara.iPixelNumber * 6 + 64;

	for(i = 0; i < 8; i++)
	{
		un32Temp.ab8Data[3] = (int)pbTemp[4 + iTemp + (i * 4)];
		un32Temp.ab8Data[2] = (int)pbTemp[5 + iTemp + (i * 4)];
		un32Temp.ab8Data[1] = (int)pbTemp[6 + iTemp + (i * 4)];
		un32Temp.ab8Data[0] = (int)pbTemp[7 + iTemp + (i * 4)];
		pdElectricalData3[i] = un32Temp.f32Data;
	}



	apCommParaST[LITSIndex]->stSpectrometerPara.cTriggerMode = (BYTE)SOFTWARE_SYNCHRONOUS;
	
	return SA_API_SUCCESS;
}



int LITS_SetMode(int LITSIndex, char cMode, char cLedType)
{
	BYTE bTemp[2];
	
	if(LITSIndex > g_iCommIndex)
	{	
		return SA_API_FAIL;
	}

	bTemp[0] = cMode;
	bTemp[1] = cLedType;

	if(MIGP_RegArea_Write(apCommParaST[LITSIndex], NVPA, NVPA_WORK_MODE_ADDR, 2, bTemp, MIGP_ACK_RX_ENABLE) == FALSE)
	{
		return SA_API_FAIL;
	}
	
	
	return SA_API_SUCCESS;
}

int LITS_GetMode(int LITSIndex, char *pcMode, char *pcLedType)
{
	BYTE *pbTemp;

	if(LITSIndex > g_iCommIndex)
	{	
		return SA_API_FAIL;
	}
	
	if(MIGP_RegArea_Read(apCommParaST[LITSIndex], NVPA, NVPA_WORK_MODE_ADDR, 2, &pbTemp, 100) == FALSE)
	{
		return SA_API_FAIL;
	}
	
	return SA_API_SUCCESS;
}


int LITS_SetPolarityJudgmentPara(int LITSIndex, float fVoltage , float fCurrent, float fDelay, float fTime)
{
	BYTE bTemp[16];
	UN_32TYPE un32Temp;
	
	if(LITSIndex > g_iCommIndex)
	{	
		return SA_API_FAIL;
	}
	
	un32Temp.f32Data = fVoltage;
	bTemp[0] = un32Temp.ab8Data[3];
	bTemp[1] = un32Temp.ab8Data[2];
	bTemp[2] = un32Temp.ab8Data[1];
	bTemp[3] = un32Temp.ab8Data[0];
	un32Temp.f32Data = fCurrent;
	bTemp[4] = un32Temp.ab8Data[3];
	bTemp[5] = un32Temp.ab8Data[2];
	bTemp[6] = un32Temp.ab8Data[1];
	bTemp[7] = un32Temp.ab8Data[0];
	un32Temp.f32Data = fDelay;
	bTemp[8] = un32Temp.ab8Data[3];
	bTemp[9] = un32Temp.ab8Data[2];
	bTemp[10] = un32Temp.ab8Data[1];
	bTemp[11] = un32Temp.ab8Data[0];
	un32Temp.f32Data = fTime;
	bTemp[12] = un32Temp.ab8Data[3];
	bTemp[13] = un32Temp.ab8Data[2];
	bTemp[14] = un32Temp.ab8Data[1];
	bTemp[15] = un32Temp.ab8Data[0];

	if(MIGP_RegArea_Write(apCommParaST[LITSIndex], NVPA, NVPA_POLARITY_VOLTAGE_ADDR, 16, bTemp, MIGP_ACK_RX_ENABLE) == FALSE)
	{
		return SA_API_FAIL;
	}
	
	return SA_API_SUCCESS;
}

int LITS_SetLedNegativePara(int LITSIndex, float fVoltage , float fCurrent, float fDelay, float fTime, int iChannelID)
{
	BYTE bTemp[16];
	UN_32TYPE un32Temp;
	int iAddress = 0;
	
	if(LITSIndex > g_iCommIndex)
	{	
		return SA_API_FAIL;
	}

	if(iChannelID == LED_CHANNEL1)
	{
		iAddress = NVPA_CH1_NEGATIVE_VOLTAGE_ADDR;
	}
	else if(iChannelID == LED_CHANNEL2)
	{
		iAddress = NVPA_CH2_NEGATIVE_VOLTAGE_ADDR;
	}
	else if(iChannelID == LED_CHANNEL3)
	{
		iAddress = NVPA_CH3_NEGATIVE_VOLTAGE_ADDR;
	}
	else
	{
		return SA_API_FAIL;
	}
	
	un32Temp.f32Data = fVoltage;
	bTemp[0] = un32Temp.ab8Data[3];
	bTemp[1] = un32Temp.ab8Data[2];
	bTemp[2] = un32Temp.ab8Data[1];
	bTemp[3] = un32Temp.ab8Data[0];
	un32Temp.f32Data = fCurrent;
	bTemp[4] = un32Temp.ab8Data[3];
	bTemp[5] = un32Temp.ab8Data[2];
	bTemp[6] = un32Temp.ab8Data[1];
	bTemp[7] = un32Temp.ab8Data[0];
	un32Temp.f32Data = fDelay;
	bTemp[8] = un32Temp.ab8Data[3];
	bTemp[9] = un32Temp.ab8Data[2];
	bTemp[10] = un32Temp.ab8Data[1];
	bTemp[11] = un32Temp.ab8Data[0];
	un32Temp.f32Data = fTime;
	bTemp[12] = un32Temp.ab8Data[3];
	bTemp[13] = un32Temp.ab8Data[2];
	bTemp[14] = un32Temp.ab8Data[1];
	bTemp[15] = un32Temp.ab8Data[0];

	if(MIGP_RegArea_Write(apCommParaST[LITSIndex], NVPA, iAddress, 16, bTemp, MIGP_ACK_RX_ENABLE) == FALSE)
	{
		return SA_API_FAIL;
	}
	
	return SA_API_SUCCESS;
}

int LITS_SetLedPositivePara(int LITSIndex, float fVoltage , float fCurrent, float fDelay, float fTime, int iChannelID)
	{
		BYTE bTemp[16];
		UN_32TYPE un32Temp;
		int iAddress = 0;
		
		if(LITSIndex > g_iCommIndex)
		{	
			return SA_API_FAIL;
		}
	
		if(iChannelID == LED_CHANNEL1)
		{
			iAddress = NVPA_CH1_POSITIVE_VOLTAGE_ADDR;
		}
		else if(iChannelID == LED_CHANNEL2)
		{
			iAddress = NVPA_CH2_POSITIVE_VOLTAGE_ADDR;
		}
		else if(iChannelID == LED_CHANNEL3)
		{
			iAddress = NVPA_CH3_POSITIVE_VOLTAGE_ADDR;
		}
		else
		{
			return SA_API_FAIL;
		}
		
		un32Temp.f32Data = fVoltage;
		bTemp[0] = un32Temp.ab8Data[3];
		bTemp[1] = un32Temp.ab8Data[2];
		bTemp[2] = un32Temp.ab8Data[1];
		bTemp[3] = un32Temp.ab8Data[0];
		un32Temp.f32Data = fCurrent;
		bTemp[4] = un32Temp.ab8Data[3];
		bTemp[5] = un32Temp.ab8Data[2];
		bTemp[6] = un32Temp.ab8Data[1];
		bTemp[7] = un32Temp.ab8Data[0];
		un32Temp.f32Data = fDelay;
		bTemp[8] = un32Temp.ab8Data[3];
		bTemp[9] = un32Temp.ab8Data[2];
		bTemp[10] = un32Temp.ab8Data[1];
		bTemp[11] = un32Temp.ab8Data[0];
		un32Temp.f32Data = fTime;
		bTemp[12] = un32Temp.ab8Data[3];
		bTemp[13] = un32Temp.ab8Data[2];
		bTemp[14] = un32Temp.ab8Data[1];
		bTemp[15] = un32Temp.ab8Data[0];
	
		if(MIGP_RegArea_Write(apCommParaST[LITSIndex], NVPA, iAddress, 16, bTemp, MIGP_ACK_RX_ENABLE) == FALSE)
		{
			return SA_API_FAIL;
		}
		
		return SA_API_SUCCESS;
	}



int LITS_GetPolarityJudgmentPara(int LITSIndex, float *pfVoltage , float *pfCurrent, float *pfDelay, float *pfTime)
{
	BYTE *pbTemp;
	UN_32TYPE un32Temp;

	if(LITSIndex > g_iCommIndex)
	{	
		return SA_API_FAIL;
	}
	
	if(MIGP_RegArea_Read(apCommParaST[LITSIndex], NVPA, NVPA_POLARITY_VOLTAGE_ADDR, 16, &pbTemp, 100) == FALSE)
	{
		return SA_API_FAIL;
	}

	un32Temp.ab8Data[3] = pbTemp[4];
	un32Temp.ab8Data[2] = pbTemp[5];
	un32Temp.ab8Data[1] = pbTemp[6];
	un32Temp.ab8Data[0] = pbTemp[7];
	*pfVoltage = un32Temp.f32Data;
	un32Temp.ab8Data[3] = pbTemp[8];
	un32Temp.ab8Data[2] = pbTemp[9];
	un32Temp.ab8Data[1] = pbTemp[10];
	un32Temp.ab8Data[0] = pbTemp[11];
	*pfCurrent = un32Temp.f32Data;
	un32Temp.ab8Data[3] = pbTemp[12];
	un32Temp.ab8Data[2] = pbTemp[13];
	un32Temp.ab8Data[1] = pbTemp[14];
	un32Temp.ab8Data[0] = pbTemp[15];
	*pfDelay = un32Temp.f32Data;
	un32Temp.ab8Data[3] = pbTemp[16];
	un32Temp.ab8Data[2] = pbTemp[17];
	un32Temp.ab8Data[1] = pbTemp[18];
	un32Temp.ab8Data[0] = pbTemp[19];
	*pfTime = un32Temp.f32Data;
	
	return SA_API_SUCCESS;
}

int LITS_GetLedPositivePara(int LITSIndex, float *pfVoltage , float *pfCurrent, float *pfDelay, float *pfTime, int iChannelID)
{
	BYTE *pbTemp;
	UN_32TYPE un32Temp;
	int iAddress = 0;

	if(LITSIndex > g_iCommIndex)
	{	
		return SA_API_FAIL;
	}

	if(iChannelID == LED_CHANNEL1)
	{
		iAddress = NVPA_CH1_POSITIVE_VOLTAGE_ADDR;
	}
	else if(iChannelID == LED_CHANNEL2)
	{
		iAddress = NVPA_CH2_POSITIVE_VOLTAGE_ADDR;
	}
	else if(iChannelID == LED_CHANNEL3)
	{
		iAddress = NVPA_CH3_POSITIVE_VOLTAGE_ADDR;
	}
	else
	{
		return SA_API_FAIL;
	}
		
	
	if(MIGP_RegArea_Read(apCommParaST[LITSIndex], NVPA, iAddress, 16, &pbTemp, 100) == FALSE)
	{
		return SA_API_FAIL;
	}

	un32Temp.ab8Data[3] = pbTemp[4];
	un32Temp.ab8Data[2] = pbTemp[5];
	un32Temp.ab8Data[1] = pbTemp[6];
	un32Temp.ab8Data[0] = pbTemp[7];
	*pfVoltage = un32Temp.f32Data;
	un32Temp.ab8Data[3] = pbTemp[8];
	un32Temp.ab8Data[2] = pbTemp[9];
	un32Temp.ab8Data[1] = pbTemp[10];
	un32Temp.ab8Data[0] = pbTemp[11];
	*pfCurrent = un32Temp.f32Data;
	un32Temp.ab8Data[3] = pbTemp[12];
	un32Temp.ab8Data[2] = pbTemp[13];
	un32Temp.ab8Data[1] = pbTemp[14];
	un32Temp.ab8Data[0] = pbTemp[15];
	*pfDelay = un32Temp.f32Data;
	un32Temp.ab8Data[3] = pbTemp[16];
	un32Temp.ab8Data[2] = pbTemp[17];
	un32Temp.ab8Data[1] = pbTemp[18];
	un32Temp.ab8Data[0] = pbTemp[19];
	*pfTime = un32Temp.f32Data;
	
	return SA_API_SUCCESS;
}

int LITS_GetLedNegativePara(int LITSIndex, float *pfVoltage , float *pfCurrent, float *pfDelay, float *pfTime, int iChannelID)
{
	BYTE *pbTemp;
	UN_32TYPE un32Temp;
	int iAddress = 0;

	if(LITSIndex > g_iCommIndex)
	{	
		return SA_API_FAIL;
	}

	if(iChannelID == LED_CHANNEL1)
	{
		iAddress = NVPA_CH1_NEGATIVE_VOLTAGE_ADDR;
	}
	else if(iChannelID == LED_CHANNEL2)
	{
		iAddress = NVPA_CH2_NEGATIVE_VOLTAGE_ADDR;
	}
	else if(iChannelID == LED_CHANNEL3)
	{
		iAddress = NVPA_CH3_NEGATIVE_VOLTAGE_ADDR;
	}
	else
	{
		return SA_API_FAIL;
	}
		
	
	if(MIGP_RegArea_Read(apCommParaST[LITSIndex], NVPA, iAddress, 16, &pbTemp, 100) == FALSE)
	{
		return SA_API_FAIL;
	}

	un32Temp.ab8Data[3] = pbTemp[4];
	un32Temp.ab8Data[2] = pbTemp[5];
	un32Temp.ab8Data[1] = pbTemp[6];
	un32Temp.ab8Data[0] = pbTemp[7];
	*pfVoltage = un32Temp.f32Data;
	un32Temp.ab8Data[3] = pbTemp[8];
	un32Temp.ab8Data[2] = pbTemp[9];
	un32Temp.ab8Data[1] = pbTemp[10];
	un32Temp.ab8Data[0] = pbTemp[11];
	*pfCurrent = un32Temp.f32Data;
	un32Temp.ab8Data[3] = pbTemp[12];
	un32Temp.ab8Data[2] = pbTemp[13];
	un32Temp.ab8Data[1] = pbTemp[14];
	un32Temp.ab8Data[0] = pbTemp[15];
	*pfDelay = un32Temp.f32Data;
	un32Temp.ab8Data[3] = pbTemp[16];
	un32Temp.ab8Data[2] = pbTemp[17];
	un32Temp.ab8Data[1] = pbTemp[18];
	un32Temp.ab8Data[0] = pbTemp[19];
	*pfTime = un32Temp.f32Data;
	
	return SA_API_SUCCESS;
}

int LITS_SetBinOutput(int LITSIndex, int iBin)
{
	BYTE bTemp[1];

	bTemp[0] = (BYTE)iBin;
	if(MIGP_RegArea_Write(apCommParaST[LITSIndex], VPA, 36, 1, bTemp, MIGP_ACK_RX_ENABLE) == FALSE)
	{
		return SA_API_FAIL;
	}

	return SA_API_SUCCESS;
}

