#pragma once

// 计算机生成了由 Microsoft Visual C++ 创建的 IDispatch 包装类

// 注意: 不要修改此文件的内容。如果此类由
//  Microsoft Visual C++ 重新生成，您的修改将被覆盖。

/////////////////////////////////////////////////////////////////////////////
// CIeditx_tmp1 包装类

class CIeditx_tmp1 : public CWnd
{
protected:
	DECLARE_DYNCREATE(CIeditx_tmp1)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x27E1C61A, 0x7770, 0x4D80, { 0x93, 0x2A, 0x93, 0xB7, 0xFC, 0x45, 0x0, 0x8C } };
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
enum
{
    iahCenter = 0,
    iahLeft = 1,
    iahRight = 2
}TxiAlignmentHorizontal;
enum
{
    ibsNone = 0,
    ibsRaised = 1,
    ibsLowered = 2
}TxiBevelStyle;
enum
{
    mbLeft = 0,
    mbRight = 1,
    mbMiddle = 2
}TxMouseButton;
enum
{
    taLeftJustify = 0,
    taRightJustify = 1,
    taCenter = 2
}TxAlignment;
enum
{
    bdLeftToRight = 0,
    bdRightToLeft = 1,
    bdRightToLeftNoAlign = 2,
    bdRightToLeftReadingOnly = 3
}TxBiDiMode;
enum
{
    ikisDotLowered = 0,
    ikisDotRaised = 1,
    ikisDot = 2,
    ikisLineCenter = 3,
    ikisLineCustom = 4,
    ikisTriangle = 5
}TxiKnobIndicatorStyle;
enum
{
    iksRaisedEdge = 0,
    iksRaised = 1,
    iksSunken = 2,
    iksSunkenEdge = 3
}TxiKnobStyle;
enum
{
    itmnaInside = 0,
    itmnaCenter = 1,
    itmnaOutside = 2
}TxiTickMinorAlignment;
enum
{
    iavCenter = 0,
    iavTop = 1,
    iavBottom = 2
}TxiAlignmentVertical;
enum
{
    iagpsArrowLine = 0,
    iagpsArrow = 1,
    iagpsLine = 2,
    iagpsTriangle = 3
}TxiAngularGaugePointerStyle;
enum
{
    ioVertical = 0,
    ioHorizontal = 1
}TxiOrientation;
enum
{
    iosBottomRight = 0,
    iosTopLeft = 1
}TxiOrientationSide;
enum
{
    ilgpsPointer = 0,
    ilgpsTriangle = 1,
    ilgpsTLine = 2,
    ilgpsColorBar = 3
}TxiLinearGaugePointerStyle;
enum
{
    ispsLed = 0,
    ispsPointer = 1,
    ispsBar = 2,
    ispsLightBar = 3,
    ispsBarColor = 4,
    ispsBitmap = 5
}TxiSliderPointerStyle;
enum
{
    istsBox = 0,
    istsLine = 1,
    istsBevelLowered = 2,
    istsBevelRasied = 3
}TxiSliderTrackStyle;
enum
{
    idUp = 0,
    idDown = 1,
    idRight = 2,
    idLeft = 3
}TxiDirection;
enum
{
    ilbssRectangle = 0,
    ilbssCircle = 1,
    ilbssTriangle = 2
}TxiLedBarSegmentStyle;
enum
{
    ilsNone = 0,
    ilsZeros = 1,
    ilsSpaces = 2
}TxiLeadingStyle;
enum
{
    ifdTopBottom = 0,
    ifdBottomTop = 1,
    ifdLeftRight = 2,
    ifdRightLeft = 3,
    ifdTopLeftBottomRight = 4,
    ifdBottomRightTopLeft = 5,
    ifdBottomLeftTopRight = 6,
    ifdTopRightBottomLeft = 7,
    ifdRectangleOut = 8,
    ifdRectangleIn = 9,
    ifdCircleOut = 10,
    ifdCircleIn = 11
}TxiFillDirection;
enum
{
    ifisNone = 0,
    ifisAuto = 1
}TxiFilterInputStyle;
enum
{
    ipsSignificantDigits = 0,
    ipsFixedDecimalPoints = 1
}TxiPrecisionStyle;
enum
{
    iassAutoMinMax = 0,
    iassFixedMinMax = 1
}TxiAutoScaleStyle;
enum
{
    itisBulb = 0,
    itisBar = 1,
    itisBarSunken = 2,
    itisBarRaised = 3
}TxiThermometerIndicatorStyle;
enum
{
    ismcsSlideOnly = 0,
    ismcsSlidePage = 1,
    ismcsGoto = 2
}TxiSliderMouseControlStyle;
enum
{
    ilaCenter = 0,
    ilaJustified = 1
}TxiLabelAlignment;
enum
{
    ilbsNone = 0,
    ilbsSingle = 1,
    ilbsLowered = 2,
    ilbsRaised = 3
}TxiLabelBorderStyle;
enum
{
    ilssProgress = 0,
    ilssPointer = 1
}TxiLedSpiralStyle;
enum
{
    ipfrsMin = 0,
    ipfrsMax = 1,
    ipfrsValue = 2
}TxiPointerFillReferenceStyle;
enum
{
    htKeyword = 0,
    htContext = 1
}TxHelpType;


