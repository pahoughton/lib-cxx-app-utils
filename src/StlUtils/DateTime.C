//
// File:        DateTime.C
// Project:	StlUtils
// Desc:        
//
//  Compiled sources for DateTime
//  
// Author:      Paul Houghton - (paul.houghton@wcom.com)
// Created:     02/24/94 06:46 
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    $Author$
//  Last Mod:	    $Date$
//  Version:	    $Revision$
//

#include "DateTime.hh"
#include "RegexScan.hh"
#include "Str.hh"
#include <cstdio>

#if defined( STLUTILS_DEBUG )
#include <DateTime.ii>
#endif


STLUTILS_VERSION(
  DateTime,
  "$Id$" );


RegexScan
DateTime::strPattern(
  "[^0-9]*" "([0-9]+)/([0-9]+)/([0-9]+)"
  "[^0-9]*" "([0-9]*):*([0-9]*):*([0-9]*)" );

long	DateTime::localSysOffset = 0;


DateTime::~DateTime( void )
{
}

//
// Note: the epoch (1/1/1970) was a thursday
//
DayOfWeek
DateTime::getDayOfWeek( void ) const
{
  return( (DayOfWeek)( ((seconds / SecPerDay) + Thursday) % 7 ));
}

// isDST - return true if Daylight Savings Time is in effect
bool
DateTime::isDST( void ) const
{
  if( flags.dstKnown )
    {
      return( flags.dst );
    }
  else
    {
      if( offset )
	{
	  // we have an offset so assume 'seconds' is
	  // gmt + offset, grab the 'localtime' and 
	  // get the dst from it.

	  static char * zone = 0;
	  static char * delZone = 0;
	  const char * oldZone = getenv( "TZ" );
	  bool isDst = false;
	  
	  if( timeZoneName && strcmp( oldZone, timeZoneName ) )
	    {
	      delZone = zone;
	      zone = new char[30];
	      
	      strcpy( zone, "TZ=" );
	      strcat( zone, timeZoneName );
	      putenv( zone );
	  
	      time_t 	sec = seconds;
	      sec -= offset;
	      isDst = localtime( &sec )->tm_isdst;
	  
	      strcpy( zone, "TZ=" );
	      strcat( zone, oldZone );
	      putenv( oldZone );

	      if( delZone ) delete delZone;
	    }
	  else
	    {
	      time_t sec = seconds;
	      sec -= offset;
	      isDst = localtime( &sec )->tm_isdst;
	    }	  
	  return( isDst );
	}
    }

  return( false );
}

// isDST - return true if Daylight Savings Time is in effect
bool
DateTime::isDST( void )
{
  if( flags.dstKnown )
    {
      return( flags.dst );
    }
  else
    {
      if( offset )
	{
	  setTm();
	  return( flags.dst );
	}
    }
  return( false );
}

// getGmtOffset - return the gmt offset for 'timeZone'
//  NOTE: the 'timezone' value is converted to a
//  	  negative value. It seems more natural to me to add
//  	  the offset that to subtract it, so I convert it up front.
long
DateTime::getGmtOffset( const char * timeZone )
{
  if( ! timeZone && localSysOffset )
    {
      return( localSysOffset );
    }


  if( timeZone )
    {
      const char * oldZone = getenv( "TZ" );

      if( strcmp( oldZone, timeZone ) )
	{      
	  static char * zone = 0;
	  static char * delZone = 0;
      
	  delZone = zone;
	  zone = new char[30];
	  
	  strcpy( zone, "TZ=" );
	  strcat( zone, timeZone);
	  putenv( zone );

	  tzset();

	  long tzOffset = - timezone;
	  
	  strcpy( zone, "TZ=" );
	  strcat( zone, oldZone );
	  putenv( zone );

	  tzset();
	  
	  if( delZone ) delete delZone;

	  return( tzOffset );
	}
    }

  tzset();
  localSysOffset = - timezone;

  return( localSysOffset );
}

// getSysTimeZone - get the name of the current system time zone
const char *
DateTime::getSysTimeZone( void )
{
  return( getenv( "TZ" ) );
}

