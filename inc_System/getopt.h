
/*
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
#include <Amy_Public.h>

/* -- */

#ifndef AMYSYS_GETOPT_H
#define AMYSYS_GETOPT_H

/****************************************************************************/

#include <unistd.h>

/****************************************************************************/

#define no_argument			0
#define required_argument	1
#define optional_argument	2

/****************************************************************************/

struct option
{
	const char *	name;
	int				has_arg;
	int *			flag;
	int				val;
};

/****************************************************************************/

AMY_EXTERN_C_BEGIN

int		getopt(				int argc, char * const argv[], const char *optstring );
int		getopt_long(		int argc, char * const argv[], const char *optstring, const struct option *longopts, int *longindex );
int		getopt_long_only(	int argc, char * const argv[], const char *optstring, const struct option *longopts, int *longindex );

AMY_EXTERN_C_END

/****************************************************************************/

#define optarg	AmyCLibPublic->ra_optarg
#define optind	AmyCLibPublic->ra_optind
#define opterr	AmyCLibPublic->ra_opterr
#define optopt	AmyCLibPublic->ra_optopt

/****************************************************************************/

#endif /* AMYSYS_GETOPT_H */
