// SpectraArsenal.cpp : Defines the entry point for the DLL application.
//
#include "stdafx.h"
#include "stdlib.h"
#include "malloc.h"
#include "stdio.h"
#include "USB_Driver.h"

#include "MIGP.h"
#include "LITS.h"

void MIGP_RevBuff_Init(MIGP_ST *pstMIGPCom)
{
	pstMIGPCom->ulBuffRxNum = 0;
    pstMIGPCom->ucFrameState = MIGP_REV_FRAME_NULL;
	pstMIGPCom->bReceiveFlag = MIGP_FRAME_RX_FLAG_NULL;

	return;
}

void MIGP_Rev_Byte(MIGP_ST *pstMIGPCom, BYTE bData)
{
    if(pstMIGPCom->bReceiveFlag == MIGP_FRAME_RX_FLAG_OK)
    {
//    	printf_debug("MIGP_Rev_Byte:: bReceiveFlag is OK");
        return;
    }
	
    if(pstMIGPCom->ulBuffRxNum >= MIGP_REV_FRAME_MAX_LENGTH)
    {
        pstMIGPCom->ulBuffRxNum = 0;
        pstMIGPCom->ucFrameState = MIGP_REV_FRAME_NULL;
    }

    switch(pstMIGPCom->ucFrameState)
    {
        case MIGP_REV_FRAME_NULL:
            if(bData == 0x55)
            {
               pstMIGPCom->ucFrameState = MIGP_REV_FRAME_F_0X55_FLAG;
            }
            break;
        case MIGP_REV_FRAME_F_0X55_FLAG:
            if(bData == 0xAA)
            {
               pstMIGPCom->ucFrameState = MIGP_REV_FRAME_F_0XAA_FLAG;
            }
            else
            {
               pstMIGPCom->ucFrameState = MIGP_REV_FRAME_NULL;
            }
            break;
        case MIGP_REV_FRAME_F_0XAA_FLAG:
            if(bData == 0x7B)
            {
               pstMIGPCom->ucFrameState = MIGP_REV_FRAME_S_0X7B_FLAG;
            }
            else
            {
               pstMIGPCom->ucFrameState = MIGP_REV_FRAME_NULL;
            }
            break;
        case MIGP_REV_FRAME_S_0X55_FLAG:
            if(bData == 0xAA)
            {
                pstMIGPCom->ucFrameState = MIGP_REV_FRAME_S_0XAA_FLAG;
            }
            else
            {
                pstMIGPCom->bFrameRxBuff[pstMIGPCom->ulBuffRxNum++] = 0x55;
                pstMIGPCom->ucFrameState = MIGP_REV_FRAME_START_OK;
				MIGP_Rev_Byte(pstMIGPCom, bData);
            }
            break;
        case MIGP_REV_FRAME_S_0XAA_FLAG:
            if(bData == 0x7d)
            {
                pstMIGPCom->ucFrameState = MIGP_REV_FRAME_S_0X7D_FLAG;
            }
            else if(bData == 0x7b)
            {
                pstMIGPCom->ucFrameState = MIGP_REV_FRAME_S_0X7B_FLAG;
            }
            else
            {
                pstMIGPCom->bFrameRxBuff[pstMIGPCom->ulBuffRxNum++] = 0x55;
                pstMIGPCom->bFrameRxBuff[pstMIGPCom->ulBuffRxNum++] = 0xaa;
                pstMIGPCom->ucFrameState = MIGP_REV_FRAME_START_OK;
				MIGP_Rev_Byte(pstMIGPCom, bData);
            }
            break;
        case MIGP_REV_FRAME_F_0X7B_FLAG:
            if(bData == 0x7B)
            {
                pstMIGPCom->ucFrameState = MIGP_REV_FRAME_START_OK;
                pstMIGPCom->ulBuffRxNum = 0;
            }
            else
            {
                pstMIGPCom->ucFrameState = MIGP_REV_FRAME_NULL;
            }
            break;
        case MIGP_REV_FRAME_F_0X7D_FLAG:
            break;
        case MIGP_REV_FRAME_S_0X7B_FLAG:
            if(bData == 0x7b)
            {
                pstMIGPCom->ucFrameState = MIGP_REV_FRAME_START_OK;
                pstMIGPCom->ulBuffRxNum = 0;
            }
            else
            {
                pstMIGPCom->bFrameRxBuff[pstMIGPCom->ulBuffRxNum++] = 0x55;
                pstMIGPCom->bFrameRxBuff[pstMIGPCom->ulBuffRxNum++] = 0xaa;
                pstMIGPCom->bFrameRxBuff[pstMIGPCom->ulBuffRxNum++] = 0x7b;
                pstMIGPCom->ucFrameState = MIGP_REV_FRAME_START_OK;
				MIGP_Rev_Byte(pstMIGPCom, bData);
            }
            break;
        case MIGP_REV_FRAME_S_0X7D_FLAG:
            if(bData == 0x7d)
            {
                pstMIGPCom->bReceiveFlag = MIGP_FRAME_RX_FLAG_OK;
                pstMIGPCom->ucFrameState = MIGP_REV_FRAME_NULL;
            }
            else
            {
                pstMIGPCom->bFrameRxBuff[pstMIGPCom->ulBuffRxNum++] = 0x55;
                pstMIGPCom->bFrameRxBuff[pstMIGPCom->ulBuffRxNum++] = 0xaa;
                pstMIGPCom->bFrameRxBuff[pstMIGPCom->ulBuffRxNum++] = 0x7d;
                pstMIGPCom->ucFrameState = MIGP_REV_FRAME_START_OK;
				MIGP_Rev_Byte(pstMIGPCom, bData);
            }
            break;
        case MIGP_REV_FRAME_START_OK:
            if(bData == 0x55)
            {
                pstMIGPCom->ucFrameState = MIGP_REV_FRAME_S_0X55_FLAG;
            }
            else
            {
                pstMIGPCom->bFrameRxBuff[pstMIGPCom->ulBuffRxNum++] = bData;
            }
            break;
    }

    return;
}

