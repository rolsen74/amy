
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

enum CPUType
{
	CPUType_Any = 0,	// End Marker and Fallback Function
};

struct EnableFunc
{
	enum CPUType		CPUType;	// 0 = Fallback function and EndMarker
	PTR					CPUFunc;
};

struct EnableStruct
{
	U32					Offset;
	U32					Mask;		// EM_STRING | EM_FILE
	struct EnableFunc *	Funcs;
};

void _generic__Priv_Mem_Alloc( void );
void _generic__Priv_Mem_Free( void );
void _generic__Priv_Mem_Realloc( void );
void _generic__Priv_Mem_CreatePool( void );
void _generic__Priv_Mem_DeletePool( void );
void _generic__Priv_Mem_FlushPool( void );
void _generic__Priv_Mem_AllocPooled( void );
void _generic__Priv_Mem_FreePooled( void );
void _generic__Priv_Check_Abort( void );
void _generic__Priv_Convert_Time_to_TM( void );
void _generic__Priv_Convert_ED_to_Stat( void );
void _generic__Priv_Convert_DS_to_Time( void );
void _generic__Priv_Convert_IOErr_to_ErrNo( void );
void _generic__Priv_FB_Read( void );
void _generic__Priv_FB_Read_Fill_Buffer( void );
void _generic__Priv_FB_Read_Drop_Buffer( void );
void _generic__Priv_FB_Write( void );
void _generic__Priv_FB_Write_Flush_Buffer( void );
void _generic__Priv_FB_Write_Flush_Buffer2( void );
void _generic__Priv_FD_Alloc( void );
void _generic__Priv_FD_Free( void );
void _generic__Priv_FD_Init( void );
void _generic__Priv_FD_Init_Struct( void );
void _generic__Priv_FD_Array_Insert( void );
void _generic__Priv_FD_Array_Remove( void );
void _generic__Priv_FDLockNr( void );
void _generic__Priv_FDLockStream( void );
void _generic__Priv_FDUnlock( void );
void _generic__Priv_Print( void );
void _generic__Priv_Scan( void );

void _generic_assert_assert( void );

void _locale_ctype_isalpha( void );
void _locale_ctype_isdigit( void );
void _locale_ctype_isspace( void );
void _locale_ctype_isupper( void );
void _locale_ctype_isxdigit( void );
void _locale_ctype_tolower( void );
void _locale_ctype_toupper( void );
//void _locale_ctype_islower( void );

// void _generic_string_strlen( void );
// void _generic_string_strnlen( void );
void _generic_string_strdup( void );
void _generic_string_strndup( void );
// void _generic_string_strcpy( void );
// void _generic_string_strncpy( void );
void _generic_string_strcat( void );
// void _generic_string_memcmp( void );
// void _generic_string_memmove( void );
// void _generic_string_memcpy( void );
// void _generic_string_memset( void );
// void _generic_string_strcmp( void );
// void _generic_string_strncmp( void );

// void _generic_strings_bzero( void );
void _generic_strings_strcasecmp( void );
void _generic_strings_strncasecmp( void );

void _generic_stdlib__Exit( void );
void _generic_stdlib_abort( void );
void _generic_stdlib_atoi( void );
void _generic_stdlib_calloc( void );
void _generic_stdlib_exit( void );
void _generic_stdlib_free( void );
void _generic_stdlib_strtof( void );
void _generic_stdlib_strtod( void );
void _generic_stdlib_malloc( void );
void _generic_stdlib_realloc( void );
void _generic_stdlib_rand( void );
void _generic_stdlib_rand_r( void );
void _generic_stdlib_srand( void );
void _generic_stdlib_strtol( void );

void _generic_stdio_fopen( void );
void _generic_stdio_ftell( void );
void _generic_stdio_fgetpos( void );
void _generic_stdio_flockfile( void );
void _generic_stdio_funlockfile( void );
void _generic_stdio_fflush( void );
void _generic_stdio_ferror( void );
void _generic_stdio_fileno( void );
void _generic_stdio_puts( void );
void _generic_stdio_putchar( void );
void _generic_stdio_fputc( void );
void _generic_stdio_fputc_unlocked( void );
void _generic_stdio_setvbuf( void );
void _generic_stdio_fclose( void );
void _generic_stdio_fseek( void );
void _generic_stdio_fseeko( void );
void _generic_stdio_vprintf( void );
//void _generic_stdio_sprintf( void );
//void _generic_stdio_snprintf( void );
void _generic_stdio_vsprintf( void );
void _generic_stdio_vsnprintf( void );
void _generic_stdio_ungetc( void );
void _generic_stdio_fread( void );
void _generic_stdio_clearerr( void );
void _generic_stdio_vsscanf( void );
void _generic_stdio_vasprintf( void );
void _generic_stdio_fgetc( void );
void _generic_stdio_ungetc( void );

void _generic_setjmp_longjmp( void );
void _generic_setjmp_setjmp( void );

void _generic_time_localtime( void );
void _generic_time_time( void );
void _generic_time_strftime( void );

void _generic_fcntl_open( void );

void _generic_unistd_close( void );

void _generic_inttypes_strtoumax( void );
void _generic_inttypes_strtoimax( void );

void _generic_math_d__get_huge_val( void );
void _generic_math_d__inf( void );
void _generic_math_d__isinf( void );
void _generic_math_d__isnan( void );
void _generic_math_d_nan( void );
void _generic_math_d_pow( void );
void _generic_math_d_fabs( void );
void _generic_math_d_scalbn( void );
void _generic_math_d_sqrt( void );
void _generic_math_d_copysign( void );

void _generic_signal_signal( void );
void _generic_signal_raise( void );


