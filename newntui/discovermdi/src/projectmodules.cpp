// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


#include "stdafx.h"
#include "projectmodules.h"

/////////////////////////////////////////////////////////////////////////////
// CProjectModules

IMPLEMENT_DYNCREATE(CProjectModules, CWnd)

/////////////////////////////////////////////////////////////////////////////
// CProjectModules properties

LPDISPATCH CProjectModules::GetDataSource()
{
	LPDISPATCH result;
	GetProperty(0x1, VT_DISPATCH, (void*)&result);
	return result;
}

void CProjectModules::SetDataSource(LPDISPATCH propVal)
{
	SetProperty(0x1, VT_DISPATCH, propVal);
}

CString CProjectModules::GetProject()
{
	CString result;
	GetProperty(0x2, VT_BSTR, (void*)&result);
	return result;
}

void CProjectModules::SetProject(LPCTSTR propVal)
{
	SetProperty(0x2, VT_BSTR, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// CProjectModules operations

void CProjectModules::AboutBox()
{
	InvokeHelper(0xfffffdd8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}
