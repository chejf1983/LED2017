// TestContainer.cpp : 实现文件
//

#include "stdafx.h"
#include "TestContainer.h"
#include "LAT2000Doc.h"

// CTestContainer

CTestContainer::CTestContainer()
{
	m_bOppositeDirection	= FALSE;
	m_iLEDRowCount			= 3;
	m_iLEDColumnCount		= 10;
	m_iCurrentIndex			= -1;
	m_iCurrentThunderChannel = -1;

	m_LEDData.SetSize(m_iLEDRowCount * m_iLEDColumnCount);
	m_LEDState.SetSize(m_iLEDRowCount * m_iLEDColumnCount);
	m_LEDUpdated.SetSize(m_iLEDRowCount * m_iLEDColumnCount);
	
	m_ChannelNeedTest.SetSize(m_iLEDColumnCount);
	for (int i = 0; i < m_iLEDColumnCount; i++)
	{
		m_ChannelNeedTest[i] = TRUE;
	} 
    m_bRowScaned			= FALSE;
    m_iCurrentTestRow		= -1;
    m_bCurrentRowNeedTest	= FALSE;
	LoadALlRowLEDSNFile(g_strCurrentPath + "RowLEDSN.sn");
}

CTestContainer::~CTestContainer()
{
	SaveALlRowLEDSNFile(g_strCurrentPath + "RowLEDSN.sn");
}

// CTestContainer 成员函数

BOOL CTestContainer::SetLEDMatrix(int iRowCount, int iColumnCount)
{
	//设置界面的行列数
	if (iRowCount < 0 || iColumnCount < 0 || iRowCount > 20 || iColumnCount > 20)
	{
		return FALSE;
	}

	m_iLEDRowCount		= iRowCount;
	m_iLEDColumnCount	= iColumnCount;

	m_LEDData.SetSize(m_iLEDRowCount * m_iLEDColumnCount);
	m_LEDState.SetSize(m_iLEDRowCount * m_iLEDColumnCount);
	m_LEDUpdated.SetSize(m_iLEDRowCount * m_iLEDColumnCount);
	
	m_ChannelNeedTest.SetSize(m_iLEDColumnCount);
	for (int i = 0; i < m_iLEDColumnCount; i++)
	{
		m_ChannelNeedTest[i] = TRUE;
	}

	return TRUE;
}


void CTestContainer::ResetLEDState()
{
	for (int i = 0; i < m_LEDState.GetCount(); i++)
	{
		m_LEDState[i].ElectricalTestState = NotTest;
		m_LEDState[i].SpectrumTestState = NotTest;
	}

	for (int i = 0; i < m_LEDUpdated.GetCount(); i++)
	{
		m_LEDUpdated[i] = FALSE;
	}
}


BOOL CTestContainer::SetTestChannel(BOOL bTest[])
{
	ASSERT(NULL != bTest);

	for (int i = 0; i < m_ChannelNeedTest.GetSize(); i++)
	{
		m_ChannelNeedTest[i] = bTest[i];
	}

	return TRUE;
}


void CTestContainer::SetDirectionOpposite(BOOL bOpposite /* = TRUE */)
{
	m_bOppositeDirection = bOpposite;
}


BOOL CTestContainer::SetCurrentLED(int iIndex)
{
	if (iIndex < 0 || iIndex >= m_iLEDColumnCount)
	{
		return FALSE;
	}

	m_iCurrentIndex = iIndex;
	return TRUE;
}


BOOL CTestContainer::IsLEDUpdated(int iRowIndex, int iColumnIndex)
{
	CSingleLock lock(&m_critialUpdate, TRUE);

	int iIndex = iRowIndex * m_iLEDColumnCount + iColumnIndex;
	ASSERT(iIndex >= 0 && iIndex < m_LEDUpdated.GetCount());

	return m_LEDUpdated[iIndex];
}


BOOL CTestContainer::IsOppositeDirection()
{
	return m_bOppositeDirection;
}