const char *
DateTime::getYYYYMMDD( void ) const
{
  static char yyyymmdd[10];

  const struct tm * tmTime = ( flags.tmValid ? &tm : gmtime( &seconds ) );
  
  sprintf( yyyymmdd, "%04d%02d%02d",
	   tmTime->tm_year + 1900,
	   tmTime->tm_mon + 1,
	   tmTime->tm_mday );

  return( yyyymmdd );
}

	   
// setValid - verify input and set 
time_t
DateTime::setValid( 
  int year,
  int month,
  int day,
  int hour,
  int min,
  int sec
  )
{
  time_t old = seconds;
  flags.valid = true;

  offset = 0;
  timeZoneName = 0;

  if( ( ( year >= 0 && year <= 99 )
	|| ( year <= MaxYear && year >= MinYear ) )
      && ( month > 0 && month <= 12 )
      && ( hour >= 0 && hour < 24 )
      && ( min >= 0 && min < 60 )
      && ( sec >= 0 && sec < 60 ) )
    {
      if( day  > DaysInMonth[ month-1 ] )
	{
	  if( IsLeapYear( year ) &&
	      month == 2 &&
	      day == (DaysInMonth[ month-1 ]+1 ) )
	    {
	      //ok its feb 29 of a leap year
	      return( set( year, month, day, hour, min, sec ) );
	    }
	  else
	    {
	      flags.valid = false;
	      seconds = 0;
	      return( old );
	    }
	}
      else
	{
	  if( day > 0 )
	    {
	      return( set( year, month, day, hour, min, sec ) );
	    }
	  else
	    {
	      flags.valid = false;
	      seconds = 0;
	      return( old );
	    }
	}
    }

  flags.valid = false;
  seconds = 0;
  return( old );
  
}

// setValid - verify input and set
time_t
DateTime::setValid( const char * dateString, const char * fmt )
{
  struct tm tmTime;

  memset( &tmTime, 0, sizeof( tm ) );
  
  toTm( tmTime, dateString, fmt );

  return( setValid( tmTime.tm_year + 1900,
		    tmTime.tm_mon + 1,
		    tmTime.tm_mday,
		    tmTime.tm_hour,
		    tmTime.tm_min,
		    tmTime.tm_sec ) );
}      

time_t
DateTime::setValidYYMMDD( const char * yymmdd )
{
  int year;
  int month;
  int dom;

  if( StringTo( year, yymmdd, 10, 2 )
      && StringTo( month, yymmdd + 2, 10, 2 )
      && StringTo( dom, yymmdd + 4, 10, 2 ) )
    {
      return( setValid( year, month, dom, 0, 0, 0 ) );
    }
  else
    {
      time_t old = seconds;
      
      flags.valid = false;
      seconds = 0;
      return( old );
    }  
}

time_t
DateTime::setValidYYYYMMDD( const char * yyyymmdd )
{
  int year;
  int month;
  int dom;

  if( StringTo( year, yyyymmdd, 10, 4 )
      && StringTo( month, yyyymmdd + 4, 10, 2 )
      && StringTo( dom, yyyymmdd + 6, 10, 2 ) )
    {
      if( ( year <= MaxYear && year >= MinYear ) )
	{
	  return( setValid( year, month, dom, 0, 0, 0 ) );
	}
      else
	{
	  time_t old = seconds;
	  
	  flags.valid = false;
	  seconds = 0;
	  return( old );
	}
    }
  else
    {
      time_t old = seconds;
      
      flags.valid = false;
      seconds = 0;
      return( old );
    }  
}

// setYear - set the year
time_t
DateTime::setYear( short year )
{
  time_t old = seconds;

  int oldMonth = getMonth();
  // first get the year
  short oldYear = getYear() - 1900;

  // now take it away from seconds

  short leapCount = ((oldYear - 70) + 2) / 4;

  int oldIsLeap = IsLeapYear( oldYear );

  if( oldIsLeap )
    {
      leapCount--;
    }

  seconds -= ((oldYear - 70) * SecPerYear ) + (leapCount * SecPerDay );

  // now add the new year

  if( year > 1900 ) year -= 1900;
  
  if( year < 50 ) year += 100;
  
  leapCount = ((year - 70) + 2) / 4;

  int newIsLeap = IsLeapYear( year );
  if( newIsLeap )
    {
      leapCount--;
    }

  seconds += ((year - 70) * SecPerYear ) + (leapCount * SecPerDay );

  if( oldIsLeap )
    {
      if( ! newIsLeap && oldMonth > 2 )
	{
	  seconds -= SecPerDay;
	}
    }
  else
    {
      if( newIsLeap && oldMonth > 2 )
	{
	  seconds += SecPerDay;
	}
    }
  
  flags.tmValid = false;
  if( offset ) setTm();
  
  return( old );
}