// 操作
public:

// IiEditX

// Functions
//

	void SetValueNoEvent(LPCTSTR Value)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Value);
	}
	void Lock()
	{
		InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Unlock()
	{
		InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void SavePropertiesToFile(LPCTSTR FileName)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FileName);
	}
	void LoadPropertiesFromFile(LPCTSTR FileName)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FileName);
	}
	long OPCAddItem()
	{
		long result;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long OPCItemCount()
	{
		long result;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void OPCRemoveAllItems()
	{
		InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void OPCItemActivate(long Index)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Index);
	}
	void OPCItemActivateSend(long Index)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Index);
	}
	void OPCItemDeactivate(long Index)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Index);
	}
	void OPCItemLoaded(long Index)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Index);
	}
	CString GetOPCItemComputerName(long Index)
	{
		CString result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xd, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, Index);
		return result;
	}
	CString GetOPCItemServerName(long Index)
	{
		CString result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xe, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, Index);
		return result;
	}
	CString GetOPCItemItemName(long Index)
	{
		CString result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xf, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, Index);
		return result;
	}
	CString GetOPCItemPropertyName(long Index)
	{
		CString result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x10, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, Index);
		return result;
	}
	BOOL GetOPCItemAutoConnect(long Index)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x11, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Index);
		return result;
	}
	long GetOPCItemUpdateRate(long Index)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x12, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Index);
		return result;
	}
	void SetOPCItemComputerName(long Index, LPCTSTR Value)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR ;
		InvokeHelper(0x13, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Index, Value);
	}
	void SetOPCItemServerName(long Index, LPCTSTR Value)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR ;
		InvokeHelper(0x14, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Index, Value);
	}
	void SetOPCItemItemName(long Index, LPCTSTR Value)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR ;
		InvokeHelper(0x15, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Index, Value);
	}
	void SetOPCItemPropertyName(long Index, LPCTSTR Value)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR ;
		InvokeHelper(0x16, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Index, Value);
	}
	void SetOPCItemAutoConnect(long Index, BOOL Value)
	{
		static BYTE parms[] = VTS_I4 VTS_BOOL ;
		InvokeHelper(0x17, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Index, Value);
	}
	void SetOPCItemUpdateRate(long Index, long Value)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x18, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Index, Value);
	}
	CString get_Value()
	{
		CString result;
		InvokeHelper(0x19, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_Value(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x19, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_Alignment()
	{
		long result;
		InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Alignment(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_AutoSelect()
	{
		BOOL result;
		InvokeHelper(0x1b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_AutoSelect(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x1b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	unsigned long get_Color()
	{
		unsigned long result;
		InvokeHelper(DISPID_BACKCOLOR, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, NULL);
		return result;
	}
	void put_Color(unsigned long newValue)
	{
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(DISPID_BACKCOLOR, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_Enabled()
	{
		BOOL result;
		InvokeHelper(DISPID_ENABLED, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_Enabled(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(DISPID_ENABLED, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_Font()
	{
		LPDISPATCH result;
		InvokeHelper(DISPID_FONT, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void put_Font(LPDISPATCH newValue)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(DISPID_FONT, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void putref_Font(LPDISPATCH * newValue)
	{
		static BYTE parms[] = VTS_PDISPATCH ;
		InvokeHelper(DISPID_FONT, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms, newValue);
	}
	long get_MaxLength()
	{
		long result;
		InvokeHelper(0x1c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_MaxLength(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_Visible()
	{
		BOOL result;
		InvokeHelper(0x1d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_Visible(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x1d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_OptionSaveAllProperties()
	{
		BOOL result;
		InvokeHelper(0x21, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_OptionSaveAllProperties(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x21, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void Clear()
	{
		InvokeHelper(0x23, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void ClearSelection()
	{
		InvokeHelper(0x24, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void CopyToClipboard()
	{
		InvokeHelper(0x25, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void CutToClipboard()
	{
		InvokeHelper(0x26, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void PasteFromClipboard()
	{
		InvokeHelper(0x27, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Undo()
	{
		InvokeHelper(0x28, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void ClearUndo()
	{
		InvokeHelper(0x29, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void SelectAll()
	{
		InvokeHelper(0x2b, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	BOOL get_CanUndo()
	{
		BOOL result;
		InvokeHelper(0x2d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	BOOL get_Modified()
	{
		BOOL result;
		InvokeHelper(0x2e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_Modified(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x2e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void AboutBox()
	{
		InvokeHelper(DISPID_ABOUTBOX, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	long GetObjectPointer()
	{
		long result;
		InvokeHelper(0x1068, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	unsigned long get_FontColor()
	{
		unsigned long result;
		InvokeHelper(0x1e, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, NULL);
		return result;
	}
	void put_FontColor(unsigned long newValue)
	{
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x1e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_Width()
	{
		long result;
		InvokeHelper(0x1f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Width(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_Height()
	{
		long result;
		InvokeHelper(0x20, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Height(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x20, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void OPCItemUpdateResume(long Index)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1013, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Index);
	}
	void OPCItemUpdateSuspend(long Index)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1014, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Index);
	}
	VARIANT GetOPCItemData(long Index)
	{
		VARIANT result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1015, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, Index);
		return result;
	}
	short GetOPCItemQuality(long Index)
	{
		short result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1016, DISPATCH_METHOD, VT_I2, (void*)&result, parms, Index);
		return result;
	}
	double GetOPCItemTimeStamp(long Index)
	{
		double result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1017, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Index);
		return result;
	}
	void SetOPCItemData(long Index, VARIANT Value)
	{
		static BYTE parms[] = VTS_I4 VTS_VARIANT ;
		InvokeHelper(0x1018, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Index, &Value);
	}
	BOOL get_ErrorActive()
	{
		BOOL result;
		InvokeHelper(0x2f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_ErrorActive(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x2f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_ErrorText()
	{
		CString result;
		InvokeHelper(0x30, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_ErrorText(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x30, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_ErrorFont()
	{
		LPDISPATCH result;
		InvokeHelper(0x31, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void put_ErrorFont(LPDISPATCH newValue)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x31, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	unsigned long get_ErrorFontColor()
	{
		unsigned long result;
		InvokeHelper(0x32, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, NULL);
		return result;
	}
	void put_ErrorFontColor(unsigned long newValue)
	{
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x32, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	unsigned long get_ErrorBackGroundColor()
	{
		unsigned long result;
		InvokeHelper(0x33, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, NULL);
		return result;
	}
	void put_ErrorBackGroundColor(unsigned long newValue)
	{
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x33, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL GetOPCItemActive(long Index)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1019, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Index);
		return result;
	}
	BOOL GetOPCItemAutoError(long Index)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x101a, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Index);
		return result;
	}
	void SetOPCItemAutoError(long Index, BOOL Value)
	{
		static BYTE parms[] = VTS_I4 VTS_BOOL ;
		InvokeHelper(0x101b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Index, Value);
	}
	long get_AlignmentMargin()
	{
		long result;
		InvokeHelper(0x22, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_AlignmentMargin(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x22, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_AutoFrameRate()
	{
		BOOL result;
		InvokeHelper(0x2a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_AutoFrameRate(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x2a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_UpdateFrameRate()
	{
		long result;
		InvokeHelper(0x2c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_UpdateFrameRate(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x2c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_BorderStyle()
	{
		long result;
		InvokeHelper(0x34, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_BorderStyle(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x34, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void Apply()
	{
		InvokeHelper(0x35, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void BeginUpdate()
	{
		InvokeHelper(0x36, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void EndUpdate()
	{
		InvokeHelper(0x37, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void RepaintAll()
	{
		InvokeHelper(0x38, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	VARIANT GetBytesJPEG(long Compression, BOOL Progressive)
	{
		VARIANT result;
		static BYTE parms[] = VTS_I4 VTS_BOOL ;
		InvokeHelper(0x1069, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, Compression, Progressive);
		return result;
	}
	void SaveImageToBitmap(LPCTSTR FileName)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x56, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FileName);
	}
	void SaveImageToMetaFile(LPCTSTR FileName)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x57, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FileName);
	}
	void SaveImageToJPEG(LPCTSTR FileName, long Compression, BOOL Progressive)
	{
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_BOOL ;
		InvokeHelper(0x58, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FileName, Compression, Progressive);
	}
	void iPaintToDC(long X, long Y, BOOL Transparent, long DC)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_BOOL VTS_I4 ;
		InvokeHelper(0x10cc, DISPATCH_METHOD, VT_EMPTY, NULL, parms, X, Y, Transparent, DC);
	}
	long get_SelLength()
	{
		long result;
		InvokeHelper(0x39, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_SelLength(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x39, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_SelStart()
	{
		long result;
		InvokeHelper(0x3a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_SelStart(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x3a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_SelText()
	{
		CString result;
		InvokeHelper(0x3b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_SelText(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x3b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_PasswordChar()
	{
		CString result;
		InvokeHelper(0x3c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_PasswordChar(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x3c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_AutoSize()
	{
		BOOL result;
		InvokeHelper(0x3d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_AutoSize(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x3d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString GetOPCItemGroupName(long Index)
	{
		CString result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x101c, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, Index);
		return result;
	}
	void SetOPCItemGroupName(long Index, LPCTSTR Value)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR ;
		InvokeHelper(0x101d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Index, Value);
	}
	void OPCDeleteItem(long Index)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x101e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Index);
	}
	void OPCItemActivateSuspend(long Index)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x101f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Index);
	}
	VARIANT GetBytesPNG(long Compression)
	{
		VARIANT result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1020, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, Compression);
		return result;
	}
	void SaveImageToPNG(LPCTSTR FileName, long Compression)
	{
		static BYTE parms[] = VTS_BSTR VTS_I4 ;
		InvokeHelper(0x1021, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FileName, Compression);
	}

// Properties
//



};
