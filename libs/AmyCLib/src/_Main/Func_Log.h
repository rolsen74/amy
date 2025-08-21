
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

#ifndef _FUNCLOG_H_
#define _FUNCLOG_H_ 1

// #ifdef __DO_FUNCTION_LOG__

// --

enum
{
//	## Amiga ##

//	LOG_FUNC_ArgArrayInit,
//	LOG_FUNC_ArgArrayDone,
//	LOG_FUNC_ArgInt,
//	LOG_FUNC_ArgString,
//	LOG_FUNC_NewList,
//	LOG_FUNC_NewMinList,

//	## Assert ##

	LOG_FUNC_assert,


//	## CType ##

//	LOG_FUNC_isalnum,
	LOG_FUNC_isalpha,
//	LOG_FUNC_isascii,
//	LOG_FUNC_isblank,
//	LOG_FUNC_iscntrl,
	LOG_FUNC_isdigit,
//	LOG_FUNC_isgraph,
	LOG_FUNC_islower,
//	LOG_FUNC_isprint,
//	LOG_FUNC_ispunct,
	LOG_FUNC_isspace,
	LOG_FUNC_isupper,
	LOG_FUNC_isxdigit,
	LOG_FUNC_tolower,
	LOG_FUNC_toupper,


//	## Dirent ##

//	LOG_FUNC_closedir,
//	LOG_FUNC_opendir,
//	LOG_FUNC_readdir,
//	LOG_FUNC_rewinddir,


//	## FCntl ##

//	LOG_FUNC_creat,
//	LOG_FUNC_fcntl,
	LOG_FUNC_open,


//	## Inttypes ##

//	LOG_FUNC_imaxabs,
//	LOG_FUNC_imaxdiv,
	LOG_FUNC_strtoimax,
	LOG_FUNC_strtoumax,

//	## Locale ##

//	LOG_FUNC_localeconv,


//	## Math ##

//	LOG_FUNC_F___signbit,
//	LOG_FUNC_F_ceil,
//	LOG_FUNC_F_copysign,
//	LOG_FUNC_F_fabs,
//	LOG_FUNC_F_fdim,
//	LOG_FUNC_F_floor,
//	LOG_FUNC_F_fpclassify,
//	LOG_FUNC_F_fmax,
//	LOG_FUNC_F_fmin,
//	LOG_FUNC_F_fmod,
//	LOG_FUNC_F_isfinite,
//	LOG_FUNC_F_isinf,
//	LOG_FUNC_F_isnan,
//	LOG_FUNC_F_log,
//	LOG_FUNC_F_log10,
//	LOG_FUNC_F_nan,
//	LOG_FUNC_F_pow,
//	LOG_FUNC_F_scalbn,
//	LOG_FUNC_F_sqrt,