// setMonth - set the month
time_t
DateTime::setMonth( short month )
{
  time_t old = seconds;
  // this is kinda risky

  // take away  the old month

  short oldMonth = getMonth();

  seconds -= SecPerDay * MonthDayOfYear[ oldMonth - 1 ];
  
  if( IsLeapYear( getYear() ) && oldMonth > 2 )
    {
      seconds -= SecPerDay;
    }

  // now add the new month

  seconds += SecPerDay * MonthDayOfYear[ month - 1 ];

  if( IsLeapYear( getYear() ) && month > 2 )
    {
      seconds += SecPerDay;
    }

  flags.tmValid = false;
  if( offset ) setTm();
  
  return( old );
}

// setTimeZone - adjust time for timezone 'zone'
long
DateTime::setTimeZone( const char * zone )
{
  seconds -= offset;  
  flags.dstKnown = false;
  flags.tmValid = false;
  offset = getGmtOffset( zone );
  timeZoneName = zone;
  seconds += offset;
  setTm();
  return( offset );
}


// compare - return the difference between me and 'two'
int
DateTime::compare( const DateTime & two ) const
{
  return( (*this < two ) ? -1 :
	  (*this == two ) ? 0 : 1 );
}

ostream &
DateTime::toStream( ostream & dest ) const
{
  dest << getString();
  
  return( dest );
}  
  
// good - return true if current value is valid
bool
DateTime::good( void ) const
{
  return( flags.valid );
}

// error - return a string description for detected errors
const char *
DateTime::error( void ) const
{
  static Str errStr;
  errStr.reset();

  errStr << getClassName();

  if( good() )
    {
      errStr << ": Ok";
    }
  else
    {
      errStr << ": invalid value";
    }
  return( errStr.cstr() );  
}
  
// getClassName - return the name of this class
const char *
DateTime::getClassName( void ) const
{
  return( "DateTime" );
}

// setTmOffset - set the tm struct using a local time offset
void
DateTime::setTmOffset( void )
{
  const char * oldZone = getenv( "TZ" );

  if( flags.dstKnown && flags.dst )
    {
      seconds -= offset;
      offset -= SecPerHour;
      seconds += offset;
    }     

  if( timeZoneName )
    {      
      static char * zone = 0;
      static char * delZone = 0;
      
      delZone = zone;
      zone = new char[30];
      
      strcpy( zone, "TZ=" );
      strcat( zone, timeZoneName );
      putenv( zone );
	  
      seconds -= offset;
      memcpy( &tm, localtime( &seconds ), sizeof( struct tm ) );
      seconds += offset;

      strcpy( zone, "TZ=" );
      strcat( zone, oldZone );
      putenv( zone );

      if( delZone ) delete delZone;
    }
  else
    {
      seconds -= offset;
      memcpy( &tm, localtime( &seconds ), sizeof( struct tm ) );
      seconds += offset;
    }
  
  flags.dstKnown = true;
  flags.dst = tm.tm_isdst;
  if( flags.dst )
    {
      seconds -= offset;
      offset += SecPerHour;
      seconds += offset;
    }     
}

size_t
DateTime::getBinSize( void ) const
{
  return( sizeof( seconds ) );
}

ostream &
DateTime::write( ostream & dest ) const
{
  time_t  value = seconds - offset;
  
  dest.write( (char *)&value, sizeof( value ) );
  return( dest );
}

istream &
DateTime::read( istream & src )
{
  resetFlags();
  if( ! src.read( (char *)&seconds, sizeof( seconds ) ).good() )
    {
      flags.valid = false;
    }
  return( src );
}  


const char *
DateTime::fromTm( char * buf, const char * fmt, const struct tm * tmTime ) const
{
  static char 	dateString[50];

  char * str = (buf) ? buf : dateString;

  if( fmt )
    {
      strftime( str, 50, fmt, tmTime );
    }
  else
    {
      if( tmTime->tm_year < 50 || tmTime->tm_year > 99 )
	{
	  sprintf( str, "%02d/%02d/%04d %02d:%02d:%02d",
		   tmTime->tm_mon + 1,
		   tmTime->tm_mday,
		   1900 + tmTime->tm_year,
		   tmTime->tm_hour,
		   tmTime->tm_min,
		   tmTime->tm_sec );
	}
      else
	{
	  sprintf( str, "%02d/%02d/%02d %02d:%02d:%02d",
		   tmTime->tm_mon + 1,
		   tmTime->tm_mday,
		   tmTime->tm_year,
		   tmTime->tm_hour,
		   tmTime->tm_min,
		   tmTime->tm_sec );
	}
    }
  return( str );
}