void CTestContainer::SetLEDUpdated(int iRowIndex, int iColumnIndex, BOOL bUpdated)
{
	CSingleLock lock(&m_critialUpdate, TRUE);

	int iIndex = iRowIndex * m_iLEDColumnCount + iColumnIndex;
	ASSERT(iIndex >= 0 && iIndex < m_LEDUpdated.GetCount());

	m_LEDUpdated[iIndex] = bUpdated;
}


void CTestContainer::SetLEDUpdated(int iIndex, BOOL bUpdated)
{
	CSingleLock lock(&m_critialUpdate, TRUE);

	ASSERT(iIndex >= 0 && iIndex < m_LEDUpdated.GetCount());
	m_LEDUpdated[iIndex] = bUpdated;
}


void CTestContainer::SetCurrentLEDUpdated(BOOL bUpdated)
{
	CSingleLock lock(&m_critialUpdate, TRUE);
	
	ASSERT(m_iCurrentIndex >= 0 && m_iCurrentIndex < m_LEDUpdated.GetCount());

	m_LEDUpdated[m_iCurrentIndex] = bUpdated;
}


void CTestContainer::SetCurrentLEDState(LEDState state)
{
	ASSERT(m_iCurrentIndex >= 0 && m_iCurrentIndex < m_iLEDColumnCount);

	m_LEDState[m_iCurrentIndex]		= state;
	m_LEDUpdated[m_iCurrentIndex]	= FALSE;
}


void CTestContainer::SetLEDState(int iIndex, LEDState state)
{
	ASSERT(iIndex >= 0 && iIndex < m_iLEDColumnCount * m_iLEDRowCount);

	m_LEDState[iIndex]		= state;
	m_LEDUpdated[iIndex]	= FALSE;
}


LEDState & CTestContainer::GetCurrentLEDState()
{
	ASSERT(m_iCurrentIndex >= 0 && m_iCurrentIndex < m_iLEDColumnCount);

	return m_LEDState[m_iCurrentIndex];
}


int CTestContainer::GetCurrentLEDIndex()
{
	return m_iCurrentIndex;
}


void CTestContainer::MoveToFirst()
{
	ASSERT(m_LEDData.GetSize() > 0);

	if (m_bOppositeDirection)
	{
		for (int i = m_ChannelNeedTest.GetSize() - 1; i >= 0; i--)
		{
			if (m_ChannelNeedTest[i])
			{
				m_iCurrentIndex = i;
				break;
			}
		}
	}
	else
	{
		for (int i = 0; i < m_ChannelNeedTest.GetSize(); i++)
		{
			if (m_ChannelNeedTest[i])
			{
				m_iCurrentIndex = i;
				break;
			}
		}
	}
}


BOOL CTestContainer::MoveToNext()
{
	if (m_iCurrentIndex < 0 || m_iCurrentIndex >= m_iLEDColumnCount)
	{
		return FALSE;
	}
	if (m_bOppositeDirection)
	{
		for (int i = m_iCurrentIndex - 1; i >= 0; i--)
		{
			if (m_ChannelNeedTest[i])
			{
				m_iCurrentIndex = i;
				break;
			}
		}
	}
	else
	{
		for (int i = m_iCurrentIndex + 1; i < m_ChannelNeedTest.GetSize(); i++)
		{
			if (m_ChannelNeedTest[i])
			{
				m_iCurrentIndex = i;
				break;
			}
		}
	}
	return TRUE;
}


void CTestContainer::MoveToLast()
{
	ASSERT(m_LEDData.GetSize() > 0);

	if (m_bOppositeDirection)
	{
		for (int i = 0; i < m_ChannelNeedTest.GetSize(); i++)
		{
			if (m_ChannelNeedTest[i])
			{
				m_iCurrentIndex = i;
				break;
			}
		}
	}
	else
	{
		for (int i = m_ChannelNeedTest.GetSize() - 1; i >= 0; i--)
		{
			if (m_ChannelNeedTest[i])
			{
				m_iCurrentIndex = i;
				break;
			}
		}
	}
}


