
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include <proto/AmyCLib.h>

// --

void __attribute__((noreturn)) exit( int rc )
{
	IAmyCLib->stdlib_exit( rc );
	__builtin_unreachable();		// tell the compiler control never reaches here
}

// --
