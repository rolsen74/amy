
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

uid_t AMYFUNC _generic_unistd_getegid( struct AmyCLibPrivIFace *Self )
{
struct libData *data;
uid_t retval;

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_unistd_getegid ::IMPLEMENT::ME::\n" ); );

	DOFUNCTIONLOG( LOG_FUNC_getegid );

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	// --

	retval = -1;	// error
	data->buf_PublicData->ra_ErrNo = ENOMEM;

	// --

	return(	retval );
}
