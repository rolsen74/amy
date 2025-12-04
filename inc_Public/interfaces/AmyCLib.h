
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
#include <getopt.h>
#include <dirent.h>
#include <sys/statvfs.h>
#include <sys/mount.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <langinfo.h>
#include <ftw.h>
#include <process.h>

// --
struct PrintStruct;
struct ScanStruct;

struct AmyCLibIFace
{
	struct InterfaceData Data;
/*    0 */	U32							AMY_FUNC (*Obtain)( struct AmyCLibIFace *Self );
/*    1 */	U32							AMY_FUNC (*Release)( struct AmyCLibIFace *Self );
/*    2 */	void						AMY_FUNC (*Expunge)( struct AmyCLibIFace *Self );
/*    3 */	struct Interface *			AMY_FUNC (*Clone)( struct AmyCLibIFace *Self );
/*    4 */	S32							AMY_FUNC (*Priv_Startup_Init)( struct AmyCLibIFace *, STR args, U32 mask );
/*    5 */	S32							AMY_FUNC (*Priv_Startup_Main)( struct AmyCLibIFace *, int main( int, char ** ) , STR arg_string, S32 arg_length, PTR wbmsg, struct _AmyCLibPublic **pd );
/*    6 */	void						AMY_FUNC	(*Priv_Startup_Free)( struct AmyCLibIFace * );

	// --

/*    7 */	PTR							AMY_FUNC (*Priv_Mem_Alloc)( struct AmyCLibIFace *Self, U32 Size );
/*    8 */	U32							AMY_FUNC (*Priv_Mem_Free)( struct AmyCLibIFace *Self, PTR mem );
/*    9 */	PTR							AMY_FUNC (*Priv_Mem_Realloc)( struct AmyCLibIFace *Self, PTR oldmem, U32 Size );
/*   10 */	struct MemPoolHeader *		AMY_FUNC (*Priv_Mem_CreatePool)( struct AmyCLibIFace *Self, U32 size );
/*   11 */	U32							AMY_FUNC (*Priv_Mem_DeletePool)( struct AmyCLibIFace *Self, struct MemPoolHeader *handle );
/*   12 */	U32							AMY_FUNC (*Priv_Mem_FlushPool)( struct AmyCLibIFace *Self, struct MemPoolHeader *handle );
/*   13 */	PTR							AMY_FUNC (*Priv_Mem_AllocPooled)( struct AmyCLibIFace *Self, struct MemPoolHeader *handle, U32 Size );
/*   14 */	U32							AMY_FUNC (*Priv_Mem_FreePooled)( struct AmyCLibIFace *Self, struct MemPoolHeader *handle, PTR mem );
/*   15 */	void						AMY_FUNC (*Priv_Check_Abort)( struct AmyCLibIFace *Self );
/*   16 */	S32							AMY_FUNC (*Priv_Convert_Time_to_TM)( struct AmyCLibIFace *Self, const time_t *time, struct tm *tm );
/*   17 */	S32							AMY_FUNC (*Priv_Convert_ED_to_Stat)( struct AmyCLibIFace *Self, struct ExamineData *ed, struct stat *st );
/*   18 */	S32							AMY_FUNC (*Priv_Convert_DS_to_Time)( struct AmyCLibIFace *Self, const struct DateStamp *ds, time_t *time );
/*   19 */	S32							AMY_FUNC (*Priv_Convert_IOErr_to_ErrNo)( struct AmyCLibIFace *Self, S32 err );
/*   20 */	S32							AMY_FUNC (*Priv_FB_Read)( struct AmyCLibIFace *Self, PTR file_ptr );
/*   21 */	S32							AMY_FUNC (*Priv_FB_Read_Fill_Buffer)( struct AmyCLibIFace *Self, PTR file_ptr );
/*   22 */	S32							AMY_FUNC (*Priv_FB_Read_Drop_Buffer)( struct AmyCLibIFace *Self, PTR file_ptr );
/*   23 */	S32							AMY_FUNC (*Priv_FB_Write)( struct AmyCLibIFace *Self, PTR file_ptr, S32 mode, S32 c );
/*   24 */	S32							AMY_FUNC (*Priv_FB_Write_Flush_Buffer)( struct AmyCLibIFace *Self, PTR file_ptr );
/*   25 */	S32							AMY_FUNC (*Priv_FB_Write_Flush_Buffer2)( struct AmyCLibIFace *Self, PTR file_ptr );

/*   26 */	PTR							AMY_FUNC (*Priv_FD_Alloc)( struct AmyCLibIFace *Self, U32 ID );
/*   27 */	S32							AMY_FUNC (*Priv_FD_Free)( struct AmyCLibIFace *Self, PTR file );
/*   28 */	PTR							AMY_FUNC (*Priv_FD_Init)( struct AmyCLibIFace *Self, PTR is );
/*   29 */	S32							AMY_FUNC (*Priv_FD_Init_Struct)( struct AmyCLibIFace *Self, PTR file, U32 ID );
/*   30 */	S32							AMY_FUNC (*Priv_FD_Array_Insert)( struct AmyCLibIFace *Self, PTR Node );
/*   31 */	PTR							AMY_FUNC (*Priv_FD_Array_Remove)( struct AmyCLibIFace *Self, U32 Pos );

/*   32 */	PTR							AMY_FUNC (*Priv_FDLockNr)( struct AmyCLibIFace *Self, S32 nr );
/*   33 */	PTR							AMY_FUNC (*Priv_FDLockStream)( struct AmyCLibIFace *Self, PTR file_ptr );
/*   34 */	void						AMY_FUNC (*Priv_FDUnlock)( struct AmyCLibIFace *Self, PTR file_ptr );

/*   35 */	void						AMY_FUNC (*Priv_Print)( struct AmyCLibIFace *Self, struct PrintStruct *ps );
/*   36 */	void						AMY_FUNC (*Priv_Scan)( struct AmyCLibIFace *Self, struct ScanStruct *ss );

