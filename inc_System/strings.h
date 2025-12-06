
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

#ifndef AMYSYS_STRINGS_H
#define AMYSYS_STRINGS_H

#include <stddef.h>
#include <string.h>

AMY_EXTERN_C_BEGIN

/****************************************************************************/

int		bcmp( const void *, const void *, size_t );
void	bcopy( const void *, void *, size_t );
void	bzero( void *, size_t );
void	explicit_bzero( void *, size_t );
int		ffs( int );
char *	index( const char *, int );
char *	rindex( const char *, int );
int		strcasecmp( const char *, const char *);
int		strncasecmp( const char *, const char *, size_t );
int		timingsafe_bcmp( const void *, const void *, size_t );

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

AMY_EXTERN_C_END

#endif /* AMYSYS_STRINGS_H */
