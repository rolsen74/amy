
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2011-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

U32 _manager_Release( struct LibraryManagerInterface *Self )
{
	Self->Data.RefCount--;

	return( Self->Data.RefCount );
}

// --
