
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

void AMY_FUNC _generic_stdlib__exit( struct AmyCLibIFace *Self, int status )
{
struct libData *data;

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_stdlib__exit ::IMPLEMENT::ME::\n" ); );

	DOFUNCTIONLOG( LOG_FUNC__exit );

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	// --

	data->buf_PublicData->ra_ErrNo = ENOMEM;

	// --
}
