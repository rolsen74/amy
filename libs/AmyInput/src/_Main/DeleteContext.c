
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

void DeleteContext( struct AmyInputIFace *Self UNUSED, PTR ctx UNUSED )
{
	IExec->DebugPrintF( "DeleteContext\n" );
}

// --
