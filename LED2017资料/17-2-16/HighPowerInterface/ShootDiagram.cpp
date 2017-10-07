// ShootDiagram.cpp : implementation file
//

#include "stdafx.h"
#include "HighPowerInterface.h"
#include "ShootDiagram.h"
#include "Functions.h"
#include "SettingDlg.h"
#include "ChipsHandle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShootDiagram dialog
int shootchip = 0;
extern COLOR_PARA g_dColorPara;

CShootDiagram::CShootDiagram(CWnd* pParent /*=NULL*/)
	: CResizingDialog(CShootDiagram::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShootDiagram)
	m_shootchip = shootchip;
	m_inputset = 0;
	m_CIEPicture = false;
	m_showscale = true;
	m_HandleRange = 1;
	m_AddLevelStyle = 1;
	//}}AFX_DATA_INIT
}

void CShootDiagram::DoDataExchange(CDataExchange* pDX)
{
	CResizingDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShootDiagram)
	DDX_Control(pDX, IDC_FigureRange, m_figureRange);
	DDX_Control(pDX, IDC_ShowScale, m_showScale);
	DDX_Control(pDX, IDC_SelectCIEPicture, m_ShowCIEPicture);
	DDX_Control(pDX, IDC_parallelrectDrag, m_parallelDrag);
	DDX_Control(pDX, IDC_XYlevelFile, m_file);
	DDX_Control(pDX, IDC_SetColor, m_setColor);
	DDX_Control(pDX, IDC_ShowLevelPicture, m_showLevel);
	DDX_Control(pDX, IDC_ClearPicture, m_clearPicture);
	DDX_Control(pDX, IDC_ClearDot, m_clearDot);
	DDX_Control(pDX, IDC_CheckBinNum, m_binNum);
	DDX_Control(pDX, IDC_AddLevel, m_addlevelbutton);
	DDX_Control(pDX, IDC_DeleteLevel, m_deletebutton);
	DDX_Control(pDX, IDC_Apply, m_applybutton);
	DDX_Control(pDX, IDC_DrawPoint, m_shootpoint);
	DDX_Control(pDX, IDC_Exit, m_exit);
	DDX_Control(pDX, IDC_inputpoint, m_inputpoint);
	DDX_Control(pDX, IDC_Accumulate, m_accu);
	DDX_Control(pDX, IDC_YStart, m_ystart);
	DDX_Control(pDX, IDC_YEnd, m_yend);
	DDX_Control(pDX, IDC_XStart, m_xstart);
	DDX_Control(pDX, IDC_XEnd, m_xend);
	DDX_Control(pDX, IDC_EnableResize, m_resize);
	DDX_Control(pDX, IDC_LevelAdjust, m_adjust);
	DDX_Control(pDX, IDC_LevelStyle, m_levelstyle);
	DDX_Control(pDX, IDC_ShowPointList, m_showpointlist);
	DDX_Control(pDX, IDC_SURE, m_sure);
	DDX_Control(pDX, IDC_ShootPicture, m_shootpicture);
	DDX_Radio(pDX, IDC_shootchip1, m_shootchip);
	DDX_Radio(pDX, IDC_inputset, m_inputset);
	DDX_Check(pDX, IDC_SelectCIEPicture, m_CIEPicture);
	DDX_Check(pDX, IDC_ShowScale, m_showscale);
	DDX_Radio(pDX, IDC_SetRange, m_HandleRange);
	DDX_Radio(pDX, IDC_CoverLevel, m_AddLevelStyle);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CShootDiagram, CResizingDialog)
	//{{AFX_MSG_MAP(CShootDiagram)
	ON_BN_CLICKED(IDC_Exit, OnExit)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_DrawPoint, OnDrawPoint)
	ON_WM_RBUTTONDOWN()
	ON_BN_CLICKED(IDC_inputpoint, Oninputpoint)
	ON_BN_CLICKED(IDC_ClearPicture, OnClearPicture)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_SetColor, OnSetColor)
	ON_BN_CLICKED(IDC_SURE, OnSure)
	ON_BN_CLICKED(IDC_inputset, Oninputset)
	ON_BN_CLICKED(IDC_lineset, Onlineset)
	ON_BN_CLICKED(IDC_rectset, Onrectset)
	ON_BN_CLICKED(IDC_Apply, OnApply)
	ON_BN_CLICKED(IDC_SelectCIEPicture, OnSelectCIEPicture)
	ON_BN_CLICKED(IDC_ShowScale, OnShowScale)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_AddLevel, OnAddLevel)
	ON_BN_CLICKED(IDC_SetRange, OnSetRange)
	ON_BN_CLICKED(IDC_SetLevel, OnSetLevel)
	ON_BN_CLICKED(IDC_InsertLevel, OnInsertLevel)
	ON_BN_CLICKED(IDC_CoverLevel, OnCoverLevel)
	ON_BN_CLICKED(IDC_DeleteLevel, OnDeleteLevel)
	ON_BN_CLICKED(IDC_SelectLevel, OnSelectLevel)
	ON_BN_CLICKED(IDC_parallelrectset, Onparallelrectset)
	ON_BN_CLICKED(IDC_CheckBinNum, OnCheckBinNum)
	ON_BN_CLICKED(IDC_ShowLevelPicture, OnShowLevelPicture)
	ON_BN_CLICKED(IDC_LevelAdjust, OnLevelAdjust)
	ON_BN_CLICKED(IDC_Enlarge, OnEnlarge)
	ON_BN_CLICKED(IDC_Smaller, OnSmaller)
	ON_BN_CLICKED(IDC_EnableResize, OnEnableResize)
	ON_WM_MOUSEWHEEL()
	ON_NOTIFY(NM_CLICK, IDC_ShowPointList, OnClickShowPointList)
	ON_BN_CLICKED(IDC_XYlevelFile, OnXYlevelFile)
	ON_COMMAND(ID_ExportXYLevel, OnExportXYLevel)
	ON_COMMAND(ID_ImportXYLevel, OnImportXYLevel)
	ON_COMMAND(ID_SaveXYLevel, OnSaveXYLevel)
	ON_BN_CLICKED(IDC_ClearDot, OnClearDot)
	ON_UPDATE_COMMAND_UI(ID_ShowCIELine, OnUpdateShowCIELine)
	ON_COMMAND(ID_ShowCIELine, OnShowCIELine)
	ON_COMMAND(ID_SaveShootDot, OnSaveShootDot)
	ON_COMMAND(ID_LoadShootDot, OnLoadShootDot)
	ON_COMMAND(ID_NewCIERect, OnNewCIERect)
	ON_UPDATE_COMMAND_UI(ID_NewCIERect, OnUpdateNewCIERect)
	ON_BN_CLICKED(IDC_FigureRange, OnFigureRange)
	ON_COMMAND(ID_ImportXYLevel2, OnImportXYLevel2)
	ON_BN_CLICKED(IDC_shootchip1, Onshootchip1)
	ON_BN_CLICKED(IDC_shootchip2, Onshootchip2)
	ON_BN_CLICKED(IDC_shootchip3, Onshootchip3)
	ON_COMMAND(ID_ExportXYLevel2, OnExportXYLevel2)
	ON_COMMAND(ID_SaveXYLevel2, OnSaveXYLevel2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShootDiagram message handlers
extern bool Operator;
extern bool engineer;
extern SystemSet systemset;
extern sngPOINT point[3][4];
extern BinArray binArray;
extern int columns[3];
extern bool continuetest;

extern XYLEVELItem TotalRangeItem[3];
extern CList<XYLEVELItem, XYLEVELItem> levelItem[3];

extern LightParam PolParam[3];
extern int selectchiptype;
extern bool row1;

CList<POSITION, POSITION> InRectPos;
CList<XYLEVELItem, XYLEVELItem> tempBigRect[3];
CList<POSITION, POSITION> smallRectPos[3];

CWinThread* pThread3;
CString str_pointx[4], str_pointy[4];
sngPOINT apply_p[3][4][40];
XYLEVEL xylevel[3];

POSITION selectpos[3];
POSITION bigselectpos[3];

PictureParam picParam;

bool startshoot = false;
bool shootopen = false;
extern bool updatelevellist;
CList<sngPOINT, sngPOINT> dot[3];//存放打靶得到的点

extern bool showshoot;
bool resize = false;
double XRate;
double YRate;
double xstart = 0;
double xend = 0.8;
double ystart = 0;
double yend = 0.9;
double ChangeRate = 0.9;

bool shift = false;
bool shootChange = false;   /////判断分级图形是否更改，若真，则刷新分级

CString str_bin;
extern CString showShootBin[3][100];

extern double BlackXY[67][2];
extern XYLEVELItem BinCode[98];
extern CString BinCodeName[98];

extern double xyRange;

BOOL CShootDiagram::OnInitDialog() 
{
	CResizingDialog::OnInitDialog();
	
	// TODO: Add extra initialization here	
	int screen_width = 0, change_width = 0;
	screen_width = GetSystemMetrics(SM_CXSCREEN);
	if(screen_width > 1024)
	{
		change_width = (int)((screen_width - 1024)/2);
	}
	MoveWindow((20 + change_width), 20, 980, 700);
	CRgn rgn;
	rgn.CreateRoundRectRgn(0, 0, 980, 700, 20, 20);
	SetWindowRgn(rgn, true);
	
	UpdateData();
	m_shootchip = shootchip;
	m_inputset = 0;
	m_CIEPicture = false;
	m_showscale = true;
	m_HandleRange = 1;
	m_AddLevelStyle = 1;
	UpdateData(false);

	InitPictureParam(); 
	m_menu.LoadMenu(IDR_MENU2);
	////////////////////listcontrol
	m_showpointlist.Init();
	CFont font;
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfHeight = 20;
	strcpy(lf.lfFaceName, "Verdana");
	font.CreateFontIndirect(&lf);
	m_showpointlist.SetFont(&font, TRUE);
	
	m_showpointlist.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);

	CString strValidChars = "0123456789.-";
	m_showpointlist.SetValidEditCtrlCharacters(strValidChars);

	m_showpointlist.InsertColumn(0, "", LVCFMT_CENTER, 40);
	m_showpointlist.InsertColumn(1, "X", LVCFMT_CENTER, 94);
	m_showpointlist.InsertColumn(2, "Y", LVCFMT_CENTER, 94);
	m_showpointlist.InsertItem(0, "P1");
	m_showpointlist.InsertItem(1, "P2");
	m_showpointlist.InsertItem(2, "P3");
	m_showpointlist.InsertItem(3, "P4");
	m_showpointlist.SetReadOnlyColumns(0);

	row1 = true;
	startshoot = false;
	drag = false;
	dragRect = false;
	showCIELine = false;
	newCIERect = false;

	m_cMovePoint.x = 0;
	m_cMovePoint.y = 0;

	m_color = RGB(0, 0, 0);

	if(continuetest)
	{
		m_shootpoint.EnableWindow(false);
		m_sure.EnableWindow(false);
		shootopen = true;	
		SetTimer(0, 500, NULL);
	}
	else
	{
		m_shootpoint.EnableWindow(true);
		if(Operator || engineer)
		{
			m_sure.EnableWindow(true);
		}
		else
		{
			m_sure.EnableWindow(false);
		}
	}

//	SetTimer(1, 500, NULL);

	m_resize.SetCheck(0);
	m_accu.SetCheck(1);
	m_figureRange.SetCheck(1);

	for(int i=0; i<3; i++)
	{
		selectpos[i] = NULL;
		bigselectpos[i] = NULL;

		if(0 == levelItem[i].GetCount())  
		{
			pointnum[i] = 0;
			rectpointnum[i] = 0;
			parallelnum[i] = 0;
		}
		else
		{
			pointnum[i] = 4;
			rectpointnum[i] = 2;
			parallelnum[i] = 3;
		}

		xylevel[i].x = 1;
		xylevel[i].y = 1;
		xylevel[i].startbin = 0;
	}

	if(0 == levelItem[0].GetCount())  
	{
//		m_inputpoint.EnableWindow(false);
		m_addlevelbutton.EnableWindow(false);
	}
	else
	{
		m_inputpoint.EnableWindow(true);
		m_addlevelbutton.EnableWindow(true);
	}

	setDlgText();
	InvalidateRect(&rect, false);

	SetDialogFace();

	shootChange = false;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CShootDiagram::InitPictureParam() 
{
	xstart = 0;
	xend = 0.8;
	ystart = 0;
	yend = 0.9;
	
	XRate = 1;
	YRate = 1;

	picParam.width = 640;
	picParam.height = 540;
	picParam.left = 40;
	picParam.top = 90;
	picParam.scalex = 640 / 16;
	picParam.scaley = 540 / 18;
	picParam.ratex = picParam.scalex / 0.05;
	picParam.ratey = picParam.scaley / 0.05;
	pWnd_picture = GetDlgItem(IDC_ShootPicture);
	pWnd_picture->GetClientRect(&rect);
	pWnd_picture->MoveWindow(picParam.left, picParam.top, picParam.width, picParam.height);
	
	pDC_picture = pWnd_picture->GetDC(); 
}

void CShootDiagram::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nIDEvent)
	{
	case 0:
		InvalidateRect(&rect, false);
		CResizingDialog::OnTimer(nIDEvent);
		break;
	case 1:
		RefreshBigRect();
		break;
	default:
		break;
	}
}

