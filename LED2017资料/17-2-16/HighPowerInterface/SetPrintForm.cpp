// SetPrintForm.cpp : implementation file
//

#include "stdafx.h"
#include "highpowerinterface.h"
#include "SetPrintForm.h"
#include "Functions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetPrintForm dialog


CSetPrintForm::CSetPrintForm(CWnd* pParent /*=NULL*/)
	: CResizingDialog(CSetPrintForm::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetPrintForm)
	//}}AFX_DATA_INIT
}


void CSetPrintForm::DoDataExchange(CDataExchange* pDX)
{
	CResizingDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetPrintForm)
	DDX_Control(pDX, IDC_PosY9, m_posY9);
	DDX_Control(pDX, IDC_PosY8, m_posY8);
	DDX_Control(pDX, IDC_PosY7, m_posY7);
	DDX_Control(pDX, IDC_PosY6, m_posY6);
	DDX_Control(pDX, IDC_PosY5, m_posY5);
	DDX_Control(pDX, IDC_PosY4, m_posY4);
	DDX_Control(pDX, IDC_PosY3, m_posY3);
	DDX_Control(pDX, IDC_PosY2, m_posY2);
	DDX_Control(pDX, IDC_PosY10, m_posY10);
	DDX_Control(pDX, IDC_PosY1, m_posY1);
	DDX_Control(pDX, IDC_PosX9, m_posX9);
	DDX_Control(pDX, IDC_PosX8, m_posX8);
	DDX_Control(pDX, IDC_PosX7, m_posX7);
	DDX_Control(pDX, IDC_PosX6, m_posX6);
	DDX_Control(pDX, IDC_PosX5, m_posX5);
	DDX_Control(pDX, IDC_PosX4, m_posX4);
	DDX_Control(pDX, IDC_PosX3, m_posX3);
	DDX_Control(pDX, IDC_PosX2, m_posX2);
	DDX_Control(pDX, IDC_PosX10, m_posX10);
	DDX_Control(pDX, IDC_PosX1, m_posX1);
	DDX_Control(pDX, IDC_ItemCheck9, m_itemCheck9);
	DDX_Control(pDX, IDC_NameCode9, m_namecode9);
	DDX_Control(pDX, IDC_NameCode8, m_namecode8);
	DDX_Control(pDX, IDC_NameCode7, m_namecode7);
	DDX_Control(pDX, IDC_NameCode6, m_namecode6);
	DDX_Control(pDX, IDC_NameCode5, m_namecode5);
	DDX_Control(pDX, IDC_NameCode4, m_namecode4);
	DDX_Control(pDX, IDC_NameCode3, m_namecode3);
	DDX_Control(pDX, IDC_NameCode2, m_namecode2);
	DDX_Control(pDX, IDC_NameCode10, m_namecode10);
	DDX_Control(pDX, IDC_NameCode1, m_namecode1);
	DDX_Control(pDX, IDC_Name9, m_name9);
	DDX_Control(pDX, IDC_Name8, m_name8);
	DDX_Control(pDX, IDC_Name7, m_name7);
	DDX_Control(pDX, IDC_Name6, m_name6);
	DDX_Control(pDX, IDC_Name5, m_name5);
	DDX_Control(pDX, IDC_Name4, m_name4);
	DDX_Control(pDX, IDC_Name3, m_name3);
	DDX_Control(pDX, IDC_Name2, m_name2);
	DDX_Control(pDX, IDC_Name10, m_name10);
	DDX_Control(pDX, IDC_Name1, m_name1);
	DDX_Control(pDX, IDC_ItemCheck8, m_itemCheck8);
	DDX_Control(pDX, IDC_ItemCheck7, m_itemCheck7);
	DDX_Control(pDX, IDC_ItemCheck6, m_itemCheck6);
	DDX_Control(pDX, IDC_ItemCheck5, m_itemCheck5);
	DDX_Control(pDX, IDC_ItemCheck4, m_itemCheck4);
	DDX_Control(pDX, IDC_ItemCheck3, m_itemCheck3);
	DDX_Control(pDX, IDC_ItemCheck2, m_itemCheck2);
	DDX_Control(pDX, IDC_ItemCheck10, m_itemCheck10);
	DDX_Control(pDX, IDC_ItemCheck1, m_itemCheck1);
	DDX_Control(pDX, IDC_DataCode9, m_datacode9);
	DDX_Control(pDX, IDC_DataCode8, m_datacode8);
	DDX_Control(pDX, IDC_DataCode7, m_datacode7);
	DDX_Control(pDX, IDC_DataCode6, m_datacode6);
	DDX_Control(pDX, IDC_DataCode5, m_datacode5);
	DDX_Control(pDX, IDC_DataCode4, m_datacode4);
	DDX_Control(pDX, IDC_DataCode3, m_datacode3);
	DDX_Control(pDX, IDC_DataCode2, m_datacode2);
	DDX_Control(pDX, IDC_DataCode10, m_datacode10);
	DDX_Control(pDX, IDC_DataCode1, m_datacode1);
	DDX_Control(pDX, IDC_Data9, m_data9);
	DDX_Control(pDX, IDC_Data8, m_data8);
	DDX_Control(pDX, IDC_Data7, m_data7);
	DDX_Control(pDX, IDC_Data6, m_data6);
	DDX_Control(pDX, IDC_Data5, m_data5);
	DDX_Control(pDX, IDC_Data4, m_data4);
	DDX_Control(pDX, IDC_Data3, m_data3);
	DDX_Control(pDX, IDC_Data2, m_data2);
	DDX_Control(pDX, IDC_Data10, m_data10);
	DDX_Control(pDX, IDC_Data1, m_data1);
	DDX_Control(pDX, CMB_STYLE, cmb_Style);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetPrintForm, CResizingDialog)
	//{{AFX_MSG_MAP(CSetPrintForm)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_printPreview, OnprintPreview)
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetPrintForm message handlers
extern PrintItem tempprintItem[10];
extern CDC *print_pDC;

