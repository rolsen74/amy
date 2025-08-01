
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

U32 SetDeviceParameter( struct AmyInputIFace *Self UNUSED, PTR ctx UNUSED, DeviceHandle *handle UNUSED, U32 dParameter UNUSED, U32 dArg UNUSED )
{
	IExec->DebugPrintF( "SetDeviceParameter\n" );
	return( 0 );
}

// --
