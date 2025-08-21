
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

static void myFree_PublicData( struct AmyCLibPrivIFace *Self UNUSED, struct libData *data UNUSED )
{
	// ENTER( 8 );

	// // Close FD's and free mem
	// Self->Priv_FDExpunge();

	// LEAVE( 8 );
}

// --
