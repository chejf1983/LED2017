//ExCalc_Color.h
#ifndef  _EX_CALC_COLOR_DATA_H_
#define  _EX_CALC_COLOR_DATA_H_

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
	float fRi[15];   //显色性指数 R1-R15

	float fRR;       //红色比
	float fGR;       //绿色比
	float fBR;       //蓝色比
};

#endif
