
/*
** SPDX-License-Identifier: MIT
** Copyright (C) 1994-2025 Tecgraf/PUC-Rio.
** Mini-port by Rene W. Olsen (2025)
** Target OS: AmigaOS
*/

// --

#include "inc/All.h"

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
