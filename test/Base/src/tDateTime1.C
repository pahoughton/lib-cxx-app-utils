//
// File:        tDateTime1.C
// Desc:        
//
//  Test DateTime Constructors
//
//  	DateTime( time_t setTime = 0, Bool addLocal = FALSE );
//      DateTime( time_t day, time_t timeOfDay );
//      DateTime( const char * yymmdd, const char * hhmmss );
//      DateTime( int year, int month, int day,
//	    	  int hour = 0, int min = 0, int sec = 0 );
//      DateTime( const struct tm & tm );
//      DateTime( const char * timeString );
//
// Author:      Paul Houghton x2309 - (houghton@shoe.wiltel.com)
// Created:     11/03/94 08:56 
//
// Revision History:
//
// $Log$
// Revision 2.1  1995/11/10 12:49:05  houghton
// Change to Version 2
//
// Revision 1.1  1995/02/20  14:24:45  houghton
// Complete DateTime class test
//
//
//
static const char * RcsId =
"$Id$";

#include <ClueTest.hh>

#include <DateTime.hh>

int
tDateTime1( void )
{

  {
    DateTime dt;

    if( dt.getTimeT() != 0 ) ERROR;

    cout << dt << endl;
  }

  {
    time_t  when = 699342350;	    // is 2/29/92 05:45:50 (gmt)

    DateTime dtOneArg( when );
    DateTime dtGmt( when, FALSE );
    DateTime dtLocal( when, TRUE );

    cout << asctime( gmtime( &when ) );
    cout << dtOneArg << endl;
    cout << dtGmt << endl;

    cout << asctime( localtime( &when ) );
    cout << dtLocal << endl;    
  }
  
  {
    const char * dateString = "2/1/95 05:45:50";
    
    struct tm 	tm;
    strptime( dateString, "%m/%d/%y %H:%M:%S", &tm );

    time_t  datePart = YearMonthDayToTimeT( tm.tm_year, tm.tm_mon + 1, tm.tm_mday );
    time_t  timePart = HourMinSecToTimeT( tm.tm_hour, tm.tm_min, tm.tm_sec );
    
    DateTime	dt(datePart, timePart);

    if( dt.getTimeT() != datePart + timePart )
      {
	ERROR;
      }
    time_t tt = dt.getTimeT();
    
    cout << dateString << endl;
    cout << asctime( gmtime( &tt ) );
    cout << dt << endl;

  }
	  
  {
    const char *    yymmdd = "950205junk";
    const char *    hhmmss = "150550junk";
    
    DateTime	dt( yymmdd, hhmmss );

    cout << yymmdd << ' ' << hhmmss << endl;
    cout << dt << endl;
  }

  {
    int	    year = 95;
    int     month = 2;
    int     day = 5;
    int	    hour = 18;
    int	    min = 15;
    int	    sec = 30;
      
    DateTime	dt( year, month, day, hour, min, sec );

    cout << year << ' ' << month << ' ' << day << ' '
	 << hour << ' ' << min << ' ' << sec << endl;
    cout << dt << endl;
  }

  {
  
    int	    year = 92;
    int     month = 3;
    int     day = 1;
    int	    hour = 18;
    int	    min = 15;
    int	    sec = 30;

    struct tm tm;

    tm.tm_year = year;
    tm.tm_mon = month - 1;
    tm.tm_mday = day;
    tm.tm_hour = hour;
    tm.tm_min = min;
    tm.tm_sec = sec;

    DateTime	dt( tm );

    cout << year << ' ' << month << ' ' << day << ' '
	 << hour << ' ' << min << ' ' << sec << endl;
    cout << dt << endl;
  }

  {
    const char * dateString = "2/29/92 05:45:50";

    DateTime dt( dateString );

    cout << dateString << endl;
    cout << dt << endl;
  }
  
  return( 0 );
}

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