	// --

/*   37 */	void						AMY_FUNC (*setjmp_longjmp)( struct AmyCLibIFace *, jmp_buf buf, int val );
/*   38 */	int							AMY_FUNC (*setjmp_setjmp)( struct AmyCLibIFace *, jmp_buf buf );

/*   39 */	void *						AMY_FUNC (*stdlib_calloc)( struct AmyCLibIFace *Self, size_t num, size_t size );
/*   40 */	void *						AMY_FUNC (*stdlib_malloc)( struct AmyCLibIFace *Self, size_t size );
/*   41 */	void *						AMY_FUNC (*stdlib_realloc)( struct AmyCLibIFace *Self, void *mem, size_t size );
/*   42 */	void						AMY_FUNC (*stdlib_free)( struct AmyCLibIFace *Self, void *mem );
/*   43 */	int							AMY_FUNC (*stdlib_rand)( struct AmyCLibIFace *Self );
/*   44 */	int							AMY_FUNC (*stdlib_rand_r)( struct AmyCLibIFace *Self, unsigned int *seed );
/*   45 */	void						AMY_FUNC (*stdlib_srand)( struct AmyCLibIFace *Self, unsigned int seed );
/*   46 */	int							AMY_FUNC (*stdlib_atoi)( struct AmyCLibIFace *Self, const char *str );
/*   47 */	long						AMY_FUNC (*stdlib_strtol)( struct AmyCLibIFace *Self, const char *nptr, char **endptr, int base );

/*   48 */	size_t						AMY_FUNC (*string_strlen)( struct AmyCLibIFace *Self,const char *str );
/*   49 */	size_t						AMY_FUNC (*string_strnlen)( struct AmyCLibIFace *Self,const char *str, size_t max );
/*   50 */	char *						AMY_FUNC (*string_strdup)( struct AmyCLibIFace *Self,const char *str );
/*   51 */	char *						AMY_FUNC (*string_strndup)( struct AmyCLibIFace *Self,const char *str, size_t max );
/*   52 */	char *						AMY_FUNC (*string_strcpy)( struct AmyCLibIFace *Self, char *dst, const char *src );
/*   53 */	char *						AMY_FUNC (*string_strncpy)( struct AmyCLibIFace *Self, char *dst, const char *src, size_t max );
/*   54 */	int							AMY_FUNC (*string_strcmp)( struct AmyCLibIFace *Self, const char *s1, const char *s2 );
/*   55 */	int							AMY_FUNC (*string_strncmp)( struct AmyCLibIFace *Self, const char *s1, const char *s2, size_t max );
/*   56 */	int							AMY_FUNC (*string_memcmp)( struct AmyCLibIFace *Self, const void *s1, const void *s2, size_t len );
/*   57 */	void *						AMY_FUNC (*string_memmove)( struct AmyCLibIFace *Self, void *dst, const void *src, size_t len );
/*   58 */	PTR							AMY_FUNC (*string_memcpy)( struct AmyCLibIFace *Self, void *dst, const void *src, size_t len );
/*   59 */	void *						AMY_FUNC (*string_memset)( struct AmyCLibIFace *Self, void *s, int c, size_t n );
/*   60 */	char *					 	AMY_FUNC (*string_strcat)( struct AmyCLibIFace *Self, char *dst, const char *src );

/*   61 */	void						AMY_FUNC (*strings_bzero)( struct AmyCLibIFace *Self, void *mem, size_t len );

/*   62 */	int							AMY_FUNC (*ctype_isalpha)( struct AmyCLibIFace *Self, int c );
/*   63 */	int							AMY_FUNC (*ctype_isdigit)( struct AmyCLibIFace *Self, int c );
/*   64 */	int							AMY_FUNC (*ctype_isspace)( struct AmyCLibIFace *Self, int c );
/*   65 */	int							AMY_FUNC (*ctype_isupper)( struct AmyCLibIFace *Self, int c );
/*   66 */	int							AMY_FUNC (*ctype_isxdigit)( struct AmyCLibIFace *Self, int c );
/*   67 */	int							AMY_FUNC (*ctype_tolower)( struct AmyCLibIFace *Self, int c );
/*   68 */	int							AMY_FUNC (*ctype_toupper)( struct AmyCLibIFace *Self, int c );

/*   69 */	struct tm *					AMY_FUNC (*time_localtime)( struct AmyCLibIFace *Self, const time_t *time );
/*   70 */	time_t						AMY_FUNC (*time_time)( struct AmyCLibIFace *Self, time_t *ptr );

/*   71 */	FILE *						AMY_FUNC (*stdio_fopen)( struct AmyCLibIFace *Self, const char *filename, const char *mode );
/*   72 */	long						AMY_FUNC (*stdio_ftell)( struct AmyCLibIFace *Self, FILE *stream );
/*   73 */	int							AMY_FUNC (*stdio_fgetpos)( struct AmyCLibIFace *Self, FILE *stream, fpos_t *pos );
/*   74 */	void						AMY_FUNC (*stdio_flockfile)( struct AmyCLibIFace *Self, FILE *stream );
/*   75 */	void						AMY_FUNC (*stdio_funlockfile)( struct AmyCLibIFace *Self, FILE *stream );
/*   76 */	int							AMY_FUNC (*stdio_fflush)( struct AmyCLibIFace *Self, FILE *stream );
/*   77 */	int							AMY_FUNC (*stdio_puts)( struct AmyCLibIFace *Self, const char *str );
/*   78 */	int							AMY_FUNC (*stdio_putchar)( struct AmyCLibIFace *Self, int c );
/*   79 */	int							AMY_FUNC (*stdio_fputc)( struct AmyCLibIFace *Self, int c, FILE *stream );
/*   80 */	int							AMY_FUNC (*stdio_setvbuf)( struct AmyCLibIFace *Self, FILE *stream, char *buf, int mode, size_t size );
/*   81 */	int							AMY_FUNC (*stdio_fclose)( struct AmyCLibIFace *Self, FILE *stream );
/*   82 */	int							AMY_FUNC (*stdio_fseek)( struct AmyCLibIFace *Self, FILE *stream, long offset, int wherefrom );
/*   83 */	int							AMY_FUNC (*stdio_fseeko)( struct AmyCLibIFace *Self, FILE *stream, off_t offset, int wherefrom );
/*   84 */	int							AMY_FUNC (*stdio_vprintf)( struct AmyCLibIFace *Self, const char *fmt, va_list ap );
/*   85 */	int							AMY_FUNC (*stdio_vsprintf)( struct AmyCLibIFace *Self, char *buf, const char *fmt, va_list ap );
/*   86 */	int							AMY_FUNC (*stdio_fputc_unlocked)( struct AmyCLibIFace *Self, int c, FILE *stream );
/*   87 */	int							AMY_FUNC (*stdio_vsnprintf)( struct AmyCLibIFace *Self, char *buf, size_t size, const char *fmt, va_list ap );
/*   88 */	int							AMY_FUNC (*fcntl_open)( struct AmyCLibIFace *Self, const char *path, int oflag, ... );
/*   89 */	int							AMY_FUNC (*unistd_close)( struct AmyCLibIFace *Self, int fildes );
// --
/*   90 */	int							AMY_FUNC (*stdio_ungetc)( struct AmyCLibIFace *Self, int c, FILE *stream );
/*   91 */	size_t						AMY_FUNC (*stdio_fread)( struct AmyCLibIFace *Self, void *ptr, size_t size, size_t count, FILE *stream );
/*   92 */	float						AMY_FUNC (*stdlib_strtof)( struct AmyCLibIFace *Self, const char *str, char **ptr );
/*   93 */	double						AMY_FUNC (*stdlib_strtod)( struct AmyCLibIFace *Self, const char *str, char **ptr );
/*   94 */	uintmax_t					AMY_FUNC (*inttypes_strtoumax)( struct AmyCLibIFace *Self, const char *nptr, char **endptr, int base );
/*   95 */	intmax_t					AMY_FUNC (*inttypes_strtoimax)( struct AmyCLibIFace *Self, const char *nptr, char **endptr, int base );
/*   96 */	void						AMY_FUNC (*stdio_clearerr)( struct AmyCLibIFace *Self, FILE *stream );
/*   97 */	int							AMY_FUNC (*strings_strcasecmp)( struct AmyCLibIFace *Self, const char *s1, const char *s2 );
/*   98 */	int							AMY_FUNC (*strings_strncasecmp)( struct AmyCLibIFace *Self, const char *s1, const char *s2, size_t maxlen );
/*   99 */	double 						AMY_FUNC (*math_d__get_huge_val)( struct AmyCLibIFace *Self );
/*  100 */	double						AMY_FUNC (*math_d__inf)( struct AmyCLibIFace *Self );
/*  101 */	int							AMY_FUNC (*math_d__isinf)( struct AmyCLibIFace *Self, double x );
/*  102 */	int							AMY_FUNC (*math_d__isnan)( struct AmyCLibIFace *Self, double x );
/*  103 */	double						AMY_FUNC (*math_d_nan)( struct AmyCLibIFace *Self, const char *xx );
/*  104 */	double						AMY_FUNC (*math_d_pow)( struct AmyCLibIFace *Self, double x, double y );
/*  105 */	double						AMY_FUNC (*math_d_fabs)( struct AmyCLibIFace *Self, double x );
/*  106 */	double						AMY_FUNC (*math_d_scalbn)( struct AmyCLibIFace *Self, double x, int n );
/*  107 */	double						AMY_FUNC (*math_d_sqrt)( struct AmyCLibIFace *Self, double x );
/*  108 */	double						AMY_FUNC (*math_d_copysign)( struct AmyCLibIFace *Self, double x, double y );
/*  109 */	int							AMY_FUNC (*stdio_vsscanf)( struct AmyCLibIFace *Self, const char *, const char *, va_list );
/*  110 */	size_t						AMY_FUNC (*time_strftime)( struct AmyCLibIFace *Self, char *s, size_t maxsize, const char *format, const struct tm *timptr );
/*  111 */	sighandler_t				AMY_FUNC (*signal_signal)( struct AmyCLibIFace *Self, int sig, sighandler_t func );
/*  112 */	int							AMY_FUNC (*signal_raise)( struct AmyCLibIFace *Self, int sig );
/*  113 */	void						AMY_FUNC (*stdlib_abort)( struct AmyCLibIFace *Self );
/*  114 */	void						AMY_FUNC (*stdlib__Exit)( struct AmyCLibIFace *Self, int rc );
/*  115 */	int							AMY_FUNC (*stdio_vasprintf)( struct AmyCLibIFace *Self, char **ret, const char *fmt, va_list ap );
/*  116 */	void						AMY_FUNC (*assert_assert)( struct AmyCLibIFace *Self, const char *filename, int linenumber, const char *function, const char *expression );
/*  117 */	void						AMY_FUNC (*stdlib_exit)( struct AmyCLibIFace *Self, int rc );
/*  118 */	int							AMY_FUNC (*ctype_islower)( struct AmyCLibIFace *Self, int c );
/*  119 */	int							AMY_FUNC (*stdio_fgetc)(struct AmyCLibIFace *, FILE *stream);
/*  120 */	struct tm *					AMY_FUNC (*time_gmtime)(struct AmyCLibIFace *, const time_t *time );
/*  121 */	struct tm *					AMY_FUNC (*time_gmtime_r)(struct AmyCLibIFace *, const time_t *time, struct tm *tm );
/*  122 */	int							AMY_FUNC (*stdio_ferror)( struct AmyCLibIFace *Self, FILE *stream );
/*  123 */	void						AMY_FUNC (*Priv_Print_Log)( struct AmyCLibIFace *Self );
/*  124 */	void						AMY_FUNC (*Priv_Func_Log)( struct AmyCLibIFace *Self, S32 xx );
/*  125 */	size_t						AMY_FUNC (*string_strcspn)( struct AmyCLibIFace *Self, const char *s1, const char *s2 );
/*  126 */	size_t						AMY_FUNC (*string_strspn)( struct AmyCLibIFace *Self, const char *s1, const char *s2 );
/*  127 */	char *						AMY_FUNC (*string_strpbrk)( struct AmyCLibIFace *Self, const char *s1, const char *s2 );
/*  128 */	char *						AMY_FUNC (*string_strchr)( struct AmyCLibIFace *Self, const char *str, int c );
/*  129 */	int							AMY_FUNC	(*stdio_fileno)( struct AmyCLibIFace *Self, FILE *stream );


/*  130 */	int							AMY_FUNC (*stdio_fprintf)( struct AmyCLibIFace *Self, FILE *stream, const char *format, ... );
/*  131 */	int							AMY_FUNC (*stdio_fputs)( struct AmyCLibIFace *Self, const void *s, FILE *stream );
/*  132 */	size_t						AMY_FUNC (*stdio_fwrite)( struct AmyCLibIFace *Self, const void *ptr, size_t size, size_t nitems, FILE *stream );
/*  133 */	int							AMY_FUNC (*stdio_putc)( struct AmyCLibIFace *Self, int c, FILE *stream );
/*  134 */	void						AMY_FUNC (*stdlib__exit)( struct AmyCLibIFace *Self, int status );
/*  135 */	long						AMY_FUNC (*stdlib_atol)( struct AmyCLibIFace *Self, const char *str );
/*  136 */	char *						AMY_FUNC (*stdlib_getenv)( struct AmyCLibIFace *Self, const char *name );
/*  137 */	void						AMY_FUNC (*stdlib_qsort)( struct AmyCLibIFace *Self, void *base, size_t nel, size_t width, int (*compar)(const void *, const void *));
/*  138 */	int							AMY_FUNC (*sys_stat_chmod)( struct AmyCLibIFace *Self, const char *path, mode_t mode );
/*  139 */	int							AMY_FUNC (*sys_stat_mkdir)( struct AmyCLibIFace *Self, const char *path, mode_t mode );
/*  140 */	char *						AMY_FUNC (*sys_stat_mktemp)( struct AmyCLibIFace *Self, char *template );
/*  141 */	int							AMY_FUNC (*sys_stat_stat)( struct AmyCLibIFace *Self, const char *path, struct stat *buf );
/*  142 */	char *						AMY_FUNC (*time_ctime)( struct AmyCLibIFace *Self, const time_t *clock );
/*  143 */	int							AMY_FUNC (*unistd_unlink)( struct AmyCLibIFace *Self, const char *path );
/*  144 */	char *						AMY_FUNC (*string_strncat)( struct AmyCLibIFace *Self, char *d, const char *s, size_t n );
/*  145 */	int							AMY_FUNC (*stdio_vfprintf)( struct AmyCLibIFace *Self, FILE *stream, const char *format, va_list ap );
/*  146 */	mode_t						AMY_FUNC (*sys_stat_umask)( struct AmyCLibIFace *Self, mode_t cmask );
/*  147 */	pid_t						AMY_FUNC (*unistd_getpid)( struct AmyCLibIFace *Self );
/*  148 */	char *						AMY_FUNC (*unistd_getcwd)( struct AmyCLibIFace *Self, char *buf, size_t size );
/*  149 */	int							AMY_FUNC (*sys_stat_fstat)( struct AmyCLibIFace *Self, int fildes, struct stat *buf );
/*  150 */	int							AMY_FUNC (*sys_stat_lstat)( struct AmyCLibIFace *Self, const char *path, struct stat *buf );
/*  151 */	int							AMY_FUNC (*unistd_access)( struct AmyCLibIFace *Self, const char *path, int amode );
/*  152 */	int							AMY_FUNC (*unistd_fcntl_ap)( struct AmyCLibIFace *Self, int fildes, int cmd, va_list ap );
/*  153 */	ssize_t						AMY_FUNC (*unistd_read)( struct AmyCLibIFace *Self, int fildes, void *buf, size_t nbyte );
/*  154 */	double						AMY_FUNC (*stdlib_atof)( struct AmyCLibIFace *Self, const char *str );
/*  155 */	int							AMY_FUNC (*stdio_getc)( struct AmyCLibIFace *Self, FILE *stream );
/*  156 */	int							AMY_FUNC (*utime_utime)( struct AmyCLibIFace *Self, const char *str, const struct utimbuf *buf );
/*  157 */	int							AMY_FUNC (*unistd_link)( struct AmyCLibIFace *Self, const char *path1, const char *path2 );
/*  158 */	int							AMY_FUNC (*unistd_isatty)( struct AmyCLibIFace *Self, int fildes );
/*  159 */	void						AMY_FUNC (*stdio_perror)( struct AmyCLibIFace *Self, const char *s );
/*  160 */	int							AMY_FUNC (*stdio_remove)( struct AmyCLibIFace *Self, const char *path );
/*  161 */	int							AMY_FUNC (*stdio_rename)( struct AmyCLibIFace *Self, const char *old, const char *new );
/*  162 */	int							AMY_FUNC (*unistd_rmdir)( struct AmyCLibIFace *Self, const char *path );
/*  163 */	int							AMY_FUNC (*stdio_feof)( struct AmyCLibIFace *Self, FILE *stream );
/*  164 */	char *						AMY_FUNC (*stdio_fgets)( struct AmyCLibIFace *Self, char *s, int n, FILE *stream );
/*  165 */	void						AMY_FUNC (*stdio_rewind)( struct AmyCLibIFace *Self, FILE *stream );
/*  166 */	int							AMY_FUNC (*stdio_vfscanf)( struct AmyCLibIFace *Self, FILE *stream, const char *format, va_list arg );
/*  167 */	size_t						AMY_FUNC (*wchar_mbrtowc)( struct AmyCLibIFace *Self, wchar_t *pwc, const char *s, size_t n, mbstate_t *ps );
/*  168 */	int							AMY_FUNC (*stdio_getchar)( struct AmyCLibIFace *Self );
/*  169 */	char *						AMY_FUNC (*string_strstr)( struct AmyCLibIFace *Self, const char *s1, const char *s2 );
/*  170 */	size_t						AMY_FUNC (*wchar_mbstowcs)( struct AmyCLibIFace *Self, wchar_t *pwcs, const char *s, size_t n );
/*  171 */	uid_t						AMY_FUNC (*unistd_geteuid)( struct AmyCLibIFace *Self );
/*  172 */	gid_t						AMY_FUNC (*unistd_getegid)( struct AmyCLibIFace *Self );
/*  173 */	char *						AMY_FUNC (*locale_setlocale)( struct AmyCLibIFace *Self, int category, const char *locale );
/*  174 */	ssize_t						AMY_FUNC (*stdio_getline)( struct AmyCLibIFace *Self, char **lineptr, size_t *n, FILE *stream );
/*  175 */	ssize_t						AMY_FUNC (*stdio_getdelim)( struct AmyCLibIFace *Self, char **lineptr, size_t *n, int delimiter, FILE *stream );
/*  176 */	int							AMY_FUNC (*stdio_putc_unlocked)( struct AmyCLibIFace *Self, int c, FILE *stream );
/*  177 */	int							AMY_FUNC (*ctype_isprint)( struct AmyCLibIFace *Self, int c );
/*  178 */	char *						AMY_FUNC (*string_strerror)( struct AmyCLibIFace *Self, int errnum );
/*  179 */	int							AMY_FUNC (*string_strerror_r)( struct AmyCLibIFace *Self, int errnum, char *buf, size_t buflen );
/*  180 */	int							AMY_FUNC (*sys_time_gettimeofday)( struct AmyCLibIFace *Self, struct timeval *tp, void *tzp );
/*  181 */	int							AMY_FUNC (*ctype_isascii)( struct AmyCLibIFace *Self, int c );
/*  182 */	char *						AMY_FUNC (*string_stpcpy)( struct AmyCLibIFace *Self, char *s1, const char *s2 );
/*  183 */	int							AMY_FUNC (*ctype_isalnum)( struct AmyCLibIFace *Self, int c );
/*  184 */	double						AMY_FUNC (*math_d_ceil)( struct AmyCLibIFace *Self, double x );
/*  185 */	double						AMY_FUNC	(*math_d_cos)( struct AmyCLibIFace *Self, double x );
/*  186 */	double						AMY_FUNC (*math_d_sin)( struct AmyCLibIFace *Self, double x );
/*  187 */	double						AMY_FUNC (*math_d_atan2)( struct AmyCLibIFace *Self, double y, double x );
/*  188 */	double						AMY_FUNC (*math_d_fmod)( struct AmyCLibIFace *Self, double x, double y );
/*  189 */	char *						AMY_FUNC (*string_strtok)( struct AmyCLibIFace *Self, char *s1, const char *s2 );
/*  190 */	struct lconv *				AMY_FUNC (*locale_localeconv)( struct AmyCLibIFace *Self );
/*  191 */	int							AMY_FUNC (*stdlib_mkstemp)( struct AmyCLibIFace *Self, char *template );
/*  192 */	int							AMY_FUNC (*stdlib_atexit)( struct AmyCLibIFace *Self, void (*func)(void) );
/*  193 */	int							AMY_FUNC (*unistd_getgroups)( struct AmyCLibIFace *Self, int gidsetsize, gid_t grouplist[] );
/*  194 */	int							AMY_FUNC (*getopt_getopt)( struct AmyCLibIFace *Self, int argc, char * const argv[], const char *optstring );
/*  195 */	int							AMY_FUNC (*getopt_getopt_long)( struct AmyCLibIFace *Self, int argc, char * const argv[], const char *optstring, const struct option *longopts, int *longindex );
/*  196 */	int							AMY_FUNC (*dirent_closedir)( struct AmyCLibIFace *Self, DIR *dirp );
/*  197 */	int							AMY_FUNC (*dirent_dirfd)( struct AmyCLibIFace *Self, DIR *dirp );
/*  198 */	DIR *						AMY_FUNC (*dirent_opendir)( struct AmyCLibIFace *Self, const char *name );
/*  199 */	struct dirent *				AMY_FUNC (*dirent_readdir)( struct AmyCLibIFace *Self, DIR *dirp );
/*  200 */	struct group *				AMY_FUNC (*grp_getgrgid)( struct AmyCLibIFace *Self, gid_t aa );
/*  201 */	struct group *				AMY_FUNC (*grp_getgrnam)( struct AmyCLibIFace *Self, const char *aa );
/*  202 */	struct passwd *				AMY_FUNC (*pwd_getpwuid)( struct AmyCLibIFace *Self, uid_t aa );
/*  203 */	int							AMY_FUNC (*unistd_chown)( struct AmyCLibIFace *Self, const char *aa, uid_t bb, gid_t cc );
/*  204 */	char *						AMY_FUNC (*string_strrchr)( struct AmyCLibIFace *Self, const char *aa, int bb );
/*  205 */	struct passwd *				AMY_FUNC (*pwd_getpwnam)( struct AmyCLibIFace *Self, const char *aa );
/*  206 */	int							AMY_FUNC (*stdio_getchar_unlocked)( struct AmyCLibIFace *Self );
/*  207 */	int							AMY_FUNC (*stdio_putchar_unlocked)( struct AmyCLibIFace *Self, int c );
/*  208 */	off_t						AMY_FUNC (*unistd_lseek)( struct AmyCLibIFace *Self, int, off_t, int );
/*  209 */	ssize_t						AMY_FUNC (*unistd_write)( struct AmyCLibIFace *Self, int, const void *, size_t );
/*  210 */	int							AMY_FUNC (*unistd_symlink)( struct AmyCLibIFace *Self, const char *, const char * );
/*  211 */	int							AMY_FUNC (*time_clock_gettime)( struct AmyCLibIFace *Self, clockid_t, struct timespec * );
/*  212 */	int							AMY_FUNC (*time_clock_settime)( struct AmyCLibIFace *Self, clockid_t, const struct timespec * );
/*  213 */	int							AMY_FUNC (*unistd_gethostname)( struct AmyCLibIFace *Self, char *, size_t );
/*  214 */	void *						AMY_FUNC (*string_memrchr)( struct AmyCLibIFace *Self, const void *, int, size_t );
/*  215 */	time_t						AMY_FUNC (*time_mktime)( struct AmyCLibIFace *Self, struct tm * );
/*  216 */	long long					AMY_FUNC (*stdlib_strtoll)( struct AmyCLibIFace *Self, const char *, char **, int );
/*  217 */	int							AMY_FUNC (*stdio_getc_unlocked)( struct AmyCLibIFace *Self, FILE *stream );
/*  218 */	void *						AMY_FUNC (*string_memchr)( struct AmyCLibIFace *Self, const void *, int, size_t );
/*  219 */	int							AMY_FUNC (*ctype_iscntrl)( struct AmyCLibIFace *Self, int c );
/*  220 */	int							AMY_FUNC (*ctype_ispunct)( struct AmyCLibIFace *Self, int c );
/*  221 */	int							AMY_FUNC (*unistd_chdir)( struct AmyCLibIFace *Self, const char *aa );
/*  222 */	int							AMY_FUNC (*stdlib_system)( struct AmyCLibIFace *Self, const char *aa );
/*  223 */	int							AMY_FUNC (*string_strcoll)( struct AmyCLibIFace *Self, const char *aa, const char *bb );
/*  224 */	char *						AMY_FUNC (*time_asctime)( struct AmyCLibIFace *Self, const struct tm *aa );
/*  225 */	int							AMY_FUNC( *wchar_mbsinit)( struct AmyCLibIFace *Self, const mbstate_t *aa );
/*  226 */	void						AMY_FUNC( *dirent_rewinddir)( struct AmyCLibIFace *Self, DIR *aa );
/*  227 */	uid_t						AMY_FUNC( *unistd_getuid)( struct AmyCLibIFace *Self );
/*  228 */	int							AMY_FUNC( *unistd_fsync)( struct AmyCLibIFace *Self, int aa );
/*  229 */	gid_t						AMY_FUNC( *unistd_getgid)( struct AmyCLibIFace *Self );
/*  230 */	int							AMY_FUNC( *sys_statvfs_statvfs)( struct AmyCLibIFace *Self, const char *aa, struct statvfs *bb );
/*  231 */	int							AMY_FUNC( *sys_mount_statfs)( struct AmyCLibIFace *Self, const char *aa, struct statfs *bb );
/*  232 */	void						AMY_FUNC( *pwd_setpwent)( struct AmyCLibIFace *Self );
/*  233 */	void						AMY_FUNC( *grp_setgrent)( struct AmyCLibIFace *Self );
/*  234 */	int							AMY_FUNC (*stropts_ioctl_ap)( struct AmyCLibIFace *Self, int aa, int bb, va_list ap );
/*  235 */	DIR *						AMY_FUNC (*dirent_fdopendir)( struct AmyCLibIFace *Self, int fildes );
/*  236 */	FILE *						AMY_FUNC (*stdio_fdopen)( struct AmyCLibIFace *Self, int aa, const char *bb );
/*  237 */	int							AMY_FUNC( *sys_resource_getrlimit)( struct AmyCLibIFace *Self, int resource, struct rlimit *rlp );
/*  238 */	int							AMY_FUNC( *signal_kill)( struct AmyCLibIFace *Self, pid_t aa, int bb );
/*  239 */	int							AMY_FUNC( *unistd_usleep)( struct AmyCLibIFace *Self, useconds_t aa );
/*  240 */	int							AMY_FUNC( *stdlib_putenv)( struct AmyCLibIFace *Self, char *aa );
/*  241 */	int							AMY_FUNC( *unistd_execvp)( struct AmyCLibIFace *Self, const char *aa, char * const bb[] );
/*  242 */	char *						AMY_FUNC( *string_strsignal)( struct AmyCLibIFace *Self, int aa );
/*  243 */	char *						AMY_FUNC( *unistd_ttyname)( struct AmyCLibIFace *Self, int aa );
/*  244 */	int							AMY_FUNC( *unistd_setgid)( struct AmyCLibIFace *Self, gid_t aa );
/*  245 */	int							AMY_FUNC( *unistd_setuid)( struct AmyCLibIFace *Self, uid_t aa );
/*  246 */	int							AMY_FUNC( *unistd_setgroups)( struct AmyCLibIFace *Self, int ngroups, const gid_t *gidset );
/*  247 */	int							AMY_FUNC( *unistd_execv)( struct AmyCLibIFace *Self, const char *aa, char * const bb[] );
/*  248 */	char *						AMY_FUNC( *unistd_crypt)( struct AmyCLibIFace *Self, const char *aa, const char *bb );
/*  249 */	clock_t						AMY_FUNC( *time_clock)( struct AmyCLibIFace *Self );
/*  250 */	FILE *						AMY_FUNC( *stdio_popen)( struct AmyCLibIFace *Self, const char *, const char * );
/*  251 */	unsigned long				AMY_FUNC( *stdlib_strtoul)( struct AmyCLibIFace *Self, const char *, char **, int );
/*  252 */	unsigned long long			AMY_FUNC( *stdlib_strtoull)( struct AmyCLibIFace *Self, const char *, char **, int );
/*  253 */	off_t						AMY_FUNC( *stdio_ftello)( struct AmyCLibIFace *Self, FILE *);
/*  254 */	FILE *						AMY_FUNC( *stdio_fopen64)( struct AmyCLibIFace *Self, const char *, const char * );
/*  255 */	off64_t						AMY_FUNC( *stdio_ftello64)( struct AmyCLibIFace *Self, FILE * );
/*  256 */	int							AMY_FUNC( *stdio_fseeko64)( struct AmyCLibIFace *Self, FILE *, off64_t, int );
/*  257 */	pid_t						AMY_FUNC( *sys_wait_waitpid)( struct AmyCLibIFace *Self, pid_t, int *, int );
/*  258 */	FILE *						AMY_FUNC( *stdio_freopen)( struct AmyCLibIFace *Self, const char *, const char *, FILE * );
/*  259 */	char *						AMY_FUNC( *stdio_tempnam)( struct AmyCLibIFace *Self, const char *, const char * );
/*  260 */	char *						AMY_FUNC( *stdlib_realpath)( struct AmyCLibIFace *Self, const char *, char * );
/*  261 */	char *						AMY_FUNC( *stdio_tmpnam)( struct AmyCLibIFace *Self, char * );
/*  262 */	void *						AMY_FUNC( *string_memmem)( struct AmyCLibIFace *Self, const void *, size_t, const void *, size_t );
/*  263 */	char *						AMY_FUNC( *string_stpncpy)( struct AmyCLibIFace *Self, char *, const char *, size_t );
/*  264 */	int							AMY_FUNC( *stdlib_setenv)( struct AmyCLibIFace *Self, const char *, const char *, int );
/*  265 */	int							AMY_FUNC( *stdlib_unsetenv)( struct AmyCLibIFace *Self, const char * );
/*  266 */	char *						AMY_FUNC( *libgen_basename)( struct AmyCLibIFace *Self, char * );
/*  267 */	unsigned					AMY_FUNC( *unistd_alarm)( struct AmyCLibIFace *Self, unsigned );
/*  268 */	char *						AMY_FUNC( *langinfo_nl_langinfo)( struct AmyCLibIFace *Self, nl_item );
/*  269 */	int							AMY_FUNC( *unistd_dup)( struct AmyCLibIFace *Self, int );
/*  270 */	int							AMY_FUNC( *unistd_dup2)( struct AmyCLibIFace *Self, int, int );
/*  271 */	int							AMY_FUNC( *strings_bcmp)( struct AmyCLibIFace *Self, const void *, const void *, size_t );
/*  272 */	void						AMY_FUNC( *strings_bcopy)( struct AmyCLibIFace *Self, const void *, void *, size_t );
/*  273 */	long						AMY_FUNC( *stdlib_random)( struct AmyCLibIFace *Self );
/*  274 */	int							AMY_FUNC( *unistd_getpagesize)( struct AmyCLibIFace *Self );
/*  275 */	void						AMY_FUNC( *stdio_setbuf)( struct AmyCLibIFace *Self, FILE *, char * );
/*  276 */	long long					AMY_FUNC( *stdlib_atoll)( struct AmyCLibIFace *Self, const char * );
/*  277 */	int							AMY_FUNC( *stdio_pclose)( struct AmyCLibIFace *Self, FILE * );
/*  278 */	double						AMY_FUNC (*math_d_ldexp)( struct AmyCLibIFace *Self, double, int );
/*  279 */	int							AMY_FUNC( *ftw_ftw)( struct AmyCLibIFace *Self, const char *, int (*)(const char *, const struct stat *, int), int );
/*  280 */	int							AMY_FUNC( *ftw_nftw)( struct AmyCLibIFace *Self, const char *, int (*)(const char *, const struct stat *, int, struct FTW *), int, int );
/*  281 */	int							AMY_FUNC( *process_execvp)( struct AmyCLibIFace *Self, const char *file, char *const argv[] );
/*  282 */	pid_t						AMY_FUNC( *unistd_fork)( struct AmyCLibIFace *Self );




};

// --

#endif
