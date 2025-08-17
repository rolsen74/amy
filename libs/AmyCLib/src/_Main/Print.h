
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

#ifndef AMYLIB_SRC_MAIN_PRINT_H
#define AMYLIB_SRC_MAIN_PRINT_H

// --

enum Parameter_Size_t
{
	Parameter_Size_Byte,
	Parameter_Size_Long,
	Parameter_Size_Short,
	Parameter_Size_Size_t,
	Parameter_Size_Ptrdiff_t,
	Parameter_Size_Long_Long,
	Parameter_Size_Long_Double,
	Parameter_Size_Intmax_t,
	Parameter_Size_Default
};

struct Intern
{
	struct AmyCLibIFace *Self;
	const char *prefix;
	enum Parameter_Size_t Parameter_Size;
	char *output_buffer;
	char FORMATF_LeftJustified;
	char FORMATF_ProduceSign;
	char FORMATF_ProduceSpace;
	char FORMATF_AlternateConversion;
	char FORMATF_CapitalLetters;
	char FORMATF_IsNegative;
	char FORMATF_HexPrefix;
	char FORMATF_ZeroPrefix;
	char Conversion_Type;
	char Fill_Character;
	char buffer[128];
	char prefix_buffer[8];
	char trail_string[8];
	char c;
	int num_trailing_zeroes;
	int minimum_field_width;
	int trail_string_len;
	int argument_number;
	int argument_digits;
	int output_len;
	int precision;
};

#define ps_Written ps_Result

// --

#endif