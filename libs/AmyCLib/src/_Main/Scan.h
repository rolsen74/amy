
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

#ifndef AMYLIB_SRC_MAIN_SCAN_H
#define AMYLIB_SRC_MAIN_SCAN_H

// --

enum myReadStat
{
	MRS_Okay,	// Read okay
	MRS_Error,	// Read failed
};

#define FLOATING_POINT

#define	BUF			513	/* Maximum length of numeric string. */

/*
 * Flags used during conversion.
 */

#undef MAXINT	// remove DOS define

#define	LONG		0x00001	/* l: long or double */
#define	LONGDBL		0x00002	/* L: long double */
#define	SHORT		0x00004	/* h: short */
#define	SHORTSHORT	0x00008	/* hh: 8 bit integer */
#define LLONG		0x00010	/* ll: long long (+ deprecated q: quad) */
#define	POINTER		0x00020	/* p: void * (as hex) */
#define	SIZEINT		0x00040	/* z: (signed) size_t */
#define	MAXINT		0x00080	/* j: intmax_t */
#define	PTRINT		0x00100	/* t: ptrdiff_t */
#define	NOSKIP		0x00200	/* [ or c: do not skip blanks */
#define	SUPPRESS	0x00400	/* *: suppress assignment */
#define	UNSIGNED	0x00800	/* %[oupxX] conversions */

/*
 * The following are used in numeric conversions only:
 * SIGNOK, HAVESIGN, NDIGITS, DPTOK, and EXPOK are for floating point;
 * SIGNOK, HAVESIGN, NDIGITS, PFXOK, and NZDIGITS are for integral.
 */
#define	SIGNOK		0x01000	/* +/- is (still) legal */
#define	HAVESIGN	0x02000	/* sign detected */
#define	NDIGITS		0x04000	/* no digits detected */

#define	DPTOK		0x08000	/* (float) decimal point is still legal */
#define	EXPOK		0x10000	/* (float) exponent (e+3, etc) still legal */

#define	PFXOK		0x08000	/* 0x prefix is (still) legal */
#define	NZDIGITS	0x10000	/* no zero digits detected */

/*
 * Conversion types.
 */
#define	CT_CHAR		0	/* %c conversion */
#define	CT_CCL		1	/* %[...] conversion */
#define	CT_STRING	2	/* %s conversion */
#define	CT_INT		3	/* integer, i.e., strtoimax or strtoumax */
#define	CT_FLOAT	4	/* floating, i.e., strtod */

#define u_char unsigned char
#define u_long unsigned long

// --

struct Intern
{
	S32			c;
	STR			fmt;
	S32			nread;
	S32			width;
	S32			suppress;		// Ignore arg
	S32			nassigned;		// Number of args handled
	S32			input_fail;
	va_list		args;

	STR			buffer;
	U32			bufferPos;

	FILE *stream;
	struct AmyCLibIFace *Self;
};

// --

#endif
