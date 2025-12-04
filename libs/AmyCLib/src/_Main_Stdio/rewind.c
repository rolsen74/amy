
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

void AMY_FUNC _generic_stdio_rewind( struct AmyCLibIFace *Self, FILE *stream )
{
struct libData *data;

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_stdio_rewind ::IMPLEMENT::ME::\n" ); );

	DOFUNCTIONLOG( LOG_FUNC_rewind );

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	// --

	data->buf_PublicData->ra_ErrNo = ENOMEM;

	// --
}