BOOL CSetPrintForm::OnInitDialog() 
{
	CResizingDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	pWnd_picture = GetDlgItem(IDC_PreviewForm);
	pWnd_picture->GetClientRect(&rect);
	pDC_picture = pWnd_picture->GetDC(); 

	InitControls();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

bool CSetPrintForm::InitControls()
{
	CButton *check[10] = {&m_itemCheck1, &m_itemCheck2, &m_itemCheck3, &m_itemCheck4,
		                    &m_itemCheck5, &m_itemCheck6, &m_itemCheck7, 
		                    &m_itemCheck8, &m_itemCheck9, &m_itemCheck10};
	CEdit *nameEdit[10] = {&m_name1, &m_name2, &m_name3, &m_name4, &m_name5,
		                    &m_name6, &m_name7, &m_name8, &m_name9, &m_name10};
	CButton *namecodeBt[10] = {&m_namecode1, &m_namecode2, &m_namecode3, &m_namecode4,
		                    &m_namecode5, &m_namecode6, &m_namecode7, 
		                    &m_namecode8, &m_namecode9, &m_namecode10};
	CComboBox *datacombo[10] = {&m_data1, &m_data2, &m_data3, &m_data4, &m_data5,
		                    &m_data6, &m_data7, &m_data8, &m_data9, &m_data10};
	CButton *datacodeBt[10] = {&m_datacode1, &m_datacode2, &m_datacode3, &m_datacode4,
		                    &m_datacode5, &m_datacode6, &m_datacode7, 
		                    &m_datacode8, &m_datacode9, &m_datacode10};
	CEdit *posXEdit[10] = {&m_posX1, &m_posX2, &m_posX3, &m_posX4, &m_posX5,
		                    &m_posX6, &m_posX7, &m_posX8, &m_posX9, &m_posX10};
	CEdit *posYEdit[10] = {&m_posY1, &m_posY2, &m_posY3, &m_posY4, &m_posY5,
		                    &m_posY6, &m_posY7, &m_posY8, &m_posY9, &m_posY10};
	CString str;
	int i = 0;

	for(i=0; i<10; i++)
	{
		InitCombo(datacombo[i]);
	}

	for(i=0; i<10; i++)
	{
		check[i]->SetCheck(tempprintItem[i].ItemCheck);
		nameEdit[i]->SetWindowText(tempprintItem[i].name);
		namecodeBt[i]->SetCheck(tempprintItem[i].namecode);
		datacombo[i]->SetWindowText(tempprintItem[i].data);
		datacodeBt[i]->SetCheck(tempprintItem[i].datacode);

		str.Format("%d", tempprintItem[i].pos_X);
		posXEdit[i]->SetWindowText(str);
		str.Format("%d", tempprintItem[i].pos_Y);
		posYEdit[i]->SetWindowText(str);
	}

	return true;
}

bool CSetPrintForm::InitCombo(CComboBox *combo)
{
	combo->InsertString(0, "Auto_Qty");
	combo->InsertString(1, "Auto_CAT");
	combo->InsertString(2, "Auto_Bin");
	combo->InsertString(3, "Auto_Boxnum");
	
	return true;
}

bool CSetPrintForm::getPrintSet()
{
	CButton *check[10] = {&m_itemCheck1, &m_itemCheck2, &m_itemCheck3, &m_itemCheck4,
		                    &m_itemCheck5, &m_itemCheck6, &m_itemCheck7, 
		                    &m_itemCheck8, &m_itemCheck9, &m_itemCheck10};
	CEdit *nameEdit[10] = {&m_name1, &m_name2, &m_name3, &m_name4, &m_name5,
		                    &m_name6, &m_name7, &m_name8, &m_name9, &m_name10};
	CButton *namecodeBt[10] = {&m_namecode1, &m_namecode2, &m_namecode3, &m_namecode4,
		                    &m_namecode5, &m_namecode6, &m_namecode7, 
		                    &m_namecode8, &m_namecode9, &m_namecode10};
	CComboBox *datacombo[10] = {&m_data1, &m_data2, &m_data3, &m_data4, &m_data5,
		                    &m_data6, &m_data7, &m_data8, &m_data9, &m_data10};
	CButton *datacodeBt[10] = {&m_datacode1, &m_datacode2, &m_datacode3, &m_datacode4,
		                    &m_datacode5, &m_datacode6, &m_datacode7, 
		                    &m_datacode8, &m_datacode9, &m_datacode10};
	CEdit *posXEdit[10] = {&m_posX1, &m_posX2, &m_posX3, &m_posX4, &m_posX5,
		                    &m_posX6, &m_posX7, &m_posX8, &m_posX9, &m_posX10};
	CEdit *posYEdit[10] = {&m_posY1, &m_posY2, &m_posY3, &m_posY4, &m_posY5,
		                    &m_posY6, &m_posY7, &m_posY8, &m_posY9, &m_posY10};

	CString str;

	for(int i=0; i<10; i++)
	{
		tempprintItem[i].ItemCheck = check[i]->GetCheck();
		nameEdit[i]->GetWindowText(tempprintItem[i].name);
		tempprintItem[i].namecode = namecodeBt[i]->GetCheck();
		datacombo[i]->GetWindowText(tempprintItem[i].data);
		tempprintItem[i].datacode = datacodeBt[i]->GetCheck();

		posXEdit[i]->GetWindowText(str);
		tempprintItem[i].pos_X = atoi(str);
		posYEdit[i]->GetWindowText(str);
		tempprintItem[i].pos_Y = atoi(str);
	}

	return true;
}

void CSetPrintForm::OnCancel() 
{
	// TODO: Add extra cleanup here
	getPrintSet();

	CResizingDialog::OnClose();
}

BOOL CSetPrintForm::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
//	return CResizingDialog::OnEraseBkgnd(pDC);
	return CResizingDialog::DrawBK(pDC, IDB_SettingBK, 1);
}

