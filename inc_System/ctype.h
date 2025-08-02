
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

#include <Amy_Defines.h>	// Need AMYFUNC
#include <locale.h>

/****************************************************************************/

AMY_EXTERN_C_BEGIN

int		AMYFUNC isalnum( int );
int		AMYFUNC isalnum_l( int, locale_t );
int		AMYFUNC isalpha( int );
int		AMYFUNC isalpha_l( int, locale_t );
int		AMYFUNC isascii( int );
int		AMYFUNC isblank( int );
int		AMYFUNC isblank_l( int, locale_t );
int		AMYFUNC iscntrl( int );
int		AMYFUNC iscntrl_l( int, locale_t );
int		AMYFUNC isdigit( int );
int		AMYFUNC isdigit_l( int, locale_t );
int		AMYFUNC isgraph( int );
int		AMYFUNC isgraph_l( int, locale_t );
int		AMYFUNC islower( int );
int		AMYFUNC islower_l( int, locale_t );
int		AMYFUNC isprint( int );
int		AMYFUNC isprint_l( int, locale_t );
int		AMYFUNC ispunct( int );
int		AMYFUNC ispunct_l( int, locale_t );
int		AMYFUNC isspace( int );
int		AMYFUNC isspace_l( int, locale_t );
int		AMYFUNC isupper( int );
int		AMYFUNC isupper_l( int, locale_t );
int		AMYFUNC isxdigit( int );
int		AMYFUNC isxdigit_l( int, locale_t );
int		AMYFUNC toascii( int );
int		AMYFUNC tolower( int );
int		AMYFUNC tolower_l( int, locale_t );
int		AMYFUNC toupper( int );
int		AMYFUNC toupper_l( int, locale_t );

AMY_EXTERN_C_END

/****************************************************************************/

AMY_EXTERN_C_BEGIN

int		AMYFUNC _toupper( int );
int		AMYFUNC _tolower( int );

AMY_EXTERN_C_END

/****************************************************************************/

#endif
