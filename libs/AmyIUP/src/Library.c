
/*
** SPDX-License-Identifier: MIT
** Copyright (C) 1994-2025 Tecgraf/PUC-Rio.
** Mini-port by Rene W. Olsen (2025)
** Target OS: AmigaOS
*/

// --

#include "inc/All.h"

// --

S32 _start( STR argstring UNUSED, S32 arglen UNUSED, struct ExecBase *sysbase UNUSED )
{
	return( 0 );
}

// -- Manager Interface

static const PTR Manager_Vectors[] =
{
	(PTR) _manager_Obtain,
	(PTR) _manager_Release,
	(PTR) NULL,
	(PTR) NULL,
	(PTR) _manager_Open,
	(PTR) _manager_Close,
	(PTR) _manager_Expunge,
	(PTR) NULL,
	(PTR) -1,
};

static const struct TagItem Manager_Tags[] =
{
	{ MIT_Name,				(U32) "__library"		},
	{ MIT_VectorTable,		(U32) Manager_Vectors	},
	{ MIT_Version,			(U32) 1					},
	{ TAG_END,				(U32) 0					}
};

// -- Main Interface

static const PTR Main_Vectors[] =
{
	(PTR) _Main_Obtain,
	(PTR) _Main_Release,
	(PTR) _Main_Expunge,
	(PTR) _Main_Clone,
	(PTR) _Main_IupOpen,
	(PTR) _Main_IupClose,
	(PTR) _Main_IupMainLoop,
	(PTR) _Main_IupSetGlobal,
	(PTR) -1
};

const struct TagItem Main_Tags[] =
{
	{ MIT_Name,				(U32) "main"		},
	{ MIT_VectorTable,		(U32) Main_Vectors	},
	{ MIT_Version,			(U32) 1				},
	{ TAG_END,				(U32) 0				}
};

// --

static const PTR libInterfaces[] =
{
	(PTR) Manager_Tags,
	(PTR) Main_Tags,
	(PTR) NULL
};

// --

static PTR ROMInit( PTR Dummy, PTR SegList, struct ExecBase *SysBase );

static USED const struct Resident lib_res =
{
/* rt_MatchWord	*/			RTC_MATCHWORD,
/* rt_MatchTag	*/ (PTR)	( & lib_res + 0 ),
/* rt_EndSkip	*/ (PTR)	( & lib_res + 1 ),
/* rt_Flags		*/			RTF_NATIVE|RTF_COLDSTART,
/* rt_Version	*/			VERSION,
/* rt_Type		*/			NT_LIBRARY,
/* rt_Pri		*/			0,
/* rt_Name		*/ (STR)	LIBNAME,
/* rt_IdString	*/ (STR)	VSTRING,
/* rt_Init		*/ (PTR)	ROMInit
};

// --

static const char USED	verstag[]		= VERSTAG;
struct Library *		AmyCLibBase		= NULL;
struct AmyCLibIFace *	IAmyCLib		= NULL;
struct ExecIFace *		IExec			= NULL;

// --

void ROMFree( struct libBase *libBase UNUSED )
{
}

// --

static PTR ROMInit( PTR Dummy UNUSED, PTR SegList, struct ExecBase *mySysBase )
{
struct libBase *libBase;
S32 error;

	IExec	= (PTR) mySysBase->MainInterface;
	error	= TRUE;
	libBase	= NULL;

	IExec->DebugPrintF( "AmyIUP : ROMInit 1\n" );

	AmyCLibBase = IExec->OpenLibrary( "amyclib.library", 1 );

	if ( ! AmyCLibBase )
	{
		IExec->DebugPrintF( "AmyIUP : Error opening amyclib v1" );
		goto bailout;
	}

	IAmyCLib = IExec->GetInterface( AmyCLibBase, "main", 1, NULL );

	if ( ! IAmyCLib )
	{
		IExec->DebugPrintF( "AmyIUP : Error opening amyclib interface" );
		goto bailout;
	}

	IExec->DebugPrintF( "AmyIUP : ROMInit 2\n" );

	libBase = (PTR) IExec->CreateLibraryTags(
		CLT_DataSize, sizeof( struct libBase ),
		CLT_Interfaces,	libInterfaces,
		CLT_NoLegacyIFace, TRUE,
		TAG_END
	 );

	if ( ! libBase )
	{
		IExec->DebugPrintF( "AmyIUP : Error creating Device" );
		goto bailout;
	}

	IExec->DebugPrintF( "AmyIUP : ROMInit 3\n" );

	libBase->lib_Base.lib_Node.ln_Type	= NT_LIBRARY;
	libBase->lib_Base.lib_Node.ln_Pri	= 0;
	libBase->lib_Base.lib_Node.ln_Name	= (STR) LIBNAME,
	libBase->lib_Base.lib_Flags			= LIBF_SUMUSED | LIBF_CHANGED;
	libBase->lib_Base.lib_Version		= VERSION;
	libBase->lib_Base.lib_Revision		= REVISION;
	libBase->lib_Base.lib_IdString		= (STR) VSTRING;
	libBase->lib_SegList				= SegList;

	// --

	IExec->AddLibrary( (PTR) libBase );
	IExec->DebugPrintF( "AmyIUP : Rock'n Roll\n" );
	error = FALSE;

bailout:

	if (( error ) && ( libBase ))
	{
		ROMFree( libBase );
		libBase = NULL;
	}

	return( libBase );
}

// --