bool
DateTime::toTm( struct tm & tmTime, const char * str, const char * fmt ) const
{
  if( str == 0 )
    {
      return( false );
    }

  if( fmt )
    {
      return( strptime( (char *)str, fmt, &tmTime ) != 0 );
    }
  else
    {
      if( strPattern.search( str ) && strPattern.matchCount() > 0 )
	{
	  if( strPattern.matchLength( 1 ) )
	    {
	      tmTime.tm_mon = StringToInt( str + strPattern.matchStart( 1 ),
					   10,
					   strPattern.matchLength( 1 ) );
	      tmTime.tm_mon--;
	    }

	  if( strPattern.matchLength( 2 ) )
	    {
	      tmTime.tm_mday = StringToInt( str + strPattern.matchStart( 2 ),
					    10,
					    strPattern.matchLength( 2 ) );
	    }

	  if( strPattern.matchLength( 3 ) )
	    {
	      tmTime.tm_year = StringToInt( str + strPattern.matchStart( 3 ),
					    10,
					    strPattern.matchLength( 3 ) );
	      
	      tmTime.tm_year = ( ( tmTime.tm_year > 1900 ) ?
				 tmTime.tm_year - 1900 :
				 tmTime.tm_year < 50 ?
				 tmTime.tm_year += 100 :
				 tmTime.tm_year );
	    }

	  if( strPattern.matchLength( 4 ) )
	    {
	      tmTime.tm_hour = StringToInt( str + strPattern.matchStart( 4 ),
					    10,
					     strPattern.matchLength( 4 ) );
	    }

	  
	  if( strPattern.matchLength( 5 ) )
	    {
	      tmTime.tm_min = StringToInt( str + strPattern.matchStart( 5 ),
					   10,
					   strPattern.matchLength( 5 ) );
	    }

	  
	  if( strPattern.matchLength( 6 ) )
	    {
	      tmTime.tm_sec = StringToInt( str + strPattern.matchStart( 6 ),
					   10,
					   strPattern.matchLength( 6 ) );
	    }
	  return( true );
	}
    }
  
  return( false );
}      
  
time_t
DateTime::toTimeT( const char * str, const char * fmt ) const
{

  struct tm tmTime;
  memset( &tmTime, 0, sizeof( tmTime ) );
  
  if( toTm( tmTime, str, fmt ) )
    {
      return( toTimeT( 1900 + tmTime.tm_year,
		       tmTime.tm_mon + 1,
		       tmTime.tm_mday,
		       tmTime.tm_hour,
		       tmTime.tm_min,
		       tmTime.tm_sec ) );
    }
  else
    {
      return( 0 );
    }
}

time_t
DateTime::toTimeT(
  int 	year,
  int 	month,
  int	day,
  int 	hour,
  int	min,
  int	sec
  ) const
{
  long  secs = 0;
  long	leapCount = 0;

  if( year >= 0 )
    {
      // this is a best guess for 2 digit years
      if( year > 100 )
	year = year;
      else
	year = 1900 + ( year < 50 ? year + 100 : year );

      // safty valve - if year is out of range, use min/max
      // posible time_t value
      if( year > MaxYear )
	return( MaxTimeT );
      else
	if( year < MinYear )
	  return( MinTimeT );
      
		
      // 1968 was a leap year
      // leap years are every 4 years except centuries unless the centruy
      // is divisable by 400 (i.e. 1600 & 2000 are leap years and
      // 1700, 1800, 1900 are not leap years).
      // 
      leapCount = ( ((abs( year - 1970 ) + 2) / 4)
		    - (abs( year - 1900 ) / 100)
		    );

      leapCount += ( ( year < 2000  ?
			abs( year - 2000 ) / 400 :
			abs( year - 1600 ) / 400 ));

      if( IsLeapYear( year ) && year > 1970 )
	-- leapCount;
      
      if( year < 1970 )
	leapCount *= -1;
      
      secs = ((year - 1970) * SecPerYear) + (leapCount * SecPerDay);
      
    }

  if( month )
    {
      secs += SecPerDay * MonthDayOfYear[ month - 1 ];
      
      if( IsLeapYear( year ) && month > 2 )
	{
	  secs += SecPerDay;
	}
    }

  if( day )
    {
      day--;
  
      secs += SecPerDay * day;
    }

  
  secs += ( (hour * 60 * 60 ) + (min * 60) + sec );

  return( secs );
}

