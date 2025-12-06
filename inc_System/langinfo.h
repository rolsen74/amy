
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

#ifndef AMYSYS_LANGINFO_H
#define AMYSYS_LANGINFO_H

#include <locale.h>
#include <nl_types.h>

AMY_EXTERN_C_BEGIN

/****************************************************************************/

#ifndef _NL_ITEM_DEFINED
#define _NL_ITEM_DEFINED
typedef int nl_item;
#endif

/****************************************************************************/
// avoid AmiagOS locale.h conflict

#ifndef LIBRARIES_LOCALE_H

#define DAY_1		1
#define DAY_2		2
#define DAY_3		3
#define DAY_4		4
#define DAY_5		5
#define DAY_6		6
#define DAY_7		7

#define ABDAY_1		8
#define ABDAY_2		9
#define ABDAY_3		10
#define ABDAY_4		11
#define ABDAY_5		12
#define ABDAY_6		13
#define ABDAY_7		14

#define MON_1		15
#define MON_2		16
#define MON_3		17
#define MON_4		18
#define MON_5		19
#define MON_6		20
#define MON_7		21
#define MON_8		22
#define MON_9		23
#define MON_10		24
#define MON_11		25
#define MON_12		26

#define ABMON_1		27
#define ABMON_2		28
#define ABMON_3		29
#define ABMON_4		30
#define ABMON_5		31
#define ABMON_6		32
#define ABMON_7		33
#define ABMON_8		34
#define ABMON_9		35
#define ABMON_10	36
#define ABMON_11	37
#define ABMON_12	38

#define AM_STR		41
#define PM_STR		42

#endif

/****************************************************************************/
// Following newlib/clib4

#define CODESET			1000
#define D_T_FMT			1001
#define D_FMT			1002
#define T_FMT			1003
#define T_FMT_AMPM		1004

#define ERA				1045
#define ERA_D_FMT		1046
#define ERA_D_T_FMT		1047
#define ERA_T_FMT		1048
#define ALT_DIGITS		1049

#define RADIXCHAR		1050
#define THOUSEP			1051

#define YESEXPR			1052
#define NOEXPR			1053

#define CRNCYSTR		1056

/****************************************************************************/

char *	nl_langinfo( nl_item );
char *	nl_langinfol( nl_item, locale_t );

/****************************************************************************/

AMY_EXTERN_C_END

#endif /* AMYSYS_LANGINFO_H */
