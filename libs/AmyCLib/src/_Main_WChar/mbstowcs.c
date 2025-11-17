
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

size_t AMYFUNC _generic_wchar_mbstowcs( struct AmyCLibPrivIFace *Self, wchar_t *pwcs, const char *s, size_t n )
{
struct libData *data;
size_t retval;

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_wchar_mbstowcs ::IMPLEMENT::ME::\n" ); );

	DOFUNCTIONLOG( LOG_FUNC_mbstowcs );

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	// --

	retval = -1;	// error
	data->buf_PublicData->ra_ErrNo = ENOMEM;

	// --

	return(	retval );
}
