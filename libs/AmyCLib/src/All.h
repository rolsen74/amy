
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

#ifndef AMYLIB_ALL_H
#define AMYLIB_ALL_H

// --

#include <proto/dos.h>
#include <proto/exec.h>
#include <proto/AmyCLib.h>

#include <setjmp.h>

// --

#define LIBNAME		"AmyCLib.library"
#define VERSION		1
#define REVISION	1
#define DATE		"1.1.2025"
#define VERS		"AmyCLib.library 1.1"
#define VSTRING		"AmyCLib.library 1.1 (1.8.2025)\r\n"
#define VERSTAG		"\0$VER: AmyCLib.library 1.1 (1.8.2025)"

// Set Minimum crtbegin version number for opening AmyCLib
#define CRT_MIN_VERSION		((     1UL << 16 ) | (      0UL << 0 ))
//efine CRT_MIN_VERSION		(( VERSION << 16 ) | ( REVISION << 0 ))

// --

struct libBase
{
	struct Library		lib_Base;
	U16					lib_Pad;
	PTR					lib_SegList;

	// struct TimeRequest *		lib_TimeRequest;

	// int32						lib_Arc4Initialized;
	// struct SignalSemaphore		lib_Arc4Semaphore;
	// int32						lib_Arc4Count;
	// int32						lib_Arc4Stir;
	// struct arc4_stream			lib_Arc4Data;
	// struct Task *				lib_Arc4PID;
};

// --

struct libData
{
//	  struct ReactiveIFace *      IReactive;
	// struct RA_CIFace *	    IRA_C;

	// struct Library *		    SocketBase;
	// struct SocketIFace *	    ISocket;
	// struct Hook					SocketErrorHook;

	// // --

	// struct SignalSemaphore	    LocaleSemaphore;
	// struct Locale *			    LocaleTable[ NUM_LOCALES ];
	// struct Locale *			    LocaleDefault;

	// STRPTR					    ProgramName;
	// STRPTR					    ProgramNameBuffer;

	// char *					    Strtok_Last;

	// const unsigned char **		ArgArray;
	// struct DiskObject *			ArgDiskObject;

	// struct ArrayHeader			FileArray;
	// struct SignalSemaphore		FileSemaphore;

	// struct List 			    ExitHeader;
	// int							ExitReturnCode;
	jmp_buf						ExitJumpBuffer;
	// BOOL						ExitSet;

	// uint32					    Signals_BreakMask;
	// uint32						Signals_Blocked;
	// uint32						Signals_LocalBlocked;

	// struct Task *				SelectServerTask;
	// struct MsgPort *			SelectServerMsgPort;

	// unsigned int				Rand_Seed;

	// unsigned short				Rand48_Seed[3];
	// unsigned short				Rand48_Mult[3];
	// unsigned short				Rand48_Add;

	// struct DateStamp			TimeClock_StartTime;

	// struct SignalSemaphore		netdb_Semaphore;			// GetAddrInfo / GetNameInfo

	// struct SignalSemaphore		PThread_Semaphore;

	// int32						MemGuard;
	// struct List					MemPools;
	// struct SignalSemaphore		MemSemaphore;

	// // -- Function Flags

	// //	  int8						  SignalAllocated;
	// uint8					    Check_Abort_Enabled;
	// uint8						ExitBlocked;
	// // --	 uint8						 ATExitBlocked;
	// // --	 uint8						 UnixFileMode;
	// uint8						TrackFuncUsage;
	// uint8						Pad[2];


	// // -- Function Buffers, gets allocated when first used

	// struct lconv *				buf_LocaleConv;				// locale /localeconv
	// signal_handler_t *			buf_SignalHandlers;			// signal / signal
	// char *						buf_AscTime;				// time / asctime
	// struct tm *					buf_gmtime;					// time / gmtime
	// struct tm *					buf_LocalTime;				// time / localtime
	// char *						buf_Tmpnam;					// stdio / tmpnam
	// char *						buf_error_message;			// string / strerror_r
	// char *						buf_gai_strerror;			// netdb / gai_strerror
	// struct RACLibStruct	*		buf_PublicData;				//
	// char *						buf_progname;				// stdlib / [set/get]progname
	// char *                      buf_EnvBuffer;				// getenv
	// struct PT_ThreadInfo **		buf_PThreads;				// pthreads
	// struct random_struct *		buf_Random;					// stdlib / random,srandom,initstate
	// uint64 *					buf_FuncLogs;				// 
	
	// --
};

// --

void ROMFree( struct libBase *libBase );

extern const struct TagItem Main_Tags[];

U32 _manager_Obtain( struct LibraryManagerInterface *Self );
U32 _manager_Release( struct LibraryManagerInterface *Self );
PTR _manager_Open( struct LibraryManagerInterface *Self, U32 version );
PTR _manager_Close( struct LibraryManagerInterface *Self );
PTR _manager_Expunge( struct LibraryManagerInterface *Self );

U32 _main_Expunge( struct AmyCLibIFace *Self );

// --

#endif
