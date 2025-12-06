
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

#ifndef AMYSYS_AMIGA_H
#define AMYSYS_AMIGA_H

//#include <proto/exec.h>

AMY_EXTERN_C_BEGIN

/****************************************************************************/

void NewList( struct List * );
void NewMinList( struct MinList * );

/****************************************************************************/

AMY_EXTERN_C_END

#endif /* AMYSYS_AMIGA_H */
