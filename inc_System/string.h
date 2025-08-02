
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

#ifndef AMYSYS_STRING_H
#define AMYSYS_STRING_H

/****************************************************************************/

#include <Amy_Defines.h>	// Need AMYFUNC
#include <stddef.h>
#include <locale.h>
#include <sys/types.h>		// for mode_t

/****************************************************************************/

AMY_EXTERN_C_BEGIN

int		AMYFUNC ffsl( long int );
int		AMYFUNC ffsll( long long int );
void *	AMYFUNC memccpy( void *, const void *, int, size_t );
void *	AMYFUNC memchr( const void *, int, size_t );
int		AMYFUNC memcmp( const void *, const void *, size_t );
void *  AMYFUNC memcpy( void *, const void *, size_t );
void *	AMYFUNC memmove( void *, const void *, size_t );
void *  AMYFUNC memset( void *, int, size_t );
char *	AMYFUNC stpcpy( char *, const char * );
char *	AMYFUNC stpncpy( char *, const char *, size_t );
char *	AMYFUNC strcat( char *, const char * );
char *	AMYFUNC strchr( const char *, int );
int		AMYFUNC strcmp( const char *, const char * );
int		AMYFUNC strcoll( const char *, const char * );
int		AMYFUNC strcoll_l( const char *, const char *, locale_t );
char *	AMYFUNC strcpy( char *, const char * );
size_t	AMYFUNC strcspn( const char *, const char * );
char *	AMYFUNC strdup( const char * );
char *	AMYFUNC strerror( int );
char *  AMYFUNC strerror_l( int, locale_t );
int		AMYFUNC strerror_r( int, char *, size_t );
size_t	AMYFUNC strlen( const char * );
char *	AMYFUNC strncat( char *, const char *, size_t );
int		AMYFUNC strncmp( const char *, const char *, size_t );
char *	AMYFUNC strncpy( char *, const char *, size_t );
char *	AMYFUNC strndup( const char *, size_t );
size_t	AMYFUNC strnlen( const char *, size_t );
char *	AMYFUNC strpbrk( const char *, const char * );
char *	AMYFUNC strrchr( const char *, int );
char *	AMYFUNC strsignal( int );
size_t	AMYFUNC strspn( const char *, const char * );
char *	AMYFUNC strstr( const char *, const char * );
char *	AMYFUNC strtok( char *, const char * );
char *	AMYFUNC strtok_r( char *, const char *, char ** );
size_t	AMYFUNC strxfrm( char *, const char *, size_t );
size_t	AMYFUNC strxfrm_l( char *, const char *, size_t, locale_t );
int		AMYFUNC timingsafe_memcmp( const void *, const void *, size_t );

AMY_EXTERN_C_END

/****************************************************************************/
// BSD

AMY_EXTERN_C_BEGIN

char *	AMYFUNC strsep( char **, const char * );
size_t	AMYFUNC strlcpy( char *, const char *, size_t );
size_t	AMYFUNC strlcat( char *, const char *, size_t );
void	AMYFUNC strmode( mode_t mode, char *p );
void *	AMYFUNC memmem( const void *, size_t, const void *, size_t );

AMY_EXTERN_C_END

/****************************************************************************/

#endif

