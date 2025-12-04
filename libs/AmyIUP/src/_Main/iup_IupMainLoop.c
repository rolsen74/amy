
/*
** SPDX-License-Identifier: MIT
** Copyright (C) 1994-2025 Tecgraf/PUC-Rio.
** Mini-port by Rene W. Olsen (2025)
** Target OS: AmigaOS
*/

// --

#include "inc/All.h"

// --

int AMY_FUNC _Main_IupMainLoop( struct AmyIUPIFace *Self )
{
struct libData *data;
int retval;

	IExec->DebugPrintF( "::_Main_IupMainLoop::\n" );

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	retval = amy_IupMainLoop( data );

	return( retval );
}

// --
