//
// File:        DateTime.cc
// Desc:        
//              
//
// Author:      Paul Houghton x2309 - (houghton@shoe)
// Created:     02/24/94 06:46 
//
// Revision History:
//
// $Log$
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
// Bug Fix - Can now compile with out '-DCLUE_DEBUG'.
//
// Revision 2.1  1995/11/10  12:40:30  houghton
// Change to Version 2
//
// Revision 1.9  1995/11/05  14:44:29  houghton
// Ports and Version ID changes
//
//
//

#if !defined( CLUE_SHORT_FN )
#include "DateTime.hh"
#include "RegexScan.hh"
#include "Str.hh"
#include <cstdio>
#else
#include "DateTime.hh"
#include "RxScan.hh"
#include "Str.hh"
#include <cstdio>
#endif

#if defined( CLUE_DEBUG )
#include <DateTime.ii>
#endif


CLUE_VERSION(
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
int
DateTime::getDayOfWeek( void ) const
{
  return( ((seconds / SecPerDay) + 4) % 7  );
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

	  long offset = - timezone;
	  
	  strcpy( zone, "TZ=" );
	  strcat( zone, oldZone );
	  putenv( zone );

	  tzset();
	  
	  if( delZone ) delete delZone;

	  return( offset );
	}
    }

  if( ! localSysOffset )
    {
      tzset();
      localSysOffset = - timezone;
    }

  return( localSysOffset );
}

// getSysTimeZone - get the name of the current system time zone
const char *
DateTime::getSysTimeZone( void )
{
  return( getenv( "TZ" ) );
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
  
  if( ( ( year > 1970 && year < 2050 ) ||
	( year >= 0 && year < 50 ) ||
	( year > 70 && year < 100 ) ) &&
      ( month > 0 && month <= 12 ) &&
      ( hour >= 0 && hour < 24 ) &&
      ( min >= 0 && min < 60 ) &&
      ( sec >= 0 && sec < 60 ) )
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

BinStream &
DateTime::write( BinStream & dest ) const
{
  time_t  value = seconds - offset;
  
  dest.write( value );
  return( dest );
}


BinStream &
DateTime::read( BinStream & src )
{
  resetFlags();
  if( ! src.read( seconds ).good() )
    {
      flags.valid = false;
    }
  return( src );
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
      sprintf( str, "%02d/%02d/%02d %02d:%02d:%02d",
	       tmTime->tm_mon + 1,
	       tmTime->tm_mday,
	       tmTime->tm_year,
	       tmTime->tm_hour,
	       tmTime->tm_min,
	       tmTime->tm_sec );
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
      strptime( (char *)str, fmt, &tmTime );
      return( true );
    }
  else
    {
      if( strPattern.search( str ) && strPattern.matchCount() > 0 )
	{
	  if( strPattern.matchLength( 1 ) )
	    {
	      tmTime.tm_mon = StringToInt( str + strPattern.matchStart( 1 ), 10,
					   strPattern.matchLength( 1 ) );
	      tmTime.tm_mon--;
	    }

	  if( strPattern.matchLength( 2 ) )
	    {
	      tmTime.tm_mday = StringToInt( str + strPattern.matchStart( 2 ), 10,
					    strPattern.matchLength( 2 ) );
	    }

	  if( strPattern.matchLength( 3 ) )
	    {
	      tmTime.tm_year = StringToInt( str + strPattern.matchStart( 3 ), 10,
					    strPattern.matchLength( 3 ) );
	      tmTime.tm_year = ( ( tmTime.tm_year > 1900 ) ?
				 tmTime.tm_year - 1900 :
				 tmTime.tm_year < 50 ?
				 tmTime.tm_year += 100 :
				 tmTime.tm_year );
	    }

	  if( strPattern.matchLength( 4 ) )
	    {
	      tmTime.tm_hour = StringToInt( str + strPattern.matchStart( 4 ), 10,
					     strPattern.matchLength( 4 ) );
	    }

	  
	  if( strPattern.matchLength( 5 ) )
	    {
	      tmTime.tm_min = StringToInt( str + strPattern.matchStart( 5 ), 10,
					   strPattern.matchLength( 5 ) );
	    }

	  
	  if( strPattern.matchLength( 6 ) )
	    {
	      tmTime.tm_sec = StringToInt( str + strPattern.matchStart( 6 ), 10,
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
      return( toTimeT( tmTime.tm_year,
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
  int	leapCount = 0;
  
  if( year )
    {      
      if( year > 1900 )
	{
	  year = year - 1900;
	}
      else
	{
	  if( year < 50 )
	    {
	      year = year + 100;
	    }
	}

      leapCount = ((year - 70) + 2) / 4;

      if( IsLeapYear( year ) )
	{
	  leapCount--;
	}
  
      secs = ((year - 70) * SecPerYear) + (leapCount * SecPerDay );
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
