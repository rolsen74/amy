
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

/* -- */

#ifndef AMYSYS_UTMP_H
#define AMYSYS_UTMP_H

/****************************************************************************/
// Trying to maych Roadshow's defines


#define UT_LINESIZE		32
#define UT_NAMESIZE		32
#define UT_HOSTSIZE		256

struct lastlog
{
	U32				ll_time;
	U32				ll_sid;
	char			ll_name[UT_NAMESIZE];
	char			ll_host[UT_HOSTSIZE];
};

struct utmp
{
	U32				ut_time;
	U32				ut_sid;
	char			ut_name[UT_NAMESIZE];
	char			ut_host[UT_HOSTSIZE];
};

/****************************************************************************/

#endif /* AMYSYS_UTMP_H */
