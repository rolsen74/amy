
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

U32 AMYFUNC _Main_Obtain( struct AmyCLibIFace *Self )
{
	DOFUNCTIONPRINTF( IExec->DebugPrintF( "AmyCLib : _Main_Obtain\n" ); );

	Self->Data.RefCount++;

	return( Self->Data.RefCount );
}

// --
