// ProcessData.cpp: implementation of the CProcessData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ProcessData.h"
#include "Global_MySpec.h"
#include "ExGetColorParaDLL.h"

#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern BOOL g_bRaShowNeg;

CProcessData::CProcessData()
{
}

CProcessData::~CProcessData()
{

}

void CProcessData::xyTOuv(float x, float y, float &u, float &v)
{
	u=(4*x)/(-2*x+12*y+3);
	v=(6*y)/(-2*x+12*y+3);
}

void CProcessData::uvTOxy(float u, float v, float &x, float &y)
{
	float a11,a12,c1;
	float a21,a22,c2;
	a11 = -4-2*u;
	a12 = 12*u;
	c1  = -3*u;
	a21 = -2*v;
	a22 = 12*v-6;
	c2  = -3*v;
	y   = ((a21/a11)*c1-c2)/((a21/a11)*a12-a22);
	x   = (c2-a22*y)/a21;
}

void CProcessData::XYZTOxyz(float X, float Y, float Z, float &x, float &y, float &z)
{
	x = X/(X+Y+Z);
	y = Y/(X+Y+Z);
	z = Z/(X+Y+Z);
}

BOOL CProcessData::GetStandardRen(CString sPathName)
{
	//
	//1.读取CIE BMP
	CString strTemp;

	strTemp=sPathName+"CIE1931.bmp";
	m_ImageCIE_xy.Load(strTemp);

	strTemp=sPathName+"CIE1976.bmp";
	m_ImageCIE_uv.Load(strTemp);

	return TRUE;

// 	//2.读取标准数据
// 	FILE *fp;
// 	int i,j;
// 	BOOL  b1;
// 	BOOL  b2;
// 	BOOL  b3;
// 	BOOL  b4;
// 	BOOL  b5;
// 	BOOL  b6;
// 	if((fp=fopen(sPathName+"standard.ren","rb"))==NULL)
// 	{
// 		b1=FALSE;
// 	}
// 	else
// 	{
// 		b1=TRUE;
// 		for(j=0;j<15;j++)
// 			for(i=0;i<81;i++)
// 				fread(&s15[i][j],4,1,fp);
// 			for(i=0;i<75;i++)
// 				for(j=0;j<15;j++)
// 				{
// 					fread(&ustar[i][j],4,1,fp);
// 					fread(&vstar[i][j],4,1,fp);
// 					fread(&wstar[i][j],4,1,fp);
// 				}
// 		 ustar[17][0]=30.97f;//for error 
// 		 vstar[53][3]=9.53f;
// 		 fclose(fp);
// 	}
// 	if((fp=fopen(sPathName+"standard.xyz","rb"))==NULL)
// 	{
// 		b2=FALSE;
// 	}
// 	else
// 	{
// 		b2=TRUE;
// 		for(i=0;i<81;i++)
// 		{
// 			fread(&x5[i],4,1,fp);
// 			fread(&y5[i],4,1,fp);
// 			fread(&z5[i],4,1,fp);
// 		}
// 		for(i=0;i<75;i++)
// 		{
// 			fread(&up[i],4,1,fp);
// 			fread(&vp[i],4,1,fp);
// 			fread(&mired[i],4,1,fp);
// 		}
// 		fclose(fp);
// 	}
// 	//在原来的个数
// 	m_mired_iN=75;
// 	m_mired_iAddN=0;
// 
// 	//新增加的mired表格
// 	if((fp=fopen(sPathName+"standard.xyz2","rt"))==NULL)
// 	{
// 	}
// 	else
// 	{
// 		float up_temp[75+10],vp_temp[75+10],mired_temp[75+10];
// 		int iN;
// 		fscanf(fp,"mired:%d\n",&iN);
// 		if(iN>=10)
// 			iN=0;
// 		for(i=0;i<iN;i++)
// 			fscanf(fp,"%f %f %f\n",&up_temp[i],&vp_temp[i],&mired_temp[i]);
// 		
// 		for(i=iN;i<iN+m_mired_iN;i++)
// 		{
// 			up_temp[i]    = up[i-iN];
// 			vp_temp[i]    = vp[i-iN];
// 			mired_temp[i] = mired[i-iN];
// 		}
// 		for(i=0;i<iN+m_mired_iN;i++)
// 		{
// 			up[i]    = up_temp[i];
// 			vp[i]    = vp_temp[i];
// 			mired[i] = mired_temp[i];
// 		}
// 
// 		//在原来基础由增加个数
// 		m_mired_iN=m_mired_iN+iN;
// 		//保存增加的个数
// 		m_mired_iAddN=iN;
// 
// 		fclose(fp);
// 	}
// 
// 	//最小的mired值
// 	m_mired_fMin=mired[0];
// 	if((fp=fopen(sPathName+"stad1nm.xyz","rb"))==NULL)
// 	{
// 		b3=FALSE;
// 	}
// 	else
// 	{
// 		b3=TRUE;
// 		for(i=0;i<401;i++)
// 		{
// 			fread(&x1[i],4,1,fp);
// 			fread(&y1[i],4,1,fp);
// 			fread(&z1[i],4,1,fp);
// 		}
// 	}
// 	if((fp=fopen(sPathName+"xy001.ex","rt"))==NULL)
// 	{
// 		b4=FALSE;
// 	}
// 	else
// 	{
// 		b4=TRUE;
// 		float f;
// 		for(i=0;i<40001;i++)
// 			fscanf(fp,"%f %f %f\n",&f,&x001ex[i],&y001ex[i]);
// 	}    
// 
// 	if((fp=fopen(sPathName+"\\Cal\\uvstdspec.dat","rt"))==NULL)
// 	{
// 		b5=FALSE;
// 	}
// 	else
// 	{
// 		b5=TRUE;
// 		int iTemp;
// 		float  fTemp1[20];
// 		double fTemp2[20];
// 		for(i=0;i<19;i++)
// 		{
// 			fscanf(fp,"%d: %f",&iTemp,&fTemp1[i]);
// 			fTemp2[i]=fTemp1[i];
// 		}
// 		fclose(fp);
// 		for(i=0;i<2001;i++)
// 		{
// 			m_uvpl[i]=(float)Lagrange(200,10,19,fTemp2,200+i*0.1f);
// 		}
// 	}    
// 	
// 	if((fp=fopen(sPathName+"SUV.tab","rt"))==NULL)
// 	{
// 		b6=FALSE;
// 	}
// 	else
// 	{
// 		b6=TRUE;
// 		m_iSUV_N=0;
// 		float f1,f2;
// 		while(1)
// 		{
// 			fscanf(fp,"%f %f\n",&f1,&f2);
// 			if(f1==0&&f2==0)
// 				break;
// 			if(m_iSUV_N>=200)
// 				break;
// 
// 			m_arra_fWAL[m_iSUV_N]=f1;
// 			m_arra_fSUV[m_iSUV_N]=f2;
// 			m_iSUV_N++;
// 		}
// 		fclose(fp);
// 	}    
// 
// 	float fPL[201],fWL[201];
// 	for(i=0;i<m_iSUV_N;i++)
// 	{
// 		fWL[i]=m_arra_fWAL[i];
// 		fPL[i]=m_arra_fSUV[i];
// 	}
// 
// 	if((fp=fopen(sPathName+"SUV_2.tab","wt"))==NULL)
// 	{
// 	}
// 	else
// 	{
// 		for(i=0;i<2001;i++)
// 		{
// 			float fLamda=200+i*0.1f;
// 			float fTemp;
// 			fTemp=NewInt_float(fWL,fPL,m_iSUV_N,fLamda);
// 			fprintf(fp,"%.1f %.3f\n",fLamda,fTemp);
// 		}
// 		fclose(fp);
// 	}    
// 	
// 	if(b1&&b2&&b3&&b4)
// 		return TRUE;
// 	CString s1,s2,s3,s4;
// 	if(g_bEnglish)
// 	{
// 		if(b1)
// 			s1="  1.standard.ren.";
// 		else
// 			s1="* 1.standard.ren.";
// 		if(b2)
// 			s2="  2.standard.xyz.";
// 		else
// 			s2="* 2.standard.xyz.";
// 		if(b3)
// 			s3="  3.stad1nm.xyz.";
// 		else
// 			s3="* 3.stad1nm.xyz.";
// 		if(b4)
// 			s4="  4.xy001.ex.";
// 		else
// 			s4="* 4.xy001.ex.";
// 		AfxMessageBox("Can not Find Relative File,Please Connected With NAHON Instrument Co.,Ltd!\n\n"+s1+"\n"+s2+"\n"+s3+"\n"+s4,NULL,MB_ICONWARNING);
// 	}
// 	else
// 	{
// 		if(b1)
// 			s1="  1.standard.ren 找到.";
// 		else
// 			s1="* 1.standard.ren 未找到.";
// 		if(b2)
// 			s2="  2.standard.xyz 找到.";
// 		else
// 			s2="* 2.standard.xyz 未找到.";
// 		if(b3)
// 			s3="  3.stad1nm.xyz  找到.";
// 		else
// 			s3="* 3.stad1nm.xyz  未找到.";
// 		if(b4)
// 			s4="  4.xy001.ex     找到.";
// 		else
// 			s4="* 4.xy001.ex     未找到.";
// 		AfxMessageBox("未找到相关文件,请与远方公司联系!\n\n"+s1+"\n"+s2+"\n"+s3+"\n"+s4,NULL,MB_ICONWARNING);
// 	}
	return FALSE;
}

