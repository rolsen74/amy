
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

#ifndef AMYSYS_INTTYPES_H
#define AMYSYS_INTTYPES_H

#include <stdint.h>
#include <stddef.h>
#include <wchar.h>

AMY_EXTERN_C_BEGIN

/****************************************************************************/

#ifdef __cplusplus
#define __STDC_CONSTANT_MACROS 1
#define __STDC_FORMAT_MACROS 1
#define __STDC_LIMIT_MACROS 1
#endif

/****************************************************************************/

typedef struct
{

	long long	quot;
	long long	rem;

} imaxdiv_t;

/****************************************************************************/

// fprintf macros for signed integers

#define PRId8			"d"
#define PRId16			"d"
#define PRId32			"d"
#define PRId64			"lld"

#define PRIi8			"i"
#define PRIi16			"i"
#define PRIi32			"i"
#define PRIi64			"lli"

#define PRIdLEAST8		"d"
#define PRIdLEAST16		"d"
#define PRIdLEAST32		"d"
#define PRIdLEAST64		"lld"

#define PRIiLEAST8		"i"
#define PRIiLEAST16		"i"
#define PRIiLEAST32		"i"
#define PRIiLEAST64		"lli"

#define PRIdFAST8		"d"
#define PRIdFAST16		"d"
#define PRIdFAST32		"d"
#define PRIdFAST64		"lld"

#define PRIiFAST8		"i"
#define PRIiFAST16		"i"
#define PRIiFAST32		"i"
#define PRIiFAST64		"lli"

#define PRIdMAX			"lld"
#define PRIiMAX			"lli"

#define PRIdPTR			"lld"
#define PRIiPTR			"lli"

// fprintf macros for unsigned integers

#define PRIo8			"o"
#define PRIo16			"o"
#define PRIo32			"o"
#define PRIo64			"llo"

#define PRIu8			"u"
#define PRIu16			"u"
#define PRIu32			"u"
#define PRIu64			"llu"

#define PRIx8			"x"
#define PRIx16			"x"
#define PRIx32			"x"
#define PRIx64			"llx"

#define PRIX8			"x"
#define PRIX16			"x"
#define PRIX32			"x"
#define PRIX64			"llx"

#define PRIoLEAST8		"o"
#define PRIoLEAST16		"o"
#define PRIoLEAST32		"o"
#define PRIoLEAST64		"llo"

#define PRIuLEAST8		"u"
#define PRIuLEAST16		"u"
#define PRIuLEAST32		"u"
#define PRIuLEAST64		"llu"

#define PRIxLEAST8		"x"
#define PRIxLEAST16		"x"
#define PRIxLEAST32		"x"
#define PRIxLEAST64		"llx"

#define PRIXLEAST8		"x"
#define PRIXLEAST16		"x"
#define PRIXLEAST32		"x"
#define PRIXLEAST64		"llx"

#define PRIoFAST8		"o"
#define PRIoFAST16		"o"
#define PRIoFAST32		"o"
#define PRIoFAST64		"llo"

#define PRIuFAST8		"u"
#define PRIuFAST16		"u"
#define PRIuFAST32		"u"
#define PRIuFAST64		"llu"

#define PRIxFAST8		"x"
#define PRIxFAST16		"x"
#define PRIxFAST32		"x"
#define PRIxFAST64		"llx"

#define PRIXFAST8		"x"
#define PRIXFAST16		"x"
#define PRIXFAST32		"x"
#define PRIXFAST64		"llx"

#define PRIoMAX			"llo"
#define PRIuMAX			"llu"
#define PRIxMAX			"llx"
#define PRIXMAX			"llX"

#define PRIoPTR			"llo"
#define PRIuPTR			"llu"
#define PRIxPTR			"llx"
#define PRIXPTR			"llX"

// fscanf macros for signed integers

#define SCNd8			"hhd"
#define SCNd16			"hd"
#define SCNd32			"d"
#define SCNd64			"lld"

#define SCNi8			"hhi"
#define SCNi16			"hi"
#define SCNi32			"i"
#define SCNi64			"lli"

#define SCNdLEAST8		"hhd"
#define SCNdLEAST16		"hd"
#define SCNdLEAST32		"d"
#define SCNdLEAST64		"lld"

#define SCNiLEAST8		"hhi"
#define SCNiLEAST16		"hi"
#define SCNiLEAST32		"i"
#define SCNiLEAST64		"lli"

#define SCNdFAST8		"hhd"
#define SCNdFAST16		"hd"
#define SCNdFAST32		"d"
#define SCNdFAST64		"lld"

#define SCNiFAST8		"hhi"
#define SCNiFAST16		"hi"
#define SCNiFAST32		"i"
#define SCNiFAST64		"lli"

// fscanf macros for unsigned integers

#define SCNo8			"hho"
#define SCNo16			"ho"
#define SCNo32			"o"
#define SCNo64			"llo"

#define SCNu8			"hhu"
#define SCNu16			"hu"
#define SCNu32			"u"
#define SCNu64			"llu"

#define SCNx8			"hhx"
#define SCNx16			"hx"
#define SCNx32			"x"
#define SCNx64			"llx"

#define SCNoLEAST8		"hho"
#define SCNoLEAST16		"ho"
#define SCNoLEAST32		"o"
#define SCNoLEAST64		"llo"

#define SCNuLEAST8		"hhu"
#define SCNuLEAST16		"hu"
#define SCNuLEAST32		"u"
#define SCNuLEAST64		"llu"

#define SCNxLEAST8		"hhx"
#define SCNxLEAST16		"hx"
#define SCNxLEAST32		"x"
#define SCNxLEAST64		"llx"

#define SCNoFAST8		"hho"
#define SCNoFAST16		"ho"
#define SCNoFAST32		"o"
#define SCNoFAST64		"llo"

#define SCNuFAST8		"hhu"
#define SCNuFAST16		"hu"
#define SCNuFAST32		"u"
#define SCNuFAST64		"llu"

#define SCNxFAST8		"hhx"
#define SCNxFAST16		"hx"
#define SCNxFAST32		"x"
#define SCNxFAST64		"llx"

/****************************************************************************/

intmax_t	imaxabs( intmax_t );
imaxdiv_t	imaxdiv( intmax_t, intmax_t );
intmax_t	strtoimax( const char *, char **, int );
uintmax_t	strtoumax( const char *, char **, int );
intmax_t	wcstoimax( const wchar_t *, wchar_t **, int );
uintmax_t	wcstoumax( const wchar_t *, wchar_t **, int );

/****************************************************************************/

AMY_EXTERN_C_END

#endif /* AMYSYS_INTTYPES_H */
