
/*
** Based on The Open Group Base Specifications Issue 7
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
#ifndef __cplusplus		// C version 

#define complex			_Complex
#define _Complex_I		1.0fi

#undef I
#define I				_Complex_I

double					cabs( double complex );
float					cabsf( float complex );
long double				cabsl( long double complex );
double complex			cacos( double complex );
float complex			cacosf( float complex );
double complex			cacosh( double complex );
float complex			cacoshf( float complex );
long double complex		cacoshl( long double complex );
long double complex		cacosl( long double complex );
double					carg( double complex );
float					cargf( float complex );
long double				cargl( long double complex );
double complex			casin( double complex );
float complex			casinf( float complex );
double complex			casinh( double complex );
float complex			casinhf( float complex );
long double complex		casinhl( long double complex );
long double complex		casinl( long double complex );
double complex			catan( double complex );
float complex			catanf( float complex );
double complex			catanh( double complex );
float complex			catanhf( float complex );
long double complex		catanhl( long double complex );
long double complex		catanl( long double complex );
double complex			ccos( double complex );
float complex			ccosf( float complex );
double complex			ccosh( double complex );
float complex			ccoshf( float complex );
long double complex		ccoshl( long double complex );
long double complex		ccosl( long double complex );
double complex			cexp( double complex );
float complex			cexpf( float complex );
long double complex		cexpl( long double complex );
double					cimag( double complex );
float					cimagf( float complex );
long double				cimagl( long double complex );
double complex			clog( double complex );
float complex			clogf( float complex );
long double complex		clogl( long double complex );
double complex			conj( double complex );
float complex			conjf( float complex );
long double complex		conjl( long double complex );
double complex			cpow( double complex, double complex );
float complex			cpowf( float complex, float complex );
long double complex		cpowl( long double complex, long double complex );
double complex			cproj( double complex );
float complex			cprojf( float complex );
long double complex		cprojl( long double complex );
double					creal( double complex );
float					crealf( float complex );
long double				creall( long double complex );
double complex			csin( double complex );
float complex			csinf( float complex );
double complex			csinh( double complex );
float complex			csinhf( float complex );
long double complex		csinhl( long double complex );
long double complex		csinl( long double complex );
double complex			csqrt( double complex );
float complex			csqrtf( float complex );
long double complex		csqrtl( long double complex );
double complex			ctan( double complex );
float complex			ctanf( float complex );
long double complex		ctanl( long double complex );
double complex			ctanh( double complex );
float complex			ctanhf( float complex );
long double complex		ctanhl( long double complex );

/****************************************************************************/
#else					// C++ version 

double					cabs( double _Complex );
float					cabsf( float _Complex );
long double				cabsl( long double _Complex );
double _Complex			cacos( double _Complex );
float _Complex			cacosf( float _Complex );
double _Complex			cacosh( double _Complex );
float _Complex			cacoshf( float _Complex );
long double _Complex	cacoshl( long double _Complex );
long double _Complex	cacosl( long double _Complex );
double					carg( double _Complex );
float					cargf( float _Complex );
long double				cargl( long double _Complex );
double _Complex			casin( double _Complex );
float _Complex			casinf( float _Complex );
double _Complex			casinh( double _Complex );
float _Complex			casinhf( float _Complex );
long double _Complex	casinhl( long double _Complex );
long double _Complex	casinl( long double _Complex );
double _Complex			catan( double _Complex );
float _Complex			catanf( float _Complex );
double _Complex			catanh( double _Complex );
float _Complex			catanhf( float _Complex );
long double _Complex	catanhl( long double _Complex );
long double _Complex	catanl( long double _Complex );
double _Complex			ccos( double _Complex );
float _Complex			ccosf( float _Complex );
double _Complex			ccosh( double _Complex );
float _Complex			ccoshf( float _Complex );
long double _Complex	ccoshl( long double _Complex );
long double _Complex	ccosl( long double _Complex );
double _Complex			cexp( double _Complex );
float _Complex			cexpf( float _Complex );
long double _Complex	cexpl( long double _Complex );
double					cimag( double _Complex );
float					cimagf( float _Complex );
long double				cimagl( long double _Complex );
double _Complex			clog( double _Complex );
float _Complex			clogf( float _Complex );
long double _Complex	clogl( long double _Complex );
double _Complex			conj( double _Complex );
float _Complex			conjf( float _Complex );
long double _Complex	conjl( long double _Complex );
double _Complex			cpow( double _Complex, double _Complex );
float _Complex			cpowf( float _Complex, float _Complex );
long double _Complex	cpowl( long double _Complex, long double _Complex );
double _Complex			cproj( double _Complex );
float _Complex			cprojf( float _Complex );
long double _Complex	cprojl( long double _Complex );
double					creal( double _Complex );
float					crealf( float _Complex );
long double				creall( long double _Complex );
double _Complex			csin( double _Complex );
float _Complex			csinf( float _Complex );
double _Complex			csinh( double _Complex );
float _Complex			csinhf( float _Complex );
long double _Complex	csinhl( long double _Complex );
long double _Complex	csinl( long double _Complex );
double _Complex			csqrt( double _Complex );
float _Complex			csqrtf( float _Complex );
long double _Complex	csqrtl( long double _Complex );
double _Complex			ctan( double _Complex );
float _Complex			ctanf( float _Complex );
long double _Complex	ctanl( long double _Complex );
double _Complex			ctanh( double _Complex );
float _Complex			ctanhf( float _Complex );
long double _Complex	ctanhl( long double _Complex );

#endif
/****************************************************************************/

AMY_EXTERN_C_END

#endif /* AMYSYS_COMPLEX_H */
