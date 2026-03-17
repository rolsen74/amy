
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2025-2026 Rene W. Olsen
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
