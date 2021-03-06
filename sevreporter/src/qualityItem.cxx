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
////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////

//++OSPORT
#include <pdumem.h>
//--OSPORT

//++SEV
#include <qualityItem.h>
#include <reportStream.h>
#include <cstring.h>
#include <descParser.yacc.h>
//--SEV

qualityItem::qualityItem(char const *_name, char const *_desc, char const *_score, char const *_weight, 
			 char const *_found, char const *_outof, char const *_units)
    : reportItem(_name, _desc)
{
  __score  = _score;
  __weight = _weight;
  __found  = _found;
  __outof  = _outof;
  __units  = _units;
}

qualityItem::~qualityItem(void)
{
  FREE_MEMORY(__score);
  FREE_MEMORY(__weight);
  FREE_MEMORY(__found);
  FREE_MEMORY(__outof);
  FREE_MEMORY(__units);
}

int qualityItem::onTag(int tag)
{
  int retval = -1;
  
  if ( current_stream )
    {
      switch ( tag )
	{
	case QUALITY_RESULT:
	case EMPTY_DESCRIPTION:
	  retval = current_stream->print_quality(this);
	  break;
	  
	default:
	  // pass unprocessed tags to base class
	  retval = reportItem::onTag(tag);
	  break;
	}
    }

  return retval;
}
