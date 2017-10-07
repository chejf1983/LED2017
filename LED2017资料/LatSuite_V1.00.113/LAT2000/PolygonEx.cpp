#include "StdAfx.h"
#include "PolygonEx.h"
#include <math.h>


#define  OFFSET_DISTANCE	3
#define  OFFSET_VERTEX		1

CPolygonEx::CPolygonEx(void)
{
	m_pPointArray = NULL;
	m_nPointCount = 0;
}


CPolygonEx::~CPolygonEx(void)
{
	if (NULL != m_pPointArray)
	{
		delete [] m_pPointArray;
	}
}


// CMyPolygon ³ÉÔ±º¯Êý

BOOL CPolygonEx::SetPolygon(CPoint * pArray, int nCount)
{
	if (NULL == pArray)
	{
		return FALSE;
	}

	if (nCount < 0 || nCount > 1024)
	{
		return FALSE;
	}

	// There should not be two same point
	for (int i = 0; i < nCount; i++)
	{
		for (int j = i + 1; j < nCount; j++)
		{
			if (pArray[j] == pArray[i])
			{
				return FALSE;
			}
		}
	}

	if (NULL != m_pPointArray)
	{
		delete [] m_pPointArray;
	}
	m_pPointArray = new CPoint[nCount];
	ASSERT(NULL != m_pPointArray);
	for (int i = 0; i < nCount; i++)
	{
		m_pPointArray[i] = pArray[i];
	}
	m_nPointCount = nCount;

	return TRUE;
}


BOOL CPolygonEx::IsInPolygon(CPoint point)
{
	if (IsOnPolygon(point))
	{
		return FALSE;
	}

	CRect rect;
	GetOutlineRectangle(rect);
	if (!IsInRectangle(rect, point))
	{
		return FALSE;
	}

	int nCount = 0;
	if (GetIntersectionPointCount(CPoint(rect.left, rect.top), point, nCount))
	{
		//CString strTemp;
		//strTemp.Format("LeftTop:%d", nCount);
		//AfxMessageBox(strTemp);

		if ( nCount % 2 == 0)
		{
			return FALSE;
		}
		else
		{
			return TRUE;
		}
	}
	if (GetIntersectionPointCount(CPoint(rect.right, rect.top), point, nCount))
	{
		if ( nCount % 2 == 0)
		{
			return FALSE;
		}
		else
		{
			return TRUE;
		}
	}
	if (GetIntersectionPointCount(CPoint(rect.right, rect.bottom), point, nCount))
	{
		if ( nCount % 2 == 0)
		{
			return FALSE;
		}
		else
		{
			return TRUE;
		}
	}
	if (GetIntersectionPointCount(CPoint(rect.left, rect.bottom), point, nCount))
	{
		if ( nCount % 2 == 0)
		{
			return FALSE;
		}
		else
		{
			return TRUE;
		}
	}
	

	return TRUE;
}


BOOL CPolygonEx::IsOnPolygon(CPoint point)
{
	if (IsOnVertex(point))
	{
		return TRUE;
	}

	for (int i = 0; i < m_nPointCount - 1; i++)
	{
		if (IsOnLineSegment(m_pPointArray[i], m_pPointArray[i+1], point))
		{
			return TRUE;
		}
	}
	
	return FALSE;
}


BOOL CPolygonEx::IsOnVertex(CPoint point)
{
	for (int i = 0; i < m_nPointCount; i++)
	{
		if (abs(point.x - m_pPointArray[i].x) < OFFSET_VERTEX && abs(point.y - m_pPointArray[i].y) < OFFSET_VERTEX)
		{
			return TRUE;
		}
	}

	return FALSE;
}


int CPolygonEx::GetPointCount()
{
	return m_nPointCount;
}


BOOL CPolygonEx::GetPoint(int nIndex, CPoint & point)
{
	if (nIndex >= m_nPointCount || nIndex < 0)
	{
		return FALSE;
	}

	point = m_pPointArray[nIndex];

	return TRUE;
}


BOOL CPolygonEx::SetPoint(int nIndex, CPoint newPoint)
{
	if (nIndex >= m_nPointCount || nIndex < 0)
	{
		return FALSE;
	}

	m_pPointArray[nIndex] = newPoint;

	return TRUE;
}


