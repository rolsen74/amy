
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

#ifndef AMYLIB_ALL_H
#define AMYLIB_ALL_H

#define ANYLIB_CLIB_PRIV_H

// --

#include <setjmp.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>

#include <proto/dos.h>
#include <proto/exec.h>
#include <proto/locale.h>
#include <proto/intuition.h>
#include <proto/utility.h>
#include <proto/AmyCLib.h>

#include <dos/obsolete.h>
#include <workbench/startup.h>

// --

#ifdef __DO_FUNCTION_LOG__

#include "_Main/Func_Log.h"
#define DOFUNCTIONLOG(x)		Self->Priv_Func_Log( x );

#else

#define DOFUNCTIONLOG(x)

#endif

// --

#ifdef __DO_FUNCTION_PRINT__

#define DOFUNCTIONPRINTF(x)		({x})

#else

#define DOFUNCTIONPRINTF(x)

#endif

// --

#ifdef DEBUG

#define DODEBUGPRINTF(x)		({x})

#else

#define DODEBUGPRINTF(x)

#endif

// --


// --

#define LIBNAME				"AmyCLib.library"
#define VERSION				1
#define REVISION			1
#define DATE				"1.1.2025"
#define VERS				"AmyCLib.library 1.1"
#define VSTRING				"AmyCLib.library 1.1 (1.8.2025)\r\n"
#define VERSTAG				"\0$VER: AmyCLib.library 1.1 (1.8.2025)"

// Set Minimum crtbegin version number for opening AmyCLib
#define CRT_MIN_VERSION		((     1UL << 16 ) | (      0UL << 0 ))
//efine CRT_MIN_VERSION		(( VERSION << 16 ) | ( REVISION << 0 ))

#define NUM_LOCALES			( LC_TIME - LC_ALL + 1 )

typedef void (*signal_handler_t)( int );
#define SIG_DFL 			((void (*)(int))0)
#define SIG_IGN 			((void (*)(int))1)
#define SIG_HOLD			((void (*)(int))2)
#define SIG_ERR 			((void (*)(int))-1)

#define BUFFER_MODE_FULL	_IOFBF
#define BUFFER_MODE_LINE	_IOLBF
#define BUFFER_MODE_NONE	_IONBF

// --

/* This is the difference (in seconds) between the Unix epoch (which began
   on January 1st, 1970) and the AmigaOS epoch (which began eight years
   later on January 1st 1978). */

#define UNIX_TIME_OFFSET	252460800

// --
// Array used for File Descriptors (FD)

struct ArrayNode
{
	PTR					Node;
//	  U32			  Flags;
};

struct ArrayHeader
{
	U32					Used;
	U32					Size;
	struct ArrayNode *	Nodes;
};

// --

struct ExitNode
{
	struct Node		Node;
	void			(*Function)(void);
};

// --

struct libBase
{
	struct Library		lib_Base;
	U16					lib_Pad;
	PTR					lib_SegList;

	// struct TimeRequest *		lib_TimeRequest;

	// S32						lib_Arc4Initialized;
	// struct SignalSemaphore		lib_Arc4Semaphore;
	// S32						lib_Arc4Count;
	// S32						lib_Arc4Stir;
	// struct arc4_stream			lib_Arc4Data;
	// struct Task *				lib_Arc4PID;
};

// --

struct libData
{
//	  struct ReactiveIFace *      IReactive;
	// struct AmyCLibIFace *	    IRA_C;

	// struct Library *		    SocketBase;
	// struct SocketIFace *	    ISocket;
	// struct Hook					SocketErrorHook;

	// --

	struct AmyTaskInfo			ATIData;

	U32							EnableMask;

	struct SignalSemaphore		LocaleSemaphore;
	struct Locale *				LocaleTable[ NUM_LOCALES ];
	struct Locale *				LocaleDefault;

	STR							ProgramName;
	STR							ProgramNameBuffer;

	// char *					    Strtok_Last;

