//
// File:        DateTimeUtils.C
// Project:	StlUtils ()
// Desc:        
//
//  Compiled sources for DateTimeUtils
//  
// Author:      Paul Houghton - (paul.houghton@mci.com)
// Created:     05/02/95 06:57 
//
// Revision History: (See end of file for Revision Log)
//
//  $Author$ 
//  $Date$ 
//  $Name$ 
//  $Revision$ 
//  $State$ 
//

#include "DateTimeUtils.hh"
#include <climits>

STLUTILS_FUNCT_VERSION(
  DateTimeUtils,
  "$Id$ " );

const time_t  SecPerMin	    = 60;
const time_t  SecPerHour    = 60 * 60;
const time_t  SecPerDay	    = 60 * 60 * 24;
const time_t  SecPerYear    = 60 * 60 * 24 * 365;

const time_t  MinPerHour    = 60;
const time_t  MinPerDay	    = 60 * 24;

const time_t  MinTimeT	    = LONG_MIN;
const time_t  MaxTimeT	    = LONG_MAX;

const time_t  MinYear	    = 1970 + (LONG_MIN / (60 * 60 * 24 * 365));
const time_t  MaxYear	    = 1970 + (LONG_MAX / (60 * 60 * 24 * 365));

const int DaysInMonth[] =
{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, 0};

const int DaysInMonthLeap[] =
{ 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, 0};

const int MonthDayOfYear[] =
{ 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365, 0};

const int MonthDayOfYearLeap[] =
{ 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366, 0};

const char * Months[] =
{
  "January",
  "February",
  "March",
  "April",
  "May",
  "June",
  "July",
  "August",
  "September",
  "October",
  "November",
  "December",
  0
};

const char * AbbrMonths[] =
{
  "Jan",
  "Feb",
  "Mar",
  "Apr",
  "May",
  "Jun",
  "Jul",
  "Aug",
  "Sep",
  "Oct",
  "Nov",
  "Dec",
  0
};

const char * WeekDays[] =
{
  "Sunday",
  "Monday",
  "Tuesday",
  "Wednesday",
  "Thursday",
  "Friday",
  "Saturday",
  0
};

const char * AbbrWeekDays[] =
{
  "Sun",
  "Mon",
  "Tue",
  "Wed",
  "Thu",
  "Fri",
  "Sat",
  0
};

// Revision Log:
//
// 
// %PL%
// 
// $Log$
// Revision 6.1  2003/08/09 11:22:41  houghton
// Changed to version 6
//
// Revision 5.3  2003/08/09 11:20:58  houghton
// Changed ver strings.
//
// Revision 5.2  2001/07/26 19:29:00  houghton
// *** empty log message ***
//
// Revision 5.1  2000/05/25 10:33:15  houghton
// Changed Version Num to 5
//
// Revision 4.2  1999/03/02 12:45:04  houghton
// Added DaysInMonthLeap
// Added MonthDayOfYearLeap
//
// Revision 4.1  1997/09/17 15:12:21  houghton
// Changed to Version 4
//
// Revision 3.3  1997/09/17 11:08:18  houghton
// Changed: renamed library to StlUtils.
//
// Revision 3.2  1997/08/24 23:07:51  houghton
// Cleanup comments.
// Changed type of global const values to time_t.
// Added MinTimeT, MaxTimeT, MinYear & MaxYear.
//
// Revision 3.1  1996/11/14 01:23:38  houghton
// Changed to Release 3
//
// Revision 2.2  1996/04/27 12:59:31  houghton
// Cleanup
//
// Revision 2.1  1995/11/10 12:40:33  houghton
// Change to Version 2
//
// Revision 1.2  1995/11/05  14:44:32  houghton
// Ports and Version ID changes
//
//
