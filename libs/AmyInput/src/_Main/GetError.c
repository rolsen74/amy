
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

U32 GetError( struct AmyInputIFace *Self UNUSED, PTR ctx UNUSED )
{
	IExec->DebugPrintF( "GetError\n" );
	return( 0 );
}

// --
