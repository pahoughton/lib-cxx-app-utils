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

#if !defined( CLUE_SHORT_FN )
#include <ClueConfig.hh>
#include <ctime>
#else
#include <ClueCfg.hh>
#include <ctime>
#endif

extern const long   CLUE_GVAR_T SecPerMin;
extern const long   CLUE_GVAR_T SecPerHour;
extern const long   CLUE_GVAR_T SecPerDay;
extern const long   CLUE_GVAR_T SecPerYear;

extern const long   CLUE_GVAR_T MinPerHour;
extern const long   CLUE_GVAR_T MinPerDay;

extern const int    CLUE_GVAR_T DaysInMonth[];
extern const int    CLUE_GVAR_T MonthDayOfYear[];
extern const char * CLUE_GVAR_T Months[];
extern const char * CLUE_GVAR_T AbbrMonths[];
extern const char * CLUE_GVAR_T WeekDays[];
extern const char * CLUE_GVAR_T AbbrWeekDays[];

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

#if !defined( CLUE_SHORT_FN )
#include <DateTimeUtils.ii>
#else
#include <DtTmUtil.ii>
#endif

#endif // ! def _DateTimeUtils_hh_ 

