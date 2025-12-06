
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

#ifndef AMYSYS_SYS_PARAM_H
#define AMYSYS_SYS_PARAM_H

AMY_EXTERN_C_BEGIN

/****************************************************************************/

#define NBBY			8
#define setbit(x, y)	( (x)[(y)/NBBY] |=   1U << ((y) % NBBY))
#define clrbit(x, y)	( (x)[(y)/NBBY] &= ~(1U << ((y) % NBBY)))
#define isset(x, y)		(((x)[(y)/NBBY] &   (1U << ((y) % NBBY))) != 0)
#define isclr(x, y)		(((x)[(y)/NBBY] &   (1U << ((y) % NBBY))) == 0)

#define roundup(x, y)	((((x) + ((y) - 1)) / (y)) * (y))
#define howmany(x, y)	(( (x) + ((y) - 1)) / (y))

/****************************************************************************/

AMY_EXTERN_C_END

#endif /* AMYSYS_SYS_PARAM_H */
