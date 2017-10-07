// LimitData.cpp: implementation of the CLimitData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MySpec.h"
#include "LimitData.h"
#include "DlgFastLevel.h"
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern BOOL g_bEnglish;

CLimitData::CLimitData()
{
	Init();
}

CLimitData::~CLimitData()
{
}

void CLimitData::Init()
{
	m_iDataType = TD_VF;

	m_iN      = 1;
	for(int i=0;i<10;i++)
	{
		m_fLevel1[i]=0;
		m_fLevel2[i]=0;
	}
}

CLimitData& CLimitData::operator =(const CLimitData &limitData)
{
	Copy(limitData);
	return *this;
}

void CLimitData::Copy(const CLimitData &limitData)
{
	m_iDataType = limitData.m_iDataType;

	m_iN        = limitData.m_iN;

	for(int i=0;i<m_iN;i++)
	{
		m_fLevel1[i]=limitData.m_fLevel1[i];
		m_fLevel2[i]=limitData.m_fLevel2[i];
	}
}

void CLimitData::Serialize(CArchive &ar)
{
	CString strVer;
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		strVer="LIMIT A";
		ar<<strVer;
		ar<<m_iDataType;

		ar<<m_iN;

		for(int i=0;i<m_iN;i++)
		{
			ar<<m_fLevel1[i];
			ar<<m_fLevel2[i];
		}
	}
	else
	{
		// TODO: add loading code here
		ar>>strVer;
		if(strVer!="LIMIT A")
			return;
		ar>>m_iDataType;

		ar>>m_iN;
		for(int i=0;i<m_iN;i++)
		{
			ar>>m_fLevel1[i];
			ar>>m_fLevel2[i];
		}
	}
}

CString CLimitData::GetTypeName()
{
	CString strTemp="";
	if(m_iDataType==TD_VF)
	{
		strTemp="U(V)";
	}
	else if(m_iDataType==TD_IF)
	{
		strTemp="I(A)";
	}
	else if(m_iDataType==TD_P)
	{
		strTemp="P(W)";
	}
	else if(m_iDataType==TD_VR)
	{
		strTemp="VR(V)";
	}
	else if(m_iDataType==TD_IR)
	{
		strTemp="IR(uA)";
	}
	else if(m_iDataType==TD_F)
	{
		if(g_bEnglish)
			strTemp="Flux(lm)";
		else
			strTemp="¦µ(lm)";
	}
	else if(m_iDataType==TD_I)
	{
		strTemp="I(cd)";
	}
	else if(m_iDataType==TD_L)
	{
		strTemp="L(cd/m2)";
	}
	else if(m_iDataType==TD_Fe)
	{
		if(g_bEnglish)
			strTemp="Fe(W)";
		else
			strTemp="¦µe(W)";
	}
	else if(m_iDataType==TD_Ie)
	{
		strTemp="Ie(mW/Sr)";
	}
	else if(m_iDataType==TD_Le)
	{
		strTemp="Le(W/m2/Sr)";
	}
	else if(m_iDataType==TD_X)
	{
		strTemp="x";
	}
	else if(m_iDataType==TD_Y)
	{
		strTemp="y";
	}
	else if(m_iDataType==TD_U)
	{
		strTemp="u'";
	}
	else if(m_iDataType==TD_V)
	{
		strTemp="v'";
	}
	else if(m_iDataType==TD_CCT)
	{
		strTemp="CCT(K)";
	}
	else if(m_iDataType==TD_LD)
	{
		if(g_bEnglish)
			strTemp="Ld(nm)";
		else
			strTemp="¦Ëd(nm)";
	}
	else if(m_iDataType==TD_LP)
	{
		if(g_bEnglish)
			strTemp="Lp(nm)";
		else
			strTemp="¦Ëp(nm)";
	}
	else if(m_iDataType==TD_PUR)
	{
		strTemp="PUR(%)";
	}
	else if(m_iDataType==TD_RA)
	{
		strTemp="Ra";
	}
	else if(m_iDataType==TD_EFF)
	{
		strTemp="Eff(lm/2)";
	}
	else if(m_iDataType==TD_dC)
	{
		strTemp="dC";
	}
	else if(m_iDataType==TD_E)
	{
		strTemp="E(lx)";
	}
	else if(m_iDataType==TD_Ee)
	{
		strTemp="Ee(W/m2)";
	}
	else
		strTemp="";

	return strTemp;
}

void CLimitData::FastLevel()
{
	int i;
	CDlgFastLevel dlg;

	dlg.m_strName = GetTypeName();
	dlg.m_iN      = m_iN;
	for(i=0;i<m_iN;i++)
	{
		dlg.m_fLevel1[i]=m_fLevel1[i];
		dlg.m_fLevel2[i]=m_fLevel2[i];
	}

	if(dlg.DoModal()==IDCANCEL)
		return;
	m_iN      = dlg.m_iN;

	for(i=0;i<m_iN;i++)
	{
		m_fLevel1[i]=dlg.m_fLevel1[i];
		m_fLevel2[i]=dlg.m_fLevel2[i];
	}
}

