
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

#include "Print_Option_c.c"
#include "Print_Option_d.c"
#include "Print_Option_n.c"
#include "Print_Option_o.c"
#include "Print_Option_s.c"
#include "Print_Option_u.c"
#include "Print_Option_x.c"
#include "Print_Read_Size.c"
#include "Print_Write_Char.c"
#include "Print_Write_Fill.c"
#include "Print_Write_String.c"

// --

void AMYFUNC _generic__Priv_Print( struct AmyCLibIFace *Self, struct PrintStruct *ps )
{
enum myWriteStat stat;
struct Intern in;
S32 retval;
S32 val;

	retval = -1;

	// --

	Self->Priv_Check_Abort();

	Self->string_memset( & in, 0, sizeof( in ));

	// -- Validate Input

	if ( ! ps )
	{
		#ifdef DEBUG
		IExec->DebugPrintF( "%s:%04d: Error\n", __FILE__, __LINE__ );
		#endif
		goto bailout;
	}

	if ( ps->ps_Stream )
	{
		Self->stdio_flockfile( ps->ps_Stream );

		if ( ! ps->ps_Stream->pf_Write )
		{
			#ifdef DEBUG
			IExec->DebugPrintF( "%s:%04d: Stream not writeable\n", __FILE__, __LINE__ );
			#endif
			goto bailout;
		}
	}

	if ( ! ps->ps_Format )
	{
		#ifdef DEBUG
		IExec->DebugPrintF( "%s:%04d: Error\n", __FILE__, __LINE__ );
		#endif
		goto bailout;
	}

	if ( ps->ps_Size < 0 )
	{
		#ifdef DEBUG
		IExec->DebugPrintF( "%s:%04d: Error\n", __FILE__, __LINE__ );
		#endif
		goto bailout;
	}

	// -- Reset values

	in.Self = Self;
	ps->ps_Written = 0;

	// --
	// if Size == 0, then we count bytes

	if ( ps->ps_Size )
	{
		// Make space for NUL char
		ps->ps_Size--;

		if ( ps->ps_Size < 0 )
		{
			#ifdef DEBUG
			IExec->DebugPrintF( "%s:%04d: Error\n", __FILE__, __LINE__ );
			#endif
			goto bailout;
		}
	}

	while( TRUE )
	{
		// if Size == 0, then we count bytes
		if (( ps->ps_Size ) && ( ps->ps_Size <= ps->ps_Written ))
		{
			break;
		}

		in.c = *ps->ps_Format++;

		if ( ! in.c )
		{
			break;
		}

		if ( in.c != '%' )
		{
			stat = my_writechar( ps, & in, in.c );

			if ( stat == MWS_Error )
			{
				#ifdef DEBUG
				IExec->DebugPrintF( "%s:%04d: Error\n", __FILE__, __LINE__ );
				#endif
				goto bailout;
			}

			if ( stat == MWS_Full )
			{
				// Buffer full, we are done
				goto done;
			}

			continue;
		}

		// rwo - not sure where to put this
		in.FORMATF_IsNegative = 0;

		/* If a string of digits, terminated by a '$' character appears here,
			* it indicates which argument should be accessed. We evaluate this
			* data but for now will ignore it altogether.
			*/

		in.argument_number = 0;
		in.argument_digits = 0;

		for( S32 i=0 ; ps->ps_Format[i] != '\0' ; i++ )
		{
			if ( ps->ps_Format[i] == '$' )
			{
				if ( in.argument_digits > 0 )
				{
					ps->ps_Format = & ps->ps_Format[ i + 1 ];
				}
				break;
			}
			else if (( '0' <= ps->ps_Format[i] ) && ( ps->ps_Format[i] <= '9' ))
			{
				in.argument_number = ( 10 * in.argument_number ) + ( ps->ps_Format[i] - '0' );

				in.argument_digits++;
			}
			else
			{
				break;
			}
		}

		/*
		** Collect the flags: left justification, sign, space,
		** alternate format, fill character.
		*/

		in.Fill_Character  = ' ';

		while( TRUE )
		{
			in.c = *ps->ps_Format;

			/**/ if ( in.c == '-' )
			{
				in.FORMATF_LeftJustified = 1;
				ps->ps_Format++;
			}
			else if ( in.c == '+' )
			{
				in.FORMATF_ProduceSign = 1;
				ps->ps_Format++;
			}
			else if ( in.c == ' ' )
			{
				in.FORMATF_ProduceSpace = 1;
				ps->ps_Format++;
			}
			else if ( in.c == '#' )
			{
				in.FORMATF_AlternateConversion = 1;
				ps->ps_Format++;
			}
			else if ( in.c == '0' )
			{
				in.Fill_Character = '0';
				ps->ps_Format++;
			}
			else
			{
				break;
			}
		}

		if ( ! in.c )
		{
			break;
		}

		/* Now for the field width.
			*/

		// --

		val = my_readsize( ps, & in );

		if ( val < 0 )
		{
			#ifdef DEBUG
			IExec->DebugPrintF( "%s:%04d: Error\n", __FILE__, __LINE__ );
			#endif
			goto bailout;
		}

		in.minimum_field_width = val;

		// --

		in.c = *ps->ps_Format;

		if ( ! in.c )
		{
			break;
		}

		/* Was a precision specified?
			*/

		if ( *ps->ps_Format == '.' )
		{
			ps->ps_Format++;

			val = my_readsize( ps, & in );

			if ( val < 0 )
			{
				#ifdef DEBUG
				IExec->DebugPrintF( "%s:%04d: Error\n", __FILE__, __LINE__ );
				#endif
				goto bailout;
			}

			in.precision = val;
		}
		else
		{
			in.precision = -1;
		}

		/* Now for the size modifier, if any. */

		in.c = *ps->ps_Format;

		if ( ! in.c )
		{
			break;
		}

		/**/ if ( in.c == 'l' )
		{
			in.Parameter_Size = Parameter_Size_Long;
			ps->ps_Format++;
		}
		else if ( in.c == 'L' )
		{
			in.Parameter_Size = Parameter_Size_Long_Double;
			ps->ps_Format++;
		}
		else if ( in.c == 'h' )
		{
			in.Parameter_Size = Parameter_Size_Short;
			ps->ps_Format++;
		}
		else if ( in.c == 'j' )
		{
			in.Parameter_Size = Parameter_Size_Intmax_t;
			ps->ps_Format++;
		}
		else if ( in.c == 't' )
		{
			in.Parameter_Size = Parameter_Size_Ptrdiff_t;
			ps->ps_Format++;
		}
		else if ( in.c == 'z' )
		{
			in.Parameter_Size = Parameter_Size_Size_t;
			ps->ps_Format++;
		}
		else
		{
			/* The default is to assume 32 bit parameters. */
			in.Parameter_Size = Parameter_Size_Default;
		}

		/* Finally, the conversion_type type. */

		in.c = *ps->ps_Format;

		if ( ! in.c )
		{
			break;
		}

		/* Check for byte parameters. */
		if (( in.Parameter_Size == Parameter_Size_Short ) && ( in.c == 'h' ))
		{
			in.Parameter_Size = Parameter_Size_Byte;

			ps->ps_Format++;

			/* The conversion_type type follows. */
			in.c = *ps->ps_Format;

			/* End of the fmt string? */
			if ( ! in.c )
			{
				break;
			}
		}

		/* Check for long long parameters. */
		if (( in.Parameter_Size == Parameter_Size_Long ) && ( in.c == 'l' ))
		{
			in.Parameter_Size = Parameter_Size_Long_Long;

			ps->ps_Format++;

			/* The conversion_type type follows. */
			in.c = *ps->ps_Format;

			/* End of the fmt string? */
			if ( ! in.c )
			{
				break;
			}
		}

		// --

		in.trail_string[0] = '\0';
		in.num_trailing_zeroes = 0;
		in.Conversion_Type = in.c;
		ps->ps_Format++;

		// --

		in.output_buffer = & in.buffer[ sizeof( in.buffer ) - 1 ];
		*in.output_buffer = 0;
		in.output_len = 0;

		// --

		switch( in.Conversion_Type )
		{
			// -- Caracther

			case 'c':
			case 'C':
			{
				if ( ! my_Option_c( ps, & in ))
				{
					#ifdef DEBUG
					IExec->DebugPrintF( "%s:%04d: Error\n", __FILE__, __LINE__ );
					#endif
					goto bailout;
				}
				break;
			}

			// -- Hexadecimal

			case 'x':
			{
				in.FORMATF_CapitalLetters = 0;

				if ( ! my_Option_x( ps, & in ))
				{
					#ifdef DEBUG
					IExec->DebugPrintF( "%s:%04d: Error\n", __FILE__, __LINE__ );
					#endif
					goto bailout;
				}

				break;
			}

			case 'X':
			{
				in.FORMATF_CapitalLetters = 1;

				if ( ! my_Option_x( ps, & in ))
				{
					#ifdef DEBUG
					IExec->DebugPrintF( "%s:%04d: Error\n", __FILE__, __LINE__ );
					#endif
					goto bailout;
				}

				break;
			}

			case 'p':
			{
				in.FORMATF_CapitalLetters = 0;
				in.FORMATF_HexPrefix = 1;
				in.Conversion_Type = 'x';
				in.Fill_Character = '0';
				in.minimum_field_width = 10; // 0x12345678

				if ( ! my_Option_x( ps, & in ))
				{
					#ifdef DEBUG
					IExec->DebugPrintF( "%s:%04d: Error\n", __FILE__, __LINE__ );
					#endif
					goto bailout;
				}

				break;
			}

			// -- Octadecimal

			case 'o':
			{
				if ( ! my_Option_o( ps, & in ))
				{
					#ifdef DEBUG
					IExec->DebugPrintF( "%s:%04d: Error\n", __FILE__, __LINE__ );
					#endif
					goto bailout;
				}
				break;
			}

			// -- Decimal

			case 'd': // Signed
			{
				if ( ! my_Option_d( ps, & in ))
				{
					#ifdef DEBUG
					IExec->DebugPrintF( "%s:%04d: Error\n", __FILE__, __LINE__ );
					#endif
					goto bailout;
				}
				break;
			}

			case 'i': // Signed
			{
				if ( ! my_Option_d( ps, & in ))
				{
					#ifdef DEBUG
					IExec->DebugPrintF( "%s:%04d: Error\n", __FILE__, __LINE__ );
					#endif
					goto bailout;
				}
				break;
			}

			case 'u': // Unsigned
			{
				if ( ! my_Option_u( ps, & in ))
				{
					#ifdef DEBUG
					IExec->DebugPrintF( "%s:%04d: Error\n", __FILE__, __LINE__ );
					#endif
					goto bailout;
				}
				break;
			}

			// -- String

			case 's':
			case 'S':
			{
				if ( ! my_Option_s( ps, & in ))
				{
					#ifdef DEBUG
					IExec->DebugPrintF( "%s:%04d: Error\n", __FILE__, __LINE__ );
					#endif
					goto bailout;
				}
				break;
			}

			// -- Written bytes so far

			case 'n':
			{
				if ( ! my_Option_n( ps, & in ))
				{
					#ifdef DEBUG
					IExec->DebugPrintF( "%s:%04d: Error\n", __FILE__, __LINE__ );
					#endif
					goto bailout;
				}

				continue;
			}

			// --

			default:
			{
				/* Just store the conversion_type character. */

				stat = my_writechar( ps, & in, in.Conversion_Type );

				if ( stat == MWS_Error )
				{
					#ifdef DEBUG
					IExec->DebugPrintF( "%s:%04d: Error\n", __FILE__, __LINE__ );
					#endif
					goto bailout;
				}

				if ( stat == MWS_Full )
				{
					// Buffer full, we are done
					goto done;
				}

				continue;
			}
		}

//		  /**/ if ( in.Conversion_Type == 'a' )
//		  {
//			  if ( my_Option_a( ps, & in ) == FALSE )
//			  {
//				  goto bailout;
//			  }
//		  }
//		  else if ( in.Conversion_Type == 'A' )
//		  {
//			  in.FORMATF_CapitalLetters = 1;
//
//			  if ( my_Option_a( ps, & in ) == FALSE )
//			  {
//				  goto bailout;
//			  }
//		  }
//		  else if ( in.Conversion_Type == 'e' )
//		  {
//			  if ( my_Option_e( ps, & in ) == FALSE )
//			  {
//				  goto bailout;
//			  }
//		  }
//
//		  else if ( in.Conversion_Type == 'E' )
//		  {
//			  in.FORMATF_CapitalLetters = 1;
//
//			  if ( my_Option_e( ps, & in ) == FALSE )
//			  {
//				  goto bailout;
//			  }
//		  }
//
//		  else if ( in.Conversion_Type == 'f' )
//		  {
//			  if ( my_Option_f( ps, & in ) == FALSE )
//			  {
//				  goto bailout;
//			  }
//		  }
//		  else if ( in.Conversion_Type == 'g' )
//		  {
//			  if ( my_Option_g( ps, & in ) == FALSE )
//			  {
//				  goto bailout;
//			  }
//		  }
//		  else if ( in.Conversion_Type == 'G' )
//		  {
//			  in.FORMATF_CapitalLetters = 1;
//
//			  if ( my_Option_g( ps, & in ) == FALSE )
//			  {
//				  goto bailout;
//			  }
//		  }




		/* Get ready to prefix a sign character, if required. */
		if( in.FORMATF_IsNegative )
		{
			in.prefix = "-";
		}
		else if ( in.FORMATF_ProduceSign )
		{
			in.prefix = "+";
		}
		else if ( in.FORMATF_ProduceSpace )
		{
			in.prefix = " ";
		}
		else if ( in.FORMATF_ZeroPrefix )
		{
			in.prefix = "0";
		}
		else
		{
			in.prefix = NULL;
		}

		if ( in.FORMATF_HexPrefix )
		{
			Self->string_strcpy( in.prefix_buffer,( in.prefix != NULL ? in.prefix : "" ));
			Self->string_strcat( in.prefix_buffer, "0x" );

			in.prefix = in.prefix_buffer;
		}

		if ( in.FORMATF_LeftJustified )
		{
			if ( in.prefix != NULL )
			{
				for( S32 i=0 ; in.prefix[i] != '\0' ; i++ )
				{
					/* One less character to fill the output with. */
					in.minimum_field_width--;

					stat = my_writechar( ps, & in, in.prefix[i] );

					if ( stat == MWS_Error )
					{
						#ifdef DEBUG
						IExec->DebugPrintF( "%s:%04d: Error\n", __FILE__, __LINE__ );
						#endif
						goto bailout;
					}

					if ( stat == MWS_Full )
					{
						// Buffer full, we are done
						goto done;
					}
				}
			}

			if ( in.output_len )
			{
				stat = my_writestring( ps, & in, in.output_buffer, in.output_len );

				if ( stat == MWS_Error )
				{
					#ifdef DEBUG
					IExec->DebugPrintF( "%s:%04d: Error\n", __FILE__, __LINE__ );
					#endif
					goto bailout;
				}

				if ( stat == MWS_Full )
				{
					goto done;
				}
			}

			if ( in.num_trailing_zeroes )
			{
				stat = my_writefill( ps, & in, '0', in.num_trailing_zeroes );

				if ( stat == MWS_Error )
				{
					#ifdef DEBUG
					IExec->DebugPrintF( "%s:%04d: Error\n", __FILE__, __LINE__ );
					#endif
					goto bailout;
				}

				if ( stat == MWS_Full )
				{
					goto done;
				}

				in.output_len++;
			}

			for( S32 i=0 ; in.trail_string[i] ; i++ )
			{
				stat = my_writechar( ps, & in, in.trail_string[i] );

				if ( stat == MWS_Error )
				{
					#ifdef DEBUG
					IExec->DebugPrintF( "%s:%04d: Error\n", __FILE__, __LINE__ );
					#endif
					goto bailout;
				}

				if ( stat == MWS_Full )
				{
					// Buffer full, we are done
					goto done;
				}

				in.output_len++;
			}

			{
				/* Left justified output defaults to use the blank
				   space as the fill character. */
				stat = my_writefill( ps, & in, ' ', in.minimum_field_width - in.output_len );

				if ( stat == MWS_Error )
				{
					#ifdef DEBUG
					IExec->DebugPrintF( "%s:%04d: Error\n", __FILE__, __LINE__ );
					#endif
					goto bailout;
				}

				if ( stat == MWS_Full )
				{
					goto done;
				}
			}
		}
		else
		{
			/* 
			** If we have to add the prefix later, make sure that
			*'we don't add too many fill characters in front of
			** it now. 
			*/

			if ( in.prefix )
			{
				for( S32 i = 0 ; in.prefix[i] != '\0' ; i++ )
				{
					/* One less character to fill the output with. */
					in.minimum_field_width--;

					if ( in.Fill_Character == '0' )
					{
						stat = my_writechar( ps, & in, in.prefix[i] );

						if ( stat == MWS_Error )
						{
							#ifdef DEBUG
							IExec->DebugPrintF( "%s:%04d: Error\n", __FILE__, __LINE__ );
							#endif
							goto bailout;
						}

						if ( stat == MWS_Full )
						{
							// Buffer full, we are done
							goto done;
						}
					}
				}

				/* That takes care of the sign. */
				if ( in.Fill_Character == '0' )
				{
					in.prefix = NULL;
				}
			}

			if ( in.trail_string[0] )
			{
				in.trail_string_len = Self->string_strlen( in.trail_string );
			}
			else
			{
				in.trail_string_len = 0;
			}

			in.minimum_field_width -= in.num_trailing_zeroes + in.trail_string_len;

			{
				stat = my_writefill( ps, & in, in.Fill_Character, in.minimum_field_width - in.output_len );

				if ( stat == MWS_Error )
				{
					#ifdef DEBUG
					IExec->DebugPrintF( "%s:%04d: Error\n", __FILE__, __LINE__ );
					#endif
					goto bailout;
				}

				if ( stat == MWS_Full )
				{
					// Buffer full, we are done
					goto done;
				}
			}

			/* If we still have a sign character to add, do it here. */

			if ( in.prefix )
			{
				for( S32 i=0 ; in.prefix[i] ; i++ )
				{
					stat = my_writechar( ps, & in, in.prefix[i] );

					if ( stat == MWS_Error )
					{
						#ifdef DEBUG
						IExec->DebugPrintF( "%s:%04d: Error\n", __FILE__, __LINE__ );
						#endif
						goto bailout;
					}

					if ( stat == MWS_Full )
					{
						// Buffer full, we are done
						goto done;
					}
				}
			}

			if ( in.output_len )
			{
				stat = my_writestring( ps, & in, in.output_buffer, in.output_len );

				if ( stat == MWS_Error )
				{
					#ifdef DEBUG
					IExec->DebugPrintF( "%s:%04d: Error\n", __FILE__, __LINE__ );
					#endif
					goto bailout;
				}

				if ( stat == MWS_Full )
				{
					goto done;
				}
			}

			if ( in.num_trailing_zeroes )
			{
				stat = my_writefill( ps, & in, '0', in.num_trailing_zeroes );

				if ( stat == MWS_Error )
				{
					#ifdef DEBUG
					IExec->DebugPrintF( "%s:%04d: Error\n", __FILE__, __LINE__ );
					#endif
					goto bailout;
				}

				if ( stat == MWS_Full )
				{
					goto done;
				}
			}

			if ( in.trail_string_len )
			{
				stat = my_writestring( ps, & in, in.trail_string, in.trail_string_len );

				if ( stat == MWS_Error )
				{
					#ifdef DEBUG
					IExec->DebugPrintF( "%s:%04d: Error\n", __FILE__, __LINE__ );
					#endif
					goto bailout;
				}

				if ( stat == MWS_Full )
				{
					goto done;
				}
			}
		}
	}

done:

	if ( ! ps->ps_Stream )
//	if ( ps->ps_Buffer )	// ps_Buffer is null when counting
	{
		stat = my_writechar( ps, & in, '\0' );

		if ( stat == MWS_Error )
		{
			#ifdef DEBUG
			IExec->DebugPrintF( "%s:%04d: Error\n", __FILE__, __LINE__ );
			#endif
			goto bailout;
		}

		// make snprintf/vsnprintf do the adjusting
		// NUL char should not be counted
		//ps->ps_Written--;
	}

	retval = ps->ps_Written;

bailout:

//	IExec->DebugPrintF( "EEEEEE2 : ps_Written %ld\n", retval );

	if ( ps )
	{
		ps->ps_Written = retval;

		if ( ps->ps_Stream )
		{
			Self->stdio_funlockfile( (PTR) ps->ps_Stream );
		}
	}
}
