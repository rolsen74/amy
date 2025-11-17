
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

#ifndef AMYSYS_STRING_H
#define AMYSYS_STRING_H

/****************************************************************************/

#include <stddef.h>
#include <locale.h>
#include <sys/types.h>		/* for mode_t */

/****************************************************************************/

AMY_EXTERN_C_BEGIN

int		ffsl( long int );
int		ffsll( long long int );
void *	memccpy( void *, const void *, int, size_t );
void *	memchr( const void *, int, size_t );
int		memcmp( const void *, const void *, size_t );
void *  memcpy( void *, const void *, size_t );
void *	memmove( void *, const void *, size_t );
void *  memset( void *, int, size_t );
char *	stpcpy( char *, const char * );
char *	stpncpy( char *, const char *, size_t );
char *	strcat( char *, const char * );
char *	strchr( const char *, int );
int		strcmp( const char *, const char * );
int		strcoll( const char *, const char * );
int		strcoll_l( const char *, const char *, locale_t );
char *	strcpy( char *, const char * );
size_t	strcspn( const char *, const char * );
char *	strdup( const char * );
char *	strerror( int );
char *  strerror_l( int, locale_t );
int		strerror_r( int, char *, size_t );
size_t	strlen( const char * );
char *	strncat( char *, const char *, size_t );
int		strncmp( const char *, const char *, size_t );
char *	strncpy( char *, const char *, size_t );
char *	strndup( const char *, size_t );
size_t	strnlen( const char *, size_t );
char *	strpbrk( const char *, const char * );
char *	strrchr( const char *, int );
char *	strsignal( int );
size_t	strspn( const char *, const char * );
char *	strstr( const char *, const char * );
char *	strtok( char *, const char * );
char *	strtok_r( char *, const char *, char ** );
size_t	strxfrm( char *, const char *, size_t );
size_t	strxfrm_l( char *, const char *, size_t, locale_t );
int		timingsafe_memcmp( const void *, const void *, size_t );

AMY_EXTERN_C_END

/****************************************************************************/
// BSD

AMY_EXTERN_C_BEGIN

char *	strsep( char **, const char * );
size_t	strlcpy( char *, const char *, size_t );
size_t	strlcat( char *, const char *, size_t );
void	strmode( mode_t mode, char *p );
void *	memmem( const void *, size_t, const void *, size_t );

AMY_EXTERN_C_END

/****************************************************************************/

#endif

