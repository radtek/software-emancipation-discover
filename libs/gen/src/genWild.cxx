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
// genWild.h.C
//------------------------------------------
// synopsis:
//
// Wrapper to make command-shell glob patterns compatible with
// more general purpose regexp utility.
//
// RESTRICTION: Functions in this file are used by the internal
// tracing/exception-handling routines, so they cannot use these
// routines themselves (infinite recursion).
// Do not insert Initialize() macros in this file.
//------------------------------------------

// INCLUDE FILES

#ifndef ISO_CPP_HEADERS
#include <stdio.h>
#include <stdlib.h>
#else /* ISO_CPP_HEADERS */
#include <cstdio>
namespace std {};
using namespace std;
#include <cstdlib>
#endif /* ISO_CPP_HEADERS */

#include <genWild.h>

#include <machdep.h>
#include <genError.h>

// VARIABLE DEFINITIONS

static genString ret_str;

// FUNCTION DEFINITIONS

const char* glob_to_regexp(const char* p, int complicate_level)
// Convert shell-glob to regular expression,
// unless enclosed in double-quotes.
// Return value points to genString.
//
// p is the pattern
// complicate_level: COMPLICATE_LEVEL_0 ==> for all other"s use
//                      pre-pend ^ and append $ and "*" is replaced as ".*"
//                      pre-pend "\\" for "(" and ")"
//                   COMPLICATE_LEVEL_1 ==> for each project level definition
//                      in the pdf file
//                      pre-pend ^ and "*" is replaced as "[^/]*"
//                      no pre-pend "\\" for "(" and ")"
//                   COMPLICATE_LEVEL_2 ==> for the fast pdf mapping which
//                      uses flex
//                      The same as COMPLICATE_LEVEL_3 (obsolete)
//                      no pre-pend "\\" for "(" and ")"
//                   COMPLICATE_LEVEL_3 ==> for the fast pdf mapping which
//                      uses flex
//                      "*" is replaced as ".*"
//                      no pre-pend "\\" for "(" and ")"
//                   COMPLICATE_LEVEL_4 ==> same as COMPLICATE_LEVEL_1
//                      append $
{
  Initialize(glob_to_regexp);

    int cl = complicate_level;
    if (cl == COMPLICATE_LEVEL_4)
        complicate_level = COMPLICATE_LEVEL_1;
    if (p == NULL || *p == '\0')
        return "";

    ret_str = 0;

    IF(complicate_level == COMPLICATE_LEVEL_2)
      complicate_level = COMPLICATE_LEVEL_3;

    if (complicate_level != COMPLICATE_LEVEL_3){
      ret_str = "^";
      while(*p){
	if (strncmp(p,"**/",3) == 0) {
	  ret_str += "([^\\/].*\\/)?";
	  p += 3;
	} else if (strncmp(p,"/**",3) == 0) {
	  ret_str += "(\\/.*)?";
	  p += 3;
	} else if (strncmp(p,"**",2) == 0) {
	  ret_str += "([^\\/].*)?";
	  p += 2;
	} else if (*p == '*') {
	  if (complicate_level == COMPLICATE_LEVEL_0)
	    ret_str += ".*";
	  else if (complicate_level == COMPLICATE_LEVEL_1)
	    ret_str += "[^/]*";
	  p++;
	} else if (*p == '?') {
	  ret_str += '.';
	  p++;
	} else if (*p == '[') {
	  ret_str += *p++;
	  if (*p == '^')
	    ret_str += *p++;
	} else if (*p == '/' ||
		   *p == '.' ||
		   *p == '+' ||
		   *p == '^' ||
		   *p == '$'){
	  ret_str += "\\";
	  ret_str += *p++;
	} else if (*p == '(' || *p == ')') {
	  if (complicate_level == COMPLICATE_LEVEL_0)
	    ret_str += "\\";
	  ret_str += *p++;
	} else if (*p == '\\') {
	  if (*(p+1)) {
	    ret_str += *p++;
	    ret_str += *p++;
	  } else {
	    p++;
	  }
// mg	  break;
	} else {
	  ret_str += *p++;
	}
      }
    } else {  // complicate_level == COMPLICATE_LEVEL_3
      while(*p) {
	if (strncmp(p,"**/",3) == 0) {
	  ret_str += "([^\\n\\t][^\\t]*\\n)?";
	  p += 3;
	} else if (strncmp(p,"/**",3) == 0) {
	  ret_str += "(\\n[^\\t]*)?";
	  p += 3;
	} else if (strncmp(p,"**",2) == 0) {
	  ret_str += "([^\\n\\t][^\\t]*)?";
	  p += 2;
	} else if (*p == '*'){
	  ret_str += "[^\\n\\t]*";
	  p++;
	} else if (*p == '?'){
	  ret_str += '.';
	  p++;
	} else if (*p == '['){
	  ret_str += *p++;
	  if (*p == '^')
	    ret_str += *p++;
	} else if (*p == '/') {
	  ret_str += "\\n";
	  p++;
	} else if (*p == '.' ||
		   *p == '+' ||
		   *p == '^' ||
		   *p == '$') {
	  ret_str += "\\";
	  ret_str += *p++;
	} else if (*p == '(' || *p == ')') {
	  ret_str += *p++;
	} else if (*p == '\\'){
	  if (*(p+1)){
	    ret_str += *p++;
	    ret_str += *p++;
	  } else {
	    p++;
	  }
// mg	  break;
	} else {
	  ret_str += *p++;
	}
      }
    }

    if (complicate_level == COMPLICATE_LEVEL_0 || cl == COMPLICATE_LEVEL_4)
        ret_str += '$';

    return ret_str.str();
}

