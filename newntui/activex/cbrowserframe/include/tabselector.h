// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CTabSelector wrapper class

class CTabSelector : public CWnd
{
protected:
	DECLARE_DYNCREATE(CTabSelector)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0xadc2dfd4, 0x1e61, 0x11d2, { 0xae, 0xf3, 0x0, 0xa0, 0xc9, 0xb7, 0x1d, 0xc4 } };
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
	LPDISPATCH GetDataSource();
	void SetDataSource(LPDISPATCH);
	CString GetOutputVariable();
	void SetOutputVariable(LPCTSTR);
	CString GetSelectionVariable();
	void SetSelectionVariable(LPCTSTR);
	CString GetCaption();
	void SetCaption(LPCTSTR);
	CString GetSelectedCategories();
	void SetSelectedCategories(LPCTSTR);

// Operations
public:
	CString AccessFromName(LPCTSTR name);
	void Update();
	CString AccessFromCategory(LPCTSTR category);
	CString AccessFromQuery(LPCTSTR query);
	void Unselect();
	void AboutBox();
};