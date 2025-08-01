
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2025 Rene W. Olsen <renewolsen@gmail.com>
*/

// --

#include "All.h"

// --

STR GetErrorString( struct AmyInputIFace *Self UNUSED, U32 error_code UNUSED )
{
	IExec->DebugPrintF( "GetErrorString\n" );
	return( NULL );
}

// --
