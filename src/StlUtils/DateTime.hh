#ifndef _DateTime_hh_
#define _DateTime_hh_
//
// File:        DateTime.hh
// Desc:        
//
//  The DateTime class provides many methods for managing and coverting
//  date/time values. A time_t value is used inside the class for
//  storage. Most methods do NOT varify the values passed.
//
//  Quick Start:
//
//  	DateTime    	dt( time(0) );
//
//  	cout << dt << endl; 	// output gmt time
//
//  	dt.setTimeZone();	// set to local time
//
//  	cout << dt << endl; 	// output local time;
//
//  	dt.addDay( 5 );     	// add 5 days to the datetime
//
//  	long dayOfWeek = dt.getDayOfWeek();
//
//  DataTypes:
//
//  	DateTime    class
//
//  Constructors:
//
//  	DateTime( time_t setTime = 0, Bool addLocal = FALSE );
//  	    use 'setTime' for the inital value. If addLocal is TRUE,
//  	    the local (according to TZ) time zone offset will be added.
//
//  	DateTime( time_t day, time_t timeOfDay );
//  	    use 'day' and 'timeOfDay' to set the initial value.
//
//  	DateTime( const char * yymmdd, const char * hhmmss )
//  	    set the initial value by converting the 'yymmdd' and
//  	    'hhmmss' strings.
//
//  	DateTime( int year, int month, int day,
//  	    	  int hour = 0, int min = 0, int sec = 0 )
//  	    set the initial value from year, month, day, hour, min & sec.
//  	    The year can be either 2 or 4 digits (95 or 1995). The month
//  	    must be between 1 -> 12. The day is the day of the month and
//  	    has a range of 1 -> 31.
//
//  	DateTime( const struct tm & tmTime )
//  	    set the initial value from the tmTime. 'tmTime' is translated
//  	    as a 'GMT' value.
//
//  	DateTime( const char * timeString )
//  	    set the initial from 'timeString' the format must be
//  	    '2/20/95 13:40:50'. The time portion is not required and
//  	    leading '0' are ignored.
//
//  Destructors:
//
//  	~DateTime( void )
//  	    no special actions taken.
//
//  Public Interface:
//
//  	time_t
//  	getTimeT( void ) const;
//  	    return the current value as a time_t.
//
//  	long
//  	getSecOfDay( void ) const;
//  	    return the number of seconds since midnight. (0 -> 86399)
//
//  	short
//  	getHour( void ) const;
//  	    return the hour of the day in 24 hour format. (0 -> 23)
//
//  	short
//  	getMinute( void ) const;
//  	    return the minute of the hour. (0 -> 59)
//
//  	short
//  	getSecond( void ) const;
//  	    return the second of the minute. (0 -> 59)
//
//  	virtual
//  	short
//  	getDayOfWeek( void ) const;
//  	    return the day of the week. (sunday = 0) (0->6)
//
//  	short
//  	getDayOfyear( void ) const;
//  	short
//  	getDayOfYear( void );
//  	    return day of the year. ( 1 -> 366 )
//  	    non-const version sets the internal tm to improve performance.
//
//  	short
//  	getDayOfMonth( void ) const;
//  	short
//  	getDayOfMonth( void );
//  	    return the day of the month. (1 -> 31)
//  	    non-const version sets the internal tm to improve performance.
//
//  	short
//  	getMonth( void ) const
//  	short
//  	getMonth( void )
//  	    return the month of the year. (1 -> 12)
//  	    non-const version sets the internal tm to improve performance.
//
//  	short
//  	getYearOfCentury( void ) const
//  	short
//  	getYearOfCentury( void ) const
//  	    return the year of the century. (0 -> 99)
//  	    Both 1930 and 2030 will return '30'.
//  	    non-const version sets the internal tm to improve performance.
//
//  	short
//  	getYear( void ) const;
//  	short
//  	getYear( void )
//  	    return the year. ( all four digits - 1995, 2005 )
//  	    non-const version sets the internal tm to improve performance.
//
//  	const char *
//  	getString( char * buffer = 0, const char * fmt = 0 )
//  	const char *
//  	getString( char * buffer = 0, const char * fmt = 0 ) const
//  	    return a string representation of the date/time. If
//  	    'buffer' is not 0, the string will be placed in it, otherwise
//  	    a static internal bufferr will be used. If fmt is 0, the default
//  	    format ( '02/05/95 03:05:05' ) will be used, otherwise strftime
//  	    will use 'fmt' to determine the format of the string.
//
//  	short
//  	getOffset( void ) const
//  	    return the current timezone offset being used. Normally this
//  	    is 0. It is set by calls to 'setTimeZone'
//
//  	Bool
//  	isLocal( void ) const
//  	    return TRUE if a timezone has been set.
//
//  	Bool
//    	isDST( void )
//  	Bool
//  	isDST( void )
//  	    return TRUE if a timezone is set and daylight savings time is
//  	    in effect.
//
//  	const char *
//  	getTimeZone( void ) const
//  	    return the name of the timezone that has been set. If no
//  	    timezone is set, 0 is returned.
//
//  	time_t
//  	setTimeT( time_t timeSec = 0 )
//  	    set the date/time to the specified value. Any timezone is
//  	    reset to GMT.
//  	    Returns the previous date/time value.
//
//     	time_t
//  	set( time_t timeSec, Bool addLocal = FALSE )
//  	    set the date/time to the specific value. if allLocal
//  	    is TRUE, the local timezone offset ( according to TZ env var )
//  	    will be added to the time. Any timezone is reset to GMT.
//  	    Returns the previous date/time value.
//
//  	time_t
//  	set( const char * dateString, const char * fmt = 0 )
//  	    set the date/time by converting the'dateString'. If 'fmt' is 0,
//  	    the string is expected to be int '1/5/94 03:04:00' format.
//  	    When using this format, neither the seconds, nor the time is
//  	    not requried (ie 1/1/92 & 1/1/95 05:00 is ok). If 'fmt' is
//  	    not 0, strptime will use it to translate the string. Any timezone
//  	    is reset to GMT.
//  	    Returns the previous date/time value.
//
//  	time_t
//  	set( int year, int month, int day,
//  	     int hour = 0, int min = 0, int sec = 0)
//  	    set the date/time from year, month, day, hour, min, sec. Any
//  	    timezone is reset to GMT.
//  	    Returns the previous date/time value.
//
//  	time_t
//  	set( const struct tm & tmTime )
//  	    set the date/time from the 'tmTime' structure. The values in
//  	    'tmTime' are treated as GMT values. The timezone is reset to
//  	    GMT.
//  	    Returns the previous date/time value.
//
//  	time_t
//  	setValid( int year, int month, int day,
//  	    	  int hour = 0, int min = 0, int sec = 0 )
//  	    set the date/time according to year, month, day, hour, min & sec.
//  	    These value are checked to be sure they are in range. If
//  	    any value is not in range, the date/time value is set to 0
//  	    and a flag is set so 'good()' will return FALSE. The year
//  	    range has been limited to 1970 -> 2050, 0 -> 50, 70 -> 99.
//  	    The timezone is reset to GMT.
//  	    Returns the previous date/time value.
//
//  	time_t
//  	setValid( const char * dateString, const char * fmt = 0 )
//  	    set the date/time by converting the'dateString'. If 'fmt' is 0,
//  	    the string is expected to be int '1/5/94 03:04:00' format.
//  	    When using this format, neither the seconds, nor the time is
//  	    not requried (ie 1/1/92 & 1/1/95 05:00 is ok). If 'fmt' is
//  	    not 0, strptime will use it to translate the string.
//  	    The values are checked to be sure they are in range. If
//  	    any value is not in range, the date/time value is set to 0
//  	    and a flag is set so 'good()' will return FALSE. The timezone
//  	    is reset to GMT.
//  	    Returns the previous date/time value.
//
//  	time_t
//  	setYYYYMMDD( const char * yyyymmdd )
//  	    set the 'date' by translating 'yyyymmdd'.  The string does NOT
//  	    have to be NULL terminated. The time and timezone are not modified.
//  	    Example string (19950130)
//  	    Returns the previous date/time value.
//
//  	time_t
//  	setYYMMDD( const char * yymmdd )
//  	    set the 'date' by translating 'yymmdd'.  The string does NOT
//  	    have to be NULL terminated.  'yy' values between 00 and 50 are
//  	    considered to be for the next century (ie 05 = 2005).
//  	    The time and timezone are not modified. Example string (950130)
//  	    Returns the previous date/time value.
//
//  	time_t
//  	setHHMMSS( const char * hhmmss )
//  	    set the 'time' by translating 'hhmmss'. The string does NOT
//  	    have to be NULL terminated. The date and timezone are not
//  	    modified. Example stirng (155005 = 3:50:05 pm)
//  	    Returns the previous date/time value.
//
//  	time_t
//  	setYear( short year )
//  	    set the year. If year is < 50, it is considered to be
//  	    for the next century (10 = 2010). WARNING: If current value
//  	    is 2/29/92 (leap year) and you setYear( 95 ) (non leap year),
//  	    the new value will be 3/1/95. 
//  	    Returns the previous date/time value.
//
//  	time_t
//  	setMonth( short month )
//  	    set the month. WARNING: this function is VERY litteral. If
//   	    the current value is 1/31/95 and you 'setMonth( 6 )' you
//  	    will end up with 7/1/95 (june only has 30 days). It also does
//  	    NOT verify the input value, 'setMonth(13)' will have undefined
//  	    results.
//  	    Returns the previous date/time value.
//
//  	time_t
//  	setDayOfYear( short dayOfYear );
//  	    set the day of the year. WARNING: a value of 370 will increment
//  	    to the next year, day 5.
//  	    Returns the previous date/time value.
//
//  	time_t
//  	setDayOfMonth( short dayOfMonth );
//  	    set day of the month. WARNING: if your current value
//  	    is 2/1/95 and you 'setDayOfMonth( 30 )' you would end up
//  	    with '3/2/95'.
//  	    Returns the previous date/time value.
//
//  	time_t
//  	setHour( short hour )
//  	    set the hour of the day.
//  	    Returns the previous date/time value.
//
//  	time_t
//  	setMinute( short minute )
//  	    set the minute of the hour.
//  	    Returns the previous date/time value.
//
//  	time_t
//  	setSecond( short second )
//  	    set the second of the minute.
//  	    Returns the previous date/time value.
//
//  	long
//  	setTimeZone( const char * zone = 0 )
//  	    set the timezone. If 'zone' is 0, the 'TZ' environment
//  	    variable will be used to determine the correct timezone.
//  	    If 'zone'is not 0, it should be the same format as
//  	    the 'TZ' environment variable (ie CST6CDT).
//  	    Returns the number of seconds offset from GMT that was added
//  	    to the current value.
//
//  	DateTime &
//      add( const DateTime & dt )
//  	    add the DateTime to the current value.
//  	    Returns a referance to self
//
//  	DateTime &
//  	add( long seconds = 1 )
//  	    add the seconds to the date/time value.
//  	    Returns a referance to self
//
//  	DateTime &
//  	addSec( long seconds = 1 )
//  	    add the seconds to the date/time value.
//  	    Returns a referance to self
//
//  	DateTime &
//  	addMin( long minutes = 1 )
//  	    add the minutes to the date/time value
//  	    Returns a referance to self
//
//  	DateTime &
//  	addHour( long hours = 1 )
//  	    add the hours to the date/time value.
//  	    Returns a referance to self
//
//  	DateTime &
//  	addDay( long days = 1 )
//  	    add the days to the datd/time value.
//  	    Returns a referance to self
//
//  	void
//  	setTm( void )
//  	    set the internal tm struct for the current date/time value.
//  	    This call will pre-assign the year, month, day of month,
//  	    and day of year for the current value. I is provided so
//  	    these values do not have to be recalculated for multible
//  	    'get' calls.
//
//   	int
//  	compare( const DateTime & two ) const
//  	    return the difference between 'two' and self. If self
//  	    is > two, a > 0 value will be returned. If self is == two, a
//  	    value of 0 will be returned. If self is < two, a < 0 value will
//  	    be returned.  Only the actuall date/time value is used
//  	    for comparison
//
//  	operator time_t () const;
//  	    return the current date/time as a time_t value.
//
//  	operator const char * () const
//    	    return the current date/time as strings. The getString
//  	    method is used to provide to string.
//
//  	int
//  	operator ==( const DateTime & two ) const;
//  	    return TRUE if 'two' is equal to self. Only the actuall
//  	    date time value is used for comparison.
//
//  	int
//  	operator !=( const DateTime & two ) const;
//  	    return TRUE if 'two' is not equal to self. Only the actuall
//  	    date time value is used for comparison.
//
//  	virtual
//    	const char *
//  	getClassName( void ) const;
//  	    return the name of this class.
//
//  	virtual
//  	Bool
//  	good( void ) const
//  	    return TRUE if no detected errors existe. Only setValid will
//  	    detect and invalid date/time value.
//
//  	virtual
//  	const char *
//  	error( void ) const
//  	    return a string describing the current error state.
//
//  Other Accociated Functions:
//
//  	ostream &
//  	operator <<( ostream & dest, const DateTime & dt );
//  	    send a formated string of the current date/time to 'dest'
//  	    The format is '02/03/95 15:13:03'.
//
//  	long
//  	SecInTimeT( long sec );
//  	    return the second of the minute.
//
//  	long
//  	MinInTimeT( long sec )
//  	    return the minute of the hour.
//
//  	long
//  	HourInTimeT( long sec )
//  	    return the hour of the day.
//
//  	long
//  	HoursInTimeT( long sec )
//  	    return the number of hours.
//
//  	long
//  	DaysInTimeT( long sec )
//  	    return the number of days.
//
//  	long
//  	DateInTimeT( long sec )
//  	    return the date portion only.
//
// Author:      Paul Houghton x2309 - (houghton@shoe)
// Created:     02/09/94 12:24
//
// Revision History:
//
// 
// $Log$
// Revision 1.9  1995/11/05 12:04:28  houghton
// Removed additonal DST stuff
//
// Revision 1.8  1995/09/25  19:16:31  ichudov
// Added hasHistory function to DavlTreeOffset.
//
// Revision 1.7  1995/08/29  19:36:29  ichudov
// DST and MakeDateFromSybase added.
//
// Revision 1.6  1995/07/27  16:18:38  ichudov
// A bug corrected in the constructor of DateTime class.
//
// Revision 1.5  1995/02/20  14:24:25  houghton
// Linux port and Fix bugs in DateTime found with new test.
//
// Revision 1.4  1995/02/13  16:08:35  houghton
// New Style Avl an memory management. Many New Classes
//
// Revision 1.3  1994/09/27  16:58:40  houghton
// Added RoundUp and some DateTime cleanup
//
// Revision 1.2  1994/08/15  20:54:54  houghton
// Split Mapped out of mapped avl.
// Fixed a bunch of bugs.
// Fixed for ident of object modules.
// Prep for Rating QA Testing
//
// Revision 1.1  1994/06/06  13:19:38  houghton
// Lib Clue beta version used for Rating 1.0
//
//

