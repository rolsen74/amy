
/*
** SPDX-License-Identifier: MIT
** Copyright (C) 1994-2025 Tecgraf/PUC-Rio.
** Mini-port by Rene W. Olsen (2025)
** Target OS: AmigaOS
*/

// --

#include "inc/All.h"

// --

U32 AMY_FUNC _Main_Release( struct AmyIUPIFace *Self )
{
	IExec->DebugPrintF( ":: AmyIUP :: _Main_Release ::\n" );

	Self->Data.RefCount--;

	if (( ! Self->Data.RefCount ) && ( Self->Data.Flags & IFLF_CLONED ))
	{
		_Main_Expunge( Self );
	}

	return( Self->Data.RefCount );
}

// --
