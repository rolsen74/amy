
/*
** SPDX-License-Identifier: BSD-3-Clause
** Modifications (c) 2025 Rene W. Olsen
** Part of Amy C Lib
**
** Note : temp file for now, please implement me
**
*/

// --

#include "src/All.h"

// --

char * AMYFUNC _generic_string_strstr( struct AmyCLibIFace *Self, const char *s1, const char *s2 )
{
struct libData *data;
char *retval;

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_string_strstr ::IMPLEMENT::ME::\n" ); );

	DOFUNCTIONLOG( LOG_FUNC_strstr );

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	// --

	retval = NULL;	// error
	data->buf_PublicData->ra_ErrNo = ENOMEM;

	// --

	return(	retval );
}
