/*********************************************************************
 *
 * File:        strptime.c
 * Project:	StlUtils
 * Desc:
 *
 *  
 *
 * Notes:
 *
 *  Swipped from Linux libc-5.4.33 (9/16/97). See Copywrite at end of file
 *
 * Author:	Paul A. Houghton - (paul.houghton@wcom.com)
 * Created:	09/16/97 10:02
 *
 * Revision History: (See end of file for Revision Log)
 *
 *  Last Mod By:    $Author$
 *  Last Mod:	    $Date$
 *  Version:	    $Revision$
 *
 *********************************************************************/

#include <ctype.h>
#include <limits.h>
#include <string.h>
#include <time.h>

static const char *
DayOfWeekNames[] =
{
  "Sunday",
  "Monday",
  "Tuesday",
  "Wednesday",
  "Thursday",
  "Friday",
  "Saturday"
};

static const char *
DayOfWeekAbbr[] =
{
  "Sun",
  "Mon",
  "Tue",
  "Wed",
  "Thu",
  "Fri",
  "Sat"
};

static const char *
MonthNames[] =
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
  "December"
};

static const char *
MonthAbbr[] =
{
  "Jan", "Feb", "Mar", "Apr", "May", "Jun",
  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

#define AM_STR "AM"
#define PM_STR "PM"


#define match_char(ch1, ch2) if (ch1 != ch2) return NULL
#define match_string(cs1, s2)						      \
  ({ size_t len = strlen (cs1);						      \
     int result = strncasecmp (cs1, s2, len) == 0;			      \
     if (result) s2 += len;						      \
     result; })
/* We intentionally do not use isdigit() for testing because this will
   lead to problems with the wide character version.  */
     
#define get_number_width(from, to, max_digits )					\
  do {										\
    const char * frp = rp;							\
    val = 0;									\
    if (*rp < '0' || *rp > '9')							\
      return NULL;								\
    do {									\
      val *= 10;								\
      val += *rp++ - '0';							\
    } while ( (rp - frp) <= max_digits && *rp >= '0' && *rp <= '9');		\
    if (val < from || val > to)							\
      return NULL;								\
  } while (0)
     
#define get_number(from, to)						      \
  do {									      \
    val = 0;								      \
    if (*rp < '0' || *rp > '9')						      \
      return NULL;							      \
    do {								      \
      val *= 10;							      \
      val += *rp++ - '0';						      \
    } while (val * 10 <= to && *rp >= '0' && *rp <= '9');		      \
    if (val < from || val > to)						      \
      return NULL;							      \
  } while (0)
#define get_alt_number(from, to)					      \
  do {									      \
    const char *alts = _NL_CURRENT (LC_TIME, ALT_DIGITS);		      \
    val = 0;								      \
    while (*alts != '\0')						      \
      {									      \
	size_t len = strlen (alts);					      \
	if (strncasecmp (alts, rp, len) == 0)				      \
	  break;							      \
	alts = strchr (alts, '\0') + 1;					      \
	++val;								      \
      }									      \
    if (*alts == '\0')							      \
      return NULL;							      \
  } while (0)
#define recursive(new_fmt)						      \
  do {									      \
    if (*new_fmt == '\0')						      \
      return NULL;							      \
    rp = strptime (rp, new_fmt, tm);					      \
    if (rp == NULL)							      \
      return NULL;							      \
  } while (0)
  
     
char *
strptime(
  const char * buf,
  const char * format,
  register struct tm * tm
  )
{
  const char *rp;
  const char *fmt;
  int cnt;
  size_t val;
  int have_I, is_pm;

  rp = buf;
  fmt = format;
  have_I = is_pm = 0;

  while (*fmt != '\0')
    {
      /* A white space in the format string matches 0 more or white
	 space in the input string.  */
      if (isspace (*fmt))
	{
	  while (isspace (*rp))
	    ++rp;
	  ++fmt;
	  continue;
	}

      /* Any character but `%' must be matched by the same character
	 in the iput string.  */
      if (*fmt != '%')
	{
	  match_char (*fmt++, *rp++);
	  continue;
	}

      ++fmt;
      switch (*fmt++)
	{
	case '%':
	  /* Match the `%' character itself.  */
	  match_char ('%', *rp++);
	  break;
	case 'a':
	case 'A':
	  /* Match day of week.  */
	  for (cnt = 0; cnt < 7; ++cnt)
	    {
	      if (match_string (DayOfWeekNames[ cnt ], rp))
		break;
	      if (match_string (DayOfWeekAbbr[cnt], rp))
		break;
	    }
	  if (cnt == 7)
	    /* Does not match a weekday name.  */
	    return NULL;
	  tm->tm_wday = cnt;
	  break;
	case 'b':
	case 'B':
	case 'h':
	  /* Match month name.  */
	  for (cnt = 0; cnt < 12; ++cnt)
	    {
	      if (match_string (MonthNames[cnt], rp))
		break;
	      if (match_string (MonthAbbr[cnt], rp))
		break;
	    }
	  if (cnt == 12)
	    /* Does not match a month name.  */
	    return NULL;
	  tm->tm_mon = cnt;
	  break;
	case 'c':
	  /* Match locale's date and time format.  */
	  recursive ("%a %b %d %H:%M:%S %Y");
	  break;
	case 'C':
	  /* Match century number.  */
	  get_number (0, 99);
	  /* We don't need the number.  */
	  break;
	case 'd':
	case 'e':
	  /* Match day of month.  */
	  get_number (1, 31);
	  tm->tm_mday = val;
	  break;
	case 'D':
	  /* Match standard day format.  */
	  recursive ("%m/%d/%y");
	  break;
	case 'H':
	  /* Match hour in 24-hour clock.  */
	  get_number (0, 23);
	  tm->tm_hour = val;
	  have_I = 0;
	  break;
	case 'I':
	  /* Match hour in 12-hour clock.  */
	  get_number (1, 12);
	  tm->tm_hour = val - 1;
	  have_I = 1;
	  break;
	case 'j':
	  /* Match day number of year.  */
	  get_number (1, 366);
	  tm->tm_yday = val - 1;
	  break;
	case 'm':
	  /* Match number of month.  */
	  get_number (1, 12);
	  tm->tm_mon = val - 1;
	  break;
	case 'M':
	  /* Match minute.  */
	  get_number (0, 59);
	  tm->tm_min = val;
	  break;
	case 'n':
	case 't':
	  /* Match any white space.  */
	  while (isspace (*rp))
	    ++rp;
	  break;
	case 'p':
	  /* Match locale's equivalent of AM/PM.  */
	  if (match_string ( AM_STR, rp))
	    break;
	  if (match_string (PM_STR, rp))
	    {
	      is_pm = 1;
	      break;
	    }
	  return NULL;
	case 'r':
	  recursive ("%I:%M:%S %p");
	  break;
	case 'R':
	  recursive ("%H:%M");
	  break;
	case 'S':
	  get_number (0, 61);
	  tm->tm_sec = val;
	  break;
	case 'T':
	  recursive ("%H:%M:%S");
	  break;
	case 'U':
	case 'V':
	case 'W':
	  get_number (0, 53);
	  /* XXX This cannot determine any field in TM.  */
	  break;
	case 'w':
	  /* Match number of weekday.  */
	  get_number (0, 6);
	  tm->tm_wday = val;
	  break;
	case 'x':
	  recursive ("%m/%d/%y");
	  break;
	case 'X':
	  recursive ("%H:%M:%S");
	  break;
	case 'y':
	  /* Match year within century.  */
	  get_number_width (0, 99, 2);
	  tm->tm_year = val;
	  break;
	case 'Y':
	  /* Match year including century number.  */
	  /* Use 9999 instead of INT_MAX. That is best we can do.
	   * Let others worry about a year 9999 problem. H.J. */
	  get_number_width (0, 9999, 4);
	  tm->tm_year = val - 1900;
	  break;
	case 'Z':
	  /* XXX How to handle this?  */
	  break;
	default:
	  return NULL;
	}
    }

  if (have_I && is_pm)
    tm->tm_hour += 12;
  
  return (char *) rp;
}

/* strptime - Convert a string representation of time to a time value.
Copyright (C) 1996 Free Software Foundation, Inc.
This file is part of the GNU C Library.
Contributed by Ulrich Drepper <drepper@cygnus.com>, 1996.

The GNU C Library is free software; you can redistribute it and/or
modify it under the terms of the GNU Library General Public License as
published by the Free Software Foundation; either version 2 of the
License, or (at your option) any later version.

The GNU C Library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Library General Public
License along with the GNU C Library; see the file COPYING.LIB.  If
not, write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */

/*
 *
 * Revision Log:
 *
 * $Log$
 * Revision 4.1  1997/09/17 15:13:19  houghton
 * Changed to Version 4
 *
 * Revision 3.2  1997/09/17 11:09:12  houghton
 * Changed: renamed library to StlUtils.
 *
 * Revision 3.1  1997/09/16 16:05:17  houghton
 * Initial Version (from Linux libc-5.4.33).
 *
 *
 */
