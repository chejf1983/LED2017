// WhiteZone.cpp: implementation of the CWhiteZone class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MySpec.h"
#include "WhiteZone.h"
#include "math.h"
#include "Global_MySpec.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern CString g_strListWhite;
CWhiteZone::CWhiteZone()
{
	m_bMouse=FALSE;
}

CWhiteZone::~CWhiteZone()
{

}

BOOL CWhiteZone::WZ_Load(CString strPathName)
{
	CFile oFile;
	if(!oFile.Open(strPathName,CFile::modeRead))
	{
		g_strListWhite=g_strCurPath+"Class\\White_ANSI.WCL";
//		if(g_bEnglish)
//			AfxMessageBox("Can not open!\n\n"+strPathName,MB_ICONSTOP);
//		else
//			AfxMessageBox("不能打开文件!\n\n"+strPathName,MB_ICONSTOP);
//		return FALSE;
	}
	CArchive ar(&oFile,CArchive::load);
	Serialize(ar);
	ar.Close();
	oFile.Close();

	return TRUE;
}

BOOL CWhiteZone::WZ_Save(CString strPathName)
{
	CFile sFile;
	if(!sFile.Open(strPathName,CFile::modeCreate|CFile::modeReadWrite))
	{
		if(g_bEnglish)
			AfxMessageBox("Can not save file!",MB_ICONSTOP);
		else
			AfxMessageBox("不能保存文件!",MB_ICONSTOP);
		return FALSE;
	}
	CArchive ar(&sFile,CArchive::store);
	Serialize(ar);
	ar.Close();
	sFile.Close();

	return TRUE;
}

void CWhiteZone::Serialize(CArchive &ar)
{
	CString strVer;
	int i,iN;
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		strVer="WZ A";
		ar<<strVer;

		iN=m_arraXY.GetSize();
		ar<<iN;
		for(i=0;i<iN;i++)
			m_arraXY[i]->Serialize(ar);
	}
	else
	{
		ar>>strVer;
		if(strVer!="WZ A")
			return;
		m_arraXY.RemoveAll();
		ar>>iN;
		for(i=0;i<iN;i++)
		{
			CZOoneXY *temp=new CZOoneXY();
			temp->Serialize(ar);
			m_arraXY.Add(temp);
		}
	}
}

