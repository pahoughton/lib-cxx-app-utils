#ifndef _DateTime_hh_
#define _DateTime_hh_
//
// File:        DateTime.hh
// Project:	StlUtils ()
// Desc:        
//
//  The DateTime class provides many methods for managing and converting
//  date/time values. A time_t value is used inside the class for
//  storage.
//
// Notes:
//
//  Most methods do NOT verify the values passed.
//
//  When setting the DateTime (with 'set()' or the constructors), If the
//  value passed would exceed the range ( 1901 < year < 2038) of legal
//  values, the DateTime will be set to MinTimeT or MaxTimeT accordingly.
//
// Author:      Paul Houghton - (paul.houghton@mci.com)
// Created:     02/09/94 12:24
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
//

#include <StlUtilsConfig.hh>
#include <DateTimeUtils.hh>
#include <DumpInfo.hh>
#include <utility>
#include <ctime>

#if defined( STLUTILS_DEBUG )
#define inline
#endif

class RegexScan;

class DateTime
{
public:

  // Constructors
  inline DateTime( void );
  inline DateTime( time_t setTime, bool addLocal = false );
  inline DateTime( time_t day, time_t timeOfDay );
  inline DateTime( const char * yymmdd, const char * hhmmss );
  inline DateTime( int year, int month, int day,
		   int hour = 0, int min = 0, int sec = 0 );
  inline DateTime( const struct tm & tmTime );
  inline DateTime( const char * timeString );

  inline DateTime( istream & src, bool text = false );
  
  virtual ~DateTime( void );
  
  inline time_t	    getTimeT( void ) const;
  inline long	    getSecOfDay( void ) const;
  inline short	    getHour( void ) const;
  inline short	    getMinute( void ) const;
  inline short	    getSecond( void ) const;
  virtual DayOfWeek getDayOfWeek( void ) const;

  //
  // The non const versions set the internal struct tm so
  // the values do not have to be recalculated. If you need these
  // values repeatedly, you may want to call 'setTm(void)'
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
  inline const char *	getString( char * buffer = 0,
				   const char * fmt = 0 ) const;
  inline const char *	getString( char * buffer = 0,
				   const char * fmt = 0 );
  const char *		getYYYYMMDD( void ) const;
  const char *		getHHMMSS( void ) const;
  
  inline short	    	getOffset( void ) const;
  inline bool	    	isLocal( void ) const;
  bool	    	    	isDST( void ) const;
  bool	    	    	isDST( void );
  inline const char *	getTimeZone( void ) const;

  static const char *	getSysTimeZone( void );

  inline time_t     	setTimeT( time_t timeSec = 0 );
  
  inline time_t		set( time_t timeSec, bool addLocal = false );
  inline time_t	    	set( const char * dateString, const char * fmt = 0 );
  inline time_t         set( int year, int month, int day,
			     int hour = 0, int min = 0, int sec = 0 );
  inline time_t		set( const struct tm & tmTime );

  bool			setValid( int year, int month, int day,
				  int hour = 0, int min = 0, int sec = 0 );
  bool			setValid( const char * dateString,
				  const char * fmt = 0 );

  bool			setValidYYMMDD( const char * yymmdd );
  bool			setValidYYYYMMDD( const char * yyyymmdd );
  bool			setValidHHMM( const char * hhmm );
  bool			setValidHHMMSS( const char * hhmmss );
  
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
  
  long	    	    	setTimeZone( const char * zone = 0 );

  inline DateTime &   	add( const DateTime & dt );
  inline DateTime &   	add( long seconds = 1 );
  inline DateTime &   	addSec( long seconds = 1);
  inline DateTime &   	addMin( long minutes = 1 );
  inline DateTime &   	addHour( long hours = 1 );
  inline DateTime &   	addDay( long days = 1 );
  
  inline void	    	setTm( void );

  virtual int	    	compare( const DateTime & two ) const;

  inline    	operator time_t () const;
  inline    	operator const char * () const;
  
  inline bool 	operator == ( const DateTime & rhs ) const;
  inline bool 	operator <  ( const DateTime & rhs ) const;

#if defined( STLUTILS_RELOPS_BROKEN )
  inline bool		operator != ( const DateTime & rhs ) const;
  inline bool		operator >  ( const DateTime & rhs ) const;
  inline bool		operator <= ( const DateTime & rhs ) const;
  inline bool		operator >= ( const DateTime & rhs ) const;
#endif

