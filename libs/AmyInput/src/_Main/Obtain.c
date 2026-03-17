
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2025-2026 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

U32 AMY_FUNC _Main_Obtain( struct AmyInputIFace *Self )
{
	Self->Data.RefCount++;

	return( Self->Data.RefCount );
}

// --