#include <Compare.hh>
#include <Str.hh>

#include <Common.h>

#include <iomanip.h>
#include <stdlib.h>

class DateTime
{
public:

      // Constructors;
  inline DateTime( time_t setTime = 0, Bool addLocal = FALSE );
  inline DateTime( time_t day, time_t timeOfDay );
  inline DateTime( const char * yymmdd, const char * hhmmss );
  inline DateTime( int year, int month, int day,
		   int hour = 0, int min = 0, int sec = 0 );
  inline DateTime( const struct tm & tm );
  inline DateTime( const char * timeString );

  virtual ~DateTime( void );
  
  inline time_t		getTimeT( void ) const;
  inline long		getSecOfDay( void ) const;
  inline short		getHour( void ) const;
  inline short		getMinute( void ) const;
  inline short		getSecond( void ) const;
  virtual int		getDayOfWeek( void ) const;

  //
  // The non const versions set the internal struct tm so
  // the valuse do not have to be recalced. If you need these
  // values repeditivly, you may want to call 'setTm(void)'
  // right after construction to increase access performance
  //
  inline short  	getDayOfYear( void ) const;
  inline short  	getDayOfYear( void );
  inline short		getDayOfMonth( void ) const;
  inline short		getDayOfMonth( void );
  inline short		getMonth( void ) const;
  inline short		getMonth( void );
  inline short		getYearOfCentury( void ) const;
  inline short		getYearOfCentury( void );
  inline short		getYear( void ) const;
  inline short		getYear( void );
  inline const char *	getString( char * buffer = 0, const char * fmt = 0 ) const;
  inline const char *	getString( char * buffer = 0, const char * fmt = 0 );

