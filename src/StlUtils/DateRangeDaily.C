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
// Revision 2.1  1995/11/10 12:40:25  houghton
// Change to Version 2
//
// Revision 1.4  1995/11/05  14:44:27  houghton
// Ports and Version ID changes
//
//

#if !defined( CLUE_SHORT_FN )
#include "DateRangeDaily.hh"
#include "Clue.hh"
#include "Str.hh"
#include <iomanip>
#else
#include "DateRgDl.hh"
#include "Clue.hh"
#include "Str.hh"
#include <iomanip>
#endif


#if defined( CLUE_DEBUG )
#define inline
#if !defined( CLUE_SHORT_FN )
#include "DateRangeDaily.ii"
#else
#include "DateRgDl.ii"
#endif
#endif // def( CLUE_DEBUG )

CLUE_VERSION(
  DateRangeDaily,
  "$Id$" );


const time_t DateRangeDaily::freq = (24 * 60 * 60); // SecPerDay

time_t
DateRangeDaily::getFrequency( void ) const
{
  return( freq );
}

time_t
DateRangeDaily::secIn( const DateRange & dateTwo ) const
{
  return( UnionOfDur( getTimeT(), dur,
		      dateTwo.getSecOfDay(), dateTwo.getDur(),
		      getFrequency() ) );
}


time_t
DateRangeDaily::startsIn( const DateRange & dateTwo ) const
{
  time_t  secs = 0;
  
  if( dateTwo.getSecOfDay() >= getTimeT() &&
      dateTwo.getSecOfDay() <= getTimeT() + dur )
    {
      secs = secIn( dateTwo );
    }
  return( secs );
}

time_t
DateRangeDaily::getSecOfDay( void ) const
{
  return( SecOfDay( getTimeT() ) );
}

int
DateRangeDaily::getDayOfWeek( void ) const
{
  return( -1 );
}

time_t
DateRangeDaily::getStart( void ) const
{
  return( getTimeT() );
}

time_t
DateRangeDaily::setStart( time_t newStart )
{
  return( setTimeT( newStart ) );
}

int
DateRangeDaily::compare( const DateRange & two ) const
{
  int diff = ::compare( getStart(), two.getSecOfDay() );
  if( diff )
    return( diff );
  else
    return( ::compare( getDur(), two.getDur() ) );
}

int
DateRangeDaily::compare( const DateRangeDaily & two ) const
{
  int diff = ::compare( getStart(), two.getStart() );
  if( diff )
    return( diff );
  else
    return( ::compare( getDur(), two.getDur() ) );
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
    
bool
DateRangeDaily::good( void ) const
{
  return( DateRange::good() &&
	  getTimeT() >= 0 && getTimeT() < SecPerDay );
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

      if( ! (getTimeT() >= 0 ) )
	{
	  errStr << " start < 0";
	}

      if( ! (getTimeT() < SecPerDay ) )
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


const char *
DateRangeDaily::getVersion( bool withPrjVer ) const
{
  return( version.getVer( withPrjVer , DateRange::getVersion( false ) ) );
}

ostream &
DateRangeDaily::dumpInfo( 
  ostream &	dest,
  const char *  prefix,
  bool		showVer
  ) const
{
  if( showVer )
    dest << DateRangeDaily::getClassName() << ":\n"
	 << DateRangeDaily::getVersion() << '\n';

  if( ! DateRangeDaily::good() )
    dest << prefix << "Error: " << DateRangeDaily::error() << '\n';
  else
    dest << prefix << "Good!" << '\n';

  dest << prefix << "range:    ";
  DateRangeDaily::toStream( dest );
  dest << '\n';

  Str pre;
  pre << prefix << DateRange::getClassName() << "::";
  
  DateRange::dumpInfo( dest, pre, false );

  dest << prefix << "freq:     " << freq << '\n'
    ;
  
  dest << '\n';

  return( dest  );
}
  

