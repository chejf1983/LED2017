//thsFun.h

//通讯进度条消息
#define WM_RS_SET_RANGE    WM_USER+2000
#define WM_RS_SET_POS      WM_USER+2001

//转化函数
__declspec(dllexport) void     ths_fToB4(float &fTemp, BYTE &b1, BYTE &b2, BYTE &b3, BYTE &b4);
__declspec(dllexport) float    ths_Tof(BYTE *bb);  
__declspec(dllexport) CString  ths_sStringTo(BYTE *bb, int number);
__declspec(dllexport) int      ths_bintoint(BYTE *bb);
__declspec(dllexport) float    ths_btof196(BYTE *bb);
__declspec(dllexport) float    ths_btof(BYTE *bb);
__declspec(dllexport) void     ths_WordToByte(WORD Word, BYTE &hByte, BYTE &lByte);
__declspec(dllexport) CString  ths_sZ(double fD,int iN);
__declspec(dllexport) CString  ths_sFormat(double fD, int iN);

//通讯函数
__declspec(dllexport) BOOL     ths_RS232_Open(HANDLE &CommDev,CString sCom, int iBaudRate);
__declspec(dllexport) BOOL     ths_RS232_Close(HANDLE &CommDev);
__declspec(dllexport) BOOL     ths_RS232_Con_485A(HANDLE &CommDev, DWORD fDtrControl, DWORD fRtsControl);
__declspec(dllexport) BOOL     ths_RS232_SetReadTime(HANDLE &CommDev, int iReadIntervalTimeOut, int iReadTotalTimeoutMultiplier, int iReadTotalTimeoutConstant);
__declspec(dllexport) BOOL     ths_RS232_SetDCBParity(HANDLE &CommDev,BYTE Parity);
__declspec(dllexport) BOOL     ths_RS232_Output(HANDLE &CommDev, BYTE *OutData, DWORD OutN,HWND hWnd);
__declspec(dllexport) BOOL     ths_RS232_Input(HANDLE &CommDev, BYTE *InData, DWORD InN,HWND hWnd);
__declspec(dllexport) BOOL     ths_RS232_SetAd(HANDLE &CommDev, CString sAd,int iCommType=1);

//仪器通讯函数

//int iTestType
#define PH_F_P   0   //光通量
#define PH_E_P   1   //光照度
#define PH_L_P   2   //光亮度
#define PH_I_P   3   //光电流

__declspec(dllexport) BOOL     ths_INS_PHOTO2000Z(CString sCom,int iTestType,float &fData,BOOL bShowInfo=FALSE,HWND hWnd=NULL);

//PF4000
#define PF4000_WAVE_N      480  //wave data number
#define PF4000_UI_THD_N    51   //harmonics

#define PF4000_AD     "97"//0x61

//int iTestType
#define PF4000_DATA   1   //
#define PF4000_WAVE   2   //
#define PF4000_ALL    3   //

#define DATA_AA       1   //普通  MODE
#define DATA_BB       2   //谐波

typedef struct tag_pf4000_data_test
{
	int      iDataType;

	//普通
	float    fUrms;
	float    fUmn;
	float    fUdc;
	float    fUac;
	float    fIrms;
	float    fImn;
	float    fIdc;
	float    fIac;
	float    fP;
	float    fS;
	float    fQ;
	float    fLambda;
	float    fFi;
	float    fU_freqU;
	float    fI_freqI;
	float    fUpk_a;      //++
	float    fUpk_s;      //--
	float    fIpk_a;      //++
	float    fIpk_s;      //--
	float    fCfU;
	float    fCfI;
	float    fFfU;
	float    fFfI;
	float    fZ;
	float    fRs;
	float    fXs;
	float    fRp;
	float    fXp;
	float    fPc;
	float    fWH_IF;
	float    fWHA_IF;//wh+
	float    fWHD_IF;//wh-
	float    fIH_IF;
	float    fIHA_IF;//Ah+
	float    fIHD_IF;//Ah-
	float    fINTEG_TA;//时间


	CString  aData[36];

	CString  aUrms;
	CString  aUmn;
	CString  aUdc;
	CString  aUac;
	CString  aIrms;
	CString  aImn;
	CString  aIdc;
	CString  aIac;
	CString  aP;
	CString  aS;
	CString  aQ;
	CString  aLambda;
	CString  aFi;
	CString  aU_freqU;
	CString  aI_freqI;
	CString  aUpk_a;     
	CString  aUpk_s;
	CString  aIpk_a;      
	CString  aIpk_s;
	CString  aCfU;
	CString  aCfI;
	CString  aFfU;
	CString  aFfI;
	CString  aZ;
	CString  aRs;
	CString  aXs;
	CString  aRp;
	CString  aXp;
	CString  aPc;
	CString  aWH_IF;
	CString  aWHA_IF;//Wh+
	CString  aWHD_IF;//Wh-
	CString  aIH_IF;
	CString  aIHA_IF;//Ah+
	CString  aIHD_IF;//Ah-
	CString  aINTEG_TA;//时间

	//谐波
	float    fU_t;
	float    fI_t;
	float    fP_t;
	float    fS_t;
	float    fQ_t;
	float    fLambda_t;
	float    fFi_t;
	float    fUthd_t;
	float    fIthd_t;
	float    fPthd_t;

	float     fUthd_Nt_t;
	float     fIthd_Nt_t;
	float     fUthd_N_t[PF4000_UI_THD_N];
	float     fIthd_N_t[PF4000_UI_THD_N];

	float     fUthd_Nt_a_t;                //绝对谐波
	float     fIthd_Nt_a_t;
	float     fUthd_N_a_t[PF4000_UI_THD_N];
	float     fIthd_N_a_t[PF4000_UI_THD_N];

	CString   aU_t;
	CString   aI_t;
	CString   aP_t;
	CString   aS_t;
	CString   aQ_t;
	CString   aLambda_t;
	CString   aFi_t;
	CString   aUthd_t;
	CString   aIthd_t;
	CString   aPthd_t;

	int iU_wave[PF4000_WAVE_N];          //波形
	int iI_wave[PF4000_WAVE_N];

} PF4000_DATA_TEST;

typedef struct tag_pf4000_data_cal
{
	float fCal_Uk[8];
	float fCal_Ik[8];
	float fCal_Ik_sen[8];//use 3,not use other 5
	float fCal_uFreq[18];
	float fCal_iFreq[18];
	float fCal_pFreq[18];
} PF4000_DATA_CAL;


extern BOOL __stdcall ths_INS_PF4000_Test(int iCom,int iAd,int iBaudRate,int iCommType,int iTestType,PF4000_DATA_TEST &pf4000,BOOL bShowInfo=FALSE,HWND hWnd=NULL,BOOL bEnglish=FALSE);
extern BOOL __stdcall ths_INS_PF4000_Cal(int iCom,int iAd,int iBaudRate,int iCommType,PF4000_DATA_TEST &pf4000,int iURange=0,int iIRange=0,int iIRange_sen=0,BOOL bSen=FALSE,BOOL bShowInfo=FALSE,HWND hWnd=NULL,BOOL bEnglish=FALSE);
extern BOOL __stdcall ths_INS_PF4000_SetCal(int iCom,int iAd,int iBaudRate,int iCommType,PF4000_DATA_CAL &pf4000cal,BOOL bShowInfo=FALSE,HWND hWnd=NULL,BOOL bEnglish=FALSE);
extern BOOL __stdcall ths_INS_PF4000_GetName(int iDataType,CString sName[],CString sUnit[],int &iN);