BOOL MIGP_Frame_Resolution(void *pstCommHandle, BYTE **bBuff, BYTE bCMD, BYTE bCRCFlag)
{
    BYTE bMIGPLRC = 0;
	BYTE bTempLRC = 0;
    int i = 0;
	COMM_PARA_ST *pstMigpPara = NULL;
	int ulLength;
	BYTE RxCMD = 0 ;

	if(pstCommHandle == NULL)
	{
		//printf("MIGP_Frame_Resolution::pstCommHandle is NULL");
		return FALSE;
	}

	pstMigpPara = (COMM_PARA_ST *)pstCommHandle;

    if(pstMigpPara->stMIGP.ulBuffRxNum < 3)
    {
    	//printf("MIGP_Frame_Resolution::pstMigpPara->stMIGP.ulBuffTxNum is wrong");
        return FALSE;
    }

    RxCMD = pstMigpPara->stMIGP.bFrameRxBuff[2];
    bMIGPLRC = pstMigpPara->stMIGP.bFrameRxBuff[pstMigpPara->stMIGP.ulBuffRxNum - 1];
    *bBuff = &pstMigpPara->stMIGP.bFrameRxBuff[3];
	ulLength = pstMigpPara->stMIGP.ulBuffRxNum - 4;

    /* µØÖ·²»Æ¥Åä */
	if(pstMigpPara->stMIGP.bMasterAddress != pstMigpPara->stMIGP.bFrameRxBuff[0])
	{
		if(pstMigpPara->stMIGP.bFrameRxBuff[0] != 0x00)
		{
			//printf("MIGP_Frame_Resolution::address is wrong");
	        return FALSE;
		}
	}

    if(ulLength != 0)
    {
    	if(bCRCFlag == 1)
    	{
	        bTempLRC = 0;
	        for(i = 0; i < ulLength; i++)
	        {
	           bTempLRC += pstMigpPara->stMIGP.bFrameRxBuff[3 + i];
	        }
			
	        /* LRC²»Æ¥Åä */
	        if(bTempLRC != bMIGPLRC)
	        {
	        	//printf("MIGP_Frame_Resolution::LRC Check False");
	            return FALSE;
	        }
    	}
    }
	else
	{
		//printf("MIGP_Frame_Resolution::length is 0");
        return FALSE;
	}

	if(RxCMD != (bCMD | 0x80))
	{
		//printf("MIGP_Frame_Resolution:: Rx CMD is wrong");
		return FALSE;
	}
	

    return TRUE;
}


