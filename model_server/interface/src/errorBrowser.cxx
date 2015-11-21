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
// errorBrowser.h.C
//------------------------------------------
// synopsis:
// Interface to errors generated by the parsers.
//------------------------------------------

// INCLUDE FILES
#include <machdep.h>
#include <cLibraryFunctions.h>
#include <msg.h>
#include <x11_intrinsic.h>
#include <viewerShell.h>
#include <steView.h>
#include <ste_interface.h>

#include <smt.h>
#include <RTL.h>
#include <SelectFromRTL.h>
#include <objArr.h>
#include <errorReport.h>
#include <errorBrowser.h>
#include <genError.h>
#include <customize_util.h>
#include <gtDlgTemplate.h>
#include <gtDisplay.h>
#include <proj.h>
#include <objRawApp.h>
#include <gtRTL.h>
#include <messages.h>
#include <genArr.h>
#include <vpopen.h>
#include <driver_mode.h>

#if defined(NEW_UI)
#include "../../DIS_ui/interface.h"
#include "galaxy_undefs.h"
extern Application* DISui_app;
#endif    // NEW_UI
#include <Interpreter.h>

struct ast_shared_errors* ast_get_shared_errors();
extern "C" error_lex(const char*);
extern int is_forgiving();

// FILE STATIC VARIABLES

static errorBrowser* error_browser;
static RTLPtr err_rtl_header;
static genString containing_files;
static genString pure_message;

objArr error_messages;


// The next function was added to initialize the error information and to
//    allow gala to display the error file.
// The only call should be in DIS_main/DIS_main.code
const char* get_parser_error_filename()
{
    if(error_browser == NULL)
	error_browser = new errorBrowser;
    return(error_browser->get_error_filename() );
}

    
void make_error_string(errorReport* report, genString &str)
{
    Initialize(make_error_string);

    const char* no_file = "";
    const char* fnm     = report->filename;
    const char* msg     = report->message;
    genString   loc;

    smtHeaderPtr smt_header = (report->filename ?
			       smtHeader::find(report->filename) : NULL);

    smtTreePtr smt_node = NULL;

    fnm = report->filename;
    if(fnm){
	// skip colon character
	while (*fnm == '-' || *fnm == '+') ++fnm;
	while (isdigit(*fnm)) ++fnm;
	if (*fnm == ':') ++fnm;
    }
//    fnm = strrchr(fnm, '/');
//    fnm++;
    if(smt_header && smt_header->srcbuf)
    {
	for(int token = report->linenum; !smt_node && token > 0; token--)
	    smt_node = smt_header->tn_na(token);

//	if(smt_header->get_filename()) {
//	    fnm = smt_header->get_filename();
//	}

	if(smt_node)
	    loc.printf(gettext(TXT("line %d")), smt_node->src_line_num);
    } else if (report->filename) {
	loc.printf(gettext(TXT("line %d")), report->linenum);
    } else
	no_file = "### ";

    fnm = realOSPATH((char *)fnm);

    if(fnm == NULL) fnm = gettext(TXT("<no file>"));
    if(msg == NULL) msg = gettext(TXT("<no message>"));

    if(loc.length() == 0)
	loc.printf(gettext(TXT("line %d")), report->linenum);

    genString line;
    line.printf("%s%s, %s: %s", no_file, fnm, loc.str(), msg);

    /* 
      eliminating any control characters from the buffer
      (they cause icons to be displayed in the Error Browser)
    */
    char * line_buffer = (char *)line;
    if (line_buffer)
	while (*line_buffer) {
	    if (*line_buffer < ' ')
		*line_buffer = ' ';
	    line_buffer++;
	}
    line += '\n';
    str   = line;
}

