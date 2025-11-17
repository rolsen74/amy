
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

double AMYFUNC _generic_stdlib_atof( struct AmyCLibPrivIFace *Self, const char *str )
{
struct libData *data;
long retval;

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_stdlib_atof ::IMPLEMENT::ME::\n" ); );

	DOFUNCTIONLOG( LOG_FUNC_atof );

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	// --

	retval = -1;	// error
	data->buf_PublicData->ra_ErrNo = ENOMEM;

	// --

	return(	retval );
}
