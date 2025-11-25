
/*
** SPDX-License-Identifier: MIT
** Copyright (C) 1994-2025 Tecgraf/PUC-Rio.
** Mini-port by Rene W. Olsen (2025)
** Target OS: AmigaOS
*/

// --

#include "inc/All.h"

// --
// AmigaOS4 specific code

IUP_SDK_API int iupdrvSetFontAttrib( struct libData *data, Ihandle *ih, const char *value )
{
	return( 0 );
}
