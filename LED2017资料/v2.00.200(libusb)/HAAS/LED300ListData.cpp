// LED300ListData.cpp: implementation of the CLED300ListData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MySpec.h"
#include "LED300ListData.h"
#include "math.h"
#include "Global_MySpec.h"

#include "SortListCtrl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
BOOL		g_bInsert;
extern BOOL g_bAllSele;
extern BOOL g_bCurErr;
extern int	g_iLEDClass_Type;
extern BOOL	g_bHaveCRI;

extern BOOL  g_bPhoEffSetAuto;
extern float g_fSpectB1,g_fSpectB2,g_fSpectY1,g_fSpectY2;

BOOL g_bHavePhoEff;

extern CArray<BOOL,BOOL> g_bError;  //合格与否的标志

CFailFlagData CLED300ListData::m_failFlagData;



CLED300ListData::CLED300ListData()
{
	m_iPhType = PH_F;
}

CLED300ListData::~CLED300ListData()
{

}

void CLED300ListData::New()
{
	m_iPerCur = -1;
	m_listData.RemoveAll();
}

BOOL CLED300ListData::Export_CSV(CString strPathName)
{
	FILE *fp;
	if((fp = fopen(strPathName,"wt"))==0)
		return FALSE;
	else
	{
		CString strTemp;
		if(g_bEnglish)
			strTemp = "SN.";
		else
			strTemp = "序号";
		fprintf(fp, strTemp);

		if(m_opData.m_bNote)
		{
			if(g_bEnglish)
				strTemp="Number";
			else
				strTemp="编号";
			fprintf(fp,"	");
			fprintf(fp,strTemp);
		}
		if(1)
		{
			if(g_bEnglish)
				strTemp = "Time";
			else
				strTemp = "测试时间";
			fprintf(fp,"	");
			fprintf(fp,strTemp);
		}

		if(1)
		{
			if(g_bEnglish)
				strTemp = "inttime";
			else
				strTemp = "积分时间";
			fprintf(fp,"	");
			fprintf(fp,strTemp);
		}

		if(m_opData.m_bLevel)
		{
			if(g_bEnglish)
				strTemp="LEVEL";
			else
				strTemp="分级(LEVEL)";
			fprintf(fp,"	");
			fprintf(fp,strTemp);
		}
		if(m_opData.m_bWhite)
		{
			if(g_bEnglish)
				strTemp="WHITE";
			else
				strTemp="白光分类(WHITE)";
			fprintf(fp,"	");
			fprintf(fp,strTemp);
		}
		if(m_opData.m_bIF)
		{
			strTemp="I(A)";
			fprintf(fp,"	");
			fprintf(fp,strTemp);
		}
		if(m_opData.m_bVF)
		{
			strTemp="U(V)";
			fprintf(fp,"	");
			fprintf(fp,strTemp);
		}
		if(m_opData.m_bP)
		{
			strTemp="P(W)";
			fprintf(fp,"	");
			fprintf(fp,strTemp);
			strTemp="PF";
			fprintf(fp,"	");
			fprintf(fp,strTemp);
		}
		int iLamp=0;
		if(m_opData.m_bPH)
		{
			if(m_listData.GetSize()>0)
				iLamp=m_listData.GetAt(0)->m_spData.m_iLamp;

			strTemp=CSpectData::PH_Name(iLamp,m_iPhType);
			fprintf(fp,"	");
			fprintf(fp,strTemp);
		}

		if(m_opData.m_bPhSP)
		{
			if(g_bEnglish)
				strTemp = "Scotopic";
			else
				strTemp = "暗视觉光度";
			fprintf(fp,"	");
			fprintf(fp,strTemp);
			
			if(g_bEnglish)
				strTemp = "S/P";
			else
				strTemp = "S/P";
			fprintf(fp,"	");
			fprintf(fp,strTemp);
		}

		if(iLamp==0)
		{
			if(m_iPhType==PH_F)
			{
				strTemp=CSpectData::PH_Name(iLamp,PH_Fe);
				fprintf(fp,"	");
				fprintf(fp,strTemp);
			}
			if(m_iPhType==PH_E)
			{
				strTemp=CSpectData::PH_Name(iLamp,PH_Ee);
				fprintf(fp,"	");
				fprintf(fp,strTemp);
			}
			if(m_opData.m_bPH&&(m_iPhType==PH_I||m_iPhType==PH_Ie))
			{
				CString sStr;
				if(g_bEnglish)
					sStr="(CIE A/B)";
				else
					sStr="(条件)";

				strTemp=CSpectData::PH_Name(iLamp,PH_Ie)+sStr;

				fprintf(fp,"	");
				fprintf(fp,strTemp);
			}
			if(m_iPhType==PH_F)   //不一样的地方
			{
				if(g_bEnglish)
					strTemp="Eff.(lm/W)";
				else
					strTemp="光效(lm/W)";
				fprintf(fp,"	");
				fprintf(fp,strTemp);
			}
		}
		if(m_opData.m_bIp)
		{
			strTemp="Ip";
			fprintf(fp,"	");
			fprintf(fp,strTemp);
		}
		if(m_opData.m_bXY)
		{
			strTemp="x";
			fprintf(fp,"	");
			fprintf(fp,strTemp);
		}
		if(m_opData.m_bXY)
		{
			strTemp="y";
			fprintf(fp,"	");
			fprintf(fp,strTemp);
		}
		if(m_opData.m_bUV)
		{
			strTemp="u'";
			fprintf(fp,"	");
			fprintf(fp,strTemp);
		}
		if(m_opData.m_bUV)
		{
			strTemp="v'";
			fprintf(fp,"	");
			fprintf(fp,strTemp);
		}
		if(m_opData.m_bTc)
		{
			strTemp="CCT(K)";
			fprintf(fp,"	");
			fprintf(fp,strTemp);
		}
		if(m_opData.m_bdC)
		{
			strTemp="dC";
			fprintf(fp,"	");
			fprintf(fp,strTemp);
		}
		if(m_opData.m_bLd)
		{
			if(g_bEnglish)
				strTemp="Ld(nm)";
			else
				strTemp="主波长(nm)";
			fprintf(fp,"	");
			fprintf(fp,strTemp);
		}
		if(m_opData.m_bPur)
		{
			if(g_bEnglish)
				strTemp="Pur(%)";
			else
				strTemp="色纯度(%)";
			fprintf(fp,"	");
			fprintf(fp,strTemp);
		}
		if(m_opData.m_bLp)
		{
			if(g_bEnglish)
				strTemp="Lp(nm)";
			else
				strTemp="峰值波长(nm)";
			fprintf(fp,"	");
			fprintf(fp,strTemp);
		}
		if(m_opData.m_bHW)
		{
			if(g_bEnglish)
				strTemp="FWHM(nm)";
			else
				strTemp="半波宽(nm)";
			fprintf(fp,"	");
			fprintf(fp,strTemp);
		}
		if(m_opData.m_bRR)
		{
			if(g_bEnglish)
				strTemp="Red Ratio(%)";
			else
				strTemp="红色比(%)";
			fprintf(fp,"	");
			fprintf(fp,strTemp);
		}
		if(m_opData.m_bRa)
		{
			strTemp="Ra";
			fprintf(fp,"	");
			fprintf(fp,strTemp);

			if(g_bHaveCRI)
			{
				strTemp="CRI";
				fprintf(fp,"	");
				fprintf(fp,strTemp);
			}
		}

		if(m_opData.m_bRO)
		{
			for(int j=0;j<15;j++)
			{
				strTemp.Format("R%d",j+1);
				fprintf(fp,"	");
				fprintf(fp,strTemp);
			}
		}
		if(1)
		{
			strTemp="SDCM";
			fprintf(fp,"	");
			fprintf(fp,strTemp);
		}
		if(m_opData.m_bPhoEff)
		{
			if(g_bEnglish)
			{
				strTemp = "Fmol(umol/s)";
				if(m_iPhType == PH_E)
					strTemp = "Fmol(umol/m2/s)";
			}
			else
			{
				strTemp = "光量子数(umol/s)";
				if(m_iPhType == PH_E)
					strTemp = "光量子数(umol/m2/s)";
			}
			fprintf(fp,"	");
			fprintf(fp,strTemp);
			
			if(g_bEnglish)
			{
				strTemp="Fluorescence and blue light ratio";
			}
			else
			{
				strTemp="荧光蓝光比";
			}
			fprintf(fp,"	");
			fprintf(fp,strTemp);
			
			if(g_bEnglish)
			{
				strTemp="Fluorescent efficiency";
			}
			else
			{
				strTemp="荧光效能";
			}
			fprintf(fp,"	");
			fprintf(fp,strTemp);

		}
		if(m_opData.m_bInfo)
		{
			if(g_bEnglish)
				strTemp="Model";
			else
				strTemp="产品型号";
			fprintf(fp,"	");
			fprintf(fp,strTemp);

			if(g_bEnglish)
				strTemp="Number";
			else
				strTemp="产品编号";
			fprintf(fp,"	");
			fprintf(fp,strTemp);

			if(g_bEnglish)
				strTemp="Manufacturer";
			else
				strTemp="制造厂商";
			fprintf(fp,"	");
			fprintf(fp,strTemp);

			if(g_bEnglish)
				strTemp="Temperature";
			else
				strTemp="环境温度";
			fprintf(fp,"	");
			fprintf(fp,strTemp);

			if(g_bEnglish)
				strTemp="humidity";
			else
				strTemp="环境湿度";
			fprintf(fp,"	");
			fprintf(fp,strTemp);

			if(g_bEnglish)
				strTemp="Tester";
			else
				strTemp="测试人员";
			fprintf(fp,"	");
			fprintf(fp,strTemp);

			if(g_bEnglish)
				strTemp="Test Date";
			else
				strTemp="测试时间";
			fprintf(fp,"	");
			fprintf(fp,strTemp);

			if(g_bEnglish)
				strTemp="Remark";
			else
				strTemp="备注";
			fprintf(fp,"	");
			fprintf(fp,strTemp);
		}

		if(g_SPEC.m_bHaveLEDTMPCtrl == TRUE)
		{
			strTemp="LED TMP";
			fprintf(fp,"	");
			fprintf(fp,strTemp);
		}

		fprintf(fp,"\n");

		int NN=m_listData.GetSize();
		for(int i=0;i<NN;i++)
		{
			CLED300Data *temp=m_listData[i];
			strTemp.Format("%04d",i+1);
//			fprintf(fp,"	");
			fprintf(fp,strTemp);

			if(m_opData.m_bNote)
			{
				strTemp=temp->m_spData.m_strNumber;
				fprintf(fp,"	");
				fprintf(fp,strTemp);
			}
			if(1)
			{
				strTemp=temp->m_spData.m_strDate;
				fprintf(fp,"	");
				fprintf(fp,strTemp);
			}
			if(1)
			{
				strTemp=g_SPEC.sFormat(temp->m_spData.m_fIntTime,1);
				fprintf(fp,"	");
				fprintf(fp,strTemp);
			}
			if(m_opData.m_bLevel)
			{
				COLORREF color;
				if(g_iLEDClass_Type == 1)
					strTemp = m_newClassLimit.GetLevel(*temp, m_iPhType, color);
				else
					strTemp=m_levelLimit.GetLevel(*temp, m_iPhType);
				fprintf(fp,"	");
				fprintf(fp,strTemp);
			}
			if(m_opData.m_bWhite)
			{
				if(temp->m_spData.m_bHaveData)
					strTemp=m_xyZone.IN_ZONE(temp->m_spData.m_x,temp->m_spData.m_y);
				else
					strTemp="";
				fprintf(fp,"	");
				fprintf(fp,strTemp);
			}
			if(m_opData.m_bIF)
			{
				if(temp->m_spData.m_bTestF)
					strTemp=g_SPEC.sFormat(temp->m_spData.m_fIF,4);
				else
					strTemp="";
				fprintf(fp,"	");
				fprintf(fp,strTemp);
			}
			if(m_opData.m_bVF)
			{
				if(temp->m_spData.m_bTestF)
					strTemp=g_SPEC.sFormat(temp->m_spData.m_fVF,4);
				else
					strTemp="";
				fprintf(fp,"	");
				fprintf(fp,strTemp);
			}
			if(m_opData.m_bP)
			{
				if(temp->m_spData.m_bTestF)
					strTemp=g_SPEC.sFormat(temp->m_spData.m_fPow,4);
				else
					strTemp="";
				fprintf(fp,"	");
				fprintf(fp,strTemp);

				if(temp->m_spData.m_bTestF)
					strTemp=g_SPEC.sFormat(temp->m_spData.m_fPF,4);
				else
					strTemp="";
				fprintf(fp,"	");
				fprintf(fp,strTemp);
			}
			if(m_opData.m_bPH)
			{
				if(temp->m_spData.m_bTestPH&&temp->m_spData.m_bHaveColorPara)
					strTemp=g_SPEC.sFormat(temp->m_spData.m_fPH,5);
				else
					strTemp="";
				fprintf(fp,"	");
				fprintf(fp,strTemp);
			}

			if(m_opData.m_bPhSP)
			{
				float fPh_, fSP;
				BOOL bHave = temp->m_spData.CalcPh_(fPh_, fSP);
				if(bHave)
					strTemp.Format("%.5g", fPh_);
				else
					strTemp = "";
				fprintf(fp,"	");
				fprintf(fp,strTemp);
				
				if(bHave)
					strTemp.Format("%.5g", fSP);
				else
					strTemp = "";
				fprintf(fp,"	");
				fprintf(fp,strTemp);
			}

			if(iLamp == 0)
			{
				if(m_iPhType==PH_F)
				{
					if(temp->m_spData.m_bTestPH)
						strTemp=g_SPEC.sFormat(temp->m_spData.m_fPh_e*1000,5);
					else
						strTemp="";
					fprintf(fp,"	");
					fprintf(fp,strTemp);
				}
				if(m_iPhType==PH_E)
				{
					if(temp->m_spData.m_bTestPH)
						strTemp=g_SPEC.sFormat(temp->m_spData.m_fPh_e,5);
					else
						strTemp="";
					fprintf(fp,"	");
					fprintf(fp,strTemp);
				}
				if(m_opData.m_bPH&&(m_iPhType==PH_I||m_iPhType==PH_Ie))
				{
					if(temp->m_spData.m_fDistance==0.316f)
						strTemp="CIE A";
					else if(temp->m_spData.m_fDistance==0.100f)
						strTemp="CIE B";
					else
						strTemp.Format("%.3f m",temp->m_spData.m_fDistance);
					fprintf(fp,"	");
					fprintf(fp,strTemp);
				}
				if(m_iPhType==PH_F)   //不一样的地方
				{
					float fEff;
					if(temp->m_spData.m_bTestF&&temp->m_spData.m_bTestPH&&temp->m_spData.m_bHaveColorPara)
					{
						if(temp->m_spData.m_fPow<=0)
							fEff=0;
						else
							fEff=temp->m_spData.m_fPH/(temp->m_spData.m_fPow);
						strTemp.Format("%.2f",fEff);
					}
					else
						strTemp="";
					fprintf(fp,"	");
					fprintf(fp,strTemp);
				}
			}
	
			if(m_opData.m_bIp)
			{
				if(temp->m_spData.m_bHaveData)
					strTemp.Format("%.0f",temp->m_spData.m_fIp);
				else
					strTemp="";
				fprintf(fp,"	");
				fprintf(fp,strTemp);
			}
			if(m_opData.m_bXY)
			{
				if(temp->m_spData.m_bHaveData&&temp->m_spData.m_bHaveColorPara)
					strTemp.Format("%.4f",temp->m_spData.m_x);
				else
					strTemp="";
				fprintf(fp,"	");
				fprintf(fp,strTemp);
			}
			if(m_opData.m_bXY)
			{
				if(temp->m_spData.m_bHaveData&&temp->m_spData.m_bHaveColorPara)
					strTemp.Format("%.4f",temp->m_spData.m_y);
				else
					strTemp="";
				fprintf(fp,"	");
				fprintf(fp,strTemp);
			}
			if(m_opData.m_bUV)
			{
				if(temp->m_spData.m_bHaveData&&temp->m_spData.m_bHaveColorPara)
					strTemp.Format("%.4f",temp->m_spData.m_u);
				else
					strTemp="";
				fprintf(fp,"	");
				fprintf(fp,strTemp);
			}
			if(m_opData.m_bUV)
			{
				if(temp->m_spData.m_bHaveData&&temp->m_spData.m_bHaveColorPara)
					strTemp.Format("%.4f",temp->m_spData.m_v);
				else
					strTemp="";
				fprintf(fp,"	");
				fprintf(fp,strTemp);
			}
			if(m_opData.m_bTc)
			{
				if(temp->m_spData.m_bHaveData&&temp->m_spData.m_bHaveColorPara)
					strTemp.Format("%.0f",temp->m_spData.m_fCCT);
				else
					strTemp="";
				fprintf(fp,"	");
				fprintf(fp,strTemp);
			}
			if(m_opData.m_bdC)
			{
				if(temp->m_spData.m_bHaveData&&temp->m_spData.m_bHaveColorPara)
					strTemp.Format("%.4f",temp->m_spData.m_fdc);
				else
					strTemp="";
				fprintf(fp,"	");
				fprintf(fp,strTemp);
			}
			if(m_opData.m_bLd)
			{
				if(temp->m_spData.m_bHaveData&&temp->m_spData.m_bHaveColorPara)
					strTemp.Format("%.1f",temp->m_spData.m_fMainlambda);
				else
					strTemp="";
				fprintf(fp,"	");
				fprintf(fp,strTemp);
			}
			if(m_opData.m_bPur)
			{
				if(temp->m_spData.m_bHaveData&&temp->m_spData.m_bHaveColorPara)
					strTemp.Format("%.1f",temp->m_spData.m_fPurity);
				else
					strTemp="";
				fprintf(fp,"	");
				fprintf(fp,strTemp);
			}
			if(m_opData.m_bLp)
			{
				if(temp->m_spData.m_bHaveData)
					strTemp.Format("%.1f",temp->m_spData.m_fMaxlambda);
				else
					strTemp="";
				fprintf(fp,"	");
				fprintf(fp,strTemp);
			}
			if(m_opData.m_bHW)
			{
				if(temp->m_spData.m_bHaveData)
					strTemp.Format("%.1f",temp->m_spData.m_fHalflambda);
				else
					strTemp="";
				fprintf(fp,"	");
				fprintf(fp,strTemp);
			}
			if(m_opData.m_bRR)
			{
				if(temp->m_spData.m_bHaveData&&temp->m_spData.m_bHaveColorPara)
					strTemp.Format("%.1f",temp->m_spData.m_fRedRatio);
				else
					strTemp="";
				fprintf(fp,"	");
				fprintf(fp,strTemp);
			}
			if(m_opData.m_bRa)
			{
				if(temp->m_spData.m_bHaveData&&temp->m_spData.m_bHaveColorPara)
					strTemp.Format("%.1f",temp->m_spData.m_fRa);
				else
					strTemp="";
				fprintf(fp,"	");
				fprintf(fp,strTemp);

				if(g_bHaveCRI)
				{
					float fCRI=0;
					for(int i=0;i<14;i++)
					{
						fCRI=fCRI+temp->m_spData.m_fRi[i];
					}
					fCRI=fCRI/14;
					if(temp->m_spData.m_bHaveData&&temp->m_spData.m_bHaveColorPara)
						strTemp.Format("%.1f",fCRI);
					else
						strTemp="";
					fprintf(fp,"	");
					fprintf(fp,strTemp);
				}
			}

			if(m_opData.m_bRO)
			{
				for(int j=0;j<15;j++)
				{
					if(temp->m_spData.m_bHaveData&&temp->m_spData.m_bHaveColorPara)
						strTemp.Format("%.0f",temp->m_spData.m_fRi[j]);
					else
						strTemp="";
					fprintf(fp,"	");
					fprintf(fp,strTemp);
				}
			}

			if(1)
			{
				if(temp->m_spData.m_bHaveData&&temp->m_spData.m_bHaveColorPara)
					strTemp.Format("%.1f",temp->m_spData.GetSDCM(m_opData.m_iSeleTc));
				else
					strTemp="";
				fprintf(fp,"	");
				fprintf(fp,strTemp);
				
			}
			if(m_opData.m_bPhoEff)
			{
				float fMol  = 0;
				float fEff1 = 0;
				float fEff2 = 0;
				
				BOOL bPho = temp->m_spData.CalcPhoEff(fMol, fEff1, fEff2, m_iPhType);
				
				strTemp.Format("%.5g",fMol);
				if(bPho == FALSE)
					strTemp = "   ";
				fprintf(fp,"	");
				fprintf(fp,strTemp);
				
				strTemp = g_SPEC.sFormat(fEff1,4);
				if(bPho == FALSE)
					strTemp = "   ";
				fprintf(fp,"	");
				fprintf(fp,strTemp);
				
				strTemp = g_SPEC.sFormat(fEff2,4);
				if(bPho == FALSE)
					strTemp = "   ";
				fprintf(fp,"	");
				fprintf(fp,strTemp);

			}
			if(m_opData.m_bInfo)
			{
				strTemp=temp->m_spData.m_strModel;
				fprintf(fp,"	");
				fprintf(fp,strTemp);

				strTemp=temp->m_spData.m_strNumber;
				fprintf(fp,"	");
				fprintf(fp,strTemp);

				strTemp=temp->m_spData.m_strFactory;
				fprintf(fp,"	");
				fprintf(fp,strTemp);

				strTemp=temp->m_spData.m_strT;
				fprintf(fp,"	");
				fprintf(fp,strTemp);

				strTemp=temp->m_spData.m_strH;
				fprintf(fp,"	");
				fprintf(fp,strTemp);

				strTemp=temp->m_spData.m_strTester;
				fprintf(fp,"	");
				fprintf(fp,strTemp);

				strTemp=temp->m_spData.m_strDate;
				fprintf(fp,"	");
				fprintf(fp,strTemp);

				strTemp=temp->m_spData.m_strRemark;
				fprintf(fp,"	");
				fprintf(fp,strTemp);
			}

			fprintf(fp,"\n");
		}
		fclose(fp);
	}
	return TRUE;
}

