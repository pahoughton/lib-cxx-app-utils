//
// File:        DateTimeUtils.C
// Desc:        
//
//  
//  
// Author:      Paul Houghton - (houghton@cworld.wiltel.com)
// Created:     05/02/95 06:57 
//
// Revision History:
//
// $Log$
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


#if !defined( CLUE_SHORT_FN )
#include "DateTimeUtils.hh"
#else
#include "DtTmUtil.hh"
#endif

CLUE_FUNCT_VERSION(
  DateTimeUtils,
  "$Id$" );

const long   SecPerMin	    = 60;
const long   SecPerHour	    = 60 * 60;
const long   SecPerDay	    = 60 * 60 * 24;
const long   SecPerYear	    = 60 * 60 * 24 * 365;

const long   MinPerHour	    = 60;
const long   MinPerDay	    = 60 * 24;


const int DaysInMonth[] =
{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, 0};

const int MonthDayOfYear[] =
{ 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365, 0};

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

