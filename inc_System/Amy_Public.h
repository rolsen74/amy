
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
**
******************************************************************************
** This file is part of Amy C Lib
*/

/* -- */

#ifndef AMYSYS_PUBLIC_H
#define AMYSYS_PUBLIC_H

/****************************************************************************/

#include <stdio.h>		// FILE
#include <fenv.h>		// fenv_t

/****************************************************************************/

struct _AmyCLibPublic
{
	// Version v1.1

	int				ra_ErrNo;		// Errno.h

	char *			ra_optarg;		// Locale.h
	int				ra_optind;		// Locale.h
	int				ra_opterr;		// Locale.h
	int				ra_optopt;		// Locale.h

	FILE *			ra_stderr;		// Stdio.h
	FILE *			ra_stdin;		// Stdio.h
	FILE *			ra_stdout;		// Stdio.h

	int				ra_h_ErrNo;		// Netdb.h

	int				ra_signgam;		// Math.h

	int				ra_daylight;	// Time.h
	long int		ra_timezone;	// Time.h
	char **			ra_tzname;		// Time.h

	const fenv_t	ra_fenv;		// FEnv.h
};

// --

extern struct _AmyCLibPublic *__AmyCPublicData;
#define AmyCLibPublic __AmyCPublicData

/****************************************************************************/

#endif
