
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

struct group * AMY_FUNC _generic_grp_getgrnam( struct AmyCLibIFace *Self, const char *aa )
{
struct libData *data;
struct group *retval;

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_grp_getgrnam ::IMPLEMENT::ME::\n" ); );

	DOFUNCTIONLOG( LOG_FUNC_getgrnam );

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	// --

	retval = NULL;	// error
	data->buf_PublicData->ra_ErrNo = ENOMEM;

	// --

	return(	retval );
}
