// SpectraArsenalEmission.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "SpectraArsenalEmission.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//��ǰ��������Ŀ¼
CString g_strCurPath;

//��������ϵ��
double g_fCCor[4];

//�Ӿ�����ϵ��
float g_fLamdaWL[1000];
//�Ӿ�����ϵ��������Χ
float g_startWL = 380.0f;
float g_stopWL = 780.0f;

//����ϵ��
float g_fPixWL[2048] = { 0 }; //����ϵ��
int iPixNum = 0; //��������

//��ʼ�����豸��ѡ�е��豸��
int selectdev = -1;

double g_fSPECT1 = 380.0f;
double g_fSPECT2 = 780.0f;

//double DarkSpect[2048];
//double DarkSpect_3LED[4][2048];

float g_fIntTime = 0;
int	  g_iAveNum = 0;
float g_fSP_fIntTime;
float g_fSP_fStaTc;
float g_fCAL_fStaFlux;
float g_fCAL_fFluxK;
float g_fSP_fK[10001];
float g_fSP_fSpect1;
float g_fSP_fSpect2;
float g_fSP_fInterval;


#pragma  region ���׹����㷨

#pragma  region ����Ҷ����
struct compx { float real, imag; };   //�����ṹ

#define PI 3.1415926535897932384626433832795028841971 //Բ����ֵ  

int FFT_N = 0;//����Ҷ�仯�� 

float *SIN_TAB;//���ұ�Ĵ�ſռ�
float *COS_TAB;//���ұ�Ĵ�ſռ�
int F_N = 0;
int FFTData_Len = 2048;


float g_bInitFliter = FALSE;
 

/*******************************************************************
����ԭ�ͣ�struct compx EE(struct compx b1,struct compx b2)
�������ܣ��������������г˷�����
��������������������嶨��ĸ���a,b
���������a��b�ĳ˻��������������ʽ���
*******************************************************************/
inline void EE(struct compx a, struct compx b, compx* out)
{
	struct compx c;
	c.real = a.real*b.real - a.imag*b.imag;
	c.imag = a.real*b.imag + a.imag*b.real;
	
	out->real = c.real;
	out->imag = c.imag;
}

/******************************************************************
����ԭ�ͣ�void create_sin_table(int PointNum)
�������ܣ��������Ҿ�̬�� 
�������������Ҷ�任����� 
���������
******************************************************************/
inline void create_sin_table(int PointNum){
	//�����̬��Ϊ�գ��ͷ�֮ǰ�ľ�̬�� 
	if(SIN_TAB != 0){
		free((void *)SIN_TAB);
		free((void *)COS_TAB);
	}
	
	//���뾲̬��ռ� 
	SIN_TAB = (float *)malloc(PointNum * sizeof(float));
	COS_TAB = (float *)malloc(PointNum * sizeof(float));
	
	//��ʼ��FFT_N���� 
	FFT_N = PointNum;
	
	//��ʼ����̬�� 
	for (int i = 0; i <= FFT_N / 2; i++){
		SIN_TAB[i] = (float)sin(2 * PI * i / FFT_N);
		COS_TAB[i] = (float)cos(2 * PI * i / FFT_N);
	}
}

/******************************************************************
����ԭ�ͣ�void sin_tab(float pi)
�������ܣ����ò��ķ�������һ����������ֵ
���������pi ��Ҫ��������ֵ����ֵ����Χ0--2*PI��������ʱ��Ҫת��
�������������ֵpi������ֵ
******************************************************************/
inline float sin_tab(int pi)
{
//	int n = 0;
//	float a = 0;
//	n = (int)(pi*FFT_N / 2 / PI);
//
//	if (n >= 0 && n <= FFT_N / 4)
//		a = SIN_TAB[n];
//	else if (n > FFT_N / 4 && n < FFT_N / 2)
//	{
//		n -= FFT_N / 4;
//		a = SIN_TAB[FFT_N / 4 - n];
//	}
//	else if (n >= FFT_N / 2 && n < 3 * FFT_N / 4)
//	{
//		n -= FFT_N / 2;
//		a = -SIN_TAB[n];
//	}
//	else if (n >= 3 * FFT_N / 4 && n < 3 * FFT_N)
//	{
//		n = FFT_N - n;
//		a = -SIN_TAB[n];
//	}
	if(pi < FFT_N / 2){
		return SIN_TAB[pi];
	}else{
		return -SIN_TAB[pi - FFT_N / 2];
	}
}

/******************************************************************
����ԭ�ͣ�void cos_tab(float pi)
�������ܣ����ò��ķ�������һ����������ֵ
���������pi ��Ҫ��������ֵ����ֵ����Χ0--2*PI��������ʱ��Ҫת��
�������������ֵpi������ֵ
******************************************************************/
inline float cos_tab(int pi)
{
//	float a, pi2;
//	pi2 = pi + PI / 2;
//	if (pi2 > 2 * PI)
//		pi2 -= 2 * PI;
//	a = sin_tab(pi2);
	if(pi < FFT_N / 2){
		return COS_TAB[pi];
	}else{
		return COS_TAB[FFT_N * 3 / 2 - pi];
	}
}

/*****************************************************************
����ԭ�ͣ�void FFT(struct compx *xin)
�������ܣ�������ĸ�������п��ٸ���Ҷ�任��FFT��
���������*xin�����ṹ������׵�ַָ�룬struct��
�����������
*****************************************************************/
inline void Wn_i(int n,int i,compx *Wn)  
{  
//  Wn->real = cos(2*PI*i/n);  
//  Wn->imag = -sin(2*PI*i/n); 
  Wn->real = cos_tab(i); 
  Wn->imag = -sin_tab(i);  
}  

//void c_mul(compx a,compx b,compx *c)  
//{  
//  c->real = a.real * b.real - a.imag * b.imag;  
//  c->imag = a.real * b.imag + a.imag * b.real;     
//}  

inline void c_sub(compx a,compx b,compx *c)  
{  
  c->real = a.real - b.real;  
  c->imag = a.imag - b.imag;   
}

inline void c_plus(compx a,compx b,compx *c)  
{  
  c->real = a.real + b.real;  
  c->imag = a.imag + b.imag;  
}

//����Ҷ�仯  
inline void FFT(compx f[])  
{  
	int N = FFT_N;
	compx t,wn;//�м����  
	int i,j,k,m,n,l,r,M;  
	int la,lb,lc;  
	/*----����ֽ�ļ���M=log2(N)----*/  
	for(i=N,M=1;(i=i/2)!=1;M++);   
	/*----���յ�λ����������ԭ�ź�----*/  
	for(i=1,j=N/2;i<=N-2;i++)  
	{  
		if(i<j)  
		{	  
			t=f[j];  
			f[j]=f[i];  
			f[i]=t;  
	    }  
	    k=N/2;  
	    while(k<=j)  
	    {  
			j=j-k;  
			k=k/2;  
	    }  
	    j=j+k;  
	}  
  
  /*----FFT�㷨----*/  
	for(m=1;m<=M;m++)  
	{
		la=(int)(pow(2.0,m)); //la=2^m�����m��ÿ�����������ڵ���       
		lb=la/2;    //lb�����m��ÿ�������������ε�Ԫ��  
                 //ͬʱ��Ҳ��ʾÿ�����ε�Ԫ���½ڵ�֮��ľ���  
 		/*----��������----*/  
 		for(l=1;l<=lb;l++)  
 		{  
			r=(int)((l-1)*pow(2.0,M-m));
			for(n=l-1;n<N-1;n=n+la) //����ÿ�����飬��������ΪN/la  
			{  
 				lc=n+lb;  //n,lc�ֱ����һ�����ε�Ԫ���ϡ��½ڵ���       
  				Wn_i(N,r,&wn);//wn=Wnr  
  				EE(f[lc],wn,&t);//t = f[lc] * wn��������  
				c_sub(f[n],t,&(f[lc]));//f[lc] = f[n] - f[lc] * Wnr  
				c_plus(f[n],t,&(f[n]));//f[n] = f[n] + f[lc] * Wnr  
 			}  
		}  
 	}  
}  

