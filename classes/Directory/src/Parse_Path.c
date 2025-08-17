
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2014-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "All.h"

// --

static void Parse_Path(
	struct ReactiveIFace *Self UNUSED,
	struct DirClassData *dcls UNUSED,
	InstanceData *data,
	STR Path )
{
STR File;
U32 len;

	if ( data->String )
	{
		free( data->String );
		data->String = NULL;
	}

	asprintf( & data->String, "%s", Path );

	if ( data->Pattern )
	{
		free( data->Pattern );
		data->Pattern = NULL;
	}

	// -

	File = (PTR) IDOS->FilePart( data->String );

	if (( File ) && ( File[0] ))
	{
		len = ( strlen( File ) * 2 ) + 2;

//		data->Pattern = RAAllocMem( len );
		data->Pattern = calloc( 1, len );

		IDOS->ParsePatternNoCase( File, data->Pattern, len );

		if ( File != data->String )
		{
			File--;

			if ( File[0] == ':' )
			{	
				 File[1] = 0;
			}
			else					
			{
				 File[0] = 0;
			}
		}
	}
	else
	{
		File = NULL;
	}

	if ( File != data->String )
	{
		data->Path = data->String;
	}
	else
	{
		data->Path = (STR) "currdir:";
	}
}

// --
