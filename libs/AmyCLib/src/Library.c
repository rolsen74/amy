
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
	{ MIT_Name,				(Tag) "__library"		},
	{ MIT_VectorTable,		(Tag) Manager_Vectors	},
	{ MIT_Version,			(Tag) 1					},
	{ TAG_END,				(Tag) 0					}
};

// -- Main Interface

void AMYFUNC _Main_Obtain(void);
void AMYFUNC _Main_Release(void);
U32  AMYFUNC _Main_Expunge( struct AmyCLibIFace *Self );
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
void _generic_string_strchr(void);
void _generic_string_strcpy(void);
void _generic_string_strcspn(void);
void _generic_string_strncpy(void);
void _generic_string_strcmp(void);
void _generic_string_strncmp(void);
void _generic_string_strpbrk(void);
void _generic_string_strspn(void);
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
void _generic_stdio_sprintf(void);
void _generic_stdio_vsprintf(void);
void _generic_stdio_snprintf(void);
void _generic_stdio_vsnprintf(void);
// void _generic_fcntl_open(void);
// void _generic_unistd_close(void);
// --
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

static const PTR Main_Vectors[];

// ----

static PTR __Get_User_CLib( void )
{
struct AmyTaskInfo *ati;
struct Task *opener_task;
PTR clib;

	clib = NULL;

	while( TRUE )
	{
		opener_task = IExec->FindTask( NULL );

		ati = (PTR) opener_task->tc_UserData;

		// Check for NULL Pointer
		if ( ! ati )
		{
			IExec->DebugPrintF( "tc_UserData not set\n" );
			break;
		}

		// Make sure we have correct data
		if ( ati->ati_ID != Amy_ATI_ID )
		{
			IExec->DebugPrintF( "invalid ATI ID\n" );
			break;
		}

		// The C library should alway be there, if we have ATI
		if ( ! ati->ati_IFace_C )
		{
			IExec->DebugPrintF( "no C library\n" );
			break;
		}

		clib = (PTR) ati->ati_IFace_C;
		break;
	}

	return( clib );
}

// ----
// no Return, 1 arg
// name1 = stub name
// name2 = interface name
// arg1  = type name
#define NORET_ARG_1(name1,name2,arg1t,arg1n) \
void name1( struct AmyCLibIFace *Self, arg1t arg1n ) \
{ \
	Self = __Get_User_CLib(); \
	if (( Self ) && ( Self->name2 ) && ( Self->name2 != name1 )) \
	{ \
		Self->name2(arg1n); \
	} \
}

// --
// Return, 1 arg
// ret   = return type
// name1 = stub name
// name2 = interface name
// arg1  = type + name
#define RET_ARG_1(name1,name2,ret,arg1t,arg1n) \
ret name1( struct AmyCLibIFace *Self, arg1t arg1n ) \
{ \
	Self = __Get_User_CLib(); \
	if (( Self ) && ( Self->name2 ) && ( Self->name2 != name1 )) \
	{ \
		return( Self->name2( arg1n )); \
	} \
	else \
	{ \
		return( NULL ); \
	} \
}

// --
// Return, 2 args
// ret   = return type
// name1 = stub name
// name2 = interface name
// arg1  = type + name
// arg2  = type + name
#define RET_ARG_2(name1,name2,ret,arg1t,arg1n,arg2t,arg2n) \
ret name1( struct AmyCLibIFace *Self, arg1t arg1n, arg2t arg2n ) \
{ \
	Self = __Get_User_CLib(); \
	if (( Self ) && ( Self->name2 ) && ( Self->name2 != name1 )) \
	{ \
		return( Self->name2( arg1n, arg2n )); \
	} \
	else \
	{ \
		return( NULL ); \
	} \
}

// --


NORET_ARG_1(	stub_free,		stdlib_free,	void *,ptr );
RET_ARG_1(		stub_malloc,	stdlib_malloc,	void *,size_t,size);
RET_ARG_2(		stub_realloc,	stdlib_realloc,	void *,void *,ptr,size_t,size);
RET_ARG_1(		stub_strdup,	string_strdup,	char *,const char *,str);
RET_ARG_2(		stub_calloc,	stdlib_calloc,	void *,size_t,nelem,size_t,elsize);


