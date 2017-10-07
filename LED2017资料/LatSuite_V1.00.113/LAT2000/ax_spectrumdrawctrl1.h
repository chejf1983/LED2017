#pragma once
#include "_Font.h"

// 计算机生成了由 Microsoft Visual C++ 创建的 IDispatch 包装类

// 注意: 不要修改此文件的内容。如果此类由
//  Microsoft Visual C++ 重新生成，您的修改将被覆盖。

/////////////////////////////////////////////////////////////////////////////
// CAx_spectrumdrawctrl1 包装类

class CAx_spectrumdrawctrl1 : public CWnd
{
protected:
	DECLARE_DYNCREATE(CAx_spectrumdrawctrl1)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x62F184CF, 0xF518, 0x4589, { 0xA2, 0xC9, 0xFB, 0x4D, 0xD2, 0xE9, 0x9E, 0xD7 } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
						const RECT& rect, CWnd* pParentWnd, UINT nID, 
						CCreateContext* pContext = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); 
	}

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, 
				UINT nID, CFile* pPersist = NULL, BOOL bStorage = FALSE,
				BSTR bstrLicKey = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); 
	}

// 特性
public:


// 操作
public:

// _DAX_SpectrumDraw

// Functions
//

	void AboutBox()
	{
		InvokeHelper(DISPID_ABOUTBOX, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void SetSpectDrawPara(float * pfWaveLength, float * pfSpectrum, long iNum, float fInterVal)
	{
		static BYTE parms[] = VTS_PR4 VTS_PR4 VTS_I4 VTS_R4 ;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, parms, pfWaveLength, pfSpectrum, iNum, fInterVal);
	}
	void Draw()
	{
		InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void CopyBMP()
	{
		InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Print()
	{
		InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void ClearAllData()
	{
		InvokeHelper(0x18, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}

// Properties
//

BOOL GetDrawType()
{
	BOOL result;
	GetProperty(0x1, VT_BOOL, (void*)&result);
	return result;
}
void SetDrawType(BOOL propVal)
{
	SetProperty(0x1, VT_BOOL, propVal);
}
CString GetPASSWORD()
{
	CString result;
	GetProperty(0x4, VT_BSTR, (void*)&result);
	return result;
}
void SetPASSWORD(CString propVal)
{
	SetProperty(0x4, VT_BSTR, propVal);
}
unsigned long GetBKColor()
{
	unsigned long result;
	GetProperty(0x9, VT_UI4, (void*)&result);
	return result;
}
void SetBKColor(unsigned long propVal)
{
	SetProperty(0x9, VT_UI4, propVal);
}
CString GetTitle()
{
	CString result;
	GetProperty(0xa, VT_BSTR, (void*)&result);
	return result;
}
void SetTitle(CString propVal)
{
	SetProperty(0xa, VT_BSTR, propVal);
}
unsigned long GetTitleFontColor()
{
	unsigned long result;
	GetProperty(0xb, VT_UI4, (void*)&result);
	return result;
}
void SetTitleFontColor(unsigned long propVal)
{
	SetProperty(0xb, VT_UI4, propVal);
}
CString GetXAxesTitle()
{
	CString result;
	GetProperty(0xc, VT_BSTR, (void*)&result);
	return result;
}
void SetXAxesTitle(CString propVal)
{
	SetProperty(0xc, VT_BSTR, propVal);
}
unsigned long GetXAxesFontColor()
{
	unsigned long result;
	GetProperty(0xd, VT_UI4, (void*)&result);
	return result;
}
void SetXAxesFontColor(unsigned long propVal)
{
	SetProperty(0xd, VT_UI4, propVal);
}
CString GetYAxesTitle()
{
	CString result;
	GetProperty(0xe, VT_BSTR, (void*)&result);
	return result;
}
void SetYAxesTitle(CString propVal)
{
	SetProperty(0xe, VT_BSTR, propVal);
}
unsigned long GetYAxesFontColor()
{
	unsigned long result;
	GetProperty(0xf, VT_UI4, (void*)&result);
	return result;
}
void SetYAxesFontColor(unsigned long propVal)
{
	SetProperty(0xf, VT_UI4, propVal);
}
COleFont GetTitleFont()
{
	LPDISPATCH result;
	GetProperty(0x10, VT_DISPATCH, (void*)&result);
	return COleFont(result);
}
void SetTitleFont(LPDISPATCH propVal)
{
	SetProperty(0x10, VT_DISPATCH, propVal);
}
COleFont GetXAxesFont()
{
	LPDISPATCH result;
	GetProperty(0x11, VT_DISPATCH, (void*)&result);
	return COleFont(result);
}
void SetXAxesFont(LPDISPATCH propVal)
{
	SetProperty(0x11, VT_DISPATCH, propVal);
}
COleFont GetYAxesFont()
{
	LPDISPATCH result;
	GetProperty(0x12, VT_DISPATCH, (void*)&result);
	return COleFont(result);
}
void SetYAxesFont(LPDISPATCH propVal)
{
	SetProperty(0x12, VT_DISPATCH, propVal);
}
unsigned long GetXAxesLabelColor()
{
	unsigned long result;
	GetProperty(0x13, VT_UI4, (void*)&result);
	return result;
}
void SetXAxesLabelColor(unsigned long propVal)
{
	SetProperty(0x13, VT_UI4, propVal);
}
unsigned long GetYAxesLabelColor()
{
	unsigned long result;
	GetProperty(0x14, VT_UI4, (void*)&result);
	return result;
}
void SetYAxesLabelColor(unsigned long propVal)
{
	SetProperty(0x14, VT_UI4, propVal);
}
float GetWaveLengthStart()
{
	float result;
	GetProperty(0x15, VT_R4, (void*)&result);
	return result;
}
void SetWaveLengthStart(float propVal)
{
	SetProperty(0x15, VT_R4, propVal);
}
float GetWaveLengthEnd()
{
	float result;
	GetProperty(0x16, VT_R4, (void*)&result);
	return result;
}
void SetWaveLengthEnd(float propVal)
{
	SetProperty(0x16, VT_R4, propVal);
}
BOOL GetCursor()
{
	BOOL result;
	GetProperty(0x17, VT_BOOL, (void*)&result);
	return result;
}
void SetCursor(BOOL propVal)
{
	SetProperty(0x17, VT_BOOL, propVal);
}


};
