
/*
** Based on The Open Group Base Specifications Issue 7
**
** SPDX-License-Identifier: BSD-3-Clause
** Modifications (c) 2025 Rene W. Olsen
** Part of Amy C Lib
**
** Based on:
**
**  Copyright (C) 2014 Szilard Biro
**
**  This software is provided 'as-is', without any express or implied
**  warranty.  In no event will the authors be held liable for any damages
**  arising from the use of this software.
**
**  Permission is granted to anyone to use this software for any purpose,
**  including commercial applications, and to alter it and redistribute it
**  freely, subject to the following restrictions:
**
**  1. The origin of this software must not be misrepresented; you must not
**     claim that you wrote the original software. If you use this software
**     in a product, an acknowledgment in the product documentation would be
**     appreciated but is not required.
**  2. Altered source versions must be plainly marked as such, and must not be
**     misrepresented as being the original software.
**  3. This notice may not be removed or altered from any source distribution.
**
*/

#ifndef AMYSYS_PTHREAD_H
#define AMYSYS_PTHREAD_H

/****************************************************************************/

#include <Amy_Defines.h>	// Need AMY_EXTERN_C_BEGIN

#include <proto/exec.h>
#include <sys/types.h>
#include <time.h>
#include <sched.h>

/****************************************************************************/

//#define NULL_MINLIST {0, 0, 0}
//#define NULL_MINNODE {0, 0}
//#define NULL_SEMAPHOREREQUEST {NULL_MINNODE, 0}
//#define NULL_SEMAPHORE {NULL_MINNODE, 0, NULL_MINLIST, NULL_SEMAPHOREREQUEST, 0, 0}

//--#define PTHREAD_PRIO_NONE				0
//--#define PTHREAD_PRIO_INHERIT			1
//--#define PTHREAD_PRIO_PROTECT			2

/****************************************************************************/

//
// POSIX pthread types
//

typedef unsigned int pthread_t;
typedef unsigned int pthread_key_t;

//
// POSIX thread attribute values
//

#define PTHREAD_CREATE_JOINABLE       0
#define PTHREAD_CREATE_DETACHED       1

#define PTHREAD_INHERIT_SCHED         0
#define PTHREAD_EXPLICIT_SCHED        1

#define PTHREAD_SCOPE_PROCESS         0
#define PTHREAD_SCOPE_SYSTEM          1

#define PTHREAD_CANCEL_ENABLE         0
#define PTHREAD_CANCEL_DISABLE        1

#define PTHREAD_CANCEL_ASYNCHRONOUS   0
#define PTHREAD_CANCEL_DEFERRED       1

#define PTHREAD_PROCESS_PRIVATE       0
#define PTHREAD_PROCESS_SHARED        1

/****************************************************************************/

//
// Threads
//

//struct pthread_attr
//{
//    void *stackaddr;
//    size_t stacksize;
//    int detachstate;
//    struct sched_param param;
//    int inheritsched;
//    int contentionscope;
//};

typedef void *	pthread_attr_t;

#define PTHREAD_CANCELED              ((void *)-1)

/****************************************************************************/

//
// Once key
//

//struct pthread_once
//{
//	  volatile int done;
//	  int started;
//	  int lock;
//};

typedef int pthread_once_t;

#define PTHREAD_ONCE_INIT	0

/****************************************************************************/

//
// Mutex
//

#define PTHREAD_MUTEX_NORMAL     0
#define PTHREAD_MUTEX_RECURSIVE  1
#define PTHREAD_MUTEX_ERRORCHECK 2
#define PTHREAD_MUTEX_DEFAULT    PTHREAD_MUTEX_NORMAL

//--#define PTHREAD_MUTEX_ROBUST			3
//--#define PTHREAD_MUTEX_STALLED			4

//--struct pthread_mutexattr
//--{
//--    int pshared;
//--    int kind;
//--};

typedef void *	pthread_mutexattr_t;

//--struct pthread_mutex
//--{
//--    int kind;
//--    struct SignalSemaphore semaphore;
//--    int incond;
//--};

typedef void *	pthread_mutex_t;

#define PTHREAD_MUTEX_INITIALIZER		NULL

//#define PTHREAD_RECURSIVE_MUTEX_INITIALIZER {PTHREAD_MUTEX_RECURSIVE, NULL_SEMAPHORE}
//#define PTHREAD_ERRORCHECK_MUTEX_INITIALIZER {PTHREAD_MUTEX_ERRORCHECK, NULL_SEMAPHORE}

/****************************************************************************/

//--struct pthread_condattr
//--{
//--    int pshared;
//--};
//--
//--typedef struct pthread_condattr pthread_condattr_t;
typedef void *	pthread_condattr_t;

