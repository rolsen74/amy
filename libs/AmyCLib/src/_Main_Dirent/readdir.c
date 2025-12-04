
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

struct dirent * AMY_FUNC _generic_dirent_readdir( struct AmyCLibIFace *Self, DIR *dirp )
{
struct libData *data;
struct dirent *retval;

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_dirent_readdir ::IMPLEMENT::ME::\n" ); );

	DOFUNCTIONLOG( LOG_FUNC_readdir );

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	// --

	retval = NULL;	// error
	data->buf_PublicData->ra_ErrNo = ENOMEM;

	// --

	return(	retval );
}
