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

bool checklink();   ///���ڼ����Ժ�PLCͨ��

///////�ж�ĳһ���Ƿ���ָ��͹�ı�����
bool ispointInquadrangle(double x, double y, sngPOINT *p, double range);

///////���ݲ��ֵ��ȡ������ֵ�����ж��Ƿ��������С��Χ��
bool HandleCalValue(int chip, int i);

///////����ͳ�Ʋ�����Ŀ�����ֵ����Сֵ
bool HandleStatisticValue(double *total, double *max, double *min, double value);

//void Do_Scan_USB2000(DoubleArray *SA, double time, int average, int boxcar);
//void Do_Scan_USB2000_test(DoubleArray *SA, double time, int average, int boxcar);
//void Do_Scan_PC2000(double time, int average, int boxcar);
//void SingleScan_PC2000(OOI_PARAM *ooip, double time, int average, int boxcar);
bool getSpectrumFromFile();   //���ļ��л�ȡ����
bool testgetSpectrum(int chip);   //��ȡ����
bool testgetSpectrum2(int chip);   //��ȡ�����ף��������ѧ������Ŀ
bool closeMixLight(int times, int delay);  ///�رջ��򿪵ĵ�
bool test(int chip);   //����
bool KeepLight_test(int chip);    //��������
bool MixLight_test(int chip);     //������
bool MixKeepLight_test(int chip);   //��ⳤ������
bool test2(int chip);        //˫��˫������
bool KeepLight_test2(int chip);   //˫��˫����������

void Mappingtestlevel();   ////////ʹ������Ŀ�ͷּ��ж�Ӧ
int *CalculateBin(bool autotest);    ///��������bin��
int searchMachineBin(int bin, bool autotest); //����bin��
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
void LineApply(XYLEVELItem item, int x, int y, int chip, int handle, int style);   //����λ����ShootDiagram��
void ColumnApply(XYLEVELItem item, int x, int y, int chip, int handle, int style);    //����λ����ShootDiagram��
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

//////////////��CIE���귶Χ�ж�
bool BinCodeList();
bool ifpointInXYLevelItem(double x, double y, XYLEVELItem item, double range);
bool ifLinesCross(Line l1, Line l2);
bool ifRectLineCross(XYLEVELItem item1, XYLEVELItem item2);
bool ifRectCross(XYLEVELItem item1, XYLEVELItem item2, bool left);
CString MappingBinCode(XYLEVELItem item);
bool GetCIECode();

///////////�Զ���ȡ����ʱ��
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