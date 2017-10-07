#include "stdafx.h"
#include "FileHandle.h"

////////////////////stafile
double DiameterOptic = 0;
int intTestWay = 0;   //0为正常测试  1为长亮测试
int intMixLight = 0;   //0为正常测试  1为混光测试
int intVfAverage = 0;
int intTestType = 0;  //0为可见光 1为不可见光
int intPackageway = 0;  //0为直插  1为贴片
int selectchiptype = 0;
int intChip = 0;      //0为双脚单晶  1为双脚双晶  2为三脚双晶  3为四脚双晶   4为四脚三晶   5为六角三晶
int intCommonfoot = 0;   //公共脚  0为D 1为A 2为B 3为C
int intPolarity = -1;    //0为共阳    1为共阴
int intSetway = 0;
int intIVTestWay = 0; //0为探头测IV 1为光谱仪测IV
int intWLType = 0;    //0为峰值波长  1为主波长
int intWLStepSetWay = 0;  //0为统一设置主波步长  1为分别设置
int intWLStep = 1;    //0为步长1nm，1为步长5nm
int intWLSteps[3] = {1, 1, 1};
int intSampleAverage = 0;
int intBoxcar = 0;
int intFailBin = 0;
int intMiddlePin = 0;
int intMiddleWave1 = 0;
int intMiddleWave2 = 0;
int DeadLed = 0;
int DeadLedBin[3] = {0, 0, 0};


TESTTYPE CHIP[3][18];
sngPOINT point[3][4];
int c[3];
bool usespectrum[3] = {false, false, false};
bool testXYZ[3] = {false, false, false}; 
int polfalsenum[3] = {0, 0, 0};  //反向测试项目的个数  IR VR
int intOpticGain[3];      //0为低   1为中    2为高  3为超高
double intIntegrationTime[3];
LightParam KeepLight[3];
LightParam PolParam[3];

int columns[3] = {0, 0, 0};
BinArray binArray;
extern CString MapBinCode[MAXBIN];

////////systemfile
SystemSet systemset;

////////////spectrumsetfile
CalCoeff calcoeff;
int iniTimeRate = 0;    //首次积分时间倍率
int WaitInteDelay = 0;  ///积分后 仅延时积分时间不够 还需另加延时

/////////////caldarkfile
double sngCurrentDark[3][PIXELNUM];

//////////////referfile
StandardLightResource standardCal;

//////////////csvfile
BinArray level_binArray;
int csvcolumns[3] = {0, 0, 0};

////////////XYcsvfile
CList<XYLEVELItem, XYLEVELItem> levelItem[3];
XYLEVELItem TotalRangeItem[3];

////////////////////ShootDotfile
extern CList<sngPOINT, sngPOINT> dot[3];

//////////////////logfile
CString passpercentpara[4];
CString BinData[MAXBIN][2];
CString StatisticData[3][54];
CArray<CString,CString> dataList;

/////////////////LMPfile
double standardWL[PIXELNUM], power[PIXELNUM];
int powernum = 0;

/////////////////////////////////FILE
bool ReadSysFile(CStdioFile *m_file)
{
	CString str;
	CString str2, str3, str4;

	m_file->ReadString(str);
	sscanf(str, "%*[^0-9]%d", &systemset.intMachineType);

	str2 = "";
	m_file->ReadString(str);
	sscanf(str, "%*[^0-9.-]%[0-9.-]", str2);
	systemset.VRoffset[0] = atof(str2);

	str3 = "";
	m_file->ReadString(str);
	sscanf(str, "%*[^0-9.-]%[0-9.-]", str3);
	systemset.VRoffset[1] = atof(str3);

	str4 = "";
	m_file->ReadString(str);
	sscanf(str, "%*[^0-9.-]%[0-9.-]", str4);
	systemset.VRoffset[2] = atof(str4);

	m_file->ReadString(str);
	sscanf(str, "%*[^0-9]%d", &systemset.checkCount);

	m_file->ReadString(str);
	sscanf(str, "%*[^0-9]%d", &systemset.validCount);

	m_file->ReadString(str);
	sscanf(str, "%*[^0-9]%d", &systemset.sentBinDelay);

	m_file->ReadString(str);
	sscanf(str, "%*[^0-9]%d", &systemset.mintesttime);

	return true;
}

bool WriteSysFile(CStdioFile *m_file)
{
	CString str_write;
	
	str_write.Format("MachineType:, %d\n", systemset.intMachineType);
	m_file->WriteString(str_write);

	str_write.Format("VRoffsetA:, %0.3f\n", systemset.VRoffset[0]);
	m_file->WriteString(str_write);

	str_write.Format("VRoffsetB:, %0.3f\n", systemset.VRoffset[1]);
	m_file->WriteString(str_write);

	str_write.Format("VRoffsetC:, %0.3f\n", systemset.VRoffset[2]);
	m_file->WriteString(str_write);

	str_write.Format("CheckCount:, %d\n", systemset.checkCount);
	m_file->WriteString(str_write);

	str_write.Format("ValidCount:, %d\n", systemset.validCount);
	m_file->WriteString(str_write);

	str_write.Format("SentBinDelay:, %d\n", systemset.sentBinDelay);
	m_file->WriteString(str_write);

	str_write.Format("Mintesttime:, %d\n", systemset.mintesttime);
	m_file->WriteString(str_write);

	return true;
}


bool ReadSpectrumSetFile(CStdioFile *m_file)
{
	CString str;
	CString str2;

	m_file->ReadString(str);
	sscanf(str, "%*[^0-9]%d", &calcoeff.pixels);

	str2 = "";
	m_file->ReadString(str);
	sscanf(str, "%*[^0-9.]%[0-9.]", str2);
	calcoeff.intercept = atof(str2);

	str2 = "";
	m_file->ReadString(str);
	sscanf(str, "%*[^0-9.]%[0-9.]", str2);
	calcoeff.firstCoeff = atof(str2);

	str2 = "";
	m_file->ReadString(str);
	sscanf(str, "%*[^0-9.-]%[0-9.-]", str2);
	calcoeff.secondCoeff = atof(str2);

	str2 = "";
	m_file->ReadString(str);
	sscanf(str, "%*[^0-9.-]%[0-9.-]", str2);
	calcoeff.thirdCoeff = atof(str2);

	m_file->ReadString(str);
	sscanf(str, "%*[^0-9]%d", &iniTimeRate);

	m_file->ReadString(str);
	sscanf(str, "%*[^0-9]%d", &WaitInteDelay);
	
	return true;
}

bool WriteSpectrumSetFile(CStdioFile *m_file)
{
	CString str_write;

	str_write.Format("Pixels:,      %d\n", calcoeff.pixels);
	m_file->WriteString(str_write);

	str_write.Format("Intecept:,    %f\n", calcoeff.intercept);
	m_file->WriteString(str_write);

	str_write.Format("FirstCoeff:,  %f\n", calcoeff.firstCoeff);
	m_file->WriteString(str_write);

	str_write.Format("SecondCoeff:, %f\n", calcoeff.secondCoeff);
	m_file->WriteString(str_write);

	str_write.Format("ThirdCoeff:,  %f\n", calcoeff.thirdCoeff);
	m_file->WriteString(str_write);
	
	str_write.Format("IniTimeRate:, %d\n", iniTimeRate);
	m_file->WriteString(str_write);

	str_write.Format("WaitInteDelay:, %d\n", WaitInteDelay);
	m_file->WriteString(str_write);

	return true;
}

