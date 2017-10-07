
#ifndef __EX_SPECTRAARSENALEMISSIOAPI_H__
#define __EX_SPECTRAARSENALEMISSIOAPI_H__


#define SA_API_SUCCESS   0
#define SA_API_FAIL      -1

struct COLOR_PARA
{
	float fx;        //ɫ����
	float fy;
	float fu;
	float fv;
	
	float fCCT;      //���ɫ��(K)
	float dC;        //ɫ��dC
	float fLd;       //������(nm)
	float fPur;      //ɫ����(%)
	float fLp;       //��ֵ����(nm)
	float fHW;       //�벨��(nm)
	float fLav;      //ƽ������(nm)
	float fRa;       //��ɫ��ָ�� Ra
	float fRR;       //��ɫ��
	float fGR;       //��ɫ��
	float fBR;       //��ɫ��
	float fRi[15];   //��ɫ��ָ�� R1-R15
	
	
	float fIp;		//��ֵAD
	
	float fPh;		//���ֵ
	float fPhe;		//�����ֵ
	float fPlambda;	//���Թ���ϴ��
	float fSpect1;	//��ʼ����
	float fSpect2;	//
	float fInterval;
	float fPL[10000];	//��������
};


struct ORI_PARA
{
	int iPixN;			//���ص����
	float fDecWL[2048];	//ԭʼ��������
	float fDecAD[2048]; //ԭʼADֵ
	float fDecPL[2048]; //��һ��֮��Ĺ�������
};


extern "C" __declspec(dllexport) int WINAPI JK_Emission_Init();
extern "C" __declspec(dllexport) int WINAPI JK_Emission_DarkStorage(float fIntTime, int iAveNum,int iFilterBW);
extern "C" __declspec(dllexport) int WINAPI JK_Emission_GetData(float fIntTime, int iAveNum,int iFilterBW, COLOR_PARA &dPara);
extern "C" __declspec(dllexport) int WINAPI JK_Emission_Calib(float fIntTime, int iAveNum,int iFilterBW, float fCCT, float fFlux,float &fIp);
extern "C" __declspec(dllexport) int WINAPI JK_Emission_Close();
extern "C" __declspec(dllexport) int WINAPI JK_Emission_GetData_3LED(int iLED,float fIntTime, int iAveNum,int iFilterBW, COLOR_PARA &dPara, ORI_PARA &dOriPara);
extern "C" __declspec(dllexport) int WINAPI JK_Emission_DarkStorage_3LED(int iLED, float fIntTime, int iAveNum,int iFilterBW,ORI_PARA &dOriPara);



#endif

