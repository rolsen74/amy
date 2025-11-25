
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Portions based on clib2 by Olaf Barthel (2002–2016)
** Target OS: AmigaOS
*/

#ifndef AMYLIB_INTERFACES_AMYCLIBPRIV_H
#define AMYLIB_INTERFACES_AMYCLIBPRIV_H

// --

#include <proto/dos.h>
#include <proto/exec.h>

#include "Amy_Defines.h"

#include <stdarg.h>
#include <stddef.h>
#include <string.h>
#include <setjmp.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <utime.h>
#include <wchar.h>

// --
struct PrintStruct;
struct ScanStruct;
struct PrivFile;

struct AmyCLibPrivIFace
{
	struct InterfaceData Data;

	// --

/*    0 */	U32							AMYFUNC (*Obtain)( struct AmyCLibPrivIFace *Self );
/*    1 */	U32							AMYFUNC (*Release)( struct AmyCLibPrivIFace *Self );
/*    2 */	void						AMYFUNC (*Expunge)( struct AmyCLibPrivIFace *Self );
/*    3 */	struct Interface *			AMYFUNC (*Clone)( struct AmyCLibPrivIFace *Self );
/*    4 */	S32							AMYFUNC (*Priv_Startup_Init)( struct AmyCLibPrivIFace *, STR args, U32 mask );
/*    5 */	S32							AMYFUNC (*Priv_Startup_Main)( struct AmyCLibPrivIFace *, int main( int, char ** ) , STR arg_string, S32 arg_length, PTR wbmsg, struct _AmyCLibPublic **pd );
/*    6 */	void						AMYFUNC	(*Priv_Startup_Free)( struct AmyCLibPrivIFace * );

	// --

/*    7 */	PTR							AMYFUNC (*Priv_Mem_Alloc)( struct AmyCLibPrivIFace *Self, U32 Size );
/*    8 */	U32							AMYFUNC (*Priv_Mem_Free)( struct AmyCLibPrivIFace *Self, PTR mem );
/*    9 */	PTR							AMYFUNC (*Priv_Mem_Realloc)( struct AmyCLibPrivIFace *Self, PTR oldmem, U32 Size );
/*   10 */	struct MemPoolHeader *		AMYFUNC (*Priv_Mem_CreatePool)( struct AmyCLibPrivIFace *Self, U32 size );
/*   11 */	U32							AMYFUNC (*Priv_Mem_DeletePool)( struct AmyCLibPrivIFace *Self, struct MemPoolHeader *handle );
/*   12 */	U32							AMYFUNC (*Priv_Mem_FlushPool)( struct AmyCLibPrivIFace *Self, struct MemPoolHeader *handle );
/*   13 */	PTR							AMYFUNC (*Priv_Mem_AllocPooled)( struct AmyCLibPrivIFace *Self, struct MemPoolHeader *handle, U32 Size );
/*   14 */	U32							AMYFUNC (*Priv_Mem_FreePooled)( struct AmyCLibPrivIFace *Self, struct MemPoolHeader *handle, PTR mem );
/*   15 */	void						AMYFUNC (*Priv_Check_Abort)( struct AmyCLibPrivIFace *Self );
/*   16 */	S32							AMYFUNC (*Priv_Convert_Time_to_TM)( struct AmyCLibPrivIFace *Self, const time_t *time, struct tm *tm );
/*   17 */	S32							AMYFUNC (*Priv_Convert_ED_to_Stat)( struct AmyCLibPrivIFace *Self, struct ExamineData *ed, struct stat *st );
/*   18 */	S32							AMYFUNC (*Priv_Convert_DS_to_Time)( struct AmyCLibPrivIFace *Self, const struct DateStamp *ds, time_t *time );
/*   19 */	S32							AMYFUNC (*Priv_Convert_IOErr_to_ErrNo)( struct AmyCLibPrivIFace *Self, S32 err );
/*   20 */	S32							AMYFUNC (*Priv_FB_Read)( struct AmyCLibPrivIFace *Self, struct PrivFile *stream );
/*   21 */	S32							AMYFUNC (*Priv_FB_Read_Fill_Buffer)( struct AmyCLibPrivIFace *Self, struct PrivFile *stream );
/*   22 */	S32							AMYFUNC (*Priv_FB_Read_Drop_Buffer)( struct AmyCLibPrivIFace *Self, struct PrivFile *stream );
/*   23 */	S32							AMYFUNC (*Priv_FB_Write)( struct AmyCLibPrivIFace *Self, struct PrivFile *stream, S32 mode, S32 c );
/*   24 */	S32							AMYFUNC (*Priv_FB_Write_Flush_Buffer)( struct AmyCLibPrivIFace *Self, struct PrivFile *stream );
/*   25 */	S32							AMYFUNC (*Priv_FB_Write_Flush_Buffer2)( struct AmyCLibPrivIFace *Self, struct PrivFile *stream );

/*   26 */	PTR							AMYFUNC (*Priv_FD_Alloc)( struct AmyCLibPrivIFace *Self, U32 ID );
/*   27 */	S32							AMYFUNC (*Priv_FD_Free)( struct AmyCLibPrivIFace *Self, struct PrivFile *stream );
/*   28 */	PTR							AMYFUNC (*Priv_FD_Init)( struct AmyCLibPrivIFace *Self, PTR is );
/*   29 */	S32							AMYFUNC (*Priv_FD_Init_Struct)( struct AmyCLibPrivIFace *Self, struct PrivFile *stream, U32 ID );
/*   30 */	S32							AMYFUNC (*Priv_FD_Array_Insert)( struct AmyCLibPrivIFace *Self, PTR Node );
/*   31 */	PTR							AMYFUNC (*Priv_FD_Array_Remove)( struct AmyCLibPrivIFace *Self, U32 Pos );

/*   32 */	PTR							AMYFUNC (*Priv_FDLockNr)( struct AmyCLibPrivIFace *Self, S32 nr );
/*   33 */	PTR							AMYFUNC (*Priv_FDLockStream)( struct AmyCLibPrivIFace *Self, struct PrivFile *stream );
/*   34 */	void						AMYFUNC (*Priv_FDUnlock)( struct AmyCLibPrivIFace *Self, struct PrivFile *stream );

/*   35 */	void						AMYFUNC (*Priv_Print)( struct AmyCLibPrivIFace *Self, struct PrintStruct *ps );
/*   36 */	void						AMYFUNC (*Priv_Scan)( struct AmyCLibPrivIFace *Self, struct ScanStruct *ss );

