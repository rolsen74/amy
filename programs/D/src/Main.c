
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2012-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include <proto/dos.h>
#include <proto/exec.h>
#include <proto/AmyCLib.h>
#include <proto/Reactive.h>

#include <devices/conunit.h>

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>

// It just need a working function to read a key to work
//#define DO_PAGE

static S32		TargetPage	= FALSE;
static STR *	TargetDirs	= NULL;

static struct RAArguments arglist[] =
{
	RAArg( "S,Page",    TargetPage ),
	RAArg( "M,",    	TargetDirs ),
	RAArgEnd()
};

//static const TEXT USED		verstag[]		= VERSTAG;
static struct RA_Object *	RAAppObject		= NULL;
static S32					ConsoleHeight	= 0;
static S32					ConsoleLine		= 0;

/* -- Main -- */

static void myVPrintF( const char *fmt, va_list args )
{
BPTR h;

	ConsoleLine++;

	if ( ConsoleLine >= ConsoleHeight-1 )
	{
		// --

		printf( "Press Any key to Continue" );
		fflush( stdout );

		// --

		h = IDOS->Input();

		IDOS->FFlush(	h );
		IDOS->SetMode(	h, TRUE );
		IDOS->FGetC(	h );
		IDOS->SetMode(	h, FALSE );

		// --
		// Move cursor x=1 and clear rest of the line

		printf( "\r\x9B\x4B" );
		fflush( stdout );

		// --

		ConsoleLine = 1;
	}

	vprintf( fmt, args );
}

static void VARARGS68K myPrintF( const char *fmt, ... )
{
va_list ap;

	va_start( ap, fmt );

	myVPrintF( fmt, ap );

	va_end( ap );
}

static void myGetConsoleSizes( S32 *Width, S32 *Height )
{
char *ptr;
char buf[32];
BPTR con;
S32 x;
S32 y;
S32 w;
S32 h;
S32 c;

	// --

	x = 0;
	y = 0;
	w = INT32_MAX;
	h = INT32_MAX;

	// --

//	  con = IDOS->Open( "console:", MODE_OLDFILE );
	con = IDOS->Output();   //Open( "console:", MODE_OLDFILE );

	if ( con )
	{
		IDOS->SetMode( con, TRUE );

		sprintf( buf, "\x9B\x30\x20\x71" );

		IDOS->Write( con, buf, strlen( buf ));

		ptr = buf;

		while( TRUE )
		{
			c = IDOS->FGetC( con );

			//printf( "c: '%c' %d\n", c, c );

			if ( c < 0 )
			{
				break;
			}

			*ptr++ = c;

			if ( c == 'r' )
			{
				break;
			}
		}

		*ptr = 0;

		IDOS->SetMode( con, FALSE );

//		  IDOS->Close( con );

// printf( "buf: '%s'\n", & buf[1] );

		sscanf( buf, "\x9B%d;%d;%d;%d r", & x, & y, & h, & w );
	}

	// --

	if ( Width )
	{
		*Width = w;
	}

	if ( Height )
	{
		*Height = h;
	}

	// --
}

int main( int argc, char **argv )
{
struct ExamineData *dat;
struct RA_Object *dirObj;
char sizebuf[16];
U64 totalbytes;
U32 totalfiles;
U32 totaldirs;
U32 retval;
STR path;
STR sstr;
STR estr;
U32 err;
U32 id;

	RAAppObject = NULL;

	retval	= RETURN_FAIL;
	dirObj	= NULL;

	signal( SIGINT, SIG_IGN );

	// --

	printf( "argc %d, argv[0] %s\n", argc, argv[0] );

	err = RAV_General_Success;

	RAAppObject = RACreate( NULL, RAC_Application,
		RAA_APP_Argument_Values, argv,
		RAA_APP_Argument_Count, argc,
		RAA_APP_Argument_List, arglist,
		RAA_ErrorCode, & err,
		RAA_APP_Base, "D",
		TAG_END
	);

	if ( ! RAAppObject )
	{
		printf( "Error Creating Object (ErrCode: %u)\n", err );
		goto bailout;
	}

	// -- Find Console Window Char Height

	if ( TargetPage )
	{
		myGetConsoleSizes( NULL, & ConsoleHeight );
	}
	else
	{
		ConsoleHeight = INT32_MAX;
	}

	// --

	if ( TargetDirs )
	{
		path = TargetDirs[0];
	}
	else
	{
		path = "currdir:";
	}
	
	dirObj = RACreate( NULL, RAC_Directory,
		RAA_ErrorCode, & err,
		RAA_DIR_Path, path,
		TAG_END
	);

	if (( ! dirObj ) || ( err != RAV_General_Success ))
	{
		goto bailout;
	}

	retval = RAMethod( dirObj, RAM_DIR_Scan );

	if ( retval != RAV_General_Success )
	{
		char *str = (PTR) RAXGet( dirObj, RAA_DIR_IOErrString );
		
		if ( str )
		{
			printf( "%s\n", str );
		}

		goto bailout;
	}

	RAMethod( dirObj, RAM_DIR_Sort, 0 );

	id			= 0;
	totalfiles	= 0;
	totaldirs	= 0;
	totalbytes	= 0;

	myPrintF( "\n" );

	while( RAMethod( dirObj, RAM_DIR_GetEntry, & id, & dat ) == RAV_General_Success )
	{
		if ( IDOS->CheckSignal( SIGBREAKF_CTRL_C ))
		{
			printf( "** User break\n" );
			goto bailout;
		}

		if ( EXD_IS_LINK( dat ))
		{
			sstr = "\x1b[4m";
			estr = "\x1b[24m";
		}
		else
		{
			sstr = "";
			estr = "";
		}
		
		if ( EXD_IS_FILE( dat ))
		{
			totalfiles++;
			totalbytes += dat->FileSize;

			snprintf( sizebuf, 16, "%10lld", dat->FileSize );
		}
		else
		{
			totaldirs++;

			snprintf( sizebuf, 16, "       Dir" );
		}

		myPrintF( "%s %s%s%s\n", sizebuf, sstr, dat->Name, estr );
	}

	myPrintF( "\n" );
	myPrintF( "   %lu File%s, %lu Directory%s, %llu Byte%s\n",
		totalfiles,
		( totalfiles == 1 ) ? "" : "s",
		totaldirs,
		( totaldirs  == 1 ) ? "" : "s",
		totalbytes,
		( totalbytes == 1 ) ? "" : "s"
	);
	myPrintF( "\n" );

	// --

	retval = RETURN_OK;

bailout:

	if ( dirObj )
	{
		RADelete( dirObj );
	}

	if ( RAAppObject )
	{
		RADelete( RAAppObject );
	}

	// --

	return( retval );
}

/* -- The End -- */