void CProcessData::Process51(int iN,float fWL[],float fPL[],
							 float &fx, float &fy, float &fu, float &fv,
							 float &fRedRatio,float &fGreenRatio,float &fBlueRatio,
							 float &fMaxslamda,float &fHaveWidth,
							 float &fCCT,float &fdc, float &fRa, float *fRi,float &fMainWave,
							 float &fQuality)
{
	COLOR_PARA para;
	//按新算法计算色参数
	NH_GetColorPara(fWL, fPL,iN, para);
	fx  = para.fx;
	fy  = para.fy;
	fu  = para.fu;
	fv  = para.fv;
	fCCT = para.fCCT;
	fdc  = para.dC;
	fRedRatio  = para.fRR;
	fGreenRatio= para.fGR;
	fBlueRatio = para.fBR;
	fHaveWidth = para.fHW;
	fMaxslamda = para.fLp;
	fMainWave  = para.fLd;
	fQuality   = para.fPur;
	fRa  = para.fRa;
	for(int t=0;t<15;t++)
		fRi[t]=para.fRi[t];
	//重新计算U' V'1976
	fu=(4*fx)/(-2*fx+12*fy+3);
	fv=(9*fy)/(-2*fx+12*fy+3);

	if(!g_bRaShowNeg)//不显示负数
	{
		for(int i=0;i<15;i++)
		{
			if(fRi[i]<0)
				fRi[i]=0;
		}
		fRa = (float)(fRi[0]+fRi[1]+fRi[2]+fRi[3]+fRi[4]+fRi[5]+fRi[6]+fRi[7])/8;
	}
	return;
}

