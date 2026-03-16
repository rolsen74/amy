
/*
** Based on The Open Group Base Specifications Issue 8
**
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2026 Rene W. Olsen
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

#ifndef AMYSYS_POLL_H
#define AMYSYS_POLL_H

#include <signal.h>
#include <time.h>

AMY_EXTERN_C_BEGIN

/****************************************************************************/

#define POLLIN			0x0001
#define POLLPRI			0x0002
#define POLLOUT			0x0004
#define POLLERR			0x0008
#define POLLHUP			0x0010
#define POLLNVAL		0x0020
#define POLLRDNORM		POLLIN
#define POLLRDBAND		0x0040
#define POLLWRNORM		POLLOUT
#define POLLWRBAND		0x0080

typedef unsigned long	nfds_t;

struct pollfd
{
	int		fd;
	short	events;
	short	revents;
};

/****************************************************************************/

int		poll(	struct pollfd *, nfds_t, int );
int		ppoll(	struct pollfd *, nfds_t, const struct timespec *, const sigset_t * );

/****************************************************************************/

AMY_EXTERN_C_END

#endif /* AMYSYS_POLL_H */
