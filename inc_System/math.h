
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

#ifndef AMYSYS_MATH_H
#define AMYSYS_MATH_H

/****************************************************************************/

#include <Amy_Defines.h>	// Need AMY_EXTERN_C_BEGIN
#include <limits.h>			// For INT_MAX

/****************************************************************************/

#define FLT_EVAL_METHOD	0

/****************************************************************************/

typedef float			float_t;
typedef double			double_t;

// fix me for AmyCLib
// #define signgam			AmyCLibPublic->ra_signgam

#define HUGE_VAL			__builtin_huge_val()
#define HUGE_VALF			__builtin_huge_valf()
#define HUGE_VALL			__builtin_huge_vall()
#define INFINITY			__builtin_inff()
#define NAN					__builtin_nanf("")

/****************************************************************************/

#define	FP_INFINITE			0x01
#define	FP_NAN				0x02
#define	FP_NORMAL			0x04
#define	FP_SUBNORMAL		0x08
#define	FP_ZERO				0x10

#define	FP_FAST_FMA			1
#define	FP_FAST_FMAF		1
#define	FP_FAST_FMAL		1

#define	FP_ILOGB0			( -INT_MAX )
#define	FP_ILOGBNAN			( +INT_MAX )

#define MATH_ERRNO			1
#define MATH_ERREXCEPT		2
#define math_errhandling	( MATH_ERRNO | MATH_ERREXCEPT )

#define	MAXFLOAT			((float)3.40282346638528860e+38)

/****************************************************************************/

/****************************************************************************/
/* Compiler built-in fallbacks for internal helpers */

#ifndef __fpclassify
#define __fpclassify(x)		__builtin_fpclassify(FP_INFINITE, FP_NAN, FP_NORMAL, FP_SUBNORMAL, FP_ZERO, (x))
#endif

#ifndef __fpclassifyf
#define __fpclassifyf(x)	__builtin_fpclassify(FP_INFINITE, FP_NAN, FP_NORMAL, FP_SUBNORMAL, FP_ZERO, (float)(x))
#endif

#ifndef __fpclassifyl
#define __fpclassifyl(x)	__builtin_fpclassify(FP_INFINITE, FP_NAN, FP_NORMAL, FP_SUBNORMAL, FP_ZERO, (long double)(x))
#endif

#ifndef __isfinite
#define __isfinite(x)		__builtin_isfinite(x)
#endif

#ifndef __isfinitef
#define __isfinitef(x)		__builtin_isfinite((float)(x))
#endif

#ifndef __isfinitel
#define __isfinitel(x)		__builtin_isfinite((long double)(x))
#endif

#ifndef __isinf
#define __isinf(x)			__builtin_isinf(x)
#endif

#ifndef __isinff
#define __isinff(x)			__builtin_isinf((float)(x))
#endif

#ifndef __isinfl
#define __isinfl(x)			__builtin_isinf((long double)(x))
#endif

#ifndef __isnan
#define __isnan(x)			__builtin_isnan(x)
#endif

//#ifndef __isnanf
//#define __isnanf(x)			__builtin_isnan((float)(x))
//#endif

#ifndef __isnanl
#define __isnanl(x)			__builtin_isnan((long double)(x))
#endif

#ifndef __isnormal
#define __isnormal(x)		__builtin_isnormal(x)
#endif

#ifndef __isnormalf
#define __isnormalf(x)		__builtin_isnormal((float)(x))
#endif

#ifndef __isnormall
#define __isnormall(x)		__builtin_isnormal((long double)(x))
#endif

#ifndef __signbit
#define __signbit(x)		__builtin_signbit(x)
#endif

//#ifndef __signbitf
//#define __signbitf(x)		__builtin_signbit((float)(x))
//#endif

//#ifndef __signbitl
//#define __signbitl(x)		__builtin_signbit((long double)(x))
//#endif

#define fpclassify(x) \
	((sizeof (x) == sizeof (float)) ? \
		__fpclassifyf(x) \
	: (sizeof (x) == sizeof (double)) ? \
		__fpclassify(x) \
	:	__fpclassifyl(x))

#define isfinite(x) \
	((sizeof (x) == sizeof (float)) ? \
		__isfinitef(x) \
	: (sizeof (x) == sizeof (double)) ? \
		__isfinite(x) \
	:	__isfinitel(x))

