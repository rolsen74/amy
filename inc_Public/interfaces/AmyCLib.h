
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Portions based on clib2 by Olaf Barthel (2002–2016)
** Target OS: AmigaOS
*/

#ifndef AMYLIB_INTERFACES_AMYCLIB_H
#define AMYLIB_INTERFACES_AMYCLIB_H

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

struct AmyCLibIFace
{
	struct InterfaceData Data;
/*    0 */ 	U32							AMYFUNC (*Obtain)( struct AmyCLibIFace *Self );
/*    1 */ 	U32							AMYFUNC (*Release)( struct AmyCLibIFace *Self );
/*    2 */ 	void						AMYFUNC (*Expunge)( struct AmyCLibIFace *Self );
/*    3 */ 	struct Interface *			AMYFUNC (*Clone)( struct AmyCLibIFace *Self );
/*    4 */ 	S32							AMYFUNC (*Priv_Startup_Init)( struct AmyCLibIFace *, STR args, U32 mask );
/*    5 */ 	S32							AMYFUNC (*Priv_Startup_Main)( struct AmyCLibIFace *, int main( int, char ** ) , STR arg_string, S32 arg_length, PTR wbmsg, struct _AmyCLibPublic **pd );
/*    6 */ 	void						AMYFUNC	(*Priv_Startup_Free)( struct AmyCLibIFace * );

	// --

/*    7 */ 	PTR							AMYFUNC (*Priv_Mem_Alloc)( struct AmyCLibIFace *Self, U32 Size );
/*    8 */ 	U32							AMYFUNC (*Priv_Mem_Free)( struct AmyCLibIFace *Self, PTR mem );
/*    9 */ 	PTR							AMYFUNC (*Priv_Mem_Realloc)( struct AmyCLibIFace *Self, PTR oldmem, U32 Size );
/*   10 */ 	struct MemPoolHeader *		AMYFUNC (*Priv_Mem_CreatePool)( struct AmyCLibIFace *Self, U32 size );
/*   11 */ 	U32							AMYFUNC (*Priv_Mem_DeletePool)( struct AmyCLibIFace *Self, struct MemPoolHeader *handle );
/*   12 */ 	U32							AMYFUNC (*Priv_Mem_FlushPool)( struct AmyCLibIFace *Self, struct MemPoolHeader *handle );
/*   13 */ 	PTR							AMYFUNC (*Priv_Mem_AllocPooled)( struct AmyCLibIFace *Self, struct MemPoolHeader *handle, U32 Size );
/*   14 */ 	U32							AMYFUNC (*Priv_Mem_FreePooled)( struct AmyCLibIFace *Self, struct MemPoolHeader *handle, PTR mem );
/*   15 */ 	void						AMYFUNC (*Priv_Check_Abort)( struct AmyCLibIFace *Self );
/*   16 */ 	S32							AMYFUNC (*Priv_Convert_Time_to_TM)( struct AmyCLibIFace *Self, const time_t *time, struct tm *tm );
/*   17 */ 	S32							AMYFUNC (*Priv_Convert_ED_to_Stat)( struct AmyCLibIFace *Self, struct ExamineData *ed, struct stat *st );
/*   18 */ 	S32							AMYFUNC (*Priv_Convert_DS_to_Time)( struct AmyCLibIFace *Self, const struct DateStamp *ds, time_t *time );
/*   19 */ 	S32							AMYFUNC (*Priv_Convert_IOErr_to_ErrNo)( struct AmyCLibIFace *Self, S32 err );
/*   20 */ 	S32							AMYFUNC (*Priv_FB_Read)( struct AmyCLibIFace *Self, PTR file_ptr );
/*   21 */ 	S32							AMYFUNC (*Priv_FB_Read_Fill_Buffer)( struct AmyCLibIFace *Self, PTR file_ptr );
/*   22 */ 	S32							AMYFUNC (*Priv_FB_Read_Drop_Buffer)( struct AmyCLibIFace *Self, PTR file_ptr );
/*   23 */ 	S32							AMYFUNC (*Priv_FB_Write)( struct AmyCLibIFace *Self, PTR file_ptr, S32 mode, S32 c );
/*   24 */ 	S32							AMYFUNC (*Priv_FB_Write_Flush_Buffer)( struct AmyCLibIFace *Self, PTR file_ptr );
/*   25 */ 	S32							AMYFUNC (*Priv_FB_Write_Flush_Buffer2)( struct AmyCLibIFace *Self, PTR file_ptr );

/*   26 */ 	PTR							AMYFUNC (*Priv_FD_Alloc)( struct AmyCLibIFace *Self, U32 ID );
/*   27 */ 	S32							AMYFUNC (*Priv_FD_Free)( struct AmyCLibIFace *Self, PTR file );
/*   28 */ 	PTR							AMYFUNC (*Priv_FD_Init)( struct AmyCLibIFace *Self, PTR is );
/*   29 */ 	S32							AMYFUNC (*Priv_FD_Init_Struct)( struct AmyCLibIFace *Self, PTR file, U32 ID );
/*   30 */ 	S32							AMYFUNC (*Priv_FD_Array_Insert)( struct AmyCLibIFace *Self, PTR Node );
/*   31 */ 	PTR							AMYFUNC (*Priv_FD_Array_Remove)( struct AmyCLibIFace *Self, U32 Pos );

/*   32 */ 	PTR							AMYFUNC (*Priv_FDLockNr)( struct AmyCLibIFace *Self, S32 nr );
/*   33 */ 	PTR							AMYFUNC (*Priv_FDLockStream)( struct AmyCLibIFace *Self, PTR file_ptr );
/*   34 */ 	void						AMYFUNC (*Priv_FDUnlock)( struct AmyCLibIFace *Self, PTR file_ptr );

/*   35 */ 	void						AMYFUNC (*Priv_Print)( struct AmyCLibIFace *Self, struct PrintStruct *ps );
/*   36 */ 	void						AMYFUNC (*Priv_Scan)( struct AmyCLibIFace *Self, struct ScanStruct *ss );

