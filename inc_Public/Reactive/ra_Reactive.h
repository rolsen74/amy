
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2011-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#ifndef REACTIVE_RA_REACTIVE_H
#define REACTIVE_RA_REACTIVE_H

/***[ Library Info ]********************************************************/

#define RA_LIB_NAME			"Reactive.library"
#define RA_LIB_VERSION		1

/***[ Reactive Arguments ]**************************************************/

#define RAArg( name,var)		{ (name), (PTR*)&(var) }
#define RAArgEnd()			{ NULL, NULL }

struct RAArguments
{
	STR		Name;
	PTR *	Storage;
};

/***[ General Error Values ]************************************************/

enum
{
	// [0] Everything went as it should.
	RAV_General_Success = 0,
	RAV_OK = 0,

	// [1] Some kind of Error occured.
	RAV_General_Failure = 1,
	RAV_Fail = 1,

	// [2] The Attribute or Method is not implemented or known.
	RAV_General_NotImplemented,

	// [3] No more data, this maybe not an error.
	RAV_General_EndOfData,

	// [4] Invalid Object (Pointer)
	RAV_General_InvalidObject,

	// [5] No Storage (Pointer)
	RAV_General_NoStorage,

	// [6] No Data (Pointer)
	RAV_General_NoData,

	// [7] A Memory Allocation failed
	RAV_General_OutOfMemory,

	// [8] Error Creating Object
	RAV_General_ObjectError,

	// [9] Missing Tag
	RAV_General_MissingTag,

	// [10] Illegal Tag Data
	RAV_General_IllegalTagData,

	// [11] The Attribute or Method is not Supported.
	RAV_General_NotSupported,

	// [12] Stack is Low (less than 20kb).
	//      Installing new failed. Function not run.
	RAV_General_LowStack,

	// [13] Wrong Type
	RAV_General_WrongType,

	// [14] Object has no Parent Object
	RAV_General_NoParent,

	// [15] Missing Keyword.. can be a missing Required cli argument
	RAV_General_MissingKeyword,

	// [16] Illegal Arguments
	RAV_General_IllegalArguments,

	// [17] Not Found
	RAV_General_NotFound,

	// [18] Gadget found but not Visible.
	RAV_General_NotVisible,

	// [19] Error obtaining Object Semaphore
	RAV_General_SemaphoreTimeOut,

	// [20] Invalid MethodID (Zero)
	RAV_General_InvalidMethod,

	// [21] Invalid Class
	RAV_General_InvalidClass,
};

/***[ Base Values ]*********************************************************/