#define	isgreater(x, y)	\
	(!isunordered((x), (y)) && (x) > (y))

#define	isgreaterequal(x, y) \
	(!isunordered((x), (y)) && (x) >= (y))

#define isinf(x) \
	((sizeof (x) == sizeof (float)) ? \
		__isinff(x) \
	: (sizeof (x) == sizeof (double)) ? \
		__isinf(x) \
	:	__isinfl(x))

#define	isless(x, y) \
	(!isunordered((x), (y)) && (x) < (y))

#define	islessequal(x, y) \
	(!isunordered((x), (y)) && (x) <= (y))

#define	islessgreater(x, y)	\
	(!isunordered((x), (y)) && \
		((x) > (y) || (y) > (x)))

#define isnan(x) \
	((sizeof (x) == sizeof (float)) ? \
		__isnanf(x) \
	: (sizeof (x) == sizeof (double)) ? \
		__isnan(x) \
	:	__isnanl(x))

#define isnormal(x) \
	((sizeof (x) == sizeof (float)) ? \
		__isnormalf(x) \
	: (sizeof (x) == sizeof (double)) ? \
		__isnormal(x) \
	:	__isnormall(x))

#define	isunordered(x, y) \
	(isnan(x) || isnan(y))

#define signbit(x) \
	((sizeof (x) == sizeof (float)) ? \
		__signbitf(x) \
	: (sizeof (x) == sizeof (double)) ? \
		__signbit(x) \
	:	__signbitl(x))

/****************************************************************************/

#ifndef M_E
#define M_E				2.718281828459045235360
#endif

#ifndef M_LOG2E
#define M_LOG2E			1.442695040888963407360
#endif

#ifndef M_LOG10E
#define M_LOG10E		0.434294481903251827651
#endif

#ifndef M_LN2
#define M_LN2			0.693147180559945309417
#endif

#ifndef M_LN10
#define M_LN10			2.302585092994045684020
#endif

#ifndef M_PI
#define M_PI			3.141592653589793238460
#endif

#ifndef M_PI_2
#define M_PI_2			1.570796326794896619230
#endif

#ifndef M_PI_4
#define M_PI_4			0.785398163397448309616
#endif

#ifndef M_1_PI
#define M_1_PI			0.318309886183790671538
#endif

#ifndef M_2_PI
#define M_2_PI			0.636619772367581343076
#endif

#ifndef M_2_SQRTPI
#define M_2_SQRTPI		1.128379167095512573900
#endif

#ifndef M_SQRT2
#define M_SQRT2			1.414213562373095048800
#endif

#ifndef M_SQRT1_2
#define M_SQRT1_2		0.707106781186547524401
#endif

/****************************************************************************/

AMY_EXTERN_C_BEGIN

double		acos(			double );
float		acosf(			float );
long double	acosl(			long double );

double		acosh(			double );
float		acoshf(			float );
long double	acoshl( 		long double );

double		asin(			double );
float		asinf(			float );
long double	asinl(			long double );

double		asinh(			double );
float		asinhf(			float );
long double	asinhl(			long double );

double		atan2(			double, double );
float		atan2f(			float, float );
long double	atan2l(			long double, long double );

double		atan(			double );
float		atanf(			float );
long double	atanl(			long double );

double		atanh(			double );
float		atanhf(			float );
long double	atanhl(			long double );

double		cbrt(			double );
float		cbrtf(			float );
long double	cbrtl(			long double );

double		ceil(			double );
float		ceilf(			float );
long double	ceill(			long double );

double		copysign(		double, double );
float		copysignf(		float, float );
long double	copysignl(		long double, long double );

double		cos(			double );
float		cosf(			float );
long double	cosl(			long double );

double		cosh(			double );
float		coshf(			float );
long double	coshl(			long double );

double		erf(			double );
float		erff(			float );
long double	erfl(			long double );

double		erfc(			double );
float		erfcf(			float );
long double	erfcl(			long double );

double		exp(			double );
float		expf(			float );
long double	expl(			long double );

double		exp2(			double );
float		exp2f(			float );
long double	exp2l(			long double );

double		expm1(			double );
float		expm1f(			float );
long double	expm1l(			long double );