float CProcessData::maximums(float arr[], float *pt1, int *pt2, int n)
{
	int i;
	*pt1=arr[0];
	*pt2=0;
	for(i=1;i<n;i++)
	{
		if(*pt1<arr[i])
		{
			*pt1=arr[i];
			*pt2=i;
		}
	}
	return *pt1;
}

void CProcessData::Getxy(float fLamda, float &x, float &y)
{
	//得到色度图的边缘坐标
	double xx,yy,zz;
	int iLamdaPos=int((fLamda-380.0f)*100);
	xx=x001[iLamdaPos];
	yy=y001[iLamdaPos];
	zz=z001[iLamdaPos];
	xx=(xx*100.0/yy);
	zz=(zz*100.0/yy);
	yy=100.0;
	x=(float)(xx/(xx+yy+zz));
	y=(float)(yy/(xx+yy+zz));
}

BOOL CProcessData::GetMaxWaveAndQuality(float x, float y, float &fMaxWave, float &fQuality)
{
	double Mind;
	float a,b,c;
	float xex,yex;
	const float x_e=0.333333f;
	const float y_e=0.333333f;
	double d;

	TwoPointGetLine(x_e,y_e,x,y,a,b,c);
	Mind=100;

	int i;

	int D=5;       //nm
	int MM=500;    //D/0.01f
	int iPos=0;

	//粗找
	for(i=0;i<(40001-1)/MM+1;i++)
	{
		d=GetPointToLineDistance(x001ex[i*MM],y001ex[i*MM],a,b,c);
		BOOL b1,b2;
		b1=FALSE;
		b2=FALSE;
		if((x_e-x)*(x_e-x001ex[i*MM])>=0)
			b1=TRUE;
		if((y_e-y)*(y_e-y001ex[i*MM])>=0)
			b2=TRUE;
		if(b1&&b2&&(d<=Mind))
		{
			iPos=i*MM;
			fMaxWave=380+0.01f*i*MM;
			Mind=d;
			xex=x001ex[i*MM];
			yex=y001ex[i*MM];
		}
	}

	int iB,iE;
	iB=iPos-MM*1;
	iE=iPos+MM*1;
	if(iB<0)
		iB=0;
	if(iE>40000)
		iE=40000;
	//细找
	for(i=iB;i<=iE;i++)
	{
		d=GetPointToLineDistance(x001ex[i],y001ex[i],a,b,c);
		BOOL b1,b2;
		b1=FALSE;
		b2=FALSE;
		if((x_e-x)*(x_e-x001ex[i])>=0)
			b1=TRUE;
		if((y_e-y)*(y_e-y001ex[i])>=0)
			b2=TRUE;
		if(b1&&b2&&(d<=Mind))
		{
			fMaxWave=380+0.01f*i;
			Mind=d;
			xex=x001ex[i];
			yex=y001ex[i];
		}
	}
	//if(Mind>0.0001)
	//	return FALSE;

	double A=sqrt(pow((x-x_e),2)+pow((y-y_e),2));
	double B=sqrt(pow((xex-x_e),2)+pow((yex-y_e),2));
    fQuality=(float)((A/B)*100);
	if(fQuality>=100)
		fQuality=100;
	if(fQuality<=0)
		fQuality=0;
	return TRUE;
}

double CProcessData::GetPointToLineDistance(float xPoint, float yPoint, float aLine, float bLine,float cLine)
{
    //Solve d
    //line: aLine*x+bLine*y=cLine
	//Point xPoint,yPoint
	double d;
	if(aLine==0)
		d=fabs(cLine/bLine-yPoint);
	else if(bLine==0)
		d=fabs(cLine/aLine-xPoint);
	else
	{
		long double kL,bL;//y=kL*x+bL
		kL=-1*aLine/bLine;
		bL=cLine/bLine;
		double xd,yd;
		xd=(yPoint+(1/kL)*xPoint-bL)/(kL+1/kL);
		yd=kL*xd+bL;
		d=sqrt(pow((xd-xPoint),2)+pow((yd-yPoint),2));
	}
	return d;
}

void CProcessData::TwoPointGetLine(float x1, float y1, float x2, float y2, float &a, float &b, float &c)
{
R:	if(x1==x2&&y1==y2)
	{
		x1=x1-0.0001f;
		goto R;
	}
	else if(x1==x2)
	{
		a=1;
		b=0;
		c=x1;
	}
	else if(y1==y2)
	{
		a=0;
		b=1;
		c=y1;
	}
	else
	{
		long double k;
		k=(y1-y2)/(x1-x2);
		a=(float)(-1*k*1000);
		b=1000;
		c=(float)((y1-k*x1)*1000);
	}
}

int CProcessData::iHalfWave(float f[], int iN)
{
	int i;
	int iMax;
	float fMax;
	fMax=g_fMax(f,iN,iMax);
	int iL,iR;
	iL=0;
	iR=iN-1;
	for(i=iMax;i>=0;i--)
	{
		if(f[i]<=0.5*fMax)
		{
			iL=i;
			break;
		}
	}
	for(i=iMax;i<iN;i++)
	{
		if(f[i]<=0.5*fMax)
		{
			iR=i;
			break;
		}
	}
	return iR-iL;
}

