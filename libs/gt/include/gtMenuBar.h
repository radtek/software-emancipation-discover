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
#ifndef _gtMenuBar_h
#define _gtMenuBar_h

// gtMenuBar.h
//------------------------------------------
// synopsis:
// generic MenuBar manager (gtMenuBar)
//
//------------------------------------------

#ifndef _gtManager_h
#include <gtManager.h>
#endif

class gtMenuBar : public gtManager
{
  public:
    // Creates a MenuBar suitable for specifying arbitrary geometries.
    // gtMenuBars can only have gtCascadeButtons as children.
    // Pre: It must have a valid gt object parent passed to it.
    // Post: The returned pointer points to a valid gtMenuBar specific to
    // to the chosen toolkit.
    static gtMenuBar* create(gtBase *parent, const char *name);

    ~gtMenuBar();

    // specifies the cascade button which opens up the help menu
    virtual void set_help(gtCascadeButton *) = 0;

  protected:
    gtMenuBar();
};

#endif // _gtMenuBar_h

/*
   START-LOG-------------------------------------------

 $Log: gtMenuBar.h  $
 Revision 1.1 1993/07/28 19:47:45EDT builder 
 made from unix file
 * Revision 1.2.1.2  1992/10/09  18:10:18  jon
 * RCS history fixup
 *
 * Revision 1.2.1.1  92/10/07  20:33:58  smit
 * *** empty log message ***
 * 
 * Revision 1.2  92/10/07  20:33:57  smit
 * *** empty log message ***
 * 
 * Revision 1.1  92/10/07  18:19:52  smit
 * Initial revision
 * 
 * Revision 1.1  92/10/07  17:55:21  smit
 * Initial revision
 * 
// Revision 1.5  92/09/11  11:12:12  builder
// Make destructor public.
// 
// Revision 1.4  92/09/11  04:07:29  builder
// Add ctor and dtor.
// 
// Revision 1.3  92/07/30  23:44:45  glenn
// GT method name changes
// 
// Revision 1.2  92/07/22  13:40:54  rfermier
// added set_help functions
// 
// Revision 1.1  92/07/08  20:39:03  rfermier
// Initial revision
// 

   END-LOG---------------------------------------------
*/
