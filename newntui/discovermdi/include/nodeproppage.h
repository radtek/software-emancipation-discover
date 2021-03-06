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
#if !defined(AFX_NODEPROPPAGE_H__406F8FC4_C2A4_11D2_AF89_00A0C9B71DC4__INCLUDED_)
#define AFX_NODEPROPPAGE_H__406F8FC4_C2A4_11D2_AF89_00A0C9B71DC4__INCLUDED_
#include "GraphView.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NodePropPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNodePropPage dialog

class CNodePropPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CNodePropPage)

// Construction
public:
	void UpdateBorderColorRect(void);
	void SetGraphSettings(CGraphSettings* settings);
	CNodePropPage();
	~CNodePropPage();

// Dialog Data
	//{{AFX_DATA(CNodePropPage)
	enum { IDD = IDD_GRAPH_NODE };
	CComboBox	m_BorderSize;
	CSliderCtrl	m_NodeRed;
	CSliderCtrl	m_NodeGreen;
	CStatic	m_NodeColor;
	CSliderCtrl	m_BorderRed;
	CSliderCtrl	m_BorderGreen;
	CSliderCtrl	m_NodeBlue;
	CStatic	m_BorderColor;
	CSliderCtrl	m_BorderBlue;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CNodePropPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CNodePropPage)
	afx_msg void OnFocused();
	afx_msg void OnSelected();
	afx_msg void OnUnselected();
	virtual BOOL OnInitDialog();
	afx_msg void OnBorderRed(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBorderGreen(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBorderBlue(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNodeRed(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OneNodeGreen(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNodeBlue(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPaint();
	afx_msg void OnFont();
	afx_msg void OnSelchangeThickness();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void SetBorderSizeControl();
	void UpdateNodeColorRect(void);
	int m_CurType;
	void SetSliders(void);
	CGraphSettings* m_Settings;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NODEPROPPAGE_H__406F8FC4_C2A4_11D2_AF89_00A0C9B71DC4__INCLUDED_)
