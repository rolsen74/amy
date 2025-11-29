
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

struct lconv * AMYFUNC _generic_locale_localeconv( struct AmyCLibIFace *Self )
{
struct libData *data;
struct lconv *retval;

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_locale_localeconv ::IMPLEMENT::ME::\n" ); );

	DOFUNCTIONLOG( LOG_FUNC_localeconv );

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	// --

	retval = NULL;	// error
	data->buf_PublicData->ra_ErrNo = ENOMEM;

	// --

	return(	retval );
}