  inline short	    	getOffset( void ) const;
  inline Bool	    	isLocal( void ) const;
  Bool	    	    	isDST( void ) const;
  Bool	    	    	isDST( void );
  inline const char *	getTimeZone( void ) const;

  static long       	getGmtOffset( const char * timeZone = 0 );
  static const char *	getSysTimeZone( void );

  inline time_t     	setTimeT( time_t timeSec = 0 );
  
  inline time_t		set( time_t timeSec, Bool addLocal = FALSE );
  inline time_t	    	set( const char * dateString, const char * fmt = 0 );
  inline time_t         set( int year, int month, int day,
			     int hour = 0, int min = 0, int sec = 0 );
  inline time_t		set( const struct tm & tmTime );

  time_t            	setValid( int year, int month, int day,
				  int hour = 0, int min = 0, int sec = 0 );
  time_t	    	setValid( const char * dateString, const char * fmt = 0 );
  
  inline time_t		setYYYYMMDD( const char * yyyymmdd);
  inline time_t		setYYMMDD( const char * yymmdd);
  inline time_t		setHHMMSS( const char * hhmmss);
  
  time_t		setYear( short year );
  time_t		setMonth( short month );
  inline time_t		setDayOfYear( short dayOfYear );
  inline time_t		setDayOfMonth( short dayOfMonth );
  inline time_t		setHour( short hour );
  inline time_t		setMinute( short minute );
  inline time_t		setSecond( short second );
  
