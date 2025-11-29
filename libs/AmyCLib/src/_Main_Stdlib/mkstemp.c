
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

int AMYFUNC _generic_stdlib_mkstemp( struct AmyCLibIFace *Self, char *template )
{
struct libData *data;
int retval;

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_stdlib_qsort ::IMPLEMENT::ME::\n" ); );

	DOFUNCTIONLOG( LOG_FUNC_qsort );

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	// --

	retval = -1; // error
	data->buf_PublicData->ra_ErrNo = ENOMEM;

	// --

	return( retval );
}
