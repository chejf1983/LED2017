// MyMFC_Lib.cpp
#include "stdafx.h"
#include "MyMFC_Lib.h"
#include "math.h"

namespace MyMFC_Lib
{
	// 代数多项式的Gauss最小二乘法,曲线拟合
	//  IN:  fx[],fy[] 拟合数据 iN个数
	//      iMN  拟合多项式的次数
	//  OUT: a[]  多项式各次系数  a0 a1 a2 ...共 (iMN+1)个
	BOOL Gauss2XF_Calc(float fx[], float fy[], int iN, int iMN, float a[])
	{
		if(iN < iMN)
			return FALSE;

		if(iMN < 1)
			return FALSE;

		int NN = iMN + 1;
		int i,j,t;
		float *K = new float[NN*NN];    //系数     ==
		float *z = new float[NN];
		//1.求出法方程的系数
		for(i = 0; i < NN; i++)          //行
		{
			//K
			for(j = i; j < NN; j++)      //列
			{
				K[i*NN+j]=0;
				for(t=0;t<iN;t++)
					K[i*NN+j]=K[i*NN+j]+powf(fx[t],i+j*1.0f);

				if(i!=j)
					K[j*NN+i]=K[i*NN+j];    
			}
			//z
			z[i]=0;
			for(t=0;t<iN;t++)
				z[i]=z[i]+powf(fx[t],i*1.0f)*fy[t];
		}

		//2.解线性方程组  高斯消元()法
		if(Gauss_EQU(K,z,NN,a)==FALSE)
		{
			delete K;
			delete z;
			return FALSE;
		}

		delete K;
		delete z;

		return TRUE;
	}

	// 高斯消去法解线性方程组
	// IN:  fK[] iN*iN 个行-列
	//       fz   iN行
	// OUT: a[]  iN个解
	BOOL Gauss_EQU(float fk[], float fz[], int iN,float a[])
	{		
		int i,j,t;
		float fTemp1,fTemp2,fTemp;
		float K;
		//1.消元
		for(i=0;i<iN-1;i++)              //行
		{
			fTemp1=fk[i*iN+i];           //i行i列
			
			//如果是0找出不是0的换行
			if(fTemp1==0.0)
			{
				//找出不是0的i列的某一行iSele
				int iSele=-1;
				for(j=i+1;j<iN;j++)
				{
					if(fk[j*iN+i]!=0.0)
					{
						iSele=j;
						break;
					}
				}
				if(iSele==-1)        //找不到
					return FALSE;
				
				//交换
				for(j=0;j<iN;j++)
				{
					fTemp=fk[i*iN+j];
					fk[i*iN+j]=fk[iSele*iN+j];
					fk[iSele*iN+j]=fTemp;
				}
				fTemp=fz[i];
				fz[i]=fz[iSele];
				fz[iSele]=fTemp;
				
				fTemp1=fk[i*iN+i];           //i行i列
			}
			
			//计算三角矩形，及Z
			for(j=i+1;j<iN;j++)          //行
			{
				fTemp2=fk[j*iN+i];       //j行i列
				K=-fTemp2/fTemp1;
				for(t=i;t<iN;t++)        //列变化
					fk[j*iN+t]=fk[j*iN+t]+fk[i*iN+t]*K;
				fz[j]=fz[j]+fz[i]*K;
			}
		}
		//2.回代
		for(i=iN-1;i>=0;i--)     //行
		{
			a[i]=fz[i];
			for(j=i+1;j<iN;j++)    //列
				a[i]=a[i]-fk[i*iN+j]*a[j];
			a[i]=a[i]/fk[i*iN+i];
		}
		return TRUE;
	}

	/*
	 * 导出 CSV格式数据根据CListCtrl
	 */
	BOOL Export_List(CListCtrl &list, CString strPathName)
	{
		FILE *fp;
		if(fopen_s(&fp, strPathName, "wt") != 0)
		{
			return FALSE;
		}
		else
		{
			int i;
			
			CString strTemp;
			
			int iN;
			
			iN = list.GetHeaderCtrl()->GetItemCount();
			for(i = 0; i < iN ; i++)
			{
				HDITEM  aStHDI;
				TCHAR   aSzBuf[255];
				
				aStHDI.mask       = HDI_TEXT;
				aStHDI.pszText    = aSzBuf;
				aStHDI.cchTextMax = sizeof(aSzBuf);
				
				list.GetHeaderCtrl()->GetItem(i,&aStHDI);
				
				strTemp = aStHDI.pszText;	
				fprintf(fp,"\"%s\",",strTemp);
			}
			fprintf(fp,"\n");
			
			for(int aRow = 0; aRow < list.GetItemCount(); aRow++)
			{			
				for(int aColumn = 0; aColumn < list.GetHeaderCtrl()->GetItemCount(); aColumn++)
				{
					strTemp = list.GetItemText(aRow,aColumn);
					fprintf(fp,"\"%s\",",strTemp);
				}
				fprintf(fp,"\n");
			}
			
			fclose(fp);
		}
		return TRUE;
	}

	/*
	 *  字符串补空格
	 */
	CString StrAddSpace(CString strTemp, int iMaxN, BOOL bAddLast)
	{
		int iAddN = iMaxN - strTemp.GetLength();
		for(int i = 0; i < iAddN; i++)
		{
			if(bAddLast)
				strTemp += " ";
			else
				strTemp = " " + strTemp;
		}
		return strTemp;
	}
}
