#pragma once

// 计算机生成了由 Microsoft Visual C++ 创建的 IDispatch 包装类

// 注意: 不要修改此文件的内容。如果此类由
//  Microsoft Visual C++ 重新生成，您的修改将被覆盖。

/////////////////////////////////////////////////////////////////////////////
// CAxciexyzctrl1 包装类

class CAxciexyzctrl1 : public CWnd
{
protected:
	DECLARE_DYNCREATE(CAxciexyzctrl1)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x593CF92C, 0xF3C3, 0x4EBB, { 0xB0, 0x94, 0xFA, 0xEE, 0x9B, 0xB2, 0x7D, 0x46 } };
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

// _DAX_CIE_XYZ

// Functions
//

	void Draw()
	{
		InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void CopyBMP()
	{
		InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Print()
	{
		InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void AboutBox()
	{
		InvokeHelper(DISPID_ABOUTBOX, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}

// Properties
//

short GetCIEType()
{
	short result;
	GetProperty(0x1, VT_I2, (void*)&result);
	return result;
}
void SetCIEType(short propVal)
{
	SetProperty(0x1, VT_I2, propVal);
}
BOOL GetShowBBC()
{
	BOOL result;
	GetProperty(0x2, VT_BOOL, (void*)&result);
	return result;
}
void SetShowBBC(BOOL propVal)
{
	SetProperty(0x2, VT_BOOL, propVal);
}
BOOL GetbShowXY()
{
	BOOL result;
	GetProperty(0x3, VT_BOOL, (void*)&result);
	return result;
}
void SetbShowXY(BOOL propVal)
{
	SetProperty(0x3, VT_BOOL, propVal);
}
float Getx()
{
	float result;
	GetProperty(0x4, VT_R4, (void*)&result);
	return result;
}
void Setx(float propVal)
{
	SetProperty(0x4, VT_R4, propVal);
}
float Gety()
{
	float result;
	GetProperty(0x5, VT_R4, (void*)&result);
	return result;
}
void Sety(float propVal)
{
	SetProperty(0x5, VT_R4, propVal);
}
BOOL GetbShowXYValue()
{
	BOOL result;
	GetProperty(0x6, VT_BOOL, (void*)&result);
	return result;
}
void SetbShowXYValue(BOOL propVal)
{
	SetProperty(0x6, VT_BOOL, propVal);
}
CString GetszPath()
{
	CString result;
	GetProperty(0x7, VT_BSTR, (void*)&result);
	return result;
}
void SetszPath(CString propVal)
{
	SetProperty(0x7, VT_BSTR, propVal);
}
CString GetPASSWORD()
{
	CString result;
	GetProperty(0x8, VT_BSTR, (void*)&result);
	return result;
}
void SetPASSWORD(CString propVal)
{
	SetProperty(0x8, VT_BSTR, propVal);
}
CString GetTitle()
{
	CString result;
	GetProperty(0x9, VT_BSTR, (void*)&result);
	return result;
}
void SetTitle(CString propVal)
{
	SetProperty(0x9, VT_BSTR, propVal);
}


};