	// const unsigned char **		ArgArray;
	// struct DiskObject *			ArgDiskObject;

	struct ArrayHeader			FD_Array;
	struct SignalSemaphore		FD_Semaphore;

	struct List					ExitHeader;
	int							ExitReturnCode;
	jmp_buf						ExitJumpBuffer;
	S32							ExitSet;

	U32							Signals_BreakMask;
	U32							Signals_Blocked;
	U32							Signals_LocalBlocked;

	STR							cli_ArgString;			// AllocVec

	// struct Task *				SelectServerTask;
	// struct MsgPort *			SelectServerMsgPort;

	unsigned int				Rand_Seed;

	// unsigned short				Rand48_Seed[3];
	// unsigned short				Rand48_Mult[3];
	// unsigned short				Rand48_Add;

	// struct DateStamp			TimeClock_StartTime;

	// struct SignalSemaphore		netdb_Semaphore;			// GetAddrInfo / GetNameInfo

	// struct SignalSemaphore		PThread_Semaphore;

	struct List					MemPools;
	struct SignalSemaphore		MemSemaphore;

	// // -- Function Flags

	// //	  int8						  SignalAllocated;
	U8							Check_Abort_Enabled;
	U8							ExitBlocked;
	// // --	 uint8						 ATExitBlocked;
	// // --	 uint8						 UnixFileMode;
	U8							TrackFuncUsage;
	// uint8						Pad[2];

	U8							Enable_Strings;
	U8							Enable_Memory;
	U8							Enable_File;
	U8							UserDataSet;

	// // -- Function Buffers, gets allocated when first used

	// struct lconv *				buf_LocaleConv;				// locale /localeconv
	signal_handler_t *			buf_SignalHandlers;			// signal / signal
	// char *						buf_AscTime;				// time / asctime
	struct tm *					buf_gmtime;					// time / gmtime
	struct tm *					buf_LocalTime;				// time / localtime
	// char *						buf_Tmpnam;					// stdio / tmpnam
	// char *						buf_error_message;			// string / strerror_r
	// char *						buf_gai_strerror;			// netdb / gai_strerror
	struct _AmyCLibPublic *		buf_PublicData;				//
	STR							buf_progname;				// stdlib / [set/get]progname
	// char *                      buf_EnvBuffer;				// getenv
	// struct PT_ThreadInfo **		buf_PThreads;				// pthreads
	// struct random_struct *		buf_Random;					// stdlib / random,srandom,initstate
	U64 *						buf_FuncLogs;				// 

	// --
};

// --

#define ID_MEM					0x937C1585
#define ID_POOL					0x4B7E7651
#define ID_FILE					0xA24ED2C8
#define ID_SOCKET				0xB3BD72E0
#define ID_SEMAPHORE			0x47BACBBA
#define ID_STRING				0x434CF945
#define ID_PRIVFILE				0x234658ab

struct MemStruct
{
	U32							ID;
	U32							Size;		// Memory size plus MemStruct (8)
};

struct MemPoolHeader
{
	struct Node					ph_Node;
	U32							ph_ID;
	U32							ph_Headers;
	U32							ph_UsedBytes;
	U32							ph_TotalBytes;
	U32							ph_PoolSize;
	struct List					ph_Pools;
	struct SignalSemaphore 		ph_Semaphore;
	S32							ph_Global;
};

struct PoolNode
{
	struct Node					pn_Node;
	PTR							pn_Memory;
	U32							pn_Size;
	struct PoolBlock *			pn_Blocks;
};

struct PoolBlock
{
	PTR							pb_Next;
	U32							pb_Free;
};

struct PoolMem
{
	U32							pm_ID;
	U32							pm_Size;
};

// --

