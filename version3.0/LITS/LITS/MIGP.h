/*******************************************************************************************************
**
** Copyright (C), 2011-2046, Nahon photoelectric technology CO., LTD.
** File Name:              MIGP.h
** Description:             
** Created By:             Monster
**
*********************************************************************************************************/



/* 设备信息域命令 */
#define MIGP_CMD_EIA_READ     0x30
#define MIGP_CMD_EIA_WRITE    0x31

/* 易失参数域命令 */
#define MIGP_CMD_VPA_READ      0x40
#define MIGP_CMD_VPA_WRITE     0x41
//#define MIGP_CMD_VPA_UPDATE    0x42

/* 非易失参数域命令 */
#define MIGP_CMD_NVPA_READ       0x50
#define MIGP_CMD_NVPA_WRITE      0x51
//#define MIGP_CMD_NVPA_UPDATE     0x52

/* 测量参数域命令 */
#define MIGP_CMD_MDA_READ       0x60
#define MIGP_CMD_MDA_UPDATE     0x62

/*保留域命令 */
#define MIGP_CMD_SRA_READ     0x70
#define MIGP_CMD_SRA_WRITE    0x71

#define  MIGP_REV_FRAME_NULL         0x00
#define  MIGP_REV_FRAME_F_0X55_FLAG  0x01
#define  MIGP_REV_FRAME_F_0XAA_FLAG  0x02
#define  MIGP_REV_FRAME_F_0X7B_FLAG  0x03
#define  MIGP_REV_FRAME_F_0X7D_FLAG  0x04
#define  MIGP_REV_FRAME_S_0X55_FLAG  0x05
#define  MIGP_REV_FRAME_S_0XAA_FLAG  0x06
#define  MIGP_REV_FRAME_S_0X7B_FLAG  0x07
#define  MIGP_REV_FRAME_S_0X7D_FLAG  0x08
#define  MIGP_REV_FRAME_START_OK     0x09

#define  MIGP_REV_FRAME_MAX_LENGTH   8000


#define COM_SEND_MAX_TIMEOUT  5000


#define MIGP_FRAME_RX_FLAG_OK    1 
#define MIGP_FRAME_RX_FLAG_NULL  0

#define MIGP_ACK_RX_ENABLE    1
#define MIGP_ACK_RX_DISABLE   0

#define NONLINEAR_CALIB_DISABLE        0
#define NONLINEAR_CALIB_WAVELENGTH     1
#define NONLINEAR_CALIB_PIXEL          2
#define NONLINEAR_CALIB_WAVELENGTH_II  3
#define NONLINEAR_CALIB_PIXEL_II       4

#define ASYN_SCAN_STOP              0x00
#define ASYN_SCAN_WORK              0x01
#define ASYN_SCAN_OK                0x02


#define NVPA_WORK_MODE_ADDR               1024
#define NVPA_LED_TYPE_ADDR                1025
#define NVPA_POLARITY_VOLTAGE_ADDR		  1026
#define NVPA_POLARITY_CURRENT_ADDR        1030
#define NVPA_POLARITY_DELAY_TIME_ADDR     1034
#define NVPA_POLARITY_TEST_TIME_ADDR      1038

#define NVPA_CH1_NEGATIVE_VOLTAGE_ADDR    1042
#define NVPA_CH1_NEGATIVE_CURRENT_ADDR    1046
#define NVPA_CH1_NEGATIVE_DELAY_TIME_ADDR 1050
#define NVPA_CH1_NEGATIVE_TEST_TIME_ADDR  1054

#define NVPA_CH1_POSITIVE_VOLTAGE_ADDR    1058
#define NVPA_CH1_POSITIVE_CURRENT_ADDR    1062
#define NVPA_CH1_POSITIVE_DELAY_TIME_ADDR 1066
#define NVPA_CH1_POSITIVE_TEST_TIME_ADDR  1070

