#ifndef _DateTime_hh_
#define _DateTime_hh_
//
// File:        DateTime.hh
// Desc:        
//              
//
// Author:      Paul Houghton x2309 - (houghton@shoe)
// Created:     02/09/94 12:24
//
// Revision History:
//
// 
// $Log$
// Revision 1.2  1994/08/15 20:54:54  houghton
// Split Mapped out of mapped avl.
// Fixed a bunch of bugs.
// Fixed for ident of object modules.
// Prep for Rating QA Testing
//
// Revision 1.1  1994/06/06  13:19:38  houghton
// Lib Clue beta version used for Rating 1.0
//
//

#include <time.h>
#include <iomanip.h>
#include <DateTime.h>
#include <stdio.h>

//
// Generic time_t manipulators
//

inline long
SecInTimeT( long sec )
{
  return(sec % 60 );
}

inline long
MinInTimeT( long sec )
{
  return( (sec % (60 * 60)) / 60 );
}

inline long
HourInTimeT( long sec )
{
  return( (sec % (60 * 60 * 24)) / (60 * 60) );
}

inline long
DaysInTimeT( long sec )
{
  return( (sec / SEC_PER_DAY ) );
}


class DateTime
{
public:

      // Constructors;
  inline DateTime( time_t setTime = 0 );
  inline DateTime( time_t day, time_t timeOfDay );
  inline DateTime( const char * yymmdd, const char * hhmmss );
  inline DateTime( int year, int month, int day, int hour = 0, int min = 0, int sec = 0 );
  
  inline DateTime( const struct tm & tm );
  inline DateTime( const char * timeString );

  virtual ~DateTime( void );
  
  inline int		isValid( void ) const;
  
  inline time_t		getTimeT( void ) const;
  inline long		getSecOfDay( void ) const;
  inline short		getHour( void ) const;
  inline short		getMinute( void ) const;
  inline short		getSecond( void ) const;

  inline short		getYear( void ) const;
  inline short		getYearOfCentury( void ) const;
  inline short		getMonth( void ) const;
  inline short		getDayOfMonth( void ) const;
  inline short  	getDayOfYear( void ) const;

      //
      // The non const versions set the internal struct tm so
      // the valuse do not have to be recalced. If you need these
      // values repeditivly, you may want to call 'setTm(void)'
      // right after construction to increase access performance
      //
  inline short		getYear( void );
  inline short		getYearOfCentury( void );
  inline short		getMonth( void );
  inline short		getDayOfMonth( void );
  inline short  	getDayOfYear( void );


  virtual int		getDayOfWeek( void ) const;

  inline long           getSysOffset( void ) const;

  inline void		setYYMMDD( const char * yymmdd);
  inline void		setHHMMSS( const char * hhmmss);
  
  inline void 		setTimeT( time_t timeSec );
  inline void		setDate( const DateTime & dateTwo );
//  inline void		setTm( const struct tm & time );
//  inline void		setYear( short year );
//  inline void		setMonth( short month );
//  inline void		setDayOfYear( short dayOfYear );
//  inline void		setDayOfMonth( short dayOfMonth );
//  inline void		setHour( short hour );
//  inline void		setMinute( short minute );
//  inline void		setSecond( short second );
  
  inline void setTm( void );
  inline const DateTime &   addSeconds( long seconds );
  inline const DateTime &   addHours( long hours );

  inline operator time_t () const;

friend ostream & operator<<( ostream & dest, const DateTime & time );
friend ostream & operator<<( ostream & dest, DateTime & time );
  
protected:

  
private:

  time_t      seconds;
  struct tm   tm;
  time_t      tmSec;
};


//
// Inline Methods
//

inline 
DateTime::DateTime( time_t setTime )
{
  seconds = setTime;
  tmSec = 0;
}

inline 
DateTime::DateTime( time_t day, time_t timeOfDay )
{
  seconds = day + timeOfDay;
  tmSec = 0;
}