void CSetPrintForm::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	//	dc.SetBkMode(TRANSPARENT);

	dc.TextOut(10, 10, "条码资讯设定");
	dc.TextOut(68, 75, "Name");
	dc.TextOut(122, 75, "Barcode");
	dc.TextOut(183, 75, "Data");
	dc.TextOut(352, 75, "Barcode");
	dc.TextOut(410, 75, "X");
	dc.TextOut(455, 75, "Y");

	CString str;
	int pos_x = 35, pos_y = 105;
	for(int i=0; i<9; i++)
	{
		str.Format("%d", i+1);
		dc.TextOut(pos_x, pos_y+30*i, str);
	}
	dc.TextOut(pos_x-5, pos_y+270, "10");

	CDC MemDC;
	CBitmap MemBitmap;

	MemDC.CreateCompatibleDC(NULL);
	MemBitmap.CreateCompatibleBitmap(pDC_picture, 500, 400);
	CBitmap *pOldBit = MemDC.SelectObject(&MemBitmap);
	MemDC.FillSolidRect(0, 0, 500, 400, RGB(255, 255, 255));

	P_DrawBarCode(&MemDC,0);

	pDC_picture->BitBlt(0, 0, 500, 400, &MemDC, 0, 0, SRCCOPY);

	MemBitmap.DeleteObject();
	MemDC.DeleteDC();


	// Do not call CResizingDialog::OnPaint() for painting messages
}

