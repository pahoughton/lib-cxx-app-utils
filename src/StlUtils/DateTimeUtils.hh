#ifndef _DateTimeUtils_hh_
#define _DateTimeUtils_hh_
//
// File:        DateTimeUtils.hh
// Project:	StlUtils
// Desc:        
//
//
//
// Quick Start: - short example of class usage
//
// Author:      Paul Houghton - (paul.houghton@wcom.com)
// Created:     05/02/95 06:32
//
// Revision History: (See end of file for Revision Log)
//
//  Last Mod By:    $Author$
//  Last Mod:	    $Date$
//  Version:	    $Revision$
//
//  $Id$
//

#include <StlUtilsConfig.hh>
#include <ctime>
#include <cstring>


extern const time_t STLUTILS_GVAR_T SecPerMin;
extern const time_t STLUTILS_GVAR_T SecPerHour;
extern const time_t STLUTILS_GVAR_T SecPerDay;
extern const time_t STLUTILS_GVAR_T SecPerYear;

extern const time_t STLUTILS_GVAR_T MinPerHour;
extern const time_t STLUTILS_GVAR_T MinPerDay;

extern const time_t STLUTILS_GVAR_T MinTimeT;
extern const time_t STLUTILS_GVAR_T MaxTimeT;

extern const time_t STLUTILS_GVAR_T MinYear;
extern const time_t STLUTILS_GVAR_T MaxYear;

extern const int    STLUTILS_GVAR_T DaysInMonth[];
extern const int    STLUTILS_GVAR_T DaysInMonthLeap[];

extern const int    STLUTILS_GVAR_T MonthDayOfYear[];
extern const int    STLUTILS_GVAR_T MonthDayOfYearLeap[];

extern const char * STLUTILS_GVAR_T Months[];
extern const char * STLUTILS_GVAR_T AbbrMonths[];
extern const char * STLUTILS_GVAR_T WeekDays[];
extern const char * STLUTILS_GVAR_T AbbrWeekDays[];

#if !defined( DAYOFWEEK_ENUM )
#define DAYOFWEEK_ENUM 1

typedef enum {
  Sunday = 0,
  Monday,
  Tuesday,
  Wednesday,
  Thursday,
  Friday,
  Saturday
} DayOfWeek;

#endif

#if !defined( STLUTILS_HAS_STRPTIME )
extern "C"
char *
STLUTILS_FUNCT_T
strptime( char * b, const char * fmt, struct tm * t );
#endif



#include <DateTimeUtils.ii>

//
// Detail Documentation
//
// Types:
//
//	enum DayOfWeek
//	    The days of the week where Sunday is 0 and Saturday is 6
//
// Variables:
//
//	extern const time_t STLUTILS_GVAR_T SecPerMin;
//	    The number of seconds in a minute (60)
//
//	extern const time_t STLUTILS_GVAR_T SecPerHour;
//	    The number of seconds in a hour (60 * 60)
//
//	extern const time_t STLUTILS_GVAR_T SecPerDay;
//	    The number of seconds in a day (60 * 60 * 24)
//
//	extern const time_t STLUTILS_GVAR_T SecPerYear;
//	    The number of seconds in a year (60 * 60 * 24 * 365)
//	
//	extern const time_t STLUTILS_GVAR_T MinPerHour;
//	    The number of minutes in a hour (60)
//
//	extern const time_t STLUTILS_GVAR_T MinPerDay;
//	    The number of minutes in a day (60 * 24)
//	
//	extern const time_t STLUTILS_GVAR_T MinTimeT;
//	    The minimum time_t value
//
//	extern const time_t STLUTILS_GVAR_T MaxTimeT;
//	    The maximum time_t value
//	
//	extern const time_t STLUTILS_GVAR_T MinYear;
//	    The minimum year possible for a time_t value
//
//	extern const time_t STLUTILS_GVAR_T MaxYear;
//	    The maximum year possible for a time_t value
//
//	extern const int    STLUTILS_GVAR_T DaysInMonth[];
//	    The number of days in each month where Jan is month 0 so,
//	    DaysInMonth[1] == 28.
//
//	extern const int    STLUTILS_GVAR_T MonthDayOfYear[];
//	    The number of days since the beging of the year for the first day
//	    of the month where Jan is month 0 so
//	    MonthDayOfYear[1] == 31 && MonthDayOfYear[2] == 58
//
//	extern const char * STLUTILS_GVAR_T Months[];
//	    The full names of the months where Jan is month 0 so,
//	    Months[2] == "March"
//
//	extern const char * STLUTILS_GVAR_T AbbrMonths[];
//	    The first three letters of the month where Jan is month 0 so,
//	    AbbrMonths[9] == "Oct"
//
//	extern const char * STLUTILS_GVAR_T WeekDays[];
//	    The full name of the days of the week where sunday is 0 so,
//	    WeekDays[ 2 ] = "Tuesday"
//
//	extern const char * STLUTILS_GVAR_T AbbrWeekDays[];
//	    The 3 char abbeviated names of the days of the week where
//	    sunday is 0, so AbbrWeekDays[ 4 ] == "Thu"
//
//	
// Functions:
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
//	void
//	YYMMDDtoYYYYMMDD( char * dest, const char * src )
//	    convert 970304 to 19970304. if the first digit is < 5
//	    the year is assumed to be 2000, so 050304 will be 20050304.
//
// Example:
//
// See Also:
//
// Files:
//
//	DateTimeUtils.hh
//	DateTimeUtils.ii
//	libStlUtils.a
//
// Documented Ver: 4.3
//
// Tested Ver: 4.3
//
// Revision Log:
//
// $Log$
// Revision 4.5  1999/03/02 12:45:10  houghton
// Added DaysInMonthLeap
// Added MonthDayOfYearLeap
//
// Revision 4.4  1998/10/13 16:18:38  houghton
// Change: strptime is now part of libCommon.
//
// Revision 4.3  1997/12/20 16:08:33  houghton
// Added Detail descriptions.
//
// Revision 4.2  1997/12/19 12:48:22  houghton
// Cleanup
//
// Revision 4.1  1997/09/17 15:12:21  houghton
// Changed to Version 4
//
// Revision 3.3  1997/09/17 11:08:18  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.2  1997/08/24 23:07:04  houghton
// Changed type of global const values to time_t.
//
// Revision 3.1  1996/11/14 01:23:39  houghton
// Changed to Release 3
//
// Revision 2.2  1996/04/27 12:59:36  houghton
// Cleanup
//
// Revision 2.1  1995/11/10 12:40:33  houghton
// Change to Version 2
//
// Revision 1.3  1995/11/05  15:28:32  houghton
// Revised
//
//
#endif // ! def _DateTimeUtils_hh_ 