extern "C" int compilation_start(char *mode_name, int force_popup = 1)
{
    Initialize(compilation_start);
    int         retval              = 0;
#ifndef NEW_UI
    viewer      *compilation_viewer = NULL;
    viewerShell *vs                 = NULL;

    if(force_popup == 1)
	compilation_viewer = viewerShell::find_target_viewer();
    else{
	vs = viewerShell::get_current_vs(1); // Don\'t create if not exists.
	if(vs)
	    compilation_viewer = viewerShell::find_target_viewer();
    }
    if(compilation_viewer){
	// Setup text (epoch) view in a viewer
	retval         = 1;
	view      *v   = compilation_viewer->get_view_ptr();
	steScreen *scr = compilation_viewer->get_screen();
	int  screen_id = 0;
	if(scr)
	    screen_id = scr->get_screen();
	if(v && !is_steView(v)){
	    if(force_popup)
		compilation_viewer->change_view(NULL, 1);
	    else
		retval = 0;  // Don\'t switch from graphical to text view.
	}
	ste_compilation_init(mode_name, screen_id);
    }
    else
	retval = 0;
#endif
    return retval;
}

// genArr(char) is faster then genString
genArr(char);

static int append_string (genArrOf(char) * arr, const char * text)
{
    int ret_val = -1;

    if (text) {
	int size = strlen (text);
	char * ptr = arr->grow(size);
	memcpy(ptr, text, size);
	ret_val = 0;
    }
    
    return ret_val;
}

extern "C" void errorBrowser_show_errors_array()
{
    Initialize(errorBrowser_show_errors_array);
    
    if(!errorBrowser_empty()){
	if(compilation_start("Parser errors")){
	    genArrOf(char) comp_buff;
	    for(int i = 0; i < error_messages.size(); i++){
		objString *error_str = (objString *)error_messages[i];
		const char * message = error_str->str();
		append_string (&comp_buff, message);
	    }
	    append_string (&comp_buff, "\nCompilation finished.\n");
	    comp_buff.append("");

	    ste_compilation_add(comp_buff[0]);

	    ste_compilation_finalize();
	}
    }
    else{ // Just clear errors if any viewerShell exists.
	if(is_gui())
	    ste_compilation_clear();
    }
    return;
}

