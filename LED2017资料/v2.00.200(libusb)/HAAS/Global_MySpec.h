//Global_MySpec.h
#include "SPEC_PRO.h"
#include "ProcessData.h"
#include "ImageObject.h"
#include "CalFluxList.h"
#include "DaXinPowerComm.h"
#include "NPPowerMeterComm.h"

#define LED_VIS      0   //ֻ�пɼ�
#define LED_VIR      1   //ֻ�к���
#define LED_ALL      2   //ȫ���� ,������������

//ˢ��List head��Ϣ
#define WM_RE_HEAD   WM_USER+486
//����������Ϣ
#define WM_UPDATE    WM_USER+487

extern CImageObject  g_ImageLogo;

////////////////////////////////////////////
extern BOOL g_bDemo;
extern BOOL g_bEnglish;
extern CString g_strCurPath;

extern int  g_iTR80_or_90;
extern HWND g_MainWnd;

extern CProcessData g_doData;

extern CCSPEC_PRO g_SPEC;

extern BOOL g_bManuP;
extern BOOL	g_bHavePower;
extern CString	g_strPowCom;
extern CString	g_strPowType;
//��Դ����
extern int		g_iSouType;
extern CString	g_strSouComm;
extern BOOL		g_bAutoLamp;
extern int		g_iPerTime;
extern int		g_iSetType;
extern float	g_fSetVol;
extern float	g_fSetCurr;
extern float	g_fSetVol2;
extern float	g_fSetCurr2;

extern CDaXinPowerComm g_cPower;
extern CNPPowerMeterComm g_cPowerMeter;

extern BOOL g_bFunDebug;

//�����ͨ��
extern CCalFluxList g_calFluxData;
extern BOOL g_bUseCalFlux;
extern int  g_iSeleCalFlux;

extern BOOL WY_RESET(CString strCom);
extern BOOL WY_GET(CString strCom,float &fU,float &fI);
extern int WY_SETUI(CString strCom,float fSetU,float fSetI,float &fU,float &fI);

////////////////////////////////////////////////
////̽ͷ�Զ�������������
#define AD_FLUX_MAX 52000
#define AD_FLUX_MIN 4000
