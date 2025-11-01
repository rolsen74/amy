
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

/* -- */

#ifndef AMYSYS_PROCESS_H
#define AMYSYS_PROCESS_H

/****************************************************************************/

#include <stdlib.h>
#include <stddef.h>

/****************************************************************************/
/* Compatibility mode flags (from DOS/Windows) */

#define P_WAIT		0
#define P_NOWAIT	1
#define P_OVERLAY	2
#define P_NOWAITO	3
#define P_DETACH	4

/****************************************************************************/

AMY_EXTERN_C_BEGIN

/* Stubs for spawn/exec APIs — can return -1 with ENOSYS */
int		execl(		const char *path, const char *arg0, ... );
int		execle(		const char *path, const char *arg0, ... );
int		execlp(		const char *file, const char *arg0, ... );
int		execvp(		const char *file, char *const argv[] );

int		spawnl(		int mode, const char *path, const char *arg0, ... );
int		spawnle(	int mode, const char *path, const char *arg0, ... );
int		spawnlp(	int mode, const char *file, const char *arg0, ... );
int		spawnlpe(	int mode, const char *file, const char *arg0, ... );
int		spawnv(		int mode, const char *path, const char *const argv[] );
int		spawnve(	int mode, const char *path, const char *const argv[], const char *const envp[] );

AMY_EXTERN_C_END

/****************************************************************************/

#endif /* AMYSYS_PROCESS_H */
