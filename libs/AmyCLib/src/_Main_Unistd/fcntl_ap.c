
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
// I needed fcntl to call a va_list version.. 
// so I renamed it to fcntl_ap

int AMY_FUNC _generic_unistd_fcntl_ap( struct AmyCLibIFace *Self, int fildes, int cmd, va_list ap )
{
struct libData *data;
int retval;

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_unistd_fcntl_ap ::IMPLEMENT::ME::\n" ); );

	DOFUNCTIONLOG( LOG_FUNC_fcntl_ap );

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	// --

	retval = -1;	// error
	data->buf_PublicData->ra_ErrNo = ENOMEM;

	// --

	return(	retval );
}