#define NVPA_CH2_NEGATIVE_VOLTAGE_ADDR    1074
#define NVPA_CH2_NEGATIVE_CURRENT_ADDR    1078
#define NVPA_CH2_NEGATIVE_DELAY_TIME_ADDR 1082
#define NVPA_CH2_NEGATIVE_TEST_TIME_ADDR  1086
#define NVPA_CH2_POSITIVE_VOLTAGE_ADDR    1090
#define NVPA_CH2_POSITIVE_CURRENT_ADDR    1094
#define NVPA_CH2_POSITIVE_DELAY_TIME_ADDR 1098
#define NVPA_CH2_POSITIVE_TEST_TIME_ADDR  1102

#define NVPA_CH3_NEGATIVE_VOLTAGE_ADDR    1106
#define NVPA_CH3_NEGATIVE_CURRENT_ADDR    1110
#define NVPA_CH3_NEGATIVE_DELAY_TIME_ADDR 1114
#define NVPA_CH3_NEGATIVE_TEST_TIME_ADDR  1118
#define NVPA_CH3_POSITIVE_VOLTAGE_ADDR    1122
#define NVPA_CH3_POSITIVE_CURRENT_ADDR    1126
#define NVPA_CH3_POSITIVE_DELAY_TIME_ADDR 1130
#define NVPA_CH3_POSITIVE_TEST_TIME_ADDR  1134





typedef enum
{
	EIA,
	NVPA,
	VPA,
	MDA,
	SRA
}AREA_TYPE;

typedef enum
{
	COM_SERIAL,
	USB_WINLIB,
	TCP_ETHERNET
}COMM_TYPE;


typedef struct
{
    BYTE bMasterAddress;
	BYTE bSlaveAddress;
	int ulBuffRxNum;
    int ulBuffTxNum;
	unsigned char  ucFrameState;
	BOOL  bReceiveFlag;
    WORD  dErrorCode;
	BYTE  bFrameRxBuff[MIGP_REV_FRAME_MAX_LENGTH];
    BYTE  bFrameTxBuff[MIGP_REV_FRAME_MAX_LENGTH];
}MIGP_ST;

typedef struct
{
	HANDLE ComHandle;
	int iBaudRate;
	int iUSBDevNum;
	char acComName[50];
}COM_PARA_ST;


typedef struct
{
	
}NET_PARA_ST;

typedef struct
{
	char cTriggerMode;
	int iIntegrationTime;
	int iChannelIntegrationTime[16];
	int iAverageTimes;
	int iTriggerDelay;
	
    int iStartWavelength;
    int iEndWavelength;
    int iMinIntegrationTimeUS;
    int iMaxIntegrationTimeUS;
    int iPixelNumber;
	
    double adWavelengthCalib[4];
    char cNonlinearCalibType;
    int iNonlinearCalibLength;
    float fNonlinearCalibPixelOrWL[8];
    int iNonlinearCalibCoNumber[8];
    float afNonlinearCalibAD[8][10];
    float afNonlinearCalibCo[8][10];
}SP_PARA_ST;


typedef struct
{
	char aucEquipmentInfo[17];
    char ucHardWareVersion;
    char aucSoftWareVersion[5];
    char aucSerialNumber[17];
    char aucManufacturingDate[17];
}EIA_ST;

typedef struct
{
	COMM_TYPE enCommType;
    MIGP_ST stMIGP;
	COM_PARA_ST stComPara;
	NET_PARA_ST stNetPara;
	SP_PARA_ST stSpectrometerPara;
    EIA_ST stEIA;
}COMM_PARA_ST;

typedef union
{
	BYTE  ab8Data[8];
	double d64Data;
}UN_TYPE;

typedef union
{
	BYTE  ab8Data[4];
	float f32Data;
}UN_32TYPE;

/* EIA 数据*/
#define EIA_EQUIPMENT_INFO_ADDR        0
#define EIA_HARDWARE_VERSION_ADDR      16
#define EIA_SOFTWARE_VERSION_ADDR      24
#define EIA_SERIAL_NUMBER_ADDR         32
#define EIA_MANUFACTURING_DATE_ADDR    48

