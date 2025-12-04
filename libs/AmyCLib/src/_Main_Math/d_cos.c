
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

double AMY_FUNC _generic_math_cos( struct AmyCLibIFace *Self, double x )
{
struct libData *data;
double retval;

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_math_cos ::IMPLEMENT::ME::\n" ); );

	DOFUNCTIONLOG( LOG_FUNC_D_cos );

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	// --

	retval = -1;	// error
	data->buf_PublicData->ra_ErrNo = ENOMEM;

	// --

	return(	retval );
}