// --
struct EnableFunc  __Mem_Alloc[] =				{{ CPUType_Any, _generic__Priv_Mem_Alloc }};
struct EnableFunc  __Mem_Free[] =				{{ CPUType_Any, _generic__Priv_Mem_Free }};
struct EnableFunc  __Mem_Realloc[] =			{{ CPUType_Any, _generic__Priv_Mem_Realloc }};
struct EnableFunc  __Mem_CreatePool[] =			{{ CPUType_Any, _generic__Priv_Mem_CreatePool }};
struct EnableFunc  __Mem_DeletePool[] =			{{ CPUType_Any, _generic__Priv_Mem_DeletePool }};
struct EnableFunc  __Mem_FlushPool[] =			{{ CPUType_Any, _generic__Priv_Mem_FlushPool }};
struct EnableFunc  __Mem_AllocPooled[] =		{{ CPUType_Any, _generic__Priv_Mem_AllocPooled }};
struct EnableFunc  __Mem_FreePooled[] =			{{ CPUType_Any, _generic__Priv_Mem_FreePooled }};
struct EnableFunc  __Check_Abort[] =			{{ CPUType_Any, _generic__Priv_Check_Abort }};
struct EnableFunc  __Convert_Time_to_TM[] =		{{ CPUType_Any, _generic__Priv_Convert_Time_to_TM }};
struct EnableFunc  __Convert_ED_to_Stat[] =		{{ CPUType_Any, _generic__Priv_Convert_ED_to_Stat }};
struct EnableFunc  __Convert_DS_to_Time[] =		{{ CPUType_Any, _generic__Priv_Convert_DS_to_Time }};
struct EnableFunc  __Convert_IOErr_to_ErrNo[] =	{{ CPUType_Any, _generic__Priv_Convert_IOErr_to_ErrNo }};
struct EnableFunc  __FB_Read[] =				{{ CPUType_Any, _generic__Priv_FB_Read }};
struct EnableFunc  __FB_Read_Fill_Buffer[] =	{{ CPUType_Any, _generic__Priv_FB_Read_Fill_Buffer }};
struct EnableFunc  __FB_Read_Drop_Buffer[] =	{{ CPUType_Any, _generic__Priv_FB_Read_Drop_Buffer }};
struct EnableFunc  __FB_Write[] =				{{ CPUType_Any, _generic__Priv_FB_Write }};
struct EnableFunc  __FB_Write_Flush_Buffer[] =	{{ CPUType_Any, _generic__Priv_FB_Write_Flush_Buffer }};
struct EnableFunc  __FB_Write_Flush_Buffer2[] =	{{ CPUType_Any, _generic__Priv_FB_Write_Flush_Buffer2 }};
struct EnableFunc  __FD_Alloc[] =				{{ CPUType_Any, _generic__Priv_FD_Alloc }};
struct EnableFunc  __FD_Free[] =				{{ CPUType_Any, _generic__Priv_FD_Free }};
struct EnableFunc  __FD_Init[] =				{{ CPUType_Any, _generic__Priv_FD_Init }};
struct EnableFunc  __FD_Init_Struct[] =			{{ CPUType_Any, _generic__Priv_FD_Init_Struct }};
struct EnableFunc  __FD_Array_Insert[] =		{{ CPUType_Any, _generic__Priv_FD_Array_Insert }};
struct EnableFunc  __FD_Array_Remove[] =		{{ CPUType_Any, _generic__Priv_FD_Array_Remove }};
struct EnableFunc  __FDLockNr[] =				{{ CPUType_Any, _generic__Priv_FDLockNr }};
struct EnableFunc  __FDLockStream[] =			{{ CPUType_Any, _generic__Priv_FDLockStream }};
struct EnableFunc  __FDUnlock[] =				{{ CPUType_Any, _generic__Priv_FDUnlock }};
struct EnableFunc  __Print[] =					{{ CPUType_Any, _generic__Priv_Print }};
struct EnableFunc  __Scan[] =					{{ CPUType_Any, _generic__Priv_Scan }};
// --
// struct EnableFunc  __strlen[] =				{{ CPUType_Any, _generic_string_strlen }};
// struct EnableFunc  __strnlen[] =				{{ CPUType_Any, _generic_string_strnlen }};
struct EnableFunc  __strdup[] =					{{ CPUType_Any, _generic_string_strdup }};
struct EnableFunc  __strndup[] =				{{ CPUType_Any, _generic_string_strndup }};
// struct EnableFunc  __strcpy[] =				{{ CPUType_Any, _generic_string_strcpy }};
// struct EnableFunc  __strncpy[] =				{{ CPUType_Any, _generic_string_strncpy }};
struct EnableFunc  __strcat[] =					{{ CPUType_Any, _generic_string_strcat }};
// struct EnableFunc  __strcmp[] =				{{ CPUType_Any, _generic_string_strcmp }};
// struct EnableFunc  __strncmp[] =				{{ CPUType_Any, _generic_string_strncmp }};
// struct EnableFunc  __memcmp[] =				{{ CPUType_Any, _generic_string_memcmp }};
// struct EnableFunc  __memmove[] =				{{ CPUType_Any, _generic_string_memmove }};
// struct EnableFunc  __memcpy[] =				{{ CPUType_Any, _generic_string_memcpy }};
// struct EnableFunc  __memset[] =				{{ CPUType_Any, _generic_string_memset }};
// --
struct EnableFunc  __stdio_fopen[] =			{{ CPUType_Any, _generic_stdio_fopen }};
struct EnableFunc  __stdio_ftell[] =			{{ CPUType_Any, _generic_stdio_ftell }};
struct EnableFunc  __stdio_fgetpos[] =			{{ CPUType_Any, _generic_stdio_fgetpos }};
struct EnableFunc  __stdio_flockfile[] =		{{ CPUType_Any, _generic_stdio_flockfile }};
struct EnableFunc  __stdio_funlockfile[] =		{{ CPUType_Any, _generic_stdio_funlockfile }};
struct EnableFunc  __stdio_fflush[] =			{{ CPUType_Any, _generic_stdio_fflush }};
struct EnableFunc  __stdio_puts[] =				{{ CPUType_Any, _generic_stdio_puts }};
struct EnableFunc  __stdio_putchar[] =			{{ CPUType_Any, _generic_stdio_putchar }};
struct EnableFunc  __stdio_fputc[] =			{{ CPUType_Any, _generic_stdio_fputc }};
struct EnableFunc  __stdio_fputc_unlocked[] =	{{ CPUType_Any, _generic_stdio_fputc_unlocked }};
struct EnableFunc  __stdio_setvbuf[] =			{{ CPUType_Any, _generic_stdio_setvbuf }};
struct EnableFunc  __stdio_fclose[] =			{{ CPUType_Any, _generic_stdio_fclose }};
struct EnableFunc  __stdio_fseek[] =			{{ CPUType_Any, _generic_stdio_fseek }};
struct EnableFunc  __stdio_fseeko[] =			{{ CPUType_Any, _generic_stdio_fseeko }};
struct EnableFunc  __stdio_vprintf[] =			{{ CPUType_Any, _generic_stdio_vprintf }};
// struct EnableFunc  __sprintf[] =				{{ CPUType_Any, _generic_stdio_sprintf }};
// struct EnableFunc  __snprintf[] =			{{ CPUType_Any, _generic_stdio_snprintf }};
struct EnableFunc  __stdio_vsprintf[] =			{{ CPUType_Any, _generic_stdio_vsprintf }};
struct EnableFunc  __stdio_vsnprintf[] =		{{ CPUType_Any, _generic_stdio_vsnprintf }};
struct EnableFunc  __stdio_ungetc[] =			{{ CPUType_Any, _generic_stdio_ungetc }};
struct EnableFunc  __stdio_fread[] =			{{ CPUType_Any, _generic_stdio_fread }};
struct EnableFunc  __stdio_clearerr[] =			{{ CPUType_Any, _generic_stdio_clearerr }};
struct EnableFunc  __stdio_fgetc[] =			{{ CPUType_Any, _generic_stdio_fgetc }};
struct EnableFunc  __stdio_ferror[] =			{{ CPUType_Any, _generic_stdio_ferror }};
struct EnableFunc  __stdio_fileno[] =			{{ CPUType_Any, _generic_stdio_fileno }};
// --
struct EnableFunc  __setjmp_longjmp[] =			{{ CPUType_Any, _generic_setjmp_longjmp }};
struct EnableFunc  __setjmp_setjmp[] =			{{ CPUType_Any, _generic_setjmp_setjmp }};
// --
struct EnableFunc  __stdlib_calloc[] =			{{ CPUType_Any, _generic_stdlib_calloc }};
struct EnableFunc  __stdlib_malloc[] =			{{ CPUType_Any, _generic_stdlib_malloc }};
struct EnableFunc  __stdlib_realloc[] =			{{ CPUType_Any, _generic_stdlib_realloc }};
struct EnableFunc  __stdlib_free[] =			{{ CPUType_Any, _generic_stdlib_free }};
struct EnableFunc  __stdlib_rand[] =			{{ CPUType_Any, _generic_stdlib_rand }};
struct EnableFunc  __stdlib_rand_r[] =			{{ CPUType_Any, _generic_stdlib_rand_r }};
struct EnableFunc  __stdlib_srand[] =			{{ CPUType_Any, _generic_stdlib_srand }};
struct EnableFunc  __stdlib_atoi[] =			{{ CPUType_Any, _generic_stdlib_atoi }};
struct EnableFunc  __stdlib_strtol[] =			{{ CPUType_Any, _generic_stdlib_strtol }};
// --
struct EnableFunc  __assert_assert[] =			{{ CPUType_Any, _generic_assert_assert }};
// --
struct EnableFunc  __ctype_isalpha[] =			{{ CPUType_Any, _locale_ctype_isalpha }};
struct EnableFunc  __ctype_isdigit[] =			{{ CPUType_Any, _locale_ctype_isdigit }};
struct EnableFunc  __ctype_isspace[] =			{{ CPUType_Any, _locale_ctype_isspace }};
struct EnableFunc  __ctype_isupper[] =			{{ CPUType_Any, _locale_ctype_isupper }};
struct EnableFunc  __ctype_isxdigit[] =			{{ CPUType_Any, _locale_ctype_isxdigit }};
struct EnableFunc  __ctype_tolower[] =			{{ CPUType_Any, _locale_ctype_tolower }};
struct EnableFunc  __ctype_toupper[] =			{{ CPUType_Any, _locale_ctype_toupper }};
// struct EnableFunc  __ctype_islower[] =			{{ CPUType_Any, _locale_ctype_islower }};
// --
struct EnableFunc  __fcntl_open[] =				{{ CPUType_Any, _generic_fcntl_open }};
// --
struct EnableFunc  __inttypes_strtoumax[] =		{{ CPUType_Any, _generic_inttypes_strtoumax }};
struct EnableFunc  __inttypes_strtoimax[] =		{{ CPUType_Any, _generic_inttypes_strtoimax }};
// --
struct EnableFunc  __math_d__get_huge_val[] =	{{ CPUType_Any, _generic_math_d__get_huge_val }};
struct EnableFunc  __math_d__inf[] =			{{ CPUType_Any, _generic_math_d__inf }};
struct EnableFunc  __math_d__isinf[] =			{{ CPUType_Any, _generic_math_d__isinf }};
struct EnableFunc  __math_d__isnan[] =			{{ CPUType_Any, _generic_math_d__isnan }};
struct EnableFunc  __math_d_nan[] =				{{ CPUType_Any, _generic_math_d_nan }};
struct EnableFunc  __math_d_pow[] =				{{ CPUType_Any, _generic_math_d_pow }};
struct EnableFunc  __math_d_fabs[] =			{{ CPUType_Any, _generic_math_d_fabs }};
struct EnableFunc  __math_d_scalbn[] =			{{ CPUType_Any, _generic_math_d_scalbn }};
struct EnableFunc  __math_d_sqrt[] =			{{ CPUType_Any, _generic_math_d_sqrt }};
struct EnableFunc  __math_d_copysign[] =		{{ CPUType_Any, _generic_math_d_copysign }};
// --
struct EnableFunc  __stdlib__Exit[] =			{{ CPUType_Any, _generic_stdlib__Exit }};
struct EnableFunc  __stdlib_abort[] =			{{ CPUType_Any, _generic_stdlib_abort }};
struct EnableFunc  __stdlib_exit[] =			{{ CPUType_Any, _generic_stdlib_exit }};
struct EnableFunc  __stdlib_strtof[] =			{{ CPUType_Any, _generic_stdlib_strtof }};
struct EnableFunc  __stdlib_strtod[] =			{{ CPUType_Any, _generic_stdlib_strtod }};
// --
struct EnableFunc  __stdio_vasprintf[] =		{{ CPUType_Any, _generic_stdio_vasprintf }};
struct EnableFunc  __stdio_vsscanf[] =			{{ CPUType_Any, _generic_stdio_vsscanf }};
// --
// --
struct EnableFunc  __strings_strcasecmp[] =		{{ CPUType_Any, _generic_strings_strcasecmp }};
struct EnableFunc  __strings_strncasecmp[] =	{{ CPUType_Any, _generic_strings_strncasecmp }};
// --
struct EnableFunc  __time_localtime[] =			{{ CPUType_Any, _generic_time_localtime }};
struct EnableFunc  __time_time[] =				{{ CPUType_Any, _generic_time_time }};
// --
struct EnableFunc  __unistd_close[] =			{{ CPUType_Any, _generic_unistd_close }};
// --