#define EIA_PRODUCT_SERIES_ADDR        64
#define EIA_PRODUCT_TYPE_ADDR          66
#define EIA_MIGP_COMM_ADDR             68

#define EIA_UART_PARA_ADDR             80
#define EIA_CAN_PARA_ADDR              84
#define EIA_ETHERNET_PARA_ADDR         96

#define EIA_REG_MAX_LENGTH             128


/* VPA 数据*/
#define VPA_RUN_MODE_ADDR                    0
#define VPA_INTE_TIME_ADDR                   1
#define VPA_AVERAGE_TIME_ADDR                5
#define VPA_TRIGGER_DELAY_ADDR               7

#define VPA_ASYN_SCAN_ADDR                   9

#define VPA_LAMP_ENABLE_ADDR                 16

#define VPA_UNSYNC_STROBE_ENABLE_ADDR        17
#define VPA_UNSYNC_STROBE_HIGH_ADDR          18
#define VPA_UNSYNC_STROBE_LOW_ADDR           20

#define VPA_SYNC_STROBE_ENABLE_ADDR          22
#define VPA_SYNC_STROBE_TYPE_ADDR            23
#define VPA_SYNC_STROBE_PULSE_WIDTH_ADDR     24
#define VPA_SYNC_STROBE_INTERVAL_WIDTH_ADDR  26
#define VPA_SYNC_STROBE_DELAY_ADDR           28
#define VPA_SYNC_STROBE_NUMBER_ADDR          32

#define VPA_GPIO_REG_ADDR                    36
#define VPA_I2C_REG_ADDR                     40
#define VPA_SPI_REG_ADDR                     44
#define VPA_DATA_BUFF_ADDR                   48


#define VPA_REG_MAX_LENGTH               112


/* NVPA 数据*/
#define NVPA_MIN_WAVELENGTH_ADDR     0
#define NVPA_MAX_WAVELENGTH_ADDR     2
#define NVPA_MIN_INTEGRAL_TIME_ADDR  4
#define NVPA_MAX_INTEGRAL_TIME_ADDR  8
#define NVPA_PIXELS_NUMBER_ADDR      12


#define NVPA_OUTPUT_ADDR                  14

#define NVPA_PIXELS_MISS_ADDR             16



#define NVPA_WAVELENGTH_CALIB_ADDR   32
#define NVPA_NONLINEAR_CALIB_ADDR    64
#define NVPA_REG_MAX_LENGTH          128



void MIGP_RevBuff_Init(MIGP_ST *pstMIGPCom);
BOOL MIGP_Send_FrameHead(void *pstCommHandle);
BOOL MIGP_Send_FrameEnd(void *pstCommHandle, BYTE bLRC);
BOOL MIGP_Send_FrameCMD(void *pstCommHandle, BYTE bCMD);
BOOL MIGP_Send_FrameData(void *pstCommHandle, int ulLength, BYTE *pucData, BYTE *pbLRC);
BOOL MIGP_RegArea_Write(void *pstCommHandle, AREA_TYPE enAreaType, int ulAddress, int ulLength, BYTE *pbTxData, BYTE bACKEnable);
BOOL MIGP_Frame_Resolution(void *pstCommHandle, BYTE **bBuff, int *pulLength, BYTE *bCMD, BYTE bCRCFlag);
BOOL MIGP_RegArea_Read(void *pstCommHandle, AREA_TYPE enAreaType, 
	                   int ulAddress, int ulLength, 
	                   BYTE **pbRxData, int iTimeOut);
BOOL MIGP_Receive_Frame(void *pstCommHandle, int iTimeOut, int ulFrameLength, BYTE bCmd, BYTE **pbRxData);
BOOL MIGP_Receive_Frame_No_CRC(void *pstCommHandle, int iTimeOut, int ulFrameLength, BYTE bCmd, BYTE **pbRxData);
BOOL MIGP_RegArea_Read_NoRequest(void *pstCommHandle, AREA_TYPE enAreaType, 
	                   int ulAddress, int ulLength, 
	                   BYTE **pbRxData, int iTimeOut);