void CLED300ListData::Serialize(CArchive &ar)
{
	CString strVer;
	int i,iN;
	if (ar.IsStoring())
	{
		strVer="LED300_B";
		ar<<strVer;
		ar<<m_iPhType;
		iN=m_listData.GetSize();
		ar<<iN;
		for(i=0;i<iN;i++)
			m_listData.GetAt(i)->Serialize(ar);
		m_opData.Serialize(ar);
		m_levelLimit.Serialize(ar);
		m_xyZone.Serialize(ar);
		m_newClassLimit.Serialize(ar);
	}
	else
	{
		ar>>strVer;
		if(strVer!="LED300_A"&&strVer!="LED300_B")
		{
			if(g_bEnglish)
				AfxMessageBox("The file isn't SpectraNexus files",MB_ICONINFORMATION);
			else
				AfxMessageBox("该文件非SpectraNexus文件",MB_ICONINFORMATION);
			return;
		}
		ar>>m_iPhType;
		m_listData.RemoveAll();
		ar>>iN;
		for(i=0;i<iN;i++)
		{
			CLED300Data *temp=new CLED300Data();
			temp->Serialize(ar);
			m_listData.Add(temp);
		}
		m_opData.Serialize(ar);
		m_levelLimit.Serialize(ar);
		m_xyZone.Serialize(ar);
		if(strVer!="LED300_A")
			m_newClassLimit.Serialize(ar);
	}
}

