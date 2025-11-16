
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

#ifndef AMYSYS_LOCALE_H
#define AMYSYS_LOCALE_H

/****************************************************************************/

#include <stddef.h>

/****************************************************************************/

#define LC_ALL			0
#define LC_COLLATE		1
#define LC_CTYPE		2
#define LC_MONETARY		3
#define LC_NUMERIC		4
#define LC_TIME			5
#define LC_MESSAGES		6

#define _LC_LAST		( LC_MESSAGES + 1 )

#define LC_COLLATE_MASK			( 1UL << 0 )
#define LC_CTYPE_MASK			( 1UL << 1 )
#define LC_MONETARY_MASK		( 1UL << 2 )
#define LC_NUMERIC_MASK			( 1UL << 3 )
#define LC_TIME_MASK			( 1UL << 4 )
#define LC_MESSAGES_MASK		( 1UL << 5 )

#define LC_ALL_MASK				( LC_COLLATE_MASK \
								| LC_CTYPE_MASK \
								| LC_MONETARY_MASK \
								| LC_NUMERIC_MASK \
								| LC_TIME_MASK \
								| LC_MESSAGES_MASK )

#define _LC_LAST_MASK			( 1UL << ( 6 - 1 ))

#define LC_GLOBAL_LOCALE		(( locale_t ) -1 )

/****************************************************************************/

typedef void * locale_t;

/****************************************************************************/

struct lconv
{
	char *	decimal_point;
	char *	thousands_sep;
	char *	grouping;
	char *	int_curr_symbol;
	char *	currency_symbol;
	char *	mon_decimal_point;
	char *	mon_thousands_sep;
	char *	mon_grouping;
	char *	positive_sign;
	char *	negative_sign;
	char	int_frac_digits;
	char	frac_digits;
	char	p_cs_precedes;
	char	p_sep_by_space;
	char	n_cs_precedes;
	char	n_sep_by_space;
	char	p_sign_posn;
	char	n_sign_posn;
	char	int_p_cs_precedes;
	char	int_n_cs_precedes;
	char	int_p_sep_by_space;
	char	int_n_sep_by_space;
	char	int_p_sign_posn;
	char	int_n_sign_posn;
};

/****************************************************************************/

AMY_EXTERN_C_BEGIN

locale_t		duplocale( locale_t );
void			freelocale( locale_t );
struct lconv *	localeconv( void );
locale_t		newlocale( int, const char *, locale_t );
char *			setlocale( int, const char * );
locale_t		uselocale( locale_t );

AMY_EXTERN_C_END

/****************************************************************************/

#endif

