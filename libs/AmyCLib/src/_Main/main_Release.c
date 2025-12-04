
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

U32 AMY_FUNC _Main_Release( struct AmyCLibIFace *Self )
{
	DOFUNCTIONPRINTF( IExec->DebugPrintF( "AmyCLib : _Main_Release\n" ); );

	Self->Data.RefCount--;

	if (( ! Self->Data.RefCount ) && ( Self->Data.Flags & IFLF_CLONED ))
	{
		_Main_Expunge( Self );
	}

	return( Self->Data.RefCount );
}

// --
