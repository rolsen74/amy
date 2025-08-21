
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

static void myFree_Locale( struct AmyCLibPrivIFace *Self UNUSED, struct libData *data )
{
int cnt;

	// -- Free Locale

	for( cnt=0 ; cnt<NUM_LOCALES ; cnt++ )
	{
		if ( cnt == LC_ALL )
		{
			continue;
		}

		if ( data->LocaleTable[ cnt ] )
		{
			if ( data->LocaleTable[ cnt ] != data->LocaleTable[LC_ALL] )
			{
				ILocale->CloseLocale( data->LocaleTable[ cnt ] );
			}

			data->LocaleTable[ cnt ] = NULL;
		}
	}

	if ( data->LocaleTable[ LC_ALL ] )
	{
		ILocale->CloseLocale( data->LocaleTable[ LC_ALL ] );
		data->LocaleTable[ LC_ALL ] = NULL;
	}

	if ( data->LocaleDefault )
	{
		ILocale->CloseLocale( data->LocaleDefault );
	}
}

// --