  inline long	    	setTimeZone( const char * zone = 0 );

  inline DateTime &   	add( const DateTime & dt );
  inline DateTime &   	add( long seconds = 1 );
  inline DateTime &   	addSec( long seconds = 1);
  inline DateTime &   	addMin( long minutes = 1 );
  inline DateTime &   	addHour( long hours = 1 );
  inline DateTime &   	addDay( long days = 1 );
  
  inline void	    setTm( void );

  virtual int	    compare( const DateTime & two ) const;

  inline operator time_t () const;
  inline operator const char * () const;
  
  inline int operator ==( const DateTime & two ) const;
  inline int operator !=( const DateTime & two ) const;

  virtual const char * 	getClassName( void ) const;
  virtual Bool	    	good( void ) const;
  virtual const char *	error( void ) const;

  
protected:

  inline void resetFlags( void );
  
private:
  
  void 	    	    setTmOffset( void );
  
  static long	    localSysOffset;
  
  struct Flags
  {
    char    	valid 	    : 1;
    char    	dstKnown    : 1;
    char    	dst   	    : 1;
    char    	tmValid	    : 1;
  };

  Flags	    	flags;
  const char *	timeZoneName;  
  long	    	offset;
  struct tm   	tm;

  time_t      	seconds;
  
};

ostream & operator<<( ostream & dest, const DateTime & time );
//
// Generic time_t manipulators
//

