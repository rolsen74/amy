
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

int AMYFUNC _generic_unistd_chown( struct AmyCLibIFace *Self, const char *aa, uid_t bb, gid_t cc )
{
struct libData *data;
int retval;

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_unistd_chown ::IMPLEMENT::ME::\n" ); );

	DOFUNCTIONLOG( LOG_FUNC_chown );

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	// --

	retval = -1;	// error
	data->buf_PublicData->ra_ErrNo = ENOMEM;

	// --

	return(	retval );
}
