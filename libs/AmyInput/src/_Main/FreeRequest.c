
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

void FreeRequest( struct AmyInputIFace *Self UNUSED, PTR ctx UNUSED, struct _RequesterResult *result UNUSED )
{
	IExec->DebugPrintF( "FreeRequest\n" );
}

// --