	// --

/*   37 */	void						AMYFUNC (*setjmp_longjmp)( struct AmyCLibPrivIFace *, jmp_buf buf, int val );
/*   38 */	int							AMYFUNC (*setjmp_setjmp)( struct AmyCLibPrivIFace *, jmp_buf buf );

/*   39 */	void *						AMYFUNC (*stdlib_calloc)( struct AmyCLibPrivIFace *Self, size_t num, size_t size );
/*   40 */	void *						AMYFUNC (*stdlib_malloc)( struct AmyCLibPrivIFace *Self, size_t size );
/*   41 */	void *						AMYFUNC (*stdlib_realloc)( struct AmyCLibPrivIFace *Self, void *mem, size_t size );
/*   42 */	void						AMYFUNC (*stdlib_free)( struct AmyCLibPrivIFace *Self, void *mem );
/*   43 */	int							AMYFUNC (*stdlib_rand)( struct AmyCLibPrivIFace *Self );
/*   44 */	int							AMYFUNC (*stdlib_rand_r)( struct AmyCLibPrivIFace *Self, unsigned int *seed );
/*   45 */	void						AMYFUNC (*stdlib_srand)( struct AmyCLibPrivIFace *Self, unsigned int seed );
/*   46 */	int							AMYFUNC (*stdlib_atoi)( struct AmyCLibPrivIFace *Self, const char *str );
/*   47 */	long						AMYFUNC (*stdlib_strtol)( struct AmyCLibPrivIFace *Self, const char *nptr, char **endptr, int base );

/*   48 */	size_t						AMYFUNC (*string_strlen)( struct AmyCLibPrivIFace *Self,const char *str );
/*   49 */	size_t						AMYFUNC (*string_strnlen)( struct AmyCLibPrivIFace *Self,const char *str, size_t max );
/*   50 */	char *						AMYFUNC (*string_strdup)( struct AmyCLibPrivIFace *Self,const char *str );
/*   51 */	char *						AMYFUNC (*string_strndup)( struct AmyCLibPrivIFace *Self,const char *str, size_t max );
/*   52 */	char *						AMYFUNC (*string_strcpy)( struct AmyCLibPrivIFace *Self, char *dst, const char *src );
/*   53 */	char *						AMYFUNC (*string_strncpy)( struct AmyCLibPrivIFace *Self, char *dst, const char *src, size_t max );
/*   54 */	int							AMYFUNC (*string_strcmp)( struct AmyCLibPrivIFace *Self, const char *s1, const char *s2 );
/*   55 */	int							AMYFUNC (*string_strncmp)( struct AmyCLibPrivIFace *Self, const char *s1, const char *s2, size_t max );
/*   56 */	int							AMYFUNC (*string_memcmp)( struct AmyCLibPrivIFace *Self, const void *s1, const void *s2, size_t len );
/*   57 */	void *						AMYFUNC (*string_memmove)( struct AmyCLibPrivIFace *Self, void *dst, const void *src, size_t len );
/*   58 */	PTR							AMYFUNC (*string_memcpy)( struct AmyCLibPrivIFace *Self, void *dst, const void *src, size_t len );
/*   59 */	void *						AMYFUNC (*string_memset)( struct AmyCLibPrivIFace *Self, void *s, int c, size_t n );
/*   60 */	char *					 	AMYFUNC (*string_strcat)( struct AmyCLibPrivIFace *Self, char *dst, const char *src );

/*   61 */	void						AMYFUNC (*strings_bzero)( struct AmyCLibPrivIFace *Self, void *mem, size_t len );

/*   62 */	int							AMYFUNC (*ctype_isalpha)( struct AmyCLibPrivIFace *Self, int c );
/*   63 */	int							AMYFUNC (*ctype_isdigit)( struct AmyCLibPrivIFace *Self, int c );
/*   64 */	int							AMYFUNC (*ctype_isspace)( struct AmyCLibPrivIFace *Self, int c );
/*   65 */	int							AMYFUNC (*ctype_isupper)( struct AmyCLibPrivIFace *Self, int c );
/*   66 */	int							AMYFUNC (*ctype_isxdigit)( struct AmyCLibPrivIFace *Self, int c );
/*   67 */	int							AMYFUNC (*ctype_tolower)( struct AmyCLibPrivIFace *Self, int c );
/*   68 */	int							AMYFUNC (*ctype_toupper)( struct AmyCLibPrivIFace *Self, int c );

/*   69 */	struct tm *					AMYFUNC (*time_localtime)( struct AmyCLibPrivIFace *Self, const time_t *time );
/*   70 */	time_t						AMYFUNC (*time_time)( struct AmyCLibPrivIFace *Self, time_t *ptr );

/*   71 */	struct PrivFile *			AMYFUNC (*stdio_fopen)( struct AmyCLibPrivIFace *Self, const char *filename, const char *mode );
/*   72 */	long						AMYFUNC (*stdio_ftell)( struct AmyCLibPrivIFace *Self, struct PrivFile *stream );
/*   73 */	int							AMYFUNC (*stdio_fgetpos)( struct AmyCLibPrivIFace *Self, struct PrivFile *stream, fpos_t *pos );
/*   74 */	void						AMYFUNC (*stdio_flockfile)( struct AmyCLibPrivIFace *Self, struct PrivFile *stream );
/*   75 */	void						AMYFUNC (*stdio_funlockfile)( struct AmyCLibPrivIFace *Self, struct PrivFile *stream );
/*   76 */	int							AMYFUNC (*stdio_fflush)( struct AmyCLibPrivIFace *Self, struct PrivFile *stream );
/*   77 */	int							AMYFUNC (*stdio_puts)( struct AmyCLibPrivIFace *Self, const char *str );
/*   78 */	int							AMYFUNC (*stdio_putchar)( struct AmyCLibPrivIFace *Self, int c );
/*   79 */	int							AMYFUNC (*stdio_fputc)( struct AmyCLibPrivIFace *Self, int c, struct PrivFile *stream );
/*   80 */	int							AMYFUNC (*stdio_setvbuf)( struct AmyCLibPrivIFace *Self, struct PrivFile *stream, char *buf, int mode, size_t size );
/*   81 */	int							AMYFUNC (*stdio_fclose)( struct AmyCLibPrivIFace *Self, struct PrivFile *stream );
/*   82 */	int							AMYFUNC (*stdio_fseek)( struct AmyCLibPrivIFace *Self, struct PrivFile *stream, long offset, int wherefrom );
/*   83 */	int							AMYFUNC (*stdio_fseeko)( struct AmyCLibPrivIFace *Self, struct PrivFile *stream, off_t offset, int wherefrom );
/*   84 */	int							AMYFUNC (*stdio_vprintf)( struct AmyCLibPrivIFace *Self, const char *fmt, va_list ap );
/*   85 */	int							AMYFUNC (*stdio_vsprintf)( struct AmyCLibPrivIFace *Self, char *buf, const char *fmt, va_list ap );
/*   86 */	int							AMYFUNC (*stdio_fputc_unlocked)( struct AmyCLibPrivIFace *Self, int c, struct PrivFile *stream );
/*   87 */	int							AMYFUNC (*stdio_vsnprintf)( struct AmyCLibPrivIFace *Self, char *buf, size_t size, const char *fmt, va_list ap );
/*   88 */	int							AMYFUNC (*fcntl_open)( struct AmyCLibPrivIFace *Self, const char *path, int oflag, ... );
/*   89 */	int							AMYFUNC (*unistd_close)( struct AmyCLibPrivIFace *Self, int fildes );
	// --
/*   90 */	int							AMYFUNC (*stdio_ungetc)( struct AmyCLibPrivIFace *Self, int c, struct PrivFile *stream );
/*   91 */	size_t						AMYFUNC (*stdio_fread)( struct AmyCLibPrivIFace *Self, void *ptr, size_t size, size_t count, struct PrivFile *stream );
/*   92 */	float						AMYFUNC (*stdlib_strtof)( struct AmyCLibPrivIFace *Self, const char *str, char **ptr );
/*   93 */	double						AMYFUNC (*stdlib_strtod)( struct AmyCLibPrivIFace *Self, const char *str, char **ptr );
/*   94 */	uintmax_t					AMYFUNC (*inttypes_strtoumax)( struct AmyCLibPrivIFace *Self, const char *nptr, char **endptr, int base );
/*   95 */	intmax_t					AMYFUNC (*inttypes_strtoimax)( struct AmyCLibPrivIFace *Self, const char *nptr, char **endptr, int base );
/*   96 */	void						AMYFUNC (*stdio_clearerr)( struct AmyCLibPrivIFace *Self, struct PrivFile *stream );
/*   97 */	int							AMYFUNC (*strings_strcasecmp)( struct AmyCLibPrivIFace *Self, const char *s1, const char *s2 );
/*   98 */	int							AMYFUNC (*strings_strncasecmp)( struct AmyCLibPrivIFace *Self, const char *s1, const char *s2, size_t maxlen );
/*   99 */	double 						AMYFUNC (*math_d__get_huge_val)( struct AmyCLibPrivIFace *Self );
/*  100 */	double						AMYFUNC (*math_d__inf)( struct AmyCLibPrivIFace *Self );
/*  101 */	int							AMYFUNC (*math_d__isinf)( struct AmyCLibPrivIFace *Self, double x );
/*  102 */	int							AMYFUNC (*math_d__isnan)( struct AmyCLibPrivIFace *Self, double x );
/*  103 */	double						AMYFUNC (*math_d_nan)( struct AmyCLibPrivIFace *Self, const char *xx );
/*  104 */	double						AMYFUNC (*math_d_pow)( struct AmyCLibPrivIFace *Self, double x, double y );
/*  105 */	double						AMYFUNC (*math_d_fabs)( struct AmyCLibPrivIFace *Self, double x );
/*  106 */	double						AMYFUNC (*math_d_scalbn)( struct AmyCLibPrivIFace *Self, double x, int n );
/*  107 */	double						AMYFUNC (*math_d_sqrt)( struct AmyCLibPrivIFace *Self, double x );
/*  108 */	double						AMYFUNC (*math_d_copysign)( struct AmyCLibPrivIFace *Self, double x, double y );
/*  109 */	int							AMYFUNC (*stdio_vsscanf)( struct AmyCLibPrivIFace *Self, const char *, const char *, va_list );
/*  110 */	size_t						AMYFUNC (*time_strftime)( struct AmyCLibPrivIFace *Self, char *s, size_t maxsize, const char *format, const struct tm *timptr );
/*  111 */	void						AMYFUNC (*signal_signal)( struct AmyCLibPrivIFace *Self, int sig, void (*func)(int) );
/*  112 */	int							AMYFUNC (*signal_raise)( struct AmyCLibPrivIFace *Self, int sig );
/*  113 */	void						AMYFUNC (*stdlib_abort)( struct AmyCLibPrivIFace *Self );
/*  114 */	void						AMYFUNC (*stdlib__Exit)( struct AmyCLibPrivIFace *Self, int rc );
/*  115 */	int							AMYFUNC (*stdio_vasprintf)( struct AmyCLibPrivIFace *Self, char **ret, const char *fmt, va_list ap );
/*  116 */	void						AMYFUNC (*assert_assert)( struct AmyCLibPrivIFace *Self, const char *filename, int linenumber, const char *function, const char *expression );
/*  117 */	void						AMYFUNC (*stdlib_exit)( struct AmyCLibPrivIFace *Self, int rc );
/*  118 */	int							AMYFUNC (*ctype_islower)( struct AmyCLibPrivIFace *Self, int c );
/*  119 */	int							AMYFUNC (*stdio_fgetc)(struct AmyCLibPrivIFace *, struct PrivFile *stream);
/*  120 */	struct tm *					AMYFUNC (*time_gmtime)(struct AmyCLibPrivIFace *, const time_t *time );
/*  121 */	struct tm *					AMYFUNC (*time_gmtime_r)(struct AmyCLibPrivIFace *, const time_t *time, struct tm *tm );
/*  122 */	int							AMYFUNC	(*stdio_ferror)( struct AmyCLibPrivIFace *Self, struct PrivFile *stream );
/*  123 */	void						AMYFUNC (*Priv_Print_Log)( struct AmyCLibPrivIFace *Self );
/*  124 */	void						AMYFUNC (*Priv_Func_Log)( struct AmyCLibPrivIFace *Self, S32 xx );
/*  125 */	size_t						AMYFUNC (*string_strcspn)( struct AmyCLibPrivIFace *Self, const char *s1, const char *s2 );
/*  126 */	size_t						AMYFUNC (*string_strspn)( struct AmyCLibPrivIFace *Self, const char *s1, const char *s2 );
/*  127 */	char *						AMYFUNC (*string_strpbrk)( struct AmyCLibPrivIFace *Self, const char *s1, const char *s2 );
/*  128 */	char *						AMYFUNC (*string_strchr)( struct AmyCLibPrivIFace *Self, const char *str, int c );
/*  129 */	int							AMYFUNC	(*stdio_fileno)( struct AmyCLibPrivIFace *Self, struct PrivFile *stream );

/*  130 */	int							AMYFUNC (*stdio_fprintf)( struct AmyCLibPrivIFace *Self, struct PrivFile *stream, const char *format, ... );
/*  131 */	int							AMYFUNC (*stdio_fputs)( struct AmyCLibPrivIFace *Self, const void *s, struct PrivFile *stream );
/*  132 */	size_t						AMYFUNC (*stdio_fwrite)( struct AmyCLibPrivIFace *Self, const void *ptr, size_t size, size_t nitems, struct PrivFile *stream );
/*  133 */	int							AMYFUNC (*stdio_putc)( struct AmyCLibPrivIFace *Self, int c, struct PrivFile *stream );
/*  134 */	void						AMYFUNC (*stdlib__exit)( struct AmyCLibPrivIFace *Self, int status );
/*  135 */	long						AMYFUNC (*stdlib_atol)( struct AmyCLibPrivIFace *Self, const char *str );
/*  136 */	char *						AMYFUNC (*stdlib_getenv)( struct AmyCLibPrivIFace *Self, const char *name );
/*  137 */	void						AMYFUNC (*stdlib_qsort)( struct AmyCLibPrivIFace *Self, void *base, size_t nel, size_t width, int (*compar)(const void *, const void *));
/*  138 */	int							AMYFUNC (*sys_stat_chmod)( struct AmyCLibPrivIFace *Self, const char *path, mode_t mode );
/*  139 */	int							AMYFUNC (*sys_stat_mkdir)( struct AmyCLibPrivIFace *Self, const char *path, mode_t mode );
/*  140 */	char *						AMYFUNC (*sys_stat_mktemp)( struct AmyCLibPrivIFace *Self, char *template );
/*  141 */	int							AMYFUNC (*sys_stat_stat)( struct AmyCLibPrivIFace *Self, const char *path, struct stat *buf );
/*  142 */	char *						AMYFUNC (*time_ctime)( struct AmyCLibPrivIFace *Self, const time_t *clock );
/*  143 */	int							AMYFUNC (*unistd_unlink)( struct AmyCLibPrivIFace *Self, const char *path );
/*  144 */	char *						AMYFUNC (*string_strncat)( struct AmyCLibPrivIFace *Self, char *d, const char *s, size_t n );
/*  145 */	int							AMYFUNC (*stdio_vfprintf)( struct AmyCLibPrivIFace *Self, struct PrivFile *stream, const char *format, va_list ap );
/*  146 */	mode_t						AMYFUNC (*sys_stat_umask)( struct AmyCLibPrivIFace *Self, mode_t cmask );
/*  147 */	pid_t						AMYFUNC (*unistd_getpid)( struct AmyCLibPrivIFace *Self );
/*  148 */	char *						AMYFUNC (*unistd_getcwd)( struct AmyCLibPrivIFace *Self, char *buf, size_t size );
/*  149 */	int							AMYFUNC (*sys_stat_fstat)( struct AmyCLibPrivIFace *Self, int fildes, struct stat *buf );
/*  150 */	int							AMYFUNC (*sys_stat_lstat)( struct AmyCLibPrivIFace *Self, const char *path, struct stat *buf );
/*  151 */	int							AMYFUNC (*unistd_access)( struct AmyCLibPrivIFace *Self, const char *path, int amode );
/*  152 */	int							AMYFUNC (*unistd_fcntl_ap)( struct AmyCLibPrivIFace *Self, int fildes, int cmd, va_list ap );
/*  153 */	ssize_t						AMYFUNC (*unistd_read)( struct AmyCLibPrivIFace *Self, int fildes, void *buf, size_t nbyte );
/*  154 */	double						AMYFUNC (*stdlib_atof)( struct AmyCLibPrivIFace *Self, const char *str );
/*  155 */	int							AMYFUNC (*stdio_getc)( struct AmyCLibPrivIFace *Self, struct PrivFile *stream );
/*  156 */	int							AMYFUNC (*utime_utime)( struct AmyCLibPrivIFace *Self, const char *str, const struct utimbuf *buf );
/*  157 */	int							AMYFUNC (*unistd_link)( struct AmyCLibPrivIFace *Self, const char *path1, const char *path2 );
/*  158 */	int							AMYFUNC (*unistd_isatty)( struct AmyCLibPrivIFace *Self, int fildes );
/*  159 */	void						AMYFUNC (*stdio_perror)( struct AmyCLibPrivIFace *Self, const char *s );
/*  160 */	int							AMYFUNC (*stdio_remove)( struct AmyCLibPrivIFace *Self, const char *path );
/*  161 */	int							AMYFUNC (*stdio_rename)( struct AmyCLibPrivIFace *Self, const char *old, const char *new );
/*  162 */	int							AMYFUNC (*unistd_rmdir)( struct AmyCLibPrivIFace *Self, const char *path );
/*  163 */	int							AMYFUNC (*stdio_feof)( struct AmyCLibPrivIFace *Self, struct PrivFile *stream );
/*  164 */	char *						AMYFUNC (*stdio_fgets)( struct AmyCLibPrivIFace *Self, char *s, int n, struct PrivFile *stream );
/*  165 */	void						AMYFUNC (*stdio_rewind)( struct AmyCLibPrivIFace *Self, struct PrivFile *stream );
/*  166 */	int							AMYFUNC (*stdio_vfscanf)( struct AmyCLibPrivIFace *Self, struct PrivFile *stream, const char *format, va_list arg );
/*  167 */	size_t						AMYFUNC (*wchar_mbrtowc)( struct AmyCLibPrivIFace *Self, wchar_t *pwc, const char *s, size_t n, mbstate_t *ps );
/*  168 */	int							AMYFUNC (*stdio_getchar)( struct AmyCLibPrivIFace *Self );
/*  169 */	char *						AMYFUNC (*string_strstr)( struct AmyCLibPrivIFace *Self, const char *s1, const char *s2 );
/*  170 */	size_t						AMYFUNC (*wchar_mbstowcs)( struct AmyCLibPrivIFace *Self, wchar_t *pwcs, const char *s, size_t n );
/*  171 */	uid_t						AMYFUNC (*unistd_geteuid)( struct AmyCLibPrivIFace *Self );
/*  172 */	gid_t						AMYFUNC (*unistd_getegid)( struct AmyCLibPrivIFace *Self );
/*  173 */	char *						AMYFUNC (*locale_setlocale)( struct AmyCLibPrivIFace *Self, int category, const char *locale );
/*  174 */	ssize_t						AMYFUNC (*stdio_getline)( struct AmyCLibPrivIFace *Self, char **lineptr, size_t *n, struct PrivFile *stream );
/*  175 */	ssize_t						AMYFUNC (*stdio_getdelim)( struct AmyCLibPrivIFace *Self, char **lineptr, size_t *n, int delimiter, struct PrivFile *stream );
/*  176 */	int							AMYFUNC (*stdio_putc_unlocked)( struct AmyCLibPrivIFace *Self, int c, struct PrivFile *stream );
/*  177 */	int							AMYFUNC (*ctype_isprint)( struct AmyCLibPrivIFace *Self, int c );
/*  178 */	char *						AMYFUNC (*string_strerror)( struct AmyCLibPrivIFace *Self, int errnum );
/*  179 */	int							AMYFUNC (*string_strerror_r)( struct AmyCLibPrivIFace *Self, int errnum, char *buf, size_t buflen );
/*  180 */	int							AMYFUNC (*sys_time_gettimeofday)( struct AmyCLibPrivIFace *Self, struct timeval *tp, void *tzp );
/*  181 */	int							AMYFUNC (*ctype_isascii)( struct AmyCLibPrivIFace *Self, int c );
/*  182 */	char *						AMYFUNC (*string_stpcpy)( struct AmyCLibPrivIFace *Self, char *s1, const char *s2 );
/*  183 */	int							AMYFUNC (*ctype_isalnum)( struct AmyCLibPrivIFace *Self, int c );
/*  184 */	double						AMYFUNC (*math_d_ceil)( struct AmyCLibPrivIFace *Self, double x );
/*  185 */	double						AMYFUNC	(*math_d_cos)( struct AmyCLibPrivIFace *Self, double x );
/*  186 */	double						AMYFUNC (*math_d_sin)( struct AmyCLibPrivIFace *Self, double x );
/*  187 */	double						AMYFUNC (*math_d_atan2)( struct AmyCLibPrivIFace *Self, double y, double x );
/*  188 */	double						AMYFUNC (*math_d_fmod)( struct AmyCLibPrivIFace *Self, double x, double y );
/*  189 */	char *						AMYFUNC (*string_strtok)( struct AmyCLibPrivIFace *Self, char *s1, const char *s2 );
/*  190 */	struct lconv *				AMYFUNC (*locale_localeconv)( struct AmyCLibPrivIFace *Self );
/*  191 */	int							AMYFUNC (*stdlib_mkstemp)( struct AmyCLibPrivIFace *Self, char *template );




};

// --

#endif
