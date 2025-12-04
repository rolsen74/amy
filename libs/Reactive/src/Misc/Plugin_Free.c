
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2011-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

S32 AMY_FUNC _main_Misc_Plugin_Free( struct ReactivePrivIFace *Self UNUSED, struct RA_Plugin *rap )
{
U32 result;
S32 retval;

//	IExec->DebugPrintF( "RA_Misc_Plugin_Free\n" );

	retval = FALSE;

	if ( ! rap )
	{
		goto bailout;
	}

	if ( rap->RA_Plugin_Exit )
	{
		// Plugin Exit may refuze to exit, and we have to obay that
		
		result = rap->RA_Plugin_Exit( IExec, rap );

		if ( result != RAV_General_Success )
		{
//			IExec->DebugPrintF( "Plugin refused to Exit\n" );
			goto bailout;
		}
	}

	#if 0
	if ( rap->RA_Plugin_NotifyRequest )
	{
		IDOS->EndNotify( rap->RA_Plugin_NotifyRequest );

		IDOS->FreeDosObject( DOS_NOTIFYREQUEST, rap->RA_Plugin_NotifyRequest );
		rap->RA_Plugin_NotifyRequest = NULL;
	}
	#endif

	if ( rap->RA_Plugin_PathName )
	{
		free( rap->RA_Plugin_PathName );
		rap->RA_Plugin_PathName = NULL;
	}

	if (( rap->RA_Plugin_DataSize ) && ( rap->RA_Plugin_Data ))
	{
		IExec->FreeVec( rap->RA_Plugin_Data );
		rap->RA_Plugin_Data = NULL;
	}

	if ( rap->RA_Plugin_LoadSeg )
	{
		IDOS->UnLoadSeg( rap->RA_Plugin_LoadSeg );
		rap->RA_Plugin_LoadSeg = 0;
	}

	retval = TRUE;

bailout:

	return(	retval );
}

// --
