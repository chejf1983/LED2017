
#include "stdafx.h"

#include "PropertiesWnd.h"
#include "Resource.h"
#include "MainFrm.h"
#include "LAT2000.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar

CPropertiesWnd::CPropertiesWnd()
{
}

CPropertiesWnd::~CPropertiesWnd()
{
}

BEGIN_MESSAGE_MAP(CPropertiesWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_EXPAND_ALL, OnExpandAllProperties)
	ON_UPDATE_COMMAND_UI(ID_EXPAND_ALL, OnUpdateExpandAllProperties)
	ON_COMMAND(ID_SORTPROPERTIES, OnSortProperties)
	ON_UPDATE_COMMAND_UI(ID_SORTPROPERTIES, OnUpdateSortProperties)
	ON_COMMAND(ID_PROPERTIES1, OnProperties1)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES1, OnUpdateProperties1)
	ON_COMMAND(ID_PROPERTIES2, OnProperties2)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES2, OnUpdateProperties2)
	ON_WM_SETFOCUS()
	ON_WM_SETTINGCHANGE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar 消息处理程序

void CPropertiesWnd::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient,rectCombo;
	GetClientRect(rectClient);

// 	m_wndObjectCombo.GetWindowRect(&rectCombo);
// 
// 	int cyCmb = rectCombo.Size().cy;
	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

// 	m_wndObjectCombo.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), 200, SWP_NOACTIVATE | SWP_NOZORDER);
// 	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top + cyCmb, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
// 	m_wndPropList.SetWindowPos(NULL, rectClient.left, rectClient.top + cyCmb + cyTlb, rectClient.Width(), rectClient.Height() -(cyCmb+cyTlb), SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndPropList.SetWindowPos(NULL, rectClient.left, rectClient.top + cyTlb, rectClient.Width(), rectClient.Height() -cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);

}

int CPropertiesWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// 创建组合:
 	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_BORDER | CBS_SORT | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
//
// 	if (!m_wndObjectCombo.Create(dwViewStyle, rectDummy, this, 1))
// 	{
// 		TRACE0("未能创建属性组合 \n");
// 		return -1;      // 未能创建
// 	}
// 
// 	m_wndObjectCombo.AddString(_T("应用程序"));
// 	m_wndObjectCombo.AddString(_T("属性窗口"));
// 	m_wndObjectCombo.SetCurSel(0);

	if (!m_wndPropList.Create(WS_VISIBLE | WS_CHILD, rectDummy, this, 2))
	{
		TRACE0("未能创建属性网格\n");
		return -1;      // 未能创建
	}

	InitPropList();

	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_PROPERTIES);
	m_wndToolBar.LoadToolBar(IDR_PROPERTIES, 0, 0, TRUE /* 已锁定*/);
	m_wndToolBar.CleanUpLockedImages();
//	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_PROPERTIES_HC : IDR_PROPERTIES, 0, 0, TRUE /* 锁定*/);
	m_wndToolBar.LoadBitmap(IDR_PROPERTIES, 0, 0, TRUE /* 锁定*/);

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	m_wndToolBar.SetOwner(this);

	// 所有命令将通过此控件路由，而不是通过主框架路由:
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	AdjustLayout();
	return 0;
}

void CPropertiesWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CPropertiesWnd::OnExpandAllProperties()
{
	m_wndPropList.ExpandAll();
}

void CPropertiesWnd::OnUpdateExpandAllProperties(CCmdUI* /* pCmdUI */)
{
}

void CPropertiesWnd::OnSortProperties()
{
	m_wndPropList.SetAlphabeticMode(!m_wndPropList.IsAlphabeticMode());
}

void CPropertiesWnd::OnUpdateSortProperties(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_wndPropList.IsAlphabeticMode());
}

void CPropertiesWnd::OnProperties1()
{
	// TODO: 在此处添加命令处理程序代码
}

void CPropertiesWnd::OnUpdateProperties1(CCmdUI* /*pCmdUI*/)
{
	// TODO: 在此处添加命令更新 UI 处理程序代码
}