ostream &
DateTime::dumpInfo(
  ostream &	dest,
  const char *  prefix,
  bool		showVer
  ) const
{
  if( showVer )
    dest << DateTime::getClassName() << ":\n"
	 << DateTime::getVersion() << '\n';

  if( ! DateTime::good() )
    dest << prefix << "Error: " << DateTime::error() << '\n';
  else
    dest << prefix << "Good!" << '\n';

  dest << prefix << "date string:    ";
  DateTime::toStream( dest );
  dest << '\n';

  dest << prefix << "localSysOffset: " << localSysOffset << '\n'
    ;
  if( timeZoneName )
    dest << prefix << "timeZoneName:   " << timeZoneName << '\n'
      ;

  dest << prefix << "flags.valid:    " << flags.valid << '\n'
       << prefix << "flags.dstKnown: " << flags.dstKnown << '\n'
       << prefix << "flags.dst:      " << flags.dst << '\n'
       << prefix << "flags.tmValid:  " << flags.tmValid << '\n'
    ;
  
  if( flags.tmValid )
    dest << prefix << "tm.tm_year:     " << tm.tm_year << '\n'
	 << prefix << "tm.tm_mon:      " << tm.tm_mon << '\n'
	 << prefix << "tm.tm_mday:     " << tm.tm_mday << '\n'
	 << prefix << "tm.tm_hour:     " << tm.tm_hour << '\n'
	 << prefix << "tm.tm_min:      " << tm.tm_min << '\n'
	 << prefix << "tm.tm_sec:      " << tm.tm_sec << '\n'
	 << prefix << "tm.tm_wday:     " << tm.tm_wday << '\n'
	 << prefix << "tm.tm_yday:     " << tm.tm_yday << '\n'
	 << prefix << "tm.tm_isdst:    " << tm.tm_isdst << '\n'
      ;

  dest << prefix << "seconds:        " << seconds << '\n'
    ;
  
  return( dest  );
}

const char *
DateTime::getVersion( bool withPrjVer ) const
{
  return( version.getVer( withPrjVer ) );
}

// Revision Log:
//
// $Log$
// Revision 4.4  1998/01/22 18:29:58  houghton
// Added setValidYYYYMMDD().
//
// Revision 4.3  1998/01/09 10:36:34  houghton
// Bug-Fix: setValid() year <= 99 is ok (was < 99)
// Bug-Fix: set() if year >= 0 is ok (was !- 0).
//
// Revision 4.2  1998/01/05 13:20:02  houghton
// Added getYYYYMMDD()
// Added setValidYYMMDD()
//
// Revision 4.1  1997/09/17 15:12:17  houghton
// Changed to Version 4
//
// Revision 3.6  1997/09/17 11:08:15  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.5  1997/08/24 22:07:42  houghton
// Cleanup comments.
// Changed getDayOfWeek to return a DayOfWeek.
// Changed getString to return a 4 digit year if the year is before 1950
//     or after 1999.
// Bug-Fix: toTm( struct tm &, const char * str, const char * fmt ) const
//     if 'fmt' was used, would return true even if an error occured.
// Bug-Fix: toTimeT(  const char * str, const char * fmt ) const
//     the range of the year was not being verified. Fixed.
// Bug-Fix: toTimeT( year, month, day, hour, min, sec ) const
//     complete rework now verifies the year is in range and returns
//     either MinTimeT or MaxTimeT if it is not. Also dates prior to 1970
//     were not being handled correctly.
//
// Revision 3.4  1997/03/21 15:37:08  houghton
// Bug-Fix: setTimeZone was not resetting the localOffset.
//
// Revision 3.3  1997/01/18 17:28:12  houghton
// Minor cleanup. changed a local var name from offset to tzOffset. There
//   is a class var with the name 'offset'.
//
// Revision 3.2  1996/11/20 12:11:46  houghton
// Removed support for BinStream.
//
// Revision 3.1  1996/11/14 01:23:36  houghton
// Changed to Release 3
//
// Revision 2.4  1996/05/01 10:58:59  houghton
// Bug-Fix: gcc did not like the flags being a char changed to int.
//
// Revision 2.3  1996/04/27 12:58:26  houghton
// Removed unneeded includes.
//
// Revision 2.2  1995/12/04 11:17:20  houghton
// Bug Fix - Can now compile with out '-DSTLUTILS_DEBUG'.
//
// Revision 2.1  1995/11/10  12:40:30  houghton
// Change to Version 2
//
// Revision 1.9  1995/11/05  14:44:29  houghton
// Ports and Version ID changes
//
//
//
