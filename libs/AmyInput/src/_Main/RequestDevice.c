
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2025-2026 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

struct _RequesterResult *RequestDevice( struct AmyInputIFace *Self UNUSED, PTR ctx UNUSED, struct TagItem *tags UNUSED )
{
	IExec->DebugPrintF( "GetError\n" );
	return( NULL );
}

// --
