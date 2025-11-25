/** \file
 * \brief Timer Resource (not exported API)
 *
 * See Copyright Notice in "iup.h"
 */
 
#ifndef __IUP_TIMER_H 
#define __IUP_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif


void iupdrvTimerStop( struct libData *data, Ihandle *ih );
void iupdrvTimerRun( struct libData *data, Ihandle *ih );
void iupdrvTimerInitClass( struct libData *data, Iclass *ic );

long long iupTimerGetLongLong( struct libData *data, Ihandle *ih, const char *name );


#ifdef __cplusplus
}
#endif

#endif
