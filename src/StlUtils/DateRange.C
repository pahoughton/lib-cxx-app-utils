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
// Revision 1.6  1995/11/05 14:44:25  houghton
// Ports and Version ID changes
//
//
//

#if !defined( CLUE_SHORT_FN )
#include "DateRange.hh"
#include "Clue.hh"
#include "Str.hh"
#include <iomanip>
#else
#include "DateRg.hh"
#include "Clue.hh"
#include "Str.hh"
#include <iomanip>
#endif


#if defined( CLUE_DEBUG )
#define  inline
#if !defined( CLUE_SHORT_FN )
#include "DateRange.ii"
#else
#include "DateRg.ii"
#endif
#endif // def( CLUE_DEBUG )

CLUE_VERSION(
  DateRange,
  "$Id$");


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
  if( diff )
    return( diff );
  else
    return( ::compare( dur, two.dur ) );
}

size_t
DateRange::getBinSize( void ) const
{
  return( DateTime::getBinSize() + sizeof( dur ) );
}

BinStream &
DateRange::write( BinStream & dest ) const
{
  DateTime::write( dest );
  return( dest.write( dur ) );
}

BinStream &
DateRange::read( BinStream & src )
{
  DateTime::read( src );
  return( src.read( dur ) );
}


ostream &
DateRange::write( ostream & dest ) const
{
  DateTime::write( dest );
  dest.write( (const char *)&dur, sizeof( dur ) );
  return( dest );
}

inline
istream &
DateRange::read( istream & src )
{
  DateTime::read( src );

  time_t    rDur;
  src.read( (char *)&rDur, sizeof( rDur ) );
  setDur( rDur );
  return( src );
}

ostream &
DateRange::toStream( ostream & dest ) const
{
  
  dest << "Start: "
    ;

  DateTime::toStream( dest );
  
  dest << " Dur: "
       << setfill('0')
       << setw(2) << HoursInTimeT( getDur() ) << ':'
       << setw(2) << MinInTimeT( getDur() ) << ':'
       << setw(2) << SecInTimeT( getDur() )
       << setfill(' ')
       ;
  
  return( dest );
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
DateRange::dumpInfo( 
  ostream &	dest,
  const char *  prefix,
  bool		showVer
  ) const
{
  if( showVer )
    dest << DateRange::getClassName() << ":\n"
	 << DateRange::getVersion() << '\n';

  if( ! DateRange::good() )
    dest << prefix << "Error: " << DateRange::error() << '\n';
  else
    dest << prefix << "Good!" << '\n';

  dest << prefix << "range:   ";
  DateRange::toStream( dest );
  dest << '\n';

  Str pre;
  pre << prefix << DateTime::getClassName() << "::";
  
  DateTime::dumpInfo( dest, pre, false );

  dest << prefix << "dur:     " << dur << '\n';
  dest << '\n';

  return( dest  );
}
  
const char *
DateRange::getVersion( bool withPrjVer ) const
{
  return( version.getVer( withPrjVer, DateTime::getVersion( false ) ) );
}
