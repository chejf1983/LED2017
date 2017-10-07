#include "StdAfx.h"
#include "CalibrationData.h"


CCalibrationData::CCalibrationData(void)
{
	for (int i = 0; i < MAX_RANGE; i++)
	{
		m_fkI[i] = 1.0f;
		m_fbI[i] = 0.0f;
		m_fkU[i] = 1.0f;
		m_fbU[i] = 0.0f;

		for (int j = 0; j < CAL_DA_NUM; j++)
		{
			m_fI[i][j] = 0.0f;
			m_fDAI[i][j] = 0.0f;
			m_fStdI[i][j] = 0.0f;

			m_fU[i][j] = 0.0f;
			m_fDAU[i][j] = 0.0f;
			m_fStdU[i][j] = 0.0f;
		}
	}
}


CCalibrationData::~CCalibrationData(void)
{
}


BOOL CCalibrationData::Serialize(CArchive & ar)
{
	if (ar.IsStoring())
	{
		CString strEdition = "Calibration Data V1.00";
		ar<<strEdition;

		for (int i = 0; i < MAX_RANGE; i++)
		{
			ar<<m_fkI[i];
			ar<<m_fbI[i];
			ar<<m_fkU[i];
			ar<<m_fbU[i];

			for (int j = 0; j < CAL_DA_NUM; j++)
			{
				ar<<m_fI[i][j];
				ar<<m_fDAI[i][j];
				ar<<m_fStdI[i][j];

				ar<<m_fU[i][j];
				ar<<m_fDAU[i][j];
				ar<<m_fStdU[i][j];
			}
		}
	}
	else
	{
		CString strEdition;
		ar>>strEdition;
		if ("Calibration Data V1.00" != strEdition)
		{
			AfxMessageBox("定标数据文件版本不对，无法打开！");
			return FALSE;
		}
		
		for (int i = 0; i < MAX_RANGE; i++)
		{
			ar>>m_fkI[i];
			ar>>m_fbI[i];
			ar>>m_fkU[i];
			ar>>m_fbU[i];

			for (int j = 0; j < CAL_DA_NUM; j++)
			{
				ar>>m_fI[i][j];
				ar>>m_fDAI[i][j];
				ar>>m_fStdI[i][j];

				ar>>m_fU[i][j];
				ar>>m_fDAU[i][j];
				ar>>m_fStdU[i][j];
			}
		} // for
	}

	return TRUE;
}


BOOL CCalibrationData::SaveFile(CString strPathName)
{
	CFile file;
	BOOL bR = file.Open(strPathName, CFile::modeCreate | CFile::modeWrite);
	if (!bR)
	{
		return FALSE;
	}

	CArchive ar(&file, CArchive::store);
	bR = Serialize(ar);
	if (!bR)
	{
		return FALSE;
	}

	ar.Close();
	file.Close();

	return TRUE;
}


BOOL CCalibrationData::OpenFile(CString strPathName)
{
	CFile file;
	BOOL bR = file.Open(strPathName, CFile::modeRead);
	if (!bR)
	{
		return FALSE;
	}

	CArchive ar(&file, CArchive::load);
	bR = Serialize(ar);
	if (!bR)
	{
		return FALSE;
	}

	ar.Close();
	file.Close();
	return TRUE;
}


int CCalibrationData::GetNoneZeroIk()
{
	int iNum = 0;
	for (int i = 0; i < MAX_RANGE; i++)
	{
		if (m_fkI[i] > 1e-6 || m_fkI[i] < -1e-6)
		{
			iNum++;
		}
	}

	return iNum;
}


int CCalibrationData::GetNoneZeroUk()
{
	int iNum = 0;
	for (int i = 0; i < MAX_RANGE; i++)
	{
		if (m_fkU[i] > 1e-6 || m_fkU[i] < -1e-6)
		{
			iNum++;
		}
	}

	return iNum;
}