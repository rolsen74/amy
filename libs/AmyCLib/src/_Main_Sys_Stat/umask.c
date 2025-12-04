
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

mode_t AMY_FUNC _generic_sys_stat_umask( struct AmyCLibIFace *Self, mode_t cmask )
{
struct libData *data;
mode_t retval;

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_sys_stat_umask ::IMPLEMENT::ME::\n" ); );

	DOFUNCTIONLOG( LOG_FUNC__exit );

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	// --

	retval = -1;	// error
	data->buf_PublicData->ra_ErrNo = ENOMEM;

	// --

	return(	retval );
}