BOOL MIGP_Receive_Frame(void *pstCommHandle, int iTimeOut, int ulFrameLength, BYTE bCmd, BYTE **pbRxData)
{
	COMM_PARA_ST *pstMigpPara = NULL;
	BYTE bRxBuff[8000];
	//unsigned long ulRxLength;
	int USBRxLength;
	int i;
	
	if(pstCommHandle == NULL)
	{
		//printf_debug("MIGP_Receive_Frame::pstCommHandle is NULL");
		return FALSE;
	}

	pstMigpPara = (COMM_PARA_ST *)pstCommHandle;

	pstMigpPara->stMIGP.bReceiveFlag = MIGP_FRAME_RX_FLAG_NULL;
	pstMigpPara->stMIGP.ulBuffRxNum = 0;
	pstMigpPara->stMIGP.ucFrameState = MIGP_REV_FRAME_NULL;
    if(pstMigpPara->enCommType == USB_WINLIB)
	{	
		USBRxLength = USBBulkReadData(pstMigpPara->stComPara.iUSBDevNum, EP2_IN, (char *)bRxBuff, ulFrameLength, iTimeOut);
		if(USBRxLength <=  0)
		{
			return FALSE;
		}
		else
		{

	
            for(i = 0; i < USBRxLength; i++)
            {
				MIGP_Rev_Byte(&pstMigpPara->stMIGP, bRxBuff[i]);
				if(pstMigpPara->stMIGP.bReceiveFlag == MIGP_FRAME_RX_FLAG_OK)
				{
					if(MIGP_Frame_Resolution(pstCommHandle, pbRxData, bCmd, 1) == FALSE)
					{
						MIGP_RevBuff_Init(&pstMigpPara->stMIGP);
						return FALSE;
					}
					else
					{
						//printf("MIGP_Receive_Frame:: OK");
						return TRUE;
					}
				}
            }
		}
	}

	
	
	//printf_debug("MIGP_Receive_Frame::FALSE");
	return FALSE;
}

BOOL MIGP_Receive_Frame_No_CRC(void *pstCommHandle, int iTimeOut, int ulFrameLength, BYTE bCmd, BYTE **pbRxData)
{
	COMM_PARA_ST *pstMigpPara = NULL;
	//BYTE bRxBuff[4200];
	//unsigned long ulRxLength;
	//int i;
	
	if(pstCommHandle == NULL)
	{
//		printf_debug("MIGP_Receive_Frame::pstCommHandle is NULL");
		return FALSE;
	}

	pstMigpPara = (COMM_PARA_ST *)pstCommHandle;

	pstMigpPara->stMIGP.bReceiveFlag = MIGP_FRAME_RX_FLAG_NULL;
	pstMigpPara->stMIGP.ulBuffRxNum = 0;
	pstMigpPara->stMIGP.ucFrameState = MIGP_REV_FRAME_NULL;

	return FALSE;
}


void MIGP_Construct_FrameHead(BYTE *bTxBuff, int *pulTxNum)
{
    int ulNum = 0;

	bTxBuff[ulNum++] = 0x55;
	bTxBuff[ulNum++] = 0xaa;
	bTxBuff[ulNum++] = 0x7b;
	bTxBuff[ulNum++] = 0x7b;
	*pulTxNum = ulNum;
	
	return;
}

void MIGP_Construct_FrameEnd(BYTE *bTxBuff, int *pulTxNum, BYTE bLRC)
{
	int ulNum = *pulTxNum;
	
	bTxBuff[ulNum++] = bLRC;
	bTxBuff[ulNum++] = 0x55;
	bTxBuff[ulNum++] = 0xaa;
	bTxBuff[ulNum++] = 0x7d;
	bTxBuff[ulNum++] = 0x7d;
	*pulTxNum = ulNum;

	return;
}


void MIGP_Construct_FrameCMDAndAddr(BYTE *bTxBuff, int *pulTxNum, BYTE bCMD, BYTE bSlaveAddress, BYTE bMasterAddress)
{
	int ulNum = *pulTxNum;
	
	bTxBuff[ulNum++] = bSlaveAddress;
	bTxBuff[ulNum++] = bMasterAddress;
	bTxBuff[ulNum++] = bCMD;
	*pulTxNum = ulNum;

	return;
}

void MIGP_Construct_FrameData(BYTE *bTxBuff, int *pulTxNum, int ulLength, BYTE *pucData, BYTE *pbLRC)
{
	int i = 0;
	int ulNum = *pulTxNum;
	
	for(i = 0; i < ulLength; i++)
	{
		*pbLRC += pucData[i];
		bTxBuff[ulNum++] = pucData[i];
	}

	*pulTxNum = ulNum;

	return;
}