bool CShootDiagram::RefreshBigRect()
{
	CString str;
	int i = 0;
	XYLEVELItem tempItem;
	
	if((1 == m_HandleRange) && (bigselectpos[m_shootchip] != NULL))
	{
		for(i=0; i<4; i++)
		{
			str = m_showpointlist.GetItemText(i, 1);
			tempItem.x[i] = atof(str);
			str = m_showpointlist.GetItemText(i, 2);
			tempItem.y[i] = atof(str);	
		}
		
		if(IfConvexQuadrangle(tempItem.x, tempItem.y))
		{
			if(!compareXYLEVELItem(tempBigRect[m_shootchip].GetAt(bigselectpos[m_shootchip]), tempItem))
			{
				DelAllInRect(m_shootchip, tempBigRect[m_shootchip].GetAt(bigselectpos[m_shootchip]));
				tempItem.num = tempBigRect[m_shootchip].GetAt(bigselectpos[m_shootchip]).num;
				tempBigRect[m_shootchip].GetAt(bigselectpos[m_shootchip]) = tempItem;
				
				InvalidateRect(&rect, false);
				return true;
			}
		}
		
		for(i=0; i<4; i++)
		{
			str.Format("%0.4f", tempBigRect[m_shootchip].GetAt(bigselectpos[m_shootchip]).x[i]);
			m_showpointlist.SetItemText(i, 1, ReformatString(str));
			str.Format("%0.4f", tempBigRect[m_shootchip].GetAt(bigselectpos[m_shootchip]).y[i]);
			m_showpointlist.SetItemText(i, 2, ReformatString(str));
		}
	}
/*	else if((2 == m_HandleRange) && (selectpos[m_shootchip] != NULL))
	{
		for(i=0; i<4; i++)
		{
			str = m_showpointlist.GetItemText(i, 1);
			tempItem.x[i] = atof(str);
			str = m_showpointlist.GetItemText(i, 2);
			tempItem.y[i] = atof(str);	
		}
		
		if(IfConvexQuadrangle(tempItem.x, tempItem.y))
		{
			if(1)//!IfSameRectExist(levelItem[m_shootchip].GetAt(selectpos[m_shootchip]), m_shootchip))
			{
				tempItem.num = levelItem[m_shootchip].GetAt(selectpos[m_shootchip]).num;
				levelItem[m_shootchip].GetAt(selectpos[m_shootchip]) = tempItem;
				InvalidateRect(&rect, false);
				return true;	
			}
		}
		
		for(i=0; i<4; i++)
		{
			str.Format("%0.4f", levelItem[m_shootchip].GetAt(selectpos[m_shootchip]).x[i]);
			m_showpointlist.SetItemText(i, 1, ReformatString(str));
			str.Format("%0.4f", levelItem[m_shootchip].GetAt(selectpos[m_shootchip]).y[i]);
			m_showpointlist.SetItemText(i, 2, ReformatString(str));
		}
	}*/

	return false;
}
//////////////////////////////////////显示设置
void CShootDiagram::OnSetColor() 
{
	// TODO: Add your control notification handler code here
	CColorDialog colordlg(m_color);
	if (colordlg.DoModal() == IDOK)
	{
		m_color = colordlg.GetColor();
	}
}

void CShootDiagram::OnSelectCIEPicture() 
{
	// TODO: Add your control notification handler code here
	if(m_CIEPicture)
	{
		m_CIEPicture = false;
		m_showscale = true;
		m_showScale.SetCheck(1);

		GetDlgItem(IDC_EnableResize)->ShowWindow(SW_SHOW);
//		GetDlgItem(IDC_Enlarge)->ShowWindow(SW_HIDE);
//		GetDlgItem(IDC_Smaller)->ShowWindow(SW_HIDE);
	}
	else
	{
		m_CIEPicture = true;
		m_showscale = false;
		m_showScale.SetCheck(0);

		GetDlgItem(IDC_EnableResize)->ShowWindow(SW_HIDE);
//		GetDlgItem(IDC_Enlarge)->ShowWindow(SW_SHOW);
//		GetDlgItem(IDC_Smaller)->ShowWindow(SW_SHOW);
	}	

	InvalidateRect(false);
	InvalidateRect(&rect, false);
}

void CShootDiagram::OnShowScale() 
{
	// TODO: Add your control notification handler code here
	if(m_showscale)
	{
		m_showscale = false;
		m_CIEPicture = true;
		m_ShowCIEPicture.SetCheck(1);
		
		GetDlgItem(IDC_EnableResize)->ShowWindow(SW_HIDE);
//		GetDlgItem(IDC_Enlarge)->ShowWindow(SW_SHOW);
//		GetDlgItem(IDC_Smaller)->ShowWindow(SW_SHOW);
		
	}
	else
	{
		m_showscale = true;
		m_CIEPicture = false;
		m_ShowCIEPicture.SetCheck(0);

//		InitPictureParam(); 
		GetDlgItem(IDC_EnableResize)->ShowWindow(SW_SHOW);
//		GetDlgItem(IDC_Enlarge)->ShowWindow(SW_HIDE);
//		GetDlgItem(IDC_Smaller)->ShowWindow(SW_HIDE);
	}	
	
	InvalidateRect(false);
	InvalidateRect(&rect, false);
}

void CShootDiagram::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	// TODO: Add your message handler code here
	CDC MemDC;
	CBitmap MemBitmap;

	int i;
	CString str;
	CPen pen, pen2, pen3, pen4;
	CPen *ptrPenOld;
	int nMode;

	MemDC.CreateCompatibleDC(NULL);
	MemBitmap.CreateCompatibleBitmap(pDC_picture, picParam.width, picParam.height);
	CBitmap *pOldBit = MemDC.SelectObject(&MemBitmap);
	MemDC.FillSolidRect(0, 0, picParam.width, picParam.height, RGB(255,255,255));

	if(m_CIEPicture)
	{
		CBitmap bitmapbk;
		BITMAP bm;
		bitmapbk.LoadBitmap(IDB_shootCIE);
		bitmapbk.GetBitmap(&bm);
		CDC dcMemory;
		dcMemory.CreateCompatibleDC(&MemDC);
		CBitmap* pOldBitmap = dcMemory.SelectObject(&bitmapbk);	
		int bmpstartX = 0, bmpstartY = 0;
		bmpstartX = (int)(xstart * 800);
		bmpstartY = (int)((0.9 - yend) * 600);
		MemDC.StretchBlt(0, 0, (int)(picParam.width * XRate), (int)(picParam.height * YRate), 
			&dcMemory, bmpstartX, bmpstartY, bm.bmWidth, bm.bmHeight, SRCCOPY);
	}

    ////////////////////////////显示坐标刻度
	dc.SetBkMode(TRANSPARENT);
	if(m_showscale)
	{
		int xscalenum = 8, yscalenum = 9;
		xscalenum = (int)((xend - xstart) * 20);
		yscalenum = (int)((yend - ystart) * 20);

		if(((xend - xstart) * 20 / xscalenum) > 1)
		{
			xscalenum += 1;
		}

		if(((yend - ystart) * 20 / yscalenum) > 1)
		{
			yscalenum += 1;
		}

		if(yscalenum < 10)
		{
			for(i=1; i<yscalenum; i++)
			{
				str.Format("%0.2f", ystart + (double)i/20);
				dc.TextOut(13, 624 - (int)(i * picParam.scaley * YRate), str);
			}
		}
		else
		{
			for(i=1; i<yscalenum/2; i++)
			{
				str.Format("%0.2f", ystart + (double)i/10);
				dc.TextOut(13, 624 - (int)(i * picParam.scaley * YRate * 2), str);
			}	
		}
		str.Format("%0.2f", ystart);
		dc.TextOut(13, 616, str);
		
		str.Format("%0.2f", yend);
		dc.TextOut(13, 84, str);
		
		
		if(xscalenum < 9)
		{
			for(i=0; i<xscalenum; i++)
			{
				str.Format("%0.2f", xstart + (double)i/20);
				dc.TextOut(32 + (int)(i * picParam.scalex * XRate), 635, str);
			}
		}
		else
		{
			for(i=0; i<xscalenum/2; i++)
			{
				str.Format("%0.2f", xstart + (double)i/10);
				dc.TextOut(32 + (int)(i * picParam.scalex * XRate * 2), 635, str);
			}
		}

		str.Format("%0.2f", xend);
		dc.TextOut(672, 635, str);
		
		pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
		ptrPenOld = MemDC.SelectObject(&pen);
		nMode = MemDC.SetROP2(R2_COPYPEN);
	
		CPoint st, en;
		if(xscalenum < 9)
		{
			for(i=1; i<xscalenum*2; i++)
			{
				st.x = (int)(i * picParam.scalex * XRate / 2);
				st.y = 0;
				en.x = (int)(i * picParam.scalex * XRate / 2);
				en.y = picParam.height;
				
				MemDC.MoveTo(st);
				MemDC.LineTo(en);
			}
		}
		else
		{
			for(i=1; i<xscalenum; i++)
			{
				st.x = (int)(i * picParam.scalex * XRate);
				st.y = 0;
				en.x = (int)(i * picParam.scalex * XRate);
				en.y = picParam.height;
				
				MemDC.MoveTo(st);
				MemDC.LineTo(en);
			}
		}

		if(yscalenum < 10)
		{
			for(i=1; i<yscalenum*2; i++)
			{
				st.x = 0;
				st.y = (int)(picParam.height - i * picParam.scaley * YRate / 2);
				en.x = picParam.width;
				en.y = (int)(picParam.height - i * picParam.scaley * YRate / 2);
				
				MemDC.MoveTo(st);
				MemDC.LineTo(en);
			}
		}
		else
		{
			for(i=1; i<yscalenum; i++)
			{
				st.x = 0;
				st.y = (int)(picParam.height - i * picParam.scaley * YRate);
				en.x = picParam.width;
				en.y = (int)(picParam.height - i * picParam.scaley * YRate);
				
				MemDC.MoveTo(st);
				MemDC.LineTo(en);
			}
		}
	}

	////////////////显示大范围分级
	pen2.CreatePen(PS_DOT, 1, RGB(255, 0, 0));
	ptrPenOld = MemDC.SelectObject(&pen2);
	nMode = MemDC.SetROP2(R2_COPYPEN);

	CPoint p[4]; 
	XYLEVELItem item;

	if(!showshoot)
	{
		POSITION pos2 = tempBigRect[m_shootchip].GetHeadPosition();
		while(pos2 != NULL)
		{
			item = tempBigRect[m_shootchip].GetNext(pos2);
			for(i=0; i<4; i++)
			{
				p[i].x = (int)((item.x[i] - xstart) * picParam.ratex);
				p[i].y = (int)(picParam.height - (item.y[i] - ystart) * picParam.ratey);
			}
			DrawRect(p, &MemDC);
		}
	}

	////////////////////画图方法选择
	switch(m_inputset)
	{
	case 1:
		if((pointnum[m_shootchip] > 0) && (pointnum[m_shootchip] < 4))
		{
			MemDC.MoveTo(m_vInputPoint[pointnum[m_shootchip]-1]);
			MemDC.LineTo(m_cMovePoint);
			
			for(i=0; i<(pointnum[m_shootchip]-1); i++)
			{
				MemDC.MoveTo(m_vInputPoint[i]);
				MemDC.LineTo(m_vInputPoint[i+1]);
			}
		}	
		break;
	case 2:
		if(1 == rectpointnum[m_shootchip])
		{
			if((rectdraw.left != rectdraw.right) && (rectdraw.top != rectdraw.bottom))
			{
				p[0].x = rectdraw.left;
				p[0].y = rectdraw.top;
				p[1].x = rectdraw.right;
				p[1].y = rectdraw.top;
				p[2].x = rectdraw.right;
				p[2].y = rectdraw.bottom;
				p[3].x = rectdraw.left;
				p[3].y = rectdraw.bottom;
				DrawRect(p, &MemDC);
			}
		}	
		break;
	case 3:
		if(1 == parallelnum[m_shootchip])
		{
			MemDC.MoveTo(m_vInputPoint[0]);
			MemDC.LineTo(m_cMovePoint);
		}
		else if(2 == parallelnum[m_shootchip])
		{
			p[0] = m_vInputPoint[0];
			p[1] = m_vInputPoint[1];
			p[2] = m_cMovePoint;
			p[3].x = p[2].x + p[0].x - p[1].x; 
			p[3].y = p[2].y + p[0].y - p[1].y; 
			DrawRect(p, &MemDC);
		}
		break;
	default:
		break;
	}

    //////////////////////显示鼠标所在点坐标
	pen3.CreatePen(PS_SOLID, 1, m_color);
	ptrPenOld = MemDC.SelectObject(&pen3);
	nMode = MemDC.SetROP2(R2_COPYPEN);

	double x, y;
	double CCT = 0;
	x = xstart + (double)m_cMovePoint.x / picParam.ratex;
	y = ystart + (double)(picParam.height - m_cMovePoint.y) / picParam.ratey;

	str.Format(" %0.4f, %0.4f ", x, y);

	///////显示当前图形bin号
	if(showshoot)
	{
		if(FindSelectedRect(x, y))
		{
			MemDC.TextOut(5, 10, "BIN:  " + str_bin);
		}
		else
		{
			selectpos[m_shootchip] = NULL;
		}
	}
	
	if(m_cMovePoint.x > 500)
	{
		if(m_cMovePoint.y > 515)
		{
			MemDC.TextOut(m_cMovePoint.x-150, m_cMovePoint.y-20, str);
		}
		else
		{
			MemDC.TextOut(m_cMovePoint.x-150, m_cMovePoint.y+10, str);
		}
	}
	else if(m_cMovePoint.y > 515)
	{
		MemDC.TextOut(m_cMovePoint.x+10, m_cMovePoint.y-20, str);
	}
	else
	{
		MemDC.TextOut(m_cMovePoint.x+10, m_cMovePoint.y+10, str);
	}

	CCT = g_dColorPara.fCCT;//getCCT(x, y);
	str.Format("%0.2f", CCT);
	MemDC.TextOut(5, 515, "CCT:  " + str);

	if(newCIERect)
	{
		if(FindNewCIERect(x, y))
		{
			MemDC.TextOut(110, 515, BinCodeName[CIERectNum]);
		}	
	}

	if(!showshoot)
	{
		if(m_HandleRange != 2)
		{
			if(((1 == m_inputset) && (pointnum[m_shootchip] < 4)) 
				|| ((2 == m_inputset) && (rectpointnum[m_shootchip] < 2)) 
				|| ((3 == m_inputset) && (parallelnum[m_shootchip] < 3)))
			{
				MemDC.Ellipse(m_cMovePoint.x-2, m_cMovePoint.y-2, m_cMovePoint.x+2, m_cMovePoint.y+2);
			}
		}
	}

	////////////////////////打点
	CBrush brush, *oldbrush;
	brush.CreateSolidBrush(m_color);
	oldbrush = MemDC.SelectObject(&brush);
	CPoint dotPoint;
	sngPOINT point;
	POSITION pos = dot[0].GetHeadPosition();
	while(pos != NULL)
	{
		point = dot[0].GetNext(pos);
		dotPoint.x = (int)((point.x - xstart) * picParam.ratex);
        dotPoint.y = (int)(picParam.height - (point.y - ystart) * picParam.ratey);
		MemDC.Ellipse(dotPoint.x-1, dotPoint.y-1, dotPoint.x+1, dotPoint.y+1);
	}
	MemDC.SelectObject(oldbrush);

	////////////////////////////显示分级
	POSITION pos3 = levelItem[m_shootchip].GetHeadPosition();
	while(pos3 != NULL)
	{
		item = levelItem[m_shootchip].GetNext(pos3);
		for(i=0; i<4; i++)
		{
			p[i].x = (int)((item.x[i] - xstart) * picParam.ratex);
			p[i].y = (int)(picParam.height - (item.y[i] - ystart) * picParam.ratey);
		}
		DrawRect(p, &MemDC);
	}

	////////////////////显示色温线
	pen4.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	ptrPenOld = MemDC.SelectObject(&pen4);
	nMode = MemDC.SetROP2(R2_COPYPEN);

	if(showCIELine)
	{
		CPoint CIELinePoint[2];
		for(i=0; i<66; i++)
		{
			CIELinePoint[0].x = (int)((BlackXY[i][0] - xstart) * picParam.ratex);
			CIELinePoint[0].y = (int)(picParam.height - (BlackXY[i][1] - ystart) * picParam.ratey);
			CIELinePoint[1].x = (int)((BlackXY[i+1][0] - xstart) * picParam.ratex);
			CIELinePoint[1].y = (int)(picParam.height - (BlackXY[i+1][1] - ystart) * picParam.ratey);
			
			MemDC.MoveTo(CIELinePoint[0]);
			MemDC.LineTo(CIELinePoint[1]);
		}
	}
    //////////////////////显示新CIE坐标
	if(newCIERect)
	{
		for(i=0; i<98; i++)
		{
			for(int j=0; j<4; j++)
			{
				p[j].x = (int)((BinCode[i].x[j] - xstart) * picParam.ratex);
				p[j].y = (int)(picParam.height - (BinCode[i].y[j] - ystart) * picParam.ratey);
			}
			DrawRect(p, &MemDC);
		}
	}

	//////////////////////操作方式选择
	switch(m_HandleRange)
	{
	case 0:
		for(i=0; i<4; i++)
		{
			p[i].x = (int)((TotalRangeItem[m_shootchip].x[i] - xstart) * picParam.ratex);
			p[i].y = (int)(picParam.height - (TotalRangeItem[m_shootchip].y[i] - ystart) * picParam.ratey);
		}
		DrawRect(p, &MemDC);
		break;
	case 1:
		if(bigselectpos[m_shootchip] != NULL)
		{
			item = tempBigRect[m_shootchip].GetAt(bigselectpos[m_shootchip]);
			for(i=0; i<4; i++)
			{
				p[i].x = (int)((item.x[i] - xstart) * picParam.ratex);
				p[i].y = (int)(picParam.height - (item.y[i] - ystart) * picParam.ratey);
				MemDC.Ellipse(p[i].x-4, p[i].y-4, p[i].x+4, p[i].y+4);
			}
		}
		break;
	case 2:
		if(selectpos[m_shootchip] != NULL)
		{
			item = levelItem[m_shootchip].GetAt(selectpos[m_shootchip]);
			for(i=0; i<4; i++)
			{
				p[i].x = (int)((item.x[i] - xstart) * picParam.ratex);
				p[i].y = (int)(picParam.height - (item.y[i] - ystart) * picParam.ratey);
				MemDC.Ellipse(p[i].x-4, p[i].y-4, p[i].x+4, p[i].y+4);
			}
		}
		break;
	default:
		break;
	}

	MemDC.SelectObject(ptrPenOld);
	MemDC.SetROP2(nMode);

	pWnd_picture->UpdateWindow(); 
	pDC_picture->BitBlt(0, 0, picParam.width, picParam.height, &MemDC, 0, 0, SRCCOPY);

	MemBitmap.DeleteObject();
	MemDC.DeleteDC();

	// Do not call CResizingDialog::OnPaint() for painting messages
}