void CLED300ListData::printListTable(CDC *pDC, CRect printRect, int iCurPage, int iMaxPage,int iB,CString strPathName,int PT_N)
{
	CFont *pOldFont;
	CFont Font1;

	if(printRect.Width()>printRect.Height())
	{
		Font1.CreateFont(printRect.Height()/55,0,0,0,600,FALSE,FALSE,0,
			ANSI_CHARSET,OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
			DEFAULT_PITCH|FF_MODERN,"Courier New");
	}
	else
	{
		Font1.CreateFont(printRect.Height()/65,0,0,0,600,FALSE,FALSE,0,
			ANSI_CHARSET,OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
			DEFAULT_PITCH|FF_MODERN,"Courier New");
	}
	
	CPen  *pOldPen;
	CPen  Pen1;
	CPen  Pen2;

	Pen1.CreatePen(PS_SOLID,4,RGB(0,0,0));
	Pen2.CreatePen(PS_SOLID,2,RGB(0,0,0));

	pOldPen=pDC->SelectObject(&Pen1);
	pOldFont=pDC->SelectObject(&Font1);

	int i;

	int iFontH,iFontW;
	TEXTMETRIC  tm;

	pDC->GetTextMetrics(&tm);
	iFontH=tm.tmHeight+tm.tmExternalLeading;
	iFontW=tm.tmAveCharWidth;

	int Wn=(int)(iFontW*1.05);
	int Hn=iFontH;

	pDC->SetTextAlign(TA_CENTER);

	pDC->Rectangle(printRect);
	pDC->SelectObject(&Pen2);

	float fOne=printRect.Height()/(PT_N+2.0f);

	for(i=2;i<(2+PT_N);i++)
	{
		pDC->MoveTo(printRect.left,(int)(printRect.top+i*fOne));
		pDC->LineTo(printRect.right,(int)(printRect.top+i*fOne));
	}
	int iCurWPos;
	int W;
	float fAddH=0.2f;
	CArray<int,int> saveW;

	iCurWPos=printRect.left;
	if(1)
	{
		W=6*Wn;
		saveW.Add(W);
		iCurWPos=iCurWPos+W;
		pDC->MoveTo(iCurWPos,printRect.top);
		pDC->LineTo(iCurWPos,printRect.bottom);
		if(g_bEnglish)
			pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+fAddH*Hn),"No.");
		else
			pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+fAddH*Hn),"序号");
	}
	if(m_opData.m_bNote)
	{
		W=14*Wn;
		saveW.Add(W);
		iCurWPos=iCurWPos+W;
		pDC->MoveTo(iCurWPos,printRect.top);
		pDC->LineTo(iCurWPos,printRect.bottom);
		if(g_bEnglish)
			pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+fAddH*Hn),"Number");
		else
			pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+fAddH*Hn),"编 号");
	}
	if(m_opData.m_bLevel)
	{
		W=8*Wn;
		saveW.Add(W);
		iCurWPos=iCurWPos+W;
		pDC->MoveTo(iCurWPos,printRect.top);
		pDC->LineTo(iCurWPos,printRect.bottom);
		if(g_bEnglish)
			pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+fAddH*Hn),"LEVEL");
		else
			pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+fAddH*Hn),"分级");
		pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+(fAddH+1)*Hn),"");
	}
	if(m_opData.m_bWhite)
	{
		W=10*Wn;
		saveW.Add(W);
		iCurWPos=iCurWPos+W;
		pDC->MoveTo(iCurWPos,printRect.top);
		pDC->LineTo(iCurWPos,printRect.bottom);
		if(g_bEnglish)
			pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+fAddH*Hn),"WHITE");
		else
			pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+fAddH*Hn),"白光");
		pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+(fAddH+1)*Hn),"");
	}
	if(m_opData.m_bVF)
	{
		W=6*Wn;
		saveW.Add(W);
		iCurWPos=iCurWPos+W;
		pDC->MoveTo(iCurWPos,printRect.top);
		pDC->LineTo(iCurWPos,printRect.bottom);
		pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+fAddH*Hn),"U");
		pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+(fAddH+1)*Hn),"(V)");
	}
	if(m_opData.m_bIF)
	{
		W=6*Wn;
		saveW.Add(W);
		iCurWPos=iCurWPos+W;
		pDC->MoveTo(iCurWPos,printRect.top);
		pDC->LineTo(iCurWPos,printRect.bottom);
		pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+fAddH*Hn),"I");
		pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+(fAddH+1)*Hn),"(A)");
	}
	if(m_opData.m_bP)
	{
		W=6*Wn;
		saveW.Add(W);
		iCurWPos=iCurWPos+W;
		pDC->MoveTo(iCurWPos,printRect.top);
		pDC->LineTo(iCurWPos,printRect.bottom);
		pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+fAddH*Hn),"P");
		pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+(fAddH+1)*Hn),"(W)");
		W=6*Wn;
		saveW.Add(W);
		iCurWPos=iCurWPos+W;
		pDC->MoveTo(iCurWPos,printRect.top);
		pDC->LineTo(iCurWPos,printRect.bottom);
		pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+fAddH*Hn),"PF");
		pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+(fAddH+1)*Hn),"");
	}
	int iLamp=0;
	if(m_listData.GetSize()>0)
		iLamp=m_listData.GetAt(0)->m_spData.m_iLamp;

	if(m_opData.m_bPH)
	{
		W=8*Wn;
		saveW.Add(W);
		iCurWPos=iCurWPos+W;
		pDC->MoveTo(iCurWPos,printRect.top);
		pDC->LineTo(iCurWPos,printRect.bottom);
		CString s1,s2;

		s1=CSpectData::PH_Name(iLamp,m_iPhType,s2);
		pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+fAddH*Hn),s1);
		pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+(fAddH+1)*Hn),"("+s2+")");
	}
	if(iLamp==0)
	{
	if(m_iPhType==PH_F)
	{
		W=8*Wn;
		saveW.Add(W);
		iCurWPos=iCurWPos+W;
		pDC->MoveTo(iCurWPos,printRect.top);
		pDC->LineTo(iCurWPos,printRect.bottom);
		CString s1,s2;
		s1=CSpectData::PH_Name(iLamp,PH_Fe,s2);
		pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+fAddH*Hn),s1);
		pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+(fAddH+1)*Hn),"("+s2+")");
	}
	if(m_iPhType==PH_E)
	{
		W=8*Wn;
		saveW.Add(W);
		iCurWPos=iCurWPos+W;
		pDC->MoveTo(iCurWPos,printRect.top);
		pDC->LineTo(iCurWPos,printRect.bottom);
		CString s1,s2;
		s1=CSpectData::PH_Name(iLamp,PH_Ee,s2);
		pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+fAddH*Hn),s1);
		pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+(fAddH+1)*Hn),"("+s2+")");
	}
	if(m_opData.m_bPH&&(m_iPhType==PH_I||m_iPhType==PH_Ie))
	{
		W=6*Wn;
		saveW.Add(W);
		iCurWPos=iCurWPos+W;
		pDC->MoveTo(iCurWPos,printRect.top);
		pDC->LineTo(iCurWPos,printRect.bottom);
		pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+fAddH*Hn),"CIE");
		pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+(fAddH+1)*Hn),"A/B");
	}
	if(m_iPhType==PH_F)
	{
		W=8*Wn;
		saveW.Add(W);
		iCurWPos=iCurWPos+W;
		pDC->MoveTo(iCurWPos,printRect.top);
		pDC->LineTo(iCurWPos,printRect.bottom);
		if(g_bEnglish)
			pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+fAddH*Hn),"Eff.");
		else
			pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+fAddH*Hn),"光效");
		pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+(fAddH+1)*Hn),"(lm/W)");
	}
	}
	if(m_opData.m_bIp)
	{
		W=6*Wn;
		saveW.Add(W);
		iCurWPos=iCurWPos+W;
		pDC->MoveTo(iCurWPos,printRect.top);
		pDC->LineTo(iCurWPos,printRect.bottom);
		pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+fAddH*Hn),"Ip");
		pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+(fAddH+1)*Hn),"");
	}
	if(m_opData.m_bXY)
	{
		W=14*Wn;
		saveW.Add(W);
		iCurWPos=iCurWPos+W;
		pDC->MoveTo(iCurWPos,printRect.top);
		pDC->LineTo(iCurWPos,printRect.bottom);
		if(g_bEnglish)
			pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+fAddH*Hn),"Coordinate");
		else
			pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+fAddH*Hn),"色坐标");
		pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+(fAddH+1)*Hn),"x , y");
	}
	if(m_opData.m_bUV)
	{
		W=14*Wn;
		saveW.Add(W);
		iCurWPos=iCurWPos+W;
		pDC->MoveTo(iCurWPos,printRect.top);
		pDC->LineTo(iCurWPos,printRect.bottom);
		if(g_bEnglish)
			pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+fAddH*Hn),"Coordinate");
		else
			pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+fAddH*Hn),"色坐标");
		pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+(fAddH+1)*Hn),"u', v'");
	}
	if(m_opData.m_bTc)
	{
		W=6*Wn;
		saveW.Add(W);
		iCurWPos=iCurWPos+W;
		pDC->MoveTo(iCurWPos,printRect.top);
		pDC->LineTo(iCurWPos,printRect.bottom);
		if(g_bEnglish)
			pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+fAddH*Hn),"CCT");
		else
			pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+fAddH*Hn),"色温");
		pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+(fAddH+1)*Hn),"(K)");
	}
	if(m_opData.m_bLd)
	{
		W=8*Wn;
		saveW.Add(W);
		iCurWPos=iCurWPos+W;
		pDC->MoveTo(iCurWPos,printRect.top);
		pDC->LineTo(iCurWPos,printRect.bottom);
		if(g_bEnglish)
		{
			pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+fAddH*Hn),"Domi.");
			pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+(fAddH+1)*Hn),"WL(nm)");
		}
		else
		{
			pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+fAddH*Hn),"主波长");
			pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+(fAddH+1)*Hn),"(nm)");
		}
	}
	if(m_opData.m_bPur)
	{
		W=8*Wn;
		saveW.Add(W);
		iCurWPos=iCurWPos+W;
		pDC->MoveTo(iCurWPos,printRect.top);
		pDC->LineTo(iCurWPos,printRect.bottom);
		if(g_bEnglish)
			pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+fAddH*Hn),"Purity");
		else
			pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+fAddH*Hn),"色纯度");
		pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+(fAddH+1)*Hn),"(%)");
	}
	if(m_opData.m_bLp)
	{
		W=8*Wn;
		saveW.Add(W);
		iCurWPos=iCurWPos+W;
		pDC->MoveTo(iCurWPos,printRect.top);
		pDC->LineTo(iCurWPos,printRect.bottom);
		if(g_bEnglish)
		{
			pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+fAddH*Hn),"Peak");
			pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+(fAddH+1)*Hn),"WL(nm)");
		}
		else
		{
			pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+fAddH*Hn),"峰值波长");
			pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+(fAddH+1)*Hn),"(nm)");
		}
	}
	if(m_opData.m_bHW)
	{
		W=8*Wn;
		saveW.Add(W);
		iCurWPos=iCurWPos+W;
		pDC->MoveTo(iCurWPos,printRect.top);
		pDC->LineTo(iCurWPos,printRect.bottom);
		if(g_bEnglish)
		{
			pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+fAddH*Hn),"FWHM");
			pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+(fAddH+1)*Hn),"(nm)");
		}
		else
		{
			pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+fAddH*Hn),"半宽度");
			pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+(fAddH+1)*Hn),"(nm)");
		}
	}
	if(m_opData.m_bRR)
	{
		W=8*Wn;
		saveW.Add(W);
		iCurWPos=iCurWPos+W;
		pDC->MoveTo(iCurWPos,printRect.top);
		pDC->LineTo(iCurWPos,printRect.bottom);
		if(g_bEnglish)
		{
			pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+fAddH*Hn),"Red(%)");
			pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+(fAddH+1)*Hn),"Ratio");
		}
		else
		{
			pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+fAddH*Hn),"红色比");
			pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+(fAddH+1)*Hn),"(%)");
		}
	}
	if(m_opData.m_bRa)
	{
		W=8*Wn;
		saveW.Add(W);
		iCurWPos=iCurWPos+W;
//		pDC->MoveTo(iCurWPos,printRect.top);
//		pDC->LineTo(iCurWPos,printRect.bottom);
		if(g_bEnglish)
			pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+fAddH*Hn),"Render");
		else
			pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+fAddH*Hn),"显示指数");
		pDC->TextOut(iCurWPos-W/2,(int)(printRect.top+(fAddH+1)*Hn),"Ra");
	}

	int iN=m_listData.GetSize();
	float fAddW=0.5f;
	CString sTemp;
	for(i=0;i<PT_N;i++)
	{
		int iCurN=(iCurPage-iB-1)*PT_N+i;  //??? -iB
		if((iCurN+1)>iN)
			break;

		iCurWPos=printRect.left;
		int iCur=0;
		if(1)
		{
			sTemp.Format("%04d",iCurN+1);
			pDC->SetTextAlign(TA_LEFT);
			pDC->TextOut((int)(iCurWPos+fAddW*Wn),(int)(printRect.top+(2+i+fAddH)*fOne),sTemp);
			iCurWPos=iCurWPos+saveW.GetAt(iCur);
			iCur++;
		}
		if(m_opData.m_bNote)
		{
			sTemp=m_listData.GetAt(iCurN)->m_spData.m_strNumber;
			pDC->SetTextAlign(TA_LEFT);
			pDC->TextOut((int)(iCurWPos+fAddW*Wn),(int)(printRect.top+(2+i+fAddH)*fOne),sTemp);
			iCurWPos=iCurWPos+saveW.GetAt(iCur);
			iCur++;
		}
		if(m_opData.m_bLevel)
		{
			COLORREF color;
			sTemp=GetLevel(iCurN, color);
			pDC->SetTextAlign(TA_LEFT);
			pDC->TextOut((int)(iCurWPos+fAddW*Wn),(int)(printRect.top+(2+i+fAddH)*fOne),sTemp);
			iCurWPos=iCurWPos+saveW.GetAt(iCur);
			iCur++;
		}
		if(m_opData.m_bWhite)
		{
			sTemp=GetWhite(iCurN);
			pDC->SetTextAlign(TA_LEFT);
			pDC->TextOut((int)(iCurWPos+fAddW*Wn),(int)(printRect.top+(2+i+fAddH)*fOne),sTemp);
			iCurWPos=iCurWPos+saveW.GetAt(iCur);
			iCur++;
		}
		if(m_opData.m_bVF)
		{
			if(m_listData.GetAt(iCurN)->m_spData.m_bTestF)
			{
				sTemp=g_SPEC.sFormat(m_listData.GetAt(iCurN)->m_spData.m_fVF,4);
				pDC->SetTextAlign(TA_LEFT);
				pDC->TextOut((int)(iCurWPos+fAddW*Wn),(int)(printRect.top+(2+i+fAddH)*fOne),sTemp);
			}
			iCurWPos=iCurWPos+saveW.GetAt(iCur);
			iCur++;
		}
		if(m_opData.m_bIF)
		{
			if(m_listData.GetAt(iCurN)->m_spData.m_bTestF)
			{
				sTemp=g_SPEC.sFormat(m_listData.GetAt(iCurN)->m_spData.m_fIF,4);
				pDC->SetTextAlign(TA_LEFT);
				pDC->TextOut((int)(iCurWPos+fAddW*Wn),(int)(printRect.top+(2+i+fAddH)*fOne),sTemp);
			}
			iCurWPos=iCurWPos+saveW.GetAt(iCur);
			iCur++;
		}
		if(m_opData.m_bP)
		{
			if(m_listData.GetAt(iCurN)->m_spData.m_bTestF)
			{
				sTemp=g_SPEC.sFormat(m_listData.GetAt(iCurN)->m_spData.m_fPow,4);
				pDC->SetTextAlign(TA_LEFT);
				pDC->TextOut((int)(iCurWPos+fAddW*Wn),(int)(printRect.top+(2+i+fAddH)*fOne),sTemp);
			}
			iCurWPos=iCurWPos+saveW.GetAt(iCur);
			iCur++;

			if(m_listData.GetAt(iCurN)->m_spData.m_bTestF)
			{
				sTemp=g_SPEC.sFormat(m_listData.GetAt(iCurN)->m_spData.m_fPF,4);
				pDC->SetTextAlign(TA_LEFT);
				pDC->TextOut((int)(iCurWPos+fAddW*Wn),(int)(printRect.top+(2+i+fAddH)*fOne),sTemp);
			}
			iCurWPos=iCurWPos+saveW.GetAt(iCur);
			iCur++;
		}
		if(m_opData.m_bPH)
		{
			if(m_listData.GetAt(iCurN)->m_spData.m_bTestPH&&m_listData.GetAt(iCurN)->m_spData.m_bHaveColorPara)
			{
				sTemp=g_SPEC.sFormat(m_listData.GetAt(iCurN)->m_spData.m_fPH,4);
				pDC->SetTextAlign(TA_RIGHT);
				pDC->TextOut((int)(iCurWPos+saveW.GetAt(iCur)-fAddW*Wn),(int)(printRect.top+(2+i+fAddH)*fOne),sTemp);
			}
			iCurWPos=iCurWPos+saveW.GetAt(iCur);
			iCur++;
		}
		if(m_iPhType==PH_F)
		{
			if(m_listData.GetAt(iCurN)->m_spData.m_bHaveData)
			{
				sTemp=g_SPEC.sFormat(m_listData.GetAt(iCurN)->m_spData.m_fPh_e*1000,4);
				pDC->SetTextAlign(TA_RIGHT);
				pDC->TextOut((int)(iCurWPos+saveW.GetAt(iCur)-fAddW*Wn),(int)(printRect.top+(2+i+fAddH)*fOne),sTemp);
			}
			iCurWPos=iCurWPos+saveW.GetAt(iCur);
			iCur++;
		}
		if(m_iPhType==PH_E)
		{
			if(m_listData.GetAt(iCurN)->m_spData.m_bHaveData)
			{
				sTemp=g_SPEC.sFormat(m_listData.GetAt(iCurN)->m_spData.m_fPh_e,4);
				pDC->SetTextAlign(TA_RIGHT);
				pDC->TextOut((int)(iCurWPos+saveW.GetAt(iCur)-fAddW*Wn),(int)(printRect.top+(2+i+fAddH)*fOne),sTemp);
			}
			iCurWPos=iCurWPos+saveW.GetAt(iCur);
			iCur++;
		}
		if(m_opData.m_bPH&&(m_iPhType==PH_I||m_iPhType==PH_Ie))
		{
			if(m_listData.GetAt(iCurN)->m_spData.m_fDistance==0.316f)
				sTemp="CIE A";
			else if(m_listData.GetAt(iCurN)->m_spData.m_fDistance==0.100f)
				sTemp="CIE B";
			else
				sTemp.Format("%.3fm",m_listData.GetAt(iCurN)->m_spData.m_fDistance);
			pDC->SetTextAlign(TA_RIGHT);
			pDC->TextOut((int)(iCurWPos+saveW.GetAt(iCur)-fAddW*Wn),(int)(printRect.top+(2+i+fAddH)*fOne),sTemp);
			iCurWPos=iCurWPos+saveW.GetAt(iCur);
			iCur++;
		}
		if(m_iPhType==PH_F)
		{
			if(m_listData.GetAt(iCurN)->m_spData.m_bTestPH&&m_listData.GetAt(iCurN)->m_spData.m_bTestF&&m_listData.GetAt(iCurN)->m_spData.m_bHaveColorPara)
			{
				float fEff;
				if(m_listData.GetAt(iCurN)->m_spData.m_fPow>0)
					fEff=m_listData.GetAt(iCurN)->m_spData.m_fPH/(m_listData.GetAt(iCurN)->m_spData.m_fPow);
				else
					fEff=0;

				sTemp.Format("%.2f",fEff);
				pDC->SetTextAlign(TA_RIGHT);
				pDC->TextOut((int)(iCurWPos+saveW.GetAt(iCur)-fAddW*Wn),(int)(printRect.top+(2+i+fAddH)*fOne),sTemp);
			}
			iCurWPos=iCurWPos+saveW.GetAt(iCur);
			iCur++;
		}
		if(m_opData.m_bIp)
		{
			if(m_listData.GetAt(iCurN)->m_spData.m_bHaveData)
			{
				sTemp.Format("%.0f",m_listData.GetAt(iCurN)->m_spData.m_fIp);
				pDC->SetTextAlign(TA_LEFT);
				pDC->TextOut((int)(iCurWPos+fAddW*Wn),(int)(printRect.top+(2+i+fAddH)*fOne),sTemp);
			}
			iCurWPos=iCurWPos+saveW.GetAt(iCur);
			iCur++;
		}
		if(m_opData.m_bXY)
		{
			if(m_listData.GetAt(iCurN)->m_spData.m_bHaveData&&m_listData.GetAt(iCurN)->m_spData.m_bHaveColorPara)
			{
				sTemp.Format("%.4f,%.4f",m_listData.GetAt(iCurN)->m_spData.m_x,m_listData.GetAt(iCurN)->m_spData.m_y);
				pDC->SetTextAlign(TA_LEFT);
				pDC->TextOut((int)(iCurWPos+fAddW*Wn),(int)(printRect.top+(2+i+fAddH)*fOne),sTemp);
			}
			iCurWPos=iCurWPos+saveW.GetAt(iCur);
			iCur++;
		}
		if(m_opData.m_bUV)
		{
			if(m_listData.GetAt(iCurN)->m_spData.m_bHaveData&&m_listData.GetAt(iCurN)->m_spData.m_bHaveColorPara)
			{
				sTemp.Format("%.4f,%.4f",m_listData.GetAt(iCurN)->m_spData.m_u,m_listData.GetAt(iCurN)->m_spData.m_v);
				pDC->SetTextAlign(TA_LEFT);
				pDC->TextOut((int)(iCurWPos+fAddW*Wn),(int)(printRect.top+(2+i+fAddH)*fOne),sTemp);
			}
			iCurWPos=iCurWPos+saveW.GetAt(iCur);
			iCur++;
		}
		if(m_opData.m_bTc)
		{
			if(m_listData.GetAt(iCurN)->m_spData.m_bHaveData&&m_listData.GetAt(iCurN)->m_spData.m_bHaveColorPara)
			{
				sTemp.Format("%.0f",m_listData.GetAt(iCurN)->m_spData.m_fCCT);
				pDC->SetTextAlign(TA_RIGHT);
				pDC->TextOut((int)(iCurWPos+saveW.GetAt(iCur)-fAddW*Wn),(int)(printRect.top+(2+i+fAddH)*fOne),sTemp);
			}
			iCurWPos=iCurWPos+saveW.GetAt(iCur);
			iCur++;
		}
		if(m_opData.m_bLd)
		{
			if(m_listData.GetAt(iCurN)->m_spData.m_bHaveData&&m_listData.GetAt(iCurN)->m_spData.m_bHaveColorPara)
			{
				sTemp.Format("%.1f",m_listData.GetAt(iCurN)->m_spData.m_fMainlambda);
				pDC->SetTextAlign(TA_RIGHT);
				pDC->TextOut((int)(iCurWPos+saveW.GetAt(iCur)-fAddW*Wn),(int)(printRect.top+(2+i+fAddH)*fOne),sTemp);
			}
			iCurWPos=iCurWPos+saveW.GetAt(iCur);
			iCur++;
		}
		if(m_opData.m_bPur)
		{
			if(m_listData.GetAt(iCurN)->m_spData.m_bHaveData&&m_listData.GetAt(iCurN)->m_spData.m_bHaveColorPara)
			{
				sTemp.Format("%.2f",m_listData.GetAt(iCurN)->m_spData.m_fPurity);
				pDC->SetTextAlign(TA_RIGHT);
				pDC->TextOut((int)(iCurWPos+saveW.GetAt(iCur)-fAddW*Wn),(int)(printRect.top+(2+i+fAddH)*fOne),sTemp);
			}
			iCurWPos=iCurWPos+saveW.GetAt(iCur);
			iCur++;
		}
		if(m_opData.m_bLp)
		{
			if(m_listData.GetAt(iCurN)->m_spData.m_bHaveData)
			{
				sTemp.Format("%.1f",m_listData.GetAt(iCurN)->m_spData.m_fMaxlambda);
				pDC->SetTextAlign(TA_RIGHT);
				pDC->TextOut((int)(iCurWPos+saveW.GetAt(iCur)-fAddW*Wn),(int)(printRect.top+(2+i+fAddH)*fOne),sTemp);
			}
			iCurWPos=iCurWPos+saveW.GetAt(iCur);
			iCur++;
		}
		if(m_opData.m_bHW)
		{
			if(m_listData.GetAt(iCurN)->m_spData.m_bHaveData)
			{
				sTemp.Format("%.1f",m_listData.GetAt(iCurN)->m_spData.m_fHalflambda);
				pDC->SetTextAlign(TA_RIGHT);
				pDC->TextOut((int)(iCurWPos+saveW.GetAt(iCur)-fAddW*Wn),(int)(printRect.top+(2+i+fAddH)*fOne),sTemp);
			}
			iCurWPos=iCurWPos+saveW.GetAt(iCur);
			iCur++;
		}
		if(m_opData.m_bRR)
		{
			if(m_listData.GetAt(iCurN)->m_spData.m_bHaveData&&m_listData.GetAt(iCurN)->m_spData.m_bHaveColorPara)
			{
				sTemp.Format("%.1f",m_listData.GetAt(iCurN)->m_spData.m_fRedRatio);
				pDC->SetTextAlign(TA_RIGHT);
				pDC->TextOut((int)(iCurWPos+saveW.GetAt(iCur)-fAddW*Wn),(int)(printRect.top+(2+i+fAddH)*fOne),sTemp);
			}
			iCurWPos=iCurWPos+saveW.GetAt(iCur);
			iCur++;
		}
		if(m_opData.m_bRa)
		{
			if(m_listData.GetAt(iCurN)->m_spData.m_bHaveData&&m_listData.GetAt(iCurN)->m_spData.m_bHaveColorPara)
			{
				sTemp.Format("%.1f",m_listData.GetAt(iCurN)->m_spData.m_fRa);
				pDC->SetTextAlign(TA_RIGHT);
				pDC->TextOut((int)(iCurWPos+saveW.GetAt(iCur)-fAddW*Wn),(int)(printRect.top+(2+i+fAddH)*fOne),sTemp);
			}
			iCurWPos=iCurWPos+saveW.GetAt(iCur);
			iCur++;
		}
	}
	pDC->SetTextAlign(TA_CENTER);
	pDC->TextOut(printRect.left+printRect.Width()/2,printRect.bottom+2*Hn,strPathName);
	pDC->SetTextAlign(TA_RIGHT);
	if(g_bEnglish)
		sTemp.Format("%d Of %d",iCurPage,iMaxPage);
	else
		sTemp.Format("第 %d 页  共 %d 页",iCurPage,iMaxPage);
	pDC->TextOut(printRect.left+printRect.Width()*16/17,printRect.bottom+2*Hn,sTemp);
	pDC->SelectObject(pOldFont);
	pDC->SelectObject(pOldPen);

}

