
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

void AMYFUNC _generic_strings_bzero( struct AmyCLibPrivIFace *Self UNUSED, void *mem, size_t len )
{
	IExec->DebugPrintF( "_generic_strings_bzero\n" );

	#if 0

	Self->string_memset( mem, 0, len );

	#else

	IUtility->SetMem( mem, 0, len );

	#endif
}

// --
