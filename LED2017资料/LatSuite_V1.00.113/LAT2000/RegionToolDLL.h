#include "ntgraph.h"

#define DllExport _stdcall

void DllExport Region_ShowEditRegionDlg();

int  DllExport Region_GetRegionCount();

BOOL DllExport Region_SaveFile(char * strPathName);

BOOL DllExport Region_LoadFile(char * strPathName);

BOOL DllExport Region_IsInAnyRegion(float fx, float fy, int * iIndex, int & nCount);

BOOL DllExport Region_SetRegionName(int iIndex, char * strName);

void DllExport Region_DrawRegion(CNTGraph & cDraw, int iIndex);

BOOL DllExport Region_GetRegionName(int iIndex, char * strName, int nNameSize);

BOOL DllExport Region_GetRegion(int iIndex, float * fx, float * fy, int nSize, int & nPointCount);

int  DllExport Region_GetRegionPointCount(int iIndex);

BOOL DllExport Region_GetOutlineRect(float & fLeft, float & fTop, float & fRight, float & fBottom);