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
// Revision 3.4  1997/09/17 11:08:12  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.3  1997/07/18 19:10:23  houghton
// Added compare( const DateTime & two ) const to eliminate compiler warnings.
//
// Revision 3.2  1996/11/20 12:11:31  houghton
// Removed support for BinStream.
//
// Revision 3.1  1996/11/14 01:23:31  houghton
// Changed to Release 3
//
// Revision 2.5  1996/11/06 18:03:45  houghton
// StlUtils.hh renamed to StlUtilsUtils.hh
//
// Revision 2.4  1996/04/27 12:54:34  houghton
// Cleanup.
//
// Revision 2.3  1995/12/31 11:21:52  houghton
// Bug fix - Removed 'inline' statement.
//
// Revision 2.2  1995/12/04 11:17:04  houghton
// Bug Fix - Can now compile with out '-DSTLUTILS_DEBUG'.
//
// Revision 2.1  1995/11/10  12:40:23  houghton
// Change to Version 2
//
// Revision 1.6  1995/11/05  14:44:25  houghton
// Ports and Version ID changes
//
//
//

#if !defined( STLUTILS_SHORT_FN )
#include "DateRange.hh"
#include "StlUtilsUtils.hh"
#include "Str.hh"
#include "DateTimeUtils.hh"
#include <iomanip>
#else
#include "DateRg.hh"
#include "StlUtils.hh"
#include "Str.hh"
#include "DateTimeUtils.hh"
#include <iomanip>
#endif



#if defined( STLUTILS_DEBUG )
#if !defined( STLUTILS_SHORT_FN )
#include "DateRange.ii"
#else
#include "DateRg.ii"
#endif
#endif // def( STLUTILS_DEBUG )

STLUTILS_VERSION(
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

int
DateRange::compare( const DateTime & two ) const
{
  int diff = DateTime::compare( two );
  if( diff )
    return( diff );
  else
    return( 1 );
}

size_t
DateRange::getBinSize( void ) const
{
  return( DateTime::getBinSize() + sizeof( dur ) );
}


ostream &
DateRange::write( ostream & dest ) const
{
  DateTime::write( dest );
  dest.write( (const char *)&dur, sizeof( dur ) );
  return( dest );
}

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