#define RAB_Global					0xAC000000	// Reactive Library Tags
#define RAB_Root					0xAC001000
// #define RAB_User					0xAC002000
// #define RAB_Array				    0xAC003000
// #define RAB_List		            0xAC004000
#define RAB_Application				0xAC005000
// #define RAB_Gadget				    0xAC006000
// #define RAB_Window				    0xAC007000
// #define RAB_Stream			      0xAC008000
// #define RAB_Stream_File			  0xAC009000
// #define RAB_Gadget_Group			  0xAC00A000
// #define RAB_Gadget_Button			  0xAC00B000
#define RAB_Directory			    0xAC00C000
// #define RAB_Gadget_Scroller		  0xAC00D000
// #define RAB_Gadget_Page		      0xAC00E000
// #define RAB_Gadget_Chooser		  0xAC00F000
// #define RAB_Hash_MD6				  0xAC010000
// #define RAB_Gadget_Busy			  0xAC011000
// #define RAB_Base64					0xAC012000
// #define RAB_Gadget_ListView		  0xAC013000
// #define RAB_Hash_CRC16				0xAC014000
// #define RAB_Gadget_CheckBox		  0xAC015000
// #define RAB_USBStack			    0xAC016000	// USB Stack
// #define RAB_Hash_HAS_160			0xAC017000
// #define RAB_Media				      0xAC018000
// #define RAB_Media_Coder		      0xAC019000  // Media Encoder or Decoder
// #define RAB_Media_Filter		      0xAC01A000  // Convert data into new format or add effect to data
// #define RAB_Media_Muxer		      0xAC01B000  // Media Demuxer / Muxer
// #define RAB_Media_Output		      0xAC01C000  // Media output like File or Screen
// #define RAB_Gadget_ProgressBar	  0xAC01D000
// #define RAB_Gadget_String			  0xAC01E000
// #define RAB_Date					  0xAC01F000
// #define RAB_WebBrowser			  0xAC020000
// #define RAB_Scanner			      0xAC021000  // Scanner
// #define RAB_Timer				    0xAC022000
// #define RAB_Hash					0xAC023000
// #define RAB_Hash_MD4				0xAC024000
// #define RAB_Hash_MD5				0xAC025000
// #define RAB_Hash_SHA1				0xAC026000
// #define RAB_Hash_SHA2_224			0xAC027000
// #define RAB_Hash_SHA2_256			0xAC028000
// #define RAB_Hash_SHA2_384			0xAC029000
// #define RAB_Hash_SHA2_512			0xAC02A000
// #define RAB_Hash_MD2				0xAC02B000
// #define RAB_Hash_CRC32				0xAC02C000
// #define RAB_Compress				  0xAC02D000
// #define RAB_Crypto				  0xAC02E000
// #define RAB_Compress_ZLib			  0xAC02F000
// #define RAB_Crypto_Blowfish		  0xAC030000
// #define RAB_Compress_LZ4			  0xAC031000
// #define RAB_Compress_LZF			  0xAC032000
// #define RAB_RA3Graphics				0xAC033000	// RA_Graphics.library
// #define RAB_Hash_Tiger_128			0xAC034000
// #define RAB_Hash_Tiger_160			0xAC035000
// #define RAB_Hash_Tiger_192			0xAC036000
// #define RAB_Hash_Tiger2_128		  0xAC037000
// #define RAB_Hash_Tiger2_160		  0xAC038000
// #define RAB_Hash_Tiger2_192		  0xAC039000
// #define RAB_Hash_RIPEMD_128			0xAC03A000
// #define RAB_Hash_RIPEMD_160			0xAC03B000
// #define RAB_Hash_RIPEMD_256			0xAC03C000
// #define RAB_Hash_RIPEMD_320			0xAC03D000
// #define RAB_Hash_Snefru_128			0xAC03E000
// #define RAB_Hash_Snefru_256			0xAC03F000
// #define RAB_Hash_Whirlpool			0xAC040000
// #define RAB_Gadget_Terminal		  0xAC041000
// #define RAB_Tree234				  0xAC042000
// #define RAB_Images1				  0xAC043000
// #define RAB_Hash_Blake_224			0xAC044000
// #define RAB_Hash_Blake_256			0xAC045000
// #define RAB_Hash_Blake_384			0xAC046000
// #define RAB_Hash_Blake_512			0xAC047000
// #define RAB_Gadget_Radio			  0xAC048000
// #define RAB_ReSrc4					0xAC049000	// ReSrc4
// #define RAB_LAST					0xAC04A000

/***************************************************************************/

//--#define RAA_Process_Name			( RAB_Global + 0 )
//--#define RAA_Process_StackSize		( RAB_Global + 1 )
//--#define RAA_Process_Priority		( RAB_Global + 2 )
//--#define RAA_Process_Init			( RAB_Global + 3 )
//--#define RAA_Process_Entry			( RAB_Global + 4 )
//--#define RAA_Process_Free			( RAB_Global + 5 )
//--#define RAA_Process_Data			( RAB_Global + 6 )
//--#define RAA_Process_DataSize		( RAB_Global + 7 )

#define RAA_Argument_Argc			( RAB_Global + 8 )
#define RAA_Argument_Argv			( RAB_Global + 9 )
#define RAA_Argument_File			( RAB_Global + 10 )
#define RAA_Argument_WBStartup		( RAB_Global + 11 )

#define RAA_ErrorCode				( RAB_Global + 12 )
// #define RAA_LogMessages				( RAB_Global + 13 )

//--#define RAA_Process_InitData		( RAB_Global + 14 )
#define RAA_Object_BaseType			( RAB_Global + 15 )

// #define RAA_Image_Chunky			( RAB_Global + 16 )		// ARGB

// -- Images

// #define RAA_Image_Arrow_Up			( RAB_Global + 1000 )
// #define RAA_Image_Arrow_Down		( RAB_Global + 1001 )
// #define RAA_Image_Arrow_Left		( RAB_Global + 1002 )
// #define RAA_Image_Arrow_Right		( RAB_Global + 1003 )
// #define RAA_Image_Window_Close		( RAB_Global + 1004 )
// #define RAA_Image_Window_Depth		( RAB_Global + 1005 )
// #define RAA_Image_Window_Settings	( RAB_Global + 1006 )
// #define RAA_Image_Scroll_HorizKnob	( RAB_Global + 1007 )
// #define RAA_Image_Scroll_VertKnob	( RAB_Global + 1008 )

/***************************************************************************/

#include "Reactive/ra_Plugin.h"
#include "Reactive/cls_Application.h"
#include "Reactive/cls_Directory.h"
#include "Reactive/cls_Root.h"

/***************************************************************************/

#endif
