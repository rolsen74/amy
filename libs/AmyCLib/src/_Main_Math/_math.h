
/*
** SPDX-License-Identifier: BSD-3-Clause
** Modifications (c) 2025 Rene W. Olsen
** Part of Amy C Lib
**
** Based on:
**
** ====================================================
** Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
**
** Developed at SunPro, a Sun Microsystems, Inc. business.
** Permission to use, copy, modify, and distribute this
** software is freely granted, provided that this notice
** is preserved.
** ====================================================
*/

#ifndef AMYLIB_MATH_HEADERS_H
#define AMYLIB_MATH_HEADERS_H

union FloatBits
{
	float		value;

	U32		raw;

	struct
	{
		U32	high;
	}			longs;

	struct
	{
		U32	sign	: 1;
		U32	exp		: 8;
		U32	man		: 23;
	}			bits;
};

union DoubleBits
{
	double		value;

	uint64		raw;

	struct
	{
		U32	high;
		U32	low;
	}			longs;

	struct
	{
		U32	sign	: 1;
		U32	exp		: 11;
		uint64	man		: 52;
	}			bits;
};

union LongDoubleBits
{
	long double	value;

//	uint96	   raw;

	struct
	{
		U32	high;
		U32	mid;
		U32	low;
	}			longs;

	// fix me 'bits' are wrong
	struct
	{
		U32	sign	:1;
		U32	exp		:11;
		U32	manh	:20;
		U32	manl	:32;
	} 			bits;
};

#if 0
union DoubleDoubleBits
{
	double double value;

//	uint128	    raw;

	// fix me 'bits' are wrong
	struct
	{
		U32	sign	:1;
		U32	exp		:11;
		U32	manh	:20;
		U32	manl	:32;
	} 			bits;
};
#endif


#if 0




// -- /****************************************************************************/
// -- 
// -- #include <limits.h>
// -- #include <errno.h>
// -- #include <float.h>
// -- #include <math.h>
// -- #include <fenv.h>
// -- 
// -- /****************************************************************************/
// -- 
// -- #ifndef _MACROS_H
// -- #include "macros.h"
// -- #endif /* _MACROS_H */
// -- 
// -- #ifndef _DEBUG_H
// -- #include "debug.h"
// -- #endif /* _DEBUG_H */
// -- 
// -- /****************************************************************************/
// -- 
// -- #ifndef _MATH_FP_SUPPORT_H
// -- #include "math_fp_support.h"
// -- #endif /* _MATH_FP_SUPPORT_H */
// -- 
// -- /****************************************************************************/
// -- 
// -- #ifndef _STDLIB_HEADERS_H
// -- #include "stdlib_headers.h"
// -- #endif /* _STDLIB_HEADERS_H */
// -- 
// -- /****************************************************************************/
// -- 
// -- #ifndef _STDLIB_PROFILE_H
// -- #include "stdlib_profile.h"
// -- #endif /* _STDLIB_PROFILE_H */
// -- 
// -- /****************************************************************************/
// -- 
// -- #if defined(IEEE_FLOATING_POINT_SUPPORT)
// -- 
// -- /****************************************************************************/
// -- 
// -- #ifndef PROTO_MATHIEEESINGBAS_H
// -- #include <proto/mathieeesingbas.h>
// -- #endif /* PROTO_MATHIEEESINGBAS_H */
// -- 
// -- #ifndef PROTO_MATHIEEEDOUBBAS_H
// -- #include <proto/mathieeedoubbas.h>
// -- #endif /* PROTO_MATHIEEEDOUBBAS_H */
// -- 
// -- #ifndef PROTO_MATHIEEEDOUBTRANS_H
// -- #include <proto/mathieeedoubtrans.h>
// -- #endif /* PROTO_MATHIEEEDOUBTRANS_H */
// -- 
// -- /****************************************************************************/
// -- 
// -- extern struct Library * NOCOMMON MathIeeeSingBasBase;
// -- extern struct Library * NOCOMMON MathIeeeDoubBasBase;
// -- extern struct Library * NOCOMMON MathIeeeDoubTransBase;
// -- 
// -- /****************************************************************************/
// -- 
// -- #endif /* IEEE_FLOATING_POINT_SUPPORT */

/****************************************************************************/

/* 'Portable' raw representations of three IEEE floating point formats. */
union ieee_long_double
{
	long double		value;
	unsigned long	raw[3];
};

union ieee_double
{
	double			value;
	unsigned long	raw[2];
};

union ieee_single
{
	float			value;
	unsigned long	raw[1];
};

/****************************************************************************/

