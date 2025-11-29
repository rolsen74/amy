
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

#ifdef __DO_FUNCTION_LOG__

enum
{
/* xx */ GROUP_Dummy,
/*  1 */ GROUP_Amiga,
/*  2 */ GROUP_Assert,
/*  3 */ GROUP_CType,
/*  4 */ GROUP_Dirent,
/*  5 */ GROUP_FCntl,
/*  6 */ GROUP_Getopt,
/*  7 */ GROUP_Inttypes,
/*  8 */ GROUP_Locale,
/*  9 */ GROUP_Math_F,
/* 10 */ GROUP_Math_D,
/* 11 */ GROUP_Math_LD,
/* 12 */ GROUP_Netdb,
/* 13 */ GROUP_Poll,
/* 14 */ GROUP_PThread,
/* 15 */ GROUP_Regex,
/* 16 */ GROUP_Setjmp,
/* 17 */ GROUP_Signal,
/* 18 */ GROUP_Stdio,
/* 19 */ GROUP_Stdlib,
/* 20 */ GROUP_String,
/* 21 */ GROUP_Strings,
/* 22 */ GROUP_Time,
/* 23 */ GROUP_Unistd,
/* 24 */ GROUP_UTime,
/* 25 */ GROUP_WChar,
/* 26 */ GROUP_Sys_Socket,
/* 27 */ GROUP_Sys_Stat,
/* 28 */ GROUP_Sys_Time,
/* 29 */ GROUP_Sys_Uio,
/* 30 */ GROUP_Grp,
/* 31 */ GROUP_Pwd,
/* xx */ GROUP_LAST
};

typedef struct
{
	const U32 Group;
	const STR Name;
}
FuncString;

