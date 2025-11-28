
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2011-2025 Rene W. Olsen
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
	{ MIT_Name,				(Tag) "__library"		},
	{ MIT_VectorTable,		(Tag) Manager_Vectors	},
	{ MIT_Version,			(Tag) 1					},
	{ TAG_END,				(Tag) 0					}
};

// -- Main Interface

void _Main_Obtain( void );
void _Main_Release( void );
//void _Main_Expunge( void );
void _Main_Clone( void );

// -- Class
/*    1 */	void _main_Class_Add( void );
/*    2 */	void _main_Class_CreateTags( void );
/*    3 */	void _main_Class_CreateList( void );
/*    4 */	void _main_Class_Delete( void );
/*    5 */	void _main_Class_FindTags( void );
/*    6 */	void _main_Class_FindList( void );
/*    7 */	void _main_Class_Lock( void );
/*    8 */	void _main_Class_Unlock( void );

// -- Object
/*   21 */	void _main_Object_CreateTags( void );
/*   22 */	void _main_Object_CreateList( void );
/*   23 */	void _main_Object_Delete( void );

// -- Method
/*   41 */	void _main_Method_DoTags( void );
/*   42 */	void _main_Method_DoList( void );
/*   43 */	void _main_Method_DoParentTags( void );
/*   44 */	void _main_Method_DoParentList( void );
/*   45 */	void _main_Method_DoSuperNew( void );
/*   46 */	void _main_Method_DoSuperTags( void );
/*   47 */	void _main_Method_DoSuperList( void );
/*   48 */	void _main_Method_RunFunc( void );

// -- Misc
/*   61 */	void _main_Misc_GetTagData( void );
/*   62 */	void _main_Misc_GetTagValue( void );
/*   63 */	void _main_Misc_Plugin_Open( void );
/*   64 */	void _main_Misc_Plugin_Free( void );
/*   65 */	void _main_Misc_Valid_Class_Name( void );
/*   66 */	void _main_Misc_NextTag( void );
/*   67 */	void _main_Misc_XGet( void );
/*   68 */	void _main_Misc_Valid_Base_Name( void );	// App Base
/*   69 */	void _main_Misc_LoadFile_32( void );
/*   70 */	void _main_Misc_LoadFile_64( void );

// -- Arguments
/*   81 */	void _main_Arguments_ParseList( void );
/*   82 */	void _main_Arguments_ParseTags( void );
/*   83 */	void _main_Arguments_Free( void );

// -- Attributes
/*  101 */	void _main_Attr_Get( void );
/*  102 */	void _main_Attr_GetTags( void );
/*  103 */	void _main_Attr_GetList( void );
/*  104 */	void _main_Attr_GetSuper( void );
/*  105 */	void _main_Attr_GetSuperTags( void );
/*  106 */	void _main_Attr_GetSuperList( void );
/*  107 */	void _main_Attr_GetParent( void );
/*  108 */	void _main_Attr_GetParentTags( void );
/*  109 */	void _main_Attr_GetParentList( void );
/*  110 */	void _main_Attr_Set( void );
/*  111 */	void _main_Attr_SetTags( void );
/*  112 */	void _main_Attr_SetList( void );
/*  113 */	void _main_Attr_SetSuper( void );
/*  114 */	void _main_Attr_SetSuperTags( void );
/*  115 */	void _main_Attr_SetSuperList( void );
/*  116 */	void _main_Attr_SetParent( void );
/*  117 */	void _main_Attr_SetParentTags( void );
/*  118 */	void _main_Attr_SetParentList( void );


