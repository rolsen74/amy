
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

size_t AMY_FUNC _generic_stdio_fwrite( struct AmyCLibIFace *Self, const void *ptr, size_t size, size_t nitems, FILE *stream )
{
struct libData *data;
size_t retval;

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_stdio_fwrite ::IMPLEMENT::ME::\n" ); );

	DOFUNCTIONLOG( LOG_FUNC_fwrite );

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	// --

	retval = -1;	// error
	data->buf_PublicData->ra_ErrNo = ENOMEM;

	// --

	return(	retval );
}
