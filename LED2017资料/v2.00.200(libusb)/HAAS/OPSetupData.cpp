// OPSetupData.cpp: implementation of the COPSetupData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MySpec.h"
#include "OPSetupData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern BOOL g_bPrintLogo;

COPSetupData::COPSetupData()
{
	m_bPhSP = FALSE;

	m_bdC = FALSE;
	m_bR1_15 = FALSE;
	m_bColorCorrectStr = FALSE;

	Init();
}

COPSetupData::~COPSetupData()
{

}

void COPSetupData::Serialize(CArchive &ar)
{
	CString strVer;
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		strVer = "OP_G";
		ar << strVer;

		ar << m_iShowCIE;
		ar << m_iSeleTc;
		ar << m_iSDCM1;
		ar << m_iSDCM2;

		ar << m_bNote;
		ar << m_bIF;
		ar << m_bP;
		ar << m_bVF;
		ar << m_bIp;
		ar << m_bPH;  
		ar << m_bXY;
		ar << m_bUV;
		ar << m_bTc;
		ar << m_bLd;
		ar << m_bPur;
		ar << m_bLp;
		ar << m_bHW;
		ar << m_bRR;
		ar << m_bRa;
		
		ar << m_bLevel;
		ar << m_bWhite;

		ar << m_fExportIntervalWL;
		ar << m_bPrintLogo;
		ar << m_iPrintLogoPos;
		m_iReportType = 0;
		ar << m_iReportType;
		ar << m_bPrintPage;

		ar << m_bInfo;
		ar << m_bRO;

		ar << m_bPhoEff;
		ar << m_bPhSP;

		ar << m_bdC;
		ar << m_bR1_15;
		ar<< m_bColorCorrectStr;
	}
	else
	{
		// TODO: add loading code here
		ar >> strVer;
		if(strVer != "OP_A" && strVer != "OP_B" 
			&& strVer != "OP_C" && strVer != "OP_D" 
			&& strVer != "OP_E"&& strVer != "OP_F"
			&& strVer != "OP_G")
		{
			return;
		}

		ar >> m_iShowCIE;
		ar >> m_iSeleTc;
		ar >> m_iSDCM1;
		ar >> m_iSDCM2;

		ar >> m_bNote;
		ar >> m_bIF;
		ar >> m_bP;
		ar >> m_bVF;
		ar >> m_bIp;
		ar >> m_bPH;  
		ar >> m_bXY;
		ar >> m_bUV;
		ar >> m_bTc;
		ar >> m_bLd;
		ar >> m_bPur;
		ar >> m_bLp;
		ar >> m_bHW;
		ar >> m_bRR;
		ar >> m_bRa;

		ar >> m_bLevel;
		ar >> m_bWhite;
//		m_bWhite = TRUE;

		ar >> m_fExportIntervalWL;
		ar >> m_bPrintLogo;
		g_bPrintLogo = m_bPrintLogo;
		ar >> m_iPrintLogoPos;
		ar >> m_iReportType;
		m_iReportType = 0;
		ar >> m_bPrintPage;

		if(strVer != "OP_A")
		{
			ar >> m_bInfo;
		}

		if(strVer != "OP_A" && strVer != "OP_B")
		{
			ar >> m_bRO;
		}

		if(strVer!="OP_A" && strVer != "OP_B" && strVer != "OP_C")
		{
			ar >> m_bPhoEff;
		}

		if(strVer=="OP_A" || strVer == "OP_B" || strVer == "OP_C"|| strVer == "OP_D")
		{
			m_bPhSP = FALSE;
		}
		else
			ar>> m_bPhSP;

		if(strVer=="OP_A" || strVer == "OP_B" || strVer == "OP_C"|| strVer == "OP_D"|| strVer == "OP_E")
		{

		}
		else
		{
			ar >> m_bdC;
			ar >> m_bR1_15;
		}

		if(strVer=="OP_A" || strVer == "OP_B" || strVer == "OP_C"
			|| strVer == "OP_D"|| strVer == "OP_E"|| strVer == "OP_F")
		{
			m_bColorCorrectStr = FALSE;
		}
		else
			ar>>m_bColorCorrectStr;

	}
}

void COPSetupData::Init()
{
	m_iShowCIE    = 0;
	m_iSeleTc     = 0;
	m_iSDCM1      = 5;
	m_iSDCM2      = 6;

	m_bNote      = TRUE;
	m_bIF        = FALSE;
	m_bP         = FALSE;
	m_bVF        = FALSE;
	m_bIp        = TRUE;
	m_bPH        = TRUE;  
	m_bXY        = TRUE;
	m_bUV        = FALSE;
	m_bTc        = TRUE;
	m_bLd        = TRUE;
	m_bPur       = TRUE;
	m_bLp        = TRUE;
	m_bHW        = TRUE;
	m_bRR        = TRUE;
	m_bRa        = TRUE;
	m_bRO        = FALSE;
	m_bLevel     = TRUE;
	m_bWhite     = TRUE;
	m_bPhoEff	 = FALSE;

	m_fExportIntervalWL = 1.0f;

	m_bPrintLogo = TRUE;
	m_iPrintLogoPos = 0;
	m_iReportType = 0;
	m_bPrintPage = TRUE;
}

BOOL COPSetupData::Open(CString strPathName)
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

BOOL COPSetupData::Save(CString strPathName)
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