/*****************************************************************
����ԭ�ͣ�void IFFT(struct compx *xin)
�������ܣ�������ĸ�������п��ٸ���Ҷ��任��FFT��
���������*xin�����ṹ������׵�ַָ�룬struct��
�����������
*****************************************************************/
inline void IFFT(struct compx *xin)
{
	int i;
	float tmp;
	//��ת���� 
	for(i = 0; i < FFT_N; i++)
	{
		tmp = xin[i].imag;
		xin[i].imag = xin[i].real;
		xin[i].real = tmp;
	}
	
	//�������ٸ���Ҷ�任 
	FFT(xin);
	
	//�ٴη�ת����������С 
	for(i = 0; i < FFT_N; i++)
	{
		tmp = xin[i].imag;
		xin[i].imag = xin[i].real / FFT_N;
		xin[i].real = tmp / FFT_N;
	}
}
#pragma endregion

#pragma region ��Ƶ�˲�
float * scale;

/******************************************************************
����ԭ�ͣ�void initScaleTable(int PointNum, int start, int N)
�������ܣ�����������˹���˴��� 
���������int PointNum ����������int start ������ʼ�� (0 ~ PointNum / 2) һ��ȡ���ȵ� 1/20
N ���� 
���������
******************************************************************/
void initScaleTable(int PointNum, int start, int N)
{
	if (scale != 0) {
		free(scale);
	}

	scale = (float *)malloc(FFTData_Len * sizeof(float));

	for (int i = 0; i < PointNum / 2; i++) {
		float value = 1 / (1 + pow(((float)i / (float)start), 2*N));
		scale[i] = value;
		scale[PointNum - i - 1] = value;
	}
}

//////////////////////////////////////////////////////////////////
////FFTFilter

/******************************************************************
����ԭ�ͣ�void initFFTFilter(int PointNum, int filternum)
�������ܣ���ʼ���˲��� 
���������int PointNum ����������, int filternum ���˵� (0 ~ PointNum / 2) һ��ȡ���ȵ� 1/20 
	      filternum =  PointNum / 2 ȫͨ 
	      filternum Խ��ͨ����Ƶ��Խ�� 
���������1�������������ȷ 
******************************************************************/
inline int FFT_initFilter(int PointNum, int filternum)
{
	create_sin_table(PointNum);
	initScaleTable(PointNum, filternum, 8); //��ʼ��������˹�˲�����
	F_N = filternum;
	FFTData_Len = PointNum;
	
	return 0;
}

/*****************************************************************
����ԭ�ͣ�void FFTFilter(float *input, int inputlen)
�������ܣ����������������˲��㷨
���������float *input ԭʼ���ݣ����˺�����ֱ����д��ԭʼ�����ϣ���ʡ�ռ�, 
          int inputlen ���ݳ���
�������������1 ���ݳ��Ⱥͳ�ʼ���Ĳ�һ�£���Ҫ���³�ʼ���˲��� 
*****************************************************************/
inline int FFT_Filter(double *input, int inputlen)
{
	int i;
	if(inputlen != FFTData_Len)
	{
		return 1;
	}
	
    //����buffer 
	compx cinput[5000];
	
	//��ԭʼ����ת������ƽ�� 
	for(i = 0; i < FFTData_Len; i++)
	{
		cinput[i].real = (float)input[i];
		cinput[i].imag = 0;
	}
	//���ٸ���Ҷ�任 
	FFT(cinput);	
	
	//�˲� ================================================ 
	for(i = 0; i < FFTData_Len; i++)
	{
		cinput[i].real *= scale[i];
		cinput[i].imag *= scale[i];		
		//if(i > F_N && i < FFTData_Len - F_N)
		//{
			//cinput[i].real = cinput[i].real*0.1f;
			//cinput[i].imag = cinput[i].imag*0.1f;
		//}
	}
	//�˲� ================================================ 
	
	//����Ҷ��任 
	IFFT(cinput);
	
	for(i = 0; i < FFTData_Len; i++)
	{
		input[i] = cinput[i].real;
	}

	return 0;
}
#pragma endregion

#pragma region �������˲�
float* x_last;
float* p_last; 
float g_noise; //���� 
float g_limit; // �л����� 
float Q = 0;    //��������
float R = 0;    //��������
int nodenum;

//////////////////////////////////////////////////////////////////
/******************************************************************
����ԭ�ͣ�void initKalMan(int PointNum, int noise)
�������ܣ���ʼ���������˲���
���������PointNum ����������, 
		  noise ϵͳ������Χ��50)��
		  fNoiseQ ����������Χ��0-0.5)��
		  ������������Χ , float limit ()
���������
******************************************************************/
inline void initKalMan(int PointNum, float noise, float fNoiseQ, float limit)
{
	nodenum = PointNum;
	
	if(x_last != 0) 
	{
		free(x_last);
		free(p_last);
	} 
	
	x_last = (float *)malloc(nodenum * sizeof(float));
	p_last = (float *)malloc(nodenum * sizeof(float));
    
    Q = noise * fNoiseQ;     //��������������0��
    R = noise; //�������������ڰ�����������Χ��
    g_noise = noise; 
    g_limit = limit;
	int i;	
    for (i = 0; i < nodenum; i++)
	{
        x_last[i] = 0;
        p_last[i] = noise;
    }
}

/******************************************************************
����ԭ�ͣ� void Filter(float* data, int length)
�������ܣ��������˲�
���������float* data �������ݣ�int length ���ݳ��� 
���������float* data�޸ĺ������ 
******************************************************************/
inline void KFilter(double * data, int length)
 {
    if (length != nodenum)
	{
        return;
    }

	double fMax = 0;
	for(int i = 0; i < length; i++)
	{
		if(fMax < data[i]){
			fMax = data[i];
		}
	}

	g_limit = (float)(50 + (int)(fMax / 250));

	int nid = 0;
    for (nid = 0; nid < nodenum; nid++)
	{
        if (fabs(x_last[nid] - data[nid]) > g_limit) 
		{
             x_last[nid] = (float)data[nid];
             p_last[nid] = g_noise;
        }
		else 
		{	
	        float x_mid = x_last[nid];
	        float p_mid = p_last[nid] + Q;
	        float kg = p_mid / (p_mid + R);
	
	        x_last[nid] = (float)(x_mid + kg * (data[nid] - x_mid));//���Ƴ�������ֵ  
	        p_last[nid] = (1 - kg) * p_mid;//����ֵ��Ӧ��Э����  
	        data[nid] = x_last[nid];
    	}
    }
}

#pragma endregion

inline void SA_FilerInit(int iPixN, float fNoiseQ)
{
	int inum = iPixN/10;
	FFT_initFilter(iPixN,inum);
	float fNoise = 50.0f;
	float fLimit = 50.0f;
	initKalMan(iPixN,fNoise,fNoiseQ,fLimit);
	g_bInitFliter = TRUE;
}

inline void SA_FilterAD(double fAD[], int iPixN)
{
	if (g_bInitFliter)
	{
		FFT_Filter(fAD, iPixN);
	
		//KFilter(fAD, iPixN);
	}
}
#pragma endregion

#pragma region DLL��ӡ�ӿ�
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
Pprint DllPrint = NULL;

DLLEXP void WINAPI DLL_PRINT_SET(void(*ptr)(char*)) {
	DllPrint = ptr;
}

