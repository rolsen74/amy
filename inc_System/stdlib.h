
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

#ifndef AMYSYS_STDLIB_H
#define AMYSYS_STDLIB_H

/****************************************************************************/

#include <Amy_Defines.h>	// Need AMYFUNC
#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>

/****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************/

#define EXIT_FAILURE	20
#define EXIT_SUCCESS	0

#define RAND_MAX		2147483647

#define MB_CUR_MAX		4

/****************************************************************************/

typedef struct
{
	int quot;
	int rem;

} div_t;

typedef struct
{
	long quot;
	long rem;

} ldiv_t;

typedef struct
{
	long long quot;
	long long rem;

} lldiv_t;

/****************************************************************************/

void		AMYFUNC _Exit( int );
long		AMYFUNC a641( const char * );
void		AMYFUNC abort( void );
int			AMYFUNC abs( int );
uint32_t	AMYFUNC arc4random( void );
void		AMYFUNC arc4random_addrandom( unsigned char *, int );
void		AMYFUNC arc4random_buf( void *, size_t );
uint32_t	AMYFUNC arc4random_uniform( uint32_t );
void		AMYFUNC arc4random_stir( void );
int			AMYFUNC atexit( void (*)(void) );
double		AMYFUNC atof( const char * );
int			AMYFUNC atoi( const char * );
long		AMYFUNC atol( const char * );
long long	AMYFUNC atoll( const char * );
void *		AMYFUNC bsearch( const void *, const void *, size_t, size_t, int (*)( const void *, const void * ));
void *		AMYFUNC calloc( size_t, size_t );
div_t		AMYFUNC div( int, int );
double		AMYFUNC drand48( void );
double		AMYFUNC erand48( unsigned short[3] );
void		AMYFUNC exit( int );
void		AMYFUNC free( void * );
char *		AMYFUNC getenv( const char * );
int			AMYFUNC getsubopt( char **, char *const *, char ** );
int			AMYFUNC grantpt( int );
char *		AMYFUNC initstate( unsigned int, char *, size_t );
long		AMYFUNC jrand48( unsigned short[3] );
char *		AMYFUNC l64a( long );
long		AMYFUNC labs( long );
void		AMYFUNC lcong48( unsigned short[7] );
ldiv_t		AMYFUNC ldiv( long, long );
long long	AMYFUNC llabs( long long );
lldiv_t		AMYFUNC lldiv( long long, long long );
long		AMYFUNC lrand48( void );
void *		AMYFUNC malloc( size_t );
int			AMYFUNC mblen( const char *, size_t );
size_t		AMYFUNC mbstowcs( wchar_t *, const char *, size_t );
int			AMYFUNC mbtowc( wchar_t *, const char *, size_t );
char *		AMYFUNC mkdtemp( char * );
int			AMYFUNC mkstemp( char * );
long		AMYFUNC mrand48( void );
long		AMYFUNC nrand48( unsigned short[3] );
int			AMYFUNC posix_memalign( void **, size_t, size_t );
int			AMYFUNC posix_openpt( int );
char *		AMYFUNC ptsname( int );
int			AMYFUNC putenv( char * );
void		AMYFUNC qsort( void *, size_t, size_t, int (*)( const void *, const void * ));
int			AMYFUNC rand( void );
int			AMYFUNC rand_r( unsigned * );
long		AMYFUNC random( void );
void *		AMYFUNC realloc( void *, size_t );
char *		AMYFUNC realpath( const char *, char * );
unsigned short * AMYFUNC seed48( unsigned short[3] );
int			AMYFUNC setenv( const char *, const char *, int );
void		AMYFUNC setkey( const char * );
char *		AMYFUNC setstate( const char * );
void		AMYFUNC srand( unsigned );
void		AMYFUNC srand48( long );
void		AMYFUNC srandom( unsigned );
double		AMYFUNC strtod( const char *, char ** );
float		AMYFUNC strtof( const char *, char ** );
long		AMYFUNC strtol( const char *, char **, int );
long double	AMYFUNC strtold( const char *, char ** );
long long	AMYFUNC strtoll( const char *, char **, int );
unsigned long AMYFUNC strtoul( const char *, char **, int );
unsigned long long AMYFUNC strtoull( const char *, char **, int );
int			AMYFUNC system( const char * );
int			AMYFUNC unlockpt( int );
int			AMYFUNC unsetenv( const char * );
size_t		AMYFUNC wcstombs( char *, const wchar_t *, size_t );
int			AMYFUNC wctomb( char *, wchar_t );

/****************************************************************************/
// BSD

const char *	AMYFUNC getprogname( void );
void			AMYFUNC setprogname( const char * );
void			AMYFUNC freezero( void *, size_t );
void *			AMYFUNC reallocarray( void *, size_t, size_t );
void *			AMYFUNC recallocarray( void *, size_t, size_t, size_t );
quad_t			AMYFUNC strtoq( const char *, char **, int );

/****************************************************************************/

#ifdef __cplusplus
}
#endif

/****************************************************************************/

#endif

