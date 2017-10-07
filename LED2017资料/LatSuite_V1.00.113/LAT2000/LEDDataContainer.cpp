#include "StdAfx.h"
#include "LEDDataContainer.h"
#include "_cell.h"
#include "_column.h"
#include "RegionToolDLL.h"
#include "LAT2000Doc.h"
#include  "math.h"
#include "LAT2000.h"



CLEDDataContainer::CLEDDataContainer(void)
{      


}

CLEDDataContainer::~CLEDDataContainer(void)
{
}


BOOL CLEDDataContainer::InsertData(int iRow, int iCol, CLedData & data)
{
	LEDIndex IndexTemp;
	IndexTemp.iRow		= iRow;
	IndexTemp.iColumn	= iCol;
	m_LedIndex.Add(IndexTemp);

	m_data.Add(data);

	return TRUE;
}


CTime CLEDDataContainer::GetLEDTestTime(int iIndex)
{
	ASSERT(iIndex > 0 && iIndex < m_data.GetSize());

	int i = 0;
	for (i = m_iTN.GetSize() - 1; i >= 0; i--)
	{
		if (iIndex >= m_iTN[i])
		{
			break;
		}
	}
	if (i < 0)
	{
		return FALSE;
	}

	return m_tTime[i];
}


CString CLEDDataContainer::GetLEDTestTimeString(int iIndex)
{
	ASSERT(iIndex >= 0 && iIndex < m_data.GetCount());

	int i = 0;
	for (i = m_iTN.GetSize() - 1; i >= 0; i--)
	{
		if (iIndex >= m_iTN[i])
		{
			break;
		}
	}
	if (i < 0)
	{
		return FALSE;
	}

	return m_tTime[i].Format("%Y/%m/%d %H:%M:%S");
}


int CLEDDataContainer::GetDataNumberTestAtTime(int iDataIndex)
{
	if (iDataIndex < 0 || iDataIndex >= m_data.GetSize())
	{
		return 0;
	}

	int i = 0;
	for (i = 0; i < m_iTN.GetSize(); i++)
	{
		if (m_iTN[i] == iDataIndex)
		{
			break;
		}
	}
	if (m_iTN.GetSize() == i)
	{
		return 0;
	}

	int iBegin = m_iTN[i], iEnd = 0;
	if (m_iTN.GetSize() > i + 1)
	{
		iEnd = m_iTN[i+1];
	}
	else
	{
		iEnd = m_data.GetSize();
	}

	return iEnd - iBegin;
}


BOOL CLEDDataContainer::DeleteDataTestAtTime(int iDataIndex)
{
	if (iDataIndex < 0 || iDataIndex >= m_data.GetSize())
	{
		return FALSE;
	}
	int i = 0;
	for (i = m_iTN.GetSize() - 1; i >= 0; i--)
	{
		if (m_iTN[i] <= iDataIndex)
		{
			break;
		}
	}

	int iBegin = m_iTN[i], iEnd = 0;
	if (i + 1 < m_iTN.GetSize())
	{
		iEnd = m_iTN[i+1];
	}
	else
	{
		iEnd = m_data.GetSize();
	}

	if (iEnd < iBegin)
	{
		return FALSE;
	}

	m_data.RemoveAt(iBegin, iEnd - iBegin);
	m_LedIndex.RemoveAt(iBegin, iEnd - iBegin);

	m_tTime.RemoveAt(i);
	m_iTN.RemoveAt(i);
	for (int j = i; j < m_iTN.GetSize(); j++)
	{
		m_iTN[j] -= iEnd - iBegin;
	}

	return TRUE;
}


BOOL CLEDDataContainer::GetLEDRowColumn(int iIndex, int & iRow, int & iCol)
{
	if (iIndex < 0 && iIndex >= m_data.GetSize())
	{
		return FALSE;
	}

	iRow = m_LedIndex[iIndex].iRow;
	iCol = m_LedIndex[iIndex].iColumn;
	
	return TRUE;
}


CLedData & CLEDDataContainer::GetAt(int iIndex)
{
	ASSERT(iIndex >= 0 && iIndex < m_data.GetCount());

	return m_data[iIndex];
}


