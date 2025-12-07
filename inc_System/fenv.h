
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
// Default FP environment 

#define FE_DFL_ENV		((fenv_t *)NULL)

/****************************************************************************/
// Rounding modes

#define FE_DOWNWARD		0
#define FE_UPWARD		1
#define FE_TONEAREST	2
#define FE_TOWARDZERO	3

int	fegetround(			void );
int	fesetround(			int );
int	fetestexcept(		int );

/****************************************************************************/
// Exception flags

#define FE_DIVBYZERO	0x0001
#define FE_INEXACT		0x0002
#define FE_INVALID		0x0004
#define FE_OVERFLOW		0x0008
#define FE_UNDERFLOW	0x0010
#define FE_ALL_EXCEPT	( FE_DIVBYZERO | FE_INEXACT | FE_INVALID | FE_OVERFLOW | FE_UNDERFLOW )

typedef int fexcept_t;

int	feclearexcept(		int );
int	fegetexceptflag(	fexcept_t *, int );
int	feraiseexcept(		int );
int	fesetexceptflag(	const fexcept_t *, int );

/****************************************************************************/
// Environment save/restore

typedef int fenv_t;

int	fegetenv(			fenv_t * );
int	fesetenv(			const fenv_t * );
int	feholdexcept(		fenv_t * );
int	feupdateenv(		const fenv_t * );

/****************************************************************************/

AMY_EXTERN_C_END

#endif /* AMYSYS_FENV_H */
