
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include <proto/AmyCLib.h>

// --
#if 0

int sprintf( char *buf, const char *fmt, ... )
{
va_list ap;
int retval;

	IExec->DebugPrintF( "stub : snprintf\n" );

	va_start( ap, fmt );

	retval = IAmyCLib->stdio_vsprintf( buf, fmt, ap );

	va_end( ap );

	return(	retval );
}

#endif
// --
