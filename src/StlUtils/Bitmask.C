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
// Revision 1.2  1995/11/05 14:44:23  houghton
// Ports and Version ID changes
//
//

#include "Bitmask.hh"
#include "Compare.hh"
#include <climits>

#if defined( CLUE_DEBUG )
#define  inline
#include <Bitmask.ii>
#endif // def( CLUE_DEBUG )

const char Bitmask::version[] =
LIB_CLUE_VERSION
"$Id$";

const size_t Bitmask::maxPos = CHAR_BIT * sizeof( Bitmask::ValueType );

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





