
#ifndef __EX_SPECTRAARSENALEMISSIOAPI_H__
#define __EX_SPECTRAARSENALEMISSIOAPI_H__


#define SA_API_SUCCESS    0
#define SA_API_FAIL      -1

typedef enum
{
    SOFTWARE_SYNCHRONOUS,		//���ͬ��ģʽ
	SOFTWARE_ASYNCHRONOUS,		//����첽ģʽ
	SOFTWARE_AUTO,				//�Զ�����ģʽ
	EXINT_RISING_EDGE,			//�����ش���
	EXINT_FALLING_EDGE,			//�½��ش���
	EXINT_HIGH_LEVEL,			//�ߵ�ƽ����ģʽ
	EXINT_LOW_LEVEL,			//�͵�ƽ����ģʽ
}TRIGGER_MODE;

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
extern "C" __declspec(dllexport) int WINAPI JK_Emission_DarkStorage(float fIntTime, int iAveNum,int iFilterBW,float fDarkAD[]);
extern "C" __declspec(dllexport) int WINAPI JK_Emission_GetData(TRIGGER_MODE TriggerMode, float fIntTime, int iAveNum,int iFilterBW, float fDx,float fDy,float fSetWL1,float fSetWL2,float fDarkAD[], COLOR_PARA &dPara);

//iCalType = 0; //ע�⣺0��Զ��� ����ɫ�¹�ͨ������
				//      1���Զ��꣬������Թ������� iStaNumΪ����Ĺ������ݸ��� fStaWL��׼���׶�Ӧ�Ĳ��� fStaPL��������
extern "C" __declspec(dllexport) int WINAPI JK_Emission_Calib(float fIntTime, int iAveNum,int iFilterBW, int iCalType, float fCCT, float fFlux,int iStaNum,float fStaWL[],float fStaPL[],float fDarkAD[],float &fIp);
extern "C" __declspec(dllexport) int WINAPI JK_Emission_Close();

//�첽����ģʽ
extern "C" __declspec(dllexport) int WINAPI JK_ScanStartAsyncSoftTrigger();
extern "C" __declspec(dllexport) int WINAPI JK_GetSpectumAsyncSoftTrigger(int &pState, float fIntTime, int iAveNum,int iFilterBW, float fDx,float fDy,float fSetWL1,float fSetWL2, COLOR_PARA &dPara);


//����ƫ�����¼���
extern "C" __declspec(dllexport) int WINAPI JK_Emission_CalcDxy(COLOR_PARA &dPara,float fDx,float fDy);

#endif