bool ReadCalDarkFile(CStdioFile *m_file)
{
	CString str;
	char str_dark[3][20];

	for(int i=0; i<2048; i++)
	{
		m_file->ReadString(str);
		sscanf(str, "%s%s%s", str_dark[0], str_dark[1], str_dark[2]);
		sngCurrentDark[0][i] = atof(str_dark[0]);
		sngCurrentDark[1][i] = atof(str_dark[1]);
		sngCurrentDark[2][i] = atof(str_dark[2]);
	}

	return true;
}


bool ReadReferFile(CStdioFile *m_file)
{
	CString str;
	int i = 0;
	char str_sngReference[20], str_sngDark[20];
	char str_sngListPower[20], str_uJoulesCount[20];
	while(m_file->ReadString(str))
	{
		sscanf(str, "%s%s%s%s", str_sngReference, str_sngDark,
			                    str_sngListPower, str_uJoulesCount);
		standardCal.sngReference[i] = atof(str_sngReference);
		standardCal.sngDark[i] = atof(str_sngDark); 
		standardCal.sngListPower[i] = atof(str_sngListPower);
		standardCal.uJoulesCount[i] = atof(str_uJoulesCount);

		double differ = 0;
		differ = standardCal.sngReference[i] - standardCal.sngDark[i];
		if(differ <= 0)
		{
			standardCal.standardpower[i] = 0;
		}
		else
		{
			standardCal.standardpower[i] = standardCal.sngListPower[i] / differ;
		}
		i++;
	}

	return true;
}

bool WriteReferFile(CStdioFile *m_file, StandardLightResource *staCal)
{
	CString str_write;
	for(int i=0; i<PIXELNUM; i++)
	{
		str_write.Format("%f    %f    %f    %e\n", 
			staCal->sngReference[i], staCal->sngDark[i],
			staCal->sngListPower[i], staCal->uJoulesCount[i]);
		m_file->WriteString(str_write);
	}

	return true;
}