// -- #define FLT_UWORD_IS_ZERO(x) ((x)==0)
// -- #define FLT_UWORD_IS_SUBNORMAL(x) ((x)<0x00800000L)
// -- #define FLT_UWORD_MIN 0x00000001
// -- #define FLT_UWORD_EXP_MIN 0x43160000
// -- #define FLT_UWORD_LOG_MIN 0x42cff1b5
// -- #define FLT_SMALLEST_EXP -22

typedef union
{
    double value;
    struct
    {
	    unsigned int msw;
	    unsigned int lsw;
    } parts;
} ieee_double_shape_type;

#define EXTRACT_WORDS(ix0,ix1,d)				    \
do {											    \
  ieee_double_shape_type ew_u;					    \
  ew_u.value = (d);								    \
  (ix0) = ew_u.parts.msw;						    \
  (ix1) = ew_u.parts.lsw;						    \
} while (0)

/* Get the more significant 32 bit int from a double.  */

#define GET_HIGH_WORD(i,d)						    \
do {											    \
  ieee_double_shape_type gh_u;					    \
  gh_u.value = (d);								    \
  (i) = gh_u.parts.msw;							    \
} while (0)

/* Get the less significant 32 bit int from a double.  */

#define GET_LOW_WORD(i,d)						    \
do {											    \
  ieee_double_shape_type gl_u;					    \
  gl_u.value = (d);								    \
  (i) = gl_u.parts.lsw;							    \
} while (0)

/* Set a double from two 32 bit ints.  */

#define INSERT_WORDS(d,ix0,ix1)					    \
do {											    \
  ieee_double_shape_type iw_u;					    \
  iw_u.parts.msw = (ix0);						    \
  iw_u.parts.lsw = (ix1);						    \
  (d) = iw_u.value;								    \
} while (0)

/* Set the more significant 32 bits of a double from an int.  */

#define SET_HIGH_WORD(d,v)						    \
do {											    \
  ieee_double_shape_type sh_u;					    \
  sh_u.value = (d);								    \
  sh_u.parts.msw = (v);							    \
  (d) = sh_u.value;								    \
} while (0)

/* Set the less significant 32 bits of a double from an int.  */

#define SET_LOW_WORD(d,v)						    \
do {											    \
  ieee_double_shape_type sl_u;					    \
  sl_u.value = (d);								    \
  sl_u.parts.lsw = (v);							    \
  (d) = sl_u.value;								    \
} while (0)

/* A union which permits us to convert between a float and a 32 bit
   int. */

typedef union
{
  float value;
  unsigned int word;
} ieee_float_shape_type;

/* Get a 32 bit int from a float.  */

#define GET_FLOAT_WORD(i,d)	    \
do {						    \
  ieee_float_shape_type gf_u;   \
  gf_u.value = (d);			    \
  (i) = gf_u.word;			    \
} while (0)

/* Set a float from a 32 bit int.  */

#define SET_FLOAT_WORD(d,i)	    \
do {						    \
  ieee_float_shape_type sf_u;   \
  sf_u.word = (i);			    \
  (d) = sf_u.value;			    \
} while (0)

// -- extern double __kernel_cos(double x, double y);
// -- extern double __kernel_sin(double x, double y, int iy);
// -- extern int __rem_pio2(double x, double *y);
// -- extern double __kernel_tan(double x, double y, int iy);
// -- extern double __expm1(double x);
// -- extern float __kernel_cosf(float x, float y);
// -- extern float __kernel_sinf(float x, float y, int iy);
// -- extern LONG __rem_pio2f(float x, float *y);
// -- extern float __kernel_tanf(float x, float y, int iy);
// -- extern double __lgamma(double x,int * gamma_sign_ptr);
// -- extern float __lgammaf(float x,int * gamma_sign_ptr);
// -- 
// -- /****************************************************************************/
// -- 
// -- /* math_huge_val.c */
// -- extern double __get_huge_val(void);
// -- 
// -- /****************************************************************************/
// -- 
// -- /* math_huge_valf.c */
// -- extern float __get_huge_valf(void);

/****************************************************************************/


/****************************************************************************/

#define	DBL_MANH_SIZE	20
#define	DBL_MANL_SIZE	32


#define	mask_nbit_l(u)	((void)0)
#define	LDBL_IMPLICIT_NBIT
#define	LDBL_NBIT	0

#define	LDBL_MANH_SIZE	20
#define	LDBL_MANL_SIZE	32

#define	LDBL_TO_ARRAY32(u, a) do {			\
	(a)[0] = (U32)(u).bits.manl;		  \
	(a)[1] = (U32)(u).bits.manh;		  \
} while(0)