void CWhiteZone::Draw(CDC *pDC, CRect dRect, int iSele,BOOL bPrint,int iType)
{
	CFont *pOldFont;
	CFont Font1,Font2;

	CPen *pOldPen;
	CPen Pen1,Pen2,Pen3;

	if(!bPrint)
	{
		Font1.CreateFont(15,0,0,0,600,FALSE,FALSE,0,
			ANSI_CHARSET,OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
			DEFAULT_PITCH|FF_MODERN,"Courier New");  

		Pen1.CreatePen(PS_SOLID,1,RGB(255,255,255));
		Pen2.CreatePen(PS_SOLID,2,RGB(0,255,255));
		Pen3.CreatePen(PS_SOLID,2,RGB(255,0,0));
	}
	else
	{
		if(iType==0)
		{
		Font1.CreateFont(dRect.Height()/30,0,0,0,600,FALSE,FALSE,0,
			ANSI_CHARSET,OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
			DEFAULT_PITCH|FF_MODERN,"Courier New");  
		}
		else
		{
		Font1.CreateFont(dRect.Height()/50,0,0,0,600,FALSE,FALSE,0,
			ANSI_CHARSET,OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
			DEFAULT_PITCH|FF_MODERN,"Courier New");  
		}
		Font2.CreateFont(dRect.Height()/75,0,0,0,500,FALSE,FALSE,0,
			ANSI_CHARSET,OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
			DEFAULT_PITCH|FF_MODERN,"Courier New");  

		Pen1.CreatePen(PS_SOLID,3,RGB(0,0,0));
		Pen2.CreatePen(PS_SOLID,6,RGB(0,0,255));
		Pen3.CreatePen(PS_SOLID,3,RGB( 0,0,0));
	}

	pOldPen=pDC->SelectObject(&Pen1);
	pOldFont=pDC->SelectObject(&Font1);

	if(bPrint)
	{
		pDC->MoveTo(dRect.left,dRect.top);
		pDC->LineTo(dRect.right,dRect.top);
		pDC->LineTo(dRect.right,dRect.bottom);
		pDC->LineTo(dRect.left,dRect.bottom);
		pDC->LineTo(dRect.left,dRect.top);
	}

	int iFontH,iFontW;
	TEXTMETRIC  tm;
	pDC->GetTextMetrics(&tm);
	iFontH=tm.tmHeight+tm.tmExternalLeading;
	iFontW=tm.tmAveCharWidth;

	CRect xRect;
	if(!bPrint)
	{
		xRect.left=dRect.left+3*iFontW;
		xRect.right=dRect.right-2*iFontW;
		xRect.top=dRect.top+1*iFontH;
		xRect.bottom=dRect.bottom-1*iFontH;
	}
	else
	{
		xRect.left=dRect.left+5*iFontW;
		xRect.right=dRect.right-2*iFontW;
		xRect.top=dRect.top+3*iFontH;
		xRect.bottom=dRect.bottom-3*iFontH;
	}

	pDC->SetTextAlign(TA_RIGHT);
	pDC->SetBkMode(TRANSPARENT);
	if(!bPrint)
		pDC->SetTextColor(RGB(255,255,255));
	else
		pDC->SetTextColor(RGB(0,0,0));

	if(iType==1)
	{
		pDC->SetTextAlign(TA_CENTER);
		pDC->TextOut(xRect.left+xRect.Width()/2,xRect.top-iFontH*2,"CIE1931 色 坐 标 分 布 图");
		pDC->SetTextAlign(TA_RIGHT);
	}
	float fMinX,fMaxX;
	float fMinY,fMaxY;
	int i,j,iT,iN;
	iT=m_arraXY.GetSize();
	if(iT==0)
	{
		fMinX=0.0f;
		fMaxX=1.0f;
		fMinY=0.0f;
		fMaxY=1.0f;
	}
	else
	{
		fMinX=1.0f;
		fMaxX=0.0f;
		fMinY=1.0f;
		fMaxY=0.0f;
	}
	for(i=0;i<iT;i++)
	{
		if(iType==1)
		{
			if(iSele!=i)
					continue;
		}
		iN=m_arraXY[i]->m_fx.GetSize();
		for(j=0;j<iN;j++)
		{
			if(m_arraXY[i]->m_fx[j]<fMinX)
				fMinX=m_arraXY[i]->m_fx[j];
			if(m_arraXY[i]->m_fx[j]>fMaxX)
				fMaxX=m_arraXY[i]->m_fx[j];

			if(m_arraXY[i]->m_fy[j]<fMinY)
				fMinY=m_arraXY[i]->m_fy[j];
			if(m_arraXY[i]->m_fy[j]>fMaxY)
				fMaxY=m_arraXY[i]->m_fy[j];
		}
	}

/*	if(m_fX<fMinX)
		fMinX=m_fX;
	if(m_fX>fMaxX)
		fMaxX=m_fX;
	if(m_fY<fMinY)
		fMinY=m_fY;
	if(m_fY>fMaxY)
		fMaxY=m_fY;*/

/*	fMinX=0;
	fMinY=0;
	fMaxX=1;
	fMaxY=1;*/

	if(fMinX==fMaxX)
		fMaxX=fMinX+0.01f;
	if(fMinY==fMaxY)
		fMaxY=fMinY+0.01f;

/*	fMinX=(float)floor(fMinX/0.01f)*0.01f;
	fMaxX=(float)ceil(fMaxX/0.01f)*0.01f;
	fMinY=(float)floor(fMinY/0.01f)*0.01f;
	fMaxY=(float)ceil(fMaxY/0.01f)*0.01f;*/

	float fDX=(fMaxX-fMinX)/10;
	float fDY=(fMaxY-fMinY)/10;

	fMinX=fMinX-fDX;
	fMaxX=fMaxX+fDX;
	fMinY=fMinY-fDY;
	fMaxY=fMaxY+fDY;

	float K1=(fMaxY-fMinY)/(fMaxX-fMinX);
	float K2=xRect.Height()*1.0f/xRect.Width();
	if(K1<K2)
	{
		float fTemp;
		fTemp=(K2*(fMaxX-fMinX)-(fMaxY-fMinY))/2;
		fMinY=fMinY-fTemp;
		fMaxY=fMaxY+fTemp;
	}
	else
	{
		float fTemp;
		fTemp=((1/K1)*(fMaxY-fMinY)-(fMaxX-fMinX))/2;
		fMinX=fMinX-fTemp;
		fMaxX=fMaxX+fTemp;
	}
	pDC->MoveTo(xRect.left,xRect.top);
	pDC->LineTo(xRect.right,xRect.top);
	pDC->LineTo(xRect.right,xRect.bottom);
	pDC->LineTo(xRect.left,xRect.bottom);
	pDC->LineTo(xRect.left,xRect.top);

	CString strTemp;

	int DN,NN;
	if(iType==0)
	{
		DN=100;
		NN=1;
	}
	else
	{
		DN=1000;
		NN=10;
	}
	int x,y;
	for(i=0;i<=1*DN;i++)
	{
		float fx=i*1.0f/DN;
		float fy=i*1.0f/DN;
		if(fx>=fMinX&&fx<=fMaxX)
		{
			if(i%(10*NN)==0)
			{
				x=(int)(xRect.left+(fx-fMinX)*xRect.Width()/(fMaxX-fMinX));
				pDC->MoveTo(x,xRect.bottom-iFontH/2);
				pDC->LineTo(x,xRect.bottom);

				if(1)
				{
					pDC->SetTextAlign(TA_CENTER);
					strTemp.Format("%.2f",fx);
					pDC->TextOut(x,xRect.bottom+iFontH/8,strTemp);
				}
			}
			else if(i%(1*NN)==0)
			{
				x=(int)(xRect.left+(fx-fMinX)*xRect.Width()/(fMaxX-fMinX));
				pDC->MoveTo(x,xRect.bottom-iFontH/3);
				pDC->LineTo(x,xRect.bottom);

				if(iType==1&&(i/(1*NN))%2==0)
				{
					pDC->SetTextAlign(TA_CENTER);
					strTemp.Format("%.2f",fx);
					pDC->TextOut(x,xRect.bottom+iFontH/8,strTemp);
				}
			}
			else
			{
				x=(int)(xRect.left+(fx-fMinX)*xRect.Width()/(fMaxX-fMinX));
				pDC->MoveTo(x,xRect.bottom-iFontH/4);
				pDC->LineTo(x,xRect.bottom);
			}
		}
		if(fy>=fMinY&&fy<=fMaxY)
		{
			if(i%(10*NN)==0)
			{
				y=(int)(xRect.bottom-(fy-fMinY)*xRect.Height()/(fMaxY-fMinY));
				pDC->MoveTo(xRect.left+iFontH/2,y);
				pDC->LineTo(xRect.left,y);

				if(1)
				{
					pDC->SetTextAlign(TA_RIGHT);
					strTemp.Format("%.2f",fy);
					pDC->TextOut(xRect.left-iFontW/5,y-iFontH/2,strTemp);
				}
			}
			else if(i%(1*NN)==0)
			{
				y=(int)(xRect.bottom-(fy-fMinY)*xRect.Height()/(fMaxY-fMinY));
				pDC->MoveTo(xRect.left+iFontH/3,y);
				pDC->LineTo(xRect.left,y);

				if(iType==1&&(i/(1*NN))%2==0)
				{
					pDC->SetTextAlign(TA_RIGHT);
					strTemp.Format("%.2f",fy);
					pDC->TextOut(xRect.left-iFontW/5,y-iFontH/2,strTemp);
				}
			}
			else
			{
				y=(int)(xRect.bottom-(fy-fMinY)*xRect.Height()/(fMaxY-fMinY));
				pDC->MoveTo(xRect.left+iFontH/4,y);
				pDC->LineTo(xRect.left,y);
			}
		}
	}

	for(i=0;i<iT;i++)
	{
		if(iType==1)
		{
			if(iSele!=i)
				continue;
		}

		if(iSele==i)
			pDC->SelectObject(&Pen2);

		iN=m_arraXY[i]->m_fx.GetSize();
		for(j=0;j<iN;j++)
		{
			x=(int)(xRect.left+(m_arraXY[i]->m_fx[j]-fMinX)*xRect.Width()/(fMaxX-fMinX));
			y=(int)(xRect.bottom-(m_arraXY[i]->m_fy[j]-fMinY)*xRect.Height()/(fMaxY-fMinY));
			if(j==0)
				pDC->MoveTo(x,y);
			else
				pDC->LineTo(x,y);
		}
		if(iN!=0)
		{
			x=(int)(xRect.left+(m_arraXY[i]->m_fx[0]-fMinX)*xRect.Width()/(fMaxX-fMinX));
			y=(int)(xRect.bottom-(m_arraXY[i]->m_fy[0]-fMinY)*xRect.Height()/(fMaxY-fMinY));
			pDC->LineTo(x,y);

		}
		if(iSele==i)
			pDC->SelectObject(&Pen1);
		if(iSele==i)
		{
			pDC->SetTextAlign(TA_RIGHT);
			if(iType==1&&iSele==3)
			{
				pDC->TextOut(xRect.right,xRect.top-iFontH,"选择性黄色");
			}
			else
				pDC->TextOut(xRect.right,xRect.top-iFontH,m_arraXY[i]->m_strName);
		}
	}

	if(m_bMouse)
	{
		m_fX=fMinX+(m_xyPoint.x-xRect.left)*(fMaxX-fMinX)/xRect.Width();
		m_fY=fMaxY-(m_xyPoint.y-xRect.top)*(fMaxY-fMinY)/xRect.Height();
	}

	if(iType==0)
	{
		x=(int)(xRect.left+(m_fX-fMinX)*xRect.Width()/(fMaxX-fMinX));
		y=(int)(xRect.bottom-(m_fY-fMinY)*xRect.Height()/(fMaxY-fMinY));
		if(x<xRect.left)
			x=xRect.left;
		if(x>xRect.right)
			x=xRect.right;
		if(y<xRect.top)
			y=xRect.top;
		if(y>xRect.bottom)
			y=xRect.bottom;

		pDC->SelectObject(&Pen3);

		pDC->MoveTo(x-iFontW,y);
		pDC->LineTo(x+iFontW,y);
		pDC->MoveTo(x,y+iFontW);
		pDC->LineTo(x,y-iFontW);
	}
	else
	{
		pDC->SelectObject(&Font2);
		pDC->SetTextAlign(TA_CENTER);
		for(i=0;i<m_arra_fx.GetSize();i++)
		{
			x=(int)(xRect.left+(m_arra_fx[i]-fMinX)*xRect.Width()/(fMaxX-fMinX));
			y=(int)(xRect.bottom-(m_arra_fy[i]-fMinY)*xRect.Height()/(fMaxY-fMinY));
			if(x<xRect.left)
				x=xRect.left;
			if(x>xRect.right)
				x=xRect.right;
			if(y<xRect.top)
				y=xRect.top;
			if(y>xRect.bottom)
				y=xRect.bottom;

			pDC->SelectObject(&Pen3);

			pDC->MoveTo(x-iFontW/3,y);
			pDC->LineTo(x+iFontW/3,y);
			pDC->MoveTo(x,y+iFontW/3);
			pDC->LineTo(x,y-iFontW/3);

			CString strTemp;
			strTemp.Format("%d",i+1);
			pDC->TextOut(x,y+iFontW/3,strTemp);
		}
		pDC->SelectObject(&Font1);
	}

	CString strRe;
	strRe=IN_ZONE(m_fX,m_fY);
	pDC->SetTextAlign(TA_LEFT);
	if(!bPrint)
		pDC->SetTextColor(RGB(255,255,255));
	else
		pDC->SetTextColor(RGB(0,0,0));
	if(iType==0)
		pDC->TextOut(xRect.left,xRect.top-iFontH,"CLASS: "+ strRe);


	pDC->SetTextColor(RGB(0,0,0));
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldFont);
}

