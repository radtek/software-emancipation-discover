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
#ifndef _ASET_GRAPH_H
#define _ASET_GRAPH_H

// ASET_GRAPH.H
//------------------------------------------
// synopsis:   aset_graph.h class.
//
// description:   "aset_graph" class based on EDGE's "graph" class;
//                it is created to use EDGE layout algorithms
//                while having aset nodes, egdes, and graphics.
// 
//------------------------------------------
// Restrictions:
// ...
//------------------------------------------
// include files

#include "graph.h"

class viewNode;
class objArr;

class aset_graph : public graph
{
public:

    int up_tree;          // flag to specifiy up-tree graph
                          // for call tree diagram
// constructors and destructors

    aset_graph(viewNode *, int x_space = NODE_SPACE, 
         int y_space = NODE_SPACE, 
         objArr *root_arr = NULL, int uu = 0);
};
/*
   START-LOG-------------------------------------------

   $Log: aset_graph.h  $
   Revision 1.1 1993/07/28 19:45:42EDT builder 
   made from unix file
 * Revision 1.2.1.2  1992/10/09  19:03:13  smit
 * *** empty log message ***
 *

   END-LOG---------------------------------------------

*/

#endif
