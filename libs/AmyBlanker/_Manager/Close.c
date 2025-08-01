
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "All.h"

// --

PTR _manager_Close( struct LibraryManagerInterface *Self )
{
struct libBase *libBase;
PTR seglist;

	libBase = (PTR) Self->Data.LibBase;

	libBase->lib_Base.lib_OpenCnt--;

	seglist = NULL;

	if ( ! libBase->lib_Base.lib_OpenCnt )
	{
		if ( libBase->lib_Base.lib_Flags & LIBF_DELEXP )
		{
			seglist = _manager_Expunge( Self );
		}
	}

	return( seglist );
}

// --
