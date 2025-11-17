
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include <proto/AmyCLib.h>

// --

int fprintf( FILE *stream, const char *fmt, ... )
{
va_list ap;
int retval;

	va_start( ap, fmt );

	retval = IAmyCLib->stdio_vfprintf( stream, fmt, ap );

	va_end( ap );

	return(	retval );
}

// --
