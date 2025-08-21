
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

void AMYFUNC _Main_Obtain(void);
void AMYFUNC _Main_Release(void);
U32  AMYFUNC _Main_Expunge( struct AmyCLibPrivIFace *Self );
void AMYFUNC _Main_Clone(void);
void AMYFUNC _generic__Priv_Startup_Init(void);
void AMYFUNC _generic__Priv_Startup_Main(void);
void AMYFUNC _generic__Priv_Startup_Free(void);

// void _generic__Priv_Mem_Alloc(void);
// void _generic__Priv_Mem_Free(void);
// void _generic__Priv_Mem_Realloc(void);
// void _generic__Priv_Mem_CreatePool(void);
// void _generic__Priv_Mem_DeletePool(void);
// void _generic__Priv_Mem_FlushPool(void);
// void _generic__Priv_Mem_AllocPooled(void);
// void _generic__Priv_Mem_FreePooled(void);
// void _generic__Priv_Check_Abort(void);
// void _generic__Priv_Convert_Time_to_TM(void);
// void _generic__Priv_Convert_ED_to_Stat(void);
// void _generic__Priv_Convert_DS_to_Time(void);
// void _generic__Priv_Convert_IOErr_to_ErrNo(void);
// void _generic__Priv_FB_Read(void);
// void _generic__Priv_FB_Read_Fill_Buffer(void);
// void _generic__Priv_FB_Read_Drop_Buffer(void);
// void _generic__Priv_FB_Write(void);
// void _generic__Priv_FB_Write_Flush_Buffer(void);
// void _generic__Priv_FB_Write_Flush_Buffer2(void);
// void _generic__Priv_FD_Alloc(void);
// void _generic__Priv_FD_Free(void);
// void _generic__Priv_FD_Init(void);
// void _generic__Priv_FD_Init_Struct(void);
// void _generic__Priv_FD_Array_Insert(void);
// void _generic__Priv_FD_Array_Remove(void);
// void _generic__Priv_FDLockNr(void);
// void _generic__Priv_FDLockStream(void);
// void _generic__Priv_FDUnlock(void);
// void _generic__Priv_Print(void);
// void _generic__Priv_Scan(void);
// void _generic_setjmp_longjmp(void);
// void _generic_setjmp_setjmp(void);
// void _generic_stdlib_calloc(void);
// void _generic_stdlib_malloc(void);
// void _generic_stdlib_realloc(void);
// void _generic_stdlib_free(void);
// void _generic_stdlib_rand(void);
// void _generic_stdlib_rand_r(void);
// void _generic_stdlib_srand(void);
// void _generic_stdlib_atoi(void);
// void _generic_stdlib_strtol(void);
void _generic_string_strlen(void);
void _generic_string_strnlen(void);
// void _generic_string_strdup(void);
// void _generic_string_strndup(void);
void _generic_string_strcpy(void);
void _generic_string_strncpy(void);
void _generic_string_strcmp(void);
void _generic_string_strncmp(void);
void _generic_string_memcmp(void);
void _generic_string_memmove(void);
void _generic_string_memcpy(void);
void _generic_string_memset(void);
// void _generic_string_strcat(void);
void _generic_strings_bzero(void);
void _generic_ctype_isalpha(void);
void _generic_ctype_isdigit(void);
void _generic_ctype_isspace(void);
void _generic_ctype_isupper(void);
void _generic_ctype_isxdigit(void);
void _generic_ctype_tolower(void);
void _generic_ctype_toupper(void);
void _generic_ctype_islower(void);
// void _generic_time_localtime(void);
// void _generic_time_time(void);
// void _generic_stdio_fopen(void);
// void _generic_stdio_ftell(void);
// void _generic_stdio_fgetpos(void);
// void _generic_stdio_flockfile(void);
// void _generic_stdio_funlockfile(void);
// void _generic_stdio_fflush(void);
// void _generic_stdio_puts(void);
// void _generic_stdio_putchar(void);
// void _generic_stdio_fputc(void);
// void _generic_stdio_setvbuf(void);
// void _generic_stdio_fclose(void);
// void _generic_stdio_fseek(void);
// void _generic_stdio_fseeko(void);
//-- void _generic_stdio_printf(void);
// void _generic_stdio_vprintf(void);
// void _generic_stdio_sprintf(void);
// void _generic_stdio_snprintf(void);
// void _generic_stdio_vsnprintf(void);
// void _generic_fcntl_open(void);
// void _generic_unistd_close(void);
// // --
// void _generic_stdio_ungetc(void);
// void _generic_stdio_fread(void);
// void _generic_stdlib_strtof(void);
// void _generic_stdlib_strtod(void);
// void _generic_inttypes_strtoumax(void);
// void _generic_inttypes_strtoimax(void);
// void _generic_stdio_clearerr(void);
// void _generic_strings_strcasecmp(void);
// void _generic_strings_strncasecmp(void);
// void _generic_math_d__get_huge_val(void);
// void _generic_math_d__inf(void);
// void _generic_math_d__isinf(void);
// void _generic_math_d__isnan(void);
// void _generic_math_d_nan(void);
// void _generic_math_d_pow(void);
// void _generic_math_d_fabs(void);
// void _generic_math_d_scalbn(void);
// void _generic_math_d_sqrt(void);
// void _generic_math_d_copysign(void);
// void _generic_stdio_vsscanf(void);
void _generic_time_strftime(void);
void _generic_time_gmtime(void);
void _generic_time_gmtime_r(void);
// void _generic_signal_signal(void);
// void _generic_signal_raise(void);
// void _generic_stdlib_abort(void);
// void _generic_stdlib__Exit(void);
void _generic__Priv_Print_Log(void);
void _generic__Priv_Func_Log(void);