struct FDInitStruct
{
	// --
	S32							is_Fildes;
	STR							is_Filename;
	// --
	U8							is_MustNotExists;		// O_EXCL flag
	U8							is_NonBlocking;			// O_NONBLOCK flag
	U8							is_CanCreate;			// O_CREAT flag
	U8							is_Append;
	U8							is_Trunc;				// O_TRUNC flag
	U8							is_Write;
	U8							is_Read;
	U8							is_Pad;
	// --
};

struct stat;
struct FileStruct;
struct PrivInterface
{
	void	( *pi_Close 	) ( struct AmyCLibIFace *, struct FileStruct *file );
	S64		( *pi_Read		) ( struct AmyCLibIFace *, struct FileStruct *file, PTR buf, S32 size );
	S64		( *pi_Write 	) ( struct AmyCLibIFace *, struct FileStruct *file, PTR buf, S32 size );
	S32		( *pi_Seek		) ( struct AmyCLibIFace *, struct FileStruct *file, S64 pos, S32 mode );
	S64		( *pi_GetPos	) ( struct AmyCLibIFace *, struct FileStruct *file );
	S32		( *pi_Examine	) ( struct AmyCLibIFace *, struct FileStruct *file, struct stat *stat );
};

// --

struct PrintStruct
{
	va_list						ps_Args;
	const char *				ps_Format;

	// -- File
	struct FileStruct *			ps_Stream;

	// -- Buffer
	char *						ps_Buffer;
	S32							ps_Size;

	// --
	S32							ps_Written;		// -1 == Error, or Written Bytes
};

// --

struct ScanStruct
{
	va_list						ss_Args;
	const char *				ss_Format;

	// -- File
	struct FileStruct *			ss_Stream;

	// -- Buffer
	const char *				ss_Buffer;

	// --
	S32							ss_Error;
	S32							ss_Handled;
};

// --

struct FileStruct
{
	// -- Public

	FILE						pf_Public;

	// -- Private

	struct PrivInterface		pf_Interface;
	U32							pf_StructID;

	U32							pf_FileType;						// See id's above

	S32							pf_ArrayPos;				// Array Pos number

	//	S64						pf_FilePosition;

	U8 *						pf_Buffer;					// Active Buffer
	S32							pf_BufferSize;				// Size of allocated buffer
	S32							pf_BufferPosition;
	S32							pf_BufferReadBytes;
	S32							pf_BufferWriteBytes;
	U8 *						pf_BufferCustom;			// Custom allocated buffer

	// STRPTR						pf_TempFileName;
	// BPTR						pf_TempDirLock;

	union 
	{
		BPTR					pf_File;
		long					pf_Socket;
	}							pf_Handle;

	struct SignalSemaphore		pf_Semaphore;

	S32							pf_Locks;				// Must Hold ' data->FileSemaphore '

	// --

	U8							pf_EOF_Reached;
	U8							pf_Read;
	U8							pf_Write;
	U8							pf_Error;
	// uint8				        pf_Temp;
	// uint8				        pf_No_Null;
	U8							pf_BufferMode;
	U8							pf_Expunge;				// FD has been marked for Deletion
	U8							pf_Append;				// Write happens at end of file
	// uint8					    pf_Created;			    //
	U8							pf_NonBlocking;
	U8							pf_IsInteractive;		// Is Console
	U8							pf_CachePosition;		// Seek possible
	U8							pf_BufferDefault;		// Default buffer for File Descriptor
	// uint8						pf_NoNul;				// Don't send NUL on this stream
	U8							pf_DontFreeHandle;
};

// --

void ROMFree( struct libBase *libBase );

extern const struct TagItem Main_Tags[];

U32 _manager_Obtain( struct LibraryManagerInterface *Self );
U32 _manager_Release( struct LibraryManagerInterface *Self );
PTR _manager_Open( struct LibraryManagerInterface *Self, U32 version );
PTR _manager_Close( struct LibraryManagerInterface *Self );
PTR _manager_Expunge( struct LibraryManagerInterface *Self );

U32 AMY_FUNC _Main_Expunge( struct AmyCLibIFace *Self );

// --

#endif