BOOL MIGP_RegArea_Write(void *pstCommHandle, AREA_TYPE enAreaType, int ulAddress, int ulLength, BYTE *pbTxData, BYTE bACKEnable)
{
	BYTE bTemp[8];
	BYTE bLRC = 0;
	BYTE bCmd = 0;
	COMM_PARA_ST *pstMigpPara = NULL;
//	BYTE bRxCMD;
//	int ulDataLength;
    BYTE *pbRxBuff;

	if(pstCommHandle == NULL)
	{
		//printf_debug("MIGP_RegArea_Write:: pstCommHandle is NULL");
		return FALSE;
	}

	pstMigpPara = (COMM_PARA_ST *)pstCommHandle;

	if(enAreaType == EIA)
	{
		bCmd = MIGP_CMD_EIA_WRITE;
	}
	else if(enAreaType == NVPA)
	{
		bCmd = MIGP_CMD_NVPA_WRITE;
	}
	else if(enAreaType == VPA)
	{
		bCmd = MIGP_CMD_VPA_WRITE;
	}
	else if(enAreaType == SRA)
	{
		bCmd = MIGP_CMD_SRA_WRITE;
	}
	else
	{
		//printf_debug("MIGP_RegArea_Write:: bCmd is Error");
		return FALSE;
	}

	MIGP_Construct_FrameHead(pstMigpPara->stMIGP.bFrameTxBuff, &pstMigpPara->stMIGP.ulBuffTxNum);
	
	MIGP_Construct_FrameCMDAndAddr(pstMigpPara->stMIGP.bFrameTxBuff, &pstMigpPara->stMIGP.ulBuffTxNum, bCmd,
		                           pstMigpPara->stMIGP.bSlaveAddress, pstMigpPara->stMIGP.bMasterAddress);

	bTemp[0] = (BYTE)((ulAddress >> 24) & 0x000000ff);
	bTemp[1] = (BYTE)((ulAddress >> 16) & 0x000000ff);
	bTemp[2] = (BYTE)((ulAddress >> 8) & 0x000000ff);
	bTemp[3] = (BYTE)(ulAddress & 0x000000ff);
	bTemp[4] = (BYTE)((ulLength >> 24) & 0x000000ff);
	bTemp[5] = (BYTE)((ulLength >> 16) & 0x000000ff);
	bTemp[6] = (BYTE)((ulLength >> 8) & 0x000000ff);
	bTemp[7] = (BYTE)(ulLength & 0x000000ff);
	MIGP_Construct_FrameData(pstMigpPara->stMIGP.bFrameTxBuff, &pstMigpPara->stMIGP.ulBuffTxNum, 8, bTemp, &bLRC);

	MIGP_Construct_FrameData(pstMigpPara->stMIGP.bFrameTxBuff, &pstMigpPara->stMIGP.ulBuffTxNum, ulLength, pbTxData, &bLRC);
	
	MIGP_Construct_FrameEnd(pstMigpPara->stMIGP.bFrameTxBuff, &pstMigpPara->stMIGP.ulBuffTxNum, bLRC);

	
	
    if(pstMigpPara->enCommType == USB_WINLIB)
	{
		USBBulkWriteData(pstMigpPara->stComPara.iUSBDevNum, EP2_OUT, (char *)pstMigpPara->stMIGP.bFrameTxBuff,pstMigpPara->stMIGP.ulBuffTxNum, 100);
	}

	if(bACKEnable == MIGP_ACK_RX_ENABLE)
	{
		if(MIGP_Receive_Frame(pstCommHandle, 1000, 13, bCmd, &pbRxBuff) == FALSE)
		{
			//printf("MIGP_RegArea_Write:: MIGP_Receive_Frame is FALSE");
			return FALSE;
		}

		if(pbRxBuff[0] != 0x66)
		{
			//printf("MIGP_RegArea_Write:: ack is False");
			return FALSE;
		}
	}

	return TRUE;
}

