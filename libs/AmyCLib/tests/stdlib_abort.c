
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025-2026 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include <stdlib.h>
#include <signal.h>

void aborthandler( int aa )
{
	exit( 0 );
}

int main( int argc, char **argv )
{
	signal( SIGABRT, aborthandler );
	
	abort();

	return( 10 );
}