bool ReadStaFile(CStdioFile *m_file)
{	
	CString str, str_num, str_item;
	int i = 0, j = 0;
	int cols = 0;
	char str_pointX[4][10], str_pointY[4][10]; 
	char name[200] = "";
	char Vcom[20] = "0", Icom[20] = "0", min[20] = "0", max[20] = "0", contest[10] = "false";
	char str_time[20] = "1";
	char stavalue1[20] = "0", stavalue2[20] = "0";
	char calway[10] = "offset";
	char calparam1[20] = "1", calparam2[20] = "0", calparam3[20] = "1", calparam4[20];
	char usespec[10], tXYZ[10];
	char read[200] = "";
	char str_read[LEVELCOLUMNS][10] = {"", "", "", "", "", "", "", "", "", "",
                                       "", "", "", "", "", "", "", "", "", "",
						               "", "", "", "", "", "", "", "", "", "",
                                       "", "", "", "", "", "", "", "", "", "",
	                                   "", "", "", "", "", "", "", "", "", "",
	                                   "", "", "", "", "", "", "", "", "", ""};
	m_file->ReadString(str);   //1
	sscanf(str, "%s", str);
	if(str != "HC00")
	{
		return false;
	}

	m_file->ReadString(str);   //2
	m_file->ReadString(str);   //3              
	sscanf(str, "%*[^,],%s", str_read[0]);
	sscanf(str_read[0], "%[0-9.]", str_read[0]);
	DiameterOptic = atof(str_read[0]);

	m_file->ReadString(str);   //4              
	sscanf(str, "%*[^,],%d", &intTestWay);

	m_file->ReadString(str);   //5              
	sscanf(str, "%*[^,],%d", &intTestType);

	m_file->ReadString(str);   //6              
	sscanf(str, "%*[^,],%d", &intMixLight);

	m_file->ReadString(str);   //6.1              
	sscanf(str, "%*[^,],%d", &intVfAverage);
	
	m_file->ReadString(str);   //7
	sscanf(str, "%*[^,],%d", &selectchiptype);

	m_file->ReadString(str);   //8
	sscanf(str, "%*[^,],%d", &intPackageway);

	m_file->ReadString(str);   //9
	sscanf(str, "%*[^,],%d", &intChip);

	m_file->ReadString(str);   //10
	sscanf(str, "%*[^,],%d", &intCommonfoot);

	m_file->ReadString(str);   //11
	sscanf(str, "%*[^,],%d", &intPolarity);

	m_file->ReadString(str);   //12
	sscanf(str, "%*[^,],%d", &intSetway);

	m_file->ReadString(str);   //13
	sscanf(str, "%*[^,],%d", &intIVTestWay);

	m_file->ReadString(str);   //14
	sscanf(str, "%*[^,],%d", &intWLType);

	m_file->ReadString(str);   //15
	sscanf(str, "%*[^,],%d", &intWLStepSetWay);

	m_file->ReadString(str);   //16
	sscanf(str, "%*[^,],%d", &intWLStep);

	m_file->ReadString(str);   //17
	sscanf(str, "%*[^,],%d", &intSampleAverage);

	m_file->ReadString(str);   //18
	sscanf(str, "%*[^,],%d", &intBoxcar);
	
	m_file->ReadString(str);   //19
	sscanf(str, "%*[^,],%d", &intFailBin);

	m_file->ReadString(str);   //20
	sscanf(str, "%*[^,],%d", &intMiddlePin);
	
	m_file->ReadString(str);   //21
	sscanf(str, "%*[^,],%d", &intMiddleWave1);
	
	m_file->ReadString(str);   //22
	sscanf(str, "%*[^,],%d", &intMiddleWave2);

	m_file->ReadString(str);
	sscanf(str, "%*[^,],%d,%d,%d,%d", &DeadLed, &DeadLedBin[0], &DeadLedBin[1], &DeadLedBin[2]);

	///////////////////////wafer
	for(int chip=0; chip<3; chip++)
	{
		m_file->ReadString(str); 
		m_file->ReadString(str);   
		sscanf(str, "%*[^,],%d,%s%s%d", &c[chip], usespec,
			                            tXYZ, &polfalsenum[chip]);
		sscanf(usespec, "%[^,]", usespec);
		sscanf(tXYZ, "%[^,]", tXYZ);
		if(0 == strcmp(usespec, "true"))
		{
			usespectrum[chip] = true;
		}
		else
		{
			usespectrum[chip] = false;
		}
		if(0 == strcmp(tXYZ, "true"))
		{
			testXYZ[chip] = true;
		}
		else
		{
			testXYZ[chip] = false;
		}
		m_file->ReadString(str); 
	
		for(i=0; i<c[chip]; i++)
		{
			m_file->ReadString(str);
			sscanf(str, "%s"
				"%*[^A-Za-z]%[^,],""%d,"
				"%*[^0-9.]%[0-9.]""%*[^0-9.]%[0-9.]"
				"%*[^0-9.]%[0-9.]""%*[^0-9.]%[0-9.],"
				"%d,%s"
				"%*[^0-9.]%[0-9.]""%*[^0-9.-]%[0-9.-],"
				"%s"
				"%*[^0-9.]%[0-9.]""%*[^0-9.-]%[0-9.-]"
				"%*[^0-9.]%[0-9.]""%*[^0-9.-]%[0-9.-]",
    			str_num,
				CHIP[chip][i].TestItem, &CHIP[chip][i].Delay,
				Vcom, Icom,
				min, max,
				&CHIP[chip][i].Fail, contest,
				stavalue1, stavalue2,
				calway,
				calparam1, calparam2,
				calparam3, calparam4);
		
			CHIP[chip][i].VCom = atof(Vcom);				
			CHIP[chip][i].ICom = atof(Icom);					
			CHIP[chip][i].Lower = atof(min);						
			CHIP[chip][i].Upper = atof(max);

			sscanf(contest, "%[^,]", str);
			if(0 == strcmp(str, "True"))
			{
				CHIP[chip][i].Continue = 1;
			}
			else
			{
				CHIP[chip][i].Continue = 0;
			}

			sscanf(calway, "%[^,]", str);
			if(0 == strcmp(str, "offset"))
			{
				CHIP[chip][i].Calway = 0;
			}
			else if(0 == strcmp(str, "multiple"))
			{
				CHIP[chip][i].Calway = 1;
			}
			else
			{
				CHIP[chip][i].Calway = 2;
			}

			sscanf(CHIP[chip][i].TestItem, "%[^(]", str_item);
			if(0 == strcmp(str_item, "XYZ"))
			{
				CHIP[chip][i].stavalue1 = atof(stavalue1);
				CHIP[chip][i].stavalue2 = atof(stavalue2);

				CHIP[chip][i].CalParam1X = atof(calparam1);
				CHIP[chip][i].CalParam2X = atof(calparam2);
				CHIP[chip][i].CalParam1Y = atof(calparam3);
				CHIP[chip][i].CalParam2Y = atof(calparam4);

				m_file->ReadString(str);
				sscanf(str, 
					"%*[^0]%[0-9.]""%*[^0]%[0-9.]""%*[^0]%[0-9.]""%*[^0]%[0-9.]"
					"%*[^0]%[0-9.]""%*[^0]%[0-9.]""%*[^0]%[0-9.]""%*[^0]%[0-9.]",
					str_pointX[0], str_pointY[0], str_pointX[1], str_pointY[1],
					str_pointX[2], str_pointY[2], str_pointX[3], str_pointY[3]);
				for(j=0; j<4; j++)
				{
					point[chip][j].x = atof(str_pointX[j]);
					point[chip][j].y = atof(str_pointY[j]);
				}	
			}
			else
			{
				CHIP[chip][i].stavalue1 = atof(stavalue1);
				CHIP[chip][i].CalParam1 = atof(calparam1);
				CHIP[chip][i].CalParam2 = atof(calparam2);
			}
		}

		m_file->ReadString(str);
		sscanf(str, "%*[^,],%*[^0-9.]%[0-9.]", Vcom);
		PolParam[chip].Voltage = atof(Vcom);
	
		m_file->ReadString(str);
		sscanf(str, "%*[^,],%*[^0-9.]%[0-9.]", Icom);
		PolParam[chip].Current = atof(Icom);

		m_file->ReadString(str);
		sscanf(str, "%*[^,],%d", &PolParam[chip].Delay);

		int steps;
		m_file->ReadString(str);
		sscanf(str, "%*[^,],%d", &steps);
		if(1 == steps)
		{
			intWLSteps[chip] = 0;
		}
		else
		{
			intWLSteps[chip] = 1;
		}

		strcpy(str_read[0], "");
		m_file->ReadString(str);
		sscanf(str, "%*[^,],%s", str_read[0]);
		if(0 == strcmp(str_read[0], "低亮LED"))
		{
			intOpticGain[chip] = 0;
		}
		else if(0 == strcmp(str_read[0], "普亮LED"))
		{
			intOpticGain[chip] = 1;
		}
		else if(0 == strcmp(str_read[0], "高亮LED"))
		{
			intOpticGain[chip] = 2;
		}
		else if(0 == strcmp(str_read[0], "超高亮LED"))
		{
			intOpticGain[chip] = 3;
		}

		m_file->ReadString(str);
		sscanf(str, "%*[^,],%*[^0-9.]%[0-9.]", str_time);
		intIntegrationTime[chip] = atof(str_time);
		if(intIntegrationTime[chip] < 1)
		{
			intIntegrationTime[chip] = 1;
		}

		m_file->ReadString(str);
		sscanf(str, "%*[^,],%*[^0-9.]%[0-9.]", Vcom);
		KeepLight[chip].Voltage = atof(Vcom);
	
		m_file->ReadString(str);
		sscanf(str, "%*[^,],%*[^0-9.]%[0-9.]", Icom);
		KeepLight[chip].Current = atof(Icom);

		m_file->ReadString(str);
		sscanf(str, "%*[^,],%d", &KeepLight[chip].Delay);
	}

    /////////////////////////classification
	m_file->ReadString(str);
	m_file->ReadString(str);     //Classification
	sscanf(str, "%s%d,%d,%d", str_read[0], &columns[0], &columns[1], &columns[2]);
	cols = columns[0] + columns[1] + columns[2];
	for(i=0; i<cols; i++)
	{
		strcpy(str_read[i], "");
	}
	m_file->ReadString(str);
	sscanf(str, "%[^,]""%s"
		        "%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]"
				"%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]"
				"%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]"
				"%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]"
				"%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]"
				"%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]"
				"%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]"
				"%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]"
				"%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]"
				"%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]"
				"%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]"
				"%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]",
				str_num, name,
				str_read[0], str_read[1], str_read[2], str_read[3], str_read[4], 
				str_read[5], str_read[6], str_read[7], str_read[8], str_read[9],
				str_read[10], str_read[11], str_read[12], str_read[13], str_read[14],
				str_read[15], str_read[16], str_read[17], str_read[18], str_read[19],
				str_read[20], str_read[21], str_read[22], str_read[23], str_read[24],
				str_read[25], str_read[26], str_read[27], str_read[28], str_read[29],
				str_read[30], str_read[31], str_read[32], str_read[33], str_read[34],
				str_read[35], str_read[36], str_read[37], str_read[38], str_read[39],
				str_read[40], str_read[41], str_read[42], str_read[43], str_read[44],
				str_read[45], str_read[46], str_read[47], str_read[48], str_read[49],
				str_read[50], str_read[51], str_read[52], str_read[53], str_read[54],
				str_read[55], str_read[56], str_read[57], str_read[58], str_read[59]
				);

	for(i=0; i<cols; i++)
	{
		binArray.strBinArray[0][i] = str_read[i];
	}

	m_file->ReadString(str);

	for(i=1; i <= systemset.intMachineType; i++)
	{	
		if(m_file->ReadString(str))
		{
			for(j=0; j<cols; j++)
			{
				strcpy(str_read[j], "");
			}

			sscanf(str, "%s""%s"
		       "%s""%s""%s""%s""%s"
			   "%s""%s""%s""%s""%s"
		       "%s""%s""%s""%s""%s"
			   "%s""%s""%s""%s""%s"
			   "%s""%s""%s""%s""%s"
			   "%s""%s""%s""%s""%s"
			   "%s""%s""%s""%s""%s"
			   "%s""%s""%s""%s""%s"
			   "%s""%s""%s""%s""%s"
			   "%s""%s""%s""%s""%s"
			   "%s""%s""%s""%s""%s"
			   "%s""%s""%s""%s""%s",	
			   str_num, name,
			   str_read[0], str_read[1], str_read[2], str_read[3], str_read[4],
			   str_read[5], str_read[6], str_read[7], str_read[8], str_read[9],
			   str_read[10], str_read[11], str_read[12], str_read[13], str_read[14],
			   str_read[15], str_read[16], str_read[17], str_read[18], str_read[19],
			   str_read[20], str_read[21], str_read[22], str_read[23], str_read[24],
			   str_read[25], str_read[26], str_read[27], str_read[28], str_read[29],
			   str_read[30], str_read[31], str_read[32], str_read[33], str_read[34],
			   str_read[35], str_read[36], str_read[37], str_read[38], str_read[39],
			   str_read[40], str_read[41], str_read[42], str_read[43], str_read[44],
			   str_read[45], str_read[46], str_read[47], str_read[48], str_read[49],
			   str_read[50], str_read[51], str_read[52], str_read[53], str_read[54],
			   str_read[55], str_read[56], str_read[57], str_read[58], str_read[59]
			   );

			strcpy(read , "");
			sscanf(name, "%[^,]", read);
			binArray.binName[i-1] = "NULL";
			binArray.binName[i-1] = read;
			for(j=0; j<cols; j++)
			{
				strcpy(read , "");
				sscanf(str_read[j], "%[0-9.]", read); 
				binArray.strBinArray[i][j] = "NULL";
				binArray.strBinArray[i][j] = read;
			}
		}
		else
		{
			i = systemset.intMachineType + 1;
		}
	}

	return true;
}

