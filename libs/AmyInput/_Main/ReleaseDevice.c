
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "All.h"

// --

void ReleaseDevice( struct AmyInputIFace *Self UNUSED, PTR ctx UNUSED, DeviceHandle *handle UNUSED )
{
	IExec->DebugPrintF( "ReleaseDevice\n" );
}

// --
