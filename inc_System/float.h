
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

#ifndef AMYSYS_FLOAT_H
#define AMYSYS_FLOAT_H

AMY_EXTERN_C_BEGIN

/****************************************************************************/

#define FLT_ROUNDS			1
#define FLT_RADIX			2
#define FLT_EVAL_METHOD		0

#define FLT_DIG				6
#define FLT_MANT_DIG		24
#define FLT_EPSILON			1.19209290E-07F
#define FLT_MIN				1.17549435E-38F
#define FLT_MIN_EXP			( -125 )
#define FLT_MIN_10_EXP		( -37 )
#define FLT_MAX				3.40282347E+38F
#define FLT_MAX_EXP			128
#define FLT_MAX_10_EXP		38

#define DBL_DIG				15
#define DBL_MANT_DIG		53
#define DBL_EPSILON			2.2204460492503131E-16
#define DBL_MIN				2.2250738585072014E-308
#define DBL_MIN_EXP			( -1021 )
#define DBL_MIN_10_EXP		( -307 )
#define DBL_MAX				1.7976931348623157E+308
#define DBL_MAX_EXP			1024
#define DBL_MAX_10_EXP		308

// Follows IEEE standards for 80-bit floating point
#define LDBL_DIG			18
#define LDBL_MANT_DIG		64
#define LDBL_EPSILON		1.0842021724855044340075E-19L
#define LDBL_MIN			3.3621031431120935062627E-4932L
#define LDBL_MIN_EXP		( -16381 )
#define LDBL_MIN_10_EXP		( -4931 )
#define LDBL_MAX			1.1897314953572317650213E+4932L
#define LDBL_MAX_EXP		( +16384 )
#define LDBL_MAX_10_EXP		( +4932 )

/****************************************************************************/

AMY_EXTERN_C_END

#endif /* AMYSYS_FLOAT_H */