bool WriteStaFile(CStdioFile *m_file)
{
	CString str_write, str_item;
	char calway[10], contest[10];
	int cols = 0;
	int i = 0;

	CTime t = CTime::GetCurrentTime();
	str_write.Format("%d-%d-%d %d:%d\n", t.GetYear(), t.GetMonth(),
		                                 t.GetDay(), t.GetHour(), t.GetMinute());
	m_file->WriteString("HC00   " + str_write);

	m_file->WriteString("General:\n");

	str_write.Format("DiameterOptic:,    %f\n", DiameterOptic);
	m_file->WriteString(str_write);

	str_write.Format("TestWay:,     %d\n", intTestWay);
	m_file->WriteString(str_write);

	str_write.Format("TestType:,    %d\n", intTestType);
	m_file->WriteString(str_write);

	str_write.Format("MixLight:,    %d\n", intMixLight);
	m_file->WriteString(str_write);

	str_write.Format("VfAverage:,   %d\n", intVfAverage);
	m_file->WriteString(str_write);

	str_write.Format("intChipType:,     %d\n", selectchiptype);
	m_file->WriteString(str_write);

	str_write.Format("intPackageway:,     %d\n", intPackageway);
	m_file->WriteString(str_write);

	str_write.Format("intChip:,     %d\n", intChip);
	m_file->WriteString(str_write);

	str_write.Format("intCommonfoot:,     %d\n", intCommonfoot);
	m_file->WriteString(str_write);

	str_write.Format("intPolarity:,     %d\n", intPolarity);
	m_file->WriteString(str_write);

	str_write.Format("intSetway:,     %d\n", intSetway);
	m_file->WriteString(str_write);

	str_write.Format("intIVTestWay:,     %d\n", intIVTestWay);
	m_file->WriteString(str_write);

	str_write.Format("intWLType:,    %d\n", intWLType);
	m_file->WriteString(str_write);

	str_write.Format("intWLStepSetWay:,  %d\n", intWLStepSetWay);
	m_file->WriteString(str_write);

	str_write.Format("intWLStep:,    %d\n", intWLStep);
	m_file->WriteString(str_write);

	str_write.Format("intSampleAverage:,     %d\n", intSampleAverage);
	m_file->WriteString(str_write);

	str_write.Format("intBoxcar:,    %d\n", intBoxcar);
	m_file->WriteString(str_write);

	str_write.Format("intFailBin:,   %d\n", intFailBin);
	m_file->WriteString(str_write);

	str_write.Format("intMiddlePin:,     %d\n", intMiddlePin);
	m_file->WriteString(str_write);

	str_write.Format("intMiddleWave1:,   %d\n", intMiddleWave1);
	m_file->WriteString(str_write);

	str_write.Format("intMiddleWave2:,   %d\n", intMiddleWave2);
	m_file->WriteString(str_write);

	str_write.Format("DeadLed:, %d,%d,%d,%d\n", DeadLed, DeadLedBin[0], DeadLedBin[1], DeadLedBin[2]);
	m_file->WriteString(str_write);
	m_file->WriteString("\n");
///////////////////////wafer
	for(int chip=0; chip<3; chip++)
	{
		if(usespectrum[chip])
		{
			if(testXYZ[chip])
			{
				str_write.Format(" Wafer %d:, %d, true, true, %d\n",
					               (chip+1), c[chip], polfalsenum[chip]);
			}
			else
			{
				str_write.Format(" Wafer %d:, %d, true, false, %d\n",
					               (chip+1), c[chip], polfalsenum[chip]);
			}
		}
		else
		{
			if(testXYZ[chip])
			{
				str_write.Format(" Wafer %d:, %d, false, true, %d\n", 
					               (chip+1), c[chip], polfalsenum[chip]);
			}
			else
			{
				str_write.Format(" Wafer %d:, %d, false, false, %d\n", 
					               (chip+1), c[chip], polfalsenum[chip]);
			}
		}
	
		m_file->WriteString(str_write);

		m_file->WriteString("Num   TestType   Delay(ms)   VComp(V)   IComp(mA)       Min          Max        FailBin   ContTest    StaValue1     StaValue2    CalibrationWay    CalibrationParameter*/x*   CalibrationParameter+/x+    CalibrationParameter y*   CalibrationParameter y+\n");
	
		for(i = 0; i<c[chip]; i++)
		{
			if(0 == CHIP[chip][i].Continue)
			{
				strcpy(contest, "False");
			}
			else
			{
				strcpy(contest, "True");
			}

			if(0 == CHIP[chip][i].Calway)
			{
				strcpy(calway, "offset");
			}
			else if(1 == CHIP[chip][i].Calway)
			{
				strcpy(calway, "multiple");
			}
			else
			{
				strcpy(calway, "both");
			}

			sscanf(CHIP[chip][i].TestItem, "%[^(]", str_item);
			if(0 == strcmp(str_item, "XYZ"))
			{
				str_write.Format(" %d ,    %s,       %d,         %f,  %f,   %f,    %f,        %d,      %s,       %f,         %f,         %s,             %f,             %f,             %f,             %f",
					i+1,
					CHIP[chip][i].TestItem, CHIP[chip][i].Delay,
					CHIP[chip][i].VCom, CHIP[chip][i].ICom,
					CHIP[chip][i].Lower, CHIP[chip][i].Upper,
					CHIP[chip][i].Fail, contest,
					CHIP[chip][i].stavalue1, CHIP[chip][i].stavalue2,
					calway,
					CHIP[chip][i].CalParam1X, CHIP[chip][i].CalParam2X,
					CHIP[chip][i].CalParam1Y, CHIP[chip][i].CalParam2Y);
				m_file->WriteString(str_write + "\n");

				str_write.Format("    XYZ: point1_X %f,  point1_Y %f,  point2_X %f,  point2_Y %f,  point3_X %f,  point3_Y %f,  point4_X %f,  point4_Y %f",
					point[chip][0].x, point[chip][0].y, point[chip][1].x, point[chip][1].y,
					point[chip][2].x, point[chip][2].y, point[chip][3].x, point[chip][3].y);
				m_file->WriteString(str_write + "\n");
			}
			else
			{
				str_write.Format(" %d ,    %s,       %d,         %f,  %f,   %f,    %f,        %d,      %s,         %f,         %f,         %s,             %f,             %f",
					i+1, CHIP[chip][i].TestItem, CHIP[chip][i].Delay,
					CHIP[chip][i].VCom, CHIP[chip][i].ICom,
					CHIP[chip][i].Lower, CHIP[chip][i].Upper,
					CHIP[chip][i].Fail, contest,
					CHIP[chip][i].stavalue1, CHIP[chip][i].stavalue2,
					calway,
					CHIP[chip][i].CalParam1, CHIP[chip][i].CalParam2);
				m_file->WriteString(str_write + "\n");
			}
		}
	
		str_write.Format("POLVoltage:, %f\n", PolParam[chip].Voltage);
		m_file->WriteString(str_write);

		str_write.Format("POLCurrent:, %f\n", PolParam[chip].Current);
		m_file->WriteString(str_write);

		str_write.Format("POLDelay:, %d\n", PolParam[chip].Delay);
		m_file->WriteString(str_write);

		if(0 == intWLSteps[chip])
		{
			str_write.Format("intWLStep:, 1nm\n");
		}
		else
		{
			str_write.Format("intWLStep:, 5nm\n");
		}
		
		m_file->WriteString(str_write);

		if(3 == intOpticGain[chip])
		{
			str_write.Format("Optic:, 超高亮LED\n");
		}
		else if(2 == intOpticGain[chip])
		{
			str_write.Format("Optic:, 高亮LED\n");
		}
		else if(1 == intOpticGain[chip])
		{
			str_write.Format("Optic:, 普亮LED\n");
		}
		else if(0 == intOpticGain[chip])
		{
			str_write.Format("Optic:, 低亮LED\n");
		}
		m_file->WriteString(str_write);

		if(intIntegrationTime[chip] < 1)
		{
			intIntegrationTime[chip] = 1;
		}

		str_write.Format("IntegrationTime:, %0.1f\n", intIntegrationTime[chip]);
		m_file->WriteString(str_write);

		str_write.Format("KeepLightVoltage:, %f\n", KeepLight[chip].Voltage);
		m_file->WriteString(str_write);

		str_write.Format("KeepLightCurrent:, %f\n", KeepLight[chip].Current);
		m_file->WriteString(str_write);

		str_write.Format("KeepLightDelay:, %d\n", KeepLight[chip].Delay);
		m_file->WriteString(str_write);

		m_file->WriteString("\n");
	}

	/////////////////////////////////classification
	cols = columns[0] + columns[1] + columns[2];
	str_write.Format("Classification:,    %d,    %d,    %d\n", 
		                         columns[0], columns[1], columns[2]);
	m_file->WriteString(str_write);
	
	str_write = "BIN,    NAME,      ";
	for(i=0; i<cols; i++)
	{
		str_write += binArray.strBinArray[0][i] + ",    ";
	}
	str_write += "\n";
	m_file->WriteString(str_write);

	str_write = "BIN,    NAME,    ";	
	for(i=0; i<cols; i+=2)
	{
		sscanf(binArray.strBinArray[0][i], "%*[^-]-%[^(]", str_item);
		if(binArray.strBinArray[0][i] != "")
		{
			if(0 == strcmp(str_item, "XYZ")) 
			{
				str_write += "X0,    ";
				str_write += "Y0,    ";
				str_write += "X1,    ";
				str_write += "Y1,    ";
				str_write += "X2,    ";
				str_write += "Y2,    ";
				str_write += "X3,    ";
				str_write += "Y3,    ";
				i += 6;
			}
			else
			{
				str_write += "MIN,    ";
				str_write += "MAX,    ";
			}
		}
		else
		{
			i = LEVELCOLUMNS;
		}
	}
	str_write += "\n";
	m_file->WriteString(str_write);

	for(i=0; i<systemset.intMachineType; i++)
	{
		str_write.Format("%d,   %s,   ", i, binArray.binName[i]);
		for(int j=0; j<cols; j++)
		{
			str_write += binArray.strBinArray[i+1][j] + ",    ";
		}
		str_write += "\n";
		m_file->WriteString(str_write);
	}

	return true;
}

