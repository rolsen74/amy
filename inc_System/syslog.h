
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

#ifndef AMYSYS_SYSLOG_H
#define AMYSYS_SYSLOG_H

/****************************************************************************/

#include <stdarg.h>
#include <stddef.h> 

/****************************************************************************/

#define LOG_EMERG			0		// System is unusable
#define LOG_ALERT			1		// Action must be taken immediately
#define LOG_CRIT			2		// Critical conditions
#define LOG_ERR				3		// Error conditions
#define LOG_WARNING			4		// Warning conditions
#define LOG_NOTICE			5		// Normal but signifcant condition
#define LOG_INFO			6		// Informational
#define LOG_DEBUG			7		// Debug level messages

#define LOG_PRIMASK			0x07	// Mask to extract priority part (internal)
#
#define LOG_PRI(p)				((p) & LOG_PRIMASK )
#define LOG_MAKEPRI(fac, pri)	((fac) | (pri))

/****************************************************************************/

// Facility codes
#define	LOG_KERN			( 0 << 3 )		// Kernel messages
#define LOG_USER			( 1 << 3 )		// Random user-level messages
#define LOG_MAIL			( 2 << 3 )		// Mail system
#define LOG_DAEMON			( 3 << 3 )		// System daemons
#define LOG_AUTH			( 4 << 3 )		//
#define LOG_SYSLOG			( 5 << 3 )		//
#define LOG_LPR				( 6 << 3 )		//
#define LOG_NEWS			( 7 << 3 )		//
#define LOG_UUCP			( 8 << 3 )		//
#define LOG_CRON			( 9 << 3 )		//
#define LOG_AUTHPRIV		( 10 << 3 )		//
#define LOG_FTP				( 11 << 3 )		//

// Other codes through 15 reserved for system use
#define LOG_LOCAL0			( 16 << 3 )		//
#define LOG_LOCAL1			( 17 << 3 )		//
#define LOG_LOCAL2			( 18 << 3 )		//
#define LOG_LOCAL3			( 19 << 3 )		//
#define LOG_LOCAL4			( 20 << 3 )		//
#define LOG_LOCAL5			( 21 << 3 )		//
#define LOG_LOCAL6			( 22 << 3 )		//
#define LOG_LOCAL7			( 23 << 3 )		//

#define LOG_NFACILITIES		24
#define LOG_FACMASK			0x03f8

#define LOG_FAC(p)			(((p) & LOG_FACMASK ) >> 3 )

/****************************************************************************/

// Arguments to setlogmask
#define LOG_MASK(pri)		( 1 << (pri))
#define LOG_UPTO(pri)		(( 1 << ((pri)+1)) - 1 )

// Options for openlog
#define LOG_PID				0x01
#define LOG_CONS			0x02
#define LOG_ODELAY			0x04
#define LOG_NDELAY			0x08
#define LOG_NOWAIT			0x10
#define LOG_PERROR			0x20

/****************************************************************************/

AMY_EXTERN_C_BEGIN

void	syslog( int, const char *, ... );
void	vsyslog( int, const char *, va_list );
void	openlog( const char *, int, int );
void	closelog( void );
int		setlogmask( int );

AMY_EXTERN_C_END

/****************************************************************************/

#endif
