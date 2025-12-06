
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

#ifndef AMYSYS_ICONV_H
#define AMYSYS_ICONV_H

#include <sys/types.h>

AMY_EXTERN_C_BEGIN

/****************************************************************************/

typedef void *	iconv_t;

/****************************************************************************/

size_t	iconv( iconv_t, char **, size_t *, char **, size_t * );
int		iconv_close( iconv_t );
iconv_t	iconv_open( const char *, const char * );

/****************************************************************************/

AMY_EXTERN_C_END

#endif /* AMYSYS_ICONV_H */