void CShootDiagram::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if((point.x >= picParam.left) && (point.x <= (picParam.left + picParam.width)) 
		&& (point.y >= picParam.top) && (point.y <= picParam.top + picParam.height))
	{	
		m_cMovePoint.x = point.x - picParam.left;
		m_cMovePoint.y = point.y - picParam.top;
		
		CString str;
		double x = 0, y = 0;
		double offset_x = 0, offset_y = 0;
		int tempPointNum1 = 0, tempPointNum2 = 0, tempPointNum3 = 0;

		if(drag)
		{	
			x = xstart + (double)m_cMovePoint.x / picParam.ratex;
			y = ystart + (double)(picParam.height - m_cMovePoint.y) / picParam.ratey;
			offset_x = x - tempBigRect[m_shootchip].GetAt(bigselectpos[m_shootchip]).x[dragPointNum];
			offset_y = y - tempBigRect[m_shootchip].GetAt(bigselectpos[m_shootchip]).y[dragPointNum];
			
			tempBigRect[m_shootchip].GetAt(bigselectpos[m_shootchip]).x[dragPointNum] = x;
			tempBigRect[m_shootchip].GetAt(bigselectpos[m_shootchip]).y[dragPointNum] = y;
			str.Format("%0.4f", x);
			m_showpointlist.SetItemText(dragPointNum, 1, str);
			str.Format("%0.4f", y);
			m_showpointlist.SetItemText(dragPointNum, 2, str);
			
			if(3 == m_inputset)
			{ 
				if(0 == m_parallelDrag.GetCheck())
				{
					switch(dragPointNum)
					{
					case 0:
						tempPointNum1 = 1;
						tempPointNum2 = 2;
						tempPointNum3 = 3;
						break;
					case 1:
						tempPointNum1 = 0;
						tempPointNum2 = 3;
						tempPointNum3 = 2;
						break;
					case 2:
						tempPointNum1 = 3;
						tempPointNum2 = 0;
						tempPointNum3 = 1;
						break;
					case 3:
						tempPointNum1 = 2;
						tempPointNum2 = 1;
						tempPointNum3 = 0;
						break;
					default:
						break;
					}
				}
				else
				{
					switch(dragPointNum)
					{
					case 0:
						tempPointNum1 = 3;
						tempPointNum2 = 2;
						tempPointNum3 = 1;
						break;
					case 1:
						tempPointNum1 = 2;
						tempPointNum2 = 3;
						tempPointNum3 = 0;
						break;
					case 2:
						tempPointNum1 = 1;
						tempPointNum2 = 0;
						tempPointNum3 = 3;
						break;
					case 3:
						tempPointNum1 = 0;
						tempPointNum2 = 1;
						tempPointNum3 = 2;
						break;
					default:
						break;
					}
				}

				tempBigRect[m_shootchip].GetAt(bigselectpos[m_shootchip]).x[tempPointNum1] = x + tempBigRect[m_shootchip].GetAt(bigselectpos[m_shootchip]).x[tempPointNum2] - tempBigRect[m_shootchip].GetAt(bigselectpos[m_shootchip]).x[tempPointNum3];
				tempBigRect[m_shootchip].GetAt(bigselectpos[m_shootchip]).y[tempPointNum1] = y + tempBigRect[m_shootchip].GetAt(bigselectpos[m_shootchip]).y[tempPointNum2] - tempBigRect[m_shootchip].GetAt(bigselectpos[m_shootchip]).y[tempPointNum3];
			
				str.Format("%0.4f", x);
				m_showpointlist.SetItemText(tempPointNum1, 1, str);
				str.Format("%0.4f", y);
				m_showpointlist.SetItemText(tempPointNum1, 2, str);
			}
			else if(2 == m_inputset)
			{
				switch(dragPointNum)
				{
				case 0:
					tempPointNum1 = 3;
					tempPointNum2 = 1;
					break;
				case 1:
					tempPointNum1 = 2;
					tempPointNum2 = 0;
					break;
				case 2:
					tempPointNum1 = 1;
					tempPointNum2 = 3;
					break;
				case 3:
					tempPointNum1 = 0;
					tempPointNum2 = 2;
					break;
				default:
					break;
				}

				tempBigRect[m_shootchip].GetAt(bigselectpos[m_shootchip]).x[tempPointNum1] += offset_x;
				tempBigRect[m_shootchip].GetAt(bigselectpos[m_shootchip]).y[tempPointNum2] += offset_y;
				str.Format("%0.4f", x);
				m_showpointlist.SetItemText(tempPointNum1, 1, str);
				str.Format("%0.4f", y);
				m_showpointlist.SetItemText(tempPointNum2, 2, str);
			}
		}
		else if(dragRect)
		{
			shootChange = true;

			x = (double)(point.x - downPoint.x) / picParam.ratex;
			y = (double)(downPoint.y - point.y) / picParam.ratey;
		//	MoveRects(m_shootchip, x, y);    //图形里面的分级全部一同移动

			if(bigselectpos[m_shootchip] != NULL)
			{
				for(int i=0; i<4; i++)
				{
					tempBigRect[m_shootchip].GetAt(bigselectpos[m_shootchip]).x[i] += x;
					tempBigRect[m_shootchip].GetAt(bigselectpos[m_shootchip]).y[i] += y;
					str.Format("%0.4f", tempBigRect[m_shootchip].GetAt(bigselectpos[m_shootchip]).x[i]);
					m_showpointlist.SetItemText(i, 1, str);
					str.Format("%0.4f", tempBigRect[m_shootchip].GetAt(bigselectpos[m_shootchip]).y[i]);
					m_showpointlist.SetItemText(i, 2, str);
				}
			}
			
			downPoint = point;
		}
		else
		{
			if((2 == m_inputset) && (1 == rectpointnum[m_shootchip]))
			{
				rectdraw.right = m_cMovePoint.x;
				rectdraw.bottom = m_cMovePoint.y;
			}
		}
	
		InvalidateRect(&rect, false);
	}
	CResizingDialog::OnMouseMove(nFlags, point);
}

void CShootDiagram::FreezeWindow()
{
	GetDlgItem(IDC_SetRange)->EnableWindow(false);
	GetDlgItem(IDC_SetLevel)->EnableWindow(false);
	GetDlgItem(IDC_SelectLevel)->EnableWindow(false);
	GetDlgItem(IDC_shootchip1)->EnableWindow(false);
	GetDlgItem(IDC_shootchip2)->EnableWindow(false);
	GetDlgItem(IDC_shootchip3)->EnableWindow(false);
	GetDlgItem(IDC_inputset)->EnableWindow(false);
	GetDlgItem(IDC_lineset)->EnableWindow(false);
	GetDlgItem(IDC_rectset)->EnableWindow(false);
	GetDlgItem(IDC_parallelrectset)->EnableWindow(false);

	GetDlgItem(IDC_LevelStyle)->EnableWindow(false);
	GetDlgItem(IDC_LevelAdjust)->EnableWindow(false);
	GetDlgItem(IDC_parallelrectDrag)->EnableWindow(false);
	GetDlgItem(IDC_ShowLevelPicture)->EnableWindow(false);
}

void CShootDiagram::ReleaseWindow()
{
	GetDlgItem(IDC_SetRange)->EnableWindow(true);
	GetDlgItem(IDC_SetLevel)->EnableWindow(true);
	GetDlgItem(IDC_SelectLevel)->EnableWindow(true);
	GetDlgItem(IDC_shootchip1)->EnableWindow(true);
	GetDlgItem(IDC_shootchip2)->EnableWindow(true);
	GetDlgItem(IDC_shootchip3)->EnableWindow(true);
	GetDlgItem(IDC_inputset)->EnableWindow(true);
	GetDlgItem(IDC_lineset)->EnableWindow(true);
	GetDlgItem(IDC_rectset)->EnableWindow(true);
	GetDlgItem(IDC_parallelrectset)->EnableWindow(true);

	GetDlgItem(IDC_LevelStyle)->EnableWindow(true);
	GetDlgItem(IDC_LevelAdjust)->EnableWindow(true);
	GetDlgItem(IDC_parallelrectDrag)->EnableWindow(true);
	GetDlgItem(IDC_ShowLevelPicture)->EnableWindow(true);
}