void CLED300ListData::ListHead(CListCtrl &cList)
{
	m_failFlagData.ClearAll();
	COPSetupData *op = &m_opData;

	CString strRe = "";
	cList.ShowWindow(FALSE);

	cList.DeleteAllItems();
	while(1)
	{
		if(cList.DeleteColumn(0)==FALSE)
			break;
	}

	int iN = 0;

	CString strTemp;

	if(g_bEnglish)
		strTemp = "SN.";
	else
		strTemp = "序号";
	cList.InsertColumn(iN, strTemp);
	cList.SetColumnWidth(iN, 60);
	iN++;
	m_failFlagData.AddListPara(CFailFlagData::NONE_DATA);

	if(op->m_bNote)
	{
		if(g_bEnglish)
			strTemp=" Number";
		else
			strTemp=" 编号";
		cList.InsertColumn(iN,strTemp);
		cList.SetColumnWidth(iN,180);
		iN++;
		m_failFlagData.AddListPara(CFailFlagData::NONE_DATA);
	}
	if(op->m_bLevel)
	{
		if(g_bEnglish)
			strTemp="LEVEL";
		else
			strTemp="分级(LEVEL)";
		cList.InsertColumn(iN,strTemp);
		cList.SetColumnWidth(iN,60);
		iN++;
		m_failFlagData.AddListPara(CFailFlagData::NONE_DATA);
	}
	if(op->m_bWhite)
	{
		if(g_bEnglish)
			strTemp="WHITE";
		else
			strTemp="白光分类(WHITE)";
		cList.InsertColumn(iN,strTemp);
		cList.SetColumnWidth(iN,120);
		iN++;
		m_failFlagData.AddListPara(CFailFlagData::NONE_DATA);
	}
	int iLamp=g_SPEC.m_iLamp;
	if(m_listData.GetSize()>0)
	{
		iLamp=m_listData.GetAt(0)->m_spData.m_iLamp;
	}
	if(op->m_bPH)
	{
		strTemp=CSpectData::PH_Name(iLamp,m_iPhType);
		cList.InsertColumn(iN,strTemp);
		cList.SetColumnWidth(iN,80);
		iN++;

		m_failFlagData.AddListPara(TD_F);
	}
	if(op->m_bPhSP)
	{
		if(g_bEnglish)
			strTemp = "Scotopic";
		else
			strTemp = "暗视觉光度";
		cList.InsertColumn(iN,strTemp);
		cList.SetColumnWidth(iN,80);
		iN++;
		m_failFlagData.AddListPara(CFailFlagData::NONE_DATA);

		if(g_bEnglish)
			strTemp = "S/P";
		else
			strTemp = "S/P";
		cList.InsertColumn(iN,strTemp);
		cList.SetColumnWidth(iN,80);
		iN++;

		m_failFlagData.AddListPara(CFailFlagData::NONE_DATA);
	}
	if(iLamp==0&&op->m_bPH)
	{
		if(m_iPhType==PH_F)           //注意,有光通量，即有辐射通量
		{
			strTemp=CSpectData::PH_Name(iLamp,PH_Fe);
			cList.InsertColumn(iN,strTemp);
			cList.SetColumnWidth(iN,80);
			iN++;

			m_failFlagData.AddListPara(TD_Fe);
		}
		if(m_iPhType==PH_E)           //注意,有光通量，即有辐射通量
		{
			strTemp=CSpectData::PH_Name(iLamp,PH_Ee);
			cList.InsertColumn(iN,strTemp);
			cList.SetColumnWidth(iN,80);
			iN++;

			m_failFlagData.AddListPara(CFailFlagData::NONE_DATA);
		}
		if(op->m_bPH&&(m_iPhType==PH_I||m_iPhType==PH_Ie))
		{
			if(g_bEnglish)
				strTemp="Ie(mW/sr)(CIE A/B)";
			else
				strTemp="辐射强度(mW/sr)(条件)";
			cList.InsertColumn(iN,strTemp);
			cList.SetColumnWidth(iN,120);
			iN++;

			m_failFlagData.AddListPara(CFailFlagData::NONE_DATA);
		}
		if(m_iPhType==PH_F)
		{
			if(g_bEnglish)
				strTemp="Eff.(lm/W)";
			else
				strTemp="光效(lm/W)";
			cList.InsertColumn(iN,strTemp);
			cList.SetColumnWidth(iN,80);
			iN++;

			m_failFlagData.AddListPara(TD_EFF);
		}
	}
	if(op->m_bXY)
	{
		if(g_bEnglish)
			strTemp="x,y";
		else
			strTemp="色坐标 x,y";
		cList.InsertColumn(iN,strTemp);
		cList.SetColumnWidth(iN,100);
		iN++;

		m_failFlagData.AddListPara(TD_X);
	}

	if(op->m_bUV)
	{
		if(g_bEnglish)
			strTemp="u',v'";
		else
			strTemp="色坐标 u',v'";
		cList.InsertColumn(iN,strTemp);
		cList.SetColumnWidth(iN,100);
		iN++;

		m_failFlagData.AddListPara(TD_U);
	}

	if(op->m_bTc)
	{
		if(g_bEnglish)
			strTemp="CCT(K)";
		else
			strTemp="色温(K)";
		cList.InsertColumn(iN,strTemp);
		cList.SetColumnWidth(iN,60);
		iN++;

		m_failFlagData.AddListPara(TD_CCT);
	}
	if(op->m_bdC)
	{
		if(g_bEnglish)
			strTemp="Duv";
		else
			strTemp="色差Duv";
		cList.InsertColumn(iN,strTemp);
		cList.SetColumnWidth(iN,60);
		iN++;

		m_failFlagData.AddListPara(TD_dC);
	}
	if(op->m_bIp)
	{
		strTemp="  Ip";
		cList.InsertColumn(iN,strTemp);
		cList.SetColumnWidth(iN,100);
		iN++;

		m_failFlagData.AddListPara(CFailFlagData::NONE_DATA);
	}

	if(op->m_bLd)
	{
		if(g_bEnglish)
			strTemp="Ld(nm)";
		else
			strTemp="主波长(nm)";
		cList.InsertColumn(iN,strTemp);
		cList.SetColumnWidth(iN,80);
		iN++;
		
		m_failFlagData.AddListPara(TD_LD);
	}

	if(op->m_bPur)
	{
		if(g_bEnglish)
			strTemp="Pur(%)";
		else
			strTemp="色纯度(%)";
		cList.InsertColumn(iN,strTemp);
		cList.SetColumnWidth(iN,80);
		iN++;

		m_failFlagData.AddListPara(TD_PUR);
	}

	if(op->m_bLp)
	{
		if(g_bEnglish)
			strTemp="Lp(nm)";
		else
			strTemp="峰值波长(nm)";
		cList.InsertColumn(iN,strTemp);
		cList.SetColumnWidth(iN,100);
		iN++;

		m_failFlagData.AddListPara(TD_LP);
	}

	if(op->m_bHW)
	{
		if(g_bEnglish)
			strTemp="FWHM(nm)";
		else
			strTemp="半波宽(nm)";
		cList.InsertColumn(iN,strTemp);
		cList.SetColumnWidth(iN,80);
		iN++;

		m_failFlagData.AddListPara(CFailFlagData::NONE_DATA);
	}

	if(op->m_bRR)
	{
		if(g_bEnglish)
			strTemp="Red Ratio(%)";
		else
			strTemp="红色比(%)";
		cList.InsertColumn(iN,strTemp);
		cList.SetColumnWidth(iN,80);
		iN++;

		m_failFlagData.AddListPara(CFailFlagData::NONE_DATA);
	}

	if(op->m_bRa)
	{
		strTemp="Ra";
		cList.InsertColumn(iN,strTemp);
		cList.SetColumnWidth(iN,80);
		iN++;

		m_failFlagData.AddListPara(TD_RA);

		if(g_bHaveCRI)
		{
			strTemp="CRI";
			cList.InsertColumn(iN,strTemp);
			cList.SetColumnWidth(iN,80);
			iN++;

			m_failFlagData.AddListPara(CFailFlagData::NONE_DATA);
		}
	}
	if(op->m_bRO)
	{
		for(int i = 0; i < 15; i++)
		{
			strTemp.Format(_T("R%d"), i + 1);
			cList.InsertColumn(iN,strTemp);
			cList.SetColumnWidth(iN,80);
			iN++;

			m_failFlagData.AddListPara(CFailFlagData::NONE_DATA);
		}
	}

	if(1)
	{
		strTemp="SDCM";
		cList.InsertColumn(iN,strTemp);
		cList.SetColumnWidth(iN,80);
		iN++;

		m_failFlagData.AddListPara(CFailFlagData::NONE_DATA);
	}

	if(0)//op->m_bZW)
	{
		strTemp="UVC";
		cList.InsertColumn(iN,strTemp);
		cList.SetColumnWidth(iN,80);
		iN++;
		m_failFlagData.AddListPara(CFailFlagData::NONE_DATA);

		strTemp="UVB";
		cList.InsertColumn(iN,strTemp);
		cList.SetColumnWidth(iN,80);
		iN++;
		m_failFlagData.AddListPara(CFailFlagData::NONE_DATA);

		strTemp="UVA";
		cList.InsertColumn(iN,strTemp);
		cList.SetColumnWidth(iN,80);
		iN++;
		m_failFlagData.AddListPara(CFailFlagData::NONE_DATA);

	}

	if(op->m_bIF)
	{
		strTemp="I(A)";
		cList.InsertColumn(iN,strTemp);
		cList.SetColumnWidth(iN,50);
		iN++;

		m_failFlagData.AddListPara(TD_IF);
	}
	if(op->m_bVF)
	{
		strTemp="U(V)";
		cList.InsertColumn(iN,strTemp);
		cList.SetColumnWidth(iN,50);
		iN++;

		m_failFlagData.AddListPara(TD_VF);
	}
	if(op->m_bP)
	{
		strTemp="P(W)";
		cList.InsertColumn(iN,strTemp);
		cList.SetColumnWidth(iN,50);
		iN++;
		m_failFlagData.AddListPara(TD_P);

		strTemp="PF";
		cList.InsertColumn(iN,strTemp);
		cList.SetColumnWidth(iN,50);
		iN++;

		m_failFlagData.AddListPara(CFailFlagData::NONE_DATA);
	}
	if(op->m_bPhoEff)
	{
		g_bHavePhoEff = TRUE;
		if(g_bEnglish)
		{
			strTemp = "Fmol(umol/s)";
			if(m_iPhType == PH_E)
				strTemp = "Fmol(umol/m2/s)";
		}
		else
		{
			strTemp = "光量子数(umol/s)";
			if(m_iPhType == PH_E)
				strTemp = "光量子数(umol/m2/s)";
		}
		cList.InsertColumn(iN,strTemp);
		cList.SetColumnWidth(iN,80);
		iN++;
		m_failFlagData.AddListPara(CFailFlagData::NONE_DATA);
		
		if(g_bEnglish)
		{
			strTemp="Fluorescence and blue light ratio";
		}
		else
		{
			strTemp="荧光蓝光比";
		}
		cList.InsertColumn(iN,strTemp);
		cList.SetColumnWidth(iN,80);
		iN++;
		m_failFlagData.AddListPara(CFailFlagData::NONE_DATA);
		
		if(g_bEnglish)
		{
			strTemp="Fluorescent efficiency";
		}
		else
		{
			strTemp="荧光效能";
		}
		cList.InsertColumn(iN,strTemp);
		cList.SetColumnWidth(iN,80);
		iN++;
		m_failFlagData.AddListPara(CFailFlagData::NONE_DATA);

	}
	else
	{
		g_bHavePhoEff = FALSE;
	}

	if(op->m_bColorCorrectStr)
	{
		if(g_bEnglish)
			strTemp="Color Correct Info.";
		else
			strTemp="色校正选择";
		cList.InsertColumn(iN,strTemp);
		cList.SetColumnWidth(iN,120);
		iN++;
		m_failFlagData.AddListPara(CFailFlagData::NONE_DATA);	
	}

	g_bError.RemoveAll();
	int NN=m_listData.GetSize();
	for(int i=0;i<NN;i++)
	{
		g_bInsert=TRUE;
		if(i==NN-1)
			g_bInsert=FALSE;

		LIST_Insert(cList,i);
	}
	g_bInsert=FALSE;
	cList.ShowWindow(TRUE);
}