static const PTR Main_Vectors[] =
{
	(PTR) _Main_Obtain,
	(PTR) _Main_Release,
	(PTR) _Main_Expunge,
	(PTR) _Main_Clone,

	// -- Arguments
/*   81 */	_main_Arguments_ParseList,
/*   82 */	_main_Arguments_ParseTags,
/*   83 */	_main_Arguments_Free,

// -- Attributes
/*  101 */	_main_Attr_Get,
/*  102 */	_main_Attr_GetTags,
/*  103 */	_main_Attr_GetList,
/*  104 */	_main_Attr_GetSuper,
/*  105 */	_main_Attr_GetSuperTags,
/*  106 */	_main_Attr_GetSuperList,
/*  107 */	_main_Attr_GetParent,
/*  108 */	_main_Attr_GetParentTags,
/*  109 */	_main_Attr_GetParentList,
/*  110 */	_main_Attr_Set,
/*  111 */	_main_Attr_SetTags,
/*  112 */	_main_Attr_SetList,
/*  113 */	_main_Attr_SetSuper,
/*  114 */	_main_Attr_SetSuperTags,
/*  115 */	_main_Attr_SetSuperList,
/*  116 */	_main_Attr_SetParent,
/*  117 */	_main_Attr_SetParentTags,
/*  118 */	_main_Attr_SetParentList,

// -- Class
/*    1 */	_main_Class_Add,
/*    2 */	_main_Class_CreateTags,
/*    3 */	_main_Class_CreateList,
/*    4 */	_main_Class_Delete,
/*    5 */	_main_Class_FindTags,
/*    6 */	_main_Class_FindList,
/*    7 */	_main_Class_Lock,
/*    8 */	_main_Class_Unlock,

// -- Object
/*   21 */	_main_Object_CreateTags,
/*   22 */	_main_Object_CreateList,
/*   23 */	_main_Object_Delete,

// -- Method
/*   41 */	_main_Method_DoTags,
/*   42 */	_main_Method_DoList,
/*   43 */	_main_Method_DoParentTags,
/*   44 */	_main_Method_DoParentList,
/*   45 */	_main_Method_DoSuperNew,
/*   46 */	_main_Method_DoSuperTags,
/*   47 */	_main_Method_DoSuperList,
/*   48 */	_main_Method_RunFunc,

// -- Misc
/*   61 */	_main_Misc_GetTagData,
/*   62 */	_main_Misc_GetTagValue,
/*   63 */	_main_Misc_Plugin_Open,
/*   64 */	_main_Misc_Plugin_Free,
/*   65 */	_main_Misc_Valid_Class_Name,
/*   66 */	_main_Misc_NextTag,
/*   67 */	_main_Misc_XGet,
/*   68 */	_main_Misc_Valid_Class_Name,		// App Base, for now same as Class Name
/*   69 */  _main_Misc_LoadFile_32,
/*   70 */  _main_Misc_LoadFile_64,

	(PTR) -1
};

