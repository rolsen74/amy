
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
**
******************************************************************************
** This file is part of Amy C Lib
*/

#ifndef AMYSYS_AMIGA_H
#define AMYSYS_AMIGA_H

/****************************************************************************/

#include <proto/exec.h>

#include <Amy_Defines.h>

/****************************************************************************/

AMY_EXTERN_C_BEGIN

void NewList( struct List * );
void NewMinList( struct MinList * );

AMY_EXTERN_C_END

/****************************************************************************/

#endif

