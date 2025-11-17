
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

ssize_t AMYFUNC _generic_unistd_read( struct AmyCLibPrivIFace *Self, int fildes, void *buf, size_t nbyte )
{
struct libData *data;
int retval;

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_unistd_read ::IMPLEMENT::ME::\n" ); );

	DOFUNCTIONLOG( LOG_FUNC_read );

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	// --

	retval = -1;	// error
	data->buf_PublicData->ra_ErrNo = ENOMEM;

	// --

	return(	retval );
}
