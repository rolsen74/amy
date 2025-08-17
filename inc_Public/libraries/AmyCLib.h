
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Portions based on clib2 by Olaf Barthel (2002–2016)
** Target OS: AmigaOS
*/

#ifndef AMYLIB_LIBRARIES_AMYCLIB_H
#define AMYLIB_LIBRARIES_AMYCLIB_H

// --

#include "Amy_Defines.h"
#include <stdio.h>

// --
// Emable Mask .. should proberly rename

#define EM_ALWAYS 			-1U
#define EM_FILE				1
#define EM_STRING			2
#define EM_MEMORY			4
#define EM_LOCALE			8

// --

struct _AmyCLibPublic
{
	// Version v1.1

	int			ra_ErrNo;		// Errno.h

	FILE *		ra_stderr;		// Stdio.h
	FILE *		ra_stdin;		// Stdio.h
	FILE *		ra_stdout;		// Stdio.h

	int			ra_h_ErrNo;		// Netdb.h

//	fenv_t		ra_fenv;		// fenv.h - Default float envirement
//
// --	 int		 ra_daylight;	 // Time.h
// --	 long int	 ra_timezone;	 // Time.h
// --	 char **	 ra_tzname;		 // Time.h
//
//
// --	 int		 ra_signgam;	 // Math.h
};

extern struct _AmyCLibPublic * __AmyCPublicData;
#define AmyCLibPublic __AmyCPublicData

// --

#endif
