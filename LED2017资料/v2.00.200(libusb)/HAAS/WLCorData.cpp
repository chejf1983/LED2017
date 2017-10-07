// WLCorData.cpp: implementation of the CWLCorData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MySpec.h"
#include "WLCorData.h"
#include "math.h"
#include "Global_MySpec.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWLCorData::CWLCorData()
{
	m_iPixN=2048;
}

CWLCorData::~CWLCorData()
{

}

int CWLCorData::Delete(int iSele)
{
	int iN=m_arra_fStaWL.GetSize();
	if(iSele>=0&&iSele<iN)
	{
		m_arra_fStaWL.RemoveAt(iSele);
		m_arra_fPix.RemoveAt(iSele);
		return iSele;
	}
	else
		return -1;
}

void CWLCorData::Add(float fStaWL, float fPix)
{
	int iN=m_arra_fStaWL.GetSize();
	for(int i=0;i<iN;i++)
	{
		if(m_arra_fStaWL[i]==fStaWL)
		{
			m_arra_fStaWL.RemoveAt(i);
			m_arra_fPix.RemoveAt(i);
			break;
		}
	}
	for(i=0;i<m_arra_fStaWL.GetSize();i++)
	{
		if(m_arra_fPix[i]==fPix)
		{
			m_arra_fStaWL.RemoveAt(i);
			m_arra_fPix.RemoveAt(i);
			break;
		}
	}

	m_arra_fStaWL.Add(fStaWL);
	m_arra_fPix.Add(fPix);

	Sort();
}

BOOL CWLCorData::Load(CString strPathName)
{
	//光谱定标数据
	FILE *fp;
	if((fp=fopen(strPathName,"rt"))==NULL)
		return FALSE;
	else
	{
		char a[256];
		fscanf(fp,"%s\n",a);
		CString strTemp=a;
		if(strTemp!="WLCOR")
		{
			fclose(fp);	
			return FALSE;
		}

		fscanf(fp,"PixN=%d\n",&m_iPixN);

		m_arra_fStaWL.RemoveAll();
		m_arra_fPix.RemoveAll();
		while(1)
		{
			float fWL;
			float fPix;
			fscanf(fp,"%f %f\n",&fWL,&fPix);
			if(fWL>0&&fPix>0)
			{
				m_arra_fStaWL.Add(fWL);
				m_arra_fPix.Add(fPix);
			}
			else
				break;
		}
	}
    fclose(fp);	
	return TRUE;
}

BOOL CWLCorData::Save(CString strPathName,BOOL bShowErr)
{
	FILE *fp;
	if((fp=fopen(strPathName,"wt"))==NULL)
		return FALSE;
	else
	{
		int i,j;
		m_iPixN = 2048;
		fprintf(fp,"WLCOR\n");
		fprintf(fp,"PixN=%d\n",m_iPixN);
		int iN=m_arra_fStaWL.GetSize();
		for(i=0;i<iN;i++)
			fprintf(fp,"%10.3f   %.1f\n",m_arra_fStaWL[i],m_arra_fPix[i]);
		fprintf(fp,"-1 -1\n");

		//附加校正系数
		fprintf(fp,"\n");
		double fC[10];
		CalcCor(fC,iN,bShowErr);
		fprintf(fp,"\n-------------------------------------------------------------\n");
		for(i=0;i<iN;i++)
			fprintf(fp,"%e ",fC[i]);
		fprintf(fp,"\n-------------------------------------------------------------\n");
		fprintf(fp,"\n");
		if(iN>0)
		{
			double fWL1=0;
			for(j=0;j<iN;j++)
				fWL1=fWL1+fC[j]*pow(0,j);
			double fWL2=0;
			for(j=0;j<iN;j++)
				fWL2=fWL2+fC[j]*pow(m_iPixN-1,j);

			fprintf(fp,"WL: %.2fnm-%.2fnm\n\n",fWL1,fWL2);

			double fPreWL=0;
			BOOL bError=FALSE;
			for(i=0;i<m_iPixN;i++)
			{
				double fWL=0;
				for(j=0;j<iN;j++)
					fWL=fWL+fC[j]*pow(i,j);
				if(i==0)
					fPreWL=fWL;
				if(fPreWL>fWL)
					bError=TRUE;
				if(fPreWL>fWL)
					fprintf(fp,"%5d  %7.2f %7.2f Error\n",i,fWL,fWL-fPreWL);
				else
					fprintf(fp,"%5d  %7.2f %7.2f\n",i,fWL,fWL-fPreWL);
				fPreWL=fWL;
			}
			if(bError)
			{
				if(bShowErr)
				{
					if(g_bEnglish)
						AfxMessageBox("Fail!");
					else
						AfxMessageBox("校正有问题,校正出来的波长不是从小到大!");
				}
			}
		}

		fprintf(fp,g_SPEC.m_strSN);
	}
    fclose(fp);	
	return TRUE;
}

void CWLCorData::Sort()
{
	int iN=m_arra_fStaWL.GetSize();
	float fTemp;
	for(int i=0;i<iN;i++)
	{
		for(int j=i;j<iN;j++)
		{
			if(m_arra_fStaWL[i]>m_arra_fStaWL[j])
			{
				fTemp=m_arra_fStaWL[i];
				m_arra_fStaWL[i]=m_arra_fStaWL[j];
				m_arra_fStaWL[j]=fTemp;

				fTemp=m_arra_fPix[i];
				m_arra_fPix[i]=m_arra_fPix[j];
				m_arra_fPix[j]=fTemp;
			}
		}
	}

}

void CWLCorData::CalcCor(double fC[], int &iN,BOOL bShowErr)
{
	//计算校正系数
	int NN=m_arra_fStaWL.GetSize();
	if(NN<3)
	{
		iN=0;
		return;
	}
	if(NN==3&&g_SPEC.T_SPECT2==400.0f)
	{
		int i;
		double fx[100];
		double fy[100];
		for(i=0;i<NN;i++)
		{
			fx[i]=m_arra_fPix[i]*1.0;
			fy[i]=m_arra_fStaWL[i]*1.0;
			if(i>=1)
			{
				if(fx[i]<fx[i-1])
				{
					if(bShowErr)
					{
						if(g_bEnglish)
							AfxMessageBox("Correct fail!");
						else
							AfxMessageBox("数据有误,像素点应该从小到大!");
					}
					iN=0;
					return;
				}
			}
		}
		BOOL bR;
		bR=g_SPEC.Gauss2XF_Calc(fx,fy,NN,2,fC);
		if(!bR)
		{
			iN=0;
			return;
		}
		fC[3]=0;
		iN=3+1;
		return;
	}
	int i;
	double fx[100];
	double fy[100];
	for(i=0;i<NN;i++)
	{
		fx[i]=m_arra_fPix[i]*1.0;
		fy[i]=m_arra_fStaWL[i]*1.0;
		if(i>=1)
		{
			if(fx[i]<fx[i-1])
			{
				if(bShowErr)
				{
					if(g_bEnglish)
						AfxMessageBox("Correct fail!");
					else
						AfxMessageBox("数据有误,像素点应该从小到大!");
				}
				iN=0;
				return;
			}
		}
	}
	BOOL bR;
	bR=g_SPEC.Gauss2XF_Calc(fx,fy,NN,3,fC);
	if(!bR)
	{
		iN=0;
		return;
	}
	iN=3+1;
	return;
}
