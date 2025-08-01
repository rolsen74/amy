
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

U32 Query( struct AmyInputIFace *Self UNUSED, PTR ctx UNUSED, DeviceID device_id UNUSED, U32 qParameter UNUSED, U32 qArg UNUSED, PTR result UNUSED, U32 result_length UNUSED )
{
	IExec->DebugPrintF( "Query\n" );
	return( 0 );
}

// --
