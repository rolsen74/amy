
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2025 Rene W. Olsen <renewolsen@gmail.com>
*/

// --

#include "All.h"

// --

U32 ReadDevice( struct AmyInputIFace *Self UNUSED, PTR ctx UNUSED, DeviceHandle *handle UNUSED, PTR *data UNUSED )
{
	IExec->DebugPrintF( "ReadDevice\n" );
	return( 0 );
}

// --