bool ReadLevelCSVFile(CStdioFile *m_file)
{
	CString str, str_num, str2, str3, str_name;
	int length[2] = {0, 0}, start[2] = {0, 0};
	int i = 0, j = 0;
	int cols = 0;
	char read[10];
	char str_read[LEVELCOLUMNS][20] = {"", "", "", "", "", "", "", "", "", "",
                                       "", "", "", "", "", "", "", "", "", "",
	                                   "", "", "", "", "", "", "", "", "", "",
	                                   "", "", "", "", "", "", "", "", "", "",
                                       "", "", "", "", "", "", "", "", "", "",
	                                   "", "", "", "", "", "", "", "", "", ""};
	m_file->ReadString(str);   
	sscanf(str, "%s", str);
	if(str != "HC01")
	{
		return false;
	}

	m_file->ReadString(str);     //Classification
	sscanf(str, "%[^,],%d,%d,%d", str_read[0], &csvcolumns[0], &csvcolumns[1], &csvcolumns[2]);
	cols = csvcolumns[0] + csvcolumns[1] + csvcolumns[2];
	for(i=0; i<cols; i++)
	{
		strcpy(str_read[i], "");
	}
	m_file->ReadString(str);
	sscanf(str, "%[^,]""%s"
		        "%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]"
				"%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]"
				"%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]"
				"%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]"
				"%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]"
				"%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]"
				"%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]"
				"%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]"
				"%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]"
				"%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]"
				"%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]"
				"%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]""%*[^C]%[^,]",
				str_num, str_name,
				str_read[0], str_read[1], str_read[2], str_read[3], str_read[4],
				str_read[5], str_read[6], str_read[7], str_read[8], str_read[9],
				str_read[10], str_read[11], str_read[12], str_read[13], str_read[14],
				str_read[15], str_read[16], str_read[17], str_read[18], str_read[19],
				str_read[20], str_read[21], str_read[22], str_read[23], str_read[24],
				str_read[25], str_read[26], str_read[27], str_read[28], str_read[29],
				str_read[30], str_read[31], str_read[32], str_read[33], str_read[34],
				str_read[35], str_read[36], str_read[37], str_read[38], str_read[39],
				str_read[40], str_read[41], str_read[42], str_read[43], str_read[44],
				str_read[45], str_read[46], str_read[47], str_read[48], str_read[49],
				str_read[50], str_read[51], str_read[52], str_read[53], str_read[54],
				str_read[55], str_read[56], str_read[57], str_read[58], str_read[59]
				);

	for(i=0; i<cols; i++)
	{
		level_binArray.strBinArray[0][i] = str_read[i];
	}
	
	m_file->ReadString(str); 
	for(i=1; i <= systemset.intMachineType; i++)
	{	
		if(m_file->ReadString(str))
		{
			for(j=0; j<cols; j++)
			{
				strcpy(str_read[j], "");
			}
			
			start[0] = str.Find(",");
			
			if(start[0] > 0)
			{
				length[0] = strlen(str);
				str2 = str.Mid(start[0]+1, length[0]);
				
				start[1] = str2.Find(",");
				length[1] = strlen(str2);
				
				str_name = "";
				str_name = str2.Left(start[1]+1);
				if(str_name != ",")
				{
					str_name = str2.Left(start[1]);
					level_binArray.binName[i-1] = str_name;
				}
				else
				{
					level_binArray.binName[i-1] = "";
				}
				
				str3 = str2.Mid(start[1]+1, length[1]);		
				
				sscanf(str3, 
					"%[^,],""%[^,],""%[^,],""%[^,],""%[^,],"
					"%[^,],""%[^,],""%[^,],""%[^,],""%[^,],"
					"%[^,],""%[^,],""%[^,],""%[^,],""%[^,],"
					"%[^,],""%[^,],""%[^,],""%[^,],""%[^,],"
					"%[^,],""%[^,],""%[^,],""%[^,],""%[^,],"
					"%[^,],""%[^,],""%[^,],""%[^,],""%[^,],"
					"%[^,],""%[^,],""%[^,],""%[^,],""%[^,],"
					"%[^,],""%[^,],""%[^,],""%[^,],""%[^,],"
					"%[^,],""%[^,],""%[^,],""%[^,],""%[^,],"
					"%[^,],""%[^,],""%[^,],""%[^,],""%[^,],"
					"%[^,],""%[^,],""%[^,],""%[^,],""%[^,],"
					"%[^,],""%[^,],""%[^,],""%[^,],""%[^,],",	
					str_read[0], str_read[1], str_read[2], str_read[3], str_read[4],
					str_read[5], str_read[6], str_read[7], str_read[8], str_read[9],
					str_read[10], str_read[11], str_read[12], str_read[13], str_read[14],
					str_read[15], str_read[16], str_read[17], str_read[18], str_read[19],
					str_read[20], str_read[21], str_read[22], str_read[23], str_read[24],
					str_read[25], str_read[26], str_read[27], str_read[28], str_read[29],
					str_read[30], str_read[31], str_read[32], str_read[33], str_read[34],
					str_read[35], str_read[36], str_read[37], str_read[38], str_read[39],
					str_read[40], str_read[41], str_read[42], str_read[43], str_read[44],
					str_read[45], str_read[46], str_read[47], str_read[48], str_read[49],
					str_read[50], str_read[51], str_read[52], str_read[53], str_read[54],
					str_read[55], str_read[56], str_read[57], str_read[58], str_read[59]
					);
				
				for(j=0; j<cols; j++)
				{	
					strcpy(read , "");
					if(str3.Left(1) != ",")
					{
						sscanf(str_read[j], "%s", read); 
					}
					level_binArray.strBinArray[i][j] = "NULL";
					level_binArray.strBinArray[i][j] = read;
				}
			}
			else
			{
				level_binArray.binName[i-1] = "";

				for(j=0; j<cols; j++)
				{	
					level_binArray.strBinArray[i][j] = "NULL";
					level_binArray.strBinArray[i][j] = "";
				}
			}
			
			str = "";
		}
		else
		{
			i = systemset.intMachineType + 1;
		}
	}
	return true;
}
	
