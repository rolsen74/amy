
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

int iupdrvImageGetInfo( struct libData *data, void *handle, int *w, int *h, int *bpp )
{
	return( 0 );
}
