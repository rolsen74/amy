
/*
** SPDX-License-Identifier: MIT
** Copyright (C) 1994-2025 Tecgraf/PUC-Rio.
** Mini-port by Rene W. Olsen (2025)
** Target OS: AmigaOS
*/

// --

#include "inc/All.h"

// --

PTR _manager_Expunge( struct LibraryManagerInterface *Self )
{
struct libBase *libBase;
PTR result;

	libBase = (PTR) Self->Data.LibBase;

	if ( ! libBase->lib_Base.lib_OpenCnt )
	{
		result = libBase->lib_SegList;

		/* Undo what the init code did */

		ROMFree( libBase );

		/* Remove Library from Public */

		IExec->Remove( (PTR) libBase );
		IExec->DeleteLibrary( (PTR) libBase );
	}
	else
	{
		libBase->lib_Base.lib_Flags |= LIBF_DELEXP;
		result = NULL;
	}

	return( result );
}

// --
