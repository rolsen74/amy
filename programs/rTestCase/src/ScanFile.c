
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2018-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "Main.h"

// --

void ScanFile( STR path )
{
	// Todo: change to path dir and load script from there
	
	DefaultScript = RALoadFile( "Compile.Script", NULL );

	TestFile( (PTR) IDOS->FilePart( path ), 1 );

}

// --