struct EnableFunc
{
	U32					CPUType;	// 0 = Fallback function and EndMarker
	PTR					CPUFunc;
};

struct EnableStruct
{
	U32					Mask;		// EM_STRING | EM_FILE
	struct EnableFunc *	Func;
};

static U32 _NotEnabled( void )
{
	IExec->DebugPrintF( "Function not enabled\n" );
	return( 0 );
}

static const PTR Main_Vectors[] =
{
/*    0 */	(PTR) _Main_Obtain,
/*    1 */	(PTR) _Main_Release,
/*    2 */	(PTR) _Main_Expunge,
/*    3 */	(PTR) _Main_Clone,
/*    4 */	(PTR) _generic__Priv_Startup_Init,
/*    5 */	(PTR) _generic__Priv_Startup_Main,
/*    6 */	(PTR) _generic__Priv_Startup_Free,
/*    7 */	(PTR) _NotEnabled,	// _generic__Priv_Mem_Alloc,
/*    8 */	(PTR) _NotEnabled,	// _generic__Priv_Mem_Free,
/*    9 */	(PTR) _NotEnabled,	// _generic__Priv_Mem_Realloc,
/*   10 */	(PTR) _NotEnabled,	// _generic__Priv_Mem_CreatePool,
/*   11 */	(PTR) _NotEnabled,	// _generic__Priv_Mem_DeletePool,
/*   12 */	(PTR) _NotEnabled,	// _generic__Priv_Mem_FlushPool,
/*   13 */	(PTR) _NotEnabled,	// _generic__Priv_Mem_AllocPooled,
/*   14 */	(PTR) _NotEnabled,	// _generic__Priv_Mem_FreePooled,
/*   15 */	(PTR) _NotEnabled,	// _generic__Priv_Check_Abort,
/*   16 */	(PTR) _NotEnabled,	// _generic__Priv_Convert_Time_to_TM,
/*   17 */	(PTR) _NotEnabled,	// _generic__Priv_Convert_ED_to_Stat,
/*   18 */	(PTR) _NotEnabled,	// _generic__Priv_Convert_DS_to_Time,
/*   19 */	(PTR) _NotEnabled,	// _generic__Priv_Convert_IOErr_to_ErrNo,
/*   20 */	(PTR) _NotEnabled,	// _generic__Priv_FB_Read,
/*   21 */	(PTR) _NotEnabled,	// _generic__Priv_FB_Read_Fill_Buffer,
/*   22 */	(PTR) _NotEnabled,	// _generic__Priv_FB_Read_Drop_Buffer,
/*   23 */	(PTR) _NotEnabled,	// _generic__Priv_FB_Write,
/*   24 */	(PTR) _NotEnabled,	// _generic__Priv_FB_Write_Flush_Buffer,
/*   25 */	(PTR) _NotEnabled,	// _generic__Priv_FB_Write_Flush_Buffer2,
/*   26 */	(PTR) _NotEnabled,	// _generic__Priv_FD_Alloc,
/*   27 */	(PTR) _NotEnabled,	// _generic__Priv_FD_Free,
/*   28 */	(PTR) _NotEnabled,	// _generic__Priv_FD_Init,
/*   29 */	(PTR) _NotEnabled,	// _generic__Priv_FD_Init_Struct,
/*   30 */	(PTR) _NotEnabled,	// _generic__Priv_FD_Array_Insert,
/*   31 */	(PTR) _NotEnabled,	// _generic__Priv_FD_Array_Remove,
/*   32 */	(PTR) _NotEnabled,	// _generic__Priv_FDLockNr,
/*   33 */	(PTR) _NotEnabled,	// _generic__Priv_FDLockStream,
/*   34 */	(PTR) _NotEnabled,	// _generic__Priv_FDUnlock,
/*   35 */	(PTR) _NotEnabled,	// _generic__Priv_Print,
/*   36 */	(PTR) _NotEnabled,	// _generic__Priv_Scan,
/*   37 */	(PTR) _NotEnabled,	// _generic_setjmp_longjmp,
/*   38 */	(PTR) _NotEnabled,	// _generic_setjmp_setjmp,
/*   39 */	(PTR) _NotEnabled,	// _generic_stdlib_calloc,
/*   40 */	(PTR) _NotEnabled,	// _generic_stdlib_malloc,
/*   41 */	(PTR) _NotEnabled,	// _generic_stdlib_realloc,
/*   42 */	(PTR) _NotEnabled,	// _generic_stdlib_free,
/*   43 */	(PTR) _NotEnabled,	// _generic_stdlib_rand,
/*   44 */	(PTR) _NotEnabled,	// _generic_stdlib_rand_r,
/*   45 */	(PTR) _NotEnabled,	// _generic_stdlib_srand,
/*   46 */	(PTR) _NotEnabled,	// _generic_stdlib_atoi,
/*   47 */	(PTR) _NotEnabled,	// _generic_stdlib_strtol,
/*   48 */	(PTR) _generic_string_strlen,
/*   49 */	(PTR) _generic_string_strnlen,
/*   50 */	(PTR) _NotEnabled,	// _generic_string_strdup,
/*   51 */	(PTR) _NotEnabled,	// _generic_string_strndup,
/*   52 */	(PTR) _generic_string_strcpy,
/*   53 */	(PTR) _generic_string_strncpy,
/*   54 */	(PTR) _generic_string_strcmp,
/*   55 */	(PTR) _generic_string_strncmp,
/*   56 */	(PTR) _generic_string_memcmp,
/*   57 */	(PTR) _generic_string_memmove,
/*   58 */	(PTR) _generic_string_memcpy,
/*   59 */	(PTR) _generic_string_memset,
/*   60 */	(PTR) _NotEnabled,	// _generic_string_strcat,
/*   61 */	(PTR) _generic_strings_bzero,
/*   62 */	(PTR) _generic_ctype_isalpha,
/*   63 */	(PTR) _generic_ctype_isdigit,
/*   64 */	(PTR) _generic_ctype_isspace,
/*   65 */	(PTR) _generic_ctype_isupper,
/*   66 */	(PTR) _generic_ctype_isxdigit,
/*   67 */	(PTR) _generic_ctype_tolower,
/*   68 */	(PTR) _generic_ctype_toupper,
/*   69 */	(PTR) _NotEnabled,	// _generic_time_localtime,
/*   70 */	(PTR) _NotEnabled,	// _generic_time_time,
/*   71 */	(PTR) _NotEnabled,	// _generic_stdio_fopen,
/*   72 */	(PTR) _NotEnabled,	// _generic_stdio_ftell,
/*   73 */	(PTR) _NotEnabled,	// _generic_stdio_fgetpos,
/*   74 */	(PTR) _NotEnabled,	// _generic_stdio_flockfile,
/*   75 */	(PTR) _NotEnabled,	// _generic_stdio_funlockfile,
/*   76 */	(PTR) _NotEnabled,	// _generic_stdio_fflush,
/*   77 */	(PTR) _NotEnabled,	// _generic_stdio_puts,
/*   78 */	(PTR) _NotEnabled,	// _generic_stdio_putchar,
/*   79 */	(PTR) _NotEnabled,	// _generic_stdio_fputc,
/*   80 */	(PTR) _NotEnabled,	// _generic_stdio_setvbuf,
/*   81 */	(PTR) _NotEnabled,	// _generic_stdio_fclose,
/*   82 */	(PTR) _NotEnabled,	// _generic_stdio_fseek,
/*   83 */	(PTR) _NotEnabled,	// _generic_stdio_fseeko,
/*   84 */	(PTR) _NotEnabled,	// _generic_stdio_vprintf,
/*   85 */	(PTR) _NotEnabled,	// _generic_stdio_vsprintf,
/*   86 */	(PTR) _NotEnabled,	// _generic_stdio_fputc_unlocked,
/*   87 */	(PTR) _NotEnabled,	// _generic_stdio_vsnprintf,
/*   88 */	(PTR) _NotEnabled,	// _generic_fcntl_open,
/*   89 */	(PTR) _NotEnabled,	// _generic_unistd_close,
/*   90 */	(PTR) _NotEnabled,	// _generic_stdio_ungetc,
/*   91 */	(PTR) _NotEnabled,	// _generic_stdio_fread,
/*   92 */	(PTR) _NotEnabled,	// _generic_stdlib_strtof,
/*   93 */	(PTR) _NotEnabled,	// _generic_stdlib_strtod,
/*   94 */	(PTR) _NotEnabled,	// _generic_inttypes_strtoumax,
/*   95 */	(PTR) _NotEnabled,	// _generic_inttypes_strtoimax,
/*   96 */	(PTR) _NotEnabled,	// _generic_stdio_clearerr,
/*   97 */	(PTR) _NotEnabled,	// _generic_strings_strcasecmp,
/*   98 */	(PTR) _NotEnabled,	// _generic_strings_strncasecmp,
/*   99 */	(PTR) _NotEnabled,	// _generic_math_d__get_huge_val,
/*  100 */	(PTR) _NotEnabled,	// _generic_math_d__inf,
/*  101 */	(PTR) _NotEnabled,	// _generic_math_d__isinf,
/*  102 */	(PTR) _NotEnabled,	// _generic_math_d__isnan,
/*  103 */	(PTR) _NotEnabled,	// _generic_math_d_nan,
/*  104 */	(PTR) _NotEnabled,	// _generic_math_d_pow,
/*  105 */	(PTR) _NotEnabled,	// _generic_math_d_fabs,
/*  106 */	(PTR) _NotEnabled,	// _generic_math_d_scalbn,
/*  107 */	(PTR) _NotEnabled,	// _generic_math_d_sqrt,
/*  108 */	(PTR) _NotEnabled,	// _generic_math_d_copysign,
/*  109 */	(PTR) _NotEnabled,	// _generic_stdio_vsscanf,
/*  110 */	(PTR) _generic_time_strftime,
/*  111 */	(PTR) _NotEnabled,	// _generic_signal_signal,
/*  112 */	(PTR) _NotEnabled,	// _generic_signal_raise,
/*  113 */	(PTR) _NotEnabled,	// _generic_stdlib_abort,
/*  114 */	(PTR) _NotEnabled,	// _generic_stdlib__Exit,
/*  115 */	(PTR) _NotEnabled,	// _generic_stdio_vasprintf
/*  116 */	(PTR) _NotEnabled,	// _generic_assert_assert
/*  117 */	(PTR) _NotEnabled,	// _generic_stdlib_exit
/*  118 */	(PTR) _generic_ctype_islower,
/*  119 */	(PTR) _NotEnabled,	// _generic_stdio_fgetc
/*  120 */	(PTR) _generic_time_gmtime,
/*  121 */	(PTR) _generic_time_gmtime_r,
/*  122 */	(PTR) _NotEnabled,	// _generic_stdio_ferror
/*  123 */	(PTR) _generic__Priv_Print_Log,
/*  124 */	(PTR) _generic__Priv_Func_Log,


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
struct Library *		LocaleBase		= NULL;
struct LocaleIFace *	ILocale			= NULL;
struct Library *		IntuitionBase	= NULL;
struct IntuitionIFace *	IIntuition		= NULL;
struct Library *		UtilityBase		= NULL;
struct UtilityIFace *	IUtility		= NULL;

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
		IExec->DebugPrintF( "AmyCLib : Error opening dos.lib v50" );
		goto bailout;
	}

	IDOS = (PTR) IExec->GetInterface( DOSBase, "main", 1, NULL );

	if ( ! IDOS )
	{
		IExec->DebugPrintF( "AmyCLib : Error opening dos interface" );
		goto bailout;
	}

	/* --  -- */
	// uhh should I only open locale if EM_LOCALE is set

	LocaleBase = IExec->OpenLibrary( "locale.library", 50 );

	if ( ! LocaleBase )
	{
		IExec->DebugPrintF( "AmyCLib : Error opening locale.lib v50" );
		goto bailout;
	}

	ILocale = (PTR) IExec->GetInterface( LocaleBase, "main", 1, NULL );

	if ( ! ILocale )
	{
		IExec->DebugPrintF( "AmyCLib : Error opening Locale interface\n" );
		goto bailout;
	}

	/* --  -- */

	UtilityBase = IExec->OpenLibrary( "utility.library", 50 );

	if ( ! UtilityBase )
	{
		IExec->DebugPrintF( "AmyCLib : Error opening utility.lib v50" );
		goto bailout;
	}

	IUtility = (PTR) IExec->GetInterface( UtilityBase, "main", 1, NULL );

	if ( ! IUtility )
	{
		IExec->DebugPrintF( "AmyCLib : Error opening utility interface" );
		goto bailout;
	}

	/* --  -- */

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
