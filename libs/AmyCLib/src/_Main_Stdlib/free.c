
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

void AMYFUNC _generic_stdlib_free( struct AmyCLibPrivIFace *Self, void *mem )
{
	IExec->DebugPrintF( "_generic_stdlib_free : Mem %p\n", mem );

	DOFUNCTIONLOG( LOG_FUNC_free );

	// Memory is set to to 0xAC
	Self->Priv_Mem_Free( mem );
}

// --
