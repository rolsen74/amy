
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
**
******************************************************************************
** This file is part of Amy C Lib
*/

#ifndef AMYSYS_ERR_H
#define AMYSYS_ERR_H

/****************************************************************************/

#include <Amy_Defines.h>	// Need AMY_EXTERN_C_BEGIN
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

