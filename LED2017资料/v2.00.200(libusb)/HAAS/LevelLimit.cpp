// LevelLimit.cpp: implementation of the CLevelLimit class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MySpec.h"
#include "LevelLimit.h"
#include "DlgParaSele.h"
#include "Global_MySpec.h"

#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern CString g_strListLevel;

CLevelLimit::CLevelLimit()
{
	Init();
}

CLevelLimit::~CLevelLimit()
{

}

CLevelLimit& CLevelLimit::operator =(const CLevelLimit &levelData)
{
	Copy(levelData);
	return *this;
}

void CLevelLimit::Copy(const CLevelLimit &levelData)
{
	m_arraLevelLimit.RemoveAll();

	int i,iN;
	iN=levelData.m_arraLevelLimit.GetSize();
	for(i=0;i<iN;i++)
	{
		CLimitData *temp=new CLimitData();
		m_arraLevelLimit.Add(temp);
		m_arraLevelLimit[i]=levelData.m_arraLevelLimit[i];
	}
}

void CLevelLimit::Serialize(CArchive &ar)
{
	CString strVer;
	int i,iN;
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		strVer="LEVEL A";
		ar<<strVer;
		iN=m_arraLevelLimit.GetSize();
		ar<<iN;
		for(i=0;i<iN;i++)
			m_arraLevelLimit[i]->Serialize(ar);
	}
	else
	{
		// TODO: add loading code here
		ar>>strVer;
		if(strVer!="LEVEL A")
		{
			if(g_bEnglish)
				AfxMessageBox("Can not open file!\n"+strVer,NULL,MB_ICONSTOP);
			else
				AfxMessageBox("不能打开该类型文件!\n"+strVer,NULL,MB_ICONSTOP);
			return;
		}
		m_arraLevelLimit.RemoveAll();
		ar>>iN;
		for(i=0;i<iN;i++)
		{
			CLimitData *temp=new CLimitData();
			temp->Serialize(ar);
			m_arraLevelLimit.Add(temp);
		}
	}
}

void CLevelLimit::Init()
{
	m_arraLevelLimit.RemoveAll();
}

BOOL CLevelLimit::AddLimitPara()
{
	CArray<CString,CString> strName;
	CArray<int,int> iType;

	CLimitData limit;
	limit.GetName(strName,iType);

	int iN;
	iN=strName.GetSize();
	CDlgParaSele dlg;
	dlg.m_arraName.RemoveAll();
	for(int i=0;i<iN;i++)
		dlg.m_arraName.Add(strName[i]);

	if(dlg.DoModal()==IDCANCEL)
		return FALSE;

	CLimitData *temp=new CLimitData();

	temp->m_iDataType=iType[dlg.m_iName];

	m_arraLevelLimit.Add(temp);

	iN=m_arraLevelLimit.GetSize();
	BOOL bR;
	bR=EditLimitPara(iN-1);
	if(!bR)
		return FALSE;
	return TRUE;
}

BOOL CLevelLimit::EditLimitPara(int iSele)
{
	if(iSele==-1)
	{
		iSele=SelePara();
	}
	int iN=m_arraLevelLimit.GetSize();
	if(iSele>=0&&iSele<=(iN-1))
	{
		m_arraLevelLimit[iSele]->FastLevel();
		return TRUE;
	}
	return FALSE;
}

BOOL CLevelLimit::DelLimitPara(int iSele)
{
	if(iSele==-1)
	{
		iSele=SelePara();
	}
	int iN=m_arraLevelLimit.GetSize();
	if(iSele>=0&&iSele<=(iN-1))
	{
		m_arraLevelLimit.RemoveAt(iSele);
		return TRUE;
	}
	return FALSE;
}

int CLevelLimit::SelePara()
{
	int iN;
	iN=m_arraLevelLimit.GetSize();
	CDlgParaSele dlg;
	dlg.m_arraName.RemoveAll();
	for(int i=0;i<iN;i++)
		dlg.m_arraName.Add(m_arraLevelLimit[i]->GetTypeName());
	if(dlg.DoModal()==IDCANCEL)
		return -1;
	return dlg.m_iName;
}

