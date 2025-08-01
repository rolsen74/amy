
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

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

#if 0
static const PTR Main_Vectors[] =
{
	(PTR) _main_Obtain,
	(PTR) _main_Release,
	(PTR) NULL,
	(PTR) NULL,
//	(PTR) _main_GetAttrsA,
//	(PTR) _main_GetAttrs,
//	(PTR) _main_RunFunction,
//	(PTR) _main_RunInterface,
	(PTR) -1
};

static const struct TagItem Main_Tags[] =
{
	{ MIT_Name,				(U32) "main"		},
	{ MIT_VectorTable,		(U32) Main_Vectors	},
	{ MIT_Version,			(U32) 1				},
	{ TAG_END,				(U32) 0				}
};
#endif

// --

static const PTR libInterfaces[] =
{
	(PTR) Manager_Tags,
//	(PTR) Main_Tags,
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
struct Library *		NewlibBase		= NULL;
struct Interface *		INewlib			= NULL;
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

	IExec->DebugPrintF( "AmyCLib : ROMInit 1\n" );

	NewlibBase = IExec->OpenLibrary( "newlib.library", 53 );

	if ( ! NewlibBase )
	{
		IExec->DebugPrintF( "AmyCLib : Error opening newlib v53" );
		goto bailout;
	}

	INewlib = IExec->GetInterface( NewlibBase, "main", 1, NULL );

	if ( ! INewlib )
	{
		IExec->DebugPrintF( "AmyCLib : Error opening newlib interface" );
		goto bailout;
	}

	IExec->DebugPrintF( "AmyCLib : ROMInit 2\n" );

	libBase = (PTR) IExec->CreateLibraryTags(
		CLT_DataSize, sizeof( struct libBase ),
		CLT_Interfaces,	libInterfaces,
		CLT_NoLegacyIFace, TRUE,
		TAG_END
	);

	if ( ! libBase )
	{
		IExec->DebugPrintF( "AmyCLib : Error creating Device" );
		goto bailout;
	}

	IExec->DebugPrintF( "AmyCLib : ROMInit 3\n" );

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
	IExec->DebugPrintF( "AmyCLib : Rock'n Roll\n" );
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