  inline bool 	operator == ( time_t rhs ) const;
  inline bool 	operator <  ( time_t rhs ) const;

#if defined( STLUTILS_RELOPS_BROKEN )
  inline bool		operator != ( time_t rhs ) const;
  inline bool		operator >  ( time_t rhs ) const;
  inline bool		operator <= ( time_t rhs ) const;
  inline bool		operator >= ( time_t rhs ) const;
#endif

  // note: time_t IS a signed value.
  
  inline time_t	operator -  ( const DateTime & rhs ) const;
  inline time_t operator -  ( const time_t rhs ) const;
  
  // libStlUtils Common Class Methods
  
  virtual size_t    	getBinSize( void ) const;
  
  virtual ostream & 	write( ostream & dest ) const;
  virtual istream & 	read( istream & src );
  
  virtual ostream & 	toStream( ostream & dest = cout ) const;
  
  friend inline ostream & operator << ( ostream & dest, const DateTime & obj );
  
  virtual bool	    	good( void ) const;
  virtual const char *	error( void ) const;
  virtual const char * 	getClassName( void ) const;
  virtual const char *	getVersion( bool withPrjVer = true ) const;
  virtual ostream & 	dumpInfo( ostream &	dest = cerr,
				  const char *	prefix = "    ",
				  bool		showVer = true ) const;

  inline DumpInfo< DateTime >
  dump( const char * prefix = "    ", bool showVer = true ) const;
  
  static const ClassVersion 	version;
  
protected:

  inline void 	resetFlags( void );
  
  const char * 	    	fromTm( char * buf,
				const char * fmt,
				const struct tm * tmTime ) const;
  inline const char *	fromTimeT( char * buffer, const char * fmt ) const;

  inline time_t    	fromYYYYMMDD( const char * yyyymmdd ) const;
  inline time_t    	fromYYMMDD( const char * yymmdd ) const;
  inline time_t    	fromHHMMSS( const char * hhmmss ) const;

  bool	    	    	toTm( struct tm & tmTime,
			      const char * str,
			      const char * fmt ) const;
  time_t    	    	toTimeT( const char * str, const char * fmt ) const;
  time_t    	    	toTimeT( int y, int m, int d,
				 int h=0, int min=0, int s=0 ) const;
  
  static RegexScan 	strPattern;

private:
  
  // void			setTmOffset( void );
  long			setTimeZoneOffset( void );
  
  static void		setEnvTimeZone( const char * timeZone );
  
  struct Flags
  {
    int    	valid 	    : 1;
    int    	dstKnown    : 1;
    int    	dst   	    : 1;
    int    	tmValid	    : 1;
  };

  char		timeZone[ 30 ];
  Flags	    	flags;
  long	    	offset;
  struct tm   	tm;

  time_t	seconds;
  
};



#if !defined( inline )
#include "DateTime.ii"
#else
#undef inline

int
compare( const DateTime & one, const DateTime & two );

time_t
operator - ( const time_t lhs, const DateTime & rhs );