static const FuncString myStrings[ LOG_FUNC_LAST ] =
{
	// Amiga.h
//	[LOG_FUNC_ArgArrayInit] = { .Group = GROUP_Amiga, .Name = "ArgArrayInit" },
//	[LOG_FUNC_ArgInt] = { .Group = GROUP_Amiga, .Name = "ArgInt" },
//	[LOG_FUNC_ArgString] = { .Group = GROUP_Amiga, .Name = "ArgString" },
//	[LOG_FUNC_NewList] = { .Group = GROUP_Amiga, .Name = "NewList" },
//	[LOG_FUNC_NewMinList] = { .Group = GROUP_Amiga, .Name = "NewMinList" },

	// Assert.h
	[LOG_FUNC_assert] = { .Group = GROUP_Assert, .Name = "assert" },

	// CType.h
	[LOG_FUNC_isalnum] = { .Group = GROUP_CType, .Name = "isalnum" },
	[LOG_FUNC_isalpha] = { .Group = GROUP_CType, .Name = "isalpha" },
	[LOG_FUNC_isascii] = { .Group = GROUP_CType, .Name = "isascii" },
//	[LOG_FUNC_isblank] = { .Group = GROUP_CType, .Name = "isblank" },
//	[LOG_FUNC_iscntrl] = { .Group = GROUP_CType, .Name = "iscntrl" },
	[LOG_FUNC_isdigit] = { .Group = GROUP_CType, .Name = "isdigit" },
//	[LOG_FUNC_isgraph] = { .Group = GROUP_CType, .Name = "isgraph" },
	[LOG_FUNC_islower] = { .Group = GROUP_CType, .Name = "islower" },
	[LOG_FUNC_isprint] = { .Group = GROUP_CType, .Name = "isprint" },
//	[LOG_FUNC_ispunct] = { .Group = GROUP_CType, .Name = "ispunct" },
	[LOG_FUNC_isspace] = { .Group = GROUP_CType, .Name = "isspace" },
	[LOG_FUNC_isupper] = { .Group = GROUP_CType, .Name = "isupper" },
	[LOG_FUNC_isxdigit] = { .Group = GROUP_CType, .Name = "isxdigit" },
	[LOG_FUNC_tolower] = { .Group = GROUP_CType, .Name = "tolower" },
	[LOG_FUNC_toupper] = { .Group = GROUP_CType, .Name = "toupper" },

	// Dirent.h
	[LOG_FUNC_closedir] = { .Group = GROUP_Dirent, .Name = "closedir" },
	[LOG_FUNC_dirfd] = { .Group = GROUP_Dirent, .Name = "dirfd" },
	[LOG_FUNC_opendir] = { .Group = GROUP_Dirent, .Name = "opendir" },
	[LOG_FUNC_readdir] = { .Group = GROUP_Dirent, .Name = "readdir" },
//	[LOG_FUNC_rewinddir] = { .Group = GROUP_Dirent, .Name = "rewinddir" },

	// FCntl.h
//	[LOG_FUNC_creat] = { .Group = GROUP_FCntl, .Name = "creat" },
	[LOG_FUNC_fcntl_ap] = { .Group = GROUP_FCntl, .Name = "fcntl_ap" },
	[LOG_FUNC_open] = { .Group = GROUP_FCntl, .Name = "open" },

	// Getopt.h
	[LOG_FUNC_getopt] = { .Group = GROUP_Getopt, .Name = "getopt" },
	[LOG_FUNC_getopt_long] = { .Group = GROUP_Getopt, .Name = "getopt_long" },

	// Grp.h
	[LOG_FUNC_getgrgid] = { .Group = GROUP_Grp, .Name = "getgrgid" },
	[LOG_FUNC_getgrnam] = { .Group = GROUP_Grp, .Name = "getgrnam" },

	// Inttypes.h
//	[LOG_FUNC_imaxabs] = { .Group = GROUP_Inttypes, .Name = "imaxabs" },
//	[LOG_FUNC_imaxdiv] = { .Group = GROUP_Inttypes, .Name = "imaxdiv" },
	[LOG_FUNC_strtoimax] = { .Group = GROUP_Inttypes, .Name = "strtoimax" },
	[LOG_FUNC_strtoumax] = { .Group = GROUP_Inttypes, .Name = "strtoumax" },

	// Locale.h
	[LOG_FUNC_localeconv] = { .Group = GROUP_Locale, .Name = "localeconv" },
	[LOG_FUNC_setlocale] = { .Group = GROUP_Locale, .Name = "setlocale" },

	// Math.h (Float)
//	[LOG_FUNC_F___signbit] = { .Group = GROUP_Math_F, .Name = "__signbit.f" },
//	[LOG_FUNC_F_ceil] = { .Group = GROUP_Math_F, .Name = "ceilf" },
//	[LOG_FUNC_F_copysign] = { .Group = GROUP_Math_F, .Name = "copysignf" },
//	[LOG_FUNC_F_fabs] = { .Group = GROUP_Math_F, .Name = "fabsf" },
//	[LOG_FUNC_F_fdim] = { .Group = GROUP_Math_F, .Name = "fdimf" },
//	[LOG_FUNC_F_floor] = { .Group = GROUP_Math_F, .Name = "floorf" },
//	[LOG_FUNC_F_fpclassify] = { .Group = GROUP_Math_F, .Name = "fpclassifyf" },
//	[LOG_FUNC_F_fmax] = { .Group = GROUP_Math_F, .Name = "fmaxf" },
//	[LOG_FUNC_F_fmin] = { .Group = GROUP_Math_F, .Name = "fminf" },
//	[LOG_FUNC_F_fmod] = { .Group = GROUP_Math_F, .Name = "fmodf" },
//	[LOG_FUNC_F_isfinite] = { .Group = GROUP_Math_F, .Name = "isfinitef" },
//	[LOG_FUNC_F_isinf] = { .Group = GROUP_Math_F, .Name = "isinff" },
//	[LOG_FUNC_F_isnan] = { .Group = GROUP_Math_F, .Name = "isnanf" },
//	[LOG_FUNC_F_log] = { .Group = GROUP_Math_F, .Name = "logf" },
//	[LOG_FUNC_F_log10] = { .Group = GROUP_Math_F, .Name = "log10f" },
//	[LOG_FUNC_F_nan] = { .Group = GROUP_Math_F, .Name = "nanf" },
//	[LOG_FUNC_F_pow] = { .Group = GROUP_Math_F, .Name = "powf" },
//	[LOG_FUNC_F_scalbn] = { .Group = GROUP_Math_F, .Name = "scalbnf" },
//	[LOG_FUNC_F_sqrt] = { .Group = GROUP_Math_F, .Name = "sqrtf" },

	// Math.h (Double)
//	[LOG_FUNC_D___signbit] = { .Group = GROUP_Math_D, .Name = "__signbit" },
	[LOG_FUNC_D_ceil] = { .Group = GROUP_Math_D, .Name = "ceil" },
	[LOG_FUNC_D_copysign] = { .Group = GROUP_Math_D, .Name = "copysign" },
	[LOG_FUNC_D_fabs] = { .Group = GROUP_Math_D, .Name = "fabs" },
//	[LOG_FUNC_D_fdim] = { .Group = GROUP_Math_D, .Name = "fdim" },
//	[LOG_FUNC_D_floor] = { .Group = GROUP_Math_D, .Name = "floor" },
//	[LOG_FUNC_D_fpclassify] = { .Group = GROUP_Math_D, .Name = "fpclassify" },
//	[LOG_FUNC_D_fmax] = { .Group = GROUP_Math_D, .Name = "fmax" },
//	[LOG_FUNC_D_fmin] = { .Group = GROUP_Math_D, .Name = "fmin" },
	[LOG_FUNC_D_fmod] = { .Group = GROUP_Math_D, .Name = "fmod" },
//	[LOG_FUNC_D_isfinite] = { .Group = GROUP_Math_D, .Name = "isfinite" },
	[LOG_FUNC_D_isinf] = { .Group = GROUP_Math_D, .Name = "isinf" },
	[LOG_FUNC_D_isnan] = { .Group = GROUP_Math_D, .Name = "isnan" },
//	[LOG_FUNC_D_log] = { .Group = GROUP_Math_D, .Name = "log" },
//	[LOG_FUNC_D_log10] = { .Group = GROUP_Math_D, .Name = "log10" },
	[LOG_FUNC_D_nan] = { .Group = GROUP_Math_D, .Name = "nan" },
	[LOG_FUNC_D_pow] = { .Group = GROUP_Math_D, .Name = "pow" },
	[LOG_FUNC_D_scalbn] = { .Group = GROUP_Math_D, .Name = "scalbn" },
	[LOG_FUNC_D_sqrt] = { .Group = GROUP_Math_D, .Name = "sqrt" },
	[LOG_FUNC_D_cos] = { .Group = GROUP_Math_D, .Name = "cos" },
	[LOG_FUNC_D_sin] = { .Group = GROUP_Math_D, .Name = "sin" },
	[LOG_FUNC_D_atan2] = { .Group = GROUP_Math_D, .Name = "atan2" },


	// Math.h (Long Double)
//	[LOG_FUNC_LD___signbit] = { .Group = GROUP_Math_LD, .Name = "__signbitl" },

	// Netdb.h
//	[LOG_FUNC_freeaddrinfo] = { .Group = GROUP_Netdb, .Name = "freeaddrinfo" },
//	[LOG_FUNC_gai_strerror] = { .Group = GROUP_Netdb, .Name = "gai_strerror" },
//	[LOG_FUNC_getaddrinfo] = { .Group = GROUP_Netdb, .Name = "getaddrinfo" },
//	[LOG_FUNC_gethostbyaddr] = { .Group = GROUP_Netdb, .Name = "gethostbyaddr" },
//	[LOG_FUNC_gethostbyname] = { .Group = GROUP_Netdb, .Name = "gethostbyname" },
//	[LOG_FUNC_getnameinfo] = { .Group = GROUP_Netdb, .Name = "getnameinfo" },
//	[LOG_FUNC_getservbyname] = { .Group = GROUP_Netdb, .Name = "getservbyname" },
//	[LOG_FUNC_getservbyport] = { .Group = GROUP_Netdb, .Name = "getservbyport" },

	// Poll.h
//	[LOG_FUNC_poll] = { .Group = GROUP_Poll, .Name = "poll" },
//	[LOG_FUNC_waitpoll] = { .Group = GROUP_Poll, .Name = "waitpoll" },

	// PThread.h
//	[LOG_FUNC_pthread_create] = { .Group = GROUP_PThread, .Name = "pthread_create" },
//	[LOG_FUNC_pthread_equal] = { .Group = GROUP_PThread, .Name = "pthread_equal" },
//	[LOG_FUNC_pthread_exit] = { .Group = GROUP_PThread, .Name = "pthread_exit" },
//	[LOG_FUNC_pthread_join] = { .Group = GROUP_PThread, .Name = "pthread_join" },
//	[LOG_FUNC_pthread_once] = { .Group = GROUP_PThread, .Name = "pthread_once" },
//	[LOG_FUNC_pthread_self] = { .Group = GROUP_PThread, .Name = "pthread_self" },
//	[LOG_FUNC_pthread_attr_init] = { .Group = GROUP_PThread, .Name = "pthread_attr_init" },
//	[LOG_FUNC_pthread_attr_destroy] = { .Group = GROUP_PThread, .Name = "pthread_attr_destroy" },
//	[LOG_FUNC_pthread_barrier_init] = { .Group = GROUP_PThread, .Name = "pthread_barrier_init" },
//	[LOG_FUNC_pthread_barrier_destroy] = { .Group = GROUP_PThread, .Name = "pthread_barrier_destroy" },
//	[LOG_FUNC_pthread_barrierattr_init] = { .Group = GROUP_PThread, .Name = "pthread_barrierattr_init" },
//	[LOG_FUNC_pthread_barrierattr_destroy] = { .Group = GROUP_PThread, .Name = "pthread_barrierattr_destroy" },
//	[LOG_FUNC_pthread_cond_init] = { .Group = GROUP_PThread, .Name = "pthread_cond_init" },
//	[LOG_FUNC_pthread_cond_wait] = { .Group = GROUP_PThread, .Name = "pthread_cond_wait" },
//	[LOG_FUNC_pthread_cond_signal] = { .Group = GROUP_PThread, .Name = "pthread_cond_signal" },
//	[LOG_FUNC_pthread_cond_broadcast] = { .Group = GROUP_PThread, .Name = "pthread_cond_boradcast" },
//	[LOG_FUNC_pthread_cond_timedwait] = { .Group = GROUP_PThread, .Name = "pthread_cond_timedwait" },
//	[LOG_FUNC_pthread_cond_destroy] = { .Group = GROUP_PThread, .Name = "pthread_cond_destroy" },
//	[LOG_FUNC_pthread_condattr_init] = { .Group = GROUP_PThread, .Name = "pthread_condattr_init" },
//	[LOG_FUNC_pthread_condattr_destroy] = { .Group = GROUP_PThread, .Name = "pthread_condattr_destroy" },
//	[LOG_FUNC_pthread_condattr_getclock] = { .Group = GROUP_PThread, .Name = "pthread_condattr_getclock" },
//	[LOG_FUNC_pthread_condattr_setclock] = { .Group = GROUP_PThread, .Name = "pthread_condattr_setclock" },
//	[LOG_FUNC_pthread_mutex_init] = { .Group = GROUP_PThread, .Name = "pthread_mutex_init" },
//	[LOG_FUNC_pthread_mutex_lock] = { .Group = GROUP_PThread, .Name = "pthread_mutex_lock" },
//	[LOG_FUNC_pthread_mutex_unlock] = { .Group = GROUP_PThread, .Name = "pthread_mutex_unlock" },
//	[LOG_FUNC_pthread_mutex_trylock] = { .Group = GROUP_PThread, .Name = "pthread_mutex_trylock" },
//	[LOG_FUNC_pthread_mutex_timedlock] = { .Group = GROUP_PThread, .Name = "pthread_mutex_timedlock" },
//	[LOG_FUNC_pthread_mutex_destroy] = { .Group = GROUP_PThread, .Name = "pthread_mutex_destroy" },
//	[LOG_FUNC_pthread_mutexattr_init] = { .Group = GROUP_PThread, .Name = "pthread_mutexattr_init" },
//	[LOG_FUNC_pthread_mutexattr_destroy] = { .Group = GROUP_PThread, .Name = "pthread_mutexattr_destroy" },
//	[LOG_FUNC_pthread_mutexattr_settype] = { .Group = GROUP_PThread, .Name = "pthread_mutexattr_settype" },
//	[LOG_FUNC_pthread_mutexattr_gettype] = { .Group = GROUP_PThread, .Name = "pthread_mutexattr_gettype" },
//	[LOG_FUNC_pthread_rwlock_init] = { .Group = GROUP_PThread, .Name = "pthread_rwlock_init" },
//	[LOG_FUNC_pthread_rwlock_rdlock] = { .Group = GROUP_PThread, .Name = "pthread_rwlock_rdlock" },
//	[LOG_FUNC_pthread_rwlock_wrlock] = { .Group = GROUP_PThread, .Name = "pthread_rwlock_wrlock" },
//	[LOG_FUNC_pthread_rwlock_unlock] = { .Group = GROUP_PThread, .Name = "pthread_rwlock_unlock" },
//	[LOG_FUNC_pthread_rwlock_tryrdlock] = { .Group = GROUP_PThread, .Name = "pthread_rwlock_tryrdlock" },
//	[LOG_FUNC_pthread_rwlock_trywrlock] = { .Group = GROUP_PThread, .Name = "pthread_rwlock_trywrlock" },
//	[LOG_FUNC_pthread_rwlock_timedrdlock] = { .Group = GROUP_PThread, .Name = "pthread_rwlock_timedrdlock" },
//	[LOG_FUNC_pthread_rwlock_timedwrlock] = { .Group = GROUP_PThread, .Name = "pthread_rwlock_timedwrlock" },
//	[LOG_FUNC_pthread_rwlock_destroy] = { .Group = GROUP_PThread, .Name = "pthread_rwlock_destroy" },
//	[LOG_FUNC_pthread_rwlockattr_init] = { .Group = GROUP_PThread, .Name = "pthread_rwlockattr_init" },
//	[LOG_FUNC_pthread_rwlockattr_destroy] = { .Group = GROUP_PThread, .Name = "pthread_rwlockattr_destroy" },
//	[LOG_FUNC_pthread_spinlock_init] = { .Group = GROUP_PThread, .Name = "pthread_spinlock_init" },
//	[LOG_FUNC_pthread_spinlock_lock] = { .Group = GROUP_PThread, .Name = "pthread_spinlock_lock" },
//	[LOG_FUNC_pthread_spinlock_unlock] = { .Group = GROUP_PThread, .Name = "pthread_spinlock_unlock" },
//	[LOG_FUNC_pthread_spinlock_trylock] = { .Group = GROUP_PThread, .Name = "pthread_spinlock_trylock" },
//	[LOG_FUNC_pthread_spinlock_destroy] = { .Group = GROUP_PThread, .Name = "pthread_spinlock_destroy" },

	// Pwd.h
	[LOG_FUNC_getpwuid] = { .Group = GROUP_Pwd, .Name = "getpwuid" },
	[LOG_FUNC_getpwnam] = { .Group = GROUP_Pwd, .Name = "getpwnam" },

	// Regex.h
//	[LOG_FUNC_regcomp] = { .Group = GROUP_Regex, .Name = "regcomp" },
//	[LOG_FUNC_regerror] = { .Group = GROUP_Regex, .Name = "regerror" },
//	[LOG_FUNC_regexec] = { .Group = GROUP_Regex, .Name = "regexec" },
//	[LOG_FUNC_regfree] = { .Group = GROUP_Regex, .Name = "regfree" },

	// Setjmp.h
//	[LOG_FUNC_longjmp] = { .Group = GROUP_Setjmp, .Name = "longjmp" },
//	[LOG_FUNC_setjmp] = { .Group = GROUP_Setjmp, .Name = "setjmp" },

	// Signal.h
	[LOG_FUNC_raise] = { .Group = GROUP_Signal, .Name = "raise" },
	[LOG_FUNC_signal] = { .Group = GROUP_Setjmp, .Name = "signal" },

	// Stdio.h
//	[LOG_FUNC_asprintf] = { .Group = GROUP_Stdio, .Name = "asprintf" },
	[LOG_FUNC_clearerr] = { .Group = GROUP_Stdio, .Name = "clearerr" },
//	[LOG_FUNC_ctermid] = { .Group = GROUP_Stdio, .Name = "ctermid" },
	[LOG_FUNC_fclose] = { .Group = GROUP_Stdio, .Name = "fclose" },
//	[LOG_FUNC_fdopen] = { .Group = GROUP_Stdio, .Name = "fdopen" },
//	[LOG_FUNC_feof] = { .Group = GROUP_Stdio, .Name = "feof" },
	[LOG_FUNC_ferror] = { .Group = GROUP_Stdio, .Name = "ferror" },
	[LOG_FUNC_fflush] = { .Group = GROUP_Stdio, .Name = "fflush" },
	[LOG_FUNC_fgetc] = { .Group = GROUP_Stdio, .Name = "fgetc" },
	[LOG_FUNC_fgetpos] = { .Group = GROUP_Stdio, .Name = "fgetpos" },
	[LOG_FUNC_fgets] = { .Group = GROUP_Stdio, .Name = "fgets" },
	[LOG_FUNC_fileno] = { .Group = GROUP_Stdio, .Name = "fileno" },
	[LOG_FUNC_flockfile] = { .Group = GROUP_Stdio, .Name = "flockfile" },
	[LOG_FUNC_fopen] = { .Group = GROUP_Stdio, .Name = "fopen" },
//	[LOG_FUNC_fprintf] = { .Group = GROUP_Stdio, .Name = "fprintf" },
	[LOG_FUNC_fputc] = { .Group = GROUP_Stdio, .Name = "fputc" },
	[LOG_FUNC_fputc_unlocked] = { .Group = GROUP_Stdio, .Name = "fputc_unlocked" },
	[LOG_FUNC_fputs] = { .Group = GROUP_Stdio, .Name = "fputs" },
	[LOG_FUNC_fread] = { .Group = GROUP_Stdio, .Name = "fread" },
//	[LOG_FUNC_fscanf] = { .Group = GROUP_Stdio, .Name = "fscanf" },
	[LOG_FUNC_fseek] = { .Group = GROUP_Stdio, .Name = "fseek" },
	[LOG_FUNC_fseeko] = { .Group = GROUP_Stdio, .Name = "fseeko" },
//	[LOG_FUNC_fsetpos] = { .Group = GROUP_Stdio, .Name = "fsetpos" },
	[LOG_FUNC_ftell] = { .Group = GROUP_Stdio, .Name = "ftell" },
//	[LOG_FUNC_ftello] = { .Group = GROUP_Stdio, .Name = "ftello" },
//	[LOG_FUNC_ftrylockfile] = { .Group = GROUP_Stdio, .Name = "ftrylockfile" },
	[LOG_FUNC_funlockfile] = { .Group = GROUP_Stdio, .Name = "funlockfile" },
//	[LOG_FUNC_fwrite] = { .Group = GROUP_Stdio, .Name = "fwrite" },
//	[LOG_FUNC_getc] = { .Group = GROUP_Stdio, .Name = "getc" },
//	[LOG_FUNC_getc_unlocked] = { .Group = GROUP_Stdio, .Name = "getc_unlocked" },
	[LOG_FUNC_getchar] = { .Group = GROUP_Stdio, .Name = "getchar" },
	[LOG_FUNC_getchar_unlocked] = { .Group = GROUP_Stdio, .Name = "getchar_unlocked" },
	[LOG_FUNC_getline] = { .Group = GROUP_Stdio, .Name = "getline" },
	[LOG_FUNC_getdelim] = { .Group = GROUP_Stdio, .Name = "getdelim" },
	[LOG_FUNC_perror] = { .Group = GROUP_Stdio, .Name = "perror" },
//	[LOG_FUNC_printf] = { .Group = GROUP_Stdio, .Name = "printf" },
	[LOG_FUNC_putc] = { .Group = GROUP_Stdio, .Name = "putc" },
	[LOG_FUNC_putc_unlocked] = { .Group = GROUP_Stdio, .Name = "putc_unlocked" },
	[LOG_FUNC_putchar] = { .Group = GROUP_Stdio, .Name = "putchar" },
	[LOG_FUNC_putchar_unlocked] = { .Group = GROUP_Stdio, .Name = "putchar_unlocked" },
	[LOG_FUNC_puts] = { .Group = GROUP_Stdio, .Name = "puts" },
	[LOG_FUNC_remove] = { .Group = GROUP_Stdio, .Name = "remove" },
	[LOG_FUNC_rename] = { .Group = GROUP_Stdio, .Name = "rename" },
	[LOG_FUNC_rewind] = { .Group = GROUP_Stdio, .Name = "rewind" },
//	[LOG_FUNC_scanf] = { .Group = GROUP_Stdio, .Name = "scanf" },
//	[LOG_FUNC_setbuf] = { .Group = GROUP_Stdio, .Name = "setbuf" },
	[LOG_FUNC_setvbuf] = { .Group = GROUP_Stdio, .Name = "setvbuf" },
//	[LOG_FUNC_snprintf] = { .Group = GROUP_Stdio, .Name = "snprintf" },
//	[LOG_FUNC_sprintf] = { .Group = GROUP_Stdio, .Name = "sprintf" },
//	[LOG_FUNC_sscanf] = { .Group = GROUP_Stdio, .Name = "sscanf" },
//	[LOG_FUNC_tmpfile] = { .Group = GROUP_Stdio, .Name = "tmpfile" },
//	[LOG_FUNC_tmpnam] = { .Group = GROUP_Stdio, .Name = "tmpnam" },
//	[LOG_FUNC_tmpnam_r] = { .Group = GROUP_Stdio, .Name = "tmpnam_r" },
	[LOG_FUNC_ungetc] = { .Group = GROUP_Stdio, .Name = "ungetc" },
	[LOG_FUNC_vasprintf] = { .Group = GROUP_Stdio, .Name = "vasprintf" },
//	[LOG_FUNC_vfprintf] = { .Group = GROUP_Stdio, .Name = "vfprintf" },
	[LOG_FUNC_vfscanf] = { .Group = GROUP_Stdio, .Name = "vfscanf" },
	[LOG_FUNC_vprintf] = { .Group = GROUP_Stdio, .Name = "vprintf" },
	[LOG_FUNC_vscanf] = { .Group = GROUP_Stdio, .Name = "vscanf" },
	[LOG_FUNC_vsnprintf] = { .Group = GROUP_Stdio, .Name = "vsnprintf" },
	[LOG_FUNC_vsprintf] = { .Group = GROUP_Stdio, .Name = "vsprintf" },

	// Stdlib.h
	[LOG_FUNC__Exit] = { .Group = GROUP_Stdio, .Name = "_Exit" },
	[LOG_FUNC_abort] = { .Group = GROUP_Stdio, .Name = "abort" },
	[LOG_FUNC_abs] = { .Group = GROUP_Stdio, .Name = "abs" },
//	[LOG_FUNC_arc4random] = { .Group = GROUP_Stdio, .Name = "arc4random" },
//	[LOG_FUNC_arc4random_buf] = { .Group = GROUP_Stdio, .Name = "arc4random_buf" },
//	[LOG_FUNC_arc4random_stir] = { .Group = GROUP_Stdio, .Name = "arc4random_stir" },
//	[LOG_FUNC_arc4random_uniform] = { .Group = GROUP_Stdio, .Name = "arc4random_uniform" },
//	[LOG_FUNC_arc4random_addrandom] = { .Group = GROUP_Stdio, .Name = "arc4random_addrandom" },
	[LOG_FUNC_atexit] = { .Group = GROUP_Stdio, .Name = "atexit" },
	[LOG_FUNC_atof] = { .Group = GROUP_Stdio, .Name = "atof" },
	[LOG_FUNC_atoi] = { .Group = GROUP_Stdio, .Name = "atoi" },
//	[LOG_FUNC_atol] = { .Group = GROUP_Stdio, .Name = "atol" },
//	[LOG_FUNC_atoll] = { .Group = GROUP_Stdio, .Name = "atoll" },
//	[LOG_FUNC_bsearch] = { .Group = GROUP_Stdio, .Name = "bsearch" },
	[LOG_FUNC_calloc] = { .Group = GROUP_Stdio, .Name = "calloc" },
//	[LOG_FUNC_div] = { .Group = GROUP_Stdio, .Name = "div" },
	[LOG_FUNC_exit] = { .Group = GROUP_Stdio, .Name = "exit" },
	[LOG_FUNC_free] = { .Group = GROUP_Stdio, .Name = "free" },
//	[LOG_FUNC_freezero] = { .Group = GROUP_Stdio, .Name = "freezero" },
//	[LOG_FUNC_getenv] = { .Group = GROUP_Stdio, .Name = "getenv" },
//	[LOG_FUNC_getprogname] = { .Group = GROUP_Stdio, .Name = "getprogname" },
//	[LOG_FUNC_initstate] = { .Group = GROUP_Stdio, .Name = "initstate" },
//	[LOG_FUNC_jrand48] = { .Group = GROUP_Stdio, .Name = "jrand48" },
//	[LOG_FUNC_labs] = { .Group = GROUP_Stdio, .Name = "labs" },
//	[LOG_FUNC_ldiv] = { .Group = GROUP_Stdio, .Name = "ldiv" },
//	[LOG_FUNC_llabs] = { .Group = GROUP_Stdio, .Name = "llabs" },
//	[LOG_FUNC_lldiv] = { .Group = GROUP_Stdio, .Name = "lldiv" },
//	[LOG_FUNC_lrand48] = { .Group = GROUP_Stdio, .Name = "lrand48" },
	[LOG_FUNC_malloc] = { .Group = GROUP_Stdio, .Name = "malloc" },
//	[LOG_FUNC_mblen] = { .Group = GROUP_Stdio, .Name = "mblen" },
//	[LOG_FUNC_mbtowc] = { .Group = GROUP_Stdio, .Name = "mbtowc" },
//	[LOG_FUNC_mrand48] = { .Group = GROUP_Stdio, .Name = "mrand48" },
//	[LOG_FUNC_nrand48] = { .Group = GROUP_Stdio, .Name = "nrand48" },
//	[LOG_FUNC_qsort] = { .Group = GROUP_Stdio, .Name = "qsort" },
	[LOG_FUNC_rand] = { .Group = GROUP_Stdio, .Name = "rand" },
	[LOG_FUNC_rand_r] = { .Group = GROUP_Stdio, .Name = "rand_r" },
	[LOG_FUNC_random] = { .Group = GROUP_Stdio, .Name = "random" },
	[LOG_FUNC_realloc] = { .Group = GROUP_Stdio, .Name = "realloc" },
//	[LOG_FUNC_reallocarray] = { .Group = GROUP_Stdio, .Name = "reallocarray" },
//	[LOG_FUNC_recallocarray] = { .Group = GROUP_Stdio, .Name = "recallocarray" },
//	[LOG_FUNC_setprogname] = { .Group = GROUP_Stdio, .Name = "setprogname" },
//	[LOG_FUNC_setstate] = { .Group = GROUP_Stdio, .Name = "setstate" },
	[LOG_FUNC_srand] = { .Group = GROUP_Stdio, .Name = "srand" },
//	[LOG_FUNC_srand48] = { .Group = GROUP_Stdio, .Name = "srand48" },
//	[LOG_FUNC_srandom] = { .Group = GROUP_Stdio, .Name = "srandom" },
	[LOG_FUNC_strtod] = { .Group = GROUP_Stdio, .Name = "strtod" },
	[LOG_FUNC_strtof] = { .Group = GROUP_Stdio, .Name = "strtof" },
	[LOG_FUNC_strtol] = { .Group = GROUP_Stdio, .Name = "strtol" },
//	[LOG_FUNC_strtoq] = { .Group = GROUP_Stdio, .Name = "strtoq" },
//	[LOG_FUNC_strtoll] = { .Group = GROUP_Stdio, .Name = "strtoll" },
//	[LOG_FUNC_strtoul] = { .Group = GROUP_Stdio, .Name = "strtoul" },
//	[LOG_FUNC_strtoull] = { .Group = GROUP_Stdio, .Name = "strtoull" },
//	[LOG_FUNC_system] = { .Group = GROUP_Stdio, .Name = "system" },
	[LOG_FUNC_mkstemp] = { .Group = GROUP_Stdio, .Name = "mkstemp" },

	// String.h
//	[LOG_FUNC_ffsl] = { .Group = GROUP_String, .Name = "ffsl" },
//	[LOG_FUNC_ffsll] = { .Group = GROUP_String, .Name = "ffsll" },
//	[LOG_FUNC_memccpy] = { .Group = GROUP_String, .Name = "memccpy" },
//	[LOG_FUNC_memchr] = { .Group = GROUP_String, .Name = "memchr" },
	[LOG_FUNC_memcmp] = { .Group = GROUP_String, .Name = "memcmp" },
	[LOG_FUNC_memcpy] = { .Group = GROUP_String, .Name = "memcpy" },
//	[LOG_FUNC_memmem] = { .Group = GROUP_String, .Name = "memmem" },
	[LOG_FUNC_memmove] = { .Group = GROUP_String, .Name = "memmove" },
	[LOG_FUNC_memset] = { .Group = GROUP_String, .Name = "memset" },
	[LOG_FUNC_stpcpy] = { .Group = GROUP_String, .Name = "stpcpy" },
//	[LOG_FUNC_stpncpy] = { .Group = GROUP_String, .Name = "stpncpy" },
	[LOG_FUNC_strcat] = { .Group = GROUP_String, .Name = "strcat" },
	[LOG_FUNC_strchr] = { .Group = GROUP_String, .Name = "strchr" },
	[LOG_FUNC_strcmp] = { .Group = GROUP_String, .Name = "strcmp" },
//	[LOG_FUNC_strcoll] = { .Group = GROUP_String, .Name = "strcoll" },
	[LOG_FUNC_strcpy] = { .Group = GROUP_String, .Name = "strcpy" },
	[LOG_FUNC_strcspn] = { .Group = GROUP_String, .Name = "strcspn" },
	[LOG_FUNC_strdup] = { .Group = GROUP_String, .Name = "strdup" },
	[LOG_FUNC_strerror] = { .Group = GROUP_String, .Name = "strerror" },
	[LOG_FUNC_strerror_r] = { .Group = GROUP_String, .Name = "strerror_r" },
//	[LOG_FUNC_strlcat] = { .Group = GROUP_String, .Name = "strlcat" },
//	[LOG_FUNC_strlcpy] = { .Group = GROUP_String, .Name = "strlcpy" },
	[LOG_FUNC_strlen] = { .Group = GROUP_String, .Name = "strlen" },
	[LOG_FUNC_strncmp] = { .Group = GROUP_String, .Name = "strncmp" },
	[LOG_FUNC_strncpy] = { .Group = GROUP_String, .Name = "strncpy" },
	[LOG_FUNC_strndup] = { .Group = GROUP_String, .Name = "strndup" },
	[LOG_FUNC_strnlen] = { .Group = GROUP_String, .Name = "strnlen" },
	[LOG_FUNC_strrchr] = { .Group = GROUP_String, .Name = "strrchr" },
	[LOG_FUNC_strpbrk] = { .Group = GROUP_String, .Name = "strpbrk" },
//	[LOG_FUNC_strrchr] = { .Group = GROUP_String, .Name = "strrchr" },
//	[LOG_FUNC_strsep] = { .Group = GROUP_String, .Name = "strsep" },
	[LOG_FUNC_strspn] = { .Group = GROUP_String, .Name = "strspn" },
	[LOG_FUNC_strstr] = { .Group = GROUP_String, .Name = "strstr" },
	[LOG_FUNC_strtok] = { .Group = GROUP_String, .Name = "strtok" },
//	[LOG_FUNC_strtok_r] = { .Group = GROUP_String, .Name = "strtok_r" },
//	[LOG_FUNC_strxfrm] = { .Group = GROUP_String, .Name = "strxfrm" },
//	[LOG_FUNC_timingsafe_memcmp] = { .Group = GROUP_String, .Name = "timingsafe_memcmp" },

	// Strings.h
//	[LOG_FUNC_bcmp] = { .Group = GROUP_Strings, .Name = "bcmp" },
//	[LOG_FUNC_bcopy] = { .Group = GROUP_Strings, .Name = "bcopy" },
	[LOG_FUNC_bzero] = { .Group = GROUP_Strings, .Name = "bzero" },
//	[LOG_FUNC_explicit_bzero] = { .Group = GROUP_Strings, .Name = "explicit_bzero" },
//	[LOG_FUNC_ffs] = { .Group = GROUP_Strings, .Name = "ffs" },
//	[LOG_FUNC_index] = { .Group = GROUP_Strings, .Name = "index" },
//	[LOG_FUNC_rindex] = { .Group = GROUP_Strings, .Name = "rindex" },
	[LOG_FUNC_strcasecmp] = { .Group = GROUP_Strings, .Name = "strcasecmp" },
	[LOG_FUNC_strncasecmp] = { .Group = GROUP_Strings, .Name = "strncasecmp" },
//	[LOG_FUNC_timingsafe_bcmp] = { .Group = GROUP_Strings, .Name = "timingsafe_bcmp" },

	// Time.h
//	[LOG_FUNC_asctime] = { .Group = GROUP_Time, .Name = "asctime" },
//	[LOG_FUNC_asctime_r] = { .Group = GROUP_Time, .Name = "asctime_r" },
//	[LOG_FUNC_clock] = { .Group = GROUP_Time, .Name = "clock" },
	[LOG_FUNC_clock_gettime] = { .Group = GROUP_Time, .Name = "clock_gettime" },
	[LOG_FUNC_clock_settime] = { .Group = GROUP_Time, .Name = "clock_settime" },
//	[LOG_FUNC_ctime] = { .Group = GROUP_Time, .Name = "ctime" },
//	[LOG_FUNC_ctime_r] = { .Group = GROUP_Time, .Name = "ctime_r" },
//	[LOG_FUNC_gmtime] = { .Group = GROUP_Time, .Name = "gmtime" },
//	[LOG_FUNC_gmtime_r] = { .Group = GROUP_Time, .Name = "gmtime_r" },
	[LOG_FUNC_localtime] = { .Group = GROUP_Time, .Name = "localtime" },
//	[LOG_FUNC_localtime_r] = { .Group = GROUP_Time, .Name = "localtime_r" },
//	[LOG_FUNC_mktime] = { .Group = GROUP_Time, .Name = "mktime" },
	[LOG_FUNC_time] = { .Group = GROUP_Time, .Name = "time" },
//	[LOG_FUNC_timegm] = { .Group = GROUP_Time, .Name = "timegm" },
	[LOG_FUNC_strftime] = { .Group = GROUP_Time, .Name = "strftime" },

	// Unistd.h
//	[LOG_FUNC__exit] = { .Group = GROUP_Unistd, .Name = "_exit" },
	[LOG_FUNC_close] = { .Group = GROUP_Unistd, .Name = "close" },
	[LOG_FUNC_chown] = { .Group = GROUP_Unistd, .Name = "chown" },
//	[LOG_FUNC_ftruncate] = { .Group = GROUP_Unistd, .Name = "ftruncate" },
	[LOG_FUNC_getcwd] = { .Group = GROUP_Unistd, .Name = "getcwd" },
	[LOG_FUNC_geteuid] = { .Group = GROUP_Unistd, .Name = "geteuid" },
	[LOG_FUNC_getegid] = { .Group = GROUP_Unistd, .Name = "getegid" },
	[LOG_FUNC_getgroups] = { .Group = GROUP_Unistd, .Name = "getgroups" },
	[LOG_FUNC_gethostname] = { .Group = GROUP_Unistd, .Name = "gethostname" },
//	[LOG_FUNC_getpagesize] = { .Group = GROUP_Unistd, .Name = "getpagesize" },
	[LOG_FUNC_getpid] = { .Group = GROUP_Unistd, .Name = "getpid" },
//	[LOG_FUNC_getppid] = { .Group = GROUP_Unistd, .Name = "getppid" },
//	[LOG_FUNC_getwd] = { .Group = GROUP_Unistd, .Name = "getwd" },
	[LOG_FUNC_isatty] = { .Group = GROUP_Unistd, .Name = "isatty" },
	[LOG_FUNC_link] = { .Group = GROUP_Unistd, .Name = "link" },
	[LOG_FUNC_lseek] = { .Group = GROUP_Unistd, .Name = "lseek" },
//	[LOG_FUNC_pread] = { .Group = GROUP_Unistd, .Name = "pread" },
//	[LOG_FUNC_pwrite] = { .Group = GROUP_Unistd, .Name = "pwrite" },
	[LOG_FUNC_read] = { .Group = GROUP_Unistd, .Name = "read" },
	[LOG_FUNC_rmdir] = { .Group = GROUP_Unistd, .Name = "rmdir" },
	[LOG_FUNC_symlink] = { .Group = GROUP_Unistd, .Name = "symlink" },
//	[LOG_FUNC_swab] = { .Group = GROUP_Unistd, .Name = "swab" },
	[LOG_FUNC_unlink] = { .Group = GROUP_Unistd, .Name = "unlink" },
	[LOG_FUNC_write] = { .Group = GROUP_Unistd, .Name = "write" },


	// UTime.h
	[LOG_FUNC_utime] = { .Group = GROUP_UTime, .Name = "utime" },

	// WChar.h
	[LOG_FUNC_mbrtowc] = { .Group = GROUP_WChar, .Name = "mbrtowc" },
	[LOG_FUNC_mbstowcs] = { .Group = GROUP_WChar, .Name = "mbstowcs" },
//	[LOG_FUNC_wcscat] = { .Group = GROUP_WChar, .Name = "wcscat" },
//	[LOG_FUNC_wcschr] = { .Group = GROUP_WChar, .Name = "wcschr" },
//	[LOG_FUNC_wcscmp] = { .Group = GROUP_WChar, .Name = "wcscmp" },
//	[LOG_FUNC_wcslcat] = { .Group = GROUP_WChar, .Name = "wcslcat" },
//	[LOG_FUNC_wcslcpy] = { .Group = GROUP_WChar, .Name = "wcslcpy" },
//	[LOG_FUNC_wcslen] = { .Group = GROUP_WChar, .Name = "wcslen" },
//	[LOG_FUNC_wmemchr] = { .Group = GROUP_WChar, .Name = "wmemchr" },
//	[LOG_FUNC_wmemcmp] = { .Group = GROUP_WChar, .Name = "wmemcmp" },
//	[LOG_FUNC_wmemcpy] = { .Group = GROUP_WChar, .Name = "wmemcpy" },
//	[LOG_FUNC_wmemmove] = { .Group = GROUP_WChar, .Name = "wmemmove" },
//	[LOG_FUNC_wmemset] = { .Group = GROUP_WChar, .Name = "wmemset" },

	// Sys / Socket.h
//	[LOG_FUNC_accept] = { .Group = GROUP_Sys_Socket, .Name = "accept" },
//	[LOG_FUNC_bind] = { .Group = GROUP_Sys_Socket, .Name = "bind" },
//	[LOG_FUNC_connect] = { .Group = GROUP_Sys_Socket, .Name = "connect" },
//	[LOG_FUNC_getpeername] = { .Group = GROUP_Sys_Socket, .Name = "getpeername" },
//	[LOG_FUNC_getsockname] = { .Group = GROUP_Sys_Socket, .Name = "getsockname" },
//	[LOG_FUNC_getsockopt] = { .Group = GROUP_Sys_Socket, .Name = "getsockopt" },
//	[LOG_FUNC_inet_addr] = { .Group = GROUP_Sys_Socket, .Name = "inet_addr" },
//	[LOG_FUNC_inet_ntoa] = { .Group = GROUP_Sys_Socket, .Name = "inet_ntoa" },
//	[LOG_FUNC_inet_ntop] = { .Group = GROUP_Sys_Socket, .Name = "inet_ntop" },
//	[LOG_FUNC_inet_pton] = { .Group = GROUP_Sys_Socket, .Name = "inet_pton" },
//	[LOG_FUNC_listen] = { .Group = GROUP_Sys_Socket, .Name = "listen" },
//	[LOG_FUNC_recv] = { .Group = GROUP_Sys_Socket, .Name = "recv" },
//	[LOG_FUNC_recvfrom] = { .Group = GROUP_Sys_Socket, .Name = "recvfrom" },
//	[LOG_FUNC_select] = { .Group = GROUP_Sys_Socket, .Name = "select" },
//	[LOG_FUNC_send] = { .Group = GROUP_Sys_Socket, .Name = "send" },
//	[LOG_FUNC_sendto] = { .Group = GROUP_Sys_Socket, .Name = "sendto" },
//	[LOG_FUNC_setsockopt] = { .Group = GROUP_Sys_Socket, .Name = "setsockopt" },
//	[LOG_FUNC_shutdown] = { .Group = GROUP_Sys_Socket, .Name = "shutdown" },
//	[LOG_FUNC_socket] = { .Group = GROUP_Sys_Socket, .Name = "socket" },
//	[LOG_FUNC_waitselect] = { .Group = GROUP_Sys_Socket, .Name = "waitselect" },

	// Sys / Stat.h
	[LOG_FUNC_chmod] = { .Group = GROUP_Sys_Stat, .Name = "chmod" },
	[LOG_FUNC_fstat] = { .Group = GROUP_Sys_Stat, .Name = "fstat" },
	[LOG_FUNC_lstat] = { .Group = GROUP_Sys_Stat, .Name = "lstat" },
	[LOG_FUNC_mkdir] = { .Group = GROUP_Sys_Stat, .Name = "mkdir" },
	[LOG_FUNC_mktemp] = { .Group = GROUP_Sys_Stat, .Name = "mktemp" },
	[LOG_FUNC_stat] = { .Group = GROUP_Sys_Stat, .Name = "stat" },
	[LOG_FUNC_umask] = { .Group = GROUP_Sys_Stat, .Name = "umask" },

	// Sys / Time.h
	[LOG_FUNC_gettimeofday] = { .Group = GROUP_Sys_Time, .Name = "gettimeofday" },

	// Sys / Uio.h
//	[LOG_FUNC_readv] = { .Group = GROUP_Sys_Uio, .Name = "readv" },
//	[LOG_FUNC_writev] = { .Group = GROUP_Sys_Uio, .Name = "writev" },
};

