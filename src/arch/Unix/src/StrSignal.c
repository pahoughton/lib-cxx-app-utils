/*********************************************************************
 *
 * File:        StrSignal.c
 * Project:	StlUtils
 * Desc:
 *
 *  
 *
 * Notes:
 *
 * Author:	Paul Houghton - (paul.houghton@wcom.com)
 * Created:	01/30/98 06:27
 *
 * Revision History: (See end of file for Revision Log)
 *
 *  Last Mod By:    $Author$
 *  Last Mod:	    $Date$
 *  Version:	    $Revision$
 *
 *********************************************************************/

#include "StrSignal.h"
#include "_SignalStrings.h"
#include <stdio.h>

#define ArraySize( _a_ ) ( sizeof( _a_ ) / sizeof( _a_[0] ) )

static char	SigNumString[32];

const char *
StrSignal( int sig )
{

  if( sig < ArraySize( SignalStrings ) )
    {
      return( SignalStrings[ sig ] );
    }
  else
    {
      sprintf( SigNumString, "SIGNUM_%d", sig );
      return( SigNumString );
    }
}

/*
 *
 * Revision Log:
 *
 * $Log$
 * Revision 1.1  1998/02/02 15:32:27  houghton
 * Initial version.
 *
 *
 */