//--struct pthread_cond
//--{
//--    int pad1;
//--    struct SignalSemaphore semaphore;
//--    struct MinList waiters;
//--};
//--
//--typedef struct pthread_cond pthread_cond_t;
typedef void *	pthread_cond_t;

//--#define PTHREAD_COND_INITIALIZER {0, NULL_SEMAPHORE, NULL_MINLIST}
#define PTHREAD_COND_INITIALIZER 		NULL

/****************************************************************************/

//
// Barriers
//

//--#define PTHREAD_BARRIER_SERIAL_THREAD 1
//--
//--struct pthread_barrierattr
//--{
//--    int pshared;
//--};
//--
//--typedef struct pthread_barrierattr pthread_barrierattr_t;
typedef void *	pthread_barrierattr_t;

//--struct pthread_barrier
//--{
//--    unsigned int curr_height;
//--    unsigned int total_height;
//--    pthread_cond_t breeched;
//--    pthread_mutex_t lock;
//--};

//--typedef struct pthread_barrier pthread_barrier_t;
typedef void *	pthread_barrier_t;

/****************************************************************************/

//
// Read-write locks
//

//--struct pthread_rwlockattr
//--{
//--    int pshared;
//--};
//--
//--typedef struct pthread_rwlockattr pthread_rwlockattr_t;
typedef void *	pthread_rwlockattr_t;

//--struct pthread_rwlock
//--{
//--    struct SignalSemaphore semaphore;
//--};
//--
//--typedef struct pthread_rwlock pthread_rwlock_t;
typedef void *	pthread_rwlock_t;

//--#define PTHREAD_RWLOCK_INITIALIZER {NULL_SEMAPHORE}
#define PTHREAD_RWLOCK_INITIALIZER 		NULL

/****************************************************************************/

//
// Spinlocks
//

typedef void *	pthread_spinlock_t;

#define PTHREAD_SPINLOCK_INITIALIZER	NULL

/****************************************************************************/

AMY_EXTERN_C_BEGIN

