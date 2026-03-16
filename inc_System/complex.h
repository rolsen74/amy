
/*
** Based on The Open Group Base Specifications Issue 8
**
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025-2026 Rene W. Olsen
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

#ifndef AMYSYS_COMPLEX_H
#define AMYSYS_COMPLEX_H

AMY_EXTERN_C_BEGIN

/****************************************************************************/

#define complex			_Complex
#define _Complex_I		((__extension__ 1.0fi))

#define imaginary		_Imaginary

#undef I
#define I				_Complex_I

#define CMPLX(x,y)		((_Complex double)((double)(x) + (double)(y) * I))
#define CMPLXF(x,y)		((_Complex float)((float)(x) + (float)(y) * I))
#define CMPLXL(x,y)		((_Complex long double)((long double)(x) + (long double)(y) * I))

/****************************************************************************/

double					cabs( _Complex double );
float					cabsf( _Complex float );
long double				cabsl( _Complex long double );
_Complex double			cacos( _Complex double );
_Complex float			cacosf( _Complex float );
_Complex double			cacosh( _Complex double );
_Complex float			cacoshf( _Complex float );
_Complex long double	cacoshl( _Complex long double );
_Complex long double	cacosl( _Complex long double );
double					carg( _Complex double );
float					cargf( _Complex float );
long double				cargl( _Complex long double );
_Complex double			casin( _Complex double );
_Complex float			casinf( _Complex float );
_Complex double			casinh( _Complex double );
_Complex float			casinhf( _Complex float );
_Complex long double	casinhl( _Complex long double );
_Complex long double	casinl( _Complex long double );
_Complex double			catan( _Complex double );
_Complex float			catanf( _Complex float );
_Complex double			catanh( _Complex double );
_Complex float			catanhf( _Complex float );
_Complex long double	catanhl( _Complex long double );
_Complex long double	catanl( _Complex long double );
_Complex double			ccos( _Complex double );
_Complex float			ccosf( _Complex float );
_Complex double			ccosh( _Complex double );
_Complex float			ccoshf( _Complex float );
_Complex long double	ccoshl( _Complex long double );
_Complex long double	ccosl( _Complex long double );
_Complex double			cexp( _Complex double );
_Complex float			cexpf( _Complex float );
_Complex long double	cexpl( _Complex long double );
double					cimag( _Complex double );
float					cimagf( _Complex float );
long double				cimagl( _Complex long double );
_Complex double			clog( _Complex double );
_Complex float			clogf( _Complex float );
_Complex long double	clogl( _Complex long double );
_Complex double			conj( _Complex double );
_Complex float			conjf( _Complex float );
_Complex long double	conjl( _Complex long double );
_Complex double			cpow( _Complex double, _Complex double );
_Complex float			cpowf( _Complex float, _Complex float );
_Complex long double	cpowl( _Complex long double, _Complex long double );
_Complex double			cproj( _Complex double );
_Complex float			cprojf( _Complex float );
_Complex long double	cprojl( _Complex long double );
double					creal( _Complex double );
float					crealf( _Complex float );
long double				creall( _Complex long double );
_Complex double			csin( _Complex double );
_Complex float			csinf( _Complex float );
_Complex double			csinh( _Complex double );
_Complex float			csinhf( _Complex float );
_Complex long double	csinhl( _Complex long double );
_Complex long double	csinl( _Complex long double );
_Complex double			csqrt( _Complex double );
_Complex float			csqrtf( _Complex float );
_Complex long double	csqrtl( _Complex long double );
_Complex double			ctan( _Complex double );
_Complex float			ctanf( _Complex float );
_Complex long double	ctanl( _Complex long double );
_Complex double			ctanh( _Complex double );
_Complex float			ctanhf( _Complex float );
_Complex long double	ctanhl( _Complex long double );

/****************************************************************************/

AMY_EXTERN_C_END

#endif /* AMYSYS_COMPLEX_H */
