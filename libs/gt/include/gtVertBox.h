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
#ifndef _gtVertBox_h
#define _gtVertBox_h

// gtVertBox.h
//------------------------------------------
// synopsis:
// Manager suitable for aligning children vertically.
//------------------------------------------

#ifndef _gtManager_h
#include <gtManager.h>
#endif


class gtVertBox : public gtManager
{
  public:
    static gtVertBox* create(gtBase* parent, const char* name);
    static gtVertBox* create(gtBase* parent, const char* name, gtAlign);

    ~gtVertBox();

    virtual void margins(int h, int v) = 0;
    virtual void packing(gtPacking) = 0;
    virtual void columns(int) = 0;

  protected:
    gtVertBox();
};


/*
   START-LOG-------------------------------------------

   $Log: gtVertBox.h  $
   Revision 1.1 1993/02/24 13:32:17EST builder 
   made from unix file
 * Revision 1.2.1.4  1993/01/26  05:11:45  glenn
 * Add create with gtAlign.
 *
 * Revision 1.2.1.3  1992/12/30  19:08:54  glenn
 * Add margins, packing, columns.
 *
   END-LOG---------------------------------------------
*/

#endif // _gtVertBox_h
