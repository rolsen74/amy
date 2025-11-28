
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

struct passwd * AMYFUNC _generic_pwd_getpwnam( struct AmyCLibPrivIFace *Self, const char *nam )
{
struct libData *data;
struct passwd *retval;

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_pwd_getpwnam ::IMPLEMENT::ME::\n" ); );

	DOFUNCTIONLOG( LOG_FUNC_getpwnam );

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	// --

	retval = NULL;	// error
	data->buf_PublicData->ra_ErrNo = ENOMEM;

	// --

	return(	retval );
}
