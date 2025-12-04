
/*
** SPDX-License-Identifier: BSD-3-Clause
** Modifications (c) 2025 Rene W. Olsen
** Part of Amy C Lib
**
** Based on:
**
** Portable ISO 'C' (1994) runtime library for the Amiga computer
** Copyright (c) 2002-2015 by Olaf Barthel <obarthel (at) gmx.net>
** All rights reserved.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions
** are met:
**
**   - Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**
**   - Neither the name of Olaf Barthel nor the names of contributors
**     may be used to endorse or promote products derived from this
**     software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
** AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
** IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
** ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
** LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
** CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
** SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
** INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
** CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
** ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
** POSSIBILITY OF SUCH DAMAGE.
**
*/

// --

#include "src/All.h"

// --

S32 AMY_FUNC _generic__Priv_Convert_ED_to_Stat( struct AmyCLibIFace *Self, struct ExamineData *ed, struct stat *st )
{
time_t time;
mode_t mode;
S32 retval;
U32 flags;

	retval = -1;

	Self->string_memset( st, 0, sizeof( struct stat ));

	// --

	/**/ if ( EXD_IS_PIPE( ed ))
	{
		mode = S_IFIFO;
	}
	else if ( EXD_IS_SOCKET( ed ))
	{
		mode = S_IFSOCK;
	}
//	else if ( fib->fib_DirEntryType == ST_CONSOLE || fib->fib_DirEntryType == ST_NIL)
//	{
//		mode = S_IFCHR;
//	}
	else if ( EXD_IS_FILE( ed ))
	{
		mode = S_IFREG;
	}
	else // EXF_IS_DIR
	{
		mode = S_IFDIR;
	}

	// --

	flags = ed->Protection ^ (FIBF_READ|FIBF_WRITE|FIBF_EXECUTE|FIBF_DELETE);

	if ( flags & FIBF_READ )
	{
		mode |= S_IRUSR;
	}

	if (( flags & FIBF_WRITE ) && ( flags & FIBF_DELETE ))
	{
		mode |= S_IWUSR;
	}

	if ( flags & FIBF_EXECUTE )
	{
		mode |= S_IXUSR;
	}

	if ( flags & FIBF_GRP_READ )
	{
		mode |= S_IRGRP;
	}

	if (( flags & FIBF_GRP_WRITE ) && ( flags & FIBF_GRP_DELETE ))
	{
		mode |= S_IWGRP;
	}

	if ( flags & FIBF_GRP_EXECUTE )
	{
		mode |= S_IXGRP;
	}

	if ( flags & FIBF_OTR_READ )
	{
		mode |= S_IROTH;
	}

	if (( flags & FIBF_OTR_WRITE ) && ( flags & FIBF_OTR_DELETE ))
	{
		mode |= S_IWOTH;
	}

	if ( flags & FIBF_OTR_EXECUTE )
	{
		mode |= S_IXOTH;
	}

	// --

	if ( Self->Priv_Convert_DS_to_Time( & ed->Date, & time ) < 0 )
	{
		goto bailout;
	}

	if ( EXD_IS_FILE( ed ))
	{
		st->st_nlink = 1;
		st->st_size  = ed->FileSize;
	}
	else
	{
		st->st_nlink = 2;
	}

//	  st->st_ino	  = fib->fib_DiskKey;
//	  st->st_dev	  = (dev_t)file_system;
	st->st_mode		= mode;
	st->st_mtime	= time;
	st->st_atime	= time;
	st->st_ctime	= time;
	st->st_uid		= ed->OwnerUID;
	st->st_gid		= ed->OwnerGID;
	st->st_blksize	= 512;
	st->st_blocks	= ( st->st_size + st->st_blksize - 1 ) / st->st_blksize;

	retval = 0;

bailout:

	return( retval );
}

// --