void CLED300ListData::LIST_Insert(CListCtrl &cList, int iSele)
{
	CLED300Data *data=m_listData[iSele];
	COPSetupData *op=&m_opData;

	CString strRe="";

	int iN=0;

	CString strTemp;
	strTemp.Format(" %04d",iSele+1);
	cList.InsertItem(iSele,strTemp,5);
	iN++;
	
	if(g_bAllSele)
		cList.SetCheck(iSele);

	if(op->m_bNote)
	{
		strTemp=data->m_spData.m_strNumber;
		cList.SetItemText(iSele,iN,strTemp);
		iN++;
	}
	if(op->m_bLevel)
	{
		COLORREF color;
		BOOL bErr=FALSE;
		strTemp=GetLevel(iSele, color);
		int iLength=strTemp.GetLength();
		for(int i=0;i<iLength;i++)
		{
			if(strTemp.GetAt(i)=='*'||strTemp.GetAt(i)=='-'||strTemp=="OUT")
			{
				bErr=TRUE;
				break;
			}
		}
		if(bErr)
			strTemp=strTemp+"[Fail]";

		//当前行失败信息
		g_bCurErr=bErr;

		g_bError.Add(bErr);
		cList.SetItemText(iSele,iN,strTemp);
		iN++;
	}
	if(op->m_bWhite)
	{
		strTemp=GetWhite(iSele);
		cList.SetItemText(iSele,iN,strTemp);
		iN++;
	}
	if(op->m_bPH)
	{
		if(data->m_spData.m_bTestPH&&data->m_spData.m_bHaveColorPara)
			strTemp.Format(" %s",g_SPEC.sFormat(data->m_spData.m_fPH,5));
		else
			strTemp="-";
		cList.SetItemText(iSele,iN,strTemp);
		iN++;

		if(op->m_bPhSP)
		{
			float fPh_, fSP;
			BOOL bHave = data->m_spData.CalcPh_(fPh_, fSP);
			if(bHave)
				strTemp.Format("%.5g", fPh_);
			else
				strTemp = "";
			cList.SetItemText(iSele,iN,strTemp);
			iN++;

			if(bHave)
				strTemp.Format("%.5g", fSP);
			else
				strTemp = "";
			cList.SetItemText(iSele,iN,strTemp);
			iN++;
		}

		if(data->m_spData.m_iLamp==0)
		{
			if(m_iPhType==PH_F)
			{
				if(data->m_spData.m_bTestPH)
					strTemp.Format(" %s",g_SPEC.sFormat(data->m_spData.m_fPh_e*1000,5));
				else
					strTemp="-";
				cList.SetItemText(iSele,iN,strTemp);
				iN++;
			}
			if(m_iPhType==PH_E)
			{
				if(data->m_spData.m_bTestPH)
					strTemp.Format(" %s",g_SPEC.sFormat(data->m_spData.m_fPh_e,5));
				else
					strTemp="-";
				cList.SetItemText(iSele,iN,strTemp);
				iN++;
			}
			if(op->m_bPH&&(m_iPhType==PH_I||m_iPhType==PH_Ie))
			{
				CString sStr;
				if(data->m_spData.m_fDistance==0.316f)
					sStr="(CIE A)";
				else if(data->m_spData.m_fDistance==0.100f)
					sStr="(CIE B)";
				else
					sStr.Format("(%.3f m)",data->m_spData.m_fDistance);

				if(data->m_spData.m_bTestPH)
					strTemp.Format(" %s",g_SPEC.sFormat(data->m_spData.m_fPh_e*1000,5));
				else
					strTemp="-";
				cList.SetItemText(iSele,iN,strTemp+sStr);
				iN++;

			}
			if(m_iPhType==PH_F)
			{
				float fEff;
				if(data->m_spData.m_bTestF&&data->m_spData.m_bTestPH&&data->m_spData.m_bHaveColorPara)
				{
					if(data->m_spData.m_fPow<=0)
						fEff=0;
					else
						fEff=data->m_spData.m_fPH/(data->m_spData.m_fPow);
					strTemp.Format("%5.2f",fEff);
				}
				else
					strTemp="-";
				cList.SetItemText(iSele,iN,strTemp);
				iN++;
			}
		}
	}
	if(op->m_bXY)
	{
		if(data->m_spData.m_bHaveData&&data->m_spData.m_bHaveColorPara)
			strTemp.Format("%.4f %.4f",data->m_spData.m_x,data->m_spData.m_y);
		else
			strTemp="-";
		cList.SetItemText(iSele,iN,strTemp);
		iN++;
	}
	if(op->m_bUV)
	{
		if(data->m_spData.m_bHaveData&&data->m_spData.m_bHaveColorPara)
			strTemp.Format("%.4f %.4f",data->m_spData.m_u,data->m_spData.m_v);
		else
			strTemp="-";
		cList.SetItemText(iSele,iN,strTemp);
		iN++;
	}
	if(op->m_bTc)
	{
		if(data->m_spData.m_bHaveData&&data->m_spData.m_bHaveColorPara)
			strTemp.Format("%6.0f",data->m_spData.m_fCCT);
		else
			strTemp="-";
		cList.SetItemText(iSele,iN,strTemp);
		iN++;
	}
	if(op->m_bdC)
	{
		if(data->m_spData.m_bHaveData&&data->m_spData.m_bHaveColorPara)
			strTemp.Format("%.4f",data->m_spData.m_fdc);
		else
			strTemp="-";
		cList.SetItemText(iSele,iN,strTemp);
		iN++;
	}
	if(op->m_bIp)
	{
		if(data->m_spData.m_bHaveData)
		{
			strTemp.Format("%5.0f(%3.0f%%)",data->m_spData.m_fIp,data->m_spData.m_fIp*100.0f/(data->m_spData.m_nADW-1));
			if(data->m_spData.m_fIp/(data->m_spData.m_nADW-1)<T_L)
				strTemp=strTemp+"*";
			else
				strTemp=strTemp+" ";
		}
		else
			strTemp="-";
		cList.SetItemText(iSele,iN,strTemp);
		iN++;
	}
	if(op->m_bLd)
	{
		if(data->m_spData.m_bHaveData&&data->m_spData.m_bHaveColorPara)
			strTemp.Format("%5.1f",data->m_spData.m_fMainlambda);
		else
			strTemp="-";
		cList.SetItemText(iSele,iN,strTemp);
		iN++;
	}
	if(op->m_bPur)
	{
		if(data->m_spData.m_bHaveData&&data->m_spData.m_bHaveColorPara)
			strTemp.Format("%5.1f",data->m_spData.m_fPurity);
		else
			strTemp="-";
		cList.SetItemText(iSele,iN,strTemp);
		iN++;
	}
	if(op->m_bLp)
	{
		if(data->m_spData.m_bHaveData)
			strTemp.Format("%5.1f",data->m_spData.m_fMaxlambda);
		else
			strTemp="-";
		cList.SetItemText(iSele,iN,strTemp);
		iN++;
	}
	if(op->m_bHW)
	{
		if(data->m_spData.m_bHaveData)
			strTemp.Format("%5.1f",data->m_spData.m_fHalflambda);
		else
			strTemp="-";
		cList.SetItemText(iSele,iN,strTemp);
		iN++;
	}
	if(op->m_bRR)
	{
		if(data->m_spData.m_bHaveData&&data->m_spData.m_bHaveColorPara)
			strTemp.Format("%5.1f",data->m_spData.m_fRedRatio);
		else
			strTemp="-";
		cList.SetItemText(iSele,iN,strTemp);
		iN++;
	}
	if(op->m_bRa)
	{
		if(data->m_spData.m_bHaveData&&data->m_spData.m_bHaveColorPara)
			strTemp.Format("%5.1f",data->m_spData.m_fRa);
		else
			strTemp="-";
		cList.SetItemText(iSele,iN,strTemp);
		iN++;

		if(g_bHaveCRI)
		{
			float fCRI=0;
			for(int i=0;i<14;i++)
			{
				fCRI=fCRI+data->m_spData.m_fRi[i];
			}
			fCRI=fCRI/14;

			if(data->m_spData.m_bHaveData&&data->m_spData.m_bHaveColorPara)
				strTemp.Format("%5.1f",fCRI);
			else
				strTemp="-";
			cList.SetItemText(iSele,iN,strTemp);
			iN++;
		}
	}
	if(op->m_bRO)
	{
		for(int i = 0; i < 15; i++)
		{
			if(data->m_spData.m_bHaveData&&data->m_spData.m_bHaveColorPara)
				strTemp.Format("%.0f",data->m_spData.m_fRi[i]);
			else
				strTemp="-";
			cList.SetItemText(iSele,iN,strTemp);
			iN++;
		}
	}

	if(1)
	{
		if(data->m_spData.m_bHaveData&&data->m_spData.m_bHaveColorPara)
			strTemp.Format("%5.1f",data->m_spData.GetSDCM(m_opData.m_iSeleTc));
		else
			strTemp="-";
		cList.SetItemText(iSele,iN,strTemp);
		iN++;
	}
	if(0)//op->m_bZW)
	{
		if(data->m_spData.m_bHaveData&&data->m_spData.m_fSpect1<300.0f)
			strTemp=g_SPEC.sFormat(data->m_spData.m_fKuv,4);
		else
			strTemp="-";
		cList.SetItemText(iSele,iN,strTemp);

		iN++;
		if(data->m_spData.m_bHaveData&&data->m_spData.m_fSpect1<300.0f)
			strTemp=g_SPEC.sFormat(data->m_spData.m_fK1,4);
		else
			strTemp="-";
		cList.SetItemText(iSele,iN,strTemp);
		iN++;

		if(data->m_spData.m_bHaveData&&data->m_spData.m_fSpect1<300.0f)
			strTemp=g_SPEC.sFormat(data->m_spData.m_fK2,4);
		else
			strTemp="-";
		cList.SetItemText(iSele,iN,strTemp);
		iN++;
	}
	if(op->m_bIF)
	{
		if(data->m_spData.m_bTestF)
			strTemp=g_SPEC.sFormat(data->m_spData.m_fIF,4);
		else
			strTemp="-";
		cList.SetItemText(iSele,iN,strTemp);
		iN++;
	}
	if(op->m_bVF)
	{
		if(data->m_spData.m_bTestF)
			strTemp=g_SPEC.sFormat(data->m_spData.m_fVF,4);
		else
			strTemp="-";
		cList.SetItemText(iSele,iN,strTemp);
		iN++;
	}
	if(op->m_bP)
	{
		if(data->m_spData.m_bTestF)
		{
			strTemp=g_SPEC.sFormat(data->m_spData.m_fPow,4);
		}
		else
		{
			strTemp="-";
		}
		cList.SetItemText(iSele,iN,strTemp);
		iN++;

		if(data->m_spData.m_bTestF)
		{
			strTemp=g_SPEC.sFormat(data->m_spData.m_fPF,4);
		}
		else
		{
			strTemp="-";
		}
		cList.SetItemText(iSele,iN,strTemp);
		iN++;
	}
	if(op->m_bPhoEff)
	{
		float fMol  = 0;
		float fEff1 = 0;
		float fEff2 = 0;

		BOOL bPho = data->m_spData.CalcPhoEff(fMol,fEff1,fEff2, m_iPhType);
		
		strTemp.Format("%.5g",fMol);
		if(bPho == FALSE)
			strTemp = "";
		cList.SetItemText(iSele,iN,strTemp);
		iN++;
		
		strTemp = g_SPEC.sFormat(fEff1,4);
		if(bPho == FALSE)
			strTemp = "";
		cList.SetItemText(iSele,iN,strTemp);
		iN++;
		
		strTemp = g_SPEC.sFormat(fEff2,4);
		if(bPho == FALSE)
			strTemp = "";
		cList.SetItemText(iSele,iN,strTemp);
		iN++;
	}

	if(op->m_bColorCorrectStr)
	{
		strTemp = data->m_spData.m_strColorCorrectStr;
		cList.SetItemText(iSele,iN,strTemp);
		iN++;
	}
}

