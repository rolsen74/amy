
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

/* -- */

#ifndef AMYSYS_FTW_H
#define AMYSYS_FTW_H

/****************************************************************************/

#include <sys/types.h>
#include <sys/stat.h>

/****************************************************************************/

#define FTW_F			0	// File
#define FTW_D			1	// Directory
#define FTW_DNR			2	// Directory not readable
#define FTW_DP			3	// Directory post-order
#define FTW_NS			4	// stat failed
#define FTW_SL			5	// Symbolic link
#define FTW_SLN			6	// Symlink with nonexistent target

#define FTW_PHYS		( 1UL << 0 )
#define FTW_MOUNT		( 1UL << 1 )
#define FTW_DEPTH		( 1UL << 2 )
#define FTW_CHDIR		( 1UL << 3 )
#define FTW_ALL_FLAGS	( 0x000f )

struct FTW
{
	int		base;
	int		level;
};

/****************************************************************************/

AMY_EXTERN_C_BEGIN

int	ftw( const char *, int (*)(const char *, const struct stat *, int), int );
int	nftw( const char *, int (*)(const char *, const struct stat *, int, struct FTW *), int, int );

AMY_EXTERN_C_END

/****************************************************************************/

#endif
