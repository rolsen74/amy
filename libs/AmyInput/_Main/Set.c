
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2025 Rene W. Olsen <renewolsen@gmail.com>
*/

// --

#include "All.h"

// --

U32 Set( struct AmyInputIFace *Self UNUSED, PTR ctx UNUSED, struct TagItem *tags UNUSED )
{
	IExec->DebugPrintF( "Set\n" );
	return( 0 );
}

// --
