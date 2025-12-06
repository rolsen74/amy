
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

#ifndef AMYSYS_ISO646_H
#define AMYSYS_ISO646_H

AMY_EXTERN_C_BEGIN

/****************************************************************************/

#define and		&&
#define and_eq	&=
#define bitand	&
#define bitor	|
#define compl	~
#define not		!
#define not_eq	!=
#define or		||
#define or_eq	|=
#define xor		^
#define xor_eq	^=

/****************************************************************************/

AMY_EXTERN_C_END

#endif /* AMYSYS_ISO646_H */
