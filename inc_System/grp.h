
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

#ifndef AMYSYS_GRP_H
#define AMYSYS_GRP_H

/****************************************************************************/

#include <Amy_Defines.h>	// Need AMY_EXTERN_C_BEGIN
#include <sys/types.h>

/****************************************************************************/

struct group
{
	char *	gr_name;
	gid_t	gr_gid;
	char **	gr_mem;
};

/****************************************************************************/

AMY_EXTERN_C_BEGIN

void			endgrent( void );
struct group *	getgrent( void );
struct group *	getgrgid( gid_t );
int				getgrgid_r(  gid_t, struct group *, char *, size_t, struct group ** );
struct group *	getgrnam( const char * );
int				getgrnam_r( const char *, struct group *, char *, size_t, struct group ** );
void			setgrent( void );

AMY_EXTERN_C_END

/****************************************************************************/

#endif
