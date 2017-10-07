#include <Afxtempl.h>

#define PIXELNUM		2048 
#define MAXBIN			500
#define LEVELCOLUMNS	102

typedef struct
{
   char   TestItem[10];         //������Ŀ
   int    Delay;                //�ӳ�ʱ��
   double VCom;					//��ѹ
   double ICom;					//����
   double Lower;				//����
   double Upper;				//����
   int    Fail;                 //ʧ�ܵȼ�
   int    Continue;             //��ʧ���Ƿ���������   0Ϊfalse  1Ϊtrue
   double stavalue1;            //��׼ֵ
   double stavalue2;            //��׼ֵ
   int    Calway;               //У����ʽ  0Ϊoffset 1Ϊmultiple  2Ϊboth
   int    Calway2;
   double CalParam1;            //У������*
   double CalParam2;            //У������+
   double TestValue;            //����ֵ
   double XValue;
   double YValue;
   double CalParam1X;            //У������x*
   double CalParam2X;            //У������x+
   double CalParam1Y;            //У������y*
   double CalParam2Y;            //У������y+
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
	int checkCount;		//������ӵ�������
	int validCount;		//��Ч��������ʱ��Ϊ�ɹ�
	int sentBinDelay;   //�ּ�����ʱ
	int mintesttime;    //��̲���ʱ��
	double VRoffset[3]; //�������ѹ����

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

//////////////��CIE���귶Χ�ж�
bool WriteBinCodeCSVFile(CStdioFile *m_file);
bool WriteNewCIECSVFile(CStdioFile *m_file);

bool ReadPrintSetFile(CStdioFile *m_file);
bool WritePrintSetFile(CStdioFile *m_file);

bool ReadBinMapFile(CStdioFile *m_file);
bool WriteBinMapFile(CStdioFile *m_file);
