//
// File:        DateRangeWeekly.cc
// Project:	StlUtils (%PP%)
// Item:   	%PI% (%PF%)
// Desc:        
//              
//	Compiled source for DateRangeWeekly.
//
// Author:      Paul Houghton - (houghton@cworld)
// Created:     02/20/94 09:30 
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    %PO%
//  Last Mod:	    %PRT%
//  Version:	    %PIV%
//  Status: 	    %PS%
//
// %PID%
//

#if !defined( STLUTILS_SHORT_FN )
#include "DateRangeWeekly.hh"
#include "DateTimeUtils.hh"
#include "StlUtilsMisc.hh"
#include "Str.hh"
#include <iomanip>
#else
#include "DateRgWk.hh"
#include "DtTmUtil.hh"
#include "StlUtils.hh"
#include "Str.hh"
#include <iomanip>
#endif

#if defined( STLUTILS_DEBUG )
#if !defined( STLUTILS_SHORT_FN )
#include "DateRangeWeekly.ii"
#else
#include "DateRgWk.ii"
#endif
#endif // def( STLUTILS_DEBUG )

STLUTILS_VERSION(
  DateRangeWeekly,
  "%PID%" );


const time_t DateRangeWeekly::freq = (24 * 60 * 60 * 7);

DayOfWeek
DateRangeWeekly::getDayOfWeek( void ) const
{
  return( (DayOfWeek)(getStart() / SecPerDay ) );
}

time_t
DateRangeWeekly::getFrequency( void ) const
{
  return( freq );
}

bool
DateRangeWeekly::in( const DateTime & dateTwo ) const
{
  return( getDayOfWeek() == dateTwo.getDayOfWeek()
	  && DateRangeDaily::in( dateTwo ) );
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

// Revision Log:
//
// 
// %PL%
// 
// $Log$
// Revision 5.3  2003/05/12 15:51:25  houghton
// Added in( const DateTime & dateTwo ) const.
//
// Revision 5.2  2001/07/26 19:29:00  houghton
// *** empty log message ***
//
// Revision 5.1  2000/05/25 10:33:14  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:12:16  houghton
// Changed to Version 4
//
// Revision 3.4  1997/09/17 14:10:15  houghton
// Renamed StlUtilsUtils.hh to StlUtilsMisc.hh
//
// Revision 3.3  1997/09/17 11:08:14  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.2  1997/08/24 21:55:11  houghton
// Changed getDayOfWeek to return a 'DayOfWeek' (was int).
//
// Revision 3.1  1996/11/14 01:23:34  houghton
// Changed to Release 3
//
// Revision 2.4  1996/11/06 18:04:09  houghton
// StlUtils.hh renamed to StlUtilsUtils.hh
//
// Revision 2.3  1996/04/27 12:57:24  houghton
// Removed unneeded includes.
//
// Revision 2.2  1995/12/04 11:17:19  houghton
// Bug Fix - Can now compile with out '-DSTLUTILS_DEBUG'.
//
// Revision 2.1  1995/11/10  12:40:28  houghton
// Change to Version 2
//
// Revision 1.4  1995/11/05  14:44:28  houghton
// Ports and Version ID changes
//
//
