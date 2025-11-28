
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2014-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "All.h"

// --

static U32 App_RAM_Delete(
		struct ReactiveIFace *Self,
		struct RA_Class *cl,
		struct RA_Object *obj,
		struct RAP_Delete *msg,
UNUSED	struct AppClassData *cls,
		InstanceData *data )
{
U32 retval;

//	IExec->DebugPrintF( "App_Delete\n" );

	/* Free */

	// data->Dying = TRUE;

	// if ( data->AppWindowProcess )
	// {
	// 	SENDCMD( APPCMD_Stop, NULL, NULL );
	// }

	if ( data->Args )
	{
		Self->RA_Arguments_Free( data->Args );
		data->Args = NULL;
	}

	// Freeing Tracking List must be before Memory List

	// if ( data->TrackingList )
	// {
	// 	RADelete( data->TrackingList );
	// 	data->TrackingList = NULL;
	// }

	// while(( mn = (APTR) RARemHead( & data->WindowList )))
	// {
	// 	RADelete( mn->Object );
	// 	free( mn );
	// }

	// if ( data->Process )
	// {
	// 	StopGUIProcess( data );
	// 	data->Process = NULL;
	// }

	// if (( data->UserCmdPort ) && ( data->UserCmdPortDel == TRUE ))
	// {
	// 	myDelPort( Self, data->UserCmdPort );
	// 	data->UserCmdPort = NULL;
	// }

	if ( data->AppBase )
	{
		free( data->AppBase );
		data->AppBase = NULL;
	}

	// Done

	retval = RASuper( cl, obj, msg );

	return(	retval );
}

