//
// File:        DateRange.cc
// Desc:        
//              
//
// Author:      Paul Houghton - (houghton@cworld)
// Created:     02/20/94 08:57 
//
// Revision History:
//
// $Log$
// Revision 1.5  1995/11/05 13:28:59  houghton
// Major Implementation Changes.
// Made more consistant with the C++ Standard
//
//
//

#include "DateRange.hh"

#include <Clue.hh>
#include <Str.hh>

#include <iomanip>

#ifdef   CLUE_DEBUG
#define  inline
#include <DateRange.ii>
#endif

const char DateRange::version[] =
LIB_CLUE_VERSION
"$Id$";


time_t
DateRange::getDur( void ) const
{
  return( dur );
}

time_t
DateRange::getSecOfDay( void ) const
{
  return( DateTime::getSecOfDay() );
}

time_t
DateRange::setDur( time_t newDur )
{
  time_t oldDur = dur;
  dur = newDur;
  
  return( oldDur );
}

time_t
DateRange::secIn( const DateRange & dateTwo ) const
{
  time_t   secs = 0;

  return( UnionOfDur( getTimeT(), dur,
		      dateTwo.getTimeT(), dateTwo.getDur() ) );
  
  return( secs );
}


time_t
DateRange::startsIn( const DateRange & dateTwo ) const
{
  time_t  secs = 0;

  if( dateTwo.getTimeT() >= getTimeT() &&
      dateTwo.getTimeT() <= (getTimeT() + dur ) )
    {
      secs = secIn( dateTwo );
    }
  return( secs );
}


int
DateRange::compare( const DateRange & two ) const
{
  int diff = DateTime::compare( two );
  return( diff ? diff : ::compare( dur, two.dur ) );
}


bool
DateRange::good( void ) const
{
  return( DateTime::good() && dur > 0 );
}

const char *
DateRange::error( void ) const
{
  static Str errStr;
  errStr.reset();

  errStr << getClassName() << ':';

  if( good() )
    {
      errStr << " Ok";
    }
  else
    {
      if( ! (DateTime::good() ) )
	{
	  errStr << " " << DateTime::error();
	}
      if( ! (dur > 0) )
	{
	  errStr << " Stop time <= StartTime";
	}
    }
  return( errStr.cstr() );  
}

const char *
DateRange::getClassName( void ) const
{
  return( "DateRange" );
}

ostream &
DateRange::toStream( ostream & dest ) const
{
  
  dest << "Start: "
    ;

  DateTime::toStream( dest );
  
  dest << "Dur: "
       << setfill('0')
       << setw(2) << HoursInTimeT( getDur() ) << ':'
       << setw(2) << MinInTimeT( getDur() ) << ':'
       << setw(2) << SecInTimeT( getDur() )
       << setfill(' ')
       ;
  
  return( dest );
}

ostream &
DateRange::dumpInfo( ostream & dest  ) const
{
  dest << getClassName() << ":\n";

  dest << "    " << version << '\n';

  if( ! good() )
    dest << "    Error: " << error() << '\n';
  else
    dest << "    " << "Good!" << '\n';

  dest << "    " ;
  toStream( dest );
  dest << '\n';

  dest << getClassName() << "::" ;
  DateTime::dumpInfo( dest );

  dest << '\n';

  return( dest  );
}
  
  
