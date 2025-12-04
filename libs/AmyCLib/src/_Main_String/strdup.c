
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

char * AMY_FUNC _generic_string_strdup( struct AmyCLibIFace *Self, const char *s )
{
struct libData *data;
size_t len;
char *str;

	// --

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_string_strdup\n" ); );

	DOFUNCTIONLOG( LOG_FUNC_strdup );

	str = NULL;

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	// --

	if ( ! s )
	{
		data = (PTR)( (U32) Self - Self->Data.NegativeSize );
		data->buf_PublicData->ra_ErrNo = EFAULT;
		goto bailout;
	}

	len = Self->string_strlen( s );
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
