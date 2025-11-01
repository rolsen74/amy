
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

/* -- */

#ifndef AMYSYS_LANGINFO_H
#define AMYSYS_LANGINFO_H

/****************************************************************************/

#include <locale.h>
#include <nl_types.h>

/****************************************************************************/

typedef int nl_item;

/****************************************************************************/

enum
{
	D_T_FMT = 0,
	D_FMT,
	T_FMT,
	T_FMT_AMPM,
	AM_STR,
	PM_STR,

	DAY_1,
	DAY_2,
	DAY_3,
	DAY_4,
	DAY_5,
	DAY_6,
	DAY_7,

	ABDAY_1,
	ABDAY_2,
	ABDAY_3,
	ABDAY_4,
	ABDAY_5,
	ABDAY_6,
	ABDAY_7,

	MON_1,
	MON_2,
	MON_3,
	MON_4,
	MON_5,
	MON_6,
	MON_7,
	MON_8,
	MON_9,
	MON_10,
	MON_11,
	MON_12,

	ABMON_1,
	ABMON_2,
	ABMON_3,
	ABMON_4,
	ABMON_5,
	ABMON_6,
	ABMON_7,
	ABMON_8,
	ABMON_9,
	ABMON_10,
	ABMON_11,
	ABMON_12,

	ERA,
	ERA_D_FMT,
	ERA_D_T_FMT,
	ERA_T_FMT,
	ALT_DIGITS,
	
	RADIXCHAR,
	THOUSEP,
	YESEXPR,
	NOEXPR,
	CRNCYSTR,

	CODESET,
};

/****************************************************************************/

AMY_EXTERN_C_BEGIN

char *	nl_langinfo( nl_item );
char *	nl_langinfol( nl_item, locale_t );

AMY_EXTERN_C_END

/****************************************************************************/

#endif