/*********************************
* LED_LITS_SEARCH() �����ӣ��������豸
*���أ� ���������豸������ 0 ��ʾû���豸
*********************************/
DLLEXP int WINAPI LED_LITS_SEARCH() {
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	//�����豸��-1��ʾû���豸��0��ʾ1���豸��+1
	int g_devlist = LITS_SystemOpen() + 1;

	//�ر�����
	LITS_SystemClose();

	return g_devlist;
}
#pragma endregion

#pragma region ��ʼ���豸

/*********************************
* LED_LITS_SEARCH() �Ͽ�����
*int devnum ѡ��Ҫ��ʼ�����豸��
*���أ�DLL_SUCESS         ��ʼ���ɹ�
*      FILE_OPEN_FAILED   ����ļ���ʧ��
*      DEV_OPEN_FAILED    �豸����ʧ��
*      DEV_INIT_FAILED    �豸��ʼ��ʧ��
*      DLL_INIT_FAILED    ���dll��ʼ��ʧ��
*********************************/
DLLEXP int WINAPI LED_LITS_CONNECT(int devnum)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	//������
	if (devnum < 0) {
		//��������ȷ
		return INVALID_PAR;
	}

	//�����豸��-1��ʾû���豸��0��ʾ1���豸��+1
	int g_devlist = LITS_SystemOpen() + 1;
	selectdev = -1;

	if (devnum > g_devlist) {
		//�ر�����
		LITS_SystemClose();
		//��������ȷ
		return INVALID_PAR;
	}

	//��ʼ���⶯̬��

	//��ȡ��������ϵ��
	if (LITS_GetWavelengthCalibrationCoefficients(devnum, g_fCCor) == SA_API_FAIL)
	{
		//�ر�����
		LITS_SystemClose();
		return DEV_INIT_FAILED;
	}

	//��ȡ���ص����
	//iPixNum = 2048;//��ʱд������ȡ�豸�����ص�
	iPixNum = LITS_GetPixelNumber(devnum);
	//��ʼ���˲���
	SA_FilerInit(iPixNum, 0);

	//���ݲ���ת��ϵ�������㲨��ֵ
	for (int i = 0; i < iPixNum; i++)
	{
		g_fPixWL[i] = (float)(g_fCCor[0]
			+ g_fCCor[1] * i
			+ g_fCCor[2] * i * i
			+ g_fCCor[3] * i * i * i);
	}

	char Path[256];
	GetModuleFileName(NULL,Path,250);   
	* ( strrchr( Path, '\\' ) + 1 ) = '\0';	
	g_strCurPath=Path;

	BOOL bR;
	char sPass1[256];
	char sPass2[256];
	char sPath[256];
	CString strPass1;
	strPass1 = "NAHONG_TECH_NAHONG";
	CString strPass2;
	strPass2 = "GET_COLOR_PARA";
	int i;
	for (i = 0; i < strPass1.GetLength(); i++)
	{
		sPass1[i] = strPass1.GetAt(i);
	}
	sPass1[i] = 0x00;

	for (i = 0; i < strPass2.GetLength(); i++)
	{
		sPass2[i] = strPass2.GetAt(i);
	}
	sPass2[i] = 0x00;

	for (i = 0; i < g_strCurPath.GetLength(); i++)
	{
		sPath[i] = g_strCurPath.GetAt(i);
	}
	sPath[i] = 0x00;
	bR = NH_Init_ASCII(sPass1,sPass2,sPath);
	if(!bR)
	{
		return SA_API_FAIL;
	}

	for (int i = 0; i < 401; i++)
	{
		g_fLamdaWL[i] = NH_GetV(380.0f + i);
	}

	if(1)
	{
		int i,iN;
		//��ȡ���׶�������
		FILE *fp;
		if(fopen_s(&fp, g_strCurPath + "Calibration\\Cal_standard.nh","rt"))
		{
			return SA_API_FAIL;
		}
		else
		{
			fscanf_s(fp,"%fK Time:%f\n",&g_fSP_fStaTc,&g_fSP_fIntTime);
			fscanf_s(fp,"%f %f %f\n",&g_fSP_fSpect1,&g_fSP_fSpect2,&g_fSP_fInterval);

			//char a[256];
			//fscanf_s(fp,"%s\n",a);
			//CString SP_strDate=a;

			fscanf_s(fp,"%f  %f\n",&g_fCAL_fStaFlux, &g_fCAL_fFluxK);

			iN=(int)((g_fSP_fSpect2-g_fSP_fSpect1)/g_fSP_fInterval+1+0.5f);
			float fWL[10001];
			for(i=0;i<iN;i++)
			{
				float fAD;
				fscanf_s(fp,"%f %f %f\n",&fWL[i],&g_fSP_fK[i], &fAD);
			}
		}
		fclose(fp);
	}

	selectdev = devnum;

	return DLL_SUCCESS;
}

/*********************************
*LED_LITS_GetDevInfo(char* devserial, int* PixNum) ��ȡ�豸��Ϣ
*SDevInfo* devinfo �豸��Ϣ
*���أ�DLL_SUCESS         ִ�л��ɹ�
*********************************/
DLLEXP int WINAPI LED_LITS_GetDevInfo(char* devserial, int* PixNum) {
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (selectdev < 0) {
		return DEV_NOT_INIT;
	}

	//��ȡ���к�
	char* buildserial = LITS_GetSerialNumber(selectdev);
	if (buildserial != NULL) {
		strcpy_s(devserial, 100,  buildserial);
	}
	else {
		//�ر�����
		LITS_SystemClose();
		return DLL_FAILED;
	}

	//��ȡ���ص�
	*PixNum = iPixNum;

	return DLL_SUCCESS;
}

/*********************************
* LED_LITS_SEARCH() �Ͽ�����
*���أ�
*********************************/
DLLEXP void WINAPI LED_LITS_CLOSE()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	LITS_SystemClose();

	selectdev = -1;
}
#pragma endregion 

#pragma region ���ݲɼ�

#pragma region ��������
//ţ�ٲ�ֵ
inline float NewInt_float(float *xa, float *ya, int n, float x)
{
	//ţ�ٲ�ֵ

	int i, k;
	float u;
	k = 1;
	for (i = 1; i <= n - 2; i++)
	{
		if (x <= xa[i])
		{
			k = i;
			break;
		}
		else
			k = n - 1;
	}
	u = (x - xa[k - 1]) / (xa[k] - xa[k - 1]);
	return ya[k - 1] + u*(ya[k] - ya[k - 1]);
}

//ƽ���˲�
inline void SmoothData(double* spdata, int length, int iFilterBW) {
	if (iFilterBW > 1)
	{
		//��ʱ�̶�2048������
		double SpectumNew[5000];
		//������ʱ������
		//for (int i = 0; i <= iFilterBW; i++)
		//	SpectumNew[i] = Spectum[i];

		//for (i = iLength - iFilterBW; i <= iLength - 1; i++)
		//	SpectumNew[i] = Spectum[i];

		for (int i = iFilterBW + 1; i < length - iFilterBW; i++)
		{
			double tempSum = 0.0;
			for (int j = (i - iFilterBW); j <= (i + iFilterBW); j++)
				tempSum = tempSum + spdata[j];

			SpectumNew[i] = tempSum / (2 * iFilterBW + 1);
		}

		for (int i = iFilterBW + 1; i < length - iFilterBW; i++)
		{
			spdata[i] = SpectumNew[i];
		}
	}
}

//ת������ɫ����
inline void ConvertToColor(double* SpectumNew, int iLength, float fIntTime, int iAveNum, float fDx, float fDy, float fSetWL1, float fSetWL2, float IP, COLOR_PARA& dPara)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int i;
	float fAD[2048];
	float fRel[10001];
	dPara.fIp = IP;

	for (i = 0; i < iLength; i++)
	{
		fAD[i] = (float)(SpectumNew[i]);
	}

	float fSpect1 = (float)(g_fSPECT1);
	float fSpect2 = (float)(g_fSPECT2);
	dPara.fSpect1 = fSpect1;
	dPara.fSpect2 = fSpect2;
	float fInterval = 0.1f;
	dPara.fInterval = fInterval;
	int iN = (int)((fSpect2 - fSpect1) / fInterval + 1 + 0.5f);
	float fLastAD = 0;
	float fTempAD;
	float fTempL;

