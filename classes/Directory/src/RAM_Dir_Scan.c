
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2014-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "All.h"

// --

static U32 Dir_Scan(
		struct ReactiveIFace *Self,
UNUSED	struct RA_Class *cl,
UNUSED	struct RA_Object *obj,
UNUSED	struct RAP_DIR_Scan *msg,
UNUSED	struct DirClassData *cls,
		InstanceData *data )
{
struct ExamineData *linkedata;
struct ExamineData *dat;
U32 retval;

//	IExec->DebugPrintF( "Dir_Scan\n" );

	retval	= RAV_General_Failure;

	RAMethod( obj, RAM_DIR_Clear );

	data->Context = IDOS->ObtainDirContextTags(
		EX_DoCurrentDir, TRUE,
		EX_MatchString, ( data->UserPattern ) ? data->UserPattern : data->Pattern,
		EX_StringName, data->Path,
		EX_DataFields, data->DataFields,
		TAG_END
	);

	if ( data->Context )
	{
		while(( dat = IDOS->ExamineDir( data->Context )))
		{
			if ( EXD_IS_LINK(dat) )
			{
				PTR oldproc = IDOS->SetProcWindow( (PTR) -1 );

				linkedata = IDOS->ExamineObjectTags(
					EX_StringNameInput, dat->Link,
					TAG_END
				);

				IDOS->SetProcWindow( oldproc );

				if ( linkedata )
				{
					dat->Type		= linkedata->Type | FSOF_LINK;
					dat->FileSize	= linkedata->FileSize;

					IDOS->FreeDosObject( DOS_EXAMINEDATA, linkedata );
				}
			}

			IExec->Remove( (PTR) dat );
			IExec->AddTail( & data->Header, (PTR) dat );
			data->Entries++;
		}

		data->IOErr = IDOS->IoErr();

		if ( ERROR_NO_MORE_ENTRIES == data->IOErr )
		{
			data->Scanned = TRUE;
			retval = RAV_General_Success;
		}
		else
		{
			RAMethod( obj, RAM_DIR_Clear );
		}
	}
	else
	{
		data->IOErr = IDOS->IoErr();
	}

	return(	retval );
}
