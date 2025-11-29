
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

struct passwd * AMYFUNC _generic_pwd_getpwuid( struct AmyCLibIFace *Self, uid_t aa )
{
struct libData *data;
struct passwd *retval;

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_pwd_getpwuid ::IMPLEMENT::ME::\n" ); );

	DOFUNCTIONLOG( LOG_FUNC_getpwuid );

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	// --

	retval = NULL;	// error
	data->buf_PublicData->ra_ErrNo = ENOMEM;

	// --

	return(	retval );
}
