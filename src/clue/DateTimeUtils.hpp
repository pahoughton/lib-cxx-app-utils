#ifndef _clue_DateTimeUtils_hpp_
#define _clue_DateTimeUtils_hpp_
/* 1995-05-02 (cc) Paul Houghton <paul4hough@gmail.com>

   Various DateTime constants and functions.
*/
#include <ctime>
#include <cstring>
#include <cctype>


namespace clue {
extern const time_t SecPerMin;
extern const time_t SecPerHour;
extern const time_t SecPerDay;
extern const time_t SecPerYear;

extern const time_t MinPerHour;
extern const time_t MinPerDay;

extern const time_t MinTimeT;
extern const time_t MaxTimeT;

extern const time_t MinYear;
extern const time_t MaxYear;

extern const int DaysInMonth[];
extern const int DaysInMonthLeap[];

extern const int MonthDayOfYear[];
extern const int MonthDayOfYearLeap[];

extern const char * Months[];
extern const char * AbbrMonths[];
extern const char * WeekDays[];
extern const char * AbbrWeekDays[];

typedef enum {
  Sunday = 0,
  Monday,
  Tuesday,
  Wednesday,
  Thursday,
  Friday,
  Saturday
} DayOfWeek;


inline
time_t
SecInTimeT( time_t sec )
{
  return(sec % 60 );
}

inline
time_t
SecOfDay( time_t sec )
{
  return( sec % (60 * 60 * 24) );
}

inline
time_t
MinInTimeT( time_t sec )
{
  return( (sec % (60 * 60)) / 60 );
}

inline
time_t
HourInTimeT( time_t sec )
{
  return( (sec % (60 * 60 * 24)) / (60 * 60) );
}

inline
time_t
HoursInTimeT( time_t sec )
{
  return( sec / (60 * 60) );
}

inline
time_t
DaysInTimeT( time_t sec )
{
  return( (sec / (60 * 60 * 24) ) );
}

inline
time_t
DateInTimeT( time_t sec )
{
  return( sec - (sec % (60 * 60 * 24) ) );
}

inline
bool
IsLeapYear( int year)
{
  return( ( ( !(year % 4) ) && ( (year % 100) || !(year % 400) ) ));
}

inline
void
YYMMDDtoYYYYMMDD( char * dest, const char * src )
{
  if( isdigit( src[0] )  )
    {
      if( src[0] < '5' )
	memcpy( dest, "20", 2 );
      else
	memcpy( dest, "19", 2 );
      memcpy( dest + 2, src, 6 );
    }
  else
    {
      memset( dest, ' ', 8 );
    }
}

bool
IsTimetDst( time_t val );

time_t
TimetFrom( int y, int m, int d, int h, int min, int s );

time_t
TimetFrom( const struct tm & tm );


}; // namespace clue

/*
 Types:

	enum DayOfWeek
	    The days of the week where Sunday is 0 and Saturday is 6

 Variables:

	extern const time_t SecPerMin;
	    The number of seconds in a minute (60)

	extern const time_t SecPerHour;
	    The number of seconds in a hour (60 * 60)

	extern const time_t SecPerDay;
	    The number of seconds in a day (60 * 60 * 24)

	extern const time_t SecPerYear;
	    The number of seconds in a year (60 * 60 * 24 * 365)

	extern const time_t MinPerHour;
	    The number of minutes in a hour (60)

	extern const time_t MinPerDay;
	    The number of minutes in a day (60 * 24)

	extern const time_t MinTimeT;
	    The minimum time_t value

	extern const time_t MaxTimeT;
	    The maximum time_t value

	extern const time_t MinYear;
	    The minimum year possible for a time_t value

	extern const time_t MaxYear;
	    The maximum year possible for a time_t value

	extern const int DaysInMonth[];
	    The number of days in each month where Jan is month 0 so,
	    DaysInMonth[1] == 28.

	extern const int MonthDayOfYear[];
	    The number of days since the beging of the year for the first day
	    of the month where Jan is month 0 so
	    MonthDayOfYear[1] == 31 && MonthDayOfYear[2] == 58

	extern const char * Months[];
	    The full names of the months where Jan is month 0 so,
	    Months[2] == "March"

	extern const char * AbbrMonths[];
	    The first three letters of the month where Jan is month 0 so,
	    AbbrMonths[9] == "Oct"

	extern const char * WeekDays[];
	    The full name of the days of the week where sunday is 0 so,
	    WeekDays[ 2 ] = "Tuesday"

	extern const char * AbbrWeekDays[];
	    The 3 char abbeviated names of the days of the week where
	    sunday is 0, so AbbrWeekDays[ 4 ] == "Thu"


 Functions:

  	long
  	SecInTimeT( long sec );
  	    return the second of the minute.

  	long
  	MinInTimeT( long sec )
  	    return the minute of the hour.

  	long
  	HourInTimeT( long sec )
  	    return the hour of the day.

  	long
  	HoursInTimeT( long sec )
  	    return the number of hours.

  	long
  	DaysInTimeT( long sec )
  	    return the number of days.

  	long
  	DateInTimeT( long sec )
  	    return the date portion only.

	void
	YYMMDDtoYYYYMMDD( char * dest, const char * src )
	    convert 970304 to 19970304. if the first digit is < 5
	    the year is assumed to be 2000, so 050304 will be 20050304.

	bool
	IsTimetDst( time_t val );
	    Returns true if the time of val is between the 2 am First
	    Sunday of April and 2 am the last Sunday of October

  	long
  	SecInTimeT( long sec );
  	    return the second of the minute.

  	long
  	MinInTimeT( long sec )
  	    return the minute of the hour.

  	long
  	HourInTimeT( long sec )
  	    return the hour of the day.

  	long
  	HoursInTimeT( long sec )
  	    return the number of hours.

  	long
  	DaysInTimeT( long sec )
  	    return the number of days.

  	long
  	DateInTimeT( long sec )
  	    return the date portion only.

	void
	YYMMDDtoYYYYMMDD( char * dest, const char * src )
	    convert 970304 to 19970304. if the first digit is < 5
	    the year is assumed to be 2000, so 050304 will be 20050304.
*/
#endif // ! def _clue_DateTimeUtils_hpp_
