
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

#ifndef AMYSYS_DIRENT_H
#define AMYSYS_DIRENT_H

/****************************************************************************/

#include <sys/types.h>

/****************************************************************************/

typedef struct _DIR DIR;

/****************************************************************************/

struct dirent
{
	ino_t	d_ino;
	char	d_name[256];
};

/****************************************************************************/

AMY_EXTERN_C_BEGIN

int				alphasort( const struct dirent **, const struct dirent ** );
int				closedir( DIR * );
int				dirfd( DIR * );
DIR *			fdopendir( int fildes );
DIR *			opendir( const char * );
struct dirent *	readdir( DIR * );
int				readdir_r( DIR *, struct dirent *, struct dirent ** );
void			rewinddir( DIR * );
int				scandir( const char *, struct dirent ***, int (*)( const struct dirent *), int (*)(const struct dirent **, const struct dirent **));
void			seekdir( DIR *, long );
long			telldir( DIR * );

AMY_EXTERN_C_END

/****************************************************************************/

#endif