const struct TagItem Main_Tags[] =
{
	{ MIT_Name,				(Tag) "main"		},
	{ MIT_VectorTable,		(Tag) Main_Vectors	},
	{ MIT_DataSize,			(Tag) sizeof( struct libData ) },
	{ MIT_Version,			(Tag) 1				},
	{ TAG_END,				(Tag) 0				}
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
struct Library *		DOSBase			= NULL;
struct Library *		IconBase		= NULL;
struct AmyCLibIFace *	IAmyCLib		= NULL;
struct DOSIFace *		IDOS			= NULL;
struct ExecIFace *		IExec			= NULL;
struct IconIFace *		IIcon			= NULL;

// --

void ROMFree( struct libBase *libBase UNUSED )
{

}

// --

static PTR ROMInit( PTR Dummy UNUSED, PTR SegList, struct ExecBase *mySysBase )
{
struct RA_PrivClass *RootClass;
struct libBase *libBase;
S32 error;
S32 size;
STR name;

	IExec	= (PTR) mySysBase->MainInterface;
	error	= TRUE;
	libBase	= NULL;

//	IExec->DebugPrintF( "Reactive : ROMInit 1\n" );

	// --

	AmyCLibBase = IExec->OpenLibrary( "AmyCLib.library", 1 );

	if ( ! AmyCLibBase )
	{
//		IExec->DebugPrintF( "Reactive : Error opening AmyCLib v1\n" );
		goto bailout;
	}

	IAmyCLib = (PTR) IExec->GetInterface( AmyCLibBase, "main", 1, NULL );

	if ( ! IAmyCLib )
	{
//		IExec->DebugPrintF( "Reactive : Error opening AmyCLib interface\n" );
		goto bailout;
	}

	if ( ! IAmyCLib->Priv_Startup_Init( NULL, EM_STRING|EM_MEMORY ))
	{
//		IExec->DebugPrintF( "Reactive : Error AmyC Startup failed\n" );
		goto bailout;
	}

	// --

	DOSBase = IExec->OpenLibrary( "dos.library", 50 );

	if ( ! AmyCLibBase )
	{
//		IExec->DebugPrintF( "Reactive : Error opening DOS v50\n" );
		goto bailout;
	}

	IDOS = (PTR) IExec->GetInterface( DOSBase, "main", 1, NULL );

	if ( ! IDOS )
	{
//		IExec->DebugPrintF( "Reactive : Error opening DOS interface\n" );
		goto bailout;
	}

	// --

//	IExec->DebugPrintF( "Reactive : ROMInit 2\n" );

	libBase = (PTR) IExec->CreateLibraryTags(
		CLT_DataSize, sizeof( struct libBase ),
		CLT_Interfaces,	libInterfaces,
		CLT_NoLegacyIFace, TRUE,
		TAG_END
	);

	if ( ! libBase )
	{
//		IExec->DebugPrintF( "Reactive : Error creating Device\n" );
		goto bailout;
	}

//	IExec->DebugPrintF( "Reactive : ROMInit 3\n" );

	libBase->lib_Base.lib_Node.ln_Type	= NT_LIBRARY;
	libBase->lib_Base.lib_Node.ln_Pri	= 0;
	libBase->lib_Base.lib_Node.ln_Name	= (STR) LIBNAME,
	libBase->lib_Base.lib_Flags			= LIBF_SUMUSED | LIBF_CHANGED;
	libBase->lib_Base.lib_Version		= VERSION;
	libBase->lib_Base.lib_Revision		= REVISION;
	libBase->lib_Base.lib_IdString		= (STR) VSTRING;
	libBase->lib_SegList				= SegList;

	// -- 

	IExec->NewList( & libBase->lib_PublicClassHeader );
	IExec->NewList( & libBase->lib_PrivateClassHeader );
	IExec->InitSemaphore( & libBase->lib_ClassSemaphore );

	// -- Create Root Class

	RootClass = IExec->AllocVecTags( sizeof( struct RA_PrivClass ),
		AVT_Clear, 0,
		TAG_END
	);

	if ( ! RootClass )
	{
//		IExec->DebugPrintF( "Error allocating memory\n" );
		goto bailout;
	}

	libBase->lib_RootClass = RootClass;

//	IExec->DebugPrintF( "RootClass %p\n", RootClass );

	// --

	// Sizeof includes the nul
	int len = sizeof( RAC_Root ) - 1;

	name = IExec->AllocVecTags( len + 1,
		AVT_Clear, 0,
		TAG_END
	);

	if ( ! name )
	{
//		IExec->DebugPrintF( "Error allocating memory\n" );
		goto bailout;
	}

	for( int cnt=0 ; cnt<len ; cnt++ )
	{
		name[cnt] = RAC_Root[cnt];
	}

//	IExec->DebugPrintF( "RootName: '%s'\n", name );

	// --

	// Make sure its 8 byte alligned
	size  = sizeof( struct RootClass_Data );
	size +=  7;
	size &= ~7;

	RootClass->RA_Class_Next			= NULL;
	RootClass->RA_Class_Prev			= NULL;
	RootClass->RA_Class_Type			= RA_Type_Unknown;
	RootClass->RA_Class_ID				= ID_RAClass;
	RootClass->RA_Class_Super			= NULL;
//	RootClass->RA_Class_Plugin			= NULL;
//	RootClass->RA_Class_Count_Objects	= 0;
//	RootClass->RA_Class_Count_SubClasses= 0;
//	RootClass->RA_Class_Count_FindLocks = 0;
	RootClass->RA_Class_Dispatcher		= RootDispatcher;
	RootClass->RA_Class_InstSize		= size;
	RootClass->RA_Class_InstTotalSize	= size;
	RootClass->RA_Class_InstOffset		= 0;
	RootClass->RA_Class_Name			= name;
	RootClass->RA_Class_NameLength		= len;
//	RootClass->RA_Class_Data			= libBase;

	IExec->AddTail( & libBase->lib_PublicClassHeader, (PTR) RootClass );

	// --

	IExec->AddLibrary( (PTR) libBase );
	IExec->DebugPrintF( "Reactive : Rock'n Roll\n" );
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