BOOL CPolygonEx::IsOnLineSegment(CPoint vertex1, CPoint vertex2, CPoint point)
{
	if (point == vertex1 || point == vertex2)
	{
		return TRUE;
	}

	// 1. If the point is in the outline rectangle
	int iMinX = vertex1.x < vertex2.x ? vertex1.x : vertex2.x;
	int iMaxX = vertex1.x > vertex2.x ? vertex1.x : vertex2.x;
	int iMinY = vertex1.y < vertex2.y ? vertex1.y : vertex2.y;
	int iMaxY = vertex1.y > vertex2.y ? vertex1.y : vertex2.y;
	if (point.x < iMinX || point.x > iMaxX)
	{
		return FALSE;
	}

	if (point.y < iMinY || point.y > iMaxY)
	{
		return FALSE;
	}

	// 2. If the point is on the line segment
	//float fK1 = 1.0f * (point.y - vertex1.y) / (point.x - vertex1.x);
	//float fK2 = 1.0f * (point.y - vertex2.y) / (point.x - vertex2.x);

	//float fPrecition = (float)(iMaxX > iMaxY ? iMaxX : iMaxY);
	//fPrecition = OFFSET_PIXEL / fPrecition;

	//return fabs(fK2 - fK1) <= fPrecition;

	double dk = 1.0 * (vertex2.y - vertex1.y) / (vertex2.x - vertex1.x);
	double db = vertex2.y - dk * vertex2.x;

	// Calculate the distance between the point and the line
	double dOffsetb = fabs(db - (point.y - dk * point.x));
	dOffsetb = sqrt(1.0f / (dk * dk  + 1)) * dOffsetb;

	return dOffsetb <= OFFSET_DISTANCE;
}


BOOL CPolygonEx::GetIntersectionPointCount(CPoint vertex1, CPoint vertex2, int & nCount)
{
	nCount = 0;

	CPoint pointIntersection;
	for (int i = 0; i < m_nPointCount; i++)
	{
		int iNext = (i + 1) % m_nPointCount;
		if (GetIntersectionPoint(vertex1, vertex2, m_pPointArray[i], m_pPointArray[iNext], pointIntersection))
		{
			if (IsOnVertex(pointIntersection))
			{
				return FALSE;
			}

			nCount++;
		}
	}
	
	return TRUE;
}


BOOL CPolygonEx::GetIntersectionPoint(CPoint vertexA1, CPoint vertexA2, CPoint vertexB1, CPoint vertexB2, CPoint & intersectionPoint)
{
	double dAk, dAb, dBk, dBb;

	dAk = 1.0 * (vertexA2.y - vertexA1.y) / (vertexA2.x - vertexA1.x);
	dAb = vertexA1.y - dAk * vertexA1.x; 

	dBk = 1.0 * (vertexB2.y - vertexB1.y) / (vertexB2.x - vertexB1.x);
	dBb = vertexB1.y - dBk * vertexB1.x;

	intersectionPoint.x = (long)((dAb - dBb) / (dBk - dAk) + 0.5);
	if (fabs(dAk) < fabs(dBk))
	{
		intersectionPoint.y = (long)(intersectionPoint.x * dAk + dAb + 0.5);
	}
	else
	{
		intersectionPoint.y = (long)(intersectionPoint.x * dBk + dBb + 0.5);
	}


	if (IsOnLineSegment(vertexA1, vertexA2, intersectionPoint) && IsOnLineSegment(vertexB1, vertexB2, intersectionPoint))
	{
		return TRUE;
	}

	return FALSE;
}


BOOL CPolygonEx::GetOutlineRectangle(CRect & outlineRect)
{
	if (m_nPointCount < 2)
	{
		return FALSE;
	}

	outlineRect.left = m_pPointArray[0].x;
	outlineRect.right = m_pPointArray[0].x;
	outlineRect.top = m_pPointArray[0].y;
	outlineRect.bottom = m_pPointArray[0].y;

	for (int i = 0; i < m_nPointCount; i++)
	{
		if (m_pPointArray[i].x < outlineRect.left)
		{
			outlineRect.left = m_pPointArray[i].x;
		}

		if (m_pPointArray[i].x > outlineRect.right)
		{
			outlineRect.right = m_pPointArray[i].x;
		}

		if (m_pPointArray[i].y < outlineRect.top)
		{
			outlineRect.top = m_pPointArray[i].y;
		}

		if (m_pPointArray[i].y > outlineRect.bottom)
		{
			outlineRect.bottom = m_pPointArray[i].y;
		}
	}

	return TRUE;
}


BOOL CPolygonEx::IsInRectangle(CRect & rect, CPoint point)
{
	if (point.x <= rect.left || point.x >= rect.right)
	{
		return FALSE;
	}

	if (point.y <= rect.top || point.y >= rect.bottom)
	{
		return FALSE;
	}

	return TRUE;
}