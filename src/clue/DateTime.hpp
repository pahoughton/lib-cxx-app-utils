#ifndef _clue_DateTime_hpp_
#define _clue_DateTime_hpp_
/* 1994-02-09 (cc) Paul Houghton <paul4hough@gmail.com>

   The DateTime class provides many methods for managing and converting
   date/time values. A time_t value is used inside the class for
   storage.

   Most methods do NOT verify the values passed.

   When setting the DateTime (with 'set()' or the constructors), If the
   value passed would exceed the range ( 1901 < year < 2038) of legal
   values, the DateTime will be set to MinTimeT or MaxTimeT accordingly.

*/

#include <clue/DateTimeUtils.hpp>
#include <clue/DumpInfo.hpp>
#include <clue/StringUtils.hpp>
#include <regex>
#include <string>
#include <utility>
#include <ctime>
#include <cstdlib>
#include <cstdint>

#if !defined CLUE_DATETIME_FORMAT
#define CLUE_DATETIME_FORMAT "%m/%d/%y %H:%M:%S"
#endif

namespace clue {

class DateTime
{
public:

  // Constructors
  inline DateTime( void ); // use localtime for now by default
  inline DateTime( time_t setTime, bool gmttm = true );
  inline DateTime( int year, int month, int day,
		   int hour = 0, int min = 0, int sec = 0 );
  inline DateTime( const struct tm & tmTime );
  inline DateTime( const char * str,
		   const char * fmt = CLUE_DATETIME_FORMAT );

  virtual ~DateTime( void );

  inline time_t	    timet( void ) const;
  inline DateTime & timet( time_t val, bool gmttm = true );

  inline void       setTz( const char * tz = 0 );

  inline int32_t    year( void ) const;
  DateTime &	    year( int32_t val );
  inline uint16_t   month( void ) const;
  DateTime &	    month( uint16_t val );
  inline uint16_t   mday( void ) const;
  inline DateTime & mday( uint16_t val );
  inline uint16_t   hour( void ) const;
  inline DateTime & hour( uint16_t val );
  inline uint16_t   minute( void ) const;
  inline DateTime & minute( uint16_t val );
  inline uint16_t   second( void ) const;
  inline DateTime & second( uint16_t val );

  inline uint32_t   yearOfCentury( void ) const;
  inline uint32_t   secOfDay( void ) const;
  inline DayOfWeek  dayOfWeek( void ) const;
  inline uint16_t   dayOfYear( void ) const;

  inline int32_t    	tzOffset( void ) const;
  inline const char *	tzName( void ) const;
  inline bool	    	isLocal( void ) const;
  inline bool  	    	isDST( void ) const;

  inline std::string	yyyymmddhhmmss( void ) const;
  inline DateTime &	yyyymmddhhmmss( const char * ymdhms );
  inline DateTime &	yyyymmddhhmmss( const char * ymd, const char * hms );
  inline std::string	yyyymmdd( void ) const;
  inline DateTime &	yyyymmdd( const char * ymd );
  inline std::string	yymmdd( void ) const;
  inline DateTime &	yymmdd( const char * ymd );
  inline std::string	hhmmss( void ) const;
  inline DateTime &	hhmmss( const char * hms );
  inline std::string	yyyy_mm_dd_hh_mm_ss( void ) const; // 1999-01-01 10:10:10

  static inline bool	isValid( int year, int month, int day,
				 int hour = 0, int min = 0, int sec = 0 );
  static inline bool	isValid( const struct tm & tm );
  inline std::string	str( const char * fmt = CLUE_DATETIME_FORMAT ) const;

  inline DateTime &	set( const char * str,
			     const char * fmt = CLUE_DATETIME_FORMAT );
  inline DateTime &	set( int year, int month, int day,
			     int hour = 0, int min = 0, int sec = 0 );
  inline DateTime &	set( const struct tm & tmTime );

  inline DateTime &	setDate( int year, int month, int day );
  inline DateTime &     setTime( uint16_t h, uint16_t m, uint16_t s = 0 );
  inline DateTime &	setValid( int year, int month, int day,
				  int hour = 0, int min = 0, int sec = 0 );
  inline DateTime &	setValid( const char * dateString,
				  const char * fmt = CLUE_DATETIME_FORMAT );
  inline DateTime &	setValidYYMMDD( const char * yymmdd );
  inline DateTime &	setValidYYYYMMDD( const char * yyyymmdd );
  inline DateTime &	setValidHHMM( const char * hhmm );
  inline DateTime &	setValidHHMMSS( const char * hhmmss );

