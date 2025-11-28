
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2011-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

struct TagItem * AMYFUNC _main_Misc_NextTag( struct ReactivePrivIFace *Self UNUSED, struct TagItem *tag )
{
//	IExec->DebugPrintF( "_main_Misc_NextTag\n" );

	while( tag )
	{
		if ( tag->ti_Tag == TAG_END )
		{
			break;
		}

		if ( tag->ti_Tag == TAG_MORE )
		{
			tag = (PTR) tag->ti_Data;
			break;
		}

		tag++;

		if ( tag->ti_Tag != TAG_IGNORE )
		{
			break;
		}
	}

	#if 0
	while(( tag ) && ( tag->ti_Tag != TAG_END ))
	{
		if ( tag->ti_Tag == TAG_MORE )
		{
			tag = (struct TagItem *) tag->ti_Data;
			break;
		}

		if ( tag->ti_Tag == TAG_IGNORE )
		{
			tag++;
			continue;
		}

		tag++;
		break;
	}
	#endif

	return(	tag );
}
