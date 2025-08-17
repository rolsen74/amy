
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

U32 AMYFUNC _Main_Release( struct AmyInputIFace *Self )
{
	IExec->DebugPrintF( "AmyInput : _Main_Release\n" );

	Self->Data.RefCount--;

	return( Self->Data.RefCount );
}

// --
