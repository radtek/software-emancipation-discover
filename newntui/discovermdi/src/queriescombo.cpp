// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


#include "stdafx.h"
#include "queriescombo.h"

/////////////////////////////////////////////////////////////////////////////
// CQueriesCombo

IMPLEMENT_DYNCREATE(CQueriesCombo, CWnd)

/////////////////////////////////////////////////////////////////////////////
// CQueriesCombo properties

LPDISPATCH CQueriesCombo::GetDataSource()
{
	LPDISPATCH result;
	GetProperty(0x1, VT_DISPATCH, (void*)&result);
	return result;
}

void CQueriesCombo::SetDataSource(LPDISPATCH propVal)
{
	SetProperty(0x1, VT_DISPATCH, propVal);
}

CString CQueriesCombo::GetSelection()
{
	CString result;
	GetProperty(0x2, VT_BSTR, (void*)&result);
	return result;
}

void CQueriesCombo::SetSelection(LPCTSTR propVal)
{
	SetProperty(0x2, VT_BSTR, propVal);
}

CString CQueriesCombo::GetCategories()
{
	CString result;
	GetProperty(0x3, VT_BSTR, (void*)&result);
	return result;
}

void CQueriesCombo::SetCategories(LPCTSTR propVal)
{
	SetProperty(0x3, VT_BSTR, propVal);
}

CString CQueriesCombo::GetCaption()
{
	CString result;
	GetProperty(DISPID_CAPTION, VT_BSTR, (void*)&result);
	return result;
}

void CQueriesCombo::SetCaption(LPCTSTR propVal)
{
	SetProperty(DISPID_CAPTION, VT_BSTR, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// CQueriesCombo operations

CString CQueriesCombo::AccessFromName(LPCTSTR name)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		name);
	return result;
}

void CQueriesCombo::Update()
{
	InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

CString CQueriesCombo::GetQueriesList()
{
	CString result;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CQueriesCombo::Clear()
{
	InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

CString CQueriesCombo::GetSelectedQueries()
{
	CString result;
	InvokeHelper(0x8, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CQueriesCombo::AboutBox()
{
	InvokeHelper(0xfffffdd8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}