int			pthread_atfork( void (*)(void), void (*)(void), void (*)(void) );
int			pthread_attr_destroy( pthread_attr_t * );
int			pthread_attr_getdetachstate( const pthread_attr_t *, int * );
int			pthread_attr_getguardsize( const pthread_attr_t *, size_t * );
int			pthread_attr_getinheritsched( const pthread_attr_t *, int * );
int			pthread_attr_getschedparam( const pthread_attr_t *, struct sched_param * );
int			pthread_attr_getschedpolicy( const pthread_attr_t *, int * );
int			pthread_attr_getscope( const pthread_attr_t *, int * );
int			pthread_attr_getstack( const pthread_attr_t *, void **, size_t * );
int			pthread_attr_getstacksize( const pthread_attr_t *, size_t * );
int			pthread_attr_init( pthread_attr_t * );
int			pthread_attr_setdetachstate( pthread_attr_t *, int );
int			pthread_attr_setguardsize( pthread_attr_t *, size_t );
int			pthread_attr_setinheritsched( pthread_attr_t *, int );
int			pthread_attr_setschedparam( pthread_attr_t *, const struct sched_param * );
int			pthread_attr_setschedpolicy( pthread_attr_t *, int );
int			pthread_attr_setscope( pthread_attr_t *, int );
int			pthread_attr_setstack( pthread_attr_t *, void *, size_t );
int			pthread_attr_setstacksize( pthread_attr_t *, size_t );
int			pthread_barrier_destroy( pthread_barrier_t * );
int			pthread_barrier_init( pthread_barrier_t *, const pthread_barrierattr_t *, unsigned );
int			pthread_barrier_wait( pthread_barrier_t * );
int			pthread_barrierattr_destroy( pthread_barrierattr_t * );
int			pthread_barrierattr_getpshared( const pthread_barrierattr_t *, int * );
int			pthread_barrierattr_init( pthread_barrierattr_t * );
int			pthread_barrierattr_setpshared( pthread_barrierattr_t *, int );
int			pthread_cancel( pthread_t );
void		pthread_cleanup_pop( int );
void		pthread_cleanup_push( void (*)(void *), void * );
int			pthread_cond_broadcast( pthread_cond_t * );
int			pthread_cond_destroy( pthread_cond_t * );
int			pthread_cond_init( pthread_cond_t *, const pthread_condattr_t * );
int			pthread_cond_signal( pthread_cond_t * );
int			pthread_cond_timedwait( pthread_cond_t *, pthread_mutex_t *, const struct timespec * );
int			pthread_cond_wait( pthread_cond_t *, pthread_mutex_t * );
int			pthread_condattr_destroy( pthread_condattr_t * );
int			pthread_condattr_getclock( const pthread_condattr_t *, clockid_t * );
int			pthread_condattr_getpshared( const pthread_condattr_t *, int * );
int			pthread_condattr_init( pthread_condattr_t * );
int			pthread_condattr_setclock( pthread_condattr_t *, clockid_t );
int			pthread_condattr_setpshared( pthread_condattr_t *, int );
int			pthread_create( pthread_t *, const pthread_attr_t *, void * (*)(void *), void * );
int			pthread_detach( pthread_t );
int			pthread_equal( pthread_t, pthread_t );
void		pthread_exit( void * );
int			pthread_getconcurrency( void );
int			pthread_getcpuclockid( pthread_t, clockid_t );
int			pthread_getschedparam( pthread_t, int *, struct sched_param * );
void *		pthread_getspecific( pthread_key_t );
int			pthread_join( pthread_t, void ** );
int			pthread_key_create( pthread_key_t *, void (*)(void *) );
int			pthread_key_delete( pthread_key_t );
int			pthread_mutex_consistent( pthread_mutex_t * );
int			pthread_mutex_destroy( pthread_mutex_t * );
int			pthread_mutex_getprioceiling( const pthread_mutex_t *, int * );
int			pthread_mutex_init( pthread_mutex_t *, const pthread_mutexattr_t * );
int			pthread_mutex_lock( pthread_mutex_t * );
int			pthread_mutex_setprioceiling( pthread_mutex_t *, int, int * );
int			pthread_mutex_timedlock( pthread_mutex_t *, const struct timespec * );
int			pthread_mutex_trylock( pthread_mutex_t * );
int			pthread_mutex_unlock( pthread_mutex_t * );
int			pthread_mutexattr_destroy( pthread_mutexattr_t * );
int			pthread_mutexattr_getprioceiling( const pthread_mutexattr_t *, int * );
int			pthread_mutexattr_getprotocol( const pthread_mutexattr_t *, int * );
int			pthread_mutexattr_getpshared( const pthread_mutexattr_t *, int * );
int			pthread_mutexattr_getrobust( const pthread_mutexattr_t *, int * );
int			pthread_mutexattr_gettype( const pthread_mutexattr_t *, int * );
int			pthread_mutexattr_init( pthread_mutexattr_t * );
int			pthread_mutexattr_setprioceiling( pthread_mutexattr_t *, int );
int			pthread_mutexattr_setprotocol( pthread_mutexattr_t *, int );
int			pthread_mutexattr_setpshared( pthread_mutexattr_t *, int );
int			pthread_mutexattr_setrobust( pthread_mutexattr_t *, int );
int			pthread_mutexattr_settype( pthread_mutexattr_t *, int );
int			pthread_once( pthread_once_t *, void (*)(void) );
int			pthread_rwlock_destroy( pthread_rwlock_t * );
int			pthread_rwlock_init( pthread_rwlock_t *, const pthread_rwlockattr_t * );
int			pthread_rwlock_rdlock( pthread_rwlock_t * );
int			pthread_rwlock_timedrdlock( pthread_rwlock_t *, const struct timespec * );
int			pthread_rwlock_timedwrlock( pthread_rwlock_t *, const struct timespec * );
int			pthread_rwlock_tryrdlock( pthread_rwlock_t * );
int			pthread_rwlock_trywrlock( pthread_rwlock_t * );
int			pthread_rwlock_unlock( pthread_rwlock_t * );
int			pthread_rwlock_wrlock( pthread_rwlock_t * );
int			pthread_rwlockattr_destroy( pthread_rwlockattr_t * );
int			pthread_rwlockattr_getpshared( const pthread_rwlockattr_t *, int * );
int			pthread_rwlockattr_init( pthread_rwlockattr_t * );
int			pthread_rwlockattr_setpshared( pthread_rwlockattr_t *, int );
pthread_t	pthread_self( void );
int			pthread_setcancelstate( int, int * );
int			pthread_setcanceltype( int, int * );
int			pthread_setconcurrency( int );
int			pthread_setschedparam( pthread_t, int, const struct sched_param * );
int			pthread_setschedprio( pthread_t, int );
int			pthread_setspecific( pthread_key_t, const void * );
int			pthread_spin_destroy( pthread_spinlock_t * );
int			pthread_spin_init( pthread_spinlock_t *, int );
int			pthread_spin_lock( pthread_spinlock_t * );
int			pthread_spin_trylock( pthread_spinlock_t * );
int			pthread_spin_unlock( pthread_spinlock_t * );
void		pthread_testcancel( void );

AMY_EXTERN_C_END

/****************************************************************************/

#endif


