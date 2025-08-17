
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

void AMYFUNC _generic_strings_bzero( struct AmyCLibIFace *Self, void *mem, size_t len )
{
	IExec->DebugPrintF( "_generic_strings_bzero\n" );

	// memset checks EnableMask

	Self->string_memset( mem, 0, len );
}

// --
