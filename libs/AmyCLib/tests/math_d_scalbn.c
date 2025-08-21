
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include <proto/exec.h>
#include <math.h>
#include <stdio.h>

struct data
{
	double	xx;
	int		yy;
	double	zz;
	char *	name;
};

struct data mydata[] =
{
{ 2.0,		10,		2048.0,	"Test 1" },
{ 2048.0,	-10,	2.0,	"Test 2" },

{ 0,		0, 		0,		NULL },
};

int main( int argc, char **argv )
{
double val;
int error;
int pos;

	error = 10;

	pos = 0;

	while( mydata[pos].name )
	{
		val = scalbn( mydata[pos].xx, mydata[pos].yy );

		if ( val != mydata[pos].zz )
		{
			IExec->DebugPrintF( "math d scalbn test 1 '%s' - Failed\n", mydata[pos].name );
			goto bailout;
		}

		pos++;
	}

	error = 0;

bailout:

	return( error );
}

