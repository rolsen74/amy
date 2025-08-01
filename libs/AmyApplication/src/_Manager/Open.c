
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "All.h"

// --

PTR _manager_Open( struct LibraryManagerInterface *Self, U32 version UNUSED )
{
struct libBase *libBase;
struct libBase *retval;

	libBase = (PTR) Self->Data.LibBase;

	/* Add up the open count */
	libBase->lib_Base.lib_OpenCnt++;
	libBase->lib_Base.lib_Flags &= ~LIBF_DELEXP;

	retval = libBase;

	return( retval );
}

// --
