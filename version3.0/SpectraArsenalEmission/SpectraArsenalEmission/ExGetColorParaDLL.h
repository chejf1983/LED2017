//ExGetColorParaDLL.h

#ifndef __EXGETCOLORPARADLL_H__
#define __EXGETCOLORPARADLL_H__

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
	float fPlambda;	//���Թ���ϵ��
	float fSpect1;	//��ʼ����
	float fSpect2;	//
	float fInterval;
	float fPL[5000];	//��������
};


struct ORI_PARA
{
	int iPixN;			//���ص����
	float fDecWL[2048];	//ԭʼ��������
	float fDecAD[2048]; //ԭʼADֵ
	float fDecPL[2048]; //��һ��֮��Ĺ�������
};

extern void __stdcall NH_GetVer(CString &strVer);
extern BOOL __stdcall NH_Init(CString strPW1, CString strPW2, CString strPath);
extern void __stdcall NH_CalcColor(float fWL[], float fPL[],
	int iN, COLOR_PARA &para,BOOL bXY2CCT,float xx,float yy);
extern float __stdcall NH_GetV(float fWL);
extern float __stdcall NH_GetCDI();


extern void __stdcall NH_GetVer_ASCII(char *strVer);
extern BOOL __stdcall NH_Init_ASCII(char * strPW1, char * strPW2, char * strPath);



#endif