void CTestContainer::StartNewRow()
{
	int iIndex1 = 0, iIndex2 = 0;
	for (int i = m_iLEDRowCount - 1; i > 0; i--)
	{
		for (int j = 0; j < m_iLEDColumnCount; j++)
		{
			iIndex1 = i * m_iLEDColumnCount + j;
			iIndex2 = (i - 1) * m_iLEDColumnCount + j;
			
			m_LEDData[iIndex1] = m_LEDData[iIndex2];
			m_LEDState[iIndex1] = m_LEDState[iIndex2];
		}
	}

	for (int j = 0; j < m_iLEDColumnCount; j++)
	{
		m_LEDState[j].ElectricalTestState = NotTest;
		m_LEDState[j].SpectrumTestState = NotTest;
	}

	for (int i = 0; i < m_LEDUpdated.GetCount(); i++)
	{
		m_LEDUpdated[i] = FALSE;
	}
}


void CTestContainer::ResetCurrentRow()
{
	for (int j = 0; j < m_iLEDColumnCount; j++)
	{
		m_LEDState[j].ElectricalTestState = NotTest;
		m_LEDState[j].SpectrumTestState = NotTest;
	}

	for (int i = 0; i < m_LEDUpdated.GetCount(); i++)
	{
		m_LEDUpdated[i] = FALSE;
	}
}

void CTestContainer::ResetAllRows()
{
    for (int j = 0; j < m_LEDState.GetSize(); j++)
    {
        m_LEDState[j].ElectricalTestState = NotTest;
        m_LEDState[j].SpectrumTestState = NotTest;
    }
    for (int j = 0; j < m_LEDUpdated.GetCount(); j++)
    {
        m_LEDUpdated[j] = FALSE;
    }
}

int CTestContainer::GetIndex(int iRowIndex, int iColumnIndex)
{
	return iRowIndex * m_iLEDColumnCount + iColumnIndex;
}


int CTestContainer::GetLEDRowSize()
{
	return m_iLEDRowCount;
}


int CTestContainer::GetLEDColumnSize()
{
	return m_iLEDColumnCount;		
}


int CTestContainer::GetLEDCount()
{
	return m_LEDData.GetSize();
}


LEDState & CTestContainer::GetLEDState(int iRowIndex, int iColumnIndex)
{
	int iIndex = m_iLEDColumnCount * iRowIndex + iColumnIndex;
	ASSERT(iIndex >= 0 && iIndex < m_LEDState.GetSize());

	return m_LEDState[iIndex];
}


LEDState & CTestContainer::GetLEDState(int iIndex)
{
	ASSERT(iIndex >= 0 && iIndex < m_LEDState.GetSize());

	return m_LEDState[iIndex];
}

	
CLedData & CTestContainer::GetLEDData(int iRowIndex, int iColumnIndex)
{
	int iIndex = m_iLEDColumnCount * iRowIndex + iColumnIndex;
	ASSERT(iIndex >= 0 && iIndex < m_LEDState.GetSize());

	return m_LEDData[iIndex];
}


CLedData & CTestContainer::GetLEDData(int iIndex)
{
	ASSERT(iIndex >= 0 && iIndex < m_LEDState.GetSize());

	return m_LEDData[iIndex];
}


CLedData & CTestContainer::GetCurrentLEDData()
{
	ASSERT (m_iCurrentIndex >= 0 && m_iCurrentIndex < m_iLEDColumnCount);

	return m_LEDData[m_iCurrentIndex];
}