void CShootDiagram::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if((point.x >= picParam.left) && (point.x <= (picParam.left + picParam.width)) 
		&& (point.y >= picParam.top) && (point.y <= picParam.top + picParam.height))
	{
		if(!showshoot)
		{
			CString str_x, str_y;
			double x, y;
			x = xstart + (double)m_cMovePoint.x / picParam.ratex;
			y = ystart + (double)(picParam.height - m_cMovePoint.y) / picParam.ratey;
			
			if((0 == m_HandleRange) || (1 == m_HandleRange))
			{			
				str_x.Format("%0.4f", x);
				str_y.Format("%0.4f", y);
							
				if(1 == m_inputset)
				{
					if(pointnum[m_shootchip] < 4)
					{	
						FreezeWindow();
						m_vInputPoint[pointnum[m_shootchip]] = m_cMovePoint;

						m_showpointlist.SetItemText(pointnum[m_shootchip], 1, str_x);
						m_showpointlist.SetItemText(pointnum[m_shootchip], 2, str_y);

						pointnum[m_shootchip]++;

						if(4 == pointnum[m_shootchip])
						{
							if(SetPointInOrder(1))
							{
								if(1 == m_HandleRange)
								{
									m_addlevelbutton.EnableWindow(true);
								}
							
								ReleaseWindow();
							}
							else
							{
								m_showpointlist.SetItemText(3, 1, "");
								m_showpointlist.SetItemText(3, 2, "");
								pointnum[m_shootchip]--;
							}
						}
						
						InvalidateRect(&rect, false);
					}
				}
				else if(2 == m_inputset)
				{
					if(0 == rectpointnum[m_shootchip])
					{
						FreezeWindow();
						rectdraw.left = m_cMovePoint.x;
						rectdraw.top = m_cMovePoint.y;
						m_showpointlist.SetItemText(0, 1, str_x);
						m_showpointlist.SetItemText(0, 2, str_y);
						rectpointnum[m_shootchip] = 1;
					}
					else if(1 == rectpointnum[m_shootchip])
					{
						rectdraw.right = m_cMovePoint.x;
						rectdraw.bottom = m_cMovePoint.y;
						
						if((rectdraw.left != rectdraw.right) && (rectdraw.top != rectdraw.bottom))
						{
							rectpointnum[m_shootchip] = 2;
							
							x = xstart + (double)rectdraw.right / picParam.ratex;
							y = ystart + (double)(picParam.height - rectdraw.top) / picParam.ratey;
							str_x.Format("%0.4f", x);
							str_y.Format("%0.4f", y);
							m_showpointlist.SetItemText(1, 1, str_x);	
							m_showpointlist.SetItemText(1, 2, str_y);
							
							x = xstart + (double)rectdraw.right / picParam.ratex;
							y = ystart + (double)(picParam.height - rectdraw.bottom) / picParam.ratey;
							str_x.Format("%0.4f", x);
							str_y.Format("%0.4f", y);
							m_showpointlist.SetItemText(2, 1, str_x);	
							m_showpointlist.SetItemText(2, 2, str_y);
							
							x = xstart + (double)rectdraw.left / picParam.ratex;
							y = ystart + (double)(picParam.height - rectdraw.bottom) / picParam.ratey;
							str_x.Format("%0.4f", x);
							str_y.Format("%0.4f", y);
							m_showpointlist.SetItemText(3, 1, str_x);	
							m_showpointlist.SetItemText(3, 2, str_y);
							
							SetPointInOrder(1);
							if(1 == m_HandleRange)
							{
								m_addlevelbutton.EnableWindow(true);
							}

							ReleaseWindow();
							InvalidateRect(&rect, false);
						}
					}
				}
				else if(3 == m_inputset)
				{
					if(parallelnum[m_shootchip] < 3)
					{
						FreezeWindow();
						m_vInputPoint[parallelnum[m_shootchip]] = m_cMovePoint;
						
						m_showpointlist.SetItemText(parallelnum[m_shootchip], 1, str_x);
						m_showpointlist.SetItemText(parallelnum[m_shootchip], 2, str_y);
						
						parallelnum[m_shootchip]++;
						
						if(3 ==	parallelnum[m_shootchip])
						{
							m_vInputPoint[3].x = m_vInputPoint[2].x + m_vInputPoint[0].x - m_vInputPoint[1].x; 
							m_vInputPoint[3].y = m_vInputPoint[2].y + m_vInputPoint[0].y - m_vInputPoint[1].y; 
							
							x = xstart + (double)m_vInputPoint[3].x / picParam.ratex;
							y = ystart + (double)(picParam.height - m_vInputPoint[3].y) / picParam.ratey;
							str_x.Format("%0.4f", x);
							str_y.Format("%0.4f", y);
							m_showpointlist.SetItemText(3, 1, str_x);
							m_showpointlist.SetItemText(3, 2, str_y);
							if((x >= 0) && (y >= 0) && SetPointInOrder(1))
							{	
								if(1 == m_HandleRange)
								{
									m_addlevelbutton.EnableWindow(true);
								}

								ReleaseWindow();
							}
							else
							{
								m_showpointlist.SetItemText(2, 1, "");
								m_showpointlist.SetItemText(2, 2, "");
								m_showpointlist.SetItemText(3, 1, "");
								m_showpointlist.SetItemText(3, 2, "");
								parallelnum[m_shootchip]--;
							}
						}
						
						InvalidateRect(&rect, false);
					}
				}
				
				if(1 == m_HandleRange)
				{
					if((0 == m_inputset)
						|| ((1 == m_inputset) && (4 == pointnum[m_shootchip])) 
						|| ((2 == m_inputset) && (2 == rectpointnum[m_shootchip])) 
						|| ((3 == m_inputset) && (3 == parallelnum[m_shootchip])))
					{
						if(0 == m_adjust.GetCheck())
						{
							if(shift)
							{
								shift = false;				
								if(FindSelectedRect2(x, y))
								{
									m_applybutton.EnableWindow(true);
									m_deletebutton.EnableWindow(true);	
								}
								else
								{
									bigselectpos[m_shootchip] = NULL;
									
									if(0 == m_inputset)
									{
										for(int i=0; i<4; i++)
										{
											m_showpointlist.SetItemText(i, 1, "");
											m_showpointlist.SetItemText(i, 2, "");
										}
									}
								}
								InvalidateRect(&rect, false);
							}
						}
						else
						{
							
							if(bigselectpos[m_shootchip] != NULL)
							{
								//////////用于图形拖动
								dragRect = true;
								downPoint = point;

								//////////用于图形调整
								XYLEVELItem item;
								CPoint p[4]; 
								item = tempBigRect[m_shootchip].GetAt(bigselectpos[m_shootchip]);
								for(int i=0; i<4; i++)
								{
									p[i].x = (int)((item.x[i] - xstart) * picParam.ratex) + picParam.left;
									p[i].y = (int)(picParam.height - (item.y[i] - ystart) * picParam.ratey) + picParam.top;
									if((point.x > (p[i].x-4)) 
										&& (point.x < (p[i].x+4)) 
										&& (point.y > (p[i].y-4)) 
										&& (point.y < (p[i].y+4)))
									{
										drag = true;
										dragPointNum = i;
										m_adjust.EnableWindow(false);
										FreezeWindow();

										GetDlgItem(IDC_Apply)->EnableWindow(false);
										GetDlgItem(IDC_DeleteLevel)->EnableWindow(false);
										GetDlgItem(IDC_ShowLevelPicture)->EnableWindow(false);
										GetDlgItem(IDC_DrawPoint)->EnableWindow(false);
									}
								}
							}
						}
					}		
				}
			}
			else if(2 == m_HandleRange)
			{			
				if((FindSelectedRect(x, y))
					&& !ifSmallRect(m_shootchip, selectpos[m_shootchip]))
				{
					m_applybutton.EnableWindow(true);
					m_deletebutton.EnableWindow(true);
					m_binNum.EnableWindow(true);
				}
				else
				{
					selectpos[m_shootchip] = NULL;
					m_applybutton.EnableWindow(false);
					m_deletebutton.EnableWindow(false);
					m_binNum.EnableWindow(false);
				}
				InvalidateRect(&rect, false);
			}
		}
	}
	else
	{
		PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, 0);
	}

	CResizingDialog::OnLButtonDown(nFlags, point);
}

void CShootDiagram::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(drag)
	{
		XYLEVELItem item;
		item = tempBigRect[m_shootchip].GetAt(bigselectpos[m_shootchip]);
		if(IfConvexQuadrangle(item.x, item.y))
		{
			drag = false;
			m_adjust.EnableWindow(true);
			ReleaseWindow();
			GetDlgItem(IDC_Apply)->EnableWindow(true);
			GetDlgItem(IDC_DeleteLevel)->EnableWindow(true);
			GetDlgItem(IDC_ShowLevelPicture)->EnableWindow(true);
			GetDlgItem(IDC_DrawPoint)->EnableWindow(true);
		}	
	}
	
	dragRect = false;

	CResizingDialog::OnLButtonUp(nFlags, point);
}


void CShootDiagram::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(1 == m_HandleRange)
	{
		if(((1 == m_inputset) && (pointnum[m_shootchip] != 4))
			|| ((2 == m_inputset) && (rectpointnum[m_shootchip] != 2))
			|| ((3 == m_inputset) && (parallelnum[m_shootchip] != 3)))
		{
			pointnum[m_shootchip] = 0;
			rectpointnum[m_shootchip] = 0;
			parallelnum[m_shootchip] = 0;
		}
		
		m_addlevelbutton.EnableWindow(true);
		ReleaseWindow();
		InvalidateRect(&rect, false);
	}
	
	CResizingDialog::OnRButtonDown(nFlags, point);
}

