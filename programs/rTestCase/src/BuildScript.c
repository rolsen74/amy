
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2018-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "Main.h"

// --

S32 BuildScript( STR Script, STR FileName )
{
S32 retval;
STR str;
STR buf;
U32 max;
U8 chr;

	retval = FALSE;

	if ( ! Script )
	{
		goto bailout;
	}

	max = 10 * 1024 - 1;
	buf = CompileScript;

	while(( max-- ) && ( *Script ))
	{
		chr = *Script++;

		if ( chr == '[' )
		{
			if ( ! strnicmp( Script, "FILENAME]", 9 ))
			{
				str = (PTR) FileName;

				while(( max ) && ( *str ))
				{
					max--;
					chr = *str++;
					*buf++ = chr;

					if ( chr == 0 )
					{
						break;
					}
				}
			}

			// Skip [xx] Command name
			while( TRUE )
			{
				chr = *Script++;

				if ( chr == 0 )
				{
					break;
				}

				if ( chr == ']' )
				{
					break;
				}
			}
		}
		else
		{
			*buf++ = chr;
		}
	}

	if ( ! max )
	{
		goto bailout;
	}

	*buf = 0;

	retval = TRUE;

bailout:

	return( retval );
}

// --
