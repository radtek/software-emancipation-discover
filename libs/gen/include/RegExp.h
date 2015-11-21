#ifndef _RegExp_h
#define _RegExp_h

/*
 * Copyright (c) 1987, 1988, 1989, 1990, 1991 Stanford University
 * Copyright (c) 1991 Silicon Graphics, Inc.
 *
 * Permission to use, copy, modify, distribute, and sell this software and 
 * its documentation for any purpose is hereby granted without fee, provided
 * that (i) the above copyright notices and this permission notice appear in
 * all copies of the software and related documentation, and (ii) the names of
 * Stanford and Silicon Graphics may not be used in any advertising or
 * publicity relating to the software without the specific, prior written
 * permission of Stanford and Silicon Graphics.
 * 
 * THE SOFTWARE IS PROVIDED "AS-IS" AND WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY 
 * WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.  
 *
 * IN NO EVENT SHALL STANFORD OR SILICON GRAPHICS BE LIABLE FOR
 * ANY SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND,
 * OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
 * WHETHER OR NOT ADVISED OF THE POSSIBILITY OF DAMAGE, AND ON ANY THEORY OF 
 * LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE 
 * OF THIS SOFTWARE.
 */

/*
 * Regexp - regular expression searching
 */

/*
 * These definitions are from Henry Spencers public-domain regular
 * expression matching routines.
 *
 * Definitions etc. for regexp(3) routines.
 *
 * Caveat:  this is V8 regexp(3) [actually, a reimplementation thereof],
 * not the System V one.
 */

#ifndef NSUBEXP
/* NOTE: NSUBEXP*2 + offset(15) < 128 (sizeof(char)) */
#define NSUBEXP	50
#endif

struct regexp {
    char *startp[NSUBEXP];
    char *endp[NSUBEXP];
    char *textStart;
    char regstart;		/* Internal use only. */
    char reganch;		/* Internal use only. */
    char *regmust;		/* Internal use only. */
    int regmlen;		/* Internal use only. */
    char program[1];		/* Unwarranted chumminess with compiler. */
};

/*
 * The first byte of the regexp internal "program" is actually this magic
 * number; the start node begins in the second byte.
 */
#define	REGEXP_MAGIC	0234

class Regexp
{
  public:
    Regexp(const char*);
    Regexp(const char*, int length);
    ~Regexp();

    int Search(const char* text, int length, int index, int range);
    int Match(const char* text, int length, int index);
    /* The following function is equivalent to Match(), except that
       it assumes the pattern string has already been compiled: */
    int MatchPrebuilt(const char* text, int length, int index);
    /* Use this to precompile the pattern: */
    int Compile();
    int BeginningOfMatch(int subexp = 0);
    int EndOfMatch(int subexp = 0);
    int NumOfMatched();

  private:
    char* pattern;
    regexp* c_pattern;
};

#endif // _RegExp_h
