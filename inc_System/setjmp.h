
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

#ifndef AMYSYS_SETJMP_H
#define AMYSYS_SETJMP_H

/****************************************************************************/

#include <Amy_Defines.h>	// Need AMY_EXTERN_C_BEGIN
#include <stdint.h>

/****************************************************************************/

struct __jmp_buf
{
	// Offset 0
	PTR				ReturnAddress;

	// Offset 4
	U32				CondCode;

	// Offset 8
	PTR		 		StackPointer;

	// Offset 12
	U32				GPR[19];

	// Offset 88
	// Floating Points must be 8 byte alligned
	U64				FPR[18];

	// Adding 8 bytes for Alignment
	// Handled internaly in setjmp/longjmp
	U8				Padding[8];
};

// jmp_buf set to the same size as Newlib's
typedef uint8_t jmp_buf[ 512 ];

/****************************************************************************/

AMY_EXTERN_C_BEGIN

void	_longjmp( jmp_buf, int );
void	longjmp( jmp_buf, int );
void	siglongjmp( jmp_buf, int );

int		_setjmp( jmp_buf );
int		setjmp( jmp_buf );
int		sigsetjmp( jmp_buf );

AMY_EXTERN_C_END

/****************************************************************************/

#endif

