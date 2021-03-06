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
// LockPromptDlg.cpp : implementation file
//

#include "stdafx.h"
#include "discovermdi.h"
#include "LockPromptDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLockPromptDlg dialog


CLockPromptDlg::CLockPromptDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLockPromptDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLockPromptDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CLockPromptDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLockPromptDlg)
	DDX_Control(pDX, IDC_FILELIST, m_FileList);
	DDX_Control(pDX, IDC_DATASOURCE, m_DataSource);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLockPromptDlg, CDialog)
	//{{AFX_MSG_MAP(CLockPromptDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLockPromptDlg message handlers

BOOL CLockPromptDlg::OnInitDialog() {
CString res;
CString cmd;
BSTR sysCmd;
int elements;

	CDialog::OnInitDialog();

	// Forming file list  for submission
	cmd="set __cm_files__ [filter {kind==\"module\" && writable==1} [where defined $DiscoverSelection]]";
	sysCmd=cmd.AllocSysString();
	DataSourceAccessSync(&sysCmd);
	::SysFreeString(sysCmd);

	cmd="size $__cm_files__";
	sysCmd=cmd.AllocSysString();
	res=DataSourceAccessSync(&sysCmd);
	elements=atoi(res);
	::SysFreeString(sysCmd);

	for(int i=0;i<elements;i++) {

		// Extracting file name
	    cmd.Format("fname $__cm_files__ %d",i+1);
	    sysCmd=cmd.AllocSysString();
	    res=DataSourceAccessSync(&sysCmd);
	    ::SysFreeString(sysCmd);

		m_FileList.AddString(res);

	}
	cmd="unset __cm_files__";
	sysCmd=cmd.AllocSysString();
	res=DataSourceAccessSync(&sysCmd);
	elements=atoi(res);
	::SysFreeString(sysCmd);
	
	return TRUE;  
}

void CLockPromptDlg::OnOK()  {
CString cmd;
BSTR sysCmd;

	cmd="set __cm_files__ [filter {kind==\"module\" && writable==1} [where defined $DiscoverSelection]]";
	sysCmd=cmd.AllocSysString();
	DataSourceAccessSync(&sysCmd);
	::SysFreeString(sysCmd);

	cmd.Format("cm_lock $__cm_files__");
    sysCmd=cmd.AllocSysString();
    DataSourceAccessSync(&sysCmd);
    ::SysFreeString(sysCmd);

	cmd="unset __cm_files__";
	sysCmd=cmd.AllocSysString();
	DataSourceAccessSync(&sysCmd);
    ::SysFreeString(sysCmd);
	
	CDialog::OnOK();

}

CString CLockPromptDlg::DataSourceAccessSync(BSTR* command) {
	CString res;
	static BOOL bCommDlgShown = FALSE;
	res = m_DataSource.AccessSync(command);
	if (m_DataSource.IsConnectionLost() == TRUE &&
		bCommDlgShown != TRUE) {
		::MessageBox(m_hWnd, 
			   _T("Connection with server is lost."
			   " Make sure the server is running."),
			   _T("Server Communication Error."), 
			   MB_OK | MB_ICONINFORMATION); 
		bCommDlgShown = TRUE;
	} else if (m_DataSource.IsConnectionLost() != TRUE) {
		bCommDlgShown = FALSE;
	}	
	return res;
}
