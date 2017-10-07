#include <Afxtempl.h>

#define PIXELNUM		2048 
#define MAXBIN			500
#define LEVELCOLUMNS	102

typedef struct
{
   char   TestItem[10];         //测试项目
   int    Delay;                //延迟时间
   double VCom;					//电压
   double ICom;					//电流
   double Lower;				//下限
   double Upper;				//上限
   int    Fail;                 //失败等级
   int    Continue;             //如失败是否连续测试   0为false  1为true
   double stavalue1;            //标准值
   double stavalue2;            //标准值
   int    Calway;               //校正方式  0为offset 1为multiple  2为both
   int    Calway2;
   double CalParam1;            //校正参数*
   double CalParam2;            //校正参数+
   double TestValue;            //测量值
   double XValue;
   double YValue;
   double CalParam1X;            //校正参数x*
   double CalParam2X;            //校正参数x+
   double CalParam1Y;            //校正参数y*
   double CalParam2Y;            //校正参数y+
   bool   Result;

   double total;
   double max;
   double min;
   double average;
   
   double total_X;
   double total_Y;
   double max_X;
   double max_Y;
   double min_X;
   double min_Y;
   double average_X;
   double average_Y;

}TESTTYPE;

typedef struct
{
	double Voltage;
	double Current;
	int Delay;

}LightParam;

typedef struct
{
	double x; 
	double y;

}sngPOINT;

typedef struct
{
	CString strBinArray[MAXBIN][LEVELCOLUMNS];
	CString binName[MAXBIN];

}BinArray;

typedef struct
{
	int intMachineType;
	int checkCount;		//检测连接的最多次数
	int validCount;		//有效次数多少时视为成功
	int sentBinDelay;   //分级后延时
	int mintesttime;    //最短测试时间
	double VRoffset[3]; //正反向电压补偿

}SystemSet;

typedef struct
{
	int    pixels;
	double intercept;
	double firstCoeff;
	double secondCoeff;
	double thirdCoeff;

}CalCoeff;

typedef struct
{
	double sngReference[PIXELNUM];
	double sngDark[PIXELNUM];
	double sngListPower[PIXELNUM];
	double uJoulesCount[PIXELNUM];
	double standardpower[PIXELNUM];

}StandardLightResource;

typedef struct
{
	int num;
	double x[4];
	double y[4];

}XYLEVELItem;

typedef struct
{
	double x[4];
	double y[4];
	POSITION pos;
	int levelnum;

}tempXYLEVELItem;

typedef struct
{
	double x[2];
	double y[2];

}Line;

typedef struct
{
	int ItemCheck;
	CString name;
	int namecode;
	CString data;
	int datacode;
	int pos_X;
	int pos_Y;

}PrintItem;


bool ReadSysFile(CStdioFile *m_file);
bool WriteSysFile(CStdioFile *m_file);

bool ReadSpectrumSetFile(CStdioFile *m_file);
bool WriteSpectrumSetFile(CStdioFile *m_file);

bool ReadCalDarkFile(CStdioFile *m_file);

bool ReadReferFile(CStdioFile *m_file);
bool WriteReferFile(CStdioFile *m_file, StandardLightResource *staCal);

bool ReadStaFile(CStdioFile *m_file);
bool WriteStaFile(CStdioFile *m_file);

bool ReadLevelCSVFile(CStdioFile *m_file);
bool WriteLevelCSVFile(CStdioFile *m_file);

bool ReadXYLevelCSVFile(CStdioFile *m_file);
bool WriteXYLevelCSVFile(CStdioFile *m_file);
bool ReadXYLevelCSVFile2(CStdioFile *m_file);
bool WriteXYLevelCSVFile2(CStdioFile *m_file);

bool ReadShootDotCSVFile(CStdioFile *m_file);
bool WriteShootDotCSVFile(CStdioFile *m_file);

bool ReadLogFile(CStdioFile *m_file);
bool WriteLogFile(CStdioFile *m_file);

bool ReadLMPFile(CStdioFile *m_file);	

bool ReadSpecFile(CStdioFile *m_file, double *spec);
bool WriteSpecFile(CStdioFile *m_file, double *spec);

//////////////新CIE坐标范围判断
bool WriteBinCodeCSVFile(CStdioFile *m_file);
bool WriteNewCIECSVFile(CStdioFile *m_file);

bool ReadPrintSetFile(CStdioFile *m_file);
bool WritePrintSetFile(CStdioFile *m_file);

bool ReadBinMapFile(CStdioFile *m_file);
bool WriteBinMapFile(CStdioFile *m_file);