#define	STRICT_ASSIGN(type, lval, rval)	((lval) = (rval))

/****************************************************************************/

#ifndef	__fenv_static
#define	__fenv_static	static
#endif

typedef	U32	fenv_t;
typedef	U32	fexcept_t;

/* Exception flags */
#define	FE_INEXACT	0x02000000
#define	FE_DIVBYZERO	0x04000000
#define	FE_UNDERFLOW	0x08000000
#define	FE_OVERFLOW	0x10000000
#define	FE_INVALID	0x20000000	/* all types of invalid FP ops */

/*
 * The PowerPC architecture has extra invalid flags that indicate the
 * specific type of invalid operation occurred.  These flags may be
 * tested, set, and cleared---but not masked---separately.  All of
 * these bits are cleared when FE_INVALID is cleared, but only
 * FE_VXSOFT is set when FE_INVALID is explicitly set in software.
 */
#define	FE_VXCVI	0x00000100	/* invalid integer convert */
#define	FE_VXSQRT	0x00000200	/* square root of a negative */
#define	FE_VXSOFT	0x00000400	/* software-requested exception */
#define	FE_VXVC		0x00080000	/* ordered comparison involving NaN */
#define	FE_VXIMZ	0x00100000	/* inf * 0 */
#define	FE_VXZDZ	0x00200000	/* 0 / 0 */
#define	FE_VXIDI	0x00400000	/* inf / inf */
#define	FE_VXISI	0x00800000	/* inf - inf */
#define	FE_VXSNAN	0x01000000	/* operation on a signalling NaN */
#define	FE_ALL_INVALID	(FE_VXCVI | FE_VXSQRT | FE_VXSOFT | FE_VXVC | \
			 FE_VXIMZ | FE_VXZDZ | FE_VXIDI | FE_VXISI | \
			 FE_VXSNAN | FE_INVALID)
#define	FE_ALL_EXCEPT	(FE_DIVBYZERO | FE_INEXACT | \
			 FE_ALL_INVALID | FE_OVERFLOW | FE_UNDERFLOW)

/* Rounding modes */
#define	FE_TONEAREST	0x0000
#define	FE_TOWARDZERO	0x0001
#define	FE_UPWARD	0x0002
#define	FE_DOWNWARD	0x0003
#define	_ROUND_MASK	(FE_TONEAREST | FE_DOWNWARD | \
			 FE_UPWARD | FE_TOWARDZERO)

// -- __BEGIN_DECLS
// -- 
// -- /* Default floating-point environment */
// -- extern const fenv_t __fe_dfl_env;
// -- #define FE_DFL_ENV  (&__fe_dfl_env)

/* We need to be able to map status flag positions to mask flag positions */
#define	_FPUSW_SHIFT	22
#define	_ENABLE_MASK	((FE_DIVBYZERO | FE_INEXACT | FE_INVALID | \
			 FE_OVERFLOW | FE_UNDERFLOW) >> _FPUSW_SHIFT)

#define	__mffs(__env)	__asm __volatile("mffs %0" : "=f" (*(__env)))
#define	__mtfsf(__env)	__asm __volatile("mtfsf 255,%0" : : "f" (__env))

union __fpscr {
	double __d;
	struct {
		U32 __junk;
		fenv_t __reg;
	} __bits;
};

// -- __fenv_static inline int
// -- feclearexcept(int __excepts)
// -- {
// -- 	  union __fpscr __r;
// -- 
// -- 	  if (__excepts & FE_INVALID)
// -- 		  __excepts |= FE_ALL_INVALID;
// -- 	  __mffs(&__r.__d);
// -- 	  __r.__bits.__reg &= ~__excepts;
// -- 	  __mtfsf(__r.__d);
// -- 	  return (0);
// -- }
// -- 
// -- __fenv_static inline int
// -- fegetexceptflag(fexcept_t *__flagp, int __excepts)
// -- {
// -- 	  union __fpscr __r;
// -- 
// -- 	  __mffs(&__r.__d);
// -- 	  *__flagp = __r.__bits.__reg & __excepts;
// -- 	  return (0);
// -- }
// -- 
// -- __fenv_static inline int
// -- fesetexceptflag(const fexcept_t *__flagp, int __excepts)
// -- {
// -- 	  union __fpscr __r;
// -- 
// -- 	  if (__excepts & FE_INVALID)
// -- 		  __excepts |= FE_ALL_EXCEPT;
// -- 	  __mffs(&__r.__d);
// -- 	  __r.__bits.__reg &= ~__excepts;
// -- 	  __r.__bits.__reg |= *__flagp & __excepts;
// -- 	  __mtfsf(__r.__d);
// -- 	  return (0);
// -- }
// -- 
// -- __fenv_static inline int
// -- feraiseexcept(int __excepts)
// -- {
// -- 	  union __fpscr __r;
// -- 
// -- 	  if (__excepts & FE_INVALID)
// -- 		  __excepts |= FE_VXSOFT;
// -- 	  __mffs(&__r.__d);
// -- 	  __r.__bits.__reg |= __excepts;
// -- 	  __mtfsf(__r.__d);
// -- 	  return (0);
// -- }
// -- 
// -- __fenv_static inline int
// -- fetestexcept(int __excepts)
// -- {
// -- 	  union __fpscr __r;
// -- 
// -- 	  __mffs(&__r.__d);
// -- 	  return (__r.__bits.__reg & __excepts);
// -- }