int CLEDDataContainer::GetSize()
{
	return m_data.GetCount();
}


void CLEDDataContainer::SetTestTime(CTime tTime)
{
	m_iTN.Add(m_data.GetSize());
	m_tTime.Add(tTime);
}


void CLEDDataContainer::RemoveAllData()
{
	m_data.RemoveAll();
	m_LedIndex.RemoveAll();
	m_iTN.RemoveAll();
	m_tTime.RemoveAll();
}


BOOL CLEDDataContainer::LoadFile(CString strPathName)
{
	CFile file;
	if (!file.Open(strPathName, CFile::modeRead))
	{
		return FALSE;
	}

	CArchive ar(&file, CArchive::load);
	if (!Serialize(ar))
	{
		ar.Close();
		file.Close();
		return FALSE;
	}
	
	ar.Close();
	file.Close();

	return TRUE;
}


BOOL CLEDDataContainer::SaveFile(CString strPathName)
{
	CFile file;
	if (!file.Open(strPathName, CFile::modeWrite | CFile::modeCreate))
	{
		return FALSE;
	}

	CArchive ar(&file, CArchive::store);
	if (!Serialize(ar))
	{
		ar.Close();
		file.Close();
		return FALSE;
	}
	
	ar.Close();
	file.Close();

	return TRUE;
}


BOOL CLEDDataContainer::Serialize(CArchive & ar)
{
	if (ar.IsStoring())
	{
		CString strEdition = "LED Data Container V1.01";
		ar<<strEdition;

		ar<<(int)m_data.GetSize();
		for (int i = 0; i < m_data.GetSize(); i++)
		{
			m_LedIndex[i].Serialize(ar);
			m_data[i].Serialize(ar);
		}

		ar<<(int)m_iTN.GetSize();
		for (int i = 0; i < m_iTN.GetSize(); i++)
		{
			ar<<m_iTN[i];
			m_tTime[i].Serialize64(ar);
		}
       
		m_TestInfoData.Serialize(ar);
		m_TestSetData.Serialize(ar);
	}
	else
	{
		CString strEdition;
		ar>>strEdition;
		if ("LED Data Container V1.00" != strEdition && "LED Data Container V1.01" != strEdition)
		{
			AfxMessageBox("文件版本错误！");
			return FALSE;
		}
		
		// Remove all data
		m_data.RemoveAll();
		m_LedIndex.RemoveAll();
		m_iTN.RemoveAll();
		m_tTime.RemoveAll();

		int iSize = 0;
		ar>>iSize;
		for (int i = 0; i < iSize; i++)
		{
			LEDIndex index;
			index.Serialize(ar);
			m_LedIndex.Add(index);

			CLedData data;
			data.Serialize(ar);
			m_data.Add(data);
		}

		int iCount = 0;
		int iTemp = 0;
		CTime timeTemp;
		ar>>iCount;
		for (int i = 0; i < iCount; i++)
		{
			ar>>iTemp;
			m_iTN.Add(iTemp);
			timeTemp.Serialize64(ar);
			m_tTime.Add(timeTemp);
		}
        if (strEdition == "LED Data Container V1.01")
        {
            m_TestInfoData.Serialize(ar);
			m_TestSetData.Serialize(ar);
        }
	}

	return TRUE;
}


CLEDDataContainer& CLEDDataContainer::operator = (CLEDDataContainer &data)
{
    if (this == &data)
    {
        return *this;
    }
    m_data.RemoveAll();
    m_LedIndex.RemoveAll();
    m_iTN.RemoveAll();
    m_tTime.RemoveAll();

    for (int i = 0; i < data.m_data.GetSize(); i++)
    {
        CLedData *pTemp = new CLedData;
        *pTemp = data.m_data.GetAt(i);
        m_data.Add(data.m_data.GetAt(i));
        m_LedIndex.Add(data.m_LedIndex.GetAt(i));
    }

    for (int i = 0; i < data.m_iTN.GetSize(); i++)
    {
        m_iTN.Add(data.m_iTN.GetAt(i));
        m_tTime.Add(data.m_tTime.GetAt(i));
    }
    m_TestInfoData = data.m_TestInfoData;
    m_TestSetData = data.m_TestSetData;
    return *this;             
}