BOOL CLED300ListData::Open(CString strPathName)
{
	CFile oFile;
	if(!oFile.Open(strPathName,CFile::modeRead))
		return FALSE;

    CArchive ar(&oFile,CArchive::load);
	Serialize(ar);
	ar.Close();
	oFile.Close();
	return TRUE;
}

BOOL CLED300ListData::Save(CString strPathName)
{
	CFile sFile;
	if(!sFile.Open(strPathName,CFile::modeCreate|CFile::modeReadWrite))
		return FALSE;
	CArchive ar(&sFile,CArchive::store);
	Serialize(ar);
	ar.Close();
	sFile.Close();
	return TRUE;
}

void CLED300ListData::DoAllTestInfo()
{
	if(m_listData.GetSize()<=0)
		return;

	for(int i=1;i<m_listData.GetSize();i++)
	{
		m_listData.GetAt(i)->m_spData.m_strModel  = m_listData.GetAt(0)->m_spData.m_strModel;
		m_listData.GetAt(i)->m_spData.m_strNumber = m_listData.GetAt(0)->m_spData.m_strNumber;
		m_listData.GetAt(i)->m_spData.m_strFactory= m_listData.GetAt(0)->m_spData.m_strFactory;
		m_listData.GetAt(i)->m_spData.m_strT      = m_listData.GetAt(0)->m_spData.m_strT;
		m_listData.GetAt(i)->m_spData.m_strH      = m_listData.GetAt(0)->m_spData.m_strH;
		m_listData.GetAt(i)->m_spData.m_strTester = m_listData.GetAt(0)->m_spData.m_strTester;
		m_listData.GetAt(i)->m_spData.m_strDate   = m_listData.GetAt(0)->m_spData.m_strDate;
		m_listData.GetAt(i)->m_spData.m_strRemark = m_listData.GetAt(0)->m_spData.m_strRemark;
	}
}

