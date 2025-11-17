
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include <proto/AmyCLib.h>

// --

int fcntl( int fildes, int cmd, ... )
{
va_list ap;
int retval;

//	IExec->DebugPrintF( "stub : asprintf\n" );

	va_start( ap, cmd );

	retval = IAmyCLib->unistd_fcntl_ap( fildes, cmd, ap );

	va_end( ap );

	return(	retval );
}

// --
