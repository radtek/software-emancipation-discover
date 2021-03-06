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
#ifdef COUNT_STRUCTS
#include <iostream.h>
#endif

#include <parray.h>

#include <positionStruct.h>

#define POSITION_STRUCTS_TO_ALLOCATE 10

static parray freePositions(POSITION_STRUCTS_TO_ALLOCATE);

#ifdef COUNT_STRUCTS
static int max_count = 0;
static int current_count = 0;
#endif

positionStruct *CreatePositionStruct(void)
{
  return new positionStruct;
}

#ifndef USING_PURIFY      
void *str_position::operator new(size_t)
{
  positionStruct *retval = 0;

  if ( freePositions.size() == 0  )
    {
      positionStruct *more = ::new positionStruct [ POSITION_STRUCTS_TO_ALLOCATE ];
      if ( more )
	{
	  for ( int i = 0; i < POSITION_STRUCTS_TO_ALLOCATE; i++ )
	    {
	      freePositions.insert((void *)&more[i]);
	    }
	}
    }
  
  retval = (positionStruct *) freePositions[freePositions.size()-1];
  freePositions.remove(freePositions.size()-1);
  
#ifdef COUNT_STRUCTS
  current_count++;
  if ( current_count > max_count )
    max_count = current_count;
#endif

  return retval;
}
#endif

void DestroyPositionStruct(positionStruct *p)
{
  delete p;
}

#ifndef USING_PURIFY
void str_position::operator delete(void *p)
{
  if ( p )
    {
      freePositions.insert((void *)p);
#ifdef COUNT_STRUCTS
      current_count--;
#endif
    }
}
#endif

#ifdef COUNT_STRUCTS
void ReportPositionStructs(void)
{
  cout << "Maximum number of position structs in use at one time: " << max_count << "\n";
  cout << "Current number of position structs in use: " << current_count << "\n";
}
#endif
