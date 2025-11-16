
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

#ifndef AMYSYS_ERR_H
#define AMYSYS_ERR_H

/****************************************************************************/

#include <stdarg.h>

/****************************************************************************/
// BSD-specific error reporting functions

AMY_EXTERN_C_BEGIN

void		err(	int, const char *, ... );
void		verr(	int, const char *, va_list );
void		errc(	int, int, const char *, ... );
void		verrc(	int, int, const char *, va_list );
void		errx(	int, const char *, ... );
void		verrx(	int, const char *, va_list );
void		warn(	const char *, ... );
void		vwarn(	const char *, va_list );
void		warnc(	int, const char *, ... );
void		vwarnc(	int, const char *, va_list );
void		warnx(	const char *, ... );
void		vwarnx(	const char *, va_list );

AMY_EXTERN_C_END

/****************************************************************************/

#endif

