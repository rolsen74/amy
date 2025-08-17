
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2014-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "All.h"

// --

static STR Get_IOErrString( U32 ioerr )
{
STR str;

	switch( ioerr )
	{
		case ERROR_OBJECT_NOT_FOUND:	str = "Object not found";	break;
		default:						str = "Unknown Error";		break;
	}

	return( str );
}
