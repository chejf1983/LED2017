
#ifndef __EX_SPECTRAARSENALEMISSIOAPI_H__
#define __EX_SPECTRAARSENALEMISSIOAPI_H__


#define SA_API_SUCCESS   0
#define SA_API_FAIL      -1

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
extern "C" __declspec(dllexport) int WINAPI JK_Emission_DarkStorage(float fIntTime, int iAveNum,int iFilterBW);
extern "C" __declspec(dllexport) int WINAPI JK_Emission_GetData(float fIntTime, int iAveNum,int iFilterBW, COLOR_PARA &dPara);
extern "C" __declspec(dllexport) int WINAPI JK_Emission_Calib(float fIntTime, int iAveNum,int iFilterBW, float fCCT, float fFlux,float &fIp);
extern "C" __declspec(dllexport) int WINAPI JK_Emission_Close();
extern "C" __declspec(dllexport) int WINAPI JK_Emission_GetData_3LED(int iLED,float fIntTime, int iAveNum,int iFilterBW, COLOR_PARA &dPara, ORI_PARA &dOriPara);
extern "C" __declspec(dllexport) int WINAPI JK_Emission_DarkStorage_3LED(int iLED, float fIntTime, int iAveNum,int iFilterBW,ORI_PARA &dOriPara);



#endif

