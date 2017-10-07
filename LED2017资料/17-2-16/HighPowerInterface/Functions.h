#include "highpower.h"
#include "FileHandle.h"
//#include "holychip.h"
#include "HolyChipOptics.h"
#include "math.h"
#include "resFile\Barcode\Barcode.h"

#include "SpectraArsenalEmissionAPI.h"

#define HIGHRESTIMESTAMP_H
#define SPECTROMETERCHANNEL_H


#define Pai 3.14159265358979

typedef struct
{
	double inteTime;
	int boxcarWidth;
	int scanTimes;

}OpticSetParam;


typedef struct
{
	int    ledtotalnum;
	int    ledpassnum;
	int    ledfailnum;
	double ledpasspercent;

}LEDNumStatistic;


typedef struct
{
	int  x;
	int  y;
	int  startbin;
//	bool level;
	int  column;

}XYLEVEL;

typedef struct
{
	int left;
	int top;
	int width;
	int height;
	int scalex;
	int scaley;
	double ratex;
	double ratey;

}PictureParam;

typedef struct
{
	int bin;
	int boxnum;
	bool pass;

}LedStatus;



bool resetparam();
int ExistLevels(int chip, int bin);
int IsXYLevelExist(int chip);
bool SetBinArrayXYZItem(XYLEVELItem item, int bin,
						CString (*string)[LEVELCOLUMNS],
						int chip);

bool SetBinArrayXYZItem2(XYLEVELItem item, int bin,
						CString (*string)[LEVELCOLUMNS],
						int chip, int num);

bool InitCalDarkParam(int chip);
bool setCalDarkParam(int chip, double time);

//bool SpectrumParamInit_GCS300();
bool SpectrumParamInit_USB2000();
bool SpectrumParamInit_PC2000();

bool PWLPOL(int chip, int middleWave);
bool WLPOL(int chip);
bool GetPOL(int way, int chip);

UINT StartContinuousTest(LPVOID lpParam);
UINT StartAutoTest(LPVOID lpParam);

bool checklink();   ///用于检测电脑和PLC通信

///////判断某一点是否在指定凸四边形内
bool ispointInquadrangle(double x, double y, sngPOINT *p, double range);

///////根据测得值获取矫正后值，并判断是否在最大最小范围内
bool HandleCalValue(int chip, int i);

///////用于统计测试项目的最大值，最小值
bool HandleStatisticValue(double *total, double *max, double *min, double value);

//void Do_Scan_USB2000(DoubleArray *SA, double time, int average, int boxcar);
//void Do_Scan_USB2000_test(DoubleArray *SA, double time, int average, int boxcar);
//void Do_Scan_PC2000(double time, int average, int boxcar);
//void SingleScan_PC2000(OOI_PARAM *ooip, double time, int average, int boxcar);
bool getSpectrumFromFile();   //从文件中获取光谱
bool testgetSpectrum(int chip);   //获取光谱
bool testgetSpectrum2(int chip);   //获取混光光谱，并计算光学测试项目
bool closeMixLight(int times, int delay);  ///关闭混光打开的灯
bool test(int chip);   //测试
bool KeepLight_test(int chip);    //长亮测试
bool MixLight_test(int chip);     //混光测试
bool MixKeepLight_test(int chip);   //混光长亮测试
bool test2(int chip);        //双脚双晶测试
bool KeepLight_test2(int chip);   //双脚双晶长亮测试

void Mappingtestlevel();   ////////使测试项目和分级列对应
int *CalculateBin(bool autotest);    ///计算所属bin号
int searchMachineBin(int bin, bool autotest); //分配bin盒
bool ifbinboxExist(int binbox);

bool IfMenuCheck(CMenu *m_menu, UINT nID);

//bool InitBigRect(int chip);
//bool SetBigRect(int chip);
bool InitXYLEVELItem(int chip);
bool CSVLevel_InitXYLEVELItem(int chip);
void DrawRect(CPoint *p, CDC *MemDC);
bool CoverExistLevel(int bin, int chip);
bool InsertLevel(int bin, int chip);
bool HandleAddLevelStyle(int style, int bin, int chip);
void LineApply(XYLEVELItem item, int x, int y, int chip, int handle, int style);   //函数位置在ShootDiagram中
void ColumnApply(XYLEVELItem item, int x, int y, int chip, int handle, int style);    //函数位置在ShootDiagram中
bool compareXYLEVELItem(XYLEVELItem item1, XYLEVELItem item2);
bool IfSameRectExist(XYLEVELItem item, int chip);
bool IfExistXYLEVELItem(XYLEVELItem item1, int chip);
bool SetOrderNum(int chip);

int CountNum(int chip);
int CalculateShootBin();

bool SetRange(int chip);
bool GetRange(int chip);
bool ifRectInRect(XYLEVELItem Rect, XYLEVELItem item);
bool DelAllInRect(int chip, XYLEVELItem Rect);
bool DelAllBigInRect(int chip, XYLEVELItem Rect);
bool FindInRect(int chip, XYLEVELItem Rect);
bool MoveRects(int chip, double x, double y);

bool ifSmallRect(int chip, POSITION pos);
int FigureLevelLocation(XYLEVELItem item1, XYLEVELItem item2, bool way);
bool ifExistBigRect(int chip, XYLEVELItem item);
XYLEVELItem FindTotalBigRect(int chip, XYLEVELItem item, POSITION position, bool prev);
bool SearchRange(int chip);

CString ReformatString(CString str);

bool InitBlackXY();

bool ifRectSame(XYLEVELItem item1, XYLEVELItem item2);
bool ifExistRect(int chip, XYLEVELItem item1);

//////////////新CIE坐标范围判断
bool BinCodeList();
bool ifpointInXYLevelItem(double x, double y, XYLEVELItem item, double range);
bool ifLinesCross(Line l1, Line l2);
bool ifRectLineCross(XYLEVELItem item1, XYLEVELItem item2);
bool ifRectCross(XYLEVELItem item1, XYLEVELItem item2, bool left);
CString MappingBinCode(XYLEVELItem item);
bool GetCIECode();

///////////自动获取积分时间
double autoGetMaxpower(int chip, int average, int boxcar, double time);
double getTime(int chip, int average, int boxcar, double max, double min);

char HexChar(char c);
int Str2Hex(CString str,CByteArray &data);
int Str2Hex2(CString str, unsigned char* data);
bool sendString(CString str);
CString readdata();

bool ifpassClow(int pos);
bool checkBoxnum();
int getRealNumInBox(int boxnum);
bool checkBoxStatus();

bool seperateBincode();
void P_DrawBarCode(CDC*pDC, int boxnum);
void P_DrawBarcode(CDC*pDC,int iX,int iY0,int iY10,int iY11,COLORREF clrBar,COLORREF clrSpace,int iPenW,BarcodeBase*pBc);