///////////////////判断所画图形是否为凸四边形
bool CShootDiagram::IfConvexQuadrangle(double *x, double *y) 
{
	int i = 0;
	double standardy[2];
	double k, b;

	if(x[0] == x[2])
	{
		if(((x[1] > x[0]) && (x[3] < x[0])) 
			|| ((x[1] < x[0]) && (x[3] > x[0])))
		{
			return true;
		}
	}
	else
	{
		k = (y[2] - y[0]) / (x[2] - x[0]);
		b = y[0] - k * x[0];
		standardy[0] = k * x[1] + b;
		standardy[1] = k * x[3] + b;

		if(((standardy[0] > y[1]) && (standardy[1] < y[3])) 
			|| ((standardy[0] < y[1]) && (standardy[1] > y[3])))
		{
			k = (y[1] - y[0]) / (x[1] - x[0]);
			b = y[0] - k * x[0];
			standardy[0] = k * x[2] + b;
			standardy[1] = k * x[3] + b;

			if(((standardy[0] > y[2]) && (standardy[1] > y[3]))
				|| ((standardy[0] < y[2]) && (standardy[1] < y[3])))
			{
				k = (y[1] - y[2]) / (x[1] - x[2]);
				b = y[1] - k * x[1];
				standardy[0] = k * x[0] + b;
				standardy[1] = k * x[3] + b;

				if(((standardy[0] > y[0]) && (standardy[1] > y[3]))
				|| ((standardy[0] < y[0]) && (standardy[1] < y[3])))
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool CShootDiagram::IfRectIntersectionExist() 
{	
	sngPOINT p[4];
	XYLEVELItem item;
	
	for(int i=0; i<4; i++)
	{
		p[i].x = xstart + (double)m_vInputPoint[i].x / picParam.ratex;
		p[i].y = ystart + (double)(picParam.height - m_vInputPoint[i].y) / picParam.ratey;
	}

	POSITION pos = levelItem[m_shootchip].GetHeadPosition();
	while(pos != NULL)
	{
		selectpos[m_shootchip] = pos;
		item = levelItem[m_shootchip].GetNext(pos);
		if(ispointInquadrangle(item.x[0], item.y[0], p, xyRange))
		{
			return true;
		}
	}
	return false;
}

bool CShootDiagram::IfCrossLineExist(int pointnum)
{
	sngPOINT p1, p2;
	XYLEVELItem item;
	LineParam line[2];
	bool vertical = false;
	int i = 0; 
	
	p1.x = xstart + (double)m_vInputPoint[pointnum-1].x / picParam.ratex;
	p1.y = ystart + (double)(picParam.height - m_vInputPoint[pointnum-1].y) / picParam.ratey;
	p2.x = xstart + (double)m_vInputPoint[pointnum].x / picParam.ratex;
	p2.y = ystart + (double)(picParam.height - m_vInputPoint[pointnum].y) / picParam.ratey;
	if(pointnum == 4)
	{
		p2.x = xstart + (double)m_vInputPoint[0].x / picParam.ratex;
		p2.y = ystart + (double)(picParam.height - m_vInputPoint[0].y) / picParam.ratey;
	}

	line[0].x[0] = p1.x;
	line[0].y[0] = p1.y;
	line[0].x[1] = p2.x;
	line[0].y[1] = p2.y;
	if(p1.x == p2.x)
	{
		vertical = true;
	}
	else
	{
		line[0].k = (p2.y - p1.y) / (p2.x - p1.x);
		line[0].b = p1.y - line[0].k * p1.x;
	}
	
	POSITION pos = levelItem[m_shootchip].GetHeadPosition();
	while(pos != NULL)
	{
		selectpos[m_shootchip] = pos;
		item = levelItem[m_shootchip].GetNext(pos);
		
		for(i=0; i<3; i++)
		{
			line[1].x[0] = item.x[i];
			line[1].y[0] = item.y[i];
			line[1].x[1] = item.x[i+1];
			line[1].y[1] = item.y[i+1];	
			if(IfLinesCross(line, vertical))
			{
				return true;
			}
		}
		
		line[1].x[0] = item.x[0];
		line[1].y[0] = item.y[0];
		line[1].x[1] = item.x[3];
		line[1].y[1] = item.y[3];	
		if(IfLinesCross(line, vertical))
		{
			return true;
		}
	}
	
	return false;
}

bool CShootDiagram::IfLinesCross(LineParam *line, bool vertical) 
{
	double x[2] = {0, 0}, y[2] = {0, 0};

	if(line[1].x[0] == line[1].x[1])
	{
		x[1] = line[1].x[0];
		if(vertical)
		{
			x[0] = line[0].x[0];
			if(x[0] == x[1])
			{
				return true;
			}
		
			return false;
		}
		else
		{
			y[0] = line[0].k * x[1] + line[0].b;
			if((y[0] == line[0].y[0])
				|| (y[0] == line[0].y[1])
				|| ((y[0] > line[0].y[0]) && (y[0] < line[0].y[1]))
				|| ((y[0] > line[0].y[1]) && (y[0] < line[0].y[0])))
			{
				return true;
			}

			return false;
		}
	}
	else
	{
		line[1].k = (line[1].y[1] - line[1].y[0]) / (line[1].x[1] - line[1].x[0]);
		line[1].b = line[1].y[0] - line[1].k * line[1].x[0];

		if(vertical)
		{
			x[0] = line[0].x[0];
			y[1] = line[1].k * x[0] + line[1].b;
			
			if((y[1] == line[1].y[0]) 
				|| (y[1] == line[1].y[1])
				|| ((y[1] > line[1].y[0]) && (y[1] < line[1].y[1]))
				|| ((y[1] > line[1].y[1]) && (y[1] < line[1].y[0])))
			{
				return true;
			}

			return false;
		}
		else
		{
			if(line[0].k == line[1].k)
			{
				if(line[0].b == line[1].b)
				{
					return true;
				}

				return false;
			}
			else
			{
				x[1] = (line[1].b - line[0].b) / (line[0].k - line[1].k); 
				if((x[1] == line[1].x[0])
					|| (x[1] == line[1].x[1])
					|| ((x[1] > line[1].x[0]) && (x[1] < line[1].x[1])))
				{
					if((x[1] == line[0].x[0])
					|| (x[1] == line[0].x[1])
					|| ((x[1] > line[0].x[0]) && (x[1] < line[0].x[1]))
					|| ((x[1] > line[0].x[1]) && (x[1] < line[0].x[0])))
					{
						return true;
					}
				}

				return false;
			}
		}
	}

	return false;
}

bool setOrder = false;
//////////////////////////给四点排序 添加图形并显示坐标
bool CShootDiagram::SetPointInOrder(int way)
{
	XYLEVELItem item;
	bool xychoose = true;
	double x[4], y[4];
	double k1, k2;
	int i = 0;

	for(i = 0; i<4; i++)
	{
		str_pointx[i] = m_showpointlist.GetItemText(i, 1);
		str_pointy[i] = m_showpointlist.GetItemText(i, 2);
		x[i] = atof(str_pointx[i]);
		y[i] = atof(str_pointy[i]);
	}

	if(!IfConvexQuadrangle(x, y))
	{
		return false;
	}

	if(x[1] == x[0])
	{
		xychoose = false;
	}
	else if(x[1] == x[2])
	{
		xychoose = true;
	}
	else
	{
		k1 = fabs((y[1] - y[0]) / (x[1] - x[0]));
		k2 = fabs((y[1] - y[2]) / (x[1] - x[2]));
		if(k1 <= k2)
		{
			xychoose = true;
		}
		else
		{
			xychoose = false;
		}
	}

	if(setOrder)
	{
		if(xychoose)
		{
			if(x[0] < x[1])
			{
				if(y[0] < y[3])
				{
					item.x[0] = x[3];
					item.y[0] = y[3];
					item.x[1] = x[2];
					item.y[1] = y[2];
					item.x[2] = x[1];
					item.y[2] = y[1];
					item.x[3] = x[0];
					item.y[3] = y[0];
				}
				else
				{
					item.x[0] = x[0];
					item.y[0] = y[0];
					item.x[1] = x[1];
					item.y[1] = y[1];
					item.x[2] = x[2];
					item.y[2] = y[2];
					item.x[3] = x[3];
					item.y[3] = y[3];	
				}
			}
			else
			{
				if(y[0] < y[3])
				{
					item.x[0] = x[2];
					item.y[0] = y[2];
					item.x[1] = x[3];
					item.y[1] = y[3];
					item.x[2] = x[0];
					item.y[2] = y[0];
					item.x[3] = x[1];
					item.y[3] = y[1];
				}
				else
				{
					item.x[0] = x[1];
					item.y[0] = y[1];
					item.x[1] = x[0];
					item.y[1] = y[0];
					item.x[2] = x[3];
					item.y[2] = y[3];
					item.x[3] = x[2];
					item.y[3] = y[2];
				}
			}
		}
		else
		{
			if(y[0] < y[1])
			{
				if(x[0] < x[3])
				{
					item.x[0] = x[1];
					item.y[0] = y[1];
					item.x[1] = x[2];
					item.y[1] = y[2];
					item.x[2] = x[3];
					item.y[2] = y[3];
					item.x[3] = x[0];
					item.y[3] = y[0];
				}
				else
				{
					item.x[0] = x[2];
					item.y[0] = y[2];
					item.x[1] = x[1];
					item.y[1] = y[1];
					item.x[2] = x[0];
					item.y[2] = y[0];
					item.x[3] = x[3];
					item.y[3] = y[3];
				}
			}
			else
			{
				if(x[0] < x[3])
				{
					item.x[0] = x[0];
					item.y[0] = y[0];
					item.x[1] = x[3];
					item.y[1] = y[3];
					item.x[2] = x[2];
					item.y[2] = y[2];
					item.x[3] = x[1];
					item.y[3] = y[1];
				}
				else
				{
					item.x[0] = x[3];
					item.y[0] = y[3];
					item.x[1] = x[0];
					item.y[1] = y[0];
					item.x[2] = x[1];
					item.y[2] = y[1];
					item.x[3] = x[2];
					item.y[3] = y[2];
				}
			}
		}
	}
	else
	{
		if(xychoose)
		{
			if(x[0] < x[1])
			{
				if(y[0] < y[3])
				{
					item.x[0] = x[0];
					item.y[0] = y[0];
					item.x[1] = x[1];
					item.y[1] = y[1];
					item.x[2] = x[2];
					item.y[2] = y[2];
					item.x[3] = x[3];
					item.y[3] = y[3];
				}
				else
				{
					item.x[0] = x[3];
					item.y[0] = y[3];
					item.x[1] = x[2];
					item.y[1] = y[2];
					item.x[2] = x[1];
					item.y[2] = y[1];
					item.x[3] = x[0];
					item.y[3] = y[0];	
				}
			}
			else
			{
				if(y[0] < y[3])
				{
					item.x[0] = x[1];
					item.y[0] = y[1];
					item.x[1] = x[0];
					item.y[1] = y[0];
					item.x[2] = x[3];
					item.y[2] = y[3];
					item.x[3] = x[2];
					item.y[3] = y[2];
				}
				else
				{
					item.x[0] = x[2];
					item.y[0] = y[2];
					item.x[1] = x[3];
					item.y[1] = y[3];
					item.x[2] = x[0];
					item.y[2] = y[0];
					item.x[3] = x[1];
					item.y[3] = y[1];
				}
			}
		}
		else
		{
			if(y[0] < y[1])
			{
				if(x[0] < x[3])
				{
					item.x[0] = x[0];
					item.y[0] = y[0];
					item.x[1] = x[3];
					item.y[1] = y[3];
					item.x[2] = x[2];
					item.y[2] = y[2];
					item.x[3] = x[1];
					item.y[3] = y[1];
				}
				else
				{
					item.x[0] = x[3];
					item.y[0] = y[3];
					item.x[1] = x[0];
					item.y[1] = y[0];
					item.x[2] = x[1];
					item.y[2] = y[1];
					item.x[3] = x[2];
					item.y[3] = y[2];
				}
			}
			else
			{
				if(x[0] < x[3])
				{
					item.x[0] = x[1];
					item.y[0] = y[1];
					item.x[1] = x[2];
					item.y[1] = y[2];
					item.x[2] = x[3];
					item.y[2] = y[3];
					item.x[3] = x[0];
					item.y[3] = y[0];
				}
				else
				{
					item.x[0] = x[2];
					item.y[0] = y[2];
					item.x[1] = x[1];
					item.y[1] = y[1];
					item.x[2] = x[0];
					item.y[2] = y[0];
					item.x[3] = x[3];
					item.y[3] = y[3];
				}
			}	
		}
	}
		

	if(0 == m_HandleRange)
	{
		TotalRangeItem[m_shootchip] = item;

		pointnum[m_shootchip] = 0;
		rectpointnum[m_shootchip] = 0;
		parallelnum[m_shootchip] = 0;
	}
	else if(1 == m_HandleRange)
	{
		if(0 == way)
		{
			item.num = 0;
			levelItem[m_shootchip].AddTail(item);		
			SetOrderNum(m_shootchip);
		}
		else
		{
			DelAllInRect(m_shootchip, item);
			DelAllBigInRect(m_shootchip, item);
			tempBigRect[m_shootchip].AddTail(item);
			shootChange = true;
		}
		m_applybutton.EnableWindow(true);

		pointnum[m_shootchip] = 4;
		rectpointnum[m_shootchip] = 2;
		parallelnum[m_shootchip] = 3;
	}

	for(i=0; i<4; i++)
	{
		str_pointx[i].Format("%f", item.x[i]); 
		str_pointy[i].Format("%f", item.y[i]); 
		m_showpointlist.SetItemText(i, 1, ReformatString(str_pointx[i]));
		m_showpointlist.SetItemText(i, 2, ReformatString(str_pointy[i]));
	}

	return true;
}

///////////////////////////////查找选中图形
bool CShootDiagram::FindSelectedRect(double x, double y)
{
	XYLEVELItem item;
	sngPOINT p[4];
	int i = 0;
	int num = 0;

	POSITION select;
	POSITION pos = levelItem[m_shootchip].GetHeadPosition();
	while(pos != NULL)
	{	
		select = pos;
		item = levelItem[m_shootchip].GetNext(pos);
		for(i=0; i<4; i++)
		{
			p[i].x = item.x[i];
			p[i].y = item.y[i];
		}

		if(ispointInquadrangle(x, y, p, xyRange))
		{
			for(i=0; i<4; i++)
			{
				str_pointx[i].Format("%0.4f", item.x[i]); 
				str_pointy[i].Format("%0.4f", item.y[i]); 
				m_showpointlist.SetItemText(i, 1, ReformatString(str_pointx[i]));
				m_showpointlist.SetItemText(i, 2, ReformatString(str_pointy[i]));
			}
			
			selectpos[m_shootchip] = select;

			num = levelItem[m_shootchip].GetAt(selectpos[m_shootchip]).num;
			if(showshoot)
			{		
				str_bin = showShootBin[m_shootchip][num];
			}
			else
			{
				str_bin.Format("%d", num+1);
			}
			return true;
		}
	}
	
	return false;
}

bool CShootDiagram::FindNewCIERect(double x, double y)
{
	sngPOINT p[4];

	for(int j=0; j<98; j++)
	{
		for(int i=0; i<4; i++)
		{
			p[i].x = BinCode[j].x[i];
			p[i].y = BinCode[j].y[i];
		}

		if(ispointInquadrangle(x, y, p, xyRange))
		{
			CIERectNum = j;
			return true;
		}
	}

	return false;
}

bool CShootDiagram::FindSelectedRect2(double x, double y)
{
	CPoint start, end;
	XYLEVELItem item;
	sngPOINT p[4];
	int i = 0;

	POSITION select;
	POSITION pos = tempBigRect[m_shootchip].GetHeadPosition();
	while(pos != NULL)
	{	
		select = pos;
		item = tempBigRect[m_shootchip].GetNext(pos);
		for(i=0; i<4; i++)
		{
			p[i].x = item.x[i];
			p[i].y = item.y[i];
		}

		if(ispointInquadrangle(x, y, p, xyRange))
		{
			for(i=0; i<4; i++)
			{
				str_pointx[i].Format("%0.4f", item.x[i]); 
				str_pointy[i].Format("%0.4f", item.y[i]); 
				m_showpointlist.SetItemText(i, 1, ReformatString(str_pointx[i]));
				m_showpointlist.SetItemText(i, 2, ReformatString(str_pointy[i]));
			}
			
			bigselectpos[m_shootchip] = select;
			return true;
		}
	}
	
	return false;
}

/////////////////////////////////打靶
void CShootDiagram::OnDrawPoint() 
{
	// TODO: Add your control notification handler code here
	if(startshoot)
	{
		startshoot = false;
		SetDlgItemText(IDC_DrawPoint, "打    靶");
	}
	else
	{
		UpdateData(true);
		startshoot = true;
		pThread3 = AfxBeginThread(shoot, this);
		SetDlgItemText(IDC_DrawPoint, "停止打靶");
	}
}

UINT shoot(LPVOID lpParam)
{
	CShootDiagram* pInfo = (CShootDiagram*)lpParam;
	ASSERT(pInfo);

	double x = 0, y = 0;
	int bin = 0;
	CString str1, str2;	

	OpenLightSet(selectchiptype, pInfo->m_shootchip);
	while(startshoot)
	{	
		testgetSpectrum(pInfo->m_shootchip);	
		getXY();
		
		x = g_dColorPara.fx;//getX();
		y = g_dColorPara.fy;//getY();
		str1.Format("%0.4f", x);
		str2.Format("%0.4f", y);
		AddTail(x, y);
		
		if(startshoot)
		{
			pInfo->InvalidateRect(&pInfo->rect, false);
			pInfo->SetDlgItemText(IDC_XValue, str1);		
			pInfo->SetDlgItemText(IDC_YValue, str2);	
		}	
	}

	DWORD dwExitCode;
	GetExitCodeThread(pThread3->m_hThread, &dwExitCode);
	AfxEndThread(dwExitCode, true);
	return 0;
}

void AddTail(double x, double y)
{	
	sngPOINT point;
	point.x = x;
    point.y = y;
	dot[0].AddTail(point);
	if(dot[0].GetCount() > 3000)
	{
		dot[0].RemoveHead();
	}
}


///////////////////////////////////切换晶片
void CShootDiagram::Onshootchip1() 
{
	// TODO: Add your control notification handler code here
	startshoot = false;
	m_shootchip = 0;
	SetDlgItemText(IDC_DrawPoint, "打    靶");
	InvalidateRect(&rect, false);
	m_applybutton.EnableWindow(false);
}

void CShootDiagram::Onshootchip2() 
{
	// TODO: Add your control notification handler code here
	startshoot = false;
	m_shootchip = 1;
	SetDlgItemText(IDC_DrawPoint, "打    靶");
	InvalidateRect(&rect, false);
	m_applybutton.EnableWindow(false);
}

void CShootDiagram::Onshootchip3() 
{
	// TODO: Add your control notification handler code here
	startshoot = false;
	m_shootchip = 2;	
	SetDlgItemText(IDC_DrawPoint, "打    靶");
	InvalidateRect(&rect, false);
	m_applybutton.EnableWindow(false);
}

bool CShootDiagram::Oninputpoint() 
{
	// TODO: Add your control notification handler code here
	if(!RefreshBigRect())
	{
		for(int i=0; i<4; i++)
		{
			str_pointx[i] = m_showpointlist.GetItemText(i, 1);
			str_pointy[i] = m_showpointlist.GetItemText(i, 2);
			if((str_pointx[i] == "") || (str_pointy[i] == ""))
			{
				i = 5;
				MessageBox("请完整输入各点坐标");
				return false;
			}
		}
		
		if(SetPointInOrder(1))
		{
			InvalidateRect(&rect, false);
			m_addlevelbutton.EnableWindow(true);
			return true;
		}
	}

	return true;
}

//////////////////////////显示当前晶片设置范围
bool CShootDiagram::setDlgText()
{
	CString str_xnum, str_ynum, str_bin;
	str_xnum.Format("%d", xylevel[m_shootchip].x);
	str_ynum.Format("%d", xylevel[m_shootchip].y);
	str_bin.Format("%d", xylevel[m_shootchip].startbin);
	SetDlgItemText(level_x, str_xnum);
	SetDlgItemText(level_y, str_ynum);
//	SetDlgItemText(levelstartbin, str_bin);

	for(int i=0; i<4; i++)
	{
		str_pointx[i].Format("%f", TotalRangeItem[m_shootchip].x[i]);
		str_pointy[i].Format("%f", TotalRangeItem[m_shootchip].y[i]);
		m_showpointlist.SetItemText(i, 1, ReformatString(str_pointx[i]));
		m_showpointlist.SetItemText(i, 2, ReformatString(str_pointy[i]));
	}	

	return true;
}

//////////////////////////////应用分级
bool CShootDiagram::OnApply() 
{
	// TODO: Add your control notification handler code here
	if(0 == m_adjust.GetCheck())
	{
		XYLEVELItem item;
		CString str_xnum, str_ynum, str, str1, str2;
		double smallx[2] = {0, 0}, smally[2] = {0, 0};
		double scalex[2] = {0, 0}, scaley[2] = {0, 0};
		int i = 0;
		double accuracy_x = 0, accuracy_y = 0;

		shootChange = true;
		
		item.num = 0;
		
		GetDlgItemText(level_x, str_xnum);
		GetDlgItemText(level_y, str_ynum);
		xylevel[m_shootchip].x = atoi(str_xnum);
		xylevel[m_shootchip].y = atoi(str_ynum);
		
		if(xylevel[m_shootchip].x < 0)
		{
			xylevel[m_shootchip].x = 0;
			str_xnum = "1";
			SetDlgItemText(level_x, str_xnum);
		}
		if(xylevel[m_shootchip].y < 0)
		{
			xylevel[m_shootchip].y = 0;
			str_ynum = "1";
			SetDlgItemText(level_y, str_ynum);
		}
		
		if((xylevel[m_shootchip].x < 1) || (xylevel[m_shootchip].y < 1))
		{
			return false;
		}
		if((xylevel[m_shootchip].x * xylevel[m_shootchip].y) > (systemset.intMachineType - xylevel[m_shootchip].startbin))
		{
			MessageBox("分级数过多, 应用失败!");
			return false;
		}
		
		for(i=0; i<4; i++)
		{
			str_pointx[i] = m_showpointlist.GetItemText(i, 1);
			str_pointy[i] = m_showpointlist.GetItemText(i, 2);
			
			item.x[i] = atof(str_pointx[i]);
			item.y[i] = atof(str_pointy[i]);
		}

		accuracy_x = (item.x[1] - item.x[0]) / xylevel[m_shootchip].x;
		accuracy_y = (item.y[3] - item.y[0]) / xylevel[m_shootchip].y;
		
		for(i=1; i<xylevel[m_shootchip].x; i++)
		{
			apply_p[m_shootchip][0][i-1].x = item.x[0] 
				+ i * (item.x[1] - item.x[0]) / xylevel[m_shootchip].x;
			apply_p[m_shootchip][0][i-1].y = item.y[0] 
				+ i * (item.y[1] - item.y[0]) / xylevel[m_shootchip].x;
			apply_p[m_shootchip][1][i-1].x = item.x[3]
				+ i * (item.x[2] - item.x[3]) / xylevel[m_shootchip].x;
			apply_p[m_shootchip][1][i-1].y = item.y[3] 
				+ i * (item.y[2] - item.y[3]) / xylevel[m_shootchip].x;
		}
		for(i=1; i<xylevel[m_shootchip].y; i++)
		{
			apply_p[m_shootchip][2][i-1].x = item.x[0]
				+ i * (item.x[3] - item.x[0]) / xylevel[m_shootchip].y;
			apply_p[m_shootchip][2][i-1].y = item.y[0]
				+ i * (item.y[3] - item.y[0]) / xylevel[m_shootchip].y;	
			apply_p[m_shootchip][3][i-1].x = item.x[1] 
				+ i * (item.x[2] - item.x[1]) / xylevel[m_shootchip].y;
			apply_p[m_shootchip][3][i-1].y = item.y[1] 
				+ i * (item.y[2] - item.y[1]) / xylevel[m_shootchip].y;
		}
		
		if(0 == m_levelstyle.GetCheck())
		{
			LineApply(item, xylevel[m_shootchip].x, xylevel[m_shootchip].y,
				m_shootchip, m_HandleRange, m_AddLevelStyle);
		}
		else
		{
			ColumnApply(item, xylevel[m_shootchip].x, xylevel[m_shootchip].y,
				m_shootchip, m_HandleRange, m_AddLevelStyle);
		}
		SetOrderNum(m_shootchip);
		
		InvalidateRect(&rect, false);
		
		if(1 == m_HandleRange)
		{
			SearchRange(m_shootchip);
		}
		if(2 == m_HandleRange)
		{
			selectpos[m_shootchip] = NULL;
			m_applybutton.EnableWindow(false);
			m_deletebutton.EnableWindow(false);
			m_binNum.EnableWindow(false);
		}

		str1.Format("%0.4f", accuracy_x);
		str2.Format("%0.4f", accuracy_y);
		SetDlgItemText(IDC_XValue, str1);		
		SetDlgItemText(IDC_YValue, str2);
	}
	else
	{
		MessageBox("请先取消图形调整!");
	}

	return true;
}
//////////横分分级
void LineApply(XYLEVELItem item, int x, int y, int chip, int handle, int style)
{
	int i = 0;
	XYLEVELItem XYItem;
	double smallx[2] = {0, 0}, smally[2] = {0, 0};
	double scalex[2] = {0, 0}, scaley[2] = {0, 0};
	bool first = true;
	POSITION pos;

	if(1 == handle)
	{
		DelAllInRect(chip, item);
	}

	for(i=0; i<y; i++)
	{				
		if(0 == i)
		{
			smallx[0] = item.x[0];
			scalex[0] = (item.x[1] - item.x[0]) / x;
		}
		else
		{
			smallx[0] = apply_p[chip][2][i-1].x;
			scalex[0] = (apply_p[chip][3][i-1].x - apply_p[chip][2][i-1].x) / x;	
		}

		if(i == (y - 1))
		{
			smallx[1] = item.x[3];
			scalex[1] = (item.x[2] - item.x[3]) / x;
		}
		else
		{
			smallx[1] = apply_p[chip][2][i].x;
			scalex[1] = (apply_p[chip][3][i].x - apply_p[chip][2][i].x) / x;
		}
		
		for(int j=0; j<x; j++)
		{				
			if(0 == j)
			{
				smally[0] = item.y[0];
				scaley[0] = (item.y[3] - item.y[0]) / y;
			}
			else
			{
				smally[0] = apply_p[chip][0][j-1].y;
				scaley[0] = (apply_p[chip][1][j-1].y - apply_p[chip][0][j-1].y) / y;
			}

			if(j == (x - 1))
			{
				smally[1] = item.y[1];
				scaley[1] = (item.y[2] - item.y[1]) / y;
			}
			else
			{
				smally[1] = apply_p[chip][0][j].y;
				scaley[1] = (apply_p[chip][1][j].y - apply_p[chip][0][j].y) / y;
			}
			
			XYItem.x[0] = smallx[0] + j * scalex[0]; 
			XYItem.y[0] = smally[0] + i * scaley[0];
			XYItem.x[1] = smallx[0] + (j + 1) * scalex[0];
			XYItem.y[1] = smally[1] + i * scaley[1];
			XYItem.x[2] = smallx[1] + (j + 1) * scalex[1]; 
			XYItem.y[2] = smally[1] + (i + 1) * scaley[1];
			XYItem.x[3] = smallx[1] + j * scalex[1];
			XYItem.y[3] = smally[0] + (i + 1) * scaley[0];
			
			XYItem.num = 0;
			HandleAddLevelStyle(style, XYItem.num, chip);
			if((2 == handle) && first)
			{
				first = false;
				levelItem[chip].GetAt(selectpos[chip]) = XYItem;
				smallRectPos[chip].AddTail(selectpos[chip]);
			}
			else
			{
				levelItem[chip].AddTail(XYItem);
				if(2 == handle)
				{
					pos = levelItem[chip].GetTailPosition();
					smallRectPos[chip].AddTail(pos);
				}
			}	
		}
	}
}
/////////////竖分分级
void ColumnApply(XYLEVELItem item, int x, int y, int chip, int handle, int style)
{
	int i = 0;
	XYLEVELItem XYItem;
	bool first = true;
	double smallx[2] = {0, 0}, smally[2] = {0, 0};
	double scalex[2] = {0, 0}, scaley[2] = {0, 0};
	POSITION pos;

	if(1 == handle)
	{
		DelAllInRect(chip, item);
	}

	for(int j=0; j<x; j++)
	{	
		if(0 == j)
		{
			smally[0] = item.y[0];
			scaley[0] = (item.y[3] - item.y[0]) / y;
		}
		else
		{
			smally[0] = apply_p[chip][0][j-1].y;
			scaley[0] = (apply_p[chip][1][j-1].y - apply_p[chip][0][j-1].y) / y;
		}
		
		if(j == (x - 1))
		{
			smally[1] = item.y[1];
			scaley[1] = (item.y[2] - item.y[1]) / y;
		}
		else
		{
			smally[1] = apply_p[chip][0][j].y;
			scaley[1] = (apply_p[chip][1][j].y - apply_p[chip][0][j].y) / y;
		}
		
		for(int i=0; i<y; i++)
		{		
			if(0 == i)
			{
				smallx[0] = item.x[0];
				scalex[0] = (item.x[1] - item.x[0]) / x;
			}
			else
			{
				smallx[0] = apply_p[chip][2][i-1].x;
				scalex[0] = (apply_p[chip][3][i-1].x - apply_p[chip][2][i-1].x) / x;	
			}
			
			if(i == (y - 1))
			{
				smallx[1] = item.x[3];
				scalex[1] = (item.x[2] - item.x[3]) / x;
			}
			else
			{
				smallx[1] = apply_p[chip][2][i].x;
				scalex[1] = (apply_p[chip][3][i].x - apply_p[chip][2][i].x) / x;
			}
			
			XYItem.x[0] = smallx[0] + j * scalex[0]; 
			XYItem.y[0] = smally[0] + i * scaley[0];
			XYItem.x[1] = smallx[0] + (j + 1) * scalex[0];
			XYItem.y[1] = smally[1] + i * scaley[1];
			XYItem.x[2] = smallx[1] + (j + 1) * scalex[1]; 
			XYItem.y[2] = smally[1] + (i + 1) * scaley[1];
			XYItem.x[3] = smallx[1] + j * scalex[1];
			XYItem.y[3] = smally[0] + (i + 1) * scaley[0];

			XYItem.num = 0;
			HandleAddLevelStyle(style, XYItem.num, chip);
			if((2 == handle) && first)
			{
				first = false;
				levelItem[chip].GetAt(selectpos[chip]) = XYItem;
				smallRectPos[chip].AddTail(selectpos[chip]);
			}
			else
			{
				levelItem[chip].AddTail(XYItem);
				if(2 == handle)
				{
					pos = levelItem[chip].GetTailPosition();
					smallRectPos[chip].AddTail(pos);
				}
			}	
		}
	}
}

////////////////////////////选择分级处理类型: 总范围/添加分级/选择分级
void CShootDiagram::OnSetRange() 
{
	// TODO: Add your control notification handler code here
	selectpos[m_shootchip] = NULL;
	bigselectpos[m_shootchip] = NULL;
	m_HandleRange = 0;
	m_applybutton.EnableWindow(false);
	m_deletebutton.EnableWindow(false);
	m_addlevelbutton.EnableWindow(false);
	GetDlgItem(IDC_ClearPicture)->EnableWindow(true);
	
	if((4 == pointnum[m_shootchip])
		|| (2 == rectpointnum[m_shootchip])
		|| (3 == parallelnum[m_shootchip]))
	{
		pointnum[m_shootchip] = 0;
		rectpointnum[m_shootchip] = 0;
		parallelnum[m_shootchip] = 0;
	}
		
	InvalidateRect(&rect, false);
}

void CShootDiagram::OnSetLevel() 
{
	// TODO: Add your control notification handler code here
	selectpos[m_shootchip] = NULL;
	bigselectpos[m_shootchip] = NULL;
	m_HandleRange = 1;
	m_deletebutton.EnableWindow(false);
	m_applybutton.EnableWindow(false);
	m_binNum.EnableWindow(false);
	GetDlgItem(IDC_ClearPicture)->EnableWindow(true);
	
	if(0 == m_inputset)
	{
		m_inputpoint.EnableWindow(true);
	}

	if(((1 == m_inputset) && (4 == pointnum[m_shootchip])) 
		|| ((2 == m_inputset) && (2 == rectpointnum[m_shootchip])) 
		|| ((3 == m_inputset) && (3 == parallelnum[m_shootchip])))
	{
		m_addlevelbutton.EnableWindow(true);
	}

	InvalidateRect(&rect, false);
}

void CShootDiagram::OnSelectLevel() 
{
	// TODO: Add your control notification handler code here
	selectpos[m_shootchip] = NULL;
	bigselectpos[m_shootchip] = NULL;
	m_HandleRange = 2;
	m_inputpoint.EnableWindow(false);
	m_applybutton.EnableWindow(false);
	m_deletebutton.EnableWindow(false);
	m_addlevelbutton.EnableWindow(false);
	GetDlgItem(IDC_ClearPicture)->EnableWindow(false);

	InvalidateRect(&rect, false);
}

////////////////添加分级
void CShootDiagram::OnAddLevel() 
{
	// TODO: Add your control notification handler code here
	for(int i=0; i<4; i++)
	{
		m_showpointlist.SetItemText(i, 1, "");
		m_showpointlist.SetItemText(i, 2, "");
	}
	m_inputpoint.EnableWindow(true);
	pointnum[m_shootchip] = 0;
	rectpointnum[m_shootchip] = 0;
	parallelnum[m_shootchip] = 0;
	
	m_addlevelbutton.EnableWindow(false);
	m_applybutton.EnableWindow(false);
	
	bigselectpos[m_shootchip] = NULL;
	InvalidateRect(&rect, false);
}

//////////////////删除分级
void CShootDiagram::OnDeleteLevel() 
{
	// TODO: Add your control notification handler code here
	if(selectpos[m_shootchip] != NULL)
	{
		shootChange = true;
		levelItem[m_shootchip].RemoveAt(selectpos[m_shootchip]);
		SetOrderNum(m_shootchip);
		
		for(int i=0; i<4; i++)
		{
			m_showpointlist.SetItemText(i, 1, "");
			m_showpointlist.SetItemText(i, 2, "");
		}
		
		InvalidateRect(&rect, false);
		selectpos[m_shootchip] = NULL;
		m_applybutton.EnableWindow(false);
		m_deletebutton.EnableWindow(false);
		m_binNum.EnableWindow(false);
		
		POSITION pos = levelItem[m_shootchip].GetHeadPosition();
		if(pos == NULL)
		{
			pointnum[m_shootchip] = 0;
			rectpointnum[m_shootchip] = 0;
			parallelnum[m_shootchip] = 0;
		}
	}

	if(bigselectpos[m_shootchip] != NULL)
	{
		XYLEVELItem item;
		item = tempBigRect[m_shootchip].GetAt(bigselectpos[m_shootchip]);
		DelAllInRect(m_shootchip, item);
		tempBigRect[m_shootchip].RemoveAt(bigselectpos[m_shootchip]);
		bigselectpos[m_shootchip] = NULL;
		InvalidateRect(&rect, false);
		m_applybutton.EnableWindow(false);
		m_deletebutton.EnableWindow(false);
		m_binNum.EnableWindow(false);
		shootChange = true;
	}
}
////////////////////////////调整指定分级
void CShootDiagram::OnLevelAdjust() 
{
	// TODO: Add your control notification handler code here
	if(bigselectpos[m_shootchip] != NULL)
	{
		XYLEVELItem item;
		item = tempBigRect[m_shootchip].GetAt(bigselectpos[m_shootchip]);
		DelAllInRect(m_shootchip, item);
		SetPointInOrder(1);	
	}
	else
	{
		m_adjust.SetCheck(0);
		MessageBox("请先(shift+单击图形)选中要调整的图形!");
	}
	InvalidateRect(&rect, false);
}

///////////////////////添加分级方式: 覆盖/插入
void CShootDiagram::OnCoverLevel() 
{
	// TODO: Add your control notification handler code here
	m_AddLevelStyle = 0;
}

void CShootDiagram::OnInsertLevel() 
{
	// TODO: Add your control notification handler code here
	m_AddLevelStyle = 1;
}

//////////////////////////添加分级方式: 手动输入/画线/矩形/平行四边形
void CShootDiagram::Oninputset() 
{
	// TODO: Add your control notification handler code here
	for(int i=0; i<4; i++)
	{
		m_showpointlist.SetItemText(i, 1, "");
		m_showpointlist.SetItemText(i, 2, "");
	}

	m_inputset = 0;
	if((0 == m_HandleRange) || (1 == m_HandleRange))
	{
		m_inputpoint.EnableWindow(true);
	}	

}

void CShootDiagram::Onlineset() 
{
	// TODO: Add your control notification handler code her
	if(0 ==	m_inputset)
	{
		m_applybutton.EnableWindow(false);
	}
	
	m_inputset = 1;
	m_inputpoint.EnableWindow(false);

}

void CShootDiagram::Onrectset() 
{
	// TODO: Add your control notification handler code here
	if(0 ==	m_inputset)
	{
		m_applybutton.EnableWindow(false);
	}

	m_inputset = 2;
	m_inputpoint.EnableWindow(false);

}

void CShootDiagram::Onparallelrectset() 
{
	// TODO: Add your control notification handler code here
	if(0 ==	m_inputset)
	{
		m_applybutton.EnableWindow(false);
	}

	m_inputset = 3;
	m_inputpoint.EnableWindow(false);

//	KillTimer(1);
}

/////////////////查看分级总数 选中分级的bin
void CShootDiagram::OnCheckBinNum() 
{
	// TODO: Add your control notification handler code here
}

void CShootDiagram::OnShowLevelPicture() 
{
	// TODO: Add your control notification handler code here
	if(0 == m_HandleRange)
	{
		GetRange(m_shootchip);
		setDlgText();
	}
	else if((1 == m_HandleRange) || (2 == m_HandleRange))
	{
		InitXYLEVELItem(m_shootchip);
		SearchRange(m_shootchip);
		POSITION pos = levelItem[m_shootchip].GetHeadPosition();
		if(pos == NULL)
		{
			m_applybutton.EnableWindow(false);
			if((4 == pointnum[m_shootchip])
				|| (2 == rectpointnum[m_shootchip])
				|| (3 == parallelnum[m_shootchip]))
			{
				pointnum[m_shootchip] = 0;
				rectpointnum[m_shootchip] = 0;
				parallelnum[m_shootchip] = 0;
			}
		}
		selectpos[m_shootchip] = NULL;
		bigselectpos[m_shootchip] = NULL;
	}
	InvalidateRect(&rect, false);
}

void CShootDiagram::OnClearPicture() 
{
	// TODO: Add your control notification handler code here
	int i = 0;
	if(0 == m_HandleRange)
	{
		for(i=0; i<4; i++)
		{
			TotalRangeItem[m_shootchip].x[i] = 0;
			TotalRangeItem[m_shootchip].y[i] = 0;
		}
	}
	else if(1 == m_HandleRange)
	{
		drag = false;
		shootChange = true;
		levelItem[m_shootchip].RemoveAll();	
		tempBigRect[m_shootchip].RemoveAll();
		smallRectPos[m_shootchip].RemoveAll();
		bigselectpos[m_shootchip] = NULL;
	}
	
	pointnum[m_shootchip] = 0;
	rectpointnum[m_shootchip] = 0;
	parallelnum[m_shootchip] = 0;
	m_applybutton.EnableWindow(false);
	m_addlevelbutton.EnableWindow(false);
	m_binNum.EnableWindow(false);
	
	for(i=0; i<4; i++)
	{
		m_showpointlist.SetItemText(i, 1, "");
		m_showpointlist.SetItemText(i, 2, "");
	}

	ReleaseWindow();
	InvalidateRect(&rect, false);	
}

void CShootDiagram::OnClearDot() 
{
	// TODO: Add your control notification handler code here
	dot[0].RemoveAll();
	InvalidateRect(&rect, false);
}

void CShootDiagram::OnExit() 
{
	// TODO: Add your control notification handler code here	
	startshoot = false;
	shootopen = false;
	KillTimer(0);
	KillTimer(1);
	CResizingDialog::OnClose();
}

void CShootDiagram::OnSure() 
{
	// TODO: Add your control notification handler code here
	startshoot = false;
	if(OnSave())
	{
		shootopen = false;
		KillTimer(0);
		KillTimer(1);
		OnClose();
	}
}

bool CShootDiagram::OnSave() 
{
	// TODO: Add your control notification handler code here
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<4; j++)
		{
			point[i][j].x = TotalRangeItem[i].x[j];
			point[i][j].y = TotalRangeItem[i].y[j];
		}	
	}
	
	XYLevelSave();
	updatelevellist = true;
	return true;
}

void CShootDiagram::XYLevelSave()
{
	int line = 0;
	XYLEVELItem item;
	POSITION pos;
	int bin = 1;
//	CString str;
//	GetDlgItemText(levelstartbin, str);  ////原本是用来设置从哪个bin开始分级的  现默认为1
//	bin = atoi(str);
	int num = 0;

	for(int i=0; i<3; i++)
	{
		num = ExistLevels(i, bin);
		pos = NULL;
		pos = levelItem[i].GetHeadPosition();
		while(pos != NULL)
		{
			item = levelItem[i].GetNext(pos);
			if(item.num >= 0)
			{
				if(0 == m_accu.GetCheck())
				{
					SetBinArrayXYZItem(item, bin, binArray.strBinArray, i);
				}
				else
				{
					SetBinArrayXYZItem2(item, bin, binArray.strBinArray, i, num);
				}
			}
		}
	}
}

void CShootDiagram::OnEnableResize() 
{
	// TODO: Add your control notification handler code here
	if(resize)
	{
		double start[2], end[2];
		CString str;
		GetDlgItemText(IDC_XStart, str);
		start[0] = atof(str);
		GetDlgItemText(IDC_XEnd, str);
		end[0] = atof(str);
		GetDlgItemText(IDC_YStart, str);
		start[1] = atof(str);
		GetDlgItemText(IDC_YEnd, str);
		end[1] = atof(str);

		if((end[0] < 0) || (end[1] < 0) || (start[0] < 0) || (start[1] < 0))
		{
			MessageBox("输入的坐标值不能小于0");
			m_resize.SetCheck(1);
			return;
		}
		
		if((start[0] > 0.7) || (end[0] > 0.8) || (start[1] > 0.8) || (end[1] > 0.9))
		{
			MessageBox("输入坐标值超出范围");
			m_resize.SetCheck(1);
			return;
		}

	//	if(((end[0] - start[0]) >= 0.1) && ((end[1] - start[1]) >= 0.1))
	//	{
			resize = false;

			xstart = start[0];
			xend = end[0];
			ystart = start[1];
			yend = end[1];

			XRate = 0.8 / (xend - xstart);
			YRate = 0.9 / (yend - ystart);
			
			picParam.ratex = picParam.scalex * XRate/ 0.05;
			picParam.ratey = picParam.scaley * YRate/ 0.05;
			
			m_xstart.ShowWindow(SW_HIDE);
			m_xend.ShowWindow(SW_HIDE);
			m_ystart.ShowWindow(SW_HIDE);
			m_yend.ShowWindow(SW_HIDE);
			
			InvalidateRect(false);
			InvalidateRect(&rect, false);
	//	}
	//	else
	//	{
	//		m_resize.SetCheck(1);
	//	}

		GetDlgItem(IDC_ShowScale)->EnableWindow(true);
		GetDlgItem(IDC_SelectCIEPicture)->EnableWindow(true);
	}
	else
	{
		resize = true;
		m_xstart.ShowWindow(SW_SHOW);
		m_xend.ShowWindow(SW_SHOW);
		m_ystart.ShowWindow(SW_SHOW);
		m_yend.ShowWindow(SW_SHOW);

		CString str;
		str.Format("%0.2f", xstart);
		SetDlgItemText(IDC_XStart, str);
		str.Format("%0.2f", xend);
		SetDlgItemText(IDC_XEnd, str);
		str.Format("%0.2f", ystart);
		SetDlgItemText(IDC_YStart, str);
		str.Format("%0.2f", yend);
		SetDlgItemText(IDC_YEnd, str);

		GetDlgItem(IDC_ShowScale)->EnableWindow(false);
		GetDlgItem(IDC_SelectCIEPicture)->EnableWindow(false);
	}
}

void CShootDiagram::enlarge(double staPointX, double staPointY) 
{
	double start[2], end[2];
	start[0] = xstart;
	start[1] = ystart;
	end[0] = xend;
	end[1] = yend;
	
	if(((end[0] - start[0]) >= 0.1) && ((end[1] - start[1]) >= 0.1))
	{
		xstart = staPointX - (staPointX - start[0]) * ChangeRate;
		xend = staPointX + (end[0] - staPointX) * ChangeRate;
		ystart = staPointY - (staPointY - start[1]) * ChangeRate;
		yend = staPointY + (end[1] - staPointY) * ChangeRate;
		
		XRate /= ChangeRate;
		YRate /= ChangeRate;
		picParam.ratex = picParam.scalex * XRate/ 0.05;
		picParam.ratey = picParam.scaley * YRate/ 0.05;
		
		InvalidateRect(&rect, false);
	}
}

void CShootDiagram::smaller(double staPointX, double staPointY)
{
	double start[2], end[2];
	start[0] = xstart;
	start[1] = ystart;
	end[0] = xend;
	end[1] = yend;

	if((start[0] >= 0) && (start[1] >= 0) 
		&& (staPointX >= (staPointX - start[0]) / ChangeRate)
		&& (staPointY >= (staPointY - start[1]) / ChangeRate))
	{
		xstart = staPointX - (staPointX - start[0]) / ChangeRate;
		xend = staPointX + (end[0] - staPointX) / ChangeRate;
		ystart = staPointY - (staPointY - start[1]) / ChangeRate;
		yend = staPointY + (end[1] - staPointY) / ChangeRate;
		
		XRate *= ChangeRate;
		YRate *= ChangeRate;
		picParam.ratex = picParam.scalex * XRate/ 0.05;
		picParam.ratey = picParam.scaley * YRate/ 0.05;
		
		InvalidateRect(&rect, false);
	}
	else
	{
		xstart = 0;
		xend = 0.8;
		ystart = 0;
		yend = 0.9;
		XRate = 1;
		YRate = 1;
		picParam.ratex = picParam.scalex * XRate/ 0.05;
		picParam.ratey = picParam.scaley * YRate/ 0.05;
		
		InvalidateRect(&rect, false);
	}
}

void CShootDiagram::OnEnlarge() 
{
	// TODO: Add your control notification handler code here
	double staPointX, staPointY;
	staPointX = (xstart + xend) / 2;
	staPointY = (ystart + yend) / 2;
	enlarge(staPointX, staPointY); 
}

void CShootDiagram::OnSmaller() 
{
	// TODO: Add your control notification handler code here
	double staPointX, staPointY;
	staPointX = (xstart + xend) / 2;
	staPointY = (ystart + yend) / 2;
	smaller(staPointX, staPointY); 
}

BOOL CShootDiagram::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	// TODO: Add your message handler code here and/or call default
	if((pt.x >= picParam.left) && (pt.x <= (picParam.left + picParam.width)) 
		&& (pt.y >= picParam.top) && (pt.y <= picParam.top + picParam.height))
	{
		if(!m_showscale)
		{
			double x, y;
			double staPointX, staPointY;
			
			x = pt.x - picParam.left;
			y = pt.y - picParam.top;
			staPointX = xstart + (double)x / picParam.ratex;
			staPointY = ystart + (double)(picParam.height - y) / picParam.ratey;
			
			if(zDelta == 120)
			{
				enlarge(staPointX, staPointY); 
			}
			else if(zDelta == -120)
			{
				smaller(staPointX, staPointY);
			}
		}
	}
	return CResizingDialog::OnMouseWheel(nFlags, zDelta, pt);
}


void CShootDiagram::OnClickShowPointList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
}


