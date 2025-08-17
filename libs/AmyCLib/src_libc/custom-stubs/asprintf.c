
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include <proto/AmyCLib.h>

// --

int asprintf( char **buf, const char *fmt, ... )
{
va_list ap;
int retval;

//	IExec->DebugPrintF( "stub : asprintf\n" );

	va_start( ap, fmt );

	retval = IAmyCLib->stdio_vasprintf( buf, fmt, ap );

	va_end( ap );

	return(	retval );
}

// --