void CProcessData::GetRGB(float fSpect, int &R, int &G, int &B)
{
	if(fSpect<380)
		fSpect=380;
	if(fSpect>780)
		fSpect=780;

	int iSPE1=450;
	int iSPE2=520;
	int iSPE3=620;
	if(fSpect<=iSPE1)
	{
		R=0;
		G=0;
		B=(int)(255*(fSpect-380)/(iSPE1-380));
	}
	else if(fSpect<iSPE2)
	{
		float k1=255*2.0f/(iSPE2-iSPE1);
		float b1=-iSPE1*k1;
		int m1=(int)(k1*fSpect+b1);

		float k2=255*2.0f/(iSPE1-iSPE2);
		float b2=-iSPE2*k2;
		int m2=(int)(k2*fSpect+b2);
		if(m1>=255)
			m1=255;
		if(m1<=0)
			m1=0;
		if(m2>=255)
			m2=255;
		if(m2<=0)
			m2=0;
		R=0;
		G=m1;
		B=m2;
	}
	else if(fSpect<iSPE3)
	{
		float k1=255*2.0f/(iSPE3-iSPE2);
		float b1=-iSPE2*k1;
		int m1=(int)(k1*fSpect+b1);

		float k2=255*2.0f/(iSPE2-iSPE3);
		float b2=-iSPE3*k2;
		int m2=(int)(k2*fSpect+b2);
		if(m1>=255)
			m1=255;
		if(m1<=0)
			m1=0;
		if(m2>=255)
			m2=255;
		if(m2<=0)
			m2=0;
		R=m1;
		G=m2;
		B=0;
	}
	else
	{
		R=(int)((780-fSpect)*255/(780-iSPE3));
		G=0;
		B=0;
	}
}