///////XY分级文件
CString XYFilePath;

void CShootDiagram::OnXYlevelFile() 
{
	// TODO: Add your control notification handler code here
	PopupMenu(IDR_MENU2, 5, this);
}

void CShootDiagram::OnImportXYLevel() 
{
	// TODO: Add your command handler code here
	CString sz = "CSV file (*.csv)|*.csv|All File(*.*)|*.*||";
	CFileDialog dlg(true, ".csv", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, sz, this);
	CFileException e;

	if(IDOK==dlg.DoModal())
	{
		CString path = dlg.GetPathName();
		CStdioFile m_file;
		if(m_file.Open((LPCTSTR)path, CFile::modeReadWrite, &e))
		{
			if(ReadXYLevelCSVFile(&m_file))
			{
				shootChange = true;
				m_file.Close();	
				
				XYFilePath = path;
				SetDlgItemText(IDC_XYFilePath, XYFilePath);
				InvalidateRect(&rect, false);

				for(int i=0; i<3; i++)
				{
					SearchRange(i);
				}
			}
			else
			{
				m_file.Close();
				MessageBox("文件类型不正确!");
			}
		}
		else
		{
			CString sss;
			sss.Format("%d", e.m_cause);
			MessageBox(sss);
			MessageBox("文件打开失败!");
		}
	}		
}

