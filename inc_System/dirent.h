
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

#ifndef AMYSYS_DIRENT_H
#define AMYSYS_DIRENT_H

/****************************************************************************/

#include <Amy_Defines.h>	// Need AMYFUNC
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

int				AMYFUNC alphasort( const struct dirent **, const struct dirent ** );
int				AMYFUNC closedir( DIR * );
int				AMYFUNC dirfd( DIR * );
DIR *			AMYFUNC fdopendir( int fildes );
DIR *			AMYFUNC opendir( const char * );
struct dirent *	AMYFUNC readdir( DIR * );
int				AMYFUNC readdir_r( DIR *, struct dirent *, struct dirent ** );
void			AMYFUNC rewinddir( DIR * );
int				AMYFUNC scandir( const char *, struct dirent ***, int (*)( const struct dirent *), int (*)(const struct dirent **, const struct dirent **));
void			AMYFUNC seekdir( DIR *, long );
long			AMYFUNC telldir( DIR * );

AMY_EXTERN_C_END

/****************************************************************************/

#endif