static STR GroupNames[GROUP_LAST] =
{
/* xx */ "",
/*  1 */ "## Amiga ##",
/*  2 */ "## Assert ##",
/*  3 */ "## CType ##",
/*  4 */ "## Dirent ##",
/*  5 */ "## FCntl ##",
/*  6 */ "## Inttypes ##",
/*  7 */ "## Locale ##",
/*  8 */ "## Math (Float) ##",
/*  9 */ "## Math (Double) ##",
/* 10 */ "## Math (Long Double) ##",
/* 11 */ "## Netdb ##",
/* 12 */ "## Poll ##",
/* 13 */ "## PThread ##",
/* 14 */ "## Regex ##",
/* 15 */ "## Setjmp ##",
/* 16 */ "## Signal ##",
/* 17 */ "## Stdio ##",
/* 18 */ "## Stdlib ##",
/* 19 */ "## String ##",
/* 20 */ "## Strings ##",
/* 21 */ "## Time ##",
/* 22 */ "## Unistd ##",
/* 23 */ "## UTime ##",
/* 24 */ "## WChar ##",
/* 25 */ "## Sys / Socket ##",
/* 26 */ "## Sys / Stat ##",
/* 27 */ "## Sys / Time ##",
/* 28 */ "## Sys / Uio ##",
};