bool WriteLevelCSVFile(CStdioFile *m_file)
{
	CString str_write, str_item;
	int i = 0;
	int cols = 0;

	CTime t = CTime::GetCurrentTime();
	str_write.Format("%d-%d-%d %d:%d\n", t.GetYear(), t.GetMonth(),
		                                 t.GetDay(), t.GetHour(), t.GetMinute());
	m_file->WriteString("HC01   " + str_write);

	cols = csvcolumns[0] + csvcolumns[1] + csvcolumns[2];
	str_write.Format("ColumnsNumber:,    %d,    %d,    %d\n", csvcolumns[0], csvcolumns[1], csvcolumns[2]);
	m_file->WriteString(str_write);

	str_write = "BIN,    NAME,    ";
	for(i=0; i<cols; i++)
	{
		str_write += level_binArray.strBinArray[0][i] + ",    ";
	}
	str_write += "\n";
	m_file->WriteString(str_write);

	str_write = "BIN,    NAME,    ";
	for(i=0; i<cols; i+=2)
	{
		if(level_binArray.strBinArray[0][i] != "")
		{
			sscanf(level_binArray.strBinArray[0][i], "%*[^-]-%[^(]", str_item);
			if(0 == strcmp(str_item, "XYZ")) 
			{
				str_write += "X0,    ";
				str_write += "Y0,    ";
				str_write += "X1,    ";
				str_write += "Y1,    ";
				str_write += "X2,    ";
				str_write += "Y2,    ";
				str_write += "X3,    ";
				str_write += "Y3,    ";
				i += 6;
			}
			else
			{
				str_write += "MIN,    ";
				str_write += "MAX,    ";
			}
		}
		else
		{
			i = LEVELCOLUMNS;
		}
	}
	str_write += "\n";
	m_file->WriteString(str_write);

	for(i=0; i<systemset.intMachineType; i++)
	{
		str_write.Format("%d,%s,", i, level_binArray.binName[i]);
		for(int j=0; j<cols; j++)
		{
			str_write += level_binArray.strBinArray[i+1][j] + ",";
		}
		str_write += "\n";
		m_file->WriteString(str_write);
	}
	return true;
}

bool ReadXYLevelCSVFile(CStdioFile *m_file)
{
	CString first[3] = {"NULL", "NULL", "NULL"};
	CString str, string;
	char str_point[3][4][2][10];
	int i = 0, j = 0;
	XYLEVELItem item;
	int pointnum[3] = {0, 0, 0};

	m_file->ReadString(str);   
	sscanf(str, "%s", str);
	if(str != "HC02")
	{
		return false;
	}

	m_file->ReadString(str);
	m_file->ReadString(str);
	m_file->ReadString(str);

	m_file->ReadString(str);
	for(i=0; i<3; i++)
	{
		for(j=0; j<4; j++)
		{
			strcpy(str_point[i][j][0] ,"");
			strcpy(str_point[i][j][1] ,"");
		}
	}
	sscanf(str, "%[^,],""%[^,],""%[^,],""%[^,],""%[^,],""%[^,],""%[^,],""%[^,],""%[^,],,"
		                "%[^,],""%[^,],""%[^,],""%[^,],""%[^,],""%[^,],""%[^,],""%[^,],,"
					    "%[^,],""%[^,],""%[^,],""%[^,],""%[^,],""%[^,],""%[^,],""%[^,]",
			string, str_point[0][0][0], str_point[0][0][1], str_point[0][1][0], str_point[0][1][1],
			        str_point[0][2][0], str_point[0][2][1], str_point[0][3][0], str_point[0][3][1],
				    str_point[1][0][0], str_point[1][0][1], str_point[1][1][0], str_point[1][1][1],
					str_point[1][2][0], str_point[1][2][1], str_point[1][3][0], str_point[1][3][1],
					str_point[2][0][0], str_point[2][0][1], str_point[2][1][0], str_point[2][1][1],
					str_point[2][2][0], str_point[2][2][1], str_point[2][3][0], str_point[2][3][1]);

	for(i = 0; i<3; i++)
	{
		for(j=0; j<4; j++)
		{	
			str = "";
			sscanf(str_point[i][j][0], "%[^,]", str);
			TotalRangeItem[i].x[j] = atof(str);

			str = "";
			sscanf(str_point[i][j][1], "%[^,]", str);
			TotalRangeItem[i].y[j] = atof(str);	
		}
		levelItem[i].RemoveAll();
	}


	m_file->ReadString(str);
	while(m_file->ReadString(str))
	{
		for(i=0; i<3; i++)
		{
			for(j=0; j<4; j++)
			{
				strcpy(str_point[i][j][0] ,"");
				strcpy(str_point[i][j][1] ,"");
			}
		}
		sscanf(str, "%[^,],""%[^,],""%[^,],""%[^,],""%[^,],""%[^,],""%[^,],""%[^,],""%[^,],,"
		                    "%[^,],""%[^,],""%[^,],""%[^,],""%[^,],""%[^,],""%[^,],""%[^,],,"
					        "%[^,],""%[^,],""%[^,],""%[^,],""%[^,],""%[^,],""%[^,],""%[^,],",
			string, str_point[0][0][0], str_point[0][0][1], str_point[0][1][0], str_point[0][1][1],
			        str_point[0][2][0], str_point[0][2][1], str_point[0][3][0], str_point[0][3][1],
				    str_point[1][0][0], str_point[1][0][1], str_point[1][1][0], str_point[1][1][1],
					str_point[1][2][0], str_point[1][2][1], str_point[1][3][0], str_point[1][3][1],
					str_point[2][0][0], str_point[2][0][1], str_point[2][1][0], str_point[2][1][1],
					str_point[2][2][0], str_point[2][2][1], str_point[2][3][0], str_point[2][3][1]);

		for(i = 0; i<3; i++)
		{
			first[i] = str_point[i][0][0];
			if(first[i] != "")
			{
				for(j=0; j<4; j++)
				{	
					item.x[j] = atof(str_point[i][j][0]);
					item.y[j] = atof(str_point[i][j][1]);	
				}
				item.num = pointnum[i]++;
				levelItem[i].AddTail(item);
			}	
		}
	}
	
	return true;
}