CString CLevelLimit::GetLevel(CLED300Data &data,int iPhType)
{
	CString strLevel="";
	CString strTemp;
	int i,j,iN,iM;
	float fData;
	iN=m_arraLevelLimit.GetSize();
	for(i=0;i<iN;i++)
	{
		BOOL bInLevel=TRUE;  //是否满足这个等级
		iM=m_arraLevelLimit[i]->m_iN;
		int iDataType;
		iDataType=m_arraLevelLimit[i]->m_iDataType;
		strTemp="*";
		if(GetData(iDataType,data,iPhType,fData))
		{
			for(j=0;j<iM;j++)
			{
				if(fData>=m_arraLevelLimit[i]->m_fLevel1[j]&&fData<m_arraLevelLimit[i]->m_fLevel2[j])
				{
					strTemp.Format("%d",j);
					break;
				}
			}
		}
		strLevel=strLevel+strTemp;
	}
	return strLevel;
}

BOOL CLevelLimit::Save(CString sPathName)
{
	CFile sFile;
	if(!sFile.Open(sPathName,CFile::modeCreate|CFile::modeReadWrite))
		return FALSE;
	CArchive ar(&sFile,CArchive::store);

	Serialize(ar);
	ar.Close();
	sFile.Close();
	return TRUE;
}

BOOL CLevelLimit::Open(CString sPathName)
{
	CFile oFile;
	if(!oFile.Open(sPathName,CFile::modeRead))
	{
		g_strListLevel=g_strCurPath+"Class\\LED_LEVEL_1.sta";
//		return FALSE;
	}

	CArchive ar(&oFile,CArchive::load);
	
	Serialize(ar);
	ar.Close();
	oFile.Close();

	return TRUE;
}