static U32 _NotEnabled( struct AmyCLibIFace *Self UNUSED )
{
	IExec->DebugPrintF( "Function not enabled!\n" );
	(*(volatile int*)0) = 0;
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
/*   39 */	(PTR) stub_calloc,	// _generic_stdlib_calloc,
/*   40 */	(PTR) stub_malloc,	// _generic_stdlib_malloc,
/*   41 */	(PTR) stub_realloc,	// _generic_stdlib_realloc,
/*   42 */	(PTR) stub_free,	// _generic_stdlib_free,
/*   43 */	(PTR) _NotEnabled,	// _generic_stdlib_rand,
/*   44 */	(PTR) _NotEnabled,	// _generic_stdlib_rand_r,
/*   45 */	(PTR) _NotEnabled,	// _generic_stdlib_srand,
/*   46 */	(PTR) _NotEnabled,	// _generic_stdlib_atoi,
/*   47 */	(PTR) _NotEnabled,	// _generic_stdlib_strtol,
/*   48 */	(PTR) _generic_string_strlen,
/*   49 */	(PTR) _generic_string_strnlen,
/*   50 */	(PTR) stub_strdup,	// _generic_string_strdup,
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
/*   85 */	(PTR) _generic_stdio_vsprintf,
/*   86 */	(PTR) _NotEnabled,	// _generic_stdio_fputc_unlocked,
/*   87 */	(PTR) _generic_stdio_vsnprintf,
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
/*  125 */	(PTR) _generic_string_strcspn,
/*  126 */	(PTR) _generic_string_strspn,
/*  127 */	(PTR) _generic_string_strpbrk,
/*  128 */	(PTR) _generic_string_strchr,
/*  129 */	(PTR) _NotEnabled,	// _generic_stdio_fileno,
/*  130 */	(PTR) _NotEnabled,	// int AMYFUNC _generic_stdio_fprintf( struct AmyCLibIFace *Self, FILE *stream, const char *format, ... )
/*  131 */	(PTR) _NotEnabled,	// int AMYFUNC _generic_stdio_fputs( struct AmyCLibIFace *Self, const void *s, FILE *stream )
/*  132 */	(PTR) _NotEnabled,	// size_t AMYFUNC _generic_stdio_fwrite( struct AmyCLibIFace *Self, const void *ptr, size_t size, size_t nitems, FILE *stream )
/*  133 */	(PTR) _NotEnabled,	// int AMYFUNC _generic_stdio_putc( struct AmyCLibIFace *Self, int c, FILE *stream )
/*  134 */	(PTR) _NotEnabled,	// void AMYFUNC _generic_stdlib__exit( struct AmyCLibIFace *Self, int status )
/*  135 */	(PTR) _NotEnabled,	// long AMYFUNC _generic_stdlib_atol( struct AmyCLibIFace *Self, const char *str )
/*  136 */	(PTR) _NotEnabled,	// char * AMYFUNC _generic_stdlib_getenv( struct AmyCLibIFace *Self, const char *name )
/*  137 */	(PTR) _NotEnabled,	// void AMYFUNC _generic_stdlib_qsort( struct AmyCLibIFace *Self, void *base, size_t nel, size_t width, int (*compar)(const void *, const void *))
/*  138 */	(PTR) _NotEnabled,	// int AMYFUNC _generic_sys_stat_chmod( struct AmyCLibIFace *Self, const char *path, mode_t mode )
/*  139 */	(PTR) _NotEnabled,	// int AMYFUNC _generic_sys_stat_mkdir( struct AmyCLibIFace *Self, const char *path, mode_t mode )
/*  140 */	(PTR) _NotEnabled,	// char * AMYFUNC _generic_sys_stat_mktemp( struct AmyCLibIFace *Self, char *template )
/*  141 */	(PTR) _NotEnabled,	// int AMYFUNC _generic_sys_stat_stat( struct AmyCLibIFace *Self, const char *path, struct stat *buf )
/*  142 */	(PTR) _NotEnabled,	// char * AMYFUNC _generic_time_ctime( struct AmyCLibIFace *Self, const time_t *clock )
/*  143 */	(PTR) _NotEnabled,	// int AMYFUNC _generic_unistd_unlink( struct AmyCLibIFace *Self, const char *path )
/*  144 */	(PTR) _NotEnabled,	// char *AMYFUNC (*string_strncat)( struct AmyCLibIFace *Self, char *d, const char *s, size_t n );
/*  145 */	(PTR) _NotEnabled,	// int AMYFUNC (*stdio_vfprintf)( struct AmyCLibIFace *Self, FILE *stream, const char *format, va_list ap );
/*  146 */	(PTR) _NotEnabled,	// mode_t AMYFUNC (*sys_stat_umask)( struct AmyCLibIFace *Self, mode_t cmask );
/*  147 */	(PTR) _NotEnabled,	// pid_t AMYFUNC (*unistd_getpid)( struct AmyCLibIFace *Self );
/*  148 */	(PTR) _NotEnabled,	// char * AMYFUNC (*unistd_getcwd)( struct AmyCLibIFace *Self, char *buf, size_t size );
/*  149 */	(PTR) _NotEnabled,	// int AMYFUNC (*sys_stat_fstat)( struct AmyCLibIFace *Self, int fildes, struct stat *buf );
/*  150 */	(PTR) _NotEnabled,	// int AMYFUNC (*sys_stat_lstat)( struct AmyCLibIFace *Self, const char *path, struct stat *buf );
/*  151 */	(PTR) _NotEnabled,	// int AMYFUNC (*unistd_access)( struct AmyCLibIFace *Self, const char *path, int amode );
/*  152 */	(PTR) _NotEnabled,	// int AMYFUNC (*unistd_fcntl_ap)( struct AmyCLibIFace *Self, int fildes, int cmd, va_list ap );
/*  153 */	(PTR) _NotEnabled,	// ssize_t AMYFUNC (*unistd_read)( struct AmyCLibIFace *Self, int fildes, void *buf, size_t nbyte );
/*  154 */	(PTR) _NotEnabled,	// double AMYFUNC (*stdlib_atof)( struct AmyCLibIFace *Self, const char *str );
/*  155 */	(PTR) _NotEnabled,	// int AMYFUNC (*stdio_getc)( struct AmyCLibIFace *Self, FILE *stream );
/*  156 */	(PTR) _NotEnabled,	// int AMYFUNC (*utime_utime)( struct AmyCLibIFace *Self, const char *str, const struct utimbuf *buf );
/*  157 */	(PTR) _NotEnabled,	// int AMYFUNC (*unistd_link)( struct AmyCLibIFace *Self, const char *path1, const char *path2 );
/*  158 */	(PTR) _NotEnabled,	// int AMYFUNC (*unistd_isatty)( struct AmyCLibIFace *Self, int fildes );
/*  159 */	(PTR) _NotEnabled,	// void AMYFUNC (*stdio_perror)( struct AmyCLibIFace *Self, const char *s );
/*  160 */	(PTR) _NotEnabled,	// int AMYFUNC (*stdio_remove)( struct AmyCLibIFace *Self, const char *path );
/*  161 */	(PTR) _NotEnabled,	// int AMYFUNC (*stdio_rename)( struct AmyCLibIFace *Self, const char *old, const char *new );
/*  162 */	(PTR) _NotEnabled,	// int AMYFUNC (*unistd_rmdir)( struct AmyCLibIFace *Self, const char *path );
/*  163 */	(PTR) _NotEnabled,	// int AMYFUNC (*stdio_feof)( struct AmyCLibIFace *Self, FILE *stream );
/*  164 */	(PTR) _NotEnabled,	// char * AMYFUNC (*stdio_fgets)( struct AmyCLibIFace *Self, char *s, int n, FILE *stream );
/*  165 */	(PTR) _NotEnabled,	// void AMYFUNC (*stdio_rewind)( struct AmyCLibIFace *Self, FILE *stream );
/*  166 */	(PTR) _NotEnabled,	// int AMYFUNC (*stdio_vfscanf)( struct AmyCLibIFace *Self, FILE *stream, const char *format, va_list arg );
/*  167 */	(PTR) _NotEnabled,	// size_t AMYFUNC (*wchar_mbrtowc)( struct AmyCLibIFace *Self, wchar_t *pwc, const char *s, size_t n, mbstate_t *ps );
/*  168 */	(PTR) _NotEnabled,	// int AMYFUNC (*stdio_getchar)( struct AmyCLibIFace *Self );
/*  169 */	(PTR) _NotEnabled,	// char * AMYFUNC (*string_strstr)( struct AmyCLibIFace *Self, const char *s1, const char *s2 );
/*  170 */	(PTR) _NotEnabled,	// size_t AMYFUNC (*wchar_mbstowcs)( struct AmyCLibIFace *Self, wchar_t *pwcs, const char *s, size_t n );
/*  171 */	(PTR) _NotEnabled,	// uid_t AMYFUNC (*unistd_geteuid)( struct AmyCLibIFace *Self );
/*  172 */	(PTR) _NotEnabled,	// gid_t AMYFUNC (*unistd_getegid)( struct AmyCLibIFace *Self );
/*  173 */	(PTR) _NotEnabled,	// char * AMYFUNC (*locale_setlocale)( struct AmyCLibIFace *Self, int category, char *locale );
/*  174 */	(PTR) _NotEnabled,	// ssize_t AMYFUNC (*stdio_getline)( struct AmyCLibIFace *Self, char **lineptr, size_t *n, FILE *stream );
/*  175 */	(PTR) _NotEnabled,	// ssize_t AMYFUNC (*stdio_getdelim)( struct AmyCLibIFace *Self, char **lineptr, size_t *n, int delimiter, FILE *stream );
/*  176 */	(PTR) _NotEnabled,	// int AMYFUNC (*stdio_putc_unlocked)( struct AmyCLibIFace *Self, int c, FILE *stream );
/*  177 */	(PTR) _NotEnabled,	// int AMYFUNC _generic_ctype_isprint( struct AmyCLibIFace *Self, int c )
/*  178 */	(PTR) _NotEnabled,	// char * AMYFUNC _generic_string_strerror( struct AmyCLibIFace *Self, int errnum )
/*  179 */	(PTR) _NotEnabled,	// int AMYFUNC _generic_string_strerror_r( struct AmyCLibIFace *Self, int errnum, char *buf, size_t buflen )
/*  180 */	(PTR) _NotEnabled,	// int AMYFUNC _generic_sys_time_gettimeofday( struct AmyCLibIFace *Self, struct timeval *tp, void *tzp )
/*  181 */	(PTR) _NotEnabled,	// int AMYFUNC _generic_ctype_isascii( struct AmyCLibIFace *Self, int c )
/*  182 */	(PTR) _NotEnabled,	// char * AMYFUNC (*string_stpcpy)( struct AmyCLibIFace *Self, char *s1, const char *s2 );
/*  183 */	(PTR) _NotEnabled,	// int AMYFUNC (*ctype_isalnum)( struct AmyCLibIFace *Self, int c );
/*  184 */	(PTR) _NotEnabled,	// double AMYFUNC (*math_ceil)( struct AmyCLibIFace *Self, double x );
/*  185 */	(PTR) _NotEnabled,	// double AMYFUNC (*math_cos)( struct AmyCLibIFace *Self, double x );
/*  186 */	(PTR) _NotEnabled,	// double AMYFUNC (*math_sin)( struct AmyCLibIFace *Self, double x );
/*  187 */	(PTR) _NotEnabled,	// double AMYFUNC (*math_atan2)( struct AmyCLibIFace *Self, double y, double x );
/*  188 */	(PTR) _NotEnabled,	// double AMYFUNC (*math_fmod)( struct AmyCLibIFace *Self, double x, double y );
/*  189 */	(PTR) _NotEnabled,	// char * AMYFUNC (*string_strtok)( struct AmyCLibIFace *Self, char *s1, const char *s2 );
/*  190 */	(PTR) _NotEnabled,	// struct lconv * AMYFUNC (*locale_localeconv)( struct AmyCLibIFace *Self );
/*  191 */	(PTR) _NotEnabled,	// int AMYFUNC (*stdlib_mkstemp)( struct AmyCLibIFace *Self, char *template );
/*  192 */	(PTR) _NotEnabled,	// int AMYFUNC (*stdlib_atexit)( struct AmyCLibIFace *Self, void (*func)(void) );
/*  193 */	(PTR) _NotEnabled,	// int AMYFUNC (*unistd_getgroups)( struct AmyCLibIFace *Self, int gidsetsize, gid_t grouplist[] );
/*  194 */	(PTR) _NotEnabled,	// int AMYFUNC (*getopt_getopt)( struct AmyCLibIFace *Self, int argc, char * const argv[], const char *optstring );
/*  195 */	(PTR) _NotEnabled,	// int AMYFUNC (*getopt_getopt_long)( struct AmyCLibIFace *Self, int argc, char * const argv[], const char *optstring, const struct option *longopts, int *longindex );
/*  196 */	(PTR) _NotEnabled,	// int AMYFUNC (*dirent_closedir)( struct AmyCLibIFace *Self, DIR *dirp );
/*  197 */	(PTR) _NotEnabled,	// int AMYFUNC (*dirent_dirfd)( struct AmyCLibIFace *Self, DIR *dirp );
/*  198 */	(PTR) _NotEnabled,	// DIR * AMYFUNC (*dirent_opendir)( struct AmyCLibIFace *Self, const char *name );
/*  199 */	(PTR) _NotEnabled,	// struct dirent * AMYFUNC (*dirent_readdir)( struct AmyCLibIFace *Self, DIR *dirp );
/*  200 */	(PTR) _NotEnabled,	// struct group * AMYFUNC (*grp_getgrgid)( struct AmyCLibIFace *Self, gid_t aa );
/*  201 */	(PTR) _NotEnabled,	// struct group * AMYFUNC (*grp_getgrnam)( struct AmyCLibIFace *Self, const char *aa );
/*  202 */	(PTR) _NotEnabled,	// struct passwd * AMYFUNC (*pwd_getpwuid)( struct AmyCLibIFace *Self, uid_t aa );
/*  203 */	(PTR) _NotEnabled,	// int AMYFUNC (*unistd_chown)( struct AmyCLibIFace *Self, const char *aa, uid_t bb, gid_t cc );
/*  204 */	(PTR) _NotEnabled,	// char * AMYFUNC (*string_strrchr)( struct AmyCLibIFace *Self, const char *aa, int bb );
/*  205 */	(PTR) _NotEnabled,	// struct passwd * AMYFUNC (*pwd_getpwnam)( struct AmyCLibIFace *Self, const char *aa );
/*  206 */	(PTR) _NotEnabled,	// int AMYFUNC (*stdio_getchar_unlocked)( struct AmyCLibIFace *Self );
/*  207 */	(PTR) _NotEnabled,	// int AMYFUNC (*stdio_putchar_unlocked)( struct AmyCLibIFace *Self, int c );
/*  208 */	(PTR) _NotEnabled,	// off_t AMYFUNC (*unistd_lseek)( struct AmyCLibIFace *Self, int, off_t, int );
/*  209 */	(PTR) _NotEnabled,	// ssize_t AMYFUNC (*unistd_write)( struct AmyCLibIFace *Self, int, const void *, size_t );
/*  210 */	(PTR) _NotEnabled,	// int AMYFUNC (*unistd_symlink)( struct AmyCLibIFace *Self, const char *, const char * );
/*  211 */	(PTR) _NotEnabled,	// int AMYFUNC (*time_clock_gettime)( struct AmyCLibIFace *Self, clockid_t, struct timespec * );
/*  212 */	(PTR) _NotEnabled,	// int AMYFUNC (*time_clock_settime)( struct AmyCLibIFace *Self, clockid_t, const struct timespec * );
/*  213 */	(PTR) _NotEnabled,	// int AMYFUNC (*unistd_gethostname)( struct AmyCLibIFace *Self, char *, size_t );
/*  214 */	(PTR) _NotEnabled,	// void * AMYFUNC (*string_memrchr)( struct AmyCLibIFace *Self, const void *, int, size_t );
/*  215 */	(PTR) _NotEnabled,	// time_t AMYFUNC (*time_mktime)( struct AmyCLibIFace *Self, struct tm * );
/*  216 */	(PTR) _NotEnabled,	// long long AMYFUNC (*stdlib_strtoll)( struct AmyCLibIFace *Self, const char *, char **, int );







	(PTR) -1
};

const struct TagItem Main_Tags[] =
{
	{ MIT_Name,				(Tag) "main"		},
	{ MIT_VectorTable,		(Tag) Main_Vectors	},
	{ MIT_DataSize,			(Tag) sizeof( struct libData ) },
	{ MIT_Flags,			(Tag) IFLF_PRIVATE	},
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
