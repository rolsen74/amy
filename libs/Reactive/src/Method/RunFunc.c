
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2011-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

struct NSR_Args
{
	struct RA_PrivClass *cl;
	PTR obj;
	PTR method;
	PTR data;
	PTR data2;
	PTR Self;
	U32 *retval;
};

// --

static U32 StackRunFunc( struct NSR_Args *args )
{
	*args->retval = args->cl->RA_Class_Dispatcher(
		(PTR) args->Self,
		(PTR) args->cl,
		(PTR) args->obj,
		(PTR) args->method,
		(PTR) args->data,
		(PTR) args->data2
	);

	return(	0 );
}

// --

U32 AMYFUNC _main_Method_RunFunc(
	struct ReactivePrivIFace *Self,
	struct RA_PrivClass *cl,
	struct RA_PrivObject *obj,
	struct RA_Method *method )
{
struct SignalSemaphore *ss;
struct RootClass_Data *o;
struct Task *self;
U32 retval;
U32 free;
U32 err;
U32 sp;

//	IExec->DebugPrintF( "RA_Method_RunFunc\n" );

#if 0
	if ( cl->RA_Class_ID != ID_RAClass )
	{
//		IExec->DebugPrintF( "Self->Method_RunFunc: Invalid Class ID\n" );
	}

	if ( obj->RA_Object_ID != ID_RAObject )
	{
//		IExec->DebugPrintF( "Self->Method_RunFunc: Invalid Object ID\n" );
	}
#endif


	o = (PTR) obj;

	if (( o->rcd_Flags & ROOTCLASSF_NoSemaphore ) == 0 )
	{
		ss = o->rcd_SemaphoreAdr;

		IExec->ObtainSemaphore( ss );
	}
	else
	{
		ss = NULL;
	}
	
	// Calculate Free Stack

	self	= IExec->FindTask( NULL );

	__asm volatile( "mr %0,1" : "=r" ( sp ));

	free	= sp - (U32)self->tc_SPLower;

	if ( free >= 10*1024 )
	{
		retval = cl->RA_Class_Dispatcher(
			(PTR) Self,
			(PTR) cl,
			(PTR) obj,
			(PTR) method,
			(PTR) cl->RA_Class_Data,
			(PTR) (((U8 *)obj)+cl->RA_Class_InstOffset)
		);
	}
	else
	{
//		IExec->DebugPrintF( "Method new stack (free %ld)", free );

		struct NSR_Args args =
		{
			cl,
			obj,
			method,
			cl->RA_Class_Data,
			(((uint8 *)obj)+cl->RA_Class_InstOffset),
			Self,
			& retval
		};

		// Swap to new stack
		err = IExec->NewStackRunTags( & StackRunFunc,
			NSR_MinStackSize, 65536,
			NSR_StackSize, 65536,
			NSR_Arg1, & args,
			TAG_END
		);

		if ( err != 0 )
		{
			retval = RAV_General_LowStack;
		}
	}

	if ( ss )
	{
		IExec->ReleaseSemaphore( ss );
	}

	return(	retval );
}
