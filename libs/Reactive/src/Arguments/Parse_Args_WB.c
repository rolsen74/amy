
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2011-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

static PTR Handle_WBArgs( struct ReactivePrivIFace *Self, struct RAArguments *args, struct WBStartup *msg, U32 *error )
{
struct WBArg *arg;
U32 errcode;
PTR retval;

//	IExec->DebugPrintF( "RA_Arguments_ParseList : Handle_WBArgs\n" );

	errcode = RAV_General_Failure;

	retval	= NULL;

	arg		= msg->sm_ArgList;

	if ( ! arg )
	{
		goto bailout;
	}

	retval = Handle_WBFile( Self, args, arg->wa_Name, error );

	errcode = RAV_General_Success;

bailout:

	if (( error ) && ( *error == RAV_General_Success ))
	{
		*error = errcode;
	}

	return(	retval );
}

// --