inline
long
SecInTimeT( long sec )
{
  return(sec % 60 );
}

inline
long
MinInTimeT( long sec )
{
  return( (sec % (60 * 60)) / 60 );
}

inline
long
HourInTimeT( long sec )
{
  return( (sec % (60 * 60 * 24)) / (60 * 60) );
}

inline
long
HoursInTimeT( long sec )
{
  return( sec / (60 * 60) );
}

inline
long
DaysInTimeT( long sec )
{
  return( (sec / SEC_PER_DAY ) );
}

inline time_t
DateInTimeT( time_t sec )
{
  return( sec - (sec % SEC_PER_DAY ) );
}


//
// Inline Methods
//

// Constructor - initialize to setTime value
inline 
DateTime::DateTime( time_t setTime, Bool addLocal )
{
  seconds = 0;
  resetFlags();
  set( setTime, addLocal );
}

// Constructor - initialize to day + timeOfDay
inline 
DateTime::DateTime( time_t day, time_t timeOfDay )
{
  seconds = 0;
  resetFlags();
  seconds = day + timeOfDay;
}

// Constructor - initialize from year, month, day, hour, min sec
inline
DateTime::DateTime(
    int 	year,
    int 	month,
    int 	day,
    int 	hour,
    int 	min,
    int 	sec
    )
{  
  seconds = 0;
  resetFlags();
  set( year, month, day, hour, min, sec );
}


