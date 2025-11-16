
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

#ifndef AMYSYS_SYS_STAT_H
#define AMYSYS_SYS_STAT_H

/****************************************************************************/

#include <time.h>

/****************************************************************************/

struct stat
{
	dev_t			st_dev;		// Device ID
	ino_t			st_ino;		// File serial number
	mode_t			st_mode;	// Mode of file
	nlink_t			st_nlink;	// Number of hard links to the file
	uid_t			st_uid;		// User ID of file
	gid_t			st_gid;		// Group ID of file
	dev_t			st_rdev;	// Device ID (if file is character or block special)
	off_t			st_size;	// File size
	time_t			st_atime;	// Last data access timestamp
	time_t			st_mtime;	// Last data modification timestamp
	time_t			st_ctime;	// Last file status change timestamp
	blksize_t		st_blksize;	// I/O block size
	blkcnt_t		st_blocks;	// Number of blocks allocated
};

/****************************************************************************/

#define S_IXOTH		01
#define S_IWOTH		02
#define S_IROTH		04
#define S_IRWXO		07

#define S_IXGRP		010
#define S_IWGRP		020
#define S_IRGRP		040
#define S_IRWXG		070

#define S_IXUSR		0100
#define S_IWUSR		0200
#define S_IRUSR		0400
#define S_IRWXU		0700

#define S_ISVTX		01000
#define S_ISGID		02000
#define S_ISUID		04000

#define S_IFIFO		010000
#define S_IFCHR		020000
#define S_IFDIR		040000
#define S_IFNAM		050000
#define S_IFBLK		060000

#define S_IFREG		0100000
#define S_IFLNK		0120000
#define S_IFSOCK	0140000
#define S_IFMT		0170000

#define S_IEXEC		S_IXUSR
#define S_IREAD		S_IRUSR
#define S_IWRITE	S_IWUSR

#define	S_ISBLK(m)	(0)
#define	S_ISCHR(m)	(((m) & S_IFMT) == S_IFCHR)
#define	S_ISDIR(m)	(((m) & S_IFMT) == S_IFDIR)
#define	S_ISFIFO(m)	(((m) & S_IFMT) == S_IFIFO)
#define	S_ISREG(m)	(((m) & S_IFMT) == S_IFREG)
#define	S_ISLNK(m)	(((m) & S_IFMT) == S_IFLNK)
#define S_ISSOCK(m)	(((m) & S_IFMT) == S_IFSOCK)

/****************************************************************************/

AMY_EXTERN_C_BEGIN

int		chmod( const char *, mode_t );
int		fchmod( int, mode_t );
int		fchmodat( int, const char *, mode_t, int );
int		fstat( int, struct stat * );
int		fstatat( int, const char *, struct stat *, int );
int		futimens( int, const struct timespec [2] );
int		lstat( const char *, struct stat * );
int		mkdir( const char *, mode_t );
int		mkdirat( int, const char *, mode_t );
int		mkfifo( const char *, mode_t );
int		mkfifoat( int, const char *, mode_t );
int		mknod( const char *, mode_t, dev_t );
int		mknodat( int, const char *, mode_t, dev_t );
int		stat( const char *, struct stat * );
mode_t	umask( mode_t );
int		utimensat( int, const char *, const struct timespec [2], int );

AMY_EXTERN_C_END

/****************************************************************************/

#endif
