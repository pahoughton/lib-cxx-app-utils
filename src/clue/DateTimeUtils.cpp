// 1995-05-02 (cc) Paul Houghton <paul4hough@gmail.com>

#include "DateTimeUtils.hpp"
#include <climits>

namespace clue {

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

}; // namespace clue