void CPropertiesWnd::OnProperties2()
{
	// TODO: 在此处添加命令处理程序代码
}

void CPropertiesWnd::OnUpdateProperties2(CCmdUI* /*pCmdUI*/)
{
	// TODO: 在此处添加命令更新 UI 处理程序代码
}

void CPropertiesWnd::InitPropList()
{
	SetPropListFont();

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();
	
	CMFCPropertyGridProperty* pProp = NULL;
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("光色测试数据"));
	
	pProp = new CMFCPropertyGridProperty(_T("光通量(lm)"), (_variant_t) _T("350"), _T("当前选中LED的光通量"));
	pProp->AllowEdit(FALSE);
	pProp->SetData(11);
	pGroup1->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty(_T("主波长(nm)"), (_variant_t) _T("480"), _T("当前选中LED的主波长"));
	pProp->AllowEdit(FALSE);
	pProp->SetData(12);
	pGroup1->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty(_T("色温(K)"), (_variant_t) _T("2856"), _T("当前选中LED的色温"));
	pProp->AllowEdit(FALSE);
	pProp->SetData(13);
	pGroup1->AddSubItem(pProp);

// 	CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty(_T("边框"), _T("对话框外框"), _T("其中之一:“无”、“细”、“可调整大小”或“对话框外框”"));
// 	pProp->AddOption(_T("无"));
// 	pProp->AddOption(_T("细"));
// 	pProp->AddOption(_T("可调整大小"));
// 	pProp->AddOption(_T("对话框外框"));
// 	pProp->AllowEdit(FALSE);
// 
// 	pGroup1->AddSubItem(pProp);
//	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("标题"), (_variant_t) _T("关于"), _T("指定窗口标题栏中显示的文本")));

	m_wndPropList.AddProperty(pGroup1);

	CMFCPropertyGridProperty* pSize = new CMFCPropertyGridProperty(_T("色品坐标"), 0, TRUE);
	pSize->AllowEdit(FALSE);

	pProp = new CMFCPropertyGridProperty(_T("Cx"), (_variant_t) 0.25f, _T("X坐标"));
	//pProp->EnableSpinControl(TRUE, 50, 300);
	pProp->AllowEdit(FALSE);
	
	pProp->SetData(141);
	pProp->m_strFormatFloat = "%.2f";
	pSize->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty( _T("Cy"), (_variant_t) 0.15f, _T("Y坐标"));
	//pProp->EnableSpinControl(TRUE, 50, 200);
	pProp->AllowEdit(FALSE);
	pProp->SetData(142);
	pProp->m_strFormatFloat = "%.2f";
	pSize->AddSubItem(pProp);

	m_wndPropList.AddProperty(pSize);

	CMFCPropertyGridProperty* pGroup2 = new CMFCPropertyGridProperty(_T("电性能测试数据"));

// 	LOGFONT lf;
// 	CFont* font = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
// 	font->GetLogFont(&lf);
// 
// 	lstrcpy(lf.lfFaceName, _T("宋体, Arial"));
// 	
// 	pGroup2->AddSubItem(new CMFCPropertyGridFontProperty(_T("字体"), lf, CF_EFFECTS | CF_SCREENFONTS, _T("指定窗口的默认字体")));
	pProp = new CMFCPropertyGridProperty(_T("电流(mA)"), (_variant_t) _T("10"), _T("当前选中LED电流"));
	pProp->AllowEdit(FALSE);
	pProp->SetData(21);
	pGroup2->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty(_T("电压(V)"), (_variant_t) _T("10"), _T("当前选中LED电流"));
	pProp->AllowEdit(FALSE);
	pProp->SetData(22);
	pGroup2->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty(_T("漏电流(μA)"), (_variant_t) _T("10"), _T("当前选中LED电流"));
	pProp->AllowEdit(FALSE);
	pProp->SetData(23);
	pGroup2->AddSubItem(pProp);

	m_wndPropList.AddProperty(pGroup2);

	CMFCPropertyGridProperty* pGroup3 = new CMFCPropertyGridProperty(_T("测试信息"));
	pProp = new CMFCPropertyGridProperty(_T("积分时间(ms)"), _T("100"));
	pProp->AllowEdit(FALSE);
	pProp->SetData(31);
	pGroup3->AddSubItem(pProp);

	CTime time;
	time = CTime::GetCurrentTime();
	CString strTemp = time.Format("%Y-%m-%d %H:%M:%S");
	pProp = new CMFCPropertyGridProperty(_T("测试时间"), strTemp );
	pProp->AllowEdit(FALSE);
	pProp->SetData(32);
	pGroup3->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty(_T("LED型号"), _T("LED-100"));
	pProp->AllowEdit(FALSE);
	pProp->SetData(33);
	pGroup3->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty(_T("测试人员"), _T("Damin"));
	pProp->AllowEdit(FALSE);
	pProp->SetData(34);
	pGroup3->AddSubItem(pProp);

 	m_wndPropList.AddProperty(pGroup3);
