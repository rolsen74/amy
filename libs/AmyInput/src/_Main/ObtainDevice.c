
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

DeviceHandle *ObtainDevice( struct AmyInputIFace *Self UNUSED, PTR ctx UNUSED, DeviceID device_id UNUSED )
{
	IExec->DebugPrintF( "ObtainDevice\n" );
	return( NULL );
}

// --
