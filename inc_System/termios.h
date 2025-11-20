
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

#ifndef AMYSYS_TERMIOS_H
#define AMYSYS_TERMIOS_H

/****************************************************************************/

#include <sys/types.h>		/* For pid_t */

/****************************************************************************/

typedef unsigned char	cc_t;
typedef unsigned int	speed_t;
typedef unsigned int	tcflag_t;

/* Input flags */
#define BRKINT			0x0001
#define ICRNL			0x0002
#define IGNBRK			0x0004
#define IGNCR			0x0008
#define IGNPAR			0x0010
#define INLCR			0x0020
#define INPCK			0x0040
#define ISTRIP			0x0080
#define IXANY			0x0100
#define IXOFF			0x0200
#define IXON			0x0400
#define PARMRK			0x0800

/* Output flags */
#define OPOST			0x0001
#define ONLCR			0x0002
#define OCRNL			0x0004
#define ONOCR			0x0008
#define ONLRET			0x0010
#define OFILL			0x0020

/* Control flags */
#define CSTOPB			0x0001
#define CREAD			0x0002
#define PARENB			0x0004
#define PARODD			0x0008
#define HUPCL			0x0010
#define CLOCAL			0x0020

#define CSIZE			0x7000		/* Size Mask */
#define CS5				0x0000		/* 5 bits */
#define CS6				0x1000		/* 6 bits */
#define CS7				0x2000		/* 7 bits */
#define CS8				0x3000		/* 8 bits */

/* Local flags */
#define ECHO			0x0001
#define ECHOE			0x0002
#define ECHOK			0x0004
#define ECHONL			0x0008
#define ICANON			0x0010
#define IEXTEN			0x0020
#define ISIG			0x0040
#define NOFLSH			0x0080
#define TOSTOP			0x0100

/* Control characters */
#define VEOF			0
#define VEOL			1
#define VERASE			2
#define VINTR			3
#define VKILL			4
#define VMIN			5
#define VQUIT			6
#define VSTART			7
#define VSTOP			8
#define VSUSP			9
#define VTIME			10

/* Baud Rate */
#define B0				0
#define B50				50
#define B75				75
#define B110			110
#define B134			134
#define B150			150
#define B200			200
#define B300			300
#define B600			600
#define B1200			1200
#define B1800			1800
#define B2400			2400
#define B4800			4800
#define B9600			9600
#define B19200			19200
#define B38400			38400

/* tcserattr actions */
#define TCSANOW			0
#define TCSADRAIN		1
#define TCSAFLUSH		2

/* tcflush actions */
#define TCIFLUSH		0
#define TCIOFLUSH		1
#define TCOFLUSH		2

/* tcflow actions */
#define TCIOFF			0
#define TCION			1
#define TCOOFF			2
#define TCOON			3

/****************************************************************************/

#define NCCS			32

struct termios 
{
	tcflag_t	c_iflag;		/* Input flags */
	tcflag_t	c_oflag;		/* Output flags */
	tcflag_t	c_cflag;		/* Control flags */
	tcflag_t	c_lflag;		/* Local flags */
	cc_t		c_cc[NCCS];		/* Control characters */
};

/****************************************************************************/

AMY_EXTERN_C_BEGIN

speed_t		cfgetispeed( const struct termios * );
speed_t		cfgetospeed( const struct termios * );
int			cfsetispeed( struct termios *, speed_t );
int			cfsetospeed( struct termios *, speed_t );
int			tcdrain( int );
int			tcflow( int, int );
int			tcflush( int, int );
int			tcgetattr( int, struct termios * );
pid_t		tcgetsid( int );
int			tcsendbreak( int, int );
int			tcsetattr( int, int, const struct termios * );

AMY_EXTERN_C_END

/****************************************************************************/

#endif /* AMYSYS_TERMIOS_H */
