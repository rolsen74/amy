
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2025-2026 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

void FreeEvent( struct AmyInputIFace *Self UNUSED, PTR ctx UNUSED, InputEvent *event UNUSED )
{
	IExec->DebugPrintF( "FreeEvent\n" );
}

// --
