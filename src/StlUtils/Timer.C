//
// File:        Timer.C
// Desc:        
//
//  
//  
// Author:      Paul Houghton - (houghton@cworld1.wiltel.com)
// Created:     07/28/95 07:00
//
// Revision History:
//
// $Log$
// Revision 1.1  1995/11/05 13:23:42  houghton
// Initaial implementation
//
//

#include "Timer.hh"
#include "DateTimeUtils.hh"

#include <iomanip>

const char Timer::version[] =
LIB_CLUE_VERSION
"$Id$";

#ifdef   CLUE_DEBUG
#define  inline
#include "Timer.ii"
#endif

ostream &
Timer::dumpInfo( ostream & dest  ) const
{
  dest << getClassName() << ":\n";

  dest << "    " << version << '\n';

  dest << "    " ;
  toStream( dest );
  dest << '\n';

  dest << "    Start:   " << startSec << '\n'
       << "    Stop:    " << stopSec << '\n'
       << "    Dur:     " << getDur() << '\n'
    ;
  
  dest << '\n';

  return( dest  );
}



