// OPSetupData.h: interface for the COPSetupData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPSETUPDATA_H__18ED9161_C557_11DA_949C_00055D02EEF1__INCLUDED_)
#define AFX_OPSETUPDATA_H__18ED9161_C557_11DA_949C_00055D02EEF1__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class COPSetupData : public CObject  
{
public:
	BOOL Save(CString strPathName);
	BOOL Open(CString strPathName);
	void Init();
	void Serialize(CArchive &ar);

	BOOL    m_iShowCIE;
	int     m_iSeleTc;
	int		m_iSDCM1;
	int		m_iSDCM2;

	BOOL    m_bNote;
	BOOL	m_bIF;
	BOOL	m_bP;
	BOOL	m_bVF;
	BOOL    m_bIp;
	BOOL    m_bPH;  
	BOOL    m_bXY;
	BOOL    m_bUV;
	BOOL    m_bTc;
	BOOL    m_bLd;
	BOOL    m_bPur;
	BOOL    m_bLp;
	BOOL    m_bHW;
	BOOL    m_bRR;
	BOOL    m_bRa;
	BOOL    m_bRO;

	BOOL    m_bLevel;
	BOOL    m_bWhite;

	BOOL	m_bPhoEff;
	BOOL    m_bZW;//×ÏÍâ²ÎÊý
	BOOL	m_bInfo;

	BOOL    m_bPhSP;

	float   m_fExportIntervalWL;

	BOOL	m_bPrintLogo;
	int		m_iPrintLogoPos;
	int     m_iReportType;
	BOOL    m_bPrintPage;

	BOOL	m_bdC;
	BOOL	m_bR1_15;
	BOOL    m_bColorCorrectStr;

	COPSetupData();
	virtual ~COPSetupData();

};

#endif // !defined(AFX_OPSETUPDATA_H__18ED9161_C557_11DA_949C_00055D02EEF1__INCLUDED_)