BOOL CLEDDataContainer::IsBoundaryData(int iIndex)
{
	for (int i = 0; i < m_iTN.GetCount(); i++)
	{
		if (iIndex == m_iTN[i])
		{
			return TRUE;
		}
	}

	return FALSE;
}


int CLEDDataContainer::GetDisplayParaNum()
{
    m_DisPlayID.RemoveAll();
    for (int i = 0; i < PARA_NUM; i++)
    {
        if (g_bListPara[i])
        {
            m_DisPlayID.Add(i);
        }
    }
    return m_DisPlayID.GetSize();
}


CString CLEDDataContainer::GetParaText(int iID, CTestSettingsData & data, CLedData &LEDdata, BOOL &bQualified,int &iTypeFail)
{
	BOOL bOK = TRUE;
	CString sStr,sTemp;
	sStr	= "";
	sTemp	= "";
	CString strTemp;
	if (LEDdata.IsLEDON())
	{
		switch(iID)
		{
		case 0:
			strTemp.Format("%.1f(%s)", LEDdata.m_fSDCM, LEDdata.m_strSDCMSta);
			bQualified = data.IsQulified(iID, LEDdata.m_fSDCM);
			if (!bQualified)
			{
				iTypeFail = 3;
			}
			break;
		case 1:
			strTemp.Format("%.1f", LEDdata.m_fCurrentA * 1000);
			bQualified = data.IsQulified(iID, LEDdata.m_fCurrentA * 1000);
			if (!bQualified)
			{
				iTypeFail = 1;
			}
			break;
        case 2:
            strTemp.Format("%.1f",LEDdata.m_fVoltageV);
            bQualified = data.IsQulified(iID,LEDdata.m_fVoltageV);
			if (!bQualified)
			{
				iTypeFail = 1;
			}
			break;
        case 3:
            strTemp.Format("%.0f",LEDdata.m_fFrequencyHz);
            bQualified = data.IsQulified(iID,LEDdata.m_fFrequencyHz);
			if (!bQualified)
			{
				iTypeFail = 1;
			}
			break;
        case 4:
            strTemp.Format("%.2f",LEDdata.m_fPowerW);
            bQualified = data.IsQulified(iID,LEDdata.m_fPowerW);
			if (!bQualified)
			{
				iTypeFail = 1;
			}
			break;
        case 5:
            strTemp.Format("%.4f",LEDdata.m_fPowerFactor);
            bQualified = data.IsQulified(iID,LEDdata.m_fPowerFactor);
			if (!bQualified)
			{
				iTypeFail = 1;
			}
			break;
        case 6:
            strTemp.Format("%.4g",LEDdata.m_ColorData.m_fPh);
            bQualified = data.IsQulified(iID,LEDdata.m_ColorData.m_fPh);
			if (!bQualified)
			{
				iTypeFail = 2;
			}
            break;
        case 7:
            strTemp.Format("%.0f",LEDdata.m_ColorData.m_fTc);
            bQualified = data.IsQulified(iID,LEDdata.m_ColorData.m_fTc);
			if (!bQualified)
			{
				iTypeFail = 4;
			}
            break;
		case 8:
            strTemp.Format("%.4f",LEDdata.m_ColorData.m_fCIEx);
            bQualified = data.IsQulified(iID,LEDdata.m_ColorData.m_fCIEx);
			if (!bQualified)
			{
				iTypeFail = 4;
			}
            break;
        case 9:
            strTemp.Format("%.4f",LEDdata.m_ColorData.m_fCIEy);
            bQualified = data.IsQulified(iID,LEDdata.m_ColorData.m_fCIEy);
			if (!bQualified)
			{
				iTypeFail = 4;
			}
            break;
        case 10:
            strTemp.Format("%.4f",LEDdata.m_ColorData.m_fCIEu_);
            bQualified = data.IsQulified(iID,LEDdata.m_ColorData.m_fCIEu_);
			if (!bQualified)
			{
				iTypeFail = 4;
			}
            break;
        case 11:
            strTemp.Format("%.4f",LEDdata.m_ColorData.m_fCIEv_);
            bQualified = data.IsQulified(iID,LEDdata.m_ColorData.m_fCIEv_);
			if (!bQualified)
			{
				iTypeFail = 4;
			}
            break;
        case 12:
            strTemp.Format("%.1f",LEDdata.m_ColorData.m_fLd);
            bQualified = data.IsQulified(iID,LEDdata.m_ColorData.m_fLd);
			if (!bQualified)
			{
				iTypeFail = 4;
			}
            break;
        case 13:
            strTemp.Format("%.1f",LEDdata.m_ColorData.m_fHW);
            bQualified = data.IsQulified(iID,LEDdata.m_ColorData.m_fHW);
			if (!bQualified)
			{
				iTypeFail = 4;
			}
            break;
        case 14:
            strTemp.Format("%.1f",LEDdata.m_ColorData.m_fLp);
            bQualified = data.IsQulified(iID,LEDdata.m_ColorData.m_fLp);
			if (!bQualified)
			{
				iTypeFail = 4;
			}
            break;
        case 15:
            strTemp.Format("%.0f",LEDdata.m_ColorData.m_fIp);
			if (!bQualified)
			{
				iTypeFail = 4;
			}
           break;
        case 16:
            strTemp.Format("%.1f",LEDdata.m_ColorData.m_fPur);
            bQualified = data.IsQulified(iID,LEDdata.m_ColorData.m_fPur);
			if (!bQualified)
			{
				iTypeFail = 4;
			}
          break;
        case 17:
            strTemp.Format("%.1f",LEDdata.m_ColorData.m_fRa);
            bQualified = data.IsQulified(iID,LEDdata.m_ColorData.m_fRa);
			if (!bQualified)
			{
				iTypeFail = 4;
			}
          break;
        case 18:
			if (LEDdata.m_fPowerW < 0.01f)
			{
				strTemp = "----";
			}
			else
			{
				float fEff;
				fEff =LEDdata.m_ColorData.m_fPh /LEDdata.m_fPowerW;
				strTemp.Format("%.1f", fEff);
				bQualified = data.IsQulified(iID, fEff);
				if (!bQualified)
				{
					iTypeFail = 4;
				}
			}
			break;
		case 19:
            strTemp.Format("%.1f",LEDdata.m_ColorData.m_fRi[0]);
            bQualified = data.IsQulified(iID,LEDdata.m_ColorData.m_fRi[0]);
			if (!bQualified)
			{
				iTypeFail = 4;
			}
            break;
        case 20:
            strTemp.Format("%.1f",LEDdata.m_ColorData.m_fRi[1]);
            bQualified = data.IsQulified(iID,LEDdata.m_ColorData.m_fRi[1]);
			if (!bQualified)
			{
				iTypeFail = 4;
			}
           break;
        case 21:
            strTemp.Format("%.1f",LEDdata.m_ColorData.m_fRi[2]);
            bQualified = data.IsQulified(iID,LEDdata.m_ColorData.m_fRi[2]);
			if (!bQualified)
			{
				iTypeFail = 4;
			}
           break;
        case 22:
            strTemp.Format("%.1f",LEDdata.m_ColorData.m_fRi[3]);
            bQualified = data.IsQulified(iID,LEDdata.m_ColorData.m_fRi[3]);
			if (!bQualified)
			{
				iTypeFail = 4;
			}
			break;
        case 23:
            strTemp.Format("%.1f",LEDdata.m_ColorData.m_fRi[4]);
            bQualified = data.IsQulified(iID,LEDdata.m_ColorData.m_fRi[4]);
			if (!bQualified)
			{
				iTypeFail = 4;
			}
			break;
       case 24:
            strTemp.Format("%.1f",LEDdata.m_ColorData.m_fRi[5]);
            bQualified = data.IsQulified(iID,LEDdata.m_ColorData.m_fRi[5]);
			if (!bQualified)
			{
				iTypeFail = 4;
			}
            break;
        case 25:
            strTemp.Format("%.1f",LEDdata.m_ColorData.m_fRi[6]);
            bQualified = data.IsQulified(iID,LEDdata.m_ColorData.m_fRi[6]);
			if (!bQualified)
			{
				iTypeFail = 4;
			}
	        break;
        case 26:
            strTemp.Format("%.1f",LEDdata.m_ColorData.m_fRi[7]);
            bQualified = data.IsQulified(iID,LEDdata.m_ColorData.m_fRi[7]);
			if (!bQualified)
			{
				iTypeFail = 4;
			}
	        break;
        case 27:
            strTemp.Format("%.1f",LEDdata.m_ColorData.m_fRi[8]);
            bQualified = data.IsQulified(iID,LEDdata.m_ColorData.m_fRi[8]);
			if (!bQualified)
			{
				iTypeFail = 4;
			}
            break;
        case 28:
            strTemp.Format("%.1f",LEDdata.m_ColorData.m_fRR);
            bQualified = data.IsQulified(iID,LEDdata.m_ColorData.m_fRR);
			if (!bQualified)
			{
				iTypeFail = 4;
			}
            break;
        case 29:
            strTemp.Format("%.1f",LEDdata.m_ColorData.m_fGR);
            bQualified = data.IsQulified(iID,LEDdata.m_ColorData.m_fGR);
			if (!bQualified)
			{
				iTypeFail = 4;
			}
            break;
        case 30:
            strTemp.Format("%.1f",LEDdata.m_ColorData.m_fBR);
            bQualified = data.IsQulified(iID,LEDdata.m_ColorData.m_fBR);
			if (!bQualified)
			{
				iTypeFail = 4;
			}
            break;
		case 31:
			if (LEDdata.m_bHaveTestSaft)
			{
				if(g_pDoc->m_CommSettingsData.m_bHaveSaft_JYDZ)
				{
					if(LEDdata.m_fSaft_R >= LEDdata.m_fSaftLimit_R )
						bOK = TRUE;
					else
						bOK = FALSE;
					sTemp.Format("IR:%.0fMΩ,",LEDdata.m_fSaft_R);
					sStr = sStr + sTemp;
				}

				if (g_pDoc->m_CommSettingsData.m_bHaveSaft_NYY)
				{
					sTemp.Format("耐压:%.3fmA,",LEDdata.m_fSaft_V);
					sStr = sStr + sTemp;
					if(bOK)
					{
						if(LEDdata.m_fSaft_V <= LEDdata.m_fSaftLimit_V )
							bOK = TRUE;
						else
							bOK = FALSE;
					}
				}

				if (g_pDoc->m_CommSettingsData.m_bHaveSaft_XLDL)
				{
					sTemp.Format("LC:%.3fmA",LEDdata.m_fSaft_C);
					sStr = sStr + sTemp;
					if(bOK)
					{
						if(LEDdata.m_fSaft_C <= LEDdata.m_fSaftLimit_C )
							bOK = TRUE;
						else
							bOK = FALSE;
					}
				}
				if(bOK)
					strTemp = "合格(" + sStr + ")";
				else
					strTemp = "不合格(" + sStr + ")";
			}
			else
			{
				strTemp = "----";
			}
			bQualified = TRUE;
			break;
        default:
            break;
      }
    }
    else
    {
        switch(iID)
        {
        case 0:
            strTemp.Format("%.1f", LEDdata.m_fCurrentA * 1000);
            break;
        case 1:
            strTemp.Format("%.1f", LEDdata.m_fVoltageV);
            break;
        case 2:
            strTemp.Format("%.0f", LEDdata.m_fFrequencyHz);
            break;
        case 3:
            strTemp.Format("%.2f", LEDdata.m_fPowerW);
            break;
		case 4:
			strTemp.Format("%.2f", LEDdata.m_fPowerFactor);
			break;
		case 15:
			strTemp.Format("%.0f", LEDdata.m_ColorData.m_fIp);
			break;
        default:
            strTemp = "----";
            break;
        }
    }
    return strTemp;
}


