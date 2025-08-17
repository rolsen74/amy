
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

#ifndef AMYSYS_SYS_SELECT_H
#define AMYSYS_SYS_SELECT_H

/****************************************************************************/

#include <Amy_Defines.h>	// Need AMY_EXTERN_C_BEGIN
#include <signal.h>
#include <time.h>
#include <string.h>			// for memmove and memset

/****************************************************************************/

#ifndef FD_SET

#define FD_SETSIZE	256

typedef	struct
{
	U32 bits[ ( FD_SETSIZE + 31 ) / 32 ];

} fd_set;

#define	FD_SET(n,p)		(( (p)->bits[ n >> 5 ] |=  ( 1UL << ( n & 31 ))))
#define	FD_CLR(n,p)		(( (p)->bits[ n >> 5 ] &= ~( 1UL << ( n & 31 ))))
#define	FD_ISSET(n,p)	(( (p)->bits[ n >> 5 ] &   ( 1UL << ( n & 31 ))))
#define	FD_COPY(f,t)	( memmove( t, f, sizeof( *f )))
#define	FD_ZERO(p)		( memset(  p, 0, sizeof( *p )))

#endif

/****************************************************************************/

AMY_EXTERN_C_BEGIN

int	pselect( int, fd_set *, fd_set *, fd_set *, const struct timespec *, const sigset_t * );

// Amiga
struct timeval;
int waitselect( int, fd_set *, fd_set *, fd_set *, struct timeval *, unsigned long * );

AMY_EXTERN_C_END

/****************************************************************************/

#endif