double		fabs(			double );
float		fabsf(			float );
long double	fabsl(			long double );

double		fdim(			double, double );
float		fdimf(			float, float );
long double	fdiml(			long double, long double );

double		floor(			double );
float		floorf(			float );
long double	floorl(			long double );

double		fma(			double, double, double );
float		fmaf(			float, float, float );
long double	fmal(			long double, long double, long double );

double		fmax(			double, double );
float		fmaxf(			float, float );
long double	fmaxl(			long double, long double );

double		fmin(			double, double );
float		fminf(			float, float );
long double	fminl(			long double, long double );

double		fmod(			double, double );
float		fmodf(			float, float );
long double	fmodl(			long double, long double );

double		frexp(			double, int * );
float		frexpf(			float, int * );
long double	frexpl(			long double, int * );

double		hypot(			double, double );
float		hypotf(			float, float );
long double	hypotl(			long double, long double );

int			ilogb(			double );
int			ilogbf(			float );
int			ilogbl(			long double );

double		j0(				double );
double		j1(				double );
double		jn(				int, double );

double		ldexp(			double, int );
float		ldexpf(			float, int );
long double	ldexpl(			long double, int );

double		lgamma(			double );
float		lgammaf(		float );
long double	lgammal(		long double );

long long	llrint(			double );
long long	llrintf(		float );
long long	llrintl(		long double );

long long	llround(		double );
long long	llroundf(		float );
long long	llroundl(		long double );

double		log(			double );
float		logf(			float );
long double	logl(			long double );

double		log1p(			double );
float		log1pf(			float );
long double	log1pl(			long double );

double		log2(			double );
float		log2f(			float );
long double	log2l(			long double );

double		log10(			double );
float		log10f(			float );
long double	log10l(			long double );

double		logb(			double );
float		logbf(			float );
long double	logbl(			long double );

long		lrint(			double );
long		lrintf(			float );
long		lrintl(			long double );

long		lround(			double );
long		lroundf(		float );
long		lroundl(		long double );

double		modf(			double, double * );
float		modff(			float, float * );
long double	modfl(			long double, long double * );

double		nan(			const char * );
float		nanf(			const char * );
long double	nanl(			const char * );

double		nearbyint(		double );
float		nearbyintf(		float );
long double	nearbyintl(		long double );

double		nextafter( 		double, double );
float		nextafterf(		float, float );
long double	nextafterl(		long double, long double );

double		nexttoward(		double, long double );
float		nexttowardf(	float, long double );
long double	nexttowardl(	long double, long double );

double		pow(			double, double );
float		powf(			float, float );
long double	powl(			long double, long double );

double		remainder(		double, double );
float		remainderf(		float, float );
long double	remainderl(		long double, long double );

double		remquo(			double, double, int * );
float		remquof(		float, float, int * );
long double	remquol(		long double, long double, int * );

double		rint(			double );
float		rintf(			float );
long double	rintl(			long double );

double		round(			double );
float		roundf(			float );
long double	roundl(			long double );

double		scalbln(		double, long );
float		scalblnf(		float, long );
long double	scalblnl(		long double, long );

double		scalbn(			double, int );
float		scalbnf(		float, int );
long double	scalbnl(		long double, int );

double		sin(			double );
float		sinf(			float );
long double	sinl(			long double );

double		sinh(			double );
float		sinhf(			float );
long double	sinhl(			long double );

double		sqrt(			double );
float		sqrtf(			float );
long double	sqrtl(			long double );

double		tan(			double );
float		tanf(			float );
long double	tanl(			long double );

double		tanh(			double );
float		tanhf(			float );
long double	tanhl(			long double );

double		tgamma(			double );
float		tgammaf(		float );
long double	tgammal(		long double );

double		trunc(			double );
float		truncf(			float );
long double	truncl(			long double );

double		y0(				double );
double		y1(				double );
double		yn(				int, double );

AMY_EXTERN_C_END

/****************************************************************************/
// Internal function not part of the specs

AMY_EXTERN_C_BEGIN

int			__isnan(		double );
int			__isnanf(		float );

int			__signbit(		double );
int			__signbitf(		float );
int			__signbitl(		long double );

AMY_EXTERN_C_END

/****************************************************************************/

#endif

