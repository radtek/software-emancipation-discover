// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


#include "stdafx.h"
#include "impact.h"

/////////////////////////////////////////////////////////////////////////////
// CImpactCtrl

IMPLEMENT_DYNCREATE(CImpactCtrl, CWnd)

/////////////////////////////////////////////////////////////////////////////
// CImpactCtrl properties

LPDISPATCH CImpactCtrl::GetDataSource()
{
	LPDISPATCH result;
	GetProperty(0x1, VT_DISPATCH, (void*)&result);
	return result;
}

void CImpactCtrl::SetDataSource(LPDISPATCH propVal)
{
	SetProperty(0x1, VT_DISPATCH, propVal);
}

LPDISPATCH CImpactCtrl::GetEditorCtrl()
{
	LPDISPATCH result;
	GetProperty(0x2, VT_DISPATCH, (void*)&result);
	return result;
}

void CImpactCtrl::SetEditorCtrl(LPDISPATCH propVal)
{
	SetProperty(0x2, VT_DISPATCH, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// CImpactCtrl operations

BOOL CImpactCtrl::Update()
{
	BOOL result;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL CImpactCtrl::SaveReportTo(LPCTSTR szFileName)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		szFileName);
	return result;
}

BOOL CImpactCtrl::IsReportView()
{
	BOOL result;
	InvokeHelper(0x5, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString CImpactCtrl::GetReportName()
{
	CString result;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}
