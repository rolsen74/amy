
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2011-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

static PTR Handle_WBFile( struct ReactivePrivIFace *Self, struct RAArguments *args, STRPTR Filename, U32 *error )
{
struct DiskObject *dobj;
U32 errorcode;
PTR retval;
U32 pos;

	IExec->DebugPrintF( "RA_Arguments_ParseList : Handle_WBArgs\n" );

	errorcode = RAV_General_Success;

	retval	= NULL;

	// --

	if ( ! IIcon )
	{
		if ( ! IconBase )
		{
			IconBase = IExec->OpenLibrary( "icon.library", 53 );
		}


		if (( IconBase ) && ( ! IIcon ))
		{
			IIcon = (PTR) IExec->GetInterface( IconBase, "main", 1, NULL );
		}

		if ( ! IIcon )
		{
			IExec->DebugPrintF( "RA_Arguments_ParseList : Error opening icon.library v53" );
			goto bailout;
		}
	}
	
	// --

	dobj = IIcon->GetDiskObjectNew( Filename );

	if ( dobj )
	{
		if ( dobj->do_ToolTypes )
		{
			pos = 0;

			while( dobj->do_ToolTypes[pos] )
			{
				pos++;
			}

			retval = Handle_Options( Self, args, pos, dobj->do_ToolTypes, & errorcode, TRUE );
		}
		else
		{
			retval = RAV_General_Success;
		}

		IIcon->FreeDiskObject( dobj );
	}

bailout:

	if ( ! retval )
	{
		*error = errorcode;
	}

	return( retval );
}

// --
