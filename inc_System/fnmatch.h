
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

#ifndef AMYSYS_FNMATCH_H
#define AMYSYS_FNMATCH_H

/****************************************************************************/

#include <Amy_Defines.h>	// Need AMY_EXTERN_C_BEGIN

/****************************************************************************/

#define FNM_NOMATCH			1

#define FNM_NOESCAPE		0x01
#define FNM_PATHNAME		0x02
#define FNM_PERIOD			0x04
#define FNM_LEADING_DIR		0x08
#define FNM_CASEFOLD		0x10

/****************************************************************************/

AMY_EXTERN_C_BEGIN

int	fnmatch( const char *, const char *, int );

AMY_EXTERN_C_END

/****************************************************************************/

#endif

