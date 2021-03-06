/*************************************************************************
* Copyright (c) 2015, Synopsys, Inc.                                     *
* All rights reserved.                                                   *
*                                                                        *
* Redistribution and use in source and binary forms, with or without     *
* modification, are permitted provided that the following conditions are *
* met:                                                                   *
*                                                                        *
* 1. Redistributions of source code must retain the above copyright      *
* notice, this list of conditions and the following disclaimer.          *
*                                                                        *
* 2. Redistributions in binary form must reproduce the above copyright   *
* notice, this list of conditions and the following disclaimer in the    *
* documentation and/or other materials provided with the distribution.   *
*                                                                        *
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS    *
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT      *
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR  *
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT   *
* HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, *
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT       *
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,  *
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY  *
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT    *
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE  *
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.   *
*************************************************************************/
#if !defined(AFX_QACHILDFRAME_H__447BA2A4_59FC_11D2_AF35_00A0C9B71DC4__INCLUDED_)
#define AFX_QACHILDFRAME_H__447BA2A4_59FC_11D2_AF35_00A0C9B71DC4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// QAChildFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CQAChildFrame frame

class CQAChildFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CQAChildFrame)
protected:
	CQAChildFrame();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:
	BOOL m_ResultsReady;
	void SetCurrentSetEnable(BOOL status);
	CSplitterWnd m_wndSplitter;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQAChildFrame)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_OVERLAPPEDWINDOW, const RECT& rect = rectDefault, CMDIFrameWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CQAChildFrame();

	// Generated message map functions
	//{{AFX_MSG(CQAChildFrame)
	afx_msg void OnClose();
	afx_msg void OnCancelMode();
	afx_msg void OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd);
	afx_msg void OnQAReset();
	afx_msg void OnQARun();
	afx_msg void OnQARunSel();
	afx_msg void OnUpdateQaBrowse(CCmdUI* pCmdUI);
	afx_msg void OnQaBrowse();
	afx_msg LRESULT OnServiceDisconnect(WPARAM wparam, LPARAM lparam);
	afx_msg void OnServiceChanged(void);
	afx_msg void OnOpen();
	afx_msg void OnSave();
	afx_msg void OnSaveReport();
	afx_msg void OnUpdateSavereport(CCmdUI* pCmdUI);
	afx_msg void OnUpdateQasave(CCmdUI* pCmdUI);
	afx_msg void OnIMAttach();
	afx_msg void OnUpdateIMAttach(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	CToolBar m_QATools;
private:
	BOOL m_ResultSetExist;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QACHILDFRAME_H__447BA2A4_59FC_11D2_AF35_00A0C9B71DC4__INCLUDED_)