void CLED300ListData::Draw_LEDCurve(CDC *pDC, CRect mRect,int iPara,int iSele,BOOL bPrint)
{
	CFont *pOldFont;
	CFont Font1Landscape,Font1Portrait;
	if(!bPrint)
	{
		int iTemp;
		iTemp=mRect.Height()/20;
		if(iTemp<16)
			iTemp=16;
		if(iTemp>32)
			iTemp=32;
		Font1Landscape.CreateFont(iTemp,0,0,0,500,FALSE,FALSE,0,
			ANSI_CHARSET,OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
			DEFAULT_PITCH|FF_MODERN,"Courier New");  

		Font1Portrait.CreateFont(iTemp,0,900,-900,500,FALSE,FALSE,0,
			ANSI_CHARSET,OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
			DEFAULT_PITCH|FF_MODERN,"Courier New");  
	}
	else
	{
		Font1Landscape.CreateFont(mRect.Height()/15,0,0,0,600,FALSE,FALSE,0,
			ANSI_CHARSET,OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
			DEFAULT_PITCH|FF_MODERN,"Courier New");  

		Font1Portrait.CreateFont(mRect.Height()/15,0,900,-900,600,FALSE,FALSE,0,
			ANSI_CHARSET,OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
			DEFAULT_PITCH|FF_MODERN,"Courier New");  
	}
	CPen *pOldPen;
	CPen Pen1,Pen2,Pen3,PenC,PenS;
	if(!bPrint)
	{
		Pen1.CreatePen(PS_SOLID,2,RGB(255,255,255));
		Pen2.CreatePen(PS_SOLID,1,RGB(255,255,255));
		Pen3.CreatePen(PS_DOT,1,RGB(255,255,255));
		PenC.CreatePen(PS_SOLID,1,RGB(0,255,0));
		PenS.CreatePen(PS_SOLID,1,RGB(255,0,0));
	}
	else
	{
		Pen1.CreatePen(PS_SOLID,4,RGB(0,0,0));
		Pen2.CreatePen(PS_SOLID,2,RGB(0,0,0));
		Pen3.CreatePen(PS_SOLID,2,RGB(0,0,0));
		PenC.CreatePen(PS_SOLID,2,RGB(0,0,0));
		PenS.CreatePen(PS_SOLID,2,RGB(255,0,0));
	}

	pOldFont=pDC->SelectObject(&Font1Landscape);
	pOldPen =pDC->SelectObject(&Pen1);
	pDC->SetBkMode(TRANSPARENT);

	int i;
	CString sTemp;
	CRect drawRect;

	int iFontH,iFontW;
	TEXTMETRIC  tm;

	pDC->GetTextMetrics(&tm);
	iFontH=tm.tmHeight+tm.tmExternalLeading;
	iFontW=tm.tmAveCharWidth;

	if(!bPrint)
	{
		drawRect.left=mRect.left+iFontW*7;
		drawRect.right=mRect.right-iFontW*2;
		drawRect.top=mRect.top+iFontH*2;
		drawRect.bottom=(int)(mRect.bottom-iFontH*2.5f);
	}
	else
	{
		drawRect.left=mRect.left+iFontW*7+1*iFontW;
		drawRect.right=mRect.right-iFontW*2-1*iFontW;
		drawRect.top=mRect.top+iFontH*2+1*iFontW;
		drawRect.bottom=(int)(mRect.bottom-iFontH*2.5f)-1*iFontW;
	}

	if(bPrint)
		pDC->Rectangle(mRect);

	pDC->MoveTo(drawRect.left,drawRect.top);
	pDC->LineTo(drawRect.left,drawRect.bottom);
	pDC->LineTo(drawRect.right,drawRect.bottom);

	if(!bPrint)
		pDC->SetTextColor(RGB(255,255,255));
	else
		pDC->SetTextColor(RGB(0,0,0));

	pDC->SelectObject(&Pen2);
	pDC->SetTextAlign(TA_CENTER);

	BOOL bAxis=FALSE;        //x - y 轴对换

	int iN=m_listData.GetSize();
	float fIF1,fIF2;
	if(iN<=0)
	{
		fIF1=0;
		fIF2=50;
	}
	else
	{
		fIF1=m_listData[0]->m_spData.m_fIF;
		fIF1=floorf(fIF1/10)*10.0f;  
		if(fIF1<=0)
			fIF1=0;
		fIF2=ceilf((m_listData[iN-1]->m_spData.m_fIF-fIF1-0.000001f)/10.0f)*10.0f;  //??-0.000001f
		if(fIF2==0)
			fIF2=10;
		fIF2=fIF1+fIF2;
	}

	float *pData=new float[iN];
	float fD1;
	float fD2;

	if(iN<=0)
	{
		fD1=0;
		fD2=1;
	}
	else
	{
		for(i=0;i<iN;i++)
		{
			if(iPara==PARA_VF)
			{
				pData[i]=m_listData[i]->m_spData.m_fVF;
				bAxis=TRUE;
			}
			if(iPara==PARA_P)
				pData[i]=m_listData[i]->m_spData.m_fPow;
			if(iPara==PARA_PH)
				pData[i]=m_listData[i]->m_spData.m_fPH;
			if(iPara==PARA_EFF)
			{
				if(m_listData[i]->m_spData.m_fPow<=0)
					pData[i]=0;
				else
					pData[i]=m_listData[i]->m_spData.m_fPH/(m_listData[i]->m_spData.m_fPow);
			}
			if(iPara==PARA_x)
				pData[i]=m_listData[i]->m_spData.m_x;
			if(iPara==PARA_y)
				pData[i]=m_listData[i]->m_spData.m_y;
			if(iPara==PARA_u)
				pData[i]=m_listData[i]->m_spData.m_u;
			if(iPara==PARA_v)
				pData[i]=m_listData[i]->m_spData.m_v;
			if(iPara==PARA_Tc)
				pData[i]=m_listData[i]->m_spData.m_fCCT;
			if(iPara==PARA_Ld)
				pData[i]=m_listData[i]->m_spData.m_fMainlambda;
			if(iPara==PARA_Pur)
				pData[i]=m_listData[i]->m_spData.m_fPurity;
			if(iPara==PARA_Lp)
				pData[i]=m_listData[i]->m_spData.m_fMaxlambda;
			if(iPara==PARA_HW)
				pData[i]=m_listData[i]->m_spData.m_fHalflambda;
			if(iPara==PARA_RR)
				pData[i]=m_listData[i]->m_spData.m_fRedRatio;
			if(iPara==PARA_Ra)
				pData[i]=m_listData[i]->m_spData.m_fRa;
		}

		fD1=pData[0];
		fD2=pData[0];
		for(i=1;i<iN;i++)
		{
			if(pData[i]<fD1)
				fD1=pData[i];
			if(pData[i]>fD2)
				fD2=pData[i];
		}

		if(fD2<=1)
			fD1=floorf(fD1/0.01f)*0.01f;
		else if(fD2<=10)
			fD1=floorf(fD1/1.0f)*1.0f;
		else if(fD2<=100)
			fD1=floorf(fD1/10.0f)*10.0f;
		else
			fD1=floorf(fD1/100.0f)*100.0f;

		if(fD1<=0)
			fD1=0;
		//fD1=0;

		if(fD2<=1)
			fD2=ceilf(fD2/0.01f)*0.01f;
		else if(fD2<=10)
			fD2=ceilf(fD2/1.0f)*1.0f;
		else if(fD2<=100)
			fD2=ceilf(fD2/10.0f)*10.0f;
		else
			fD2=ceilf(fD2/100.0f)*100.0f;

		if(fD2<=0)
			fD2=1;
	}

	if(!bAxis)
	{
		pDC->SetTextAlign(TA_CENTER);
		for(i=0;i<=10;i++)
		{
			sTemp.Format("%.0f",fIF1+(fIF2-fIF1)*i/10.0f);
			pDC->TextOut((int)(drawRect.left+drawRect.Width()*i/10.0f),drawRect.bottom+iFontH/4,sTemp);

			pDC->MoveTo((int)(drawRect.left+drawRect.Width()*i/10.0f),drawRect.bottom);
			pDC->LineTo((int)(drawRect.left+drawRect.Width()*i/10.0f),drawRect.bottom+iFontH/4);
		}
		if(g_bEnglish)
			pDC->TextOut(drawRect.right-6*iFontW,drawRect.bottom+iFontH*5/4,"I (A)");
		else
			pDC->TextOut(drawRect.right-6*iFontW,drawRect.bottom+iFontH*5/4,"电流I (A)");

		pDC->SetTextAlign(TA_RIGHT);
		int iXN;
		iXN=5;
		for(i=0;i<=iXN;i++)
		{
			sTemp.Format("%s",g_SPEC.sFormat(fD1+(fD2-fD1)*i/iXN,3));
			pDC->TextOut(drawRect.left-iFontW*3/4,(int)(drawRect.bottom-drawRect.Height()*i/iXN-iFontH/2),sTemp);

			pDC->MoveTo(drawRect.left,(int)(drawRect.bottom-drawRect.Height()*i/iXN));
			pDC->LineTo(drawRect.left-iFontW/2,(int)(drawRect.bottom-drawRect.Height()*i/iXN));
		}
		pDC->SetTextAlign(TA_CENTER);
//		pDC->TextOut((int)(drawRect.left),(int)(drawRect.top-iFontH*1.5f),CSpectData::DATA_Name(iPara,m_iPhType));
		pDC->SelectObject(&Font1Landscape);
	}
	else
	{
		pDC->SetTextAlign(TA_RIGHT);
		for(i=0;i<=10;i++)
		{
			sTemp.Format("%.0f",fIF1+(fIF2-fIF1)*i/10.0f);
			pDC->TextOut(drawRect.left-iFontW*3/4,(int)(drawRect.bottom-drawRect.Height()*i/10.0f-iFontH/2),sTemp);

			pDC->MoveTo(drawRect.left,(int)(drawRect.bottom-drawRect.Height()*i/10.0f));
			pDC->LineTo(drawRect.left-iFontW/2,(int)(drawRect.bottom-drawRect.Height()*i/10.0f));
		}
		pDC->SetTextAlign(TA_CENTER);
		if(g_bEnglish)
			pDC->TextOut((int)(drawRect.left),(int)(drawRect.top-iFontH*1.5f),"I (A)");
		else
			pDC->TextOut((int)(drawRect.left),(int)(drawRect.top-iFontH*1.5f),"电流I (A)");
		pDC->SelectObject(&Font1Landscape);

		pDC->SetTextAlign(TA_CENTER);
		int iXN;
		iXN=5;
		for(i=0;i<=iXN;i++)
		{
			sTemp.Format("%s",g_SPEC.sFormat(fD1+(fD2-fD1)*i/iXN,3));
			pDC->TextOut((int)(drawRect.left+drawRect.Width()*i/(iXN*1.0f)),drawRect.bottom+iFontH/4,sTemp);

			pDC->MoveTo((int)(drawRect.left+drawRect.Width()*i/(iXN*1.0f)),drawRect.bottom);
			pDC->LineTo((int)(drawRect.left+drawRect.Width()*i/(iXN*1.0f)),drawRect.bottom+iFontH/4);
		}

//		pDC->TextOut(drawRect.right-6*iFontW,drawRect.bottom+iFontH*5/4,CSpectData::DATA_Name(iPara,m_iPhType));
	}

	int x,y;
	pDC->SelectObject(&PenC);
	for(i=0;i<iN;i++)
	{
		if(!bAxis)
		{
			x=(int)(drawRect.left+drawRect.Width()*(m_listData[i]->m_spData.m_fIF-fIF1)/(fIF2-fIF1));
			y=(int)(drawRect.bottom-drawRect.Height()*(pData[i]-fD1)/(fD2-fD1));
		}
		else
		{
			x=(int)(drawRect.left+drawRect.Width()*(pData[i]-fD1)/(fD2-fD1));
			y=(int)(drawRect.bottom-drawRect.Height()*(m_listData[i]->m_spData.m_fIF-fIF1)/(fIF2-fIF1));
		}

		if(1)
		{
			if(i==0)
				pDC->MoveTo(x,y);
			else
				pDC->LineTo(x,y);
		}
		else
		{
			int MM=iFontH/4;
			pDC->MoveTo(x-MM,y-MM);
			pDC->LineTo(x+MM,y+MM);
			pDC->MoveTo(x+MM,y-MM);
			pDC->LineTo(x-MM,y+MM);
		}
	}
	pDC->SelectObject(&PenS);
	if(iSele>=0&&iSele<iN)
	{
		i=iSele;
		if(!bAxis)
		{
			x=(int)(drawRect.left+drawRect.Width()*(m_listData[i]->m_spData.m_fIF-fIF1)/(fIF2-fIF1));
			y=(int)(drawRect.bottom-drawRect.Height()*(pData[i]-fD1)/(fD2-fD1));
		}
		else
		{
			x=(int)(drawRect.left+drawRect.Width()*(pData[i]-fD1)/(fD2-fD1));
			y=(int)(drawRect.bottom-drawRect.Height()*(m_listData[i]->m_spData.m_fIF-fIF1)/(fIF2-fIF1));
		}
		if(1)
		{
			int MM=iFontH/4;
			pDC->MoveTo(x-MM,y-MM);
			pDC->LineTo(x+MM,y+MM);
			pDC->MoveTo(x+MM,y-MM);
			pDC->LineTo(x-MM,y+MM);
		}
	}

	delete []pData;
	pDC->SelectObject(pOldFont);
	pDC->SelectObject(pOldPen);
}

