
/*
** SPDX-License-Identifier: MIT
** Copyright (C) 1994-2025 Tecgraf/PUC-Rio.
** Mini-port by Rene W. Olsen (2025)
** Target OS: AmigaOS
*/

// --

#include "inc/All.h"

// --

void AMYFUNC _Main_IupSetGlobal( struct AmyIUPIFace *Self, const char *name, const char *value )
{
struct libData *data;

	IExec->DebugPrintF( "::_Main_IupSetGlobal::\n" );

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	amy_IupSetGlobal( data, name, value );
}

// --