//	char buffer[100];
	//sprintf_s(buffer, "��ʼ��ֵ%d",GetCurrentTime());
	//DllPrint(buffer);
	int iPerStart = 1;
	for (i = 0; i < iN; i++)
	{
		fTempL = fSpect1 + i * fInterval;
		//��崦���һ���������
		if (fTempL < g_fPixWL[0])
		{
			fTempAD = fAD[0];
		}
		else if (fTempL <= g_fPixWL[iLength - 1])
		{
			//��崦������һ���ADֵ
			//fTempAD = NewInt_float(g_fPixWL, fAD, iLength, fTempL);
			if (1)
			{
				int m, k;
				float u;
				k = 1;
				for (m = iPerStart; m <= iLength - 2; m++)
				{
					if (fTempL <= g_fPixWL[m])
					{
						k = m;
						break;
					}
					else
						k = iLength - 1;
				}
				iPerStart = k;
				if ((g_fPixWL[k] - g_fPixWL[k - 1]) != 0)
				{
					u = (fTempL - g_fPixWL[k - 1]) / (g_fPixWL[k] - g_fPixWL[k - 1]);
				}
				else
				{
					u = 0;
				}
				fTempAD = fAD[k - 1] + u*(fAD[k] - fAD[k - 1]);
			}
			fLastAD = fTempAD;
		}
		else
		{
			fTempAD = fLastAD;
		}

		fRel[i] = fTempAD * g_fSP_fK[i];
	}
	
	//sprintf_s(buffer, "������Թ���%d",GetCurrentTime());
	//DllPrint(buffer);

	//��һ����Թ���
	float fMax = fRel[0];

	for (i = 0; i < iN; i++)
	{
		if (fRel[i] > fMax)
		{
			fMax = fRel[i];
		}
	}
	if (fMax <= 0)
	{
		fMax = 1;
	}
	for (i = 0; i < iN; i++)
	{
		fRel[i] = fRel[i] / fMax;
		dPara.fPL[i] = fRel[i];
	}

	//ע�� ȡ��1nm���ݼ���
	float fRel_N[401];
	int   iB = (int)((380.0f - fSpect1) / fInterval + 0.5f);
	int   iE = (int)((780.0f - fSpect1) / fInterval + 0.5f);
	int   NN = (int)(1.0f / fInterval + 0.5f);
	float f;
	for (i = 0; i < 401; i++)
	{
		if ((iB + i*NN) < 0)
		{
			fRel_N[i] = 0;
		}
		else if ((iB + i*NN) <= iE)
		{
			f = fRel[iB + i*NN];
			if (f > 1)
			{
				f = 1;
			}
			fRel_N[i] = f;
		}
		else
		{
			fRel_N[i] = 0;
		}
	}

	//���ֵ
	dPara.fPh = 0;
	for (i = 0; i < 401; i++)
	{
		//float fLamda = 380 + i * 1.0f;
		dPara.fPh = dPara.fPh + fRel_N[i] * fMax * g_fLamdaWL[i];//NH_GetV(fLamda);        //* fMax
	}

	float fPh1 = dPara.fPh;
	dPara.fPh = dPara.fPh * g_fSP_fIntTime * g_fCAL_fFluxK / fIntTime;
	if (dPara.fPh <= 0)
		dPara.fPh = 0;

	for (i = 0; i < iN; i++)
		dPara.fPhe = dPara.fPhe + fRel[i] * fMax* fInterval;

	dPara.fPhe = dPara.fPhe * g_fCAL_fFluxK * g_fSP_fIntTime / fIntTime / 683;
	if (dPara.fPhe <= 0)
		dPara.fPhe = 0;

	dPara.fPlambda = fMax* g_fSP_fIntTime * g_fCAL_fFluxK / fIntTime / 683 * 1000;

	float fPL_N[4096];
	float fWL_N[4096];
	int   MM = (int)(1.0f / fInterval + 0.5f);
	int iNum;
	iNum = 401;
	for (i = 0; i < iNum; i++)
	{
		fWL_N[i] = fSpect1 + i;
		float f = fRel[i*MM];
		if (f > 1)
			f = 1;
		fPL_N[i] = f;
	}
		
	//sprintf_s(buffer, "������ɫ%d",GetCurrentTime());
	//DllPrint(buffer);

	//�����㷨����ɫ����
	NH_CalcColor(fWL_N, fPL_N, iNum, dPara, FALSE, 0.3f, 0.3f);
		
	//sprintf_s(buffer, "������ɫ����%d",GetCurrentTime());
	//DllPrint(buffer);

	if (fDx != 0 || fDy != 0)
	{
		//����ƫ�ú��ɫ�Ȳ���
		float fxx, fyy;
		fxx = dPara.fx + fDx;
		fyy = dPara.fy + fDy;
		float fLD;
		fLD = dPara.fLd;
		NH_CalcColor(fWL_N, fPL_N, iNum, dPara, TRUE, fxx, fyy);
		if (fabs(fLD - dPara.fLd) > 3)
		{
			//	dPara.fLd = fLD;
		}
		dPara.fx = fxx;
		dPara.fy = fyy;
	}

		
	//sprintf_s(buffer, "�����ֵ����%d",GetCurrentTime());
	//DllPrint(buffer);
	if (1)
	{
		//�Ƿ���Ҫ���¼����ֵ����
		int iB, iE;
		iB = (int)((fSetWL1 - fSpect1) / fInterval + 1 + 0.5f);
		iE = (int)((fSetWL2 - fSpect1) / fInterval + 1 + 0.5f);
		if (iB < 0)
		{
			iB = 0;
		}
		if (iE > iN)
		{
			iE = iN;
		}
		if (iB >= iE)
		{
			iB = 0;
			iE = iN;
		}
		//�����ֵ����
		fMax = 0.01f;
		int iMax = iB;

		for (i = 0; i < iN; i++)
		{
			if (dPara.fPL[i] < 0)
			{
				dPara.fPL[i] = 0;
			}
		}

		for (i = iB; i < iE; i++)
		{
			if (dPara.fPL[i] > fMax)
			{
				iMax = i;
				fMax = dPara.fPL[i];
			}
		}
		dPara.fLp = iMax * fInterval + fSpect1;
		if (fMax <= 0)
		{
			fMax = 1;
		}
		int iTempMax = iMax;
		//�����ֵ�������� �ڷ�ֵ���������ҵ㴦��
		int iL = iMax;
		BOOL bLeft = FALSE;	//�Ƿ�����ֵ
		for (i = iMax; i > iB; i--)
		{
			if (dPara.fPL[i] / fMax <= 0.9f)
			{
				iL = i;
				bLeft = TRUE;
				break;
			}
		}

		int iR = iMax;
		BOOL bRight = FALSE;	//�Ƿ�����ֵ
		for (i = iMax; i < iE; i++)
		{
			if (dPara.fPL[i] / fMax <= 0.9f)
			{
				iR = i;
				bRight = TRUE;
				break;
			}
		}
		if (bLeft && bRight)
		{
			iTempMax = (iL + iR) / 2;

			dPara.fLp = iTempMax * fInterval + fSpect1;
		}
	}	
}