void CProcessData::ProGetTc(int interv, float *flamda, float *RelSpec, float &fx, float &fy, float &fu, float &fv, float &fRedRatio, int &iMaxslamda, float &fHaveWidth, float &fCCT, float &fRa, float *fRi, float fTox, float fToy, float fToX, float fToY, float fToZ, int iToType)
{
	//iToType
	//0:常规,1:X,Y->ct,2:x,y->ct
	float rsd[401],ou[20];
	float m_redRatio;
	int wil;
    float halfl;
	
	int i,j,yy;
	double ss,b1,b2,b3,b4,x,y,z,xs,ys,zs,w,ra,k,bb,u0,v0,m0,m1;
	double ou0,ou1,u,v,xk,yk,ly,de,ck,dk,cr,dr,cki,dki,wkstar,uk,vk,uki,vki;
	double s[75],r[15],urstar[15],vrstar[15],wrstar[15],rsd5[85];
	x=0.0; y=0.0; z=0.0;
	double Redup=0.0;
 	if(interv==5)
	{
		for(i=0;i<80+1;i++)
		  rsd5[i]=flamda[i];   //380-->780nm
		for(i=0;i<81;i+=1)
		{
			x=x+rsd5[i]*x5[i];
			y=y+rsd5[i]*y5[i];
			z=z+rsd5[i]*z5[i];
		}
		for(i=44;i<81;i++)
		{
			Redup+=rsd5[i]*y5[i];
		}
		m_redRatio=(float)(Redup/y)*100.0f;
		for(i=0;i<81;i++)
			rsd5[i]=(rsd5[i]*100.0/y);
		if(iToType==1)
		{
			x=fToX;
			y=fToY;
			z=fToZ;
		}
		x=(x*100.0/y);
		z=(z*100.0/y);
		y=100.0;

		ou0=(x/(x+y+z));
		ou1=(y/(x+y+z));
		
		if(iToType==2)
		{
			ou0=fTox;
			ou1=fToy;
		}
	}
	else
	{
		for(i=0;i<400+1;i++)
			rsd[i]=flamda[i];
		for(i=0;i<401;i++)
		{
			x=x+rsd[i]*x1[i];
			y=y+rsd[i]*y1[i];
			z=z+rsd[i]*z1[i];
		}
		for(i=220;i<401;i++)
		{
			Redup+=rsd[i]*y1[i];
		}
		m_redRatio=(float)(Redup/y)*100.0f;
		for(i=0;i<401;i++)
			rsd[i]=(float)(rsd[i]*100.0/y);
		if(iToType==1)
		{
			x=fToX;
			y=fToY;
			z=fToZ;
		}
		x=(x*100.0/y);
		z=(z*100.0/y);
		y=100.0;
		ou0=(x/(x+y+z));
		ou1=(y/(x+y+z));
		if(iToType==2)
		{
			ou0=fTox;
			ou1=fToy;
		}
		rsd5[0]=rsd[0];
		rsd5[80]=rsd[400];
		for(i=0;i<79;i++)
		{
			rsd5[i+1]=(0.2*rsd[i*5+1]+0.4*rsd[i*5+2]+0.6*rsd[i*5+3]+0.8*rsd[i*5+4]);
			rsd5[i+1]=(rsd5[i+1]+rsd[i*5+5]+0.8*rsd[i*5+6]+0.6*rsd[i*5+7]);
			rsd5[i+1]=(rsd5[i+1]+0.4*rsd[i*5+8]+0.2*rsd[i*5+9]);
		}
		y=0.0;
		for(i=0;i<81;i++)
			y=y+(rsd5[i]*y5[i]);
		for(i=0;i<81;i++)
			rsd5[i]=(rsd5[i]*100.0/y);
	}
	u=(4.0*ou0/(-2.0*ou0+12.0*ou1+3));
	v=(6.0*ou1/(-2.0*ou0+12.0*ou1+3));
	ou[16]=(float)ou0;
	ou[17]=(float)ou1;
	ou[18]=(float)u;
	ou[19]=(float)v;			//u,v
	m1=0;
	b1=(up[0]-up[1])*(up[0]-up[1])+(vp[0]-vp[1])*(vp[0]-vp[1]);
	b1=b1+(u-up[0])*(u-up[0])+(v-vp[0])*(v-vp[0]);
	b2=(u-up[1])*(u-up[1])+(v-vp[1])*(v-vp[1]);
	b3=(up[74]-up[73])*(up[74]-up[73])+(vp[74]-vp[73])*(vp[74]-vp[73]);
	b3=b3+(u-up[74])*(u-up[74])+(v-vp[74])*(v-vp[74]);
	b4=(u-up[73])*(u-up[73])+(v-vp[73])*(v-vp[73]);
	if((b1-b2)<=-0.0001)  //
	{
		m1=40; yy=0;
	}
	else
	  if((b3-b4)<=-0.0001)
      {
		m1=435; yy=74;
      }
	  else
      {
		for(i=0;i<75;i++)
		{
			x=(u-up[i])*(u-up[i])+(v-vp[i])*(v-vp[i]);
			s[i]=sqrt(x);
		}
		w=((1.05*u)+v-0.5451);
		if(fabs(w)<=0.00001)
		{
			m1=200; yy=33;
		}
        else if(w<0)
	    {
			yy=0; ss=s[0];
			for(i=0;i<33;i++)
			{
				if(fabs(s[i])<=0.00001)
				{
					m1=mired[i];
					yy=i;
					break;
				}
				else if(ss>s[i+1])
				{
					ss=s[i+1];
					yy=i+1;
				}
				else break;
			}
		}
		else
		{
			yy=34;
			ss=s[34];
			for(i=34;i<74;i++)
			{
				if(fabs(s[i])<=0.00001)
				{
					m1=mired[i];
					yy=i;
					break;
				}
				else if(ss>s[i+1])
				{
					ss=s[i+1];
					yy=i+1;
				}
				else break;
			}
		}
     }
	if(m1>=40)
    {
		m0=m1; u0=up[yy]; v0=vp[yy];
		for(i=0;i<15;i++)
		{
			urstar[i]=ustar[yy][i];
			vrstar[i]=vstar[yy][i];
			wrstar[i]=wstar[yy][i];
		}
    }
	else
    {
		if(yy==0||yy==34) j=yy+1;
		else if(yy==74||yy==33) j=yy-1;
		else j=yy;
		u0=up[j-1];v0=vp[j-1];
		b1=(u0-u)*(u0-u)+(v0-v)*(v0-v);
		u0=(u0+0.00001);
		do
		{
			k=(u0-up[j])*(u0-up[j+1])/((up[j-1]-up[j])*(up[j-1]-up[j+1]));
			bb=(u0-up[j-1])*(u0-up[j+1])/((up[j]-up[j-1])*(up[j]-up[j+1]));
			ss=(u0-up[j-1])*(u0-up[j])/((up[j+1]-up[j-1])*(up[j+1]-up[j]));
			v0=k*vp[j-1]+bb*vp[j]+ss*vp[j+1];
			b2=(u0-u)*(u0-u)+(v0-v)*(v0-v);
			if(b1>b2) b1=b2;
			else break;
			u0=(u0+0.00001);
		} while(u0<=up[j+1]);
		u0=(u0-0.00001);
		k=(u0-up[j])*(u0-up[j+1])/((up[j-1]-up[j])*(up[j-1]-up[j+1]));
		bb=(u0-up[j-1])*(u0-up[j+1])/((up[j]-up[j-1])*(up[j]-up[j+1]));
		ss=(u0-up[j-1])*(u0-up[j])/((up[j+1]-up[j-1])*(up[j+1]-up[j]));
		v0=k*vp[j-1]+bb*vp[j]+ss*vp[j+1];
		m0=k*mired[j-1]+bb*mired[j]+ss*mired[j+1];
		for(i=0;i<15;i++)
		{
			urstar[i]=k*ustar[j-1][i]+bb*ustar[j][i]+ss*ustar[j+1][i];
			vrstar[i]=k*vstar[j-1][i]+bb*vstar[j][i]+ss*vstar[j+1][i];
			wrstar[i]=k*wstar[j-1][i]+bb*wstar[j][i]+ss*wstar[j+1][i];
		}
	}
	if(m0>435)
		ou[15]=2300;
	else if(m0<40)
		ou[15]=25000;
	else
	    ou[15]=(float)(1000.0/m0*1000.0);

	if(m0>=426)
	{
		double pl[81];
		double x435,y435,z435;
		double ou0435,ou1435,u435,v435;
		double c1,c2,k;
		int tk;
		int TK,lmt;
		double Rmin=0.0,R;

		for(tk=2350;tk>=1000;tk--)
		{
			c1=(3.741844E19*9.58378/8.071367);
			c2=(1.438833E7/tk);
			for(i=0;i<81;i++)
			{
				lmt=380+i*5;
				pl[i]=(c1/pow(lmt,5)/(exp(c2/lmt)-1));
			}
			x435=0;y435=0;z435=0;
			for(i=0;i<81;i++)
			{
				x435=x435+pl[i]*x5[i];
				y435=y435+pl[i]*y5[i];
				z435=z435+pl[i]*z5[i];
			}
			x435=(x435*100.0/y435);
			z435=(z435*100.0/y435);
			y435=100.0;
			ou0435=(x435/(x435+y435+z435));
			ou1435=(y435/(x435+y435+z435));	
			u435=(4.0*ou0435/(-2.0*ou0435+12.0*ou1435+3));
			v435=(6.0*ou1435/(-2.0*ou0435+12.0*ou1435+3));

			R=(u435-u)*(u435-u)+(v435-v)*(v435-v);
			if(tk==2350) Rmin=R;
			else if(R<=Rmin) Rmin=R;
			else if(R>Rmin) break;
		}

		TK=tk+1;
		ou[15]=(float)TK;
		c1=(3.741844E19*9.58378/8.071367);
		c2=(1.438833E7/TK);
		for(i=0;i<81;i++)
		{
			lmt=380+i*5;
			pl[i]=(c1/pow(lmt,5)/(exp(c2/lmt)-1));
		}
		x435=0;y435=0;z435=0;
		for(i=0;i<81;i++)
		{
			x435=x435+pl[i]*x5[i];
			y435=y435+pl[i]*y5[i];
			z435=z435+pl[i]*z5[i];
		}
		k=100/y435;
		x435=(x435*100.0/y435);
		z435=(z435*100.0/y435);
		y435=100.0;
		ou0=(x435/(x435+y435+z435));
		ou1=(y435/(x435+y435+z435));	
		u0=u435=(4.0*ou0435/(-2.0*ou0435+12.0*ou1435+3));
		v0=v435=(6.0*ou1435/(-2.0*ou0435+12.0*ou1435+3));
		for(j=0;j<15;j++)
		{
			xs=0.0; ys=0.0; zs=0.0;
			for(i=0;i<81;i++) 
			{
				xs=xs+pl[i]*s15[i][j]*x5[i];
				ys=ys+pl[i]*s15[i][j]*y5[i];
				zs=zs+pl[i]*s15[i][j]*z5[i];
			}
			xk=xs/(xs+ys+zs);
			yk=ys/(xs+ys+zs);
			ys=k*ys;
			ly=((log(ys))/3);
			wrstar[j]=(25*(exp(ly))-17.0);
			uk=(4*xk/(-2.0*xk+12*yk+3));
			vk=(6*yk/(-2.0*xk+12*yk+3));
			urstar[j]=13*wrstar[j]*(uk-u435);
			vrstar[j]=13*wrstar[j]*(vk-v435);
		}
	}


 ck=(4-u-10*v)/v;
 dk=((1.708*v+0.404-1.481*u)/v);
 cr=(4-u0-10*v0)/v0;
 dr=((1.708*v0+0.404-1.481*u0)/v0);
 for(j=0;j<15;j++)
  {
   xs=0.0; ys=0.0; zs=0.0;
   for(i=0;i<81;i++)
    {
     xs=xs+rsd5[i]*s15[i][j]*x5[i];
     ys=ys+rsd5[i]*s15[i][j]*y5[i];
     zs=zs+rsd5[i]*s15[i][j]*z5[i];
    }
   xk=xs/(xs+ys+zs);
   yk=ys/(xs+ys+zs);
   ly=((log(ys))/3);
   wkstar=(25*(exp(ly))-17.0);
   uk=(4*xk/(-2.0*xk+12*yk+3));
   vk=(6*yk/(-2.0*xk+12*yk+3));
   cki=((4-uk-10*vk)/vk);
   dki=((1.708*vk+0.404-1.481*uk)/vk);
   uki=((10.872+0.404*cr*cki/ck-4*dr*dki/dk)/(16.518+1.481*cr*cki/ck-dr*dki/dk));
   vki=(5.520/(16.518+1.481*cr*cki/ck-dr*dki/dk));
   de=((urstar[j]-13*wkstar*(uki-u0))*(urstar[j]-13*wkstar*(uki-u0)));
   de=de+((vrstar[j]-13*wkstar*(vki-v0))*(vrstar[j]-13*wkstar*(vki-v0)));
   de=de+((wrstar[j]-wkstar)*(wrstar[j]-wkstar));
   r[j]=(100.0-4.6*sqrt(de));
  }
 ra=(r[0]+r[1]+r[2]+r[3]+r[4]+r[5]+r[6]+r[7])/8;
 ou[0]=(float)ra;
 if(ou[0]<-999.0) ou[0]=-999.0;
 for(i=0;i<14;i++)
   if(r[i]<-999.0) ou[i+1]=-999.0;
   else ou[i+1]=(float)r[i];

	if(interv==5)
	{
		for(i=0;i<81;i++)
			rsd5[i]=flamda[i];
		for(i=0;i<(81)/2;i++)
		{
			for(j=0;j<10;j++)
			{
				rsd[i*10+j]=(float)((j-5)*(j-10)*rsd5[2*i]/50-j*(j-10)*rsd5[2*i+1]/25+j*(j-5)*rsd5[2*i+2]/50);
				if(rsd[i*10+j]<=0.0) rsd[i*10+j]=0.0;
			}
		}
		rsd[400]=(float)rsd5[80];
	}
	else
	{
		for(i=0;i<401;i++)
			rsd[i]=flamda[i];
	}
	float max; 
	maximums(rsd,&max,&wil,401);

	for(i=0;i<401;i++) {rsd[i]/=max;}

	int tempyy=0,tempj=0;
	for(i=wil;i>=0;i--)
	{
		if(rsd[i]<0.5f)
		{
			tempyy=i;
			break;
		}
	}
	if(tempyy==0)
		yy=i+1;
	else yy=tempyy;
	for(i=wil;i<401;i++)
	{
		if(rsd[i]<0.5f)
		{
			tempj=i;
			break;
		}	
	}
	if(tempj==0)
		j=i-1;
	else 
		j=tempj;
	m0=0;
	m1=0;
	if(rsd[yy]<0.5) 
		m0=((0.5-rsd[yy])/(rsd[yy+1]-rsd[yy]));
	if(rsd[j]<0.5)
		m1=((0.5-rsd[j])/(rsd[j-1]-rsd[j]));
	halfl=(float)(j-yy-m0-m1);

	for(i=0;i<401;i++)
		RelSpec[i]=rsd[i];
	fx=ou[16];
	fy=ou[17];
	fu=ou[18];
	fv=ou[19];
	fCCT=ou[15];
	fRedRatio=m_redRatio;
	if(fRedRatio>=100)
		fRedRatio=100;
	if(fRedRatio<=0)
		fRedRatio=0;
	fRa=ou[0];
	for(i=0;i<15;i++)
		fRi[i]=ou[i+1];
	iMaxslamda=380+wil;
	fHaveWidth=halfl;
}

