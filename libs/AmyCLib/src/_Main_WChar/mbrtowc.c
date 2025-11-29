
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

size_t AMYFUNC _generic_wchar_mbrtowc( struct AmyCLibIFace *Self, wchar_t *pwc, const char *s, size_t n, mbstate_t *ps )
{
struct libData *data;
size_t retval;

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_wchar_mbrtowc ::IMPLEMENT::ME::\n" ); );

	DOFUNCTIONLOG( LOG_FUNC_mbrtowc );

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	// --

	retval = -1;	// error
	data->buf_PublicData->ra_ErrNo = ENOMEM;

	// --

	return(	retval );
}
