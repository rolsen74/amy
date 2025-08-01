
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2025 Rene W. Olsen <renewolsen@gmail.com>
*/

// --

#include "All.h"

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
