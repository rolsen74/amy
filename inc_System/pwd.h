
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

#ifndef AMYSYS_PWD_H
#define AMYSYS_PWD_H

/****************************************************************************/

#include <sys/types.h>

/****************************************************************************/

struct passwd
{
	char *	pw_name;
	char *	pw_passwd;
	uid_t	pw_uid;
	gid_t	pw_gid;
	char *	pw_gecos;
	char *	pw_dir;
	char *	pw_shell;
};

/****************************************************************************/

AMY_EXTERN_C_BEGIN

struct passwd *	getpwnam( const char * );
struct passwd *	getpwuid( uid_t );
int				getpwnam_r( const char *, struct passwd *, char *, size_t, struct passwd ** );
int				getpwuid_r( uid_t, struct passwd *, char *, size_t, struct passwd ** );
void			endpwent( void );
struct passwd *	getpwent( void );
void			setpwent( void );

AMY_EXTERN_C_END

/****************************************************************************/

#endif