/////////重写Encode128Auto（校验位处理：103+ID*No.+...%103）
void CSetPrintForm::P_DrawBarCode(CDC*pDC,const BOOL bPrint)
{
	CButton *check[10] = {&m_itemCheck1, &m_itemCheck2, &m_itemCheck3, &m_itemCheck4,
		                    &m_itemCheck5, &m_itemCheck6, &m_itemCheck7, 
		                    &m_itemCheck8, &m_itemCheck9, &m_itemCheck10};
	CEdit *nameEdit[10] = {&m_name1, &m_name2, &m_name3, &m_name4, &m_name5,
		                    &m_name6, &m_name7, &m_name8, &m_name9, &m_name10};
	CButton *namecodeBt[10] = {&m_namecode1, &m_namecode2, &m_namecode3, &m_namecode4,
		                    &m_namecode5, &m_namecode6, &m_namecode7, 
		                    &m_namecode8, &m_namecode9, &m_namecode10};
	CComboBox *datacombo[10] = {&m_data1, &m_data2, &m_data3, &m_data4, &m_data5,
		                    &m_data6, &m_data7, &m_data8, &m_data9, &m_data10};
	CButton *datacodeBt[10] = {&m_datacode1, &m_datacode2, &m_datacode3, &m_datacode4,
		                    &m_datacode5, &m_datacode6, &m_datacode7, 
		                    &m_datacode8, &m_datacode9, &m_datacode10};
	CEdit *posXEdit[10] = {&m_posX1, &m_posX2, &m_posX3, &m_posX4, &m_posX5,
		                    &m_posX6, &m_posX7, &m_posX8, &m_posX9, &m_posX10};
	CEdit *posYEdit[10] = {&m_posY1, &m_posY2, &m_posY3, &m_posY4, &m_posY5,
		                    &m_posY6, &m_posY7, &m_posY8, &m_posY9, &m_posY10};
	int i=0;
	int codeheight = 40;
	int height = 40;
	int iPenW = 2;
	int pos_X = 0, pos_Y = 0;

	const int iMapMode=pDC->SetMapMode(0);
	
	if(!bPrint)
	{
		iPenW /= 2;
		codeheight /= 2;
		height /= 2;
	}

	if(iPenW==0)	iPenW=1;

	COLORREF clrBar		=RGB(0,0,0);
	COLORREF clrSpace	=RGB(255,255,255);

	if(bPrint)
	{
		pDC->StartDoc("HolyChip");
		pDC->StartPage();
	}

	Barcode128 code;

	CString str, str_name1, str_name2;
	CString str_X, str_Y;

	for(i=0; i<10; i++)
	{
		if(1 == check[i]->GetCheck())
		{
			nameEdit[i]->GetWindowText(str_name1);
			datacombo[i]->GetWindowText(str_name2);
			str = str_name1 + str_name2;

			posXEdit[i]->GetWindowText(str_X);
			posYEdit[i]->GetWindowText(str_Y);
			pos_X = atoi(str_X);
			pos_Y = atoi(str_Y);
			if(!bPrint)
			{
				pos_X /= 2;
				pos_Y /= 2;
			}

			if(str != "")
			{
				pDC->TextOut(pos_X, pos_Y, str);
			}

			if((1 == namecodeBt[i]->GetCheck()) && (1 == datacodeBt[i]->GetCheck()))
			{
				pos_Y += height;
				code.Encode128Auto(str);
				P_DrawBarcode(pDC,pos_X,pos_Y,pos_Y+codeheight,pos_Y+codeheight,clrBar,clrSpace,iPenW,&code);	
			}
			else if((1 == namecodeBt[i]->GetCheck()) && (0 == datacodeBt[i]->GetCheck()))
			{
				pos_Y += height;
				code.Encode128Auto(str_name1);
				P_DrawBarcode(pDC,pos_X,pos_Y,pos_Y+codeheight,pos_Y+codeheight,clrBar,clrSpace,iPenW,&code);	
			}
			else if((0 == namecodeBt[i]->GetCheck()) && (1 == datacodeBt[i]->GetCheck()))
			{
				pos_Y += height;
				code.Encode128Auto(str_name2);
				P_DrawBarcode(pDC,pos_X,pos_Y,pos_Y+codeheight,pos_Y+codeheight,clrBar,clrSpace,iPenW,&code);	
			}
		}
	}

	if(bPrint)
	{
		pDC->EndPage();
		pDC->EndDoc();
	}
	pDC->SetMapMode(iMapMode);
}

void CSetPrintForm::OnprintPreview() 
{
	// TODO: Add your control notification handler code here
//	if(cp.GetDefaults())//if(cp.DoModal()!=IDOK)	
	clock_t start, finish; 
	double during = 0;
	start = clock();

	P_DrawBarCode(print_pDC, true);

	finish = clock();
	
	during = (double)(finish - start);
	CString str;
	str.Format("%f", during);
//	MessageBox(str);

	InvalidateRect(&rect, false);
}

void CSetPrintForm::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	CResizingDialog::OnChar(nChar, nRepCnt, nFlags);
}

void CSetPrintForm::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	CResizingDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CSetPrintForm::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, 0);
	CResizingDialog::OnLButtonDown(nFlags, point);
}
