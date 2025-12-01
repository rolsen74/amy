
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

#ifndef AMYSYS_UNISTD_H
#define AMYSYS_UNISTD_H

/****************************************************************************/

#include <inttypes.h>
#include <sys/types.h>
#include <getopt.h>

/****************************************************************************/

#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void *)0)
#endif
#endif

/****************************************************************************/

#define _POSIX_VERSION		200112L
#define _POSIX2_VERSION		200112L
#define _XOPEN_VERSION		600

/****************************************************************************/

#define F_OK		0
#define X_OK		1
#define W_OK		2
#define R_OK		4

/****************************************************************************/

#define SEEK_SET	0
#define SEEK_CUR	1
#define SEEK_END	2

/****************************************************************************/

#define F_ULOCK		0
#define F_LOCK		1
#define F_TLOCK		2
#define F_TEST		3

/****************************************************************************/

#define STDIN_FILENO		0
#define STDOUT_FILENO		1
#define STDERR_FILENO		2

/****************************************************************************/

AMY_EXTERN_C_BEGIN

int			access( const char *, int );
unsigned	alarm( unsigned );
int			chdir( const char * );
int			chown( const char *, uid_t, gid_t );
int			close( int );
size_t		confstr( int, char *, size_t );
char *		crypt( const char *, const char * );
char *		ctermid( char * );
int			dup( int );
int			dup2( int, int );
void		encrypt( char[64], int );
int			execl( const char *, const char *, ... );
int			execle( const char *, const char *, ... );
int			execlp( const char *, const char *, ... );
int			execv( const char *, char * const [] );
int			execve( const char *, char * const [], char * const [] );
int			execvp( const char *, char * const [] );
void		_exit( int );
int			fchown( int, uid_t, gid_t );
int			fchdir( int );
int			fdatasync( int );
pid_t		fork( void );
long		fpathconf( int, int );
int			fsync( int );
int			ftruncate( int, off_t );
char *		getcwd( char *, size_t );
gid_t		getegid( void );
uid_t		geteuid( void );
gid_t		getgid( void );
int			getgroups( int, gid_t [] );
long		gethostid( void );
int			gethostname( char *, size_t );
char *		getlogin( void );
int			getlogin_r( char *, size_t );
int			getopt( int, char * const [], const char * );
int			getpagesize( void );
pid_t		getpgid( pid_t );
pid_t		getpgrp( void );
pid_t		getpid( void );
pid_t		getppid( void );
pid_t		getsid( pid_t );
uid_t		getuid( void );
char *		getwd( char * );
int			isatty( int );
int			lchown( const char *, uid_t, gid_t );
int			link( const char *, const char * );
int			lockf( int, int, off_t );
off_t		lseek( int, off_t, int );
int			nice( int );
long		pathconf( const char *, int );
int			pause( void );
int			pipe( int[2] );
ssize_t		pread( int, void *, size_t, off_t );
ssize_t		pwrite( int, const void *, size_t, off_t );
ssize_t		read( int, void *, size_t );
ssize_t		readlink( const char *, char *, size_t );
int			rmdir( const char * );
int			setegid( gid_t );
int			seteuid( uid_t );
int			setgid( gid_t );
int			setgroups( int ngroups, const gid_t *gidset );
int			setpgid( pid_t, pid_t );
pid_t		setpgrp( void );
int			setregid( gid_t, gid_t );
int			setreuid( uid_t, uid_t );
pid_t		setsid( void );
int			setuid( uid_t );
unsigned	sleep( unsigned );
void		swab( const void *, void *, ssize_t );
int			symlink( const char *, const char * );
void		sync( void );
long		sysconf( int );
pid_t		tcgetpgrp( int );
int			tcsetpgrp( int );
int			truncate( const char *, off_t );
char *		ttyname( int );
int			ttyname_r( int, char *, size_t );
useconds_t	ualarm( useconds_t, useconds_t );
int			unlink( const char * );
int			usleep( useconds_t );
pid_t		vfork( void );
ssize_t		write( int, const void *, size_t );

AMY_EXTERN_C_END

/****************************************************************************/

// moved to getopt.h
// char *optarg
// int optind
// int opterr
// int optopt

/****************************************************************************/

#endif
