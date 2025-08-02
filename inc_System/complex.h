
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

#ifndef AMYSYS_COMPLEX_H
#define AMYSYS_COMPLEX_H

/****************************************************************************/

#include <Amy_Defines.h>	// Need AMYFUNC

/****************************************************************************/

#define complex			_Complex
#define _Complex_I		1.0fi
#define I				_Complex_I

/****************************************************************************/

AMY_EXTERN_C_BEGIN

double					AMYFUNC cabs( double complex );
float					AMYFUNC cabsf( float complex );
long double				AMYFUNC cabsl( long double complex );
double complex			AMYFUNC cacos( double complex );
float complex			AMYFUNC cacosf( float complex );
double complex			AMYFUNC cacosh( double complex );
float complex			AMYFUNC cacoshf( float complex );
long double complex		AMYFUNC cacoshl( long double complex );
long double complex		AMYFUNC cacosl( long double complex );
double					AMYFUNC carg( double complex );
float					AMYFUNC cargf( float complex );
long double				AMYFUNC cargl( long double complex );
double complex			AMYFUNC casin( double complex );
float complex			AMYFUNC casinf( float complex );
double complex			AMYFUNC casinh( double complex );
float complex			AMYFUNC casinhf( float complex );
long double complex		AMYFUNC casinhl( long double complex );
long double complex		AMYFUNC casinl( long double complex );
double complex			AMYFUNC catan( double complex );
float complex			AMYFUNC catanf( float complex );
double complex			AMYFUNC catanh( double complex );
float complex			AMYFUNC catanhf( float complex );
long double complex		AMYFUNC catanhl( long double complex );
long double complex		AMYFUNC catanl( long double complex );
double complex			AMYFUNC ccos( double complex );
float complex			AMYFUNC ccosf( float complex );
double complex			AMYFUNC ccosh( double complex );
float complex			AMYFUNC ccoshf( float complex );
long double complex		AMYFUNC ccoshl( long double complex );
long double complex		AMYFUNC ccosl( long double complex );
double complex			AMYFUNC cexp( double complex );
float complex			AMYFUNC cexpf( float complex );
long double complex		AMYFUNC cexpl( long double complex );
double					AMYFUNC cimag( double complex );
float					AMYFUNC cimagf( float complex );
long double				AMYFUNC cimagl( long double complex );
double complex			AMYFUNC clog( double complex );
float complex			AMYFUNC clogf( float complex );
long double complex		AMYFUNC clogl( long double complex );
double complex			AMYFUNC conj( double complex );
float complex			AMYFUNC conjf( float complex );
long double complex		AMYFUNC conjl( long double complex );
double complex			AMYFUNC cpow( double complex, double complex );
float complex			AMYFUNC cpowf( float complex, float complex );
long double complex		AMYFUNC cpowl( long double complex, long double complex );
double complex			AMYFUNC cproj( double complex );
float complex			AMYFUNC cprojf( float complex );
long double complex		AMYFUNC cprojl( long double complex );
double					AMYFUNC creal( double complex );
float					AMYFUNC crealf( float complex );
long double				AMYFUNC creall( long double complex );
double complex			AMYFUNC csin( double complex );
float complex			AMYFUNC csinf( float complex );
double complex			AMYFUNC csinh( double complex );
float complex			AMYFUNC csinhf( float complex );
long double complex		AMYFUNC csinhl( long double complex );
long double complex		AMYFUNC csinl( long double complex );
double complex			AMYFUNC csqrt( double complex );
float complex			AMYFUNC csqrtf( float complex );
long double complex		AMYFUNC csqrtl( long double complex );
double complex			AMYFUNC ctan( double complex );
float complex			AMYFUNC ctanf( float complex );
long double complex		AMYFUNC ctanl( long double complex );
double complex			AMYFUNC ctanh( double complex );
float complex			AMYFUNC ctanhf( float complex );
long double complex		AMYFUNC ctanhl( long double complex );

AMY_EXTERN_C_END

/****************************************************************************/

#endif