float CProcessData::g_fMax(float f[], int iN, int &iMax)
{
	float fMax=f[0];
	iMax=0;
	for(int i=1;i<iN;i++)
		if(f[i]>fMax)
		{
			fMax=f[i];
			iMax=i;
		}
	return fMax;
}

double xa[360*100+1];
double CProcessData::Lagrange(double x0, double h, int n, double y[], double t)
{
	//Lagrange等距插值：
	//                  X0：      等距结点中第一个结点值
	//                  H：       步长值
	//                  N：       个数
	//                  Y[N]：    N个结点上的值
	//                  T：       指定插值的点
	//                  return：  T处的值                
	for(int mm=0;mm<n;mm++)
		xa[mm]=x0+h*mm;

	return NewInt_double(xa,y,n,t);
  
	int i,j,k,m;
	double z,s,xi,xj;
	double p,q;
	z=0.0;
	if(n<1)
	{
		return(z);
	}
	
	if(n==1)
	{
		z=y[0];
		return(z);
	}
	if(n==2)
	{
		z=(y[1]*(t-x0)-y[0]*(t-x0-h))/h;
		return(z);
	}
	if(t>x0)
	{
		p=(t-x0)/h;
		i=(int)p;
		q=(float)i;
		if(p>q)
		{i++;}
	}
	else 
		i=0;
	k=(i-4)<0?0:i-4;
	m=(i+3)>n-1?n-1:i+3;
	for(i=k;i<=m;i++)
	{
		s=1.0;
		xi=x0+i*h;
		for(j=k;j<=m;j++)
		{
			if(j!=i)
			{
				xj=x0+j*h;
				s*=(t-xj)/(xi-xj);
			} 
			 
		}
		z+=s*y[i];
	}
	
	return(z);
}