//	CMFCPropertyGridColorProperty* pColorProp = new CMFCPropertyGridColorProperty(_T("结果"), RGB(210, 192, 254), NULL, _T("测试是否合格"));
//	pColorProp->EnableOtherButton(_T("其他..."));
//	pColorProp->Enable(FALSE);
//	pColorProp->SetColor(RGB(50,255,50));
//	pColorProp->
//	pColorProp->EnableAutomaticButton(_T("默认"), ::GetSysColor(COLOR_3DFACE));
//	pGroup3->AddSubItem(pColorProp);
// 
// 	static const TCHAR szFilter[] = _T("图标文件(*.ico)|*.ico|所有文件(*.*)|*.*||");
// 	pGroup3->AddSubItem(new CMFCPropertyGridFileProperty(_T("图标"), TRUE, _T(""), _T("ico"), 0, szFilter, _T("指定窗口图标")));
// 
// 	pGroup3->AddSubItem(new CMFCPropertyGridFileProperty(_T("文件夹"), _T("c:\\")));
// 
// 	m_wndPropList.AddProperty(pGroup3);
// 
// 	CMFCPropertyGridProperty* pGroup4 = new CMFCPropertyGridProperty(_T("层次结构"));
// 
// 	CMFCPropertyGridProperty* pGroup41 = new CMFCPropertyGridProperty(_T("第一个子级")); pGroup4->AddSubItem(pGroup41);
// 
// 	CMFCPropertyGridProperty* pGroup411 = new CMFCPropertyGridProperty(_T("第二个子级"));
// 	pGroup41->AddSubItem(pGroup411);
// 
// 	pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("项 1"), (_variant_t) _T("值 1"), _T("此为说明")));
// 	pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("项 2"), (_variant_t) _T("值 2"), _T("此为说明")));
// 	pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("项 3"), (_variant_t) _T("值 3"), _T("此为说明")));
// 
// 	pGroup4->Expand(FALSE);
// 	m_wndPropList.AddProperty(pGroup4);

	//
// 	COleVariant itemValue;
// 	itemValue = m_wndPropList.FindItemByData(11)->GetOriginalValue();
// 	CString strTemp = itemValue;
}

void CPropertiesWnd::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);
	m_wndPropList.SetFocus();
}

void CPropertiesWnd::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CDockablePane::OnSettingChange(uFlags, lpszSection);
	SetPropListFont();
}

void CPropertiesWnd::SetPropListFont()
{
	::DeleteObject(m_fntPropList.Detach());

	LOGFONT lf;
	afxGlobalData.fontRegular.GetLogFont(&lf);

	NONCLIENTMETRICS info;
	info.cbSize = sizeof(info);

	afxGlobalData.GetNonClientMetrics(info);

	lf.lfHeight = info.lfMenuFont.lfHeight;
	lf.lfWeight = info.lfMenuFont.lfWeight;
	lf.lfItalic = info.lfMenuFont.lfItalic;

	m_fntPropList.CreateFontIndirect(&lf);

	m_wndPropList.SetFont(&m_fntPropList);
	//	m_wndObjectCombo.SetFont(&m_fntPropList);
}
