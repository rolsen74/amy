
/*
** Based on The Open Group Base Specifications Issue 7
**
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
**
******************************************************************************
** This file is part of Amy C Lib
*/

/* --------------------------------------------------------------------------
** Always include Amy_Features.h FIRST — this defines feature macros like
** _FILE_OFFSET_BITS and _TIME_BITS before any typedefs depend on them.
** -------------------------------------------------------------------------- 
*/

#include <Amy_Features.h>
#include <Amy_Defines.h>

#ifndef AMYSYS_LIMITS_H
#define AMYSYS_LIMITS_H

AMY_EXTERN_C_BEGIN

/****************************************************************************/
// Runtime Invariant Values

#define AIO_LISTIO_MAX					0xac
#define AIO_MAX							0xac
#define AIO_PRIO_DELTA_MAX				0xac
#define ARG_MAX							0xac
#define ATEXIT_MAX						10000
#define CHILD_MAX						0xac
#define DELAYTIMER_MAX					0xac
#define HOST_NAME_MAX					0xac
#define IOV_MAX							0xac
#define LOGIN_NAME_MAX					0xac
#define MQ_OPEN_MAX						0xac
#define OPEN_MAX						0xac
//#define PAGESIZE						  4096
//#define PAGE_SIZE						  4096
#define PTHREAD_DESTRUCTOR_ITERATIONS	4
#define PTHREAD_KEYS_MAX				64
#define PTHREAD_STACK_MIN				40960
#define PTHREAD_THREADS_MAX				256
#define RTSIG_MAX						0xac
#define SEM_NSEMS_MAX					256
#define SEM_VALUE_MAX					INT_MAX
#define SIGQUEUE_MAX					0xac
#define SS_REPL_MAX						0xac
#define STREAM_MAX						0xac
#define SYMLOOP_MAX						0xac
#define TIMER_MAX						0xac
#define TRACE_EVENT_NAME_MAX			0xac
#define TRACE_NAME_MAX					0xac
#define TRACE_SYS_MAX					0xac
#define TRACE_USER_EVENT_MAX			0xac
#define TTY_NAME_MAX					0xac
#define TZNAME_MAX						0xac

/****************************************************************************/
// Pathname Variable Values

#define FILESIZEBITS					32
#define LINK_MAX						0xac
#define MAX_CANON						0xac
#define MAX_INPUT						0xac
#define NAME_MAX						0xac
#define PATH_MAX						1024
#define PIPE_BUF						0xac
#define POSIX_ALLOC_SIZE_MIN			0xac
#define POSIX_REC_INCR_XFER_SIZE		0xac
#define POSIX_REC_MAX_XFER_SIZE			0xac
#define POSIX_REC_MIN_XFER_SIZE			0xac
#define POSIX_REC_XFER_ALIGN			0xac
#define SYMLINK_MAX						0xac

// Not sure were this one belong
#define MAXPATHLEN						PATH_MAX

/****************************************************************************/
// Runtime Increasable Values

#define BC_BASE_MAX						0xac
#define BC_DIM_MAX						0xac
#define BC_SCALE_MAX					0xac
#define BC_STRING_MAX					0xac
#define CHARCLASS_NAME_MAX				0xac
#define COLL_WEIGHTS_MAX				0xac
#define EXPR_NEST_MAX					0xac
#define LINE_MAX						0xac
#define NGGROUPS_MAX					0xac
#define RE_DUP_MAX						0xac

/****************************************************************************/
// Maximum Values

#define _POSIX_CLOCKRES_MIN				20000000

/****************************************************************************/
// Minimum Values

