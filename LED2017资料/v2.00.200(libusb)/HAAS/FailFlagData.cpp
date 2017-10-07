// FailFlagData.cpp: implementation of the CFailFlagData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MySpec.h"
#include "FailFlagData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

const int CFailFlagData::NONE_DATA = -999;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFailFlagData::CFailFlagData()
{
	m_pFailData = 0;
	m_iLineNum = 0;
	m_bModifyLisType = TRUE;
}

CFailFlagData::~CFailFlagData()
{
	ClearAll();
}

void CFailFlagData::ClearAll()
{
	m_bModifyLisType = TRUE;
	m_iListDataType.RemoveAll();


	if(m_pFailData != 0)
	{
		for(int i = 0; i < m_iLineNum; i++)
			m_pFailData[i].RemoveAll();
	}

	delete [] m_pFailData;
	m_pFailData = 0;
	m_iLineNum = 0;
}

void CFailFlagData::AddListPara(int iType)
{
	m_bModifyLisType = TRUE;
	m_iListDataType.Add(iType);
}

void CFailFlagData::SetDataLineNum(int iDataLineNum)
{
	if(m_pFailData != 0)
	{
		for(int i = 0; i < m_iLineNum; i++)
			m_pFailData[i].RemoveAll();
	}

	delete [] m_pFailData;

	m_pFailData = 0;
	m_iLineNum = 0;


	m_iLineNum = iDataLineNum;
	if(iDataLineNum > 0)
		m_pFailData = new CArray<int, int> [iDataLineNum];
	else
		m_pFailData = 0;
	return;
}

void CFailFlagData::AddLineFailDataType(int iSeleLine, int iType)
{
	if(m_pFailData == 0)
		return;

	if(iSeleLine < 0 || iSeleLine >= m_iLineNum)
		return;

	m_pFailData[iSeleLine].Add(iType);
	return;
}

BOOL CFailFlagData::IsFail(int iSeleLine, int iSeleList) const
{
	if(m_pFailData == 0)
		return FALSE;

	if(iSeleLine < 0 || iSeleLine >= m_iLineNum)
		return FALSE;

	if(iSeleList < 0 || iSeleList >= m_iListDataType.GetSize())
		return FALSE;

	for(int i = 0; i < m_pFailData[iSeleLine].GetSize(); i++)
	{
		if(m_pFailData[iSeleLine][i] == m_iListDataType[iSeleList])
			return TRUE;
	}

	return FALSE;
}

int CFailFlagData::GetListTypeNum()
{
	return m_iListDataType.GetSize();
}
