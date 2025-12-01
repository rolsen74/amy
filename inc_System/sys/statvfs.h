
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

#ifndef AMYSYS_SYS_STATVFS_H
#define AMYSYS_SYS_STATVFS_H

/****************************************************************************/

#include <sys/types.h>

/****************************************************************************/

#define ST_RDONLY			1
#define ST_NOSUID			2

struct statvfs
{
	unsigned long	f_bsize;
	unsigned long	f_frsize;
	fsblkcnt_t		f_blocks;
	fsblkcnt_t		f_bfree;
	fsblkcnt_t		f_bavail;
	fsfilcnt_t		f_files;
	fsfilcnt_t		f_ffree;
	fsfilcnt_t		f_favail;
	unsigned long	f_fsid;
	unsigned long	f_flag;
	unsigned long	f_namemax;
};

/****************************************************************************/

AMY_EXTERN_C_BEGIN

int		statvfs( const char *, struct statvfs * );
int		fstatvfs( int, struct statvfs * );

AMY_EXTERN_C_END

/****************************************************************************/

#endif
