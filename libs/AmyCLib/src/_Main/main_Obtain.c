
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

U32 _main_Obtain( struct AmyCLibIFace *Self )
{
	IExec->DebugPrintF( "_main_Obtain\n" );

	Self->Data.RefCount++;

	return( Self->Data.RefCount );
}

// --