// Constructor - initialize from setTime tm struct
inline 
DateTime::DateTime( const struct tm & setTime )
{
  seconds = 0;
  resetFlags();
  set( setTime );
}

// Constructor - initialize from yymmdd & hhmmss strings
inline
DateTime::DateTime( const char * yymmdd, const char * hhmmss )
{
  seconds = 0; // ichudov
  resetFlags();
  setHHMMSS( hhmmss );
  setYYMMDD( yymmdd );
}


// Constructor - initialize from dateString
inline
DateTime::DateTime( const char * dateString )
{
  seconds = 0;
  resetFlags();
  set( dateString, 0 );
}

// getTimeT - return current time_t value
inline
time_t
DateTime::getTimeT( void ) const
{
  return( seconds );
}

// getSecOfDay - return the number of seconds since midnight 
inline
long
DateTime::getSecOfDay( void ) const
{
  return( seconds % SEC_PER_DAY );
}

// getHour - return the hour of the day (2pm = 14)
inline
short
DateTime::getHour( void ) const
{
  return( HourInTimeT( seconds ) );
}

// getMinute - return the minute of the hour
inline
short
DateTime::getMinute( void ) const
{
  return( MinInTimeT( seconds ) );
}

// getSecond - return the second of the minute
inline short
DateTime::getSecond( void ) const
{
  return( SecInTimeT( seconds ) );
}

// getDayOfYear - return the julian date (1 -> 366)
inline
short
DateTime::getDayOfYear( void ) const
{
  if( flags.tmValid )
    {
      return( tm.tm_yday + 1);
    }
  else
    {
      return( gmtime( &seconds )->tm_yday + 1);
    }
}

// getDayOfYear - return the julian date (1 -> 366)
inline
short
DateTime::getDayOfYear( void )
{
  setTm();
  return( tm.tm_yday + 1);
}

// getDayOfMonth - return day of the month (1 -> 31)
inline short
DateTime::getDayOfMonth( void ) const
{
  if( flags.tmValid )
    {
      return( tm.tm_mday );
    }
  else
    {
      return( gmtime( &seconds )->tm_mday );
    }
}

// getDayOfMonth - return day of the month (1 -> 31)
inline
short
DateTime::getDayOfMonth( void )
{
  setTm();
  return( tm.tm_mday );
}

// getMonth - return month of year (1 -> 12)
inline
short
DateTime::getMonth( void ) const
{
  if( flags.tmValid )
    {
      return( tm.tm_mon + 1 );
    }
  else
    {
      return( gmtime( &seconds )->tm_mon + 1 );
    }
}

// getMonth - return month of year (1 -> 12)
inline
short
DateTime::getMonth( void )
{
  setTm();
  return( tm.tm_mon + 1 );
}

// getYearOfCentury - ( 1995 return 95, 2005 retun 5 )
inline
short
DateTime::getYearOfCentury( void ) const
{
  return( getYear() % 100 );
}

// getYearOfCentury - ( 1995 return 95, 2005 retun 5 )
inline
short
DateTime::getYearOfCentury( void )
{
  return( getYear() % 100 );
}

// getYear - return the current year (1995, 2010)
inline
short
DateTime::getYear( void ) const
{
  if( flags.tmValid )
    {
      return( tm.tm_year + 1900 );
    }
  else
    {
      return( gmtime( &seconds )->tm_year + 1900 );
    }
}

// getYear - return the current year (1995, 2010)
inline
short
DateTime::getYear( void )
{
  setTm();
  return( tm.tm_year + 1900 );	
}

// getString - return a formated string of the current time value
inline
const char *
DateTime::getString( char * buffer, const char * fmt ) const
{
  if( flags.tmValid )
    {
      return( DateStringFromTm( buffer, fmt, &tm ) );
    }
  else
    {
      return( DateStringFromTm( buffer, fmt, gmtime( &seconds ) ) );
    }
}