  inline DateTime &   	add( const DateTime & dt );
  inline DateTime &   	add( long seconds = 1 );
  inline DateTime &   	addSec( long seconds = 1);
  inline DateTime &   	addMin( long minutes = 1 );
  inline DateTime &   	addHour( long hours = 1 );
  inline DateTime &   	addDay( long days = 1 );
  //inline DateTime &   	addMonth( long months = 1 );
  //inline DateTime &   	addYear( long years = 1 );

  virtual int	    	compare( const DateTime & two ) const;

  inline    	operator time_t () const;

  inline bool 	operator == ( const DateTime & rhs ) const;
  inline bool 	operator <  ( const DateTime & rhs ) const;
  inline bool	operator != ( const DateTime & rhs ) const;
  inline bool	operator >  ( const DateTime & rhs ) const;
  inline bool	operator <= ( const DateTime & rhs ) const;
  inline bool	operator >= ( const DateTime & rhs ) const;

  inline bool 	operator == ( time_t rhs ) const;
  inline bool 	operator <  ( time_t rhs ) const;
  inline bool	operator != ( time_t rhs ) const;
  inline bool	operator >  ( time_t rhs ) const;
  inline bool	operator <= ( time_t rhs ) const;
  inline bool	operator >= ( time_t rhs ) const;

  inline time_t	operator -  ( const DateTime & rhs ) const;
  inline time_t operator -  ( const time_t rhs ) const;

  virtual size_t	    getBinSize( void ) const;

  virtual std::ostream &    write( std::ostream & dest ) const;
  virtual std::istream &    read( std::istream & src );

  virtual std::ostream &    toStream( std::ostream & dest = std::cout ) const;

  virtual bool		    good( void ) const;
  virtual std::ostream &    dumpInfo( std::ostream &	dest = std::cerr,
				      const char *	prefix = "    " ) const;

  inline DumpInfo< DateTime >
  dump( const char * prefix = "    " ) const{
    return( DumpInfo< DateTime >( *this, prefix ) );
  }


protected:

  time_t	m_seconds;
  struct tm   	m_tm;

private:

};

inline
DateTime::DateTime( void  )
{
  timet( time(0), false );
}

inline
DateTime::DateTime( time_t secs, bool gmttm )
{
  timet( secs, gmttm );
}

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
  m_tm.tm_gmtoff = 0;
  set( year, month, day, hour, min, sec );
}


inline
DateTime::DateTime( const struct tm & setTime )
{
  m_tm.tm_gmtoff = 0;
  set( setTime );
}

inline
DateTime::DateTime( const char * str, const char * fmt )
{
  m_tm.tm_gmtoff = 0;
  set( str, fmt );
}

inline
time_t
DateTime::timet( void ) const
{
  return( m_seconds );
}

inline
void
DateTime::setTz( const char * tz )
{
  if( tz ) {
    static char envtz[64];
    SafeStrcpy( envtz, tz, sizeof( envtz ) );
    putenv( envtz );
  }
  memcpy( &m_tm, localtime( &m_seconds ), sizeof( m_tm ) );
}

inline
DateTime &
DateTime::timet( time_t secs, bool gmttm )
{
  m_seconds = secs;
  if( gmttm ) {
    memcpy( &m_tm, gmtime( &m_seconds ), sizeof( m_tm ) );
  } else {
    memcpy( &m_tm, localtime( &m_seconds ), sizeof( m_tm ) );
  }
  return( *this );
}

inline
int32_t
DateTime::year( void ) const
{
  return( m_tm.tm_year + 1900 );
}

inline
uint16_t
DateTime::month( void ) const
{
  return( m_tm.tm_mon + 1 );
}

inline
uint16_t
DateTime::mday( void ) const
{
  return( m_tm.tm_mday );
}

inline
DateTime &
DateTime::mday( uint16_t mday )
{
  m_seconds -= m_tm.tm_mday * SecPerDay;
  m_seconds += mday * SecPerDay;
  m_tm.tm_mday = mday;
  return( *this );
}

inline
uint16_t
DateTime::hour( void ) const
{
  return( m_tm.tm_hour );
}

inline
DateTime &
DateTime::hour( uint16_t hour )
{
  m_seconds -= m_tm.tm_hour * 60 * 60;
  m_seconds += hour * 60 * 60;
  m_tm.tm_hour = hour;
  return( *this );
}

inline
uint16_t
DateTime::minute( void ) const
{
  return( m_tm.tm_min );
}

inline
DateTime &
DateTime::minute( uint16_t minute )
{
  m_seconds -= m_tm.tm_min * 60;
  m_seconds += minute * 60;
  m_tm.tm_min = minute;
  return( *this );
}

inline
uint16_t
DateTime::second( void ) const
{
  return( m_tm.tm_sec );
}

inline
DateTime &
DateTime::second( uint16_t sec )
{
  m_seconds -= m_tm.tm_sec;
  m_seconds += sec;
  m_tm.tm_sec = sec;
  return( *this );
}