// struct EnableFunc  __time_strftime[] =			{{ CPUType_Any, _generic_time_strftime }};
struct EnableFunc  __signal_signal[] =			{{ CPUType_Any, _generic_signal_signal }};
struct EnableFunc  __signal_raise[] =			{{ CPUType_Any, _generic_signal_raise }};


// --


// --
#if 0
	EM_MEMORY:
		stdlib_calloc
		stdlib_malloc
		stdlib_realloc
		stdlib_free
		string_strdup
		string_strndup
		stdio_vasprintf

	EM_STRING:
		string_strlen
		string_strnlen
		string_strcpy
		string_strncpy
		string_strcmp
		string_strncmp
		--string_memcmp
		--string_memmove
		--string_memcpy
		--string_memset
		string_strcat
		strings_bzero
		strings_strcasecmp
		strings_strncasecmp
		inttypes_strtoumax
		inttypes_strtoimax

	EM_FILE:
		stdio_fopen
		stdio_ftell
		stdio_fgetpos
		stdio_flockfile
		stdio_funlockfile
		stdio_fflush
		stdio_puts
		stdio_putchar
		stdio_fputc
		stdio_setvbuf
		stdio_fclose
		stdio_fseek
		stdio_fseeko
		stdio_vprintf
		stdio_sprintf
		stdio_snprintf
		stdio_vsnprintf
		unistd_close
		stdio_ungetc
		stdio_fread
		stdio_clearerr
		fcntl_open
		stdio_ferror

	EM_LOCALE:
		__ctype_tolower
		__ctype_toupper
