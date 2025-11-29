
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

static S32 mySetup_PublicData(
	struct AmyCLibIFace *Self,
	struct libData *data )
{
// struct RACLibStruct *pd;
// FILE *file;
S32 error;

// 	ENTER( 8 );

 	error = TRUE;

// 	pd = Self->_Priv_Mem_Alloc( sizeof( struct RACLibStruct ));

// 	if ( pd == NULL )
// 	{
// 		SHOWMSG( 1, "Error allocating memory" );
// 		goto bailout;
// 	}

// 	data->buf_PublicData = pd;

// 	-- FD 0 - is stdin

// 	if ( Self->fcntl_open( "console:", O_RDONLY ) < 0 )
// 	{
// 		goto bailout;
// 	}

// 	file = data->FileArray.Nodes[0].Node;

// 	if ( Self->stdio_setvbuf( (APTR) file, NULL, BUFFER_MODE_LINE, 2048 ) < 0 )
// 	{
// 		goto bailout;
// 	}

// 	pd->ra_stdin = (APTR) file;

// 	-- FD 1 - is stdout

// 	if ( Self->fcntl_open( "console:", O_WRONLY ) < 0 )
// 	{
// 		goto bailout;
// 	}

// 	file = data->FileArray.Nodes[1].Node;

// 	if ( Self->stdio_setvbuf( (APTR) file, NULL, BUFFER_MODE_LINE, 2048 ) < 0 )
// 	{
// 		goto bailout;
// 	}

// 	pd->ra_stdout = (APTR) file;

// 	-- FD 2 - is stderr

// 	if ( Self->fcntl_open( "console:", O_WRONLY ) < 0 )
// 	{
// 		goto bailout;
// 	}

// 	file = data->FileArray.Nodes[2].Node;

// 	if ( Self->stdio_setvbuf( (APTR) file, NULL, BUFFER_MODE_LINE, 2048 ) < 0 )
// 	{
// 		goto bailout;
// 	}

// 	pd->ra_stderr = (APTR) file;

	error = FALSE;

bailout:

 	return( error );
}
