
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

U32 AMYFUNC _Main_Obtain( struct AmyInputIFace *Self )
{
	Self->Data.RefCount++;

	return( Self->Data.RefCount );
}

// --