/*   62 */ { offsetof( struct AmyCLibPrivIFace, ctype_isalpha ), EM_ALWAYS, __ctype_isalpha },
/*   63 */ { offsetof( struct AmyCLibPrivIFace, ctype_isdigit ), EM_ALWAYS, __ctype_isdigit },
/*   64 */ { offsetof( struct AmyCLibPrivIFace, ctype_isspace ), EM_ALWAYS, __ctype_isspace },
/*   65 */ { offsetof( struct AmyCLibPrivIFace, ctype_isupper ), EM_ALWAYS, __ctype_isupper },
/*   66 */ { offsetof( struct AmyCLibPrivIFace, ctype_isxdigit ), EM_ALWAYS, __ctype_isxdigit },
/*  118 */ { offsetof( struct AmyCLibPrivIFace, ctype_islower ), EM_ALWAYS, __ctype_islower },

	EM_ALWAYS:

/*   37 */ { offsetof( struct AmyCLibPrivIFace, setjmp_longjmp ), EM_ALWAYS, __setjmp_longjmp },
/*   38 */ { offsetof( struct AmyCLibPrivIFace, setjmp_setjmp ), EM_ALWAYS, __setjmp_setjmp },
/*   43 */ { offsetof( struct AmyCLibPrivIFace, stdlib_rand ), EM_ALWAYS, __stdlib_rand },
/*   44 */ { offsetof( struct AmyCLibPrivIFace, stdlib_rand_r ), EM_ALWAYS, __stdlib_rand_r },
/*   45 */ { offsetof( struct AmyCLibPrivIFace, stdlib_srand ), EM_ALWAYS, __stdlib_srand },
/*   46 */ { offsetof( struct AmyCLibPrivIFace, stdlib_atoi ), EM_ALWAYS, __stdlib_atoi },
/*   47 */ { offsetof( struct AmyCLibPrivIFace, stdlib_strtol ), EM_ALWAYS, __stdlib_strtol },
/*   69 */ { offsetof( struct AmyCLibPrivIFace, time_localtime ), EM_ALWAYS, __time_localtime },
/*   70 */ { offsetof( struct AmyCLibPrivIFace, time_time ), EM_ALWAYS, __time_time },
/*   92 */ { offsetof( struct AmyCLibPrivIFace, stdlib_strtof ), EM_ALWAYS, __stdlib_strtof },
/*   93 */ { offsetof( struct AmyCLibPrivIFace, stdlib_strtod ), EM_ALWAYS, __stdlib_strtod },
/*   99 */ { offsetof( struct AmyCLibPrivIFace, math_d__get_huge_val ), EM_ALWAYS, __math_d__get_huge_val },
/*  100 */ { offsetof( struct AmyCLibPrivIFace, math_d__inf ), EM_ALWAYS, __math_d__inf },
/*  101 */ { offsetof( struct AmyCLibPrivIFace, math_d__isinf ), EM_ALWAYS, __math_d__isinf },
/*  102 */ { offsetof( struct AmyCLibPrivIFace, math_d__isnan ), EM_ALWAYS, __math_d__isnan },
/*  103 */ { offsetof( struct AmyCLibPrivIFace, math_d_nan ), EM_ALWAYS, __math_d_nan },
/*  104 */ { offsetof( struct AmyCLibPrivIFace, math_d_pow ), EM_ALWAYS, __math_d_pow },
/*  105 */ { offsetof( struct AmyCLibPrivIFace, math_d_fabs ), EM_ALWAYS, __math_d_fabs },
/*  106 */ { offsetof( struct AmyCLibPrivIFace, math_d_scalbn ), EM_ALWAYS, __math_d_scalbn },
/*  107 */ { offsetof( struct AmyCLibPrivIFace, math_d_sqrt ), EM_ALWAYS, __math_d_sqrt },
/*  108 */ { offsetof( struct AmyCLibPrivIFace, math_d_copysign ), EM_ALWAYS, __math_d_copysign },
/*  109 */ { offsetof( struct AmyCLibPrivIFace, stdio_vsscanf ), EM_ALWAYS, __stdio_vsscanf },
/*  110 */ { offsetof( struct AmyCLibPrivIFace, time_strftime ), EM_ALWAYS, __time_strftime },
/*  111 */ { offsetof( struct AmyCLibPrivIFace, signal_signal ), EM_ALWAYS, __signal_signal },
/*  112 */ { offsetof( struct AmyCLibPrivIFace, signal_raise ), EM_ALWAYS, __signal_raise },
/*  113 */ { offsetof( struct AmyCLibPrivIFace, stdlib_abort ), EM_ALWAYS, __stdlib_abort },
/*  114 */ { offsetof( struct AmyCLibPrivIFace, stdlib__Exit ), EM_ALWAYS, __stdlib__Exit },
/*  115 */ (PTR) _NotEnabled,	// _generic_stdio_vasprintf
/*  116 */ (PTR) _NotEnabled,	// _generic_assert_assert
/*  117 */ (PTR) _NotEnabled,	// _generic_stdlib_exit


