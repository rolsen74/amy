
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

#ifndef AMYSYS_ICONV_H
#define AMYSYS_ICONV_H

/****************************************************************************/

#include <Amy_Defines.h>	// Need AMYFUNC
#include <sys/types.h>

/****************************************************************************/

typedef void *	iconv_t;

/****************************************************************************/

AMY_EXTERN_C_BEGIN

size_t	AMYFUNC iconv( iconv_t, char **, size_t *, char **, size_t * );
int		AMYFUNC iconv_close( iconv_t );
iconv_t	AMYFUNC iconv_open( const char *, const char * );

AMY_EXTERN_C_END

/****************************************************************************/

#endif

