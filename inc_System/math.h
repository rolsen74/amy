
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

#include <Amy_Defines.h>	// Need AMYFUNC
#include <limits.h>			// For INT_MAX

/****************************************************************************/

#define FLT_EVAL_METHOD	0

/****************************************************************************/

typedef float			float_t;
typedef double			double_t;

// fix me for AmyCLib
// #define signgam			RACLibPublic->ra_signgam

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

#ifndef __isnanf
#define __isnanf(x)			__builtin_isnan((float)(x))
#endif

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

#ifndef __signbitf
#define __signbitf(x)		__builtin_signbit((float)(x))
#endif

#ifndef __signbitl
#define __signbitl(x)		__builtin_signbit((long double)(x))
#endif

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

double		AMYFUNC acos(			double );
float		AMYFUNC acosf(			float );
long double	AMYFUNC acosl(			long double );

double		AMYFUNC acosh(			double );
float		AMYFUNC acoshf(			float );
long double	AMYFUNC acoshl( 		long double );

double		AMYFUNC asin(			double );
float		AMYFUNC asinf(			float );
long double	AMYFUNC asinl(			long double );

double		AMYFUNC asinh(			double );
float		AMYFUNC asinhf(			float );
long double	AMYFUNC asinhl(			long double );

double		AMYFUNC atan2(			double, double );
float		AMYFUNC atan2f(			float, float );
long double	AMYFUNC atan2l(			long double, long double );

double		AMYFUNC atan(			double );
float		AMYFUNC atanf(			float );
long double	AMYFUNC atanl(			long double );

double		AMYFUNC atanh(			double );
float		AMYFUNC atanhf(			float );
long double	AMYFUNC atanhl(			long double );

double		AMYFUNC cbrt(			double );
float		AMYFUNC cbrtf(			float );
long double	AMYFUNC cbrtl(			long double );

double		AMYFUNC ceil(			double );
float		AMYFUNC ceilf(			float );
long double	AMYFUNC ceill(			long double );

double		AMYFUNC copysign(		double, double );
float		AMYFUNC copysignf(		float, float );
long double	AMYFUNC copysignl(		long double, long double );

double		AMYFUNC cos(			double );
float		AMYFUNC cosf(			float );
long double	AMYFUNC cosl(			long double );

double		AMYFUNC cosh(			double );
float		AMYFUNC coshf(			float );
long double	AMYFUNC coshl(			long double );

double		AMYFUNC erf(			double );
float		AMYFUNC erff(			float );
long double	AMYFUNC erfl(			long double );

double		AMYFUNC erfc(			double );
float		AMYFUNC erfcf(			float );
long double	AMYFUNC erfcl(			long double );

double		AMYFUNC exp(			double );
float		AMYFUNC expf(			float );
long double	AMYFUNC expl(			long double );

double		AMYFUNC exp2(			double );
float		AMYFUNC exp2f(			float );
long double	AMYFUNC exp2l(			long double );

double		AMYFUNC expm1(			double );
float		AMYFUNC expm1f(			float );
long double	AMYFUNC expm1l(			long double );

double		AMYFUNC fabs(			double );
float		AMYFUNC fabsf(			float );
long double	AMYFUNC fabsl(			long double );

double		AMYFUNC fdim(			double, double );
float		AMYFUNC fdimf(			float, float );
long double	AMYFUNC fdiml(			long double, long double );

double		AMYFUNC floor(			double );
float		AMYFUNC floorf(			float );
long double	AMYFUNC floorl(			long double );

double		AMYFUNC fma(			double, double, double );
float		AMYFUNC fmaf(			float, float, float );
long double	AMYFUNC fmal(			long double, long double, long double );

double		AMYFUNC fmax(			double, double );
float		AMYFUNC fmaxf(			float, float );
long double	AMYFUNC fmaxl(			long double, long double );

double		AMYFUNC fmin(			double, double );
float		AMYFUNC fminf(			float, float );
long double	AMYFUNC fminl(			long double, long double );

double		AMYFUNC fmod(			double, double );
float		AMYFUNC fmodf(			float, float );
long double	AMYFUNC fmodl(			long double, long double );

double		AMYFUNC frexp(			double, int * );
float		AMYFUNC frexpf(			float, int * );
long double	AMYFUNC frexpl(			long double, int * );

double		AMYFUNC hypot(			double, double );
float		AMYFUNC hypotf(			float, float );
long double	AMYFUNC hypotl(			long double, long double );

int			AMYFUNC ilogb(			double );
int			AMYFUNC ilogbf(			float );
int			AMYFUNC ilogbl(			long double );

double		AMYFUNC j0(				double );
double		AMYFUNC j1(				double );
double		AMYFUNC jn(				int, double );

double		AMYFUNC ldexp(			double, int );
float		AMYFUNC ldexpf(			float, int );
long double	AMYFUNC ldexpl(			long double, int );

