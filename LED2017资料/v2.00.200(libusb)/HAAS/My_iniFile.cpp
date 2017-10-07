// My_iniFile.cpp: implementation of the CMy_iniFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "My_iniFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMy_iniFile::CMy_iniFile()
{
	m_strPathName = "";
}

CMy_iniFile::CMy_iniFile(CString strPathName)
{
	m_strPathName = strPathName;
}

CMy_iniFile::~CMy_iniFile()
{

}

void CMy_iniFile::SetPathName(CString strPathName)
{
	m_strPathName = strPathName;
}

BOOL CMy_iniFile::WriteString(CString strSec, CString strKey, CString strValue)
{
	TCHAR *pName = 0;
	if(m_strPathName != _T(""))
		pName = m_strPathName.GetBuffer(256);
	return ::WritePrivateProfileString(strSec.GetBuffer(256), strKey.GetBuffer(256), strValue.GetBuffer(256), pName);
}

BOOL CMy_iniFile::WriteString(CString strSec, CString strKey, float fValue)
{
	CString strValue;
	strValue.Format(_T("%g"), fValue);
	return WriteString(strSec, strKey, strValue);
}

BOOL CMy_iniFile::WriteString(CString strSec, CString strKey, int iValue)
{
	CString strValue;
	strValue.Format(_T("%d"), iValue);
	return WriteString(strSec, strKey, strValue);
}

CString CMy_iniFile::ReadString(CString strSec, CString strKey, CString strDefValue)
{
	CString strValue;
	TCHAR *pName = 0;
	if(m_strPathName != _T(""))
		pName = m_strPathName.GetBuffer(256);

	::GetPrivateProfileString(strSec.GetBuffer(256), strKey.GetBuffer(256), 
		strDefValue.GetBuffer(256), strValue.GetBuffer(256), 256, pName);
	strValue.ReleaseBuffer();
	return strValue; 
}

float CMy_iniFile::ReadString(CString strSec, CString strKey, float fDefValue)
{	
	CString strDefValue;
	strDefValue.Format("%g", fDefValue);

	CString strValue = ReadString(strSec, strKey, strDefValue);	
	float fValue = (float)atof(strValue);
	return fValue; 
}

int CMy_iniFile::ReadString(CString strSec, CString strKey, int iDefValue)
{
	CString strDefValue;
	strDefValue.Format("%d", iDefValue);
	
	CString strValue = ReadString(strSec, strKey, strDefValue);	
	int iValue = (int)atoi(strValue);
	return iValue; 

}

CString CMy_iniFile::GetPathName() const
{
	return m_strPathName;
}
