
/*
** SPDX-License-Identifier: MIT
** Copyright (C) 1994-2025 Tecgraf/PUC-Rio.
** Mini-port by Rene W. Olsen (2025)
** Target OS: AmigaOS
*/

// --

#include "inc/All.h"

// --

U32 AMY_FUNC _Main_Obtain( struct AmyIUPIFace *Self )
{
	IExec->DebugPrintF( ":: AmyIUP :: _Main_Obtain ::\n" );

	Self->Data.RefCount++;

	return( Self->Data.RefCount );
}

// --
