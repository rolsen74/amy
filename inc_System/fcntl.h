
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

#ifndef AMYSYS_FCNTL_H
#define AMYSYS_FCNTL_H

#include <sys/types.h>

AMY_EXTERN_C_BEGIN

/****************************************************************************/

#define F_DUPFD			0
#define F_GETFD			1
#define F_SETFD			2
#define F_GETFL			3
#define F_SETFL			4
#define F_GETOWN		5
#define F_SETOWN		6
#define F_GETLK			7
#define F_SETLK			8
#define F_SETLKW		9

/****************************************************************************/

#define F_RDLCK			0
#define F_WRLCK			1
#define F_UNLCK			2

/****************************************************************************/

#define FD_CLOEXEC		1

/****************************************************************************/

#define O_EXEC			1
#define O_RDONLY		2
#define O_RDWR			3
#define O_SEARCH		4
#define O_WRONLY		5

#define O_ACCMODE		0x07

/****************************************************************************/

#define O_CLOEXEC		( 1UL << 4 )
#define O_CREAT			( 1UL << 5 )
#define O_DIRECTORY		( 1UL << 6 )
#define O_EXCL			( 1UL << 7 )
#define O_NOCTTY		( 1UL << 8 )
#define O_NOFOLLOW		( 1UL << 9 )
#define O_TRUNC			( 1UL << 10 )
#define O_TTY_INIT		( 1UL << 11 )
#define O_APPEND		( 1UL << 12 )
#define O_DSYNC			( 1UL << 13 )
#define O_NONBLOCK		( 1UL << 14 )
#define O_RSYNC			( 1UL << 15 )
#define O_SYNC			( 1UL << 16 )

/****************************************************************************/

#define AT_FDCWD				-100
#define AT_SYMLINK_NOFOLLOW		0x100
#define AT_REMOVEDIR			0x200
#define AT_SYMLINK_FOLLOW		0x400
#define AT_EACCESS				0x800

/****************************************************************************/

struct flock
{
	short	l_type;
	short	l_whence;
	off_t	l_start;
	off_t	l_len;
	pid_t	l_pid;
};

/****************************************************************************/

int	creat( const char *, mode_t );
int	fcntl( int, int, ... );
int	open( const char *, int, ... );
int	openat( int, const char *, int, ... );
int	posix_fadvice( int, off_t, off_t, int );
int	posix_fallocate( int, off_t, off_t );

/****************************************************************************/

AMY_EXTERN_C_END

#endif /* AMYSYS_FCNTL_H */
