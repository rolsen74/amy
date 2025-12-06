
/*
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

#ifndef AMYSYS_FENV_H
#define AMYSYS_FENV_H

AMY_EXTERN_C_BEGIN

/****************************************************************************/

typedef struct
{
	// Represents the entire floating-point environment.
	char dummy[16];	 // Too be implemented later

} fenv_t;

typedef long int fexcept_t;

/****************************************************************************/

#define FE_DIVBYZERO	0x0001
#define FE_INEXACT		0x0002
#define FE_INVALID		0x0004
#define FE_OVERFLOW		0x0008
#define FE_UNDERFLOW	0x0010
#define FE_ALL_EXCEPT	( FE_DIVBYZERO | FE_INEXACT | FE_INVALID | FE_OVERFLOW | FE_UNDERFLOW )

enum
{
	FE_DOWNWARD,
	FE_UPWARD,
	FE_TONEAREST,
	FE_TOWARDZERO,
};

#define FE_DFL_ENV		AmyCLibPublic->ra_fenv

/****************************************************************************/

int	feclearexcept( int );
int	fegetenv( fenv_t * );
int	fegetexceptflag( fexcept_t *, int );
int	fegetround( void );
int	feholdexcept( fenv_t * );
int	feraiseexcept( int );
int	fesetenv( const fenv_t * );
int	fesetexceptflag( const fexcept_t *, int );
int	fesetround( int );
int	fetestexcept( int );
int	feupdateenv( const fenv_t * );

/****************************************************************************/

AMY_EXTERN_C_END

#endif /* AMYSYS_FENV_H */

// Public need's fenv_t
#include <Amy_Public.h>
