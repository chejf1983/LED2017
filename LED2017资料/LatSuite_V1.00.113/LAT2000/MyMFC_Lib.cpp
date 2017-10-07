// MyMFC_Lib.cpp
#include "stdafx.h"
#include "MyMFC_Lib.h"
#include "math.h"

namespace MyMFC_Lib
{
	// ��������ʽ��Gauss��С���˷�,�������
	//  IN:  fx[],fy[] ������� iN����
	//      iMN  ��϶���ʽ�Ĵ���
	//  OUT: a[]  ����ʽ����ϵ��  a0 a1 a2 ...�� (iMN+1)��
	BOOL Gauss2XF_Calc(float fx[], float fy[], int iN, int iMN, float a[])
	{
		if(iN < iMN)
			return FALSE;

		if(iMN < 1)
			return FALSE;

		int NN = iMN + 1;
		int i,j,t;
		float *K = new float[NN*NN];    //ϵ��     ==
		float *z = new float[NN];
		//1.��������̵�ϵ��
		for(i = 0; i < NN; i++)          //��
		{
			//K
			for(j = i; j < NN; j++)      //��
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

		//2.�����Է�����  ��˹��Ԫ()��
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

	// ��˹��ȥ�������Է�����
	// IN:  fK[] iN*iN ����-��
	//       fz   iN��
	// OUT: a[]  iN����
	BOOL Gauss_EQU(float fk[], float fz[], int iN,float a[])
	{		
		int i,j,t;
		float fTemp1,fTemp2,fTemp;
		float K;
		//1.��Ԫ
		for(i=0;i<iN-1;i++)              //��
		{
			fTemp1=fk[i*iN+i];           //i��i��
			
			//�����0�ҳ�����0�Ļ���
			if(fTemp1==0.0)
			{
				//�ҳ�����0��i�е�ĳһ��iSele
				int iSele=-1;
				for(j=i+1;j<iN;j++)
				{
					if(fk[j*iN+i]!=0.0)
					{
						iSele=j;
						break;
					}
				}
				if(iSele==-1)        //�Ҳ���
					return FALSE;
				
				//����
				for(j=0;j<iN;j++)
				{
					fTemp=fk[i*iN+j];
					fk[i*iN+j]=fk[iSele*iN+j];
					fk[iSele*iN+j]=fTemp;
				}
				fTemp=fz[i];
				fz[i]=fz[iSele];
				fz[iSele]=fTemp;
				
				fTemp1=fk[i*iN+i];           //i��i��
			}
			
			//�������Ǿ��Σ���Z
			for(j=i+1;j<iN;j++)          //��
			{
				fTemp2=fk[j*iN+i];       //j��i��
				K=-fTemp2/fTemp1;
				for(t=i;t<iN;t++)        //�б仯
					fk[j*iN+t]=fk[j*iN+t]+fk[i*iN+t]*K;
				fz[j]=fz[j]+fz[i]*K;
			}
		}
		//2.�ش�
		for(i=iN-1;i>=0;i--)     //��
		{
			a[i]=fz[i];
			for(j=i+1;j<iN;j++)    //��
				a[i]=a[i]-fk[i*iN+j]*a[j];
			a[i]=a[i]/fk[i*iN+i];
		}
		return TRUE;
	}

	/*
	 * ���� CSV��ʽ���ݸ���CListCtrl
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
	 *  �ַ������ո�
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