	LOG_FUNC_D__get_huge_val,
	LOG_FUNC_D__inf,
//	LOG_FUNC_D___signbit,
//	LOG_FUNC_D_ceil,
	LOG_FUNC_D_copysign,
	LOG_FUNC_D_fabs,
//	LOG_FUNC_D_fdim,
//	LOG_FUNC_D_floor,
//	LOG_FUNC_D_fpclassify,
//	LOG_FUNC_D_fmax,
//	LOG_FUNC_D_fmin,
//	LOG_FUNC_D_fmod,
//	LOG_FUNC_D_isfinite,
	LOG_FUNC_D_isinf,
	LOG_FUNC_D_isnan,
//	LOG_FUNC_D_log,
//	LOG_FUNC_D_log10,
	LOG_FUNC_D_nan,
	LOG_FUNC_D_pow,
	LOG_FUNC_D_scalbn,
	LOG_FUNC_D_sqrt,

//	LOG_FUNC_LD___signbit,


//	## Netdb ##

//	LOG_FUNC_freeaddrinfo,
//	LOG_FUNC_gai_strerror,
//	LOG_FUNC_getaddrinfo,
//	LOG_FUNC_gethostbyaddr,
//	LOG_FUNC_gethostbyname,
//	LOG_FUNC_getnameinfo,
//	LOG_FUNC_getservbyname,
//	LOG_FUNC_getservbyport,


//	## Poll ##

//	LOG_FUNC_poll,
//	LOG_FUNC_waitpoll,


//	## PThread ##

//	LOG_FUNC_pthread_create,
//	LOG_FUNC_pthread_equal,
//	LOG_FUNC_pthread_exit,
//	LOG_FUNC_pthread_join,
//	LOG_FUNC_pthread_once,
//	LOG_FUNC_pthread_self,
//
//	LOG_FUNC_pthread_attr_init,
//	LOG_FUNC_pthread_attr_destroy,
//
//	LOG_FUNC_pthread_barrier_init,
//	LOG_FUNC_pthread_barrier_destroy,
//	LOG_FUNC_pthread_barrierattr_init,
//	LOG_FUNC_pthread_barrierattr_destroy,
//
//	LOG_FUNC_pthread_cond_init,
//	LOG_FUNC_pthread_cond_wait,
//	LOG_FUNC_pthread_cond_signal,
//	LOG_FUNC_pthread_cond_broadcast,
//	LOG_FUNC_pthread_cond_timedwait,
//	LOG_FUNC_pthread_cond_destroy,
//	LOG_FUNC_pthread_condattr_init,
//	LOG_FUNC_pthread_condattr_destroy,
//	LOG_FUNC_pthread_condattr_getclock,
//	LOG_FUNC_pthread_condattr_setclock,
//
//	LOG_FUNC_pthread_mutex_init,
//	LOG_FUNC_pthread_mutex_lock,
//	LOG_FUNC_pthread_mutex_unlock,
//	LOG_FUNC_pthread_mutex_trylock,
//	LOG_FUNC_pthread_mutex_timedlock,
//	LOG_FUNC_pthread_mutex_destroy,
//	LOG_FUNC_pthread_mutexattr_init,
//	LOG_FUNC_pthread_mutexattr_destroy,
//	LOG_FUNC_pthread_mutexattr_settype,
//	LOG_FUNC_pthread_mutexattr_gettype,
//
//	LOG_FUNC_pthread_rwlock_init,
//	LOG_FUNC_pthread_rwlock_rdlock,
//	LOG_FUNC_pthread_rwlock_wrlock,
//	LOG_FUNC_pthread_rwlock_unlock,
//	LOG_FUNC_pthread_rwlock_tryrdlock,
//	LOG_FUNC_pthread_rwlock_trywrlock,
//	LOG_FUNC_pthread_rwlock_timedrdlock,
//	LOG_FUNC_pthread_rwlock_timedwrlock,
//	LOG_FUNC_pthread_rwlock_destroy,
//	LOG_FUNC_pthread_rwlockattr_init,
//	LOG_FUNC_pthread_rwlockattr_destroy,
//
//	LOG_FUNC_pthread_spinlock_init,
//	LOG_FUNC_pthread_spinlock_lock,
//	LOG_FUNC_pthread_spinlock_unlock,
//	LOG_FUNC_pthread_spinlock_trylock,
//	LOG_FUNC_pthread_spinlock_destroy,


//	## Regex ##

//	LOG_FUNC_regcomp,
//	LOG_FUNC_regerror,
//	LOG_FUNC_regexec,
//	LOG_FUNC_regfree,


//	## Setjmp ##

//	LOG_FUNC_longjmp,
//	LOG_FUNC_setjmp,


//	## Signal ##

	LOG_FUNC_raise,
	LOG_FUNC_signal,


//	## Stdio ##

//	LOG_FUNC_asprintf,
	LOG_FUNC_clearerr,
//	LOG_FUNC_ctermid,
	LOG_FUNC_fclose,
//	LOG_FUNC_fdopen,
//	LOG_FUNC_feof,
	LOG_FUNC_ferror,
	LOG_FUNC_fflush,
	LOG_FUNC_fgetc,
	LOG_FUNC_fgetpos,
	LOG_FUNC_fgets,
//	LOG_FUNC_fileno,
	LOG_FUNC_flockfile,
	LOG_FUNC_fopen,
//	LOG_FUNC_fprintf,
	LOG_FUNC_fputc,
	LOG_FUNC_fputc_unlocked,
	LOG_FUNC_fputs,
	LOG_FUNC_fread,
//	LOG_FUNC_fscanf,
	LOG_FUNC_fseek,
	LOG_FUNC_fseeko,
//	LOG_FUNC_fsetpos,
	LOG_FUNC_ftell,
//	LOG_FUNC_ftello,
//	LOG_FUNC_ftrylockfile,
	LOG_FUNC_funlockfile,
//	LOG_FUNC_fwrite,
//	LOG_FUNC_getc,
//	LOG_FUNC_getc_unlocked,
//	LOG_FUNC_getchar,
//	LOG_FUNC_getchar_unlocked,
//	LOG_FUNC_perror,
//	LOG_FUNC_printf,
//	LOG_FUNC_putc,
//	LOG_FUNC_putc_unlocked,
	LOG_FUNC_putchar,
//	LOG_FUNC_putchar_unlocked,
	LOG_FUNC_puts,
//	LOG_FUNC_remove,
//	LOG_FUNC_rename,
//	LOG_FUNC_rewind,
//	LOG_FUNC_scanf,
//	LOG_FUNC_setbuf,
	LOG_FUNC_setvbuf,
//	LOG_FUNC_snprintf,
//	LOG_FUNC_sprintf,
//	LOG_FUNC_sscanf,
//	LOG_FUNC_tmpfile,
//	LOG_FUNC_tmpnam,
//	LOG_FUNC_tmpnam_r,
	LOG_FUNC_ungetc,
	LOG_FUNC_vasprintf,
//	LOG_FUNC_vfprintf,
//	LOG_FUNC_vfscanf,
	LOG_FUNC_vscanf,
	LOG_FUNC_vsscanf,
	LOG_FUNC_vprintf,
	LOG_FUNC_vsprintf,
	LOG_FUNC_vsnprintf,


//	## Stdlib ##