BOOL CWhiteZone::XY_CheckPoyIN(CArray<float,float> &x,CArray<float,float> &y,float fx,float fy,int MAX_X)
{
	//////////////////////////////////////////////
	//功能:一个点是否在多边形内(交点法)
	//输入:x,y多边形顶点坐标
	//     fx,fy,所判断的点坐标
	//     MAX_Y 这种算法所需要的一个参数,
	//           一般可以是区域的右X边界
	//////////////////////////////////////////////

	MAX_X=MAX_X+100;  //保存在外面

	int iN=x.GetSize();
	if(iN<=2)
		return FALSE;

	///////////////////////////////
	//求出两条"直线"的交点
	// y= iCY(cy)
	// y= k2*x+b2
	//交点:  
	//    x0 = (cy-b2)/k2;
	//    y0 = cy;
	//再判断交点是否是在"线段"上
	//////////////////////////////
	//首尾相连

	int iErr = 0;
retry:

	int  iP=0;  //交点个数
	float fPerX=-1;
	float fPerY=-1;

	float cx,cy;  //
	cx=fx*1.0f;
	cy=fy*1.0f;

	float x1,y1;
	float x2,y2;

	float k2,b2;
	float x0,y0;  //交点坐标
	for(int i=0;i<iN;i++)
	{
		if(i==(iN-1))
		{
			x1=x[i+0]*1.0f;
			y1=y[i+0]*1.0f;
			x2=x[0]*1.0f;
			y2=y[0]*1.0f;
		}
		else
		{
			x1=x[i+0]*1.0f;
			y1=y[i+0]*1.0f;
			x2=x[i+1]*1.0f;
			y2=y[i+1]*1.0f;
		}

		if(y1==y2)
		{
			//1.平行，无交点或有无数个交点
			if((cy == y1) && (cy < max(y1, y2))) 
			{
//				AfxMessageBox("1");
				iP++;
			}
		}
		else if(x1 == x2)
		{
			fPerX = x0;
			fPerY = y0;
			//2.一定有一个交点
			x0 = x1;
			y0 = cy;

			//是不是在线段上
			if((y0 >= min(y1, y2)) && (y0 <= max(y1, y2)))
			{
				if(x0 > cx && !(fPerX == x0 && fPerY == y0))//不用>=!!!!!!!!!!
				{
//					AfxMessageBox("2");
					iP++;
				}
			}
		}
		else
		{
			//3.也一定有一个次点
			k2 = (y2 - y1) / (x2 - x1);
			b2 = y1 - k2 * x1;

			fPerX = x0;
			fPerY = y0;
			//交点坐标
			x0 = (cy - b2) / k2;
			y0 = cy;

			//是不是在线段上
			if((y0 >= min(y1, y2) && y0 <= max(y1, y2)) && (x0 >= min(x1, x2) && x0 <= max(x1, x2)))
			{
				if(x0 >= cx && !(fPerX == x0 && fPerY == y0))
				{
//					AfxMessageBox("3");
					iP++;
				}
			}
		}
	}

	CString sTemp;
	sTemp.Format("iP:  %d",iP);
//	AfxMessageBox(sTemp);
	//有奇数个交点的话就是在内部
	if(iP % 2 == 1)
	{
		//判断
		int iXL = 0;
		int iYL = 0;
		int iXM = 0;
		int iYM = 0;
		for(int i = 0; i < iN; i++)
		{
			float fTemp = x[i];
			if(cx < x[i])
			{
				iXL++;
			}
			if(cy < y[i])
			{
				iYL++;
			}
			if(cx > x[i])
			{
				iXM++;
			}
			if(cy > y[i])
			{
				iYM++;
			}
		}
		if(iXL == iN || iYL == iN || iXM == iN || iYM == iN)
		{
			iErr++;
			if(iErr == 1)
			{
				/////////////////////
				//huyubing 目的是为了有时候刚好x或者y相同时候判断有误问题 当然也有可能需要用-0.000001
				/////////////////////
				fx = fx + 0.000001f;
				fy = fy + 0.000001f;
				/////////////////////
				goto retry;
			}

			return FALSE;
		}
		return TRUE;
	}
	else
	{
		iErr++;
		if(iErr == 1)
		{
			/////////////////////
			//huyubing 目的是为了有时候刚好x或者y相同时候判断有误问题 当然也有可能需要用-0.000001
			/////////////////////
			fx = fx + 0.000001f;
			fy = fy + 0.000001f;
			/////////////////////
			goto retry;
		}

		return FALSE;
	}
}

CString CWhiteZone::IN_ZONE(float fx, float fy)
{
	CString sTemp;
	sTemp.Format("%.4f", fx);
	fx = (float)(atof(sTemp));
	sTemp.Format("%.4f", fy);
	fy = (float)(atof(sTemp));
	int iN=m_arraXY.GetSize();

	for(int i = 0; i < iN; i++)
	{
		if(XY_CheckPoyIN(m_arraXY[i]->m_fx, m_arraXY[i]->m_fy, fx, fy, 10))
		{
			return m_arraXY[i]->m_strName;
		}
	}
	return "OUT";
}