#endif
// --

struct EnableStruct funcs[] =
{
/*    7 */ { offsetof( struct AmyCLibPrivIFace, Priv_Mem_Alloc ), EM_MEMORY, __Mem_Alloc },
/*    8 */ { offsetof( struct AmyCLibPrivIFace, Priv_Mem_Free ), EM_MEMORY, __Mem_Free },
/*    9 */ { offsetof( struct AmyCLibPrivIFace, Priv_Mem_Realloc ), EM_MEMORY, __Mem_Realloc },
/*   10 */ { offsetof( struct AmyCLibPrivIFace, Priv_Mem_CreatePool ), EM_MEMORY, __Mem_CreatePool },
/*   11 */ { offsetof( struct AmyCLibPrivIFace, Priv_Mem_DeletePool ), EM_MEMORY, __Mem_DeletePool },
/*   12 */ { offsetof( struct AmyCLibPrivIFace, Priv_Mem_FlushPool ), EM_MEMORY, __Mem_FlushPool },
/*   13 */ { offsetof( struct AmyCLibPrivIFace, Priv_Mem_AllocPooled ), EM_MEMORY, __Mem_AllocPooled },
/*   14 */ { offsetof( struct AmyCLibPrivIFace, Priv_Mem_FreePooled ), EM_MEMORY, __Mem_FreePooled },
/*   15 */ { offsetof( struct AmyCLibPrivIFace, Priv_Check_Abort ), EM_ALWAYS, __Check_Abort },
/*   16 */ { offsetof( struct AmyCLibPrivIFace, Priv_Convert_Time_to_TM ), EM_ALWAYS, __Convert_Time_to_TM },
/*   17 */ { offsetof( struct AmyCLibPrivIFace, Priv_Convert_ED_to_Stat ), EM_ALWAYS, __Convert_ED_to_Stat },
/*   18 */ { offsetof( struct AmyCLibPrivIFace, Priv_Convert_DS_to_Time ), EM_ALWAYS, __Convert_DS_to_Time },
/*   19 */ { offsetof( struct AmyCLibPrivIFace, Priv_Convert_IOErr_to_ErrNo ), EM_ALWAYS, __Convert_IOErr_to_ErrNo },
/*   20 */ { offsetof( struct AmyCLibPrivIFace, Priv_FB_Read ), EM_ALWAYS, __FB_Read },
/*   21 */ { offsetof( struct AmyCLibPrivIFace, Priv_FB_Read_Fill_Buffer ), EM_ALWAYS, __FB_Read_Fill_Buffer },
/*   22 */ { offsetof( struct AmyCLibPrivIFace, Priv_FB_Read_Drop_Buffer ), EM_ALWAYS, __FB_Read_Drop_Buffer },
/*   23 */ { offsetof( struct AmyCLibPrivIFace, Priv_FB_Write ), EM_ALWAYS, __FB_Write },
/*   24 */ { offsetof( struct AmyCLibPrivIFace, Priv_FB_Write_Flush_Buffer ), EM_ALWAYS, __FB_Write_Flush_Buffer },
/*   25 */ { offsetof( struct AmyCLibPrivIFace, Priv_FB_Write_Flush_Buffer2 ), EM_ALWAYS, __FB_Write_Flush_Buffer2 },
/*   26 */ { offsetof( struct AmyCLibPrivIFace, Priv_FD_Alloc ), EM_ALWAYS, __FD_Alloc },
/*   27 */ { offsetof( struct AmyCLibPrivIFace, Priv_FD_Free ), EM_ALWAYS, __FD_Free },
/*   28 */ { offsetof( struct AmyCLibPrivIFace, Priv_FD_Init ), EM_ALWAYS, __FD_Init },
/*   29 */ { offsetof( struct AmyCLibPrivIFace, Priv_FD_Init_Struct ), EM_ALWAYS, __FD_Init_Struct },
/*   30 */ { offsetof( struct AmyCLibPrivIFace, Priv_FD_Array_Insert ), EM_ALWAYS, __FD_Array_Insert },
/*   31 */ { offsetof( struct AmyCLibPrivIFace, Priv_FD_Array_Remove ), EM_ALWAYS, __FD_Array_Remove },
/*   32 */ { offsetof( struct AmyCLibPrivIFace, Priv_FDLockNr ), EM_ALWAYS, __FDLockNr },
/*   33 */ { offsetof( struct AmyCLibPrivIFace, Priv_FDLockStream ), EM_ALWAYS, __FDLockStream },
/*   34 */ { offsetof( struct AmyCLibPrivIFace, Priv_FDUnlock ), EM_ALWAYS, __FDUnlock },
/*   35 */ { offsetof( struct AmyCLibPrivIFace, Priv_Print ), EM_ALWAYS, __Print },
/*   36 */ { offsetof( struct AmyCLibPrivIFace, Priv_Scan ), EM_ALWAYS, __Scan },
/*   37 */ { offsetof( struct AmyCLibPrivIFace, setjmp_longjmp ), EM_ALWAYS, __setjmp_longjmp },
/*   38 */ { offsetof( struct AmyCLibPrivIFace, setjmp_setjmp ), EM_ALWAYS, __setjmp_setjmp },
/*   39 */ { offsetof( struct AmyCLibPrivIFace, stdlib_calloc ), EM_MEMORY, __stdlib_calloc },
/*   40 */ { offsetof( struct AmyCLibPrivIFace, stdlib_malloc ), EM_MEMORY, __stdlib_malloc },
/*   41 */ { offsetof( struct AmyCLibPrivIFace, stdlib_realloc ), EM_MEMORY, __stdlib_realloc },
/*   42 */ { offsetof( struct AmyCLibPrivIFace, stdlib_free ), EM_MEMORY, __stdlib_free },
/*   43 */ { offsetof( struct AmyCLibPrivIFace, stdlib_rand ), EM_ALWAYS, __stdlib_rand },
/*   44 */ { offsetof( struct AmyCLibPrivIFace, stdlib_rand_r ), EM_ALWAYS, __stdlib_rand_r },
/*   45 */ { offsetof( struct AmyCLibPrivIFace, stdlib_srand ), EM_ALWAYS, __stdlib_srand },
/*   46 */ { offsetof( struct AmyCLibPrivIFace, stdlib_atoi ), EM_ALWAYS, __stdlib_atoi },
/*   47 */ { offsetof( struct AmyCLibPrivIFace, stdlib_strtol ), EM_ALWAYS, __stdlib_strtol },
/*   48 */ // { offsetof( struct AmyCLibPrivIFace, string_strlen ), EM_STRING, __strlen },
/*   49 */ // { offsetof( struct AmyCLibPrivIFace, string_strnlen ), EM_STRING, __strnlen },
/*   50 */ { offsetof( struct AmyCLibPrivIFace, string_strdup ), EM_MEMORY, __strdup },
/*   51 */ { offsetof( struct AmyCLibPrivIFace, string_strndup ), EM_MEMORY, __strndup },
/*   52 */ // { offsetof( struct AmyCLibPrivIFace, string_strcpy ), EM_STRING, __strcpy },
/*   53 */ // { offsetof( struct AmyCLibPrivIFace, string_strncpy ), EM_STRING, __strncpy },
/*   54 */ // { offsetof( struct AmyCLibPrivIFace, string_strcmp ), EM_STRING, __strcmp },
/*   55 */ // { offsetof( struct AmyCLibPrivIFace, string_strncmp ), EM_STRING, __strncmp },
/*   56 */ // { offsetof( struct AmyCLibPrivIFace, string_memcmp ), EM_STRING, __memcmp },
/*   57 */ // { offsetof( struct AmyCLibPrivIFace, string_memmove ), EM_STRING, __memmove },
/*   58 */ // { offsetof( struct AmyCLibPrivIFace, string_memcpy ), EM_STRING, __memcpy },
/*   59 */ // { offsetof( struct AmyCLibPrivIFace, string_memset ), EM_STRING, __memset },
/*   60 */ { offsetof( struct AmyCLibPrivIFace, string_strcat ), EM_STRING, __strcat },
/*   61 */ // { offsetof( struct AmyCLibPrivIFace, strings_bzero ), EM_ALWAYS, __strings_bzero },
/*   62 */ { offsetof( struct AmyCLibPrivIFace, ctype_isalpha ), EM_LOCALE, __ctype_isalpha },
/*   63 */ { offsetof( struct AmyCLibPrivIFace, ctype_isdigit ), EM_LOCALE, __ctype_isdigit },
/*   64 */ { offsetof( struct AmyCLibPrivIFace, ctype_isspace ), EM_LOCALE, __ctype_isspace },
/*   65 */ { offsetof( struct AmyCLibPrivIFace, ctype_isupper ), EM_LOCALE, __ctype_isupper },
/*   66 */ { offsetof( struct AmyCLibPrivIFace, ctype_isxdigit ), EM_LOCALE, __ctype_isxdigit },
/*   67 */ { offsetof( struct AmyCLibPrivIFace, ctype_tolower ), EM_LOCALE, __ctype_tolower },
/*   68 */ { offsetof( struct AmyCLibPrivIFace, ctype_toupper ), EM_LOCALE, __ctype_toupper },
/*   69 */ { offsetof( struct AmyCLibPrivIFace, time_localtime ), EM_ALWAYS, __time_localtime },
/*   70 */ { offsetof( struct AmyCLibPrivIFace, time_time ), EM_ALWAYS, __time_time },
/*   71 */ { offsetof( struct AmyCLibPrivIFace, stdio_fopen ), EM_FILE, __stdio_fopen },
/*   72 */ { offsetof( struct AmyCLibPrivIFace, stdio_ftell ), EM_FILE, __stdio_ftell },
/*   73 */ { offsetof( struct AmyCLibPrivIFace, stdio_fgetpos ), EM_FILE, __stdio_fgetpos },
/*   74 */ { offsetof( struct AmyCLibPrivIFace, stdio_flockfile ), EM_FILE, __stdio_flockfile },
/*   75 */ { offsetof( struct AmyCLibPrivIFace, stdio_funlockfile ), EM_FILE, __stdio_funlockfile },
/*   76 */ { offsetof( struct AmyCLibPrivIFace, stdio_fflush ), EM_FILE, __stdio_fflush },
/*   77 */ { offsetof( struct AmyCLibPrivIFace, stdio_puts ), EM_FILE, __stdio_puts },
/*   78 */ { offsetof( struct AmyCLibPrivIFace, stdio_putchar ), EM_FILE, __stdio_putchar },
/*   79 */ { offsetof( struct AmyCLibPrivIFace, stdio_fputc ), EM_FILE, __stdio_fputc },
/*   80 */ { offsetof( struct AmyCLibPrivIFace, stdio_setvbuf ), EM_FILE, __stdio_setvbuf },
/*   81 */ { offsetof( struct AmyCLibPrivIFace, stdio_fclose ), EM_FILE, __stdio_fclose },
/*   82 */ { offsetof( struct AmyCLibPrivIFace, stdio_fseek ), EM_FILE, __stdio_fseek },
/*   83 */ { offsetof( struct AmyCLibPrivIFace, stdio_fseeko ), EM_FILE, __stdio_fseeko },
/*   84 */ { offsetof( struct AmyCLibPrivIFace, stdio_vprintf ), EM_FILE, __stdio_vprintf },
/*   85 */ { offsetof( struct AmyCLibPrivIFace, stdio_vsprintf ), EM_FILE, __stdio_vsprintf },
/*   86 */ { offsetof( struct AmyCLibPrivIFace, stdio_fputc_unlocked ), EM_FILE, __stdio_fputc_unlocked },
/*   87 */ { offsetof( struct AmyCLibPrivIFace, stdio_vsnprintf ), EM_FILE, __stdio_vsnprintf },
/*   88 */ { offsetof( struct AmyCLibPrivIFace, fcntl_open ), EM_FILE, __fcntl_open },
/*   89 */ { offsetof( struct AmyCLibPrivIFace, unistd_close ), EM_FILE, __unistd_close },
/*   90 */ { offsetof( struct AmyCLibPrivIFace, stdio_ungetc ), EM_FILE, __stdio_ungetc },
/*   91 */ { offsetof( struct AmyCLibPrivIFace, stdio_fread ), EM_FILE, __stdio_fread },
/*   92 */ { offsetof( struct AmyCLibPrivIFace, stdio_clearerr ), EM_FILE, __stdio_clearerr },
/*   92 */ { offsetof( struct AmyCLibPrivIFace, stdlib_strtof ), EM_ALWAYS, __stdlib_strtof },
/*   93 */ { offsetof( struct AmyCLibPrivIFace, stdlib_strtod ), EM_ALWAYS, __stdlib_strtod },
/*   94 */ { offsetof( struct AmyCLibPrivIFace, inttypes_strtoumax ), EM_STRING, __inttypes_strtoumax },
/*   95 */ { offsetof( struct AmyCLibPrivIFace, inttypes_strtoimax ), EM_STRING, __inttypes_strtoimax },
/*   97 */ { offsetof( struct AmyCLibPrivIFace, strings_strcasecmp ), EM_STRING, __strings_strcasecmp },
/*   98 */ { offsetof( struct AmyCLibPrivIFace, strings_strncasecmp ), EM_STRING, __strings_strncasecmp },
/*   99 */ { offsetof( struct AmyCLibPrivIFace, math_d__get_huge_val ), EM_ALWAYS, __math_d__get_huge_val },
/*  100 */ { offsetof( struct AmyCLibPrivIFace, math_d__inf ), EM_ALWAYS, __math_d__inf },
/*  101 */ { offsetof( struct AmyCLibPrivIFace, math_d__isinf ), EM_ALWAYS, __math_d__isinf },
/*  102 */ { offsetof( struct AmyCLibPrivIFace, math_d__isnan ), EM_ALWAYS, __math_d__isnan },
/*  103 */ { offsetof( struct AmyCLibPrivIFace, math_d_nan ), EM_ALWAYS, __math_d_nan },
/*  104 */ { offsetof( struct AmyCLibPrivIFace, math_d_pow ), EM_ALWAYS, __math_d_pow },
/*  105 */ { offsetof( struct AmyCLibPrivIFace, math_d_fabs ), EM_ALWAYS, __math_d_fabs },
/*  106 */ { offsetof( struct AmyCLibPrivIFace, math_d_scalbn ), EM_ALWAYS, __math_d_scalbn },
/*  107 */ { offsetof( struct AmyCLibPrivIFace, math_d_sqrt ), EM_ALWAYS, __math_d_sqrt },
/*  108 */ { offsetof( struct AmyCLibPrivIFace, math_d_copysign ), EM_ALWAYS, __math_d_copysign },
/*  109 */ { offsetof( struct AmyCLibPrivIFace, stdio_vsscanf ), EM_ALWAYS, __stdio_vsscanf },
/*  110 */ // { offsetof( struct AmyCLibPrivIFace, time_strftime ), EM_ALWAYS, __time_strftime },
/*  111 */ { offsetof( struct AmyCLibPrivIFace, signal_signal ), EM_ALWAYS, __signal_signal },
/*  112 */ { offsetof( struct AmyCLibPrivIFace, signal_raise ), EM_ALWAYS, __signal_raise },
/*  113 */ { offsetof( struct AmyCLibPrivIFace, stdlib_abort ), EM_ALWAYS, __stdlib_abort },
/*  114 */ { offsetof( struct AmyCLibPrivIFace, stdlib__Exit ), EM_ALWAYS, __stdlib__Exit },
/*  115 */ { offsetof( struct AmyCLibPrivIFace, stdio_vasprintf ), EM_MEMORY, __stdio_vasprintf },
/*  116 */ { offsetof( struct AmyCLibPrivIFace, assert_assert ), EM_ALWAYS, __assert_assert },
/*  117 */ { offsetof( struct AmyCLibPrivIFace, stdlib_exit ), EM_ALWAYS, __stdlib_exit },
/*  118 */ // { offsetof( struct AmyCLibPrivIFace, ctype_islower ), EM_LOCALE, __ctype_islower },
/*  119 */ { offsetof( struct AmyCLibPrivIFace, stdio_fgetc ), EM_FILE, __stdio_fgetc },
/*  120 */	// time_gmtime
/*  121 */	// time_gmtime_r
/*  122 */ { offsetof( struct AmyCLibPrivIFace, stdio_ferror ), EM_FILE, __stdio_ferror },
/*  123 */	// _generic__Priv_Print_Log,
/*  124 */	// _generic__Priv_Func_Log,
/*  125 */	// _generic_string_strcspn,
/*  126 */	// _generic_string_strspn,
/*  127 */	// _generic_string_strpbrk,
/*  128 */	// _generic_string_strchr,
/*  129 */	{ offsetof( struct AmyCLibPrivIFace, stdio_fileno ), EM_FILE, __stdio_fileno },
/*  130 */	// int AMYFUNC _generic_stdio_fprintf( struct AmyCLibPrivIFace *Self, struct PrivFile *stream, const char *format, ... )
/*  131 */	// int AMYFUNC _generic_stdio_fputs( struct AmyCLibPrivIFace *Self, const void *s, struct PrivFile *stream )
/*  132 */	// size_t AMYFUNC _generic_stdio_fwrite( struct AmyCLibPrivIFace *Self, const void *ptr, size_t size, size_t nitems, struct PrivFile *stream )
/*  133 */	// int AMYFUNC _generic_stdio_putc( struct AmyCLibPrivIFace *Self, int c, struct PrivFile *stream )
/*  134 */	// void AMYFUNC _generic_stdlib__exit( struct AmyCLibPrivIFace *Self, int status )
/*  135 */	// long AMYFUNC _generic_stdlib_atol( struct AmyCLibPrivIFace *Self, const char *str )
/*  136 */	// char * AMYFUNC _generic_stdlib_getenv( struct AmyCLibPrivIFace *Self, const char *name )
/*  137 */	// void AMYFUNC _generic_stdlib_qsort( struct AmyCLibPrivIFace *Self, void *base, size_t nel, size_t width, int (*compar)(const void *, const void *))
/*  138 */	// int AMYFUNC _generic_sys_stat_chmod( struct AmyCLibPrivIFace *Self, const char *path, mode_t mode )
/*  139 */	// int AMYFUNC _generic_sys_stat_mkdir( struct AmyCLibPrivIFace *Self, const char *path, mode_t mode )
/*  140 */	// char * AMYFUNC _generic_sys_stat_mktemp( struct AmyCLibPrivIFace *Self, char *template )
/*  141 */	// int AMYFUNC _generic_sys_stat_stat( struct AmyCLibPrivIFace *Self, const char *path, struct stat *buf )
/*  142 */	// char * AMYFUNC _generic_time_ctime( struct AmyCLibPrivIFace *Self, const time_t *clock )
/*  143 */	// int AMYFUNC _generic_unistd_unlink( struct AmyCLibPrivIFace *Self, const char *path )
/*  144 */	// char *AMYFUNC (*string_strncat)( struct AmyCLibPrivIFace *Self, char *d, const char *s, size_t n );
/*  145 */	// int AMYFUNC (*stdio_vfprintf)( struct AmyCLibPrivIFace *Self, FILE *stream, const char *format, va_list ap );
/*  146 */	// mode_t AMYFUNC (*sys_stat_umask)( struct AmyCLibPrivIFace *Self, mode_t cmask );
/*  147 */	// pid_t AMYFUNC (*unistd_getpid)( struct AmyCLibPrivIFace *Self );
/*  148 */	// char * AMYFUNC (*unistd_getcwd)( struct AmyCLibPrivIFace *Self, char *buf, size_t size );
/*  149 */	// int AMYFUNC (*sys_stat_fstat)( struct AmyCLibPrivIFace *Self, int fildes, struct stat *buf );
/*  150 */	// int AMYFUNC (*sys_stat_lstat)( struct AmyCLibPrivIFace *Self, const char *path, struct stat *buf );
/*  151 */	// int AMYFUNC (*unistd_access)( struct AmyCLibPrivIFace *Self, const char *path, int amode );
/*  152 */	// int AMYFUNC (*unistd_fcntl_ap)( struct AmyCLibPrivIFace *Self, int fildes, int cmd, va_list ap );
/*  153 */	// ssize_t AMYFUNC (*unistd_read)( struct AmyCLibPrivIFace *Self, int fildes, void *buf, size_t nbyte );
/*  154 */	// double AMYFUNC (*stdlib_atof)( struct AmyCLibPrivIFace *Self, const char *str );
/*  155 */	// int AMYFUNC (*stdio_getc)( struct AmyCLibPrivIFace *Self, struct PrivFile *stream );
/*  156 */	// int AMYFUNC (*utime_utime)( struct AmyCLibPrivIFace *Self, const char *str, const struct utimbuf *buf );
/*  157 */	// int AMYFUNC (*unistd_link)( struct AmyCLibPrivIFace *Self, const char *path1, const char *path2 );
/*  158 */	// int AMYFUNC (*unistd_isatty)( struct AmyCLibPrivIFace *Self, int fildes );
/*  159 */	// void AMYFUNC (*stdio_perror)( struct AmyCLibPrivIFace *Self, const char *s );
/*  160 */	// int AMYFUNC (*stdio_remove)( struct AmyCLibPrivIFace *Self, const char *path );
/*  161 */	// int AMYFUNC (*stdio_rename)( struct AmyCLibPrivIFace *Self, const char *old, const char *new );
/*  162 */	// int AMYFUNC (*unistd_rmdir)( struct AmyCLibPrivIFace *Self, const char *path );
/*  163 */	// int AMYFUNC (*stdio_feof)( struct AmyCLibPrivIFace *Self, struct PrivFile *stream );
/*  164 */	// char * AMYFUNC (*stdio_fgets)( struct AmyCLibPrivIFace *Self, char *s, int n, struct PrivFile *stream );
/*  165 */	// void AMYFUNC (*stdio_rewind)( struct AmyCLibPrivIFace *Self, struct PrivFile *stream );
/*  166 */	// int AMYFUNC (*stdio_vfscanf)( struct AmyCLibPrivIFace *Self, struct PrivFile *stream, const char *format, va_list arg );
/*  167 */	// size_t AMYFUNC (*wchar_mbrtowc)( struct AmyCLibPrivIFace *Self, wchar_t *pwc, const char *s, size_t n, mbstate_t *ps );
/*  168 */	// int AMYFUNC (*stdio_getchar)( struct AmyCLibPrivIFace *Self );
/*  169 */	// char * AMYFUNC (*string_strstr)( struct AmyCLibPrivIFace *Self, const char *s1, const char *s2 );
/*  170 */	// size_t AMYFUNC (*wchar_mbstowcs)( struct AmyCLibPrivIFace *Self, wchar_t *pwcs, const char *s, size_t n );
/*  171 */	// uid_t AMYFUNC (*unistd_geteuid)( struct AmyCLibPrivIFace *Self );
/*  172 */	// gid_t AMYFUNC (*unistd_getegid)( struct AmyCLibPrivIFace *Self );
/*  173 */	// char * AMYFUNC (*locale_setlocale)( struct AmyCLibIFace *Self, int category, char *locale );
/*  174 */	// ssize_t AMYFUNC (*stdio_getline)( struct AmyCLibPrivIFace *Self, char **lineptr, size_t *n, FILE *stream );
/*  175 */	// ssize_t AMYFUNC (*stdio_getdelim)( struct AmyCLibPrivIFace *Self, char **lineptr, size_t *n, int delimiter, FILE *stream );
/*  176 */	// int AMYFUNC (*stdio_putc_unlocked)( struct AmyCLibPrivIFace *Self, int c, struct PrivFile *stream );
/*  177 */	// int AMYFUNC _generic_ctype_isprint( struct AmyCLibPrivIFace *Self, int c )
/*  178 */	// char * AMYFUNC _generic_string_strerror( struct AmyCLibPrivIFace *Self, int errnum )
/*  179 */	// int AMYFUNC _generic_string_strerror_r( struct AmyCLibPrivIFace *Self, int errnum, char *buf, size_t buflen )





	{ 0, 0, NULL },
};

// --

static void myInit_Enable( struct AmyCLibPrivIFace *Self, struct libData *data UNUSED, U32 emmask )
{
struct EnableStruct *es;
struct EnableFunc *ef;
enum CPUType type;
U32 pos;
//U32 cnt;

	// todo.. find out what type of cpu we are 
	type = CPUType_Any;		

	// 
	pos = 0;

	while( TRUE )
	{
		es = & funcs[pos++];

		if ( ! es->Offset )
		{
			break;
		}

		if ( ! ( es->Mask & emmask ))
		{
			continue;
		}

		ef = es->Funcs;

		if ( ! ef )
		{
			continue;
		}

		while( TRUE )
		{
			if (( ef->CPUType == CPUType_Any ) 
			||	( ef->CPUType == type )
			||	( ef->CPUFunc == NULL ))
			{
				break;
			}
			else
			{
				ef++;
			}
		}

		if ( ! ef->CPUFunc )
		{
			continue;
		}

		IExec->SetMethod( (PTR) Self, es->Offset, ef->CPUFunc );
	}
}

// --
