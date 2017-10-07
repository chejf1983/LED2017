#pragma once
class CPolygonEx
{
public:
	CPolygonEx(void);
	~CPolygonEx(void);

public:
	BOOL SetPolygon(float fx[], float fy[], int nCount);

	BOOL SetPolygon(CPoint * pArray, int nCount);
	
	BOOL IsInPolygon(CPoint point);

	BOOL IsOnPolygon(CPoint point);

	BOOL IsOnVertex(CPoint point);

/// Point operation
	int  GetPointCount();

	BOOL GetPoint(int nIndex, CPoint & point);

	BOOL SetPoint(int nIndex, CPoint newPoint);

private:
	BOOL IsOnLineSegment(CPoint vertex1, CPoint vertex2, CPoint point);

	BOOL GetIntersectionPointCount(CPoint vertex1, CPoint vertex2, int & nCount);

	BOOL GetIntersectionPoint(CPoint vertexA1, CPoint vertexA2, CPoint vertexB1, CPoint vertexB2, CPoint & intersectionPoint);

	BOOL GetOutlineRectangle(CRect & outlineRect);

	BOOL IsInRectangle(CRect & rect, CPoint point);

private:
	CPoint *	m_pPointArray;
	int			m_nPointCount;
};