__fenv_static inline int
fegetround(void)
{
	union __fpscr __r;

	__mffs(&__r.__d);
	return (__r.__bits.__reg & _ROUND_MASK);
}

__fenv_static inline int
fesetround(int __round)
{
	union __fpscr __r;

	if (__round & ~_ROUND_MASK)
		return (-1);
	__mffs(&__r.__d);
	__r.__bits.__reg &= ~_ROUND_MASK;
	__r.__bits.__reg |= __round;
	__mtfsf(__r.__d);
	return (0);
}

// -- __fenv_static inline int
// -- fegetenv(fenv_t *__envp)
// -- {
// -- 	  union __fpscr __r;
// -- 
// -- 	  __mffs(&__r.__d);
// -- 	  *__envp = __r.__bits.__reg;
// -- 	  return (0);
// -- }
// -- 
// -- __fenv_static inline int
// -- feholdexcept(fenv_t *__envp)
// -- {
// -- 	  union __fpscr __r;
// -- 
// -- 	  __mffs(&__r.__d);
// -- 	  *__envp = __r.__d;
// -- 	  __r.__bits.__reg &= ~(FE_ALL_EXCEPT | _ENABLE_MASK);
// -- 	  __mtfsf(__r.__d);
// -- 	  return (0);
// -- }
// -- 
// -- __fenv_static inline int
// -- fesetenv(const fenv_t *__envp)
// -- {
// -- 	  union __fpscr __r;
// -- 
// -- 	  __r.__bits.__reg = *__envp;
// -- 	  __mtfsf(__r.__d);
// -- 	  return (0);
// -- }
// -- 
// -- __fenv_static inline int
// -- feupdateenv(const fenv_t *__envp)
// -- {
// -- 	  union __fpscr __r;
// -- 
// -- 	  __mffs(&__r.__d);
// -- 	  __r.__bits.__reg &= FE_ALL_EXCEPT;
// -- 	  __r.__bits.__reg |= *__envp;
// -- 	  __mtfsf(__r.__d);
// -- 	  return (0);
// -- }
// -- 
// -- #if __BSD_VISIBLE
// -- 
// -- /* We currently provide no external definitions of the functions below. */
// -- 
// -- static inline int
// -- feenableexcept(int __mask)
// -- {
// -- 	  union __fpscr __r;
// -- 	  fenv_t __oldmask;
// -- 
// -- 	  __mffs(&__r.__d);
// -- 	  __oldmask = __r.__bits.__reg;
// -- 	  __r.__bits.__reg |= (__mask & FE_ALL_EXCEPT) >> _FPUSW_SHIFT;
// -- 	  __mtfsf(__r.__d);
// -- 	  return ((__oldmask & _ENABLE_MASK) << _FPUSW_SHIFT);
// -- }
// -- 
// -- static inline int
// -- fedisableexcept(int __mask)
// -- {
// -- 	  union __fpscr __r;
// -- 	  fenv_t __oldmask;
// -- 
// -- 	  __mffs(&__r.__d);
// -- 	  __oldmask = __r.__bits.__reg;
// -- 	  __r.__bits.__reg &= ~((__mask & FE_ALL_EXCEPT) >> _FPUSW_SHIFT);
// -- 	  __mtfsf(__r.__d);
// -- 	  return ((__oldmask & _ENABLE_MASK) << _FPUSW_SHIFT);
// -- }
// -- 
// -- static inline int
// -- fegetexcept(void)
// -- {
// -- 	  union __fpscr __r;
// -- 
// -- 	  __mffs(&__r.__d);
// -- 	  return ((__r.__bits.__reg & _ENABLE_MASK) << _FPUSW_SHIFT);
// -- }

/****************************************************************************/
#endif

#endif

