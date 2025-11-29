
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

char * AMYFUNC _generic_locale_setlocale( struct AmyCLibIFace *Self, int category, char *locale )
{
struct libData *data;
char * retval;

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_locale_setlocale ::IMPLEMENT::ME::\n" ); );

	DOFUNCTIONLOG( LOG_FUNC_setlocale );

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	// --

	retval = NULL;	// error
	data->buf_PublicData->ra_ErrNo = ENOMEM;

	// --

	return(	retval );
}