	LOG_FUNC__Exit,
	LOG_FUNC_abort,
	LOG_FUNC_abs,
//	LOG_FUNC_arc4random,
//	LOG_FUNC_arc4random_buf,
//	LOG_FUNC_arc4random_stir,
//	LOG_FUNC_arc4random_uniform,
//	LOG_FUNC_arc4random_addrandom,
//	LOG_FUNC_atexit,
//	LOG_FUNC_atof,
	LOG_FUNC_atoi,
//	LOG_FUNC_atol,
//	LOG_FUNC_atoll,
//	LOG_FUNC_bsearch,
	LOG_FUNC_calloc,
//	LOG_FUNC_div,
	LOG_FUNC_exit,
	LOG_FUNC_free,
//	LOG_FUNC_freezero,
//	LOG_FUNC_getenv,
//	LOG_FUNC_getprogname,
//	LOG_FUNC_initstate,
//	LOG_FUNC_jrand48,
//	LOG_FUNC_labs,
//	LOG_FUNC_ldiv,
//	LOG_FUNC_llabs,
//	LOG_FUNC_lldiv,
//	LOG_FUNC_lrand48,
	LOG_FUNC_malloc,
//	LOG_FUNC_mblen,
//	LOG_FUNC_mbtowc,
//	LOG_FUNC_mrand48,
//	LOG_FUNC_nrand48,
//	LOG_FUNC_qsort,
	LOG_FUNC_rand,
	LOG_FUNC_rand_r,
	LOG_FUNC_random,
	LOG_FUNC_realloc,
//	LOG_FUNC_reallocarray,
//	LOG_FUNC_recallocarray,
//	LOG_FUNC_setprogname,
//	LOG_FUNC_setstate,
	LOG_FUNC_srand,
//	LOG_FUNC_srand48,
//	LOG_FUNC_srandom,
	LOG_FUNC_strtod,
	LOG_FUNC_strtof,
	LOG_FUNC_strtol,
//	LOG_FUNC_strtoq,
//	LOG_FUNC_strtoll,
//	LOG_FUNC_strtoul,
//	LOG_FUNC_strtoull,
//	LOG_FUNC_system,


//	## String ##

//	LOG_FUNC_ffsl,
//	LOG_FUNC_ffsll,
//	LOG_FUNC_memccpy,
//	LOG_FUNC_memchr,
	LOG_FUNC_memcmp,
	LOG_FUNC_memcpy,
//	LOG_FUNC_memmem,
	LOG_FUNC_memmove,
	LOG_FUNC_memset,
//	LOG_FUNC_stpcpy,
//	LOG_FUNC_stpncpy,
	LOG_FUNC_strcat,
//	LOG_FUNC_strchr,
	LOG_FUNC_strcmp,
//	LOG_FUNC_strcoll,
	LOG_FUNC_strcpy,
//	LOG_FUNC_strcspn,
	LOG_FUNC_strdup,
//	LOG_FUNC_strerror,
//	LOG_FUNC_strerror_r,
//	LOG_FUNC_strlcat,
//	LOG_FUNC_strlcpy,
	LOG_FUNC_strlen,
//	LOG_FUNC_strncat,
	LOG_FUNC_strncmp,
	LOG_FUNC_strncpy,
	LOG_FUNC_strndup,
	LOG_FUNC_strnlen,
//	LOG_FUNC_strpbrk,
//	LOG_FUNC_strrchr,
//	LOG_FUNC_strsep,
//	LOG_FUNC_strspn,
//	LOG_FUNC_strstr,
//	LOG_FUNC_strtok,
//	LOG_FUNC_strtok_r,
//	LOG_FUNC_strxfrm,
//	LOG_FUNC_timingsafe_memcmp,


//	## Strings ##

//	LOG_FUNC_bcmp,
//	LOG_FUNC_bcopy,
	LOG_FUNC_bzero,
//	LOG_FUNC_explicit_bzero,
//	LOG_FUNC_ffs,
//	LOG_FUNC_index,
//	LOG_FUNC_rindex,
	LOG_FUNC_strcasecmp,
	LOG_FUNC_strncasecmp,
//	LOG_FUNC_timingsafe_bcmp,


//	## RA_SysLog ##

//	LOG_FUNC_closelog,
//	LOG_FUNC_closelog_r,
//	LOG_FUNC_openlog,
//	LOG_FUNC_openlog_r,
//	LOG_FUNC_setlogmask,
//	LOG_FUNC_setlogmask_r,
//	LOG_FUNC_syslog,
//	LOG_FUNC_syslog_r,
//	LOG_FUNC_vsyslog,
//	LOG_FUNC_vsyslog_r,


//	## Time ##

//	LOG_FUNC_asctime,
//	LOG_FUNC_asctime_r,
//	LOG_FUNC_clock,
//	LOG_FUNC_clock_gettime,
//	LOG_FUNC_ctime,
//	LOG_FUNC_ctime_r,
	LOG_FUNC_gmtime,
	LOG_FUNC_gmtime_r,
	LOG_FUNC_localtime,
//	LOG_FUNC_localtime_r,
//	LOG_FUNC_mktime,
	LOG_FUNC_strftime,
	LOG_FUNC_time,
//	LOG_FUNC_timegm,


//	## Unistd ##

//	LOG_FUNC__exit,
	LOG_FUNC_close,
//	LOG_FUNC_ftruncate,
//	LOG_FUNC_getcwd,
//	LOG_FUNC_getpagesize,
//	LOG_FUNC_getpid,
//	LOG_FUNC_getppid,
//	LOG_FUNC_getwd,
//	LOG_FUNC_isatty,
//	LOG_FUNC_lseek,
//	LOG_FUNC_pread,
//	LOG_FUNC_pwrite,
//	LOG_FUNC_read,
//	LOG_FUNC_rmdir,
//	LOG_FUNC_swab,
//	LOG_FUNC_write,


//	## UTime ##

//	LOG_FUNC_utime,


//	## WChar ##

//	LOG_FUNC_wcscat,
//	LOG_FUNC_wcschr,
//	LOG_FUNC_wcscmp,
//	LOG_FUNC_wcslcat,
//	LOG_FUNC_wcslcpy,
//	LOG_FUNC_wcslen,
//	LOG_FUNC_wmemchr,
//	LOG_FUNC_wmemcmp,
//	LOG_FUNC_wmemcpy,
//	LOG_FUNC_wmemmove,
//	LOG_FUNC_wmemset,


//	## Sys / Socket ##

//	LOG_FUNC_accept,
//	LOG_FUNC_bind,
//	LOG_FUNC_connect,
//	LOG_FUNC_getpeername,
//	LOG_FUNC_getsockname,
//	LOG_FUNC_getsockopt,
//	LOG_FUNC_inet_addr,
//	LOG_FUNC_inet_ntoa,
//	LOG_FUNC_inet_ntop,
//	LOG_FUNC_inet_pton,
//	LOG_FUNC_listen,
//	LOG_FUNC_recv,
//	LOG_FUNC_recvfrom,
//	LOG_FUNC_select,
//	LOG_FUNC_send,
//	LOG_FUNC_sendto,
//	LOG_FUNC_setsockopt,
//	LOG_FUNC_shutdown,
//	LOG_FUNC_socket,
//	LOG_FUNC_waitselect,


//	## Sys / Stat ##

//	LOG_FUNC_fstat,
//	LOG_FUNC_mkdir,
//	LOG_FUNC_stat,


//	## Sys / Time ##

//	LOG_FUNC_gettimeofday,


//	## Sys / Uio ##

//	LOG_FUNC_readv,
//	LOG_FUNC_writev,


//	## End ##

	LOG_FUNC_LAST
};

// --

#endif
