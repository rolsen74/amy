
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "All.h"

// --

U32 EnumDevices( struct AmyInputIFace *Self UNUSED, PTR ctx UNUSED, PTR enumfunc UNUSED, PTR user_data UNUSED )
{
	IExec->DebugPrintF( "EnumDevices\n" );
	return( 0 );
}

// --