// getString - return a formated string of the current time value
inline
const char *
DateTime::getString( char * buffer, const char * fmt )
{
  if( ! flags.tmValid )
    {
      setTm();
    }
  return( DateStringFromTm( buffer, fmt, &tm ) );
}


// getOffset - return the offset from GMT of the current value
inline
short
DateTime::getOffset( void ) const
{
  return( offset );
}

// isLocal - return TRUE if the current value is a local time
inline
Bool
DateTime::isLocal( void ) const
{
  return( (offset) ? TRUE : FALSE );
}

// getTimeZone - return the time zone name
inline
const char *
DateTime::getTimeZone( void ) const
{
  if( offset )
    {
      return( (timeZoneName) ? timeZoneName : getenv( "TZ" ) );
    }
  else
    {
      return( "GMT" );
    }
}

// setTimeT - set the time from timeSec return old value
inline
time_t
DateTime::setTimeT( time_t timeSec )
{
  time_t    old = seconds;
  resetFlags();
  seconds = timeSec;
  
  return( old );
}

// set - set the time from timeSec return old value
inline
time_t
DateTime::set( time_t timeSec, Bool addLocal )
{
  time_t    old = seconds;
  resetFlags();
  seconds = timeSec;
  
  if( addLocal )
    {
      setTimeZone();
    }
  
  return( old );
}

// set - set date/time from string
inline
time_t
DateTime::set( const char * dateStr, const char * fmt )
{
  time_t old = seconds;
  resetFlags();
  seconds = DateStringToTimeT( dateStr, fmt );
  return( old );
}

// set - set from year, month, day, hour, min, second
inline
time_t
DateTime::set( 
  int year,
  int month,
  int day,
  int hour,
  int min,
  int sec
  )
{
  time_t old = seconds;
  resetFlags();

  seconds = ( YearMonthDayToTimeT( year, month, day ) +
	      HourMinSecToTimeT( hour, min, sec ) );

  return( old );
}

// set - set from tm struct ( assumed to be gmt )
inline
time_t
DateTime::set( const struct tm & tmTime )
{
  return( set( tmTime.tm_year,
	       tmTime.tm_mon+1,
	       tmTime.tm_mday,
	       tmTime.tm_hour,
	       tmTime.tm_min,
	       tmTime.tm_sec ) );
}

// setYYMMDD - set the date from the string (ie 950131 )
inline
time_t
DateTime::setYYMMDD( const char * yymmdd )
{
  time_t old = seconds;
  seconds = YYMMDDtoTimeT( yymmdd ) + (seconds % SEC_PER_DAY );
  flags.tmValid = FALSE;
  if( offset ) setTm();
  return( old );
}

// setYYYYMMDD - set the date from the string ( ie 19950131 )
time_t
DateTime::setYYYYMMDD( const char * yyyymmdd )
{
  time_t old = seconds;
  seconds = YYYYMMDDtoTimeT( yyyymmdd ) + (seconds % SEC_PER_DAY );
  flags.tmValid = FALSE;
  if( offset ) setTm();
  return( old );
}


// setHHMMSS - set the time from the string ( 130550 = 1:05:50 pm )
inline
time_t
DateTime::setHHMMSS( const char * hhmmss )
{
  time_t old = seconds;
  seconds = (seconds - (seconds % SEC_PER_DAY)) + HHMMSStoTimeT( hhmmss );
  flags.tmValid = FALSE;
  if( offset ) setTm();
  return( old );
}



// setDayOfYear - set the day of the year
inline
time_t
DateTime::setDayOfYear( short dayOfYear )
{
  time_t old = seconds;
  seconds -= getDayOfYear() * SEC_PER_DAY;
  seconds += dayOfYear * SEC_PER_DAY;
  flags.tmValid = FALSE;
  if( offset ) setTm();
  return( old );
}

// setDayOfMonth - set the day of the month
inline
time_t
DateTime::setDayOfMonth( short dayOfMonth )
{
  time_t old = seconds;
  seconds -= getDayOfMonth() * SEC_PER_DAY;
  seconds += dayOfMonth * SEC_PER_DAY;
  flags.tmValid = FALSE;
  if( offset ) setTm();
  return( old );
}

