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
// Revision 2.3  1996/04/27 12:57:24  houghton
// Removed unneeded includes.
//
// Revision 2.2  1995/12/04 11:17:19  houghton
// Bug Fix - Can now compile with out '-DCLUE_DEBUG'.
//
// Revision 2.1  1995/11/10  12:40:28  houghton
// Change to Version 2
//
// Revision 1.4  1995/11/05  14:44:28  houghton
// Ports and Version ID changes
//
//

#if !defined( CLUE_SHORT_FN )
#include "DateRangeWeekly.hh"
#include "DateTimeUtils.hh"
#include "Clue.hh"
#include "Str.hh"
#include <iomanip>
#else
#include "DateRgWk.hh"
#include "DtTmUtil.hh"
#include "Clue.hh"
#include "Str.hh"
#include <iomanip>
#endif

#if defined( CLUE_DEBUG )
#if !defined( CLUE_SHORT_FN )
#include "DateRangeWeekly.ii"
#else
#include "DateRgWk.ii"
#endif
#endif // def( CLUE_DEBUG )

CLUE_VERSION(
  DateRangeWeekly,
  "$Id$" );


const time_t DateRangeWeekly::freq = (24 * 60 * 60 * 7);

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

const char *
DateRangeWeekly::getVersion( bool withPrjVer ) const
{
  return( version.getVer( withPrjVer , DateRangeDaily::getVersion( false ) ) );
}

ostream &
DateRangeWeekly::dumpInfo( 
  ostream &	dest,
  const char *  prefix,
  bool		showVer
  ) const
{
  if( showVer )
    dest << DateRangeWeekly::getClassName() << ":\n"
	 << DateRangeWeekly::getVersion() << '\n';

  if( ! DateRangeWeekly::good() )
    dest << prefix << "Error: " << DateRangeWeekly::error() << '\n';
  else
    dest << prefix << "Good!" << '\n';

  dest << prefix << "range:    ";
  DateRangeWeekly::toStream( dest );
  dest << '\n';

  Str pre;
  pre << prefix << DateRangeDaily::getClassName() << "::";
  
  DateRangeDaily::dumpInfo( dest, pre, false );

  dest << prefix << "freq:     " << freq << '\n';
  
  dest << '\n';

  return( dest  );
}
