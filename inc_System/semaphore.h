
/*
** Based on The Open Group Base Specifications Issue 7
**
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2026 Rene W. Olsen
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

#ifndef AMYSYS_SEMAPHORE_H
#define AMYSYS_SEMAPHORE_H

#include <fcntl.h>
#include <sys/types.h>

AMY_EXTERN_C_BEGIN

/****************************************************************************/

typedef void *		sem_t;

#define SEM_FAILED	NULL

/****************************************************************************/

int		sem_close(		sem_t * );
int		sem_destroy(	sem_t * );
int		sem_getvalue(	sem_t *, int * );
int		sem_init(		sem_t *, int, unsigned int );
sem_t *	sem_open(		const char *, int, ... );
int		sem_post(		sem_t * );
int		sem_trywait(	sem_t * );
int		sem_unlink(		const char * );
int		sem_wait(		sem_t * );

/****************************************************************************/

AMY_EXTERN_C_END

#endif /* AMYSYS_SEMAPHORE_H */
