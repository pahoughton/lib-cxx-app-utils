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
extern const int    STLUTILS_GVAR_T MonthDayOfYear[];
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

#include <DateTimeUtils.ii>

//
// Detail Documentation
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
// $Log$
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

