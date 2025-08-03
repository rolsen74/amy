
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

U32 _main_Release( struct AmyCLibIFace *Self )
{
	IExec->DebugPrintF( "_main_Release\n" );

	Self->Data.RefCount--;

	if (( ! Self->Data.RefCount ) && ( Self->Data.Flags & IFLF_CLONED ))
	{
		_main_Expunge( Self );
	}

	return( Self->Data.RefCount );
}

// --
