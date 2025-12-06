
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

#ifndef AMYSYS_FNMATCH_H
#define AMYSYS_FNMATCH_H

AMY_EXTERN_C_BEGIN

/****************************************************************************/

#define FNM_NOMATCH			1

#define FNM_NOESCAPE		0x01
#define FNM_PATHNAME		0x02
#define FNM_PERIOD			0x04
#define FNM_LEADING_DIR		0x08
#define FNM_CASEFOLD		0x10

/****************************************************************************/

int	fnmatch( const char *, const char *, int );

/****************************************************************************/

AMY_EXTERN_C_END

#endif /* AMYSYS_FNMATCH_H */
