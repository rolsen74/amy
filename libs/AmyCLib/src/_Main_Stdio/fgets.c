
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

char * AMYFUNC _generic_stdio_fgets( struct AmyCLibPrivIFace *Self, char *s, int n, struct PrivFile *stream )
{
struct libData *data;
char *retval;

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_stdio_fgets ::IMPLEMENT::ME::\n" ); );

	DOFUNCTIONLOG( LOG_FUNC_fgets );

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	// --

	retval = NULL;	// error
	data->buf_PublicData->ra_ErrNo = ENOMEM;

	// --

	return(	retval );
}