bool WriteXYLevelCSVFile(CStdioFile *m_file)
{
	CString str_write = ",";
	CString str[3] = {"C1-XYZ,", "C2-XYZ,", "C3-XYZ,"};
	CString str_point;
	int i = 0, j = 0;
	int num = 0;
	POSITION pos[3];

	CTime t = CTime::GetCurrentTime();
	str_write.Format("%d-%d-%d %d:%d\n", t.GetYear(), t.GetMonth(),
		                                 t.GetDay(), t.GetHour(), t.GetMinute());
	m_file->WriteString("HC02   " + str_write);


	m_file->WriteString("XY分级数据\n");

	str_write = ",";
	for(i=0; i<3; i++)
	{
		for(j=0; j<8; j++)
		{
			str_write += str[i];
		}	
		str_write += ",";
	}
	m_file->WriteString(str_write + "\n");


	str_write = ",";
	for(i=0; i<3; i++)
	{
		str_write += "X0, Y0, X1, Y1, X2, Y2, X3, Y3,,";
	}
	m_file->WriteString(str_write + "\n");


	str_write = "范围,";
	for(i=0; i<3; i++)
	{
		for(j=0; j<4; j++)
		{
			str_point.Format("%f,", TotalRangeItem[i].x[j]);
			str_write += str_point;
			str_point.Format("%f,", TotalRangeItem[i].y[j]);
			str_write += str_point;
		}
		str_write += ",";
	}
	m_file->WriteString(str_write + "\n");
	m_file->WriteString("\n");


	for(i=0; i<3; i++)
	{
		pos[i] = levelItem[i].GetHeadPosition();
	}
	while((pos[0] != NULL) || (pos[1] != NULL) || (pos[2] != NULL))
	{
		num++;
		str_write.Format("%d,", num);
		for(int chip = 0; chip<3; chip++)
		{
			if(pos[chip] != NULL)
			{
				for(i=0; i<4; i++)
				{
					str_point.Format("%f,", levelItem[chip].GetAt(pos[chip]).x[i]);
					str_write += str_point;
					str_point.Format("%f,", levelItem[chip].GetAt(pos[chip]).y[i]);
					str_write += str_point;
				}	
				levelItem[chip].GetNext(pos[chip]);
			}
			else
			{
				str_write += ",,,,,,,,";
			}
			str_write += ",";	
		}
		m_file->WriteString(str_write + "\n");
	}

	return true;
}

bool ReadXYLevelCSVFile2(CStdioFile *m_file)
{
	CString first = "NULL";
	CString str, string;
	char str_point[2][20];
	int i = 0;
	XYLEVELItem item;
	int pointnum = 0;
	int num = 0;
	int pointX = 0;

	m_file->ReadString(str);   
	sscanf(str, "%s", str);
	if(str != "HC022")
	{
		return false;
	}

	m_file->ReadString(str);
	m_file->ReadString(str);
	m_file->ReadString(str);

	for(i=0; i<4; i++)
	{
		strcpy(str_point[0] ,"");
		strcpy(str_point[1] ,"");
		m_file->ReadString(str);
		sscanf(str, "%[^,],""%[^,],""%[^,]", string, str_point[0], str_point[1]);

		str = "";
		sscanf(str_point[0], "%[^,]", str);
		TotalRangeItem[0].x[i] = atof(str);
		
		str = "";
		sscanf(str_point[1], "%[^,]", str);
		TotalRangeItem[0].y[i] = atof(str);	
	}
	m_file->ReadString(str);

	levelItem[0].RemoveAll();
	while(m_file->ReadString(str))
	{
		pointX = num%4;
		
		strcpy(str_point[0], "");
		strcpy(str_point[1], "");
		sscanf(str, "%[^,],""%[^,],""%[^,]", 
			string, str_point[0], str_point[1]);

		if((str_point[0] != "") && (str_point[1] != ""))
		{
			item.x[pointX] = atof(str_point[0]);
			item.y[pointX] = atof(str_point[1]);
			
			if(3 == num%4)
			{
				item.num = pointnum++;
				levelItem[0].AddTail(item);	
			}
			num++;
		}	
	}
	
	return true;
}

bool WriteXYLevelCSVFile2(CStdioFile *m_file)
{
	CString str_write = ",";
	CString str = "C1-XYZ,";
	CString str_point;
	int i = 0;
	int num = 0;
	POSITION pos;

	CTime t = CTime::GetCurrentTime();
	str_write.Format("%d-%d-%d %d:%d\n", t.GetYear(), t.GetMonth(),
		                                 t.GetDay(), t.GetHour(), t.GetMinute());
	m_file->WriteString("HC022   " + str_write);
	m_file->WriteString("XY分级数据(格式2)\n");
	m_file->WriteString(",XYZ,XYZ,\n");
	m_file->WriteString(",X, Y,,\n");

	for(i=0; i<4; i++)
	{
		str_write = "范围,";
		str_point.Format("%f,%f", TotalRangeItem[0].x[i], TotalRangeItem[0].y[i]);
		str_write += str_point;
		m_file->WriteString(str_write + "\n");
	}
	m_file->WriteString("\n");

	pos = levelItem[0].GetHeadPosition();
	while(pos != NULL)
	{
		num++;
		for(i=0; i<4; i++)
		{
			str_write.Format("%d,%f,%f,,\n", num, levelItem[0].GetAt(pos).x[i], levelItem[0].GetAt(pos).y[i]);
			m_file->WriteString(str_write);	
		}
		levelItem[0].GetNext(pos);
	}

	return true;
}

bool ReadShootDotCSVFile(CStdioFile *m_file)
{
	CString str;
	CString str_num, str_x, str_y;
	sngPOINT point;

	m_file->ReadString(str);   
	sscanf(str, "%s", str);
	if(str != "HC03")
	{
		return false;
	}

	m_file->ReadString(str);
	m_file->ReadString(str);
	
	while(m_file->ReadString(str))
	{
		sscanf(str, "%[^,],""%[^,],""%s",str_num, str_x, str_y);
		point.x = atof(str_x);
		point.y = atof(str_y);
		dot[0].AddTail(point);
	}

	return true;
}

bool WriteShootDotCSVFile(CStdioFile *m_file)
{
	int num = 0;
	CString str_write = ",";
	CString str_x, str_y, str_num;

	CTime t = CTime::GetCurrentTime();
	str_write.Format("%d-%d-%d %d:%d\n", t.GetYear(), t.GetMonth(),
		                                 t.GetDay(), t.GetHour(), t.GetMinute());
	m_file->WriteString("HC03   " + str_write);
	m_file->WriteString("XY打靶数据\n");
	m_file->WriteString("Num,X,Y\n");

	sngPOINT point;
	POSITION pos = dot[0].GetHeadPosition();
	while(pos != NULL)
	{
		num++;
		point = dot[0].GetNext(pos);
		str_num.Format("%d,", num);
		str_x.Format("%0.4f,", point.x);
		str_y.Format("%0.4f", point.y);
		str_write = str_num + str_x + str_y;
		m_file->WriteString(str_write + "\n");
	}

	return true;
}

bool ReadLogFile(CStdioFile *m_file)
{
	CString str;
	int i = 0;
	while(m_file->ReadString(str))
	{
	}
	return true;
}
	
