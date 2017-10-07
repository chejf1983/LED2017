// LED300Data.cpp: implementation of the CLED300Data class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MySpec.h"
#include "LED300Data.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLED300Data::CLED300Data()
{
	Init();
}

CLED300Data::~CLED300Data()
{

}

void CLED300Data::Copy(const CLED300Data &Data)
{
	m_spData  = Data.m_spData;
}

CLED300Data& CLED300Data::operator =(const CLED300Data &Data)
{
	Copy(Data);
	return *this;
}

void CLED300Data::Serialize(CArchive &ar)
{
	CString strVer;
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		strVer ="LED300_DATA_A";
		ar<<strVer;
		m_spData.Serialize(ar);
	}
	else
	{
		// TODO: add loading code here
		ar>>strVer;
		if(strVer!="LED300_DATA_A")
			return;
		m_spData.Serialize(ar);
	}
}

void CLED300Data::Init()
{
	m_spData.Init();
}

/* 用于特殊软件中的字串格式 */
CString CLED300Data::GetFormatData()
{
	CString strData;
	CString strTemp;

	strTemp.Format("%.5g\t", m_spData.m_fPow);
	strData += strTemp;

	strTemp.Format("%.5g\t", m_spData.m_fVF);
	strData += strTemp;

	strTemp.Format("%.5g\t", m_spData.m_fIF);
	strData += strTemp;

	strTemp.Format("-\t");
	strData += strTemp;

	strTemp.Format("-\t");
	strData += strTemp;

	strTemp.Format("-\t");
	strData += strTemp;
	
	strTemp.Format("-\t");
	strData += strTemp;

	strTemp.Format("-\t");
	strData += strTemp;
	
	strTemp.Format("-\t");
	strData += strTemp;

	strTemp.Format("%.0f\t", m_spData.m_fCCT);
	strData += strTemp;

	strTemp.Format("%.1f\t", m_spData.m_fRa);
	strData += strTemp;

	strTemp.Format("%.4f\t", m_spData.m_x);
	strData += strTemp;

	strTemp.Format("%.4f\t", m_spData.m_y);
	strData += strTemp;

	strTemp.Format("%.5g\t", m_spData.m_fPh);
	strData += strTemp;

	strTemp.Format("-\t", m_spData.m_fPh);
	strData += strTemp;

	if((m_spData.m_fPow) > 0)
		strTemp.Format("%.1f\t", m_spData.m_fPh / (m_spData.m_fPow));
	else
		strTemp.Format("-\t");
	strData += strTemp;

	strTemp.Format("\r\n");
	strData += strTemp;

	return strData;
}
