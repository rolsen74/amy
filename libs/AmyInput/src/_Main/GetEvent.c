
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

InputEvent *GetEvent( struct AmyInputIFace *Self UNUSED, PTR ctx UNUSED )
{
	IExec->DebugPrintF( "GetEvent\n" );
	return( NULL );
}

// --
