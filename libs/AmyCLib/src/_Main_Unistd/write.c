
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

ssize_t AMY_FUNC _generic_unistd_write( struct AmyCLibIFace *Self, int aa, const void *bb, size_t cc )
{
struct libData *data;
ssize_t retval;

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_unistd_write ::IMPLEMENT::ME::\n" ); );

	DOFUNCTIONLOG( LOG_FUNC_write );

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	// --

	retval = -1;	// error
	data->buf_PublicData->ra_ErrNo = ENOMEM;

	// --

	return(	retval );
}
