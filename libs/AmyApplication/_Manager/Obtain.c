
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2025 Rene W. Olsen <renewolsen@gmail.com>
*/

// --

#include "All.h"

// --

U32 _manager_Obtain( struct LibraryManagerInterface *Self )
{
	Self->Data.RefCount++;

	return( Self->Data.RefCount );
}

// --
