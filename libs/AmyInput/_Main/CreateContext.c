
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2025 Rene W. Olsen <renewolsen@gmail.com>
*/

// --

#include "All.h"

// --

PTR CreateContext( struct AmyInputIFace *Self UNUSED, U32 apiver UNUSED, struct TagItem *tags UNUSED )
{
	IExec->DebugPrintF( "CreateContext\n" );
	return( NULL );
}

// --
