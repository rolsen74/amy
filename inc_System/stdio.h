
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

#ifndef AMYSYS_STDIO_H
#define AMYSYS_STDIO_H

/****************************************************************************/

#include <Amy_Defines.h>	// Need AMYFUNC
#include <locale.h>
#include <stddef.h>
#include <stdarg.h>
#include <sys/types.h>

/****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

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

// fix me for AmyCLib
//#define stderr			RACLibPublic->ra_stderr
//#define stdin				RACLibPublic->ra_stdin
//#define stdout			RACLibPublic->ra_stdout

//--#define L_cuserid		0

/****************************************************************************/

// clib2? and Newlib is only 32bit
typedef long long int fpos_t;

/****************************************************************************/

typedef struct
{
	int dummy;

} FILE;

/****************************************************************************/

void	AMYFUNC clearerr( FILE * );
char *	AMYFUNC ctermid( char * );
int		AMYFUNC dprintf( int, const char *, ... );
int		AMYFUNC fclose( FILE * );
FILE *	AMYFUNC fdopen( int, const char * );
int		AMYFUNC feof( FILE * );
int		AMYFUNC ferror( FILE * );
int		AMYFUNC fflush( FILE * );
int		AMYFUNC fgetc( FILE * );
int		AMYFUNC fgetpos( FILE *, fpos_t * );
char *	AMYFUNC fgets( char *, int, FILE * );
int		AMYFUNC fileno( FILE * );
void	AMYFUNC flockfile( FILE * );
FILE *	AMYFUNC fmemopen( void *, size_t, const char * );
FILE *	AMYFUNC fopen( const char *, const char * );
int		AMYFUNC fprintf( FILE *, const char *, ... );
int		AMYFUNC fputc( int, FILE * );
int		AMYFUNC fputs( const char *, FILE * );
size_t	AMYFUNC fread( void *, size_t, size_t, FILE * );
FILE *	AMYFUNC freopen( const char *, const char *, FILE * );
int		AMYFUNC fscanf( FILE *, const char *, ... );
int		AMYFUNC fseek( FILE *, long int, int );
int		AMYFUNC fseeko( FILE *, off_t, int  );
int		AMYFUNC fsetpos( FILE *, const fpos_t * );
long	AMYFUNC ftell( FILE * );
off_t	AMYFUNC ftello( FILE * );
int		AMYFUNC ftrylockfile( FILE * );
void	AMYFUNC funlockfile( FILE * );
size_t	AMYFUNC fwrite( const void *, size_t, size_t, FILE * );
int		AMYFUNC getc( FILE * );
int		AMYFUNC getchar( void );
int		AMYFUNC getc_unlocked( FILE * );
int		AMYFUNC getchar_unlocked( void );
ssize_t	AMYFUNC getdelim( char **, size_t, int, FILE * );
ssize_t	AMYFUNC getline( char **, size_t, FILE * );
char *	AMYFUNC gets( char * );
FILE *	AMYFUNC open_memstream( char **, size_t * );
int		AMYFUNC pclose( FILE * );
void	AMYFUNC perror( const char * );
FILE *	AMYFUNC popen( const char *, const char * );
int		AMYFUNC printf( const char *, ... );
int		AMYFUNC putc( int, FILE * );
int		AMYFUNC putchar( int );
int		AMYFUNC putc_unlocked( int, FILE * );
int		AMYFUNC putchar_unlocked( int );
int     AMYFUNC puts( const char * );
int		AMYFUNC remove( const char * );
int		AMYFUNC rename( const char *, const char * );
int		AMYFUNC renameat( int, const char *, int, const char * );
void	AMYFUNC rewind( FILE * );
int		AMYFUNC scanf( const char *, ... );
void	AMYFUNC setbuf( FILE *, char * );
int		AMYFUNC setvbuf( FILE *, char *, int, size_t );
int		AMYFUNC snprintf( char *, size_t, const char *, ... );
int		AMYFUNC sprintf( char *, const char *, ... );
int		AMYFUNC sscanf( const char *, const char *, ... );
char *	AMYFUNC tempnam( const char *, const char * );
FILE *	AMYFUNC tmpfile( void );
char *	AMYFUNC tmpnam( char * );
char *	AMYFUNC tmpnam_r( char * );
int		AMYFUNC ungetc( int, FILE * );
int		AMYFUNC vdprintf( int, const char *, va_list );
int		AMYFUNC vfprintf( FILE *, const char *, va_list );
int		AMYFUNC vfscanf( FILE *, const char *, va_list );
int		AMYFUNC vprintf( const char *, va_list );
int		AMYFUNC vscanf( const char *, va_list );
int		AMYFUNC vsnprintf( char *, size_t, const char *, va_list );
int		AMYFUNC vsprintf( char *, const char *, va_list );
int		AMYFUNC vsscanf( const char *, const char *, va_list );

/****************************************************************************/
// BSD

int		AMYFUNC asprintf( char **, const char *, ... );
int		AMYFUNC vasprintf( char **, const char *, va_list );

/****************************************************************************/

#ifdef __cplusplus
}
#endif

/****************************************************************************/

#endif
