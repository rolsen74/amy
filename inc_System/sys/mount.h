
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

#ifndef AMYSYS_SYS_MOUNT_H
#define AMYSYS_SYS_MOUNT_H

/****************************************************************************/

#include <sys/types.h>

/****************************************************************************/

#define MNT_RDONLY			1
#define MNT_NOSUID			2
#define MNT_NODEV			4
#define MNT_NOEXEC			8
#define MNT_SYNCHRONOUS		16
#define MNT_NOATIME			32
#define MNT_NODIRATIME		64
#define MNT_RELATIME		128

struct statfs
{
	uint32_t	f_version;
	uint32_t	f_type;
	uint64_t	f_flags;
	uint64_t	f_bsize;
	uint64_t	f_iosize;
	uint64_t	f_blocks;
	uint64_t	f_bfree;
	uint64_t	f_bavail;
	uint64_t	f_files;
	uint64_t	f_ffree;
	uint64_t	f_fsid[2];
	uint64_t	f_namemax;
	char		f_fstypename[32];
};

/****************************************************************************/

AMY_EXTERN_C_BEGIN

int		statfs( const char *, struct statfs * );
int		fstatfs( int, struct statfs * );

AMY_EXTERN_C_END

/****************************************************************************/

#endif