CString CLEDDataContainer::GetVirtualItemText(int iRow, int iCol, CTestSettingsData & data, BOOL &bQualified, int &iTypeFail)
{
    int iDataIndex = iRow - 1;
    if (iDataIndex >= m_data.GetSize())
    {
        return "";
    }
    bQualified = TRUE;

    // Row header
    if (0 == iRow && iCol < m_DisPlayID.GetSize() + 7)
    {
        CString strTemp[7] = {"序号", "测试时间", "LED", "LED型号", "LED编号", "是否合格", 
            "区域"};
        if (iCol < 7)
        {
            return strTemp[iCol];
        }
        else
        {
            return g_strListParaName[m_DisPlayID.GetAt(iCol - 7)];
        }
    }

    // Data
    CString strTemp;
    if (m_data[iDataIndex].IsLEDON())
    {
        if (iCol < 7)
        {
            switch(iCol)
            {
            case 0:
                strTemp.Format("%d", iRow);
                break;
            case 1:
                if (IsBoundaryData(iDataIndex))
                {
                    strTemp = GetLEDTestTimeString(iDataIndex);
                }
                break;
            case 2:
                strTemp.Format("[%d]", m_LedIndex[iDataIndex].iColumn + 1);
                break;
            case 3:
                strTemp.Format("%s", m_data[iDataIndex].m_strLedModel);
                break;
            case 4:
                if (g_pDoc->m_CommSettingsData.m_bHaveScaner)
                {
                    strTemp = m_data[iDataIndex].m_strSN;
                }    
                else
                {
                    strTemp.Format("%d", m_data[iDataIndex].m_ulID);
                }
                break;
            case 5:
                strTemp = g_pDoc->m_dataContainer.GetTestSettingData().IsQulified(m_data[iDataIndex],iTypeFail) ? "合格" : "不合格";
                break;
            case 6:
                strTemp = "";
                if (m_data[iDataIndex].m_ColorData.m_bHaveColorData)
                {
                    float fx = m_data[iDataIndex].m_ColorData.m_fCIEx;
                    float fy = m_data[iDataIndex].m_ColorData.m_fCIEy;
                    int iRegionIndex[64];
                    int iRegionCount = 64;
                    if (Region_IsInAnyRegion(fx, fy, iRegionIndex, iRegionCount))
                    {
                        char strName[256];
                        for (int iR = 0; iR < iRegionCount; iR++)
                        {
                            Region_GetRegionName(iRegionIndex[iR], strName, 256);
                            strTemp += strName;
                            if (iR < iRegionCount - 1)
                            {
                                strTemp += ";";
                            }
                        }
                    }
                }
                break;

            default:
                break;
            }
        }
        else
        {
            strTemp = GetParaText(m_DisPlayID.GetAt(iCol - 7), data, m_data[iDataIndex], bQualified,iTypeFail);
        } 
    }
    else
    {
        if (iCol < 7)
        {
            switch(iCol)
            {
            case 0:
                strTemp.Format("%d", iRow);
                break;
            case 1:
                if (IsBoundaryData(iDataIndex))
                {
                    strTemp = GetLEDTestTimeString(iDataIndex);
                }
                break;
            case 2:
                strTemp.Format("[%d]", m_LedIndex[iDataIndex].iColumn + 1);
                break;
            case 3:
                strTemp.Format("%s", m_data[iDataIndex].m_strLedModel);
                break;
            case 4:
                if (g_pDoc->m_CommSettingsData.m_bHaveScaner)
                {
                    strTemp = m_data[iDataIndex].m_strSN;
                }    
                else
                {
                    strTemp.Format("%d", m_data[iDataIndex].m_ulID);
                }
                break;
            case 5:
                strTemp =  "不合格";
                break;
			case 6:
				strTemp =  "----";
				break;
            default:
                strTemp = "----";
                break;
            }
        }
        else
        {
            strTemp = GetParaText(m_DisPlayID.GetAt(iCol - 7), data, m_data[iDataIndex], bQualified,iTypeFail);
        }
    }

    return strTemp;
}

void CLEDDataContainer::ListData(C_Grid & grid)
{
	if (!IsWindow(grid.GetSafeHwnd()))
	{
		return;
	}

	//m_grid.SetAutoRedraw(FALSE);

	grid.SetCols(m_DisPlayID.GetSize() + 7);
	grid.SetFixedCols(1);
	grid.Column(1).SetWidth(150);
	grid.Column(1).SetCellType(5);
	grid.Column(38).SetWidth(250);
	grid.SetRows(m_data.GetSize() + 1);
	grid.ShowWindow(SW_SHOW);
	return;
}


void CLEDDataContainer::ListDataAddEnd(C_Grid & grid)
{
}


