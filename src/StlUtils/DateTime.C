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
// Revision 1.5  1995/02/20 14:24:25  houghton
// Linux port and Fix bugs in DateTime found with new test.
//
// Revision 1.4  1995/02/13  16:08:35  houghton
// New Style Avl an memory management. Many New Classes
//
// Revision 1.3  1994/08/16  20:50:16  houghton
// fixed datetime output if sec == 0
//
// Revision 1.2  1994/08/15  20:54:53  houghton
// Split Mapped out of mapped avl.
// Fixed a bunch of bugs.
// Fixed for ident of object modules.
// Prep for Rating QA Testing
//
// Revision 1.1  1994/06/06  13:19:37  houghton
// Lib Clue beta version used for Rating 1.0
//
//
static const char * RcsId =
"$Id$";

#include <iostream.h>

#include "DateTime.hh"

#include <ctype.h>

DateTime::~DateTime( void )
{
}

//
// Note: the epoch (1/1/1970) was a thursday
//
int
DateTime::getDayOfWeek( void ) const
{
  return( ((seconds / SEC_PER_DAY) + 4) % 7  );
}

// isDST - return TRUE if Daylight Savings Time is in effect
Bool
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
	  Bool isDst = FALSE;
	  
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

  return( FALSE );
}

// isDST - return TRUE if Daylight Savings Time is in effect
Bool
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
  return( FALSE );
}

long	DateTime::localSysOffset = 0;

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
  flags.valid = TRUE;

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
	      flags.valid = FALSE;
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
	      flags.valid = FALSE;
	      seconds = 0;
	      return( old );
	    }
	}
    }

  flags.valid = FALSE;
  seconds = 0;
  return( old );
  
}

// setValid - verify input and set
time_t
DateTime::setValid( const char * dateString, const char * fmt )
{
  time_t old = seconds;
  
  if( fmt )
    {
      struct tm tmTime;
      
      tmTime.tm_year = 0;
      tmTime.tm_mon = 0;
      tmTime.tm_mday = 0;
      tmTime.tm_hour = 0;
      tmTime.tm_min = 0;
      tmTime.tm_sec = 0;
      
      if( strptime( dateString, fmt, &tmTime ) )
	{
	  return( setValid( tmTime.tm_year + 1900,
			    tmTime.tm_mon + 1,
			    tmTime.tm_mday,
			    tmTime.tm_hour, tmTime.tm_min, tmTime.tm_sec ) );
	}
      else
	{
	  flags.valid = FALSE;
	  seconds = 0;
	  return( old );
	}
    }
  else
    {
      // note this is a duplication of code in DateStringToTimeT.c
      
      const char * start = dateString;
      const char * end = 0;
      
      if( (end = strchr( start, '/' ) ) == 0 )
	{
	  flags.valid = FALSE;
	  seconds = 0;
	  return( old );
	}

      short month = StringToInt( start, 10, (end - start) );

      start = end + 1;

      if( (end = strchr( start, '/') ) == 0 )
	{
	  flags.valid = FALSE;
	  seconds = 0;
	  return( old );
	}

      short day = StringToInt( start, 10, (end - start)  );

      start = end + 1;

      for( end = start; isdigit( *end ); end++ );

      short year = StringToInt( start, 10, (end - start) );

        
      for( start = end; ! isdigit( *start ) && *start != 0; start++ );

      if( *start == 0 )
	{
	  return( setValid( year, month, day, 0, 0, 0 ) );
	}

      if( (end = strchr( start, ':' ) ) == 0 )
	{
	  flags.valid = FALSE;
	  seconds = 0;
	  return( old );
	}

      short hour = StringToInt( start, 10, (end - start) );

      start = end + 1;

      for( end++ ; isdigit( *end ); end++ );

      if( end == start )
	{
	  flags.valid = FALSE;
	  seconds = 0;
	  return( old );
	}

      short min = StringToInt( start, 10, (end - start) );

      short sec = 0;
      if( *end == ':' )
	{

	  start = end + 1;

	  for( end++; isdigit( *end ); end++ );

	  sec = StringToInt( start, 10, (end - start) );
	}      

      return( setValid( year, month, day, hour, min, sec ) );
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

  seconds -= ((oldYear - 70) * SEC_PER_YEAR ) + (leapCount * SEC_PER_DAY );

  // now add the new year

  if( year > 1900 ) year -= 1900;
  
  if( year < 50 ) year += 100;
  
  leapCount = ((year - 70) + 2) / 4;

  int newIsLeap = IsLeapYear( year );
  if( newIsLeap )
    {
      leapCount--;
    }

  seconds += ((year - 70) * SEC_PER_YEAR ) + (leapCount * SEC_PER_DAY );

  if( oldIsLeap )
    {
      if( ! newIsLeap && oldMonth > 2 )
	{
	  seconds -= SEC_PER_DAY;
	}
    }
  else
    {
      if( newIsLeap && oldMonth > 2 )
	{
	  seconds += SEC_PER_DAY;
	}
    }
  
  flags.tmValid = FALSE;
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

  seconds -= SEC_PER_DAY * MonthDayOfYear[ oldMonth - 1 ];
  
  if( IsLeapYear( getYear() ) && oldMonth > 2 )
    {
      seconds -= SEC_PER_DAY;
    }

  // now add the new month

  seconds += SEC_PER_DAY * MonthDayOfYear[ month - 1 ];

  if( IsLeapYear( getYear() ) && month > 2 )
    {
      seconds += SEC_PER_DAY;
    }

  flags.tmValid = FALSE;
  if( offset ) setTm();
  
  return( old );
}


// getClassName - return the name of this class
const char *
DateTime::getClassName( void ) const
{
  return( "DateTime" );
}

// good - return TRUE if current value is valid
Bool
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
  
// setTmOffset - set the tm struct using a local time offset
void
DateTime::setTmOffset( void )
{
  const char * oldZone = getenv( "TZ" );

  if( flags.dstKnown && flags.dst )
    {
      seconds -= offset;
      offset -= SEC_PER_HOUR;
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
  
  flags.dstKnown = TRUE;
  flags.dst = tm.tm_isdst;
  if( flags.dst )
    {
      seconds -= offset;
      offset += SEC_PER_HOUR;
      seconds += offset;
    }     
}

	  
ostream & operator<<( ostream & dest, const DateTime & time )
{
  dest << time.getString();
  
  return( dest );
}




//
//              This software is the sole property of
// 
//                 The Williams Companies, Inc.
//                        1 Williams Center
//                          P.O. Box 2400
//        Copyright (c) 1994 by The Williams Companies, Inc.
// 
//                      All Rights Reserved.  
// 
//