BOOL MIGP_RegArea_Read(void *pstCommHandle, AREA_TYPE enAreaType, 
	                   int ulAddress, int ulLength, 
	                   BYTE **pbRxData, int iTimeOut)
{
	BYTE bTemp[8];
	BYTE bLRC = 0;
	BYTE bCmd = 0;
	COMM_PARA_ST *pstMigpPara = NULL;
//	BYTE bRxCMD;
//	int ulDataLength;

	if(pstCommHandle == NULL)
	{
		//printf_debug("MIGP_RegArea_Read:: pstCommHandle is NULL");
		return FALSE;
	}

	pstMigpPara = (COMM_PARA_ST *)pstCommHandle;

	if(enAreaType == EIA)
	{
		bCmd = MIGP_CMD_EIA_READ;
	}
	else if(enAreaType == NVPA)
	{
		bCmd = MIGP_CMD_NVPA_READ;
	}
	else if(enAreaType == VPA)
	{
		bCmd = MIGP_CMD_VPA_READ;
	}
	else if(enAreaType == MDA)
	{
		bCmd = MIGP_CMD_MDA_READ;
	}
	else if(enAreaType == SRA)
	{
		bCmd = MIGP_CMD_SRA_READ;
	}
	else
	{
		//printf_debug("MIGP_RegArea_Read:: enAreaType is Error");
		return FALSE;
	}
	

	MIGP_Construct_FrameHead(pstMigpPara->stMIGP.bFrameTxBuff, &pstMigpPara->stMIGP.ulBuffTxNum);
	
	MIGP_Construct_FrameCMDAndAddr(pstMigpPara->stMIGP.bFrameTxBuff, &pstMigpPara->stMIGP.ulBuffTxNum, bCmd,
		                           pstMigpPara->stMIGP.bSlaveAddress, pstMigpPara->stMIGP.bMasterAddress);

	bTemp[0] = (BYTE)((ulAddress >> 24) & 0x000000ff);
	bTemp[1] = (BYTE)((ulAddress >> 16) & 0x000000ff);
	bTemp[2] = (BYTE)((ulAddress >> 8) & 0x000000ff);
	bTemp[3] = (BYTE)(ulAddress & 0x000000ff);
	bTemp[4] = (BYTE)((ulLength >> 24) & 0x000000ff);
	bTemp[5] = (BYTE)((ulLength >> 16) & 0x000000ff);
	bTemp[6] = (BYTE)((ulLength >> 8) & 0x000000ff);
	bTemp[7] = (BYTE)(ulLength & 0x000000ff);
	MIGP_Construct_FrameData(pstMigpPara->stMIGP.bFrameTxBuff, &pstMigpPara->stMIGP.ulBuffTxNum, 8, bTemp, &bLRC);
	
	MIGP_Construct_FrameEnd(pstMigpPara->stMIGP.bFrameTxBuff, &pstMigpPara->stMIGP.ulBuffTxNum, bLRC);

	
    if(pstMigpPara->enCommType == USB_WINLIB)
	{
		
		USBBulkWriteData(pstMigpPara->stComPara.iUSBDevNum, EP2_OUT, (char *)pstMigpPara->stMIGP.bFrameTxBuff,pstMigpPara->stMIGP.ulBuffTxNum, 100);
	}


 
	if(MIGP_Receive_Frame(pstCommHandle, iTimeOut, ulLength + 16, bCmd, pbRxData) == FALSE)
	{
		//printf("MIGP_RegArea_Read:: MIGP_Receive_Frame is FALSE");
		return FALSE;
	}

	
	return TRUE;
}

BOOL MIGP_RegArea_Read_NoRequest(void *pstCommHandle, AREA_TYPE enAreaType, 
	                   int ulAddress, int ulLength, 
	                   BYTE **pbRxData, int iTimeOut)
{
	//BYTE bTemp[8];
	BYTE bLRC = 0;
	BYTE bCmd = 0;
	COMM_PARA_ST *pstMigpPara = NULL;
//	BYTE bRxCMD;
//	int ulDataLength;

	if(pstCommHandle == NULL)
	{
//		printf_debug("MIGP_RegArea_Read:: pstCommHandle is NULL");
		return FALSE;
	}

	pstMigpPara = (COMM_PARA_ST *)pstCommHandle;

	if(enAreaType == EIA)
	{
		bCmd = MIGP_CMD_EIA_READ;
	}
	else if(enAreaType == NVPA)
	{
		bCmd = MIGP_CMD_NVPA_READ;
	}
	else if(enAreaType == VPA)
	{
		bCmd = MIGP_CMD_VPA_READ;
	}
	else if(enAreaType == MDA)
	{
		bCmd = MIGP_CMD_MDA_READ;
	}
	else if(enAreaType == SRA)
	{
		bCmd = MIGP_CMD_SRA_READ;
	}
	else
	{
		return FALSE;
	}
	
 
	if(MIGP_Receive_Frame(pstCommHandle, iTimeOut, ulLength + 16, bCmd, pbRxData) == FALSE)
	{
//		printf_debug("MIGP_RegArea_Read_NoRequest:: MIGP_Receive_Frame is FALSE");
		return FALSE;
	}

	
	return TRUE;
}