inline
uint32_t
DateTime::yearOfCentury( void ) const
{
  return( m_tm.tm_year % 100 );
}
inline
uint32_t
DateTime::secOfDay( void ) const
{
  return( (m_tm.tm_hour * SecPerHour)
	  + (m_tm.tm_min * 60)
	  + m_tm.tm_sec );
}

// Note: the epoch (1/1/1970) was a thursday
DayOfWeek
DateTime::dayOfWeek( void ) const
{
  return( (DayOfWeek)(m_tm.tm_wday));
}

inline
uint16_t
DateTime::dayOfYear( void ) const
{
  return( m_tm.tm_yday + 1 );
}

inline
int32_t
DateTime::tzOffset( void ) const
{
  return( m_tm.tm_gmtoff );
}

inline
const char *
DateTime::tzName( void ) const
{
  return( m_tm.tm_zone );
}

inline
bool
DateTime::isLocal( void ) const
{
  return( m_tm.tm_gmtoff != 0 );
}

inline
bool
DateTime::isDST( void ) const
{
  return( m_tm.tm_isdst );
}

inline
std::string
DateTime::yyyymmddhhmmss( void ) const
{
  char tmp[32];
  snprintf( tmp, sizeof( tmp )
	    ,"%04d%02d%02d%02d%02d%02d"
	    ,m_tm.tm_year + 1900
	    ,m_tm.tm_mon + 1
	    ,m_tm.tm_mday
	    ,m_tm.tm_hour
	    ,m_tm.tm_min
	    ,m_tm.tm_sec );
  return( std::string( tmp ) );
}

inline
DateTime &
DateTime::yyyymmddhhmmss( const char * ymdhms )
{
  return( set( StringToInt( ymdhms,      10, 4 ),
	       StringToInt( ymdhms + 4,  10, 2 ),
	       StringToInt( ymdhms + 6,  10, 2 ),
	       StringToInt( ymdhms + 8,  10, 2 ),
	       StringToInt( ymdhms + 10, 10, 2 ),
	       StringToInt( ymdhms + 12, 10, 2 ) ) );
}

inline
DateTime &
DateTime::yyyymmddhhmmss( const char * ymd, const char * hms )
{
  return( set( StringToInt( ymd,     10, 4 ),
	       StringToInt( ymd + 4, 10, 2 ),
	       StringToInt( ymd + 6, 10, 2 ),
	       StringToInt( hms,     10, 2 ),
	       StringToInt( hms + 2, 10, 2 ),
	       StringToInt( hms + 4, 10, 2 ) ) );
}

inline
std::string
DateTime::yyyymmdd( void ) const
{
  char tmp[16];
  snprintf( tmp, sizeof( tmp )
	    ,"%04d%02d%02d"
	    ,m_tm.tm_year + 1900
	    ,m_tm.tm_mon + 1
	    ,m_tm.tm_mday );
  return( std::string( tmp ) );
}

inline
DateTime &
DateTime::yyyymmdd( const char * ymd )
{
  return( setDate( StringToInt( ymd,      10, 4 ),
		   StringToInt( ymd + 4,  10, 2 ),
		   StringToInt( ymd + 6,  10, 2 ) ) );
}

inline
std::string
DateTime::yymmdd( void ) const
{
  char tmp[16];
  snprintf( tmp, sizeof( tmp )
	    ,"%02d%02d%02d"
	    ,m_tm.tm_year % 100
	    ,m_tm.tm_mon + 1
	    ,m_tm.tm_mday );
  return( std::string( tmp ) );
}

inline
DateTime &
DateTime::yymmdd( const char * ymd )
{
  return( setDate( StringToInt( ymd,      10, 2 ),
		   StringToInt( ymd + 2,  10, 2 ),
		   StringToInt( ymd + 4,  10, 2 ) ) );
}

inline
std::string
DateTime::hhmmss( void ) const
{
  char tmp[16];
  snprintf( tmp, sizeof( tmp )
	    ,"%02d%02d%02d"
	    ,m_tm.tm_hour
	    ,m_tm.tm_min
	    ,m_tm.tm_sec );
  return( std::string( tmp ) );
}

inline
DateTime &
DateTime::hhmmss( const char * hms )
{
  return( setTime( StringToInt( hms,      10, 2 ),
		   StringToInt( hms + 2,  10, 2 ),
		   StringToInt( hms + 4,  10, 2 ) ) );
}

inline
std::string
DateTime::yyyy_mm_dd_hh_mm_ss( void ) const
{
  char tmp[32];
  snprintf( tmp, sizeof( tmp )
	    ,"%04d-%02d-%02d %02d:%02d:%02d"
	    ,m_tm.tm_year + 1900
	    ,m_tm.tm_mon + 1
	    ,m_tm.tm_mday
	    ,m_tm.tm_hour
	    ,m_tm.tm_min
	    ,m_tm.tm_sec );
  return( std::string( tmp ) );
}


