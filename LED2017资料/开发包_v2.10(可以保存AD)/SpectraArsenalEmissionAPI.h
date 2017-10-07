
#ifndef __EX_SPECTRAARSENALEMISSIOAPI_H__
#define __EX_SPECTRAARSENALEMISSIOAPI_H__


#define SA_API_SUCCESS    0
#define SA_API_FAIL      -1

typedef enum
{
    SOFTWARE_SYNCHRONOUS,		//软件同步模式
	SOFTWARE_ASYNCHRONOUS,		//软件异步模式
	SOFTWARE_AUTO,				//自动采样模式
	EXINT_RISING_EDGE,			//上升沿触发
	EXINT_FALLING_EDGE,			//下降沿触发
	EXINT_HIGH_LEVEL,			//高电平触发模式
	EXINT_LOW_LEVEL,			//低电平触发模式
}TRIGGER_MODE;

struct COLOR_PARA
{
	float fx;        //色坐标
	float fy;
	float fu;
	float fv;
	
	float fCCT;      //相关色温(K)
	float dC;        //色差dC
	float fLd;       //主波长(nm)
	float fPur;      //色纯度(%)
	float fLp;       //峰值波长(nm)
	float fHW;       //半波宽(nm)
	float fLav;      //平均波长(nm)
	float fRa;       //显色性指数 Ra
	float fRR;       //红色比
	float fGR;       //绿色比
	float fBR;       //蓝色比
	float fRi[15];   //显色性指数 R1-R15
		
	float fIp;		//峰值AD
	
	float fPh;		//光度值
	float fPhe;		//辐射度值
	float fPlambda;	//绝对光谱洗漱
	float fSpect1;	//起始波长
	float fSpect2;	//
	float fInterval;
	float fPL[10000];	//光谱数据
};

struct ORI_PARA
{
	int iPixN;			//像素点个数
	float fDecWL[2048];	//原始波长数据
	float fDecAD[2048]; //原始AD值
	float fDecPL[2048]; //归一化之后的光谱数据
};

extern "C" __declspec(dllexport) int WINAPI JK_Emission_Init();
extern "C" __declspec(dllexport) int WINAPI JK_Emission_DarkStorage(float fIntTime, int iAveNum,int iFilterBW,float fDarkAD[]);
extern "C" __declspec(dllexport) int WINAPI JK_Emission_GetData(TRIGGER_MODE TriggerMode, float fIntTime, int iAveNum,int iFilterBW, float fDx,float fDy,float fSetWL1,float fSetWL2,float fDarkAD[], COLOR_PARA &dPara);

//iCalType = 0; //注意：0相对定标 输入色温光通量即可
				//      1绝对定标，输入绝对光谱数据 iStaNum为输入的光谱数据个数 fStaWL标准光谱对应的波长 fStaPL光谱数据
extern "C" __declspec(dllexport) int WINAPI JK_Emission_Calib(float fIntTime, int iAveNum,int iFilterBW, int iCalType, float fCCT, float fFlux,int iStaNum,float fStaWL[],float fStaPL[],float fDarkAD[],float &fIp);
extern "C" __declspec(dllexport) int WINAPI JK_Emission_Close();

//异步触发模式
extern "C" __declspec(dllexport) int WINAPI JK_ScanStartAsyncSoftTrigger();
extern "C" __declspec(dllexport) int WINAPI JK_GetSpectumAsyncSoftTrigger(int &pState, float fIntTime, int iAveNum,int iFilterBW, float fDx,float fDy,float fSetWL1,float fSetWL2, COLOR_PARA &dPara);


//输入偏置重新计算
extern "C" __declspec(dllexport) int WINAPI JK_Emission_CalcDxy(COLOR_PARA &dPara,float fDx,float fDy);

#endif

