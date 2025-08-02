
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
**
******************************************************************************
** This file is part of Amy C Lib
*/

#ifndef AMYSYS_FENV_H
#define AMYSYS_FENV_H 1

/****************************************************************************/

#include <Amy_Defines.h>	// Need AMYFUNC

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

// fix me for AmyCLib
// #define FE_DFL_ENV		& RACLibPublic->ra_fenv;  

/****************************************************************************/

AMY_EXTERN_C_BEGIN

int	AMYFUNC feclearexcept( int );
int	AMYFUNC fegetenv( fenv_t * );
int	AMYFUNC fegetexceptflag( fexcept_t *, int );
int	AMYFUNC fegetround( void );
int	AMYFUNC feholdexcept( fenv_t * );
int	AMYFUNC feraiseexcept( int );
int	AMYFUNC fesetenv( const fenv_t * );
int	AMYFUNC fesetexceptflag( const fexcept_t *, int );
int	AMYFUNC fesetround( int );
int	AMYFUNC fetestexcept( int );
int	AMYFUNC feupdateenv( const fenv_t * );

AMY_EXTERN_C_END

/****************************************************************************/

#endif