void CShootDiagram::OnExportXYLevel() 
{
	// TODO: Add your command handler code here
	CString sz = "CSV file (*.csv)|*.csv|All File(*.*)|*.*||";
	CFileDialog dlg(false, ".csv", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, sz, this);

	if(IDOK==dlg.DoModal())
	{
		CString path = dlg.GetPathName();
		CStdioFile m_file;
		if(m_file.Open((LPCTSTR)path, CFile::modeCreate|CFile::modeReadWrite))
		{
			WriteXYLevelCSVFile(&m_file);
			m_file.Close();
		}
		else
		{
			MessageBox("文件另存失败!");
		}
	}
}

void CShootDiagram::OnSaveXYLevel() 
{
	// TODO: Add your command handler code here
	CString path;
	path = XYFilePath;

	CStdioFile m_file;
	if(m_file.Open((LPCTSTR)path, CFile::modeReadWrite))
	{
		WriteXYLevelCSVFile(&m_file);
		m_file.Close();
	}
	else
	{
		MessageBox("文件保存失败!");
	}
}

void CShootDiagram::OnSaveShootDot() 
{
	// TODO: Add your command handler code here
	CString sz = "CSV file (*.csv)|*.csv|All File(*.*)|*.*||";
	CFileDialog dlg(false, ".csv", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, sz, this);

	if(IDOK==dlg.DoModal())
	{
		CString path = dlg.GetPathName();
		CStdioFile m_file;
		if(m_file.Open((LPCTSTR)path, CFile::modeCreate|CFile::modeReadWrite))
		{
			WriteShootDotCSVFile(&m_file);
			m_file.Close();
		}
		else
		{
			MessageBox("文件另存失败!");
		}
	}
}