double CProcessData::NewInt_double(double *xa, double *ya, int n, double x)
{
	int i, k;
	double u;

	//注意：新增加的 因为KJ380波长范围不到800nm 处理波形插值问题
	if(x>xa[n-1]&&n==2048)
	{
		double fTemp=1.0;
		int i;
		double aa[200];
		double bb[200];
		double fMax = ya[n-1];
		int iMax = 0;
		for(i=0;i<200;i++)
		{
			if(fMax < ya[n-1-200+i])
			{
				fMax = ya[n-1-200+i];
				iMax = i;
			}
		}

		for(i = iMax; i < 200; i++)
		{
			aa[i-iMax]=xa[n-1-(200)+i];
			bb[i-iMax]=ya[n-1-(200)+i];
		}

		if((200 - iMax) < 10)
		{
			k=n-1;
			if(xa[0]>xa[1]) //数组从大到小
			{
				for(i=1; i<=n-2; i++)
				{
					if( x >= xa[i] )
					{
						k=i;
						break;
					}
					else
						k=n-1;
				}
			}
			else  //从小到大
			{
				for(i=1; i<=n-2; i++)
				{
					if( x <= xa[i] )
					{
						k=i;
						break;
					}
					else
						k=n-1;
				}
			}
			u=(x-xa[k-1])/(xa[k]-xa[k-1]);
			return ya[k-1]+u*(ya[k]-ya[k-1]);
		}
		else
		{
			fTemp = (double)(g_SPEC.Lagrange_New(aa,bb,200-iMax,(float)x));
//			double d[10];
//			g_SPEC.Gauss2XF_Calc(aa,bb,200-iMax,3,d);

//			fTemp=(float)(d[0]+d[1]*pow(x,1)+d[2]*pow(x,2)+d[3]*pow(x,3));
		}
		
		return fTemp;
	}
	else
	{
		k=n-1;
		if(xa[0]>xa[1]) //数组从大到小
		{
			for(i=1; i<=n-2; i++)
			{
				if( x >= xa[i] )
				{
					k=i;
					break;
				}
				else
					k=n-1;
			}
		}
		else  //从小到大
		{
			for(i=1; i<=n-2; i++)
			{
				if( x <= xa[i] )
				{
					k=i;
					break;
				}
				else
					k=n-1;
			}
		}
		u=(x-xa[k-1])/(xa[k]-xa[k-1]);
		return ya[k-1]+u*(ya[k]-ya[k-1]);
	}
}