#define _POSIX_AIO_LISTIO_MAX			2
#define _POSIX_AIO_MAX					1
#define _POSIX_ARG_MAX					4096
#define _POSIX_CHILD_MAX				25
#define _POSIX_DELAYTIMER_MAX			32
#define _POSIX_HOST_NAME_MAX			255
#define _POSIX_LINK_MAX					8
#define _POSIX_LOGIN_NAME_MAX			9
#define _POSIX_MAX_CANON				255
#define _POSIX_MAX_INPUT				255
#define _POSIX_MQ_OPEN_MAX				8
#define _POSIX_MQ_PRIO_MAX				32
#define _POSIX_NAME_MAX					14
#define _POSIX_NGROUP_MAX				8
#define _POSIX_OPEN_MAX					20
#define _POSIX_PATH_MAX					256
#define _POSIX_PIPE_BUF					512
#define _POSIX_RE_DUP_MAX				255
#define _POSIX_RTSIG_MAX				8
#define _POSIX_SEM_NSEMS_MAX			256
#define _POSIX_SEM_VALUE_MAX			32767
#define _POSIX_SIGQUEUE_MAX				32
#define _POSIX_SSIZE_MAX				32767
#define _POSIX_SS_REPL_MAX				4
#define _POSIX_STREAM_MAX				8
#define _POSIX_SYMLINK_MAX				255
#define _POSIX_SYMLOOP_MAX				8
#define _POSIX_THREAD_DESTRUCTOR_ITERATIONS	4
#define _POSIX_THREAD_THREADS_MAX		64
#define _POSIX_TIMER_MAX				32
#define _POSIX_TRACE_EVENT_NAME_MAX		30
#define _POSIX_TRACE_NAME_MAX			8
#define _POSIX_TRACE_SYS_MAX			8
#define _POSIX_TRACE_USER_EVENT_MAX		32
#define _POSIX_TTY_NAME_MAX				9
#define _POSIX_TZNAME_MAX				6
#define _POSIX2_BC_BASE_MAX				99
#define _POSIX2_BC_DIM_MAX				2048
#define _POSIX2_BC_SCALE_MAX			99
#define _POSIX2_BC_STRING_MAX			1000
#define _POSIX2_CHARCLASS_NAME_MAX		14
#define _POSIX2_COLL_WEIGHTS_MAX		2
#define _POSIX2_EXPR_NEST_MAX			32
#define _POSIX2_LINE_MAX				2048
#define _POSIX2_RE_DUP_MAX				255
#define _XOPEN_IOV_MAX					16
#define _XOPEN_NAME_MAX					255
#define _XOPEN_PATH_MAX					1024

/****************************************************************************/
// Numerical Limits

#define SCHAR_MIN						-128
#define SCHAR_MAX						+127

#define UCHAR_MIN						0
#define UCHAR_MAX						255

#define SHRT_MIN						-32767
#define SHRT_MAX						+32767

#define USHRT_MIN						0
#define USHRT_MAX						65535

#define INT_MIN							-2147483647
#define INT_MAX							+2147483647

#define UINT_MIN						0
#define UINT_MAX						4294967295U

#define LONG_BIT						32
#define LONG_MIN						-2147483647L
#define LONG_MAX						+2147483647L

#define ULONG_MIN						0
#define ULONG_MAX						4294967295UL

#define LLONG_MIN						-9223372036854775807LL
#define LLONG_MAX   					+9223372036854775807LL
#define ULLONG_MAX						18446744073709551615ULL

#define WORD_BIT						32

#define CHAR_BIT						8

#ifdef __CHAR_UNSIGNED__
 #define CHAR_MIN						UCHAR_MIN
 #define CHAR_MAX						UCHAR_MAX
#else
 #define CHAR_MIN						SCHAR_MIN
 #define CHAR_MAX						SCHAR_MAX
#endif

#define MB_LEN_MAX						1
#define SSIZE_MAX						_POSIX_SSIZE_MAX

/****************************************************************************/
// Other Invariant Values

#define NL_ARGMAX						9
#define NL_LANGMAX						14
#define NL_MSGMAX						32767
#define NL_SETMAX						255
#define NL_TEXTMAX						_POSIX2_LINE_MAX
#define NZERO							20

/****************************************************************************/

// OpenBSD

#define UQUAD_MAX		0xffffffffffffffffULL		// Max unsigned
#define QUAD_MAX		0x7fffffffffffffffLL		// Max signed
#define QUAD_MIN		(-0x7fffffffffffffffLL-1 )  // Min signed

/****************************************************************************/

AMY_EXTERN_C_END

#endif /* AMYSYS_LIMITS_H */
