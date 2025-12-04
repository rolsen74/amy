
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

struct group * AMY_FUNC _generic_grp_getgrgid( struct AmyCLibIFace *Self, gid_t aa )
{
struct libData *data;
struct group *retval;

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_grp_getgrgid ::IMPLEMENT::ME::\n" ); );

	DOFUNCTIONLOG( LOG_FUNC_getgrgid );

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	// --

	retval = NULL;	// error
	data->buf_PublicData->ra_ErrNo = ENOMEM;

	// --

	return(	retval );
}