extern "C" void errorBrowser_show_errors()
{
    Initialize(errorBrowser_show_errors);
    
#ifndef NEW_UI
    errorBrowser_show_errors_array();
#endif

    Return
}
#ifdef XXX_errorBrowser_collect_errors_array
extern "C" void errorBrowser_collect_errors_array(sharedArrOf(errorReport)& array,
                                                  const char * lname /* =NULL */ )
{
    Initialize(errorBrowser_collect_errors_array);

#ifdef NEW_UI
    if(error_browser == NULL)
	error_browser = new errorBrowser;
    bool alreadyOpen = error_browser->error_file_open();
    if (!alreadyOpen) error_browser->open_error_file();
#endif

    int num_errors = array.size();

#ifdef NEW_UI
    genString label;
    if (lname == NULL) {
        if ((array.size() > 0) && (array[0]->filename) )
            lname = array[0]->filename;
        else 
            lname = " ";
    }
    if (num_errors == 0)
        label.printf("%s - No Parser Errors", lname);
    else if (num_errors == 1)
        label.printf("%s - Parser Error", lname);
    else
        label.printf("%s - Parser Errors", lname);
    error_browser->timestamp(label);
#endif

    for(int i = 0; i < num_errors; i++){
	genString error_str;
	make_error_string(array[i], error_str);
	objString *str = new objString((char *)error_str);
	Assert(str);
#ifdef NEW_UI
	OSapi_fprintf(error_browser->get_error_fd(), "\t%s", (char*)error_str);
#else
	error_messages.insert(str);
#endif
    }

#ifdef NEW_UI
    OSapi_fprintf(error_browser->get_error_fd(), "\n");
    if (alreadyOpen)
        error_browser->flush_error_file();
    else
        error_browser->close_error_file();
#endif    // NEW_UI

    Return;
#endif //}
#ifdef XXX_errorBrowser_collect_errors
extern "C" void errorBrowser_collect_errors(const char* lname /* =NULL */)
{
    Initialize(errorBrowser_collect_errors);

    sharedArrOf(errorReport)& array = *(sharedArrOf(errorReport)*)ast_get_shared_errors();
    errorBrowser_collect_errors_array(array, lname);
}
#endif
extern "C" int errorBrowser_empty()
{
    Initialize(errorBrowser_empty);
    
    return(error_messages.size() == 0);
}

void ast_error_clean ()
{
    Initialize(ast_error_clean);

    sharedArrOf(errorReport)& array =
	*(sharedArrOf(errorReport)*)ast_get_shared_errors();
    array.reset();
}

void errorBrowser::popup()
{
    Initialize(errorBrowser::popup);
#ifndef NEW_UI
    if(error_browser == NULL)
	error_browser = new errorBrowser;

    error_browser->sf_rtl->shell->popup(0);
    error_browser->sf_rtl->shell->bring_to_top();
#endif
    Return
}

errorBrowser::errorBrowser()
{
#ifndef NEW_UI
    sf_rtl = new SelectFromRTL(
	0, TXT("Error Browser"), select_callback, &rtl_selection);
    sf_rtl->mode(gtBrowse, 0);
    sf_rtl->buttons(TXT("Clear All"), TXT("Show"), TXT("Done"));
    sf_rtl->help_context_name("Pset.Help.ErrorBrowser");
    timestamp(NULL);

#else    // NEW_UI
    error_fd_ = NULL;
    error_filename_ = OSapi_tempnam(0, "cpp_errors");

    // gala bug - Need to make sure the file is created
    //    so gala can succussfully monitor it.
    open_error_file();
    OSapi_fprintf(get_error_fd(), "\n");
    close_error_file();
    
#endif    // NEW_UI

}

errorBrowser::~errorBrowser()
{
#ifdef NEW_UI
    close_error_file();

#else    // Not NEW_UI
    delete sf_rtl;

#endif    // NEW_UI
}

void errorBrowser::timestamp(const char* label)
{
    genString message;
    time_t seconds_since_epoch = OSapi_time(NULL);

#ifdef NEW_UI
    if (label && *label)
        message.printf("%s : %s", label, OSapi_ctime(&seconds_since_epoch) );
    else
        message.printf("\t%s", OSapi_ctime(&seconds_since_epoch) );

    bool alreadyOpen = error_file_open();
    if (!alreadyOpen) open_error_file();

    OSapi_fprintf (get_error_fd(), "%s", (char*) message);

    if (alreadyOpen)
        flush_error_file();
    else
        close_error_file();

#else    // Not NEW_UI
    message.printf("%s: %s", TXT("Parser Errors"), OSapi_ctime(&seconds_since_epoch));
    sf_rtl->init(message, err_rtl_header, 0);

#endif    // NEW_UI
}

static objSet hds_in_browser;

void errorBrowserClear ()
{
    for(int i = error_messages.size() - 1; i >= 0; i--){
	delete error_messages[i];
    }
    error_messages.removeAll();
    ast_error_clean();
#ifndef NEW_UI
    if (err_rtl_header)
	((RTLNodePtr)err_rtl_header->get_root())->clear();
     if(error_browser !=NULL){
        RTLPtr old_rtl_head = error_browser->sf_rtl->rtlist->RTL();
	error_browser->sf_rtl->rtlist->set_rtl(NULL);
	error_browser->sf_rtl->rtlist->set_rtl(old_rtl_head);
    }
    hds_in_browser.remove_all();
    ste_compilation_clear();
#endif
}

#ifndef NEW_UI
void errorBrowser::select_callback(void* oa, int show_button, int, const char*)
{
    Initialize(errorBrowser::select_callback);
    if(!oa)
	Return

    if(! show_button) {  // clear button was pressed
	ast_error_clean();
	if (err_rtl_header) ((RTLNodePtr)err_rtl_header->get_root())->clear();
	
	if(error_browser !=NULL){
            RTLPtr old_rtl_head = error_browser->sf_rtl->rtlist->RTL();
	    error_browser->sf_rtl->rtlist->set_rtl(NULL);
	    error_browser->sf_rtl->rtlist->set_rtl(old_rtl_head);
	 }
     }

    objArr& array = *(objArr*)oa;
    Obj* el;
#if 0
    ForEach(el, array)
    {
	objNotePtr obj_note = checked_cast(objNote,el);
	if(is_objNote(obj_note))
	    obj_note->focus();
    }
#endif
    array.removeAll();
    Return
}
#endif    // Not NEW_UI

#ifndef NEW_UI
void errorBrowser::destroy_callback(void* data)
{
    Initialize(errorBrowser::destroy_callback);
    if(data)
    {
	errorBrowser* eb = (errorBrowser*)data;

	eb->sf_rtl = NULL;
	delete eb;

	if(error_browser == eb)
	    error_browser = NULL;
    }
    Return
}
#endif    // NEW_UI

// Update the errorBrowser display.

extern "C" void view_flush_rtls();

void errorBrowser::resume_display()
{
    Initialize(errorBrowser::resume_display);
#ifndef NEW_UI
    timestamp(NULL);

    view_flush_rtls();
    //real_view_regenerate(err_rtl_header);

    popup();
#endif
    Return
}

// Stop updating the errorBrowser display.

void errorBrowser::suspend_display()
{
    // We cannot close the view of the RTL in this function because a
    // transaction may be pending in the SMT code that invoked it.
    // Modifications to the RTL after its view is closed cause a crash
    // because the view is not completely removed until the transaction is
    // completed.  Anyway, the pending transaction seems to suppress the
    // update of the display (which is what we wanted).
}

// Add a new error to the list of errors known by the errorBrowser.
void errorBrowser::add_error(errorReport* report)
{
    Initialize(errorBrowser::add_error);
#ifndef NEW_UI
    if(!err_rtl_header)
	Return
#endif

    const char* no_file = "";
    const char* fnm = report->filename;
    const char* msg = report->message;
    genString loc;

    smtHeaderPtr smt_header = (report->filename ?
			       smtHeader::find(report->filename) : NULL);

    smtTreePtr smt_node = NULL;
    appTreePtr err_node = NULL;

    if(smt_header && smt_header->srcbuf)
    {
	for(int token = report->linenum; !smt_node && token > 0; token--)
	    smt_node = smt_header->tn_na(token);

	if(smt_header->get_filename()) {
	    fnm = smt_header->get_filename();
	}

	if(smt_node)
	    loc.printf(gettext(TXT("line %d")), smt_node->src_line_num);

	err_node = smt_node;
    } else if (report->filename) {
	fnm = report->filename;

	// skip colon character

	while (*fnm == '-' || *fnm == '+') ++fnm;
	while (isdigit(*fnm)) ++fnm;
	if (*fnm == ':') ++fnm;
	
	// check if raw mode file is created
	app *hd = app::get_header(App_RAW, (char *) fnm);
	if (!hd)
	    hd = db_new (objRawApp, ((char *)fnm, 0, 0));

	loc.printf(gettext(TXT("line %d")), report->linenum);

	err_node = checked_cast (appTree, hd->get_root());
    } else
	no_file = "### ";

    fnm = realOSPATH((char *)fnm);

    if(fnm == NULL)
	fnm = gettext(TXT("<no file>"));

    if(msg == NULL)
	msg = gettext(TXT("<no message>"));

    if(loc.length() == 0)
	loc.printf(gettext(TXT("line %d")), report->linenum);

    genString line;
    line.printf("%s%s, %s: %s", no_file, fnm, loc.str(), msg);

    /* 
      eliminating any control characters from the buffer
      (they cause icons to be displayed in the Error Browser)
    */
    char * line_buffer = (char *)line;
    if (line_buffer)
	while (*line_buffer) {
	    if (*line_buffer < ' ')
		*line_buffer = ' ';
	    line_buffer++;
	}

    IF(err_node == NULL)
	return;
    
#if 0
    objErrNotePtr err_note = db_new(objErrNote, (err_node, line, smt_node ? smt_node->src_line_num : report->linenum));
#ifndef NEW_UI
    obj_insert(err_rtl_header, FIRST, err_note,
	       checked_cast(appTree,err_rtl_header->get_root()), NULL);
#else    // NEW_UI
    dis_message(NULL, MSG_WARN, "add_error in errorBrowser needs to be implemented.");
#endif
#endif
}

static void print_error(errorReport* report)
{
    Initialize(print_error);

    const char* no_file = "";
    const char* fnm = report->filename;
    const char* msg1 = report->message;
    genString loc;

    smtHeaderPtr smt_header = (fnm ? smtHeader::find(report->filename) : NULL);

    smtTreePtr smt_node = NULL;
    appTreePtr err_node = NULL;

    if(smt_header) {
	if (smt_header->srcbuf) {
	    for(int token = report->linenum; !smt_node && token > 0; token--)
		smt_node = smt_header->tn_na(token);

	    if(smt_node)
		loc.printf(gettext(TXT(", line %d")), smt_node->src_line_num);
	}
	if(smt_header->get_phys_name())
	    fnm = smt_header->get_phys_name();
	else if (smt_header->get_filename())
	    fnm = smt_header->get_filename();

	err_node = smt_node;
    } else if (report->filename) {
	// skip colon character
	fnm = strchr(report->filename, ':');
	if (!fnm) 
	    fnm = report->filename;
	else 
	    fnm++;
	
	loc.printf(gettext(TXT(", line %d")), report->linenum);

    } else
	no_file = "### ";

    fnm = realOSPATH((char *)fnm);

    if(fnm == NULL)
	fnm = gettext(TXT("<no file>"));

    if(msg1 == NULL)
	msg1 = gettext(TXT("<no message>"));

    if(loc.length() == 0)
	loc.printf(gettext(TXT(",line %d")), report->linenum);

    containing_files = 0;
    pure_message = 0;
    error_lex(msg1);
    
    if (containing_files.length() )
	msg("$1") << containing_files.str() << eom;

    genString line;
    const char* puremessage = pure_message.str();
    if (!puremessage)
	puremessage = "";
    line.printf("%s%s%s: %s", no_file, fnm, loc.str(), puremessage);
    
    msg("$1") << line.str() << eom;

#if 0
    if (is_forgiving() && smt_node)
	build_error_node (smt_node, line, pure_message);  
#endif
}

extern "C" void print_errors_array(sharedArrOf(errorReport)& array)
{
    Initialize(print_errors_array);

    int sz = array.size();
    for(int i = 0; i < sz; i++)
	print_error(array[i]);
}

extern "C" void errorBrowser_print_errors()
{
    Initialize(errorBrowser_print_errors);
    sharedArrOf(errorReport)& array =
	*(sharedArrOf(errorReport)*)ast_get_shared_errors();

    if (array.size())
	print_errors_array(array);
}

extern "C" void error_lex_out (char c)
{
    pure_message += c;
}

extern "C" void error_lex_print (char* txt, int fl)
{
    if (txt == 0 || *txt == 0)
	return;

    if (!fl) {
	containing_files += txt;
	return;
    }

    int len = strlen (txt);
    if (len >= 2) {
	char save = txt[len - 2];
	txt[len - 2] = 0;
	char* last_colon = strrchr(txt, ':');
	genString loc;
	if (last_colon) {
	    char* fnm = txt;
	    int linenum = 0;
	    linenum = (int)OSapi_atol(last_colon + 1);
	    *last_colon = 0;
	    smtHeader* smt_header = smtHeader::find(txt);
	    if(smt_header) {
		if (smt_header->srcbuf) {
		    smtTree* smt_node = NULL;
		    for(int token = linenum; !smt_node && token > 0; token--)
			smt_node = smt_header->tn_na(token);
		    
		    if(smt_node)
			linenum =smt_node->src_line_num;
		}	
		if(smt_header->get_phys_name())
		    fnm = smt_header->get_phys_name();
		else if(smt_header->get_filename())
		    fnm = smt_header->get_filename();
	    } else {
		fnm = strchr(txt, ':');
		if (!fnm) 
		    fnm = txt;
		else 
		    fnm++;
	    }
	    loc.printf ("%s:%d", fnm, linenum);
	    *last_colon = ':';
	} else 
	    loc = txt;
	loc += save;
	txt[len - 2] = save;
	if (save == ':')
	    loc += '\n';
	containing_files += loc;
    }
}

// This function returns ready status for screen parameter of viewer.
// called from void errorBrowser_show_errors_from_apps ()

static int errorBrowser_show_errors_from_app_ready()
{
    int retval = 0;
#ifndef NEW_UI 
    viewer* compilation_viewer = viewerShell::find_target_viewer();
    if(compilation_viewer){
	steScreen *scr = compilation_viewer->get_screen();
	if (scr)
	    retval = 1;
    }
#else
    fprintf(stderr,"errorBrowser_show_errors_from_app_ready() needs to be implemented\n");
#endif
    return retval;
}

// Extracts from app compilation errors (saved earlier), 
// builds compilation buffer and brings it to view

void errorBrowser_collect_errors_from_app (smtHeader* h)
{
    Initialize(errorBrowser_collect_errors_from_app);
}	    

// Brings error browser to view.
// Does delayed execution according result
// of errorBrowser_show_errors_from_app_ready()

void errorBrowser_show_errors_from_apps()
{
    Initialize(errorBrowser_show_errors_from_apps);
#ifndef NEW_UI
    if (!errorBrowser_show_errors_from_app_ready())
	gtBase::oneshot((void(*)(void*))errorBrowser_show_errors_from_apps, NULL);
    else
	errorBrowser_show_errors();
#else
    fprintf(stderr,"errorBrowser_show_errors_from_apps() needs to be implemented\n");
#endif
}

static int print_file(FILE* f, char* file)
{
  int retval = 0;
  char buffer[2048];

  FILE* src = OSapi_fopen(file, "rt");

  if (src) {
    while (OSapi_fgets (buffer, sizeof(buffer)-1, src))
      OSapi_fprintf(f, "%s", buffer);

    ;
    OSapi_fclose(src);
    retval = 1;
  }

  return retval;
}

static int errorbrowser_report_errorsCmd (Interpreter*i, int argc, char**argv)
{
  Initialize( errorbrowser_report_errorsCmd);

  if(argc < 2)
    return TCL_ERROR;

  char* errfile = argv[1];

#ifndef NEW_UI
  if (is_gui() && compilation_start("Parser errors")) {
    genString cmd;
    cmd.printf("(di-append-file-compilation-buffer \"%s\")", errfile);
    ste_epoch_evaluate(cmd);
  } else {
    print_file (stderr, errfile);
  }
#else
  if (!is_gui()) {
    print_file (stderr, errfile);
  } else {
    if(error_browser == NULL)
      error_browser = new errorBrowser;
    bool alreadyOpen = error_browser->error_file_open();
    if (!alreadyOpen) 
      error_browser->open_error_file();
    FILE* out = error_browser->get_error_fd();
    print_file (out, errfile);
    if (alreadyOpen)
      error_browser->flush_error_file();
    else
      error_browser->close_error_file();

    genString command = "dis_parser_message {Errors encountered while parsing.\nThe list of errors is stored in ";
    command += errfile;
    command += '\n';
    command += '}';
    rcall_dis_DISui_eval(DISui_app, (vstr*)command.str() );
  }
#endif
  return TCL_OK;
}

static int add_commands()
{
  new cliCommand("errorbrowser_report_errors", errorbrowser_report_errorsCmd);
  return 0;
}

static int dummy = add_commands();

