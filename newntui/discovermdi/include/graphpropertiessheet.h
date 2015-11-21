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
#if !defined(AFX_GRAPHPROPERTIESSHEET_H__A3EC5B9C_C1F1_11D2_AF88_00A0C9B71DC4__INCLUDED_)
#define AFX_GRAPHPROPERTIESSHEET_H__A3EC5B9C_C1F1_11D2_AF88_00A0C9B71DC4__INCLUDED_

#include "graphlayoutproppage.h"	// Added by ClassView
#include "GraphView.h"
#include "NodePropPage.h"
#include "EdgePropPage.h"
#include "GraphInheritancePropPage.h"
#include "GraphRelationsPropPage.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GraphPropertiesSheet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGraphPropertiesSheet

class CGraphPropertiesSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CGraphPropertiesSheet)

// Construction
public:
	CGraphPropertiesSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CGraphPropertiesSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:
	CGraphSettings* m_Settings;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphPropertiesSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetParameters(CGraphSettings* settings);
	CGraphLayoutPropPage m_Layout;
	CNodePropPage m_Node;
	CEdgePropPage m_Edge;
	CGraphInheritancePropPage m_Inheritance;
	CGraphRelationsPropPage m_Relations;
	virtual ~CGraphPropertiesSheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGraphPropertiesSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHPROPERTIESSHEET_H__A3EC5B9C_C1F1_11D2_AF88_00A0C9B71DC4__INCLUDED_)