void CLED300ListData::printLEDCurve(CDC *pDC, CRect printRect, int iPara[],int iSele)
{
	CFont *pOldFont;
	CFont Font1;
	CFont Font2;
	CFont Font3;

	Font1.CreateFont(printRect.Height()/40,0,0,0,700,FALSE,FALSE,0,
		ANSI_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH|FF_MODERN,"Courier New");

	Font2.CreateFont(printRect.Height()/57,0,0,0,600,FALSE,FALSE,0,
		ANSI_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH|FF_MODERN,"Courier New");
	Font3.CreateFont(printRect.Height()/60,0,0,0,600,TRUE,FALSE,0,
		ANSI_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH|FF_MODERN,"Courier New");
	
	CPen  *pOldPen;
	CPen  Pen1;
	CPen  Pen2;
	CPen  Pen3;

	Pen1.CreatePen(PS_SOLID,1,RGB(255,255,0));
	Pen2.CreatePen(PS_SOLID,1,RGB(255,0,0));
	Pen3.CreatePen(PS_SOLID,1,RGB(255,255,255));

	pOldPen=pDC->SelectObject(&Pen1);
	pOldFont=pDC->SelectObject(&Font1);

	int Wn=printRect.Width()/40;
	int Hn=printRect.Height()/40;

	pDC->SetTextAlign(TA_CENTER);
	if(g_bEnglish)
		pDC->TextOut(printRect.left+printRect.Width()/2,printRect.top+4*Hn,"LED Curves Report");
	else
		pDC->TextOut(printRect.left+printRect.Width()/2,printRect.top+4*Hn,"LED 特 性 曲 线 测 试 报 告");

	const int iN=3;
	CRect drRect[iN];

	CRect tempRect;
	tempRect.left  = printRect.left+printRect.Width()/20;
	tempRect.right = printRect.right-printRect.Width()/20;
	tempRect.top   = printRect.top+8*Hn;
	tempRect.bottom= printRect.bottom-2*Hn;

	for(int i=0;i<iN;i++)
	{
		drRect[i].left  = tempRect.left;
		drRect[i].right = tempRect.right;
		drRect[i].top   = tempRect.top+(int)(tempRect.Height()*(i+0.02f)*1.0f/iN);
		drRect[i].bottom= drRect[i].top+(int)(tempRect.Height()*0.95f/iN);

		Draw_LEDCurve(pDC,drRect[i],iPara[i],iSele,TRUE);
	}

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldFont);
}

void CLED300ListData::GetList(int iPhType, BOOL bHaveSpect, int iList[], int &iN)
{
	iN=0;

	iList[iN]=PARA_VF;
	iN++;
	iList[iN]=PARA_P;
	iN++;
	iList[iN]=PARA_PH;
	iN++;
	if(iPhType==PH_F)
	{
		iList[iN]=PARA_EFF;
		iN++;
	}
	if(bHaveSpect)
	{
		iList[iN]=PARA_x;
		iN++;
		iList[iN]=PARA_y;
		iN++;
		iList[iN]=PARA_u;
		iN++;
		iList[iN]=PARA_v;
		iN++;
		iList[iN]=PARA_Tc;
		iN++;
		iList[iN]=PARA_Ld;
		iN++;
		iList[iN]=PARA_Pur;
		iN++;
		iList[iN]=PARA_Lp;
		iN++;
		iList[iN]=PARA_HW;
		iN++;
		iList[iN]=PARA_RR;
		iN++;
	}
}

CString CLED300ListData::GetLevel(int iCur, COLORREF &color)
{
	CString strTemp;
	if(g_iLEDClass_Type == 1)
		strTemp = m_newClassLimit.GetLevel(*m_listData[iCur],m_iPhType, color);
	else
		strTemp=m_levelLimit.GetLevel(*m_listData[iCur],m_iPhType);
	return strTemp;
}

CString CLED300ListData::GetWhite(int iCur)
{
	CString strTemp;
	if(m_listData[iCur]->m_spData.m_bHaveData&&m_listData[iCur]->m_spData.m_bHaveColorPara)
		strTemp=m_xyZone.IN_ZONE(m_listData[iCur]->m_spData.m_x,m_listData[iCur]->m_spData.m_y);
	else
		strTemp="";
	return strTemp;
}



BOOL CLED300ListData::Export_CSV_ALL(CString strPathName, float fInterval)
{
	FILE *fp;
    if((fp=fopen(strPathName,"wt"))==0)
	{
		if(g_bEnglish)
			AfxMessageBox("Save file fail!",MB_ICONINFORMATION);
		else
			AfxMessageBox("保存文件失败!",MB_ICONINFORMATION);
		return  FALSE;
	}
    else
	{    
		int i;
		CString strTemp;
		
		strTemp="WL(nm)";
		fprintf(fp,"\"%s\",",strTemp);
		
		for(i = 0; i < m_listData.GetSize(); i++)
		{
			strTemp.Format("Spectrum #%03d", i + 1);
			fprintf(fp,"\"%s\",",strTemp);

			strTemp.Format("Spectrum #%03d_ABS", i + 1);
			fprintf(fp,"\"%s\",",strTemp);
		}
		
		fprintf(fp,"\n");
		
		int NN = (int)(fInterval/m_listData[0]->m_spData.m_fInterval+0.5f);
		int iN = m_listData[0]->m_spData.m_fRelSpect.GetSize();
		iN = (iN - 1) / NN + 1;
		
		for(i = 0; i < iN; i++)
		{
			strTemp.Format("%.1f",m_listData[0]->m_spData.m_fSpect1 + fInterval * i);
			fprintf(fp,"\"%s\",",strTemp);
			
			for(int j = 0; j < m_listData.GetSize(); j++)
			{
				strTemp.Format("%.4f", m_listData[j]->m_spData.m_fRelSpect[i*NN]);
				fprintf(fp,"\"%s\",",strTemp);

				strTemp.Format("%.4g", m_listData[j]->m_spData.m_fRelSpect[i*NN] *  m_listData[j]->m_spData.m_fPlambda);
				fprintf(fp,"\"%s\",",strTemp);
			}
			
			fprintf(fp,"\n");
		}
		fclose(fp);
		return TRUE;
	}
}

void CLED300ListData::ReCalcLeve()
{
	static int iLineN = 0;
	static int iListNum = 0;

	if(iLineN !=  m_listData.GetSize()
		|| iListNum != m_failFlagData.GetListTypeNum() || m_failFlagData.m_bModifyLisType)
	{
		CString strTemp;
		COLORREF color;
		m_failFlagData.SetDataLineNum(m_listData.GetSize());
		
		for(int i = 0; i < m_listData.GetSize(); i++)
		{
			CNewLEDClass::m_iTempTypeNum = 0;
			strTemp = GetLevel(i, color);
			
			for(int j = 0; j < CNewLEDClass::m_iTempTypeNum; j++)
			{
				m_failFlagData.AddLineFailDataType(i, CNewLEDClass::m_iTempType[j]);
			}
		}	

		iLineN = m_listData.GetSize();
		iListNum = m_failFlagData.GetListTypeNum();
		m_failFlagData.m_bModifyLisType = FALSE;
	}
}