BOOL CTestContainer::IsTestHalfway()
{
	BOOL bHaveTested = FALSE, bHaveUntested = FALSE;
	for (int i = 0; i < m_iLEDColumnCount; i++)
	{
		if (m_ChannelNeedTest[i])
		{
			if (NotTest == m_LEDState[i].ElectricalTestState)
			{
				bHaveUntested = TRUE;
			}
			else
			{
				bHaveTested = TRUE;
			}
		}
	}
	if (bHaveTested && bHaveUntested)
	{
		return TRUE;
	}

	bHaveUntested = FALSE;
	bHaveTested = FALSE;
	for (int i = 0; i < m_iLEDColumnCount; i++)
	{
		if (m_ChannelNeedTest[i])
		{
			if (NotTest == m_LEDState[i].SpectrumTestState)
			{
				bHaveUntested = TRUE;
			}
			else
			{
				bHaveTested = TRUE;
			}
		}
	}
	if (bHaveTested && bHaveUntested)
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CTestContainer::HaveTestedLED()
{
	for (int i = 0; i < m_iLEDColumnCount; i++)
	{
		if ((NotTest != m_LEDState[i].ElectricalTestState || NotTest != m_LEDState[i].SpectrumTestState) && m_ChannelNeedTest[i])
		{
			return TRUE;
		}
	}

	return FALSE;
}

int CTestContainer::HaveElectricalUntestedLED()
{
	int iCount = 0;
	if (g_pDoc->m_CommSettingsData.m_bHaveScaner)
	{
		int iCurTestRowScanNumTemp = 0;
		for (int i = 0; i < m_iLEDColumnCount; i++)
		{
			GetCurrentTestRow();
			if (m_ChannelNeedTest[i])
			{
				if (NotTest == m_LEDState[i].ElectricalTestState)
				{
					iCount++;
				}
				iCurTestRowScanNumTemp ++;
				if (iCurTestRowScanNumTemp >= m_strRowLEDSN.GetAt(m_iCurrentTestRow).GetSNNum())
				{
					break;
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < m_iLEDColumnCount; i++)
		{
			if (NotTest == m_LEDState[i].ElectricalTestState && m_ChannelNeedTest[i])
			{
				iCount++;
			}
		}
	}
	return iCount;
}

BOOL CTestContainer::IsAllLEDTest()
{
	GetCurrentTestRow();
	if (g_pDoc->m_CommSettingsData.m_bHaveScaner)
	{
		int iCurTestRowScanNumTemp = 0;
		for (int i = 0; i < m_iLEDColumnCount; i++)
		{
			if (m_ChannelNeedTest[i])
			{
				if ((NotTest == m_LEDState[i].ElectricalTestState || NotTest == m_LEDState[i].SpectrumTestState))
				{
					return FALSE;
				}
				iCurTestRowScanNumTemp ++;
				if (m_iCurrentTestRow >= 0)
				{
					if (iCurTestRowScanNumTemp >= m_strRowLEDSN.GetAt(m_iCurrentTestRow).GetSNNum())
					{
						break;
					}
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < m_iLEDColumnCount; i++)
		{
			if ((NotTest == m_LEDState[i].ElectricalTestState || NotTest == m_LEDState[i].SpectrumTestState) && m_ChannelNeedTest[i])
			{
				return FALSE;
			}
		}	
	}
	return TRUE;
}

int CTestContainer::HaveSpectrumUntestedLED()
{
	int iCount = 0;
	if (g_pDoc->m_CommSettingsData.m_bHaveScaner)
	{
		int iCurTestRowScanNumTemp = 0;
		for (int i = 0; i < m_iLEDColumnCount; i++)
		{
			if (m_ChannelNeedTest[i])
			{
				GetCurrentTestRow();
				if (NotTest == m_LEDState[i].SpectrumTestState)
				{
					iCount++;
				}
				iCurTestRowScanNumTemp ++;
				if (iCurTestRowScanNumTemp >= m_strRowLEDSN.GetAt(m_iCurrentTestRow).GetSNNum())
				{
					break;
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < m_iLEDColumnCount; i++)
		{
			if (NotTest == m_LEDState[i].SpectrumTestState && m_ChannelNeedTest[i])
			{
				iCount++;
			}
		}
	}

	return iCount;
}


CString CTestContainer::GetInfoString(int iRowIndex, int iColumnIndex, BOOL bLedOn)
{
	int iIndex = m_iLEDColumnCount * iRowIndex + iColumnIndex;
	if (iIndex < 0 || iIndex > m_LEDData.GetCount())
	{
		return "Invalid";
	}

	return m_LEDData[iIndex].GetInfoString(bLedOn);
}


RowLEDSN &CTestContainer::GetRowLEDSN(int iIndex)
{
    return m_strRowLEDSN.GetAt(iIndex);
}

BOOL CTestContainer::IsCurBoardIDInRowLEDSN(int iIndex)
{
    if (iIndex >= 0 && iIndex <= m_strRowLEDSN.GetSize() - 1)
    {
        return FALSE;
    }
    for (int i = 0; i < m_strRowLEDSN.GetCount(); i ++)
    {
        if (iIndex == m_strRowLEDSN.GetAt(i).GetRowSN())
        {
            return TRUE;
        }
    }
    return FALSE;
}

void CTestContainer::InsertRowLEDSN(int iIndex, RowLEDSN &data)
{
    m_strRowLEDSN.InsertAt(iIndex, data);
    if (GetRowLEDSNCount() == g_pDoc->m_CommSettingsData.m_iTotalBoard)
    {
        m_strRowLEDSN.SetSize(g_pDoc->m_CommSettingsData.m_iTotalBoard);
    }
}

int CTestContainer::GetRowLEDSNCount()
{
    return m_strRowLEDSN.GetSize();
}

void  CTestContainer::SetCurrentRowScaned(BOOL bScaned)
{
    m_bRowScaned = bScaned;
}

BOOL  CTestContainer::HaveLastRowLEDScaned()
{   
    if (g_pDoc->m_CommSettingsData.m_bHaveScaner)
    {
        return m_bRowScaned;
    }
    else
    {
        return TRUE;
    }
}

int CTestContainer::GetCurrentScanBoard()
{
	//得到当前扫码的板号
	int iCurrentScanBoardID;
	iCurrentScanBoardID = g_pDoc->m_systemSettingsData.m_iCurrentBoardID;
	if (iCurrentScanBoardID <= 0)
	{
		iCurrentScanBoardID += g_pDoc->m_CommSettingsData.m_iTotalBoard;
	}
	return iCurrentScanBoardID;
}

int CTestContainer::GetCurrentScanIDNum()
{
	//if(m_strRowLEDSN.GetSize() > 0)
		return m_tempRowLEDSN.GetSNNum();
	//else
		return 0;
}

int CTestContainer::GetCurrentTestBoard()
{
	//得到当前测试的板号
	int iCurrentBoardID;
	if (g_pDoc->m_systemSettingsData.m_iLEDOnPos)
	{
		iCurrentBoardID = g_pDoc->m_systemSettingsData.m_iCurrentBoardID - g_pDoc->m_CommSettingsData.m_iSpectialLEDOnAndLEDTestRange - 1;			
	}
	else
	{
		iCurrentBoardID = g_pDoc->m_systemSettingsData.m_iCurrentBoardID - g_pDoc->m_CommSettingsData.m_iLEDOnAndLEDTestRange - 1;
	}
	if (iCurrentBoardID <= 0)
	{
		iCurrentBoardID += g_pDoc->m_CommSettingsData.m_iTotalBoard;
	}
	return iCurrentBoardID;
}

BOOL CTestContainer::CurrentTestRowIsScaned()
{
	//当前测试工位是否已经扫码
    int iCurrentBoardID = GetCurrentTestBoard();
    for (int i = 0; i < m_strRowLEDSN.GetSize(); i ++)
    {
        if (iCurrentBoardID
            == m_strRowLEDSN.GetAt(i).GetRowSN())
        {
            return TRUE;
        }
    }
    return FALSE;
}

BOOL CTestContainer::CurrentTestRowIsSafted()
{
	//当前测试工位是否已经测试过安规
	
	return FALSE;
}

int CTestContainer::GetRemoveBoard()
{
	int iLEDDownBoard;
	if (g_pDoc->m_systemSettingsData.m_iLEDOnPos)
	{
		iLEDDownBoard = g_pDoc->m_systemSettingsData.m_iCurrentBoardID- g_pDoc->m_CommSettingsData.m_iSpectialLEDOnAndLEDTestRange - 1
			- g_pDoc->m_CommSettingsData.m_iLEDTestAndLEDDownRange - 1;
	}
	else
	{
		iLEDDownBoard = g_pDoc->m_systemSettingsData.m_iCurrentBoardID - g_pDoc->m_CommSettingsData.m_iLEDOnAndLEDTestRange - 1 
			- g_pDoc->m_CommSettingsData.m_iLEDTestAndLEDDownRange - 1;
	}

	if (iLEDDownBoard <= 0)
	{
		iLEDDownBoard += g_pDoc->m_CommSettingsData.m_iTotalBoard;
	}
	return iLEDDownBoard;
}

void CTestContainer::RemoveLEDDownRow()
{
	int iLEDDownBoard = GetRemoveBoard();
    for (int i = 0; i < m_strRowLEDSN.GetSize(); i ++)
    {
        if (iLEDDownBoard
            == m_strRowLEDSN.GetAt(i).GetRowSN())
        {
            m_strRowLEDSN.RemoveAt(i);
        }
    }
}


int CTestContainer::GetCurrentTestRow()
{
	int iCurrentBoardID;
	if (g_pDoc->m_systemSettingsData.m_iLEDOnPos)
	{
		iCurrentBoardID = g_pDoc->m_systemSettingsData.m_iCurrentBoardID - g_pDoc->m_CommSettingsData.m_iSpectialLEDOnAndLEDTestRange - 1;			
	}
	else
	{
		iCurrentBoardID = g_pDoc->m_systemSettingsData.m_iCurrentBoardID - g_pDoc->m_CommSettingsData.m_iLEDOnAndLEDTestRange - 1;
	}
	if (iCurrentBoardID <= 0)
	{
		iCurrentBoardID += g_pDoc->m_CommSettingsData.m_iTotalBoard;
	}
	for (int i = 0; i < m_strRowLEDSN.GetSize(); i ++)
	{
		if (iCurrentBoardID
			== m_strRowLEDSN.GetAt(i).GetRowSN())
		{
			m_iCurrentTestRow = i;
		}
	}
	return m_iCurrentTestRow;
}

BOOL CTestContainer::LoadALlRowLEDSNFile(CString strPathName)
{
    CFile file;
    if (!file.Open(strPathName, CFile::modeRead))
    {
        return FALSE;
    }

    CArchive ar(&file, CArchive::load);
    if (!SerializeALlRowLEDSN(ar))
    {
        ar.Close();
        file.Close();
        return FALSE;
    }

    ar.Close();
    file.Close();

    return TRUE;
}


BOOL CTestContainer::SaveALlRowLEDSNFile(CString strPathName)
{
    CFile file;
    if (!file.Open(strPathName, CFile::modeWrite | CFile::modeCreate))
    {
        return FALSE;
    }

    CArchive ar(&file, CArchive::store);
    if (!SerializeALlRowLEDSN(ar))
    {
        ar.Close();
        file.Close();
        return FALSE;
    }

    ar.Close();
    file.Close();

    return TRUE;
}


BOOL CTestContainer::SerializeALlRowLEDSN(CArchive & ar)
{
    CString strDev;
    if (ar.IsStoring())
    {
        strDev = "AllRowLEDSN";
        ar << strDev;
        ar << m_strRowLEDSN.GetSize();
        for (int i = 0; i < m_strRowLEDSN.GetSize(); i ++)
        {
            ar << m_strRowLEDSN.GetAt(i).m_iRowSN;
            ar << m_strRowLEDSN.GetAt(i).m_strLEDSN.GetSize();
            for (int j = 0; j < m_strRowLEDSN.GetAt(i).m_strLEDSN.GetSize(); j ++)
            {
                ar << m_strRowLEDSN.GetAt(i).m_strLEDSN.GetAt(j);
            }
        }
    }
    else
    {
        ar >> strDev;
        if ("AllRowLEDSN" != strDev)
        {
            return FALSE;
        }
        int iN;
        int iM;
        CString strTemp;
        ar >> iN;
        m_strRowLEDSN.RemoveAll();
        for (int i = 0; i < iN; i ++)
        {
            RowLEDSN temp;
            ar >> temp.m_iRowSN;
            ar >> iM;
            for (int j = 0; j < iM; j ++)
            {
                ar >> strTemp;
                temp.AddLEDSN (strTemp);
            }
            m_strRowLEDSN.Add(temp);
        }
    }
    return TRUE;
}

void CTestContainer::SetCurrentRowNeedTest(BOOL bNeedTest)
{
    m_bCurrentRowNeedTest = bNeedTest;
}

BOOL CTestContainer::IsLastRowNeedTest()
{
	if (g_pDoc->m_CommSettingsData.m_bHaveScaner)
	{
		return m_bCurrentRowNeedTest;
	}
	else
	{
		return TRUE;
	}
}
///////////////////////////////////////////////////////////////////////////////////

void  CTestContainer::SetCurrentRowInLamped(BOOL bInLamped)
{
	m_bRowInLamped = bInLamped;
}

BOOL  CTestContainer::HaveLastRowLEDInLamped()
{   
	if (g_pDoc->m_CommSettingsData.m_bHaveHandAuto)
	{
		return m_bRowInLamped;
	}
	else
	{
		return TRUE;
	}
}

int CTestContainer::GetCurrentInLampBoard()
{
	//得到当前上灯的板号
	int iCurrentScanBoardID;
	iCurrentScanBoardID = g_pDoc->m_systemSettingsData.m_iCurrentBoardID;
	if (iCurrentScanBoardID <= 0)
	{
		iCurrentScanBoardID += g_pDoc->m_CommSettingsData.m_iTotalBoard;
	}
	return iCurrentScanBoardID;
}

int CTestContainer::GetCurrentInLampIDNum()
{
	//得到已经上灯的板数
	return m_tempInLampLED.m_bInLamp.GetSize();
}

int CTestContainer::GetCurrentTest2Board()
{
	//得到当前测试的板号
	int iCurrentBoardID;
	if (g_pDoc->m_systemSettingsData.m_iLEDOnPos)
	{
		iCurrentBoardID = g_pDoc->m_systemSettingsData.m_iCurrentBoardID - g_pDoc->m_CommSettingsData.m_iSpectialLEDOnAndLEDTestRange - 1;			
	}
	else
	{
		iCurrentBoardID = g_pDoc->m_systemSettingsData.m_iCurrentBoardID - g_pDoc->m_CommSettingsData.m_iLEDOnAndLEDTestRange - 1;
	}
	if (iCurrentBoardID <= 0)
	{
		iCurrentBoardID += g_pDoc->m_CommSettingsData.m_iTotalBoard;
	}
	return iCurrentBoardID;
}

BOOL CTestContainer::CurrentTestRowIsInLamped()
{
	//当前测试工位是否已经扫码
	int iCurrentBoardID = GetCurrentTestBoard();
	for (int i = 0; i < m_strRowLEDSN.GetSize(); i ++)
	{
		if (iCurrentBoardID
			== m_strRowLEDSN.GetAt(i).GetRowSN())
		{
			return TRUE;
		}
	}
	return FALSE;
}