//�������ģʽ
DLLEXP int WINAPI LED_LITS_ResetModel()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//����ʼ�����豸��
	if (selectdev < 0) {
		return DEV_NOT_INIT;
	}

	if(SA_API_SUCCESS != LIST_SetTriggerMode(selectdev, SOFTWARE_SYNCHRONOUS))
	{
		return DLL_FAILED;
	}

	return DLL_SUCCESS;
}
#pragma endregion

#pragma region �������ǿ���
float g_fPerIntTime = 0;
int g_fPerAveN = 0;

//��ȡ������
DLLEXP int WINAPI LED_LITS_GetDarkData(SSpectralPar spar, double* fAdValue, int ADlen)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (selectdev < 0) {
		return DEV_NOT_INIT;
	}

	//ȷ�������buffer����������ص����
	if (ADlen < iPixNum) {
		return INVALID_PAR;
	}

	//�·�����ʱ��
	if (g_fPerIntTime!=spar.fIntTime)
	{
		int retry = 0;
		while(SA_API_SUCCESS != LITS_SetIntegrationTime(selectdev, (int)(spar.fIntTime * 1000))) {
			if(retry ++ > 3){
				return DLL_FAILED;
			}
			LITS_SystemClose();
			LITS_SystemOpen();
		}
	}

	//�·�ƽ������
	if (g_fPerAveN!=spar.iAveNum)
	{
		int retry = 0;
		while(SA_API_SUCCESS != LITS_SetAverageTimes(selectdev, spar.iAveNum)) {
			if(retry ++ > 3){
				return DLL_FAILED;
			}
			LITS_SystemClose();
			LITS_SystemOpen();
		}
	}

	
	int retry = 0;
	//trigerģʽֻ�����
	//�ɼ�ԭʼADֵ
	while (SA_API_SUCCESS != LITS_GetSpectralData(selectdev, fAdValue)) {
		if(retry ++ > 3){
			return DLL_FAILED;
		}
		LITS_SystemClose();
		LITS_SystemOpen();
	}

	return DLL_SUCCESS;
}

//��ȡԭʼ����
DLLEXP int WINAPI LED_LITS_GetOriginalData(SSpectralPar spar, float dkdata[], int dklen, double* fAdValue, int ADlen, double* IP)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (selectdev < 0) {
		return DEV_NOT_INIT;
	}

	//ȷ�������buffer����������ص����
	if (ADlen < iPixNum) {
		return INVALID_PAR;
	}

	//�·�����ʱ��
	if (g_fPerIntTime!=spar.fIntTime)
	{
		int retry = 0;
		while (SA_API_SUCCESS != LITS_SetIntegrationTime(selectdev, (int)(spar.fIntTime * 1000))) {
			if(retry ++ > 3){
				return DLL_FAILED;
			}
			LITS_SystemClose();
			LITS_SystemOpen();
		}
	}

	//�·�ƽ������
	if (g_fPerAveN!=spar.iAveNum)
	{
		int retry = 0;
		while (SA_API_SUCCESS != LITS_SetAverageTimes(selectdev, spar.iAveNum)) {
			if(retry ++ > 3){
				return DLL_FAILED;
			}
			LITS_SystemClose();
			LITS_SystemOpen();
		}
	}

	int retry = 0;
	//trigerģʽֻ�����
	//�ɼ�ԭʼADֵ
	while (SA_API_SUCCESS != LITS_GetSpectralData(selectdev, fAdValue)) {
		if(retry ++ > 3){
				return DLL_FAILED;
		}
		LITS_SystemClose();
		LITS_SystemOpen();
	}

	//�������ADֵ
	*IP = 0;
	//����������
	double fAdValueOld[5000];
	for (int i = 0; i < ADlen; i++)
	{
		if (dklen == iPixNum) 
		{
			fAdValueOld[i] = fAdValue[i] - dkdata[i];
		}
		if(*IP < fAdValue[i])
		{
			*IP = fAdValue[i];
		}
	}

	//ƽ���˲�
	SmoothData(fAdValue, ADlen, spar.iFilterBW);

	retry = 0;
	//������У׼
	while (SA_API_SUCCESS != LITS_NonlinearCalibration(selectdev, fAdValueOld, fAdValue, ADlen))
	{
		if(retry ++ > 3){
				return DLL_FAILED;
		}
		LITS_SystemClose();
		LITS_SystemOpen();
	}

	//���˲�
	SA_FilterAD(fAdValue,ADlen);

	return DLL_SUCCESS;
}

//��ȡ������ɫ��������
DLLEXP int WINAPI LED_LITS_GetData(SSpectralPar spar, float dkdata[], int dklen,
	float fDx, float fDy, COLOR_PARA &dPara)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	int iR, iLength;
	iLength = iPixNum;

	double Spectum[5000];
	double IP = 0;
	//�ɼ�ԭʼADֵ
	iR = LED_LITS_GetOriginalData(spar, dkdata, dklen, Spectum, iLength, &IP);
	if (iR != DLL_SUCCESS)
	{
		return iR;
	}	
	
	ConvertToColor(Spectum, iLength, spar.fIntTime, spar.iAveNum, fDx, fDy, 380, 780, (float)IP, dPara);
	
	return DLL_SUCCESS;
}
#pragma endregion 

#pragma region LED+���������

//����LED����
DLLEXP int WINAPI LED_LITS_SetLEDType(int ledtype)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//����ʼ�����豸��
	if (selectdev < 0) {
		return DEV_NOT_INIT;
	}

	int retry  = 0;
	//����ģʽ
	while (SA_API_SUCCESS != LITS_SetLedInterfaceType(selectdev, (BYTE)(ledtype)))
	{
		if(retry ++ > 3){
			return DLL_FAILED;
		}
		LITS_SystemClose();
		LITS_SystemOpen();
	}
	
	return DLL_SUCCESS;
}

//���õ������������
DLLEXP int WINAPI LED_LITS_SetElectricPar(SElectricPar epar, int ledmode)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//����ʼ�����豸��
	if (selectdev < 0) {
		return DEV_NOT_INIT;
	}

	//������鳤�ȣ�����һ���������������
	if (ledmode < 1 || ledmode > 3) {
		return INVALID_PAR;
	}

	int retry  = 0;
	//����ģʽ
	while (SA_API_SUCCESS != LITS_SetMode(selectdev, 0x03, (char)(ledmode - 1)))
	{
		if(retry ++ > 3){
			return DLL_FAILED;
		}
		LITS_SystemClose();
		LITS_SystemOpen();
	}	
	Sleep(30);

	retry  = 0;
	//���ü��Բ��Բ���
	while (SA_API_SUCCESS != LITS_SetPolarityJudgmentPara(
		selectdev, epar.NeVoltage, epar.NeCurrent, epar.NeDelay, epar.NeTime))
	{
		if(retry ++ > 3){
				return DLL_FAILED;
		}
		LITS_SystemClose();
		LITS_SystemOpen();
	}
	Sleep(30);

	for (int i = 0; i < ledmode; i++) {
		retry = 0;
		//�������������������
		while (SA_API_SUCCESS != LITS_SetLedPositivePara(
			selectdev, epar.FVoltage[i], epar.FCurrent[i], epar.FDelay[i], epar.FTime[i], i))
		{
			if(retry ++ > 3){
				return DLL_FAILED;
			}
			LITS_SystemClose();
			LITS_SystemOpen();
		}
		
		Sleep(30);

		retry = 0;
		//�����������ķ������
		while (SA_API_SUCCESS != LITS_SetLedNegativePara(
			selectdev, epar.RVoltage[i], epar.RCurrent[i], epar.RDelay[i], epar.RTime[i], i))
		{
			if(retry ++ > 3){
				return DLL_FAILED;
			}
			LITS_SystemClose();
			LITS_SystemOpen();
		}		
		Sleep(30);
	}
	return DLL_SUCCESS;
}

