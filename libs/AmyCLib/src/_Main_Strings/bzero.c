
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
	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_strings_bzero : Mem %p : Len %lu :\n", mem, len ); );

	DOFUNCTIONLOG( LOG_FUNC_bzero );

	#if 0

	Self->string_memset( mem, 0, len );

	#else

	if ( len )
	{
		if ( ! mem )
		{
			// Only an error if len is none zero
			struct libData *data = (PTR)( (U32) Self - Self->Data.NegativeSize );
			data->buf_PublicData->ra_ErrNo = EFAULT;
		}
		else
		{
			IUtility->SetMem( mem, 0, len );
		}
	}

	#endif
}

// --
