//ExCalc_Color.h
#ifndef  _EX_CALC_COLOR_DATA_H_
#define  _EX_CALC_COLOR_DATA_H_

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
	float fRi[15];   //��ɫ��ָ�� R1-R15

	float fRR;       //��ɫ��
	float fGR;       //��ɫ��
	float fBR;       //��ɫ��
};

#endif
