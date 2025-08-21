
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

char * AMYFUNC _generic_string_strndup( struct AmyCLibPrivIFace *Self, const char *s, size_t max )
{
struct libData *data;
size_t len;
char *str;

	// --

	IExec->DebugPrintF( "_generic_string_strndup\n" );

	DOFUNCTIONLOG( LOG_FUNC_strndup );

	str = NULL;

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	// --

	if ( ! s )
	{
		data->buf_PublicData->ra_ErrNo = EFAULT;
		goto bailout;
	}

	len = Self->string_strnlen( s, max );
	str = Self->stdlib_malloc( len + 1 );

	if ( ! str )
	{
		// malloc sets ErrNo
		goto bailout;
	}

	Self->string_memcpy( str, s, len );
	str[len] = '\0';

bailout:

	return( str );
}

// --
