
/*
** SPDX-License-Identifier: BSD-3-Clause
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

void _main_Obtain(void);
void _main_Release(void);
U32  _main_Expunge( struct AmyCLibIFace *Self );
void _main_Clone(void);
void _main__Priv_Startup_Init(void);
void _main__Priv_Startup_Main(void);
void _main__Priv_Startup_Free(void);
void _main__Priv_Mem_Alloc(void);
void _main__Priv_Mem_Free(void);
void _main__Priv_Mem_Realloc(void);
void _main__Priv_Mem_CreatePool(void);
void _main__Priv_Mem_DeletePool(void);
void _main__Priv_Mem_FlushPool(void);
void _main__Priv_Mem_AllocPooled(void);
void _main__Priv_Mem_FreePooled(void);
void _main_setjmp_longjmp(void);
void _main_setjmp_setjmp(void);
void _main_string_memcpy(void);
void _main_string_memset(void);
void _main_strings_bzero(void);
void _main_stdlib_calloc(void);
void _main_stdlib_malloc(void);
void _main_stdlib_realloc(void);
void _main_stdlib_free(void);

static const PTR Main_Vectors[] =
{
	(PTR) _main_Obtain,
	(PTR) _main_Release,
	(PTR) _main_Expunge,
	(PTR) _main_Clone,
	(PTR) _main__Priv_Startup_Init,
	(PTR) _main__Priv_Startup_Main,
	(PTR) _main__Priv_Startup_Free,
	(PTR) _main__Priv_Mem_Alloc,
	(PTR) _main__Priv_Mem_Free,
	(PTR) _main__Priv_Mem_Realloc,
	(PTR) _main__Priv_Mem_CreatePool,
	(PTR) _main__Priv_Mem_DeletePool,
	(PTR) _main__Priv_Mem_FlushPool,
	(PTR) _main__Priv_Mem_AllocPooled,
	(PTR) _main__Priv_Mem_FreePooled,
	(PTR) _main_setjmp_longjmp,
	(PTR) _main_setjmp_setjmp,
	(PTR) _main_string_memcpy,
	(PTR) _main_string_memset,
	(PTR) _main_strings_bzero,
	(PTR) _main_stdlib_calloc,
	(PTR) _main_stdlib_malloc,
	(PTR) _main_stdlib_realloc,
	(PTR) _main_stdlib_free,
	(PTR) -1
};

const struct TagItem Main_Tags[] =
{
	{ MIT_Name,				(U32) "main"		},
	{ MIT_VectorTable,		(U32) Main_Vectors	},
	{ MIT_DataSize,			(U32) sizeof( struct libData ) },
	{ MIT_Flags,			(U32) IFLF_PRIVATE	},
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
//struct Library *		NewlibBase		= NULL;
//struct Interface *	INewlib			= NULL;
struct ExecIFace *		IExec			= NULL;
struct Library *		DOSBase			= NULL;
struct DOSIFace *		IDOS			= NULL;

// --

void ROMFree( struct libBase *libBase UNUSED )
{
	IExec->DebugPrintF( "AmyCLib : Library ROMFree :\n" );
}

// --

static PTR ROMInit( PTR Dummy UNUSED, PTR SegList, struct ExecBase *mySysBase )
{
struct libBase *libBase;
S32 error;

	IExec	= (PTR) mySysBase->MainInterface;
	error	= TRUE;
	libBase	= NULL;

	IExec->DebugPrintF( "AmyCLib : Library ROMInit :\n" );

	// --
	#if 0

	// NewlibBase = IExec->OpenLibrary( "newlib.library", 50 );

	// if ( ! NewlibBase )
	// {
	// 	IExec->DebugPrintF( "AmyCLib : Error opening newlib v50" );
	// 	goto bailout;
	// }

	// INewlib = IExec->GetInterface( NewlibBase, "main", 1, NULL );

	// if ( ! INewlib )
	// {
	// 	IExec->DebugPrintF( "AmyCLib : Error opening newlib interface" );
	// 	goto bailout;
	// }

	#endif
	// --

	DOSBase = IExec->OpenLibrary( "dos.library", 50 );

	if ( ! DOSBase )
	{
		IExec->DebugPrintF( "AmyCLib : Error opening dos v50" );
		goto bailout;
	}

	IDOS = (PTR) IExec->GetInterface( DOSBase, "main", 1, NULL );

	if ( ! IDOS )
	{
		IExec->DebugPrintF( "AmyCLib : Error opening dos interface" );
		goto bailout;
	}

	// --

	libBase = (PTR) IExec->CreateLibraryTags(
		CLT_DataSize, sizeof( struct libBase ),
		CLT_Interfaces,	libInterfaces,
		CLT_NoLegacyIFace, TRUE,
		TAG_END
	);

	if ( ! libBase )
	{
		goto bailout;
	}

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