void CShootDiagram::OnLoadShootDot() 
{
	// TODO: Add your command handler code here
	CString sz = "CSV file (*.csv)|*.csv|All File(*.*)|*.*||";
	CFileDialog dlg(true, ".csv", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, sz, this);
	CFileException e;

	if(IDOK==dlg.DoModal())
	{
		CString path = dlg.GetPathName();
		CStdioFile m_file;
		if(m_file.Open((LPCTSTR)path, CFile::modeReadWrite, &e))
		{		
			if(ReadShootDotCSVFile(&m_file))
			{	
				InvalidateRect(&rect, false);
			}
			else
			{
				MessageBox("文件类型不正确!");
			}
			m_file.Close();
		}
		else
		{
			CString sss;
			sss.Format("%d", e.m_cause);
			MessageBox(sss);
			MessageBox("文件打开失败!");
		}
	}		
}

void CShootDiagram::SetDialogFace()
{
	m_exit.SetBitmaps(IDB_Button_ExitNormal, IDB_Button_ExitDown,
		                 IDB_Button_ExitHigh, IDB_Button_ExitDisable);
	m_exit.SizeToContent();

	
	m_setColor.SetBitmaps(IDB_setColor, IDB_setColor,
		                 IDB_setColor, IDB_setColor);
	m_setColor.SizeToContent();

	m_file.SetBitmaps(IDB_ShootFileNormal, IDB_ShootFileDown,
		                 IDB_ShootFileHigh, IDB_ShootFileDisable);
	m_file.SizeToContent();
	
	m_inputpoint.SetBitmaps(IDB_ShowPointNormal, IDB_ShowPointDown,
		                 IDB_ShowPointHigh, IDB_ShowPointDisable);
	m_inputpoint.SizeToContent();

	m_clearPicture.SetBitmaps(IDB_ClearPicNormal, IDB_ClearPicDown,
		                 IDB_ClearPicHigh, IDB_ClearPicDisable);
	m_clearPicture.SizeToContent();

	m_clearDot.SetBitmaps(IDB_ClearDotNormal, IDB_ClearDotDown,
		                 IDB_ClearDotHigh, IDB_ClearDotDisable);
	m_clearDot.SizeToContent();

	m_shootpoint.SetBitmaps(IDB_DotNormal, IDB_DotDown,
		                 IDB_DotHigh, IDB_DotDisable);
	m_shootpoint.SizeToContent();
	m_shootpoint.SetDrawText(true, false)
			.SetFont3D(true, 0, 0, false)
		    .SetFontSize(10, false)
			.SetForceColor(RGB(255, 255, 255), RGB(255, 255, 255), RGB(255, 255, 255), false);


	m_applybutton.SetBitmaps(IDB_ApplyBTNormal, IDB_ApplyBTDown,
		                 IDB_ApplyBTHigh, IDB_ApplyBTDisable);
	m_applybutton.SizeToContent();

	m_showLevel.SetBitmaps(IDB_ShowLevelNormal, IDB_ShowLevelDown,
		                 IDB_ShowLevelHigh, IDB_ShowLevelDisable);
	m_showLevel.SizeToContent();

	m_addlevelbutton.SetBitmaps(IDB_AddLevelNormal, IDB_AddLevelDown,
		                 IDB_AddLevelHigh, IDB_AddLevelDisable);
	m_addlevelbutton.SizeToContent();

	m_deletebutton.SetBitmaps(IDB_DelLevelNormal, IDB_DelLevelDown,
		                 IDB_DelLevelHigh, IDB_DelLevelDisable);
	m_deletebutton.SizeToContent();

	m_binNum.SetBitmaps(IDB_BinNumNormal, IDB_BinNumDown,
		                 IDB_BinNumHigh, IDB_BinNumDisable);
	m_binNum.SizeToContent();
	
}

BOOL CShootDiagram::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message == WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
		case VK_DELETE:
			OnDeleteLevel();
			return true;
		case VK_SHIFT:
			shift = true;
			return true;
		}
	}

	return CResizingDialog::PreTranslateMessage(pMsg);
}

BOOL CShootDiagram::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return CResizingDialog::DrawBK(pDC, IDB_ShootBK, 0);
//	return CResizingDialog::OnEraseBkgnd(pDC);
}

HBRUSH CShootDiagram::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CResizingDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if(nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		nCtlColor = RGB(120, 195, 232);
		hbr = (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}


void CShootDiagram::OnUpdateShowCIELine(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(IfMenuCheck(&m_menu, ID_ShowCIELine))
	{
		pCmdUI->SetCheck(1);
	}
	else 
	{
		pCmdUI->SetCheck(0);
	}
}

void CShootDiagram::OnShowCIELine() 
{
	// TODO: Add your command handler code here
	if(IfMenuCheck(&m_menu, ID_ShowCIELine))
	{
		showCIELine = false;
		m_menu.CheckMenuItem(ID_ShowCIELine, MF_UNCHECKED);
	}
	else
	{
		showCIELine = true;
		m_menu.CheckMenuItem(ID_ShowCIELine, MF_CHECKED);
	}

	InvalidateRect(&rect, false);
}

void CShootDiagram::OnNewCIERect() 
{
	// TODO: Add your command handler code here
	if(IfMenuCheck(&m_menu, ID_NewCIERect))
	{
		newCIERect = false;
		m_menu.CheckMenuItem(ID_NewCIERect, MF_UNCHECKED);
	}
	else
	{
		newCIERect = true;
		m_menu.CheckMenuItem(ID_NewCIERect, MF_CHECKED);
	}

	InvalidateRect(&rect, false);
}

void CShootDiagram::OnUpdateNewCIERect(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(IfMenuCheck(&m_menu, ID_NewCIERect))
	{
		pCmdUI->SetCheck(1);
	}
	else 
	{
		pCmdUI->SetCheck(0);
	}
}

void CShootDiagram::OnFigureRange() 
{
	// TODO: Add your control notification handler code here
	if(0 == m_figureRange.GetCheck())
	{
		tempBigRect[m_shootchip].RemoveAll();
		smallRectPos[m_shootchip].RemoveAll();	
	}
	else
	{
		SearchRange(m_shootchip);
	}
	InvalidateRect(&rect, false);
}

void CShootDiagram::OnImportXYLevel2() 
{
	// TODO: Add your command handler code here
	CString sz = "CSV file (*.csv)|*.csv|All File(*.*)|*.*||";
	CFileDialog dlg(true, ".csv", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, sz, this);
	CFileException e;

	if(IDOK==dlg.DoModal())
	{
		CString path = dlg.GetPathName();
		CStdioFile m_file;
		if(m_file.Open((LPCTSTR)path, CFile::modeReadWrite, &e))
		{
			if(ReadXYLevelCSVFile2(&m_file))
			{
				shootChange = true;
				m_file.Close();	
				
				XYFilePath = path;
				SetDlgItemText(IDC_XYFilePath, XYFilePath);
				InvalidateRect(&rect, false);

				for(int i=0; i<3; i++)
				{
					SearchRange(i);
				}
			}
			else
			{
				m_file.Close();
				MessageBox("文件类型不正确!");
			}
		}
		else
		{
			CString sss;
			sss.Format("%d", e.m_cause);
			MessageBox(sss);
			MessageBox("文件打开失败!");
		}
	}		
}

void CShootDiagram::OnExportXYLevel2() 
{
	// TODO: Add your command handler code here
	CString sz = "CSV file (*.csv)|*.csv|All File(*.*)|*.*||";
	CFileDialog dlg(false, ".csv", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, sz, this);

	if(IDOK==dlg.DoModal())
	{
		CString path = dlg.GetPathName();
		CStdioFile m_file;
		if(m_file.Open((LPCTSTR)path, CFile::modeCreate|CFile::modeReadWrite))
		{
			WriteXYLevelCSVFile2(&m_file);
			m_file.Close();
		}
		else
		{
			MessageBox("文件另存失败!");
		}
	}
}

void CShootDiagram::OnSaveXYLevel2() 
{
	// TODO: Add your command handler code here
	CString path;
	path = XYFilePath;

	CStdioFile m_file;
	if(m_file.Open((LPCTSTR)path, CFile::modeReadWrite))
	{
		WriteXYLevelCSVFile2(&m_file);
		m_file.Close();
	}
	else
	{
		MessageBox("文件保存失败!");
	}
}
