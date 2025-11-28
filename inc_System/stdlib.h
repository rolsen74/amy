
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

#include <Amy_Defines.h>	// Need AMY_EXTERN_C_BEGIN
#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>

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

AMY_EXTERN_C_BEGIN

void		_Exit( int );
long		a641( const char * );
void		abort( void );
int			abs( int );
int			atexit( void (*)(void) );
double		atof( const char * );
int			atoi( const char * );
long		atol( const char * );
long long	atoll( const char * );
void *		bsearch( const void *, const void *, size_t, size_t, int (*)( const void *, const void * ));
void *		calloc( size_t, size_t );
div_t		div( int, int );
double		drand48( void );
double		erand48( unsigned short[3] );
void		exit( int );
void		free( void * );
char *		getenv( const char * );
int			getsubopt( char **, char *const *, char ** );
int			grantpt( int );
char *		initstate( unsigned int, char *, size_t );
long		jrand48( unsigned short[3] );
char *		l64a( long );
long		labs( long );
void		lcong48( unsigned short[7] );
ldiv_t		ldiv( long, long );
long long	llabs( long long );
lldiv_t		lldiv( long long, long long );
long		lrand48( void );
void *		malloc( size_t );
int			mblen( const char *, size_t );
size_t		mbstowcs( wchar_t *, const char *, size_t );
int			mbtowc( wchar_t *, const char *, size_t );
char *		mkdtemp( char * );
int			mkstemp( char * );
long		mrand48( void );
long		nrand48( unsigned short[3] );
int			posix_memalign( void **, size_t, size_t );
int			posix_openpt( int );
char *		ptsname( int );
int			putenv( char * );
void		qsort( void *, size_t, size_t, int (*)( const void *, const void * ));
int			rand( void );
int			rand_r( unsigned * );
long		random( void );
void *		realloc( void *, size_t );
char *		realpath( const char *, char * );
unsigned short * seed48( unsigned short[3] );
int			setenv( const char *, const char *, int );
void		setkey( const char * );
char *		setstate( const char * );
void		srand( unsigned );
void		srand48( long );
void		srandom( unsigned );
double		strtod( const char *, char ** );
float		strtof( const char *, char ** );
long		strtol( const char *, char **, int );
long double	strtold( const char *, char ** );
long long	strtoll( const char *, char **, int );
unsigned long strtoul( const char *, char **, int );
unsigned long long strtoull( const char *, char **, int );
int			system( const char * );
int			unlockpt( int );
int			unsetenv( const char * );
size_t		wcstombs( char *, const wchar_t *, size_t );
int			wctomb( char *, wchar_t );

AMY_EXTERN_C_END

/****************************************************************************/
// Legacy

AMY_EXTERN_C_BEGIN

char *			ecvt( double, int, int *restrict, int * );
char *			fcvt( double, int, int *restrict, int * );
char *			gcvt( double, int, char * );
char *			mktemp( char * );

AMY_EXTERN_C_END

/****************************************************************************/
// BSD

AMY_EXTERN_C_BEGIN

uint32_t		arc4random( void );
void			arc4random_addrandom( unsigned char *, int );
void			arc4random_buf( void *, size_t );
uint32_t		arc4random_uniform( uint32_t );
void			arc4random_stir( void );

const char *	getprogname( void );
void			setprogname( const char * );
void			freezero( void *, size_t );
void *			reallocarray( void *, size_t, size_t );
void *			recallocarray( void *, size_t, size_t, size_t );
quad_t			strtoq( const char *, char **, int );

AMY_EXTERN_C_END

/****************************************************************************/
// GNU

AMY_EXTERN_C_BEGIN

int				on_exit( void(*)(int, void *), void * );

AMY_EXTERN_C_END

/****************************************************************************/

#endif

