#if !defined(AFX_CODEROVERINTEGRATOR_H__8A87C74A_62FA_4600_9193_73F43FEB0876__INCLUDED_)
#define AFX_CODEROVERINTEGRATOR_H__8A87C74A_62FA_4600_9193_73F43FEB0876__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CCodeRoverIntegrator wrapper class

class CCodeRoverIntegrator : public CWnd
{
protected:
	DECLARE_DYNCREATE(CCodeRoverIntegrator)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x8dbae788, 0xdb45, 0x11d4, { 0x8e, 0x41, 0x0, 0x1, 0x2, 0x39, 0x3, 0x21 } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName,
		LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect,
		CWnd* pParentWnd, UINT nID,
		CCreateContext* pContext = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); }

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect, CWnd* pParentWnd, UINT nID,
		CFile* pPersist = NULL, BOOL bStorage = FALSE,
		BSTR bstrLicKey = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); }

// Attributes
public:
	CString GetEditorName();
	void SetEditorName(LPCTSTR);
	CString GetEditorsList();
	void SetEditorsList(LPCTSTR);

// Operations
public:
	void MakeSelection(LPCTSTR filename, long line, long column, long len);
	void OpenFile(LPCTSTR filename, long line);
	void SetInfo(LPCTSTR text);
	BOOL Reconnect();
	long GetModelLine(LPCTSTR pszLocalName, LPCTSTR pszBaseName, long nLine);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CODEROVERINTEGRATOR_H__8A87C74A_62FA_4600_9193_73F43FEB0876__INCLUDED_)
