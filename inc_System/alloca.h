
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
**
******************************************************************************
** This file is part of Amy C Lib
*/

#ifndef AMYSYS_ALLOCA_H
#define AMYSYS_ALLOCA_H

/****************************************************************************/

#undef alloca

#define	alloca(size)		__builtin_alloca(size)

/****************************************************************************/

#endif

