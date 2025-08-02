
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

#include <Amy_Defines.h>	// Need AMYFUNC
#include <stdint.h>

/****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************/

struct __jmp_buf
{
	// Offset 0
	void *			ReturnAddress;

	// Offset 4
	uint32_t		CondCode;

	// Offset 8
	void *   		StackPointer;

	// Offset 12
	uint32_t		GPR[19];

	// Offset 88
	// Floating Points must be 8 byte alligned
	double			FPR[18];

	// Adding 8 bytes for Alignment
	// Handled internaly in setjmp/longjmp
	uint8_t			Padding[8];
};

// jmp_buf set to the same size as Newlib's
typedef uint8_t jmp_buf[ 512 ];

/****************************************************************************/

void	AMYFUNC _longjmp( jmp_buf, int );
void	AMYFUNC longjmp( jmp_buf, int );
void	AMYFUNC siglongjmp( jmp_buf, int );

int		AMYFUNC _setjmp( jmp_buf );
int		AMYFUNC setjmp( jmp_buf );
int		AMYFUNC sigsetjmp( jmp_buf );

/****************************************************************************/

#ifdef __cplusplus
}
#endif

/****************************************************************************/

#endif

