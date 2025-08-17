
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

static S32 myInit_Locale( struct AmyCLibIFace *Self UNUSED, struct libData *data )
{
int error;

	error = TRUE;

	data->LocaleDefault = ILocale->OpenLocale( NULL );

	if ( ! data->LocaleDefault )
	{
		IExec->DebugPrintF( "myInit_Locale : Error Opening Default Locale\n" );
		goto bailout;
	}

	error = FALSE;

bailout:

	return( error );
}
