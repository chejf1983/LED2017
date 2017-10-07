#include "stdafx.h"
#include "Functions.h"

#include "SpectraArsenalEmissionAPI.h"

extern double DiameterOptic;
extern int intTestWay;   //0为正常测试  1为长亮测试
extern int intVfAverage;
extern int intChip;      //0为双脚单晶  1为双脚双晶  2为三脚双晶  3为四脚三晶
extern int intCommonfoot;   //公共脚  0为D 1为A 2为B 3为C
extern int intSetway;
extern int intWLType;    //0为峰值波长  1为主波长
extern int intWLSteps[3];
extern int intSampleAverage;
extern int intBoxcar;
extern int intFailBin;

extern TESTTYPE CHIP[3][18];
extern sngPOINT point[3][4];
extern int c[3];
extern bool usespectrum[3];

extern COLOR_PARA g_dColorPara;

extern bool testXYZ[3]; 
bool iftestXY[3] = {false, false, false};

extern int polfalsenum[3];  //反向测试项目的个数  IR VR
extern int intOpticGain[3];      //0为低   1为中    2为高  3为超高
extern double intIntegrationTime[3];
extern LightParam KeepLight[3];
extern LightParam PolParam[3];

extern int columns[3];
extern BinArray binArray;

extern int csvcolumns[3];
extern BinArray level_binArray;


extern SystemSet systemset; //systemfile
extern CalCoeff calcoeff;   //spectrumsetfile
extern double sngCurrentDark[3][PIXELNUM];   //caldarkfile
extern StandardLightResource standardCal;   //referfile

///////////////Init
int Show_wl[256];
///////////////test()
LEDNumStatistic ledStatistic;

int binnum[MAXBIN];
int binBox[MAXBIN][2];
CArray<int, int>feedingClowBox;
int MaxLedNum = 1000;

double spectrum_USB2000[3][2048];

HWND hWnd;

HINSTANCE hInstance;
bool Register = false;
extern int WaitInteDelay;

COLOR_PARA g_dColorPara;
ORI_PARA g_dOriPara;

//Wrapper wrapper;
//DoubleArray SA;
//DoubleArray WA;	
double *spectrum[3], *wavelengths;
double realx = 0, realy = 0;
double x[3] = {0.3333, 0.3333, 0.3333};
double y[3] = {0.3333, 0.3333, 0.3333};

CString showShootBin[3][100];

///////测试值不在最大最小值范围内的项目序号,此序号后的项目需判断continue?来决定测试项目是否至此中止
int failItem[3] = {50, 50, 50};

double xyRange = 0.00001;   //////XY分级图形处理精度

HANDLE hCom; //准备打开的串口句柄
unsigned char read_data[1024];
int dataSize = 0;
CArray<int, int> OldBoxStatusArray;
CArray<int, int> NewBoxStatusArray;
CArray<int, int> BoxStatusArray;
CArray<LedStatus, LedStatus> waitingCheckLed;

////////新CIE坐标
XYLEVELItem BinCode[98];
CString BinCodeName[98];
CString MapBinCode[MAXBIN];
int AverageVfNum = -1;

bool iftestpass = false;
bool resetparam()
{
	int i = 0;

	ledStatistic.ledtotalnum = 1;
	ledStatistic.ledpassnum = 0;
	ledStatistic.ledfailnum = 0;
	ledStatistic.ledpasspercent = 0;

	for(i=0; i<3; i++)
	{
		for(int j=0; j<18; j++)
		{
			CHIP[i][j].min = 100000;
			CHIP[i][j].max = 0;
			CHIP[i][j].total = 0;
			CHIP[i][j].average = 0;
			
			CHIP[i][j].min_X = 100000;
			CHIP[i][j].max_X = 0;
			CHIP[i][j].total_X = 0;
			CHIP[i][j].average_X = 0;
			CHIP[i][j].min_Y = 100000;
			CHIP[i][j].max_Y = 0;
			CHIP[i][j].total_Y = 0;
			CHIP[i][j].average_Y = 0;
		}
	}

	for(i=0; i<MAXBIN; i++)
	{
		binnum[i] = 0;
	}

	return true;
}

int ExistLevels(int chip, int bin)
{
	CString str;
	int i = 0;
	int cols[4];
	int column = 0;
	int levels = bin + 1;

	cols[0] = 0;
	cols[1] = columns[0];
	cols[2] = columns[0] + columns[1];
	cols[3] = columns[0] + columns[1] + columns[2];

	for(i=0; i<3; i++)
	{
		if((i != chip) || ((i == chip) && (columns[i] < 8)))
		{
			if(columns[i] > 0)
			{
				levels = bin + 1;
				while((binArray.strBinArray[levels][cols[i]] != "")
					&&(binArray.strBinArray[levels][cols[i]] != "NULL"))
				{
					levels++;
				}
				return (levels-bin-1);
			}
		}
	}


	column = IsXYLevelExist(chip);
	if(cols[chip] > 8)
	{
		if((column < 0) || (column > cols[chip]))
		{
			levels = bin + 1;
			while((binArray.strBinArray[levels][cols[chip]] != "")
				&&(binArray.strBinArray[levels][cols[chip]] != "NULL"))
			{
				levels++;
			}
			return (levels-bin-1);
		}
		else
		{
			if(column == cols[chip])
			{
				levels = bin + 1;
				while((binArray.strBinArray[levels][cols[chip] + 8] != "")
					&&(binArray.strBinArray[levels][cols[chip] + 8] != "NULL"))
				{
					levels++;
				}
				return (levels-bin-1);
			}
		}
	}

	return 0;
}

int IsXYLevelExist(int chip)
{
	CString str_item;
	int cols[4];
	cols[0] = 0;
	cols[1] = columns[0];
	cols[2] = columns[0] + columns[1];
	cols[3] = columns[0] + columns[1] + columns[2];

	for(int i=cols[chip]; i<cols[chip + 1]; i++)
	{
		sscanf(binArray.strBinArray[0][i], "%*[^-]-%[^(]", str_item);
		if(0 == strcmp(str_item, "XYZ"))
		{
			return i;
		}
	}

	return -1;
}

bool SetBinArrayXYZItem(XYLEVELItem item, int bin,
						   CString (*string)[LEVELCOLUMNS],
						   int chip)
{
	int column = 0;
	CString str0, str[3];
	int i = 0;
	int cols0 = 0, cols[3] = {0, 0, 0};
	int startbin = 0;

	startbin = bin + 1;
	bin = startbin + item.num;
	column = IsXYLevelExist(chip);
	
	if(column < 0)
	{
		str[0] = "C1-XYZ";
		str[1] = "C2-XYZ";
		str[2] = "C3-XYZ";
		cols[0] = columns[0];
		cols[1] = columns[0] + columns[1];
		cols[2] = columns[0] + columns[1] + columns[2];
		cols0 = columns[0] + columns[1] + columns[2] - 1;
		
		//////不存在分级 则将要插入的位置后面的参数都后移八位
		for(i=0; i<=systemset.intMachineType; i++)
		{
			for(int j=cols0; j>=cols[chip]; j--)
			{
				string[i][j+8] = string[i][j];
			}
		}

		for(i=0; i<8; i++)
		{
			string[0][cols[chip] + i] = str[chip];
			for(int j=1; j<=systemset.intMachineType; j++)
			{
				str0 = "";
				string[j][cols[chip] + i] = "NULL";
				string[j][cols[chip] + i] = str0;
			}
		}

		columns[chip] += 8;
		column = cols[chip];
	}
	
	string[bin][column].Format("%f", item.x[0]);
	string[bin][column+1].Format("%f", item.y[0]);
	string[bin][column+2].Format("%f", item.x[1]);
	string[bin][column+3].Format("%f", item.y[1]);
	string[bin][column+4].Format("%f", item.x[2]);
	string[bin][column+5].Format("%f", item.y[2]);
	string[bin][column+6].Format("%f", item.x[3]);
	string[bin][column+7].Format("%f", item.y[3]);
	
	return true;
}

bool SetBinArrayXYZItem2(XYLEVELItem item, int bin, 
						   CString (*string)[LEVELCOLUMNS],
						   int chip, int num)
{
	int column = 0;
	CString str0, str[3];
	int i = 0, j = 0;
	int cols0 = 0, cols[3] = {0, 0, 0};
	int startbin = 0;

	startbin = bin + 1;
	column = IsXYLevelExist(chip);
	if(column > 0)
	{
		column = 0;
	}
	
	str[0] = "C1-XYZ";
	str[1] = "C2-XYZ";
	str[2] = "C3-XYZ";
	cols[0] = columns[0];
	cols[1] = columns[0] + columns[1];
	cols[2] = columns[0] + columns[1] + columns[2];
	cols0 = columns[0] + columns[1] + columns[2] - 1;

	if(column < 0)
	{
		//////不存在分级 则将要插入的位置后面的参数都后移八位
		for(i=0; i<=systemset.intMachineType; i++)
		{
			for(j=cols0; j>=cols[chip]; j--)
			{
				string[i][j+8] = string[i][j];
			}
		}

		for(i=0; i<8; i++)
		{
			string[0][cols[chip] + i] = str[chip];
			for(j=1; j<=systemset.intMachineType; j++)
			{
				str0 = "";
				string[j][cols[chip] + i] = "NULL";
				string[j][cols[chip] + i] = str0;
			}
		}

		columns[chip] += 8;
		column = cols[chip];
	}
	
	if((0 == num) || (1 == num))
	{
		bin = startbin + item.num;
		string[bin][column].Format("%f", item.x[0]);
		string[bin][column+1].Format("%f", item.y[0]);
		string[bin][column+2].Format("%f", item.x[1]);
		string[bin][column+3].Format("%f", item.y[1]);
		string[bin][column+4].Format("%f", item.x[2]);
		string[bin][column+5].Format("%f", item.y[2]);
		string[bin][column+6].Format("%f", item.x[3]);
		string[bin][column+7].Format("%f", item.y[3]);
	}
	else
	{
		bin = startbin + item.num * num;
		for(i=0; i<num; i++)
		{
			string[bin+i][column].Format("%f", item.x[0]);
			string[bin+i][column+1].Format("%f", item.y[0]);
			string[bin+i][column+2].Format("%f", item.x[1]);
			string[bin+i][column+3].Format("%f", item.y[1]);
			string[bin+i][column+4].Format("%f", item.x[2]);
			string[bin+i][column+5].Format("%f", item.y[2]);
			string[bin+i][column+6].Format("%f", item.x[3]);
			string[bin+i][column+7].Format("%f", item.y[3]);
		}
		
		if(item.num > 0)
		{
			cols[2] = columns[0] + columns[1] + columns[2];
			for(i=0; i<cols[2]; i++)
			{
				if((i < column) || (i > (column + 7)))
				{
					for(j=0; j<num; j++)
					{
						string[bin+j][i] = string[startbin+j][i];
					}
				}
			}
		}
	}
	
	return true;
}

bool InitCalDarkParam(int chip)
{
	for(int i=0; i<2048; i++)
	{
		sngCurrentDark[chip][i] = 0;
	}

	return true;
}

bool setCalDarkParam(int chip, double time)
{
	int Intetime = 1;
	ORI_PARA dOriPara;

	JK_Emission_DarkStorage_3LED(chip,(float)time,1,3,dOriPara);
	for(int i=0; i<calcoeff.pixels; i++)
	{
		sngCurrentDark[chip][i] = dOriPara.fDecAD[i];//fDecAD[i];
	}

	return true;
}

////////////////////////TEST
extern int intMiddleWave1;
bool PWLPOL(int chip, int middleWave)
{
	double pwl = 0;
	testgetSpectrum(chip);
	pwl = getPeakWL(1, false);
	if(pwl <= middleWave)
	{
		return true;
	}
	else
	{
		return false;
	}
	CloseLight(1, 600);
}

bool WLPOL(int chip)
{
	testgetSpectrum(chip);
	CloseLight(1, 600);
	return true;
}

bool GetPOL(int way, int chip)
{
	return TRUE;
	if(0 == way)
	{
		setway0(PolParam[chip].Voltage, PolParam[chip].Current, PolParam[chip].Delay);
	}
	else if(1 == way)
	{
		setway1(PolParam[chip].Voltage, PolParam[chip].Current, PolParam[chip].Delay);
	}
	else
	{
		if(0 == intWLType)
		{
			return PWLPOL(chip, intMiddleWave1);
		}
		else if(1 == intWLType)
		{
			return WLPOL(chip);
		}
	}

	return true;
}

bool checklink()
{
	int check = 0, valid = 0;
	for(int i=0; i<systemset.checkCount; i++)
	{
		if(0 == (Inport(0x250) & 1))
		{
			valid++;
			if(valid >= systemset.validCount)
			{
				return true;
			}
		}
		else
		{
			valid = 0;
		}
	}
	return false;
}