inline
std::string
DateTime::str( const char * fmt ) const
{
  char tmp[1024];
  strftime(tmp, sizeof( tmp ), fmt, &m_tm );
  return( std::string( tmp ) );
}

inline
DateTime &
DateTime::set(
  const char * str,
  const char * fmt
  )
{
  bool lcl = isLocal();
  memset(&m_tm,0,sizeof(m_tm));
  if( strptime( str, fmt, &m_tm ) ) {
    m_seconds = TimetFrom( m_tm );
    if( lcl ) {
      memcpy( &m_tm, localtime( &m_seconds ), sizeof( m_tm ) );
    } else {
      memcpy( &m_tm, gmtime( &m_seconds ), sizeof( m_tm ) );
    }
  } else {
    memset( &m_tm, 0, sizeof( m_tm ) );
    m_seconds = 0;
  }
  return( *this );
}

inline
DateTime &
DateTime::set(
  int 	year,
  int 	month,
  int	day,
  int 	hour,
  int	min,
  int	sec
  )
{
  m_seconds = TimetFrom( year, month, day, hour, min, sec );
  if( m_seconds ) {
    if( m_tm.tm_gmtoff ) {
      memcpy( &m_tm, localtime( &m_seconds ), sizeof( m_tm ) );
    } else {
      memcpy( &m_tm, gmtime( &m_seconds ), sizeof( m_tm ) );
    }
  } else {
    memset( &m_tm, 0, sizeof( m_tm ) );
  }
  return( *this );
}

inline
DateTime &
DateTime::set( const struct tm & tmTime )
{
  return( set( 1900 + tmTime.tm_year,
	       tmTime.tm_mon+1,
	       tmTime.tm_mday,
	       tmTime.tm_hour,
	       tmTime.tm_min,
	       tmTime.tm_sec ) );
}

inline
DateTime &
DateTime::setDate(
  int 	year,
  int 	month,
  int	day
  )
{
  time_t tod = m_seconds % SecPerDay;
  m_seconds = TimetFrom( year, month, day, 0, 0, 0 );
  m_seconds += tod;
  if( m_seconds ) {
    if( m_tm.tm_gmtoff ) {
      memcpy( &m_tm, localtime( &m_seconds ), sizeof( m_tm ) );
    } else {
      memcpy( &m_tm, gmtime( &m_seconds ), sizeof( m_tm ) );
    }
  } else {
    memset( &m_tm, 0, sizeof( m_tm ) );
  }
  return( *this );
}

inline
DateTime &
DateTime::setTime(
  uint16_t hour,
  uint16_t min,
  uint16_t sec
  )
{
  m_tm.tm_hour = hour;
  m_tm.tm_min  = min;
  m_tm.tm_sec  = sec;
  m_seconds -= m_seconds % SecPerDay;
  m_seconds += (hour * SecPerHour);
  m_seconds += (min * SecPerMin);
  m_seconds += sec;
  return( *this );
}

inline
bool
DateTime::isValid(
  int year,
  int month,
  int day,
  int hour,
  int min,
  int sec
  )
{
  return( ( ( year >= 0 && year <= 99 )
	    || ( year <= MaxYear && year >= MinYear ) )
	  && ( month > 0 && month <= 12 )
	  && ( day > 0 && ( day <= DaysInMonth[ month-1 ]
			    || ( IsLeapYear( year )
				 && month == 2 && day == 29 ) ) )
	  && ( hour >= 0 && hour < 24 )
	  && ( min >= 0 && min < 60 )
	  && ( sec >= 0 && sec < 60 ) );
}

inline
bool
DateTime::isValid( const struct tm & tm )
{
  return( isValid( tm.tm_year + 1900,
		   tm.tm_mon + 1,
		   tm.tm_mday,
		   tm.tm_hour,
		   tm.tm_min,
		   tm.tm_sec ) );
}

inline
DateTime &
DateTime::setValid(
  int year,
  int month,
  int day,
  int hour,
  int min,
  int sec
  )
{
  if( isValid( year, month, day, hour, min, sec ) ) {
    set( year, month, day, hour, min, sec );
  } else {
    m_seconds = 0;
  }
  return( *this );
}

inline
DateTime &
DateTime::setValid(
  const char * str,
  const char * fmt
  )
{
  // note strftime allows 2/31 :(
  if( StringTo( m_tm, str, fmt ) && isValid( m_tm ) ) {
    m_seconds = TimetFrom( m_tm );
  } else {
    memset( &m_tm, 0, sizeof( m_tm ) );
    m_seconds = 0;
  }
  return( *this );
}

