
/*
** SPDX-License-Identifier: MIT
** Copyright (C) 1994-2025 Tecgraf/PUC-Rio.
** Mini-port by Rene W. Olsen (2025)
** Target OS: AmigaOS
*/

// --

#include "inc/All.h"

// --

void AMY_FUNC _Main_IupClose( struct AmyIUPIFace *Self )
{
struct libData *data;

	IExec->DebugPrintF( "::_Main_IupClose::\n" );

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	amy_IupClose( data );
}

// --