bool ispointInquadrangle(double x, double y, sngPOINT *p, double range)
{
	double k[4], b[4], gety[4];
	double maxx, minx;
	double totalmaxX = 0, totalminX = 0;
	int crosspoint = 0, totalpoint = 0;
	int cross = 0;
	int i = 0;

	for(i=0; i<3; i++)
	{
		totalmaxX = p[i].x;
		totalminX = p[i].x;

		if(p[i+1].x > totalmaxX)
		{
			totalmaxX = p[i+1].x;
		}

		if(p[i+1].x < totalminX)
		{
			totalminX = p[i+1].x;
		}
	}

	for(i=0; i<3; i++)
	{
		if(p[i+1].x >= p[i].x)
		{
			maxx = p[i+1].x;
			minx = p[i].x;
		}
		else
		{
			maxx = p[i].x;
			minx = p[i+1].x;
		}

		if((maxx >= (minx + range)) && (x >= (minx - range)) && (x <= (maxx + range)))
		{
			totalpoint ++;

			k[i] = (p[i+1].y - p[i].y) / (p[i+1].x - p[i].x);
			b[i] = p[i].y - k[i] * p[i].x;
			gety[i] = k[i] * x + b[i];
			
			if((gety[i] >= (y - range)) && (gety[i] <= (y + range)))
			{
				return true;
			}
			
			if(gety[i] > y)
			{
				crosspoint++;
				if(((x >= (minx - range)) && (x <= (minx + range)))
					|| ((x >= (maxx - range)) && (x <= (maxx + range))))
				{
					if(((x >= (totalminX - range)) && (x <= (totalminX + range)))
					|| ((x >= (totalmaxX - range)) && (x <= (totalmaxX + range))))
					{
						return false;
					}
					cross ++;
				}
			}
		}
		else if((maxx >= (minx - range)) && (maxx <= (minx + range)) 
			 && (x >= (minx - range)) && (x <= (minx + range)))
		{	
			if(((y >= (p[i].y + range)) && (y <= (p[i+1].y - range))) 
				|| ((y <= (p[i].y - range)) && (y >= (p[i+1].y + range))))
			{
				return true;
			}
		}
	}
	
	if(p[3].x >= p[0].x)
	{
		maxx = p[3].x;
		minx = p[0].x;
	}
	else
	{
		maxx = p[0].x;
		minx = p[3].x;
	}
	if((maxx >= (minx + range)) && (x >= (minx - range)) && (x <= (maxx + range)))
	{
		totalpoint ++;

		k[3] = (p[3].y - p[0].y) / (p[3].x - p[0].x);
		b[3] = p[3].y - k[3] * p[3].x;
		gety[3] = k[3] * x + b[3];
		
		if((gety[3] >= (y - range)) && (gety[3] <= (y + range)))
		{
			return true;
		}
		
		if(gety[3] > y)
		{
			crosspoint++;
			if(((x >= (minx - range)) && (x <= (minx + range)))
					|| ((x >= (maxx - range)) && (x <= (maxx + range))))
			{
				cross ++;
			}
		}
	}
	else if((maxx >= (minx - range)) && (maxx <= (minx + range)) 
			 && (x >= (minx - range)) && (x <= (minx + range)))
	{
		if(((y >= (p[3].y + range)) && (y <= (p[0].y - range))) 
				|| ((y <= (p[3].y - range)) && (y >= (p[0].y + range))))
		{
			return true;
		}
	}


	if(totalpoint > 2)
	{
		crosspoint -= cross/2;
	}

	if(1 == crosspoint)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool testgetSpectrum(int chip)
{
	int i = 0;
	bool IFSaturated = true;

 	OpenLight(KeepLight[chip].Voltage, KeepLight[chip].Current);
 	Delay(KeepLight[chip].Delay * 1000);

	COLOR_PARA dPara;
	ORI_PARA dOriPara;
	
	float fIntTime;
	fIntTime = (float)intIntegrationTime[chip];
	if (fIntTime < 0.1f)
	{
		fIntTime = 0.1f;
	}
	if (fIntTime > 60)
	{
		fIntTime = 60.0f;
	}
	int iR;
	iR = JK_Emission_GetData_3LED(chip,fIntTime,intSampleAverage,3,dPara,dOriPara);
	if (iR == SA_API_FAIL)
	{
		IFSaturated = false;
		return FALSE;
	}

	IFSaturated = TRUE;

	double dDecAD[2048];
	for (i = 0; i< dOriPara.iPixN; i++)
	{
		dDecAD[i] = dOriPara.fDecAD[i];
	}
	spectrum[chip] = &dDecAD[0];
	for (i = 0; i< 256; i++)
	{
		Show_wl[i] = (int)(0.48 * dOriPara.fDecWL[i*8] - 72);
	}
	for (i = 0; i< dOriPara.iPixN; i++)
	{
		spectrum_USB2000[chip][i] = dOriPara.fDecPL[i];//AD[i];
		if(spectrum_USB2000[chip][i] > 60000)
		{
			IFSaturated = false;
		}
	}

	g_dColorPara	= dPara;
	g_dOriPara		= dOriPara;

	CloseLight(1, 0);

	return IFSaturated;
}


bool getSpectrumFromFile()
{
	CStdioFile m_file;
	CString filePath;
	filePath = "C:\\Documents and Settings\\Administrator\\桌面\\gragh.Graph";

	if(m_file.Open((LPCTSTR)filePath, CFile::modeReadWrite))
	{
		CString str;
		int i = 0;
		char str_wl[20], str_sng[20];
		while(m_file.ReadString(str))
		{
			sscanf(str, "%s%s", str_wl, str_sng);	
//			spectrum_PC2000[0][i] = atof(str_sng);
			i++;
		}
//		setsngCounts(spectrum_PC2000[0], sngCurrentDark[0]);
		return true;
	}

	return false;
}

bool closeMixLight(int times, int delay)
{
	int delaytime = delay*1000;

	for(int i=0; i<times; i++)
	{
		Supply(0, 0, 2);
		Supply(0, 0, 3);
		CloseLight(1, 0);

		Delay(delaytime);
	}
	
	return true;
}

bool testgetSpectrum2(int chip)
{
	CString str_item;
	bool IFSaturated = true;

	OpenLight(KeepLight[chip].Voltage, KeepLight[chip].Current);
	OpenSupply(3);
	Supply(KeepLight[1].Voltage, KeepLight[1].Current, 2);
	Supply(KeepLight[2].Voltage, KeepLight[2].Current, 3);
	Delay(KeepLight[chip].Delay * 1000);

	int i;
	COLOR_PARA dPara;
	ORI_PARA dOriPara;

	JK_Emission_GetData_3LED(chip,(float)intIntegrationTime[chip],intSampleAverage,3,dPara,dOriPara);
	double dDecAD[2048];
	for (i = 0; i< dOriPara.iPixN; i++)
	{
		dDecAD[i] = dOriPara.fDecAD[i];
		spectrum_USB2000[chip][i] = dOriPara.fDecPL[i];//AD[i];
		if(spectrum_USB2000[chip][i] > 60000)
		{
			IFSaturated = false;
		}
	}
	spectrum[chip] = &dDecAD[0];
	for (i = 0; i< 256; i++)
	{
		Show_wl[i] = (int)(0.48 * dOriPara.fDecWL[i*8] - 72);
	}

// 	if (1)
// 	{
// 		//文件保存看看
// 		FILE *fp;
// 		CString sName;
// 		sName.Format("c:\\TestPL%d.dat", chip);
// 		if((fp=fopen(sName,"wt"))==0)
// 		{
// 		}
// 		else
// 		{
// 			for(int i=0;i<2048;i++)
// 			{
// 				fprintf(fp,"%.1f %.1f\n",dOriPara.fDecWL[i],dOriPara.fDecAD[i]);
// 			}
// 			
// 			fclose(fp);
// 		}
// 	}

	closeMixLight(1, 0);

	iftestXY[chip] = false;
	for( i=0; i<c[chip]; i++)
	{
		str_item = "NULL";
		sscanf(CHIP[chip][i].TestItem, "%[^(]", str_item);
		if(0 == strcmp(str_item, "XYZ"))
		{
			if(IFSaturated)
			{
				getXY();
				realx = getX();
				realy = getY();
				iftestXY[chip] = true;
				if(0 == CHIP[chip][i].Calway)
				{
					x[chip] = realx + CHIP[chip][i].CalParam2X;
					y[chip] = realy + CHIP[chip][i].CalParam2Y;
				}
				else if(1 == CHIP[chip][i].Calway)
				{
					x[chip] = realx * CHIP[chip][i].CalParam1X;
					y[chip] = realy * CHIP[chip][i].CalParam1Y;
				}
				else
				{
					x[chip] = realx * CHIP[chip][i].CalParam1X + CHIP[chip][i].CalParam2X;
					y[chip] = realy * CHIP[chip][i].CalParam1Y + CHIP[chip][i].CalParam2Y;
				}
				
				CHIP[chip][i].XValue = g_dColorPara.fx;//x[chip];
				CHIP[chip][i].YValue = g_dColorPara.fx;//y[chip];
				
				if(!ispointInquadrangle(CHIP[chip][i].XValue, CHIP[chip][i].YValue, point[chip], xyRange))
				{
					CHIP[chip][i].Result = false;
					if(!CHIP[chip][i].Continue)
					{
						failItem[chip] = i;
						return false;
					}
				}
				else
				{
					CHIP[chip][i].Result = true;
					HandleStatisticValue(&CHIP[chip][i].total_X, &CHIP[chip][i].max_X, &CHIP[chip][i].min_X, CHIP[chip][i].XValue);
					HandleStatisticValue(&CHIP[chip][i].total_Y, &CHIP[chip][i].max_Y, &CHIP[chip][i].min_Y, CHIP[chip][i].YValue);
				}
			}
			else
			{
				CHIP[chip][i].XValue = 0;
				CHIP[chip][i].YValue = 0;

				CHIP[chip][i].Result = false;
				if(!CHIP[chip][i].Continue)
				{
					failItem[chip] = i;
					return false;
				}
			}
		}
		else if(0 == strcmp(str_item, "IV"))
		{
			SetSupplyParam(KeepLight[1].Voltage, KeepLight[2].Voltage, KeepLight[1].Current, KeepLight[2].Current);
			CHIP[chip][i].TestValue = getYbit(true, intOpticGain[0], KeepLight[0].Voltage,
				KeepLight[0].Current, KeepLight[0].Delay, true);
			if(CHIP[chip][i].TestValue < 0)
			{
				CHIP[chip][i].TestValue = 0;
			}
			
			if(HandleCalValue(chip, i))
			{
				HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
			}
			else
			{
				if(!CHIP[chip][i].Continue)
				{	
					failItem[chip] = i;
					return false;
				}
			}
		}
		else if(0 == strcmp(str_item, "IE"))
		{
			CHIP[chip][i].TestValue = getOptics_IV(0, intIntegrationTime[chip]);
			
			if(HandleCalValue(chip, i))
			{
				HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
			}
			else
			{
				if(!CHIP[chip][i].Continue)
				{	
					failItem[chip] = i;
					return false;
				}
			}
		}
		else if(0 == strcmp(str_item, "LE"))
		{
			CHIP[chip][i].TestValue = getOptics_IV(2, intIntegrationTime[chip]);
			
			if(HandleCalValue(chip, i))
			{
				HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
			}
			else
			{
				if(!CHIP[chip][i].Continue)
				{	
					failItem[chip] = i;
					return false;
				}
			}
		}
		else if(0 == strcmp(str_item, "LV"))
		{
			CHIP[chip][i].TestValue = getOptics_IV(1, intIntegrationTime[chip]);
			
			if(HandleCalValue(chip, i))
			{
				HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
			}
			else
			{
				if(!CHIP[chip][i].Continue)
				{	
					failItem[chip] = i;
					return false;
				}
			}
		}
		else if(0 == strcmp(str_item, "PWL"))
		{
			if(IFSaturated)
			{
				CHIP[chip][i].TestValue = g_dColorPara.fLp;//getPeakWL(1, false);
				
				if(HandleCalValue(chip, i))
				{
					HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
				}
				else
				{
					if(!CHIP[chip][i].Continue)
					{	
						failItem[chip] = i;
						return false;
					}
				}
			}
			else
			{
				CHIP[chip][i].TestValue = 0;
				if(!CHIP[chip][i].Continue)
				{	
					failItem[chip] = i;
					return false;
				}
			}
		}
		else if(0 == strcmp(str_item, "DeltaWL"))
		{
			if(IFSaturated)
			{
				CHIP[chip][i].TestValue = g_dColorPara.fLd;//getDeltaWL();
				
				if(HandleCalValue(chip, i))
				{
					HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
				}
				else
				{
					if(!CHIP[chip][i].Continue)
					{	
						failItem[chip] = i;
						return false;
					}
				}
			}
			else
			{
				CHIP[chip][i].TestValue = 0;
				if(!CHIP[chip][i].Continue)
				{	
					failItem[chip] = i;
					return false;
				}
			}
		}
		else
		{
			if(IFSaturated)
			{
				if(!iftestXY[chip])
				{
					getXY();
					realx = getX();
					realy = getY();
					x[chip] = realx;
					y[chip] = realy;
					iftestXY[chip] = true;
				}	
			}
			
			if(0 == strcmp(str_item, "WL"))
			{
				if(IFSaturated)
				{
					if(0 == intWLSteps[chip])
					{
						CHIP[chip][i].TestValue = getWL_New(realx, realy);
					}	
					else
					{
						CHIP[chip][i].TestValue = getWL_5nm_New(realx, realy);
					}
					
					if(HandleCalValue(chip, i))
					{
						HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
					}
					else
					{
						if(!CHIP[chip][i].Continue)
						{	
							failItem[chip] = i;
							return false;
						}
					}
				}
				else
				{
					CHIP[chip][i].TestValue = 0;
					if(!CHIP[chip][i].Continue)
					{	
						failItem[chip] = i;
						return false;
					}
				}
			}
			
			else if(0 == strcmp(str_item, "PUR"))
			{
				if(IFSaturated)
				{
					CHIP[chip][i].TestValue = g_dColorPara.fPur;//getPUR(realx, realy);
					
					if(HandleCalValue(chip, i))
					{
						HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
					}
					else
					{
						if(!CHIP[chip][i].Continue)
						{	
							failItem[chip] = i;
							return false;
						}
					}
				}
				else
				{
					CHIP[chip][i].TestValue = 0;
					if(!CHIP[chip][i].Continue)
					{	
						failItem[chip] = i;
						return false;
					}
				}
			}
			
			else if(0 == strcmp(str_item, "CCT"))
			{
				if(IFSaturated)
				{
					CHIP[chip][i].TestValue = g_dColorPara.fCCT;//getCCT(realx, realy);
					
					if(HandleCalValue(chip, i))
					{
						HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
					}
					else
					{
						if(!CHIP[chip][i].Continue)
						{	
							failItem[chip] = i;
							return false;
						}
					}
				}
				else
				{
					CHIP[chip][i].TestValue = 0;
					if(!CHIP[chip][i].Continue)
					{	
						failItem[chip] = i;
						return false;
					}
				}
			}
			
			else if(0 == strcmp(str_item, "CRI"))
			{
				if(IFSaturated)
				{
					CHIP[chip][i].TestValue = g_dColorPara.fRa;//getCRI(realx, realy);
					
					if(HandleCalValue(chip, i))
					{
						HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
					}
					else
					{
						if(!CHIP[chip][i].Continue)
						{	
							failItem[chip] = i;
							return false;
						}
					}
				}
				else
				{
					CHIP[chip][i].TestValue = 0;
					if(!CHIP[chip][i].Continue)
					{	
						failItem[chip] = i;
						return false;
					}
				}
			}
		}
	}

	closeMixLight(1, 0);

	failItem[chip] = c[chip];
	return true;
}

bool HandleCalValue(int chip, int i)
{
	if(0 == CHIP[chip][i].Calway)
	{
		CHIP[chip][i].TestValue += CHIP[chip][i].CalParam2;
	}
	else if(1 == CHIP[chip][i].Calway)
	{
		CHIP[chip][i].TestValue *= CHIP[chip][i].CalParam1;
	}
	else
	{
		CHIP[chip][i].TestValue = CHIP[chip][i].TestValue * CHIP[chip][i].CalParam1 
		                                                  + CHIP[chip][i].CalParam2;
	}

	if((CHIP[chip][i].TestValue > CHIP[chip][i].Upper) 
		|| (CHIP[chip][i].TestValue < CHIP[chip][i].Lower))
	{
		CHIP[chip][i].Result = false;
	}
	else
	{
		CHIP[chip][i].Result = true;
	}

	return CHIP[chip][i].Result;
}

bool HandleStatisticValue(double *total, double *max, double *min, double value)
{
	*total += value;

	if(value > *max)
	{
		*max = value;
	}

	if(value < *min)
	{
		*min = value;
	}

	return true;
}

void testSpecially0(int chip)  //常用测试项目  IR VF IV XYZ 
{
	OpenLight(KeepLight[chip].Voltage, KeepLight[chip].Current);
	Delay(KeepLight[chip].Delay * 1000);
	int i;
	COLOR_PARA dPara;
	ORI_PARA dOriPara;
	
	JK_Emission_GetData_3LED(chip,(float)intIntegrationTime[chip],intSampleAverage,3,dPara,dOriPara);
	double dDecAD[2048];
	for (i = 0; i< dOriPara.iPixN; i++)
	{
		dDecAD[i] = dOriPara.fDecPL[i];//fDecAD[i];
	}
	spectrum[chip] = &dDecAD[0];
	setsngCounts(spectrum[chip], sngCurrentDark[chip]);

	CloseLight(1, 0);
}

bool test(int chip)
{
	CString str_item;
	bool ifgetspectrum	= false;
	bool IFSaturated	= true;
/*	if(usespectrum[chip])
	{	
		IFSaturated = testgetSpectrum(chip);
	}*/

	iftestXY[chip] = false;
	for(int i=0; i<c[chip]; i++)
	{
		str_item = "NULL";
		sscanf(CHIP[chip][i].TestItem, "%[^(]", str_item);
		if(0 == strcmp(str_item, "IR"))
		{
			CHIP[chip][i].TestValue = 1000 * fabs(getIR(CHIP[chip][i].VCom, CHIP[chip][i].ICom, CHIP[chip][i].Delay));
			
			if(HandleCalValue(chip, i))
			{
				HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
			}
			else
			{
				if(!CHIP[chip][i].Continue)
				{	
					failItem[chip] = i;
					return false;
				}
			}
		}
		else if(0 == strcmp(str_item, "VF"))
		{
			CHIP[chip][i].TestValue = getVF(CHIP[chip][i].VCom, CHIP[chip][i].ICom, CHIP[chip][i].Delay);
			if(!getBering())
			{
				CHIP[chip][i].TestValue += systemset.VRoffset[chip];
			}

			if(HandleCalValue(chip, i))
			{
				HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
			}
			else
			{
				if(!CHIP[chip][i].Continue)
				{	
					failItem[chip] = i;
					return false;
				}
			}
		}
		else if(0 == strcmp(str_item, "IV"))
		{
			CHIP[chip][i].TestValue = getYbit(false, intOpticGain[chip], CHIP[chip][i].VCom,
				CHIP[chip][i].ICom, CHIP[chip][i].Delay, true);
			if(CHIP[chip][i].TestValue < 0)
			{
				CHIP[chip][i].TestValue = 0;
			}
			
			if(HandleCalValue(chip, i))
			{
				HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
			}
			else
			{
				if(!CHIP[chip][i].Continue)
				{	
					failItem[chip] = i;
					return false;
				}
			}
		}
		else if(0 == strcmp(str_item, "IE"))
		{
			if(!ifgetspectrum)
			{
				IFSaturated = testgetSpectrum(chip);
				ifgetspectrum = true;
			}

			if(IFSaturated)
			{
				CHIP[chip][i].TestValue = getOptics_IV(0, intIntegrationTime[chip]);
				
				if(HandleCalValue(chip, i))
				{
					HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
				}
				else
				{
					if(!CHIP[chip][i].Continue)
					{	
						failItem[chip] = i;
						return false;
					}
				}
			}
			else
			{
				CHIP[chip][i].TestValue = 0;
				if(!CHIP[chip][i].Continue)
				{	
					failItem[chip] = i;
					return false;
				}
			}
		}
		else if(0 == strcmp(str_item, "LE"))
		{
			if(!ifgetspectrum)
			{
				IFSaturated = testgetSpectrum(chip);
				ifgetspectrum = true;
			}

			if(IFSaturated)
			{
				CHIP[chip][i].TestValue = getOptics_IV(2, intIntegrationTime[chip]);
				
				if(HandleCalValue(chip, i))
				{
					HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
				}
				else
				{
					if(!CHIP[chip][i].Continue)
					{	
						failItem[chip] = i;
						return false;
					}
				}
			}
			else
			{
				CHIP[chip][i].TestValue = 0;
				if(!CHIP[chip][i].Continue)
				{	
					failItem[chip] = i;
					return false;
				}
			}
		}
		else if(0 == strcmp(str_item, "LV"))
		{
			if(!ifgetspectrum)
			{
				IFSaturated = testgetSpectrum(chip);
				ifgetspectrum = true;
			}

			if(IFSaturated)
			{
				CHIP[chip][i].TestValue = getOptics_IV(1, intIntegrationTime[chip]);
				
				if(HandleCalValue(chip, i))
				{
					HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
				}
				else
				{
					if(!CHIP[chip][i].Continue)
					{	
						failItem[chip] = i;
						return false;
					}
				}
			}
			else
			{
				CHIP[chip][i].TestValue = 0;
				if(!CHIP[chip][i].Continue)
				{	
					failItem[chip] = i;
					return false;
				}
			}
		}
		else if(0 == strcmp(str_item, "XYZ"))
		{
			if(!ifgetspectrum)
			{
				IFSaturated = testgetSpectrum(chip);
				ifgetspectrum = true;
			}
			
			if(IFSaturated)
			{
				getXY();
				realx = getX();
				realy = getY();
				iftestXY[chip] = true;
				if(0 == CHIP[chip][i].Calway)
				{
					x[chip] = realx + CHIP[chip][i].CalParam2X;
					y[chip] = realy + CHIP[chip][i].CalParam2Y;
				}
				else if(1 == CHIP[chip][i].Calway)
				{
					x[chip] = realx * CHIP[chip][i].CalParam1X;
					y[chip] = realy * CHIP[chip][i].CalParam1Y;
				}
				else
				{
					x[chip] = realx * CHIP[chip][i].CalParam1X + CHIP[chip][i].CalParam2X;
					y[chip] = realy * CHIP[chip][i].CalParam1Y + CHIP[chip][i].CalParam2Y;
				}
				
				CHIP[chip][i].XValue = g_dColorPara.fx;//x[chip];
				CHIP[chip][i].YValue = g_dColorPara.fy;//y[chip];


				if(!ispointInquadrangle(CHIP[chip][i].XValue, CHIP[chip][i].YValue, point[chip], xyRange))
				{
					CHIP[chip][i].Result = false;
					if(!CHIP[chip][i].Continue)
					{
						failItem[chip] = i;
						return false;
					}
				}
				else
				{
					CHIP[chip][i].Result = true;
					HandleStatisticValue(&CHIP[chip][i].total_X, &CHIP[chip][i].max_X, &CHIP[chip][i].min_X, CHIP[chip][i].XValue);
					HandleStatisticValue(&CHIP[chip][i].total_Y, &CHIP[chip][i].max_Y, &CHIP[chip][i].min_Y, CHIP[chip][i].YValue);
				}
			}
			else
			{
				CHIP[chip][i].XValue = 0;
				CHIP[chip][i].YValue = 0;
				
				CHIP[chip][i].Result = false;
				if(!CHIP[chip][i].Continue)
				{
					failItem[chip] = i;
					return false;
				}
			}
		}
		else if(0 == strcmp(str_item, "PWL"))
		{
			if(!ifgetspectrum)
			{
				IFSaturated = testgetSpectrum(chip);
				ifgetspectrum = true;
			}

			if(IFSaturated)
			{
				CHIP[chip][i].TestValue = g_dColorPara.fLp;//getPeakWL(1, false);
				
				if(HandleCalValue(chip, i))
				{
					HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
				}
				else
				{
					if(!CHIP[chip][i].Continue)
					{	
						failItem[chip] = i;
						return false;
					}
				}
			}
			else
			{
				CHIP[chip][i].TestValue = 0;
				if(!CHIP[chip][i].Continue)
				{	
					failItem[chip] = i;
					return false;
				}
			}
		}
		else if(0 == strcmp(str_item, "DVF"))
		{
			CHIP[chip][i].TestValue = getDVF(CHIP[chip][i].ICom, CHIP[chip][i].Delay);

			if(HandleCalValue(chip, i))
			{
				HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
			}
			else
			{
				if(!CHIP[chip][i].Continue)
				{	
					failItem[chip] = i;
					return false;
				}
			}
		}
		else if(0 == strcmp(str_item, "DeltaWL"))
		{
			if(!ifgetspectrum)
			{
				IFSaturated = testgetSpectrum(chip);
				ifgetspectrum = true;
			}

			if(IFSaturated)
			{
				CHIP[chip][i].TestValue = g_dColorPara.fLd;//getDeltaWL();
				
				if(HandleCalValue(chip, i))
				{
					HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
				}
				else
				{
					if(!CHIP[chip][i].Continue)
					{	
						failItem[chip] = i;
						return false;
					}
				}
			}
			else
			{
				CHIP[chip][i].TestValue = 0;
				if(!CHIP[chip][i].Continue)
				{	
					failItem[chip] = i;
					return false;
				}
			}
		}
		else if(0 == strcmp(str_item, "IF"))
		{
			CHIP[chip][i].TestValue = getIF(CHIP[chip][i].VCom, CHIP[chip][i].ICom, CHIP[chip][i].Delay);
			
			if(HandleCalValue(chip, i))
			{
				HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
			}
			else
			{
				if(!CHIP[chip][i].Continue)
				{	
					failItem[chip] = i;
					return false;
				}
			}
		}
		else if(0 == strcmp(str_item, "VR"))
		{
			CHIP[chip][i].TestValue = getVR(CHIP[chip][i].VCom, CHIP[chip][i].ICom, CHIP[chip][i].Delay);
			
			if(HandleCalValue(chip, i))
			{
				HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
			}
			else
			{
				if(!CHIP[chip][i].Continue)
				{	
					failItem[chip] = i;
					return false;
				}
			}
		}	
		else if(0 == strcmp(str_item, "THY"))
		{
			CHIP[chip][i].TestValue = getTHY(CHIP[chip][i].VCom, CHIP[chip][i].ICom);
			
			if(HandleCalValue(chip, i))
			{
				HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
			}
			else
			{
				if(!CHIP[chip][i].Continue)
				{	
					failItem[chip] = i;
					return false;
				}
			}
		}
		else
		{
			if(!ifgetspectrum)
			{
				IFSaturated = testgetSpectrum(chip);
				ifgetspectrum = true;
			}

			if(IFSaturated)
			{
				if(!iftestXY[chip])
				{
					getXY();
					realx = getX();
					realy = getY();
					x[chip] = realx;
					y[chip] = realy;
					iftestXY[chip] = true;
				}
			}

			if(0 == strcmp(str_item, "WL"))
			{
				if(IFSaturated)
				{
					if(0 == intWLSteps[chip])
					{
						CHIP[chip][i].TestValue = getWL_New(realx, realy);
					}	
					else
					{
						CHIP[chip][i].TestValue = getWL_5nm_New(realx, realy);
					}
					
					if(HandleCalValue(chip, i))
					{
						HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
					}
					else
					{
						if(!CHIP[chip][i].Continue)
						{
							failItem[chip] = i;
							return false;
						}
					}
				}
				else
				{
					CHIP[chip][i].TestValue = 0;
					if(!CHIP[chip][i].Continue)
					{
						failItem[chip] = i;
						return false;
					}
				}
			}

			else if(0 == strcmp(str_item, "PUR"))
			{
				if(IFSaturated)
				{
					CHIP[chip][i].TestValue = g_dColorPara.fPur;//getPUR(realx, realy);
					
					if(HandleCalValue(chip, i))
					{
						HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
					}
					else
					{
						if(!CHIP[chip][i].Continue)
						{	
							failItem[chip] = i;
							return false;
						}
					}
				}
				else
				{
					CHIP[chip][i].TestValue = 0;
					if(!CHIP[chip][i].Continue)
					{
						failItem[chip] = i;
						return false;
					}
				}
			}

			else if(0 == strcmp(str_item, "CCT"))
			{
				if(IFSaturated)
				{
					CHIP[chip][i].TestValue = g_dColorPara.fCCT;//getCCT(realx, realy);
					
					if(HandleCalValue(chip, i))
					{
						HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
					}
					else
					{
						if(!CHIP[chip][i].Continue)
						{	
							failItem[chip] = i;
							return false;
						}
					}
				}
				else
				{
					CHIP[chip][i].TestValue = 0;
					if(!CHIP[chip][i].Continue)
					{
						failItem[chip] = i;
						return false;
					}
				}
			}

			else if(0 == strcmp(str_item, "CRI"))
			{
				if(IFSaturated)
				{
					CHIP[chip][i].TestValue = g_dColorPara.fRa;//getCRI(realx, realy);
					
					if(HandleCalValue(chip, i))
					{
						HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
					}
					else
					{
						if(!CHIP[chip][i].Continue)
						{	
							failItem[chip] = i;
							return false;
						}
					}
				}
				else
				{
					CHIP[chip][i].TestValue = 0;
					if(!CHIP[chip][i].Continue)
					{
						failItem[chip] = i;
						return false;
					}
				}
			}
		}	
	}

	failItem[chip] = c[chip];
	return true;
}

bool KeepLight_test(int chip)
{	
	CString str_item;
	bool IFSaturated = true;
	if(usespectrum[chip])
	{
		IFSaturated = testgetSpectrum(chip);
	}

	int i = 0;
	if(polfalsenum[chip] != 0)
	{
		for(i=0; i<polfalsenum[chip]; i++)//firstopticnum[chip]
		{
			str_item = "NULL";
			sscanf(CHIP[chip][i].TestItem, "%[^(]", str_item);
			if(0 == strcmp(str_item, "IR"))
			{
				if(KeepLight[chip].Current > 0.1)
				{
					OpenLight(KeepLight[chip].Voltage, 0.1);
					Delay(KeepLight[chip].Delay * 1000);
				}
				else
				{
					OpenLight(KeepLight[chip].Voltage, KeepLight[chip].Current);
					Delay(KeepLight[chip].Delay * 1000);
				}
				CHIP[chip][i].TestValue = 1000 * fabs(KeepLight_getIR(CHIP[chip][i].Delay));

				if(HandleCalValue(chip, i))
				{
					HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
				}
				else
				{
					if(!CHIP[chip][i].Continue)
					{	
						failItem[chip] = i;
						return false;
					}
				}
			}
			else if(0 == strcmp(str_item, "VR"))
			{
				OpenLight(KeepLight[chip].Voltage, KeepLight[chip].Current);
				Delay(KeepLight[chip].Delay * 1000);
				CHIP[chip][i].TestValue = KeepLight_getVR(CHIP[chip][i].Delay);
				if(HandleCalValue(chip, i))
				{
					HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
				}
				else
				{
					if(!CHIP[chip][i].Continue)
					{	
						failItem[chip] = i;
						return false;
					}
				}
				CloseLight(1, 600);
			}	
		}
	}

	iftestXY[chip] = false;
	OpenLight(KeepLight[chip].Voltage, KeepLight[chip].Current);
	Delay(KeepLight[chip].Delay * 1000);
	for(i=0; i<c[chip]; i++)
	{
		if(0 == strcmp(str_item, "VF"))
		{
			CHIP[chip][i].TestValue = KeepLight_getVF(CHIP[chip][i].Delay);
			if(!getBering())
			{
				CHIP[chip][i].TestValue += systemset.VRoffset[chip];
			}

			if(HandleCalValue(chip, i))
			{
				HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
			}
			else
			{
				if(!CHIP[chip][i].Continue)
				{	
					failItem[chip] = i;
					return false;
				}
			}
		}
		else if(0 == strcmp(str_item, "IV"))
		{
			CHIP[chip][i].TestValue = getYbit(false, intOpticGain[chip], CHIP[chip][i].VCom, 
				CHIP[chip][i].ICom, CHIP[chip][i].Delay, true);
			if(CHIP[chip][i].TestValue < 0)
			{
				CHIP[chip][i].TestValue = 0;
			}
			
			if(HandleCalValue(chip, i))
			{
				HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
			}
			else
			{
				if(!CHIP[chip][i].Continue)
				{	
					failItem[chip] = i;
					return false;
				}
			}
		}
		else if(0 == strcmp(str_item, "IE"))
		{
			CHIP[chip][i].TestValue = getOptics_IV(0, intIntegrationTime[chip]);
			
			if(HandleCalValue(chip, i))
			{
				HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
			}
			else
			{
				if(!CHIP[chip][i].Continue)
				{	
					failItem[chip] = i;
					return false;
				}
			}
		}
		else if(0 == strcmp(str_item, "LE"))
		{
			CHIP[chip][i].TestValue = getOptics_IV(2, intIntegrationTime[chip]);
			
			if(HandleCalValue(chip, i))
			{
				HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
			}
			else
			{
				if(!CHIP[chip][i].Continue)
				{	
					failItem[chip] = i;
					return false;
				}
			}
		}
		else if(0 == strcmp(str_item, "LV"))
		{
			CHIP[chip][i].TestValue = getOptics_IV(1, intIntegrationTime[chip]);
			
			if(HandleCalValue(chip, i))
			{
				HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
			}
			else
			{
				if(!CHIP[chip][i].Continue)
				{	
					failItem[chip] = i;
					return false;
				}
			}
		}
		
		else if(0 == strcmp(str_item, "XYZ"))
		{
			if(IFSaturated)
			{
				getXY();
				realx = getX();
				realy = getY();
				iftestXY[chip] = true;
				if(0 == CHIP[chip][i].Calway)
				{
					x[chip] = realx + CHIP[chip][i].CalParam2X;
					y[chip] = realy + CHIP[chip][i].CalParam2Y;
				}
				else if(1 == CHIP[chip][i].Calway)
				{
					x[chip] = realx * CHIP[chip][i].CalParam1X;
					y[chip] = realy * CHIP[chip][i].CalParam1Y;
				}
				else
				{
					x[chip] = realx * CHIP[chip][i].CalParam1X + CHIP[chip][i].CalParam2X;
					y[chip] = realy * CHIP[chip][i].CalParam1Y + CHIP[chip][i].CalParam2Y;
				}
				
				CHIP[chip][i].XValue = g_dColorPara.fx;//x[chip];
				CHIP[chip][i].YValue = g_dColorPara.fy;//y[chip];
				
				if(!ispointInquadrangle(CHIP[chip][i].XValue, CHIP[chip][i].YValue, point[chip], xyRange))
				{
					CHIP[chip][i].Result = false;
					if(!CHIP[chip][i].Continue)
					{
						failItem[chip] = i;
						return false;
					}
				}
				else
				{
					CHIP[chip][i].Result = true;
					HandleStatisticValue(&CHIP[chip][i].total_X, &CHIP[chip][i].max_X, &CHIP[chip][i].min_X, CHIP[chip][i].XValue);
					HandleStatisticValue(&CHIP[chip][i].total_Y, &CHIP[chip][i].max_Y, &CHIP[chip][i].min_Y, CHIP[chip][i].YValue);
				}
			}
			else
			{
				CHIP[chip][i].XValue = 0;
				CHIP[chip][i].YValue = 0;
				
				CHIP[chip][i].Result = false;
				if(!CHIP[chip][i].Continue)
				{
					failItem[chip] = i;
					return false;
				}
			}
		}
		else if(0 == strcmp(str_item, "PWL"))
		{
			if(IFSaturated)
			{
				CHIP[chip][i].TestValue = g_dColorPara.fLp;//getPeakWL(1, false);
				
				if(HandleCalValue(chip, i))
				{
					HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
				}
				else
				{
					if(!CHIP[chip][i].Continue)
					{	
						failItem[chip] = i;
						return false;
					}
				}
			}
			else
			{
				CHIP[chip][i].TestValue = 0;
				if(!CHIP[chip][i].Continue)
				{	
					failItem[chip] = i;
					return false;
				}
			}
		}
		else if(0 == strcmp(str_item, "IF"))
		{
			CHIP[chip][i].TestValue = KeepLight_getIF(CHIP[chip][i].Delay);
			
			if(HandleCalValue(chip, i))
			{
				HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
			}
			else
			{
				if(!CHIP[chip][i].Continue)
				{	
					failItem[chip] = i;
					return false;
				}
			}
		}
		else if(0 == strcmp(str_item, "DVF"))
		{
			CHIP[chip][i].TestValue = getDVF(CHIP[chip][i].ICom, CHIP[chip][i].Delay);
			
			if(HandleCalValue(chip, i))
			{
				HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
			}
			else
			{
				if(!CHIP[chip][i].Continue)
				{
					failItem[chip] = i;
					return false;
				}
			}
		}
		else if(0 == strcmp(str_item, "DeltaWL"))
		{
			if(IFSaturated)
			{
				CHIP[chip][i].TestValue = g_dColorPara.fLd;//getDeltaWL();
				
				if(HandleCalValue(chip, i))
				{
					HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
				}
				else
				{
					if(!CHIP[chip][i].Continue)
					{	
						failItem[chip] = i;
						return false;
					}
				}
			}
			else
			{
				CHIP[chip][i].TestValue = 0;
				if(!CHIP[chip][i].Continue)
				{
					failItem[chip] = i;
					return false;
				}
			}
		}
		else if(0 == strcmp(str_item, "THY"))
		{
			CHIP[chip][i].TestValue = getTHY(CHIP[chip][i].VCom, CHIP[chip][i].ICom);
			
			if(HandleCalValue(chip, i))
			{
				HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
			}
			else
			{
				if(!CHIP[chip][i].Continue)
				{
					failItem[chip] = i;
					return false;
				}
			}
		}
		else
		{
			if(IFSaturated)
			{
				if(!iftestXY[chip])
				{
					getXY();
					realx = getX();
					realy = getY();
					x[chip] = realx;
					y[chip] = realy;
					iftestXY[chip] = true;
				}
			}
		

			if(0 == strcmp(str_item, "WL"))
			{
				if(IFSaturated)
				{
					if(0 == intWLSteps[chip])
					{
						CHIP[chip][i].TestValue = getWL_New(realx, realy);
					}	
					else
					{
						CHIP[chip][i].TestValue = getWL_5nm_New(realx, realy);
					}
					
					if(HandleCalValue(chip, i))
					{
						HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
					}
					else
					{
						if(!CHIP[chip][i].Continue)
						{
							failItem[chip] = i;
							return false;
						}
					}
				}
				else
				{
					CHIP[chip][i].TestValue = 0;
					if(!CHIP[chip][i].Continue)
					{	
						failItem[chip] = i;
						return false;
					}
				}
			}

			else if(0 == strcmp(str_item, "PUR"))
			{	
				if(IFSaturated)
				{
					CHIP[chip][i].TestValue = g_dColorPara.fPur;//getPUR(realx, realy);
					
					if(HandleCalValue(chip, i))
					{
						HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
					}
					else
					{
						if(!CHIP[chip][i].Continue)
						{	
							failItem[chip] = i;
							return false;
						}
					}
				}
				else
				{
					CHIP[chip][i].TestValue = 0;
					if(!CHIP[chip][i].Continue)
					{
						failItem[chip] = i;
						return false;
					}
				}
			}

			else if(0 == strcmp(str_item, "CCT"))
			{
				if(IFSaturated)
				{
					CHIP[chip][i].TestValue = g_dColorPara.fCCT;//getCCT(realx, realy);
					
					if(HandleCalValue(chip, i))
					{
						HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
					}
					else
					{
						if(!CHIP[chip][i].Continue)
						{
							failItem[chip] = i;
							return false;
						}
					}
				}
				else
				{
					CHIP[chip][i].TestValue = 0;
					if(!CHIP[chip][i].Continue)
					{
						failItem[chip] = i;
						return false;
					}
				}
			}

			else if(0 == strcmp(str_item, "CRI"))
			{
				if(IFSaturated)
				{
					CHIP[chip][i].TestValue = g_dColorPara.fRa;//getCRI(realx, realy);	
					
					if(HandleCalValue(chip, i))
					{
						HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
					}
					else
					{
						if(!CHIP[chip][i].Continue)
						{	
							failItem[chip] = i;
							return false;
						}
					}
				}
				else
				{
					CHIP[chip][i].TestValue = 0;
					if(!CHIP[chip][i].Continue)
					{
						failItem[chip] = i;
						return false;
					}
				}
			}
		}	
	}
	CloseLight(1, 0);

	failItem[chip] = c[chip];
	return true;
}

bool MixLight_test(int chip)
{
	CString str_item;

	for(int i=0; i<c[chip]; i++)
	{
		str_item = "NULL";
		sscanf(CHIP[chip][i].TestItem, "%[^(]", str_item);
		if(0 == strcmp(str_item, "IR"))
		{
			CHIP[chip][i].TestValue = 1000 * fabs(getIR(CHIP[chip][i].VCom, CHIP[chip][i].ICom, CHIP[chip][i].Delay));
			
			if(HandleCalValue(chip, i))
			{
				HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
			}
			else
			{
				if(!CHIP[chip][i].Continue)
				{	
					failItem[chip] = i;
					return false;
				}
			}
		}
		else if(0 == strcmp(str_item, "VR"))
		{
			CHIP[chip][i].TestValue = getVR(CHIP[chip][i].VCom, CHIP[chip][i].ICom, CHIP[chip][i].Delay);
			
			if(HandleCalValue(chip, i))
			{
				HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
			}
			else
			{
				if(!CHIP[chip][i].Continue)
				{	
					failItem[chip] = i;
					return false;
				}
			}
		}	
		else if(0 == strcmp(str_item, "VZ"))
		{
			CHIP[chip][i].TestValue = getVR(CHIP[chip][i].VCom, CHIP[chip][i].ICom, CHIP[chip][i].Delay);
			
			if(HandleCalValue(chip, i))
			{
				HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
			}
			else
			{
				if(!CHIP[chip][i].Continue)
				{	
					failItem[chip] = i;
					return false;
				}
			}
		}	
		else if(0 == strcmp(str_item, "VF"))
		{
			CHIP[chip][i].TestValue = getVF(CHIP[chip][i].VCom, CHIP[chip][i].ICom, CHIP[chip][i].Delay);

			if(!getBering())
			{
				CHIP[chip][i].TestValue += systemset.VRoffset[chip];
			}
			
			if(0 == intVfAverage)
			{
				if(HandleCalValue(chip, i))
				{
					HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
				}
				else
				{
					if(!CHIP[chip][i].Continue)
					{	
						failItem[chip] = i;
						return false;
					}
				}
			}
			else
			{
				AverageVfNum = i;
			}
		}
		else if(0 == strcmp(str_item, "IF"))
		{
			CHIP[chip][i].TestValue = getIF(CHIP[chip][i].VCom, CHIP[chip][i].ICom, CHIP[chip][i].Delay);
			
			if(HandleCalValue(chip, i))
			{
				HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
			}
			else
			{
				if(!CHIP[chip][i].Continue)
				{	
					failItem[chip] = i;
					return false;
				}
			}
		}
		else if(0 == strcmp(str_item, "DVF"))
		{
			CHIP[chip][i].TestValue = getDVF(CHIP[chip][i].ICom, CHIP[chip][i].Delay);

			if(HandleCalValue(chip, i))
			{
				HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
			}
			else
			{
				if(!CHIP[chip][i].Continue)
				{	
					failItem[chip] = i;
					return false;
				}
			}
		}
		else if(0 == strcmp(str_item, "THY"))
		{
			CHIP[chip][i].TestValue = getTHY(CHIP[chip][i].VCom, CHIP[chip][i].ICom);
			
			if(HandleCalValue(chip, i))
			{
				HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
			}
			else
			{
				if(!CHIP[chip][i].Continue)
				{	
					failItem[chip] = i;
					return false;
				}
			}
		}
		
/*		else if((strcmp(str_item, "XYZ") != 0) && (strcmp(str_item, "IV") != 0))
		{
			testgetSpectrum(chip);
			
			if(0 == strcmp(str_item, "PWL"))
			{
				CHIP[chip][i].TestValue = getPeakWL(1);
				
				if(HandleCalValue(chip, i))
				{
					HandleStatisticValue(&total_PWL[chip], &max_PWL[chip], &min_PWL[chip], CHIP[chip][i].TestValue);
				}
				else
				{
					if(!CHIP[chip][i].Continue)
					{	
						failItem[chip] = i;
						return false;
					}
				}
			}

			else
			{
				getXY();
				realx = getX();
				realy = getY();
				x[chip] = realx;
				y[chip] = realy;
				
				
				if(0 == strcmp(str_item, "WL"))
				{
					if(0 == intWLSteps[chip])
					{
						CHIP[chip][i].TestValue = getWL_New(realx, realy);
					}	
					else
					{
						CHIP[chip][i].TestValue = getWL_5nm_New(realx, realy);
					}
					
					if(HandleCalValue(chip, i))
					{
						HandleStatisticValue(&total_WL[chip], &max_WL[chip], &min_WL[chip], CHIP[chip][i].TestValue);
					}
					else
					{
						if(!CHIP[chip][i].Continue)
						{
							failItem[chip] = i;
							return false;
						}
					}
				}
				
				else if(0 == strcmp(str_item, "PUR"))
				{			
					CHIP[chip][i].TestValue = getPUR(realx, realy);
					
					if(HandleCalValue(chip, i))
					{
						HandleStatisticValue(&total_PUR[chip], &max_PUR[chip], &min_PUR[chip], CHIP[chip][i].TestValue);
					}
					else
					{
						if(!CHIP[chip][i].Continue)
						{	
							failItem[chip] = i;
							return false;
						}
					}
				}
				
				else if(0 == strcmp(str_item, "CCT"))
				{
					CHIP[chip][i].TestValue = getCCT(realx, realy);
					
					if(HandleCalValue(chip, i))
					{
						HandleStatisticValue(&total_CCT[chip], &max_CCT[chip], &min_CCT[chip], CHIP[chip][i].TestValue);
					}
					else
					{
						if(!CHIP[chip][i].Continue)
						{	
							failItem[chip] = i;
							return false;
						}
					}
				}
				
				else if(0 == strcmp(str_item, "CRI"))
				{
					CHIP[chip][i].TestValue = getCRI(realx, realy);
					
					if(HandleCalValue(chip, i))
					{
						HandleStatisticValue(&total_CRI[chip], &max_CRI[chip], &min_CRI[chip], CHIP[chip][i].TestValue);
					}
					else
					{
						if(!CHIP[chip][i].Continue)
						{	
							failItem[chip] = i;
							return false;
						}
					}
				}
				else if(0 == strcmp(str_item, "DeltaWL"))
				{
					CHIP[chip][i].TestValue = getDeltaWL();
					
					if(HandleCalValue(chip, i))
					{
						HandleStatisticValue(&total_DeltaWL[chip], &max_DeltaWL[chip], &min_DeltaWL[chip], CHIP[chip][i].TestValue);
					}
					else
					{
						if(!CHIP[chip][i].Continue)
						{	
							failItem[chip] = i;
							return false;
						}
					}
				}
			}
		}*/	
	}
	
	if((1 == intVfAverage) && (AverageVfNum >= 0) && ((1 == chip) || (2 == chip)))
	{
		CHIP[0][AverageVfNum].TestValue += getVF(CHIP[0][AverageVfNum].VCom, CHIP[0][AverageVfNum].ICom, CHIP[0][AverageVfNum].Delay);
		
		if(!getBering())
		{
			CHIP[0][AverageVfNum].TestValue += systemset.VRoffset[chip];
		}

		if(2 == chip)
		{
			CHIP[0][AverageVfNum].TestValue = CHIP[0][AverageVfNum].TestValue / 3;

			if(HandleCalValue(0, AverageVfNum))
			{
				HandleStatisticValue(&CHIP[0][AverageVfNum].total, &CHIP[0][AverageVfNum].max, &CHIP[0][AverageVfNum].min, CHIP[0][AverageVfNum].TestValue);
			}
			else
			{
				if(!CHIP[0][AverageVfNum].Continue)
				{	
					failItem[0] = AverageVfNum;
					return false;
				}
			}

			AverageVfNum = -1;
		}
	}	

	failItem[chip] = c[chip];
	return true;
}


bool MixKeepLight_test(int chip)
{
	CString str_item;
	int i = 0;
	if(polfalsenum[chip] != 0)
	{
		for(i=0; i<polfalsenum[chip]; i++)//firstopticnum[chip]
		{
			str_item = "NULL";
			sscanf(CHIP[chip][i].TestItem, "%[^(]", str_item);
			if(0 == strcmp(str_item, "IR"))
			{
				if(KeepLight[chip].Current > 0.1)
				{
					OpenLight(KeepLight[chip].Voltage, 0.1);
					Delay(KeepLight[chip].Delay * 1000);
				}
				else
				{
					OpenLight(KeepLight[chip].Voltage, KeepLight[chip].Current);
					Delay(KeepLight[chip].Delay * 1000);
				}
				CHIP[chip][i].TestValue = 1000 * fabs(KeepLight_getIR(CHIP[chip][i].Delay));

				if(HandleCalValue(chip, i))
				{
					HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
				}
				else
				{
					if(!CHIP[chip][i].Continue)
					{	
						failItem[chip] = i;
						return false;
					}
				}
			}
			else if(0 == strcmp(str_item, "VR"))
			{
				OpenLight(KeepLight[chip].Voltage, KeepLight[chip].Current);
				Delay(KeepLight[chip].Delay * 1000);
				CHIP[chip][i].TestValue = KeepLight_getVR(CHIP[chip][i].Delay);
				if(HandleCalValue(chip, i))
				{
					HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
				}
				else
				{
					if(!CHIP[chip][i].Continue)
					{	
						failItem[chip] = i;
						return false;
					}
				}
				CloseLight(1, 600);
			}	
		}
	}

	OpenLight(KeepLight[chip].Voltage, KeepLight[chip].Current);
	Delay(KeepLight[chip].Delay * 1000);
	for(i=0; i<c[chip]; i++)
	{
		if(0 == strcmp(str_item, "VF"))
		{
			CHIP[chip][i].TestValue = KeepLight_getVF(CHIP[chip][i].Delay);
			if(!getBering())
			{
				CHIP[chip][i].TestValue += systemset.VRoffset[chip];
			}
			
			if(0 == intVfAverage)
			{
				if(HandleCalValue(chip, i))
				{
					HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
				}
				else
				{
					if(!CHIP[chip][i].Continue)
					{	
						failItem[chip] = i;
						return false;
					}
				}
			}
			else
			{
				AverageVfNum = i;
			}
		}
		else if(0 == strcmp(str_item, "IF"))
		{
			CHIP[chip][i].TestValue = KeepLight_getIF(CHIP[chip][i].Delay);
			
			if(HandleCalValue(chip, i))
			{
				HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
			}
			else
			{
				if(!CHIP[chip][i].Continue)
				{	
					failItem[chip] = i;
					return false;
				}
			}
		}
		else if(0 == strcmp(str_item, "DVF"))
		{
			CHIP[chip][i].TestValue = getDVF(CHIP[chip][i].ICom, CHIP[chip][i].Delay);
			
			if(HandleCalValue(chip, i))
			{
				HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
			}
			else
			{
				if(!CHIP[chip][i].Continue)
				{	
					failItem[chip] = i;
					return false;
				}
			}
		}
		else if(0 == strcmp(str_item, "THY"))
		{
			CHIP[chip][i].TestValue = getTHY(CHIP[chip][i].VCom, CHIP[chip][i].ICom);
			
			if(HandleCalValue(chip, i))
			{
				HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
			}
			else
			{
				if(!CHIP[chip][i].Continue)
				{	
					failItem[chip] = i;
					return false;
				}
			}
		}
	}

	if((1 == intVfAverage) && (AverageVfNum >= 0) && ((1 == chip) || (2 == chip)))
	{
		CHIP[0][AverageVfNum].TestValue += getVF(CHIP[0][AverageVfNum].VCom, CHIP[0][AverageVfNum].ICom, CHIP[0][AverageVfNum].Delay);
		
		if(!getBering())
		{
			CHIP[0][AverageVfNum].TestValue += systemset.VRoffset[chip];
		}

		if(2 == chip)
		{
			CHIP[0][AverageVfNum].TestValue = CHIP[0][AverageVfNum].TestValue / 3;

			if(HandleCalValue(0, AverageVfNum))
			{
				HandleStatisticValue(&CHIP[0][AverageVfNum].total, &CHIP[0][AverageVfNum].max, &CHIP[0][AverageVfNum].min, CHIP[0][AverageVfNum].TestValue);
			}
			else
			{
				if(!CHIP[0][AverageVfNum].Continue)
				{	
					failItem[0] = AverageVfNum;
					return false;
				}
			}

			AverageVfNum = -1;
		}
	}	

	failItem[chip] = c[chip];
	return true;
}

bool test2(int chip)
{
	CString str_item;
	bool IFSaturated = true;
	if(usespectrum[chip])
	{	
		IFSaturated = testgetSpectrum(chip);
	}

	iftestXY[chip] = false;
	int i = 0;
	for(i=0; i<c[chip]; i++)
	{
		str_item = "NULL";
		sscanf(CHIP[chip][i].TestItem, "%[^(]", str_item);
		if(0 == strcmp(str_item, "VF"))
		{
			CHIP[chip][i].TestValue = getVF(CHIP[chip][i].VCom, CHIP[chip][i].ICom, CHIP[chip][i].Delay);
			if(!getBering())
			{
				CHIP[chip][i].TestValue += systemset.VRoffset[chip];
			}

			if(HandleCalValue(chip, i))
			{
				HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
			}
			else
			{
				if(!CHIP[chip][i].Continue)
				{	
					failItem[chip] = i;
					return false;
				}
			}
		}
		else if(0 == strcmp(str_item, "IV"))
		{
			CHIP[chip][i].TestValue = getYbit(false, intOpticGain[chip], CHIP[chip][i].VCom,
				CHIP[chip][i].ICom, CHIP[chip][i].Delay, true);
			if(CHIP[chip][i].TestValue < 0)
			{
				CHIP[chip][i].TestValue = 0;
			}
			
			if(HandleCalValue(chip, i))
			{
				HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
			}
			else
			{
				if(!CHIP[chip][i].Continue)
				{	
					failItem[chip] = i;
					return false;
				}
			}
		}
		else if(0 == strcmp(str_item, "IE"))
		{
			CHIP[chip][i].TestValue = getOptics_IV(0, intIntegrationTime[chip]);
			
			if(HandleCalValue(chip, i))
			{
				HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
			}
			else
			{
				if(!CHIP[chip][i].Continue)
				{	
					failItem[chip] = i;
					return false;
				}
			}
		}
		else if(0 == strcmp(str_item, "LE"))
		{
			CHIP[chip][i].TestValue = getOptics_IV(2, intIntegrationTime[chip]);
			
			if(HandleCalValue(chip, i))
			{
				HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
			}
			else
			{
				if(!CHIP[chip][i].Continue)
				{	
					failItem[chip] = i;
					return false;
				}
			}
		}
		else if(0 == strcmp(str_item, "LV"))
		{
			CHIP[chip][i].TestValue = getOptics_IV(1, intIntegrationTime[chip]);
			
			if(HandleCalValue(chip, i))
			{
				HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
			}
			else
			{
				if(!CHIP[chip][i].Continue)
				{	
					failItem[chip] = i;
					return false;
				}
			}
		}
		
		else if(0 == strcmp(str_item, "XYZ"))
		{
			if(IFSaturated)
			{
				getXY();
				realx = getX();
				realy = getY();
				iftestXY[chip] = true;
				if(0 == CHIP[chip][i].Calway)
				{
					x[chip] = realx + CHIP[chip][i].CalParam2X;
					y[chip] = realy + CHIP[chip][i].CalParam2Y;
				}
				else if(1 == CHIP[chip][i].Calway)
				{
					x[chip] = realx * CHIP[chip][i].CalParam1X;
					y[chip] = realy * CHIP[chip][i].CalParam1Y;
				}
				else
				{
					x[chip] = realx * CHIP[chip][i].CalParam1X + CHIP[chip][i].CalParam2X;
					y[chip] = realy * CHIP[chip][i].CalParam1Y + CHIP[chip][i].CalParam2Y;
				}
				
				CHIP[chip][i].XValue = g_dColorPara.fx;//x[chip];
				CHIP[chip][i].YValue = g_dColorPara.fy;//y[chip];
				
				if(!ispointInquadrangle(CHIP[chip][i].XValue, CHIP[chip][i].YValue, point[chip], xyRange))
				{
					CHIP[chip][i].Result = false;
					if(!CHIP[chip][i].Continue)
					{
						failItem[chip] = i;
						return false;
					}
				}
				else
				{
					CHIP[chip][i].Result = true;
					HandleStatisticValue(&CHIP[chip][i].total_X, &CHIP[chip][i].max_X, &CHIP[chip][i].min_X, CHIP[chip][i].XValue);
					HandleStatisticValue(&CHIP[chip][i].total_Y, &CHIP[chip][i].max_Y, &CHIP[chip][i].min_Y, CHIP[chip][i].YValue);
				}
			}
			else
			{
				CHIP[chip][i].XValue = 0;
				CHIP[chip][i].YValue = 0;
				
				CHIP[chip][i].Result = false;
				if(!CHIP[chip][i].Continue)
				{
					failItem[chip] = i;
					return false;
				}
			}
		}
		else if(0 == strcmp(str_item, "PWL"))
		{
			if(IFSaturated)
			{
				CHIP[chip][i].TestValue = g_dColorPara.fLp;//getPeakWL(1, false);
				if(HandleCalValue(chip, i))
				{
					HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
				}
				else
				{
					if(!CHIP[chip][i].Continue)
					{	
						failItem[chip] = i;
						return false;
					}
				}
			}
			else
			{
				CHIP[chip][i].TestValue = 0;
				if(!CHIP[chip][i].Continue)
				{	
					failItem[chip] = i;
					return false;
				}
			}
		}
		else if(0 == strcmp(str_item, "DVF"))
		{
			CHIP[chip][i].TestValue = getDVF(CHIP[chip][i].ICom, CHIP[chip][i].Delay);
			
			if(HandleCalValue(chip, i))
			{
				HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
			}
			else
			{
				if(!CHIP[chip][i].Continue)
				{	
					failItem[chip] = i;
					return false;
				}
			}
		}
		else if(0 == strcmp(str_item, "DeltaWL"))
		{
			if(IFSaturated)
			{
				CHIP[chip][i].TestValue = g_dColorPara.fLd;//getDeltaWL();
				
				if(HandleCalValue(chip, i))
				{
					HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
				}
				else
				{
					if(!CHIP[chip][i].Continue)
					{	
						failItem[chip] = i;
						return false;
					}
				}
			}
			else
			{
				CHIP[chip][i].TestValue = 0;
				if(!CHIP[chip][i].Continue)
				{	
					failItem[chip] = i;
					return false;
				}
			}
		}
		else if(0 == strcmp(str_item, "IF"))
		{
			CHIP[chip][i].TestValue = getIF(CHIP[chip][i].VCom, CHIP[chip][i].ICom, CHIP[chip][i].Delay);
			
			if(HandleCalValue(chip, i))
			{
				HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
			}
			else
			{
				if(!CHIP[chip][i].Continue)
				{	
					failItem[chip] = i;
					return false;
				}
			}
		}
		else if(0 == strcmp(str_item, "THY"))
		{
			CHIP[chip][i].TestValue = getTHY(CHIP[chip][i].VCom, CHIP[chip][i].ICom);
			
			if(HandleCalValue(chip, i))
			{
				HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
			}
			else
			{
				if(!CHIP[chip][i].Continue)
				{	
					failItem[chip] = i;
					return false;
				}
			}
		}
		else
		{
			if(IFSaturated)
			{
				if(!iftestXY[chip])
				{
					getXY();
					realx = getX();
					realy = getY();
					x[chip] = realx;
					y[chip] = realy;
					iftestXY[chip] = true;
				}	
			}

			if(0 == strcmp(str_item, "WL"))
			{
				if(IFSaturated)
				{
					if(0 == intWLSteps[chip])
					{
						CHIP[chip][i].TestValue = getWL_New(realx, realy);
					}	
					else
					{
						CHIP[chip][i].TestValue = getWL_5nm_New(realx, realy);
					}
					
					if(HandleCalValue(chip, i))
					{
						HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
					}
					else
					{
						if(!CHIP[chip][i].Continue)
						{	
							failItem[chip] = i;
							return false;
						}
					}
				}
				else
				{
					CHIP[chip][i].TestValue = 0;
					if(!CHIP[chip][i].Continue)
					{	
						failItem[chip] = i;
						return false;
					}
				}
			}

			else if(0 == strcmp(str_item, "PUR"))
			{		
				if(IFSaturated)
				{
					CHIP[chip][i].TestValue = g_dColorPara.fPur;//getPUR(realx, realy);
					
					if(HandleCalValue(chip, i))
					{
						HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
					}
					else
					{
						if(!CHIP[chip][i].Continue)
						{	
							failItem[chip] = i;
							return false;
						}
					}
				}
				else
				{
					CHIP[chip][i].TestValue = 0;
					if(!CHIP[chip][i].Continue)
					{	
						failItem[chip] = i;
						return false;
					}
				}
			}

			else if(0 == strcmp(str_item, "CCT"))
			{
				if(IFSaturated)
				{
					CHIP[chip][i].TestValue = g_dColorPara.fCCT;//getCCT(realx, realy);
					
					if(HandleCalValue(chip, i))
					{
						HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
					}
					else
					{
						if(!CHIP[chip][i].Continue)
						{	
							failItem[chip] = i;
							return false;
						}
					}
				}
				else
				{
					CHIP[chip][i].TestValue = 0;
					if(!CHIP[chip][i].Continue)
					{	
						failItem[chip] = i;
						return false;
					}
				}
			}

			else if(0 == strcmp(str_item, "CRI"))
			{
				if(IFSaturated)
				{
					CHIP[chip][i].TestValue = g_dColorPara.fRa;//getCRI(realx, realy);
					
					if(HandleCalValue(chip, i))
					{
						HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
					}
					else
					{
						if(!CHIP[chip][i].Continue)
						{	
							failItem[chip] = i;
							return false;
						}
					}
				}
				else
				{
					CHIP[chip][i].TestValue = 0;
					if(!CHIP[chip][i].Continue)
					{	
						failItem[chip] = i;
						return false;
					}
				}
			}
		}	
	}

	failItem[chip] = c[chip];
	return true;
}

bool KeepLight_test2(int chip)
{	
	CString str_item;
	bool IFSaturated = true;
	if(usespectrum[chip])
	{
		IFSaturated = testgetSpectrum(chip);
	}

	iftestXY[chip] = false;
	int i = 0;
	OpenLight(KeepLight[chip].Voltage, KeepLight[chip].Current);
	Delay(KeepLight[chip].Delay * 1000);
	for(i=0; i<c[chip]; i++)
	{
		str_item = "NULL";
		sscanf(CHIP[chip][i].TestItem, "%[^(]", str_item);
		if(0 == strcmp(str_item, "VF"))
		{
			CHIP[chip][i].TestValue = KeepLight_getVF(CHIP[chip][i].Delay);
			if(!getBering())
			{
				CHIP[chip][i].TestValue += systemset.VRoffset[chip];
			}

			if(HandleCalValue(chip, i))
			{
				HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
			}
			else
			{
				if(!CHIP[chip][i].Continue)
				{	
					failItem[chip] = i;
					return false;
				}
			}
		}
		else if(0 == strcmp(str_item, "IV"))
		{
			CHIP[chip][i].TestValue = getYbit(false, intOpticGain[chip], CHIP[chip][i].VCom,
				CHIP[chip][i].ICom, CHIP[chip][i].Delay, true);
			if(CHIP[chip][i].TestValue < 0)
			{
				CHIP[chip][i].TestValue = 0;
			}
			
			if(HandleCalValue(chip, i))
			{
				HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
			}
			else
			{
				if(!CHIP[chip][i].Continue)
				{	
					failItem[chip] = i;
					return false;
				}
			}
		}
		else if(0 == strcmp(str_item, "IE"))
		{
			CHIP[chip][i].TestValue = getOptics_IV(0, intIntegrationTime[chip]);
			
			if(HandleCalValue(chip, i))
			{
				HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
			}
			else
			{
				if(!CHIP[chip][i].Continue)
				{	
					failItem[chip] = i;
					return false;
				}
			}
		}
		else if(0 == strcmp(str_item, "LE"))
		{
			CHIP[chip][i].TestValue = getOptics_IV(2, intIntegrationTime[chip]);
			
			if(HandleCalValue(chip, i))
			{
				HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
			}
			else
			{
				if(!CHIP[chip][i].Continue)
				{	
					failItem[chip] = i;
					return false;
				}
			}
		}
		else if(0 == strcmp(str_item, "LV"))
		{
			CHIP[chip][i].TestValue = getOptics_IV(1, intIntegrationTime[chip]);
			
			if(HandleCalValue(chip, i))
			{
				HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
			}
			else
			{
				if(!CHIP[chip][i].Continue)
				{	
					failItem[chip] = i;
					return false;
				}
			}
		}
		
		else if(0 == strcmp(str_item, "XYZ"))
		{
			if(IFSaturated)
			{
				getXY();
				realx = getX();
				realy = getY();
				iftestXY[chip] = true;
				if(0 == CHIP[chip][i].Calway)
				{
					x[chip] = realx + CHIP[chip][i].CalParam2X;
					y[chip] = realy + CHIP[chip][i].CalParam2Y;
				}
				else if(1 == CHIP[chip][i].Calway)
				{
					x[chip] = realx * CHIP[chip][i].CalParam1X;
					y[chip] = realy * CHIP[chip][i].CalParam1Y;
				}
				else
				{
					x[chip] = realx * CHIP[chip][i].CalParam1X + CHIP[chip][i].CalParam2X;
					y[chip] = realy * CHIP[chip][i].CalParam1Y + CHIP[chip][i].CalParam2Y;
				}
				
				CHIP[chip][i].XValue = g_dColorPara.fx;//x[chip];
				CHIP[chip][i].YValue = g_dColorPara.fx;//y[chip];
				
				if(!ispointInquadrangle(CHIP[chip][i].XValue, CHIP[chip][i].YValue, point[chip], xyRange))
				{
					CHIP[chip][i].Result = false;
					if(!CHIP[chip][i].Continue)
					{
						failItem[chip] = i;
						return false;
					}
				}
				else
				{
					CHIP[chip][i].Result = true;
					HandleStatisticValue(&CHIP[chip][i].total_X, &CHIP[chip][i].max_X, &CHIP[chip][i].min_X, CHIP[chip][i].XValue);
					HandleStatisticValue(&CHIP[chip][i].total_Y, &CHIP[chip][i].max_Y, &CHIP[chip][i].min_Y, CHIP[chip][i].YValue);
				}
			}
			else
			{
				CHIP[chip][i].XValue = 0;
				CHIP[chip][i].YValue = 0;

				CHIP[chip][i].Result = false;
				if(!CHIP[chip][i].Continue)
				{
					failItem[chip] = i;
					return false;
				}
			}
		}
		else if(0 == strcmp(str_item, "PWL"))
		{
			if(IFSaturated)
			{
				CHIP[chip][i].TestValue = g_dColorPara.fLp;//getPeakWL(1, false);
				
				if(HandleCalValue(chip, i))
				{
					HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
				}
				else
				{
					if(!CHIP[chip][i].Continue)
					{	
						failItem[chip] = i;
						return false;
					}
				}
			}
			else
			{
				CHIP[chip][i].TestValue = 0;
				if(!CHIP[chip][i].Continue)
				{	
					failItem[chip] = i;
					return false;
				}
			}
		}
		else if(0 == strcmp(str_item, "IF"))
		{
			CHIP[chip][i].TestValue = KeepLight_getIF(CHIP[chip][i].Delay);
			
			if(HandleCalValue(chip, i))
			{
				HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
			}
			else
			{
				if(!CHIP[chip][i].Continue)
				{	
					failItem[chip] = i;
					return false;
				}
			}
		}
		else if(0 == strcmp(str_item, "DVF"))
		{
			CHIP[chip][i].TestValue = getDVF(CHIP[chip][i].ICom, CHIP[chip][i].Delay);
			
			if(HandleCalValue(chip, i))
			{
				HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
			}
			else
			{
				if(!CHIP[chip][i].Continue)
				{	
					failItem[chip] = i;
					return false;
				}
			}
		}
		else if(0 == strcmp(str_item, "DeltaWL"))
		{
			if(IFSaturated)
			{
				CHIP[chip][i].TestValue = g_dColorPara.fLd;//getDeltaWL();
				
				if(HandleCalValue(chip, i))
				{
					HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
				}
				else
				{
					if(!CHIP[chip][i].Continue)
					{	
						failItem[chip] = i;
						return false;
					}
				}
			}
			else
			{
				CHIP[chip][i].TestValue = 0;
				if(!CHIP[chip][i].Continue)
				{	
					failItem[chip] = i;
					return false;
				}
			}
		}
		else if(0 == strcmp(str_item, "THY"))
		{
			CHIP[chip][i].TestValue = getTHY(CHIP[chip][i].VCom, CHIP[chip][i].ICom);
			
			if(HandleCalValue(chip, i))
			{
				HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
			}
			else
			{
				if(!CHIP[chip][i].Continue)
				{	
					failItem[chip] = i;
					return false;
				}
			}
		}
		else
		{
			if(IFSaturated)
			{
				if(!iftestXY[chip])
				{
					getXY();
					realx = getX();
					realy = getY();
					x[chip] = realx;
					y[chip] = realy;
					iftestXY[chip] = true;
				}
			}
		
			
			if(0 == strcmp(str_item, "WL"))
			{
				if(IFSaturated)
				{
					if(0 == intWLSteps[chip])
					{
						CHIP[chip][i].TestValue = getWL_New(realx, realy);
					}	
					else
					{
						CHIP[chip][i].TestValue = getWL_5nm_New(realx, realy);
					}
					
					if(HandleCalValue(chip, i))
					{
						HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
					}
					else
					{
						if(!CHIP[chip][i].Continue)
						{	
							failItem[chip] = i;
							return false;
						}
					}
				}
				else
				{
					CHIP[chip][i].TestValue = 0;
					if(!CHIP[chip][i].Continue)
					{	
						failItem[chip] = i;
						return false;
					}
				}
			}

			else if(0 == strcmp(str_item, "PUR"))
			{	
				if(IFSaturated)
				{
					CHIP[chip][i].TestValue = g_dColorPara.fPur;//getPUR(realx, realy);
					
					if(HandleCalValue(chip, i))
					{
						HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
					}
					else
					{
						if(!CHIP[chip][i].Continue)
						{	
							failItem[chip] = i;
							return false;
						}
					}
				}
				else
				{
					CHIP[chip][i].TestValue = 0;
					if(!CHIP[chip][i].Continue)
					{	
						failItem[chip] = i;
						return false;
					}
				}
			}

			else if(0 == strcmp(str_item, "CCT"))
			{
				if(IFSaturated)
				{
					CHIP[chip][i].TestValue = g_dColorPara.fCCT;//getCCT(realx, realy);
					
					if(HandleCalValue(chip, i))
					{
						HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
					}
					else
					{
						if(!CHIP[chip][i].Continue)
						{	
							failItem[chip] = i;
							return false;
						}
					}
				}
				else
				{
					CHIP[chip][i].TestValue = 0;
					if(!CHIP[chip][i].Continue)
					{	
						failItem[chip] = i;
						return false;
					}
				}
			}

			else if(0 == strcmp(str_item, "CRI"))
			{
				if(IFSaturated)
				{
					CHIP[chip][i].TestValue = g_dColorPara.fRa;//getCRI(realx, realy);	
					
					if(HandleCalValue(chip, i))
					{
						HandleStatisticValue(&CHIP[chip][i].total, &CHIP[chip][i].max, &CHIP[chip][i].min, CHIP[chip][i].TestValue);
					}
					else
					{
						if(!CHIP[chip][i].Continue)
						{	
							failItem[chip] = i;
							return false;
						}
					}
				}
				else
				{
					CHIP[chip][i].TestValue = 0;
					if(!CHIP[chip][i].Continue)
					{	
						failItem[chip] = i;
						return false;
					}
				}
			}
		}	
	}
	CloseLight(1, 0);

	failItem[chip] = c[chip];
	return true;
}



//////////////////////////////////分级
//将与测试项目相同的分级项目挑选出来 进行一一对应  以便于直接进行分bin  免去判断过程
TESTTYPE *mappingChip[42];
int mappingBinArray[42];
int mappingnum = 0;
void Mappingtestlevel()
{
	CString str;
	int chip = 3;
	int cols[4];
	cols[0] = 0;
	cols[1] = columns[0];
	cols[2] = columns[0] + columns[1];
	cols[3] = columns[0] + columns[1] + columns[2];

	if(0 == intChip)
	{
		chip = 1;
	}
	else if((1 == intChip) || (2 == intChip) || (3 == intChip))
	{
		chip = 2;
	}
	else if((4 == intChip) || (5 == intChip))
	{
		chip = 3;
	}

	mappingnum = 0;

	for(int chipnum=0; chipnum<chip; chipnum++)
	{
		for(int i=0; i<c[chipnum]; i++)
		{
			for(int j=cols[chipnum]; j<cols[chipnum+1]; j+=2)
			{	
				sscanf(binArray.strBinArray[0][j], "%*[^-]-%s", str);
				if(0 == strcmp(CHIP[chipnum][i].TestItem, str))
				{
					mappingChip[mappingnum] = &CHIP[chipnum][i];
					mappingBinArray[mappingnum] = j;
					
					sscanf(CHIP[chipnum][i].TestItem, "%[^(]", str);
					if(0 == strcmp(str, "XYZ"))
					{	
						j += 6;
					}
					mappingnum++;					
				}
			}
		}
	}
}

int *CalculateBin(bool autotest)
{
	CString str_item;
	extern bool ifDead;
	extern int DeadLedBin[3];
	int *bin = (int *)malloc(sizeof(int)*2);
	bin[0] = intFailBin;
	bin[1] = 0;

	int i = 0;
	int chipnum = 3;
	if(0 == intChip)
	{
		chipnum = 1;
	}
	else if((1 == intChip) || (2 == intChip) || (3 == intChip))
	{
		chipnum = 2;
	}
	else if((4 == intChip) || (5 == intChip))
	{
		chipnum = 3;
	}

	if(ifDead)
	{
		bin[0] = DeadLedBin[0];
		binnum[bin[0]]++;
		bin[1] = searchMachineBin(bin[0], autotest);
		return bin;
	}
	//////////////////////////////首先判断是否在min max范围内 若不是  则bin为fail
	for(i=0; i<chipnum; i++)
	{
		for(int j=0; j<c[i]; j++)
		{
			if(!CHIP[i][j].Result)
			{
				bin[0] = CHIP[i][j].Fail;
				binnum[bin[0]]++;
				bin[1] = searchMachineBin(bin[0], autotest);
				return bin;
			}	
		}
	}

	ledStatistic.ledpassnum++;
	iftestpass = true;
	//////////////////////////////然后按分级表格分bin
	/////////判断是否设置了分级 若没设置分级 则bin为intfailbin
	if(binArray.strBinArray[0][0] == "")
	{
		bin[0] = intFailBin;
		binnum[bin[0]]++;
		bin[1] = searchMachineBin(bin[0], autotest);
		return bin;
	}
    //////////若设置了分级 判断是否有关于测试项目的分级  若无  则bin为intfailbin
	int levelstart = 0, levelend = 0;
	double min = 0, max = 0;
	int num = systemset.intMachineType + 1;
	
	for(i=1; i<num; i++)
	{	
		for(int j=0; j<mappingnum; j++)
		{
			if((binArray.strBinArray[i][mappingBinArray[j]] != "") 
				&& (binArray.strBinArray[i][mappingBinArray[j]] != "NULL"))
			{
				sscanf(mappingChip[j]->TestItem, "%[^(]", str_item);
				if(0 == strcmp(str_item, "XYZ"))
				{
					sngPOINT p[4];
					p[0].x = atof(binArray.strBinArray[i][mappingBinArray[j]]);
					p[0].y = atof(binArray.strBinArray[i][mappingBinArray[j]+1]);
					p[1].x = atof(binArray.strBinArray[i][mappingBinArray[j]+2]);
					p[1].y = atof(binArray.strBinArray[i][mappingBinArray[j]+3]);
					p[2].x = atof(binArray.strBinArray[i][mappingBinArray[j]+4]);
					p[2].y = atof(binArray.strBinArray[i][mappingBinArray[j]+5]);
					p[3].x = atof(binArray.strBinArray[i][mappingBinArray[j]+6]);
					p[3].y = atof(binArray.strBinArray[i][mappingBinArray[j]+7]);
					
					if(ispointInquadrangle(mappingChip[j]->XValue, mappingChip[j]->YValue, p, xyRange))
					{
						if(j == (mappingnum - 1))
						{
							bin[0] = i - 1;
							binnum[bin[0]]++;
							bin[1] = searchMachineBin(bin[0], autotest);
							return bin;
						}
					}
					else
					{
						j = mappingnum;
					}
				}
				else
				{
					min = atof(binArray.strBinArray[i][mappingBinArray[j]]);
					max = atof(binArray.strBinArray[i][mappingBinArray[j]+1]);
					if((mappingChip[j]->TestValue >= min) && (mappingChip[j]->TestValue <= max))
					{
						if(j == (mappingnum - 1))
						{
							bin[0] = i - 1;
							binnum[bin[0]]++;
							bin[1] = searchMachineBin(bin[0], autotest);
            				return bin;
						}
					}
					else
					{
						j = mappingnum;
					}
				}	
			}
		}
	}
	
	
//	bin = intFailBin;
	binnum[bin[0]]++;
	bin[1] = searchMachineBin(bin[0], autotest);
	return bin;
}

int searchMachineBin(int bin, bool autotest)
{
	if(!autotest)
	{
		return bin;
	}
	else
	{
		int i = 0;
		
		for(i=0; i<systemset.intMachineType; i++)
		{
			if((binBox[i][0] == bin) && (binBox[i][1] < MaxLedNum) && (binBox[i][1] > 0))
			{
				if(ifbinboxExist(i))
				{
					binBox[i][1]++;
					return i;
				}
			}
		}
		
		for(i=0; i<systemset.intMachineType; i++)
		{
			if((binBox[i][1] == 0) && ifbinboxExist(i))
			{
				binBox[i][0] = bin;
				binBox[i][1]++;
				return i;
			}
		}
		
		return 80;
	}
	
	return 80;
}

bool ifbinboxExist(int binbox)
{
	int outboxnum = NewBoxStatusArray.GetSize();
	int num = 0;

	for(int i=0; i<outboxnum; i++)
	{
		num = NewBoxStatusArray.GetAt(i); 
		if(binbox == num)
		{
			return false;
		}
	}

	return true;
}

//判断菜单项是否选中
bool IfMenuCheck(CMenu *m_menu, UINT nID)
{	
	MENUITEMINFO info;
	info.cbSize = sizeof(MENUITEMINFO);
	info.fMask = MIIM_STATE;
	m_menu->GetMenuItemInfo(nID, &info);
	if(info.fState & MF_CHECKED)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//////////////////////XY打靶分级部分处理
extern CList<XYLEVELItem, XYLEVELItem> levelItem[3];
extern XYLEVELItem TotalRangeItem[3];
extern CList<XYLEVELItem, XYLEVELItem> tempBigRect[3];
extern CList<POSITION, POSITION> InRectPos;
//////////分级初始化
/*
extern CList<XYLEVELItem, XYLEVELItem> bigRect[3];
bool InitBigRect(int chip)
{
	XYLEVELItem item;
	tempBigRect[chip].RemoveAll();

	POSITION pos = bigRect[chip].GetHeadPosition();
	while(pos != NULL)
	{
		item = bigRect[chip].GetNext(pos);
		tempBigRect[chip].AddTail(item);
	}
	return true;
}

bool SetBigRect(int chip)
{
	XYLEVELItem item;
	bigRect[chip].RemoveAll();

	POSITION pos = tempBigRect[chip].GetHeadPosition();
	while(pos != NULL)
	{
		item = tempBigRect[chip].GetNext(pos);
		bigRect[chip].AddTail(item);
	}
	return true;
}
*/
bool InitXYLEVELItem(int chip)
{
	XYLEVELItem item;
	CString str, str_item;
	int i = 0, j = 0;
	int cols[4];

	cols[0] = 0;
	cols[1] = columns[0];
	cols[2] = columns[0] + columns[1];
	cols[3] = columns[0] + columns[1] + columns[2];

	levelItem[chip].RemoveAll();
	
	for(i=cols[chip]; i<cols[chip+1]; i++)
	{
		sscanf(binArray.strBinArray[0][i], "%*[^-]-%[^(]", str_item);
		if(0 == strcmp(str_item, "XYZ"))
		{
			for(j = 1; j<=systemset.intMachineType; j++)
			{
				if(binArray.strBinArray[j][i] != "")
				{
					item.x[0] = atof(binArray.strBinArray[j][i]);
					item.y[0] = atof(binArray.strBinArray[j][i+1]);
					item.x[1] = atof(binArray.strBinArray[j][i+2]);
					item.y[1] = atof(binArray.strBinArray[j][i+3]);
					item.x[2] = atof(binArray.strBinArray[j][i+4]);
					item.y[2] = atof(binArray.strBinArray[j][i+5]);
					item.x[3] = atof(binArray.strBinArray[j][i+6]);
					item.y[3] = atof(binArray.strBinArray[j][i+7]);
			
					item.num = 0;
			
					if(!ifExistRect(chip, item))
					{
						levelItem[chip].AddTail(item);
					}
				}
			}
			SetOrderNum(chip);
			return true;
		}
	}
	
	return true;
}

///////计算要显示的当前分级图形bin号
int CalculateShootBin()
{
	XYLEVELItem item, item2;
	int i = 0;
	int colsnum;
	int num = 0;
	CString str_item, string;
	
	for(i=0; i<columns[0]; i++)
	{
		sscanf(binArray.strBinArray[0][i], "%*[^-]-%[^(]", str_item);
		if(0 == strcmp(str_item, "XYZ"))
		{
			colsnum = i;
			i = columns[0];
		}
	}

	for(i=0; i<102; i++)
	{
		showShootBin[0][i] = "NULL";
		showShootBin[0][i] = "";
	}
	string = "";

	POSITION pos = levelItem[0].GetHeadPosition();
	while(pos != NULL)
	{
		item = levelItem[0].GetAt(pos);
		for(i=1; i<=systemset.intMachineType; i++)
		{
			if(binArray.strBinArray[i][colsnum] != "")
			{
				item2.x[0] = atof(binArray.strBinArray[i][colsnum]);
				item2.y[0] = atof(binArray.strBinArray[i][colsnum+1]);
				item2.x[1] = atof(binArray.strBinArray[i][colsnum+2]);
				item2.y[1] = atof(binArray.strBinArray[i][colsnum+3]);
				item2.x[2] = atof(binArray.strBinArray[i][colsnum+4]);
				item2.y[2] = atof(binArray.strBinArray[i][colsnum+5]);
				item2.x[3] = atof(binArray.strBinArray[i][colsnum+6]);
				item2.y[3] = atof(binArray.strBinArray[i][colsnum+7]);
				
				if(ifRectSame(item, item2))
				{
					string.Format("%d, ", i-1);
					num = levelItem[0].GetAt(pos).num;
					showShootBin[0][num] += string;
				}
			}
		}
		levelItem[0].GetNext(pos);
	}

	return colsnum;
}

bool CSVLevel_InitXYLEVELItem(int chip)
{
	XYLEVELItem item;
	CString str, str_item;
	int i = 0, j = 0;
	int cols[4];
	
	cols[0] = 0;
	cols[1] = csvcolumns[0];
	cols[2] = csvcolumns[0] + csvcolumns[1];
	cols[3] = csvcolumns[0] + csvcolumns[1] + csvcolumns[2];
	
	levelItem[chip].RemoveAll();
	
	for(i=cols[chip]; i<cols[chip+1]; i++)
	{
		sscanf(level_binArray.strBinArray[0][i], "%*[^-]-%[^(]", str_item);
		if(0 == strcmp(str_item, "XYZ"))
		{
			for(j = 1; j<=systemset.intMachineType; j++)
			{
				if(level_binArray.strBinArray[j][i] != "")
				{
					item.x[0] = atof(level_binArray.strBinArray[j][i]);
					item.y[0] = atof(level_binArray.strBinArray[j][i+1]);
					item.x[1] = atof(level_binArray.strBinArray[j][i+2]);
					item.y[1] = atof(level_binArray.strBinArray[j][i+3]);
					item.x[2] = atof(level_binArray.strBinArray[j][i+4]);
					item.y[2] = atof(level_binArray.strBinArray[j][i+5]);
					item.x[3] = atof(level_binArray.strBinArray[j][i+6]);
					item.y[3] = atof(level_binArray.strBinArray[j][i+7]);
					
					item.num = 0;

					if(!ifExistRect(chip, item))
					{
						levelItem[chip].AddTail(item);
					}	
				}
			}
			SetOrderNum(chip);
			return true;
		}
	}
	
	return true;
}

void DrawRect(CPoint *p, CDC *MemDC)
{
	MemDC->MoveTo(p[0]);
	MemDC->LineTo(p[1]);
				
	MemDC->MoveTo(p[1]);
	MemDC->LineTo(p[2]);
				
	MemDC->MoveTo(p[2]);
	MemDC->LineTo(p[3]);
				
	MemDC->MoveTo(p[3]);
	MemDC->LineTo(p[0]);
}

bool CoverExistLevel(int bin, int chip)
{ 
	XYLEVELItem item;
	POSITION pos, pos2;
	pos = levelItem[chip].GetHeadPosition();

	while(pos != NULL)
	{
		pos2 = pos;
		item = levelItem[chip].GetNext(pos);
		if(item.num == bin)
		{
			levelItem[chip].RemoveAt(pos2);
			return true;
		}
	}
	return false;
}

bool InsertLevel(int bin, int chip)
{
	XYLEVELItem item;
	POSITION pos, pos2, pos3;
	pos = levelItem[chip].GetHeadPosition();
	pos3 = NULL;
	while(pos != NULL)
	{
		pos2 = pos;
		item = levelItem[chip].GetNext(pos);
		if((pos2 != pos3) && (item.num == bin))
		{
			bin ++;
			levelItem[chip].GetAt(pos2).num = bin;
			pos = levelItem[chip].GetHeadPosition();
			pos3 = pos2;
		}
	}
	return false;
}

bool HandleAddLevelStyle(int style, int bin, int chip)
{
	if(0 == style)
	{
		CoverExistLevel(bin, chip);
	}
	else if(1 == style)
	{
		InsertLevel(bin, chip);
	}
	return true;
}


bool compareXYLEVELItem(XYLEVELItem item1, XYLEVELItem item2)
{
	for(int i=0; i<4; i++)
	{
		if((item1.x[i] >= (item2.x[i] + 0.01)) || (item1.x[i] <= (item2.x[i] - 0.01))
		   || (item1.y[i] >= (item2.y[i] + 0.01)) || (item1.y[i] <= (item2.y[i] - 0.01)))
		{
			return false;
		}
	}
	return true;
}

bool ifExistRect(int chip, XYLEVELItem item1)
{
	XYLEVELItem item;
	POSITION pos;
	pos = levelItem[chip].GetHeadPosition();
	while(pos != NULL)
	{
		item = levelItem[chip].GetNext(pos);
		if(ifRectSame(item1, item))
		{
			return true;
		}
	}

	return false;
}

bool ifRectSame(XYLEVELItem item1, XYLEVELItem item2)
{
	for(int i=0; i<4; i++)
	{
		if((item1.x[i] != item2.x[i]) || (item1.y[i] != item2.y[i]))
		{
			return false;
		}
	}
	return true;
}

/////////////////////////查找相同的图形
extern POSITION selectpos[3];

bool IfSameRectExist(XYLEVELItem item, int chip)
{
	XYLEVELItem item2;
	POSITION pos;
	pos = levelItem[chip].GetHeadPosition();

	while(pos != NULL)
	{
		selectpos[chip] = pos;
		item2 = levelItem[chip].GetNext(pos);
		if(compareXYLEVELItem(item, item2))
		{
			return true;
		}
	}

	selectpos[chip] = NULL;
	return false;
}

bool IfExistXYLEVELItem(XYLEVELItem item1, int chip)
{
	POSITION pos;
	XYLEVELItem item2;
	pos = levelItem[chip].GetHeadPosition();
	while(pos != NULL)
	{
		item2 = levelItem[chip].GetNext(pos);
		if(compareXYLEVELItem(item1, item2))
		{
			return true;
		}
	}

	return false;
}

bool SetOrderNum(int chip)
{
	int num = 0;
	POSITION pos;
	pos = levelItem[chip].GetHeadPosition();
	while(pos != NULL)
	{
		if(levelItem[chip].GetAt(pos).num >= 0)
		{
			levelItem[chip].GetNext(pos).num = num++;
		}
	}

	return true;
}

int CountNum(int chip)
{
	POSITION pos;
	pos = levelItem[chip].GetHeadPosition();
	int num = 0;
		
	while(pos != NULL)
	{
		if(levelItem[chip].GetNext(pos).num >= 0)
		{
			num++;
		}
	}

	return num;
}

bool IfExistSameBig(XYLEVELItem item1, int chip)
{
	POSITION pos;
	XYLEVELItem item2;
	pos = tempBigRect[chip].GetHeadPosition();
	while(pos != NULL)
	{
		item2 = tempBigRect[chip].GetNext(pos);
		if(compareXYLEVELItem(item1, item2))
		{
			return true;
		}
	}

	return false;
}

bool SetRange(int chip)
{
	for(int i=0; i<4; i++)
	{
		point[chip][i].x = TotalRangeItem[chip].x[i];
		point[chip][i].y = TotalRangeItem[chip].y[i];
	}
	return true;
}

bool GetRange(int chip)
{
	for(int i=0; i<4; i++)
	{
		TotalRangeItem[chip].x[i] = point[chip][i].x;
		TotalRangeItem[chip].y[i] = point[chip][i].y;
	}
	return true;
}

bool ifRectInRect(XYLEVELItem Rect, XYLEVELItem item, double range)
{
	int i = 0;
	double x = 0, y = 0;
	sngPOINT p[4];
	extern bool setOrder;

	if(setOrder)
	{
		p[0].x = Rect.x[0] - range;
		p[0].y = Rect.y[0] + range;
		
		p[1].x = Rect.x[1] + range;
		p[1].y = Rect.y[1] + range;
		
		p[2].x = Rect.x[2] + range;
		p[2].y = Rect.y[2] - range;
		
		p[3].x = Rect.x[3] - range;
		p[3].y = Rect.y[3] - range;
	}
	else
	{
		p[0].x = Rect.x[0] - range;
		p[0].y = Rect.y[0] - range;
		
		p[1].x = Rect.x[1] + range;
		p[1].y = Rect.y[1] - range;
		
		p[2].x = Rect.x[2] + range;
		p[2].y = Rect.y[2] + range;
		
		p[3].x = Rect.x[3] - range;
		p[3].y = Rect.y[3] + range;
	}
	

	for(i=0; i<4; i++)
	{
		x = item.x[i];
		y = item.y[i];
		if(!ispointInquadrangle(x, y, p, xyRange))
		{
			return false;
		}
	}
	return true;
}

bool DelAllBigInRect(int chip, XYLEVELItem Rect)
{
	XYLEVELItem item;
	bool clear = false;
	
	POSITION pos;
	pos = tempBigRect[chip].GetHeadPosition();
	
	while(pos != NULL)
	{ 
		item = tempBigRect[chip].GetAt(pos);
		if(ifRectInRect(Rect, item, 0.0005))
		{
			tempBigRect[chip].RemoveAt(pos);
			pos = tempBigRect[chip].GetHeadPosition();
		}
		else
		{
			tempBigRect[chip].GetNext(pos);
		}	
	}
	
	return true;
}

bool DelAllInRect(int chip, XYLEVELItem Rect)
{
	XYLEVELItem item;
	bool clear = false;
	
	POSITION pos;
	pos = levelItem[chip].GetHeadPosition();
	
	while(pos != NULL)
	{ 
		item = levelItem[chip].GetAt(pos);
		if(ifRectInRect(Rect, item, 0.0005))
		{
			levelItem[chip].RemoveAt(pos);
			pos = levelItem[chip].GetHeadPosition();
		}
		else
		{
			levelItem[chip].GetNext(pos);
		}	
	}
	
	return true;
}

bool FindInRect(int chip, XYLEVELItem Rect)
{
	XYLEVELItem item;
	bool clear = false;
	
	POSITION pos;
	pos = levelItem[chip].GetHeadPosition();
	
	InRectPos.RemoveAll();
	while(pos != NULL)
	{ 
		item = levelItem[chip].GetAt(pos);
		if(ifRectInRect(Rect, item, 0.0005))
		{
			InRectPos.AddTail(pos);
		}
		levelItem[chip].GetNext(pos);	
	}
	return true;
}

bool MoveRects(int chip, double x, double y)
{
	POSITION pos, position;
	pos = InRectPos.GetHeadPosition();

	while(pos != NULL)
	{ 
		position = InRectPos.GetAt(pos);
		
		for(int i=0; i<4; i++)
		{
			levelItem[chip].GetAt(position).x[i] += x;
			levelItem[chip].GetAt(position).y[i] += y;
		}
		
		InRectPos.GetNext(pos);	
	}
	return true;
}

////////////判断查找大分级区域
int FigureLevelLocation(XYLEVELItem item1, XYLEVELItem item2, bool way)
{
	double result = 1;

	if(way)
	{	
		result = (item1.y[1]-item1.y[0])*(item2.x[1]-item2.x[0]) - (item2.y[1]-item2.y[0])*(item1.x[1]-item1.x[0]);
		if((result > -0.00005) && (result < 0.00005))
		{
			result = (item1.y[2]-item1.y[3])*(item2.x[2]-item2.x[3]) - (item2.y[2]-item2.y[3])*(item1.x[2]-item1.x[3]);
			
			if((result > -0.00005) && (result < 0.00005))
			{
				if((item1.x[1] == item2.x[0]) && (item1.y[1] == item2.y[0]))
				{	
					if ((item1.x[2] == item2.x[3]) && (item1.y[2] == item2.y[3]))
					{
						result = (item1.x[1] - item1.x[0]) - (item2.x[1] - item2.x[0]);
						if((result > -0.0002) && (result < 0.0002))
						{
							return 3;
						}	
					}

					return 2;
				}

				return 1;
			}
		}
	}
	else
	{	
		result = (item1.y[3]-item1.y[0])*(item2.x[3]-item2.x[0]) - (item2.y[3]-item2.y[0])*(item1.x[3]-item1.x[0]);
		
		if((result > -0.00005) && (result < 0.00005))
		{
			result = (item1.y[2]-item1.y[1])*(item2.x[2]-item2.x[1]) - (item2.y[2]-item2.y[1])*(item1.x[2]-item1.x[1]);
			
			if((result > -0.00005) && (result < 0.00005))
			{
				if((item1.x[3] == item2.x[0]) && (item1.y[3] == item2.y[0]))
				{
					if((item1.x[2] == item2.x[1]) && (item1.y[2] == item2.y[1]))
					{
						result = (item1.y[3] - item1.y[0]) - (item2.y[3] - item2.y[0]);
						if((result > -0.0002) && (result < 0.0002))
						{
							return 3;
						}
					}
					
					return 2;
				}
				
				return 1;
			}
		}
	}
	
	return 0;
}

bool ifExistBigRect(int chip, XYLEVELItem item)
{
	XYLEVELItem Range;
	POSITION pos = tempBigRect[chip].GetHeadPosition();
	
	while(pos != NULL)
	{
		Range = tempBigRect[chip].GetNext(pos);
		if(ifRectInRect(Range, item, 0.0005))
		{
			return true;
		}
	}
	return false;
}

extern CList<POSITION, POSITION> smallRectPos[3];
XYLEVELItem FindTotalBigRect(int chip, XYLEVELItem item, POSITION position, bool prev)
{
	XYLEVELItem item0, item1, item2;
	XYLEVELItem Range;
	XYLEVELItem Corner[4];
	POSITION pos, pos0, pos1, save;
	CList<POSITION, POSITION> savePos;

	int num = 0;
	bool count = true;
	bool way;//图形分级方式, true为横分, false为竖分
	int i;
	bool line = true;

	pos = position;
	if(prev)
	{
		levelItem[chip].GetPrev(position);
	}

	for(i=0; i<4; i++)
	{
		Corner[i] = item;
	}
	
	while(pos != NULL)
	{	
		if(0 == num)   //////判断第一个
		{
			pos0 = pos;
			item2 = levelItem[chip].GetNext(pos);
			
			if(line)
			{
				if(3 == FigureLevelLocation(item, item2, true))
				{
					way = true;
					Corner[1] = item2;
					Corner[2] = item2;
					
					num++;
					smallRectPos[chip].AddTail(position);
					smallRectPos[chip].AddTail(pos0);
				}
				else if(pos == NULL)
				{
					line = false;
					levelItem[chip].GetNext(position);
					pos = position;
				}
			}
			else if(3 == FigureLevelLocation(item, item2, false))
			{
				Corner[2] = item2;
				Corner[3] = item2;
				
				smallRectPos[chip].AddTail(position);
				smallRectPos[chip].AddTail(pos0);
				pos = NULL;
			}
		}
		else  ////存在连续大范围 判断开始
		{
			if(count)  ////开始对单行或单列的分级计数
			{
				item1 = item2;
				pos0 = pos;
				item2 = levelItem[chip].GetNext(pos);
				
				if(3 == FigureLevelLocation(item1, item2, way))    //////计数
				{
					num++;
					smallRectPos[chip].AddTail(pos0);
					if(way)
					{
						Corner[1] = item2;
						Corner[2] = item2;
						Corner[3] = Corner[0];
					}
					else
					{
						Corner[1] = Corner[0];
						Corner[2] = item2;
						Corner[3] = item2;
					}
				} 
				else
				{
					if(3 == FigureLevelLocation(Corner[0], item2, !way))    //////发现换行，计数结束
					{
						count = false;
					}
					else
					{
						pos = NULL;
					}

					if(way)
					{
						Corner[1] = item1;
						Corner[2] = item1;
						Corner[3] = Corner[0];
					}
					else
					{
						Corner[1] = Corner[0];
						Corner[2] = item1;
						Corner[3] = item1;
					}
				}
			}
			else  /////计数结束，开始搜索整个大小
			{
				item0 = item2;
				savePos.RemoveAll();
				for(i=0; i<num; i++)
				{	
					item1 = item2;
					savePos.AddTail(pos);
					item2 = levelItem[chip].GetNext(pos);
					
					if(FigureLevelLocation(item1, item2, way) != 3)
					{
						pos = NULL;
						num = 0;
					}
				}
				
				if(pos == NULL)
				{
					smallRectPos[chip].AddTail(pos0);
					pos1 = savePos.GetHeadPosition();
					while(pos1 != NULL)
					{
						save = savePos.GetNext(pos1);
						smallRectPos[chip].AddTail(save);
					}

					if(way)
					{
						Corner[2] = item2;
						Corner[3] = item0;
					}
					else
					{
						Corner[2] = item2;
						Corner[1] = item0;
					}
					
					num = 0;
				}
				
				if(num != 0)  /////////一行或一列判断结束
				{
					smallRectPos[chip].AddTail(pos0);
					pos1 = savePos.GetHeadPosition();
					while(pos1 != NULL)
					{
						save = savePos.GetNext(pos1);
						smallRectPos[chip].AddTail(save);
					}

					item1 = item2;
					pos0 = pos;
					item2 = levelItem[chip].GetNext(pos);
						
					if(FigureLevelLocation(item0, item2, !way) != 3)
					{	
						if(way)
						{
							Corner[2] = item1;
							Corner[3] = item0;
						}
						else
						{
							Corner[2] = item1;
							Corner[1] = item0;
						}
						
						pos = NULL;
					}
				}
			}
		}	
	}
	
	for(i=0; i<4; i++)
	{
		Range.x[i] = Corner[i].x[i];
		Range.y[i] = Corner[i].y[i];
	}
	
	return Range;
}

bool ifSmallRect(int chip, POSITION pos)
{
	POSITION pos0, posValue;

	pos0 = smallRectPos[chip].GetHeadPosition();
	while(pos0 != NULL)
	{
		posValue = smallRectPos[chip].GetNext(pos0);
		if(posValue == pos)
		{
			return true;
		}
	}
	return false;
}

bool SearchRange(int chip)
{
	tempBigRect[chip].RemoveAll();
	smallRectPos[chip].RemoveAll();

	XYLEVELItem item0, item1, item2;
	XYLEVELItem Range;
	XYLEVELItem Corner[4];
	int num = 0;
	bool count = true;
	bool way;//图形分级方式, true为横分, false为竖分
	int i, j;
	int result1 = 0, result2 = 0;

	POSITION pos = levelItem[chip].GetHeadPosition();

	if(pos != NULL)
	{
		item1 = levelItem[chip].GetNext(pos);
	}
	else
	{
		return false;
	}

	if(pos == NULL)
	{
		Range = item1;
		tempBigRect[chip].AddTail(Range);
		return true;
	}

	for(i=0; i<4; i++)
	{
		Corner[i] = item1;
	}

	while(pos != NULL)
	{	
		if(0 == num)   ////// 1. 判断第一个
		{
			if(!ifExistBigRect(chip, item1))
			{
				item2 = levelItem[chip].GetAt(pos);
				
				result1 = FigureLevelLocation(item1, item2, true);
				result2 = FigureLevelLocation(item1, item2, false);
				
				if(3 == result1)
				{
					way = true;
					num++;
				}
				else if(3 == result2)
				{
					way = false;
					num++;
				}
				else
				{
					if((0 == result1) && (0 ==result2))
					{
						tempBigRect[chip].AddTail(item1);
						Corner[0] = item2;
						num = 0;
					}
					else 
					{
						if((result1 != 2) && (result2 != 2))
						{
							item1 = FindTotalBigRect(chip, item1, pos, true);
							Corner[0] = item1;
							
							result1 = FigureLevelLocation(item1, item2, true);
							result2 = FigureLevelLocation(item1, item2, false);
							
							if(3 == result1)
							{
								way = true;
								num++;
							}
							else if(3 == result2)
							{
								way = false;
								num++;
							}
							else if((result1 != 2) && (result2 != 2))
							{
								if(!ifExistBigRect(chip, item1))
								{
									tempBigRect[chip].AddTail(item1);
								}
								
								Corner[0] = item2;
								num = -1;
							}
						}
						
						if(0 == num)
						{
							item2 = FindTotalBigRect(chip, item2, pos, false);
							result1 = FigureLevelLocation(item1, item2, true);
							result2 = FigureLevelLocation(item1, item2, false);
							
							if(3 == result1)
							{
								way = true;
								num++;
							}
							else if(3 == result2)
							{
								way = false;
								num++;
							}
							else
							{
								if(!ifExistBigRect(chip, item1))
								{
									tempBigRect[chip].AddTail(item1);
								}
								
								Corner[0] = levelItem[chip].GetAt(pos);
								num = 0;
							}
						}
						else if(-1 == num)
						{
							num = 0;
						}
					}
				}
			}
			
			item1 = item2;
			levelItem[chip].GetNext(pos);
			
			if((pos == NULL) && (num != 0))
			{
				if(way)
				{
					Corner[3] = Corner[0];
					Corner[1] = item1;
					Corner[2] = item1;
				}
				else
				{
					Corner[1] = Corner[0];
					Corner[2] = item1;
					Corner[3] = item1;
				}
				
				for(i=0; i<4; i++)
				{
					Range.x[i] = Corner[i].x[i];
					Range.y[i] = Corner[i].y[i];
				}
				
				if(!ifExistBigRect(chip, Range))
				{
					tempBigRect[chip].AddTail(Range);
				}
			}
		}
		else  //// 2. 存在连续大范围 判断开始
		{
			if(count)  //// 2.1 开始对单行或单列的分级计数
			{
				item2 = levelItem[chip].GetAt(pos);
				result1 = FigureLevelLocation(item1, item2, way);
				result2 = FigureLevelLocation(Corner[0], item2, !way);
				
				if(3 == result1)    //////计数
				{
					num++;
				}
				else
				{
					if(way)
					{
						Corner[1] = item1;
						Corner[2] = item1;
						Corner[3] = Corner[0];
					}
					else
					{
						Corner[1] = Corner[0];
						Corner[2] = item1;
						Corner[3] = item1;
					}

					for(i=0; i<4; i++)
					{
						Range.x[i] = Corner[i].x[i];
						Range.y[i] = Corner[i].y[i];
					}

					if(3 == result2)    //////发现换行，计数结束
					{	
						count = false;
					}
					else if((result1 != 2) && (result2 != 2))   //////图形搜索结束
					{
						tempBigRect[chip].AddTail(Range);	
						Corner[0] = item2;
						num = 0;
					}
					else    //////////查找大范围后，再次判断
					{
						item2 = FindTotalBigRect(chip, item2, pos, false);
						
						result1 = FigureLevelLocation(item1, item2, way);
						result2 = FigureLevelLocation(Corner[0], item2, !way);
						
						if(3 == result1)   //////计数
						{
							num++;
						}
						else if(3 == result2)   ////////发现换行，计数结束	
						{
							count = false;
						}
						else   /////查找大范围后依旧不连续，图形搜索结束
						{
							tempBigRect[chip].AddTail(Range);	
							Corner[0] = levelItem[chip].GetAt(pos);
							num = 0;
						}
					}
				}

				item1 = item2;
				levelItem[chip].GetNext(pos);
				if((pos == NULL) && (num != 0))
				{
					if(way)
					{
						Corner[1] = item1;
						Corner[2] = item1;
						Corner[3] = Corner[0];
					}
					else
					{
						Corner[1] = Corner[0];
						Corner[2] = item1;
						Corner[3] = item1;
					}
					
					for(i=0; i<4; i++)
					{
						Range.x[i] = Corner[i].x[i];
						Range.y[i] = Corner[i].y[i];
					}
					
					tempBigRect[chip].AddTail(Range);	
				}
			}
			else  ///// 2.2 计数结束，开始搜索整个大小
			{
				item0 = item1;
				for(i=0; i<num; i++)  /////// 2.2.1 判断一整行
				{	
					item2 = levelItem[chip].GetAt(pos);
					result1 = FigureLevelLocation(item1, item2, way);
					if((0 == result1) || (1 == result1))
					{
						tempBigRect[chip].AddTail(Range);	
						Corner[0] = item0;
						num = 0;
						count = true;
						item2 = item0;
						for(int a=0; a<=i; a++)
						{
							levelItem[chip].GetPrev(pos);
						}
					}
					else if(2 == result1)
					{
						item2 = FindTotalBigRect(chip, item2, pos, false);
						result1 = FigureLevelLocation(item1, item2, way);
						if(result1 != 3)
						{
							tempBigRect[chip].AddTail(Range);	
							Corner[0] = item0;
							num = 0;
							count = true;
							item2 = item0;
							for(int a=0; a<=i; a++)
							{
								levelItem[chip].GetPrev(pos);
							}
						}
					}
					
					item1 = item2;
					levelItem[chip].GetNext(pos);
					
					if(pos == NULL)
					{
						if(way)
						{
							Corner[2] = item1;
							Corner[3] = item0;
						}
						else
						{
							Corner[2] = item1;
							Corner[1] = item0;
						}
						
						for(j=0; j<4; j++)
						{
							Range.x[j] = Corner[j].x[j];
							Range.y[j] = Corner[j].y[j];
						}
						
						tempBigRect[chip].AddTail(Range);	
						num = 0;
					}
				}
				
				if(num != 0)  ///////// 2.2.2 一行或一列判断结束，判断是否有下一行
				{
					if(way)
					{
						Corner[2] = item1;
						Corner[3] = item0;
					}
					else
					{
						Corner[2] = item1;
						Corner[1] = item0;
					}
					
					for(j=0; j<4; j++)
					{
						Range.x[j] = Corner[j].x[j];
						Range.y[j] = Corner[j].y[j];
					}
					
					item2 = levelItem[chip].GetAt(pos);
					result1 = FigureLevelLocation(item0, item2, !way);
					
					if((0 == result1) || (1 == result1))
					{
						tempBigRect[chip].AddTail(Range);	
						Corner[0] = item2;
						num = 0;
						count = true;
					}
					else if(2 == result1)
					{
						item2 = FindTotalBigRect(chip, item2, pos, false);
						result1 = FigureLevelLocation(item0, item2, !way);
						if(result1 != 3)
						{
							tempBigRect[chip].AddTail(Range);	
							Corner[0] = levelItem[chip].GetAt(pos);
							num = 0;
							count = true;
						}
					}
					
					item1 = item2;
					levelItem[chip].GetNext(pos);
					
					if(pos == NULL)
					{	
						Range = item1;
						if(!ifExistBigRect(chip, Range))
						{
							tempBigRect[chip].AddTail(Range);	
						}
					}
				}
			}
		}	
	}
	
	return true;
}


////////////////////////字符串显示方式处理
CString ReformatString(CString str)
{
	CString str1, str2;
	int num = 0;
	int no;

	num = strlen(str);
	no = str.ReverseFind(TEXT('.'));
	if(no < 0)
	{
		return str;
	}
	str1 = str.Left(no);
	str2 = str.Right(num - no - 1);
	num = strlen(str2) - 1;
	if(num > 0)
	{
		for(int i=num; i>=0; i--)
		{
			no = str2.ReverseFind(TEXT('0'));
			if(no == i)
			{
				if(no == 0)
				{
					str = str1;
					return str;
				}
				else
				{
					str2 = str2.Left(no); 
				}
			}
			else
			{
				str = str1 + "." + str2;
				return str;
			}
		}
	}

	return str;
}

///////////////////色温线
double BlackXY[67][2];
bool InitBlackXY()
{
	BlackXY[0][0] = 0.2399, BlackXY[0][1] = 0.2341;
	BlackXY[1][0] = 0.2426, BlackXY[1][1] = 0.2381;
	BlackXY[2][0] = 0.2456, BlackXY[2][1] = 0.2425;
	BlackXY[3][0] = 0.2489, BlackXY[3][1] = 0.2472;
	BlackXY[4][0] = 0.2525, BlackXY[4][1] = 0.2523;
	
	BlackXY[5][0] = 0.2565, BlackXY[5][1] = 0.2577;
	BlackXY[6][0] = 0.2607, BlackXY[6][1] = 0.2634;
	BlackXY[7][0] = 0.2653, BlackXY[7][1] = 0.2693;
	BlackXY[8][0] = 0.2701, BlackXY[8][1] = 0.2755;
	BlackXY[9][0] = 0.2752, BlackXY[9][1] = 0.2818;
	
	BlackXY[10][0] = 0.2806, BlackXY[10][1] = 0.2883;
	BlackXY[11][0] = 0.2863, BlackXY[11][1] = 0.2949;
	BlackXY[12][0] = 0.2921, BlackXY[12][1] = 0.3015;
	BlackXY[13][0] = 0.2982, BlackXY[13][1] = 0.3081;
	BlackXY[14][0] = 0.3045, BlackXY[14][1] = 0.3146;
	
	BlackXY[15][0] = 0.311, BlackXY[15][1] = 0.3211;
	BlackXY[16][0] = 0.3176, BlackXY[16][1] = 0.3275;
	BlackXY[17][0] = 0.3243, BlackXY[17][1] = 0.3338;
	BlackXY[18][0] = 0.3311, BlackXY[18][1] = 0.3399;
	BlackXY[19][0] = 0.338, BlackXY[19][1] = 0.3459;
	
	BlackXY[20][0] = 0.345, BlackXY[20][1] = 0.3516;
	BlackXY[21][0] = 0.3521, BlackXY[21][1] = 0.3571;
	BlackXY[22][0] = 0.3591, BlackXY[22][1] = 0.3624;
	BlackXY[23][0] = 0.3662, BlackXY[23][1] = 0.3674;
	BlackXY[24][0] = 0.3733, BlackXY[24][1] = 0.3722;
	
	BlackXY[25][0] = 0.3804, BlackXY[25][1] = 0.3767;
	BlackXY[26][0] = 0.3874, BlackXY[26][1] = 0.381;
	BlackXY[27][0] = 0.3944, BlackXY[27][1] = 0.385;
	BlackXY[28][0] = 0.4013, BlackXY[28][1] = 0.3887;
	BlackXY[29][0] = 0.4081, BlackXY[29][1] = 0.3921;
	
	BlackXY[30][0] = 0.4149, BlackXY[30][1] = 0.3953;
	BlackXY[31][0] = 0.4216, BlackXY[31][1] = 0.3982;
	BlackXY[32][0] = 0.4282, BlackXY[32][1] = 0.4009;
	BlackXY[33][0] = 0.4347, BlackXY[33][1] = 0.4033;
	BlackXY[34][0] = 0.4411, BlackXY[34][1] = 0.4055;
	
	BlackXY[35][0] = 0.4473, BlackXY[35][1] = 0.4074;
	
	BlackXY[36][0] = 0.4535, BlackXY[36][1] = 0.4091;
	BlackXY[37][0] = 0.4595, BlackXY[37][1] = 0.4105;
	BlackXY[38][0] = 0.4654, BlackXY[38][1] = 0.4113;
	BlackXY[39][0] = 0.4712, BlackXY[39][1] = 0.4128;
	BlackXY[40][0] = 0.4769, BlackXY[40][1] = 0.4137;
	
	BlackXY[41][0] = 0.4824, BlackXY[41][1] = 0.4143;
	BlackXY[42][0] = 0.4878, BlackXY[42][1] = 0.4148;
	BlackXY[43][0] = 0.4931, BlackXY[43][1] = 0.4151;
	BlackXY[44][0] = 0.4982, BlackXY[44][1] = 0.4153;
	BlackXY[45][0] = 0.5033, BlackXY[45][1] = 0.4153;
	
	BlackXY[46][0] = 0.5082, BlackXY[46][1] = 0.4151;
	BlackXY[47][0] = 0.5129, BlackXY[47][1] = 0.4149;
	BlackXY[48][0] = 0.5176, BlackXY[48][1] = 0.4145;
	BlackXY[49][0] = 0.5221, BlackXY[49][1] = 0.414;
	BlackXY[50][0] = 0.5266, BlackXY[50][1] = 0.4133;
	
	BlackXY[51][0] = 0.5309, BlackXY[51][1] = 0.4126;
	BlackXY[52][0] = 0.5351, BlackXY[52][1] = 0.4118;
	BlackXY[53][0] = 0.5391, BlackXY[53][1] = 0.4109;
	BlackXY[54][0] = 0.5431, BlackXY[54][1] = 0.4099;
	BlackXY[55][0] = 0.547, BlackXY[55][1] = 0.4089;
	
	BlackXY[56][0] = 0.5508, BlackXY[56][1] = 0.4078;
	BlackXY[57][0] = 0.5545, BlackXY[57][1] = 0.4066;
	BlackXY[58][0] = 0.5581, BlackXY[58][1] = 0.4054;
	BlackXY[59][0] = 0.5616, BlackXY[59][1] = 0.4041;
	BlackXY[60][0] = 0.565, BlackXY[60][1] = 0.4028;
	
	BlackXY[61][0] = 0.5683, BlackXY[61][1] = 0.4014;
	BlackXY[62][0] = 0.5715, BlackXY[62][1] = 0.4;
	BlackXY[63][0] = 0.5747, BlackXY[63][1] = 0.3986;
	BlackXY[64][0] = 0.5778, BlackXY[64][1] = 0.3972;
	BlackXY[65][0] = 0.5808, BlackXY[65][1] = 0.3957;
	
	BlackXY[66][0] = 0.5837, BlackXY[66][1] = 0.3942;
	
	return true;
}

////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//////新CIE坐标范围判断
bool BinCodeList()
{
	////偏蓝
	BinCodeName[0] = "Wa";
	BinCode[0].x[0] = 0.2545;
	BinCode[0].y[0] = 0.2245;
	BinCode[0].x[1] = 0.2633;
	BinCode[0].y[1] = 0.2410;
	BinCode[0].x[2] = 0.2545;
	BinCode[0].y[2] = 0.2480;
	BinCode[0].x[3] = 0.2450;
	BinCode[0].y[3] = 0.2290;

	BinCodeName[1] = "Wb";
	BinCode[1].x[0] = 0.2640;
	BinCode[1].y[0] = 0.2200;
	BinCode[1].x[1] = 0.2720;
	BinCode[1].y[1] = 0.2340;
	BinCode[1].x[2] = 0.2633;
	BinCode[1].y[2] = 0.2410;
	BinCode[1].x[3] = 0.2545;
	BinCode[1].y[3] = 0.2245;

	BinCodeName[2] = "Wc";
	BinCode[2].x[0] = 0.2633;
	BinCode[2].y[0] = 0.2410;
	BinCode[2].x[1] = 0.2720;
	BinCode[2].y[1] = 0.2575; 
	BinCode[2].x[2] = 0.2640;
	BinCode[2].y[2] = 0.2670;
	BinCode[2].x[3] = 0.2545;
	BinCode[2].y[3] = 0.2480; 

	BinCodeName[3] = "Wd";
	BinCode[3].x[0] = 0.2720;
	BinCode[3].y[0] = 0.2340;
	BinCode[3].x[1] = 0.2800;
	BinCode[3].y[1] = 0.2480;
	BinCode[3].x[2] = 0.2720;
	BinCode[3].y[2] = 0.2575;
	BinCode[3].x[3] = 0.2633;
	BinCode[3].y[3] = 0.2410;	 

	BinCodeName[4] = "We";
	BinCode[4].x[0] = 0.2720;
	BinCode[4].y[0] = 0.2575;
	BinCode[4].x[1] = 0.2808;
	BinCode[4].y[1] = 0.2740;
	BinCode[4].x[2] = 0.2735;
	BinCode[4].y[2] = 0.2860;
	BinCode[4].x[3] = 0.2640;
	BinCode[4].y[3] = 0.2670;

	BinCodeName[5] = "Wf";
	BinCode[5].x[0] = 0.2800;
	BinCode[5].y[0] = 0.2480;
	BinCode[5].x[1] = 0.2880;
	BinCode[5].y[1] = 0.2620;
	BinCode[5].x[2] = 0.2808;
	BinCode[5].y[2] = 0.2740;
	BinCode[5].x[3] = 0.2720;
	BinCode[5].y[3] = 0.2575;

	BinCodeName[6] = "Wg";
	BinCode[6].x[0] = 0.2808;
	BinCode[6].y[0] = 0.2740;
	BinCode[6].x[1] = 0.2895;
	BinCode[6].y[1] = 0.2905;
	BinCode[6].x[2] = 0.2830;
	BinCode[6].y[2] = 0.3050;
	BinCode[6].x[3] = 0.2735;
	BinCode[6].y[3] = 0.2860;

	BinCodeName[7] = "Wh";
	BinCode[7].x[0] = 0.2880;
	BinCode[7].y[0] = 0.2620;
	BinCode[7].x[1] = 0.2960;
	BinCode[7].y[1] = 0.2760;
	BinCode[7].x[2] = 0.2895;
	BinCode[7].y[2] = 0.2905;
	BinCode[7].x[3] = 0.2808;
	BinCode[7].y[3] = 0.2740;

	BinCodeName[8] = "86S(8200-9000K)";
	BinCode[8].x[0] = 0.2895;
	BinCode[8].y[0] = 0.2905;
	BinCode[8].x[1] = 0.2950;
	BinCode[8].y[1] = 0.2970;
	BinCode[8].x[2] = 0.2895;
	BinCode[8].y[2] = 0.3134;
	BinCode[8].x[3] = 0.2830;
	BinCode[8].y[3] = 0.3050;

	BinCodeName[9] = "86R(8200-9000K)";
	BinCode[9].x[0] = 0.2960;
	BinCode[9].y[0] = 0.2760;
	BinCode[9].x[1] = 0.3003;
	BinCode[9].y[1] = 0.2812;
	BinCode[9].x[2] = 0.2950;
	BinCode[9].y[2] = 0.2970;
	BinCode[9].x[3] = 0.2895;
	BinCode[9].y[3] = 0.2905;

	////7000-8200K
	BinCodeName[10] = "76S(7600-8200K)";
	BinCode[10].x[0] = 0.2895;
	BinCode[10].y[0] = 0.3134;
	BinCode[10].x[1] = 0.2962;
	BinCode[10].y[1] = 0.3220;
	BinCode[10].x[2] = 0.2937;
	BinCode[10].y[2] = 0.3312;
	BinCode[10].x[3] = 0.2870;
	BinCode[10].y[3] = 0.3210;

	BinCodeName[11] = "76M(7600-8200K)";
	BinCode[11].x[0] = 0.2920;
	BinCode[11].y[0] = 0.3060;
	BinCode[11].x[1] = 0.2984;
	BinCode[11].y[1] = 0.3133;
	BinCode[11].x[2] = 0.2962;
	BinCode[11].y[2] = 0.3220;
	BinCode[11].x[3] = 0.2895;
	BinCode[11].y[3] = 0.3134;

	BinCodeName[12] = "76N(7600-8200K)";
	BinCode[12].x[0] = 0.2950;
	BinCode[12].y[0] = 0.2970;
	BinCode[12].x[1] = 0.3009;
	BinCode[12].y[1] = 0.3042;
	BinCode[12].x[2] = 0.2984;
	BinCode[12].y[2] = 0.3133;
	BinCode[12].x[3] = 0.2920;
	BinCode[12].y[3] = 0.3060;

	BinCodeName[13] = "76T(7600-8200K)";
	BinCode[13].x[0] = 0.2980;
	BinCode[13].y[0] = 0.2880;
	BinCode[13].x[1] = 0.3037;
	BinCode[13].y[1] = 0.2937;
	BinCode[13].x[2] = 0.3009;
	BinCode[13].y[2] = 0.3042;
	BinCode[13].x[3] = 0.2950;
	BinCode[13].y[3] = 0.2970;

	BinCodeName[14] = "73R(7000-7600K)";
	BinCode[14].x[0] = 0.2962;
	BinCode[14].y[0] = 0.3220;
	BinCode[14].x[1] = 0.3028;
	BinCode[14].y[1] = 0.3304;
	BinCode[14].x[2] = 0.3005;
	BinCode[14].y[2] = 0.3415;
	BinCode[14].x[3] = 0.2937;
	BinCode[14].y[3] = 0.3312;

	BinCodeName[15] = "73P(7000-7600K)";
	BinCode[15].x[0] = 0.2984;
	BinCode[15].y[0] = 0.3133;
	BinCode[15].x[1] = 0.3048;
	BinCode[15].y[1] = 0.3207;
	BinCode[15].x[2] = 0.3028;
	BinCode[15].y[2] = 0.3304;
	BinCode[15].x[3] = 0.2962;
	BinCode[15].y[3] = 0.3220; 

	BinCodeName[16] = "73Q(7000-7600K)";
	BinCode[16].x[0] = 0.3009;
	BinCode[16].y[0] = 0.3042;
	BinCode[16].x[1] = 0.3068;
	BinCode[16].y[1] = 0.3113;
	BinCode[16].x[2] = 0.3048;
	BinCode[16].y[2] = 0.3207;
	BinCode[16].x[3] = 0.2984;
	BinCode[16].y[3] = 0.3133;

	BinCodeName[17] = "73U(7000-7600K)";
	BinCode[17].x[0] = 0.3037;
	BinCode[17].y[0] = 0.2937;
	BinCode[17].x[1] = 0.3093;
	BinCode[17].y[1] = 0.2993;
	BinCode[17].x[2] = 0.3068;
	BinCode[17].y[2] = 0.3113;
	BinCode[17].x[3] = 0.3009;
	BinCode[17].y[3] = 0.3042;

	////6000-7000K
	BinCodeName[18] = "68S(6500-7000K)";
	BinCode[18].x[0] = 0.3028;
	BinCode[18].y[0] = 0.3304;
	BinCode[18].x[1] = 0.3115;
	BinCode[18].y[1] = 0.3391;
	BinCode[18].x[2] = 0.3099;
	BinCode[18].y[2] = 0.3509;
	BinCode[18].x[3] = 0.3005;
	BinCode[18].y[3] = 0.3415;

	BinCodeName[19] = "68A(6500-7000K)";
	BinCode[19].x[0] = 0.3048;
	BinCode[19].y[0] = 0.3207;
	BinCode[19].x[1] = 0.3130;
	BinCode[19].y[1] = 0.3290;
	BinCode[19].x[2] = 0.3115;
	BinCode[19].y[2] = 0.3391;
	BinCode[19].x[3] = 0.3028;
	BinCode[19].y[3] = 0.3304;

	BinCodeName[20] = "68B(6500-7000K)";
	BinCode[20].x[0] = 0.3068;
	BinCode[20].y[0] = 0.3113;
	BinCode[20].x[1] = 0.3144;
	BinCode[20].y[1] = 0.3186;
	BinCode[20].x[2] = 0.3130;
	BinCode[20].y[2] = 0.3290;
	BinCode[20].x[3] = 0.3048;
	BinCode[20].y[3] = 0.3207;

	BinCodeName[21] = "68T(6500-7000K)";
	BinCode[21].x[0] = 0.3093;
	BinCode[21].y[0] = 0.2993;
	BinCode[21].x[1] = 0.3161;
	BinCode[21].y[1] = 0.3059;
	BinCode[21].x[2] = 0.3144;
	BinCode[21].y[2] = 0.3186;
	BinCode[21].x[3] = 0.3068;
	BinCode[21].y[3] = 0.3113;

	BinCodeName[22] = "62R(6000-6500K)";
	BinCode[22].x[0] = 0.3115;
	BinCode[22].y[0] = 0.3391;
	BinCode[22].x[1] = 0.3205;
	BinCode[22].y[1] = 0.3481;
	BinCode[22].x[2] = 0.3196;
	BinCode[22].y[2] = 0.3602;
	BinCode[22].x[3] = 0.3099;
	BinCode[22].y[3] = 0.3509;

	BinCodeName[23] = "62C(6000-6500K)";
	BinCode[23].x[0] = 0.3130;
	BinCode[23].y[0] = 0.3290;
	BinCode[23].x[1] = 0.3213;
	BinCode[23].y[1] = 0.3373;
	BinCode[23].x[2] = 0.3205;
	BinCode[23].y[2] = 0.3481;
	BinCode[23].x[3] = 0.3115;
	BinCode[23].y[3] = 0.3391;
 
	BinCodeName[24] = "62D(6000-6500K)";
	BinCode[24].x[0] = 0.3144;
	BinCode[24].y[0] = 0.3186;
	BinCode[24].x[1] = 0.3221;
	BinCode[24].y[1] = 0.3261;
	BinCode[24].x[2] = 0.3213;
	BinCode[24].y[2] = 0.3373;
	BinCode[24].x[3] = 0.3130;
	BinCode[24].y[3] = 0.3290;

	BinCodeName[25] = "62U(6000-6500K)";
	BinCode[25].x[0] = 0.3161;
	BinCode[25].y[0] = 0.3059;
	BinCode[25].x[1] = 0.3231;
	BinCode[25].y[1] = 0.3120;
	BinCode[25].x[2] = 0.3221;
	BinCode[25].y[2] = 0.3261;
	BinCode[25].x[3] = 0.3144;
	BinCode[25].y[3] = 0.3186;

	////5300-6000K
	BinCodeName[26] = "58S(5650-6000K)";
	BinCode[26].x[0] = 0.3207;
	BinCode[26].y[0] = 0.3462;
	BinCode[26].x[1] = 0.3290;
	BinCode[26].y[1] = 0.3537;
	BinCode[26].x[2] = 0.3290;
	BinCode[26].y[2] = 0.3690;
	BinCode[26].x[3] = 0.3196;
	BinCode[26].y[3] = 0.3602;

	BinCodeName[27] = "58A(5650-6000K)";
	BinCode[27].x[0] = 0.3215;
	BinCode[27].y[0] = 0.3350;
	BinCode[27].x[1] = 0.3290;
	BinCode[27].y[1] = 0.3417;
	BinCode[27].x[2] = 0.3290;
	BinCode[27].y[2] = 0.3537;
	BinCode[27].x[3] = 0.3207;
	BinCode[27].y[3] = 0.3462;
 	 
	BinCodeName[28] = "58B(5650-6000K)";
	BinCode[28].x[0] = 0.3222;
	BinCode[28].y[0] = 0.3243;
	BinCode[28].x[1] = 0.3290;
	BinCode[28].y[1] = 0.3300;
	BinCode[28].x[2] = 0.3290;
	BinCode[28].y[2] = 0.3417;
	BinCode[28].x[3] = 0.3215;
	BinCode[28].y[3] = 0.3350;

	BinCodeName[29] = "58T(5650-6000K)";
	BinCode[29].x[0] = 0.3231;
	BinCode[29].y[0] = 0.3120;
	BinCode[29].x[1] = 0.3290;
	BinCode[29].y[1] = 0.3180;
	BinCode[29].x[2] = 0.3290;
	BinCode[29].y[2] = 0.3300;
	BinCode[29].x[3] = 0.3222;
	BinCode[29].y[3] = 0.3243;

	BinCodeName[30] = "55R(5300-5650K)";
	BinCode[30].x[0] = 0.3290;
	BinCode[30].y[0] = 0.3538;
	BinCode[30].x[1] = 0.3376;
	BinCode[30].y[1] = 0.3616;
	BinCode[30].x[2] = 0.3381;
	BinCode[30].y[2] = 0.3762;
	BinCode[30].x[3] = 0.3290;
	BinCode[30].y[3] = 0.3690;

	BinCodeName[31] = "55C(5300-5650K)";
	BinCode[31].x[0] = 0.3290;
	BinCode[31].y[0] = 0.3417;
	BinCode[31].x[1] = 0.3371;
	BinCode[31].y[1] = 0.3490;
	BinCode[31].x[2] = 0.3376;
	BinCode[31].y[2] = 0.3616;
	BinCode[31].x[3] = 0.3290;
	BinCode[31].y[3] = 0.3538;

	BinCodeName[32] = "55D(5300-5650K)";
	BinCode[32].x[0] = 0.3290;
	BinCode[32].y[0] = 0.3300;
	BinCode[32].x[1] = 0.3366;
	BinCode[32].y[1] = 0.3369;
	BinCode[32].x[2] = 0.3371;
	BinCode[32].y[2] = 0.3490;
	BinCode[32].x[3] = 0.3290;
	BinCode[32].y[3] = 0.3417;

	BinCodeName[33] = "55U(5300-5650K)";
	BinCode[33].x[0] = 0.3290;
	BinCode[33].y[0] = 0.3180;
	BinCode[33].x[1] = 0.3361;
	BinCode[33].y[1] = 0.3245;
	BinCode[33].x[2] = 0.3366;
	BinCode[33].y[2] = 0.3369;
	BinCode[33].x[3] = 0.3290;
	BinCode[33].y[3] = 0.3300;

	////4700-5300K
	BinCodeName[34] = "52S(5000-5300K)";
	BinCode[34].x[0] = 0.3376;
	BinCode[34].y[0] = 0.3616;
	BinCode[34].x[1] = 0.3463;
	BinCode[34].y[1] = 0.3687;
	BinCode[34].x[2] = 0.3480;
	BinCode[34].y[2] = 0.3840;
	BinCode[34].x[3] = 0.3381;
	BinCode[34].y[3] = 0.3762;

	BinCodeName[35] = "52A(5000-5300K)";
	BinCode[35].x[0] = 0.3371;
	BinCode[35].y[0] = 0.3490;
	BinCode[35].x[1] = 0.3451;
	BinCode[35].y[1] = 0.3554;
	BinCode[35].x[2] = 0.3463;
	BinCode[35].y[2] = 0.3687;
	BinCode[35].x[3] = 0.3376;
	BinCode[35].y[3] = 0.3616;

	BinCodeName[36] = "52B(5000-5300K)";
	BinCode[36].x[0] = 0.3366;
	BinCode[36].y[0] = 0.3369;
	BinCode[36].x[1] = 0.3440;
	BinCode[36].y[1] = 0.3427;
	BinCode[36].x[2] = 0.3451;
	BinCode[36].y[2] = 0.3554;
	BinCode[36].x[3] = 0.3371;
	BinCode[36].y[3] = 0.3490;

	BinCodeName[37] = "52T(5000-5300K)";
	BinCode[37].x[0] = 0.3361;
	BinCode[37].y[0] = 0.3245;
	BinCode[37].x[1] = 0.3429;
	BinCode[37].y[1] = 0.3307;
	BinCode[37].x[2] = 0.3440;
	BinCode[37].y[2] = 0.3427;
	BinCode[37].x[3] = 0.3366;
	BinCode[37].y[3] = 0.3369;

	BinCodeName[38] = "48R(4700-5000K)";
	BinCode[38].x[0] = 0.3463;
	BinCode[38].y[0] = 0.3687;
	BinCode[38].x[1] = 0.3551;
	BinCode[38].y[1] = 0.3760;
	BinCode[38].x[2] = 0.3571;
	BinCode[38].y[2] = 0.3907;
	BinCode[38].x[3] = 0.3480;
	BinCode[38].y[3] = 0.3840;

	BinCodeName[39] = "48C(4700-5000K)";
	BinCode[39].x[0] = 0.3451;
	BinCode[39].y[0] = 0.3554;
	BinCode[39].x[1] = 0.3533;
	BinCode[39].y[1] = 0.3620;
	BinCode[39].x[2] = 0.3551;
	BinCode[39].y[2] = 0.3760;
	BinCode[39].x[3] = 0.3463;
	BinCode[39].y[3] = 0.3687;

	BinCodeName[40] = "48D(4700-5000K)";
	BinCode[40].x[0] = 0.3440;
	BinCode[40].y[0] = 0.3427;
	BinCode[40].x[1] = 0.3515;
	BinCode[40].y[1] = 0.3487;
	BinCode[40].x[2] = 0.3533;
	BinCode[40].y[2] = 0.3620;
	BinCode[40].x[3] = 0.3451;
	BinCode[40].y[3] = 0.3554;

	BinCodeName[41] = "48U(4700-5000K)";
	BinCode[41].x[0] = 0.3429;
	BinCode[41].y[0] = 0.3307;
	BinCode[41].x[1] = 0.3498;
	BinCode[41].y[1] = 0.3362;
	BinCode[41].x[2] = 0.3515;
	BinCode[41].y[2] = 0.3487;
	BinCode[41].x[3] = 0.3440;
	BinCode[41].y[3] = 0.3427;

	////4250-4700K
	BinCodeName[42] = "46S(4500-4700K)";
	BinCode[42].x[0] = 0.3548;
	BinCode[42].y[0] = 0.3736;
	BinCode[42].x[1] = 0.3641;
	BinCode[42].y[1] = 0.3804;
	BinCode[42].x[2] = 0.3668;
	BinCode[42].y[2] = 0.3957;
	BinCode[42].x[3] = 0.3569;
	BinCode[42].y[3] = 0.3893;

	BinCodeName[43] = "46A(4500-4700K)";
	BinCode[43].x[0] = 0.3530;
	BinCode[43].y[0] = 0.3597;
	BinCode[43].x[1] = 0.3615;
	BinCode[43].y[1] = 0.3659;
	BinCode[43].x[2] = 0.3641;
	BinCode[43].y[2] = 0.3804;
	BinCode[43].x[3] = 0.3548;
	BinCode[43].y[3] = 0.3736;
 
	BinCodeName[44] = "46B(4500-4700K)";
	BinCode[44].x[0] = 0.3512;
	BinCode[44].y[0] = 0.3465;
	BinCode[44].x[1] = 0.3590;
	BinCode[44].y[1] = 0.3521;
	BinCode[44].x[2] = 0.3615;
	BinCode[44].y[2] = 0.3659;
	BinCode[44].x[3] = 0.3530;
	BinCode[44].y[3] = 0.3597;

	BinCodeName[45] = "46T(4500-4700K)";
	BinCode[45].x[0] = 0.3495;
	BinCode[45].y[0] = 0.3339;
	BinCode[45].x[1] = 0.3567;
	BinCode[45].y[1] = 0.3389;
	BinCode[45].x[2] = 0.3590;
	BinCode[45].y[2] = 0.3521;
	BinCode[45].x[3] = 0.3512;
	BinCode[45].y[3] = 0.3465;

	BinCodeName[46] = "44R(4250-4500K)";
	BinCode[46].x[0] = 0.3641;
	BinCode[46].y[0] = 0.3804;
	BinCode[46].x[1] = 0.3736;
	BinCode[46].y[1] = 0.3874;
	BinCode[46].x[2] = 0.3769;
	BinCode[46].y[2] = 0.4022;
	BinCode[46].x[3] = 0.3668;
	BinCode[46].y[3] = 0.3957;

	BinCodeName[47] = "44C(4250-4500K)";
	BinCode[47].x[0] = 0.3615;
	BinCode[47].y[0] = 0.3659;
	BinCode[47].x[1] = 0.3702;
	BinCode[47].y[1] = 0.3722;
	BinCode[47].x[2] = 0.3736;
	BinCode[47].y[2] = 0.3874;
	BinCode[47].x[3] = 0.3641;
	BinCode[47].y[3] = 0.3804;

	BinCodeName[48] = "44D(4250-4500K)";
	BinCode[48].x[0] = 0.3590;
	BinCode[48].y[0] = 0.3521;
	BinCode[48].x[1] = 0.3670;
	BinCode[48].y[1] = 0.3578;
	BinCode[48].x[2] = 0.3702;
	BinCode[48].y[2] = 0.3722;
	BinCode[48].x[3] = 0.3615;
	BinCode[48].y[3] = 0.3659;

	BinCodeName[49] = "44U(4250-4500K)";
	BinCode[49].x[0] = 0.3567;
	BinCode[49].y[0] = 0.3389;
	BinCode[49].x[1] = 0.3640;
	BinCode[49].y[1] = 0.3440;
	BinCode[49].x[2] = 0.3670;
	BinCode[49].y[2] = 0.3578;
	BinCode[49].x[3] = 0.3590;
	BinCode[49].y[3] = 0.3521;

	////3700-4250K
	BinCodeName[50] = "41S(4050-4250K)";
	BinCode[50].x[0] = 0.3736;
	BinCode[50].y[0] = 0.3874;
	BinCode[50].x[1] = 0.3826;
	BinCode[50].y[1] = 0.3931;
	BinCode[50].x[2] = 0.3866;
	BinCode[50].y[2] = 0.4085;
	BinCode[50].x[3] = 0.3769;
	BinCode[50].y[3] = 0.4022;

	BinCodeName[51] = "41A(4050-4250K)";
	BinCode[51].x[0] = 0.3702;
	BinCode[51].y[0] = 0.3722;
	BinCode[51].x[1] = 0.3786;
	BinCode[51].y[1] = 0.3777;
	BinCode[51].x[2] = 0.3826;
	BinCode[51].y[2] = 0.3931;
	BinCode[51].x[3] = 0.3736;
	BinCode[51].y[3] = 0.3874;

	BinCodeName[52] = "41B(4050-4250K)";
	BinCode[52].x[0] = 0.3670;
	BinCode[52].y[0] = 0.3578;
	BinCode[52].x[1] = 0.3746;
	BinCode[52].y[1] = 0.3624;
	BinCode[52].x[2] = 0.3786;
	BinCode[52].y[2] = 0.3777;
	BinCode[52].x[3] = 0.3702;
	BinCode[52].y[3] = 0.3722;

	BinCodeName[53] = "41T(4050-4250K)";
	BinCode[53].x[0] = 0.3640;
	BinCode[53].y[0] = 0.3440;
	BinCode[53].x[1] = 0.3706;
	BinCode[53].y[1] = 0.3471;
	BinCode[53].x[2] = 0.3746;
	BinCode[53].y[2] = 0.3624;
	BinCode[53].x[3] = 0.3670;
	BinCode[53].y[3] = 0.3578;

	BinCodeName[54] = "39R(4050-4250K)";
	BinCode[54].x[0] = 0.3826;
	BinCode[54].y[0] = 0.3931;
	BinCode[54].x[1] = 0.3916;
	BinCode[54].y[1] = 0.3987;
	BinCode[54].x[2] = 0.3963;
	BinCode[54].y[2] = 0.4145;
	BinCode[54].x[3] = 0.3866;
	BinCode[54].y[3] = 0.4085;

	BinCodeName[55] = "39C(4050-4250K)";
	BinCode[55].x[0] = 0.3786;
	BinCode[55].y[0] = 0.3777;
	BinCode[55].x[1] = 0.3869;
	BinCode[55].y[1] = 0.3829;
	BinCode[55].x[2] = 0.3916;
	BinCode[55].y[2] = 0.3987;
	BinCode[55].x[3] = 0.3826;
	BinCode[55].y[3] = 0.3931;

	BinCodeName[56] = "39D(4050-4250K)";
	BinCode[56].x[0] = 0.3746;
	BinCode[56].y[0] = 0.3624;
	BinCode[56].x[1] = 0.3822;
	BinCode[56].y[1] = 0.3670;
	BinCode[56].x[2] = 0.3869;
	BinCode[56].y[2] = 0.3829;
	BinCode[56].x[3] = 0.3786;
	BinCode[56].y[3] = 0.3777;

	BinCodeName[57] = "39U(4050-4250K)";
	BinCode[57].x[0] = 0.3706;
	BinCode[57].y[0] = 0.3471;
	BinCode[57].x[1] = 0.3775;
	BinCode[57].y[1] = 0.3511;
	BinCode[57].x[2] = 0.3822;
	BinCode[57].y[2] = 0.3670;
	BinCode[57].x[3] = 0.3746;
	BinCode[57].y[3] = 0.3624;

	BinCodeName[58] = "38P(3700-3850K)";
	BinCode[58].x[0] = 0.3916;
	BinCode[58].y[0] = 0.3987;
	BinCode[58].x[1] = 0.4006;
	BinCode[58].y[1] = 0.4044;
	BinCode[58].x[2] = 0.4060;
	BinCode[58].y[2] = 0.4208;
	BinCode[58].x[3] = 0.3963;
	BinCode[58].y[3] = 0.4145;

	BinCodeName[59] = "38E(3700-3850K)";
	BinCode[59].x[0] = 0.3869;
	BinCode[59].y[0] = 0.3829;
	BinCode[59].x[1] = 0.3952;
	BinCode[59].y[1] = 0.3880;
	BinCode[59].x[2] = 0.4006;
	BinCode[59].y[2] = 0.4044;
	BinCode[59].x[3] = 0.3916;
	BinCode[59].y[3] = 0.3987;

	BinCodeName[60] = "38F(3700-3850K)";
	BinCode[60].x[0] = 0.3822;
	BinCode[60].y[0] = 0.3670;
	BinCode[60].x[1] = 0.3897;
	BinCode[60].y[1] = 0.3716;
	BinCode[60].x[2] = 0.3952;
	BinCode[60].y[2] = 0.3880;
	BinCode[60].x[3] = 0.3869;
	BinCode[60].y[3] = 0.3829;

	BinCodeName[61] = "38Q(3700-3850K)";
	BinCode[61].x[0] = 0.3775;
	BinCode[61].y[0] = 0.3511;
	BinCode[61].x[1] = 0.3842;
	BinCode[61].y[1] = 0.3552;
	BinCode[61].x[2] = 0.3897;
	BinCode[61].y[2] = 0.3716;
	BinCode[61].x[3] = 0.3822;
	BinCode[61].y[3] = 0.3670;

	////3225-3700K
	BinCodeName[62] = "36S(3525-3700K)";
	BinCode[62].x[0] = 0.3996;
	BinCode[62].y[0] = 0.4015;
	BinCode[62].x[1] = 0.4097;
	BinCode[62].y[1] = 0.4065;
	BinCode[62].x[2] = 0.4158;
	BinCode[62].y[2] = 0.4232;
	BinCode[62].x[3] = 0.4050;
	BinCode[62].y[3] = 0.4179;

	BinCodeName[63] = "36A(3525-3700K)";
	BinCode[63].x[0] = 0.3943;
	BinCode[63].y[0] = 0.3853;
	BinCode[63].x[1] = 0.4036;
	BinCode[63].y[1] = 0.3898;
	BinCode[63].x[2] = 0.4097;
	BinCode[63].y[2] = 0.4065;
	BinCode[63].x[3] = 0.3996;
	BinCode[63].y[3] = 0.4015;

	BinCodeName[64] = "36B(3525-3700K)";
	BinCode[64].x[0] = 0.3889;
	BinCode[64].y[0] = 0.3690;
	BinCode[64].x[1] = 0.3975;
	BinCode[64].y[1] = 0.3731;
	BinCode[64].x[2] = 0.4036;
	BinCode[64].y[2] = 0.3898;
	BinCode[64].x[3] = 0.3943;
	BinCode[64].y[3] = 0.3853;

	BinCodeName[65] = "36T(3525-3700K)";
	BinCode[65].x[0] = 0.3833;
	BinCode[65].y[0] = 0.3526;
	BinCode[65].x[1] = 0.3914;
	BinCode[65].y[1] = 0.3564;
	BinCode[65].x[2] = 0.3975;
	BinCode[65].y[2] = 0.3731;
	BinCode[65].x[3] = 0.3889;
	BinCode[65].y[3] = 0.3690;

	BinCodeName[66] = "34R(3350-3525K)";
	BinCode[66].x[0] = 0.4097;
	BinCode[66].y[0] = 0.4065;
	BinCode[66].x[1] = 0.4198;
	BinCode[66].y[1] = 0.4115;
	BinCode[66].x[2] = 0.4266;
	BinCode[66].y[2] = 0.4286;
	BinCode[66].x[3] = 0.4158;
	BinCode[66].y[3] = 0.4232;

	BinCodeName[67] = "34C(3350-3525K)";
	BinCode[67].x[0] = 0.4036;
	BinCode[67].y[0] = 0.3898;
	BinCode[67].x[1] = 0.4130;
	BinCode[67].y[1] = 0.3944;
	BinCode[67].x[2] = 0.4198;
	BinCode[67].y[2] = 0.4115;
	BinCode[67].x[3] = 0.4097;
	BinCode[67].y[3] = 0.4065;

	BinCodeName[68] = "34D(3350-3525K)";
	BinCode[68].x[0] = 0.3975;
	BinCode[68].y[0] = 0.3731;
	BinCode[68].x[1] = 0.4061;
	BinCode[68].y[1] = 0.3773;
	BinCode[68].x[2] = 0.4130;
	BinCode[68].y[2] = 0.3944;
	BinCode[68].x[3] = 0.4036;
	BinCode[68].y[3] = 0.3898;

	BinCodeName[69] = "34U(3350-3525K)";
	BinCode[69].x[0] = 0.3914;
	BinCode[69].y[0] = 0.3564;
	BinCode[69].x[1] = 0.3992;
	BinCode[69].y[1] = 0.3602;
	BinCode[69].x[2] = 0.4061;
	BinCode[69].y[2] = 0.3773;
	BinCode[69].x[3] = 0.3975;
	BinCode[69].y[3] = 0.3731;

	BinCodeName[70] = "33P(3225-3350K)";
	BinCode[70].x[0] = 0.4198;
	BinCode[70].y[0] = 0.4115;
	BinCode[70].x[1] = 0.4299;
	BinCode[70].y[1] = 0.4165;
	BinCode[70].x[2] = 0.4375;
	BinCode[70].y[2] = 0.4340;
	BinCode[70].x[3] = 0.4266;
	BinCode[70].y[3] = 0.4286;

	BinCodeName[71] = "33E(3225-3350K)";
	BinCode[71].x[0] = 0.4130;
	BinCode[71].y[0] = 0.3944;
	BinCode[71].x[1] = 0.4223;
	BinCode[71].y[1] = 0.3990;
	BinCode[71].x[2] = 0.4299;
	BinCode[71].y[2] = 0.4165;
	BinCode[71].x[3] = 0.4198;
	BinCode[71].y[3] = 0.4115;

	BinCodeName[72] = "33F(3225-3350K)";
	BinCode[72].x[0] = 0.4061;
	BinCode[72].y[0] = 0.3773;
	BinCode[72].x[1] = 0.4147;
	BinCode[72].y[1] = 0.3814;
	BinCode[72].x[2] = 0.4223;
	BinCode[72].y[2] = 0.3990;
	BinCode[72].x[3] = 0.4130;
	BinCode[72].y[3] = 0.3944;

	BinCodeName[73] = "33Q(3225-3350K)";
	BinCode[73].x[0] = 0.3992;
	BinCode[73].y[0] = 0.3602;
	BinCode[73].x[1] = 0.4071;
	BinCode[73].y[1] = 0.3638;
	BinCode[73].x[2] = 0.4147;
	BinCode[73].y[2] = 0.3814;
	BinCode[73].x[3] = 0.4061;
	BinCode[73].y[3] = 0.3773;

	////2850-3225K
	BinCodeName[74] = "31S(3100-3225K)";
	BinCode[74].x[0] = 0.4299;
	BinCode[74].y[0] = 0.4165;
	BinCode[74].x[1] = 0.4387;
	BinCode[74].y[1] = 0.4197;
	BinCode[74].x[2] = 0.4469;
	BinCode[74].y[2] = 0.4375;
	BinCode[74].x[3] = 0.4375;
	BinCode[74].y[3] = 0.4340;

	BinCodeName[75] = "31A(3100-3225K)";
	BinCode[75].x[0] = 0.4223;
	BinCode[75].y[0] = 0.3990;
	BinCode[75].x[1] = 0.4305;
	BinCode[75].y[1] = 0.4019;
	BinCode[75].x[2] = 0.4387;
	BinCode[75].y[2] = 0.4197;
	BinCode[75].x[3] = 0.4299;
	BinCode[75].y[3] = 0.4165;

	BinCodeName[76] = "31B(3100-3225K)";
	BinCode[76].x[0] = 0.4147;
	BinCode[76].y[0] = 0.3814;
	BinCode[76].x[1] = 0.4222;
	BinCode[76].y[1] = 0.3840;
	BinCode[76].x[2] = 0.4305;
	BinCode[76].y[2] = 0.4019;
	BinCode[76].x[3] = 0.4223;
	BinCode[76].y[3] = 0.3990;

	BinCodeName[77] = "31T(3100-3225K)";
	BinCode[77].x[0] = 0.4071;
	BinCode[77].y[0] = 0.3638;
	BinCode[77].x[1] = 0.4139;
	BinCode[77].y[1] = 0.3661;
	BinCode[77].x[2] = 0.4222;
	BinCode[77].y[2] = 0.3840;
	BinCode[77].x[3] = 0.4147;
	BinCode[77].y[3] = 0.3814;

	BinCodeName[78] = "30R(2975-3100K)";
	BinCode[78].x[0] = 0.4387;
	BinCode[78].y[0] = 0.4197;
	BinCode[78].x[1] = 0.4474;
	BinCode[78].y[1] = 0.4228;
	BinCode[78].x[2] = 0.4562;
	BinCode[78].y[2] = 0.4408;
	BinCode[78].x[3] = 0.4469;
	BinCode[78].y[3] = 0.4375;

	BinCodeName[79] = "30C(2975-3100K)";
	BinCode[79].x[0] = 0.4305;
	BinCode[79].y[0] = 0.4019;
	BinCode[79].x[1] = 0.4386;
	BinCode[79].y[1] = 0.4048;
	BinCode[79].x[2] = 0.4474;
	BinCode[79].y[2] = 0.4228;
	BinCode[79].x[3] = 0.4387;
	BinCode[79].y[3] = 0.4197;

	BinCodeName[80] = "30D(2975-3100K)";
	BinCode[80].x[0] = 0.4222;
	BinCode[80].y[0] = 0.3840;
	BinCode[80].x[1] = 0.4298;
	BinCode[80].y[1] = 0.3867;
	BinCode[80].x[2] = 0.4386;
	BinCode[80].y[2] = 0.4048;
	BinCode[80].x[3] = 0.4305;
	BinCode[80].y[3] = 0.4019;

	BinCodeName[81] = "30U(2975-3100K)";
	BinCode[81].x[0] = 0.4139;
	BinCode[81].y[0] = 0.3661;
	BinCode[81].x[1] = 0.4210;
	BinCode[81].y[1] = 0.3686;
	BinCode[81].x[2] = 0.4298;
	BinCode[81].y[2] = 0.3867;
	BinCode[81].x[3] = 0.4222;
	BinCode[81].y[3] = 0.3840;

	BinCodeName[82] = "29P(2850-2975K)";
	BinCode[82].x[0] = 0.4474;
	BinCode[82].y[0] = 0.4228;
	BinCode[82].x[1] = 0.4562;
	BinCode[82].y[1] = 0.4260;
	BinCode[82].x[2] = 0.4656;
	BinCode[82].y[2] = 0.4442;
	BinCode[82].x[3] = 0.4562;
	BinCode[82].y[3] = 0.4408;

	BinCodeName[83] = "29E(2850-2975K)";
	BinCode[83].x[0] = 0.4386;
	BinCode[83].y[0] = 0.4048;
	BinCode[83].x[1] = 0.4468;
	BinCode[83].y[1] = 0.4077;
	BinCode[83].x[2] = 0.4562;
	BinCode[83].y[2] = 0.4260;
	BinCode[83].x[3] = 0.4474;
	BinCode[83].y[3] = 0.4228;

	BinCodeName[84] = "29F(2850-2975K)";
	BinCode[84].x[0] = 0.4298;
	BinCode[84].y[0] = 0.3867;
	BinCode[84].x[1] = 0.4373;
	BinCode[84].y[1] = 0.3893;
	BinCode[84].x[2] = 0.4468;
	BinCode[84].y[2] = 0.4077;
	BinCode[84].x[3] = 0.4386;
	BinCode[84].y[3] = 0.4048;

	BinCodeName[85] = "29Q(2850-2975K)";
	BinCode[85].x[0] = 0.4210;
	BinCode[85].y[0] = 0.3686;
	BinCode[85].x[1] = 0.4278;
	BinCode[85].y[1] = 0.3709;
	BinCode[85].x[2] = 0.4373;
	BinCode[85].y[2] = 0.3893;
	BinCode[85].x[3] = 0.4298;
	BinCode[85].y[3] = 0.3867;

	////2550-2850K
	BinCodeName[86] = "28S(2750-2850K)";
	BinCode[86].x[0] = 0.4562;
	BinCode[86].y[0] = 0.4260;
	BinCode[86].x[1] = 0.4646;
	BinCode[86].y[1] = 0.4280;
	BinCode[86].x[2] = 0.4744;
	BinCode[86].y[2] = 0.4462;
	BinCode[86].x[3] = 0.4656;
	BinCode[86].y[3] = 0.4442;

	BinCodeName[87] = "28A(2750-2850K)";
	BinCode[87].x[0] = 0.4468;
	BinCode[87].y[0] = 0.4077;
	BinCode[87].x[1] = 0.4546;
	BinCode[87].y[1] = 0.4095;
	BinCode[87].x[2] = 0.4646;
	BinCode[87].y[2] = 0.4280;
	BinCode[87].x[3] = 0.4562;
	BinCode[87].y[3] = 0.4260;	 

	BinCodeName[88] = "28B(2750-2850K)";
	BinCode[88].x[0] = 0.4373;
	BinCode[88].y[0] = 0.3893;
	BinCode[88].x[1] = 0.4446;
	BinCode[88].y[1] = 0.3910;
	BinCode[88].x[2] = 0.4546;
	BinCode[88].y[2] = 0.4095;
	BinCode[88].x[3] = 0.4468;
	BinCode[88].y[3] = 0.4077;

	BinCodeName[89] = "28T(2750-2850K)";
	BinCode[89].x[0] = 0.4278;
	BinCode[89].y[0] = 0.3709;
	BinCode[89].x[1] = 0.4346;
	BinCode[89].y[1] = 0.3725;
	BinCode[89].x[2] = 0.4446;
	BinCode[89].y[2] = 0.3910;
	BinCode[89].x[3] = 0.4373;
	BinCode[89].y[3] = 0.3893;

	BinCodeName[90] = "27R(2650-2750K)";
	BinCode[90].x[0] = 0.4646;
	BinCode[90].y[0] = 0.4280;
	BinCode[90].x[1] = 0.4729;
	BinCode[90].y[1] = 0.4299;
	BinCode[90].x[2] = 0.4833;
	BinCode[90].y[2] = 0.4485;
	BinCode[90].x[3] = 0.4744;
	BinCode[90].y[3] = 0.4462;

	BinCodeName[91] = "27C(2650-2750K)";
	BinCode[91].x[0] = 0.4546;
	BinCode[91].y[0] = 0.4095;
	BinCode[91].x[1] = 0.4625;
	BinCode[91].y[1] = 0.4113;
	BinCode[91].x[2] = 0.4729;
	BinCode[91].y[2] = 0.4299;
	BinCode[91].x[3] = 0.4646;
	BinCode[91].y[3] = 0.4280;

	BinCodeName[92] = "27D(2650-2750K)";
	BinCode[92].x[0] = 0.4446;
	BinCode[92].y[0] = 0.3910;
	BinCode[92].x[1] = 0.4520;
	BinCode[92].y[1] = 0.3927;
	BinCode[92].x[2] = 0.4625;
	BinCode[92].y[2] = 0.4113;
	BinCode[92].x[3] = 0.4546;
	BinCode[92].y[3] = 0.4095;

	BinCodeName[93] = "27U(2650-2750K)";
	BinCode[93].x[0] = 0.4346;
	BinCode[93].y[0] = 0.3725;
	BinCode[93].x[1] = 0.4416;
	BinCode[93].y[1] = 0.3743;
	BinCode[93].x[2] = 0.4520;
	BinCode[93].y[2] = 0.3927;
	BinCode[93].x[3] = 0.4446;
	BinCode[93].y[3] = 0.3910;

	BinCodeName[94] = "26P(2550-2650K)";
	BinCode[94].x[0] = 0.4729;
	BinCode[94].y[0] = 0.4299;
	BinCode[94].x[1] = 0.4813;
	BinCode[94].y[1] = 0.4319;
	BinCode[94].x[2] = 0.4921;
	BinCode[94].y[2] = 0.4503;
	BinCode[94].x[3] = 0.4833;
	BinCode[94].y[3] = 0.4485;

	BinCodeName[95] = "26E(2550-2650K)";
	BinCode[95].x[0] = 0.4625;
	BinCode[95].y[0] = 0.4113;
	BinCode[95].x[1] = 0.4703;
	BinCode[95].y[1] = 0.4132;
	BinCode[95].x[2] = 0.4813;
	BinCode[95].y[2] = 0.4319;
	BinCode[95].x[3] = 0.4729;
	BinCode[95].y[3] = 0.4299;
 	 
	BinCodeName[96] = "26F(2550-2650K)";
	BinCode[96].x[0] = 0.4520;
	BinCode[96].y[0] = 0.3927;
	BinCode[96].x[1] = 0.4593;
	BinCode[96].y[1] = 0.3944;
	BinCode[96].x[2] = 0.4703;
	BinCode[96].y[2] = 0.4132;
	BinCode[96].x[3] = 0.4625;
	BinCode[96].y[3] = 0.4113;

	BinCodeName[97] = "26Q(2550-2650K)";
	BinCode[97].x[0] = 0.4416;
	BinCode[97].y[0] = 0.3743;
	BinCode[97].x[1] = 0.4483;
	BinCode[97].y[1] = 0.3756;
	BinCode[97].x[2] = 0.4593;
	BinCode[97].y[2] = 0.3944;
	BinCode[97].x[3] = 0.4520;
	BinCode[97].y[3] = 0.3927;

	return true;
}

bool ifpointInXYLevelItem(double x, double y, XYLEVELItem item, double range)
{
	double k[4], b[4], gety[4];
	double maxx, minx;
	int crosspoint = 0, totalpoint = 0;
	int cross = 0;

	for(int i=0; i<3; i++)
	{
		if(item.x[i+1] >= item.x[i])
		{
			maxx = item.x[i+1];
			minx = item.x[i];
		}
		else
		{
			maxx = item.x[i];
			minx = item.x[i+1];
		}

		if((maxx >= (minx + range)) && (x >= (minx - range)) && (x <= (maxx + range)))
		{
			totalpoint ++;

			k[i] = (item.y[i+1] - item.y[i]) / (item.x[i+1] - item.x[i]);
			b[i] = item.y[i] - k[i] * item.x[i];
			gety[i] = k[i] * x + b[i];
			
			if((gety[i] >= (y - range)) && (gety[i] <= (y + range)))
			{
				return true;
			}
			
			if(gety[i] > y)
			{
				crosspoint++;
				if(((x >= (minx - range)) && (x <= (minx + range)))
					|| ((x >= (maxx - range)) && (x <= (maxx + range))))
				{
					cross ++;
				}
			}
		}
		else if((maxx >= (minx - range)) && (maxx <= (minx + range)) 
			 && (x >= (minx - range)) && (x <= (minx + range)))
		{	
			if(((y >= (item.y[i] + range)) && (y <= (item.y[i+1] - range))) 
				|| ((y <= (item.y[i] - range)) && (y >= (item.y[i+1] + range))))
			{
				return true;
			}
		}
	}
	
	if(item.x[3] >= item.x[0])
	{
		maxx = item.x[3];
		minx = item.x[0];
	}
	else
	{
		maxx = item.x[0];
		minx = item.x[3];
	}
	if((maxx >= (minx + range)) && (x >= (minx - range)) && (x <= (maxx + range)))
	{
		totalpoint ++;

		k[3] = (item.y[3] - item.y[0]) / (item.x[3] - item.x[0]);
		b[3] = item.y[3] - k[3] * item.x[3];
		gety[3] = k[3] * x + b[3];
		
		if((gety[3] >= (y - range)) && (gety[3] <= (y + range)))
		{
			return true;
		}
		
		if(gety[3] > y)
		{
			crosspoint++;
			if(((x >= (minx - range)) && (x <= (minx + range)))
					|| ((x >= (maxx - range)) && (x <= (maxx + range))))
			{
				cross ++;
			}
		}
	}
	else if((maxx >= (minx - range)) && (maxx <= (minx + range)) 
			 && (x >= (minx - range)) && (x <= (minx + range)))
	{
		if(((y >= (item.y[3] + range)) && (y <= (item.y[0] - range))) 
				|| ((y <= (item.y[3] - range)) && (y >= (item.y[0] + range))))
		{
			return true;
		}
	}


	if(totalpoint > 2)
	{
		crosspoint -= cross/2;
	}

	if(1 == crosspoint)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool ifLinesCross(Line l1, Line l2)
{
	double k1 = 1, b1 = 0;
	double k2 = 1, b2 = 0;
	double x = 0, y = 0;
	double maxx1 = 0, maxy1 = 0;
	double minx1 = 0, miny1 = 0;
	double maxx2 = 0, maxy2 = 0;
	double minx2 = 0, miny2 = 0;

	if(l1.x[0] >= l1.x[1])
	{
		maxx1 = l1.x[0];
		minx1 = l1.x[1];
	}
	else
	{
		maxx1 = l1.x[1];
		minx1 = l1.x[0];
	}

	if(l1.y[0] >= l1.y[1])
	{
		maxy1 = l1.y[0];
		miny1 = l1.y[1];
	}
	else
	{
		maxy1 = l1.y[1];
		miny1 = l1.y[0];
	}

	if(l2.x[0] >= l2.x[1])
	{
		maxx2 = l2.x[0];
		minx2 = l2.x[1];
	}
	else
	{
		maxx2 = l2.x[1];
		minx2 = l2.x[0];
	}

	if(l2.y[0] >= l2.y[1])
	{
		maxy2 = l2.y[0];
		miny2 = l2.y[1];
	}
	else
	{
		maxy2 = l2.y[1];
		miny2 = l2.y[0];
	}

	if(l1.x[0] == l1.x[1])
	{
		if(l2.x[0] == l2.x[1])
		{
			if(((l1.y[0] > miny2) && (l1.y[0] < maxy2))
				|| ((l1.y[1] > miny2) && (l1.y[1] < maxy2)))
			{
				return true;
			}
		}
		else if(l2.y[1] == l2.y[0])
		{
			if((l2.y[0] > miny1) && (l2.y[0] < maxy1)
				&& (l1.x[0] > minx2) && (l1.x[0] < maxx2))
			{
				return true;
			}
		}
		else
		{
			k2 = (l2.y[1] - l2.y[1]) / (l2.x[1] - l2.x[0]);
			b2 = l2.y[0] - k2 * l2.x[0];
			y = k2 * l1.x[0] + b2;

			if((y > miny1) && (y < maxy1)
				&& (y > miny2) && (y < maxy2))
			{
				return true;
			}
		}
	}
	else if(l1.y[0] == l1.y[1])
	{
		if(l2.x[0] == l2.x[1])
		{
			if((l2.x[0] > minx1) && (l2.x[0] < maxx1)
				&& (l1.y[0] > miny2) && (l1.y[0] < maxy2))
			{
				return true;
			}
		}
		else if(l2.y[1] == l2.y[0])
		{
			if(((l1.x[0] > minx2) && (l1.x[0] < maxx2))
				|| ((l1.x[1] > minx2) && (l1.x[1] < maxx2)))
			{
				return true;
			}
		}
		else
		{
			k2 = (l2.y[1] - l2.y[1]) / (l2.x[1] - l2.x[0]);
			b2 = l2.y[0] - k2 * l2.x[0];
			x = (l1.y[0] - b2) / k2;
			if((x > minx1) && (x < maxx1)
				&& (x > minx2) && (x < maxx2))
			{
				return true;
			}
		}
	}
	else
	{
		k1 = (l1.y[1] - l1.y[1]) / (l1.x[1] - l1.x[0]);
		b1 = l1.y[0] - k1 * l1.x[0];

		if(l2.x[0] == l2.x[1])
		{
			y = k1 * l2.x[0] + b1;
			if((y > miny1) && (y < maxy1)
				&& (y > miny2) && (y < maxy2))
			{
				return true;
			}
		}
		else if(l2.y[1] == l2.y[0])
		{
			x = (l2.y[0] - b1) / k1;
			if((x > minx1) && (x < maxx1)
				&& (x > minx2) && (x < maxx2))
			{
				return true;
			}
		}
		else
		{
			k2 = (l2.y[1] - l2.y[1]) / (l2.x[1] - l2.x[0]);
			b2 = l2.y[0] - k2 * l2.x[0];
			x = (b1 - b2) / (k2 - k1);

			if((x > minx1) && (x < maxx1)
				&& (x > minx2) && (x < maxx2))
			{
				return true;
			}
		}
	}
	
	return false;
}

bool ifRectLineCross(XYLEVELItem item1, XYLEVELItem item2)
{
	Line l1, l2;
	
	for(int i=0; i<4; i++)
	{
		l1.x[0] = item1.x[i];
		l1.y[0] = item1.y[i];
		if(3 == i)
		{
			l1.x[1] = item1.x[0];
			l1.y[1] = item1.y[0];
		}
		else
		{
			l1.x[1] = item1.x[i+1];
			l1.y[1] = item1.y[i+1];
		}
		
		for(int j=0; j<4; j++)
		{
			l2.x[0] = item2.x[j];
			l2.y[0] = item2.y[j];
			if(3 == j)
			{
				l2.x[1] = item2.x[0];
				l2.y[1] = item2.y[0];
			}
			else
			{
				l2.x[1] = item2.x[j+1];
				l2.y[1] = item2.y[j+1];
			}

			if(ifLinesCross(l1, l2))
			{
				return true;
			}
		}
	}

	return false;
}


bool ifRectCross(XYLEVELItem item1, XYLEVELItem item2, bool left)
{
	int i=0;

	if(left)
	{
		if((item1.x[0] > item2.x[1]) && (item1.x[0] > item2.x[2])
			&& (item1.x[3] > item2.x[1]) && (item1.x[3] > item2.x[2]))
		{
			return false;
		}
	}
	else
	{
		if((item1.x[1] < item2.x[0]) && (item1.x[1] < item2.x[3])
			&& (item1.x[2] < item2.x[0]) && (item1.x[2] < item2.x[3]))
		{
			return false;
		}
	}

	for(i=0; i<4; i++)
	{
		if(ifpointInXYLevelItem(item1.x[i], item1.y[i], item2, 0))
		{
			return true;
		}
	}

	for(i=0; i<4; i++)
	{
		if(ifpointInXYLevelItem(item2.x[i], item2.y[i], item1, 0))
		{
			return true;
		}
	}
	
	if(ifRectLineCross(item1, item2))
	{
		return true;
	}

	return false;
}

CString MappingBinCode(XYLEVELItem item)
{
	CString str;
	bool left = true;

	str = "";
	for(int i=0; i<98; i++)
	{
		if(ifRectCross(item, BinCode[i], left))
		{
			str += BinCodeName[i];
			str += ", ";

			left = false;
		}
	}

	return str;
}

bool GetCIECode()
{
	XYLEVELItem item0, item;
	int xylevelnum = 1, xynum = 0;
	bool xyend = false;
	
	item0.x[0] = atof(binArray.strBinArray[1][0]);
	item0.y[0] = atof(binArray.strBinArray[1][1]);
	item0.x[1] = atof(binArray.strBinArray[1][2]);
	item0.y[1] = atof(binArray.strBinArray[1][3]);
	item0.x[2] = atof(binArray.strBinArray[1][4]);
	item0.y[2] = atof(binArray.strBinArray[1][5]);
	item0.x[3] = atof(binArray.strBinArray[1][6]);
	item0.y[3] = atof(binArray.strBinArray[1][7]);
	MapBinCode[0] = MappingBinCode(item0);

	for(int i = 2; i<systemset.intMachineType; i++)
	{
		if(binArray.strBinArray[i][0] != "")
		{
			if(!xyend)
			{
				item.x[0] = atof(binArray.strBinArray[i][0]);
				item.y[0] = atof(binArray.strBinArray[i][1]);
				item.x[1] = atof(binArray.strBinArray[i][2]);
				item.y[1] = atof(binArray.strBinArray[i][3]);
				item.x[2] = atof(binArray.strBinArray[i][4]);
				item.y[2] = atof(binArray.strBinArray[i][5]);
				item.x[3] = atof(binArray.strBinArray[i][6]);
				item.y[3] = atof(binArray.strBinArray[i][7]);
				
				if(ifRectSame(item0, item))
				{
					xylevelnum = i;
					xyend = true;

					xynum = (i-1)%xylevelnum + 1;
					MapBinCode[i-1] = MapBinCode[xynum];
				}
				else
				{
					MapBinCode[i-1] = MappingBinCode(item);
				}
			}
			else
			{
				xynum = (i-1)%xylevelnum + 1;
				MapBinCode[i-1] = MapBinCode[xynum];
			}
		}
		else
		{
			return true;
		}
	}

	return true;
}

bool WriteNewCIECSVFile(CStdioFile *m_file)
{
	CString str_write;	
	
	str_write = "BinCode, X0, Y0, X1, Y1, X2, Y2, X3, Y3\n";
	m_file->WriteString(str_write);
	for(int i=0; i<98; i++)
	{
		str_write.Format("%s              ,%f    ,%f    ,%f    ,%f    ,%f    ,%f    ,%f    ,%f    \n",
		   BinCodeName[i],
		   BinCode[i].x[0], BinCode[i].y[0], BinCode[i].x[1], BinCode[i].y[1],
		   BinCode[i].x[2], BinCode[i].y[2], BinCode[i].x[3], BinCode[i].y[3]);
		m_file->WriteString(str_write);
	}
	
	return true;
}

////////////////////自动获取积分时间
extern double recommended;
extern double gettime;
extern double lastpower;
extern double setting_spectrum[PIXELNUM];

double autoGetMaxpower(int chip, int average, int boxcar, double time)
{
	double maxpower = 0;
//	DoubleArray sa;
	double *spectrum;	
//	OOI_PARAM ooip;
//	double spectrumpc[PIXELNUM];

	if(average < 1)
	{
		average = 1;
	}
	
	if(boxcar < 0)
	{
		boxcar = 0;
	}

	int i;
	COLOR_PARA dPara;
	ORI_PARA dOriPara;
	
	JK_Emission_GetData_3LED(chip,(float)time,average,3,dPara,dOriPara);
	double dDecAD[2048];
	maxpower = 0;
	for (i = 0; i< dOriPara.iPixN; i++)
	{
		dDecAD[i] = dOriPara.fDecPL[i];//fDecAD[i];
		if (maxpower < dDecAD[i])
		{
			maxpower = dDecAD[i];
		}
	}
	spectrum = &dDecAD[0];
	
	for(i=0; i<PIXELNUM; i++)
	{
		setting_spectrum[i] = spectrum[i];
	}
	setsngCounts(spectrum, sngCurrentDark[chip]);

	return maxpower;
}

double getTime(int chip, int average, int boxcar, double max, double min)
{
	double maxpower = 0;	
	double differ1 = 0, differ2 = 0;
	double middle = 0;
	CString str;
	
	if((max - min) < 0.2)
	{
		differ1 = fabs(autoGetMaxpower(chip, average, boxcar, max) - recommended);
		differ2 = fabs(autoGetMaxpower(chip, average, boxcar, min) - recommended);
		if(differ1 < differ2)
		{
			return max;
		}
		else if(differ1 > differ2)
		{
			return min;
		}
		else
		{
			getTime(chip, average, boxcar, max, min);
		}
	}
	middle = (max + min) * 0.5;
	str.Format("%0.1f", middle);

	maxpower = autoGetMaxpower(chip, average, boxcar, middle);
	if(maxpower > (recommended * 1.1))
	{
		max = middle;
		getTime(chip, average, boxcar, max, min);
	}
	else if(maxpower < (recommended * 0.9))
	{
		min = middle;
		getTime(chip, average, boxcar, max, min);
	}
	else
	{ 
		differ1 = fabs(maxpower - recommended);
		differ2 = fabs(lastpower - recommended);
		if(differ1 < differ2)
		{
			gettime = middle;
			lastpower = maxpower;
		}

		if(maxpower > recommended)
		{
			max = middle;
			getTime(chip, average, boxcar, max, min);
		}
		else if(maxpower < recommended)
		{
			min = middle;
			getTime(chip, average, boxcar, max, min);
		}
		else
		{
			return gettime;
		}
	}
	
	return gettime;
}

//检测一个字符是不是十六进制字符，若是返回相应的值，否则返回0x10；
char HexChar(char c)
{	
	if((c>='0')&&(c<='9'))
	{
		return c-0x30;
	}
	else if((c>='A')&&(c<='F'))
	{
		return c-'A'+10;
	}
	else if((c>='a')&&(c<='f'))
	{
		return c-'a'+10;
	}
	else 
	{
		return 0x10;
	}
}


//将一个字符串作为十六进制串转化为一个字节数组，
//字节间可用空格分隔，返回转换后的字节数组长度，同时字节数组长度自动设置。
int Str2Hex(CString str,CByteArray &data)
{	
	int t,t1;
	int rlen=0,len=str.GetLength();
	data.SetSize(len/2);
	for(int i=0;i<len;)
	{
		char l,h=str[i];
		if(h==' ')
		{
			i++;
			continue;
		}
		
		i++;
		if(i>=len)
		{
			break;
		}
		l=str[i];
		t=HexChar(h);
		t1=HexChar(l);
		if((t==16)||(t1==16))
		{
			break;
		}	
		else
		{ 
			t=t*16+t1;
		}
		
		i++;
		data[rlen]=(char)t;
		rlen++;
	}
	
	data.SetSize(rlen);
	return rlen;
}

int Str2Hex2(CString str, unsigned char* data)
{
	int t, t1;//int   hexData, lowhexData;   
	int rlen=0, len=str.GetLength();
	//data.SetSize(len/2);
	for(int i=0; i<len; )//注意循环条件
	{
		char lstr, hstr = str[i];//获得地址的高8位和低8位   
		
		if(hstr ==' ')
		{
			++i;
			continue;
		}

		i++;

		if(i>=len)
		{
			break;
		}
			
		lstr= str[i];
		t = HexChar(hstr);
		t1= HexChar(lstr);

		if((t==16)|| (t1==16))
		{
			break;
		}	
		else 
		{
			t= t*16+t1;
		}

		++i;
		data[rlen]= (char)t;
		++rlen;
	}
	//返回转换后的字节数组长度，同时字节数组长度自动设置。
	return rlen;
}

bool sendString(CString str)
{
	dataSize = 0;
	PurgeComm(hCom, PURGE_TXABORT|
	PURGE_RXABORT|PURGE_TXCLEAR|PURGE_RXCLEAR);

	unsigned char data[1024];
	
	int len=Str2Hex2(str,data);
	DWORD dwBytesWrite=len;
	COMSTAT ComStat;
	DWORD dwErrorFlags;
	BOOL bWriteStat;
	ClearCommError(hCom,&dwErrorFlags,&ComStat);
	bWriteStat=WriteFile(hCom, data,dwBytesWrite,& 
		dwBytesWrite,NULL);
	if(!bWriteStat)
	{
		return false;
	}

	return true;
}

CString readdata()
{
	CString restr1, restr2;
	unsigned char str[1024];
	DWORD wCount=1024;//读取的字节数
	BOOL bReadStat;
	
	COMSTAT ComStat;
	DWORD dwErrorFlags;
	ClearCommError(hCom,&dwErrorFlags,&ComStat);
	DWORD len = ComStat.cbInQue;

	if(len > 0)
	{
		bReadStat=ReadFile(hCom,str,len,&len,NULL);
		if(!bReadStat)
		{
			AfxMessageBox("读串口失败!,点击确定关闭程序");
		}
		else
		{
			int length = len;
			for(int i=0; i<length; i++)
			{
				read_data[dataSize+i] = str[i];
				restr2.Format("%02X", str[i]);
				restr1 += restr2;
			}
			dataSize += len;
		}
	}
	else
	{
		restr1 = "";
	}

	return restr1;
}

bool ifpassClow(int pos)
{
	if(feedingClowBox[pos] < 80)
	{
		if(pos < 49)
		{
			if(pos < (10+feedingClowBox[pos]))
			{
				return false;
			}
		}
		else if((pos >= 49) && (pos < 64))
		{
			if(feedingClowBox[pos] >= 40)
			{
				return false;
			}
		}
		else if((pos >= 64) && (pos < 104))
		{
			////(79-(pos-65))
			if((feedingClowBox[pos]>=40) && (feedingClowBox[pos]<(144-pos)))
			{
				return false;
			}
		}
	}
	
	return true;
}

bool checkBoxnum()
{
	long num = 0;
	int box = 0;
	int clowpos = 0;
	BYTE high = 0, low = 0;
	feedingClowBox.RemoveAll();

	int i = 0;
	for(i=0; i<270; i++)
	{
		////0~269, 共270字节
		////0,1号数据为头
		////2~161, 160字节，两字节一组，表示料盒信息
		if((i>1) && (i<162))
		{
			high = read_data[i+1];
			low = read_data[i];
			num = (long)(high << 8) + low;
			box = i/2 - 1;
			binBox[box][1] = num;
			i++;
		}
		else if(162 == i)////162,163号数据为满料数据
		{
			high = read_data[i+1];
			low = read_data[i];
			num = (long)(high << 8) + low;
			MaxLedNum = num;
			i++;
		}
		else if((i>163) && (i<269))////164~268,105个料爪信息
		{
			num = read_data[i];
			clowpos = i-164;
			feedingClowBox.Add(num); 
			
			if(!ifpassClow(clowpos))
			{
				binBox[num][1]++;
			}
		}
	}

	for(i=0; i<80; i++)
	{
		if(binBox[i][1]>MaxLedNum)
		{
			return false;
		}
	}

/*	waitingCheckLed.RemoveAll();
	for(int j=0; j<9; j++)
	{
		waitingCheckLed.Add
	}*/

	return true;
}

/////料盒计数减去料爪上分配到该料盒的数量
int getRealNumInBox(int boxnum)
{
	///如果料爪上的灯尚未通过吹料位置，此时，需要减掉这颗灯，才是料盒中真实的个数
	int i = 0;
	int num = binBox[boxnum][1];

	if(boxnum < 80)
	{
		if(boxnum < 40)
		{
			for(i=0; i<(10+boxnum); i++)
			{
				if(feedingClowBox[i] == boxnum)
				{
					num--;
				}
			}
		}
		else if((boxnum >= 40) && (boxnum < 80))
		{
			for(i=0; i<(144-boxnum); i++)
			{
				if(feedingClowBox[i] == boxnum)
				{
					num--;
				}
			}
		}
	}

//	40  0~104
//	79  0~65
	
	return num;
}

bool checkBoxStatus()
{
	BYTE status;
	int num = 0;
	int i = 0, j = 0;
	int size1 = 0, size2 = 0;
	int boxnum1 = 0, boxnum2 = 0;

	BoxStatusArray.RemoveAll();
	NewBoxStatusArray.RemoveAll();

	for(i=2; i<12; i++)
	{
		status = read_data[i];

		for(j=0; j<8; j++)
		{
			if(0 == (status&1))
			{
				num = j + (i-2)*8;
				NewBoxStatusArray.Add(num);
			}
			status = status>>1;
		}
	}
/*	for(i=2; i<12; i+=2)
	{
		status = read_data[i+1];

		for(j=0; j<8; j++)
		{
			if(1 == (status&1))
			{
				num = j + (i-2)*16;
				NewBoxStatusArray.Add(num);
			}
			status = status>>1;
		}

		status = read_data[i];

		for(j=0; j<8; j++)
		{
			if(1 == (status&1))
			{
				num = j + (i-2)*16 + 8;
				NewBoxStatusArray.Add(num);
			}
			status = status>>1;
		}
	}*/

	size1 = OldBoxStatusArray.GetSize();
	size2 = NewBoxStatusArray.GetSize();
	for(i=0; i<size1; i++)
	{
		boxnum1 = OldBoxStatusArray[i];
		for(j=0; j<size2; j++)
		{
			boxnum2 = NewBoxStatusArray[j];
			if(boxnum1 == boxnum2)
			{
				BoxStatusArray.Add(boxnum2);
			}
		}
	}

	OldBoxStatusArray.RemoveAll();
	OldBoxStatusArray.Copy(NewBoxStatusArray);

	return true;
}

CArray<CString,CString> getbincode[30];
bool seperateBincode()
{
	char name[200];
	int print_itemnum[30];
	CString print_item[30];
	CString print_bincode[30];
	
	int num = 0;
	CString str_item;
	int totalcol = 0;
	totalcol = columns[0] + columns[1] + columns[2];

	int i = 0, j = 0;
	for(i=0; i<totalcol; i+=2)
	{
		print_itemnum[num] = i;
		print_item[num] = binArray.strBinArray[0][i];
		num++;

		sscanf(binArray.strBinArray[0][i], "%*[^-]-%[^(]", str_item);
		if(0 == strcmp(str_item, "XYZ"))
		{
			i += 6;
		}	
	}

	for(i=0; i<num; i++)
	{
		getbincode[i].RemoveAll();
	}

	CString str_getname, str_getname2;
	for(i=1; i<systemset.intMachineType; i++)
	{
		strcpy(name, "");
		strcpy(name, binArray.binName[i]);
		str_getname = "NULL";
		str_getname = name;
		
		if(str_getname == "")
		{
			for(int j=0; j<num; j++)
			{
				getbincode[j].Add(str_getname);
			}
		}
		else
		{
			for(j=0; j<num; j++)
			{
				if(str_getname.Left(1) == "_")
				{
					str_getname2 = "";
					getbincode[j].Add(str_getname2);
					sscanf(str_getname, "_%s", str_getname);
				}
				else
				{
					sscanf(str_getname, "%[^_]", str_getname2);
					getbincode[j].Add(str_getname2);
					sscanf(str_getname, "%*[^_]_%s", str_getname);
				}
			}
		}
	}

	return true;
}

/////////重写Encode128Auto（校验位处理：103+ID*No.+...%103）
extern PrintItem printItem[10];
extern int CAT[3];
extern int realboxnum;
void P_DrawBarCode(CDC*pDC, int boxnum)
{
	int bin = 0;
	int i=0;
	int height = 40, height2 = 0;
	int codeheight = 40;
	
	int iPenW=2;
	const int iMapMode=pDC->SetMapMode(0);//P_AddOrGet(cmb_MapMode,0));

	if(iPenW==0)	iPenW=1;

	COLORREF clrBar		=RGB(0,0,0);
	COLORREF clrSpace	=RGB(255,255,255);

	pDC->StartDoc("HolyChip");
	pDC->StartPage();

	Barcode128 code;

	CString str, str_name1, str_name2;
	for(i=0; i<10; i++)
	{
		if(1 == printItem[i].ItemCheck)
		{
			str_name1 = printItem[i].name;

			bin = binBox[boxnum][0];
			////若数据内容为"Auto_Qty", "Auto_CAT", "Auto_Bin", "Auto_Boxnum"，则需要自动获取
			if(printItem[i].data == "Auto_Qty")
			{
				str_name2.Format("%d", realboxnum);
			}
			else if(printItem[i].data == "Auto_CAT")
			{
				str_name2.Format("CAT: %s, HUE: %s, REF: %s", getbincode[CAT[0]-1][bin-1], getbincode[CAT[1]-1][bin-1], getbincode[CAT[2]-1][bin-1]);
			}
			else if(printItem[i].data == "Auto_Bin")
			{
				str_name2.Format("%d", bin);
			}
			else if(printItem[i].data == "Auto_Boxnum")
			{
				str_name2.Format("%d", boxnum);
			}
			else
			{
				str_name2 = printItem[i].data;
			}

			str = str_name1 + str_name2;

			if(str != "")
			{
				pDC->TextOut(printItem[i].pos_X, printItem[i].pos_Y, str);
			}

			if((1 == printItem[i].namecode) && (1 == printItem[i].datacode))
			{
				height2 = printItem[i].pos_Y + height;
				code.Encode128Auto(str);
				P_DrawBarcode(pDC,printItem[i].pos_X,height2,height2+codeheight,height2+codeheight,clrBar,clrSpace,iPenW,&code);	
			}
			else if((1 == printItem[i].namecode) && (0 == printItem[i].datacode))
			{
				height2 = printItem[i].pos_Y + height;
				code.Encode128Auto(str_name1);
				P_DrawBarcode(pDC,printItem[i].pos_X,height2,height2+codeheight,height2+codeheight,clrBar,clrSpace,iPenW,&code);	
			}
			else if((0 == printItem[i].namecode) && (1 == printItem[i].datacode))
			{
				height2 = printItem[i].pos_Y + height;
				code.Encode128Auto(str_name2);
				P_DrawBarcode(pDC,printItem[i].pos_X,height2,height2+codeheight,height2+codeheight,clrBar,clrSpace,iPenW,&code);	
			}
		}
	}

	pDC->EndPage();
	pDC->EndDoc();

	pDC->SetMapMode(iMapMode);
}

void P_DrawBarcode(CDC*pDC,int iX,int iY0,int iY10,int iY11,COLORREF clrBar,COLORREF clrSpace,int iPenW,BarcodeBase*pBc)
{
	pBc->DrawBarcode(pDC->m_hDC,iX,iY0,iY10,iY11,clrBar,clrSpace,iPenW);	
}