BOOL CProcessData::ReadSdcmData(CString strPath)
{
	//读取色容差标准信息文件
	m_sdcm.RemoveAll();

	FILE *fp;
	CString sTitle;
    sTitle="sdcm.dat";
    if((fp=fopen(strPath+sTitle,"rt"))==0)
	{
		AfxMessageBox("Can not file sdcm.dat",NULL,MB_ICONSTOP);
		exit(0);
		return FALSE;
	}
    else
	{
		char a[256];
		int iN=0;
		fscanf(fp,"SDCM:%d\n",&iN);
		for(int i=0;i<iN;i++)
		{
			SDCM* te=new SDCM();  //我们一定得用new
			fscanf(fp,"\n");
			fscanf(fp,"%s\n",a);
			te->m_strName=a;
			fscanf(fp,"x=%f y=%f\n",&te->m_fx,&te->m_fy);
			fscanf(fp,"g11=%f g12=%f g22=%f\n",&te->m_fg11,&te->m_fg12,&te->m_fg22);
			fscanf(fp,"xs=%f ys=%f\n",&te->m_fxs,&te->m_fys);
			m_sdcm.Add(te);
		}
		fclose(fp);
	}
	return TRUE;
}

float CProcessData::fMax(CArray<float,float> &f, int &iMax,BOOL bForNew)
{
	int iN=f.GetSize();
	if(iN<=0)
		return 0;
	float fMax=f[0];
	float fMin=fMax;
	iMax=0;
	for(int i=1;i<iN;i++)
	{
		if(f[i]>fMax)
		{
			fMax=f[i];
			iMax=i;
		}
		if(f[i]<fMin)
			fMin=f[i];
	}

	if(bForNew&&fMax>0&&fMin<0.1f*fMax)
	{
		float fL=f[0]/fMax;
		float fR=f[iN-1]/fMax;

		float fKP=(float)max(max(fL,fR),0.8);

		int iL=0;
		int iR=iN-1;
		//
		for(i=0;i<iN;i++)
		{
			if(f[i]>fMax*fKP)
			{
				iL=i;
				break;
			}
		}
		for(i=0;i<iN;i++)
		{
			if(f[iN-1-i]>fMax*fKP)
			{
				iR=iN-1-i;
				break;
			}
		}

		iMax=iL+(iR-iL)/2;

		float All=0;
		for(i=iL;i<=iR;i++)
			All=All+f[i];
		float L=0;
		for(i=iL;i<=iR;i++)
		{
			L=L+f[i];
			if(L>=0.5f*All)
			{
				iMax=i;
				break;
			}
		}
	}
	return fMax;
}

float CProcessData::fHalfWave(CArray<float,float> &f)
{
	int i;
	int iMax;
	float Max;
	int iN=f.GetSize();
	Max=fMax(f,iMax);
	float fL,fR;
	fL=0.0f;
	fR=iN-1.0f;
	for(i=iMax;i>=0;i--)
	{
		if(f[i]<=0.5*Max)
		{
			fL=i+(0.5f*Max-f[i])*1.0f/(f[i+1]-f[i]);
			break;
		}
	}
	for(i=iMax;i<iN;i++)
	{
		if(f[i]<=0.5*Max)
		{
			fR=i-(0.5f*Max-f[i])*1.0f/(f[i-1]-f[i]);
			break;
		}
	}
	return fR-fL;
}

float CProcessData::CIE_DEuv(float x1, float y1, float x2, float y2, float x0, float y0)
{
	//计算色差 L*,u*,v* 色空间
	float xL1,xu1,xv1;
	float xL2,xu2,xv2;
	float xSuv,xCuv,xHuv;

	CIE_xLuv(x1,y1,x0,y0,xL1,xu1,xv1,xSuv,xCuv,xHuv);
	CIE_xLuv(x2,y2,x0,y0,xL2,xu2,xv2,xSuv,xCuv,xHuv);

	double dE;
	dE=pow(xL1-xL2,2)+pow(xu1-xu2,2)+pow(xv1-xv2,2);
	dE=pow(dE,0.5);
	return (float)dE;
}

void CProcessData::CIE_xLuv(float x, float y, float x0, float y0, float &xL, float &xu, float &xv, float &xSuv, float &xCuv, float &xHuv)
{
	//计算L*,u*,v* (为计算色差)
	//xLuv  明度
	//xSuv  饱和度
	//xCuv  彩度
	//xHuv  色调

	float z,z0;
	z  = 1 - x - y;
	z0 = 1 -x0 - y0;

	float u_,v_;
	float u0_,v0_;

	u_  = 4*x/(x+15*y+3*z);
	v_  = 9*y/(x+15*y+3*z);

	u0_ = 4*x0/(x0+15*y0+3*z0);
	v0_ = 9*y0/(x0+15*y0+3*z0);

	xL	= (float)(116*(pow((y/y0),1/3.0f))-16);
	xu	= 13*xL*(u_-u0_);
	xv	= 13*xL*(v_-v0_);

	double d;
	d	= pow((u_-u0_),2)+pow((v_-v0_),2);
	d	= pow(d,0.5);
	
	xSuv= (float)(13*d);

	d	= pow(xu,2)+pow(xv,2);
	d	= pow(d,0.5);
	xCuv= (float)(d);

	d	= atan2(v_-v0_,u_-u0_);
	xHuv= (float)(d*180/3.1415926535);
	if(xHuv < 0)
	{
		xHuv=360 + xHuv;
	}

	return;
}

float CProcessData::Fun(float fC[], float fD1, float fD2, float fD3)
{
	return fC[0]*fD1+fC[1]*fD2+fC[2]*fD3;
}

float CProcessData::NewInt_float(float *xa, float *ya, int n, float x)
{
	//牛顿插值

	int i, k;
	float u;
	k=1;
	for(i=1; i<=n-2; i++)
	{
		if( x <= xa[i] )
		{
			k=i;
			break;
		}
		else
			k=n-1;
	}
	u=(x-xa[k-1])/(xa[k]-xa[k-1]);
	return ya[k-1]+u*(ya[k]-ya[k-1]);
}
