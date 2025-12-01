
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include <proto/AmyCLib.h>

// --

int ioctl( int aa, int bb, ... )
{
va_list ap;
int retval;

//	IExec->DebugPrintF( "stub : asprintf\n" );

	va_start( ap, bb );

	retval = IAmyCLib->stropts_ioctl_ap( aa, bb, ap );

	va_end( ap );

	return(	retval );
}

// --