bool WriteLogFile(CStdioFile *m_file)
{
	int i;
	CString str_write;
	CString str[3] = {"最小值", "最大值", "平均值"};

	CTime t = CTime::GetCurrentTime();
	str_write.Format("%d-%d-%d, %d:%d\n", t.GetYear(), t.GetMonth(), t.GetDay(), t.GetHour(), t.GetMinute());
	m_file->WriteString(str_write);

    /////////////////////////合格率
	m_file->WriteString("测试灯总数,   合格数,   不合格数,   合格率\n");
	str_write.Format("   %s,       %s,     %s,     %s",
		             passpercentpara[0], passpercentpara[1], passpercentpara[2], passpercentpara[3]);
	m_file->WriteString(str_write + "\n");
	m_file->WriteString("\n");

	///////////////////////////各项平均值
	int nCount = c[0] + c[1] + c[2];
	int a, b;
	int chipnum = 3;
	if(0 == intChip)
	{
		chipnum = 1;
	}
	else if(intChip < 4)
	{
		chipnum = 2;
	}
	m_file->WriteString("统计测试结果\n");
	m_file->WriteString("         ,");
	for(a=0; a<chipnum; a++)
	{
		for(b=0; b<c[a]; b++)
		{
			if(0 == strcmp(CHIP[a][b].TestItem, "XYZ"))
			{
				str_write.Format("C%d-XYZ-X,    ", (a+1));
				m_file->WriteString(str_write);
				str_write.Format("C%d-XYZ-Y,    ", (a+1));
				m_file->WriteString(str_write);
			}
			else
			{
				str_write.Format("C%d-%s,    ", (a+1), CHIP[a][b].TestItem);
				m_file->WriteString(str_write);
			}		
		}
	}
	m_file->WriteString("\n");
	
	
	for(int type=0; type<3; type++)
	{
		i=0;
		m_file->WriteString(str[type] + ",   ");

		for(a=0; a<3; a++)
		{
			for(b=0; b<c[a]; b++)
			{
				m_file->WriteString(StatisticData[type][i++] + ",        ");
			}
		}
		m_file->WriteString("\n");
	}
	m_file->WriteString("\n");

	/////////////////////////////BIN统计
	m_file->WriteString("BIN统计\n");
	m_file->WriteString("BIN,    NUM,   PERCENTAGE\n");
	for(i=0; i<systemset.intMachineType; i++)
	{
		str_write.Format(" %d,    %s,       %s", i, BinData[i][0], BinData[i][1]);
		m_file->WriteString(str_write + "%\n");
	}
	m_file->WriteString("\n");

	///////////////////////////显示测试数据
	m_file->WriteString("测试数据如下\n");
	str_write = "Num,    ";
	m_file->WriteString(str_write);
	for(a=0; a<chipnum; a++)
	{
		for(b=0; b<c[a]; b++)
		{
			if(0 == strcmp(CHIP[a][b].TestItem, "XYZ"))
			{
				str_write.Format("C%d-XYZ-X,    ", (a+1));
				m_file->WriteString(str_write);
				str_write.Format("C%d-XYZ-Y,    ", (a+1));
				m_file->WriteString(str_write);
			}
			else
			{
				str_write.Format("C%d-%s,    ", (a+1), CHIP[a][b].TestItem);
				m_file->WriteString(str_write);
			}		
		}
	}
	str_write = "BIN,     NAME";
	m_file->WriteString(str_write);
	m_file->WriteString("\n");

	int num = 0;
	num = dataList.GetSize();
	for(i = 0; i<num; i++)
	{
		str_write = dataList.GetAt(i);
		m_file->WriteString(str_write);
		m_file->WriteString("\n");
	}

	return true;
}


bool ReadLMPFile(CStdioFile *m_file)
{
	CString str;
	int i = 0;
	char str_standardWL[20], str_power[20];
	while(m_file->ReadString(str))
	{
		sscanf(str, "%s%s", str_standardWL, str_power);
		standardWL[i] = atof(str_standardWL);
		power[i] = atof(str_power); 
		i++;
	}
	powernum = i;
	return true;
}
	

bool ReadSpecFile(CStdioFile *m_file, double *spec)
{
	CString str;
	int i = 0;
	char str_spec[20];
	while(m_file->ReadString(str))
	{
		sscanf(str, "%s", str_spec);
		spec[i] = atof(str_spec); 
		i++;
	}
	return true;
}
	
bool WriteSpecFile(CStdioFile *m_file, double *spec)
{
	CString str_write;
	for(int i=0; i<PIXELNUM; i++)
	{
		str_write.Format("%f\n", spec[i]);
		m_file->WriteString(str_write);
	}	
	return true;
}

bool WriteBinCodeCSVFile(CStdioFile *m_file)
{
	CString str_write;	
	
	str_write = "BIN,    CIECode    \n";
	m_file->WriteString(str_write);
	
	for(int i=1; i<systemset.intMachineType; i++)
	{
		str_write.Format("%d,    %s    \n", i, MapBinCode[i]);
		m_file->WriteString(str_write);
	}
	
	return true;
}

//////////////////打印设置文件处理
PrintItem printItem[10];
int CAT[3] = {0, 0, 0};

bool ReadPrintSetFile(CStdioFile *m_file)
{
	CString str;
	char str_name[20], str_data[200];// str_get[200];
	int num = 0;

	m_file->ReadString(str);
	if(str != "PrintSet:,")
	{
		return false;
	}

	for(int i=0; i<10; i++)
	{
		strcpy(str_name, "");
		strcpy(str_data, "");

		m_file->ReadString(str);
		sscanf(str, "%d,""%d,""%[^,],""%d,""%[^,],""%d,""%d,""%d", 
			&num, 
			&printItem[i].ItemCheck, 
			str_name, &printItem[i].namecode,
			str_data, &printItem[i].datacode,
			&printItem[i].pos_X, &printItem[i].pos_Y);
	
		printItem[i].name = "NULL";
		printItem[i].data = "NULL";
		printItem[i].name = str_name;
		printItem[i].data = str_data;

		if(printItem[i].name == "NULL")
		{
			printItem[i].name = "";
		}

		if(printItem[i].data == "NULL")
		{
			printItem[i].data = "";
		}
	}

	m_file->ReadString(str);
	sscanf(str, "%*[^,], %d, %d, %d", &CAT[0], &CAT[1], &CAT[2]);

	return true;
}

bool WritePrintSetFile(CStdioFile *m_file)
{
	CString str_write;	
	
	str_write = "PrintSet:,\n";
	m_file->WriteString(str_write);
	
	for(int i=0; i<10; i++)
	{
		if(printItem[i].name == "")
		{
			printItem[i].name = "NULL";
		}

		if(printItem[i].data == "")
		{
			printItem[i].data = "NULL";
		}

		str_write.Format("%d, %d,%s, %d,%s, %d, %d, %d\n", 
			i+1, 
			printItem[i].ItemCheck, 
			printItem[i].name, printItem[i].namecode, 
			printItem[i].data, printItem[i].datacode,
			printItem[i].pos_X, printItem[i].pos_Y);
		m_file->WriteString(str_write);
	}

	str_write.Format("CAT:, %d, %d, %d\n", CAT[0], CAT[1], CAT[2]);
	m_file->WriteString(str_write);

	return true;
}

extern int binBox[MAXBIN][2];
bool ReadBinMapFile(CStdioFile *m_file)
{
	CString str, str1, str2;
	int boxnum = 0;

	m_file->ReadString(str);
	m_file->ReadString(str);

	for(int i=0; i<80; i++)
	{
		m_file->ReadString(str);
		sscanf(str, "%*[^,],%d", &binBox[i][0]);
	}

	return true;
}

bool WriteBinMapFile(CStdioFile *m_file)
{
	CString str_write;
	
	str_write = "BinMapFile:,\n";
	m_file->WriteString(str_write);

	str_write = "Boxnum,      Bin,\n";
	m_file->WriteString(str_write);

	for(int i=0; i<80; i++)
	{
		str_write.Format("%d, %d,\n", i, binBox[i][0]);
		m_file->WriteString(str_write);
	}

	return true;
}