//
// File:        Bitmask.C
// Desc:        
//
//  
//  
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     07/21/95 06:41
//
// Revision History:
//
// $Log$
// Revision 1.1  1995/11/05 13:23:17  houghton
// Initaial implementation
//
//

#include "Bitmask.hh"

#include "Compare.hh"

#include <climits>

#ifdef   CLUE_DEBUG
#define  inline
#include <Bitmask.ii>
#endif

const char Bitmask::version[] =
LIB_CLUE_VERSION
"$Id$";

const size_t Bitmask::maxPos = CHAR_BIT * sizeof( Bitmask::value );

ostream &
Bitmask::dumpInfo( ostream & dest ) const
{
  dest << getClassName() << ":\n";

  dest << "    " << version << '\n';

  dest << "    " ;
  toStream( dest );
  dest << '\n';

  dest << '\n';

  return( dest  );
}