inline 
DateTime::DateTime( const char * yymmdd, const char * hhmmss )
{
  seconds = 0;
  tmSec = 0;
  setHHMMSS( hhmmss );
  setYYMMDD( yymmdd );
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
  tmSec = 0;

  int	leapCount = 0;
  int   index = 0;

  month--;
  day--;
  
  leapCount = ((year - 70) + 2) / 4;
  
  seconds = ((year - 70) * SEC_PER_YEAR) + (leapCount * SEC_PER_DAY );
  
  for( index = 0; index < month; index++ )
    {
      seconds += SEC_PER_DAY * DaysInMonth[index];
    }
  
  if( IsLeapYear( year ) && month > 2 )
    {
      seconds += SEC_PER_DAY;
    }
  
  seconds += SEC_PER_DAY * day;
  
  seconds += hour * SEC_PER_HOUR;
  seconds += min * SEC_PER_MIN;
  seconds += sec;
}


inline 
DateTime::DateTime( const struct tm & setTime )
{
  seconds = mktime( (struct tm *)&setTime );
  tmSec = 0;
}


inline int
DateTime::isValid( void ) const
{
  return( (seconds == 0 ) ? FALSE : TRUE );
}

inline time_t
DateTime::getTimeT( void ) const
{
  return( seconds );
}

inline long
DateTime::getSecOfDay( void ) const
{
  return( seconds % SEC_PER_DAY );
}

inline short
DateTime::getHour( void ) const
{
  return( HourInTimeT( seconds ) );
}

inline short
DateTime::getMinute( void ) const
{
  return( MinInTimeT( seconds ) );
}

inline short
DateTime::getSecond( void ) const
{
  return( SecInTimeT( seconds ) );
}



inline short
DateTime::getYear( void )
{
  setTm();
  return( tm.tm_year + 1900 );	
}

inline short
DateTime::getYear( void ) const
{
  if( tmSec == seconds )
    {
      return( tm.tm_year + 1900 );
    }
  else
    {
      return( gmtime( &seconds )->tm_year );
    }
}

inline short
DateTime::getYearOfCentury( void )
{
  return( getYear() % 100 );
}

inline short
DateTime::getYearOfCentury( void ) const
{
  return( getYear() % 100 );
}

inline short
DateTime::getMonth( void )
{
  setTm();
  return( tm.tm_mon + 1 );
}

inline short
DateTime::getMonth( void ) const
{
  if( tmSec == seconds )
    {
      return( tm.tm_mon + 1 );
    }
  else
    {
      return( gmtime( &seconds )->tm_mon + 1 );
    }
}

inline short
DateTime::getDayOfMonth( void )
{
  setTm();
  return( tm.tm_mday );
}


inline short
DateTime::getDayOfMonth( void ) const
{
  if( tmSec == seconds )
    {
      return( tm.tm_mday );
    }
  else
    {
      return( gmtime( &seconds )->tm_mday );
    }
}
inline long
DateTime::getSysOffset( void ) const
{
  tzset();
  return( timezone );
}

inline void
DateTime::setYYMMDD( const char * yymmdd )
{
  seconds = YYMMDDtoTimeT( yymmdd ) + (seconds % SEC_PER_DAY );
}

inline void
DateTime::setHHMMSS( const char * hhmmss )
{
  seconds = (seconds - (seconds % SEC_PER_DAY)) + HHMMSStoTimeT( hhmmss );
}

inline void
DateTime::setTimeT( time_t timeSec )
{
  seconds = timeSec;
}


inline void
DateTime::setDate( const DateTime & dateTwo )
{
  seconds = (dateTwo.getTimeT() - dateTwo.getSecOfDay()) + getSecOfDay();
}



inline void
DateTime::setTm( void )
{
  if( tmSec != seconds )
    {
      memcpy( &tm, gmtime( &seconds ), sizeof( struct tm ) );
      tmSec = seconds;
    }
}

inline const DateTime &
DateTime::addSeconds( long sec )
{
  seconds += sec;
  return( *this );
}

inline const DateTime & 
DateTime::addHours( long hours )
{
  seconds += (hours * SEC_PER_HOUR );
  return( *this );
}

inline
DateTime::operator time_t () const
{
  return( seconds );
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
