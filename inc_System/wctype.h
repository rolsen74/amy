
/*
** Based on The Open Group Base Specifications Issue 7
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

#include <locale.h>

#ifndef AMYSYS_WCTYPE_H
#define AMYSYS_WCTYPE_H

AMY_EXTERN_C_BEGIN

/****************************************************************************/

#ifndef WINT_T_DEFINED
#define WINT_T_DEFINED
typedef unsigned int	wint_t;
#endif

typedef unsigned int	wctype_t;
typedef unsigned int	wctrans_t;

/****************************************************************************/

int			iswalnum(		wint_t );
int			iswalnum_l(		wint_t, locale_t );
int			iswalpha(		wint_t );
int			iswalpha_l(		wint_t, locale_t );
int			iswblank(		wint_t );
int			iswblank_l(		wint_t, locale_t );
int			iswcntrl(		wint_t );
int			iswcntrl_l(		wint_t, locale_t );
int			iswctype(		wint_t, wctype_t );
int			iswctype_l(		wint_t, wctype_t, locale_t );
int			iswdigit(		wint_t );
int			iswdigit_l(		wint_t, locale_t );
int			iswgraph(		wint_t );
int			iswgraph_l(		wint_t, locale_t );
int			iswlower(		wint_t );
int			iswlower_l(		wint_t, locale_t );
int			iswprint(		wint_t );
int			iswprint_l(		wint_t, locale_t );
int			iswpunct(		wint_t );
int			iswpunct_l(		wint_t, locale_t );
int			iswspace(		wint_t );
int			iswspace_l(		wint_t, locale_t );
int			iswupper(		wint_t );
int			iswupper_l(		wint_t, locale_t );
int			iswxdigit(		wint_t );
int			iswxdigit_l(	wint_t, locale_t );
wint_t		towctrans(		wint_t, wctrans_t );
wint_t		towctrans_l(	wint_t, wctrans_t, locale_t );
wint_t		towlower(		wint_t );
wint_t		towlower_l(		wint_t, locale_t );
wint_t		towupper(		wint_t );
wint_t		towupper_l(		wint_t, locale_t );
wctrans_t	wctrans(		const char * );
wctrans_t	wctrans_l(		const char *, locale_t );
wctype_t	wctype(			const char * );
wctype_t	wctype_l(		const char *, locale_t );

/****************************************************************************/

AMY_EXTERN_C_END

#endif /* AMYSYS_WCTYPE_H */
