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
/*
  help-act.h -- mark simpson

  This file contains necessary declarations for the use of the help
  features.  

  Instructions for use:

  1. include this file

  2. in the initial code add the call addHelpAction, to set up the
     help actions.

  3. set the transalations of all swidgets to have this help feature
     to helpTrans.

  4. machine wash in warm only, no bleach, dry flat.
*/

extern void UI_doHelp();
extern void UI_helpAction_func();

static XtActionsRec UI_helpAction[]=
{	{ "help", UI_helpAction_func}
};

#define helpTrans(file) \
  "#override\n<Key>F1:help(file) \n<Key>Help:help(file) \n"

#define addHelpAction UxAddActions(UI_helpAction, \
			       XtNumber(UI_helpAction));

/*
    START-LOG-------------------------------

    $Log: help-act.h  $
    Revision 1.2 1995/07/27 20:38:10EDT rajan 
    Port
 * Revision 1.2.1.2  1992/10/09  19:56:54  kws
 * Fix comments
 *

    END-LOG---------------------------------
*/

