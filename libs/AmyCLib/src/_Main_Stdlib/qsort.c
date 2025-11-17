
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

void AMYFUNC _generic_stdlib_qsort( struct AmyCLibPrivIFace *Self, void *base, size_t nel, size_t width, int (*compar)(const void *, const void *))
{
struct libData *data;

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_stdlib_qsort ::IMPLEMENT::ME::\n" ); );

	DOFUNCTIONLOG( LOG_FUNC_qsort );

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	// --

	data->buf_PublicData->ra_ErrNo = ENOMEM;

	// --
}
