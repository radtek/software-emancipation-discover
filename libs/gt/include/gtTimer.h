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
#ifndef _gtTimer_h
#define _gtTimer_h

// gtTimer.h
//------------------------------------------
// synopsis:
// Timeouts
//
//------------------------------------------

class gtTimer;
typedef void (*gtTimerCB)(gtTimer*, void*);

class gtTimer
{
  public:
    static gtTimer* create(
	unsigned int delay, gtTimerCB callback, void* callback_data);

    virtual ~gtTimer();

    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void delay(unsigned int) = 0;
    virtual int  active() = 0;

  protected:
    gtTimerCB callback;
    void* callback_data;
    unsigned int _delay;

    gtTimer(unsigned int delay, gtTimerCB callback, void* callback_data);
};

#endif // _gtTimer_h

/*
   START-LOG-------------------------------------------

// $Log: gtTimer.h  $
// Revision 1.1 1993/07/28 19:47:53EDT builder 
// made from unix file
 * Revision 1.2.1.2  1992/10/09  18:13:17  jon
 * RCS history fixup
 *
 * Revision 1.2.1.1  92/10/07  20:35:11  smit
 * *** empty log message ***
 * 
 * Revision 1.2  92/10/07  20:35:10  smit
 * *** empty log message ***
 * 
 * Revision 1.1  92/10/07  18:20:00  smit
 * Initial revision
 * 
 * Revision 1.1  92/10/07  17:55:27  smit
 * Initial revision
 * 
// Revision 1.1  92/08/02  18:25:02  glenn
// Initial revision
// 
//------------------------------------------

   END-LOG---------------------------------------------
*/
