
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

#include <Amy_Defines.h>	// Need AMYFUNC
#include <stdarg.h>

/****************************************************************************/
// BSD-specific error reporting functions

AMY_EXTERN_C_BEGIN

void		AMYFUNC err(	int, const char *, ... );
void		AMYFUNC verr(	int, const char *, va_list );
void		AMYFUNC errc(	int, int, const char *, ... );
void		AMYFUNC verrc(	int, int, const char *, va_list );
void		AMYFUNC errx(	int, const char *, ... );
void		AMYFUNC verrx(	int, const char *, va_list );
void		AMYFUNC warn(	const char *, ... );
void		AMYFUNC vwarn(	const char *, va_list );
void		AMYFUNC warnc(	int, const char *, ... );
void		AMYFUNC vwarnc(	int, const char *, va_list );
void		AMYFUNC warnx(	const char *, ... );
void		AMYFUNC vwarnx(	const char *, va_list );

AMY_EXTERN_C_END

/****************************************************************************/

#endif