//��ȡ�������������
DLLEXP int WINAPI LED_LITS_GetElectricPar(SElectricPar& epar, int& ledmode)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//����ʼ�����豸��
	if (selectdev < 0) {
		return DEV_NOT_INIT;
	}

	int retry = 0;
	char mode = 0;
	char cledmode = 0;
	//��ȡģʽ
	while (SA_API_SUCCESS != LITS_GetMode(selectdev, &mode, &cledmode))
	{
		if(retry ++ > 3){
				return DLL_FAILED;
		}
		LITS_SystemClose();
		LITS_SystemOpen();
	}

	ledmode = (int)cledmode + 1;

	retry = 0;
	//���ü��Բ��Բ���
	while (SA_API_SUCCESS != LITS_GetPolarityJudgmentPara(
		selectdev, &epar.NeVoltage, &epar.NeCurrent, &epar.NeDelay, &epar.NeTime))
	{
		if(retry ++ > 3){
				return DLL_FAILED;
		}
		LITS_SystemClose();
		LITS_SystemOpen();
	}

	for (int i = 0; i < 3; i++) {
		retry = 0;
		//�������������������
		while (SA_API_SUCCESS != LITS_GetLedPositivePara(
			selectdev, &epar.FVoltage[i], &epar.FCurrent[i], &epar.FDelay[i], &epar.FTime[i], i))
		{
			if(retry ++ > 3){
				return DLL_FAILED;
			}
			LITS_SystemClose();
			LITS_SystemOpen();
		}
		
		retry = 0;
		//�����������ķ������
		while (SA_API_SUCCESS != LITS_GetLedNegativePara(
			selectdev, &epar.RVoltage[i], &epar.RCurrent[i], &epar.RDelay[i], &epar.RTime[i], i))
		{
			if(retry ++ > 3){
				return DLL_FAILED;
			}
			LITS_SystemClose();
			LITS_SystemOpen();
		}
	}
	return DLL_SUCCESS;
}

DLLEXP int WINAPI LED_LITS_GetSPPar(float * time1, float * time2, float * time3){
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//����ʼ�����豸��
	if (selectdev < 0) {
		return DEV_NOT_INIT;
	}

	int time[3];
	int retry = 0;
	//�·�����ʱ��
	while (SA_API_SUCCESS != LITS_GetChannelIntegrationTime(selectdev
		, &time[0]
		, &time[1]
		, &time[2])) {
			if(retry ++ > 3){
				return DLL_FAILED;
			}
			LITS_SystemClose();
			LITS_SystemOpen();
	}
		
	*time1 = ((float)time[0] / 1000);
	*time2 = ((float)time[1] / 1000);
	*time3 = ((float)time[2] / 1000);

	return DLL_SUCCESS;
}

//���ù����
DLLEXP int WINAPI LED_LITS_SetSPPar(float time1, float time2, float time3, int avr)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//����ʼ�����豸��
	if (selectdev < 0) {
		return DEV_NOT_INIT;
	}
	
	int retry = 0;
	//�·�����ʱ��
	while (SA_API_SUCCESS != LITS_SetChannelIntegrationTime(selectdev
		, (int)(time1 * 1000)
		, (int)(time2 * 1000)
		, (int)(time3 * 1000))) {
			if(retry ++ > 3){
				return DLL_FAILED;
			}
			LITS_SystemClose();
			LITS_SystemOpen();
	}

	retry = 0;
	//�·�ƽ��������ֻ�þ�һ��ƽ������
	if (SA_API_SUCCESS != LITS_SetAverageTimes(selectdev, avr)) {
			if(retry ++ > 3){
				return DLL_FAILED;
			}
			LITS_SystemClose();
			LITS_SystemOpen();
	}

	return DLL_SUCCESS;
}

//��ȡ�������3��ԭʼ����
DLLEXP int WINAPI LED_LITS_GetLEDOriginalData(
	TRIGGER_MODE mode,
	int filternum,
	float dkdata1[],
	float dkdata2[],
	float dkdata3[], int dklen,
	double* fAdValue1, 
	double* fAdValue2,
	double* fAdValue3,int ADlen,
	SElectricData & ePara1,
	SElectricData & ePara2,
	SElectricData & ePara3, int ledmode, int timeout)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//����ʼ�����豸��
	if (selectdev < 0) {
		return DEV_NOT_INIT;
	}

	//������鳤�ȣ�����һ���������������
	if (ledmode < 1 || ledmode > 3 || ADlen != iPixNum) {
		return INVALID_PAR;
	}

	int iLength = iPixNum;
	int retry = 0;

	float* dkdata[3];
	SElectricData* ePara[3];

	dkdata[0] = dkdata1;
	dkdata[1] = dkdata2;
	dkdata[2] = dkdata3;

	ePara[0] = &ePara1;
	ePara[1] = &ePara2;
	ePara[2] = &ePara3;

	
	//��������ADbuffer�������������buffer
	double SpectumNew [5000];
	double* Spectum[3] = {fAdValue1,fAdValue2, fAdValue3};

	float electrl1 [10];
	float electrl2 [10];
	float electrl3 [10];
	float* electrl[3] = {electrl1,electrl2,electrl3};

	//�ɼ�����
	if (mode == EXINT_RISING_EDGE
		|| mode == EXINT_FALLING_EDGE
		|| mode == EXINT_HIGH_LEVEL
		|| mode == EXINT_LOW_LEVEL)
	{
		if(SA_API_SUCCESS != LITS_GetMeasureDataHWTrigger(selectdev, Spectum[0], electrl[0],
			Spectum[1], electrl[1], Spectum[2], electrl[2], mode, timeout)){				
				LIST_SetTriggerMode(selectdev, SOFTWARE_SYNCHRONOUS);	
				return DLL_FAILED;
		}

		LIST_SetTriggerMode(selectdev, SOFTWARE_SYNCHRONOUS);			
	}
	else
	{
		while(SA_API_SUCCESS != LITS_GetMeasureData(selectdev, Spectum[0], electrl[0],
			Spectum[1], electrl[1], Spectum[2], electrl[2])){
			if(retry ++ > 3){
				return DLL_FAILED;
			}
			LITS_SystemClose();
			LITS_SystemOpen();
		}
	}

	//ѭ��������
	for (int idex = 0; idex < ledmode; idex++) {
		//��ȡ�����
		ePara[idex]->NeType = electrl[idex][0];
		ePara[idex]->fVol = electrl[idex][1];
		ePara[idex]->fIr = electrl[idex][2];

		//ƽ���˲�
		SmoothData(Spectum[idex], iLength, filternum);
		
		//�������ADֵ
		//dPara[idex]->fIp = 0;
		//for (int i = 0; i < iLength; i++)
		//{
			//�������ֵ
		//	if (dPara[idex]->fIp < Spectum[idex][i])
		//	{
		//		dPara[idex]->fIp = (float)(Spectum[idex][i]);
		//	}
		//}
		
		//����������
		if (dklen == iLength) {
			for (int i = 0; i < iLength; i++)
			{
				Spectum[idex][i] = Spectum[idex][i] - dkdata[idex][i];
			}
		}

		retry = 0;
		//������У׼
		while (SA_API_SUCCESS != LITS_NonlinearCalibration(selectdev, Spectum[idex], SpectumNew, iLength))
		{
			if(retry ++ > 3){
				return DLL_FAILED;
			}
			LITS_SystemClose();
			LITS_SystemOpen();
		}

		//У׼������ݣ�copy��ԭʼ������
		memcpy(Spectum[idex], SpectumNew, iLength * sizeof(double));

		//���˲�
		SA_FilterAD(SpectumNew,iLength);
	}

	return DLL_SUCCESS;
}

