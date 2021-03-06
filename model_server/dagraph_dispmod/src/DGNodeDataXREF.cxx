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
//
// DGNodeDataXREF.C
// ----------------
//

#include <symbolPtr.h>

#include <DGNodeData.h>
#include <DGNodeDataXREF.h>

//
// PUBLIC:
//

DGNodeDataXREF::DGNodeDataXREF(symbolPtr & sym_in)
: DGNodeData()
{
    elem = sym_in;
}

DGNodeDataXREF::~DGNodeDataXREF()
{
}

//
// returns: cloned object; replica
//
DGNodeData *
DGNodeDataXREF::clone()
{
    DGNodeData * ret_val = (DGNodeData *)0;

    ret_val = new DGNodeDataXREF(symbol());

    return ret_val;
}

//
// returns:
//
int
DGNodeDataXREF::compare(DGNodeData & other)
{
    int ret_val = 0;

    if (other.hierarchy() == XREFsymbol) {
	ret_val = elem.sym_compare(((DGNodeDataXREF &)other).elem);
	if (ret_val == -2)
	    ret_val = -1;
	else if (ret_val == 2)
	    ret_val = 1;
	else
	    ret_val = 0;
    }

    return ret_val;
}

int
DGNodeDataXREF::hierarchy()
{
    return XREFsymbol;
}
