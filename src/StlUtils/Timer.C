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
// Revision 2.2  1995/12/04 11:18:31  houghton
// Bug Fix - Can now compile with out '-DCLUE_DEBUG'.
//
// Revision 2.1  1995/11/10  12:41:19  houghton
// Change to Version 2
//
// Revision 1.3  1995/11/05  15:28:50  houghton
// Revised
//
//

#if !defined( CLUE_SHORT_FN )
#include "Timer.hh"
#include "DateTimeUtils.hh"
#include <iomanip>
#else
#include "Timer.hh"
#include "DateTimeUtils.hh"
#include <iomanip>
#endif

CLUE_VERSION(
  Timer,
  "$Id$" );

#if defined( CLUE_DEBUG )
#include "Timer.ii"
#endif

ostream &
Timer::toStream( ostream & dest ) const
{
  if( getStart() == 0 || getStop() == 0 )
    {
      dest << "no duration";
    }

  int hours = getDur() / (60 * 60);
  int minutes = MinInTimeT( getDur() );
  int seconds = SecInTimeT( getDur() );

  dest << setfill('0') << setw(2) << hours << ':'
       << setw(2) << minutes << ':'
       << setw(2) << seconds
    ;

  dest << setfill(' ');

  return( dest );
}

const char *
Timer::getClassName( void ) const
{
  return( "Timer" );
}

const char *
Timer::getVersion( bool withPrjVer ) const
{
  return( version.getVer( withPrjVer ) );
}


ostream &
Timer::dumpInfo( 
  ostream &	dest,
  const char *  prefix,
  bool		showVer
  ) const
{
  if( showVer )
    dest << Timer::getClassName() << ":\n"
	 << Timer::getVersion() << '\n';
  
  dest << prefix;
  toStream( dest );
  dest << '\n';

  dest << prefix << "start:   " << startSec << '\n'
       << prefix << "stop:    " << stopSec << '\n'
       << prefix << "dur:     " << getDur() << '\n'
    ;
  
  dest << '\n';

  return( dest  );
}