//��ȡ�������3����ɫ����
DLLEXP int WINAPI LED_LITS_GetLEDData(
	SSpectralPar spar1,
	SSpectralPar spar2,
	SSpectralPar spar3,
	float dkdata1[],
	float dkdata2[],
	float dkdata3[], int dklen,
	float fDx[], float fDy[],
	COLOR_PARA& dPara1,
	COLOR_PARA& dPara2,
	COLOR_PARA& dPara3,
	SElectricData & ePara1,
	SElectricData & ePara2,
	SElectricData & ePara3, int ledmode, int timeout)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//����ʼ�����豸��
	if (selectdev < 0) {
		return DEV_NOT_INIT;
	}

	//������鳤�ȣ�����һ���������������
	if (ledmode < 1 || ledmode > 3) {
		return INVALID_PAR;
	}

	int iLength = iPixNum;
	int retry = 0;

	float* dkdata[3];
	SSpectralPar spar[3];
	COLOR_PARA* dPara[3];
	SElectricData* ePara[3];

	dkdata[0] = dkdata1;
	dkdata[1] = dkdata2;
	dkdata[2] = dkdata3;

	spar[0] = spar1;
	spar[1] = spar2;
	spar[2] = spar3;

	dPara[0] = &dPara1;
	dPara[1] = &dPara2;
	dPara[2] = &dPara3;

	ePara[0] = &ePara1;
	ePara[1] = &ePara2;
	ePara[2] = &ePara3;

	
	//��������ADbuffer�������������buffer
	double Spectum1 [5000];
	double Spectum2 [5000];
	double Spectum3 [5000];
	double SpectumNew [5000];
	double* Spectum[3] = {Spectum1,Spectum2, Spectum3};

	float electrl1 [10];
	float electrl2 [10];
	float electrl3 [10];
	float* electrl[3] = {electrl1,electrl2,electrl3};

	//char tmp [100];
	//sprintf(tmp, "mode:%d", spar[0].TriggerMode);
	//AfxMessageBox(tmp);
	//�ɼ�����
	if (spar[0].TriggerMode == EXINT_RISING_EDGE
		|| spar[0].TriggerMode == EXINT_FALLING_EDGE
		|| spar[0].TriggerMode == EXINT_HIGH_LEVEL
		|| spar[0].TriggerMode == EXINT_LOW_LEVEL)
	{
		if(SA_API_SUCCESS != LITS_GetMeasureDataHWTrigger(selectdev, Spectum[0], electrl[0],
			Spectum[1], electrl[1], Spectum[2], electrl[2], spar[0].TriggerMode, timeout)){
			LIST_SetTriggerMode(selectdev, SOFTWARE_SYNCHRONOUS);	
			return DLL_FAILED;
		}
		
		LIST_SetTriggerMode(selectdev, SOFTWARE_SYNCHRONOUS);	
	}
	else
	{		
		while(SA_API_SUCCESS != LITS_GetMeasureData(selectdev, Spectum[0], electrl[0],
			Spectum[1], electrl[1], Spectum[2], electrl[2])){
			if(retry ++ > 3){
				return DLL_FAILED;
			}
			LITS_SystemClose();
			LITS_SystemOpen();
		}
	}

	//ѭ��������
	for (int idex = 0; idex < ledmode; idex++) {
		//��ȡ�����
		ePara[idex]->NeType = electrl[idex][0];
		ePara[idex]->fVol = electrl[idex][1];
		ePara[idex]->fIr = electrl[idex][2];

		//char buffer[100];
		//sprintf_s(buffer, "%f, %f, %f", electrl[idex][0], electrl[idex][1], electrl[idex][2]);
		//AfxMessageBox(buffer);

		//ƽ���˲�
		SmoothData(Spectum[idex], iLength, spar[0].iFilterBW);
		
		//�������ADֵ
		dPara[idex]->fIp = 0;
		for (int i = 0; i < iLength; i++)
		{
			//�������ֵ
			if (dPara[idex]->fIp < Spectum[idex][i])
			{
				dPara[idex]->fIp = (float)(Spectum[idex][i]);
			}
		}
		
		//����������
		if (dklen == iLength) {
			for (int i = 0; i < iLength; i++)
			{
				Spectum[idex][i] = Spectum[idex][i] - dkdata[idex][i];
			}
		}

		retry = 0;
		//������У׼
		while (SA_API_SUCCESS != LITS_NonlinearCalibration(selectdev, Spectum[idex], SpectumNew, iLength))
		{
			if(retry ++ > 3){
				return DLL_FAILED;
			}
			LITS_SystemClose();
			LITS_SystemOpen();
		}

		//У׼������ݣ�copy��ԭʼ������
		memcpy(Spectum[idex], SpectumNew, iLength * sizeof(double));

		//���˲�
		SA_FilterAD(SpectumNew,iLength);

		//ת���ɹ����
		ConvertToColor(SpectumNew, iLength, spar[idex].fIntTime, spar[0].iAveNum, fDx[idex], fDy[idex], 380, 780, dPara[idex]->fIp, (*dPara[idex]));

	}

	return DLL_SUCCESS;
}

DLLEXP int WINAPI LED_LITS_SetBin(int bin)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//����ʼ�����豸��
	if (selectdev < 0) {
		return DEV_NOT_INIT;
	}
	int retry = 0;
	while(SA_API_SUCCESS != LITS_SetBinOutput(selectdev, bin))
	{
		if(retry ++ > 3){
			return DLL_FAILED;
		}
		LITS_SystemClose();
		LITS_SystemOpen();
	}

	return DLL_SUCCESS;
}
#pragma endregion 

#pragma endregion 

#pragma region ����

DLLEXP int WINAPI LED_LITS_ReCal(COLOR_PARA &dPara, float fDx, float fDy)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (fDx != 0 || fDy != 0)
	{
		float fPL_N[4096];
		float fWL_N[4096];
		int   MM = (int)(1.0f / dPara.fInterval + 0.5f);
		int iNum;
		iNum = (int)((dPara.fSpect2 - dPara.fSpect1) + 1);
		for (int i = 0; i < iNum; i++)
		{
			fWL_N[i] = dPara.fSpect1 + i;
			float f = dPara.fPL[i*MM];
			if (f > 1)
				f = 1;
			fPL_N[i] = f;
		}

		//����ƫ�ú��ɫ�Ȳ���
		float fxx, fyy;
		fxx = dPara.fx + fDx;
		fyy = dPara.fy + fDy;
		float fLD;
		fLD = dPara.fLd;
		NH_CalcColor(fWL_N, fPL_N, iNum, dPara, TRUE, fxx, fyy);
		if (fabs(fLD - dPara.fLd) > 3)
		{
			//	dPara.fLd = fLD;
		}
		dPara.fx = fxx;
		dPara.fy = fyy;
	}
	return DLL_SUCCESS;
}