inline
DateTime &
DateTime::setValidYYMMDD( const char * ymd )
{
  uint16_t y,m,d;
  if( StringTo( y, ymd, 10, 2 )
      && StringTo( m, ymd + 2, 10, 2 )
      && StringTo( d, ymd + 4, 10, 2 ) ) {
    setValid( y, m, d );
  } else {
    m_seconds = 0;
    memset( &m_tm, 0, sizeof( m_tm ));
  }
  return(*this);
}

inline
DateTime &
DateTime::setValidYYYYMMDD( const char * ymd )
{
  uint16_t y,m,d;
  if( StringTo( y, ymd, 10, 4 )
      && StringTo( m, ymd + 4, 10, 2 )
      && StringTo( d, ymd + 6, 10, 2 ) ) {
    setValid( y, m, d );
  } else {
    m_seconds = 0;
    memset( &m_tm, 0, sizeof( m_tm ));
  }
  return(*this);
}

inline
DateTime &
DateTime::setValidHHMM( const char * hm )
{
  uint16_t h,m;
  if( StringTo( h, hm, 10, 2 )
      && StringTo( m, hm + 2, 10, 2 )
      && 0 <= h && h < 24
      && 0 <= m && m < 60) {
    hour( h );
    minute( m );
  } else {
    m_seconds = 0;
    memset( &m_tm, 0, sizeof( m_tm ));
  }
  return(*this);
}


inline
DateTime &
DateTime::setValidHHMMSS( const char * hms )
{
  uint16_t h,m,s;
  if( StringTo( h, hms, 10, 2 )
      && StringTo( m, hms + 2, 10, 2 )
      && StringTo( s, hms + 4, 10, 2 )
      && 0 <= h && h < 24
      && 0 <= m && m < 60
      && 0 <= s && s < 60 ) {
    hour( h );
    minute( m );
    second( s );
  } else {
    m_seconds = 0;
    memset( &m_tm, 0, sizeof( m_tm ));
  }
  return(*this);
}

inline
DateTime &
DateTime::add( const DateTime & dt )
{
  m_seconds += dt.timet();
  if( m_tm.tm_gmtoff ) {
    memcpy( &m_tm, localtime( &m_seconds ), sizeof( m_tm ) );
  } else {
    memcpy( &m_tm, gmtime( &m_seconds ), sizeof( m_tm ) );
  }
  return( *this );
}

inline
DateTime &
DateTime::add( long sec )
{
  m_seconds += sec;
  if( m_tm.tm_gmtoff ) {
    memcpy( &m_tm, localtime( &m_seconds ), sizeof( m_tm ) );
  } else {
    memcpy( &m_tm, gmtime( &m_seconds ), sizeof( m_tm ) );
  }
  return( *this );
}

inline
DateTime &
DateTime::addSec( long sec )
{
  return( add( sec ) );
}

inline
DateTime &
DateTime::addMin( long minutes )
{
  return( add( minutes * SecPerMin ) );
}

inline
DateTime &
DateTime::addHour( long hours )
{
  return( add( hours * SecPerHour ) );
}

inline
DateTime &
DateTime::addDay( long days )
{
  return( add( days * SecPerDay ) );
}

inline
DateTime::operator time_t () const
{
  return( timet() );
}


inline
bool
DateTime::operator ==( const DateTime & two ) const
{
  return( timet() == two.timet() );
}

inline
bool
DateTime::operator < ( const DateTime & two ) const
{
  return( timet() < two.timet() );
}

inline
bool
DateTime::operator != ( const DateTime & rhs ) const
{
  return( ! (*this == rhs) );
}

inline
bool
DateTime::operator > ( const DateTime & rhs ) const
{
  return( rhs < *this );
}

inline
bool
DateTime::operator <= ( const DateTime & rhs ) const
{
  return( ! (rhs < *this) );
}

inline
bool
DateTime::operator >= ( const DateTime & rhs ) const
{
  return( ! (*this < rhs) );
}

inline
bool
DateTime::operator == ( time_t rhs ) const
{
  return( timet() == rhs );
}

inline
bool
DateTime::operator < ( time_t rhs ) const
{
  return( timet() < rhs );
}

inline
bool
DateTime::operator != ( time_t rhs ) const
{
  return( ! (*this == rhs) );
}

inline
bool
DateTime::operator > ( time_t rhs ) const
{
  return( rhs < *this );
}

inline
bool
DateTime::operator <= ( time_t rhs ) const
{
  return( ! (rhs < *this) );
}

inline
bool
DateTime::operator >= ( time_t rhs ) const
{
  return( ! (*this < rhs) );
}

inline
time_t
DateTime::operator - ( const DateTime & rhs ) const
{
  return( timet() - rhs.timet() );
}

inline
time_t
DateTime::operator - ( const time_t rhs ) const
{
  return( timet() - rhs );
}