double		AMYFUNC lgamma(			double );
float		AMYFUNC lgammaf(		float );
long double	AMYFUNC lgammal(		long double );

long long	AMYFUNC llrint(			double );
long long	AMYFUNC llrintf(		float );
long long	AMYFUNC llrintl(		long double );

long long	AMYFUNC llround(		double );
long long	AMYFUNC llroundf(		float );
long long	AMYFUNC llroundl(		long double );

double		AMYFUNC log(			double );
float		AMYFUNC logf(			float );
long double	AMYFUNC logl(			long double );

double		AMYFUNC log1p(			double );
float		AMYFUNC log1pf(			float );
long double	AMYFUNC log1pl(			long double );

double		AMYFUNC log2(			double );
float		AMYFUNC log2f(			float );
long double	AMYFUNC log2l(			long double );

double		AMYFUNC log10(			double );
float		AMYFUNC log10f(			float );
long double	AMYFUNC log10l(			long double );

double		AMYFUNC logb(			double );
float		AMYFUNC logbf(			float );
long double	AMYFUNC logbl(			long double );

long		AMYFUNC lrint(			double );
long		AMYFUNC lrintf(			float );
long		AMYFUNC lrintl(			long double );

long		AMYFUNC lround(			double );
long		AMYFUNC lroundf(		float );
long		AMYFUNC lroundl(		long double );

double		AMYFUNC modf(			double, double * );
float		AMYFUNC modff(			float, float * );
long double	AMYFUNC modfl(			long double, long double * );

double		AMYFUNC nan(			const char * );
float		AMYFUNC nanf(			const char * );
long double	AMYFUNC nanl(			const char * );

double		AMYFUNC nearbyint(		double );
float		AMYFUNC nearbyintf(		float );
long double	AMYFUNC nearbyintl(		long double );

double		AMYFUNC nextafter( 		double, double );
float		AMYFUNC nextafterf(		float, float );
long double	AMYFUNC nextafterl(		long double, long double );

double		AMYFUNC nexttoward(		double, long double );
float		AMYFUNC nexttowardf(	float, long double );
long double	AMYFUNC nexttowardl(	long double, long double );

double		AMYFUNC pow(			double, double );
float		AMYFUNC powf(			float, float );
long double	AMYFUNC powl(			long double, long double );

double		AMYFUNC remainder(		double, double );
float		AMYFUNC remainderf(		float, float );
long double	AMYFUNC remainderl(		long double, long double );

double		AMYFUNC remquo(			double, double, int * );
float		AMYFUNC remquof(		float, float, int * );
long double	AMYFUNC remquol(		long double, long double, int * );

double		AMYFUNC rint(			double );
float		AMYFUNC rintf(			float );
long double	AMYFUNC rintl(			long double );

double		AMYFUNC round(			double );
float		AMYFUNC roundf(			float );
long double	AMYFUNC roundl(			long double );

double		AMYFUNC scalbln(		double, long );
float		AMYFUNC scalblnf(		float, long );
long double	AMYFUNC scalblnl(		long double, long );

double		AMYFUNC scalbn(			double, int );
float		AMYFUNC scalbnf(		float, int );
long double	AMYFUNC scalbnl(		long double, int );

double		AMYFUNC sin(			double );
float		AMYFUNC sinf(			float );
long double	AMYFUNC sinl(			long double );

double		AMYFUNC sinh(			double );
float		AMYFUNC sinhf(			float );
long double	AMYFUNC sinhl(			long double );

double		AMYFUNC sqrt(			double );
float		AMYFUNC sqrtf(			float );
long double	AMYFUNC sqrtl(			long double );

double		AMYFUNC tan(			double );
float		AMYFUNC tanf(			float );
long double	AMYFUNC tanl(			long double );

double		AMYFUNC tanh(			double );
float		AMYFUNC tanhf(			float );
long double	AMYFUNC tanhl(			long double );

double		AMYFUNC tgamma(			double );
float		AMYFUNC tgammaf(		float );
long double	AMYFUNC tgammal(		long double );

double		AMYFUNC trunc(			double );
float		AMYFUNC truncf(			float );
long double	AMYFUNC truncl(			long double );

double		AMYFUNC y0(				double );
double		AMYFUNC y1(				double );
double		AMYFUNC yn(				int, double );

AMY_EXTERN_C_END

/****************************************************************************/
// Internal function not part of the specs

AMY_EXTERN_C_BEGIN

int			AMYFUNC __isnan(		double );
int			AMYFUNC __isnanf(		float );

int			AMYFUNC __signbit(		double );
int			AMYFUNC __signbitf(		float );
int			AMYFUNC __signbitl(		long double );

AMY_EXTERN_C_END

/****************************************************************************/

#endif

