
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

#ifndef AMYSYS_SYS_WAIT_H
#define AMYSYS_SYS_WAIT_H

#include <signal.h>
#include <sys/types.h>

AMY_EXTERN_C_BEGIN

/****************************************************************************/

typedef int idtype_t;

#define P_ALL		0
#define P_PID		1
#define P_PGID		2

#define WNOHANG		0x00000001
#define WUNTRACED	0x00000002
#define WSTOPPED	WUNTRACED
#define WEXITED		0x00000004
#define WCONTINUED	0x00000008
#define WNOWAIT		0x01000000

#define WIFCONTINUED(x) 	( (x) == 0xFFFF )
#define WIFEXITED(x)		(((x) & 0x7F ) == 0 )
#define WTERMSIG(x)			( (x) & 0x7F )
#define WIFSTOPPED(x)		(((x) & 0xFF ) == 0x7F )
#define WIFSIGNALED(x)		((((x) & 0x7F ) != 0 ) && (((x) & 0x7F ) != 0x7F ))
#define WSTOPSIG(x)			(((x) >> 8 ) & 0xFF )
#define WEXITSTATUS(x)		(((x) >> 8 ) & 0xFF )

/****************************************************************************/

pid_t	wait( int * );
int		waitid( idtype_t, id_t, siginfo_t *, int );
pid_t	waitpid( pid_t, int *, int );

/****************************************************************************/

AMY_EXTERN_C_END

#endif /* AMYSYS_SYS_WAIT_H */