BOOL CLevelLimit::GetData(int iDataType, CLED300Data &data,int iPhType,float &fData)
{
	if(iDataType==TD_VF)
	{
		if(data.m_spData.m_bTestF)
		{
			fData=data.m_spData.m_fVF;
			return TRUE;
		}
		else
			return FALSE;
	}
	if(iDataType==TD_IF)
	{
		if(data.m_spData.m_bTestF)
		{
			fData=data.m_spData.m_fIF;
			return TRUE;
		}
		else
			return FALSE;
	}
	if(iDataType==TD_P)
	{
		if(data.m_spData.m_bTestF)
		{
			fData=data.m_spData.m_fPow;
			return TRUE;
		}
		else
			return FALSE;
	}
	if(iDataType==TD_F)
	{
		if(data.m_spData.m_bTestPH&&iPhType==PH_F&&data.m_spData.m_bHaveColorPara)
		{
			fData=data.m_spData.m_fPH;
			return TRUE;
		}
		else
			return FALSE;
	}
	if(iDataType==TD_I)
	{
		if(data.m_spData.m_bTestPH&&iPhType==PH_I&&data.m_spData.m_bHaveColorPara)
		{
			fData=data.m_spData.m_fPH;
			return TRUE;
		}
		else
			return FALSE;
	}
	if(iDataType==TD_L)
	{
		if(data.m_spData.m_bTestPH&&iPhType==PH_L&&data.m_spData.m_bHaveColorPara)
		{
			fData=data.m_spData.m_fPH;
			return TRUE;
		}
		else
			return FALSE;
	}
	if(iDataType==TD_Fe)
	{
		if(data.m_spData.m_bTestPH&&iPhType==PH_Fe)
		{
			fData=data.m_spData.m_fPh_e * 1000;
			return TRUE;
		}
		else
		{
			if(data.m_spData.m_bHaveData&&iPhType==PH_F)
			{
				fData=data.m_spData.m_fPh_e * 1000;
				return TRUE;
			}
			return FALSE;
		}
	}
	if(iDataType==TD_Ie)
	{
		if(data.m_spData.m_bTestPH&&iPhType==PH_Ie)
		{
			fData=data.m_spData.m_fPh_e;
			return TRUE;
		}
		else
			return FALSE;
	}
	if(iDataType==TD_Le)
	{
		if(data.m_spData.m_bTestPH&&iPhType==PH_Le)
		{
			fData=data.m_spData.m_fPh_e;
			return TRUE;
		}
		else
			return FALSE;
	}

	if(iDataType==TD_X)
	{
		if(data.m_spData.m_bHaveData&&data.m_spData.m_bHaveColorPara)
		{
			fData=data.m_spData.m_x;
			return TRUE;
		}
		else
			return FALSE;
	}
	if(iDataType==TD_Y)
	{
		if(data.m_spData.m_bHaveData&&data.m_spData.m_bHaveColorPara)
		{
			fData=data.m_spData.m_y;
			return TRUE;
		}
		else
			return FALSE;
	}
	if(iDataType==TD_U)
	{
		if(data.m_spData.m_bHaveData&&data.m_spData.m_bHaveColorPara)
		{
			fData=data.m_spData.m_u;
			return TRUE;
		}
		else
			return FALSE;
	}
	if(iDataType==TD_V)
	{
		if(data.m_spData.m_bHaveData&&data.m_spData.m_bHaveColorPara)
		{
			fData=data.m_spData.m_v;
			return TRUE;
		}
		else
			return FALSE;
	}
	if(iDataType==TD_CCT)
	{
		if(data.m_spData.m_bHaveData&&data.m_spData.m_bHaveColorPara)
		{
			fData=data.m_spData.m_fCCT;
			return TRUE;
		}
		else
			return FALSE;
	}
	if(iDataType==TD_LD)
	{
		if(data.m_spData.m_bHaveData&&data.m_spData.m_bHaveColorPara)
		{
			fData=data.m_spData.m_fMainlambda;
			return TRUE;
		}
		else
			return FALSE;
	}
	if(iDataType==TD_LP)
	{
		if(data.m_spData.m_bHaveData)
		{
			fData=data.m_spData.m_fMaxlambda;
			return TRUE;
		}
		else
			return FALSE;
	}
	if(iDataType==TD_PUR)
	{
		if(data.m_spData.m_bHaveData)
		{
			fData=data.m_spData.m_fPurity;
			return TRUE;
		}
		else
			return FALSE;
	}
	if(iDataType==TD_RA)
	{
		if(data.m_spData.m_bHaveData&&data.m_spData.m_bHaveColorPara)
		{
			fData=data.m_spData.m_fRa;
			return TRUE;
		}
		else
			return FALSE;
	}
	if(iDataType==TD_EFF)
	{
		if(data.m_spData.m_bHaveData&&data.m_spData.m_bHaveColorPara)
		{
			if(data.m_spData.m_fPow > 0)
				fData = data.m_spData.m_fPh / data.m_spData.m_fPow;
			else
				fData = 0;
			return TRUE;
		}
		else
			return FALSE;
	}
	if(iDataType==TD_dC)
	{
		if(data.m_spData.m_bHaveData&&data.m_spData.m_bHaveColorPara)
		{
			fData=data.m_spData.m_fdc;
			return TRUE;
		}
		else
			return FALSE;
	}

	if(iDataType==TD_E)
	{
		if(data.m_spData.m_bTestPH&&iPhType==PH_E&&data.m_spData.m_bHaveColorPara)
		{
			fData=data.m_spData.m_fPH;
			return TRUE;
		}
		else
			return FALSE;
	}
	if(iDataType==TD_Ee)
	{
		if(data.m_spData.m_bTestPH&&iPhType==PH_E&&data.m_spData.m_bHaveColorPara)
		{
			fData=data.m_spData.m_fPh_e;
			return TRUE;
		}
		else
			return FALSE;
	}
	return FALSE;
}
