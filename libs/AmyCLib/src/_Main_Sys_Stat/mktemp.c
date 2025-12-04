
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

char * AMY_FUNC _generic_sys_stat_mktemp( struct AmyCLibIFace *Self, char *template )
{
struct libData *data;
char *retval;

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_sys_stat_mktemp ::IMPLEMENT::ME::\n" ); );

	DOFUNCTIONLOG( LOG_FUNC_mktemp );

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	// --

	retval = NULL;	// error
	data->buf_PublicData->ra_ErrNo = ENOMEM;

	// --

	return(	retval );
}
