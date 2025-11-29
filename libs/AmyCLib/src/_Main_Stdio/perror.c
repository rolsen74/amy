
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

void AMYFUNC _generic_stdio_perror( struct AmyCLibIFace *Self, const char *s )
{
struct libData *data;

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_stdio_perror ::IMPLEMENT::ME::\n" ); );

	DOFUNCTIONLOG( LOG_FUNC_perror );

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	// --

	data->buf_PublicData->ra_ErrNo = ENOMEM;

	// --
}
