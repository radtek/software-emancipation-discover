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
#ifndef _DC_Display_Selection_h
#define _DC_Display_Selection_h

// DC_Display_Selection.h
//------------------------------------------
// synopsis:
// Dialog to set member filter for Data Charts
//------------------------------------------

#ifndef ISO_CPP_HEADERS
#include <string.h>
#else /* ISO_CPP_HEADERS */
#include <cstring>
using namespace std;
#endif /* ISO_CPP_HEADERS */

#ifndef _prototypes_h
#include <prototypes.h>
#endif
#ifndef _gtDlgTemplate_h
#include <gtDlgTemplate.h>
#endif
#ifndef _gtTogB_h
#include <gtTogB.h>
#endif
#ifndef _gtHorzBox_h
#include <gtHorzBox.h>
#endif
#ifndef _gtLabel_h
#include <gtLabel.h>
#endif
#ifndef _gtStringEd_h
#include <gtStringEd.h>
#endif
#ifndef _gtPushButton_h
#include <gtPushButton.h>
#endif
#ifndef _gtToggleBox_h
#include <gtToggleBox.h>
#endif
#ifndef _oodt_ui_decls_h
#include <oodt_ui_decls.h>
#endif

BEGIN_C_DECL
void popup_DC_Display_Selection PROTO((void *arg_viewp, void *popup_node));
END_C_DECL

class DC_Display_Selection {
    gtHorzBox	*filtslot;
    gtToggleButton	*tb3;
    gtStringEditor	*text1;
    void       *popup_node, *viewp;

  public:
    gtDialogTemplate	*shell;
    DC_Display_Selection();
    void init(void *, void *);
    static void OK_CB(gtPushButton *tb, gtEvent *, void *cd, gtReason);
    static void Apply_CB(gtPushButton *, gtEvent *, void *cd, gtReason);
    static void Cancel_CB(gtPushButton *, gtEvent *, void *cd, gtReason);
    static void text_CB(gtStringEditor *, gtEvent *, void *cd, gtReason);
    void get_current_options();
    void do_it();
};

typedef DC_Display_Selection* DC_Display_Selection_Ptr;


/*
    START-LOG-------------------------------

    $Log: DC_Display_Selection.h  $
    Revision 1.2 2000/07/10 23:11:56EDT ktrans 
    mainline merge from Visual C++ 6/ISO (extensionless) standard header files
// Revision 1.2  1993/05/27  20:15:41  glenn
// NewFileSelector.h Noun_Context.h Noun_Search.h Nouns_RTL.h OODT_apl_entries.h PROJ_View_Pref.h Panner.h Print.h ProcessSelector.h Quick_Search.h RTL_apl_extern.h RTL_filter.h STE_Create_sd.h STE_Edit_Style.h STE_Edit_Style_Doc.h STE_Edit_Style_RGB.h STE_Edit_Style_TP.h SelectFname.h SelectFromList.h SoftAssoc_apl.h Text_Field.h all-interns.h all-stubs.h browserShell.h button_bar.h change_propagator.h customize.h dataDefn.h errorReport.h extract-dialog.h fileLanguageDlg.h generic-popup-menu.h help.h impactAnalysis.h oodt_class_member_sorter.h oodt_relation.h propagator_apl.h quickHelp.h stackmgr.h systemMessages.h top_widgets.h typeIn_Propagator.h ui-globals.h ui-rowcolumn.h uimx_context.h waiter.h waiter_types.h watchVar.h x11_intrinsic.h
//
// Revision 1.1  1992/12/17  21:36:09  wmm
// Initial revision
//
    END-LOG---------------------------------
*/

#endif // _DC_Display_Selection_h
