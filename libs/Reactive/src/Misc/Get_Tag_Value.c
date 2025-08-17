
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2011-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

U32 AMYFUNC _main_Misc_GetTagValue( struct ReactivePrivIFace *Self UNUSED, struct TagItem *tag, U32 id, U32 defval )
{
U32 retval;

	IExec->DebugPrintF( "RA_Misc_GetTagValue\n" );

	retval = defval;

	while(( tag ) && ( tag->ti_Tag != TAG_END ))
	{
		if ( tag->ti_Tag == id )
		{
			retval = tag->ti_Data;
			break;
		}

		if ( tag->ti_Tag == TAG_MORE )
		{
			tag = (struct TagItem *) tag->ti_Data;
			continue;
		}

		if ( tag->ti_Tag == TAG_IGNORE )
		{
			tag++;
			continue;
		}

		tag++;
	}

	#if 0
	while(( tag ) && ( tag->ti_Tag != TAG_END ))
	{
		else
		{
			tag++;
		}

		while(( tag ) && ( tag->ti_Tag != TAG_END ))
		{
			if ( tag->ti_Tag == TAG_MORE )
			{
				tag = (struct TagItem *) tag->ti_Data;
				continue;
			}

			if ( tag->ti_Tag == TAG_IGNORE )
			{
				tag++;
				continue;
			}

			break;
		}
	}
	#endif

	return(	retval );
}

// --
