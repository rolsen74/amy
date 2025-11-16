
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

/* --------------------------------------------------------------------------
** Always include Amy_Features.h FIRST — this defines feature macros like
** _FILE_OFFSET_BITS and _TIME_BITS before any typedefs depend on them.
** -------------------------------------------------------------------------- 
*/

#include <Amy_Features.h>
#include <Amy_Defines.h>

/* -- */

#ifndef AMYSYS_STDARG_H
#define AMYSYS_STDARG_H

/****************************************************************************/

#if 1


#ifdef __amigaos4__
 #ifdef __GNUC__
  #include_next "stdarg.h"
 #else
  #error "Unknown compiler"
 #endif
#else
 #error "Unknown compiler"
#endif


#else

// Args on stack
typedef char *va_list;

#define va_start(	ap, last )				( ap = (va_list) ( & last + 1 ) )
#define va_arg(		ap, type )				( *(type *) (( ap += sizeof( type )) - sizeof( type )) )
#define va_end(		ap )					( ap = (va_list) 0 )
#define va_copy(	dst,src )				( (void) ((dst) = (src)) )


#endif

/****************************************************************************/

#endif

