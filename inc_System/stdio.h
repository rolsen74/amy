
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

#ifndef AMYSYS_STDIO_H
#define AMYSYS_STDIO_H

/* Compatibility macro for GMP/Autoconf */
#define _STDIO_H

/****************************************************************************/

#include <locale.h>
#include <stddef.h>
#include <stdarg.h>
#include <sys/types.h>

/****************************************************************************/

#define BUFSIZ			8192

#define L_ctermid		0
#define L_tmpnam		16

#define _IOFBF			0
#define _IOLBF			1
#define _IONBF			2

#define SEEK_CUR		1
#define SEEK_END		2
#define SEEK_SET		0

#define FILENAME_MAX	256
#define FOPEN_MAX		64
#define TMP_MAX			0x40000

#define EOF				-1

#define P_tmpdir		""

#define stderr			AmyCLibPublic->ra_stderr
#define stdin			AmyCLibPublic->ra_stdin
#define stdout			AmyCLibPublic->ra_stdout

//--#define L_cuserid		0

/****************************************************************************/

// clib2? and Newlib is only 32bit
typedef long long int fpos_t;

/****************************************************************************/

typedef struct
{
	int dummy;

} FILE;

#include <Amy_Public.h>

/****************************************************************************/

AMY_EXTERN_C_BEGIN

void	clearerr( FILE * );
char *	ctermid( char * );
int		dprintf( int, const char *, ... );
int		fclose( FILE * );
FILE *	fdopen( int, const char * );
int		feof( FILE * );
int		ferror( FILE * );
int		fflush( FILE * );
int		fgetc( FILE * );
int		fgetpos( FILE *, fpos_t * );
char *	fgets( char *, int, FILE * );
int		fileno( FILE * );
void	flockfile( FILE * );
FILE *	fmemopen( void *, size_t, const char * );
FILE *	fopen( const char *, const char * );
int		fprintf( FILE *, const char *, ... );
int		fputc( int, FILE * );
int		fputs( const char *, FILE * );
size_t	fread( void *, size_t, size_t, FILE * );
FILE *	freopen( const char *, const char *, FILE * );
int		fscanf( FILE *, const char *, ... );
int		fseek( FILE *, long int, int );
int		fseeko( FILE *, off_t, int );
int		fsetpos( FILE *, const fpos_t * );
long	ftell( FILE * );
off_t	ftello( FILE * );
int		ftrylockfile( FILE * );
void	funlockfile( FILE * );
size_t	fwrite( const void *, size_t, size_t, FILE * );
int		getc( FILE * );
int		getchar( void );
ssize_t	getdelim( char **, size_t *, int, FILE * );
ssize_t	getline( char **, size_t *, FILE * );
char *	gets( char * );
FILE *	open_memstream( char **, size_t * );
int		pclose( FILE * );
void	perror( const char * );
FILE *	popen( const char *, const char * );
int		printf( const char *, ... );
int		putc( int, FILE * );
int		putchar( int );
int		puts( const char * );
int		remove( const char * );
int		rename( const char *, const char * );
int		renameat( int, const char *, int, const char * );
void	rewind( FILE * );
int		scanf( const char *, ... );
void	setbuf( FILE *, char * );
int		setvbuf( FILE *, char *, int, size_t );
int		snprintf( char *, size_t, const char *, ... );
int		sprintf( char *, const char *, ... );
int		sscanf( const char *, const char *, ... );
char *	tempnam( const char *, const char * );
FILE *	tmpfile( void );
char *	tmpnam( char * );
char *	tmpnam_r( char * );
int		ungetc( int, FILE * );
int		vdprintf( int, const char *, va_list );
int		vfprintf( FILE *, const char *, va_list );
int		vfscanf( FILE *, const char *, va_list );
int		vprintf( const char *, va_list );
int		vscanf( const char *, va_list );
int		vsnprintf( char *, size_t, const char *, va_list );
int		vsprintf( char *, const char *, va_list );
int		vsscanf( const char *, const char *, va_list );

AMY_EXTERN_C_END

/****************************************************************************/
// BSD

AMY_EXTERN_C_BEGIN

int			asprintf( char **, const char *, ... );
int			vasprintf( char **, const char *, va_list );
FILE *		fopen64( const char *, const char * );
off64_t		ftello64( FILE * );
int			fseeko64( FILE *, off64_t, int );

AMY_EXTERN_C_END

/****************************************************************************/
// glibc

AMY_EXTERN_C_BEGIN

void	clearerr_unlocked( FILE * );
int		getc_unlocked( FILE * );
int		getchar_unlocked( void );
int		putc_unlocked( int, FILE * );
int		putchar_unlocked( int );
int		feof_unlocked( FILE * );
int		ferror_unlocked( FILE * );
int		fileno_unlocked( FILE * );
int		fflush_unlocked( FILE * );
int		fgetc_unlocked( FILE * );
int		fputc_unlocked( int, FILE * );
size_t	fread_unlocked( void *, size_t, size_t,FILE * );
size_t	fwrite_unlocked( const void *, size_t, size_t,FILE * );
char *	fgets_unlocked( char *, int, FILE * );
int		fputs_unlocked( const char *, FILE * );

AMY_EXTERN_C_END

/****************************************************************************/

#endif