#endif
// --
#ifdef __DO_FUNCTION_LOG__

static int myPrintF( struct AmyCLibIFace *Self, const char *fmt, ... )
{
va_list ap;
int retval;

	va_start( ap, fmt );

	retval = Self->stdio_vprintf( fmt, ap );

	va_end( ap );

	return(	retval );
}

#endif
// --

void _generic__Priv_Print_Log( struct AmyCLibIFace *Self UNUSED )
{

#ifdef __DO_FUNCTION_LOG__

struct libData *data;
U8 groups[GROUP_LAST];
S32 addnl;
STR prgname;
STR str;
S32 grp;
S32 cnt;

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	if ( ! data->buf_FuncLogs )
	{
		goto bailout;
	}

	// Make sure we are not started again
	data->TrackFuncUsage = 0;

	// --

	addnl = FALSE;

	Self->string_memset( & groups, 0, GROUP_LAST );

	for( cnt=0 ; cnt<LOG_FUNC_LAST ; cnt++ )
	{
		if ( data->buf_FuncLogs[cnt] )
		{
			grp = ( myStrings[cnt].Group );
			str = ( myStrings[cnt].Name ) ? myStrings[cnt].Name : "" ;

			if ( ! groups[ grp ] )
			{
				groups[ grp ] = 1;

				if ( ! addnl )
				{
					prgname = data->buf_progname;

					if ( ! prgname )
					{
						prgname = IExec->FindTask(NULL)->tc_Node.ln_Name;
					}

					myPrintF( Self, "\n##\n## PrgName: %s\n##\n\n", prgname );

					addnl = TRUE;
				}

				myPrintF( Self, "\n%s\n\n", GroupNames[grp] );
			}

			myPrintF( Self, "%8lld : %s\n", data->buf_FuncLogs[cnt], str );
		}
	}

	if ( addnl )
	{
		myPrintF( Self, "\n" );
	}

	IExec->FreeVec( data->buf_FuncLogs );
	data->buf_FuncLogs = NULL;

bailout:

#endif

	return;
}

// --

void _generic__Priv_Func_Log( struct AmyCLibIFace *Self UNUSED, S32 xx UNUSED )
{

	#ifdef __DO_FUNCTION_LOG__

struct libData *data;

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	if ( ! data->TrackFuncUsage )
	{
		goto bailout;
	}

	if ( LOG_FUNC_LAST <= xx )
	{
		goto bailout;
	}

	if ( ! data->buf_FuncLogs )
	{
		// Too avoid a deadlock we are allocating with the System
		// instead of using our own Memory function.
		data->buf_FuncLogs = IExec->AllocVecTags( sizeof( uint64 ) * LOG_FUNC_LAST,
			AVT_Clear, 0,
			TAG_END
		);

		if ( ! data->buf_FuncLogs )
		{
			goto bailout;
		}
	}

	data->buf_FuncLogs[xx]++;

bailout:

	#endif

	return;
}

// --
