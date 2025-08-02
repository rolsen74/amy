
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

#ifndef AMYSYS_STRINGS_H
#define AMYSYS_STRINGS_H

/****************************************************************************/

#include <Amy_Defines.h>	// Need AMYFUNC
#include <stddef.h>

/****************************************************************************/

AMY_EXTERN_C_BEGIN

int		AMYFUNC bcmp( const void *, const void *, size_t );
void	AMYFUNC bcopy( const void *, void *, size_t );
void	AMYFUNC bzero( void *, size_t );
void	AMYFUNC explicit_bzero( void *, size_t );
int		AMYFUNC ffs( int );
char *	AMYFUNC index( const char *, int );
char *	AMYFUNC rindex( const char *, int );
int		AMYFUNC strcasecmp( const char *, const char *);
int		AMYFUNC strncasecmp( const char *, const char *, size_t );
int		AMYFUNC timingsafe_bcmp( const void *, const void *, size_t );

AMY_EXTERN_C_END

/****************************************************************************/

#ifndef strcmpi
#define strcmpi strcasecmp
#endif

#ifndef stricmp
#define stricmp strcasecmp
#endif

#ifndef strncmpi
#define strncmpi strncasecmp
#endif

#ifndef strnicmp
#define strnicmp strncasecmp
#endif

/****************************************************************************/

#endif

