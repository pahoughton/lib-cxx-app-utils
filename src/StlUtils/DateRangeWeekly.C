//
// File:        DateRangeWeekly.cc
// Desc:        
//              
//
// Author:      Paul Houghton - (houghton@cworld)
// Created:     02/20/94 09:30 
//
// Revision History:
//
// $Log$
// Revision 1.3  1995/11/05 13:29:01  houghton
// Major Implementation Changes.
// Made more consistant with the C++ Standard
//
//

#include "DateRangeWeekly.hh"

#include <Clue.hh>
#include <Str.hh>

#include <iomanip>

#ifdef  CLUE_DEBUG
#define inline
#include "DateRangeWeekly.ii"
#endif


const char DateRangeWeekly::version[] =
LIB_CLUE_VERSION
"$Id$";


time_t DateRangeWeekly::freq = (24 * 60 * 60 * 7);

int
DateRangeWeekly::getDayOfWeek( void ) const
{
  return( getStart() / SecPerDay );
}

time_t
DateRangeWeekly::getFrequency( void ) const
{
  return( freq );
}

time_t
DateRangeWeekly::secIn( const DateRange & dateTwo ) const
{
  time_t   secOfWeek = ( (dateTwo.getDayOfWeek() * SecPerDay) +
       	 	         dateTwo.getSecOfDay() );

  return( UnionOfDur( getStart(), getDur(),
		      secOfWeek, dateTwo.getDur(),
		      getFrequency() ) );
}

time_t
DateRangeWeekly::startsIn( const DateRange & dateTwo ) const
{
  time_t  secs = 0;
  time_t  secOfWeek = ( (dateTwo.getDayOfWeek() * SecPerDay) +
    		      	dateTwo.getSecOfDay() );
  
  if( secOfWeek >= getStart() &&
      secOfWeek <= getStart() + dur )
    {
      secs = secIn( dateTwo );
    }
  return( secs );
}

bool
DateRangeWeekly::good( void ) const
{
  return( DateRange::good() &&
	  getStart() >= 0 && getStart() < (SecPerDay * 7) );
}

const char *
DateRangeWeekly::error( void ) const
{
  static Str errStr;
  errStr.reset();

  errStr << getClassName() << ":";

  
  if( good() )
    {
      errStr << "Ok";
    }
  else
    {
      if( ! DateRange::good() )
	{
	  errStr << ' ' << DateRange::error();
	}

      if( ! (getStart() >= 0 ) )
	{
	  errStr << " getStart < 0";
	}

      if( ! (getStart() < (SecPerDay * 7) ) )
	{
	  errStr << " start >= 7 days";
	}
    }
  return( errStr.cstr() );
}


const char *
DateRangeWeekly::getClassName( void ) const
{
  return( "DateRangeWeekly" );
}

ostream &
DateRangeWeekly::toStream( ostream & dest ) const
{
  dest << "Start: "
       << AbbrWeekDays[ DaysInTimeT( getStart() ) ] << ' '
       << setfill('0')
       << setw(2) << HourInTimeT( getStart() ) << ':'
       << setw(2) << MinInTimeT( getStart() ) << ':'
       << setw(2) << SecInTimeT( getStart() ) << ' '
       << "Dur: "
       << setw(2) << HourInTimeT( getDur() ) << ':'
       << setw(2) << MinInTimeT( getDur() ) << ':'
       << setw(2) << SecInTimeT( getDur() )
       << setfill(' ')
       ;
  return( dest );
}

ostream &
DateRangeWeekly::dumpInfo( ostream & dest ) const
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
  DateRangeDaily::dumpInfo( dest );

  dest << '\n';

  return( dest  );
}