void CLimitData::GetName(CArray<CString,CString> &strName,CArray<int,int> &iType)
{
	strName.RemoveAll();
	iType.RemoveAll();

	strName.Add("U(V)");
	iType.Add(TD_VF);

	strName.Add("I(A)");
	iType.Add(TD_IF);

	strName.Add("P(W)");
	iType.Add(TD_P);

	strName.Add("VR(V)");
	iType.Add(TD_VR);

	strName.Add("IR(uA)");
	iType.Add(TD_IR);

	if(g_bEnglish)
		strName.Add("Flux(lm)");
	else
		strName.Add("¦µ(lm)");
	iType.Add(TD_F);

	strName.Add("I(cd)");
	iType.Add(TD_I);

	strName.Add("L(cd/m2)");
	iType.Add(TD_L);

	if(g_bEnglish)
		strName.Add("Fe(mW)");
	else
		strName.Add("¦µe(mW)");
	iType.Add(TD_Fe);

	strName.Add("Ie(mW/Sr)");
	iType.Add(TD_Ie);

	strName.Add("Le(W/m2/Sr)");
	iType.Add(TD_Le);

	strName.Add("x");
	iType.Add(TD_X);

	strName.Add("y");
	iType.Add(TD_Y);

	strName.Add("u'");
	iType.Add(TD_U);

	strName.Add("v'");
	iType.Add(TD_V);

	strName.Add("CCT(K)");
	iType.Add(TD_CCT);

	if(g_bEnglish)
		strName.Add("Ld(nm)");
	else
		strName.Add("¦Ëd(nm)");
	iType.Add(TD_LD);

	if(g_bEnglish)
		strName.Add("Lp(nm)");
	else
		strName.Add("¦Ëp(nm)");
	iType.Add(TD_LP);

	strName.Add("PUR(%)");
	iType.Add(TD_PUR);

	strName.Add("Ra");
	iType.Add(TD_RA);

	strName.Add("Eff(lm/W)");
	iType.Add(TD_EFF);

	strName.Add("dC");
	iType.Add(TD_dC);

	strName.Add("E(lx)");
	iType.Add(TD_E);

	strName.Add("Ee(W/m2)");
	iType.Add(TD_Ee);

}

CString CLimitData::Type2NameStr(int iDataType)
{
	CString strTemp="";
	if(iDataType==TD_VF)
	{
		strTemp="U(V)";
	}
	else if(iDataType==TD_IF)
	{
		strTemp="I(A)";
	}
	else if(iDataType==TD_P)
	{
		strTemp="P(W)";
	}
	else if(iDataType==TD_VR)
	{
		strTemp="VR(V)";
	}
	else if(iDataType==TD_IR)
	{
		strTemp="IR(uA)";
	}
	else if(iDataType==TD_F)
	{
		if(g_bEnglish)
			strTemp="Flux(lm)";
		else
			strTemp="¦µ(lm)";
	}
	else if(iDataType==TD_I)
	{
		strTemp="I(cd)";
	}
	else if(iDataType==TD_L)
	{
		strTemp="L(cd/m2)";
	}
	else if(iDataType==TD_Fe)
	{
		if(g_bEnglish)
			strTemp="Fe(W)";
		else
			strTemp="¦µe(W)";
	}
	else if(iDataType==TD_Ie)
	{
		strTemp="Ie(mW/Sr)";
	}
	else if(iDataType==TD_Le)
	{
		strTemp="Le(W/m2/Sr)";
	}
	else if(iDataType==TD_X)
	{
		strTemp="x";
	}
	else if(iDataType==TD_Y)
	{
		strTemp="y";
	}
	else if(iDataType==TD_U)
	{
		strTemp="u'";
	}
	else if(iDataType==TD_V)
	{
		strTemp="v'";
	}
	else if(iDataType==TD_CCT)
	{
		strTemp="CCT(K)";
	}
	else if(iDataType==TD_LD)
	{
		if(g_bEnglish)
			strTemp="Ld(nm)";
		else
			strTemp="¦Ëd(nm)";
	}
	else if(iDataType==TD_LP)
	{
		if(g_bEnglish)
			strTemp="Lp(nm)";
		else
			strTemp="¦Ëp(nm)";
	}
	else if(iDataType==TD_PUR)
	{
		strTemp="PUR(%)";
	}
	else if(iDataType==TD_RA)
	{
		strTemp="Ra";
	}
	else if(iDataType==TD_EFF)
	{
		strTemp="Eff(lm/W)";
	}
	else if(iDataType==TD_dC)
	{
		strTemp="dC";
	}
	else if(iDataType==TD_E)
	{
		strTemp="E(lx)";
	}
	else if(iDataType==TD_Ee)
	{
		strTemp="Ee(W/m2)";
	}
	else
		strTemp="";

	return strTemp;
}
