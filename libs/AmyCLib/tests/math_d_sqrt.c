
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
	double	yy;
	char *	name;
};

struct data mydata[] =
{
{ 1.0,		1.0,	"Test 1" },
{ 4.0,		2.0,	"Test 2" },
{ 9.0,		3.0,	"Test 3" },
{ 16.0,		4.0,	"Test 4" },
{ 25.0,		5.0,	"Test 5" },
{ 36.0,		6.0,	"Test 6" },
{ 49.0,		7.0,	"Test 7" },
{ 64.0,		8.0,	"Test 8" },
{ 81.0,		9.0,	"Test 9" },
{ 100.0,	10.0,	"Test 10" },
{ 121.0,	11.0,	"Test 11" },
{ 144.0,	12.0,	"Test 12" },
{ 169.0,	13.0,	"Test 13" },
{ 196.0,	14.0,	"Test 14" },
{ 225.0,	15.0,	"Test 15" },
{ 256.0,	16.0,	"Test 16" },
{ 289.0,	17.0,	"Test 17" },
{ 324.0,	18.0,	"Test 18" },
{ 361.0,	19.0,	"Test 19" },
{ 400.0,	20.0,	"Test 20" },
{ 441.0,	21.0,	"Test 21" },
{ 484.0,	22.0,	"Test 22" },
{ 529.0,	23.0,	"Test 23" },
{ 576.0,	24.0,	"Test 24" },
{ 625.0,	25.0,	"Test 25" },
{ 676.0,	26.0,	"Test 26" },
{ 729.0,	27.0,	"Test 27" },
{ 784.0,	28.0,	"Test 28" },
{ 841.0,	29.0,	"Test 29" },
{ 900.0,	30.0,	"Test 30" },
{ 961.0,	31.0,	"Test 31" },
{ 1024.0,	32.0,	"Test 32" },
{ 1089.0,	33.0,	"Test 33" },
{ 1156.0,	34.0,	"Test 34" },
{ 1225.0,	35.0,	"Test 35" },
{ 1296.0,	36.0,	"Test 36" },
{ 1369.0,	37.0,	"Test 37" },
{ 1444.0,	38.0,	"Test 38" },
{ 1521.0,	39.0,	"Test 39" },
{ 1600.0,	40.0,	"Test 40" },
{ 1681.0,	41.0,	"Test 41" },
{ 1764.0,	42.0,	"Test 42" },
{ 1849.0,	43.0,	"Test 43" },
{ 1936.0,	44.0,	"Test 44" },
{ 2025.0,	45.0,	"Test 45" },
{ 2116.0,	46.0,	"Test 46" },
{ 2209.0,	47.0,	"Test 47" },
{ 2304.0,	48.0,	"Test 48" },
{ 2401.0,	49.0,	"Test 49" },
{ 2500.0,	50.0,	"Test 50" },
{ 2601.0,	51.0,	"Test 51" },
{ 2704.0,	52.0,	"Test 52" },
{ 2809.0,	53.0,	"Test 53" },
{ 2916.0,	54.0,	"Test 54" },
{ 3025.0,	55.0,	"Test 55" },
{ 3136.0,	56.0,	"Test 56" },
{ 3249.0,	57.0,	"Test 57" },
{ 3364.0,	58.0,	"Test 58" },
{ 3481.0,	59.0,	"Test 59" },
{ 3600.0,	60.0,	"Test 60" },
{ 3721.0,	61.0,	"Test 61" },
{ 3844.0,	62.0,	"Test 62" },
{ 3969.0,	63.0,	"Test 63" },
{ 4096.0,	64.0,	"Test 64" },
{ 4225.0,	65.0,	"Test 65" },
{ 4356.0,	66.0,	"Test 66" },
{ 4489.0,	67.0,	"Test 67" },
{ 4624.0,	68.0,	"Test 68" },
{ 4761.0,	69.0,	"Test 69" },
{ 4900.0,	70.0,	"Test 70" },
{ 5041.0,	71.0,	"Test 71" },
{ 5184.0,	72.0,	"Test 72" },
{ 5329.0,	73.0,	"Test 73" },
{ 5476.0,	74.0,	"Test 74" },
{ 5625.0,	75.0,	"Test 75" },
{ 5776.0,	76.0,	"Test 76" },
{ 5929.0,	77.0,	"Test 77" },
{ 6084.0,	78.0,	"Test 78" },
{ 6241.0,	79.0,	"Test 79" },
{ 6400.0,	80.0,	"Test 80" },
{ 6561.0,	81.0,	"Test 81" },
{ 6724.0,	82.0,	"Test 82" },
{ 6889.0,	83.0,	"Test 83" },
{ 7056.0,	84.0,	"Test 84" },
{ 7225.0,	85.0,	"Test 85" },
{ 7396.0,	86.0,	"Test 86" },
{ 7569.0,	87.0,	"Test 87" },
{ 7744.0,	88.0,	"Test 88" },
{ 7921.0,	89.0,	"Test 89" },
{ 8100.0,	90.0,	"Test 90" },
{ 8281.0,	91.0,	"Test 91" },
{ 8464.0,	92.0,	"Test 92" },
{ 8649.0,	93.0,	"Test 93" },
{ 8836.0,	94.0,	"Test 94" },
{ 9025.0,	95.0,	"Test 95" },
{ 9216.0,	96.0,	"Test 96" },
{ 9409.0,	97.0,	"Test 97" },
{ 9604.0,	98.0,	"Test 98" },
{ 9801.0,	99.0,	"Test 99" },
{ 10000.0,	100.0,	"Test 100" },

// Not sure what the exact result is.. the last digis is not verifyed
//{ 999.0,	 31.6069612585 58216,  "Test 101" },

{ 0,		0, 		NULL },
};

int main( int argc, char **argv )
{
double val;
double x;
int error;
int pos;

	error = 10;

	pos = 0;

	while( mydata[pos].name )
	{
		val = sqrt( mydata[pos].xx );

		if ( val != mydata[pos].yy )
		{
			IExec->DebugPrintF( "math d sqrt test 1 '%s' - Failed\n", mydata[pos].name );
			goto bailout;
		}

		pos++;
	}

	// --
	// If nan is given, then nan should be returned

	x = nan( NULL );

	val = sqrt( x );

	if ( isnan( val ) == FALSE )
	{
		IExec->DebugPrintF( "math d sqrt test 2 - Failed\n" );
		goto bailout;
	}

	// --
	// If Zero is given, then Zero is returned

	x = 0.0;

	val = sqrt( x );

	if ( val != x )
	{
		IExec->DebugPrintF( "math d sqrt test 3 - Failed\n" );
		goto bailout;
	}

	// --
	// If +Inf is given, then Inf should be returned
	double __inf(); // Internal function

	x = __inf();

	val = sqrt( x );

	if ( isinf( val ) == FALSE )
	{
		IExec->DebugPrintF( "math d sqrt test 4 - Failed\n" );
		goto bailout;
	}


	error = 0;

bailout:

	return( error );
}

