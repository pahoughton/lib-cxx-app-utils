//
// File:        DateRangeDaily.cc
// Desc:        
//              
//
// Author:      Paul Houghton - (houghton@cworld)
// Created:     02/20/94 11:59 
//
// Revision History:
//
// $Log$
// Revision 1.3  1995/11/05 13:29:00  houghton
// Major Implementation Changes.
// Made more consistant with the C++ Standard
//
//

#include "DateRangeDaily.hh"

#include <Clue.hh>
#include <Str.hh>

#include <iomanip>

#ifdef  CLUE_DEBUG
#define inline
#include "DateRangeDaily.ii"
#endif

const char DateRangeDaily::version[] =
LIB_CLUE_VERSION
"$Id$";


time_t DateRangeDaily::freq = (24 * 60 * 60); // SecPerDay

time_t
DateRangeDaily::getFrequency( void ) const
{
  return( freq );
}

time_t
DateRangeDaily::secIn( const DateRange & dateTwo ) const
{
  return( UnionOfDur( start, dur,
		      dateTwo.getSecOfDay(), dateTwo.getDur(),
		      getFrequency() ) );
}


time_t
DateRangeDaily::startsIn( const DateRange & dateTwo ) const
{
  time_t  secs = 0;
  
  if( dateTwo.getSecOfDay() >= start &&
      dateTwo.getSecOfDay() <= start + dur )
    {
      secs = secIn( dateTwo );
    }
  return( secs );
}

time_t
DateRangeDaily::getSecOfDay( void ) const
{
  return( SecOfDay( start ) );
}

int
DateRangeDaily::getDayOfWeek( void ) const
{
  return( -1 );
}

time_t
DateRangeDaily::getStart( void ) const
{
  return( start );
}

time_t
DateRangeDaily::setStart( time_t newStart )
{
  time_t old = start;
  start = newStart;
  return( old );
}

int
DateRangeDaily::compare( const DateRange & two ) const
{
  int diff = ::compare( start, two.getSecOfDay() );
  return( diff ? diff : ::compare( getDur(),two.getDur() ) );
}

int
DateRangeDaily::compare( const DateRangeDaily & two ) const
{
  int diff = ::compare( getStart(), two.getStart() );
  return( diff ? diff : ::compare( getDur(), two.getDur() ) );
}


    
bool
DateRangeDaily::good( void ) const
{
  return( DateRange::good() &&
	  start >= 0 && start < SecPerDay );
}

const char *
DateRangeDaily::error( void ) const
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

      if( ! (start >= 0 ) )
	{
	  errStr << " start < 0";
	}

      if( ! (start < SecPerDay ) )
	{
	  errStr << " start >= 1 day";
	}
    }
  return( errStr.cstr() );
}

	    
const char *
DateRangeDaily::getClassName( void ) const
{
  return( "DateRangeDaily" );
}

ostream &
DateRangeDaily::toStream( ostream & dest ) const
{
  
  dest << "Start: "
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
DateRangeDaily::dumpInfo( ostream & dest ) const
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
  DateRange::dumpInfo( dest );

  dest << '\n';

  return( dest  );
}
