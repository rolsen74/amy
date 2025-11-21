
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
#include <Amy_Public.h>

/* -- */

#ifndef AMYSYS_NETDB_H
#define AMYSYS_NETDB_H

/****************************************************************************/

#include <inttypes.h>
#include <netinet/in.h>
#include <sys/socket.h>

/****************************************************************************/

#define h_errno		AmyCLibPublic->ra_h_ErrNo

/****************************************************************************/

struct hostent
{
	char *		h_name;
	char **		h_aliases;
	int			h_addrtype;
	int			h_length;
	char **		h_addr_list;
};

#define h_addr	h_addr_list[0]

struct netent
{
	char *		n_name;
	char **		n_aliases;
	int			n_addrtype;
	uint32_t	n_net;
};

struct protoent
{
	char *		p_name;
	char **		p_aliases;
	int			p_proto;
};

struct servent
{
	char *		s_name;
	char **		s_aliases;
	int			s_port;
	char *		s_proto;
};

struct addrinfo
{
	int					ai_flags;
	int					ai_family;
	int					ai_socktype;
	int					ai_protocol;
	socklen_t			ai_addrlen;
	struct sockaddr *	ai_addr;
	char *				ai_canonname;
	struct addrinfo *	ai_next;
};

#define AI_PASSIVE			0x0001
#define AI_CANONNAME		0x0002
#define AI_NUMERICHOST		0x0004
#define AI_V4MAPPED			0x0008
#define AI_ALL				0x0010
#define AI_ADDRCONFIG		0x0020
#define AI_NUMERICSERV		0x0400

#define NI_NOFQDN			0x0001
#define NI_NUMERICHOST		0x0002
#define NI_NAMEREQD			0x0004
#define NI_NUMERICSERV		0x0008
#define NI_DGRAM			0x0010
#define NI_WITHSCOPEID		0x0020
#define NI_NUMERICSCOPE		0x0040

#define NI_MAXHOST			256
#define NI_MAXSERV			32


#define EAI_ADDRFAMILY		1
#define EAI_AGAIN			2
#define EAI_BADFLAGS		3
#define EAI_FAIL			4
#define EAI_FAMILY			5
#define EAI_MEMORY			6
#define EAI_NODATA			7
#define EAI_NONAME			8
#define EAI_SERVICE			9
#define EAI_SOCKTYPE		10
#define EAI_SYSTEM			11
#define EAI_BADHINTS		12
#define EAI_PROTOCOL		13
#define EAI_OVERFLOW		14
#define EAI_MAX				15

#define NETDB_INTERNAL		-1
#define NETDB_SUCCESS		0
#define NO_DATA				4
#define NO_ADDRESS			NO_DATA
#define NO_RECOVERY			3
#define TRY_AGAIN			2
#define HOST_NOT_FOUND		1

/****************************************************************************/

AMY_EXTERN_C_BEGIN

void				endhostent( void );
void				endnetent( void );
void				endprotoent( void );
void				endservent( void );
void				freeaddrinfo( struct addrinfo * );
const char *		gai_strerror( int );
int					getaddrinfo( const char *, const char *,const struct addrinfo *, struct addrinfo ** );
struct hostent *	gethostbyaddr( const void *, socklen_t, int );
struct hostent *	gethostbyname( const char * );
struct hostent *	gethostent( void );
int					getnameinfo( const struct sockaddr *, socklen_t, char *, socklen_t, char *, socklen_t, int );
struct netent *		getnetbyaddr( uint32_t, int );
struct netent *		getnetbyname( const char * );
struct netent *		getnetent( void );
struct protoent *	getprotobyname( const char * );
struct protoent *	getprotobynumber( int );
struct protoent *	getprotoent( void );
struct servent *	getservbyname( const char *, const char * );
struct servent *	getservbyport( int, const char * );
struct servent *	getservent( void );
void				sethostent( int );
void				setnetent( int );
void				setprotoent( int );
void				setservent( int );

AMY_EXTERN_C_END

/****************************************************************************/

#endif

