
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

char * AMYFUNC _generic_unistd_getcwd( struct AmyCLibIFace *Self, char *buf, size_t size )
{
struct libData *data;
char *retval;

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_unistd_getcwd ::IMPLEMENT::ME::\n" ); );

	DOFUNCTIONLOG( LOG_FUNC_getcwd );

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	// --

	retval = NULL;	// error
	data->buf_PublicData->ra_ErrNo = ENOMEM;

	// --

	return(	retval );
}
