
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2011-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

static struct RA_Plugin *Plugin_FindStruct( U8 *Mem, U32 Size )
{
struct RA_Plugin *retval;
struct RA_Plugin *rap;

	retval = NULL;

	while( Size > 0 )
	{
		rap = (struct RA_Plugin *)Mem;

		if (( rap->RA_Plugin_MatchWord	 == ID_RAPlugin )
		&&	( rap->RA_Plugin_MatchTag	 == rap ))
		{
			retval = rap;
			break;
		}
		else
		{
			Mem++;
			Size--;
		}
	}

	return(	retval );
}

// --

static struct RA_Plugin * Plugin_SearchSegments( BPTR seglist )
{
struct RA_Plugin *retval;
U32 dosvers;
U32 *aseg;
U32 size;
U8 *data;

	retval	= NULL;

	dosvers	= (( DOSBase->lib_Version << 16 ) + ( DOSBase->lib_Revision ));

	// Check for pre dos 54.40 version
	if ( dosvers < (( 54 << 16 ) + 40 ))
	{
		aseg = BADDR( seglist );

		while( aseg )
		{
			data = (U8 *) &aseg[-1];
			size = aseg[-1];

			if (( retval = Plugin_FindStruct( data, size )))
			{
				break;
			}
			else
			{
				aseg = BADDR( aseg[0] );
			}
		}
	}
	else
	{
		while( seglist )
		{
			aseg = BADDR( seglist );
			data = NULL;
			size = 0;

			IDOS->GetSegListInfoTags( seglist,
				GSLI_SectionData, &data,
				GSLI_SectionSize, &size,
				TAG_END
			);

			if (( retval = Plugin_FindStruct( data, size )))
			{
				break;
			}
			else
			{
				seglist = aseg[0];
			}
		}
	}

	return(	retval );
}

// --

struct RA_PrivClass * AMYFUNC _main_Misc_Plugin_Open( struct ReactivePrivIFace *Self, STR name )
{
struct RA_PrivClass *retval;
struct RA_PrivClass *cl;
struct RA_Plugin *rap;
//struct libBase *libBase;
STR namebuf;
U32 result;
S32 error;
BPTR seg;

//	IExec->DebugPrintF( "RA_Misc_Plugin_Open\n" );

//	libBase = (PTR) Self->Data.LibBase;

	retval	= NULL;
	error	= TRUE;
	seg		= 0;
	rap		= NULL;
	cl		= NULL;

	namebuf = NULL;

	asprintf( & namebuf, "progdir:RA/%s", name );

	if ( ! namebuf )
	{
//		IExec->DebugPrintF( "Error building path name\n" );
		goto bailout;
	}

	seg = IDOS->LoadSeg( namebuf );

	if ( ! seg )
	{
		free( namebuf );
		namebuf = NULL;

		asprintf( & namebuf, "libs:Reactive/%s", name );

		if ( ! namebuf )
		{
//			IExec->DebugPrintF( "Error building path name\n" );
			goto bailout;
		}

		seg = IDOS->LoadSeg( namebuf );
	}

	if ( ! seg )
	{
//		IExec->DebugPrintF( "Unable to load '%s' class\n", name );
		free( namebuf );
		goto bailout;
	}

	rap = Plugin_SearchSegments( seg );

	if ( ! rap )
	{
//		IExec->DebugPrintF( "Plugin segment not found\n" );
		free( namebuf );
		goto bailout;
	}

	rap->RA_Plugin_PathName = namebuf;
	rap->RA_Plugin_LoadSeg = seg;
	seg = 0;

	if ( ! Self->Misc_Valid_Class_Name( rap->RA_Plugin_PubName ))
	{
//		IExec->DebugPrintF( "Class name used\n" );
		goto bailout;
	}

	if ( rap->RA_Plugin_DataSize )
	{
		rap->RA_Plugin_Data = IExec->AllocVecTags( rap->RA_Plugin_DataSize,
			AVT_Clear, 0,
			TAG_END
		);

		if ( ! rap->RA_Plugin_Data )
		{
//			IExec->DebugPrintF( "Error allocating ClassData (Size: %lu)\n", rap->RA_Plugin_DataSize );
			goto bailout;
		}
	}
	else
	{
		rap->RA_Plugin_Data = NULL;
	}

	if ( rap->RA_Plugin_Init )
	{
		result = rap->RA_Plugin_Init( IExec, rap );

		if ( result != RAV_General_Success )
		{
//			IExec->DebugPrintF( "Init of Plugin failed\n" );
			goto bailout;
		}
	}

	// Must use Global IReactive
	cl = Self->Class_CreateTags(
		NULL,
		rap->RA_Plugin_Super,
		rap->RA_Plugin_ObjectDataSize,
		rap->RA_Plugin_Dispatcher,
		TAG_END
	);

	if ( ! cl )
	{
//		IExec->DebugPrintF( "Error creating class\n" );
		goto bailout;
	}

	#if 0
	if ( rap->RA_Plugin_Flags & RAPF_BaseClass )
	{
		cl->RA_Class_Flags |= RA_CLASSF_BaseClass;
	}
	#endif

	cl->RA_Class_Plugin = rap;
	cl->RA_Class_Data = rap->RA_Plugin_Data;

	#if 0
	rap->RA_Plugin_NotifyRequest = IDOS->AllocDosObjectTags( DOS_NOTIFYREQUEST,
		ADO_NotifyName,		namebuf,
		ADO_NotifyMethod,	NRF_SEND_MESSAGE,
		ADO_NotifyUserData,	cl,
		ADO_NotifyPort,		libBase->lib_ClassUpdateMsgPort,
		TAG_END
	);

	// This Feature is optional, we can work without

	if ( rap->RA_Plugin_NotifyRequest )
	{
		IDOS->StartNotify( rap->RA_Plugin_NotifyRequest );
	}
	#endif

	rap = NULL;

	if ( ! Self->Class_Add( cl, cl->RA_Class_Plugin->RA_Plugin_PubName ))
	{
//		IExec->DebugPrintF( "Error adding class to public list\n" );
		goto bailout;
	}

	retval = cl;

	error = FALSE;

bailout:

	if ( error )
	{
		if ( seg )
		{
			IDOS->UnLoadSeg( seg );
		}

		if ( rap )
		{
			Self->Misc_Plugin_Free( rap );
		}

		if ( cl )
		{
			// Class_Delete will call Plugin_Free()
			Self->Class_Delete( cl );
		}
	}

	return(	retval );
}

// --
