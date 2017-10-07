// My_iniFile.h: interface for the CMy_iniFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MY_INIFILE_H__C65CF910_B001_4FBE_8F5F_02E0AB33D876__INCLUDED_)
#define AFX_MY_INIFILE_H__C65CF910_B001_4FBE_8F5F_02E0AB33D876__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMy_iniFile  
{
public:
	CMy_iniFile();
	CMy_iniFile(CString strPathName);
	virtual ~CMy_iniFile();

	void SetPathName(CString strPathName);
	CString GetPathName() const;

	BOOL WriteString(CString strSec, CString strKey, CString strValue);
	BOOL WriteString(CString strSec, CString strKey, float fValue);
	BOOL WriteString(CString strSec, CString strKey, int iValue);

	CString ReadString(CString strSec, CString strKey, CString strDefValue);
	float ReadString(CString strSec, CString strKey, float fDefValue);
	int ReadString(CString strSec, CString strKey, int iDefValue);

private:
	CString m_strPathName;
};

#endif // !defined(AFX_MY_INIFILE_H__C65CF910_B001_4FBE_8F5F_02E0AB33D876__INCLUDED_)
