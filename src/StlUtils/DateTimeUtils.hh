#ifndef _DateTimeUtils_hh_
#define _DateTimeUtils_hh_
//
// File:        DateTimeUtils.hh
// Desc:        
//
//
//
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     05/02/95 06:32
//
// Revision History:
//
// $Log$
// Revision 1.1  1995/11/05 13:23:22  houghton
// Initaial implementation
//
//

#include <ClueConfig.hh>
#include <ctime>

extern const long   SecPerMin;
extern const long   SecPerHour;
extern const long   SecPerDay;
extern const long   SecPerYear;

extern const long   MinPerHour;
extern const long   MinPerDay;

extern const int    DaysInMonth[];
extern const int    MonthDayOfYear[];
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

#include <DateTimeUtils.ii>

#endif // ! def _DateTimeUtils_hh_ 

