
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
**
******************************************************************************
** This file is part of Amy C Lib
*/

/****************************************************************************/

#include <string.h>

#include <proto/AmyCLib.h>

/****************************************************************************/

size_t strlen( const char *s )
{
size_t retval;

	retval = IAmyCLib -> string_strlen( s );

	return( retval );
}

/****************************************************************************/