// Compare - return the diff beween 2 DateTime values
inline
int
compare( const DateTime & one, const DateTime & two )
{
  return( one.compare( two ) );
}

inline
time_t
operator - ( const time_t lhs, const DateTime & rhs )
{
  return( lhs - rhs.timet() );
}

inline
std::ostream & operator<<( std::ostream & dest, const DateTime & obj )
{
  return( obj.toStream( dest ) );
}

}; // namespace clue

/*
  Quick Start:

  	DateTime    	dt( time(0) );

  	std::cout << dt << endl; 	// output gmt time

  	dt.setTimeZone();	// set to local time

  	std::cout << dt << endl; 	// output local time;

  	dt.addDay( 5 );     	// add 5 days to the datetime

  	long dayOfWeek = dt.getDayOfWeek();


  DataTypes:

  	DateTime    class

  Constructors:

	DateTime( void )

	    sets the initial value to current local time.

  	DateTime( time_t setTime, bool addLocal = false );
  	    use 'setTime' for the initial value. If addLocal is true,
  	    the local (according to TZ) time zone offset will be added.

  	DateTime( time_t day, time_t timeOfDay );
  	    use 'day' and 'timeOfDay' to set the initial value.

  	DateTime( const char * yymmdd, const char * hhmmss )
  	    set the initial value by converting the 'yymmdd' and
  	    'hhmmss' strings.

  	DateTime( int year, int month, int day,
  	    	  int hour = 0, int min = 0, int sec = 0 )
  	    set the initial value from year, month, day, hour, min & sec.
  	    The year can be either 2 or 4 digits (95 or 1995). The month
  	    must be between 1 -> 12. The day is the day of the month and
  	    has a range of 1 -> 31.

  	DateTime( const struct tm & tmTime )
  	    set the initial value from the tmTime. 'tmTime' is translated
  	    as a 'GMT' value.

  	DateTime( const char * timeString )
  	    set the initial value from 'timeString' the format must be
  	    '2/20/95 13:40:50'. The time portion is not required and
  	    leading '0' are ignored.

  Destructors:

  	~DateTime( void )
  	    no special actions taken.

  Public Interface:

  	time_t
  	getTimeT( void ) const;
  	    return the current value as a time_t.

  	long
  	getSecOfDay( void ) const;
  	    return the number of seconds since midnight. (0 -> 86399)

  	short
  	getHour( void ) const;
  	    return the hour of the day in 24 hour format. (0 -> 23)

  	short
  	getMinute( void ) const;
  	    return the minute of the hour. (0 -> 59)

  	short
  	getSecond( void ) const;
  	    return the second of the minute. (0 -> 59)

  	virtual
  	DateOfWeek
  	getDayOfWeek( void ) const;
  	    return the day of the week. (sunday = 0) (0->6)

  	short
  	getDayOfYear( void ) const;
  	    return day of the year. ( 1 -> 366 )
  	    non-const version sets the internal tm to improve performance.

  	short
  	getDayOfYear( void );
  	    return day of the year. ( 1 -> 366 )
  	    non-const version sets the internal tm to improve performance.

  	short
  	getDayOfMonth( void ) const;
  	    return the day of the month. (1 -> 31)
  	    non-const version sets the internal tm to improve performance.

  	short
  	getDayOfMonth( void );
  	    return the day of the month. (1 -> 31)
  	    non-const version sets the internal tm to improve performance.

  	short
  	getMonth( void ) const
  	    return the month of the year. (1 -> 12)
  	    non-const version sets the internal tm to improve performance.

  	short
  	getMonth( void )
  	    return the month of the year. (1 -> 12)
  	    non-const version sets the internal tm to improve performance.

  	short
  	getYearOfCentury( void ) const
  	    return the year of the century. (0 -> 99)
  	    Both 1930 and 2030 will return '30'.
  	    non-const version sets the internal tm to improve performance.

  	short
  	getYearOfCentury( void )
  	    return the year of the century. (0 -> 99)
  	    Both 1930 and 2030 will return '30'.
  	    non-const version sets the internal tm to improve performance.

  	short
  	getYear( void ) const;
  	    return the year. ( all four digits - 1995, 2005 )
  	    non-const version sets the internal tm to improve performance.

  	short
  	getYear( void )
  	    return the year. ( all four digits - 1995, 2005 )
  	    non-const version sets the internal tm to improve performance.

  	const char *
  	getString( char * buffer = 0, const char * fmt = 0 )
  	    return a string representation of the date/time. If
  	    'buffer' is not 0, the string will be placed in it, otherwise
  	    a static internal bufferr will be used. If fmt is not 0 (i.e. a
  	    valid string), strftime will use 'fmt' to format the
  	    string. Otherwise, the default format will be used. The default
  	    format is '02/05/95 03:15:30' unless the year is < 1950 or >
  	    2000, then it is '02/05/2010 03:15:30' (4 digit year).

  	const char *
  	getString( char * buffer = 0, const char * fmt = 0 ) const
  	    return a string representation of the date/time. If
  	    'buffer' is not 0, the string will be placed in it, otherwise
  	    a static internal bufferr will be used. If fmt is 0, the default
  	    valid string), strftime will use 'fmt' to format the
  	    string. Otherwise, the default format will be used. The default
  	    format is '02/05/95 03:15:30' unless the year is < 1950 or >
  	    2000, then it is '02/05/2010 03:15:30' (4 digit year).

  	short
  	getOffset( void ) const
  	    return the current timezone offset being used. Normally this
  	    is 0. It is set by calls to 'setTimeZone'

  	bool
  	isLocal( void ) const
  	    return true if a timezone has been set.

  	bool
    	isDST( void )
  	    return true if a timezone is set and daylight savings time is
  	    in effect.

  	bool
  	isDST( void ) const
  	    return true if a timezone is set and daylight savings time is
  	    in effect.

  	const char *
  	getTimeZone( void ) const
  	    return the name of the timezone that has been set. If no
  	    timezone is set, 0 is returned.

  	static
	const char *
  	getSysTimeZone( void )
  	    return the name of the current system time zone.
  	    i.e (CST6CDT). Uses the TZ environment variable.

  	time_t
  	setTimeT( time_t timeSec = 0 )
  	    set the date/time to the specified value. Any timezone is
  	    reset to GMT.
  	    Returns the previous date/time value.

     	time_t
  	set( time_t timeSec, bool addLocal = false )
  	    set the date/time to the specific value. if addLocal
  	    is true, the local timezone offset ( according to TZ env var )
  	    will be added to the time. Any timezone is reset to GMT.
  	    Returns the previous date/time value.

  	time_t
  	set( const char * dateString, const char * fmt = 0 )
  	    set the date/time by converting the'dateString'. If 'fmt' is 0,
  	    the string is expected to be in '1/5/94 03:04:00' format.
  	    When using this format, neither the seconds, or the time is
  	    required (ie 1/1/92 & 1/1/95 05:00 is ok).
          If 'fmt' is not 0, strptime will use it to translate the string.
          Any timezone is reset to GMT.
  	    Returns the previous date/time value.

  	time_t
  	set( int year, int month, int day,
  	     int hour = 0, int min = 0, int sec = 0)
  	    set the date/time from year, month, day, hour, min, sec.
          Any timezone is reset to GMT.
  	    Returns the previous date/time value.

  	time_t
  	set( const struct tm & tmTime )
  	    set the date/time from the 'tmTime' structure. The values in
  	    'tmTime' are treated as GMT values. The timezone is reset to
  	    GMT.
  	    Returns the previous date/time value.

  	bool
  	setValid( int year, int month, int day,
  	    	  int hour = 0, int min = 0, int sec = 0 )
  	    set the date/time according to year, month, day, hour, min & sec.
  	    These value are checked to be sure they are in range. If
  	    any value is not in range, the date/time value is set to 0
  	    and a flag is set so 'good()' will return false. The year
  	    range has been limited to 1970 -> 2050, 0 -> 50, 70 -> 99.
  	    The timezone is reset to GMT.
  	    Returns true if succeeded

  	bool
  	setValid( const char * dateString, const char * fmt = 0 )
  	    set the date/time by converting the'dateString'. If 'fmt' is 0,
  	    the string is expected to be in '1/5/94 03:04:00' format.
  	    When using this format, neither the seconds, or the time is
  	    requried (ie 1/1/92 & 1/1/95 05:00 is ok). If 'fmt' is
  	    not 0, strptime will use it to translate the string.
  	    The values are checked to be sure they are in range. If
  	    any value is not in range, the date/time value is set to 0
  	    and a flag is set so 'good()' will return false. The timezone
  	    is reset to GMT.
  	    Returns true if succeeded

  	bool
  	setYYYYMMDD( const char * yyyymmdd )
  	    set the 'date' by translating 'yyyymmdd'.  The string does NOT
  	    have to be NULL terminated. The time and timezone are not modified.
  	    Example string (19950130)
  	    Returns true if succeeded

  	bool
  	setYYMMDD( const char * yymmdd )
  	    set the 'date' by translating 'yymmdd'.  The string does NOT
  	    have to be NULL terminated.  'yy' values between 00 and 50 are
  	    considered to be for the next century (ie 05 = 2005).
  	    The time and timezone are not modified.
          Example string (950130)
  	    Returns true if succeeded

  	time_t
  	setHHMMSS( const char * hhmmss )
  	    set the 'time' by translating 'hhmmss'. The string does NOT
  	    have to be NULL terminated. The date and timezone are not
  	    modified.
          Example string (155005 = 3:50:05 pm)
  	    Returns the previous date/time value.

  	time_t
  	setYear( short year )
  	    set the year. If year is < 50, it is considered to be
  	    for the next century (10 = 2010). WARNING: If current value
  	    is 2/29/92 (leap year) and you setYear( 95 ) (non leap year),
  	    the new value will be 3/1/95.
  	    Returns the previous date/time value.

  	time_t
  	setMonth( short month )
  	    set the month. WARNING: this function is VERY literal. If
   	    the current value is 1/31/95 and you 'setMonth( 6 )' you
  	    will end up with 7/1/95 (june only has 30 days). It also does
  	    NOT verify the input value, 'setMonth(13)' will have undefined
  	    results.
  	    Returns the previous date/time value.

  	time_t
  	setDayOfYear( short dayOfYear );
  	    set the day of the year. WARNING: a value of 370 will increment
  	    to the next year, day 5.
  	    Returns the previous date/time value.

  	time_t
  	setDayOfMonth( short dayOfMonth );
  	    set day of the month. WARNING: if your current value
  	    is 2/1/95 and you 'setDayOfMonth( 30 )' you would end up
  	    with '3/2/95'.
  	    Returns the previous date/time value.

  	time_t
  	setHour( short hour )
  	    set the hour of the day.
  	    Returns the previous date/time value.

  	time_t
  	setMinute( short minute )
  	    set the minute of the hour.
  	    Returns the previous date/time value.

  	time_t
  	setSecond( short second )
  	    set the second of the minute.
  	    Returns the previous date/time value.

  	long
  	setTimeZone( const char * zone = 0 )
  	    set the timezone. If 'zone' is 0, the 'TZ' environment
  	    variable will be used to determine the correct timezone.
  	    If 'zone'is not 0, it should be the same format as
  	    the 'TZ' environment variable (ie CST6CDT).
  	    Returns the number of seconds offset from GMT that was added
  	    to the current value.

  	DateTime &
	add( const DateTime & dt )
  	    add the DateTime to the current value.
  	    Returns a reference to self

  	DateTime &
  	add( long seconds = 1 )
  	    add the seconds to the date/time value.
  	    Returns a reference to self

  	DateTime &
  	addSec( long seconds = 1 )
  	    add the seconds to the date/time value.
  	    Returns a reference to self

  	DateTime &
  	addMin( long minutes = 1 )
  	    add the minutes to the date/time value
  	    Returns a reference to self

  	DateTime &
  	addHour( long hours = 1 )
  	    add the hours to the date/time value.
  	    Returns a reference to self

  	DateTime &
  	addDay( long days = 1 )
  	    add the days to the datd/time value.
  	    Returns a reference to self

  	void
  	setTm( void )
  	    set the internal tm struct for the current date/time value.
  	    This call will pre-assign the year, month, day of month,
  	    and day of year for the current value. It is provided so
  	    these values do not have to be recalculated for multible
  	    'get' calls.

   	int
  	compare( const DateTime & two ) const
  	    return the difference between 'two' and self. If self
  	    is > two, a > 0 value will be returned. If self is == two, a
  	    value of 0 will be returned. If self is < two, a < 0 value will
  	    be returned.  Only the actual date/time value is used
  	    for comparison

  	operator time_t ( void ) const;
  	    return the current date/time as a time_t value.

  	operator const char * ( void ) const
    	    return the current date/time as strings. The getString
  	    method is used to provide to string.

  	int
  	operator == ( const DateTime & rhs ) const;
  	    return true if 'two' is equal to self. Only the actual
  	    date time value is used for comparison.

  	int
  	operator != ( const DateTime & rhs ) const;
  	    return true if 'two' is not equal to self. Only the actual
  	    date time value is used for comparison.

  	virtual
    	const char *
  	getClassName( void ) const;
  	    return the name of this class.

  	virtual
  	bool
  	good( void ) const
  	    return true if no detected errors exist. Only setValid will
  	    detect an invalid date/time value.

  	virtual
  	const char *
  	error( void ) const
  	    return a string describing the current error state.

  Other Accociated Functions:

  	std::ostream &
  	operator <<( std::ostream & dest, const DateTime & obj );
  	    send a formated string of the current date/time to 'dest'
  	    The format is '02/03/95 15:13:03'.

  	int
  	compare( const DateTime & one, const DateTime & two )
  	    return the difference between 'one' and 'two'. If one
  	    is > two, a > 0 value will be returned. If one is == two, a
  	    value of 0 will be returned. If one is < two, a < 0 value will
  	    be returned.  Only the actuall date/time value is used
  	    for comparison
*/
#endif // ! def _clue_DateTime_hpp_
