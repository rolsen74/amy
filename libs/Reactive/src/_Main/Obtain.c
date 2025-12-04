
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2011-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

U32 AMY_FUNC _Main_Obtain( struct ReactivePrivIFace *Self )
{
//	IExec->DebugPrintF( "Reactive : _Main_Obtain\n" );

	Self->Data.RefCount++;

	return( Self->Data.RefCount );
}

// --
