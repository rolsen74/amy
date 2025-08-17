
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

/*
 * scalbn (double x, int n)
 * scalbn(x,n) returns x* 2**n  computed by  exponent
 * manipulation rather than by actually performing an
 * exponentiation or a multiplication.
 */

// --

#include "src/All.h"
#include "_math.h"

// --

static const double two54	= 1.80143985094819840000e+16; /* 0x43500000, 0x00000000 */
static const double twom54	= 5.55111512312578270212e-17; /* 0x3C900000, 0x00000000 */
static const double huge	= 1.0e+300;
static const double tiny	= 1.0e-300;

// --

double AMYFUNC _generic_math_d_scalbn( struct AmyCLibIFace *Self, double x, int n )
{
union DoubleBits val;
uint64 xx;
int32 hx;
int32 lx;
int32 k;

	// Extract Words
	val.value = x;
	hx = ( val.raw >> 32 );
	lx = ( val.raw >>  0 );
//	EXTRACT_WORDS( hx, lx, x );

	// --

	/* extract exponent */
	k = ( hx & 0x7ff00000 ) >> 20;		  
	
	if ( k == 0 )
	{	
		/* 0 or subnormal x */
		if (( lx | ( hx & 0x7fffffff )) ==0 )
		{
			return x; /* +-0 */
		}

		x *= two54;


		// Extract Words
		val.value = x;
		hx = ( val.raw >> 32 );
//		GET_HIGH_WORD( hx, x );

		k = (( hx & 0x7ff00000 ) >> 20 ) - 54;
		
		if ( n < -50000 )
		{
			/* underflow */
			return tiny*x; 	 
		}
	}

	if ( k == 0x7ff )
	{
		/* NaN or Inf */
		return x+x;		  
	}

	k = k+n;

	if ( k >  0x7fe )
	{
		/* overflow  */
		return huge * Self->math_d_copysign( huge, x );
	}

	/* normal result */
	if ( k > 0 ) 			
	{
		val.value = x;

		xx = (uint64)(( hx & 0x800fffff ) | ( k << 20 )) << 32;
		xx |= val.raw & 0x00000000ffffffff;
		val.raw = xx;

//		  SET_HIGH_WORD( x, ( hx & 0x800fffff ) | ( k << 20 ));

		return( val.value );
	}

	if ( k <= -54 )
	{
		/* in case integer overflow in n+k */
		if ( n > 50000 )  
		{
			/* overflow */
			return huge * Self->math_d_copysign( huge, x );
		}
		else
		{
			/* underflow */
			return tiny * Self->math_d_copysign( tiny, x );
		}
	}

	/* subnormal result */
	k += 54;				

	// --
	val.value = x;

	xx = (uint64)(( hx & 0x800fffff ) | ( k << 20 )) << 32;
	xx |= val.raw & 0x00000000ffffffff;
	val.raw = xx;
//	SET_HIGH_WORD( x, ( hx & 0x800fffff ) | ( k << 20 ) );
	
//	return x*twom54;
	return( val.value * twom54 );
}

// --
