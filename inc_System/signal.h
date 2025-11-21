
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

#ifndef AMYSYS_SIGNAL_H
#define AMYSYS_SIGNAL_H

/****************************************************************************/

#include <sys/types.h>
#include <pthread.h>

/****************************************************************************/

#define SIGHUP		1			/* hangup */
#define SIGINT		2			/* interrupt */
#define SIGQUIT		3			/* quit */
#define SIGILL		4			/* illegal instruction */
#define SIGTRAP		5			/* trace trap */
#define SIGABRT		6			/* abort() */
#define SIGIOT		SIGABRT     /* compatibility */
#define SIGEMT		7			/* EMT instruction */
#define SIGFPE		8			/* floating point execption */
#define SIGKILL		9			/* kill */
#define SIGBUS		10			/* bus error */
#define SIGSEGV		11			/* segmentation violation */
#define SIGSYS		12			/* bad argument to system call */
#define SIGPIPE		13			/* write on pipe no one to read it */
#define SIGALRM		14			/* alarm clock */
#define SIGTERM		15			/* software termination signal from kill */
#define SIGURG		16			/* urgent condition on IO channel */
#define SIGSTOP		17			/* sendable stop signal not from tty */
#define SIGTSTP		18			/* stop signal from tty */
#define SIGCONT		19			/* continue a stopped process */
#define SIGCHLD		20			/* to parent on child stop or exit */
#define SIGTTIN		21			/* to readers prgrp upon background tty read */
#define SIGTTOU		22			/* like TTIN for output */
#define SIGIO		23			/* input/output possible signal */
#define SIGXCPU		24			/* exceeded CPU time limit */
#define SIGXFSZ		25			/* exceeded file size limit */
#define SIGVTALRM	26			/* virtual time alarm */
#define SIGPROF		27			/* profiling time alarm */
#define SIGWINCH	28			/* window size changes */
#define SIGINFO		29			/* information request */
#define SIGUSR1		30			/* user defined signal 1 */
#define SIGUSR2		31			/* user defined signal 2 */

#define SIGLAST		31

// This is a nonstandard Linux value
#define NSIG		32

/****************************************************************************/

typedef unsigned int sigset_t;
typedef unsigned int sig_atomic_t;
typedef void (*sig_t)(int);

/****************************************************************************/

struct sigaction
{
	void		(*sa_handler)(int);	/* signal handler */
	sigset_t	sa_mask;			/* signal mask to apply */
	int			sa_flags;			/* see signal options below */
};

#define SA_NOCLDSTOP	0x00000001
#define SA_NOCLDWAIT	0x00000002
#define SA_SIGINFO		0x00000004

#define SA_ONSTACK		0x08000000
#define SA_RESTART		0x10000000
#define SA_NODEFER		0x40000000
#define SA_RESETHAND	0x80000000

#define SA_NOMASK		SA_NODEFER
#define SA_ONESHOT		SA_RESETHAND

/****************************************************************************/

#define SIGEV_NONE				0
#define SIGEV_SIGNAL			1
#define SIGEV_SIGNAL_CODE		2
#define SIGEV_SIGNAL_THREAD		3
#define SIGEV_PULSE				4
#define SIGEV_UNBLOCK			5
#define SIGEV_INTR				6
#define SIGEV_THREAD			7

union sigval
{
	int				sival_int;
	void *			sival_ptr;
};

struct sigevent
{
	int				sigev_notify;

	union
	{
		int			sigev_signo;
		int			sigev_coid;
		int			sigev_id;
		void		(*sigev_notify_function)	( union sigval );
	};

	union sigval	sigev_value;

	union
	{
		struct
		{
			short	sigev_code;
			short	sigev_priority;
		};

		pthread_attr_t *	sigev_notify_attributres;
	};
};


/****************************************************************************/

#define SIG_BLOCK		1
#define SIG_UNBLOCK		2
#define SIG_SETMASK		3

/****************************************************************************/

struct sigvec
{
	void			(*sv_handler)();
	int				sv_mask;
	int				sv_flags;
};

#define SV_ONSTACK		SA_ONSTACK
#define SV_INTERRUPT	SA_RESTART
#define sv_onstack		sv_flags

/****************************************************************************/

struct signalstack
{
	char *			ss_base;
	int				ss_len;
	int				ss_onstack;
};

/****************************************************************************/

struct sigstack
{
	int				ss_onstack;
	char *			ss_sp;
};

/****************************************************************************/

struct sigcontext
{
	int				sc_onstack;
	int				sc_mask;
	int				sc_sp;
	int				sc_fp;
	int				sc_ap;
	int				sc_pc;
	int				sc_ps;
};

#define sigmask(m)		( 1 << ((m)-1))

#define SIG_DFL 		((void (*)(int))0)
#define SIG_IGN 		((void (*)(int))1)
#define SIG_HOLD		((void (*)(int))2)
#define SIG_ERR 		((void (*)(int))-1)

/****************************************************************************/

typedef struct 
{
	void *			ss_sp;
	size_t			ss_size;
	int				ss_flags;
} stack_t;

/****************************************************************************/

typedef struct
{
	int				si_signo;
	int				si_code;
	int				si_errno;
	pid_t			si_pid;
	uid_t			si_uid;
	void *			si_addr;
	int				si_status;
	long			si_band;
	union sigval	si_value;
} siginfo_t;

/****************************************************************************/

AMY_EXTERN_C_BEGIN

int		kill( pid_t, int );
int		killpg( pid_t, int );
void	psiginfo( const siginfo_t *, const char * );
void	psignal( int, const char * );
int		pthread_kill( pthread_t, int );
int		pthread_sigmask( int, const sigset_t *, sigset_t * );
int		raise( int );
int		sigaction( int, const struct sigaction *, struct sigaction * );
int		sigaddset( sigset_t *, int );
int		sigblock( int );
int		signalstack( const stack_t *, stack_t * );
int		sigdelset( sigset_t *, int );
int		sigemptyset( sigset_t * );
int		sigfillset( sigset_t * );
int		sighold( int );
int		sigignore( int );
int		siginterrupt( int, int );
int		sigismember( const sigset_t *, int );
//void	(*signal( int, void (*)(int)))(int);
void	signal( int, void * );
int		sigpause( int );
int		sigpending( sigset_t * );
int		sigprocmask( int, const sigset_t *, sigset_t * );
int		sigqueue( pid_t, int, union sigval );
int		sigrelse( int );
void	(*sigset( int, void (*)(int)))(int);
int		sigsuspend( const sigset_t * );
int		sigtimedwait( const sigset_t *, siginfo_t *, const struct timespec * );
int		sigwait( const sigset_t *, int * );
int		sigwaitinfo( const sigset_t *, siginfo_t * );

AMY_EXTERN_C_END

/****************************************************************************/

#endif

