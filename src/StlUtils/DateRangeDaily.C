//
// File:        DateRangeDaily.cc
// Project:	StlUtils ()
// Desc:        
//              
//	Compiled sources for DateRangeDaily.
//
// Author:      Paul Houghton - (houghton@cworld)
// Created:     02/20/94 11:59 
//
// Revision History: (See end of file for Revision Log)
//
//  $Author$ 
//  $Date$ 
//  $Name$ 
//  $Revision$ 
//  $State$ 
//
//  $Id$ 


#if !defined( STLUTILS_SHORT_FN )
#include "DateRangeDaily.hh"
#include "DateTimeUtils.hh"
#include "StlUtilsMisc.hh"
#include "Str.hh"
#include <iomanip>
#else
#include "DateRgDl.hh"
#include "DtTmUtil.hh"
#include "StlUtils.hh"
#include "Str.hh"
#include <iomanip>
#endif

#if defined( STLUTILS_DEBUG )
#if !defined( STLUTILS_SHORT_FN )
#include "DateRangeDaily.ii"
#else
#include "DateRgDl.ii"
#endif
#endif // def( STLUTILS_DEBUG )


STLUTILS_VERSION(
  DateRangeDaily,
  "$Id$ " );


const time_t DateRangeDaily::freq = (24 * 60 * 60); // SecPerDay

time_t
DateRangeDaily::getFrequency( void ) const
{
  return( freq );
}

bool
DateRangeDaily::isIn( const DateTime & dateTwo )  const
{
  return(   getSecOfDay() <= dateTwo.getSecOfDay()
	 && dateTwo.getSecOfDay() <= (getSecOfDay() + dur) );
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

DayOfWeek
DateRangeDaily::getDayOfWeek( void ) const
{
  return( (DayOfWeek)-1 );
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
DateRangeDaily::compare( const DateTime & two ) const
{
  return( DateRange::compare( two ) );
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
  

// Revision Log:
//
// 
// %PL%
// 
// $Log$
// Revision 6.1  2003/08/09 11:22:40  houghton
// Changed to version 6
//
// Revision 5.5  2003/08/09 11:20:58  houghton
// Changed ver strings.
//
// Revision 5.4  2003/06/25 08:49:01  houghton
// Change: rename in method it isIn.
//
// Revision 5.3  2003/05/12 15:51:07  houghton
// Added in( const DateTime & dateTwo ) const.
//
// Revision 5.2  2001/07/26 19:29:00  houghton
// *** empty log message ***
//
// Revision 5.1  2000/05/25 10:33:14  houghton
// Changed Version Num to 5
//
// Revision 4.1  1997/09/17 15:12:15  houghton
// Changed to Version 4
//
// Revision 3.5  1997/09/17 14:10:14  houghton
// Renamed StlUtilsUtils.hh to StlUtilsMisc.hh
//
// Revision 3.4  1997/09/17 11:08:13  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.3  1997/08/24 21:56:37  houghton
// Changed getDayOfWeek to return a 'DayOfWeek' (was int).
//
// Revision 3.2  1997/07/18 19:11:07  houghton
// Cleanup.
// Added compare( const DateTime & two ) const to eliminate compiler warnings.
//
// Revision 3.1  1996/11/14 01:23:33  houghton
// Changed to Release 3
//
// Revision 2.4  1996/11/06 18:03:53  houghton
// StlUtils.hh renamed to StlUtilsUtils.hh
//
// Revision 2.3  1996/04/27 12:56:43  houghton
// Removed unneeded includes.
//
// Revision 2.2  1995/12/04 11:17:19  houghton
// Bug Fix - Can now compile with out '-DSTLUTILS_DEBUG'.
//
// Revision 2.1  1995/11/10  12:40:25  houghton
// Change to Version 2
//
// Revision 1.4  1995/11/05  14:44:27  houghton
// Ports and Version ID changes
//
//
