
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

void _main_strings_bzero( struct AmyCLibIFace *Self, void *mem, size_t len )
{
	IExec->DebugPrintF( "_main_strings_bzero\n" );

	Self->string_memset( mem, 0, len );
}

// --
