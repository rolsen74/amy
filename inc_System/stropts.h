
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

#ifndef AMYSYS_STROPTS_H
#define AMYSYS_STROPTS_H

#include <unistd.h>
#include <sys/types.h>

AMY_EXTERN_C_BEGIN

/****************************************************************************/

typedef int				t_scalar_t;
typedef unsigned int	t_uscalar_t;

#define I_PUSH			1
#define I_POP			2
#define I_LOOK			3
#define I_FLUSH			4
#define I_STR			5
#define I_SETSIG		6
#define I_GETSIG		7
#define I_FIND			8
#define I_PEEK			9
#define I_SRDOPT		10
#define I_GRDOPT		11
#define I_NREAD			12
#define I_FDINSERT		13
#define I_RECVFD		14
#define I_FLUSHBAND		15

/****************************************************************************/

struct bandinfo
{
	unsigned char	bi_pri;
	int				bi_flag;
};

struct strbuf
{
	int				maxlen;
	int				len;
	char *			buf;
};

struct strfdinsert
{
	struct strbuf	ctlbuf;
	struct strbuf	databuf;
	t_uscalar_t		flags;
	int				fildes;
	int				offset;
};

struct strrecvfd
{
	int				fda;
	uid_t			uid;
	gid_t			gid;
};

struct str_mlist
{
	char			l_name[32];
};

struct str_list
{
	int					sl_nmods;
	struct str_mlist *	sl_modlist;
};

/****************************************************************************/

int		isastream( int );
int		getmsg( int, struct strbuf *, struct strbuf *, int * );
int		getpmsg( int, struct strbuf *, struct strbuf *, int *, int * );
int		ioctl( int, int, ... );
int		putmsg( int, const struct strbuf *, const struct strbuf *, int );
int		putpmsg( int, const struct strbuf *, const struct strbuf *, int, int );
int		fattach( int, const char * );
int		fdetach( const char * );

/****************************************************************************/

AMY_EXTERN_C_END

#endif /* AMYSYS_STROPTS_H */