DLLEXP int WINAPI LED_LITS_Calib(SSpectralPar spar, float dkdata[], int dklen,
	int iCalType,
	float fCCT,
	float fFlux,
	int iStaNum,    //�����
	float fStaWL[], //����
	float fStaPL[], //���ֵ
	float &fIp)
{
	//iCalType: 0ʹ��ɫ�·����㶨��
	//			1ʹ�õ���ľ��Թ��׶���
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	int iR, iLength;
	iLength = iPixNum;

	double Spectum[5000];
	double IP = 0;
	//�ɼ�ԭʼADֵ
	iR = LED_LITS_GetOriginalData(spar, dkdata, dklen, Spectum, iLength, &IP);
	if (iR != DLL_SUCCESS)
	{
		return iR;
	}

	float fPixWL[2048];
	float fAD[2048];
	float fMax = (float)IP;
	//fIp = 0;
	//for (int i = 0; i < iLength; i++)
	//{
	//	if (fIp < Spectum[i])
	//	{
	//		fIp = (float)(Spectum[i]);
	//	}
	//	if (Spectum[i] > fMax)
	//		fMax = (float)(Spectum[i]);
	//}
	if (fMax < 10000)
	{
		//AfxMessageBox("���������ʱ��!");
		return TIME_TOO_SMALL;
	}

	if (fMax > 60000)
	{
		//AfxMessageBox("���С����ʱ��!");
		return TIME_TOO_BIG;
	}

	for (int i = 0; i < iLength; i++)
	{
		fPixWL[i] = (float)(g_fCCor[0]
			+ g_fCCor[1] * i
			+ g_fCCor[2] * i * i
			+ g_fCCor[3] * i * i * i);
		fAD[i] = (float)(Spectum[i]);
	}
	
	float fPL[10001];
	float fSpect1 = g_startWL;
	float fSpect2 = g_stopWL;
	float fInterval = 0.1f;
	int iNum = (int)((fSpect2 - fSpect1) / fInterval + 1 + 0.5f);
	float fLastAD = 0;
	for (int i = 0; i < iNum; i++)
	{
		fPL[i] = NewInt_float(fPixWL, fAD, iLength, fSpect1 + i * fInterval);
		float fTempL = fSpect1 + i * fInterval;
		float fTempAD;
		//��崦���һ���������
		if (fTempL < fPixWL[0])
		{
			fTempAD = fAD[0];
		}
		//��崦������һ���ADֵ
		else if (fTempL <= fPixWL[iLength - 1])
		{
			fTempAD = NewInt_float(fPixWL, fAD, iLength, fTempL);
			fLastAD = fTempAD;
		}
		else
		{
			fTempAD = fLastAD;
		}
		fPL[i] = fTempAD;
	}

	if (iCalType == 0)
	{
		//ɫ�·����㶨��ϴ��
		float c1 = (float)(3.741844E19*9.58378 / 8.071367);
		float c2 = (float)(1.438833E7 / fCCT);

		g_fSP_fSpect1 = fSpect1;
		g_fSP_fSpect2 = fSpect2;
		g_fSP_fInterval = fInterval;
		g_fSP_fStaTc = fCCT;
		g_fSP_fIntTime = spar.fIntTime;
		g_fCAL_fStaFlux = fFlux;

		//CTime tNow;
		//tNow = CTime::GetCurrentTime();
		//CString sNow = tNow.Format("%Y-%m-%d,%H:%M");
		//CString SP_strDate = sNow;
		int i;
		for (i = 0; i < iNum; i++)
		{
			float lamda = fSpect1 + i * fInterval;
			float fRel;
			double fTemp;
			fRel = fPL[i];
			if (fRel <= 0)
			{
				fTemp = 0;
			}
			else
			{
				fTemp = (double)((c1 / pow(lamda, 5) / (exp(c2 / lamda) - 1)) / fRel);
			}

			g_fSP_fK[i] = (float)(fTemp);
		}

		//���ݹ�ͨ�����ֹ�ʽ���㶨������
		double d = 0;
		for (i = 0; i < 401; i++)
		{
			float lamda = 380 + i*1.0f;
			d = d + (c1 / pow(lamda, 5) / (exp(c2 / lamda) - 1)) * NH_GetV(lamda);
		}

		// ��ǿ���նȼ���
		float fTempPh;
		fTempPh = fFlux;

		if (d > 0)
			g_fCAL_fFluxK = (float)(fFlux / d);
		else
			g_fCAL_fFluxK = 1.0f;
		g_fCAL_fStaFlux = fTempPh;

		CString sTemp;
		sTemp = "Cal_standard.nh";   //��

		/* AAA.�½�Ŀ¼ */
		CString strPathName = g_strCurPath + "Calibration\\";
		CreateDirectory(strPathName, NULL);
		SHChangeNotify(SHCNE_MKDIR, SHCNF_PATH, strPathName, 0);

		//���׶������ݱ���
		FILE *fp;
		if (fopen_s(&fp, g_strCurPath + "Calibration\\" + sTemp, "wt"))
		{
			return SA_API_FAIL;
		}
		else
		{
			fprintf_s(fp, "%.0fK Time:%.2f\n", g_fSP_fStaTc, g_fSP_fIntTime);
			fprintf_s(fp, "%.1f %.1f %.3f\n", g_fSP_fSpect1, g_fSP_fSpect2, g_fSP_fInterval);
			//fprintf_s(fp, SP_strDate + "\n");
			fprintf_s(fp, "%.3f  %.9f\n", g_fCAL_fStaFlux, g_fCAL_fFluxK);

			for (i = 0; i < iNum; i++)
			{
				fprintf_s(fp, "%.1f %.5e %.1f \n", g_fSP_fSpect1 + i * g_fSP_fInterval, g_fSP_fK[i], fPL[i]);
			}
		}
		fclose(fp);
	}
	else
	{
		//ʹ�õ���ľ��Թ������ݼ���
		g_fSP_fSpect1 = fSpect1;
		g_fSP_fSpect2 = fSpect2;
		g_fSP_fInterval = fInterval;
		g_fSP_fStaTc = fCCT;
		g_fSP_fIntTime = spar.fIntTime;
		g_fCAL_fStaFlux = fFlux;

		//CTime tNow;
		//tNow = CTime::GetCurrentTime();
		//CString sNow = tNow.Format("%Y-%m-%d,%H:%M");
		//CString SP_strDate = sNow;
		int i;
		for (i = 0; i < iNum; i++)
		{
			float lamda = fSpect1 + i * fInterval;
			float fRel;
			double fTemp;
			fRel = fPL[i];
			float fStd;
			fStd = NewInt_float(fStaWL, fStaPL, iStaNum, fSpect1 + i * fInterval);
			if (fRel <= 0)
			{
				fTemp = 0;
			}
			else
			{
				fTemp = (double)(fStd / fRel);
			}

			g_fSP_fK[i] = (float)(fTemp);
		}

		//���ݹ�ͨ�����ֹ�ʽ���㶨������
		double d = 0;
		for (i = 0; i < 401; i++)
		{
			float lamda = 380 + i*1.0f;
			float fStd;
			fStd = NewInt_float(fStaWL, fStaPL, iStaNum, lamda);
			d = d + fStd * NH_GetV(lamda);
		}

		// ��ǿ���նȼ���
		float fTempPh;
		fTempPh = fFlux;

		if (d > 0)
			g_fCAL_fFluxK = (float)(fFlux / d);
		else
			g_fCAL_fFluxK = 1.0f;
		g_fCAL_fStaFlux = fTempPh;

		CString sTemp;
		sTemp = "Cal_standard.nh";   //��

		/* AAA.�½�Ŀ¼ */
		CString strPathName = g_strCurPath + "Calibration\\";
		CreateDirectory(strPathName, NULL);
		SHChangeNotify(SHCNE_MKDIR, SHCNF_PATH, strPathName, 0);

		//���׶������ݱ���
		FILE *fp;
		if (fopen_s(&fp, g_strCurPath + "Calibration\\" + sTemp, "wt"))
		{
			return SA_API_FAIL;
		}
		else
		{
			fprintf_s(fp, "%.0fK Time:%.2f\n", g_fSP_fStaTc, g_fSP_fIntTime);
			fprintf_s(fp, "%.1f %.1f %.3f\n", g_fSP_fSpect1, g_fSP_fSpect2, g_fSP_fInterval);
			//fprintf_s(fp, SP_strDate + "\n");
			fprintf_s(fp, "%.3f  %.9f\n", g_fCAL_fStaFlux, g_fCAL_fFluxK);

			for (i = 0; i < iNum; i++)
			{
				fprintf_s(fp, "%.1f %.5e %.1f \n", g_fSP_fSpect1 + i * g_fSP_fInterval, g_fSP_fK[i], fPL[i]);
			}
		}
		fclose(fp);
	}

	return DLL_SUCCESS;
}
#pragma endregion