#endif
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
//       
//  DataTypes:
//
//  	DateTime    class
//
//  Constructors:
//
//	DateTime( void )
//      
//	    sets the initial value to current local time.
//
//  	DateTime( time_t setTime, bool addLocal = false );
//  	    use 'setTime' for the initial value. If addLocal is true,
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
//  	    set the initial value from 'timeString' the format must be
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
//  	DateOfWeek
//  	getDayOfWeek( void ) const;
//  	    return the day of the week. (sunday = 0) (0->6)
//
//  	short
//  	getDayOfYear( void ) const;
//  	    return day of the year. ( 1 -> 366 )
//  	    non-const version sets the internal tm to improve performance.
//
//  	short
//  	getDayOfYear( void );
//  	    return day of the year. ( 1 -> 366 )
//  	    non-const version sets the internal tm to improve performance.
//
//  	short
//  	getDayOfMonth( void ) const;
//  	    return the day of the month. (1 -> 31)
//  	    non-const version sets the internal tm to improve performance.
//
//  	short
//  	getDayOfMonth( void );
//  	    return the day of the month. (1 -> 31)
//  	    non-const version sets the internal tm to improve performance.
//
//  	short
//  	getMonth( void ) const
//  	    return the month of the year. (1 -> 12)
//  	    non-const version sets the internal tm to improve performance.
//
//  	short
//  	getMonth( void )
//  	    return the month of the year. (1 -> 12)
//  	    non-const version sets the internal tm to improve performance.
//
//  	short
//  	getYearOfCentury( void ) const
//  	    return the year of the century. (0 -> 99)
//  	    Both 1930 and 2030 will return '30'.
//  	    non-const version sets the internal tm to improve performance.
//
//  	short
//  	getYearOfCentury( void ) 
//  	    return the year of the century. (0 -> 99)
//  	    Both 1930 and 2030 will return '30'.
//  	    non-const version sets the internal tm to improve performance.
//
//  	short
//  	getYear( void ) const;
//  	    return the year. ( all four digits - 1995, 2005 )
//  	    non-const version sets the internal tm to improve performance.
//
//  	short
//  	getYear( void )
//  	    return the year. ( all four digits - 1995, 2005 )
//  	    non-const version sets the internal tm to improve performance.
//
//  	const char *
//  	getString( char * buffer = 0, const char * fmt = 0 )
//  	    return a string representation of the date/time. If
//  	    'buffer' is not 0, the string will be placed in it, otherwise
//  	    a static internal bufferr will be used. If fmt is not 0 (i.e. a
//  	    valid string), strftime will use 'fmt' to format the
//  	    string. Otherwise, the default format will be used. The default
//  	    format is '02/05/95 03:15:30' unless the year is < 1950 or >
//  	    2000, then it is '02/05/2010 03:15:30' (4 digit year).
//
//  	const char *
//  	getString( char * buffer = 0, const char * fmt = 0 ) const
//  	    return a string representation of the date/time. If
//  	    'buffer' is not 0, the string will be placed in it, otherwise
//  	    a static internal bufferr will be used. If fmt is 0, the default
//  	    valid string), strftime will use 'fmt' to format the
//  	    string. Otherwise, the default format will be used. The default
//  	    format is '02/05/95 03:15:30' unless the year is < 1950 or >
//  	    2000, then it is '02/05/2010 03:15:30' (4 digit year).
//
//  	short
//  	getOffset( void ) const
//  	    return the current timezone offset being used. Normally this
//  	    is 0. It is set by calls to 'setTimeZone'
//
//  	bool
//  	isLocal( void ) const
//  	    return true if a timezone has been set.
//
//  	bool
//    	isDST( void )
//  	    return true if a timezone is set and daylight savings time is
//  	    in effect.
//
//  	bool
//  	isDST( void ) const
//  	    return true if a timezone is set and daylight savings time is
//  	    in effect.
//
//  	const char *
//  	getTimeZone( void ) const
//  	    return the name of the timezone that has been set. If no
//  	    timezone is set, 0 is returned.
//
//  	static
//	const char *
//  	getSysTimeZone( void )
//  	    return the name of the current system time zone.
//  	    i.e (CST6CDT). Uses the TZ environment variable.
//
//  	time_t
//  	setTimeT( time_t timeSec = 0 )
//  	    set the date/time to the specified value. Any timezone is
//  	    reset to GMT.
//  	    Returns the previous date/time value.
//
//     	time_t
//  	set( time_t timeSec, bool addLocal = false )
//  	    set the date/time to the specific value. if addLocal
//  	    is true, the local timezone offset ( according to TZ env var )
//  	    will be added to the time. Any timezone is reset to GMT.
//  	    Returns the previous date/time value.
//
//  	time_t
//  	set( const char * dateString, const char * fmt = 0 )
//  	    set the date/time by converting the'dateString'. If 'fmt' is 0,
//  	    the string is expected to be in '1/5/94 03:04:00' format.
//  	    When using this format, neither the seconds, or the time is
//  	    required (ie 1/1/92 & 1/1/95 05:00 is ok).
//          If 'fmt' is not 0, strptime will use it to translate the string.
//          Any timezone is reset to GMT.
//  	    Returns the previous date/time value.
//
//  	time_t
//  	set( int year, int month, int day,
//  	     int hour = 0, int min = 0, int sec = 0)
//  	    set the date/time from year, month, day, hour, min, sec.
//          Any timezone is reset to GMT.
//  	    Returns the previous date/time value.
//
//  	time_t
//  	set( const struct tm & tmTime )
//  	    set the date/time from the 'tmTime' structure. The values in
//  	    'tmTime' are treated as GMT values. The timezone is reset to
//  	    GMT.
//  	    Returns the previous date/time value.
//
//  	bool
//  	setValid( int year, int month, int day,
//  	    	  int hour = 0, int min = 0, int sec = 0 )
//  	    set the date/time according to year, month, day, hour, min & sec.
//  	    These value are checked to be sure they are in range. If
//  	    any value is not in range, the date/time value is set to 0
//  	    and a flag is set so 'good()' will return false. The year
//  	    range has been limited to 1970 -> 2050, 0 -> 50, 70 -> 99.
//  	    The timezone is reset to GMT.
//  	    Returns true if succeeded
//
//  	bool
//  	setValid( const char * dateString, const char * fmt = 0 )
//  	    set the date/time by converting the'dateString'. If 'fmt' is 0,
//  	    the string is expected to be in '1/5/94 03:04:00' format.
//  	    When using this format, neither the seconds, or the time is
//  	    requried (ie 1/1/92 & 1/1/95 05:00 is ok). If 'fmt' is
//  	    not 0, strptime will use it to translate the string.
//  	    The values are checked to be sure they are in range. If
//  	    any value is not in range, the date/time value is set to 0
//  	    and a flag is set so 'good()' will return false. The timezone
//  	    is reset to GMT.
//  	    Returns true if succeeded
//
//  	bool
//  	setYYYYMMDD( const char * yyyymmdd )
//  	    set the 'date' by translating 'yyyymmdd'.  The string does NOT
//  	    have to be NULL terminated. The time and timezone are not modified.
//  	    Example string (19950130)
//  	    Returns true if succeeded
//
//  	bool
//  	setYYMMDD( const char * yymmdd )
//  	    set the 'date' by translating 'yymmdd'.  The string does NOT
//  	    have to be NULL terminated.  'yy' values between 00 and 50 are
//  	    considered to be for the next century (ie 05 = 2005).
//  	    The time and timezone are not modified.
//          Example string (950130)
//  	    Returns true if succeeded
//
//  	time_t
//  	setHHMMSS( const char * hhmmss )
//  	    set the 'time' by translating 'hhmmss'. The string does NOT
//  	    have to be NULL terminated. The date and timezone are not
//  	    modified.
//          Example string (155005 = 3:50:05 pm)
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
//  	    set the month. WARNING: this function is VERY literal. If
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
//	add( const DateTime & dt )
//  	    add the DateTime to the current value.
//  	    Returns a reference to self
//
//  	DateTime &
//  	add( long seconds = 1 )
//  	    add the seconds to the date/time value.
//  	    Returns a reference to self
//
//  	DateTime &
//  	addSec( long seconds = 1 )
//  	    add the seconds to the date/time value.
//  	    Returns a reference to self
//
//  	DateTime &
//  	addMin( long minutes = 1 )
//  	    add the minutes to the date/time value
//  	    Returns a reference to self
//
//  	DateTime &
//  	addHour( long hours = 1 )
//  	    add the hours to the date/time value.
//  	    Returns a reference to self
//
//  	DateTime &
//  	addDay( long days = 1 )
//  	    add the days to the datd/time value.
//  	    Returns a reference to self
//
//  	void
//  	setTm( void )
//  	    set the internal tm struct for the current date/time value.
//  	    This call will pre-assign the year, month, day of month,
//  	    and day of year for the current value. It is provided so
//  	    these values do not have to be recalculated for multible
//  	    'get' calls.
//
//   	int
//  	compare( const DateTime & two ) const
//  	    return the difference between 'two' and self. If self
//  	    is > two, a > 0 value will be returned. If self is == two, a
//  	    value of 0 will be returned. If self is < two, a < 0 value will
//  	    be returned.  Only the actual date/time value is used
//  	    for comparison
//
//  	operator time_t ( void ) const;
//  	    return the current date/time as a time_t value.
//
//  	operator const char * ( void ) const
//    	    return the current date/time as strings. The getString
//  	    method is used to provide to string.
//
//  	int
//  	operator == ( const DateTime & rhs ) const;
//  	    return true if 'two' is equal to self. Only the actual
//  	    date time value is used for comparison.
//
//  	int
//  	operator != ( const DateTime & rhs ) const;
//  	    return true if 'two' is not equal to self. Only the actual
//  	    date time value is used for comparison.
//
//  	virtual
//    	const char *
//  	getClassName( void ) const;
//  	    return the name of this class.
//
//  	virtual
//  	bool
//  	good( void ) const
//  	    return true if no detected errors exist. Only setValid will
//  	    detect an invalid date/time value.
//
//  	virtual
//  	const char *
//  	error( void ) const
//  	    return a string describing the current error state.
//
//  Other Accociated Functions:
//
//  	ostream &
//  	operator <<( ostream & dest, const DateTime & obj );
//  	    send a formated string of the current date/time to 'dest'
//  	    The format is '02/03/95 15:13:03'.
//
//  	int
//  	compare( const DateTime & one, const DateTime & two )
//  	    return the difference between 'one' and 'two'. If one
//  	    is > two, a > 0 value will be returned. If one is == two, a
//  	    value of 0 will be returned. If one is < two, a < 0 value will
//  	    be returned.  Only the actuall date/time value is used
//  	    for comparison
//  	    
// Example:
//
// See Also:
//
// Files:
//
// Documented Ver:
//
// Tested Ver:
//
// Revision Log:
//
// 
// %PL%
// 
// $Log$
// Revision 5.6  2003/08/09 11:20:58  houghton
// Changed ver strings.
//
// Revision 5.5  2003/06/07 16:47:47  houghton
// Chaged setValid calls to return bool (was time_t)
//
// Revision 5.4  2001/08/02 16:34:20  houghton
// *** empty log message ***
//
// Revision 5.3  2001/07/26 19:29:00  houghton
// *** empty log message ***
//
// Revision 5.2  2000/05/25 17:05:45  houghton
// Port: Sun CC 5.0.
//
// Revision 5.1  2000/05/25 10:33:15  houghton
// Changed Version Num to 5
//
// Revision 4.5  1998/10/13 16:17:05  houghton
// Changed: time zone processing no longer uses 'static' methods.
//
// Revision 4.4  1998/10/13 15:17:04  houghton
// Added getHHMMSS( void ).
//
// Revision 4.3  1998/01/22 18:30:17  houghton
// Added setValidYYYYMMDD().
//
// Revision 4.2  1998/01/05 13:19:24  houghton
// Added getYYYYMMDD()
// Added setValidYYMMDD()
//
// Revision 4.1  1997/09/17 15:12:19  houghton
// Changed to Version 4
//
// Revision 3.5  1997/09/17 11:08:16  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.4  1997/08/28 21:20:23  houghton
// Changed operator == and operator < to return 'bool'.
// Added operator - .
//
// Revision 3.3  1997/08/24 21:57:33  houghton
// Cleanup comments.
// Changed getDayOfWeek to return a 'DayOfWeek' (was int).
// Added dump().
//
// Revision 3.2  1996/11/20 12:11:57  houghton
// Removed support for BinStream.
//
// Revision 3.1  1996/11/14 01:23:36  houghton
// Changed to Release 3
//
// Revision 2.6  1996/11/04 13:34:20  houghton
// Added strptime funct proto
//
// Revision 2.5  1996/05/01 10:59:05  houghton
// Bug-Fix: gcc did not like the flags being a char changed to int.
//
// Revision 2.4  1996/04/27 12:58:55  houghton
// Removed unneeded includes.
// Cleanup.
//
// Revision 2.3  1995/11/12 17:51:56  houghton
// New default constructor.
// Now default sets the value to current local time.
//
// Revision 2.2  1995/11/10  14:08:35  houghton
// Updated documentation comments
//
// Revision 2.1  1995/11/10  12:40:31  houghton
// Change to Version 2
//
// Revision 1.11  1995/11/05  14:44:30  houghton
// Ports and Version ID changes
//
//
#endif // ! def _DateTime_hh_ 
