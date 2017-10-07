#pragma once
#include "LedData.h"
#include "_grid.h"
#include "TestSettingsData.h"
#include "TestInfoData.h"
#include "TestSettingsData.h"
#define  DISTRIBUTION_NUM 6


class CLEDDataContainer
{
public:
	CLEDDataContainer(void);
	~CLEDDataContainer(void);
    friend class CHistogramGraphCtrl;

public:
 
	// Should be called before data test at a new time is going to be added to the container
	void SetTestTime(CTime tTime);

	void RemoveAllData();

	BOOL InsertData(int iRow, int iCol, CLedData & data);

	CLedData & GetAt(int iIndex);

	BOOL GetLEDRowColumn(int iIndex, int & iRow, int & iCol);

	int  GetSize();

    int GetDisplayParaNum();

    CString GetParaText(int iID, CTestSettingsData & data, CLedData &LEDdata, BOOL &bQualified,int &iTypeFail);

	void ListData(C_Grid & grid);

	void ListDataAddEnd(C_Grid & grid);

	BOOL DeleteDataTestAtTime(int iDataIndex);

	int GetDataNumberTestAtTime(int iDataIndex);

	CString GetLEDTestTimeString(int iIndex);

	CTime GetLEDTestTime(int iIndex);

	BOOL IsBoundaryData(int iIndex);

	BOOL SaveFile(CString strPathName);
	
	BOOL LoadFile(CString strPathName);

	BOOL Serialize(CArchive & ar);
	
	CString GetVirtualItemText(int iRow, int iCol, CTestSettingsData & data, BOOL & bQualified,int &iTypeFail);

    CTestInfoData & GetTestInfoData()
    {
        return m_TestInfoData;
    }

	CTestSettingsData &	GetTestSettingData()
	{
		return m_TestSetData;
	}
    CLEDDataContainer &operator = (CLEDDataContainer &data);
 
private:
    CTestInfoData m_TestInfoData;
	CTestSettingsData m_TestSetData;
    CArray<int, int>m_DisPlayID;
    struct LEDIndex
	{
		int iRow;
		int iColumn;

		LEDIndex()
		{
			iRow = 0;
			iColumn = 0;
		}

		void Serialize(CArchive & ar)
		{
			if (ar.IsStoring())
			{
				ar<<iRow;
				ar<<iColumn;
			}
			else
			{
				ar>>iRow;
				ar>>iColumn;
			}
		}
	};
	
	CArray<int, int> m_iTN;				// Stores the count if data when a new time is added
	CArray<CTime, CTime &> m_tTime;		// One data count with one index
	
	CArray<CLedData, CLedData &> m_data;
	CArray<LEDIndex, LEDIndex &> m_LedIndex;		// One data with one index
public:

//#define MAX_COLUMN_NUMBER	32
//	CArray<CString, CString &> m_strVirtual[MAX_COLUMN_NUMBER];
};