static const char* convert_unquoted_to_wildcard(
    const char* input, int complicate_level)
//
// Convert shell-glob to regular expression,
// unless enclosed in double-quotes.
//
// The interface of this routine is similar to the previous one glob_to_regexp.
{
    if(input == NULL || *input == '\0')
        return "";
    else if(*input != '"')
        return glob_to_regexp(input, complicate_level);

    ret_str = input + 1;

    // Strip trailing double-quote, if any.
    if(ret_str.length() > 1)
    {
        char* p = (char *)ret_str.str();
        if (p[ret_str.length()-1] == '"')
            p[ret_str.length()-1] = '\0';
    }

    return ret_str.str();
}

WildRegexp::WildRegexp(const char* pat)
: Regexp(convert_unquoted_to_wildcard(pat, COMPLICATE_LEVEL_0))
// constructor for WildRegexp take pattern only as input
// which is called all other area except the projects
// complicate_level is COMPLICATE_LEVEL_0
{}

WildRegexp::WildRegexp(const char* pat, int complicate_level)
: Regexp(convert_unquoted_to_wildcard(pat, complicate_level))
// constructor for WildRegexp take pattern and compilcate_level as input
// which is called by projects only
// complicate_level is COMPLICATE_LEVEL_1 or COMPLICATE_LEVEL_2
{}

WildRegexp::~WildRegexp()
{}

wild_buf::wild_buf(char* str)
// constructor for wild_buf take pattern only as input
// complicate_level is COMPLICATE_LEVEL_0
: ptr(new Regexp(glob_to_regexp(str, COMPLICATE_LEVEL_0))),
  wild(str)
{}

wild_buf::~wild_buf()
{
    delete ptr;
}


int gen_wild_match(char* name, wild_ptr *wild_arr, int& num_wild)
{
    const int size = strlen(name);
    for(int ii = 0; ii < num_wild; ++ii)
        if(wild_arr[ii]->match(name, size) == size)
            return 1;

    return 0;
}


/*
   START-LOG-------------------------------------------

   $Log: genWild.cxx  $
   Revision 1.12 2000/07/10 23:04:39EDT ktrans 
   mainline merge from Visual C++ 6/ISO (extensionless) standard header files
Revision 1.2.1.13  1994/07/13  15:50:27  so
Bug track: 7750
fix bug 7750

Revision 1.2.1.12  1994/05/23  20:59:17  so
Bug track: n/a
fast projHeader::fn_to_ln

Revision 1.2.1.10  1993/12/07  16:43:51  so
Bug track: 5448
fix bug 5448
exclude project

Revision 1.2.1.9  1993/10/12  20:41:52  so
Bug track: 4916
fix bg 4916

Revision 1.2.1.8  1993/07/23  13:58:36  harry
HP/Solaris Port

Revision 1.2.1.7  1993/05/07  13:37:11  so
skip backslash.

Revision 1.2.1.6  1993/05/01  20:41:24  glenn
Add class WildRegexp and supporting functions.
Protect |, +, ^, and $ in glob_to_regexp.

Revision 1.2.1.5  1993/04/30  19:19:31  glenn
Move conversion of shell-glob pattern to regexp into
separate function, glob_to_regexp.

   END-LOG---------------------------------------------
*/