	// --

/*   37 */ 	void						AMYFUNC (*setjmp_longjmp)( struct AmyCLibIFace *, jmp_buf buf, int val );
/*   38 */ 	int							AMYFUNC (*setjmp_setjmp)( struct AmyCLibIFace *, jmp_buf buf );

/*   39 */ 	void *						AMYFUNC (*stdlib_calloc)( struct AmyCLibIFace *Self, size_t num, size_t size );
/*   40 */ 	void *						AMYFUNC (*stdlib_malloc)( struct AmyCLibIFace *Self, size_t size );
/*   41 */ 	void *						AMYFUNC (*stdlib_realloc)( struct AmyCLibIFace *Self, void *mem, size_t size );
/*   42 */ 	void						AMYFUNC (*stdlib_free)( struct AmyCLibIFace *Self, void *mem );
/*   43 */ 	int							AMYFUNC (*stdlib_rand)( struct AmyCLibIFace *Self );
/*   44 */ 	int							AMYFUNC (*stdlib_rand_r)( struct AmyCLibIFace *Self, unsigned int *seed );
/*   45 */ 	void						AMYFUNC (*stdlib_srand)( struct AmyCLibIFace *Self, unsigned int seed );
/*   46 */ 	int							AMYFUNC (*stdlib_atoi)( struct AmyCLibIFace *Self, const char *str );
/*   47 */ 	long						AMYFUNC (*stdlib_strtol)( struct AmyCLibIFace *Self, const char *nptr, char **endptr, int base );

/*   48 */ 	size_t						AMYFUNC (*string_strlen)( struct AmyCLibIFace *Self,const char *str );
/*   49 */ 	size_t						AMYFUNC (*string_strnlen)( struct AmyCLibIFace *Self,const char *str, size_t max );
/*   50 */ 	char *						AMYFUNC (*string_strdup)( struct AmyCLibIFace *Self,const char *str );
/*   51 */ 	char *						AMYFUNC (*string_strndup)( struct AmyCLibIFace *Self,const char *str, size_t max );
/*   52 */ 	char *						AMYFUNC (*string_strcpy)( struct AmyCLibIFace *Self, char *dst, const char *src );
/*   53 */ 	char *						AMYFUNC (*string_strncpy)( struct AmyCLibIFace *Self, char *dst, const char *src, size_t max );
/*   54 */ 	int							AMYFUNC (*string_strcmp)( struct AmyCLibIFace *Self, const char *s1, const char *s2 );
/*   55 */ 	int							AMYFUNC (*string_strncmp)( struct AmyCLibIFace *Self, const char *s1, const char *s2, size_t max );
/*   56 */ 	int							AMYFUNC (*string_memcmp)( struct AmyCLibIFace *Self, const void *s1, const void *s2, size_t len );
/*   57 */ 	void *						AMYFUNC (*string_memmove)( struct AmyCLibIFace *Self, void *dst, const void *src, size_t len );
/*   58 */ 	PTR							AMYFUNC (*string_memcpy)( struct AmyCLibIFace *Self, void *dst, const void *src, size_t len );
/*   59 */ 	void *						AMYFUNC (*string_memset)( struct AmyCLibIFace *Self, void *s, int c, size_t n );
/*   60 */ 	char *					 	AMYFUNC (*string_strcat)( struct AmyCLibIFace *Self, char *dst, const char *src );

/*   61 */ 	void						AMYFUNC (*strings_bzero)( struct AmyCLibIFace *Self, void *mem, size_t len );

/*   62 */ 	int							AMYFUNC (*ctype_isalpha)( struct AmyCLibIFace *Self, int c );
/*   63 */ 	int							AMYFUNC (*ctype_isdigit)( struct AmyCLibIFace *Self, int c );
/*   64 */ 	int							AMYFUNC (*ctype_isspace)( struct AmyCLibIFace *Self, int c );
/*   65 */ 	int							AMYFUNC (*ctype_isupper)( struct AmyCLibIFace *Self, int c );
/*   66 */ 	int							AMYFUNC (*ctype_isxdigit)( struct AmyCLibIFace *Self, int c );
/*   67 */ 	int							AMYFUNC (*ctype_tolower)( struct AmyCLibIFace *Self, int c );
/*   68 */ 	int							AMYFUNC (*ctype_toupper)( struct AmyCLibIFace *Self, int c );

/*   69 */ 	struct tm *					AMYFUNC (*time_localtime)( struct AmyCLibIFace *Self, const time_t *time );
/*   70 */ 	time_t						AMYFUNC (*time_time)( struct AmyCLibIFace *Self, time_t *ptr );

/*   71 */ 	FILE *						AMYFUNC (*stdio_fopen)( struct AmyCLibIFace *Self, const char *filename, const char *mode );
/*   72 */ 	long						AMYFUNC (*stdio_ftell)( struct AmyCLibIFace *Self, FILE *stream );
/*   73 */ 	int							AMYFUNC (*stdio_fgetpos)( struct AmyCLibIFace *Self, FILE *stream, fpos_t *pos );
/*   74 */ 	void						AMYFUNC (*stdio_flockfile)( struct AmyCLibIFace *Self, FILE *stream );
/*   75 */ 	void						AMYFUNC (*stdio_funlockfile)( struct AmyCLibIFace *Self, FILE *stream );
/*   76 */ 	int							AMYFUNC (*stdio_fflush)( struct AmyCLibIFace *Self, FILE *stream );
/*   77 */ 	int							AMYFUNC (*stdio_puts)( struct AmyCLibIFace *Self, const char *str );
/*   78 */ 	int							AMYFUNC (*stdio_putchar)( struct AmyCLibIFace *Self, int c );
/*   79 */ 	int							AMYFUNC (*stdio_fputc)( struct AmyCLibIFace *Self, int c, FILE *stream );
/*   80 */ 	int							AMYFUNC (*stdio_setvbuf)( struct AmyCLibIFace *Self, FILE *stream, char *buf, int mode, size_t size );
/*   81 */ 	int							AMYFUNC (*stdio_fclose)( struct AmyCLibIFace *Self, FILE *stream );
/*   82 */ 	int							AMYFUNC (*stdio_fseek)( struct AmyCLibIFace *Self, FILE *stream, long offset, int wherefrom );
/*   83 */ 	int							AMYFUNC (*stdio_fseeko)( struct AmyCLibIFace *Self, FILE *stream, off_t offset, int wherefrom );
/*   84 */ 	int							AMYFUNC (*stdio_vprintf)( struct AmyCLibIFace *Self, const char *fmt, va_list ap );
/*   85 */ 	int							AMYFUNC (*stdio_vsprintf)( struct AmyCLibIFace *Self, char *buf, const char *fmt, va_list ap );
/*   86 */ 	int							AMYFUNC (*stdio_fputc_unlocked)( struct AmyCLibIFace *Self, int c, FILE *stream );
/*   87 */ 	int							AMYFUNC (*stdio_vsnprintf)( struct AmyCLibIFace *Self, char *buf, size_t size, const char *fmt, va_list ap );
/*   88 */ 	int							AMYFUNC (*fcntl_open)( struct AmyCLibIFace *Self, const char *path, int oflag, ... );
/*   89 */ 	int							AMYFUNC (*unistd_close)( struct AmyCLibIFace *Self, int fildes );
// --
/*   90 */ 	int							AMYFUNC (*stdio_ungetc)( struct AmyCLibIFace *Self, int c, FILE *stream );
/*   91 */ 	size_t						AMYFUNC (*stdio_fread)( struct AmyCLibIFace *Self, void *ptr, size_t size, size_t count, FILE *stream );
/*   92 */ 	float						AMYFUNC (*stdlib_strtof)( struct AmyCLibIFace *Self, const char *str, char **ptr );
/*   93 */ 	double						AMYFUNC (*stdlib_strtod)( struct AmyCLibIFace *Self, const char *str, char **ptr );
/*   94 */ 	uintmax_t					AMYFUNC (*inttypes_strtoumax)( struct AmyCLibIFace *Self, const char *nptr, char **endptr, int base );
/*   95 */ 	intmax_t					AMYFUNC (*inttypes_strtoimax)( struct AmyCLibIFace *Self, const char *nptr, char **endptr, int base );
/*   96 */ 	void						AMYFUNC (*stdio_clearerr)( struct AmyCLibIFace *Self, FILE *stream );
/*   97 */ 	int							AMYFUNC (*strings_strcasecmp)( struct AmyCLibIFace *Self, const char *s1, const char *s2 );
/*   98 */ 	int							AMYFUNC (*strings_strncasecmp)( struct AmyCLibIFace *Self, const char *s1, const char *s2, size_t maxlen );
/*   99 */ 	double 						AMYFUNC (*math_d__get_huge_val)( struct AmyCLibIFace *Self );
/*  100 */ 	double						AMYFUNC (*math_d__inf)( struct AmyCLibIFace *Self );
/*  101 */ 	int							AMYFUNC (*math_d__isinf)( struct AmyCLibIFace *Self, double x );
/*  102 */ 	int							AMYFUNC (*math_d__isnan)( struct AmyCLibIFace *Self, double x );
/*  103 */ 	double						AMYFUNC (*math_d_nan)( struct AmyCLibIFace *Self, const char *xx );
/*  104 */ 	double						AMYFUNC (*math_d_pow)( struct AmyCLibIFace *Self, double x, double y );
/*  105 */ 	double						AMYFUNC (*math_d_fabs)( struct AmyCLibIFace *Self, double x );
/*  106 */ 	double						AMYFUNC (*math_d_scalbn)( struct AmyCLibIFace *Self, double x, int n );
/*  107 */ 	double						AMYFUNC (*math_d_sqrt)( struct AmyCLibIFace *Self, double x );
/*  108 */ 	double						AMYFUNC (*math_d_copysign)( struct AmyCLibIFace *Self, double x, double y );
/*  109 */ 	int							AMYFUNC (*stdio_vsscanf)( struct AmyCLibIFace *Self, const char *, const char *, va_list );
/*  110 */ 	size_t						AMYFUNC (*time_strftime)( struct AmyCLibIFace *Self, char *s, size_t maxsize, const char *format, const struct tm *timptr );
/*  111 */ 	void						AMYFUNC (*signal_signal)( struct AmyCLibIFace *Self, int sig, void (*func)(int) );
/*  112 */ 	int							AMYFUNC (*signal_raise)( struct AmyCLibIFace *Self, int sig );
/*  113 */ 	void						AMYFUNC (*stdlib_abort)( struct AmyCLibIFace *Self );
/*  114 */ 	void						AMYFUNC (*stdlib__Exit)( struct AmyCLibIFace *Self, int rc );
/*  115 */	int							AMYFUNC (*stdio_vasprintf)( struct AmyCLibIFace *Self, char **ret, const char *fmt, va_list ap );
/*  116 */	void						AMYFUNC (*assert_assert)( struct AmyCLibIFace *Self, const char *filename, int linenumber, const char *function, const char *expression );
/*  117 */	void						AMYFUNC (*stdlib_exit)( struct AmyCLibIFace *Self, int rc );
/*  118 */ 	int							AMYFUNC (*ctype_islower)( struct AmyCLibIFace *Self, int c );
/*  119 */	int							AMYFUNC (*stdio_fgetc)(struct AmyCLibIFace *, FILE *stream);
/*  120 */	struct tm *					AMYFUNC (*time_gmtime)(struct AmyCLibIFace *, const time_t *time );
/*  121 */	struct tm *					AMYFUNC (*time_gmtime_r)(struct AmyCLibIFace *, const time_t *time, struct tm *tm );
/*  122 */	int							AMYFUNC (*stdio_ferror)( struct AmyCLibIFace *Self, FILE *stream );
/*  123 */	void						AMYFUNC (*Priv_Print_Log)( struct AmyCLibIFace *Self );
/*  124 */	void						AMYFUNC (*Priv_Func_Log)( struct AmyCLibIFace *Self, S32 xx );
/*  125 */ 	size_t						AMYFUNC (*string_strcspn)( struct AmyCLibIFace *Self, const char *s1, const char *s2 );
/*  126 */ 	size_t						AMYFUNC (*string_strspn)( struct AmyCLibIFace *Self, const char *s1, const char *s2 );
/*  127 */ 	char *						AMYFUNC (*string_strpbrk)( struct AmyCLibIFace *Self, const char *s1, const char *s2 );
/*  128 */ 	char *						AMYFUNC (*string_strchr)( struct AmyCLibIFace *Self, const char *str, int c );
/*  129 */	int							AMYFUNC	(*stdio_fileno)( struct AmyCLibIFace *Self, FILE *stream );


/*  130 */	int							AMYFUNC (*stdio_fprintf)( struct AmyCLibIFace *Self, FILE *stream, const char *format, ... );
/*  131 */	int							AMYFUNC (*stdio_fputs)( struct AmyCLibIFace *Self, const void *s, FILE *stream );
/*  132 */	size_t						AMYFUNC (*stdio_fwrite)( struct AmyCLibIFace *Self, const void *ptr, size_t size, size_t nitems, FILE *stream );
/*  133 */	int							AMYFUNC (*stdio_putc)( struct AmyCLibIFace *Self, int c, FILE *stream );
/*  134 */	void						AMYFUNC (*stdlib__exit)( struct AmyCLibIFace *Self, int status );
/*  135 */	long						AMYFUNC (*stdlib_atol)( struct AmyCLibIFace *Self, const char *str );
/*  136 */	char *						AMYFUNC (*stdlib_getenv)( struct AmyCLibIFace *Self, const char *name );
/*  137 */	void						AMYFUNC (*stdlib_qsort)( struct AmyCLibIFace *Self, void *base, size_t nel, size_t width, int (*compar)(const void *, const void *));
/*  138 */	int							AMYFUNC (*sys_stat_chmod)( struct AmyCLibIFace *Self, const char *path, mode_t mode );
/*  139 */	int							AMYFUNC (*sys_stat_mkdir)( struct AmyCLibIFace *Self, const char *path, mode_t mode );
/*  140 */	char *						AMYFUNC (*sys_stat_mktemp)( struct AmyCLibIFace *Self, char *template );
/*  141 */	int							AMYFUNC (*sys_stat_stat)( struct AmyCLibIFace *Self, const char *path, struct stat *buf );
/*  142 */	char *						AMYFUNC (*time_ctime)( struct AmyCLibIFace *Self, const time_t *clock );
/*  143 */	int							AMYFUNC (*unistd_unlink)( struct AmyCLibIFace *Self, const char *path );
/*  144 */	char *						AMYFUNC (*string_strncat)( struct AmyCLibIFace *Self, char *d, const char *s, size_t n );
/*  145 */	int							AMYFUNC (*stdio_vfprintf)( struct AmyCLibIFace *Self, FILE *stream, const char *format, va_list ap );
/*  146 */	mode_t						AMYFUNC (*sys_stat_umask)( struct AmyCLibIFace *Self, mode_t cmask );
/*  147 */	pid_t						AMYFUNC (*unistd_getpid)( struct AmyCLibIFace *Self );
/*  148 */	char *						AMYFUNC (*unistd_getcwd)( struct AmyCLibIFace *Self, char *buf, size_t size );
/*  149 */	int							AMYFUNC (*sys_stat_fstat)( struct AmyCLibIFace *Self, int fildes, struct stat *buf );
/*  150 */	int							AMYFUNC (*sys_stat_lstat)( struct AmyCLibIFace *Self, const char *path, struct stat *buf );
/*  151 */	int							AMYFUNC (*unistd_access)( struct AmyCLibIFace *Self, const char *path, int amode );
/*  152 */	int							AMYFUNC (*unistd_fcntl_ap)( struct AmyCLibIFace *Self, int fildes, int cmd, va_list ap );
/*  153 */	ssize_t						AMYFUNC (*unistd_read)( struct AmyCLibIFace *Self, int fildes, void *buf, size_t nbyte );
/*  154 */	double						AMYFUNC (*stdlib_atof)( struct AmyCLibIFace *Self, const char *str );
/*  155 */	int							AMYFUNC (*stdio_getc)( struct AmyCLibIFace *Self, FILE *stream );
/*  156 */	int							AMYFUNC (*utime_utime)( struct AmyCLibIFace *Self, const char *str, const struct utimbuf *buf );
/*  157 */	int							AMYFUNC (*unistd_link)( struct AmyCLibIFace *Self, const char *path1, const char *path2 );
/*  158 */	int							AMYFUNC (*unistd_isatty)( struct AmyCLibIFace *Self, int fildes );
/*  159 */	void						AMYFUNC (*stdio_perror)( struct AmyCLibIFace *Self, const char *s );
/*  160 */	int							AMYFUNC (*stdio_remove)( struct AmyCLibIFace *Self, const char *path );
/*  161 */	int							AMYFUNC (*stdio_rename)( struct AmyCLibIFace *Self, const char *old, const char *new );
/*  162 */	int							AMYFUNC (*unistd_rmdir)( struct AmyCLibIFace *Self, const char *path );
/*  163 */	int							AMYFUNC (*stdio_feof)( struct AmyCLibIFace *Self, FILE *stream );
/*  164 */	char *						AMYFUNC (*stdio_fgets)( struct AmyCLibIFace *Self, char *s, int n, FILE *stream );
/*  165 */	void						AMYFUNC (*stdio_rewind)( struct AmyCLibIFace *Self, FILE *stream );
/*  166 */	int							AMYFUNC (*stdio_vfscanf)( struct AmyCLibIFace *Self, FILE *stream, const char *format, va_list arg );
/*  167 */	size_t						AMYFUNC (*wchar_mbrtowc)( struct AmyCLibIFace *Self, wchar_t *pwc, const char *s, size_t n, mbstate_t *ps );
/*  168 */	int							AMYFUNC (*stdio_getchar)( struct AmyCLibIFace *Self );
/*  169 */	char *						AMYFUNC (*string_strstr)( struct AmyCLibIFace *Self, const char *s1, const char *s2 );
/*  170 */	size_t						AMYFUNC (*wchar_mbstowcs)( struct AmyCLibIFace *Self, wchar_t *pwcs, const char *s, size_t n );
/*  171 */	uid_t						AMYFUNC (*unistd_geteuid)( struct AmyCLibIFace *Self );
/*  172 */	gid_t						AMYFUNC (*unistd_getegid)( struct AmyCLibIFace *Self );
/*  173 */	char *						AMYFUNC (*locale_setlocale)( struct AmyCLibIFace *Self, int category, const char *locale );
/*  174 */	ssize_t						AMYFUNC (*stdio_getline)( struct AmyCLibIFace *Self, char **lineptr, size_t *n, FILE *stream );
/*  175 */	ssize_t						AMYFUNC (*stdio_getdelim)( struct AmyCLibIFace *Self, char **lineptr, size_t *n, int delimiter, FILE *stream );
/*  176 */	int							AMYFUNC (*stdio_putc_unlocked)( struct AmyCLibIFace *Self, int c, FILE *stream );
/*  177 */	int							AMYFUNC (*ctype_isprint)( struct AmyCLibIFace *Self, int c );
/*  178 */	char *						AMYFUNC (*string_strerror)( struct AmyCLibIFace *Self, int errnum );
/*  179 */	int							AMYFUNC (*string_strerror_r)( struct AmyCLibIFace *Self, int errnum, char *buf, size_t buflen );
/*  180 */	int							AMYFUNC (*sys_time_gettimeofday)( struct AmyCLibIFace *Self, struct timeval *tp, void *tzp );


};

// --

#endif
