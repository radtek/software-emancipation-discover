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
#ifndef _relationStruct_h
#define _relationStruct_h

#include <stdlib.h>

#include "uintList.h"
#include "attributeList.h"

struct relation
{
  char           *name;
  uintList       *source;
  uintList       *target;
  attributeList  *attributes;
#if defined(__cplusplus) && ! defined(USING_PURIFY)
  static void *operator new (size_t);
  static void  operator delete (void *);
#endif
};

typedef struct relation relationStruct;

#ifdef __cplusplus

extern "C"
{
  relationStruct *CreateRelationStruct(void);
  void            DestroyRelationStruct(relationStruct *loc);
#ifdef COUNT_STRUCTS
  void            ReportRelationStructs();
#endif
}

#else

  relationStruct *CreateRelationStruct();
  void            DestroyRelationStruct();
#ifdef COUNT_STRUCTS
  void            ReportRelationStructs();
#endif

#endif

#endif
