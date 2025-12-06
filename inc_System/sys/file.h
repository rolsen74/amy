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

#ifndef AMYSYS_SYS_FILE_H
#define AMYSYS_SYS_FILE_H

#include <fcntl.h>

AMY_EXTERN_C_BEGIN

/****************************************************************************/
/* Legacy BSD seek macros (compatibility) */

#ifndef L_SET
#define L_SET		SEEK_SET
#endif

#ifndef L_INCR
#define L_INCR		SEEK_CUR
#endif

#ifndef L_XTND
#define L_XTND		SEEK_END
#endif

/****************************************************************************/
/* File locking operation flags (BSD-style) */

#define LOCK_SH		1	/* shared lock */
#define LOCK_EX		2	/* exclusive lock */
#define LOCK_NB		4	/* don’t block */
#define LOCK_UN		8	/* unlock */

/****************************************************************************/

/* Optional stub for compatibility */
int flock( int fd, int operation );

/****************************************************************************/

AMY_EXTERN_C_END

#endif /* AMYSYS_SYS_FILE_H */
