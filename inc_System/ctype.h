
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

#ifndef AMYSYS_CTYPE_H
#define AMYSYS_CTYPE_H

/****************************************************************************/

#include <Amy_Defines.h>	// Need AMY_EXTERN_C_BEGIN
#include <locale.h>

/****************************************************************************/

AMY_EXTERN_C_BEGIN

int		isalnum( int );
int		isalnum_l( int, locale_t );
int		isalpha( int );
int		isalpha_l( int, locale_t );
int		isascii( int );
int		isblank( int );
int		isblank_l( int, locale_t );
int		iscntrl( int );
int		iscntrl_l( int, locale_t );
int		isdigit( int );
int		isdigit_l( int, locale_t );
int		isgraph( int );
int		isgraph_l( int, locale_t );
int		islower( int );
int		islower_l( int, locale_t );
int		isprint( int );
int		isprint_l( int, locale_t );
int		ispunct( int );
int		ispunct_l( int, locale_t );
int		isspace( int );
int		isspace_l( int, locale_t );
int		isupper( int );
int		isupper_l( int, locale_t );
int		isxdigit( int );
int		isxdigit_l( int, locale_t );
int		toascii( int );
int		tolower( int );
int		tolower_l( int, locale_t );
int		toupper( int );
int		toupper_l( int, locale_t );

AMY_EXTERN_C_END

/****************************************************************************/

AMY_EXTERN_C_BEGIN

int		_toupper( int );
int		_tolower( int );

AMY_EXTERN_C_END

/****************************************************************************/

#endif