// setHour - set the our of day ( 13 = 1pm )
inline
time_t
DateTime::setHour( short hour )
{
  time_t old = seconds;
  seconds -= getHour() * SEC_PER_HOUR;
  seconds += hour * SEC_PER_HOUR;
  flags.tmValid = FALSE;
  if( offset ) setTm();
  return( old );
}

// setMinute - set the minute of the hour
inline
time_t
DateTime::setMinute( short minute )
{
  time_t old = seconds;
  seconds -= getMinute() * SEC_PER_MIN;
  seconds += minute * SEC_PER_MIN;
  flags.tmValid = FALSE;
  if( offset ) setTm();
  return( old );
}

// setSecond - set the second of minute
inline
time_t
DateTime::setSecond( short sec )
{
  time_t old = seconds;
  seconds -= getSecond();
  seconds += sec;
  flags.tmValid = FALSE;
  if( offset ) setTm();
  return( old );
}

// setTimeZone - adjust time for timezone 'zone'
inline
long
DateTime::setTimeZone( const char * zone )
{
  seconds -= offset;  
  flags.dstKnown = FALSE;
  flags.tmValid = FALSE;
  offset = getGmtOffset( zone );
  timeZoneName = zone;
  seconds += offset;
  setTm();
  return( offset );
}

// add - add the seconds in dt to me
inline
DateTime &
DateTime::add( const DateTime & dt )
{
  seconds += dt.getTimeT();
  flags.tmValid = FALSE;
  if( offset ) setTm();
  return( *this );
}

// add - add the 'sec' to me
inline
DateTime &
DateTime::add( long sec )
{
  seconds += sec;
  flags.tmValid = FALSE;
  if( offset ) setTm();
  return( *this );
}

// addSec - add the 'sec' to me
inline
DateTime &
DateTime::addSec( long sec )
{
  seconds += sec;
  flags.tmValid = FALSE;
  if( offset ) setTm();
  return( *this );
}

// addMin - add the minutes to me
inline
DateTime &
DateTime::addMin( long minutes )
{
  seconds += minutes * SEC_PER_MIN;
  flags.tmValid = FALSE;
  if( offset ) setTm();
  return( *this );
}

// addHour - add the hours to me
inline
DateTime &
DateTime::addHour( long hours )
{
  seconds += hours * SEC_PER_HOUR;
  flags.tmValid = FALSE;
  if( offset ) setTm();
  return( *this );
}

// addDay - add the days to me
inline
DateTime &
DateTime::addDay( long days )
{
  seconds += days * SEC_PER_DAY;
  flags.tmValid = FALSE;
  if( offset ) setTm();
  return( *this );
}

// setTm - set the internal struct tm for the current value
inline
void
DateTime::setTm( void )
{
  if( ! flags.tmValid )
    {
      if( offset )
	{
	  setTmOffset();
	}
      else
	{
	  memcpy( &tm, gmtime( &seconds ), sizeof( struct tm ) );
	}
      flags.tmValid = TRUE;
    }
}

// compare - return the difference between me and 'two'
inline
int
DateTime::compare( const DateTime & two ) const
{
  return( Compare( seconds, two.seconds ) );
}

// operator time_t - return the current time_t value
inline
DateTime::operator time_t () const
{
  return( seconds );
}

// operator const char * - return a string for the current value
inline
DateTime::operator const char * () const
{
  return( getString() );
}

// operator ==  - return TRUE if I am equal to 'two'
inline
int
DateTime::operator ==( const DateTime & two ) const
{
  return( compare( two ) == 0 );
}

// operator != - return TRUE if I am not equal to 'two'
inline
int
DateTime::operator !=( const DateTime & two ) const
{
  return( ! ( *this == two ) );
}

// resetFlags - reset all state related variables
inline
void
DateTime::resetFlags( void )
{
  flags.valid = TRUE;
  flags.dstKnown = FALSE;
  flags.tmValid = FALSE;
  offset = 0;
  timeZoneName = 0;
}

// Compare - return the diff beween 2 DateTime values
inline
int
Compare( const DateTime & one, const DateTime & two )
{
  return( one.compare( two ) );
}
	  


       
#endif // ! def _DateTime_hh_ 
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
